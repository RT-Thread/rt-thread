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

    .globl _reset
    .globl turnon_VFP
    .globl vector_svc
    .globl vector_pabort
    .globl vector_dabort
    .globl vector_resv
    .globl IRQ_Handler


.globl system_vectors
system_vectors:
        b   _reset
        b   turnon_VFP
        b   vector_svc
        b   vector_pabort
        b   vector_dabort
        b   vector_resv
        b   IRQ_Handler
        ldr pc,[pc,#-0x1b0]
