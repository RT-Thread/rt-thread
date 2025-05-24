/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-10     xqyjlj       The first version.
 * 2025-04-20     GuEe-GUI     Port to the DM
 */

#include "ktime.h"
#include "riscv_timer.h"

static volatile unsigned long _init_cnt = 0;

rt_uint64_t rt_ktime_cputimer_getres(void)
{
    return ((1000ULL * 1000 * 1000) * RT_KTIME_RESMUL) / riscv_timer_get_frequency();
}

unsigned long rt_ktime_cputimer_getfrq(void)
{
    return riscv_timer_get_frequency();
}

unsigned long rt_ktime_cputimer_getcnt(void)
{
    return riscv_timer_rdtime() - _init_cnt;
}

unsigned long rt_ktime_cputimer_getstep(void)
{
    return rt_ktime_cputimer_getfrq() / RT_TICK_PER_SECOND;
}

void rt_ktime_cputimer_init(void)
{
    _init_cnt = riscv_timer_rdtime();
}
