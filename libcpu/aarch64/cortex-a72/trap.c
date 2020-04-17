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

#define GIC_ACK_INTID_MASK              0x000003ff

int rt_hw_interrupt_get_irq(void);
void rt_hw_interrupt_ack(int fiq_irq);

void rt_hw_trap_irq(void)
{
    void *param;
    int ir; 
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    ir = rt_hw_interrupt_get_irq();
    if (ir == 1023)
    {
        /* Spurious interrupt */
        return;
    }

    /* get interrupt service routine */
    isr_func = isr_table[ir].handler;
#ifdef RT_USING_INTERRUPT_INFO
    isr_table[ir].counter++;
#endif
    if (isr_func)
    {
        /* Interrupt for myself. */
        param = isr_table[ir].param;
        /* turn to interrupt service routine */
        isr_func(ir, param);
    }

    /* end of interrupt */
    rt_hw_interrupt_ack(ir);

}

void rt_hw_trap_fiq(void)
{
}
