/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013-2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard      first version
 * 2018-11-22     Jesven       add smp support
 */

#include <rthw.h>
#include <rtthread.h>
#include "realview.h"
#include "gic.h"

#define MAX_HANDLERS                NR_IRQS_PBA8

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];

#ifndef RT_USING_SMP
/* Those varibles will be accessed in ISR, so we need to share them. */
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;
#endif

const unsigned int VECTOR_BASE = 0x00;
extern void rt_cpu_vector_set_base(unsigned int addr);
extern int system_vectors;

void rt_hw_vector_init(void)
{
    rt_cpu_vector_set_base((unsigned int)&system_vectors);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    rt_uint32_t gic_cpu_base;
    rt_uint32_t gic_dist_base;

    /* initialize vector table */
    rt_hw_vector_init();

    /* initialize exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));

    /* initialize ARM GIC */
    gic_dist_base = REALVIEW_GIC_DIST_BASE;
    gic_cpu_base = REALVIEW_GIC_CPU_BASE;

    arm_gic_dist_init(0, gic_dist_base, 0);
    arm_gic_cpu_init(0, gic_cpu_base);

    /* init interrupt nest, and context in thread sp */
#ifndef RT_USING_SMP
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;
#endif
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    arm_gic_mask(0, vector);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    arm_gic_umask(0, vector);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if (vector < MAX_HANDLERS)
    {
        old_handler = isr_table[vector].handler;

        if (handler != RT_NULL)
        {
#ifdef RT_USING_INTERRUPT_INFO
            rt_strncpy(isr_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
            isr_table[vector].handler = handler;
            isr_table[vector].param = param;
        }
    }

    return old_handler;
}
