/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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
#include "interrupt.h"
#include "gic.h"
#include "gicv3.h"

#ifdef RT_USING_SMART
#include "ioremap.h"
#else
#define rt_ioremap(x, ...) (x)
#endif

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];

#ifndef RT_USING_SMP
/* Those variables will be accessed in ISR, so we need to share them. */
rt_ubase_t rt_interrupt_from_thread        = 0;
rt_ubase_t rt_interrupt_to_thread          = 0;
rt_ubase_t rt_thread_switch_interrupt_flag = 0;
#endif

#ifndef RT_CPUS_NR
#define RT_CPUS_NR 1
#endif

const unsigned int VECTOR_BASE = 0x00;
extern void rt_cpu_vector_set_base(void *addr);
extern void *system_vectors;

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
    rt_cpu_vector_set_base(&system_vectors);
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
    rt_uint64_t gic_cpu_base;
    rt_uint64_t gic_dist_base;
#ifdef BSP_USING_GICV3
    rt_uint64_t gic_rdist_base;
#endif
    rt_uint64_t gic_irq_start;

    /* initialize vector table */
    rt_hw_vector_init();

    /* initialize exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));

    /* initialize ARM GIC */
#ifdef RT_USING_SMART
    gic_dist_base = (rt_uint64_t)rt_ioremap((void*)platform_get_gic_dist_base(), 0x2000);
    gic_cpu_base = (rt_uint64_t)rt_ioremap((void*)platform_get_gic_cpu_base(), 0x1000);
#ifdef BSP_USING_GICV3
    gic_rdist_base = (rt_uint64_t)rt_ioremap((void*)platform_get_gic_redist_base(),
            RT_CPUS_NR * (2 << 16));
#endif
#else
    gic_dist_base = platform_get_gic_dist_base();
    gic_cpu_base = platform_get_gic_cpu_base();
#ifdef BSP_USING_GICV3
    gic_rdist_base = platform_get_gic_redist_base();
#endif
#endif

    gic_irq_start = GIC_IRQ_START;

    arm_gic_dist_init(0, gic_dist_base, gic_irq_start);
    arm_gic_cpu_init(0, gic_cpu_base);
#ifdef BSP_USING_GICV3
    arm_gic_redist_init(0, gic_rdist_base);
#endif
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
    return arm_gic_get_active_irq(0);
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

#ifndef SOC_BCM283x
/**
 * This function set interrupt CPU targets.
 * @param vector:   the interrupt number
 *        cpu_mask: target cpus mask, one bit for one core
 */
void rt_hw_interrupt_set_target_cpus(int vector, unsigned int cpu_mask)
{
    arm_gic_set_cpu(0, vector, cpu_mask);
}

/**
 * This function get interrupt CPU targets.
 * @param vector: the interrupt number
 * @return target cpus mask, one bit for one core
 */
unsigned int rt_hw_interrupt_get_target_cpus(int vector)
{
    return arm_gic_get_target_cpu(0, vector);
}

/**
 * This function set interrupt triger mode.
 * @param vector: the interrupt number
 *        mode:   interrupt triger mode; 0: level triger, 1: edge triger
 */
void rt_hw_interrupt_set_triger_mode(int vector, unsigned int mode)
{
    arm_gic_set_configuration(0, vector, mode);
}

/**
 * This function get interrupt triger mode.
 * @param vector: the interrupt number
 * @return interrupt triger mode; 0: level triger, 1: edge triger
 */
unsigned int rt_hw_interrupt_get_triger_mode(int vector)
{
    return arm_gic_get_configuration(0, vector);
}

/**
 * This function set interrupt pending flag.
 * @param vector: the interrupt number
 */
void rt_hw_interrupt_set_pending(int vector)
{
    arm_gic_set_pending_irq(0, vector);
}

/**
 * This function get interrupt pending flag.
 * @param vector: the interrupt number
 * @return interrupt pending flag, 0: not pending; 1: pending
 */
unsigned int rt_hw_interrupt_get_pending(int vector)
{
    return arm_gic_get_pending_irq(0, vector);
}

/**
 * This function clear interrupt pending flag.
 * @param vector: the interrupt number
 */
void rt_hw_interrupt_clear_pending(int vector)
{
    arm_gic_clear_pending_irq(0, vector);
}

/**
 * This function set interrupt priority value.
 * @param vector: the interrupt number
 *        priority: the priority of interrupt to set
 */
void rt_hw_interrupt_set_priority(int vector, unsigned int priority)
{
    arm_gic_set_priority(0, vector, priority);
}

/**
 * This function get interrupt priority.
 * @param vector: the interrupt number
 * @return interrupt priority value
 */
unsigned int rt_hw_interrupt_get_priority(int vector)
{
    return arm_gic_get_priority(0, vector);
}

/**
 * This function set priority masking threshold.
 * @param priority: priority masking threshold
 */
void rt_hw_interrupt_set_priority_mask(unsigned int priority)
{
    arm_gic_set_interface_prior_mask(0, priority);
}

/**
 * This function get priority masking threshold.
 * @param none
 * @return priority masking threshold
 */
unsigned int rt_hw_interrupt_get_priority_mask(void)
{
    return arm_gic_get_interface_prior_mask(0);
}

/**
 * This function set priority grouping field split point.
 * @param bits: priority grouping field split point
 * @return 0: success; -1: failed
 */
int rt_hw_interrupt_set_prior_group_bits(unsigned int bits)
{
    int status;

    if (bits < 8)
    {
        arm_gic_set_binary_point(0, (7 - bits));
        status = 0;
    }
    else
    {
        status = -1;
    }

    return (status);
}

/**
 * This function get priority grouping field split point.
 * @param none
 * @return priority grouping field split point
 */
unsigned int rt_hw_interrupt_get_prior_group_bits(void)
{
    unsigned int bp;

    bp = arm_gic_get_binary_point(0) & 0x07;

    return (7 - bp);
}
#endif /* SOC_BCM283x */

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

#ifdef RT_USING_SMP
void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
#ifdef BSP_USING_GICV2
    arm_gic_send_sgi(0, ipi_vector, cpu_mask, 0);
#elif defined(BSP_USING_GICV3)
    arm_gic_send_affinity_sgi(0, ipi_vector, (unsigned int *)&cpu_mask, GICV3_ROUTED_TO_SPEC);
#endif
}

void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler)
{
    /* note: ipi_vector maybe different with irq_vector */
    rt_hw_interrupt_install(ipi_vector, ipi_isr_handler, 0, "IPI_HANDLER");
}
#endif
