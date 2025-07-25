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

#ifndef CONFIG_NR_CPUS
#define CONFIG_NR_CPUS 1
#endif
.global __rt_rvstack 
.globl  Reset_Handler

.section .vectors
    .align  6
    .globl  __Vectors
    .type   __Vectors, @object
__Vectors:
#if CONFIG_INTC_CLIC_PLIC
    .dword   Default_Handler
    .dword   Default_Handler
    .dword   Default_Handler
    .dword   tspend_handler              /* 3 */
    .dword   Default_Handler
    .dword   Default_Handler
    .dword   Default_Handler
    .dword   Mcoret_Handler              /* 7 */
    .dword   Default_Handler
    .dword   Default_Handler
    .dword   Default_Handler
    .dword   Default_IRQHandler          /* 11 */
    .dword   Default_Handler
    .dword   Default_Handler
    .dword   Default_Handler
    .dword   Default_Handler

    /* External interrupts */
#if CONFIG_ECC_L1_ENABLE || CONFIG_ECC_ITCM_ENABLE || CONFIG_ECC_DTCM_ENABLE
    .dword   ECC_L1_Handler			    /* 16 */
#else
    .dword   Default_IRQHandler			/* 16 */
#endif
#if CONFIG_IRQ_LATENCY
    .dword   IRQ_LATENCY_IRQHandler
#else
    .dword   Default_IRQHandler
#endif
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
    .dword   Default_IRQHandler
#else
    j   Default_Handler			/* 0 */
    j   Stspend_Handler			/* 1 */
    j   Default_Handler			/* 2 */
    j   Mtspend_Handler			/* 3 */
    j   Default_Handler			/* 4 */
    j   Scoret_Handler			/* 5 */
    j   Default_Handler			/* 6 */
    j   Mcoret_Handler			/* 7 */
    j   Default_Handler			/* 8 */
    j   Sirq_Handler			/* 9 */
    j   Default_Handler			/* 10 */
    j   Mirq_Handler			/* 11 */
    j   Default_Handler			/* 12 */
    j   Default_Handler			/* 13 */
    j   Default_Handler			/* 14 */
    j   Default_Handler			/* 15 */
#if CONFIG_ECC_L1_ENABLE || CONFIG_ECC_ITCM_ENABLE || CONFIG_ECC_DTCM_ENABLE
    j   ECC_L1_Handler			/* 16 */
#else
    j   Default_Handler			/* 16 */
#endif
#endif

    .size   __Vectors, . - __Vectors

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
#if CONFIG_INTC_CLIC_PLIC
    la      a0, Default_Handler
    ori     a0, a0, 3
    csrw    mtvec, a0

    la      a0, __Vectors
    csrw    mtvt, a0
#else
    la      a0, __Vectors
    li	    a1, 0x1
    or	    a0, a0,a1
    csrw    mtvec, a0
#endif

    /* get cpu id */
    csrr a0, mhartid

#if defined(CONFIG_SMP) && CONFIG_SMP
    /* check if hart is within range */
    /* tp: hart id */
    li	t0, CONFIG_NR_CPUS
    bge	a0, t0, hart_out_of_bounds_loop
#endif

#ifdef CONFIG_KERNEL_NONE
    la   sp, g_base_mainstack
    addi t1, a0, 1
    li   t2, CONFIG_ARCH_MAINSTACK
    mul  t1, t1, t2
    add  sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_MAINSTACK + g_base_mainstack */
#else
    la   sp, g_base_irqstack
    addi t1, a0, 1
    li   t2, CONFIG_ARCH_INTERRUPTSTACK
    mul  t1, t1, t2
    add  sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */
#endif

    /* other cpu core, jump to cpu entry directly */
    bnez a0, secondary_cpu_entry

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

    .type   secondary_cpu_entry, %function
secondary_cpu_entry:
#if defined(CONFIG_SMP) && CONFIG_SMP
    la a0, secondary_boot_flag
    ld a0, 0(a0)
    li a1, 0xa55a
    beq a0, a1, 1f
#endif
    j secondary_cpu_entry

#if defined(CONFIG_SMP) && CONFIG_SMP
1:
    jal secondary_cpu_c_start

.size   secondary_cpu_entry, . - secondary_cpu_entry

hart_out_of_bounds_loop:
    /* Harts in this loop are out of bounds, increase CONFIG_NR_CPUS. */
    wfi
    j	hart_out_of_bounds_loop
#endif

.section .stack
    .align  4
    .global g_base_irqstack
    .global g_top_irqstack
g_base_irqstack:
    .space CONFIG_ARCH_INTERRUPTSTACK * CONFIG_NR_CPUS
g_top_irqstack:
__rt_rvstack:

#ifdef CONFIG_KERNEL_NONE
    .align  4
    .global g_base_mainstack
    .global g_top_mainstack
g_base_mainstack:
    .space CONFIG_ARCH_MAINSTACK * CONFIG_NR_CPUS
g_top_mainstack:
#endif

#if defined(CONFIG_SMP) && CONFIG_SMP
.data
.global secondary_boot_flag
.align 3
secondary_boot_flag:
    .dword 0
#endif
