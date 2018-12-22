/*
 * COPYRIGHT (C) 2013-2014, Shanghai Real-Thread Technology Co., Ltd
 *
 *  All rights reserved.
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
 */

#include <rtthread.h>
#include <rthw.h>

#include "zynq7000.h"
#include "gic.h"

extern struct rt_thread *rt_current_thread;
#ifdef RT_USING_FINSH
extern long list_thread(void);
#endif

/**
 * this function will show registers of CPU
 *
 * @param regs the registers point
 */
void rt_hw_show_register (struct rt_hw_exp_stack *regs)
{
    rt_kprintf("Execption:\n");
    rt_kprintf("r00:0x%08x r01:0x%08x r02:0x%08x r03:0x%08x\n", regs->r0, regs->r1, regs->r2, regs->r3);
    rt_kprintf("r04:0x%08x r05:0x%08x r06:0x%08x r07:0x%08x\n", regs->r4, regs->r5, regs->r6, regs->r7);
    rt_kprintf("r08:0x%08x r09:0x%08x r10:0x%08x\n", regs->r8, regs->r9, regs->r10);
    rt_kprintf("fp :0x%08x ip :0x%08x\n", regs->fp, regs->ip);
    rt_kprintf("sp :0x%08x lr :0x%08x pc :0x%08x\n", regs->sp, regs->lr, regs->pc);
    rt_kprintf("cpsr:0x%08x\n", regs->cpsr);
}

/**
 * When comes across an instruction which it cannot handle,
 * it takes the undefined instruction trap.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_undef(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("undefined instruction:\n");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

/**
 * The software interrupt instruction (SWI) is used for entering
 * Supervisor mode, usually to request a particular supervisor
 * function.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_swi(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("software interrupt:\n");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

/**
 * An abort indicates that the current memory access cannot be completed,
 * which occurs during an instruction prefetch.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_pabt(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("prefetch abort:\n");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

/**
 * An abort indicates that the current memory access cannot be completed,
 * which occurs during a data access.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_dabt(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("data abort:");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

/**
 * Normally, system will never reach here
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_resv(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("reserved trap:\n");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

#define GIC_ACK_INTID_MASK					0x000003ff

void rt_hw_trap_irq()
{
    void *param;
    unsigned long ir;
    unsigned long fullir;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    fullir = arm_gic_get_active_irq(0);
    ir = fullir & GIC_ACK_INTID_MASK;

    /* get interrupt service routine */
    isr_func = isr_table[ir].handler;
    if (isr_func)
    {
        param = isr_table[ir].param;
        /* turn to interrupt service routine */
        isr_func(ir, param);
    }

    /* end of interrupt */
    arm_gic_ack(0, fullir);
}

void rt_hw_trap_fiq()
{
    void *param;
    unsigned long ir;
    unsigned long fullir;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    fullir = arm_gic_get_active_irq(0);
    ir = fullir & GIC_ACK_INTID_MASK;

    /* get interrupt service routine */
    isr_func = isr_table[ir].handler;
    param = isr_table[ir].param;

    /* turn to interrupt service routine */
    isr_func(ir, param);

    /* end of interrupt */
    arm_gic_ack(0, fullir);
}

