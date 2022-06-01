/*
 * subg_radio.c
 *
 *  Created on: 2018. 7. 20.
 *      Author: sprit
 */
#include <stdlib.h>
#include <stdio.h>
#include <yes/yes_radio.h>
#include "assert.h"

#include "circular_queue.h"
#include "buffer_pool_allocator.h"
#include "command_interpreter.h"

#include "bsp.h"

#include "../app_common.h"
#include "yes_radio.h"
#include "user_data/user_data.h"

#include "my_uart.h"

Queue_t  txPacketQueue;
Queue_t  rxPacketQueue;
Queue_t  fwdPacketQueue;

volatile uint32_t txCount = 0;
uint32_t rxSquenceNum = 0;
extern volatile bool packetRx;
//extern volatile bool isTransmit;
extern volatile bool packetTx;

//SUB_GIGA_MESSAGE_t *reSubPacket;
//IEEE802154_MESSAGE_t *re2p4Packet;

uint8_t reTxData[128];

uint8_t reTxCount802154 = 0;
uint8_t reTxCountSubG = 0;

int rgb_delay = 1000;

static const RAIL_DataConfig_t railDataConfig = {
   .txSource = TX_PACKET_DATA,
   .rxSource = RX_PACKET_DATA,
   .txMethod = PACKET_MODE,
   .rxMethod = PACKET_MODE,
 };

const RAIL_IEEE802154_Config_t IEEE802154_config = {
    .addresses = NULL,
    .ackConfig = {
      .enable = true,
      .ackTimeout = 1000,
      .rxTransitions = {
        .success = RAIL_RF_STATE_RX,
        .error = RAIL_RF_STATE_RX // ignored
      },
      .txTransitions = {
        .success = RAIL_RF_STATE_RX,
        .error = RAIL_RF_STATE_RX // ignored
      }
    },
    .timings = {
        .idleToTx = 100,
        .idleToRx = 100,
        .rxToTx = 192,
        // Make txToRx slightly lower than desired to make sure we get to
        // RX in time
        .txToRx = 192 - 10,
        .rxSearchTimeout = 0,
        .txToRxSearchTimeout = 0
      },
    .framesMask = RAIL_IEEE802154_ACCEPT_STANDARD_FRAMES,
    .promiscuousMode = false,
    .isPanCoordinator = false
};

static uint8_t calc_crc( uint8_t *data, int len );
MAC_SUBGIGA_HEADER_t* getSubGigaHeader(SUB_GIGA_MESSAGE_t* msg);
uint8_t* getSubGigaData(SUB_GIGA_MESSAGE_t* msg);
RAIL_Status_t config2p4Ghz802154();
void ReTx_TimerExpired(RAIL_Handle_t railHandle);
void ReTxSubG_TimerExpired(RAIL_Handle_t railHandle);

void RgbTest_TimerExpired(RAIL_Handle_t railHandle);

void printPacket(char *cmdName,
                 uint8_t *data,
                 uint16_t dataLength,
                 RxPacketData_t *packetData);


static char packetPrintBuffer[(APP_MAX_PACKET_LENGTH + 1) * 5];

void QueueInit(void) {
	if (!queueInit(&txPacketQueue, MAX_QUEUE_LENGTH)) {
		while (1)
			;
	}

	if (!queueInit(&rxPacketQueue, MAX_QUEUE_LENGTH)) {
			while (1);
		}

	if (!queueInit(&fwdPacketQueue, MAX_QUEUE_LENGTH)) {
				while (1);
			}
}

void MakeSubGPacket(void) {
	//yes_subGiga_message_free();

	pSubGigaMessage = yes_subGiga_message_allocate();

	MAC_SUBGIGA_HEADER_t* pHeader = getSubGigaHeader(pSubGigaMessage);
	pHeader->frameCtrl = FRAME_CONTROL;
	pHeader->groupId = 0x12;
	pHeader->parent = 0xFF;
	pHeader->seqNum = ++txCount;
	pHeader->srcAddr =  gNodeId;
	//pSubGigaMessage->len = sizeof(SUB_GIGA_MESSAGE_t) + 1;
}



void SendSubG_TimeOut_TimerExpired(RAIL_Handle_t railHandle) {
	printf("SendSubG_TimeOut_TimerExpired \r\n");
	BSP_LedToggle(0);
	//RAIL_RadioState_t currentState = RAIL_GetRadioState(railHandle);
	//printf(" RAIL_RadioState_t : %d  \r\n", currentState);
	packetRx = true;
	reTxCountSubG = 0;
	//yes_subGiga_message_free();
	//memoryFree(txPacketMemoryHandle);
//	isTransmit = false;
	printf(" isTransmit = false \r\n");
}

void TxSubGPending(void) {
	if (!queueIsEmpty(&txPacketQueue)) {
		void *txPacketHandle = queueRemove(&txPacketQueue);
		SUB_GIGA_MESSAGE_t* txPacket = (SUB_GIGA_MESSAGE_t*) memoryPtrFromHandle(txPacketHandle);

		// Print the received packet and appended info
		if (txPacket != NULL) {

			//RAIL_SetTimer(railHandleSubG, 1000 * 200, RAIL_TIME_DELAY,
			//		&SendSubG_TimeOut_TimerExpired);
			RAIL_Idle(railHandleSubG, RAIL_IDLE, true);
//			RAIL_SetTxFifo(railHandleSubG, (uint8_t *) txPacket,txPacket->len + 1, txPacket->len + 1);
			RAIL_WriteTxFifo(railHandleSubG, (uint8_t *)txPacket, txPacket->len + 1, true);
			//RAIL_Status_t status = RAIL_StartCcaCsmaTx(railHandleSubG,
			//		gChannel_SubG, RAIL_TX_OPTIONS_DEFAULT, &CsmaConfig, NULL);
			RAIL_Status_t status = RAIL_StartTx(railHandleSubG,
					gChannel_SubG, RAIL_TX_OPTIONS_DEFAULT, NULL);

//			printf("status : %d \r\n", status);
		}
		// Free the memory allocated for this packet since we're now done with it
		memoryFree(txPacketHandle);
	}
}
#define MAX_TX_COUNT	0xFFFFFF

