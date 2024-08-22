/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-28     Shell        Move vector handling codes from context_gcc.S
 */
#ifndef __ARM64_INC_CONTEXT_H__
#define __ARM64_INC_CONTEXT_H__

#include "armv8.h"

.macro SAVE_CONTEXT_SWITCH, tmpx, tmp2x
    /* Save the entire context. */
    SAVE_FPU sp

    stp     x19, x20, [sp, #-0x10]!
    stp     x21, x22, [sp, #-0x10]!
    stp     x23, x24, [sp, #-0x10]!
    stp     x25, x26, [sp, #-0x10]!
    stp     x27, x28, [sp, #-0x10]!

    mrs     \tmpx, sp_el0
    stp     x29, \tmpx, [sp, #-0x10]!

    mrs     \tmpx, fpcr
    mrs     \tmp2x, fpsr
    stp     \tmpx, \tmp2x, [sp, #-0x10]!

    mov     \tmpx, #((3 << 6) | 0x5)    /* el1h, disable interrupt */
    stp     x30, \tmpx, [sp, #-0x10]!

.endm

.macro SAVE_CONTEXT_SWITCH_FAST
    /* Save the entire context. */
    add     sp, sp, #-1 * CONTEXT_FPU_SIZE

    add     sp, sp, #-7 * 16

    mov     x19, #((3 << 6) | 0x4 | 0x1)  /* el1h, disable interrupt */
    stp     lr, x19, [sp, #-0x10]!

.endm

.macro _RESTORE_CONTEXT_SWITCH
    ldp     x30, x19, [sp], #0x10  /* SPSR and ELR. */
    msr     elr_el1, x30
    msr     spsr_el1, x19


    /* restore NEON */
    ldp     x19, x20, [sp], #0x10
    msr     fpcr, x19
    msr     fpsr, x20

    ldp     x29, x19, [sp], #0x10
    msr     sp_el0, x19
    ldp     x27, x28, [sp], #0x10
    ldp     x25, x26, [sp], #0x10
    ldp     x23, x24, [sp], #0x10
    ldp     x21, x22, [sp], #0x10
    ldp     x19, x20, [sp], #0x10

    RESTORE_FPU sp
    eret
.endm

#endif /* __ARM64_INC_CONTEXT_H__ */
