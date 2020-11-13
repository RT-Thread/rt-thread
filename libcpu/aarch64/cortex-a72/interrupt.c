/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <gic_pl400.h>
#include <board.h>
#include <armv8.h>

#define MAX_HANDLERS                256
#define GIC_ACK_INTID_MASK          0x000003ff

#ifdef RT_USING_SMP
#define rt_interrupt_nest rt_cpu_self()->irq_nest
#else
extern volatile rt_uint8_t rt_interrupt_nest;
#endif

extern int system_vectors;

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];

rt_ubase_t rt_interrupt_from_thread;
rt_ubase_t rt_interrupt_to_thread;
rt_ubase_t rt_thread_switch_interrupt_flag;

void rt_hw_vector_init(void)
{
    rt_hw_set_current_vbar((rt_ubase_t)&system_vectors);  // cpu_gcc.S
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{

    rt_uint32_t gic_cpu_base = 0;
    rt_uint32_t gic_dist_base = 0;

    /* initialize ARM GIC */
    gic_dist_base = GIC_PL400_DISTRIBUTOR_PPTR;
    gic_cpu_base = GIC_PL400_CONTROLLER_PPTR;
    arm_gic_dist_init(0, gic_dist_base, 0);
    arm_gic_cpu_init(0, gic_cpu_base);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
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
 * This function returns the active interrupt number.
 * @param none
 */
int rt_hw_interrupt_get_irq(void)
{
    return arm_gic_get_active_irq(0) & GIC_ACK_INTID_MASK;
}

/**
 * This function acknowledges the interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_ack(int vector)
{
    arm_gic_ack(0, vector);
}
