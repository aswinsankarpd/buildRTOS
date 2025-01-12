/*
 * hal_gpio.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Aswin
 */

#ifndef HAL_GPIO_HAL_GPIO_H_
#define HAL_GPIO_HAL_GPIO_H_

#include "commonIncludes.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "pinout.h"
#include "gpio.h"

typedef enum
{
    E_LED_1 = 0
}eGpioPins_t;

typedef enum
{
    E_PIN_LOW = 0,
    E_PIN_HIGH
}eGpioPinsState_t;

void gpioInit(void);

void setGpioPin(eGpioPins_t userLED, eGpioPinsState_t pinState);

eGpioPinsState_t readGpioPin(eGpioPins_t gpioPin);

#endif /* HAL_GPIO_HAL_GPIO_H_ */
