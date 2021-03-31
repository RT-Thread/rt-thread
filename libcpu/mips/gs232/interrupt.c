/*
 * Interrupt handle for GS232
 *
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-15     Bernard      first version
 * 2010-10-15     lgnq         modified for LS1B
 * 2013-03-29     aozima       Modify the interrupt interface implementations.
 * 2015-07-06     chinesebear  modified for loongson 1c
 * 2019-12-04     Jiaxun Yang  Generialize
 */

#include <rtthread.h>
#include <rthw.h>
#include "gs232.h"


#define MAX_INTR            (GS232_NR_IRQS)

static struct rt_irq_desc irq_handle_table[MAX_INTR];
void rt_hw_timer_handler();

static struct gs232_intc_regs volatile *gs232_hw0_icregs
= (struct gs232_intc_regs volatile *)(INTC_BASE);

/**
 * @addtogroup Loongson GS232
 */

/*@{*/

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
    rt_int32_t i;
    rt_uint32_t c0_status = 0;

    for (i=0; i < GS232_INTC_CELLS; i++)
    {
        /* Disable */
        (gs232_hw0_icregs+i)->int_en = 0x0;
        /* Trigger active low */
        (gs232_hw0_icregs+i)->int_pol = -1;    /* Must be done here */
        /* Make all interrupts level triggered */
        (gs232_hw0_icregs+i)->int_edge = 0x00000000;
        /* Mask all interrupts */
        (gs232_hw0_icregs+i)->int_clr = 0xffffffff;
        mips_unmask_cpu_irq(i + 2);
    }

    rt_memset(irq_handle_table, 0x00, sizeof(irq_handle_table));
    for (idx = 0; idx < MAX_INTR; idx ++)
    {
        irq_handle_table[idx].handler = rt_hw_interrupt_handler;
    }
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    /* mask interrupt */
    (gs232_hw0_icregs+(vector>>5))->int_en &= ~(1 << (vector&0x1f));
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    (gs232_hw0_icregs+(vector>>5))->int_en |= (1 << (vector&0x1f));
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

    if (vector >= 0 && vector < MAX_INTR)
    {
        old_handler = irq_handle_table[vector].handler;

#ifdef RT_USING_INTERRUPT_INFO
        rt_strncpy(irq_handle_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
        irq_handle_table[vector].handler = handler;
        irq_handle_table[vector].param = param;
    }

    return old_handler;
}


/**
 * Call ISR
 * @IRQn ID of IRQ
 */
void gs232_do_IRQ(int IRQn)
{
    rt_isr_handler_t irq_func;
    void *param;

    irq_func = irq_handle_table[IRQn].handler;
    param    = irq_handle_table[IRQn].param;

    irq_func(IRQn, param);

#ifdef RT_USING_INTERRUPT_INFO
    irq_handle_table[IRQn].counter++;
#endif

    return ;
}


void rt_do_mips_cpu_irq(rt_uint32_t ip)
{
    rt_uint32_t intstatus, irq, n;

    if (ip == 7) {
        rt_hw_timer_handler();
    } else {
        n = ip - 2;
        /* Receive interrupt signal, compute the irq */
        intstatus = (gs232_hw0_icregs+n)->int_isr & (gs232_hw0_icregs+n)->int_en;
        if (0 == intstatus)
            return ;

        irq = __rt_ffs(intstatus) - 1;
        gs232_do_IRQ((n<<5) + irq);

        /* ack interrupt */
        (gs232_hw0_icregs+n)->int_clr |= (1 << irq);
    }
}


/*@}*/


