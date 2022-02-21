/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei  the first version
 * 2022-02-16     GuEe-GUI     replace vectors entry to macro
 */

.macro  ventry label
    .align 7
    b   \label
.endm

.globl system_vectors
.globl vector_error
.globl vector_irq
.globl vector_fiq
.align 11
system_vectors:
    /* Exception from CurrentEL (EL1t) with SP_EL0 (SPSEL = 0) */
    ventry  vector_error    /* Synchronous */
    ventry  vector_irq      /* IRQ/vIRQ */
    ventry  vector_fiq      /* FIQ/vFIQ */
    ventry  vector_error    /* SError/vSError */

    /* Exception from CurrentEL (EL1h) with SP_ELn */
    ventry  vector_error    /* Synchronous */
    ventry  vector_irq      /* IRQ/vIRQ */
    ventry  vector_fiq      /* FIQ/vFIQ */
    ventry  vector_error    /* SError/vSError */

    /* Exception from lower EL, aarch64 */
    ventry  vector_error    /* Synchronous */
    ventry  vector_error    /* IRQ/vIRQ */
    ventry  vector_error    /* FIQ/vFIQ */
    ventry  vector_error    /* SError/vSError */

    /* Exception from lower EL, aarch32 */
    ventry  vector_error    /* Synchronous */
    ventry  vector_error    /* IRQ/vIRQ */
    ventry  vector_error    /* FIQ/vFIQ */
    ventry  vector_error    /* SError/vSError */
