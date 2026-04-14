#ifndef MY_LOG_H
#define MY_LOG_H

#ifdef __cplusplus
extern "C"
{
#endif



#define MY_LOG_ONE_SIZE     128     // 一条日志的最大值

enum My_LogLevel
{
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
};

void my_log_write(enum My_LogLevel level, char *fmt, ...);
void my_log_register_callback(void (*func)(char *buffer, int num));
void my_log_print_one(void);

#ifdef __cplusplus
}
#endif

#endif
