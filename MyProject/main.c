

/**
 * main.c
 */

#include "systemInit.h"
#include "hal_gpio.h"

int main(void)
{
    systemInit();

    setGpioPin(E_LED_1, E_PIN_HIGH);

    while(1)
    {

    }
}
