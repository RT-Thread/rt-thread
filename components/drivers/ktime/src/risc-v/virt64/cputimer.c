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

static volatile unsigned long _init_cnt = 0;

rt_uint32_t rt_ktime_cputimer_getfrq(void)
{
    return CPUTIME_TIMER_FREQ;
}

rt_tick_t rt_ktime_cputimer_getcnt(void)
{
    unsigned long time_elapsed;
    __asm__ __volatile__("rdtime %0" : "=r"(time_elapsed));
    return (rt_tick_t)(time_elapsed - _init_cnt);
}

void rt_ktime_cputimer_init(void)
{
    __asm__ __volatile__("rdtime %0" : "=r"(_init_cnt));
}
