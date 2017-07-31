#include <rtthread.h>
#include <rthw.h>
#include "board.h"

static rt_uint8_t  cpu_usage_major = 0, cpu_usage_minor= 0;
static rt_uint32_t idle_begin = 0,idle_count = 0;
static rt_uint32_t run_begin = 0,run_count = 0;
static rt_uint32_t update_tick = 0;
static wtdog_count = 0;
#define jiffies rt_tick_get()

void cpu_usage_idle_hook()
{
    wtdog_count = 0;
}

void thread_switch_hook(struct rt_thread *from, struct rt_thread *to)
{
    //leave idle
    if (from->init_priority == RT_THREAD_PRIORITY_MAX - 1)
    {
        run_begin = jiffies;
        idle_count += jiffies-idle_begin;
    }
    //enter idle
    if (to->init_priority == RT_THREAD_PRIORITY_MAX - 1)
    {
        idle_begin = jiffies;
        run_count += jiffies-run_begin;
    }
    //enter main once 500ms
    else if (to->init_priority == 2)
    {
        register rt_uint32_t total_count;
        run_count += jiffies-run_begin;
        run_begin = jiffies;
        total_count = run_count+idle_count;
        cpu_usage_major = (run_count * 100) / total_count;
        cpu_usage_minor = ((run_count * 100) % total_count) * 100 / total_count;
        idle_count = run_count = 0;
        update_tick = rt_tick_get();
    }
}

#if defined(RT_USING_FINSH)
#include <finsh.h>
void cpu_usage()
{
    //long time no update?? 100%
    if ((rt_tick_get() - update_tick) > 1000)
    {
        cpu_usage_major = 100;
        cpu_usage_minor = 0;
    }
    rt_kprintf("Cpu Usage: %d.%d\n",cpu_usage_major,cpu_usage_minor);
}

void rt_usage_info(rt_uint32_t *major, rt_uint32_t *minor)
{
    //long time no update?? 100%
    if ((rt_tick_get() - update_tick) > 1000)
    {
        cpu_usage_major = 100;
        cpu_usage_minor = 0;
    }
    if (major)
        *major = cpu_usage_major;
    if (minor)
        *minor = cpu_usage_minor;
}
RTM_EXPORT(rt_usage_info);

FINSH_FUNCTION_EXPORT(cpu_usage, cpu usage);
MSH_CMD_EXPORT(cpu_usage, cpu usage);
#endif //RT_USING_FINSH
