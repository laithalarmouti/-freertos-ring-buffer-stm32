#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "FreeRTOS.h"
#include <stdint.h>
#include "semphr.h"
#include <stdbool.h>


#define BUF_SIZE 64

typedef struct {
    uint8_t  data[BUF_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
    SemaphoreHandle_t mutex;
} RingBuf_t;

void RB_Init(RingBuf_t *rb);
bool RB_Write(RingBuf_t *rb, uint8_t data);
bool RB_Read(RingBuf_t *rb, uint8_t *data);

#endif
