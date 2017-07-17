;/*
; * File      : context_iar.S
; * This file is part of RT-Thread RTOS
; * COPYRIGHT (C) 2006, RT-Thread Development Team
; *
; *  This program is free software; you can redistribute it and/or modify
; *  it under the terms of the GNU General Public License as published by
; *  the Free Software Foundation; either version 2 of the License, or
; *  (at your option) any later version.
; *
; *  This program is distributed in the hope that it will be useful,
; *  but WITHOUT ANY WARRANTY; without even the implied warranty of
; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; *  GNU General Public License for more details.
; *
; *  You should have received a copy of the GNU General Public License along
; *  with this program; if not, write to the Free Software Foundation, Inc.,
; *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
; *
; * Change Logs:
; * Date           Author       Notes
; * 2017-07-16     zhangjun    for hifive1
; */


/*
 * rt_base_t rt_hw_interrupt_disable();
 */
    .globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
	ret

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
    .globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
	ret

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * a0 --> from
 * a1 --> to
 */
    .globl rt_hw_context_switch
rt_hw_context_switch:
	addi sp, sp, -120
	sw sp, (a0)
	sw gp, (sp)
	sw tp, 4(sp)
	sw t6, 8(sp)
	sw t5, 12(sp)
	sw t4, 16(sp)
	sw t3, 20(sp)
	sw t2, 24(sp)
	sw t1, 28(sp)
	sw t0, 32(sp)
	sw s11,36(sp)
	sw s10,40(sp)
	sw s9, 44(sp)
	sw s8, 48(sp)
	sw s7, 52(sp)
	sw s6, 56(sp)
	sw s5, 60(sp)
	sw s4, 64(sp)
	sw s3, 68(sp)
	sw s2, 72(sp)
	sw s1, 76(sp)
	sw s0, 80(sp)
	sw a7, 84(sp)
	sw a6, 88(sp)
	sw a5, 92(sp)
	sw a4, 96(sp)
	sw a3, 100(sp)
	sw a2, 104(sp)
	sw a1, 108(sp)
	sw ra, 120(sp)
	sw a0, 112(sp)

	lw sp, (a1)
	lw gp, (sp)
	lw tp, 4(sp)
	lw t6, 8(sp)
	lw t5, 12(sp)
	lw t4, 16(sp)
	lw t3, 20(sp)
	lw t2, 24(sp)
	lw t1, 28(sp)
	lw t0, 32(sp)
	lw s11,36(sp)
	lw s10,40(sp)
	lw s9, 44(sp)
	lw s8, 48(sp)
	lw s7, 52(sp)
	lw s6, 56(sp)
	lw s5, 60(sp)
	lw s4, 64(sp)
	lw s3, 68(sp)
	lw s2, 72(sp)
	lw s1, 76(sp)
	lw s0, 80(sp)
	lw a7, 84(sp)
	lw a6, 88(sp)
	lw a5, 92(sp)
	lw a4, 96(sp)
	lw a3, 100(sp)
	lw a2, 104(sp)
	lw a1, 108(sp)
	lw a0, 112(sp)
	lw ra, 120(sp)
	addi sp, sp, 120
	ret

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * a0 --> to
 */
    .globl rt_hw_context_switch_to
rt_hw_context_switch_to:
	lw sp, (a0)
	lw gp, (sp)
	lw tp, 4(sp)
	lw t6, 8(sp)
	lw t5, 12(sp)
	lw t4, 16(sp)
	lw t3, 20(sp)
	lw t2, 24(sp)
	lw t1, 28(sp)
	lw t0, 32(sp)
	lw s11,36(sp)
	lw s10,40(sp)
	lw s9, 44(sp)
	lw s8, 48(sp)
	lw s7, 52(sp)
	lw s6, 56(sp)
	lw s5, 60(sp)
	lw s4, 64(sp)
	lw s3, 68(sp)
	lw s2, 72(sp)
	lw s1, 76(sp)
	lw s0, 80(sp)
	lw a7, 84(sp)
	lw a6, 88(sp)
	lw a5, 92(sp)
	lw a4, 96(sp)
	lw a3, 100(sp)
	lw a2, 104(sp)
	lw a1, 108(sp)
	lw a0, 112(sp)
	lw ra, 120(sp)
	addi sp, sp, 120
	ret

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
 */
    .globl rt_thread_switch_interrupt_flag
    .globl rt_interrupt_from_thread
    .globl rt_interrupt_to_thread
    .globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
_reswitch:
	ret
