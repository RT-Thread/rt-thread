/*
 * File      : context.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
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
 * 2011-01-13     weety    copy from mini2440
 */

/*!
 * \addtogroup AT91SAM926X
 */
/*@{*/

#define NOINT			0xc0


/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
	mrs r0, cpsr
	orr r1, r0, #NOINT
	msr cpsr_c, r1
	mov pc, lr

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
	msr cpsr, r0
	mov pc, lr

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * r0 --> from
 * r1 --> to
 */
.globl rt_hw_context_switch
rt_hw_context_switch:
	stmfd	sp!, {lr}		@ push pc (lr should be pushed in place of PC)
	stmfd	sp!, {r0-r12, lr}	@ push lr & register file

	mrs	r4, cpsr
	stmfd	sp!, {r4}		@ push cpsr
	mrs	r4, spsr
	stmfd	sp!, {r4}		@ push spsr

	str	sp, [r0]			@ store sp in preempted tasks TCB
	ldr	sp, [r1]			@ get new task stack pointer

	ldmfd	sp!, {r4}		@ pop new task spsr
	msr	spsr_cxsf, r4
	ldmfd	sp!, {r4}		@ pop new task cpsr
	msr	spsr_cxsf, r4

	ldmfd	sp!, {r0-r12, lr, pc}^	@ pop new task r0-r12, lr & pc

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * r0 --> to
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
	ldr	sp, [r0]		@ get new task stack pointer

	ldmfd	sp!, {r4}		@ pop new task spsr
	msr	spsr_cxsf, r4
	ldmfd	sp!, {r4}		@ pop new task cpsr
	msr	cpsr_cxsf, r4

	ldmfd	sp!, {r0-r12, lr, pc}	@ pop new task r0-r12, lr & pc

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
 */
.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
.globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
	ldr r2, =rt_thread_switch_interrupt_flag
	ldr r3, [r2]
	cmp r3, #1
	beq _reswitch
	mov r3, #1				@ set rt_thread_switch_interrupt_flag to 1
	str r3, [r2]
	ldr r2, =rt_interrupt_from_thread	@ set rt_interrupt_from_thread
	str r0, [r2]
_reswitch:
	ldr r2, =rt_interrupt_to_thread		@ set rt_interrupt_to_thread
	str r1, [r2]
	mov pc, lr
