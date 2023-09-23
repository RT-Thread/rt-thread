/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-10     xqyjlj       The first version.
 */

#include "ktime.h"

rt_weak unsigned long rt_ktime_cputimer_getres(void)
{
    return ((1000UL * 1000 * 1000) * RT_KTIME_RESMUL) / RT_TICK_PER_SECOND;
}

rt_weak unsigned long rt_ktime_cputimer_getfrq(void)
{
    return RT_TICK_PER_SECOND;
}

rt_weak unsigned long rt_ktime_cputimer_getcnt(void)
{
    return rt_tick_get();
}

rt_weak unsigned long rt_ktime_cputimer_getstep(void)
{
    return 1;
}

rt_weak void rt_ktime_cputimer_init(void)
{
    return;
}
