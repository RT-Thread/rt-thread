/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */

#include <rthw.h>
#include <rtthread.h>

RT_WEAK void machine_reset(void)
{
    rt_kprintf("reboot system...\n");
    rt_hw_interrupt_disable();
    while (1);
}

RT_WEAK void machine_shutdown(void)
{
    rt_kprintf("shutdown...\n");
    rt_hw_interrupt_disable();
    while (1);
}

