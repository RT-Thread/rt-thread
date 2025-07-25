/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 * 2020-03-02     Howard Su    Use structure to access registers
 */

#include <rthw.h>
#include <rtthread.h>

#include "interrupt.h"

extern rt_atomic_t rt_interrupt_nest;
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

static struct rt_irq_desc isr_table[INTERRUPTS_MAX];

static void rt_hw_interrupt_handler(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    rt_int32_t idx;

    rt_memset(isr_table, 0x00, sizeof(isr_table));
    for (idx = 0; idx < INTERRUPTS_MAX; idx ++)
    {
        isr_table[idx].handler = rt_hw_interrupt_handler;
    }

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest               = 0;
    rt_interrupt_from_thread        = 0;
    rt_interrupt_to_thread          = 0;
    rt_thread_switch_interrupt_flag = 0;

    /* set base_addr reg */
    INTC->base_addr_reg = 0x00000000;
    /* clear enable */
    INTC->en_reg[0] = 0x00000000;
    INTC->en_reg[1] = 0x00000000;
    /* mask interrupt */
    INTC->mask_reg[0] = 0xFFFFFFFF;
    INTC->mask_reg[1] = 0xFFFFFFFF;
    /* clear pending */
    INTC->pend_reg[0] = 0x00000000;
    INTC->pend_reg[1] = 0x00000000;
    /* set priority */
    INTC->resp_reg[0] = 0x00000000;
    INTC->resp_reg[1] = 0x00000000;
    /* close fiq interrupt */
    INTC->ff_reg[0] = 0x00000000;
    INTC->ff_reg[1] = 0x00000000;
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    int index;
    if ((vector < 0) || (vector >= INTERRUPTS_MAX))
    {
        return;
    }

    index = (vector & 0xE0) != 0;
    vector = (vector & 0x1F);

    INTC->mask_reg[index] |= 1 << vector;
}

/**

 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    int index;
    if ((vector < 0) || (vector >= INTERRUPTS_MAX))
    {
        return;
    }

    index = (vector & 0xE0) != 0;
    vector = (vector & 0x1F);

    INTC->mask_reg[index] &= ~(1 << vector);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param handler the interrupt service routine to be installed
 * @param param the interrupt service function parameter
 * @param name the interrupt name
 * @return old handler
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;
    int index;

    if ((vector < 0) || (vector >= INTERRUPTS_MAX))
    {
        return old_handler;
    }

    old_handler = isr_table[vector].handler;

#ifdef RT_USING_INTERRUPT_INFO
    rt_strncpy(isr_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
    isr_table[vector].handler = handler;
    isr_table[vector].param = param;

    index = (vector & 0xE0) != 0;
    vector = (vector & 0x1F);

    INTC->pend_reg[index] &= ~(0x1 << vector);
    INTC->en_reg[index] |= 0x1 << vector;

    return old_handler;
}

void rt_interrupt_dispatch(rt_uint32_t fiq_irq)
{
    void *param;
    int vector;
    rt_isr_handler_t isr_func;
    int index;

    vector = INTC->vector_reg - INTC->base_addr_reg;
    vector = vector >> 2;

    isr_func = isr_table[vector].handler;
    param = isr_table[vector].param;

    /* jump to fun */
    isr_func(vector, param);
    /* clear pend bit */

    index = (vector & 0xE0) != 0;
    vector = (vector & 0x1F);

    INTC->pend_reg[index] &= ~(0x1 << vector);

#ifdef RT_USING_INTERRUPT_INFO
    isr_table[vector].counter ++;
#endif
}









