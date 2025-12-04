/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    Unified clock_time subsystem - core implementation
 */

#include <rtdevice.h>
#include <rthw.h>

#define DBG_TAG "clock_time"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_clock_time_device *_default_clock_time = RT_NULL;

rt_err_t rt_clock_time_device_register(struct rt_clock_time_device *dev, 
                                       const char *name, 
                                       rt_uint8_t caps)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->ops != RT_NULL);
    RT_ASSERT(name != RT_NULL);
    
    /* Validate capability requirements */
    if (caps & RT_CLOCK_TIME_CAP_CLOCKSOURCE)
    {
        RT_ASSERT(dev->ops->get_freq != RT_NULL);
        RT_ASSERT(dev->ops->get_counter != RT_NULL);
    }
    
    if (caps & RT_CLOCK_TIME_CAP_CLOCKEVENT)
    {
        RT_ASSERT(dev->ops->set_timeout != RT_NULL);
    }
    
    dev->caps = caps;
    dev->parent.type = RT_Device_Class_Timer;
    dev->parent.rx_indicate = RT_NULL;
    dev->parent.tx_complete = RT_NULL;
    dev->parent.user_data = RT_NULL;
    
    /* Calculate resolution scale factor */
    if (dev->ops->get_freq)
    {
        rt_uint64_t freq = dev->ops->get_freq();
        /* res_scale = RT_CLOCK_TIME_RESMUL for nanosecond precision */
        dev->res_scale = RT_CLOCK_TIME_RESMUL;
    }
    
    /* Register as a device */
    rt_err_t result = rt_device_register(&dev->parent, name, 
                                         RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
    
    if (result == RT_EOK)
    {
        LOG_I("Clock time device '%s' registered (caps: 0x%02x)", name, caps);
        
        /* Set as default if none exists */
        if (_default_clock_time == RT_NULL)
        {
            _default_clock_time = dev;
            LOG_I("Set '%s' as default clock time device", name);
        }
    }
    
    return result;
}

rt_err_t rt_clock_time_set_default(struct rt_clock_time_device *dev)
{
    RT_ASSERT(dev != RT_NULL);
    
    _default_clock_time = dev;
    LOG_I("Default clock time device set to '%s'", dev->parent.parent.name);
    
    return RT_EOK;
}

struct rt_clock_time_device *rt_clock_time_get_default(void)
{
    return _default_clock_time;
}

/* Clocksource APIs */

rt_uint64_t rt_clock_time_getres(void)
{
    if (_default_clock_time == RT_NULL || 
        !(_default_clock_time->caps & RT_CLOCK_TIME_CAP_CLOCKSOURCE))
    {
        /* Fallback to tick-based resolution */
        return ((1000ULL * 1000 * 1000) * RT_CLOCK_TIME_RESMUL) / RT_TICK_PER_SECOND;
    }
    
    rt_uint64_t freq = _default_clock_time->ops->get_freq();
    return ((1000ULL * 1000 * 1000) * RT_CLOCK_TIME_RESMUL) / freq;
}

rt_uint64_t rt_clock_time_getfreq(void)
{
    if (_default_clock_time == RT_NULL || 
        !(_default_clock_time->caps & RT_CLOCK_TIME_CAP_CLOCKSOURCE))
    {
        /* Fallback to tick frequency */
        return RT_TICK_PER_SECOND;
    }
    
    return _default_clock_time->ops->get_freq();
}

rt_uint64_t rt_clock_time_getcnt(void)
{
    if (_default_clock_time == RT_NULL || 
        !(_default_clock_time->caps & RT_CLOCK_TIME_CAP_CLOCKSOURCE))
    {
        /* Fallback to tick counter */
        return rt_tick_get();
    }
    
    return _default_clock_time->ops->get_counter();
}

rt_err_t rt_clock_time_boottime_ns(struct timespec *ts)
{
    RT_ASSERT(ts != RT_NULL);
    
    rt_uint64_t cnt = rt_clock_time_getcnt();
    rt_uint64_t res = rt_clock_time_getres();
    rt_uint64_t ns = (cnt * res) / RT_CLOCK_TIME_RESMUL;
    
    ts->tv_sec = ns / (1000ULL * 1000 * 1000);
    ts->tv_nsec = ns % (1000ULL * 1000 * 1000);
    
    return RT_EOK;
}

rt_err_t rt_clock_time_boottime_us(struct timeval *tv)
{
    RT_ASSERT(tv != RT_NULL);
    
    rt_uint64_t cnt = rt_clock_time_getcnt();
    rt_uint64_t res = rt_clock_time_getres();
    rt_uint64_t ns = (cnt * res) / RT_CLOCK_TIME_RESMUL;
    
    tv->tv_sec = ns / (1000ULL * 1000 * 1000);
    tv->tv_usec = (ns % (1000ULL * 1000 * 1000)) / 1000;
    
    return RT_EOK;
}

rt_err_t rt_clock_time_boottime_s(time_t *t)
{
    RT_ASSERT(t != RT_NULL);
    
    rt_uint64_t cnt = rt_clock_time_getcnt();
    rt_uint64_t res = rt_clock_time_getres();
    rt_uint64_t ns = (cnt * res) / RT_CLOCK_TIME_RESMUL;
    
    *t = ns / (1000ULL * 1000 * 1000);
    
    return RT_EOK;
}

/* Time conversion functions */

rt_uint64_t rt_clock_time_cnt_to_ns(rt_uint64_t cnt)
{
    rt_uint64_t res = rt_clock_time_getres();
    return (cnt * res) / RT_CLOCK_TIME_RESMUL;
}

rt_uint64_t rt_clock_time_cnt_to_us(rt_uint64_t cnt)
{
    return rt_clock_time_cnt_to_ns(cnt) / 1000;
}

rt_uint64_t rt_clock_time_cnt_to_ms(rt_uint64_t cnt)
{
    return rt_clock_time_cnt_to_ns(cnt) / (1000 * 1000);
}

rt_uint64_t rt_clock_time_ns_to_cnt(rt_uint64_t ns)
{
    rt_uint64_t freq = rt_clock_time_getfreq();
    return (ns * freq) / (1000ULL * 1000 * 1000);
}

rt_uint64_t rt_clock_time_us_to_cnt(rt_uint64_t us)
{
    return rt_clock_time_ns_to_cnt(us * 1000);
}

rt_uint64_t rt_clock_time_ms_to_cnt(rt_uint64_t ms)
{
    return rt_clock_time_ns_to_cnt(ms * 1000 * 1000);
}
