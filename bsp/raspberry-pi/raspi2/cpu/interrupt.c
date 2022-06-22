/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/5/3       Bernard      first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "cp15.h"
#include <board.h>

#define MAX_HANDLERS                64

extern volatile rt_uint8_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];

rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

extern void rt_cpu_vector_set_base(unsigned int addr);
extern int system_vectors;

void rt_hw_vector_init(void)
{
    rt_cpu_vector_set_base((unsigned int)&system_vectors);
}

static void default_isr_handler(int vector, void *param)
{
    rt_kprintf("unhandled irq: %d\n", vector);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    uint32_t index;

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
    if (vector < 8)
    {
        IRQ_DISABLE_BASIC = (1 << vector);
    }
    else if (vector < 32)
    {
        IRQ_DISABLE1 = (1 << vector);
    }
    else
    {
        vector = vector % 32;
        IRQ_DISABLE2 = (1 << vector);
    }
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    if (vector < 8)
    {
        IRQ_ENABLE_BASIC = (1 << vector);
    }
    else if (vector < 32)
    {
        IRQ_ENABLE1 = (1 << vector);
    }
    else
    {
        vector = vector % 32;
        IRQ_ENABLE2 = (1 << vector);
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
