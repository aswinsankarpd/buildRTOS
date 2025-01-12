/*
 * uart.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Aswin
 */
#include "uart.h"
#include "hal_uart.h"
#include "sysctl.h"
#include "commonIncludes.h"
#include "gpio.h"
#include "hal_gpio.h"

#define MAX_MESSAGE_LENGTH 255
#define UART_BAUD_RATE 115200


uint8_t receivedMessage = 0; // Renamed global variable

cbFptr rxCb;
cbFptr txCb;

void uartInterruptCallback(void)
{
    uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART0_BASE, true);

    UARTIntClear(UART0_BASE, ui32Status);

    if (ui32Status & UART_INT_RX)
    {
        UARTFIFODisable(UART0_BASE);
        UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

        receivedMessage = UARTCharGetNonBlocking(UART0_BASE);
    }

    if (ui32Status & UART_INT_TX)
    {

    }
}

void uartInit(cbFptr rxCallbak, cbFptr txCallback)
{
    rxCb = rxCallbak;
    txCb = txCallback;

    uint32_t ui32SysClock = 0;

    ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_PLL), SYSTEM_CLOCK);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
    {
        // Wait for the UART peripheral to be ready
    }

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, ui32SysClock, UART_BAUD_RATE,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));

    UARTFIFODisable(UART0_BASE);

    UARTIntClear(UART0_BASE, UART_INT_RX | UART_INT_TX);

    UARTIntRegister(UART0_BASE, uartInterruptCallback);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_TX);

    while (UARTCharsAvail(UART0_BASE))
    {
        UARTCharGetNonBlocking(UART0_BASE);
    }

    receivedMessage = UARTCharGetNonBlocking(UART0_BASE);
}



void uartSendBlocking(const char *format, ...)
{
    uint8_t index = 0 ;

    char message[MAX_MESSAGE_LENGTH] = {0};
    va_list args;
    va_start(args, format);

    int length = vsnprintf(message, MAX_MESSAGE_LENGTH, format, args);
    va_end(args);

    if (length < 0) // Error in formatting
    {
        // Handle error (e.g., log, assert, etc.)
        return;
    }

    for (index = 0; index < length; index++)
    {
        UARTCharPut(UART0_BASE, message[index]);
    }
}
