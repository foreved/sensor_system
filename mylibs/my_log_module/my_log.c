#include "my_log.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static char log_level_headers[][15] =
{
    "[DEBUG] ",
    "[INFO] ",
    "[WARNING] ",
    "[ERROR] "
};

typedef struct My_Log_Obj
{
    My_RingBuffer_Obj rb;
    void (*my_log_output_func)(My_RingBuffer_Obj *rb);
} My_Log_Obj;

static My_Log_Obj logger;

void my_log_register_callback(void (*func)(My_RingBuffer_Obj *rb))
{
    logger.my_log_output_func = func;
}

void my_log_unregister_callback(void)
{
    logger.my_log_output_func = NULL;
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
    buf[len++] = '\n';
    my_ringbuffer_write(&logger.rb, (uint8_t*)buf, len);

    va_end(args);
}

void my_log_flush(void)
{
    logger.my_log_output_func(&logger.rb);
}

