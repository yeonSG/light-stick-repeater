/***************************************************************************//**
 * @file main.c
 * @brief Application specific overrides of weak functions defined as part of
 * the test application.
 * @copyright Copyright 2015 Silicon Laboratories, Inc. http://www.silabs.com
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yes/yes_radio.h>
#include "rail.h"
#include "rail_types.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_emu.h"
#include "bsp.h"
#include "gpiointerrupt.h"
#include "rail_config.h"
#include "hal_common.h"
#include "app_hal.h"

#include "command_interpreter.h"

#include "app_common.h"
#include "yes/my_uart.h"
#include "yes/app_ci.h"
#include "user_data/user_data.h"

#ifdef DISABLE_LOCAL_ECHO
#define localEcho 0
#else
#define localEcho 1
#endif

// Memory manager configuration
//#define MAX_BUFFER_SIZE  256

// Minimum allowed size of the TX FIFO
#define RAIL_TX_FIFO_SIZE 64

#define RX_ALIVE_TIME 10

static char *version = "20200514_918MHz";
// General application memory sizes
//#define APP_MAX_PACKET_LENGTH  (MAX_BUFFER_SIZE - 12) /* sizeof(RAIL_RxPacketInfo_t) == 12) */

// Prototypes
/*void RAILCb_Generic2p4(RAIL_Handle_t railHandle, RAIL_Events_t events);
 void radioInit();
 void changeChannel915(uint32_t i);
 void setRx(bool enable);*/

RAIL_Handle_t railHandleSubG = NULL;
RAIL_Handle_t railHandle2p4 = NULL;

//Command line variables
static CommandEntry_t commands[] = {
APP_CI_COMMANDS,
COMMAND_ENTRY(NULL, NULL, NULL, NULL) };
static CommandState_t ciState;
static char ciBuffer[APP_COMMAND_INTERFACE_BUFFER_SIZE];

// External control and status variables
bool receiveModeEnabled = false;

uint8_t channel915 = 0;
//uint8_t channel2p4 = 16;
volatile bool packetTx = false; //go into transfer mode
volatile bool packetRx = true;  //go into receive mode

extern volatile bool isTransmit;

static uint8_t transmitData[RAIL_TX_FIFO_SIZE] = { 0x0F, 0x16, 0x11, 0x22, 0x33,
		0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, };

//static void RAILCb_RfReady(RAIL_Handle_t railHandle);

#define LED_TX (0)
#define LED_RX (1)

void processInputCharacters(void);

void Alive_TimerExpired(RAIL_Handle_t railHandle) {
	/*RAIL_RadioState_t currentState = RAIL_GetRadioState(railHandle);
	if (currentState == RAIL_RF_STATE_ACTIVE) {
		printf(" RAIL_RadioState_t : %d  \r\n", currentState);
		packetRx = true;
	}*/
	RAIL_RadioState_t currentState = RAIL_GetRadioState(railHandle);
	printf(" Alive_TimerExpired : %d  \r\n", currentState);

	packetRx = true;
	RAIL_SetTimer(railHandle2p4, 1000 * 1000 * RX_ALIVE_TIME, RAIL_TIME_DELAY,
				&Alive_TimerExpired);
}
/*----- 20200507_gyuplus_revised----start---*/
//void send_sync_data(RAIL_Handle_t railHandle)
//{
//	LedToggle(2);
//	RAIL_SetTimer(railHandle2p4, 1000 * 100, RAIL_TIME_DELAY,
//			&send_sync_data);
//}
/*----- 20200507_gyuplus_revised----Finish---*/


void Init_TimerExpired(RAIL_Handle_t railHandle) {
	initUart();
	initB2BUart();
	BSP_LedSet(0); //BSP_LedClear(0);/*20200507_gyuplus_revised*/
	BSP_LedSet(1);//BSP_LedClear(1);/*20200507_gyuplus_revised*/	
	// BSP_LedClear(2);  /*20200507_gyuplus_revised*/

/*
#if !RADIO_2P4
	RAIL_SetTimer(railHandle2p4, 1000 * 1000 * RX_ALIVE_TIME, RAIL_TIME_DELAY,
				&Alive_TimerExpired);
#endif
*/
/*----- 20200507_gyuplus_revised----start---*/
GPIO_PinOutSet(gpioPortF, 7);
//#if RADIO_2P4
//	RAIL_SetTimer(railHandleSubG, 1000 * 100 , RAIL_TIME_DELAY,
//				&send_sync_data);
//#else
//	RAIL_SetTimer(railHandle2p4, 1000 * 100 , RAIL_TIME_DELAY,
//				&send_sync_data);
//#endif
/*----- 20200507_gyuplus_revised----Finish---*/

	printf(" OK, Let's Start!! \r\n");
}

