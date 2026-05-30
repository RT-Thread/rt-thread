/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-10     xqyjlj       The first version.
 */

#include <drivers/clock_time.h>

static volatile unsigned long _init_cnt = 0;
static rt_bool_t _riscv_clock_registered = RT_FALSE;
static struct rt_clock_time_device _riscv_clock_dev;

extern rt_uint64_t rt_hw_get_clock_timer_freq(void);

static rt_uint64_t _riscv_clock_get_freq(struct rt_clock_time_device *dev)
{
    RT_UNUSED(dev);
    return rt_hw_get_clock_timer_freq();
}

static rt_uint64_t _riscv_clock_get_counter(struct rt_clock_time_device *dev)
{
    unsigned long time_elapsed;

    RT_UNUSED(dev);
    __asm__ __volatile__("rdtime %0" : "=r"(time_elapsed));
    return (rt_uint64_t)(time_elapsed - _init_cnt);
}

static rt_err_t _riscv_clock_set_timeout(struct rt_clock_time_device *dev, rt_uint64_t delta)
{
    RT_UNUSED(dev);
    RT_UNUSED(delta);
    return -RT_ENOSYS;
}

static const struct rt_clock_time_ops _riscv_clock_ops =
{
    _riscv_clock_get_freq,
    _riscv_clock_get_counter,
    _riscv_clock_set_timeout,
};

void rt_clock_time_source_init(void)
{
    __asm__ __volatile__("rdtime %0" : "=r"(_init_cnt));

    if (!_riscv_clock_registered)
    {
        rt_uint8_t caps = RT_CLOCK_TIME_CAP_SOURCE;

        _riscv_clock_dev.ops = &_riscv_clock_ops;
        _riscv_clock_dev.res_scale = RT_CLOCK_TIME_RESMUL;
        _riscv_clock_dev.caps = caps;
        rt_clock_time_device_register(&_riscv_clock_dev, "clock_time_rdtime", caps);
        rt_clock_time_set_default_source(&_riscv_clock_dev);
        _riscv_clock_registered = RT_TRUE;
    }
}
