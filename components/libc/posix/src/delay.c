/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-07     Meco Man     first Version
 */
#include <sys/types.h>
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

unsigned int sleep(unsigned int seconds)
{
    if (rt_thread_self() != RT_NULL)
    {
        ssleep(seconds);
    }
    else /* scheduler has not run yet */
    {
        while(seconds > 0)
        {
            udelay(1000000u);
            seconds --;
        }
    }

    return 0;
}
RTM_EXPORT(sleep);

int usleep(useconds_t usec)
{
    if (rt_thread_self() != RT_NULL)
    {
        msleep(usec / 1000u);
    }
    else  /* scheduler has not run yet */
    {
        udelay(usec / 1000u);
    }
    udelay(usec % 1000u);

    return 0;
}
RTM_EXPORT(usleep);
