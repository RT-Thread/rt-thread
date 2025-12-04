/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    Tick-based clock_time adapter (fallback)
 */

#include <rtdevice.h>

/**
 * @brief Tick-based fallback clock_time implementation
 * 
 * This provides a basic clock_time implementation using RT-Thread's
 * tick counter. It should be overridden by BSP-specific implementations
 * that provide higher resolution hardware timers.
 */

static rt_uint64_t _tick_get_freq(void)
{
    return RT_TICK_PER_SECOND;
}

static rt_uint64_t _tick_get_counter(void)
{
    return rt_tick_get();
}

static const struct rt_clock_time_ops _tick_clock_ops = 
{
    .get_freq = _tick_get_freq,
    .get_counter = _tick_get_counter,
    .set_timeout = RT_NULL,  /* No hardware timeout support */
};

static struct rt_clock_time_device _tick_clock_device;

/**
 * @brief Initialize tick-based clock_time device
 * 
 * This is automatically called if no other clock_time device is registered.
 */
int rt_clock_time_tick_init(void)
{
    _tick_clock_device.ops = &_tick_clock_ops;
    
    return rt_clock_time_device_register(&_tick_clock_device, 
                                        "tick_clock",
                                        RT_CLOCK_TIME_CAP_CLOCKSOURCE);
}
INIT_DEVICE_EXPORT(rt_clock_time_tick_init);
