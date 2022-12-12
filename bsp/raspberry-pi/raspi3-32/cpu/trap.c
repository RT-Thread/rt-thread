/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 * 2019-07-28     zdzn         add smp support
 * 2019-08-09     zhangjun     fixup the problem of smp startup and scheduling issues,
 *                             write addr to mailbox3 to startup smp, and we use mailbox0 for ipi
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

#ifdef RT_USING_CPU_FFS
int __rt_ffs(int value)
{
    if (!value)
    {
        return 0;
    }

    int num = 1;

    if ((value & 0xffff) == 0)
    {
        num += 16;
        value >>= 16;
    }
    if ((value & 0xff) == 0)
    {
        num += 8;
        value >>= 8;
    }
    if ((value & 0xf) == 0)
    {
        num += 4;
        value >>= 4;
    }
    if ((value & 0x3) == 0)
    {
        num += 2;
        value >>= 2;
    }
    if ((value & 0x1) == 0)
    {
        num += 1;
    }

    return num;
}
#endif

void rt_hw_trap_irq(void)
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

}
