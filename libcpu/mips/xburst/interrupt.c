/*
 * File      : interrupt.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
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
 * 2010-07-09     Bernard      first version
 * 2013-03-29     aozima       Modify the interrupt interface implementations.
 */

#include <rtthread.h>
#include <rthw.h>
#include <board.h>

#if defined(RT_USING_JZ4770) || defined(RT_USING_JZ4775) || defined(RT_USING_JZ_M150) || defined(RT_USING_JZ_X1000)
#define INTERRUPTS_MAX 64
#else
#define INTERRUPTS_MAX 32
#endif

extern rt_uint32_t rt_interrupt_nest;
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

static struct rt_irq_desc isr_table[INTERRUPTS_MAX];

/**
 * @addtogroup Ingenic
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
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    /* mask interrupt */
    __intc_mask_irq(vector);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    __intc_unmask_irq(vector);
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

#if  defined(RT_USING_JZ4770) || defined(RT_USING_JZ4775) || defined(RT_USING_JZ_M150) || defined(RT_USING_JZ_X1000)
/*
 * fls - find last bit set.
 * @word: The word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
rt_inline int fls(int x)
{
    __asm__("clz %0, %1" : "=r" (x) : "r" (x));

    return 32 - x;
}
#endif

#include <mipsregs.h>

void rt_interrupt_dispatch(void *ptreg)
{
    int i;
    void *param;
    rt_isr_handler_t irq_func;

#if  defined(RT_USING_JZ4770) || defined(RT_USING_JZ4775) || defined(RT_USING_JZ_M150) || defined(RT_USING_JZ_X1000)
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
#ifndef RT_USING_JZ_X1000 /* X1000 has no VPU */
        else
        {
            __asm__ __volatile__ (
                "mfc0  %0, $13,  0   \n\t"
                "nop                  \n\t"
                :"=r"(vpu_pending)
                :);

            if(vpu_pending & 0x800)
                irq = IRQ_VPU;
            else
                return;
        }
#endif

        if (irq >= INTERRUPTS_MAX)
            rt_kprintf("max interrupt, irq=%d\n", irq);

        /* do interrupt */
        irq_func = isr_table[irq].handler;
        param = isr_table[irq].param;
        (*irq_func)(irq, param);

#ifdef RT_USING_INTERRUPT_INFO
        isr_table[i].counter++;
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
#else
    static rt_uint32_t pending = 0;

    /* the hardware interrupt */
    pending |= REG_INTC_IPR;
    if (!pending) return;

    for (i = INTERRUPTS_MAX; i > 0; --i)
    {
        if ((pending & (1<<i)))
        {
            pending &= ~(1<<i);

            /* do interrupt */
            irq_func = isr_table[i].handler;
            param = isr_table[i].param;
            (*irq_func)(i, param);

#ifdef RT_USING_INTERRUPT_INFO
            isr_table[i].counter++;
#endif /* RT_USING_INTERRUPT_INFO */

            /* ack interrupt */
            __intc_ack_irq(i);
        }
    }
#endif
}

/*@}*/
