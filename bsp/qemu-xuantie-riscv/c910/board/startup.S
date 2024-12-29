/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 */

//#include <csi_config.h>

#ifndef CONFIG_NR_CPUS
#define CONFIG_NR_CPUS 1
#endif

.globl  Reset_Handler


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
//    la      a0, __Vectors
//    li	    a1, 0x1
//    or	    a0, a0,a1
//    csrw    mtvec, a0

   	la t0, trap_entry
 	csrw mtvec, t0

    /* get cpu id */
    csrr a0, mhartid

#if defined(CONFIG_SMP) && CONFIG_SMP
    /* check if hart is within range */
    /* tp: hart id */
    li	t0, CONFIG_NR_CPUS
    bge	a0, t0, hart_out_of_bounds_loop
#endif

#ifdef CONFIG_KERNEL_NONE
    la   sp, g_top_mainstack
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

    la   a0, entry
    jalr a0

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
    tail secondary_cpu_c_start

hart_out_of_bounds_loop:
    /* Harts in this loop are out of bounds, increase CONFIG_NR_CPUS. */
    wfi
    j	hart_out_of_bounds_loop
#endif

    .size   Reset_Handler, . - Reset_Handler

__exit:
    j      __exit


.section .stack
    .align  4
    .global g_base_irqstack
    .global g_top_irqstack
g_base_irqstack:
    .space CONFIG_ARCH_INTERRUPTSTACK * CONFIG_NR_CPUS
g_top_irqstack:

#ifdef CONFIG_KERNEL_NONE
    .align  4
    .global g_base_mainstack
    .global g_top_mainstack
g_base_mainstack:
    .space CONFIG_ARCH_MAINSTACK
g_top_mainstack:
#endif

#if defined(CONFIG_SMP) && CONFIG_SMP
.data
.global secondary_boot_flag
.align 3
secondary_boot_flag:
    .dword 0
#endif
