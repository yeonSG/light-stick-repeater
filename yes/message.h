/*
 * message.h
 *
 *  Created on: 2018. 3. 29.
 *      Author: Dongik Kim
 */

#include <stdio.h>
#include "rail_types.h"

#ifndef YES_MESSAGE_H_
#define YES_MESSAGE_H_

#ifndef YES_DATA_LENGTH
#define YES_DATA_LENGTH 27
#endif

#ifndef YES_BCAST_ADDR
#define YES_BCAST_ADDR 0xFFFF
#endif

#ifndef YES_BASE_STATION_ADDR
#define YES_BASE_STATION_ADDR 0x0000
#endif

//#pragma pack(1)
typedef struct
{
	uint16_t	frameCtrl;
	uint8_t		seqNum;
	uint16_t	dstPanId;
	uint16_t	dstAddr;
	uint16_t	srcAddr;
} __attribute__((packed)) MAC_SADDR_HEADER_t;

typedef struct
{
	uint8_t		len;
	uint8_t		header[sizeof(MAC_SADDR_HEADER_t)];
	uint8_t		data[];
}__attribute__((packed)) IEEE802154_MESSAGE_t;


typedef struct
{
	uint16_t	frameCtrl;
	uint32_t	seqNum;
	uint8_t		groupId;
	uint16_t	parent;
	uint16_t	dstAddr;
	uint16_t	srcAddr;
} __attribute__((packed)) MAC_SUBGIGA_HEADER_t;

typedef struct
{
	uint8_t		len;
	uint8_t		header[sizeof(MAC_SUBGIGA_HEADER_t)];
	uint8_t		data[];
} __attribute__((packed)) SUB_GIGA_MESSAGE_t;

typedef struct RxPacketData {
  /**
   * A structure containing the extra information associated with this received
   * packet.
   */
  RAIL_RxPacketDetails_t appendedInfo;
  /**
   * The number of bytes that are in the dataPtr array.
   */
  uint16_t dataLength;
  /**
   * A variable length array holding the receive packet data bytes.
   */
  uint8_t dataPtr[];
  //SUB_GIGA_MESSAGE_t subMsg;
} RxPacketData_t;

#endif /* YES_MESSAGE_H_ */
