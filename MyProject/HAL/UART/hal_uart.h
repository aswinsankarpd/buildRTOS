/*
 * uart.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Aswin
 */

#ifndef HAL_UART_HAL_UART_H_
#define HAL_UART_HAL_UART_H_

#include "commonIncludes.h"

typedef void (*cbFptr) (uint8_t);

void uartInit(cbFptr, cbFptr);

void uartSendBlocking(const char *format, ...);

void uartInterruptCallback(void);

#endif /* HAL_UART_HAL_UART_H_ */
