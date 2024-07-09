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

START_POINT(vector_exception)
    SAVE_IRQ_CONTEXT
    stp     x0, x1, [sp, #-0x10]!
#ifdef RT_USING_SMART
    SAVE_USER_CTX
#endif

    bl      rt_hw_trap_exception
#ifdef RT_USING_SMART
    ldp     x0, x1, [sp]
    RESTORE_USER_CTX x0
#endif

    ldp     x0, x1, [sp], #0x10
    RESTORE_IRQ_CONTEXT_WITHOUT_MMU_SWITCH
START_POINT_END(vector_exception)

START_POINT(vector_serror)
    SAVE_IRQ_CONTEXT

#ifdef RT_USING_SMART
    SAVE_USER_CTX
#endif

    stp     x0, x1, [sp, #-0x10]!
    bl      rt_hw_trap_serror
    b       .
START_POINT_END(vector_serror)
