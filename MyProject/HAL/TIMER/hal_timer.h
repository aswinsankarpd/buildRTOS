/*
 * hal_timer.h
 *
 *  Created on: Jan 12, 2025
 *      Author: Aswin
 */

#ifndef MYPROJECT_HAL_TIMER_HAL_TIMER_H_
#define MYPROJECT_HAL_TIMER_HAL_TIMER_H_

#include "systick.h"

void systickTimerInit(void);
void sysTickInterrupt(void);

#endif /* MYPROJECT_HAL_TIMER_HAL_TIMER_H_ */
