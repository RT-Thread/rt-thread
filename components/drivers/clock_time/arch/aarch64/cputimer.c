/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-10     xqyjlj       The first version.
 */

#include "gtimer.h"
#include <drivers/clock_time.h>

static volatile unsigned long _init_cnt = 0;
static rt_bool_t _aarch64_clock_registered = RT_FALSE;
static struct rt_clock_time_device _aarch64_clock_dev;

static rt_uint64_t _aarch64_clock_get_freq(struct rt_clock_time_device *dev)
{
    RT_UNUSED(dev);
    return rt_hw_get_gtimer_frq();
}

static rt_uint64_t _aarch64_clock_get_counter(struct rt_clock_time_device *dev)
{
    RT_UNUSED(dev);
    return (rt_uint64_t)(rt_hw_get_cntpct_val() - _init_cnt);
}

static rt_err_t _aarch64_clock_set_timeout(struct rt_clock_time_device *dev, rt_uint64_t delta)
{
    RT_UNUSED(dev);
    RT_UNUSED(delta);
    return -RT_ENOSYS;
}

static const struct rt_clock_time_ops _aarch64_clock_ops =
{
    _aarch64_clock_get_freq,
    _aarch64_clock_get_counter,
    _aarch64_clock_set_timeout,
};

void rt_clock_time_source_init(void)
{
    _init_cnt = rt_hw_get_cntpct_val();

    if (!_aarch64_clock_registered)
    {
        rt_uint8_t caps = RT_CLOCK_TIME_CAP_SOURCE;

        _aarch64_clock_dev.ops = &_aarch64_clock_ops;
        _aarch64_clock_dev.res_scale = RT_CLOCK_TIME_RESMUL;
        _aarch64_clock_dev.caps = caps;
        rt_clock_time_device_register(&_aarch64_clock_dev, "clock_time_gtimer", caps);
        rt_clock_time_set_default_source(&_aarch64_clock_dev);
        _aarch64_clock_registered = RT_TRUE;
    }
}
