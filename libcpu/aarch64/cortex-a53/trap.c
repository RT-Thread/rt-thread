/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei    the first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "interrupt.h"
#include "armv8.h"

extern struct rt_thread *rt_current_thread;
#ifdef RT_USING_FINSH
extern long list_thread(void);
#endif

/**
 * this function will show registers of CPU
 *
 * @param regs the registers point
 */
void rt_hw_show_register(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("Execption:\n");
    rt_kprintf("r00:0x%16.16lx r01:0x%16.16lx r02:0x%16.16lx r03:0x%16.16lx\n", regs->x0, regs->x1, regs->x2, regs->x3);
    rt_kprintf("r04:0x%16.16lx r05:0x%16.16lx r06:0x%16.16lx r07:0x%16.16lx\n", regs->x4, regs->x5, regs->x6, regs->x7);
	rt_kprintf("r08:0x%16.16lx r09:0x%16.16lx r10:0x%16.16lx r11:0x%16.16lx\n", regs->x8, regs->x9, regs->x10, regs->x11);
	rt_kprintf("r12:0x%16.16lx r13:0x%16.16lx r14:0x%16.16lx r15:0x%16.16lx\n", regs->x12, regs->x13, regs->x14, regs->x15);
	rt_kprintf("r16:0x%16.16lx r17:0x%16.16lx r18:0x%16.16lx r19:0x%16.16lx\n", regs->x16, regs->x17, regs->x18, regs->x19);
	rt_kprintf("r20:0x%16.16lx r21:0x%16.16lx r22:0x%16.16lx r23:0x%16.16lx\n", regs->x20, regs->x21, regs->x22, regs->x23);
    rt_kprintf("r24:0x%16.16lx r25:0x%16.16lx r26:0x%16.16lx r27:0x%16.16lx\n", regs->x24, regs->x25, regs->x26, regs->x27);
	rt_kprintf("r28:0x%16.16lx r29:0x%16.16lx r30:0x%16.16lx\n", regs->x28, regs->x29, regs->x30);
	rt_kprintf("spsr:0x%16.16lx\n", regs->spsr);
	rt_kprintf("return pc:0x%16.16lx\n", regs->pc);
}

/**
 * When comes across an instruction which it cannot handle,
 * it takes the undefined instruction trap.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_error(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("error exception:\n");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

#define GIC_ACK_INTID_MASK              (0x000003ff)
#define CORE0_IRQ_SOURCE	            (0x40000060)

void rt_hw_trap_irq(void)
{
    void *param;
    uint32_t irq;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];
    uint32_t value = 0;
    value = IRQ_PEND_BASIC & 0x3ff;
#ifdef BSP_USING_CORETIMER
    uint32_t int_source = HWREG32(CORE0_IRQ_SOURCE)  & 0x3ff;
    if (int_source & 0x02)
    {
        isr_func = isr_table[IRQ_ARM_TIMER].handler;
        #ifdef RT_USING_INTERRUPT_INFO
                    isr_table[IRQ_ARM_TIMER].counter++;
        #endif
        if (isr_func)
        {
            param = isr_table[IRQ_ARM_TIMER].param;
            isr_func(IRQ_ARM_TIMER, param);
        }
    }
#endif
    /* local interrupt*/
    if (value)
    {
        if (value & (1 << 8))
        {
            value = IRQ_PEND1;
            irq = __rt_ffs(value) - 1;
        }
        else if (value & (1 << 9))
        {
            value = IRQ_PEND2;
            irq = __rt_ffs(value) + 31;
        }
        else
        {
            value &= 0x0f;
            irq = __rt_ffs(value) + 63;
        }

        /* get interrupt service routine */
        isr_func = isr_table[irq].handler;
#ifdef RT_USING_INTERRUPT_INFO
        isr_table[irq].counter++;
#endif
        if (isr_func)
        {
            /* Interrupt for myself. */
            param = isr_table[irq].param;
            /* turn to interrupt service routine */
            isr_func(irq, param);
        }
    }
}

void rt_hw_trap_fiq(void)
{
    void *param;
    uint32_t irq;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];
    uint32_t value = 0;
    value = IRQ_PEND_BASIC & 0x3ff;
#ifdef RT_USING_SMP
    uint32_t mailbox_data;
    uint32_t cpu_id = rt_hw_cpu_id();
    uint32_t int_source = CORE_IRQSOURCE(cpu_id);
    mailbox_data = IPI_MAILBOX_CLEAR(cpu_id);
    if (int_source & 0x0f)
    {
        if (int_source & 0x08)
        {
            isr_func = isr_table[IRQ_ARM_TIMER].handler;
#ifdef RT_USING_INTERRUPT_INFO
            isr_table[IRQ_ARM_TIMER].counter++;
#endif
            if (isr_func)
            {
                param = isr_table[IRQ_ARM_TIMER].param;
                isr_func(IRQ_ARM_TIMER, param);
            }
        }
    }
    if (int_source & 0xf0)
    {
        /*it's a ipi interrupt*/
        if (mailbox_data & 0x1)
        {
            /* clear mailbox */
            IPI_MAILBOX_CLEAR(cpu_id) = mailbox_data;
            isr_func = isr_table[IRQ_ARM_MAILBOX].handler;
#ifdef RT_USING_INTERRUPT_INFO
            isr_table[IRQ_ARM_MAILBOX].counter++;
#endif
            if (isr_func)
            {
                param = isr_table[IRQ_ARM_MAILBOX].param;
                isr_func(IRQ_ARM_MAILBOX, param);
            }
        }
        else
            CORE_MAILBOX3_CLEAR(cpu_id) = mailbox_data;
    }
#endif
    /* local interrupt*/
    if (value)
    {
        if (value & (1 << 8))
        {
            value = IRQ_PEND1;
            irq = __rt_ffs(value) - 1;
        }
        else if (value & (1 << 9))
        {
            value = IRQ_PEND2;
            irq = __rt_ffs(value) + 31;
        }
        else
        {
            value &= 0x0f;
            irq = __rt_ffs(value) + 63;
        }

        /* get interrupt service routine */
        isr_func = isr_table[irq].handler;
#ifdef RT_USING_INTERRUPT_INFO
        isr_table[irq].counter++;
#endif
        if (irq > 1)
            rt_kprintf("interrupt fiq %d\n", irq);
        if (isr_func)
        {
            /* Interrupt for myself. */
            param = isr_table[irq].param;
            /* turn to interrupt service routine */
            isr_func(irq, param);
        }
    }
}
