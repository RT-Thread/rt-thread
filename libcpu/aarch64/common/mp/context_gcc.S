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

.section .text

.globl rt_hw_context_switch_to

.macro update_tidr, srcx
#ifdef ARCH_USING_HW_THREAD_SELF
    msr     ARM64_THREAD_REG, \srcx
#endif /* ARCH_USING_HW_THREAD_SELF */
.endm

/*
 * void rt_hw_context_switch_to(rt_uint3 to, struct rt_thread *to_thread);
 * X0 --> to (thread stack)
 * X1 --> to_thread
 */
rt_hw_context_switch_to:
    ldr     x0, [x0]
    mov     sp, x0
    update_tidr x1

    /* reserved to_thread */
    mov     x19, x1

    mov     x0, x19
    bl      rt_cpus_lock_status_restore
#ifdef RT_USING_SMART
    mov     x0, x19
    bl      lwp_user_setting_restore
#endif
    b       _context_switch_exit

.globl rt_hw_context_switch

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32
to, struct rt_thread *to_thread);
 * X0 --> from (from_thread stack)
 * X1 --> to (to_thread stack)
 * X2 --> to_thread
 */
rt_hw_context_switch:
    SAVE_CONTEXT_SWITCH x19, x20
    mov     x3, sp
    str     x3, [x0]            // store sp in preempted tasks TCB
    ldr     x0, [x1]            // get new task stack pointer
    mov     sp, x0
    update_tidr x2

    /* backup thread self */
    mov     x19, x2

    mov     x0, x19
    bl      rt_cpus_lock_status_restore
#ifdef RT_USING_SMART
    mov     x0, x19
    bl      lwp_user_setting_restore
#endif
    b       _context_switch_exit

.globl rt_hw_irq_exit
.globl rt_hw_context_switch_interrupt

#define EXP_FRAME   x19
#define FROM_SPP    x20
#define TO_SPP      x21
#define TO_TCB      x22
/*
 * void rt_hw_context_switch_interrupt(context, from sp, to sp, tp tcb)
 * X0 :interrupt context
 * X1 :addr of from_thread's sp
 * X2 :addr of to_thread's sp
 * X3 :to_thread's tcb
 */
rt_hw_context_switch_interrupt:
#ifdef RT_USING_DEBUG
    /* debug frame for backtrace */
    stp     x29, x30, [sp, #-0x10]!
#endif /* RT_USING_DEBUG */

    /* we can discard all the previous ABI here */
    mov     EXP_FRAME, x0
    mov     FROM_SPP, x1
    mov     TO_SPP, x2
    mov     TO_TCB, x3

#ifdef RT_USING_SMART
    GET_THREAD_SELF x0
    bl      lwp_user_setting_save
#endif /* RT_USING_SMART */

    /* reset SP of from-thread */
    mov     sp, EXP_FRAME

    /* push context for swtich */
    adr     lr, rt_hw_irq_exit
    SAVE_CONTEXT_SWITCH_FAST

    /* save SP of from-thread */
    mov     x0, sp
    str     x0, [FROM_SPP]

    /* setup SP to to-thread's */
    ldr     x0, [TO_SPP]
    mov     sp, x0
    update_tidr TO_TCB

    mov     x0, TO_TCB
    bl      rt_cpus_lock_status_restore
#ifdef RT_USING_SMART
    mov     x0, TO_TCB
    bl      lwp_user_setting_restore
#endif /* RT_USING_SMART */
    b       _context_switch_exit

_context_switch_exit:
    .local _context_switch_exit

    clrex
    RESTORE_CONTEXT_SWITCH
