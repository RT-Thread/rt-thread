/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-27     flybreak     the first version.
 */

#include <arm-tpl.h>
#include <sys/time.h>
#include <rtthread.h>

extern "C" int __ARM_TPL_clock_realtime(__ARM_TPL_timespec_t* __ts)
{
    unsigned int t = std::time(nullptr);
    __ts->tv_sec = t;
    __ts->tv_nsec = 0;
    return 0;
}

extern "C" int __ARM_TPL_clock_monotonic(__ARM_TPL_timespec_t* __ts)
{
    unsigned int t = rt_tick_get();
    __ts->tv_sec = t / RT_TICK_PER_SECOND;
    __ts->tv_nsec = (t %RT_TICK_PER_SECOND) * NANOSECOND_PER_TICK  ;
    return 0;
}
