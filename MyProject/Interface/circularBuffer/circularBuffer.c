/*
 * circularBuffer.c
 *
 *  Created on: Dec 25, 2024
 *      Author: Aswin
 */


#include "circularBuffer.h"

eCbuffStat_t circularBufferInit(sCBuffStruct_t * cBuff, uint16_t maxCapacity, uint8_t sizeOfElement)
{
    eCbuffStat_t retVal = E_CBUFF_INIT_NOT_OK;

    cBuff->array = malloc(maxCapacity * sizeOfElement);

    if(cBuff->array != NULL)
    {
        cBuff->header = 0;
        cBuff->tail = 0;
        cBuff->maxCapacity = maxCapacity;
        cBuff->sizeofElement = sizeOfElement;

        retVal = E_CBUFF_INIT_OK;
    }

    return retVal;
}


eCbuffStat_t cBuffEnqueue(sCBuffStruct_t * cBuff, void * data, uint8_t dataSize)
{
    eCbuffStat_t retVal = E_CBUFF_NQ_NOT_OK;

    uint8_t next = cBuff->header +1;

    if(next == cBuff->maxCapacity)
    {
        next = 0;
    }

    if(next != cBuff->tail)
    {
        memcpy((uint8_t*)cBuff->array + (cBuff->header * cBuff->sizeofElement), (uint8_t *)data, dataSize);

        cBuff->header = next;
        retVal = E_CBUFF_NQ_OK;
    }

    return retVal;
}

eCbuffStat_t cBuffDequeue(sCBuffStruct_t * cBuff, void * data, uint8_t dataSize)
{
    eCbuffStat_t retVal = E_CBUFF_DQ_NOT_OK;

    if(cBuff->tail != cBuff->header)
    {
        uint8_t next = cBuff->tail+1;

        if( next >= cBuff->maxCapacity)
        {
            next = 0;
        }

        memcpy((uint8_t*)data, (uint8_t*)cBuff->array + (cBuff->tail * cBuff->sizeofElement), dataSize);
        cBuff->tail = next;

        retVal = E_CBUFF_DQ_OK;
    }

    return retVal;
}
