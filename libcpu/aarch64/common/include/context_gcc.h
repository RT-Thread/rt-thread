/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-28     Shell		   Move vector handling codes from context_gcc.S
 */
#ifndef __ARM64_INC_CONTEXT_H__
#define __ARM64_INC_CONTEXT_H__

.macro SAVE_CONTEXT_SWITCH
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

    mov     x19, #((3 << 6) | 0x4 | 0x1)  /* el1h, disable interrupt */
    mov     x18, x30

    stp     x18, x19, [sp, #-0x10]!
.endm

.macro _RESTORE_CONTEXT_SWITCH
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

#endif /* __ARM64_INC_CONTEXT_H__ */
