/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    Clock time core
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/clock_time.h>

static rt_uint64_t _clock_time_tick_get_freq(struct rt_clock_time_device *dev)
{
    RT_UNUSED(dev);
    return RT_TICK_PER_SECOND;
}

static rt_uint64_t _clock_time_tick_get_counter(struct rt_clock_time_device *dev)
{
    RT_UNUSED(dev);
    return (rt_uint64_t)rt_tick_get();
}

static rt_err_t _clock_time_tick_set_timeout(struct rt_clock_time_device *dev, rt_uint64_t delta)
{
    RT_UNUSED(dev);
    RT_UNUSED(delta);
    return -RT_ENOSYS;
}

static const struct rt_clock_time_ops _clock_time_tick_ops =
{
    _clock_time_tick_get_freq,
    _clock_time_tick_get_counter,
    _clock_time_tick_set_timeout,
};

static struct rt_clock_time_device _clock_time_tick_dev =
{
    .ops = &_clock_time_tick_ops,
    .caps = RT_CLOCK_TIME_CAP_SOURCE,
};

static struct rt_clock_time_device * _clock_time_default_source = &_clock_time_tick_dev;
static struct rt_clock_time_device * _clock_time_default_event = RT_NULL;

rt_weak void rt_clock_time_source_init(void)
{
    return;
}

rt_err_t rt_clock_time_device_register(struct rt_clock_time_device *dev, const char *name, rt_uint8_t caps)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->ops != RT_NULL);

    dev->caps = caps;

    if (name != RT_NULL)
    {
        dev->parent.type = RT_Device_Class_Timer;
        result = rt_device_register(&dev->parent, name,
                                    RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
    }

    if ((caps & RT_CLOCK_TIME_CAP_SOURCE) && _clock_time_default_source == &_clock_time_tick_dev)
    {
        _clock_time_default_source = dev;
    }

    if ((caps & RT_CLOCK_TIME_CAP_EVENT) && _clock_time_default_event == RT_NULL)
    {
        _clock_time_default_event = dev;
    }

    return result;
}

void rt_clock_time_set_default_source(struct rt_clock_time_device *dev)
{
    if (dev != RT_NULL)
    {
        _clock_time_default_source = dev;
    }
}

void rt_clock_time_set_default_event(struct rt_clock_time_device *dev)
{
    if (dev != RT_NULL)
    {
        _clock_time_default_event = dev;
    }
}

struct rt_clock_time_device *rt_clock_time_get_default_source(void)
{
    return _clock_time_default_source ? _clock_time_default_source : &_clock_time_tick_dev;
}

struct rt_clock_time_device *rt_clock_time_get_default_event(void)
{
    return _clock_time_default_event;
}

rt_uint64_t rt_clock_time_get_freq(void)
{
    struct rt_clock_time_device *src = rt_clock_time_get_default_source();

    if (src == RT_NULL || src->ops == RT_NULL || src->ops->get_freq == RT_NULL)
    {
        return 0;
    }

    return src->ops->get_freq(src);
}

rt_uint64_t rt_clock_time_get_counter(void)
{
    struct rt_clock_time_device *src = rt_clock_time_get_default_source();

    if (src == RT_NULL || src->ops == RT_NULL || src->ops->get_counter == RT_NULL)
    {
        return 0;
    }

    return src->ops->get_counter(src);
}

rt_uint64_t rt_clock_time_get_event_freq(void)
{
    struct rt_clock_time_device *event = rt_clock_time_get_default_event();

    if (event == RT_NULL)
    {
        return rt_clock_time_get_freq();
    }

    if (event->ops == RT_NULL || event->ops->get_freq == RT_NULL)
    {
        return 0;
    }

    return event->ops->get_freq(event);
}

rt_uint64_t rt_clock_time_counter_to_ns(rt_uint64_t cnt)
{
    rt_uint64_t freq = rt_clock_time_get_freq();

    if (freq == 0)
    {
        return 0;
    }

    return rt_muldiv_u64(cnt, NANOSECOND_PER_SECOND, freq, NULL);
}

rt_uint64_t rt_clock_time_ns_to_counter(rt_uint64_t ns)
{
    rt_uint64_t freq = rt_clock_time_get_freq();

    if (freq == 0)
    {
        return 0;
    }

    return rt_muldiv_u64(ns, freq, NANOSECOND_PER_SECOND, NULL);
}

rt_err_t rt_clock_time_set_timeout(rt_uint64_t delta)
{
    struct rt_clock_time_device *event = rt_clock_time_get_default_event();

    if (event == RT_NULL || event->ops == RT_NULL || event->ops->set_timeout == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    return event->ops->set_timeout(event, delta);
}
