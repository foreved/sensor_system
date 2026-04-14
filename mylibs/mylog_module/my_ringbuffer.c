#include "my_ringbuffer.h"

int my_ringbuffer_is_empty(My_RingBuffer_Obj *this)
{
    return this->head == this->tail;
}

int my_ringbuffer_is_full(My_RingBuffer_Obj *this)
{
    // 预留一字节, 区分空和满
    return ((this->head + 1) & (MY_RINGBUFFER_SIZE - 1)) == this->tail;
}

// 获取缓冲区中空余空间的大小
int my_ringbuffer_get_free_size(My_RingBuffer_Obj *this)
{
    if (this->head >= this->tail)
        return MY_RINGBUFFER_SIZE - (this->head - this->tail + 1);
    else
        return this->tail - this->head - 1;
}

// 获取缓冲区中有效数据的大小
int my_ringbuffer_get_valid_size(My_RingBuffer_Obj *this)
{
    if (this->head >= this->tail)
        return this->head - this->tail;
    else
        return MY_RINGBUFFER_SIZE - (this->tail - this->head);
}

void my_ringbuffer_free(My_RingBuffer_Obj *this, const int num)
{
    int valid_size, res;

    valid_size = my_ringbuffer_get_valid_size(this);
    res = valid_size < num ? valid_size : num;

    this->tail = (this->tail + res) & (MY_RINGBUFFER_SIZE - 1);
}

int my_ringbuffer_read(My_RingBuffer_Obj *this, char *buffer, int num)
{
    int valid_size, res, tmp;

    valid_size = my_ringbuffer_get_valid_size(this);
    res = valid_size < num ? valid_size : num;

    // 缓冲区连续
    if (this->head >= this->tail)
    {
        memcpy(buffer, &this->buffer[this->tail], res);
    }
    // 缓冲区不连续
    else
    {
        tmp = MY_RINGBUFFER_SIZE - this->tail;
        if (tmp < res)
        {
            memcpy(buffer, &this->buffer[this->tail], tmp);
            memcpy(buffer + tmp, this->buffer, res - tmp);
        }
        else
        {
            memcpy(buffer, &this->buffer[this->tail], res);
        }
    }

    this->tail = (this->tail + res) & (MY_RINGBUFFER_SIZE - 1);

    return res;
}

// 自动占用旧数据
void my_ringbuffer_write(My_RingBuffer_Obj *this, char *buffer, int len)
{
    int free_size, tmp;

    free_size = my_ringbuffer_get_free_size(this);
    if (len > free_size)
        my_ringbuffer_free(this, len - free_size);
    
    if (this->head >= this->tail)
    {
        tmp = MY_RINGBUFFER_SIZE - this->head;
        if (tmp < len)
        {
            memcpy(&this->buffer[this->head], buffer, tmp);
            memcpy(this->buffer, buffer + tmp, len - tmp);
        }
        else
        {
            memcpy(&this->buffer[this->head], buffer, len);
        }
    }
    else
    {
        memcpy(&this->buffer[this->head], buffer, len);
    }

    this->head = (this->head + len) & (MY_RINGBUFFER_SIZE - 1);
}

// 不占用旧数据
// 如果空余空间不够, 直接返回失败
int my_ringbuffer_write_no_free(My_RingBuffer_Obj *this, char *buffer, int len)
{
    int free_size, tmp;

    free_size = my_ringbuffer_get_free_size(this);
    if (len > free_size)
        return -1;
    
    if (this->head >= this->tail)
    {
        tmp = MY_RINGBUFFER_SIZE - this->head;
        if (tmp < len)
        {
            memcpy(&this->buffer[this->head], buffer, tmp);
            memcpy(this->buffer, buffer + tmp, len - tmp);
        }
        else
        {
            memcpy(&this->buffer[this->head], buffer, len);
        }
    }
    else
    {
        memcpy(&this->buffer[this->head], buffer, len);
    }

    this->head = (this->head + len) & (MY_RINGBUFFER_SIZE - 1);
    
    return 0;
}

void my_ringbuffer_clear(My_RingBuffer_Obj *this)
{
    this->head = 0;
    this->tail = 0;
}