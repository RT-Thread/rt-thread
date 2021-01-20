/*
 * Copyright (c) 2020, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-16     Dystopia     the first version
 */

#define SPARC_PSR_PIL_MASK 0x00000F00
#define SPARC_PSR_ET_MASK 0x00000020

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
	mov %psr, %o0
	or %o0, SPARC_PSR_PIL_MASK, %o1
	mov %o1, %psr
	nop
	nop
	nop
	retl
	nop

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
	mov %o0, %psr
	nop
	nop
	nop
	retl
	nop

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * o0 --> from
 * o1 --> to
 */
.globl rt_hw_context_switch
rt_hw_context_switch:
	ta 2
	retl
	nop
	
/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * o0 --> to
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
	mov %o0, %o1
	ta 3
	retl
	nop
	
/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
 */
.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
.globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
	set rt_thread_switch_interrupt_flag, %o2
	ld [%o2], %o3
	cmp %o3, 1
	be _reswitch
	nop
	mov 1, %o3
	st %o3, [%o2]
	set rt_interrupt_from_thread, %o2
	st %o0, [%o2]
_reswitch:
	set rt_interrupt_to_thread, %o2
	st %o1, [%o2]
	retl
	nop
