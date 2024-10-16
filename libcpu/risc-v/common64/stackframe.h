/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-02     lizhirui     first version
 * 2021-02-11     lizhirui     fixed gp save/store bug
 * 2021-11-18     JasonHu      add fpu registers save/restore
 * 2022-10-22     Shell        Support kernel mode RVV
 */

#ifndef __STACKFRAME_H__
#define __STACKFRAME_H__

#include <rtconfig.h>
#include "encoding.h"

/* bytes of register width */
#ifdef ARCH_CPU_64BIT
#define STORE                   sd
#define LOAD                    ld
#define FSTORE                  fsd
#define FLOAD                   fld
#define REGBYTES                8
#else
// error here, not portable
#error "Not supported XLEN"
#endif

#include "ext_context.h"

/* 33 general register + 1 padding */
#define CTX_GENERAL_REG_NR  34

/* all context registers */
#define CTX_REG_NR  (CTX_GENERAL_REG_NR + CTX_FPU_REG_NR + CTX_VECTOR_REG_NR)

#define BYTES(idx)          ((idx) * REGBYTES)
#define FRAME_OFF_SSTATUS   BYTES(2)
#define FRAME_OFF_SP        BYTES(32)
#define FRAME_OFF_GP        BYTES(3)

/* switch frame */
#define RT_HW_SWITCH_CONTEXT_SSTATUS    0
#define RT_HW_SWITCH_CONTEXT_S11        1
#define RT_HW_SWITCH_CONTEXT_S10        2
#define RT_HW_SWITCH_CONTEXT_S9         3
#define RT_HW_SWITCH_CONTEXT_S8         4
#define RT_HW_SWITCH_CONTEXT_S7         5
#define RT_HW_SWITCH_CONTEXT_S6         6
#define RT_HW_SWITCH_CONTEXT_S5         7
#define RT_HW_SWITCH_CONTEXT_S4         8
#define RT_HW_SWITCH_CONTEXT_S3         9
#define RT_HW_SWITCH_CONTEXT_S2         10
#define RT_HW_SWITCH_CONTEXT_S1         11
#define RT_HW_SWITCH_CONTEXT_S0         12
#define RT_HW_SWITCH_CONTEXT_RA         13
#define RT_HW_SWITCH_CONTEXT_TP         14
#define RT_HW_SWITCH_CONTEXT_ALIGNMENT  15  // Padding for alignment
#define RT_HW_SWITCH_CONTEXT_SIZE       16  // Total size of the structure

#ifdef __ASSEMBLY__

.macro SAVE_ALL

#ifdef ARCH_RISCV_FPU
    /* reserve float registers */
    addi sp, sp, -CTX_FPU_REG_NR * REGBYTES
#endif /* ARCH_RISCV_FPU */
#ifdef ARCH_RISCV_VECTOR
    /* reserve float registers */
    addi sp, sp, -CTX_VECTOR_REG_NR * REGBYTES
#endif /* ARCH_RISCV_VECTOR */

    /* save general registers */
    addi sp, sp, -CTX_GENERAL_REG_NR * REGBYTES
    STORE x1,   1 * REGBYTES(sp)

    csrr  x1, sstatus
    STORE x1, FRAME_OFF_SSTATUS(sp)

    csrr  x1, sepc
    STORE x1,   0 * REGBYTES(sp)

    STORE x3,   3 * REGBYTES(sp)
    STORE x4,   4 * REGBYTES(sp) /* save tp */
    STORE x5,   5 * REGBYTES(sp)
    STORE x6,   6 * REGBYTES(sp)
    STORE x7,   7 * REGBYTES(sp)
    STORE x8,   8 * REGBYTES(sp)
    STORE x9,   9 * REGBYTES(sp)
    STORE x10, 10 * REGBYTES(sp)
    STORE x11, 11 * REGBYTES(sp)
    STORE x12, 12 * REGBYTES(sp)
    STORE x13, 13 * REGBYTES(sp)
    STORE x14, 14 * REGBYTES(sp)
    STORE x15, 15 * REGBYTES(sp)
    STORE x16, 16 * REGBYTES(sp)
    STORE x17, 17 * REGBYTES(sp)
    STORE x18, 18 * REGBYTES(sp)
    STORE x19, 19 * REGBYTES(sp)
    STORE x20, 20 * REGBYTES(sp)
    STORE x21, 21 * REGBYTES(sp)
    STORE x22, 22 * REGBYTES(sp)
    STORE x23, 23 * REGBYTES(sp)
    STORE x24, 24 * REGBYTES(sp)
    STORE x25, 25 * REGBYTES(sp)
    STORE x26, 26 * REGBYTES(sp)
    STORE x27, 27 * REGBYTES(sp)
    STORE x28, 28 * REGBYTES(sp)
    STORE x29, 29 * REGBYTES(sp)
    STORE x30, 30 * REGBYTES(sp)
    STORE x31, 31 * REGBYTES(sp)
    csrr t0, sscratch
    STORE t0, 32 * REGBYTES(sp)

