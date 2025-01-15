/*
 * kernel.c
 *
 *  Created on: Jan 14, 2025
 *      Author: Aswin
 *
 * Description: TCB_STACK is a two dimensional array which can hold the stack frame to be saved during context switching
 *              sTaskCntrlBlock_t is the taskControl block. The stackPtr in this struct will point to an area in TCB_STACKS
 *
 */
#include "commonIncludes.h"
#include "interrupt.h"

#define NUM_OF_THREADS      3
#define THREAD_STACK_SIZE   100

typedef struct sTaskCntrlBlock_t {
    int32_t *stackPtr;
    struct sTaskCntrlBlock_t *nextPtr;
} sTaskCntrlBlock_t;

sTaskCntrlBlock_t tcbs[NUM_OF_THREADS];

//<< Each thread has a size of 100 words // 100 * 4 = 400  bytes
int32_t TCB_STACK[NUM_OF_THREADS][THREAD_STACK_SIZE];


void osKernalStackInit(uint8_t threadNumber)
{

    /**  We need to initialised the stack frame for a particular thread.
         We will set the PSR to a value to indicate thumb mode.
         Other registers R0-R14 can be initialised with dummy contents
         PC is not initialised here
         We are Storing PSR at the highest address
    **/
    //<< Setting the PSR
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-1] = (int32_t)(1<<21);  //<< PSR

    TCB_STACK[threadNumber][THREAD_STACK_SIZE-3] = (int32_t)(0xAAAA); //<< LR (R14)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-4] = (int32_t)(0xAAAA); //<<  (R13)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-5] = (int32_t)(0xAAAA); //<<  (R12)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-6] = (int32_t)(0xAAAA); //<<  (R11)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-7] = (int32_t)(0xAAAA); //<<  (R10)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-8] = (int32_t)(0xAAAA); //<<  (R9)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-9] = (int32_t)(0xAAAA); //<<  (R8)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-10] = (int32_t)(0xAAAA); //<< (R7)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-11] = (int32_t)(0xAAAA); //<< (R6)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-12] = (int32_t)(0xAAAA); //<< (R5)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-13] = (int32_t)(0xAAAA); //<< (R4)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-14] = (int32_t)(0xAAAA); //<< (R3)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-15] = (int32_t)(0xAAAA); //<< (R2)
    TCB_STACK[threadNumber][THREAD_STACK_SIZE-16] = (int32_t)(0xAAAA); //<< (R1)

    //<< setting the value in tcbs
    tcbs[threadNumber].stackPtr = &TCB_STACK[threadNumber][THREAD_STACK_SIZE - 16];
}

uint8_t osKernalAddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void))
{
    IntMasterDisable();

    tcbs[0].nextPtr = &tcbs[1];
    osKernalStackInit(0);
    TCB_STACK[0][THREAD_STACK_SIZE-2] = (int32_t)task0;

    tcbs[1].nextPtr = &tcbs[2];
    osKernalStackInit(1);
    TCB_STACK[1][THREAD_STACK_SIZE-2] = (int32_t)task1;

    tcbs[2].nextPtr = &tcbs[0];
    osKernalStackInit(2);
    TCB_STACK[2][THREAD_STACK_SIZE-2] = (int32_t)task2;

    IntMasterEnable();

    return 1;
}
