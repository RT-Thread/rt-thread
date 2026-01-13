/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30      Bernard      the first version
 */

#include <rthw.h>
#include <rtthread.h>

int main(int argc, char** argv)
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