#ifdef ARCH_RISCV_FPU
    /* backup sp and adjust sp to save float registers */
    mv t1, sp
    addi t1, t1, CTX_GENERAL_REG_NR * REGBYTES

    li  t0, SSTATUS_FS
    csrs sstatus, t0
    FSTORE f0,  FPU_CTX_F0_OFF(t1)
    FSTORE f1,  FPU_CTX_F1_OFF(t1)
    FSTORE f2,  FPU_CTX_F2_OFF(t1)
    FSTORE f3,  FPU_CTX_F3_OFF(t1)
    FSTORE f4,  FPU_CTX_F4_OFF(t1)
    FSTORE f5,  FPU_CTX_F5_OFF(t1)
    FSTORE f6,  FPU_CTX_F6_OFF(t1)
    FSTORE f7,  FPU_CTX_F7_OFF(t1)
    FSTORE f8,  FPU_CTX_F8_OFF(t1)
    FSTORE f9,  FPU_CTX_F9_OFF(t1)
    FSTORE f10, FPU_CTX_F10_OFF(t1)
    FSTORE f11, FPU_CTX_F11_OFF(t1)
    FSTORE f12, FPU_CTX_F12_OFF(t1)
    FSTORE f13, FPU_CTX_F13_OFF(t1)
    FSTORE f14, FPU_CTX_F14_OFF(t1)
    FSTORE f15, FPU_CTX_F15_OFF(t1)
    FSTORE f16, FPU_CTX_F16_OFF(t1)
    FSTORE f17, FPU_CTX_F17_OFF(t1)
    FSTORE f18, FPU_CTX_F18_OFF(t1)
    FSTORE f19, FPU_CTX_F19_OFF(t1)
    FSTORE f20, FPU_CTX_F20_OFF(t1)
    FSTORE f21, FPU_CTX_F21_OFF(t1)
    FSTORE f22, FPU_CTX_F22_OFF(t1)
    FSTORE f23, FPU_CTX_F23_OFF(t1)
    FSTORE f24, FPU_CTX_F24_OFF(t1)
    FSTORE f25, FPU_CTX_F25_OFF(t1)
    FSTORE f26, FPU_CTX_F26_OFF(t1)
    FSTORE f27, FPU_CTX_F27_OFF(t1)
    FSTORE f28, FPU_CTX_F28_OFF(t1)
    FSTORE f29, FPU_CTX_F29_OFF(t1)
    FSTORE f30, FPU_CTX_F30_OFF(t1)
    FSTORE f31, FPU_CTX_F31_OFF(t1)

    /* clr FS domain */
    csrc sstatus, t0

    /* clean status would clr sr_sd; */
    li t0, SSTATUS_FS_CLEAN
    csrs sstatus, t0

#endif /* ARCH_RISCV_FPU */

#ifdef ARCH_RISCV_VECTOR
    csrr    t0, sstatus
    andi    t0, t0, SSTATUS_VS
    beqz    t0, 0f

    /* push vector frame */
    addi t1, sp, (CTX_GENERAL_REG_NR + CTX_FPU_REG_NR) * REGBYTES

    SAVE_VECTOR t1
0:
#endif /* ARCH_RISCV_VECTOR */
.endm

/**
 * @brief Restore All General Registers, for interrupt handling
 *
 */
.macro RESTORE_ALL

#ifdef ARCH_RISCV_VECTOR
    // skip on close
    ld      t0, 2 * REGBYTES(sp)
    // cannot use vector on initial
    andi    t0, t0, SSTATUS_VS_CLEAN
    beqz    t0, 0f

    /* push vector frame */
    addi t1, sp, (CTX_GENERAL_REG_NR + CTX_FPU_REG_NR) * REGBYTES

    RESTORE_VECTOR t1
0:
#endif /* ARCH_RISCV_VECTOR */

