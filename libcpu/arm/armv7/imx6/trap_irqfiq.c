/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <rthw.h>
#include <gicv2_gicc.h>
#include "interrupt.h"

void rt_hw_trap_irq(void)
{
    extern struct rt_irq_desc isr_table[];

    GIC_IRQ gicIrq = gicc_irq_get();

    if (gicIrq.irqId < MAX_HANDLERS) {
        uint32_t irq = gicIrq.irqId;

        rt_isr_handler_t isr_func = isr_table[irq].handler;
#ifdef RT_USING_INTERRUPT_INFO
        isr_table[irq].counter++;
#endif
        if (isr_func) {
            void* param = isr_table[irq].param;
            isr_func(irq, param);
        }
    }
    gicc_irq_clr(gicIrq);
}

void rt_hw_trap_fiq(void)
{
}