void SendMessageSubGiga(uint16_t dest, uint8_t* data, uint8_t length) {
	//yes_subGiga_message_free();
	printf("sendMessageSubGiga() %d \r\n", length);
	BSP_LedClear(0); //BSP_LedSet(1);/*20200507_gyuplus_revised*/

	reTxCountSubG = 0;

	void *txPacketMemoryHandle = NULL;

	// Get a memory buffer for the received packet data
	txPacketMemoryHandle = memoryAllocate(length + sizeof(SUB_GIGA_MESSAGE_t));
	SUB_GIGA_MESSAGE_t* txPacket = (SUB_GIGA_MESSAGE_t *) memoryPtrFromHandle(txPacketMemoryHandle);
	if (txPacket != NULL) {
		uint32_t sum;

		MAC_SUBGIGA_HEADER_t* pHeader = getSubGigaHeader(txPacket);
		pHeader->frameCtrl = FRAME_CONTROL;
		pHeader->groupId = 0x12;
		pHeader->parent = 0xFF;
		pHeader->seqNum = ++txCount;
		pHeader->srcAddr = gNodeId;
		pHeader->dstAddr = dest;
		if( txCount > MAX_TX_COUNT )
		{
			txCount = 0;
		}

		txPacket->len = sizeof(SUB_GIGA_MESSAGE_t) + length - 1;

		uint8_t* payload = getSubGigaData(txPacket);
		memcpy(payload, data, length);
		sum = calc_crc( (uint8_t*)txPacket, length + sizeof(SUB_GIGA_MESSAGE_t) );
		pHeader->seqNum |= ( sum << 24 ) & 0xFF000000;
		memcpy(&reTxData, txPacket, length + sizeof(SUB_GIGA_MESSAGE_t));


		// Take an extra reference to this rx packet pointer so it's not released
		memoryTakeReference(txPacketMemoryHandle);
		// Copy this received packet into our circular queue
		queueAdd(&txPacketQueue, txPacketMemoryHandle);

		// Queue 사용 안할 거면 아래 주석 해제 해야함.
		/*RAIL_SetTimer(railHandleSubG, 1000 * 200, RAIL_TIME_DELAY,
				&SendSubG_TimeOut_TimerExpired);
		RAIL_Idle(railHandleSubG, RAIL_IDLE, true);
		RAIL_SetTxFifo(railHandleSubG, (uint8_t *) txPacket,
				txPacket->len + 1, txPacket->len + 1);
		//RAIL_WriteTxFifo(railHandle, (uint8_t *)pSubGigaMessage, sizeof(SUB_GIGA_MESSAGE_t) + length, true);
		RAIL_Status_t status = RAIL_StartCcaCsmaTx(railHandleSubG,
				gChannel_SubG, RAIL_TX_OPTIONS_DEFAULT, &CsmaConfig, NULL);
		printf("status : %d \r\n", status);*/

		if (gReTxCountSubG > 0) {
			//printf("gReTxCountSubG : %d \r\n", gReTxCountSubG);
			RAIL_SetTimer(railHandleSubG, 1000 * 20, RAIL_TIME_DELAY,
					&ReTxSubG_TimerExpired);
			reTxCountSubG++;
		} else {
			if (gSysMode == SYS_MODE_RGB_TEST) {
				RAIL_SetTimer(railHandleSubG, rgb_delay * 1000, RAIL_TIME_DELAY,
						&RgbTest_TimerExpired);
			}
		}
	}

	memoryFree(txPacketMemoryHandle);
}

void ReTxSubG_TimerExpired(RAIL_Handle_t railHandle)
{
	//printf("send retxSubG %d \r\n", reSubPacket->len);
	// 0(2); /*20200507_gyuplus_revised*/
	void *txPacketMemoryHandle = NULL;
	SUB_GIGA_MESSAGE_t *reSubPacket = (SUB_GIGA_MESSAGE_t *)reTxData;
	txPacketMemoryHandle = memoryAllocate(reSubPacket->len + 1);
	reSubPacket = (SUB_GIGA_MESSAGE_t *) memoryPtrFromHandle(txPacketMemoryHandle);
	if (reSubPacket != NULL) {
		// Take an extra reference to this rx packet pointer so it's not released
		memoryTakeReference(txPacketMemoryHandle);
		// Copy this received packet into our circular queue
		queueAdd(&txPacketQueue, txPacketMemoryHandle);

		if (reTxCountSubG < gReTxCountSubG) {
			//printf("reTxCount802154 : %d \r\n", reTxCount802154);
			RAIL_SetTimer(railHandleSubG, 1000 * 20, RAIL_TIME_DELAY,
					&ReTxSubG_TimerExpired);
			reTxCountSubG++;
		} else {
			if (gSysMode == SYS_MODE_RGB_TEST) {
				RAIL_SetTimer(railHandle, rgb_delay * 1000, RAIL_TIME_DELAY,
						&RgbTest_TimerExpired);
			}
		}
	}
	memoryFree(txPacketMemoryHandle);
	//RAIL_CancelTimer(railHandle);
}

