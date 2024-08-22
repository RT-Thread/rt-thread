/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-25     Shell        Trimming unecessary ops and
 *                             improve the performance of ctx switch
 */

#ifndef __ARM64_CONTEXT_H__
#define __ARM64_CONTEXT_H__

#include "../include/context_gcc.h"

#include <rtconfig.h>
#include <asm-generic.h>
#include <asm-fpu.h>
#include <armv8.h>

.macro RESTORE_CONTEXT_SWITCH
    _RESTORE_CONTEXT_SWITCH
.endm

.macro RESTORE_IRQ_CONTEXT
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

#endif /* __ARM64_CONTEXT_H__ */
