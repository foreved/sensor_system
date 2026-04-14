#include "my_log.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "my_ringbuffer.h"

static char log_level_headers[][15] =
{
    "[DEBUG] ",
    "[INFO] ",
    "[WARNING] ",
    "[ERROR] "
};

typedef struct My_Log_Obj
{
    My_RingBuffer_Obj *rb;
    void (*my_log_output_func)(char *buffer, int num);
} My_Log_Obj;

static My_RingBuffer_Obj ring_buffer;
static My_Log_Obj logger = 
{
    .rb = &ring_buffer,
};

void my_log_register_callback(void (*func)(char *buffer, int num))
{
    logger.my_log_output_func = func;
}

void my_log_write(enum My_LogLevel level, char *fmt, ...)
{
    char buf[MY_LOG_ONE_SIZE] = {0};
    va_list args;           // 定义参数列表
    va_start(args, fmt);    // 传入最后一个固定参数
    uint16_t len;
    
    len = strlen(log_level_headers[level]);
    memcpy(buf, log_level_headers[level], len);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);
    
    len = strlen(buf);
    my_ringbuffer_write(logger.rb, (char*)&len, sizeof(len));
    my_ringbuffer_write(logger.rb, buf, len);

    va_end(args);
}

void my_log_print_one(void)
{
    char buf[MY_LOG_ONE_SIZE] = {0};
    uint16_t len = 0;

    if (!logger.my_log_output_func)
        return;

    my_ringbuffer_read(logger.rb, (char*)&len, sizeof(len));
    my_ringbuffer_read(logger.rb, buf, len);
    logger.my_log_output_func(buf, len);
}

