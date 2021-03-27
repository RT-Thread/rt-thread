/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-7-14      Peng Fan     sep6200 implementation
 */

/**
 * \addtogroup sep6200
 */

/*@{*/

#define NOINT			0xc0

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.globl rt_hw_interrupt_disable
.type rt_hw_interrupt_disable, %function
rt_hw_interrupt_disable:
  stw.w   r1, [sp-], #4
	mov    	r0, asr
	or    	r1, r0, #NOINT
	mov.a 	asr, r1
  ldw.w   r1, [sp]+, #4
	mov	    pc, lr

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.globl rt_hw_interrupt_enable
.type rt_hw_interrupt_disable, %function
rt_hw_interrupt_enable:
	mov.a asr, r0
	mov pc, lr

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * r0 --> from
 * r1 --> to
 */
.globl rt_hw_context_switch
.type rt_hw_interrupt_disable, %function
rt_hw_context_switch:
	stm.w   (lr), [sp-]
	stm.w	(r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, lr), [sp-]
	stm.w	(r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15),  [sp-]
	mov	r4, asr
	stm.w	(r4), [sp-]
	mov 	r4, bsr
	stm.w	(r4), [sp-]

	stw	sp, [r0+]
	ldw	sp, [r1+]

	ldm.w	(r4), [sp]+
	mov.a	bsr,r4
	ldm.w	(r4), [sp]+
	mov.a	asr, r4

	ldm.w	(r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15), [sp]+
	ldm.w	(r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, lr, pc), [sp]+

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * r0 --> to
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
	ldw	sp, [r0+]
	ldm.w	(r4), [sp]+
	mov.a	bsr, r4
	ldm.w	(r4), [sp]+
	mov.a	asr, r4
	ldm.w	(r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15), [sp]+
	ldm.w	(r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, lr, pc), [sp]+

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
 */
.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
.globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
	ldw r2, =rt_thread_switch_interrupt_flag
	ldw r3, [r2+]
	cmpsub.a r3, #1
	beq _reswitch
	mov r3, #1
	stw r3, [r2+]
	ldw r2, =rt_interrupt_from_thread
	stw r0, [r2+]
_reswitch:
	ldw r2, =rt_interrupt_to_thread
	stw r1, [r2+]
	mov pc, lr
