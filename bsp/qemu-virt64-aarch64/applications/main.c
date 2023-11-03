/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/10/7      bernard      the first version
 */

#include <stdio.h>
#include <rtthread.h>
#include <rthw.h>
int main(void)
{
    const char *oem;
#ifdef RT_USING_SMART
    oem = "Smart";
#else
    oem = "Thread";
#endif
    rt_ubase_t level = rt_hw_interrupt_disable();

    rt_kprintf("Hi, this is RT-%s!!\n", oem);

    rt_hw_interrupt_enable(level);

    return 0;
}
