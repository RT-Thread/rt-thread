/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 */

#include <rthw.h>
#include <board.h>
#include <rtthread.h>

#include "armv7.h"

extern struct rt_thread *rt_current_thread;
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
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
void rt_hw_trap_swi(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("software interrupt:\n");
    rt_hw_show_register(regs);
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
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
void rt_hw_trap_dabt(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("data abort:");
    rt_hw_show_register(regs);
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
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
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
    list_thread();
#endif
    rt_hw_cpu_shutdown();
}

void rt_hw_trap_irq(void)
{
    void *param;
    rt_isr_handler_t isr_func;
    extern struct rt_irq_desc isr_table[];

    uint32_t value = 0;

    // rt_kprintf("pend basic: 0x%08x\n", IRQ_PEND_BASIC);
    // rt_kprintf("     pend1: 0x%08x\n", IRQ_PEND1);
    // rt_kprintf("     pend2: 0x%08x\n", IRQ_PEND2);

    value = IRQ_PEND_BASIC & 0x3ff;
    if (value)
    {
        uint32_t irq;

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
            irq = __rt_ffs(value) - 1;
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
    /* TODO */
}
