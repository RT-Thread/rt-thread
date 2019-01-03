/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include "interrupt.h"
#include <rthw.h>
#include <cp15.h>
#include <gicv2.h>

extern volatile uint8_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];
uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
uint32_t rt_thread_switch_interrupt_flag;

extern uint32_t system_vectors;

// This function will initialize hardware interrupt
void rt_hw_interrupt_init(void)
{
    rt_cpu_vector_set_base((uint32_t)&system_vectors);
    gicd_init();

    // init exceptions table
    rt_memset(isr_table, 0x00, sizeof(isr_table));

    // init interrupt nest, and context in thread sp
    rt_interrupt_nest = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;
}

// This function will mask a interrupt.
// @param vector the interrupt number
void rt_hw_interrupt_mask(int32_t vector)
{
    gicd_irq_disable(vector, 0);
}

// This function will un-mask a interrupt.
// @param vector the interrupt number
void rt_hw_interrupt_umask(int32_t vector)
{
    gicd_irq_enable(vector, 0, false, 0);
}

// This function will install a interrupt service routine to a interrupt.
// @param vector the interrupt number
// @param handler new handler
// @param param parameter
// @param name name
// @return old handler
rt_isr_handler_t rt_hw_interrupt_install(int32_t vector, rt_isr_handler_t handler, void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if (vector < MAX_HANDLERS)
    {
        old_handler = isr_table[vector].handler;

        if (handler != RT_NULL)
        {
#ifdef RT_USING_INTERRUPT_INFO
            rt_strncpy(isr_table[vector].name, name, RT_NAME_MAX);
#endif
            isr_table[vector].handler = handler;
            isr_table[vector].param = param;
        }
        // arm_gic_set_cpu(0, vector, 1 << rt_cpu_get_smp_id());
    }

    return old_handler;
}

// Trigger a software IRQ
// Since we are running in single core, the target CPU are always CPU0.
// @param vector the interrupt number
void rt_hw_interrupt_trigger(int32_t vector)
{
    gicd_sgi_gen(vector, GICD_FILTER_TARGET_LIST_FILTER, _B(0));
}

// clear interrupt
// @param vector the interrupt number
void rt_hw_interrupt_clear(int32_t vector)
{
    GIC_IRQ gicIrq;
    *(uint32_t*)&gicIrq = 0;
    gicIrq.irqId = vector;
    gicc_irq_clr(gicIrq);
}
