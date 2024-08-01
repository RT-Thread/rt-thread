#ifndef __SDHCI_TIME_H__
#define __SDHCI_TIME_H__

#include <rtthread.h>
#include <sys/time.h>
#include "head.h"
typedef int64_t ktime_t;

#define NSEC_PER_USEC   1000L
#define NSEC_PER_SEC    1000000000L
#define NSEC_PER_MSEC   1000000L
#define ktime_add_ns(kt, nsval)     ((kt) + (nsval))

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
#endif