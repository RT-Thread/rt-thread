/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard      first version
 * 2018-11-22     Jesven       add smp support
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "interrupt.h"
#include "gic.h"

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];

#ifndef RT_USING_SMP
/* Those variables will be accessed in ISR, so we need to share them. */
rt_uint32_t rt_interrupt_from_thread        = 0;
rt_uint32_t rt_interrupt_to_thread          = 0;
rt_uint32_t rt_thread_switch_interrupt_flag = 0;
#endif

const unsigned int VECTOR_BASE = 0x00;
extern void rt_cpu_vector_set_base(unsigned int addr);
extern int system_vectors;

#ifdef RT_USING_SMP
#define rt_interrupt_nest rt_cpu_self()->irq_nest
#else
extern volatile rt_uint8_t rt_interrupt_nest;
#endif

#ifdef SOC_BCM283x
static void default_isr_handler(int vector, void *param)
{
#ifdef RT_USING_SMP
    rt_kprintf("cpu %d unhandled irq: %d\n", rt_hw_cpu_id(),vector);
#else
    rt_kprintf("unhandled irq: %d\n",vector);
#endif
}
#endif

void rt_hw_vector_init(void)
{
    rt_cpu_vector_set_base((unsigned int)&system_vectors);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
#ifdef SOC_BCM283x
    rt_uint32_t index;
    /* initialize vector table */
    rt_hw_vector_init();

    /* initialize exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));

    /* mask all of interrupts */
    IRQ_DISABLE_BASIC = 0x000000ff;
    IRQ_DISABLE1      = 0xffffffff;
    IRQ_DISABLE2      = 0xffffffff;
    for (index = 0; index < MAX_HANDLERS; index ++)
    {
        isr_table[index].handler = default_isr_handler;
        isr_table[index].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_strncpy(isr_table[index].name, "unknown", RT_NAME_MAX);
        isr_table[index].counter = 0;
#endif
    }

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;
#else
    rt_uint32_t gic_cpu_base;
    rt_uint32_t gic_dist_base;
    rt_uint32_t gic_irq_start;

    /* initialize vector table */
    rt_hw_vector_init();

    /* initialize exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));

    /* initialize ARM GIC */
#ifdef RT_USING_USERSPACE
    gic_dist_base = (uint32_t)rt_hw_mmu_map(&mmu_info, 0, (void*)platform_get_gic_dist_base(), 0x2000, MMU_MAP_K_RW);
    gic_cpu_base = (uint32_t)rt_hw_mmu_map(&mmu_info, 0, (void*)platform_get_gic_cpu_base(), 0x1000, MMU_MAP_K_RW);
#else
    gic_dist_base = platform_get_gic_dist_base();
    gic_cpu_base = platform_get_gic_cpu_base();
#endif

    gic_irq_start = GIC_IRQ_START;

    arm_gic_dist_init(0, gic_dist_base, gic_irq_start);
    arm_gic_cpu_init(0, gic_cpu_base);
#endif
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
#ifdef SOC_BCM283x
    if (vector < 32)
    {
        IRQ_DISABLE1 = (1 << vector);
    }
    else if (vector < 64)
    {
        vector = vector % 32;
        IRQ_DISABLE2 = (1 << vector);
    }
    else
    {
        vector = vector - 64;
        IRQ_DISABLE_BASIC = (1 << vector);
    }
#else
    arm_gic_mask(0, vector);
#endif
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
#ifdef SOC_BCM283x
if (vector < 32)
    {
        IRQ_ENABLE1 = (1 << vector);
    }
    else if (vector < 64)
    {
        vector = vector % 32;
        IRQ_ENABLE2 = (1 << vector);
    }
    else
    {
        vector = vector - 64;
        IRQ_ENABLE_BASIC = (1 << vector);
    }
#else
    arm_gic_umask(0, vector);
#endif
}

/**
 * This function returns the active interrupt number.
 * @param none
 */
int rt_hw_interrupt_get_irq(void)
{
#ifndef SOC_BCM283x
    return arm_gic_get_active_irq(0) & GIC_ACK_INTID_MASK;
#else
    return 0;
#endif
}

/**
 * This function acknowledges the interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_ack(int vector)
{
#ifndef SOC_BCM283x
    arm_gic_ack(0, vector);
#endif
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
