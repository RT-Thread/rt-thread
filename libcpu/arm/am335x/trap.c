/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-23     Bernard      first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "am33xx.h"
#include "interrupt.h"

#ifdef RT_USING_GDB
#include "gdb_stub.h"
#endif

/**
 * @addtogroup AM33XX
 */
/*@{*/

extern struct rt_thread *rt_current_thread;
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
extern long list_thread(void);
#endif

/**
 * this function will show registers of CPU
 *
 * @param regs the registers point
 */

void rt_hw_show_register (struct rt_hw_register *regs)
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
 * When ARM7TDMI comes across an instruction which it cannot handle,
 * it takes the undefined instruction trap.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_udef(struct rt_hw_register *regs)
{

#ifdef RT_USING_GDB
    regs->pc -= 4; //lr in undef is pc + 4
    if (gdb_undef_hook(regs))
        return;
#endif

    rt_hw_show_register(regs);

    rt_kprintf("undefined instruction\n");
    rt_kprintf("thread %.*s stack:\n", RT_NAME_MAX, rt_current_thread->name);

#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
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
void rt_hw_trap_swi(struct rt_hw_register *regs)
{
    rt_hw_show_register(regs);

    rt_kprintf("software interrupt\n");
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
void rt_hw_trap_pabt(struct rt_hw_register *regs)
{
    rt_hw_show_register(regs);

    rt_kprintf("prefetch abort\n");
    rt_kprintf("thread %.*s stack:\n", RT_NAME_MAX, rt_current_thread->name);

#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
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
void rt_hw_trap_dabt(struct rt_hw_register *regs)
{

#ifdef RT_USING_GDB
    if (gdb_mem_fault_handler) {
        regs->pc = (unsigned long)gdb_mem_fault_handler;
        return;
    }
#endif
    rt_hw_show_register(regs);

    rt_kprintf("data abort\n");
    rt_kprintf("thread %.*s stack:\n", RT_NAME_MAX, rt_current_thread->name);

#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

void rt_hw_trap_irq()
{
    void *param;
    unsigned long ir;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    ir = rt_hw_interrupt_get_active(INT_IRQ);
    if (ir == 127)
    {
        /* new IRQ generation */
        rt_hw_interrupt_ack(INT_IRQ);
        ir = rt_hw_interrupt_get_active(INT_IRQ);
        if (ir == 127)
        {
            /* still spurious interrupt, get out */
            /*rt_kprintf("still spurious interrupt\n");*/
            return;
        }
        /*rt_kprintf("new IRQ: %d\n", ir);*/
    }

    /* get interrupt service routine */
    isr_func = isr_table[ir].handler;
    param = isr_table[ir].param;

    /* turn to interrupt service routine */
    if (isr_func != RT_NULL)
        isr_func(ir, param);

    /* new IRQ generation */
    rt_hw_interrupt_ack(INT_IRQ);
}

void rt_hw_trap_fiq()
{
    void *param;
    unsigned long ir;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    ir = rt_hw_interrupt_get_active(INT_FIQ);

    /* get interrupt service routine */
    isr_func = isr_table[ir].handler;
    param = isr_table[ir].param;

    /* turn to interrupt service routine */
    isr_func(ir, param);

    /* new FIQ generation */
    rt_hw_interrupt_ack(INT_FIQ);
}

/*@}*/
