/*
 * hal_gpio.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Aswin
 */

#include "hal_gpio.h"

typedef struct
{
    uint32_t port;
    uint32_t pin;
}sPortPinMap_t;

static sPortPinMap_t gpioPinMap[1] =
{
         {GPIO_PORTN_BASE, GPIO_PIN_0}
};

void gpioInit(void)
{
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
}


void setGpioPin(eGpioPins_t gpioPin, eGpioPinsState_t pinState)
{
    GPIOPinWrite(gpioPinMap[gpioPin].port, gpioPinMap[gpioPin].pin, (uint8_t)pinState);
}

eGpioPinsState_t readGpioPin(eGpioPins_t gpioPin)
{
   eGpioPinsState_t pinState =  (eGpioPinsState_t)GPIOPinRead(gpioPinMap[gpioPin].port, gpioPinMap[gpioPin].pin);

   return pinState;
}
