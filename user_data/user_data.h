/*
 * user_data.h
 *
 *  Created on: 2018. 5. 31.
 *      Author: sprit
 */

#ifndef USER_DATA_USER_DATA_H_
#define USER_DATA_USER_DATA_H_

#define USER_PAGE_WORDS 128
//#define USERDATA_BASE		0x0FE00000
//#define USERDATA  ((USERDATA_Union *) USERDATA_BASE)

typedef union {
	struct {
		uint32_t SERIAL;
		uint16_t NODE_ID;
		uint8_t RF_POWER_2p4;
		uint8_t RF_CHANNEL_2p4;
		uint8_t RETX_2p4;
		uint8_t RF_POWER_SUBG;
		uint8_t RF_CHANNEL_SUBG;
		uint8_t RETX_SUBG;
		char PRODNAME[32];
	//etc
	};
	uint32_t WORDS[USER_PAGE_WORDS];
} USERDATA_Union;


#define USERDATA  ((USERDATA_Union *) USERDATA_BASE)
#define UD_SUCCESS  0xFFFF

extern uint8_t gReTxCountSubG;
extern uint8_t gReTxCount802154;

void InitUserDataInfo(void);
uint32_t User_page_update(void);

#endif /* USER_DATA_USER_DATA_H_ */
