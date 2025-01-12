/*
 * hal_timer.c
 *
 *  Created on: Jan 12, 2025
 *      Author: Aswin
 */

#include "hal_timer.h"
#include "commonIncludes.h"

#define REQURIED_TICK_DURATION 0.001f


uint16_t counter = 0;

void sysTickInterrupt(void)
{

}

void systickTimerInit(void)
{
    SysTickEnable();

    SysTickIntRegister(sysTickInterrupt);

    SysTickIntEnable();

    SysTickPeriodSet(SYSTEM_CLOCK * REQURIED_TICK_DURATION - 1);
}
