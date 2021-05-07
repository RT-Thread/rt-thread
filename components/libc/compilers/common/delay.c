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

RT_WEAK void msleep(unsigned int msecs)
{
    rt_thread_mdelay(msecs);
}
RTM_EXPORT(msleep);

RT_WEAK void udelay(unsigned long usecs)
{
    rt_hw_us_delay(usecs);
}
RTM_EXPORT(udelay);

RT_WEAK void ndelay(unsigned long nsecs)
{
    rt_hw_us_delay(1);
}
RTM_EXPORT(ndelay);

RT_WEAK void ssleep(unsigned int seconds)
{
    msleep(seconds * 1000);
}
RTM_EXPORT(ssleep);
