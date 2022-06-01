/*
 * subg_radio.h
 *
 *  Created on: 2018. 7. 20.
 *      Author: sprit
 */
#include "rail.h"
#include "message.h"

#ifndef YES_YES_RADIO_H_
#define YES_YES_RADIO_H_

//#define SUB_GIGA_CHANNEL		0
#define DEFAULT_RETX_COUNT		1
#define DEFAULT_RF_POWER		200
#define DEFAULT_RF_CHANNEL_2P4	16
#define DEFAULT_RF_CHANNEL_SUBG	0

uint16_t gNodeId;

uint8_t gChannel_2p4;
uint8_t gRfPower_2p4;
uint8_t gReTxCount802154;

uint8_t gChannel_SubG;
uint8_t gRfPower_SubG;
uint8_t gReTxCountSubG;

void QueueInit(void);

void TxSubGPending(void);
void MakeSubGPacket(void);
void SendMessageSubGiga(uint16_t dest, uint8_t* data, uint8_t length);
void SendSubGigaPacket();
void RxSubGigaMessageParse();
void ReceivedPacketForwarding(void);
void MakeIEEE802154Packet(void);
void Tx2p4GPending(void);
void SendMessageIEEE802154(uint16_t dest, uint8_t* data, uint8_t length);
void SendIEEE802154Packet();
void ByPassIEEE802154(uint8_t* data, uint8_t length);

RAIL_Status_t config2p4Ghz802154();
void initRadio802154(void);

void initRadioSubGiga(void);
void SetRfConfig(void);

void SubGigaRx(void);
void ReceiveForwardPacket(void);

SUB_GIGA_MESSAGE_t* yes_subGiga_message_allocate();
void yes_subGiga_message_free();
MAC_SADDR_HEADER_t* get2p4Header(IEEE802154_MESSAGE_t* msg);
IEEE802154_MESSAGE_t* yes_2p4_message_allocate();
uint8_t* get2p4Data(IEEE802154_MESSAGE_t* msg);
void yes_2p4_message_free();
void changeNodeId(uint32_t i);
void changeChannel(uint32_t i);
void changeChannelSubG(uint32_t i);
void changePowerSubG(uint32_t i);
void setRgbTest();

#endif /* YES_YES_RADIO_H_ */