static uint8_t calc_crc( uint8_t *data, int len )
{
	uint8_t sum;
	int i;

	sum = 0x55;
	for( sum = 0, i = 0; i < len ; i++ )
	{
		sum ^= data[i];
	}
	return sum;
}

void RAILCb_GenericSubG(RAIL_Handle_t railHandle, RAIL_Events_t events) {
	(void) railHandle;
	//printf("SubG RAILCb_Generic \r\n");
	if (events & RAIL_EVENT_RX_PACKET_RECEIVED) {
		// Don't store the incoming packet, instead let RAIL drop it.
		printf("SubG RAIL_EVENT_RX_PACKET_RECEIVED \r\n");

		RAIL_RxPacketInfo_t packetInfo;
		RAIL_RxPacketHandle_t packetHandle = RAIL_GetRxPacketInfo(railHandle,
				RAIL_RX_PACKET_HANDLE_NEWEST, &packetInfo);
		uint16_t length = packetInfo.packetBytes;
		printf("Received packet(%d): \r\n", length);

		RxPacketData_t *rxPacket;
		void *rxPacketMemoryHandle = NULL;

		rxPacketMemoryHandle = memoryAllocate(length + sizeof(RxPacketData_t));
		rxPacket = (RxPacketData_t *) memoryPtrFromHandle(rxPacketMemoryHandle);

		//BSP_LedSet(0);


		if (rxPacket != NULL) {
			SUB_GIGA_MESSAGE_t *ptr;
			MAC_SUBGIGA_HEADER_t *pHeader;
			uint8_t sum = 0, tmp;
			// Read packet data into our packet structure
			RAIL_CopyRxPacket(rxPacket->dataPtr, &packetInfo);

			// Read the appended info into our packet structure
			rxPacket->dataLength = length;
			ptr = ( SUB_GIGA_MESSAGE_t * )rxPacket->dataPtr;
			pHeader = getSubGigaHeader(ptr);
			sum = ( pHeader->seqNum >> 24 ) & 0xFF;
			pHeader->seqNum &= MAX_TX_COUNT;
			tmp = calc_crc( (uint8_t *)ptr, length );
			if( tmp != sum )
			{
				memoryFree(rxPacketMemoryHandle);
				printf("check sum=%d,tmp=%d,len=%d\n", sum, tmp, length );
				return;
			}
			//rxPacket->dataLength = rxPacket->dataPtr[0];
			rxPacket->appendedInfo.timeReceived.timePosition =
					RAIL_PACKET_TIME_DEFAULT;
			rxPacket->appendedInfo.timeReceived.totalPacketBytes = 0;
			if (RAIL_GetRxPacketDetails(railHandle, packetHandle,
					&rxPacket->appendedInfo) != RAIL_STATUS_NO_ERROR) {
				// assert(false);

			}

			// Take an extra reference to this rx packet pointer so it's not released
			memoryTakeReference(rxPacketMemoryHandle);
			// Copy this received packet into our circular queue
			queueAdd(&rxPacketQueue, rxPacketMemoryHandle);
			//BSP_LedClear(0);
		}
		memoryFree(rxPacketMemoryHandle);

		packetRx = true;//
	}
	if (events & RAIL_EVENT_TX_PACKET_SENT) {
		printf("SubG RAIL_EVENT_TX_PACKET_SENT \r\n");
//		isTransmit = false;

		BSP_LedSet(0);//BSP_LedClear(1);/*20200507_gyuplus_revised*/

		/*RAIL_CancelTimer(railHandle);
		if (reTxCountSubG < gReTxCountSubG) {
			RAIL_SetTimer(railHandle, 1000 * 20, RAIL_TIME_DELAY,
					&ReTxSubG_TimerExpired);
			reTxCountSubG++;
		} else {
			reTxCountSubG = 0;
			if (gSysMode == SYS_MODE_RGB_TEST) {
				RAIL_SetTimer(railHandle2p4, 1000 * 1000, RAIL_TIME_DELAY,
						&RgbTest_TimerExpired);
			}
		}*/
		/*if (gSysMode == SYS_MODE_RGB_TEST) {
			RAIL_SetTimer(railHandle, 1000 * 1000, RAIL_TIME_DELAY,
					&RgbTest_TimerExpired);
		}*/

	}
	if (events & RAIL_EVENT_TX_UNDERFLOW) {
		printf("RAIL_EVENT_TX_UNDERFLOW \r\n");
	}
}

void SubGigaRx(void) {
	if (packetRx || RAIL_GetRadioState(railHandleSubG) == RAIL_RF_STATE_ACTIVE) {
		RAIL_RadioState_t currentState = RAIL_GetRadioState(railHandleSubG);
		//if (currentState == RAIL_RF_STATE_ACTIVE) {
			//printf(" RAIL_RadioState_t : %d  \r\n", currentState);
			//packetRx = true;
		//}

		packetRx = false;
		RAIL_Idle(railHandleSubG, RAIL_IDLE, true);
		RAIL_Status_t r = RAIL_StartRx(railHandleSubG, gChannel_SubG, NULL);
		//printf("SubGigaRx() starting.. : %d \r\n", r);
	}
}


