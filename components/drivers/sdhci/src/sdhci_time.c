#include "sdhci_time.h"
#include <rtthread.h>


void usleep_range(unsigned long min, unsigned long max)
{
    rt_int32_t msecs;

    msecs = (min + max)/2000;
    if (msecs)
        rt_thread_mdelay(msecs);
    else
        rt_hw_us_delay((min + max)/2);
}

unsigned int jiffies_to_msecs(const unsigned long j)
{
    return j * (1000u / RT_TICK_PER_SECOND);
}

int64_t ktime_add_ms(const ktime_t kt, const rt_uint64_t msec)
{
    return ktime_add_ns(kt, msec * NSEC_PER_MSEC);
}

int64_t ktime_get(void)
{
    return jiffies_to_msecs(rt_tick_get()) * NSEC_PER_MSEC;
}

int ktime_compare(const ktime_t cmp1, const ktime_t cmp2)
{
    if (cmp1 < cmp2)
        return -1;
    if (cmp1 > cmp2)
        return 1;
    return 0;
}

rt_bool_t ktime_after(const ktime_t cmp1, const ktime_t cmp2)
{
    return ktime_compare(cmp1, cmp2) > 0;
}

unsigned long nsecs_to_jiffies(rt_uint64_t n)
{
    return 0;
}

int mod_timer(struct rt_timer timer, unsigned long expires)
{
    rt_tick_t tick = rt_tick_get();

    if (expires < tick)
    {
        expires = tick;
    }
    tick = expires - tick;

    rt_timer_stop(&timer);
    rt_timer_control(&timer, RT_TIMER_CTRL_SET_TIME, &tick);

    return rt_timer_start(&timer);
}