#ifndef MY_RINGBUFFER_H
#define MY_RINGBUFFER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define MY_RINGBUFFER_SIZE      (1 << 10)    // 2的幂

typedef struct
{
    uint8_t buffer[MY_RINGBUFFER_SIZE];
    // 必须初始化为相同值
    int head;
    int tail;
} My_RingBuffer_Obj;

int my_ringbuffer_is_empty(My_RingBuffer_Obj *this);
int my_ringbuffer_is_full(My_RingBuffer_Obj *this);
int my_ringbuffer_get_free_size(My_RingBuffer_Obj *this);
int my_ringbuffer_get_valid_size(My_RingBuffer_Obj *this);
void my_ringbuffer_free(My_RingBuffer_Obj *this, int num);
void my_ringbuffer_consume(My_RingBuffer_Obj *this, int num);
int my_ringbuffer_read(My_RingBuffer_Obj *this, uint8_t *buffer, int num);
void my_ringbuffer_write(My_RingBuffer_Obj *this, uint8_t *buffer, int num);
int my_ringbuffer_write_no_free(My_RingBuffer_Obj *this, uint8_t *buffer, int num);
void my_ringbuffer_clear(My_RingBuffer_Obj *this);
int my_ringbuffer_get_continue_valid_size(My_RingBuffer_Obj *this);
int my_ringbuffer_get_continue_free_size(My_RingBuffer_Obj *this);
uint32_t my_ringbuffer_get_write_pointer(My_RingBuffer_Obj *this);
uint32_t my_ringbuffer_get_read_pointer(My_RingBuffer_Obj *this);
uint32_t my_ringbuffer_get_total_size(My_RingBuffer_Obj *this);

#ifdef __cplusplus
}
#endif

#endif