void ReceivedPacketForwarding(void) {
	if (!queueIsEmpty(&rxPacketQueue)) {
		void *rxPacketHandle = queueRemove(&rxPacketQueue);
		RxPacketData_t *rxPacketData = (RxPacketData_t*) memoryPtrFromHandle(rxPacketHandle);

		if (rxPacketData != NULL) {
			//printPacket("rxPacket", rxPacketData->dataPtr,
			//		rxPacketData->dataLength, rxPacketData);
			SUB_GIGA_MESSAGE_t *packet =
					(SUB_GIGA_MESSAGE_t *) rxPacketData->dataPtr;

			MAC_SADDR_HEADER_t *header = (MAC_SADDR_HEADER_t*) &packet->header;
			printf("Sub-G sequence : %d \r\n", header->seqNum);

			//RAIL_Status_t status = config2p4Ghz802154();
			//printf("conf status : %d \r\n", status);
			//RAIL_Idle(railHandle2p4, RAIL_IDLE, true);
			initRadio802154();
			MakeIEEE802154Packet();
			SendMessageIEEE802154(YES_BCAST_ADDR, (uint8_t *)&packet->data, packet->len - sizeof(MAC_SUBGIGA_HEADER_t));

		}
		// Free the memory allocated for this packet since we're now done with it
		memoryFree(rxPacketHandle);
	}
}

void SendMessageIEEE802154(uint16_t dest, uint8_t* data, uint8_t length) {
	//printf("SendMessageIEEE802154() %d \r\n", length);

	BSP_LedClear(0);//BSP_LedSet(0);/*20200507_gyuplus_revised*/
	reTxCount802154 = 0;
	/*if (packetTx) {
		RAIL_CancelTimer(railHandle2p4);
		printf("RAIL_CancelTimer(railHandle2p4) \r\n");
		Send2p4_TimeOut_TimerExpired(railHandle2p4);
	}*/

	void *txPacketMemoryHandle = NULL;
	IEEE802154_MESSAGE_t *txPacket;
	packetTx = true;
	// Get a memory buffer for the send packet data
	txPacketMemoryHandle = memoryAllocate(sizeof(IEEE802154_MESSAGE_t) + length + 2);
	txPacket = (IEEE802154_MESSAGE_t *) memoryPtrFromHandle(txPacketMemoryHandle);
	if (txPacket != NULL) {
		MAC_SADDR_HEADER_t* pHeader = get2p4Header(txPacket);
		pHeader->frameCtrl = FRAME_CONTROL;
		pHeader->dstPanId = PAN_ID;
		pHeader->srcAddr = gNodeID;
		pHeader->seqNum = ++txCount;
		pHeader->srcAddr = gNodeId;
		pHeader->dstAddr = dest;

		txPacket->len = sizeof(IEEE802154_MESSAGE_t) + length + 1;

		uint8_t* payload = get2p4Data(txPacket);
		memcpy(payload, data, length);
		memcpy(reTxData, txPacket, length + sizeof(IEEE802154_MESSAGE_t) + 2);

		// Take an extra reference to this rx packet pointer so it's not released
		memoryTakeReference(txPacketMemoryHandle);
		// Copy this received packet into our circular queue
		queueAdd(&txPacketQueue, txPacketMemoryHandle);

		/*RAIL_SetTimer(railHandle2p4, 1000 * 200, RAIL_TIME_DELAY,
				&Send2p4_TimeOut_TimerExpired);
		RAIL_Idle(railHandle2p4, RAIL_IDLE, true);
		RAIL_SetTxFifo(railHandle2p4, (uint8_t *) txPacket, txPacket->len + 1,
				txPacket->len + 1);
		//RAIL_WriteTxFifo(railHandle, (uint8_t *)pSubGigaMessage, sizeof(SUB_GIGA_MESSAGE_t) + length, true);
		RAIL_Status_t status = RAIL_StartCcaCsmaTx(railHandle2p4,
				gChannel_2p4, RAIL_TX_OPTIONS_DEFAULT, &CsmaConfig, NULL);
		printf("status : %d \r\n", status);*/

		if (0 < gReTxCount802154) {
			//printf("reTxCount802154 : %d \r\n", reTxCount802154);
			RAIL_SetTimer(railHandle2p4, 1000 * 20, RAIL_TIME_DELAY,
					&ReTx_TimerExpired);
			reTxCount802154++;
		}
	}
	memoryFree(txPacketMemoryHandle);
}

void ReTx_TimerExpired(RAIL_Handle_t railHandle)
{
	//printf("2p4_ReTx_TimerExpired \n");
	/*BSP_LedSet(0);
	RAIL_SetTxFifo(railHandle, (uint8_t *)pMessage, pMessage->len, pMessage->len);
	//RAIL_WriteTxFifo(railHandle, (uint8_t *)pSubGigaMessage, pSubGigaMessage->len + 1, true);
	RAIL_StartCcaCsmaTx(railHandle, gChannel_2p4, RAIL_TX_OPTIONS_DEFAULT, &CsmaConfig, NULL);

	//RAIL_CancelTimer(railHandle);*/


	// 0(2);  /*20200507_gyuplus_revised*/
	void *txPacketMemoryHandle = NULL;
	IEEE802154_MESSAGE_t *re2p4Packet = (IEEE802154_MESSAGE_t *)reTxData;
	txPacketMemoryHandle = memoryAllocate(re2p4Packet->len + 1);
	re2p4Packet = (IEEE802154_MESSAGE_t *) memoryPtrFromHandle(txPacketMemoryHandle);
	if (re2p4Packet != NULL) {
		/*RAIL_SetTxFifo(railHandle, (uint8_t *) txPacket, txPacket->len,
				txPacket->len);
		//RAIL_WriteTxFifo(railHandle, (uint8_t *)pSubGigaMessage, pSubGigaMessage->len + 1, true);
		RAIL_StartCcaCsmaTx(railHandle, gChannel_2p4,
		RAIL_TX_OPTIONS_DEFAULT, &CsmaConfig, NULL);*/
		// Take an extra reference to this rx packet pointer so it's not released
		memoryTakeReference(txPacketMemoryHandle);
		// Copy this received packet into our circular queue
		queueAdd(&txPacketQueue, txPacketMemoryHandle);

		if (reTxCount802154 < gReTxCount802154) {
			//printf("reTxCount802154 : %d \r\n", reTxCount802154);
			RAIL_SetTimer(railHandle2p4, 1000 * 20, RAIL_TIME_DELAY,
					&ReTx_TimerExpired);
			reTxCount802154++;
		}
	}
	memoryFree(txPacketMemoryHandle);

}

