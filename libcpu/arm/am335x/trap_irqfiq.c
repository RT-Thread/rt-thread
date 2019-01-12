/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include <rthw.h>
#include "interrupt.h"

extern struct rt_irq_desc isr_table[];

void rt_hw_trap_irq()
{
    uint32_t idx = rt_hw_interrupt_irq_get();

    rt_isr_handler_t isr_func = isr_table[idx].handler;
    if (isr_func != NULL)
        isr_func(idx, isr_table[idx].param);

    rt_hw_interrupt_irq_clr();
}

void rt_hw_trap_fiq()
{
    uint32_t idx = rt_hw_interrupt_fiq_get();

    rt_isr_handler_t isr_func = isr_table[idx].handler;
    if (isr_func != NULL)
        isr_func(idx, isr_table[idx].param);

    rt_hw_interrupt_fiq_clr();
}
