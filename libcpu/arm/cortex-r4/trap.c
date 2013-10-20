/*
 * File      : trap.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     XuXinming    first version
 * 2013-05-24     Grissiom     port to RM48x50
 */

#include <rtthread.h>
#include <rthw.h>

#include <sys_vim.h>

#include "armv7.h"

/**
 * @addtogroup RM48x50
 */
/*@{*/

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
void rt_hw_trap_udef(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("undefined instruction\n");
    rt_hw_show_register(regs);
	if (rt_thread_self() != RT_NULL)
		rt_kprintf("Current Thread: %s\n", rt_thread_self()->name);
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
void rt_hw_trap_svc(struct rt_hw_exp_stack *regs)
{
    rt_kprintf("software interrupt\n");
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
    rt_kprintf("prefetch abort\n");
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
    rt_kprintf("Data Abort ");
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
    rt_kprintf("Reserved trap\n");
    rt_hw_show_register(regs);
#ifdef RT_USING_FINSH
	list_thread();
#endif
    rt_hw_cpu_shutdown();
}

extern rt_isr_handler_t isr_table[];
void rt_hw_trap_irq(void)
{
	int irqno;
	struct rt_irq_desc* irq;
	extern struct rt_irq_desc irq_desc[];

	irq = (struct rt_irq_desc*) vimREG->IRQVECREG;
	irqno = ((rt_uint32_t) irq - (rt_uint32_t) &irq_desc[0])/sizeof(struct rt_irq_desc);

	/* invoke isr */
	irq->handler(irqno, irq->param);
}

void rt_hw_trap_fiq(void)
{
    rt_kprintf("fast interrupt request\n");
}

/*@}*/