void MakeIEEE802154Packet(void) {
	yes_2p4_message_free();
	pMessage = yes_2p4_message_allocate();

	MAC_SADDR_HEADER_t* pHeader = get2p4Header(pMessage);
	pHeader->frameCtrl = FRAME_CONTROL;
	pHeader->dstPanId = PAN_ID;
	//pHeader->dstAddr = YES_BCAST_ADDR;
	pHeader->srcAddr = gNodeId;
	//pSubGigaMessage->len = sizeof(SUB_GIGA_MESSAGE_t) + 1;
}



void RAILCb_Generic2p4(RAIL_Handle_t railHandle, RAIL_Events_t events) {
	(void) railHandle;
	//printf("2p4 RAILCb_Generic \r\n");
	if (events & RAIL_EVENT_RX_PACKET_RECEIVED) {
		// Don't store the incoming packet, instead let RAIL drop it.
		printf("2p4 RAIL_EVENT_RX_PACKET_RECEIVED \r\n");
	}
	if (events & RAIL_EVENT_TX_PACKET_SENT) {
		//printf("2p4 RAIL_EVENT_TX_PACKET_SENT \r\n");


		BSP_LedSet(0);//BSP_LedClear(0);			// Red LED /*20200507_gyuplus_revised*/
		/*RAIL_CancelTimer(railHandle);
		if (reTxCount802154 < gReTxCount802154) {
			//printf("reTxCount802154 : %d \r\n", reTxCount802154);
			RAIL_SetTimer(railHandle, 1000 * 20, RAIL_TIME_DELAY,
					&ReTx_TimerExpired);
			reTxCount802154++;
		} else {
			reTxCount802154 = 0;
		}*/

//		isTransmit = false;
		packetTx = false;
	}
	if (events & RAIL_EVENT_TX_UNDERFLOW) {
		printf("RAIL_EVENT_TX_UNDERFLOW \r\n");

		//packetRx = true;
	}
}

void Send2p4_TimeOut_TimerExpired(RAIL_Handle_t railHandle) {
	printf("Send2p4_TimeOut_TimerExpired \r\n");
	//RAIL_RadioState_t currentState = RAIL_GetRadioState(railHandle);
	//printf(" RAIL_RadioState_t : %d  \r\n", currentState);
	reTxCount802154 = 0;
//	isTransmit = false;
	packetTx = false;
}

/*void SendMessageIEEE802154(uint16_t dest, uint8_t* data, uint8_t length) {
	printf("SendMessageIEEE802154() %d \r\n", length);
	pMessage->len = sizeof(IEEE802154_MESSAGE_t) + length + 1;
	printf("pMessage->len : %d \r\n", pMessage->len);

	MAC_SADDR_HEADER_t* header = get2p4Header(pMessage);
	header->dstAddr = dest;
	header->seqNum = ++txCount;
	printf("h->frameCtrl : %x \r\n", header->frameCtrl);
	printf("h->dstAddr : %x \r\n", header->dstAddr);
	printf("h->srcAddr : %x \r\n", header->srcAddr);
	printf("h->seqNum : %d \r\n", header->seqNum);

	uint8_t* payload = get2p4Data(pMessage);
	memcpy(payload, data, length);

	BSP_LedSet(0);
	//RAIL_Idle(railHandle2p4, RAIL_IDLE, true);
	RAIL_SetTimer(railHandle2p4, 1000 * 200, RAIL_TIME_DELAY,&Send2p4_TimeOut_TimerExpired);
	RAIL_SetTxFifo(railHandle2p4, (uint8_t *)pMessage, pMessage->len, pMessage->len);
	//RAIL_WriteTxFifo(railHandle, (uint8_t *)pMessage, sizeof(SUB_GIGA_MESSAGE_t) + length, true);
	printf("channel : %d \r\n", gChannel_2p4);
	RAIL_Status_t status = RAIL_StartCcaCsmaTx(railHandle2p4, gChannel_2p4, RAIL_TX_OPTIONS_DEFAULT, &CsmaConfig, NULL);
	printf("status : %d \r\n", status);
}*/

void Tx2p4GPending(void) {
	if (!queueIsEmpty(&txPacketQueue)) {
		void *txPacketHandle = queueRemove(&txPacketQueue);
		IEEE802154_MESSAGE_t *txPacket = (IEEE802154_MESSAGE_t*) memoryPtrFromHandle(txPacketHandle);

		// Print the received packet and appended info
		if (txPacket != NULL) {

			//RAIL_SetTimer(railHandle2p4, 1000 * 200, RAIL_TIME_DELAY,
			//		&Send2p4_TimeOut_TimerExpired);
			//RAIL_Idle(railHandle2p4, RAIL_IDLE, true);
//			RAIL_SetTxFifo(railHandle2p4, (uint8_t *) txPacket,txPacket->len + 1, txPacket->len + 1);
			RAIL_WriteTxFifo(railHandle2p4, (uint8_t *)txPacket, txPacket->len + 1, true);
			RAIL_Status_t status = RAIL_StartCcaCsmaTx(railHandle2p4,
					gChannel_2p4, RAIL_TX_OPTIONS_DEFAULT, &CsmaConfig, NULL);
//			printf("status : %d \r\n", status);
		}
		// Free the memory allocated for this packet since we're now done with it
		memoryFree(txPacketHandle);
	}
}



