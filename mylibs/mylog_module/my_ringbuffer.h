#ifndef MY_RINGBUFFER_H
#define MY_RINGBUFFER_H

#ifdef __cplusplus
extern "C"
{
#endif

#define MY_RINGBUFFER_SIZE      1024    // 2的幂

typedef struct My_RingBuffer_Obj
{
    char buffer[MY_RINGBUFFER_SIZE];
    // 必须初始化为相同值
    int head;
    int tail;
} My_RingBuffer_Obj;

int my_ringbuffer_is_empty(My_RingBuffer_Obj *this);
int my_ringbuffer_is_full(My_RingBuffer_Obj *this);
int my_ringbuffer_get_free_size(My_RingBuffer_Obj *this);
int my_ringbuffer_get_valid_size(My_RingBuffer_Obj *this);
void my_ringbuffer_free(My_RingBuffer_Obj *this, const int num);
int my_ringbuffer_read(My_RingBuffer_Obj *this, char *buffer, int num);
void my_ringbuffer_write(My_RingBuffer_Obj *this, char *buffer, int len);
int my_ringbuffer_write_no_free(My_RingBuffer_Obj *this, char *buffer, int len);
void my_ringbuffer_clear(My_RingBuffer_Obj *this);

#ifdef __cplusplus
}
#endif

#endif
