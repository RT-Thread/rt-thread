/*
 * File      : mips_context_asm.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
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
 * 2016Äê9ÔÂ7ÈÕ     Urey         the first version
 */

#ifndef __ASSEMBLY__
#	define __ASSEMBLY__
#endif

#include "../common/mips.h"

	.global	rt_thread_switch_interrupt_flag
    .global	rt_interrupt_from_thread
    .global	rt_interrupt_to_thread

    .section .text,"ax",@progbits
    .set noreorder
    .set noat

    .globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    mfc0 	v0,CP0_STATUS
    srl 	v1,v0,1
    sll 	v1,v1,1
#	and 	v1,v0,0xfffffffe
    mtc0 	v1,CP0_STATUS
    jr 		ra
    nop

LEAF(rt_hw_interrupt_enable)
    mtc0 	a0,CP0_STATUS
    jr 		ra
    nop
END(rt_hw_interrupt_enable)

/*
 * void rt_hw_context_switch_to(rt_uint32 to)/*
 * a0 --> to
 */
LEAF(rt_hw_context_switch_to)
	lw 	sp ,	0(a0)                 	/* switch to the new stack */
    RESTORE_CONTEXT
END(rt_hw_context_switch_to)

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to)
 * a0 --> from
 * a1 --> to
 */
LEAF(rt_hw_context_switch)
	mtc0    ra, CP0_EPC
    SAVE_CONTEXT

    sw      sp, 0(a0)       /* store sp in preempted tasks TCB */
    lw      sp, 0(a1)       /* get new task stack pointer */

	RESTORE_CONTEXT
END(rt_hw_context_switch)

LEAF(rt_hw_context_switch_interrupt)
    la      t0, rt_thread_switch_interrupt_flag
    lw      t1, 0(t0)
    nop
    bnez    t1, _reswitch
    nop
    li      t1, 0x01                       /* set rt_thread_switch_interrupt_flag to 1 */
    sw      t1, 0(t0)
    la      t0, rt_interrupt_from_thread   /* set rt_interrupt_from_thread */
    sw      a0, 0(t0)
_reswitch:
    la      t0, rt_interrupt_to_thread     /* set rt_interrupt_to_thread */
    sw      a1, 0(t0)
    jr      ra
    nop
END(rt_hw_context_switch_interrupt)