void ByPassIEEE802154(uint8_t* data, uint8_t length) {

	BSP_LedClear(0);//BSP_LedSet(0);/*20200507_gyuplus_revised*/
	RAIL_SetTxFifo(railHandle2p4, (uint8_t *)data, length, length);
	//RAIL_WriteTxFifo(railHandle, (uint8_t *)pMessage, sizeof(SUB_GIGA_MESSAGE_t) + length, true);
	//printf("channel : %d \r\n", gChannel_2p4);
	RAIL_Status_t status = RAIL_StartCcaCsmaTx(railHandle2p4, gChannel_2p4, RAIL_TX_OPTIONS_DEFAULT, &CsmaConfig, NULL);
	//printf("status : %d \r\n", status);
}


MAC_SUBGIGA_HEADER_t* getSubGigaHeader(SUB_GIGA_MESSAGE_t* msg) {
	return ((void*)msg->header);
}

uint8_t* getSubGigaData(SUB_GIGA_MESSAGE_t* msg) {
	return ((void*)msg->data);
}

SUB_GIGA_MESSAGE_t* yes_subGiga_message_allocate() {
	return (SUB_GIGA_MESSAGE_t*) malloc(sizeof(SUB_GIGA_MESSAGE_t));
}

void yes_subGiga_message_free() {
	//printf("yes_packet.c: Freeing SUB_GIGA_MESSAGE_t %p\n", p);
	if (pSubGigaMessage != NULL) {
		printf("yes_packet.c: Freeing SUB_GIGA_MESSAGE_t %p\n", pSubGigaMessage);
		free(pSubGigaMessage);
	}
}

MAC_SADDR_HEADER_t* get2p4Header(IEEE802154_MESSAGE_t* msg) {
	return ((void*)msg->header);
}

IEEE802154_MESSAGE_t* yes_2p4_message_allocate() {
	return (IEEE802154_MESSAGE_t*) malloc(sizeof(IEEE802154_MESSAGE_t));
}

uint8_t* get2p4Data(IEEE802154_MESSAGE_t* msg) {
	return ((void*)msg->data);
}

void yes_2p4_message_free() {
	//printf("yes_packet.c: Freeing IEEE802154_MESSAGE_t %p\n", p);
	if (pMessage != NULL) {
		free(pMessage);
	}
}

void printPacket(char *cmdName,
                 uint8_t *data,
                 uint16_t dataLength,
                 RxPacketData_t *packetData)
{
  uint32_t offset = 0;
  int i;

  // Print out a length 0 packet message if no packet was given
  if (data == NULL) {
    responsePrint(cmdName, "len:0");
    return;
  }

  for (i = 0; i < dataLength; i++) {
    int n = snprintf(packetPrintBuffer + offset,
                     sizeof(packetPrintBuffer) - offset,
                     " 0x%.2x",
                     data[i]);
    if (n >= 0) {
      offset += n;
    } else {
      snprintf(packetPrintBuffer, sizeof(packetPrintBuffer), "Invalid Packet");
      break;
    }

    // If we've filled up the packet buffer make sure we stop trying to print
    if (offset >= sizeof(packetPrintBuffer)) {
      snprintf(packetPrintBuffer,
               sizeof(packetPrintBuffer),
               "Packet too large!");
      break;
    }
  }

  // If this is an Rx packet print the appended info
  if (packetData != NULL) {
    responsePrint(cmdName,
                  "len:%d,timeUs:%u,crc:%s,rssi:%d,lqi:%d,phy:%d,isAck:%s,syncWordId:%d,antenna:%d,payload:%s \r\n",
                  packetData->dataLength,
                  packetData->appendedInfo.timeReceived.packetTime,
                  (packetData->appendedInfo.crcPassed) ? "Pass" : "Fail",
                  packetData->appendedInfo.rssi,
                  packetData->appendedInfo.lqi,
                  packetData->appendedInfo.subPhyId,
                  packetData->appendedInfo.isAck ? "True" : "False",
                  packetData->appendedInfo.syncWordId,
                  packetData->appendedInfo.antennaId,
                  packetPrintBuffer);
  } else {
	  responsePrint(cmdName, "len:%d,payload:%s", dataLength, packetPrintBuffer);
  }
}

RAIL_Status_t config2p4Ghz802154() {
//  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0])) {
//    return;
//  }
	RAIL_Idle(railHandle2p4, RAIL_IDLE, true);

	RAIL_Status_t status = RAIL_IEEE802154_Config2p4GHzRadio(railHandle2p4);
	changeChannel2p4(26);
	//printf("config2p4Ghz802154() : %d \r\n", gRfMode);
	return status;
}






static RAIL_Config_t railCfg2p4 = {
  .eventsCallback = &RAILCb_Generic2p4,
};

static void RAILCb_RfReady2p4(RAIL_Handle_t railHandle)
{
	printf("**  RAILCb_RfReady2p4          **\r\n");
}

