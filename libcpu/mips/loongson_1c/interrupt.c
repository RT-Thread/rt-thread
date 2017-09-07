/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date                  Author       Notes
 * 2010-10-15     Bernard      first version
 * 2010-10-15     lgnq           modified for LS1B
 * 2013-03-29     aozima       Modify the interrupt interface implementations.
 * 2015-07-06     chinesebear modified for loongson 1c
 */

#include <rtthread.h>
#include <rthw.h>
#include "ls1c.h"
#include "ls1c_public.h"


#define MAX_INTR            (LS1C_NR_IRQS)

extern rt_uint32_t rt_interrupt_nest;
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

static struct rt_irq_desc irq_handle_table[MAX_INTR];
void rt_interrupt_dispatch(void *ptreg);
void rt_hw_timer_handler();

static struct ls1c_intc_regs volatile *ls1c_hw0_icregs
= (struct ls1c_intc_regs volatile *)(LS1C_INTREG_BASE);

/**
 * @addtogroup Loongson LS1B
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

    // 设置协处理器0的状态寄存器SR的IM7-2，允许中断
    c0_status = read_c0_status();
    c0_status |= 0xFC00;
    write_c0_status(c0_status);

    // 龙芯1c的中断分为五组
    for (i=0; i<5; i++)
    {
        /* disable */
        (ls1c_hw0_icregs+i)->int_en = 0x0;
        /* pci active low */
        (ls1c_hw0_icregs+i)->int_pol = -1;	   //must be done here 20110802 lgnq
        /* make all interrupts level triggered */
        (ls1c_hw0_icregs+i)->int_edge = 0x00000000;
        /* mask all interrupts */
        (ls1c_hw0_icregs+i)->int_clr = 0xffffffff;
    }

    rt_memset(irq_handle_table, 0x00, sizeof(irq_handle_table));
    for (idx = 0; idx < MAX_INTR; idx ++)
    {
        irq_handle_table[idx].handler = rt_hw_interrupt_handler;
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
    /* mask interrupt */
    (ls1c_hw0_icregs+(vector>>5))->int_en &= ~(1 << (vector&0x1f));
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    (ls1c_hw0_icregs+(vector>>5))->int_en |= (1 << (vector&0x1f));
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
                                         void *param, char *name)
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
 * 执行中断处理函数
 * @IRQn 中断号
 */
void ls1c_do_IRQ(int IRQn)
{
    rt_isr_handler_t irq_func;
    void *param;

    // 找到中断处理函数
    irq_func = irq_handle_table[IRQn].handler;
    param    = irq_handle_table[IRQn].param;

    // 执行中断处理函数
    irq_func(IRQn, param);
    
#ifdef RT_USING_INTERRUPT_INFO
    irq_handle_table[IRQn].counter++;
#endif

    return ;
}


void ls1c_irq_dispatch(int n)
{
    rt_uint32_t intstatus, irq;

    /* Receive interrupt signal, compute the irq */
    intstatus = (ls1c_hw0_icregs+n)->int_isr & (ls1c_hw0_icregs+n)->int_en;
    if (0 == intstatus)
        return ;

    // 执行中断处理函数
    irq = ls1c_ffs(intstatus) - 1;
    ls1c_do_IRQ((n<<5) + irq);

    /* ack interrupt */
    (ls1c_hw0_icregs+n)->int_clr |= (1 << irq);

    return ;
}


void rt_interrupt_dispatch(void *ptreg)
{
    int irq;
    void *param;
    rt_isr_handler_t irq_func;
    static rt_uint32_t status = 0;
    rt_uint32_t c0_status;
    rt_uint32_t c0_cause;
    volatile rt_uint32_t cause_im;
    volatile rt_uint32_t status_im;
    rt_uint32_t pending_im;

    /* check os timer */
    c0_status = read_c0_status();
    c0_cause = read_c0_cause();

    cause_im = c0_cause & ST0_IM;
    status_im = c0_status & ST0_IM;
    pending_im = cause_im & status_im;

    if (pending_im & CAUSEF_IP7)
    {
        rt_hw_timer_handler();
    }
    else if (pending_im & CAUSEF_IP2)
    {
        ls1c_irq_dispatch(0);
    }
    else if (pending_im & CAUSEF_IP3)
    {
        ls1c_irq_dispatch(1);
    }
    else if (pending_im & CAUSEF_IP4)
    {
        ls1c_irq_dispatch(2);
    }
    else if (pending_im & CAUSEF_IP5)
    {
        ls1c_irq_dispatch(3);
    }
    else if (pending_im & CAUSEF_IP6)
    {
        ls1c_irq_dispatch(4);
    }
}

/*@}*/


