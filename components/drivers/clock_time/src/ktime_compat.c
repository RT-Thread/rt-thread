/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    Compatibility layer for ktime APIs
 */

#include <rtdevice.h>
#include <rthw.h>
#include <sys/time.h>
#include <drivers/clock_time.h>

/* Legacy ktime API wrappers - all types defined in clock_time.h */

rt_err_t rt_ktime_boottime_get_us(struct timeval *tv)
{
    return rt_clock_time_boottime_us(tv);
}

rt_err_t rt_ktime_boottime_get_s(time_t *t)
{
    return rt_clock_time_boottime_s(t);
}

rt_err_t rt_ktime_boottime_get_ns(struct timespec *ts)
{
    return rt_clock_time_boottime_ns(ts);
}

rt_uint64_t rt_ktime_cputimer_getres(void)
{
    return rt_clock_time_getres();
}

unsigned long rt_ktime_cputimer_getfrq(void)
{
    return (unsigned long)rt_clock_time_getfreq();
}

unsigned long rt_ktime_cputimer_getcnt(void)
{
    return (unsigned long)rt_clock_time_getcnt();
}

void rt_ktime_cputimer_init(void)
{
    /* No initialization needed with unified clock_time */
}

rt_uint64_t rt_ktime_hrtimer_getres(void)
{
    return rt_clock_time_getres();
}

unsigned long rt_ktime_hrtimer_getfrq(void)
{
    return (unsigned long)rt_clock_time_getfreq();
}

rt_err_t rt_ktime_hrtimer_settimeout(unsigned long cnt)
{
    struct rt_clock_time_device *dev = rt_clock_time_get_default();
    
    if (dev && (dev->caps & RT_CLOCK_TIME_CAP_CLOCKEVENT))
    {
        return dev->ops->set_timeout(cnt);
    }
    
    return -RT_ENOSYS;
}

void rt_ktime_hrtimer_process(void)
{
    rt_clock_hrtimer_process();
}

void rt_ktime_hrtimer_init(struct rt_ktime_hrtimer *timer,
                          const char *name,
                          rt_uint8_t flag,
                          void (*timeout)(void *parameter),
                          void *parameter)
{
    rt_clock_hrtimer_init((rt_clock_hrtimer_t)timer, name, flag, timeout, parameter);
}

rt_err_t rt_ktime_hrtimer_start(struct rt_ktime_hrtimer *timer, unsigned long cnt)
{
    return rt_clock_hrtimer_start((rt_clock_hrtimer_t)timer, cnt);
}

rt_err_t rt_ktime_hrtimer_stop(struct rt_ktime_hrtimer *timer)
{
    return rt_clock_hrtimer_stop((rt_clock_hrtimer_t)timer);
}

rt_err_t rt_ktime_hrtimer_control(struct rt_ktime_hrtimer *timer, int cmd, void *arg)
{
    return rt_clock_hrtimer_control((rt_clock_hrtimer_t)timer, cmd, arg);
}

rt_err_t rt_ktime_hrtimer_detach(struct rt_ktime_hrtimer *timer)
{
    return rt_clock_hrtimer_detach((rt_clock_hrtimer_t)timer);
}

void rt_ktime_hrtimer_delay_init(struct rt_ktime_hrtimer *timer)
{
    rt_clock_hrtimer_init((rt_clock_hrtimer_t)timer, "delay", 
                         RT_TIMER_FLAG_ONE_SHOT, RT_NULL, RT_NULL);
}

void rt_ktime_hrtimer_delay_detach(struct rt_ktime_hrtimer *timer)
{
    rt_clock_hrtimer_detach((rt_clock_hrtimer_t)timer);
}

rt_err_t rt_ktime_hrtimer_sleep(struct rt_ktime_hrtimer *timer, unsigned long cnt)
{
    return rt_clock_hrtimer_sleep((rt_clock_hrtimer_t)timer, cnt);
}

rt_err_t rt_ktime_hrtimer_ndelay(struct rt_ktime_hrtimer *timer, unsigned long ns)
{
    return rt_clock_hrtimer_ndelay((rt_clock_hrtimer_t)timer, ns);
}

rt_err_t rt_ktime_hrtimer_udelay(struct rt_ktime_hrtimer *timer, unsigned long us)
{
    return rt_clock_hrtimer_udelay((rt_clock_hrtimer_t)timer, us);
}

rt_err_t rt_ktime_hrtimer_mdelay(struct rt_ktime_hrtimer *timer, unsigned long ms)
{
    return rt_clock_hrtimer_mdelay((rt_clock_hrtimer_t)timer, ms);
}
