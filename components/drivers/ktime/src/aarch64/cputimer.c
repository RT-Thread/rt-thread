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
#include "ktime.h"

static volatile rt_uint64_t _init_cnt = 0;

rt_uint32_t rt_ktime_cputimer_getfrq(void)
{
    return (rt_uint32_t)rt_hw_get_gtimer_frq();
}

rt_tick_t rt_ktime_cputimer_getcnt(void)
{
    return (rt_tick_t)(rt_hw_get_cntpct_val() - _init_cnt);
}

void rt_ktime_cputimer_init(void)
{
    _init_cnt = rt_hw_get_cntpct_val();
}
