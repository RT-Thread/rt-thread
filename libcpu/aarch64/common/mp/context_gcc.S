/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Jesven       the first version
 * 2023-06-24     Shell        Support backtrace for user thread
 * 2024-01-06     Shell        Fix barrier on irq_disable/enable
 * 2024-03-28     Shell		   Move vector handling codes from context_gcc.S
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "context_gcc.h"

#include <rtconfig.h>
#include <asm-generic.h>
#include <asm-fpu.h>
#include <armv8.h>

.section .text

.globl rt_hw_context_switch_to

/*
 * void rt_hw_context_switch_to(rt_uint3 to, struct rt_thread *to_thread);
 * X0 --> to (thread stack)
 * X1 --> to_thread
 */
rt_hw_context_switch_to:
    ldr     x0, [x0]
    mov     sp, x0
    mov     x0, x1
    bl      rt_cpus_lock_status_restore
#ifdef RT_USING_SMART
    bl      rt_thread_self
    bl      lwp_user_setting_restore
#endif
    b       rt_hw_context_switch_exit

.globl rt_hw_context_switch

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32
to, struct rt_thread *to_thread);
 * X0 --> from (from_thread stack)
 * X1 --> to (to_thread stack)
 * X2 --> to_thread
 */
rt_hw_context_switch:
    SAVE_CONTEXT_SWITCH
    mov     x3, sp
    str     x3, [x0]            // store sp in preempted tasks TCB
    ldr     x0, [x1]            // get new task stack pointer
    mov     sp, x0

    /* backup thread self */
    mov     x19, x2

    mov     x0, x19
    bl      rt_cpus_lock_status_restore
#ifdef RT_USING_SMART
    mov     x0, x19
    bl      lwp_user_setting_restore
#endif
    b       rt_hw_context_switch_exit

.globl rt_hw_context_switch_interrupt

/*
 * void rt_hw_context_switch_interrupt(context, from sp, to sp, tp tcb)
 * X0 :interrupt context
 * X1 :addr of from_thread's sp
 * X2 :addr of to_thread's sp
 * X3 :to_thread's tcb
 */
rt_hw_context_switch_interrupt:
    stp     x0, x1, [sp, #-0x10]!
    stp     x2, x3, [sp, #-0x10]!
    stp     x29, x30, [sp, #-0x10]!
#ifdef RT_USING_SMART
    bl      rt_thread_self
    bl      lwp_user_setting_save
#endif
    ldp     x29, x30, [sp], #0x10
    ldp     x2, x3, [sp], #0x10
    ldp     x0, x1, [sp], #0x10
    str     x0, [x1]
    ldr     x0, [x2]
    mov     sp, x0
    mov     x0, x3
    mov     x19, x0
    bl      rt_cpus_lock_status_restore
    mov     x0, x19
#ifdef RT_USING_SMART
    bl      lwp_user_setting_restore
#endif
    b       rt_hw_context_switch_exit

.global rt_hw_context_switch_exit
rt_hw_context_switch_exit:
    clrex
    mov     x0, sp
    RESTORE_CONTEXT_SWITCH
