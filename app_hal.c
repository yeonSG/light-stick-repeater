/*
 * app_hal.c
 *
 *  Created on: 2018. 7. 19.
 *      Author: sprit
 */

#include <stdio.h>

#include "rail.h"

#include "em_cmu.h"
#include "em_gpio.h"

#ifdef CONFIGURATION_HEADER
#include CONFIGURATION_HEADER
#endif

#include "bsp.h"
#include "retargetserial.h"
#include "gpiointerrupt.h"
#include "hal_common.h"

#include "app_hal.h"
#include "yes/my_uart.h"

extern bool packetTx;


void appHalInit(void) {
	// Initialize the system clocks and other HAL components
	halInit();

	// Enable the buttons on the board
//	initButtons();

	// Initialize the LEDs on the board
	BSP_LedsInit();

	CMU_ClockEnable(cmuClock_GPIO, true);

	//initUart();
	//initB2BUart();
}

#if 0 //gyuplus_revised20200507
void initButtons(void)
{
	// Enable the buttons on the board
	  for (int i = 0; i < BSP_NO_OF_BUTTONS; i++) {
	    GPIO_PinModeSet(buttonArray[i].port, buttonArray[i].pin, gpioModeInputPull, 1);
	  }

	  // Button Interrupt Config
	  GPIOINT_Init();
	  GPIOINT_CallbackRegister(buttonArray[0].pin, gpioCallback);
	  GPIOINT_CallbackRegister(buttonArray[1].pin, gpioCallback);
	  GPIO_IntConfig(buttonArray[0].port, buttonArray[0].pin, false, true, true);
	  GPIO_IntConfig(buttonArray[1].port, buttonArray[1].pin, false, true, true);

}
#endif
void gpioCallback(uint8_t pin)
{
  packetTx = true;
}

// LED's
#ifdef BSP_GPIO_LEDS

void LedSet(int led) {
	BSP_LedSet(led);
}

void LedToggle(int led) {
	BSP_LedToggle(led);
}

void LedsDisable(void)
{
  BSP_LedClear(0);
  BSP_LedClear(1);
  // BSP_LedClear(2);/*20200507_gyuplus_revised*/
}

/**
 * Delay for the specified number of microseconds by busy waiting.
 * @param microseconds Time to delay for in microseconds.
 */
void usDelay(uint32_t microseconds)
{
  uint32_t start = RAIL_GetTime();
  while ((RAIL_GetTime() - start) < microseconds) {
  }
}

#else

void LedSet(int led)
{
}
void LedToggle(int led)
{
}
void LedsDisable(void)
{
}

#endif

