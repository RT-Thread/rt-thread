/*
 * File      : contex_armasm.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Development Team
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
 * 2018-09-09     liruncong    the first version
 */

	AREA	CONTEXT, CODE, READONLY, ALIGN=5
	PRESERVE8

#define Mode_USR		0x10
#define Mode_FIQ		0x11
#define Mode_IRQ		0x12
#define Mode_SVC		0x13
#define Mode_ABT		0x17
#define Mode_UND		0x1B
#define Mode_SYS		0x1F
#define Mode_MASK		0x1F

#define T_Bit			0x20			// thumb bit
#define F_Bit			0x40			// fiq bit
#define I_Bit			0x80			// irq bit

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
	EXPORT  rt_hw_interrupt_disable
rt_hw_interrupt_disable
	mrs r0, cpsr
	cpsid if
	bx  lr

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
	EXPORT rt_hw_interrupt_enable
rt_hw_interrupt_enable
	msr cpsr_c, r0
	bx  lr

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * r0 --> from
 * r1 --> to
 */
	EXPORT rt_hw_context_switch
rt_hw_context_switch
	stmfd   sp!, {lr}
	stmfd   sp!, {r0-r12, lr}

	mrs r4, cpsr
	tst lr, #0x01
	orrne r4, r4, #T_Bit
	stmfd sp!, {r4}

	str sp, [r0]
	ldr sp, [r1]

	ldmfd sp!, {r4}
	msr spsr_cxsf, r4

_do_switch
	ldmfd sp!, {r0-r12, lr, pc}^

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * r0 --> to
 */
	EXPORT rt_hw_context_switch_to
rt_hw_context_switch_to
	ldr sp, [r0]

	ldmfd sp!, {r4}
	msr spsr_cxsf, r4

	bic r4, r4, #T_Bit
	msr cpsr_cxsf, r4

	ldmfd sp!, {r0-r12, lr, pc}^

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
 */
	IMPORT rt_thread_switch_interrupt_flag
	IMPORT rt_interrupt_from_thread
	IMPORT rt_interrupt_to_thread
	EXPORT rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt
	ldr r2, =rt_thread_switch_interrupt_flag
	ldr r3, [r2]
	cmp r3, #1
	beq _reswitch
	mov r3, #1
	str r3, [r2]
	ldr r2, =rt_interrupt_from_thread
	str r0, [r2]
_reswitch
	ldr r2, =rt_interrupt_to_thread
	str r1, [r2]
	bx  lr

	END
