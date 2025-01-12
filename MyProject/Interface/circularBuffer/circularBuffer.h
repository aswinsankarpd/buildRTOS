/*
 * circularBuffer.h
 *
 *  Created on: Dec 25, 2024
 *      Author: Aswin
 */

#ifndef MYPROJECT_INTERFACE_CIRCULARBUFFER_CIRCULARBUFFER_H_
#define MYPROJECT_INTERFACE_CIRCULARBUFFER_CIRCULARBUFFER_H_


#include "commonIncludes.h"

typedef enum
{
    E_CBUFF_INIT_OK = 0,
    E_CBUFF_INIT_NOT_OK,
    E_CBUFF_NQ_OK,
    E_CBUFF_NQ_NOT_OK,
    E_CBUFF_DQ_OK,
    E_CBUFF_DQ_NOT_OK
}eCbuffStat_t;

typedef struct
{
    uint8_t header;
    uint8_t tail;
    uint8_t maxCapacity;
    uint8_t sizeofElement;
    void * array;
}sCBuffStruct_t;

eCbuffStat_t circularBufferInit(sCBuffStruct_t * cBuff, uint16_t maxCapacity, uint8_t sizeOfElement);

eCbuffStat_t cBuffEnqueue(sCBuffStruct_t * cBuff, void * data, uint8_t dataSize);

eCbuffStat_t cBuffDequeue(sCBuffStruct_t * cBuff, void * data, uint8_t dataSize);

#endif /* MYPROJECT_INTERFACE_CIRCULARBUFFER_CIRCULARBUFFER_H_ */
