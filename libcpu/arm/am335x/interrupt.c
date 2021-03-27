/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard      first version
 * 2015-11-06     zchong       support iar compiler
 */

#include <rthw.h>
#include <rtthread.h>

#include "am33xx.h"
#include "interrupt.h"

#define AINTC_BASE  AM33XX_AINTC_REGS

#define MAX_HANDLERS    128

extern volatile rt_uint8_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * @addtogroup AM33xx
 */
/*@{*/

void rt_dump_aintc(void)
{
    int k;
    rt_kprintf("active irq %d", INTC_SIR_IRQ(AINTC_BASE));
    rt_kprintf("\n--- hw mask ---\n");
    for (k = 0; k < 4; k++)
    {
        rt_kprintf("0x%08x, ", INTC_MIR(AINTC_BASE, k));
    }
    rt_kprintf("\n--- hw itr ---\n");
    for (k = 0; k < 4; k++)
    {
        rt_kprintf("0x%08x, ", INTC_ITR(AINTC_BASE, k));
    }
    rt_kprintf("\n");
}

const unsigned int AM335X_VECTOR_BASE = 0x4030FC00;
extern void rt_cpu_vector_set_base(unsigned int addr);
#ifdef __ICCARM__
extern int __vector;
#else
extern int system_vectors;
#endif

static void rt_hw_vector_init(void)
{
    unsigned int *dest = (unsigned int *)AM335X_VECTOR_BASE;

#ifdef __ICCARM__
    unsigned int *src =  (unsigned int *)&__vector;
#else
    unsigned int *src =  (unsigned int *)&system_vectors;
#endif

    rt_memcpy(dest, src, 16 * 4);
    rt_cpu_vector_set_base(AM335X_VECTOR_BASE);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    /* initialize vector table */
    rt_hw_vector_init();

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
    INTC_MIR_SET(AINTC_BASE, vector >> 0x05) = 0x1 << (vector & 0x1f);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    INTC_MIR_CLEAR(AINTC_BASE, vector >> 0x05) = 0x1 << (vector & 0x1f);
}

/**
 * This function will control the interrupt attribute.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_control(int vector, int priority, int route)
{
    int fiq;

    if (route == 0)
        fiq = 0;
    else
        fiq = 1;

    INTC_ILR(AINTC_BASE, vector) = ((priority << 0x02) & 0x1FC) | fiq ;
}

int rt_hw_interrupt_get_active(int fiq_irq)
{
    int ir;
    if (fiq_irq == INT_FIQ)
    {
        ir = INTC_SIR_FIQ(AINTC_BASE) & 0x7f;
    }
    else
    {
        ir = INTC_SIR_IRQ(AINTC_BASE) & 0x7f;
    }

    return ir;
}

void rt_hw_interrupt_ack(int fiq_irq)
{
    if (fiq_irq == INT_FIQ)
    {
        /* new FIQ generation */
        INTC_CONTROL(AINTC_BASE) |= 0x02;
    }
    else
    {
        /* new IRQ generation */
        INTC_CONTROL(AINTC_BASE) |= 0x01;
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

    if(vector < MAX_HANDLERS)
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
 * This function will trigger an interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_trigger(int vector)
{
    INTC_ISR_SET(AINTC_BASE, vector>>5) = 1 << (vector & 0x1f);
}

void rt_hw_interrupt_clear(int vector)
{
    INTC_ISR_CLEAR(AINTC_BASE, vector>>5) = 1 << (vector & 0x1f);
}

void rt_dump_isr_table(void)
{
    int idx;
    for(idx = 0; idx < MAX_HANDLERS; idx++)
    {
#ifdef RT_USING_INTERRUPT_INFO
        rt_kprintf("nr:%4d, name: %*.s, handler: 0x%p, param: 0x%08x\r\n",
                idx, RT_NAME_MAX, isr_table[idx].name,
                isr_table[idx].handler, isr_table[idx].param);
#else
        rt_kprintf("nr:%4d, handler: 0x%p, param: 0x%08x\r\n",
                idx, isr_table[idx].handler, isr_table[idx].param);
#endif
    }
}
/*@}*/


