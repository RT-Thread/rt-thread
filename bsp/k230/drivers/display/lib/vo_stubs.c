/* Small compatibility helpers used by the source VO/DSI implementation. */

#include <rtthread.h>
#include <stdarg.h>

void cpu_ticks_delay_us(uint64_t us)
{
    rt_hw_us_delay(us);
}

void K_LOG(int level, int module, const char* fmt, ...)
{
    char buf[256];
    va_list args;
    va_start(args, fmt);
    rt_vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    rt_kprintf("[vo:%d:%d] %s", module, level, buf);
}
