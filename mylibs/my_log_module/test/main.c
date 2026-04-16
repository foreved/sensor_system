#include <stdio.h>
#include "my_log.h"

void output(My_RingBuffer_Obj *rb)
{
    char buf[120]= {0};
    uint32_t len = my_ringbuffer_get_valid_size(rb);
    my_ringbuffer_read(rb, buf, len);
    printf("%s", buf);
}

/* ===== 主函数 ===== */
int main()
{
    /* 注册输出函数 */
    my_log_register_callback(output);

    // 1. 单条测试
    my_log_write(LOG_INFO, "hello world");
    my_log_flush();

    // 2. 多条顺序测试
    my_log_write(LOG_DEBUG, "A");
    my_log_write(LOG_INFO, "B");
    my_log_write(LOG_ERROR, "C");

    my_log_flush();
    my_log_flush();
    my_log_flush();

    // 3. 格式化测试
    my_log_write(LOG_INFO, "num=%d, str=%s", 42, "test");
    my_log_flush();

    // 4. 连续测试
    for (int i = 0; i < 5; i++)
    {
        my_log_write(LOG_INFO, "log-%d", i);
    }

    for (int i = 0; i < 5; i++)
    {
        my_log_flush();
    }

    // 5. 空读测试（不应崩溃）
    my_log_flush();
    my_log_flush();

    return 0;
}