#ifdef ARCH_RISCV_FPU
    /* restore float register  */
    addi t2, sp, CTX_GENERAL_REG_NR * REGBYTES

    li  t0, SSTATUS_FS
    csrs sstatus, t0
    FLOAD f0,  FPU_CTX_F0_OFF(t2)
    FLOAD f1,  FPU_CTX_F1_OFF(t2)
    FLOAD f2,  FPU_CTX_F2_OFF(t2)
    FLOAD f3,  FPU_CTX_F3_OFF(t2)
    FLOAD f4,  FPU_CTX_F4_OFF(t2)
    FLOAD f5,  FPU_CTX_F5_OFF(t2)
    FLOAD f6,  FPU_CTX_F6_OFF(t2)
    FLOAD f7,  FPU_CTX_F7_OFF(t2)
    FLOAD f8,  FPU_CTX_F8_OFF(t2)
    FLOAD f9,  FPU_CTX_F9_OFF(t2)
    FLOAD f10, FPU_CTX_F10_OFF(t2)
    FLOAD f11, FPU_CTX_F11_OFF(t2)
    FLOAD f12, FPU_CTX_F12_OFF(t2)
    FLOAD f13, FPU_CTX_F13_OFF(t2)
    FLOAD f14, FPU_CTX_F14_OFF(t2)
    FLOAD f15, FPU_CTX_F15_OFF(t2)
    FLOAD f16, FPU_CTX_F16_OFF(t2)
    FLOAD f17, FPU_CTX_F17_OFF(t2)
    FLOAD f18, FPU_CTX_F18_OFF(t2)
    FLOAD f19, FPU_CTX_F19_OFF(t2)
    FLOAD f20, FPU_CTX_F20_OFF(t2)
    FLOAD f21, FPU_CTX_F21_OFF(t2)
    FLOAD f22, FPU_CTX_F22_OFF(t2)
    FLOAD f23, FPU_CTX_F23_OFF(t2)
    FLOAD f24, FPU_CTX_F24_OFF(t2)
    FLOAD f25, FPU_CTX_F25_OFF(t2)
    FLOAD f26, FPU_CTX_F26_OFF(t2)
    FLOAD f27, FPU_CTX_F27_OFF(t2)
    FLOAD f28, FPU_CTX_F28_OFF(t2)
    FLOAD f29, FPU_CTX_F29_OFF(t2)
    FLOAD f30, FPU_CTX_F30_OFF(t2)
    FLOAD f31, FPU_CTX_F31_OFF(t2)

    /* clr FS domain */
    csrc sstatus, t0

    /* clean status would clr sr_sd; */
    li t0, SSTATUS_FS_CLEAN
    csrs sstatus, t0

#endif /* ARCH_RISCV_FPU */

    /* restore general register */
    addi t0, sp, CTX_REG_NR * REGBYTES
    csrw sscratch, t0

    /* resw ra to sepc */
    LOAD x1, 0 * REGBYTES(sp)
    csrw sepc, x1

    LOAD x1,   2 * REGBYTES(sp)
    csrw sstatus, x1

    LOAD x1,   1 * REGBYTES(sp)

    LOAD x3,   3 * REGBYTES(sp)
    LOAD x4,   4 * REGBYTES(sp) /* restore tp */
    LOAD x5,   5 * REGBYTES(sp)
    LOAD x6,   6 * REGBYTES(sp)
    LOAD x7,   7 * REGBYTES(sp)
    LOAD x8,   8 * REGBYTES(sp)
    LOAD x9,   9 * REGBYTES(sp)
    LOAD x10, 10 * REGBYTES(sp)
    LOAD x11, 11 * REGBYTES(sp)
    LOAD x12, 12 * REGBYTES(sp)
    LOAD x13, 13 * REGBYTES(sp)
    LOAD x14, 14 * REGBYTES(sp)
    LOAD x15, 15 * REGBYTES(sp)
    LOAD x16, 16 * REGBYTES(sp)
    LOAD x17, 17 * REGBYTES(sp)
    LOAD x18, 18 * REGBYTES(sp)
    LOAD x19, 19 * REGBYTES(sp)
    LOAD x20, 20 * REGBYTES(sp)
    LOAD x21, 21 * REGBYTES(sp)
    LOAD x22, 22 * REGBYTES(sp)
    LOAD x23, 23 * REGBYTES(sp)
    LOAD x24, 24 * REGBYTES(sp)
    LOAD x25, 25 * REGBYTES(sp)
    LOAD x26, 26 * REGBYTES(sp)
    LOAD x27, 27 * REGBYTES(sp)
    LOAD x28, 28 * REGBYTES(sp)
    LOAD x29, 29 * REGBYTES(sp)
    LOAD x30, 30 * REGBYTES(sp)
    LOAD x31, 31 * REGBYTES(sp)

    /* restore user sp */
    LOAD sp, 32 * REGBYTES(sp)
.endm

.macro RESTORE_SYS_GP
    .option push
    .option norelax
        la gp, __global_pointer$
    .option pop
.endm

.macro OPEN_INTERRUPT
    csrsi sstatus, 2
.endm

.macro CLOSE_INTERRUPT
    csrci sstatus, 2
.endm

#endif /* __ASSEMBLY__ */

#endif /* __STACKFRAME_H__ */
