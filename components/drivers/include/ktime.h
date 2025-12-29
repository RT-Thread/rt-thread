/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    Compatibility layer for legacy ktime API
 *
 * COMPATIBILITY HEADER:
 * This header provides backward compatibility for code using the old ktime API.
 * All rt_ktime_* APIs are now redirected to rt_clock_* APIs.
 *
 * The old ktime subsystem has been removed and replaced with the unified
 * clock_time subsystem. Include <drivers/clock_time.h> for new code.
 */

#ifndef __KTIME_H__
#define __KTIME_H__

#include <rtthread.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_CLOCK_TIME
/* Include the unified clock_time header which provides all APIs */
#include <drivers/clock_time.h>

/* All rt_ktime_* APIs are already defined as macros in clock_time.h */

#else
/* When clock_time is not enabled, provide stub implementations for backward compatibility */

/* These are minimal stub implementations to maintain compilation compatibility */
rt_inline rt_err_t rt_ktime_boottime_get_ns(struct timespec *ts)
{
    rt_uint64_t tick = rt_tick_get();
    rt_uint64_t ns = tick * (1000000000ULL / RT_TICK_PER_SECOND);
    ts->tv_sec = ns / 1000000000ULL;
    ts->tv_nsec = ns % 1000000000ULL;
    return RT_EOK;
}

rt_inline rt_err_t rt_ktime_boottime_get_us(struct timeval *tv)
{
    rt_uint64_t tick = rt_tick_get();
    rt_uint64_t us = tick * (1000000ULL / RT_TICK_PER_SECOND);
    tv->tv_sec = us / 1000000ULL;
    tv->tv_usec = us % 1000000ULL;
    return RT_EOK;
}

rt_inline void rt_ktime_cputimer_init(void)
{
    /* Stub implementation */
}

#endif /* RT_USING_CLOCK_TIME */

#ifdef __cplusplus
}
#endif

#endif /* __KTIME_H__ */
