/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/5/3       Bernard      first version
 * 2019-07-28     zdzn         add smp support
 * 2019-08-09     zhangjun     fixup the problem of smp startup and scheduling issues, 
 *                             write addr to mailbox3 to startup smp, and we use mailbox0 for ipi
 */

#include <rthw.h>
#include <rtthread.h>

#include "cp15.h"
#include <board.h>

#define MAX_HANDLERS                72

#ifdef RT_USING_SMP
#define rt_interrupt_nest rt_cpu_self()->irq_nest
#else
extern volatile rt_uint8_t rt_interrupt_nest;
#endif

const unsigned int VECTOR_BASE = 0x00;
extern void rt_cpu_vector_set_base(unsigned int addr);
extern int system_vectors;

void rt_hw_vector_init(void)
{
    rt_cpu_vector_set_base((unsigned int)&system_vectors);
}

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];

rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

extern int system_vectors;

static void default_isr_handler(int vector, void *param)
{
#ifdef RT_USING_SMP
    rt_kprintf("cpu %d unhandled irq: %d\n", rt_hw_cpu_id(),vector);
#else
    rt_kprintf("unhandled irq: %d\n",vector);
#endif
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    rt_uint32_t index;

    /* mask all of interrupts */
    IRQ_DISABLE_BASIC = 0x000000ff;
    IRQ_DISABLE1      = 0xffffffff;
    IRQ_DISABLE2      = 0xffffffff;
    for (index = 0; index < MAX_HANDLERS; index ++)
    {
        isr_table[index].handler = default_isr_handler;
        isr_table[index].param = NULL;
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
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{

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
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
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

#ifdef RT_USING_SMP
void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    __DSB();
    if (cpu_mask & 0x1)
    {
        send_ipi_msg(0, ipi_vector);
    }
    if (cpu_mask & 0x2)
    {
    	send_ipi_msg(1, ipi_vector);
    }
    if (cpu_mask & 0x4)
    {
    	send_ipi_msg(2, ipi_vector);
    }
    if (cpu_mask & 0x8)
    {
    	send_ipi_msg(3, ipi_vector);
    }
    __DSB();
}
#endif

#ifdef RT_USING_SMP
void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler)
{
    /* note: ipi_vector maybe different with irq_vector */
    rt_hw_interrupt_install(ipi_vector, ipi_isr_handler, 0, "IPI_HANDLER");
}
#endif
