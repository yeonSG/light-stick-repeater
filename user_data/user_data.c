/*
 * user_data.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: sprit
 */
#include <stdio.h>
#include "em_msc.h"
#include "user_data.h"
#include "../yes/message.h"
#include "../yes/yes_radio.h"

extern uint8_t gReTxCount802154;


void InitUserDataInfo(void) {
	if (USERDATA->NODE_ID == 0xFFFF) {
		gNodeId = YES_BASE_STATION_ADDR;
	} else {
		gNodeId = USERDATA->NODE_ID;
	}

	if (USERDATA->RETX_2p4 == 0xFF) {
		gReTxCount802154 = DEFAULT_RETX_COUNT;
	} else {
		gReTxCount802154 = USERDATA->RETX_2p4;
	}

	if (USERDATA->RF_POWER_2p4 == 0xFF) {
		gRfPower_2p4 = DEFAULT_RF_POWER;
	} else {
		gRfPower_2p4 = USERDATA->RF_POWER_2p4;
	}

	if (USERDATA->RF_CHANNEL_2p4 == 0xFF) {
		gChannel_2p4 = DEFAULT_RF_CHANNEL_2P4;
	} else {
		gChannel_2p4 = USERDATA->RF_CHANNEL_2p4;
	}

	if (USERDATA->RETX_SUBG == 0xFF) {
		gReTxCountSubG = DEFAULT_RETX_COUNT;
	} else {
		gReTxCountSubG = USERDATA->RETX_SUBG;
	}

	if (USERDATA->RF_POWER_SUBG == 0xFF) {
		gRfPower_SubG = DEFAULT_RF_POWER;
	} else {
		gRfPower_SubG = USERDATA->RF_POWER_SUBG;
	}

	if (USERDATA->RF_CHANNEL_SUBG == 0xFF) {
		gChannel_SubG = DEFAULT_RF_CHANNEL_SUBG;
	} else {
		gChannel_SubG = USERDATA->RF_CHANNEL_SUBG;
	}

	printf("\r\n\n\n");
	printf("- SERIAL NUM     : %x \r\n", USERDATA->SERIAL);
	printf("- NODE ID		 : %x \r\n", gNodeId);
	printf("- RETX_2p4   	 : %x \r\n", gReTxCount802154);
	printf("- RF_POWER_2p4   : %x \r\n", gRfPower_2p4);
	printf("- RF_CHANNEL_2p4 : %x \r\n", gChannel_2p4);
	printf("- RETX_SUBG   	 : %x \r\n", gReTxCountSubG);
	printf("- RF_POWER_SUBG  : %x \r\n", gRfPower_SubG);
	printf("- RF_CHANNEL_SUBG: %x \r\n", gChannel_SubG);
}



uint32_t User_page_update(void) {
	USERDATA_Union user_page_copy;
	//uint32_t i;

	user_page_copy.SERIAL = USERDATA->SERIAL;
	user_page_copy.NODE_ID = gNodeId;
	user_page_copy.RF_POWER_2p4 = gRfPower_2p4;
	user_page_copy.RF_CHANNEL_2p4 =  gChannel_2p4;
	user_page_copy.RETX_2p4 = gReTxCount802154;
	user_page_copy.RF_POWER_SUBG = gRfPower_SubG;
	user_page_copy.RF_CHANNEL_SUBG = gChannel_SubG;
	user_page_copy.RETX_SUBG = gReTxCountSubG;

	// Make copy of user data page contents
	/*for (i = 0; i < USER_PAGE_WORDS; i++)
	 user_page_copy.WORDS[i] = USERDATA->WORDS[i];*/

	MSC_Init();
	// Erase user data page
	MSC_ErasePage(USERDATA);

	// Rewrite user page with new data
	/*if (MSC_WriteWord(USERDATA, &user_page_copy, sizeof(USERDATA_Union)) != mscReturnOk)
	 {
	 // etc
	 printf("User data write error");
	 }*/
	if (MSC_WriteWord(USERDATA->WORDS, user_page_copy.WORDS, USER_PAGE_WORDS)
			!= mscReturnOk) {
		// etc
		printf("User data write error");
	}
	MSC_Deinit();
	return UD_SUCCESS;
}


