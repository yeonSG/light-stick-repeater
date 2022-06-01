/*
 * my_uart.h
 *
 *  Created on: 2018. 5. 24.
 *      Author: sprit
 */

#include "../app_common.h"
#include "uartdrv.h"

#ifndef YES_MY_UART_H_
#define YES_MY_UART_H_

#define KME_HEADER_SIZE 11

#define RX_BUFFER_SIZE 38
#define TX_BUFFER_SIZE 38

#define UART_QUEUE_SIZE 1000
uint8_t MyQueue[UART_QUEUE_SIZE];
uint8_t incoming_data;

// Define receive/transmit operation queues
DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_RX_BUFS, rxBufferQueue);
DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_TX_BUFS, txBufferQueue);
// Configuration for USART0, location 11
/*
#define MY_UART                                     \
{                                                   \
  USART0,                                           \
  115200,                                           \
  _USART_ROUTELOC0_TXLOC_LOC0,                     \
  _USART_ROUTELOC0_RXLOC_LOC0,                     \
  usartStopbits1,                                   \
  usartNoParity,                                    \
  usartOVS16,                                       \
  false,                                            \
  uartdrvFlowControlNone,                           \
  gpioPortA,                                        \
  2,                                                \
  gpioPortA,                                        \
  3,                                                \
  (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueue,     \
  (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueue,     \
  _USART_ROUTELOC1_CTSLOC_LOC30,                    \
  _USART_ROUTELOC1_RTSLOC_LOC30                     \
}
*/

/*
#define MY_UART                                     \
{                                                   \
  USART1,                                           \
  115200,                                           \
  _USART_ROUTELOC0_TXLOC_LOC11,                     \
  _USART_ROUTELOC0_RXLOC_LOC11,                     \
  usartStopbits1,                                   \
  usartNoParity,                                    \
  usartOVS16,                                       \
  false,                                            \
  uartdrvFlowControlNone,                           \
  gpioPortC,                                        \
  8,                                                \
  gpioPortC,                                        \
  9,                                                \
  (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueueIO,     \
  (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueueIO,     \
}
*/

// Extend pin에 uart 연결 ok
#define B2B_UART                                   \
{                                               \
    USART1,                                       \
    115200,                                       \
    _USART_ROUTELOC0_TXLOC_LOC12,                  \
    _USART_ROUTELOC0_RXLOC_LOC10,                  \
    usartStopbits1,                               \
    usartNoParity,                                \
    usartOVS16,                                   \
    false,                                        \
    uartdrvFlowControlNone,                       \
    gpioPortF,                                    \
    6,                                            \
    gpioPortF,                                    \
    7,                                            \
    (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueue, \
    (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueue, \
    _USART_ROUTELOC1_CTSLOC_LOC27,                 \
    _USART_ROUTELOC1_RTSLOC_LOC27                  \
}


///*// Extend pin에 uart 연결
#define MY_UART                                   \
{                                               \
    USART0,                                       \
    115200,                                       \
    _USART_ROUTELOC0_TXLOC_LOC2,                  \
    _USART_ROUTELOC0_RXLOC_LOC0,                  \
    usartStopbits1,                               \
    usartNoParity,                                \
    usartOVS16,                                   \
    false,                                        \
    uartdrvFlowControlNone,                       \
    gpioPortA,                                    \
    3,                                            \
	gpioPortA,                                    \
    4,                                            \
    (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueue, \
    (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueue, \
    _USART_ROUTELOC1_CTSLOC_LOC27,                 \
    _USART_ROUTELOC1_RTSLOC_LOC27                  \
}
///*/

/*
#define MY_UART                                   \
{                                               \
    USART0,                                       \
    115200,                                       \
    _USART_ROUTELOC0_TXLOC_LOC0,                  \
    _USART_ROUTELOC0_RXLOC_LOC0,                  \
    usartStopbits1,                               \
    usartNoParity,                                \
    usartOVS16,                                   \
    false,                                        \
    uartdrvFlowControlNone,                       \
    gpioPortF,                                    \
    6,                                            \
    gpioPortF,                                    \
    7,                                            \
    (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueue, \
    (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueue, \
    _USART_ROUTELOC1_CTSLOC_LOC0,                 \
    _USART_ROUTELOC1_RTSLOC_LOC0                  \
}
*/
//extern volatile bool isTransmit;
//volatile bool isTransmit=false;


UARTDRV_HandleData_t handleData;
UARTDRV_HandleData_t handleData2;

/*static uint8_t buffer[16] =  {
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
		0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
	};*/

uint8_t txBuffer[TX_BUFFER_SIZE];
uint8_t rxBuffer[RX_BUFFER_SIZE];

void UART_Rx_cb(UARTDRV_Handle_t handle, Ecode_t transferStatus, uint8_t *data, UARTDRV_Count_t transferCount);
void UART_Tx_cb(UARTDRV_Handle_t handle, Ecode_t transferStatus, uint8_t *data, UARTDRV_Count_t transferCount);

void B2B_UART_Rx_cb(UARTDRV_Handle_t handle, Ecode_t transferStatus, uint8_t *data, UARTDRV_Count_t transferCount);

void initUart(void);
void initB2BUart(void);
void UART_process(void);
void B2B_UART_process(void);

void SendB2BUart(uint8_t *data, UARTDRV_Count_t count);

void transmit_callback(UARTDRV_Handle_t handle,
              Ecode_t transferStatus,
              uint8_t *data,
              UARTDRV_Count_t transferCount);
#endif /* YES_MY_UART_H_ */
