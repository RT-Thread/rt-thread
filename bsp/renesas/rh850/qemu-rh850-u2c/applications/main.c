/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#include <rtthread.h>

int main(void)
{
    int i;

    rt_kprintf("RT-Thread on RH850/U2C, %d ticks per second\n",
               RT_TICK_PER_SECOND);

    for (i = 0; i < 3; i++)
    {
        rt_thread_mdelay(1000);
        rt_kprintf("tick %u\n", (unsigned int)rt_tick_get());
    }

    return 0;
}
