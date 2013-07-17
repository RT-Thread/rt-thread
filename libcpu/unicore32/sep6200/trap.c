/*
 * File      : trap.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
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
 * Date           Author       Notes
 * 2013-03-16     Peng Fan     Modifiled from sep4020
 */

#include <rtthread.h>
#include <rthw.h>

#include <sep6200.h>

/**
 * @addtogroup sep6200
 */
/*@{*/

extern struct rt_thread *rt_current_thread;

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
	rt_kprintf("r08:0x%08x r09:0x%08x r10:0x%08x r11:0x%08x\n", regs->r8, regs->r9, regs->r10,regs->r11);
	rt_kprintf("r12:0x%08x r13:0x%08x r14:0x%08x r15:0x%08x\n", regs->r12,regs->r13,regs->r14,regs->r15);
	rt_kprintf("r16:0x%08x r17:0x%08x r18:0x%08x r19:0x%08x\n", regs->r16,regs->r17,regs->r18,regs->r19);
	rt_kprintf("r20:0x%08x r21:0x%08x r22:0x%08x r23:0x%08x\n", regs->r20,regs->r21,regs->r22,regs->r23);
	rt_kprintf("r24:0x%08x sb:0x%08x  sl:0x%08xfp :0x%08x ip :0x%08x\n",regs->r24,regs->sb,regs->sl,regs->fp,regs->ip);
	rt_kprintf("sp :0x%08x lr :0x%08x pc :0x%08x\n", regs->sp, regs->lr, regs->pc);
	rt_kprintf("asr:0x%08x bsr:0x%08x\n", regs->asr,regs->bsr);
}

/**
 * When unicore comes across an instruction which it cannot handle,
 * it takes the extn instruction trap.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_extn(struct rt_hw_register *regs)
{
	rt_hw_show_register(regs);

	rt_kprintf("extn instruction\n");
	rt_kprintf("thread - %s stack:\n", rt_current_thread->name);
	rt_hw_backtrace((rt_uint32_t *)regs->fp, (rt_uint32_t)rt_current_thread->entry);

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
	rt_kprintf("thread - %s stack:\n", rt_current_thread->name);
	rt_hw_backtrace((rt_uint32_t *)regs->fp, (rt_uint32_t)rt_current_thread->entry);

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
	rt_kprintf("thread - %s stack:\n", rt_current_thread->name);
	rt_hw_backtrace((rt_uint32_t *)regs->fp, (rt_uint32_t)rt_current_thread->entry);

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

extern struct rt_irq_desc isr_table[];

void rt_hw_trap_irq(void)
{
  unsigned long intstat;
  rt_uint32_t irq = 0;
  rt_isr_handler_t isr_func;
  void *param;

  /* get the interrupt number */
	irq = *(RP)(SEP6200_VIC_IRQ_VECTOR_NUM);

  /* get interrupt service routine */
  isr_func = isr_table[irq].handler;
  param = isr_table[irq].param;

  /* turn to interrupt service routine */
  isr_func(irq, param);

#ifdef RT_USING_INTERRUPT_INFO
	isr_table[irq].counter++;
#endif /* RT_USING_INTERRUPT_INFO */
}

void rt_hw_trap_fiq()
{
	rt_kprintf("fast interrupt request\n");
}

/*@}*/
