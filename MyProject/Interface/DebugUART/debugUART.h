/*
 * debugUART.h
 *
 *  Created on: Dec 25, 2024
 *      Author: Aswin
 */

#ifndef MYPROJECT_INTERFACE_DEBUGUART_DEBUGUART_H_
#define MYPROJECT_INTERFACE_DEBUGUART_DEBUGUART_H_

#include "hal_uart.h"

void debugUartRxCb(uint8_t);

void debugUartTxCb(uint8_t);

void debugUartInit(void);

bool getCommandRxFlag(void);

#endif /* MYPROJECT_INTERFACE_DEBUGUART_DEBUGUART_H_ */
