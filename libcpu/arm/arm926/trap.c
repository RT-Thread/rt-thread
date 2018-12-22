/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      modified from mini2440
 * 2015-04-15     ArdaFu     Split from AT91SAM9260 BSP
 */

#include <rtthread.h>
#include <rthw.h>

#define INT_IRQ     0x00
#define INT_FIQ     0x01

extern struct rt_thread *rt_current_thread;
#ifdef RT_USING_FINSH
extern long list_thread(void);
#endif

struct rt_hw_register
{
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t fp;
    rt_uint32_t ip;
    rt_uint32_t sp;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t cpsr;
    rt_uint32_t ORIG_r0;
};

/**
 * this function will show registers of CPU
 *
 * @param regs the registers point
 */

void rt_hw_show_register (struct rt_hw_register *regs)
{
    rt_kprintf("Execption:\n");
    rt_kprintf("r00:0x%08x r01:0x%08x r02:0x%08x r03:0x%08x\n",
               regs->r0, regs->r1, regs->r2, regs->r3);
    rt_kprintf("r04:0x%08x r05:0x%08x r06:0x%08x r07:0x%08x\n",
               regs->r4, regs->r5, regs->r6, regs->r7);
    rt_kprintf("r08:0x%08x r09:0x%08x r10:0x%08x\n",
               regs->r8, regs->r9, regs->r10);
    rt_kprintf("fp :0x%08x ip :0x%08x\n",
               regs->fp, regs->ip);
    rt_kprintf("sp :0x%08x lr :0x%08x pc :0x%08x\n",
               regs->sp, regs->lr, regs->pc);
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
    rt_hw_show_register(regs);

    rt_kprintf("undefined instruction\n");
    rt_kprintf("thread - %s stack:\n", rt_current_thread->name);

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
    rt_kprintf("thread - %s stack:\n", RT_NAME_MAX, rt_current_thread->name);

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
void rt_hw_trap_dabt(struct rt_hw_register *regs)
{
    rt_hw_show_register(regs);

    rt_kprintf("data abort\n");
    rt_kprintf("thread - %s stack:\n", RT_NAME_MAX, rt_current_thread->name);

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
void rt_hw_trap_resv(struct rt_hw_register *regs)
{
    rt_kprintf("not used\n");
    rt_hw_show_register(regs);
    rt_hw_cpu_shutdown();
}

extern struct rt_irq_desc irq_desc[];
extern rt_uint32_t rt_hw_interrupt_get_active(rt_uint32_t fiq_irq);
extern void rt_hw_interrupt_ack(rt_uint32_t fiq_irq, rt_uint32_t id);
    
void rt_hw_trap_irq()
{
    rt_isr_handler_t isr_func;
    rt_uint32_t irq;
    void *param;

    /* get irq number */
    irq = rt_hw_interrupt_get_active(INT_IRQ);

    /* get interrupt service routine */
    isr_func = irq_desc[irq].handler;
    param = irq_desc[irq].param;

    /* turn to interrupt service routine */
    isr_func(irq, param);

    rt_hw_interrupt_ack(INT_IRQ, irq);
#ifdef RT_USING_INTERRUPT_INFO
    irq_desc[irq].counter ++;
#endif
}

void rt_hw_trap_fiq()
{
    rt_isr_handler_t isr_func;
    rt_uint32_t irq;
    void *param;

    /* get irq number */
    irq = rt_hw_interrupt_get_active(INT_FIQ);

    /* get interrupt service routine */
    isr_func = irq_desc[irq].handler;
    param = irq_desc[irq].param;

    /* turn to interrupt service routine */
    isr_func(irq, param);

    rt_hw_interrupt_ack(INT_FIQ, irq);
#ifdef RT_USING_INTERRUPT_INFO
    irq_desc[irq].counter ++;
#endif
}
