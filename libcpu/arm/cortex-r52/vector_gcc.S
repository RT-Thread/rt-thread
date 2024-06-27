/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-05     Bernard      the first version
 */
 
#include "rtconfig.h"

.section .vectors, "ax"
.code 32

@-------------------------------------------------------------------------------
@ import reference for interrupt routines

    .globl Reset_Handler
    .globl turnon_VFP
    .globl SVC_Handler
    .globl Prefetch_Handler
    .globl Abort_Handler
    .globl Reserved_Handler
    .globl IRQ_Handler
    .globl FIQ_Handler


.globl system_vectors
system_vectors:
    b   Reset_Handler
    b   turnon_VFP
    b   SVC_Handler
    b   Prefetch_Handler
    b   Abort_Handler
    b   Reserved_Handler
    b   IRQ_Handler
    b   FIQ_Handler

