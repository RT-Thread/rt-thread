/*
 * File      : context_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-11     Bernard      first version
 */

/**
 * @addtogroup STM32
 */
/*@{*/

.cpu cortex-m3
.fpu softvfp
.syntax unified
.thumb
.text

.equ	NVIC_INT_CTRL,       0xE000ED04               /* interrupt control state register */
.equ	NVIC_SYSPRI2,        0xE000ED20               /* system priority register (2) */
.equ	NVIC_PENDSV_PRI,     0x00FF0000               /* PendSV priority value (lowest) */
.equ	NVIC_PENDSVSET,      0x10000000               /* value to trigger PendSV exception */

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.global rt_hw_interrupt_disable
.type rt_hw_interrupt_disable, %function
rt_hw_interrupt_disable:
	MRS		r0, PRIMASK
	CPSID	I
	BX		LR

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.global rt_hw_interrupt_enable
.type rt_hw_interrupt_enable, %function
rt_hw_interrupt_enable:
	MSR		PRIMASK, r0
	BX		LR

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * r0 --> from
 * r1 --> to
 */
.global rt_hw_context_switch_interrupt
.type rt_hw_context_switch_interrupt, %function
.global rt_hw_context_switch
.type rt_hw_context_switch, %function

rt_hw_context_switch_interrupt:
rt_hw_context_switch:
	/* set rt_thread_switch_interrput_flag to 1 */
	LDR 	r2, =rt_thread_switch_interrput_flag
	LDR 	r3, [r2]
	CMP 	r3, #1
	BEQ 	_reswitch
	MOV 	r3, #1
	STR 	r3, [r2]

	LDR 	r2, =rt_interrupt_from_thread	/* set rt_interrupt_from_thread */
	STR 	r0, [r2]

_reswitch:
	LDR 	r2, =rt_interrupt_to_thread		/* set rt_interrupt_to_thread */
	STR 	r1, [r2]

	LDR		r0, =NVIC_INT_CTRL      		/* trigger the PendSV exception (causes context switch) */
	LDR		r1, =NVIC_PENDSVSET
	STR		r1, [r0]
	BX		LR

/* r0 --> swith from thread stack
 * r1 --> swith to thread stack
 * psr, pc, lr, r12, r3, r2, r1, r0 are pushed into [from] stack
 */
.global rt_hw_pend_sv
.type rt_hw_pend_sv, %function
rt_hw_pend_sv:
	/* disable interrupt to protect context switch */
	MRS		r2, PRIMASK
	CPSID	I

	/* get rt_thread_switch_interrupt_flag */
	LDR		r0, =rt_thread_switch_interrput_flag
	LDR		r1, [r0]
	CBZ		r1, pendsv_exit			/* pendsv already handled */

	/* clear rt_thread_switch_interrput_flag to 0 */
	MOV		r1, #0x00
	STR		r1, [r0]

	LDR		r0, =rt_interrupt_from_thread
	LDR		r1, [r0]
	CBZ		r1, swtich_to_thread    /* skip register save at the first time */

	MRS		r1, psp					/* get from thread stack pointer */
	STMFD	r1!, {r4 - r11}			/* push r4 - r11 register */
	LDR		r0, [r0]
	STR		r1, [r0]				/* update from thread stack pointer */

swtich_to_thread:
	LDR		r1, =rt_interrupt_to_thread
	LDR		r1, [r1]
	LDR		r1, [r1]				/* load thread stack pointer */

	LDMFD	r1!, {r4 - r11}			/* pop r4 - r11 register */
	MSR		psp, r1					/* update stack pointer */

pendsv_exit:
	/* restore interrupt */
	MSR		PRIMASK, r2

	ORR		lr, lr, #0x04
	BX		lr

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * r0 --> to
 */
.global rt_hw_context_switch_to
.type rt_hw_context_switch_to, %function
rt_hw_context_switch_to:
	LDR		r1, =rt_interrupt_to_thread
	STR		r0, [r1]

	/* set from thread to 0 */
	LDR		r1, =rt_interrupt_from_thread
	MOV		r0, #0x0
	STR		r0, [r1]

	/* set interrupt flag to 1 */
	LDR 	r1, =rt_thread_switch_interrput_flag
	MOV 	r0, #1
	STR 	r0, [r1]

	/* set the PendSV exception priority */
	LDR		r0, =NVIC_SYSPRI2
	LDR		r1, =NVIC_PENDSV_PRI
	STR		r1, [r0]

	LDR		r0, =NVIC_INT_CTRL      /* trigger the PendSV exception (causes context switch) */
	LDR		r1, =NVIC_PENDSVSET
	STR		r1, [r0]

	CPSIE	I                       /* enable interrupts at processor level */

	/* never reach here! */

/* compatible with old version */
.global rt_hw_interrupt_thread_switch
.type rt_hw_interrupt_thread_switch, %function
rt_hw_interrupt_thread_switch:
	BX		lr
	NOP
