

/**
 * main.c
 */

#include "systemInit.h"
#include "hal_gpio.h"
#include "hal_timer.h"

int main(void)
{
    systemInit();

    setGpioPin(E_LED_1, E_PIN_HIGH);

    while(1)
    {
        uartSendBlocking("Hello");

        delay(1);
    }
}
