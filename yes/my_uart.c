/*
 * my_uart.c
 *
 *  Created on: 2018. 5. 24.
 *      Author: sprit
 */
#include <stdio.h>
#include <yes/yes_radio.h>
#include "my_uart.h"
#include "bsp.h"
#include "uartdrv.h"
#include "app_hal.h"

//static volatile bool isTransmit=false;
//volatile bool isTransmit=false;

volatile uint32_t rxCount = 0;
volatile uint16_t queue_que=0, queue_retrieve=0;

uint16_t uart_len = 0;

UARTDRV_Handle_t handle = &handleData;
UARTDRV_Handle_t handle2 = &handleData2;

extern bool packetTx;

void initUart(void) {

	// Initialize driver handle
	UARTDRV_InitUart_t initData = MY_UART;
	Ecode_t error = UARTDRV_InitUart(handle, &initData);
	//printf("UARTDRV_InitUart() 0x%4x \r\n", error);
	//error = UARTDRV_Receive(handle, &rxBuffer[0], RX_BUFFER_SIZE, receive_callback);
#if RADIO_2P4 == false
	UARTDRV_Receive(handle, &incoming_data, 1, UART_Rx_cb);
#endif
	// Transmit data using a non-blocking transmit function
	//error = UARTDRV_Transmit(handle, txBuffer, TX_BUFFER_SIZE, transmit_callback);
	//printf("UARTDRV_Transmit() 0x%4x \r\n", error);

}

void initB2BUart(void) {

	// Initialize driver handle
	UARTDRV_InitUart_t initData = B2B_UART;
	Ecode_t error = UARTDRV_InitUart(handle2, &initData);
	printf("UARTDRV_InitUart() 0x%4x \r\n", error);
	//error = UARTDRV_Receive(handle, &rxBuffer[0], RX_BUFFER_SIZE, receive_callback);
	UARTDRV_Receive(handle2, &incoming_data, 1, B2B_UART_Rx_cb);

	// Transmit data using a non-blocking transmit function
	//error = UARTDRV_Transmit(handle, txBuffer, TX_BUFFER_SIZE, transmit_callback);
	//printf("UARTDRV_Transmit() 0x%4x \r\n", error);

}

void SendB2BUart(uint8_t *data,
        UARTDRV_Count_t count) {
	Ecode_t error = UARTDRV_Transmit(handle2, data, count, transmit_callback);
	//
	if (error) {
		printf("UARTDRV_Transmit() 0x%lx \r\n", error);
	}
}

void transmit_callback(UARTDRV_Handle_t handle,
              Ecode_t transferStatus,
              uint8_t *data,
              UARTDRV_Count_t transferCount)
{
  (void)handle;
  (void)transferStatus;
  (void)data;
  (void)transferCount;

	BSP_LedSet(0);//BSP_LedClear(1);/*20200507_gyuplus_revised*/
}

void receive_callback(UARTDRV_Handle_t handle,
		Ecode_t transferStatus,
		uint8_t *data,
		UARTDRV_Count_t transferCount) {
	(void) data;
	(void) handle;
	(void) transferCount;

	if (transferStatus == ECODE_EMDRV_UARTDRV_OK)
	{
		uint8_t index;
		for (index = 0; index < transferCount; index++) {
				//putchar(&data[index]);
			printf(" %x", data[index]);
			}

	    rxCount += transferCount;
	    printf("\n rxCount : %d \n", rxCount);

	    UARTDRV_Receive(handle, rxBuffer, RX_BUFFER_SIZE, receive_callback);
	}
}

void UART_Rx_cb(UARTDRV_Handle_t handle, Ecode_t transferStatus, uint8_t *data, UARTDRV_Count_t transferCount)
{
  //printf("Rx CB called: 0x%4x\r\n", transferStatus);
  if(transferStatus!=ECODE_OK)
    return;
  MyQueue[queue_que++]=*data;
  if(queue_que>=UART_QUEUE_SIZE)
    queue_que = 0;
  UARTDRV_Receive(handle, &incoming_data, 1, UART_Rx_cb);
}

void B2B_UART_Rx_cb(UARTDRV_Handle_t handle, Ecode_t transferStatus, uint8_t *data, UARTDRV_Count_t transferCount)
{
  //printf("Rx CB called: 0x%4x\r\n", transferStatus);
  if(transferStatus!=ECODE_OK)
    return;

  MyQueue[queue_que++]=*data;
  if(queue_que>=UART_QUEUE_SIZE)
    queue_que = 0;
  UARTDRV_Receive(handle, &incoming_data, 1, B2B_UART_Rx_cb);
}

