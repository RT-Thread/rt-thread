 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <csi_config.h>

.globl  Reset_Handler
.global __rt_rvstack
.equ    Mcoret_Handler, SW_handler
.equ    Mirq_Handler, SW_handler 
.section .vectors
    .align  6
    .globl  __Vectors
    .type   __Vectors, @object
__Vectors:
    j   Default_Handler				/* 0 */
    j   Stspend_Handler			/* 1 */
    j   Default_Handler				/* 2 */
    j   Mtspend_Handler			/* 3 */
    j   Default_Handler				/* 4 */
    j   Scoret_Handler			/* 5 */
    j   Default_Handler				/* 6 */
    j   Mcoret_Handler			/* 7 */
    j   Default_Handler				/* 8 */
    j   Sirq_Handler			/* 9 */
    j   Default_Handler				/* 10 */
    j   Mirq_Handler			/* 11 */
    j   Default_Handler
    j   Default_Handler
    j   Default_Handler
    j   Default_Handler

 .text
    .align  2
    j        Reset_Handler
    .align   2
    .long    0x594B5343 /* CSKY ASCII */
    .long    0x594B5343 /* CSKY ASCII */
    .align   2
    .rept    9
    .long    0
    .endr
    .long    Reset_Handler
_start:
    .type   Reset_Handler, %function
Reset_Handler:
.option push
.option norelax
    /* disable ie and clear all interrupts */
    csrw    mie, zero
    csrw    mip, zero

    /* Disable MIE to avoid triggering interrupts before the first task starts. */
    /* This bit is set when a task recovers context. */
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    csrc    mstatus, (1 << 1)
#else
    csrc    mstatus, (1 << 3)
#endif

    la      gp, __global_pointer$
.option pop
    la      a0, __Vectors
    li	    a1, 0x1
    or	    a0, a0,a1
    csrw    mtvec, a0

#ifdef CONFIG_KERNEL_NONE
    la      sp, g_top_mainstack
#else
    la      sp, g_top_irqstack
#endif

#ifndef __NO_SYSTEM_INIT
    la   a0, SystemInit
    jalr a0
#endif

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    la   a0, smode_init
    jalr a0
#endif

#ifdef CONFIG_KERNEL_NONE
    /* Enable interrupt */
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    csrs    sstatus, (1 << 1)
#else
    csrs    mstatus, (1 << 3)
#endif
#endif

    la   a0, rtthread_startup
    jalr a0

    .size   Reset_Handler, . - Reset_Handler

__exit:
    j      __exit


.section .stack
    .align  4
    .global g_base_irqstack
    .global g_top_irqstack
g_base_irqstack:
    .space CONFIG_ARCH_INTERRUPTSTACK
g_top_irqstack:
__rt_rvstack:
#ifdef CONFIG_KERNEL_NONE
    .align  4
    .global g_base_mainstack
    .global g_top_mainstack
g_base_mainstack:
    .space CONFIG_ARCH_MAINSTACK
g_top_mainstack:
#endif
