#include "ring_buffer.h"



void RB_Init(RingBuf_t *rb){
	rb->mutex = xSemaphoreCreateMutex();
	rb->count = 0;
	rb->head = 0;
	rb->tail = 0;
}

bool RB_Write(RingBuf_t *rb, uint8_t data){
	xSemaphoreTake(rb->mutex, portMAX_DELAY);
	if(rb->count == BUF_SIZE){
		xSemaphoreGive(rb->mutex);
		return 0;
	}
	rb->data[rb->head] = data;
	rb->head = (rb->head + 1) % BUF_SIZE;
	rb->count++;
	xSemaphoreGive(rb->mutex);
	return 1;
}


bool RB_Read(RingBuf_t *rb, uint8_t *data){
	xSemaphoreTake(rb->mutex, portMAX_DELAY);
	if(rb->count == 0){
		xSemaphoreGive(rb->mutex);
		return 0;
	}
	*data = rb->data[rb->tail];
	rb->tail =(rb->tail + 1) % BUF_SIZE;
	rb->count--;
	xSemaphoreGive(rb->mutex);
	return 1;
}
