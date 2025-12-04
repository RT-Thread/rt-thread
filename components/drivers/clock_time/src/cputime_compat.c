/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    Compatibility layer for cputime APIs
 */

#include <rtdevice.h>
#include <rthw.h>
#include <sys/errno.h>

/* Legacy cputime ops structure - deprecated */
static const struct rt_clock_cputime_ops *_legacy_cputime_ops = RT_NULL;

uint64_t clock_cpu_getres(void)
{
    if (_legacy_cputime_ops && _legacy_cputime_ops->cputime_getres)
    {
        return _legacy_cputime_ops->cputime_getres();
    }
    
    /* Use new unified API */
    return rt_clock_time_getres();
}

uint64_t clock_cpu_gettime(void)
{
    if (_legacy_cputime_ops && _legacy_cputime_ops->cputime_gettime)
    {
        return _legacy_cputime_ops->cputime_gettime();
    }
    
    /* Use new unified API */
    return rt_clock_time_getcnt();
}

int clock_cpu_settimeout(uint64_t tick, void (*timeout)(void *param), void *param)
{
    if (_legacy_cputime_ops && _legacy_cputime_ops->cputime_settimeout)
    {
        return _legacy_cputime_ops->cputime_settimeout(tick, timeout, param);
    }
    
    /* Use new unified API */
    struct rt_clock_time_device *dev = rt_clock_time_get_default();
    if (dev && (dev->caps & RT_CLOCK_TIME_CAP_CLOCKEVENT))
    {
        /* Note: Legacy API doesn't directly support callbacks, 
         * would need to use hrtimer for full compatibility */
        return -RT_ENOSYS;
    }
    
    rt_set_errno(ENOSYS);
    return 0;
}

int clock_cpu_issettimeout(void)
{
    if (_legacy_cputime_ops && _legacy_cputime_ops->cputime_settimeout)
    {
        return RT_TRUE;
    }
    
    struct rt_clock_time_device *dev = rt_clock_time_get_default();
    return (dev && (dev->caps & RT_CLOCK_TIME_CAP_CLOCKEVENT)) ? RT_TRUE : RT_FALSE;
}

uint64_t clock_cpu_microsecond(uint64_t cpu_tick)
{
    return rt_clock_time_cnt_to_us(cpu_tick);
}

uint64_t clock_cpu_millisecond(uint64_t cpu_tick)
{
    return rt_clock_time_cnt_to_ms(cpu_tick);
}

int clock_cpu_setops(const struct rt_clock_cputime_ops *ops)
{
    _legacy_cputime_ops = ops;
    return 0;
}

/* Legacy cputimer APIs */

void rt_cputimer_init(struct rt_cputimer *timer,
                     const char *name,
                     void (*timeout)(void *parameter),
                     void *parameter,
                     rt_uint64_t tick,
                     rt_uint8_t flag)
{
    /* Map to hrtimer */
    rt_clock_hrtimer_init((rt_clock_hrtimer_t)timer, name, flag, timeout, parameter);
    ((rt_clock_hrtimer_t)timer)->delay_cnt = tick;
}

rt_err_t rt_cputimer_delete(struct rt_cputimer *timer)
{
    return rt_clock_hrtimer_detach((rt_clock_hrtimer_t)timer);
}

rt_err_t rt_cputimer_start(struct rt_cputimer *timer)
{
    rt_clock_hrtimer_t ht = (rt_clock_hrtimer_t)timer;
    return rt_clock_hrtimer_start(ht, ht->delay_cnt);
}

rt_err_t rt_cputimer_stop(struct rt_cputimer *timer)
{
    return rt_clock_hrtimer_stop((rt_clock_hrtimer_t)timer);
}

rt_err_t rt_cputimer_control(struct rt_cputimer *timer, int cmd, void *arg)
{
    return rt_clock_hrtimer_control((rt_clock_hrtimer_t)timer, cmd, arg);
}

rt_err_t rt_cputimer_detach(struct rt_cputimer *timer)
{
    return rt_clock_hrtimer_detach((rt_clock_hrtimer_t)timer);
}

rt_err_t rt_cputime_sleep(rt_uint64_t tick)
{
    struct rt_clock_hrtimer timer;
    return rt_clock_hrtimer_sleep(&timer, tick);
}

rt_err_t rt_cputime_ndelay(rt_uint64_t ns)
{
    return rt_clock_ndelay(ns);
}

rt_err_t rt_cputime_udelay(rt_uint64_t us)
{
    return rt_clock_udelay(us);
}

rt_err_t rt_cputime_mdelay(rt_uint64_t ms)
{
    return rt_clock_mdelay(ms);
}
