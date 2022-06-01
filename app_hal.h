/*
 * app_hal.h
 *
 *  Created on: 2018. 7. 19.
 *      Author: sprit
 */

#ifndef APP_HAL_H_
#define APP_HAL_H_

typedef struct ButtonArray{
  GPIO_Port_TypeDef   port;
  unsigned int        pin;
} ButtonArray_t;
#if 0 //gyuplus_revised20200507
static const ButtonArray_t buttonArray[BSP_NO_OF_BUTTONS] = BSP_GPIO_BUTTONARRAY_INIT;
#endif
void appHalInit(void);
void gpioCallback(uint8_t pin);
void initButtons(void);
void LedSet(int led);
void LedToggle(int led);
void LedsDisable(void);
void usDelay(uint32_t microseconds);

#endif /* APP_HAL_H_ */
