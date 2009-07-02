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
 * 2006-09-06     XuXinming    first version
 * 2006-09-15     Bernard      modify rt_hw_trap_irq for more effective
 */

#include <rtthread.h>
#include <rthw.h>

#include "s3c44b0.h"

extern unsigned char interrupt_bank0[256];
extern unsigned char interrupt_bank1[256];
extern unsigned char interrupt_bank2[256];
extern unsigned char interrupt_bank3[256];

extern struct rt_thread *rt_current_thread;

/**
 * @addtogroup S3C44B0
 */
/*@{*/

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
	rt_hw_show_register(regs);

	rt_kprintf("undefined instruction\n");
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
    rt_kprintf("software interrupt\n");
    rt_hw_show_register(regs);
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

extern rt_isr_handler_t isr_table[];
void rt_hw_trap_irq()
{
	register unsigned long ispr, intstat;
	register rt_isr_handler_t isr_func;

#ifdef BSP_INT_DEBUG
	rt_kprintf("irq coming, ");
#endif
	intstat = I_ISPR & 0x7ffffff;
#ifdef BSP_INT_DEBUG
	rt_kprintf("I_ISPR: %d\n", intstat);
#endif

	ispr = intstat;

	/* to find interrupt */
	if ( intstat & 0xff ) /* lowest 8bits */
	{
		intstat = interrupt_bank0[intstat & 0xff];
		isr_func = (rt_isr_handler_t)isr_table[ intstat ];
	}
	else if ( intstat & 0xff00 ) /* low 8bits */
	{
		intstat = interrupt_bank1[(intstat & 0xff00) >> 8];
		isr_func = (rt_isr_handler_t)isr_table[ intstat ];
	}
	else if ( intstat & 0xff0000 ) /* high 8bits */
	{
		intstat = interrupt_bank2[(intstat & 0xff0000) >> 16];
		isr_func = (rt_isr_handler_t)isr_table[ intstat ];
	}
	else if ( intstat & 0xff000000 ) /* highest 8bits */
	{
		intstat = interrupt_bank3[(intstat & 0xff000000) >> 24];
		isr_func = (rt_isr_handler_t)isr_table[ intstat ];
	}
	else return;

#ifdef BSP_INT_DEBUG
	rt_kprintf("irq: %d happen\n", intstat);
#endif

	/* turn to interrupt service routine */
	isr_func(intstat);

	I_ISPC = ispr;		/* clear interrupt */
}

void rt_hw_trap_fiq()
{
    rt_kprintf("fast interrupt request\n");
}

/*@}*/