void UART_Tx_cb(UARTDRV_Handle_t handle, Ecode_t transferStatus, uint8_t *data, UARTDRV_Count_t transferCount)
{
  //printf("Tx CB called: 0x%4x\r\n", transferStatus);
  if(transferStatus!=ECODE_OK)
    return;
  //isTransmit=false;
  //makePacket(queue_retrieve, queue_que - queue_retrieve);
}

static int calc_crc( unsigned char *data, int length )
{
	int i, j;
	unsigned short crc;
	
	crc = 0;
	for( i = 0; i < length; i++ )
	{
		crc ^= ( unsigned short )( data[ i ] << 8 );
		for( j = 0; j < 8; j++ )
		{
			if( ( crc & 0x8000 ) != 0 )
			{
				crc = ( unsigned short )( crc << 1 ^ 0x1021 );
			}
			else
			{
				crc = ( unsigned short )( crc << 1 );
			}
		}
	}
	return crc;
}

#define MAGIC_FIRST		0x69
#define MAGIC_SECOND	0xBF

#define SSPE_MAGIC_FIRST	0x99
#define SSPE_MAGIC_SECOND	0x79

#define MAIN_HDR_SIZE			6

void UART_process(void)
{
	static uint8_t prev_data[ 64 ];
	const int sspe_f_pos = 8;
	int find, length;
	uint16_t max, pos, prev;
	uint8_t *data;
	
	if( queue_que != queue_retrieve )
	{
		find = 0;
		prev = queue_que;
		length = prev - queue_retrieve;
		if( prev < queue_retrieve )
			length = UART_QUEUE_SIZE + prev - queue_retrieve;
		
		data = MyQueue;
		max = prev;
		pos = queue_retrieve;
				
		if( length > KME_HEADER_SIZE )
		{
			while( pos != max )
			{
				if( data[ pos ] == MAGIC_FIRST && data[ pos + 1 ] == MAGIC_SECOND )
				{
					// printf("## %d,, ", pos );
					if( length > sspe_f_pos && data[ pos + sspe_f_pos ] == SSPE_MAGIC_FIRST && data[ pos + sspe_f_pos + 1 ] == SSPE_MAGIC_SECOND )
					{
						uart_len = data[ pos + 2 ];
						// printf("### %d, %d, %d,, ", uart_len, length, data[ pos + 3 ] );
						if( data[ pos + 3 ] == 0 )  /* FIXME: length < 255 */
						{
							length -= MAIN_HDR_SIZE;
							if( length >= uart_len )
							{
								uint16_t crc;
								
								crc = calc_crc( &data[ pos + MAIN_HDR_SIZE ], uart_len );
								if( ( uint8_t )( crc & 0xFF ) == data[ pos + 4 ] && ( uint8_t )( ( crc >> 8 ) & 0xFF ) == data[ pos + 5 ] )
								{
									if( memcmp( prev_data, &MyQueue[ pos + KME_HEADER_SIZE ], uart_len + MAIN_HDR_SIZE - KME_HEADER_SIZE ) != 0 )
									{
										memcpy( prev_data, &MyQueue[ pos + KME_HEADER_SIZE ], uart_len + MAIN_HDR_SIZE - KME_HEADER_SIZE );
#if RADIO_2P4
										//MakeIEEE802154Packet();
										SendMessageIEEE802154( YES_BCAST_ADDR, &MyQueue[ pos + KME_HEADER_SIZE ], uart_len + MAIN_HDR_SIZE - KME_HEADER_SIZE );
#else
										/*MakeSubGPacket();
										SendMessageSubGiga(YES_BCAST_ADDR, &MyQueue[KME_HEADER_SIZE], uart_len + 6 - KME_HEADER_SIZE);*/
										SendMessageSubGiga( YES_BCAST_ADDR, &MyQueue[ pos + KME_HEADER_SIZE ], uart_len + MAIN_HDR_SIZE - KME_HEADER_SIZE );
#endif			
									}
//									 printf("## FIND %d,, ", queue_retrieve );
								}
								else
								{
//									 printf("## FIND CHK %d(%d:%d,%d:%d),, ", queue_retrieve, crc & 0xFF, ( crc >> 8 ) & 0xFF, data[ pos + 4 ], data[ pos + 5 ] );
								}
								queue_retrieve = pos + uart_len + MAIN_HDR_SIZE;
								if( queue_retrieve >= UART_QUEUE_SIZE )
									queue_retrieve -= UART_QUEUE_SIZE;
							}
							find = 1;
							// printf( "\r\n" );
							break;
						}
						else
						{
							find = 1;
							queue_retrieve = pos + MAIN_HDR_SIZE;
							if( queue_retrieve >= UART_QUEUE_SIZE )
								queue_retrieve -= UART_QUEUE_SIZE;
								
							// printf("## ERR %d\r\n", queue_retrieve );
							break;
						}
					}
					// printf( "\r\n" );
				}
				
				pos++;
				length--;
				if( pos >= UART_QUEUE_SIZE )
					pos = 0;
			}
			if( find == 0 )
			{
				queue_retrieve = 0;
				if( pos > 0 )
					queue_retrieve = pos - 1;
			}
		}

		length = queue_que - queue_retrieve;
		if( queue_que < queue_retrieve )
			length = UART_QUEUE_SIZE + queue_que - queue_retrieve;

		if( length == 0 )
		{
			CORE_DECLARE_IRQ_STATE;
			CORE_ENTER_CRITICAL();

			queue_que = 0;
			queue_retrieve = 0;
			
			CORE_EXIT_CRITICAL();
		}
	}


#if 0
		if (queue_que > queue_retrieve) {

			if (MyQueue[queue_retrieve] == 0x69
					|| MyQueue[queue_retrieve + 1] == 0xbf) {
				if (MyQueue[queue_retrieve] == 0x69
						&& MyQueue[queue_retrieve + 1] == 0xbf
						&& MyQueue[queue_retrieve + 2] != 0x00) {
					uart_len = MyQueue[queue_retrieve + 2];
//					if (queue_que >= uart_len + 6 && !isTransmit) {
					if (queue_que >= uart_len + 6) {
					//if (queue_que >= uart_len + 6) {
//						isTransmit = true;

						// 풀것
						/*sendMessageSubGiga(YES_BCAST_ADDR,
								&MyQueue[KME_HEADER_SIZE],
								queue_que - KME_HEADER_SIZE);*/
						//packetTx = true;
#if RADIO_2P4
						//MakeIEEE802154Packet();
						SendMessageIEEE802154(YES_BCAST_ADDR,
								&MyQueue[KME_HEADER_SIZE],
								uart_len + 6 - KME_HEADER_SIZE);
#else
						/*MakeSubGPacket();
						SendMessageSubGiga(YES_BCAST_ADDR,
								&MyQueue[KME_HEADER_SIZE],
								uart_len + 6 - KME_HEADER_SIZE);*/
						SendMessageSubGiga(YES_BCAST_ADDR,
								&MyQueue[KME_HEADER_SIZE],
								uart_len + 6 - KME_HEADER_SIZE);
#endif
						queue_que = 0;
						queue_retrieve = 0;
					}
				}
			} else {
				//printf("** %d, %d \n\r", queue_que, queue_retrieve);
				//if (!isTransmit)
				//queue_que = 0;
				queue_retrieve = queue_que;
			}
		}
	}
