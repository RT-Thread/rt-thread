/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    Compatibility layer for legacy cputime API
 *
 * COMPATIBILITY HEADER:
 * This header provides backward compatibility for code using the old cputime API.
 * The old cputime subsystem has been removed and replaced with the unified
 * clock_time subsystem.
 */

#ifndef __DRIVERS_CPUTIME_H__
#define __DRIVERS_CPUTIME_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_CLOCK_TIME
/* When clock_time is enabled, use the new APIs */
#include <drivers/clock_time.h>

/* Map old cputime APIs to new clock_time APIs */
#define clock_cpu_getres()          rt_clock_cputimer_getres()
#define clock_cpu_gettime()         rt_clock_cputimer_getcnt()
#define clock_cpu_microsecond(tick) ((tick) * 1000000ULL / rt_clock_cputimer_getfrq())
#define clock_cpu_millisecond(tick) ((tick) * 1000ULL / rt_clock_cputimer_getfrq())

/* Delay functions for BSP compatibility */
rt_inline void clock_cpu_delay_us(rt_uint32_t us)
{
    rt_uint64_t start = rt_clock_cputimer_getcnt();
    rt_uint64_t freq = rt_clock_cputimer_getfrq();
    rt_uint64_t delta = (rt_uint64_t)us * freq / 1000000ULL;
    while ((rt_clock_cputimer_getcnt() - start) < delta);
}

rt_inline void clock_cpu_delay_ms(rt_uint32_t ms)
{
    rt_uint64_t start = rt_clock_cputimer_getcnt();
    rt_uint64_t freq = rt_clock_cputimer_getfrq();
    rt_uint64_t delta = (rt_uint64_t)ms * freq / 1000ULL;
    while ((rt_clock_cputimer_getcnt() - start) < delta);
}

/* Stub for riscv_cputime_init - now handled by clock_time */
rt_inline int riscv_cputime_init(void)
{
    /* Initialization is now handled by clock_time subsystem */
    return 0;
}

#else
/* When clock_time is not enabled, provide stub implementations */

/* These are stub implementations for backward compatibility */
rt_inline rt_uint64_t clock_cpu_getres(void)
{
    return ((1000ULL * 1000 * 1000) * 1000000ULL) / RT_TICK_PER_SECOND;
}

rt_inline rt_uint64_t clock_cpu_gettime(void)
{
    return rt_tick_get();
}

rt_inline rt_uint64_t clock_cpu_microsecond(rt_uint64_t cpu_tick)
{
    return (cpu_tick * 1000000ULL) / RT_TICK_PER_SECOND;
}

rt_inline rt_uint64_t clock_cpu_millisecond(rt_uint64_t cpu_tick)
{
    return (cpu_tick * 1000ULL) / RT_TICK_PER_SECOND;
}

/* Tick-based delay functions */
rt_inline void clock_cpu_delay_us(rt_uint32_t us)
{
    rt_uint32_t start = rt_tick_get();
    rt_uint32_t delta = (us * RT_TICK_PER_SECOND + 999999) / 1000000;
    if (delta == 0) delta = 1;
    while ((rt_tick_get() - start) < delta);
}

rt_inline void clock_cpu_delay_ms(rt_uint32_t ms)
{
    rt_uint32_t start = rt_tick_get();
    rt_uint32_t delta = (ms * RT_TICK_PER_SECOND + 999) / 1000;
    if (delta == 0) delta = 1;
    while ((rt_tick_get() - start) < delta);
}

rt_inline int riscv_cputime_init(void)
{
    return 0;
}

#endif /* RT_USING_CLOCK_TIME */

#ifdef __cplusplus
}
#endif

#endif /* __DRIVERS_CPUTIME_H__ */
