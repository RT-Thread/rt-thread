/*
 * Copyright (c) 2021 - 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/01/16     HPMicro      The first version
 * 2020/04/27     HPMicro      Bugfix for interrupt management
 */

#include "cpuport.h"

    .section .isr_vector, "ax"
    .global irq_handler_trap
    .align 2
irq_handler_trap:
#ifdef ARCH_RISCV_FPU
    addi    sp, sp, -32 * FREGBYTES
    FSTORE  f0, 0 * FREGBYTES(sp)
    FSTORE  f1, 1 * FREGBYTES(sp)
    FSTORE  f2, 2 * FREGBYTES(sp)
    FSTORE  f3, 3 * FREGBYTES(sp)
    FSTORE  f4, 4 * FREGBYTES(sp)
    FSTORE  f5, 5 * FREGBYTES(sp)
    FSTORE  f6, 6 * FREGBYTES(sp)
    FSTORE  f7, 7 * FREGBYTES(sp)
    FSTORE  f8, 8 * FREGBYTES(sp)
    FSTORE  f9, 9 * FREGBYTES(sp)
    FSTORE  f10, 10 * FREGBYTES(sp)
    FSTORE  f11, 11 * FREGBYTES(sp)
    FSTORE  f12, 12 * FREGBYTES(sp)
    FSTORE  f13, 13 * FREGBYTES(sp)
    FSTORE  f14, 14 * FREGBYTES(sp)
    FSTORE  f15, 15 * FREGBYTES(sp)
    FSTORE  f16, 16 * FREGBYTES(sp)
    FSTORE  f17, 17 * FREGBYTES(sp)
    FSTORE  f18, 18 * FREGBYTES(sp)
    FSTORE  f19, 19 * FREGBYTES(sp)
    FSTORE  f20, 20 * FREGBYTES(sp)
    FSTORE  f21, 21 * FREGBYTES(sp)
    FSTORE  f22, 22 * FREGBYTES(sp)
    FSTORE  f23, 23 * FREGBYTES(sp)
    FSTORE  f24, 24 * FREGBYTES(sp)
    FSTORE  f25, 25 * FREGBYTES(sp)
    FSTORE  f26, 26 * FREGBYTES(sp)
    FSTORE  f27, 27 * FREGBYTES(sp)
    FSTORE  f28, 28 * FREGBYTES(sp)
    FSTORE  f29, 29 * FREGBYTES(sp)
    FSTORE  f30, 30 * FREGBYTES(sp)
    FSTORE  f31, 31 * FREGBYTES(sp)
#endif
    /* save all from thread context */
    addi sp, sp, -32 * REGBYTES

    STORE x1,   1 * REGBYTES(sp)   // ra
    li    t0,   0x80
    STORE t0,   2 * REGBYTES(sp)   // mstatus

    STORE x4,   4 * REGBYTES(sp)   // tp - thread pointer
    STORE x5,   5 * REGBYTES(sp)   // t0
    STORE x6,   6 * REGBYTES(sp)   // t1
    STORE x7,   7 * REGBYTES(sp)   // t2
    STORE x8,   8 * REGBYTES(sp)   // s0/fp
    STORE x9,   9 * REGBYTES(sp)   // s1
    STORE x10, 10 * REGBYTES(sp)   // a0
    STORE x11, 11 * REGBYTES(sp)   // a1
    STORE x12, 12 * REGBYTES(sp)   // a2
    STORE x13, 13 * REGBYTES(sp)   // a3
    STORE x14, 14 * REGBYTES(sp)   // a4
    STORE x15, 15 * REGBYTES(sp)   // a5
    STORE x16, 16 * REGBYTES(sp)   // a6
    STORE x17, 17 * REGBYTES(sp)   // a7
    STORE x18, 18 * REGBYTES(sp)   // s2
    STORE x19, 19 * REGBYTES(sp)   // s3
    STORE x20, 20 * REGBYTES(sp)   // s4
    STORE x21, 21 * REGBYTES(sp)   // s5
    STORE x22, 22 * REGBYTES(sp)   // s6
    STORE x23, 23 * REGBYTES(sp)   // s7
    STORE x24, 24 * REGBYTES(sp)   // s8
    STORE x25, 25 * REGBYTES(sp)   // s9
    STORE x26, 26 * REGBYTES(sp)   // s10
    STORE x27, 27 * REGBYTES(sp)   // s11
    STORE x28, 28 * REGBYTES(sp)   // t3
    STORE x29, 29 * REGBYTES(sp)   // t4
    STORE x30, 30 * REGBYTES(sp)   // t5
    STORE x31, 31 * REGBYTES(sp)   // t6

    /* Save the thread stack frame base to mscratch */
    csrw  mscratch, sp

    /* switch to interrupt stack */
    la sp, _stack

    /* interrupt handle */
    call  rt_interrupt_enter
    /* Get the thread stack frame base from mscratch */
    csrr  a0, mscratch
    call  trap_entry
    call  rt_interrupt_leave

    /* switch to thread stack */
    csrr  sp, mscratch

    /* need to switch new thread */
    la    s0, rt_thread_switch_interrupt_flag
    lw    s2, 0(s0)
    beqz  s2, spurious_interrupt
    /* clear switch interrupt flag */
    sw    zero, 0(s0)

    csrr  a0, mepc
    STORE a0, 0 * REGBYTES(sp)

    la    s0, rt_interrupt_from_thread
    LOAD  s1, 0(s0)
    STORE sp, 0(s1)

    la    s0, rt_interrupt_to_thread
    LOAD  s1, 0(s0)
    LOAD  sp, 0(s1)

    LOAD  a0,  0 * REGBYTES(sp)
    csrw  mepc, a0