#endif

}

#define B2B_MAGIC_FIRST		0x41
#define B2B_MAGIC_SECOND	0x88


void B2B_UART_process(void)
{
	static uint8_t cnt = 0;
	static uint8_t prev_data[ 64 ];
	int find, length, header_size;
	uint16_t max, pos, prev;
	uint8_t *data;
	
	if( queue_que != queue_retrieve )
	{
		find = 0;
		prev = queue_que;
		length = prev - queue_retrieve;
		if( prev < queue_retrieve )
			length = UART_QUEUE_SIZE + prev - queue_retrieve;
		
		data = MyQueue;
		max = prev;
		pos = queue_retrieve;
		
		header_size = sizeof( MAC_SUBGIGA_HEADER_t );
		if( length > header_size )
		{
			// printf("I:## %d,%d,%d\r\n", pos, length, header_size );
			while( pos != max )
			{
				if( data[ pos ] != 0 && data[ pos + 1 ] == B2B_MAGIC_FIRST && data[ pos + 2 ] == B2B_MAGIC_SECOND )
				{
					// printf("## %d,,\r\n", pos );
					uart_len = data[ pos ];
					if( uart_len < length )
					{
						BSP_LedClear( 0 ); //BSP_LedSet( 1 ); /*20200507_gyuplus_revised*/
						
						if( memcmp( prev_data, &data[ pos + header_size + 1 ], uart_len - header_size ) != 0 )
						{
							memcpy( prev_data, &data[ pos + header_size + 1 ], uart_len - header_size );
							SendMessageIEEE802154( YES_BCAST_ADDR, &data[ pos + header_size + 1 ], uart_len - header_size );
						}
						usDelay( 1000 );
						BSP_LedSet( 0 ) ;//BSP_LedClear( 1 );	// Green LED /*20200507_gyuplus_revised*/
						
						queue_retrieve = pos + uart_len + 1;
						if( queue_retrieve >= UART_QUEUE_SIZE )
							queue_retrieve -= UART_QUEUE_SIZE;
						// printf("find %d, %d, %d, %d, %d, %d\r\n", queue_retrieve, queue_que, length, uart_len, data[ pos ], pos );
						printf("find %d\r\n", queue_retrieve );
						find = 2;
					}
					else
					{
						queue_retrieve = pos;	
						find = 1;
					}
					break;
				}
				pos++;
				length--;
				if( pos >= UART_QUEUE_SIZE )
					pos = 0;
			}
			if( find == 0 )
			{
				queue_retrieve = UART_QUEUE_SIZE + pos - 3;
				if( pos > 3 )
					queue_retrieve = pos - 3;
			}
		}
		// length = queue_que - queue_retrieve;
		// if( queue_que < queue_retrieve )
		//	length = UART_QUEUE_SIZE + queue_que - queue_retrieve;


		{
			CORE_DECLARE_IRQ_STATE;
			CORE_ENTER_CRITICAL();

			if( queue_que == queue_retrieve && find != 1 )
			{
				queue_que = 0;
				queue_retrieve = 0;
			}
			
			CORE_EXIT_CRITICAL();
		}

	}
	if ( cnt++ %5 == 0 )
	{
		// BSP_LedSet( 0 ) ;//BSP_LedClear( 1 );	// Green LED /*20200507_gyuplus_revised*/
	}
		
#if 0
	//printf("# %d, %d \n\r", queue_que, queue_retrieve);
	if (queue_que != queue_retrieve) {

		if (queue_que > queue_retrieve + 1) {
			//printf("# %x, %x \n\r", MyQueue[queue_retrieve + 1], MyQueue[queue_retrieve + 2]);
			if (MyQueue[queue_retrieve + 1] == 0x41
					|| MyQueue[queue_retrieve + 2] == 0x88) {
				//printf("## %x, %x \n\r", MyQueue[queue_retrieve + 1], MyQueue[queue_retrieve + 2]);
				BSP_LedSet(0);
				if (MyQueue[queue_retrieve + 1] == 0x41
						&& MyQueue[queue_retrieve + 2] == 0x88
						&& MyQueue[queue_retrieve] != 0x00) {
					uart_len = MyQueue[queue_retrieve];
//					if (queue_que >= uart_len&& !isTransmit) {
					if (queue_que >= uart_len) {
					//if (queue_que >= uart_len + 6) {
						//printf("# queue_que : %d, uart_len :%d \n\r", queue_que, uart_len);
//						isTransmit = true;
						usDelay(100);
						// 풀것
						/*sendMessageSubGiga(YES_BCAST_ADDR,
								&MyQueue[KME_HEADER_SIZE],
								queue_que - KME_HEADER_SIZE);*/
						//packetTx = true;
						//MakeIEEE802154Packet();
						//SendMessageIEEE802154(YES_BCAST_ADDR,
						//		&MyQueue[0], queue_que);

						//ByPassIEEE802154(&MyQueue[0], queue_que);
						//printf("# %d, %d \n\r", queue_que, queue_retrieve);
						//MakeIEEE802154Packet();
						SendMessageIEEE802154(YES_BCAST_ADDR,
								&MyQueue[sizeof(MAC_SUBGIGA_HEADER_t) + 1],
								uart_len - sizeof(MAC_SUBGIGA_HEADER_t));

						BSP_LedClear(0);			// Green LED
						queue_que = 0;
						queue_retrieve = 0;
					}
				}
			} else {
				//printf("** %d, %d \n\r", queue_que, queue_retrieve);
				//if (!isTransmit)
				//queue_que = 0;
				queue_retrieve = queue_que;
			}
			//printf("### %x, %x \n\r", MyQueue[queue_retrieve + 1], MyQueue[queue_retrieve + 2]);
		}
	}
#endif
}
