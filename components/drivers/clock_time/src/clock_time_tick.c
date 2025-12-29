/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    Tick-based fallback implementation for clock_time
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/clock_time.h>

/*
 * CPU Timer APIs - Default tick-based implementation
 * These are weak functions that can be overridden by BSP-specific implementations
 */

rt_weak rt_uint64_t rt_clock_cputimer_getres(void)
{
    /* Resolution in nanoseconds * RT_CLOCK_TIME_RESMUL */
    return ((1000ULL * 1000 * 1000) * RT_CLOCK_TIME_RESMUL) / RT_TICK_PER_SECOND;
}

rt_weak unsigned long rt_clock_cputimer_getfrq(void)
{
    return RT_TICK_PER_SECOND;
}

rt_weak unsigned long rt_clock_cputimer_getcnt(void)
{
    return rt_tick_get();
}

rt_weak void rt_clock_cputimer_init(void)
{
    /* Default: no initialization needed for tick-based implementation */
    return;
}