void initRadio802154(void)
{

	//printf("gRfMode : %d \r\n", gRfMode);
	printf("**  change IEEE 802.15.4..      **\r\n");
	//railHandle2p4 = RAIL_Init(&railCfg2p4, NULL);
	railHandle2p4 = RAIL_Init(&railCfg2p4, &RAILCb_RfReady2p4);
	if (railHandle2p4 == NULL) {
		while(1) ;
	}
	RAIL_ConfigCal(railHandle2p4, RAIL_CAL_ALL);

  // Set up 802.15.4 PHY
  assert(RAIL_IEEE802154_Config2p4GHzRadio(railHandle2p4)==RAIL_STATUS_NO_ERROR);
  assert(RAIL_IEEE802154_Init(railHandle2p4, &IEEE802154_config)==RAIL_STATUS_NO_ERROR);
  //changeChannel2p4(26);

  // Initialize the PA now that the HFXO is up and the timing is correct
   RAIL_TxPowerConfig_t txPowerConfig = {
 #if HAL_PA_2P4_LOWPOWER
     .mode = RAIL_TX_POWER_MODE_2P4_LP,
 #else
     .mode = RAIL_TX_POWER_MODE_2P4_HP,
 #endif
     .voltage = BSP_PA_VOLTAGE,
     .rampTime = HAL_PA_RAMP,
   };
 #if 0
   if (channelConfigs[0]->configs[0].baseFrequency < 1000000UL) {
     // Use the Sub-GHz PA if required
     txPowerConfig.mode = RAIL_TX_POWER_MODE_SUBGIG;
   }
 #endif

   if (RAIL_ConfigTxPower(railHandle2p4, &txPowerConfig) != RAIL_STATUS_NO_ERROR) {
     // Error: The PA could not be initialized due to an improper configuration.
     // Please ensure your configuration is valid for the selected part.
     assert(0);
     //while (1) ;
   }
   RAIL_SetTxPower(railHandle2p4, HAL_PA_POWER);

   RAIL_ConfigEvents(railHandle2p4,
                     RAIL_EVENTS_ALL,
                     (RAIL_EVENT_RX_PACKET_RECEIVED
                      | RAIL_EVENT_TX_PACKET_SENT
                      | RAIL_EVENT_TX_UNDERFLOW
                      | RAIL_EVENT_RX_ACK_TIMEOUT
                      | RAIL_EVENT_TXACK_PACKET_SENT ));

   RAIL_ConfigData(railHandle2p4, &railDataConfig);
}

void changeNodeId(uint32_t i) {
	gNodeId = i;

	USERDATA->NODE_ID = i;
	User_page_update();

	// Automatically apply the new channel to future Tx/Rx
	//if (receiveModeEnabled) {
	//RAIL_StartRx(railHandleSubG, gChannel_SubG, NULL);
	//}
}

void changeChannel(uint32_t i) {
	gChannel_2p4 = i;

	USERDATA->RF_CHANNEL_2p4 = i;
	User_page_update();

	// Automatically apply the new channel to future Tx/Rx
	//if (receiveModeEnabled) {
	RAIL_StartRx(railHandle2p4, gChannel_2p4, NULL);
	//}
}

void changeChannelSubG(uint32_t i) {
	gChannel_SubG = i;

	USERDATA->RF_CHANNEL_SUBG = i;
	User_page_update();

	// Automatically apply the new channel to future Tx/Rx
	//if (receiveModeEnabled) {
	RAIL_StartRx(railHandleSubG, gChannel_SubG, NULL);
	//}
}

void changePowerSubG(uint32_t i) {
	gRfPower_SubG = i;

	USERDATA->RF_POWER_SUBG = i;
	User_page_update();

	// Automatically apply the new channel to future Tx/Rx
	//if (receiveModeEnabled) {
	//RAIL_StartRx(railHandleSubG, gChannel_SubG, NULL);
	//}
}



void ReceiveForwardPacket(void)
{
  // Print any newly received packets
	if (!queueIsEmpty(&rxPacketQueue)) {
		void *rxPacketHandle = queueRemove(&rxPacketQueue);
		RxPacketData_t *rxPacketData = (RxPacketData_t*) memoryPtrFromHandle(rxPacketHandle);

		// Print the received packet and appended info
		if (rxPacketData != NULL) {
//			printPacket("rxPacket", rxPacketData->dataPtr, rxPacketData->dataLength, rxPacketData);
			//printf("forward packet <%d> \r\n", rxPacketData->dataPtr[0]);
			SUB_GIGA_MESSAGE_t *packet = (SUB_GIGA_MESSAGE_t *) rxPacketData->dataPtr;

			MAC_SADDR_HEADER_t *header = (MAC_SADDR_HEADER_t*) &packet->header;
			printf("Sub-G sequence : %d \r\n", header->seqNum);
			//RAIL_SetTimer(railHandleSubG, 1000 * 200, RAIL_TIME_DELAY,&SendSubG_TimeOut_TimerExpired);

			if (header->seqNum == rxSquenceNum) {		// 중복 메시지 일 경우
				memoryFree(rxPacketHandle);
				printf("memoryFree, Duplicate message \r\n");
				RAIL_RadioState_t currentState = RAIL_GetRadioState(railHandleSubG);
				//printf(" RAIL_RadioState_t : %d  \r\n", currentState);
				//packetRx = true;
				return;
			}


			rxSquenceNum = header->seqNum;

			// B2B_UART로 전송
			printf("B2B_UART Transmit \r\n");
			//UARTDRV_Transmit(handle2, rxPacketData->dataPtr, rxPacketData->dataLength, transmit_callback);
			//printf("UARTDRV_Transmit() 0x%4x \r\n", error);
			BSP_LedClear(0);//BSP_LedSet(1);/*20200507_gyuplus_revised*/
			SendB2BUart(rxPacketData->dataPtr, rxPacketData->dataLength);
			packetRx = true;//
		}
		// Free the memory allocated for this packet since we're now done with it
		memoryFree(rxPacketHandle);
	}
}

