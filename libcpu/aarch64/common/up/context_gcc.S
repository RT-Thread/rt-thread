/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Jesven       the first version
 * 2023-06-24     Shell        Support backtrace for user thread
 * 2024-01-06     Shell        Fix barrier on irq_disable/enable
 * 2024-03-28     Shell        Move vector handling codes from context_gcc.S
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "context_gcc.h"
#include "../include/vector_gcc.h"

#include <rtconfig.h>
#include <asm-generic.h>
#include <asm-fpu.h>
#include <armv8.h>

/**
 * Context switch status
 */
.section .bss
rt_interrupt_from_thread:
    .quad 0
rt_interrupt_to_thread:
    .quad 0
rt_thread_switch_interrupt_flag:
    .quad 0

.section .text

/*
 * void rt_hw_context_switch_to(rt_ubase_t to);
 * X0 --> to sp
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    clrex
    ldr     x0, [x0]
    RESTORE_CONTEXT_SWITCH x0
    NEVER_RETURN

/*
 * void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to);
 * X0 --> from sp
 * X1 --> to sp
 * X2 --> to thread
 */
.globl rt_hw_context_switch
rt_hw_context_switch:
    clrex
    SAVE_CONTEXT_SWITCH x19, x20

    mov    x2, sp
    str    x2, [x0]            // store sp in preempted tasks TCB
    ldr    x0, [x1]            // get new task stack pointer

    RESTORE_CONTEXT_SWITCH x0
    NEVER_RETURN

.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
.globl rt_hw_context_switch_interrupt

/*
 * void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to, rt_thread_t from_thread, rt_thread_t to_thread);
 */
rt_hw_context_switch_interrupt:
    ldr     x6, =rt_thread_switch_interrupt_flag
    ldr     x7, [x6]
    cmp     x7, #1
    b.eq     _reswitch

    /* set rt_interrupt_from_thread */
    ldr     x4, =rt_interrupt_from_thread
    str     x0, [x4]

    /* set rt_thread_switch_interrupt_flag to 1 */
    mov     x7, #1
    str     x7, [x6]

    stp     x1, x30, [sp, #-0x10]!
#ifdef RT_USING_SMART
    mov     x0, x2
    bl      lwp_user_setting_save
#endif
    ldp     x1, x30, [sp], #0x10
_reswitch:
    ldr     x6, =rt_interrupt_to_thread     // set rt_interrupt_to_thread
    str     x1, [x6]
    ret

.globl rt_hw_context_switch_interrupt_do

/**
 * rt_hw_context_switch_interrupt_do(void)
 */
rt_hw_context_switch_interrupt_do:
    clrex
    SAVE_CONTEXT_SWITCH_FAST

    ldr     x3,  =rt_interrupt_from_thread
    ldr     x4,  [x3]
    mov     x0,  sp
    str     x0,  [x4]       // store sp in preempted tasks's tcb

    ldr     x3,  =rt_interrupt_to_thread
    ldr     x4,  [x3]
    ldr     x0,  [x4]       // get new task's stack pointer

    RESTORE_CONTEXT_SWITCH x0
    NEVER_RETURN