/*----- 20200507_gyuplus_revised----start---*/
#if TEST_LAONZ
	static int g_data_sync_stop_cnt =0;
#endif
static int g_data_sync_cnt;
static int data_sync_irq( void )
{
	if(g_data_sync_cnt >= 10000)
	{
#if TEST_LAONZ
	if(g_data_sync_stop_cnt <= 10)
	{
		g_data_sync_stop_cnt++;
	}
	else
	{
		return 0;
	}
#endif

		LedToggle(2);
		g_data_sync_cnt = 0;
	}
	g_data_sync_cnt++;
	return 0;
}
/*----- 20200507_gyuplus_revised----Finish---*/

int main(void) {
	//	20200507_gyuplus_revised

	// Initialize the chip
	CHIP_Init();

	// Initialize hardware for application
	appHalInit();

	// Initialize the BSP
	BSP_Init(BSP_INIT_BCC);

	BSP_LedClear(0);//BSP_LedSet(0);/*20200507_gyuplus_revised*/
	BSP_LedClear(1);//BSP_LedSet(1);/*20200507_gyuplus_revised*/
	// BSP_LedSet(2); /*20200507_gyuplus_revised*/

	InitUserDataInfo();

#if RADIO_2P4
	// Initialize 2.4Ghz Radio
	initRadio802154();
	changeChannel2p4(26);

#else
	// Initialize 915Mhz Radio
	initRadioSubGiga();
	SetRfConfig();
#endif

	QueueInit();

	printf("**     Initialize Complete!! aa   **\r\n");
	printf("***************%s**************\r\n", version );
	gSysMode = SYS_MODE_UART;
	//setRx(true);

	printf(
			" If you want setup, you should press the ENTER key in 3 second! \r\n");
	RAIL_SetTimer(railHandle2p4, 1000 * 10, RAIL_TIME_DELAY,
			&Init_TimerExpired);


	printf("> ");
	ciInitState(&ciState, ciBuffer, sizeof(ciBuffer), commands);
/*----- 20200507_gyuplus_revised----start---*/
	g_data_sync_cnt = 0;
	while (1) {
		data_sync_irq();
/*----- 20200507_gyuplus_revised----Finish---*/
//		processInputCharacters();
#if RADIO_2P4
//		UART_process();
		B2B_UART_process();
		//UART_process();
		Tx2p4GPending();
#else
		UART_process();
		//SendIEEE802154Packet(railHandle2p4);
		SubGigaRx();
		ReceiveForwardPacket();
		TxSubGPending();
#endif



	}
}

/*static void RAILCb_RfReady(RAIL_Handle_t railHandle)
 {
 //LedSet(0);
 //LedSet(1);
 //LedSet(2);
 LedToggle(1);
 }*/

void processInputCharacters(void) {
	char input = getchar();

	while (input != '\0' && input != 0xFF) {
		if (localEcho) {
			if (input != '\n') {
				printf("%c", input);
			}/* else {
			 printf("RAIL_CancelTimer\n");
			 RAIL_CancelTimer(railHandle);
			 gSysMode = SYS_MODE_CONSOLE;
			 }*/
		}

		if (ciProcessInput(&ciState, &input, 1) > 0) {
			printf("\n\r>");
			if (gSysMode == SYS_MODE_UART) {
				RAIL_CancelTimer(railHandle2p4);
			}
		}
		input = getchar();
	}
}

void changeChannel2p4(uint8_t i) {
	gChannel_2p4 = i;
	// Automatically apply the new channel to future Tx/Rx
	if (receiveModeEnabled) {
		RAIL_StartRx(railHandle2p4, gChannel_2p4, NULL);
	}
}

