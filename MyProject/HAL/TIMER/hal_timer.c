/*
 * hal_timer.c
 *
 *  Created on: Jan 12, 2025
 *      Author: Aswin
 */

#include "hal_timer.h"
#include "commonIncludes.h"
#include "interrupt.h"

#define REQURIED_TICK_DURATION  0.001f
#define MS_2_SEC                1000

volatile uint32_t sysTicker = 0;

uint16_t counter = 0;

void delay(uint32_t seconds)
{
    IntMasterDisable();
    uint32_t startTick = sysTicker;
    IntMasterEnable();

    uint32_t waitTick = startTick + (seconds* MS_2_SEC);

    while(sysTicker <= waitTick){}
}

void sysTickInterrupt(void)
{
    sysTicker++;
}

void systickTimerInit(void)
{
    SysTickEnable();

    SysTickIntRegister(sysTickInterrupt);

    SysTickIntEnable();

    SysTickPeriodSet(SYSTEM_CLOCK * REQURIED_TICK_DURATION - 1);
}
