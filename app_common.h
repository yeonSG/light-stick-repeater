/*
 * app_common.h
 *
 *  Created on: 2018. 7. 19.
 *      Author: sprit
 */

#ifndef APP_COMMON_H_
#define APP_COMMON_H_

#include "rail.h"
#include "hal_common.h"
#include "rail_config.h"

#include "rail_ieee802154.h"

#include "yes/message.h"

#define RADIO_2P4			false
//#define RADIO_2P4			(true)
// #define RADIO_2P4			(false)
#define TEST_LAONZ	false







#define FRAME_CONTROL			0x8841
#define PAN_ID					0x2475

#define SUB_GHZ_915M		0x01
#define SUB_GHZ_433M		0x02
#define IEEE802154_2P4		0x04

#define SYS_MODE_UART			0
#define SYS_MODE_CONSOLE		1
#define SYS_MODE_RGB_TEST		2
#define SYS_MODE_LIGHT_OFF		3

#define APP_MAX_PACKET_LENGTH 504

IEEE802154_MESSAGE_t *pMessage;
SUB_GIGA_MESSAGE_t *pSubGigaMessage;

uint8_t gSysMode;
uint8_t gRfMode;

// :: CSMA Config
static const  RAIL_CsmaConfig_t CsmaConfig = RAIL_CSMA_CONFIG_802_15_4_2003_2p4_GHz_OQPSK_CSMA;

extern RAIL_Handle_t railHandle2p4;
extern RAIL_Handle_t railHandleSubG;

extern uint8_t gChannel_2p4;
extern uint8_t lastSetTxPowerLevel;

extern uint16_t gNodeID;

void changeChannel2p4(uint8_t i);
void radioInit(void);

#endif /* APP_COMMON_H_ */
