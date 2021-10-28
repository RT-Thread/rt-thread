/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-07     Meco Man     first Version
 */
#include <rtthread.h>
#include <rthw.h>
#define DBG_TAG    "POSIX.delay"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

RT_WEAK void rt_hw_us_delay(rt_uint32_t us)
{
    (void) us;
    LOG_W("Please consider implementing rt_hw_us_delay() in another file.");
}

void msleep(unsigned int msecs)
{
    rt_thread_mdelay(msecs);
}
RTM_EXPORT(msleep);

void ssleep(unsigned int seconds)
{
    msleep(seconds * 1000);
}
RTM_EXPORT(ssleep);

void mdelay(unsigned long msecs)
{
    rt_hw_us_delay(msecs * 1000);
}
RTM_EXPORT(mdelay);

void udelay(unsigned long usecs)
{
    rt_hw_us_delay(usecs);
}
RTM_EXPORT(udelay);

void ndelay(unsigned long nsecs)
{
    rt_hw_us_delay(1);
}
RTM_EXPORT(ndelay);
