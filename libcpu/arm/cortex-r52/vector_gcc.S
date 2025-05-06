/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
@-------------------------------------------------------------------------------
@ sys_intvecs.asm
@
@ (c) Texas Instruments 2009-2013, All rights reserved.
@

.section .vectors, "ax"
.code 32

@-------------------------------------------------------------------------------
@ import reference for interrupt routines

    .globl Reset_Handler
    .globl Undefined_Handler
    .globl SWI_Handler
    .globl SVC_Handler
    .globl Prefetch_Handler
    .globl Abort_Handler
    .globl Reserved_Handler
    .globl IRQ_Handler
    .globl FIQ_Handler


.globl system_vector
system_vector:
        b   Reset_Handler
        b   Undefined_Handler
        b   SWI_Handler
        b   SVC_Handler
        b   Prefetch_Handler
        b   Abort_Handler
        b   Reserved_Handler
        b   IRQ_Handler
        b   FIQ_Handler
