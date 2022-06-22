/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 * 2020-07-26     lizhirui     Fixed some problems
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "mips_regs.h"
#include "stackframe.h"

    .section ".text", "ax"
    .set noreorder

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to)
 * a0 --> from
 * a1 --> to
 */
    .globl rt_hw_context_switch
rt_hw_context_switch:
    MTC0    ra, CP0_EPC
    SAVE_ALL

    REG_S      sp, 0(a0)       /* store sp in preempted tasks TCB */
    REG_L      sp, 0(a1)       /* get new task stack pointer */

    RESTORE_ALL_AND_RET

/*
 * void rt_hw_context_switch_to(rt_uint32 to)/*
 * a0 --> to
 */
    .globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    REG_L      sp, 0(a0)       /* get new task stack pointer */
    RESTORE_ALL_AND_RET

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to)/*
 */
    .globl rt_thread_switch_interrupt_flag
    .globl rt_interrupt_from_thread
    .globl rt_interrupt_to_thread
    .globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    PTR_LA      t0, rt_thread_switch_interrupt_flag
    REG_L       t1, 0(t0)
    nop
    bnez    t1, _reswitch
    nop
    li      t1, 0x01                       /* set rt_thread_switch_interrupt_flag to 1 */
    LONG_S      t1, 0(t0)
    PTR_LA      t0, rt_interrupt_from_thread   /* set rt_interrupt_from_thread */
    LONG_S      a0, 0(t0)
_reswitch:
    PTR_LA      t0, rt_interrupt_to_thread     /* set rt_interrupt_to_thread */
    LONG_S      a1, 0(t0)
    jr      ra
    nop

/*
 * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
 */
    .globl rt_interrupt_enter
    .globl rt_interrupt_leave
    .globl rt_general_exc_dispatch
    .globl mips_irq_handle
mips_irq_handle:
    SAVE_ALL

    /* let k0 keep the current context sp */
    move    k0, sp
    /* switch to kernel stack */
    PTR_LA  sp, _system_stack

    jal     rt_interrupt_enter
    nop
    /* Get Old SP from k0 as paremeter in a0 */
    move    a0, k0
    jal     rt_general_exc_dispatch
    nop
    jal     rt_interrupt_leave
    nop

    /* switch sp back to thread context */
    move    sp, k0

    /*
    * if rt_thread_switch_interrupt_flag set, jump to
    * rt_hw_context_switch_interrupt_do and do not return
    */
    PTR_LA  k0, rt_thread_switch_interrupt_flag
    LONG_L  k1, 0(k0)
    beqz    k1, spurious_interrupt
    nop
    LONG_S  zero, 0(k0)                     /* clear flag */
    nop

    /*
    * switch to the new thread
    */
    PTR_LA  k0, rt_interrupt_from_thread
    LONG_L  k1, 0(k0)
    nop
    LONG_S  sp, 0(k1)                       /* store sp in preempted task TCB */

    PTR_LA  k0, rt_interrupt_to_thread
    LONG_L  k1, 0(k0)
    nop
    LONG_L  sp, 0(k1)                       /* get new task stack pointer */
    j       spurious_interrupt
    nop

spurious_interrupt:
    RESTORE_ALL_AND_RET
    .set reorder
