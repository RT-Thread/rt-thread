/*
 * File      : start_armasm.S
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

	AREA	START, CODE, READONLY, ALIGN=5
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

#define UND_Stack_Size	0x00000200
#define SVC_Stack_Size	0x00000100
#define ABT_Stack_Size	0x00000000
#define FIQ_Stack_Size	0x00000000
#define IRQ_Stack_Size	0x00000100
#define USR_Stack_Size	0x00000100

#define ISR_Stack_Size  (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + FIQ_Stack_Size + IRQ_Stack_Size)

/* stack */
	EXPORT stack_start
	EXPORT stack_top
stack_start
	SPACE   (ISR_Stack_Size << 2)
stack_top

/* reset entry */
	EXPORT _reset
_reset
	mrs     r0, cpsr
	bic     r0, r0, #Mode_MASK
	orr     r0, r0, #(Mode_SVC :OR: I_Bit :OR: F_Bit)	// 注: reset和fiq进入时其实cpu已屏蔽中断
	msr     cpsr_c, r0

	bl      stack_setup

	mov		r0, #0
	mcr		p15, #0, r0, c7, c5, #6
	isb
	// reset c1: disable C/A/M bit
	mrc		p15, 0, r0, c1, c0, 0
	bic     r0, r0, #0x00000007							// clean C/A/M bits
	bic		r0, r0, #0x00001000							// clean I bit
	orr		r0, r0, #0x00000800							// set Z bit
	mcr		p15, 0, r0, c1, c0, 0
	// open NEON and FPU
	//mrc		p15, 0, r0, c1, c0, 2
	//orr		r0, r0, #0x00f00000
	//mcr		p15, 0, r0, c1, c0, 2
	//isb
	//mov		r0, #0x40000000
	//msr		FPEXC, r0

	// open icache and dcache
	IMPORT rt_hw_cpu_icache_enable
	bl		rt_hw_cpu_icache_enable
	IMPORT rt_hw_cpu_dcache_enable
	bl		rt_hw_cpu_dcache_enable
	// startup
	ldr     pc, _rtthread_startup
	IMPORT	__main
_rtthread_startup
	DCD		__main

stack_setup
	ldr     r0, =stack_top

	msr     cpsr_c, #(Mode_UND :OR: I_Bit :OR: F_Bit)
	mov     sp, r0
	sub     r0, r0, #UND_Stack_Size

	msr     cpsr_c, #(Mode_ABT :OR: I_Bit :OR: F_Bit)
	mov     sp, r0
	sub     r0, r0, #ABT_Stack_Size

	msr     cpsr_c, #(Mode_FIQ :OR: I_Bit :OR: F_Bit)
	mov     sp, r0
	sub     r0, r0, #FIQ_Stack_Size

	msr     cpsr_c, #(Mode_IRQ :OR: I_Bit :OR: F_Bit)
	mov     sp, r0
	sub     r0, r0, #IRQ_Stack_Size

	msr     cpsr_c, #(Mode_SVC :OR: I_Bit :OR: F_Bit)
	mov     sp, r0
	sub     r0, r0, #SVC_Stack_Size

	mov     sp, r0
	sub     sl, sp, #USR_Stack_Size
	bx      lr

	ALIGN   32
	EXPORT vector_undef
vector_undef
	sub     sp, sp, #72
	stmia   sp, {r0 - r12}
	add     r8, sp, #52

	mrs     r1, cpsr
	mrs     r2, spsr
	orr     r2, r2, #(I_Bit :OR: F_Bit)
	msr     cpsr_c, r2
	mov     r0, r0
	str     sp, [r8], #4
	str     lr, [r8], #4
	msr     cpsr_c, r1

	str     lr, [r8], #4
	mrs     r6, spsr
	str     r6, [r8], #4
	str     r0, [r8]
	mov     r0, sp

	IMPORT	rt_hw_trap_udef
	bl      rt_hw_trap_udef

	ldmia	sp, {r0 - r12}
	mov		r0, r0
	ldr		lr, [sp, #60]
	add		sp, sp, #72
	movs	pc, lr

	ALIGN   32
	EXPORT	vector_swi
	IMPORT	rt_hw_trap_swi
vector_swi
	bl      rt_hw_trap_swi

	ALIGN 	32
	EXPORT	vector_pabt
	IMPORT	rt_hw_trap_pabt
vector_pabt
	bl      rt_hw_trap_pabt

	ALIGN   32
	EXPORT	vector_dabt
	IMPORT	rt_hw_trap_dabt
vector_dabt
	sub     sp, sp, #72
	stmia   sp, {r0 - r12}
	add     r8, sp, #52

	mrs     r1, cpsr
	mrs     r2, spsr
	orr     r2, r2, #(I_Bit :OR: F_Bit)
	msr     cpsr_c, r2
	mov     r0, r0
	str     sp, [r8], #4
	str     lr, [r8], #4
	msr     cpsr_c, r1

	str     lr, [r8], #4
	mrs     r6, spsr
	str     r6, [r8], #4
	str     r0, [r8]
	mov     r0, sp

	bl      rt_hw_trap_dabt

	ldmia    sp, {r0 - r12}
	mov      r0, r0
	ldr      lr, [sp, #60]
	add      sp, sp, #72
	movs     pc, lr

	ALIGN  32
	EXPORT	vector_resv
vector_resv
	b       .

	ALIGN   32
	EXPORT	vector_fiq
	IMPORT	rt_hw_trap_fiq
vector_fiq
	stmfd   sp!, {r0-r8, lr}
	bl      rt_hw_trap_fiq
	ldmfd   sp!, {r0-r8, lr}
	subs    pc, lr, #4

	IMPORT	rt_interrupt_enter
	IMPORT	rt_interrupt_leave
	IMPORT	rt_thread_switch_interrupt_flag
	IMPORT	rt_interrupt_from_thread
	IMPORT	rt_interrupt_to_thread

	EXPORT	vector_irq
	IMPORT	rt_hw_trap_irq
vector_irq
	stmfd   sp!, {r0-r12, lr}

	bl      rt_interrupt_enter
	bl      rt_hw_trap_irq
	bl      rt_interrupt_leave

	ldr     r0, =rt_thread_switch_interrupt_flag
	ldr     r1, [r0]
	cmp     r1, #1
	beq     rt_hw_context_switch_interrupt_do

	ldmfd   sp!, {r0-r12, lr}
	subs    pc, lr, #4

rt_hw_context_switch_interrupt_do
	mov     r1,  #0
	str     r1,  [r0]

	ldmfd   sp!, {r0-r12, lr}
	stmfd   sp,  {r0-r2}

	sub     r1,  sp, #4*3
	mrs     r0,  spsr
	sub     r2,  lr, #4

	msr     cpsr_c, #(I_Bit :OR: F_Bit :OR: Mode_SVC)

	stmfd   sp!, {r2}
	stmfd   sp!, {r3-r12,lr}
	ldmfd   r1,  {r1-r3}
	stmfd   sp!, {r1-r3}
	stmfd   sp!, {r0}

	ldr     r4,  =rt_interrupt_from_thread
	ldr     r5,  [r4]
	str     sp,  [r5]

	ldr     r6,  =rt_interrupt_to_thread
	ldr     r6,  [r6]
	ldr     sp,  [r6]

	ldmfd   sp!, {r4}
	msr     spsr_cxsf, r4

	ldmfd   sp!, {r0-r12,lr,pc}^

	END
