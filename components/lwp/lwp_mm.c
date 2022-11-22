/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtthread.h>
#include "lwp_mm.h"

static rt_mutex_t mm_lock;

void rt_mm_lock(void)
{
    if (rt_thread_self())
    {
        if (!mm_lock)
        {
            mm_lock = rt_mutex_create("mm_lock", RT_IPC_FLAG_FIFO);
        }
        if (mm_lock)
        {
            rt_mutex_take(mm_lock, RT_WAITING_FOREVER);
        }
    }
}

void rt_mm_unlock(void)
{
    if (rt_thread_self())
    {
        if (mm_lock)
        {
            rt_mutex_release(mm_lock);
        }
    }
}
