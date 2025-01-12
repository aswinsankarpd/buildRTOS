/*
 * debugUART.c
 *
 *  Created on: Dec 25, 2024
 *      Author: Aswin
 */


#include "debugUART.h"
#include "circularBuffer.h"

sCBuffStruct_t receptionBuffer;

#define RECEPTION_BUFF_SIZE     255
#define RECEPTION_ELE_SIZE      sizeof(uint8_t)
#define RECPTION_NQ_SIZE        1

static bool commandRxFlag = false;

void debugUartRxCb(uint8_t data)
{
    cBuffEnqueue(&receptionBuffer, (void *)&data, RECPTION_NQ_SIZE);

    if(data == '\r')
    {
        commandRxFlag = true;
    }
}

void debugUartTxCb(uint8_t data)
{

}

void debugUartInit(void)
{
    uartInit(&debugUartRxCb, &debugUartTxCb);
    eCbuffStat_t retVal = circularBufferInit(&receptionBuffer, RECEPTION_BUFF_SIZE, RECEPTION_ELE_SIZE);
}

bool getCommandRxFlag(void)
{
    return commandRxFlag;
}