static void RAILCb_RfReadySubG(RAIL_Handle_t railHandle)
{
	printf("**  RAILCb_RfReadySubG          **\r\n");
}

static RAIL_Config_t railCfgSubG = {
  .eventsCallback = &RAILCb_GenericSubG,
};

void initRadioSubGiga(void) {
	//gRfMode = MODE_SUG_GIGA;
	printf("**  RF mode 915Mhz ..           **\r\n");
	txCount = 0;

	printf("initRadioSubGiga() \n");
	railHandleSubG = RAIL_Init(&railCfgSubG, &RAILCb_RfReadySubG);
	if (railHandleSubG == NULL) {
		while (1);
	}
	RAIL_ConfigCal(railHandleSubG, RAIL_CAL_ALL);


	// Load the channel configuration for the generated radio settings
	uint8_t r = RAIL_ConfigChannels(railHandleSubG, channelConfigs[0], NULL);
	printf("RAIL_ConfigChannels() : %d \r\n", r);
	// Set us to a valid channel for this config and force an update in the main
	// loop to restart whatever action was going on
	//RAIL_ConfigChannels(railHandle, channelConfigs[0], NULL);

	// Configure RAIL callbacks
	RAIL_Status_t c =RAIL_ConfigEvents(railHandleSubG, RAIL_EVENTS_ALL,
			(RAIL_EVENT_RX_PACKET_RECEIVED | RAIL_EVENT_TX_PACKET_SENT
					| RAIL_EVENT_TX_UNDERFLOW));
	printf("RAIL_ConfigEvents : %d \n\r", c);
}

void SetRfConfig(void) {
	// Initialize the PA now that the HFXO is up and the timing is correct
	RAIL_TxPowerConfig_t txPowerConfig = {
#if HAL_PA_2P4_LOWPOWER
			.mode = RAIL_TX_POWER_MODE_2P4_LP,
#else
			.mode = RAIL_TX_POWER_MODE_2P4_HP,
#endif
			.voltage = BSP_PA_VOLTAGE,
			.rampTime = HAL_PA_RAMP,
	};
	//uint32_t f = channelConfigs[0]->configs[0].baseFrequency;
	//printf("** frequency : %d        **\r\n", f);

	//RAIL_TxPower_t lastSetTxPower = RAIL_ConvertRawToDbm(railHandle, txPowerConfig.mode, lastSetTxPowerLevel);

	if (channelConfigs[0]->configs[0].baseFrequency < 1000000UL) {
		// Use the Sub-GHz PA if required
		printf("Sub-GHz PA \n");
		txPowerConfig.mode = RAIL_TX_POWER_MODE_SUBGIG;
	}
	if (RAIL_ConfigTxPower(railHandleSubG, &txPowerConfig) != RAIL_STATUS_NO_ERROR) {
		// Error: The PA could not be initialized due to an improper configuration.
		// Please ensure your configuration is valid for the selected part.
		while (1)
			;
	}
	RAIL_SetTxPower(railHandleSubG, HAL_PA_POWER);

	 //RAIL_SetTxPowerDbm(railHandleSubG, ciGetSigned(gRfPower_SubG));
	RAIL_SetTxPowerDbm(railHandleSubG, gRfPower_SubG);
	// Set TX FIFO, and verify that the size is correct
	 /* uint16_t fifoSize = RAIL_SetTxFifo(railHandle, txFifo, 0, TX_BUFFER_SIZE);
	  if (fifoSize != TX_BUFFER_SIZE) {
	    while (1) ;
	  }*/


}

void changeRetxCount802154(uint8_t i) {
	gReTxCount802154 = i;

	USERDATA->RETX_2p4 = i;
	User_page_update();
}

void changeRetxCountSubG(uint8_t i) {
	gReTxCountSubG = i;

	USERDATA->RETX_SUBG = i;
	User_page_update();
}

void RgbTest_TimerExpired(RAIL_Handle_t railHandle)
{
	int pos = txCount % 3;
	printf("Test_TimerExpired : %d \r\n", pos);

	//RAIL_CancelTimer(railHandle);
	uint8_t data[3][27] = { { 0x4d, 0x01, 0x00, 0x01, 0x0A, 0x00, 0x01, 0x00,
			0xFF, 0xFF, 0x01, 0x00, 0x0e, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x96 }, { 0x4d, 0x01,
			0x00, 0x01, 0x0A, 0x00, 0x01, 0x00, 0xFF, 0xFF, 0x01, 0x00, 0x0e,
			0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x64, 0x00, 0x9e }, { 0x4d, 0x01, 0x00, 0x01, 0x0A, 0x00, 0x01,
			0x00, 0xFF, 0xFF, 0x01, 0x00, 0x0e, 0x01, 0x01, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0xa6 } };

	//RAIL_CancelTimer(railHandle);



	//MakeSubGPacket();
	SendMessageSubGiga(YES_BCAST_ADDR, &data[pos][0], 27);

}

void setRgbTest(int delay) {
	rgb_delay = delay;
	RAIL_SetTimer(railHandle2p4, rgb_delay * 1000, RAIL_TIME_DELAY, &RgbTest_TimerExpired);
}


