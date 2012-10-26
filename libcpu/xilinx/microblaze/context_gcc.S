/*
 * File      : context_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-17     nl1031       first implementation for MicroBlaze.
 *
 */

#include "microblaze.inc"

	.text
    	.globl	rt_interrupt_enter
    	.globl	rt_interrupt_leave

/*
 * rt_base_t rt_hw_interrupt_disable()
 * copy from ucos-ii
 */

	.globl	rt_hw_interrupt_disable
	.ent	rt_hw_interrupt_disable
	.align	2
rt_hw_interrupt_disable:
    	ADDIK   r1, r1, -4
    	SW      r4, r1, r0

    	MFS     r3, RMSR
    	ANDNI   r4, r3, IE_BIT
    	MTS     RMSR, r4

    	LW      r4, r1, r0
    	ADDIK   r1, r1, 4

    	AND     r0, r0, r0             /* NO-OP - pipeline flush                             */
    	AND     r0, r0, r0             /* NO-OP - pipeline flush                             */
    	AND     r0, r0, r0             /* NO-OP - pipeline flush                             */

    	RTSD    r15, 8
    	AND     r0, r0, r0
	.end	rt_hw_interrupt_disable

/*
 * void rt_hw_interrupt_enable(rt_base_t level)
 * copy from ucos-ii
 */
	.globl	rt_hw_interrupt_enable
	.ent	rt_hw_interrupt_enable
	.align	2
rt_hw_interrupt_enable:
    	RTSD    r15, 8
    	MTS     rMSR, r5               		/* Move the saved status from r5 into rMSR            */
	.end	rt_hw_interrupt_enable

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to)
 * r5 --> from
 * r6 --> to
 */

	.globl rt_interrupt_from_thread
	.globl rt_interrupt_to_thread
	.globl rt_hw_context_switch
	.ent rt_hw_context_switch
	.align	2
rt_hw_context_switch:
	PUSH_ALL
    	MFS     r3,  RMSR                   /* save the MSR */
    	SWI     r3,  r1, STACK_RMSR
	SWI		r1,  r5, 0					/* store sp in preempted tasks TCB */
	LWI		r1,  r6, 0					/* get new task stack pointer */

    	LWI     r3,  r1, STACK_RMSR
    	ANDI    r3,  r3, IE_BIT
    	BNEI    r3,  rt_hw_context_switch_ie /*if IE bit set,should be use RTID (return from interrupt). */

    	LWI     r3,  r1, STACK_RMSR
    	MTS     RMSR,r3
	POP_ALL
    	ADDIK   r1,  r1, STACK_SIZE
    	RTSD    r15, 8
    	AND     r0,  r0, r0

rt_hw_context_switch_ie:

    	LWI     r3,  r1, STACK_RMSR
    	ANDNI   r3,  r3, IE_BIT         	/* clear IE bit, prevent interrupt occur immediately*/
    	MTS     RMSR,r3
    	LWI     r3,  r1, STACK_R03
	POP_ALL
    	ADDIK   r1,  r1, STACK_SIZE
    	RTID    r14, 0                    	/* IE bit will be set automatically */
    	AND     r0,  r0, r0
	.end	rt_hw_context_switch

/*
 * void rt_hw_context_switch_to(rt_uint32 to)
 * r5 --> to
 */
	.globl 	rt_hw_context_switch_to
	.ent   	rt_hw_context_switch_to
	.align	2
rt_hw_context_switch_to:
	LWI		r1,	 r5, 0 					/* get new task stack pointer */
    	LWI     r3,  r1, STACK_RMSR
    	ANDNI   r3,  r3, IE_BIT         	/* clear IE bit, prevent interrupt occur immediately*/
    	MTS     RMSR,r3
	POP_ALL
    	ADDIK   r1,  r1, STACK_SIZE
    	RTID    r14, 0                    	/* IE bit will be set automatically */
    	AND     r0,  r0, r0

	.end 	rt_hw_context_switch_to

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to)
 */
	.globl 	rt_thread_switch_interrupt_flag
	.globl 	rt_hw_context_switch_interrupt
	.ent rt_hw_context_switch_interrupt
	.align	2
