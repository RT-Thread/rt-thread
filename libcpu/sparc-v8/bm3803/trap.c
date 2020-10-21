/*
 * Copyright (c) 2020, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-16     Dystopia     the first version
 */

#include <rtthread.h>
#include <rthw.h>

extern struct rt_irq_desc isr_table[];

void rt_hw_trap(int tt, unsigned int *sp)
{
    void *param;
    rt_isr_handler_t isr_func;

    /* get interrupt service routine */
    isr_func = isr_table[tt].handler;
    param = isr_table[tt].param;

    /* turn to interrupt service routine */
    if (isr_func != RT_NULL)
        isr_func(tt, param);
}
