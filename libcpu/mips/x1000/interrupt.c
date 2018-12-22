/*
 * File      : cpu_intc.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016/09/07     Urey         the first version
 */

#include <stdio.h>
#include <stdlib.h>

#include <rtthread.h>
#include <rthw.h>
#include <board.h>

#include "../common/mips.h"

#define INTERRUPTS_MAX	64

extern rt_uint32_t rt_interrupt_nest;
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

static struct rt_irq_desc isr_table[INTERRUPTS_MAX];

static void rt_hw_interrupt_handler(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

void rt_hw_interrupt_init(void)
{
    rt_int32_t idx;

	clear_c0_status(0xff04); /* clear ERL */
	set_c0_status(0x0400);   /* set IP2 */


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

	/* enable cpu interrupt mask */
	set_c0_status(IE_IRQ0 | IE_IRQ1);
}

void rt_hw_interrupt_mask(int vector)
{
    /* mask interrupt */
    __intc_mask_irq(vector);
}

void rt_hw_interrupt_umask(int vector)
{
    __intc_unmask_irq(vector);
}

rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if(vector < INTERRUPTS_MAX)
    {
        old_handler = isr_table[vector].handler;

#ifdef RT_USING_INTERRUPT_INFO
        rt_strncpy(isr_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
        isr_table[vector].handler = handler;
        isr_table[vector].param = param;
    }

    return old_handler;
}

rt_inline int fls(int x)
{
    __asm__("clz %0, %1" : "=r" (x) : "r" (x));

    return 32 - x;
}

void rt_interrupt_dispatch(void *ptreg)
{
    void *param;
    rt_isr_handler_t irq_func;

    int irq = 0, group;
    rt_uint32_t intc_ipr0 = 0, intc_ipr1 = 0, vpu_pending = 0;

    rt_uint32_t c0_status, c0_cause;
    rt_uint32_t pending_im;

    /* check os timer */
    c0_status = read_c0_status();
    c0_cause = read_c0_cause();

	pending_im = (c0_cause & ST0_IM) & (c0_status & ST0_IM);

    if (pending_im & CAUSEF_IP3)
    {
		extern void rt_hw_ost_handler(void);
        rt_hw_ost_handler();
        return;
    }
    if (pending_im & CAUSEF_IP2)
    {
        intc_ipr0 = REG_INTC_IPR(0);
        intc_ipr1 = REG_INTC_IPR(1);

        if (intc_ipr0)
        {
            irq = fls(intc_ipr0) - 1;
            intc_ipr0 &= ~(1<<irq);
        }
        else if(intc_ipr1)
        {
            irq = fls(intc_ipr1) - 1;
            intc_ipr1 &= ~(1<<irq);
            irq += 32;
        }
        else
        {
        	//VPU
        }

        if (irq >= INTERRUPTS_MAX)
            rt_kprintf("max interrupt, irq=%d\n", irq);

        /* do interrupt */
        irq_func = isr_table[irq].handler;
        param = isr_table[irq].param;
        (*irq_func)(irq, param);

#ifdef RT_USING_INTERRUPT_INFO
        isr_table[irq].counter++;
#endif /* RT_USING_INTERRUPT_INFO */

        /* ack interrupt */
        __intc_ack_irq(irq);
    }

    if (pending_im & CAUSEF_IP0)
        rt_kprintf("CAUSEF_IP0\n");
    if (pending_im & CAUSEF_IP1)
        rt_kprintf("CAUSEF_IP1\n");
    if (pending_im & CAUSEF_IP4)
        rt_kprintf("CAUSEF_IP4\n");
    if (pending_im & CAUSEF_IP5)
        rt_kprintf("CAUSEF_IP5\n");
    if (pending_im & CAUSEF_IP6)
        rt_kprintf("CAUSEF_IP6\n");
    if (pending_im & CAUSEF_IP7)
        rt_kprintf("CAUSEF_IP7\n");
}

#ifdef RT_USING_INTERRUPT_INFO
#include <finsh.h>
int list_irqs(void)
{
    int index;

    rt_kprintf("interrupt list:\n");
    rt_kprintf("----------------\n");
    rt_kprintf("name     counter\n");
    for (index = 0; index < INTERRUPTS_MAX; index ++)
    {
        if (isr_table[index].handler != rt_hw_interrupt_handler)
        {
            rt_kprintf("%-*.*s %d\n", RT_NAME_MAX, RT_NAME_MAX, isr_table[index].name, isr_table[index].counter);
        }
    }

    return 0;
}
MSH_CMD_EXPORT(list_irqs, list interrupt counter);
#endif

unsigned int spin_lock_irqsave(void)
{
	register unsigned int t;
	t = read_c0_status();
	write_c0_status((t & (~1)));
	return (t);
}

void spin_unlock_irqrestore(unsigned int val)
{
	write_c0_status(val);
}
