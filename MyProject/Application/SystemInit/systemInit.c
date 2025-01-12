/*
 * systemInit.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Aswin
 */

#include "pinout.h"
#include "hal_gpio.h"
#include "hal_uart.h"
#include "interrupt.h"
#include "debugUART.h"
#include "hal_timer.h"

void systemInit(void)
{
    IntMasterEnable();

    PinoutSet();

    gpioInit();

    debugUartInit();

    uartSendBlocking("System Started\r\n");

    systickTimerInit();

}