rt_hw_context_switch_interrupt:
	LA	r3,	r0, rt_thread_switch_interrupt_flag
	LWI	r4, r3, 0					/* load rt_thread_switch_interrupt_flag into r4 */

	ANDI	r4, r4, 1
	BNEI	r4, _reswitch				/* if rt_thread_switch_interrupt_flag = 1 */

	ADDIK	r4, r0, 1					/* set rt_thread_switch_interrupt_flag to 1 */
	SWI	r4, r3, 0

	LA	r3, r0, rt_interrupt_from_thread /* set rt_interrupt_from_thread */
	SWI	r5, r3, 0 					/* rt_interrupt_from_thread = from */
_reswitch:
	LA	r3, r0, rt_interrupt_to_thread	/* set rt_interrupt_to_thread */
	SWI	r6, r3, 0 					/* rt_interrupt_to_thread = to */
    	RTSD    r15, 8
    	AND     r0, r0, r0
	.end rt_hw_context_switch_interrupt


    .globl     	_interrupt_handler
	.section .text
	.align 	2
	.ent _interrupt_handler
	.type _interrupt_handler, @function

_interrupt_handler:
	PUSH_ALL
    	MFS     r3,  RMSR
    	ORI     r3,  r3, IE_BIT
    	SWI     r3,  r1, STACK_RMSR         	/* push MSR    */

    	BRLID   r15, rt_interrupt_enter
    	AND     r0,  r0, r0

    	BRLID   r15, rt_hw_trap_irq
    	AND     r0,  r0, r0

    	BRLID   r15, rt_interrupt_leave
    	AND     r0,  r0, r0

	/*
	 * if rt_thread_switch_interrupt_flag set, jump to
	 * rt_hw_context_switch_interrupt_do and don't return
	 */
	LA	r3,  r0, rt_thread_switch_interrupt_flag
	LWI	r4,  r3, 0

	ANDI	r4,  r4, 1
	BNEI 	r4,  rt_hw_context_switch_interrupt_do

    	LWI     r3,  r1, STACK_RMSR
    	ANDNI   r3,  r3, IE_BIT
    	MTS     RMSR,r3
	POP_ALL
    	ADDIK   r1,  r1, STACK_SIZE

    	RTID    r14, 0
    	AND     r0,  r0, r0

/*
 * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
 */
rt_hw_context_switch_interrupt_do:
	SWI	r0,  r3, 0 						/* clear rt_thread_switch_interrupt_flag */

	LA	r3,  r0, rt_interrupt_from_thread
	LW	r4,  r0, r3
	SWI	r1,  r4, 0						/* store sp in preempted tasks's TCB */

	LA	r3,  r0, rt_interrupt_to_thread
	LW	r4,  r0, r3
	LWI	r1,  r4, 0						/* get new task's stack pointer */

    	LWI     r3,  r1, STACK_RMSR
    	ANDI    r3,  r3, IE_BIT
    	BNEI    r3,  return_with_ie     	/*if IE bit set,should be use RTID (return from interrupt). */

    	LWI     r3,  r1, STACK_RMSR
    	MTS     RMSR,r3
	POP_ALL
    	ADDIK   r1,  r1, STACK_SIZE
    	RTSD    r15, 8
    	AND     r0,  r0, r0

return_with_ie:

    	LWI     r3,  r1, STACK_RMSR
    	ANDNI   r3,  r3, IE_BIT         	/* clear IE bit, prevent interrupt occur immediately*/
    	MTS     RMSR,r3
    	LWI     r3,  r1, STACK_R03
	POP_ALL
    	ADDIK   r1,  r1, STACK_SIZE
    	RTID    r14, 0                    	/* IE bit will be set automatically */
    	AND     r0,  r0, r0

.end _interrupt_handler

