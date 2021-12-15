/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#include "interrupt.h"
#include "c66xx.h"
#include "trap.h"

#define MAX_HANDLERS 128

extern volatile rt_uint8_t rt_interrupt_nest;
struct rt_irq_desc isr_table[MAX_HANDLERS];
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    // initial system trap
    //rt_trap_init();

    /* init exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));

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
    if (vector < 0 || vector >= MAX_HANDLERS)
    {
        return;
    }
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    if (vector < 0 || vector >= MAX_HANDLERS)
    {
        return;
    }
    ICR = vector;
    IER |= vector;

    //enable GIE
    TSR = TSR | 1;
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

    if (vector < MAX_HANDLERS || vector >= 0)
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

void rt_hw_interrupt_clear(int vector)
{
    if (vector < 0 || vector >= MAX_HANDLERS)
    {
        return;
    }
}
