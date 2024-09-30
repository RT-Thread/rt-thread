/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei  the first version
 * 2024-03-28     Shell        Move vector handling codes from context_gcc.S
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include <rtconfig.h>

.text
.globl system_vectors
.globl vector_exception
.globl vector_irq
.globl vector_fiq

system_vectors:
.align 11
    .set    VBAR, system_vectors
    .org    VBAR

    /*  Exception from CurrentEL (EL1) with SP_EL0 (SPSEL=1) */
    .org (VBAR + 0x00 + 0)
    b vector_serror                     /* Synchronous */
    .org (VBAR + 0x80 + 0)
    b vector_serror                     /* IRQ/vIRQ */
    .org (VBAR + 0x100 + 0)
    b vector_serror                     /* FIQ/vFIQ */
    .org (VBAR + 0x180 + 0)
    b vector_serror                     /* Error/vError */

    /*  Exception from CurrentEL (EL1) with SP_ELn */
    .org (VBAR + 0x200 + 0)
    b vector_exception                  /* Synchronous */
    .org (VBAR + 0x280 + 0)
    b vector_irq                        /* IRQ/vIRQ */
    .org (VBAR + 0x300 + 0)
    b vector_fiq                        /* FIQ/vFIQ */
    .org (VBAR + 0x380 + 0)
    b vector_serror

    /* Exception from lower EL, aarch64 */
    .org (VBAR + 0x400 + 0)
    b vector_exception
    .org (VBAR + 0x480 + 0)
    b vector_irq
    .org (VBAR + 0x500 + 0)
    b vector_fiq
    .org (VBAR + 0x580 + 0)
    b vector_serror

    /* Exception from lower EL, aarch32 */
    .org (VBAR + 0x600 + 0)
    b vector_serror
    .org (VBAR + 0x680 + 0)
    b vector_serror
    .org (VBAR + 0x700 + 0)
    b vector_serror
    .org (VBAR + 0x780 + 0)
    b vector_serror

#include "include/vector_gcc.h"
#define EFRAMEX x19

START_POINT(vector_exception)
    SAVE_IRQ_CONTEXT
    mov     EFRAMEX, sp

    SAVE_USER_CTX EFRAMEX, x0

    mov     x0, EFRAMEX
    bl      rt_hw_trap_exception
    RESTORE_USER_CTX EFRAMEX, x0

    /* do exception switch for IRQ/exception handlers */
    EXCEPTION_SWITCH sp, x0

    RESTORE_IRQ_CONTEXT
    eret
START_POINT_END(vector_exception)

START_POINT(vector_serror)
    SAVE_IRQ_CONTEXT
    mov     EFRAMEX, sp

    SAVE_USER_CTX EFRAMEX, x0

    mov     x0, EFRAMEX
    bl      rt_hw_trap_serror

    RESTORE_USER_CTX EFRAMEX, x0

    NEVER_RETURN
START_POINT_END(vector_serror)

START_POINT(vector_irq)
    SAVE_IRQ_CONTEXT
    mov     EFRAMEX, sp

    /* trace IRQ level */
    bl      rt_interrupt_enter

    SAVE_USER_CTX EFRAMEX, x0

    /* handline IRQ */
    mov     x0, EFRAMEX
    bl      rt_hw_trap_irq

    RESTORE_USER_CTX EFRAMEX, x0

    /* restore IRQ level */
    bl      rt_interrupt_leave

    mov     x0, EFRAMEX
    bl      rt_hw_vector_irq_sched

    b       rt_hw_irq_exit
START_POINT_END(vector_irq)

rt_hw_irq_exit:
    .globl rt_hw_irq_exit

    /* do exception switch for IRQ/exception handlers */
    EXCEPTION_SWITCH sp, x0

    RESTORE_IRQ_CONTEXT
    eret
