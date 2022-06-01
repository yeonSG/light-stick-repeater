/*
 * app_ci.h
 *
 *  Created on: 2018. 4. 19.
 *      Author: sprit
 */

#ifndef APP_CI_H_
#define APP_CI_H_

/******************************************************************************
 * Application commands.
 *****************************************************************************/
#ifdef INTERNAL_COMMAND_HEADER
  #include INTERNAL_COMMAND_HEADER
#endif
#ifndef INTERNAL_COMMANDS
  #define INTERNAL_COMMANDS COMMAND_ENTRY(NULL, NULL, NULL, NULL)
#endif

// Base set of Command Interface commands
// <command> <args> <help text>
// u=uint8, v=uint16, w=uint32, s=int32, b=string, ?=Anything, *=0 or more of previous
#define APP_COMMAND_INTERFACE_BUFFER_SIZE 256

#define APP_CI_COMMANDS                                                                                                                                                                                         \
	COMMAND_SEPARATOR("Application Configuration"),																	\
	COMMAND_ENTRY("setNodeId", "u", setNodeId, "[Node Id] Set the node identify"),									\
	COMMAND_ENTRY("getNodeId", "", getNodeId, "Get the node identify"),									\
	COMMAND_ENTRY("setChannel", "u", setChannel, "[channel] Set the current radio channel"),						\
	COMMAND_ENTRY("getChannel", "", getChannel, "Get the current radio channel"),									\
	COMMAND_ENTRY("setChannelSubG", "u", setChannelSubG, "[channel] Set the current radio SubG-channel"),						\
	COMMAND_ENTRY("getChannelSubG", "", getChannelSubG, "Get the current radio SubG-channel"),									\
	COMMAND_ENTRY("setPower", "sb*", setPower, "[power raw] Set the current transmit power in deci dBm, or raw units if 'raw' is specified"),                                                                     \
	COMMAND_ENTRY("getPower", "", getPower, "Get the current transmit power in deci dBm"),                                                                                                                        \
	COMMAND_ENTRY("setPowerSubG", "sb*", setPowerSubG, "[power raw] Set the current transmit power in deci dBm, or raw units if 'raw' is specified"),                                                                     \
	COMMAND_ENTRY("getPowerSubG", "", getPowerSubG, "Get the current transmit power in deci dBm"),                                                                                                                        \
	COMMAND_ENTRY("setRetxCount", "u", setRetxCount802154, "[Retransmit Count] Set the retransmit count using IEEE 802.15.4"),                                                                                                                        \
	COMMAND_ENTRY("getRetxCount", "", getRetxCount802154, "Get the retransmit count using IEEE 802.15.4"),                                                                                                                        \
	COMMAND_ENTRY("setRetxCountSubG", "u", setRetxCountSubG, "[Retransmit Count] Set the retransmit count using SubGiga"),                                                                                                                        \
	COMMAND_ENTRY("getRetxCountSubG", "", getRetxCountSubG, "Get the retransmit count using SubGiga"),                                                                                                                        \
	COMMAND_ENTRY("lightOff", "", lightOff, "All light-stick's led off"),                                                                                                                                        \
	COMMAND_ENTRY("rgbTest", "v", rgbTest, "[period] Loop RGB color command"),                                                                                                                                        \
	COMMAND_ENTRY("reset", "", resetChip, "Perform a reboot of the chip"),                                                                                                                                        \
	INTERNAL_COMMANDS

	//parameter_ci
	void setNodeId(int argc, char **argv);
	void getNodeId(int argc, char **argv);
	void setChannel(int argc, char **argv);
	void getChannel(int argc, char **argv);
	void setChannelSubG(int argc, char **argv);
	void getChannelSubG(int argc, char **argv);
	void setPower(int argc, char **argv);
	void getPower(int argc, char **argv);
	void setPowerSubG(int argc, char **argv);
	void getPowerSubG(int argc, char **argv);
	void getRetxCountSubG(int argc, char **argv);
	void setRetxCountSubG(int argc, char **argv);
	void getRetxCount802154(int argc, char **argv);
	void setRetxCount802154(int argc, char **argv);

	void lightOff(int argc, char **argv);
	void rgbTest(int argc, char **argv);

	void resetChip(int argc, char **argv);
#endif /* APP_CI_H_ */


