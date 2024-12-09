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

/* restore address space */
.macro RESTORE_ADDRESS_SPACE
#ifdef RT_USING_SMART
    bl      rt_thread_self
    mov     x19, x0
    bl      lwp_aspace_switch
    mov     x0, x19
    bl      lwp_user_setting_restore
#endif
.endm

.macro RESTORE_CONTEXT_SWITCH using_sp
    /* Set the SP to point to the stack of the task being restored. */
    mov     sp, \using_sp

    RESTORE_ADDRESS_SPACE

    _RESTORE_CONTEXT_SWITCH
.endm

.macro RESTORE_IRQ_CONTEXT
#ifdef RT_USING_SMART
    BL      rt_thread_self
    MOV     X19, X0
    BL      lwp_aspace_switch
    MOV     X0, X19
    BL      lwp_user_setting_restore
#endif
    LDP     X2, X3, [SP], #0x10  /* SPSR and ELR. */

    TST     X3, #0x1f
    MSR     SPSR_EL1, X3
    MSR     ELR_EL1, X2

    LDP     X29, X30, [SP], #0x10
    MSR     SP_EL0, X29
    LDP     X28, X29, [SP], #0x10
    MSR     FPCR, X28
    MSR     FPSR, X29
    LDP     X28, X29, [SP], #0x10
    LDP     X26, X27, [SP], #0x10
    LDP     X24, X25, [SP], #0x10
    LDP     X22, X23, [SP], #0x10
    LDP     X20, X21, [SP], #0x10
    LDP     X18, X19, [SP], #0x10
    LDP     X16, X17, [SP], #0x10
    LDP     X14, X15, [SP], #0x10
    LDP     X12, X13, [SP], #0x10
    LDP     X10, X11, [SP], #0x10
    LDP     X8, X9, [SP], #0x10
    LDP     X6, X7, [SP], #0x10
    LDP     X4, X5, [SP], #0x10
    LDP     X2, X3, [SP], #0x10
    LDP     X0, X1, [SP], #0x10
    RESTORE_FPU SP
#ifdef RT_USING_SMART
    BEQ     arch_ret_to_user
#endif
    ERET
.endm

#endif /* __ARM64_CONTEXT_H__ */
