/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-19     WangHuachen  first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "zynqmp-r5.h"
#include "interrupt.h"
#include "gic.h"

#define MAX_HANDLERS                IRQ_ZynqMP_MAXNR

extern volatile rt_uint8_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;


void rt_hw_interrupt_handle(int vector, void *param)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", vector);
}

void rt_hw_interrupt_init(void)
{
    register rt_uint32_t idx;

    /* the initialization is done in fsbl */

    /* init exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));
    for (idx = 0; idx < MAX_HANDLERS; idx++)
    {
        isr_table[idx].handler = rt_hw_interrupt_handle;
    }

    /* initialize ARM GIC */
    arm_gic_dist_init(0, ZynqMP_GIC_DIST_BASE, 0);
    arm_gic_cpu_init(0, ZynqMP_GIC_CPU_BASE);

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;
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

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param handler the interrupt service routine to be installed
 * @param param the parameter for interrupt service routine
 * @param name the interrupt name
 *
 * @return the old handler
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
            rt_snprintf(isr_table[vector].name, RT_NAME_MAX, "%s", name);
#endif /* RT_USING_INTERRUPT_INFO */
            isr_table[vector].handler = handler;
            isr_table[vector].param = param;
        }
        /* set the interrupt to this cpu */
        arm_gic_set_cpu(0, vector, 1 << rt_cpu_get_smp_id());
    }

    return old_handler;
}

void rt_hw_interrupt_trigger(int vector)
{
    arm_gic_trigger(0, 1 << rt_cpu_get_smp_id(), vector);
}

void rt_hw_interrupt_clear(int vector)
{
    /* SGI will be cleared automatically. */
}
