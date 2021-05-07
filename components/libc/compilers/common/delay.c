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

RT_WEAK void msleep(unsigned int msecs)
{
    rt_thread_mdelay(msecs);
}
RTM_EXPORT(msleep);
