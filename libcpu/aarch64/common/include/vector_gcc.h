/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-28     Shell        Move vector handling codes from context_gcc.S
 */

#ifndef __ARM64_INC_VECTOR_H__
#define __ARM64_INC_VECTOR_H__

#include "asm-generic.h"

#include <rtconfig.h>
#include <asm-fpu.h>
#include <armv8.h>

.macro SAVE_IRQ_CONTEXT
    /* Save the entire context. */
    SAVE_FPU sp
    stp     x0, x1, [sp, #-0x10]!
    stp     x2, x3, [sp, #-0x10]!
    stp     x4, x5, [sp, #-0x10]!
    stp     x6, x7, [sp, #-0x10]!
    stp     x8, x9, [sp, #-0x10]!
    stp     x10, x11, [sp, #-0x10]!
    stp     x12, x13, [sp, #-0x10]!
    stp     x14, x15, [sp, #-0x10]!
    stp     x16, x17, [sp, #-0x10]!
    stp     x18, x19, [sp, #-0x10]!
    stp     x20, x21, [sp, #-0x10]!
    stp     x22, x23, [sp, #-0x10]!
    stp     x24, x25, [sp, #-0x10]!
    stp     x26, x27, [sp, #-0x10]!
    stp     x28, x29, [sp, #-0x10]!
    mrs     x28, fpcr
    mrs     x29, fpsr
    stp     x28, x29, [sp, #-0x10]!
    mrs     x29, sp_el0
    stp     x29, x30, [sp, #-0x10]!

    mrs     x3, spsr_el1
    mrs     x2, elr_el1

    stp     x2, x3, [sp, #-0x10]!

    mov     x0, sp   /* Move SP into X0 for saving. */
.endm

#ifdef RT_USING_SMP
#include "../mp/context_gcc.h"
#else
#include "../up/context_gcc.h"
#endif

.macro RESTORE_IRQ_CONTEXT_WITHOUT_MMU_SWITCH
    /* the SP is already ok */
    ldp     x2, x3, [sp], #0x10  /* SPSR and ELR. */

    tst     x3, #0x1f
    msr     spsr_el1, x3
    msr     elr_el1, x2

    ldp     x29, x30, [sp], #0x10
    msr     sp_el0, x29
    ldp     x28, x29, [sp], #0x10
    msr     fpcr, x28
    msr     fpsr, x29
    ldp     x28, x29, [sp], #0x10
    ldp     x26, x27, [sp], #0x10
    ldp     x24, x25, [sp], #0x10
    ldp     x22, x23, [sp], #0x10
    ldp     x20, x21, [sp], #0x10
    ldp     x18, x19, [sp], #0x10
    ldp     x16, x17, [sp], #0x10
    ldp     x14, x15, [sp], #0x10
    ldp     x12, x13, [sp], #0x10
    ldp     x10, x11, [sp], #0x10
    ldp     x8, x9, [sp], #0x10
    ldp     x6, x7, [sp], #0x10
    ldp     x4, x5, [sp], #0x10
    ldp     x2, x3, [sp], #0x10
    ldp     x0, x1, [sp], #0x10
    RESTORE_FPU sp
#ifdef RT_USING_SMART
    beq     arch_ret_to_user
#endif
    eret
.endm

.macro SAVE_USER_CTX
    mrs     x1, spsr_el1
    and     x1, x1, 0xf
    cmp     x1, xzr

    bne     1f
    bl      lwp_uthread_ctx_save
    ldp     x0, x1, [sp]
1:
.endm

.macro RESTORE_USER_CTX, ctx
    ldr     x1, [\ctx, #CONTEXT_OFFSET_SPSR_EL1]
    and     x1, x1, 0x1f
    cmp     x1, xzr

    bne     1f
    bl      lwp_uthread_ctx_restore
1:
.endm

#endif /* __ARM64_INC_VECTOR_H__ */
