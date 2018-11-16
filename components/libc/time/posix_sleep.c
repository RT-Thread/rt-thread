/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <stdlib.h>
#include <rtthread.h>

#include <unistd.h>

unsigned int sleep(unsigned int seconds)
{
    rt_tick_t delta_tick;

    delta_tick = rt_tick_get();
    rt_thread_delay(seconds * RT_TICK_PER_SECOND);
    delta_tick = rt_tick_get() - delta_tick;

    return seconds - delta_tick/RT_TICK_PER_SECOND;
}