spurious_interrupt:
    LOAD  x1,   1 * REGBYTES(sp)    // ra
    /* Remain in M-mode after mret */
    li    t0, 0x00001800
    csrs  mstatus, t0
    LOAD  t0,   2 * REGBYTES(sp)
    csrs  mstatus, t0               // mstatus.mpie

    LOAD  x4,   4 * REGBYTES(sp)    // tp
    LOAD  x5,   5 * REGBYTES(sp)    // t0
    LOAD  x6,   6 * REGBYTES(sp)    // t1
    LOAD  x7,   7 * REGBYTES(sp)    // t2
    LOAD  x8,   8 * REGBYTES(sp)    // s0/fp
    LOAD  x9,   9 * REGBYTES(sp)    // s1
    LOAD  x10, 10 * REGBYTES(sp)    // a0
    LOAD  x11, 11 * REGBYTES(sp)    // a1
    LOAD  x12, 12 * REGBYTES(sp)    // a2
    LOAD  x13, 13 * REGBYTES(sp)    // a3
    LOAD  x14, 14 * REGBYTES(sp)    // a4
    LOAD  x15, 15 * REGBYTES(sp)    // a5
    LOAD  x16, 16 * REGBYTES(sp)    // a6
    LOAD  x17, 17 * REGBYTES(sp)    // a7
    LOAD  x18, 18 * REGBYTES(sp)    // s2
    LOAD  x19, 19 * REGBYTES(sp)    // s3
    LOAD  x20, 20 * REGBYTES(sp)    // s4
    LOAD  x21, 21 * REGBYTES(sp)    // s5
    LOAD  x22, 22 * REGBYTES(sp)    // s6
    LOAD  x23, 23 * REGBYTES(sp)    // s7
    LOAD  x24, 24 * REGBYTES(sp)    // s8
    LOAD  x25, 25 * REGBYTES(sp)    // s9
    LOAD  x26, 26 * REGBYTES(sp)    // s10
    LOAD  x27, 27 * REGBYTES(sp)    // s11
    LOAD  x28, 28 * REGBYTES(sp)    // t3
    LOAD  x29, 29 * REGBYTES(sp)    // t4
    LOAD  x30, 30 * REGBYTES(sp)    // t5
    LOAD  x31, 31 * REGBYTES(sp)    // t6

    addi  sp, sp, 32 * REGBYTES

#ifdef ARCH_RISCV_FPU
    FLOAD   f0, 0 * FREGBYTES(sp)
    FLOAD   f1, 1 * FREGBYTES(sp)
    FLOAD   f2, 2 * FREGBYTES(sp)
    FLOAD   f3, 3 * FREGBYTES(sp)
    FLOAD   f4, 4 * FREGBYTES(sp)
    FLOAD   f5, 5 * FREGBYTES(sp)
    FLOAD   f6, 6 * FREGBYTES(sp)
    FLOAD   f7, 7 * FREGBYTES(sp)
    FLOAD   f8, 8 * FREGBYTES(sp)
    FLOAD   f9, 9 * FREGBYTES(sp)
    FLOAD   f10, 10 * FREGBYTES(sp)
    FLOAD   f11, 11 * FREGBYTES(sp)
    FLOAD   f12, 12 * FREGBYTES(sp)
    FLOAD   f13, 13 * FREGBYTES(sp)
    FLOAD   f14, 14 * FREGBYTES(sp)
    FLOAD   f15, 15 * FREGBYTES(sp)
    FLOAD   f16, 16 * FREGBYTES(sp)
    FLOAD   f17, 17 * FREGBYTES(sp)
    FLOAD   f18, 18 * FREGBYTES(sp)
    FLOAD   f19, 19 * FREGBYTES(sp)
    FLOAD   f20, 20 * FREGBYTES(sp)
    FLOAD   f21, 21 * FREGBYTES(sp)
    FLOAD   f22, 22 * FREGBYTES(sp)
    FLOAD   f23, 23 * FREGBYTES(sp)
    FLOAD   f24, 24 * FREGBYTES(sp)
    FLOAD   f25, 25 * FREGBYTES(sp)
    FLOAD   f26, 26 * FREGBYTES(sp)
    FLOAD   f27, 27 * FREGBYTES(sp)
    FLOAD   f28, 28 * FREGBYTES(sp)
    FLOAD   f29, 29 * FREGBYTES(sp)
    FLOAD   f30, 30 * FREGBYTES(sp)
    FLOAD   f31, 31 * FREGBYTES(sp)

    addi    sp, sp, 32 * FREGBYTES
#endif

    mret
