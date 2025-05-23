/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-02     lizhirui     first version
 * 2021-02-11     lizhirui     fixed gp save/store bug
 * 2021-11-18     JasonHu      add fpu registers save/restore
 * 2022-10-22     Shell        Support kernel mode RVV
 * 2025-04-20     GuEe-GUI     Merge 64I and 32I/E
 */

#ifndef __ASM_H__
#define __ASM_H__

#include <rtconfig.h>

#include <csr.h>
#include <stack.h>

#ifdef __GNUC__
.macro LOAD_GLOBAL_POINTER
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
.endm

.macro XRET
#ifdef ARCH_RISCV_M_MODE
    mret
#else
    sret
#endif
.endm

.macro PUSH reg
    addi    sp, sp, -SZREG
    REG_S   \reg, 0(sp)
.endm

.macro POP reg
    REG_L   \reg, 0(sp)
    addi    sp, sp, SZREG
.endm

.macro OPEN_INTERRUPT
    csrsi   CSR_STATUS, 2
.endm

.macro CLOSE_INTERRUPT
    csrci   CSR_STATUS, 2
.endm

.macro SAVE_ALL
#ifdef ARCH_RISCV_FPU
    /* Reserve float registers */
    addi    sp, sp, -CTX_FPU_REG_NR * SZREG
#endif
#ifdef ARCH_RISCV_VECTOR
    /* Reserve float registers */
    addi    sp, sp, -CTX_VECTOR_REG_NR * SZREG
#endif

    /* Save general registers */
    addi    sp, sp, -CTX_GENERAL_REG_NR * SZREG
    REG_S   x1,   1 * SZREG(sp)

    csrr    x1, CSR_STATUS
    REG_S   x1, FRAME_OFF_XSTATUS(sp)

    csrr    x1, CSR_CAUSE
    REG_S   x1, FRAME_OFF_XCAUSE(sp)

    csrr    x1, CSR_EPC
    REG_S   x1,   0 * SZREG(sp)

    REG_S   x3,   4 * SZREG(sp)
    REG_S   x4,   5 * SZREG(sp)
    REG_S   x5,   6 * SZREG(sp)
    REG_S   x6,   7 * SZREG(sp)
    REG_S   x7,   8 * SZREG(sp)
    REG_S   x8,   9 * SZREG(sp)
    REG_S   x9,  10 * SZREG(sp)
    REG_S   x10, 11 * SZREG(sp)
    REG_S   x11, 12 * SZREG(sp)
    REG_S   x12, 13 * SZREG(sp)
    REG_S   x13, 14 * SZREG(sp)
    REG_S   x14, 15 * SZREG(sp)
    REG_S   x15, 16 * SZREG(sp)
#ifndef ARCH_RISCV_32E
    REG_S   x16, 17 * SZREG(sp)
    REG_S   x17, 18 * SZREG(sp)
    REG_S   x18, 19 * SZREG(sp)
    REG_S   x19, 20 * SZREG(sp)
    REG_S   x20, 21 * SZREG(sp)
    REG_S   x21, 22 * SZREG(sp)
    REG_S   x22, 23 * SZREG(sp)
    REG_S   x23, 24 * SZREG(sp)
    REG_S   x24, 25 * SZREG(sp)
    REG_S   x25, 26 * SZREG(sp)
    REG_S   x26, 27 * SZREG(sp)
    REG_S   x27, 28 * SZREG(sp)
    REG_S   x28, 29 * SZREG(sp)
    REG_S   x29, 30 * SZREG(sp)
    REG_S   x30, 31 * SZREG(sp)
    REG_S   x31, 32 * SZREG(sp)
#endif /* !ARCH_RISCV_32E */
    csrr    t0, CSR_SCRATCH
    REG_S   t0, 33 * SZREG(sp)

#ifdef ARCH_RISCV_FPU
    /* Backup sp and adjust sp to save float registers */
    mv      t1, sp
    addi    t1, t1, CTX_GENERAL_REG_NR * SZREG

    li      t0, SR_FS
    csrs    CSR_STATUS, t0
    FREG_S  f0,  FPU_CTX_F0_OFF(t1)
    FREG_S  f1,  FPU_CTX_F1_OFF(t1)
    FREG_S  f2,  FPU_CTX_F2_OFF(t1)
    FREG_S  f3,  FPU_CTX_F3_OFF(t1)
    FREG_S  f4,  FPU_CTX_F4_OFF(t1)
    FREG_S  f5,  FPU_CTX_F5_OFF(t1)
    FREG_S  f6,  FPU_CTX_F6_OFF(t1)
    FREG_S  f7,  FPU_CTX_F7_OFF(t1)
    FREG_S  f8,  FPU_CTX_F8_OFF(t1)
    FREG_S  f9,  FPU_CTX_F9_OFF(t1)
    FREG_S  f10, FPU_CTX_F10_OFF(t1)
    FREG_S  f11, FPU_CTX_F11_OFF(t1)
    FREG_S  f12, FPU_CTX_F12_OFF(t1)
    FREG_S  f13, FPU_CTX_F13_OFF(t1)
    FREG_S  f14, FPU_CTX_F14_OFF(t1)
    FREG_S  f15, FPU_CTX_F15_OFF(t1)
    FREG_S  f16, FPU_CTX_F16_OFF(t1)
    FREG_S  f17, FPU_CTX_F17_OFF(t1)
    FREG_S  f18, FPU_CTX_F18_OFF(t1)
    FREG_S  f19, FPU_CTX_F19_OFF(t1)
    FREG_S  f20, FPU_CTX_F20_OFF(t1)
    FREG_S  f21, FPU_CTX_F21_OFF(t1)
    FREG_S  f22, FPU_CTX_F22_OFF(t1)
    FREG_S  f23, FPU_CTX_F23_OFF(t1)
    FREG_S  f24, FPU_CTX_F24_OFF(t1)
    FREG_S  f25, FPU_CTX_F25_OFF(t1)
    FREG_S  f26, FPU_CTX_F26_OFF(t1)
    FREG_S  f27, FPU_CTX_F27_OFF(t1)
    FREG_S  f28, FPU_CTX_F28_OFF(t1)
    FREG_S  f29, FPU_CTX_F29_OFF(t1)
    FREG_S  f30, FPU_CTX_F30_OFF(t1)
    FREG_S  f31, FPU_CTX_F31_OFF(t1)

    /* Clean FS domain */
    csrc    CSR_STATUS, t0

    /* Clean status would clr sr_sd; */
    li      t0, SR_FS_CLEAN
    csrs    CSR_STATUS, t0

#endif /* ARCH_RISCV_FPU */

#ifdef ARCH_RISCV_VECTOR
    csrr    t0, CSR_STATUS
    andi    t0, t0, SR_VS
    beqz    t0, 0f

    /* push vector frame */
    addi    t1, sp, (CTX_GENERAL_REG_NR + CTX_FPU_REG_NR) * SZREG

    SAVE_VECTOR t1
0:
#endif /* ARCH_RISCV_VECTOR */
.endm

.macro RESTORE_ALL
#ifdef ARCH_RISCV_VECTOR
    /* Skip on close */
    ld      t0, 2 * SZREG(sp)
    /* Cannot use vector on initial */
    andi    t0, t0, SR_VS_CLEAN
    beqz    t0, 0f

    /* Push vector frame */
    addi    t1, sp, (CTX_GENERAL_REG_NR + CTX_FPU_REG_NR) * SZREG

    RESTORE_VECTOR t1
0:
#endif /* ARCH_RISCV_VECTOR */

#ifdef ARCH_RISCV_FPU
    /* Restore float register  */
    addi    t2, sp, CTX_GENERAL_REG_NR * SZREG

    li      t0, SR_FS
    csrs    CSR_STATUS, t0
    FREG_L  f0,  FPU_CTX_F0_OFF(t2)
    FREG_L  f1,  FPU_CTX_F1_OFF(t2)
    FREG_L  f2,  FPU_CTX_F2_OFF(t2)
    FREG_L  f3,  FPU_CTX_F3_OFF(t2)
    FREG_L  f4,  FPU_CTX_F4_OFF(t2)
    FREG_L  f5,  FPU_CTX_F5_OFF(t2)
    FREG_L  f6,  FPU_CTX_F6_OFF(t2)
    FREG_L  f7,  FPU_CTX_F7_OFF(t2)
    FREG_L  f8,  FPU_CTX_F8_OFF(t2)
    FREG_L  f9,  FPU_CTX_F9_OFF(t2)
    FREG_L  f10, FPU_CTX_F10_OFF(t2)
    FREG_L  f11, FPU_CTX_F11_OFF(t2)
    FREG_L  f12, FPU_CTX_F12_OFF(t2)
    FREG_L  f13, FPU_CTX_F13_OFF(t2)
    FREG_L  f14, FPU_CTX_F14_OFF(t2)
    FREG_L  f15, FPU_CTX_F15_OFF(t2)
    FREG_L  f16, FPU_CTX_F16_OFF(t2)
    FREG_L  f17, FPU_CTX_F17_OFF(t2)
    FREG_L  f18, FPU_CTX_F18_OFF(t2)
    FREG_L  f19, FPU_CTX_F19_OFF(t2)
    FREG_L  f20, FPU_CTX_F20_OFF(t2)
    FREG_L  f21, FPU_CTX_F21_OFF(t2)
    FREG_L  f22, FPU_CTX_F22_OFF(t2)
    FREG_L  f23, FPU_CTX_F23_OFF(t2)
    FREG_L  f24, FPU_CTX_F24_OFF(t2)
    FREG_L  f25, FPU_CTX_F25_OFF(t2)
    FREG_L  f26, FPU_CTX_F26_OFF(t2)
    FREG_L  f27, FPU_CTX_F27_OFF(t2)
    FREG_L  f28, FPU_CTX_F28_OFF(t2)
    FREG_L  f29, FPU_CTX_F29_OFF(t2)
    FREG_L  f30, FPU_CTX_F30_OFF(t2)
    FREG_L  f31, FPU_CTX_F31_OFF(t2)

    /* Clean FS domain */
    csrc    CSR_STATUS, t0

    /* Clean status would clr sr_sd; */
    li      t0, SR_FS_CLEAN
    csrs    CSR_STATUS, t0

#endif /* ARCH_RISCV_FPU */

    /* Restore general register */
    addi    t0, sp, CTX_ALL_REG_NR * SZREG
    csrw    CSR_SCRATCH, t0

    /* resw ra to CSR_EPC */
    REG_L   x1,   0 * SZREG(sp)
    csrw    CSR_EPC, x1

    REG_L   x1,   2 * SZREG(sp)
    csrw    CSR_STATUS, x1

    REG_L   x1,   1 * SZREG(sp)

    REG_L   x3,   4 * SZREG(sp)
    REG_L   x4,   5 * SZREG(sp)
    REG_L   x5,   6 * SZREG(sp)
    REG_L   x6,   7 * SZREG(sp)
    REG_L   x7,   8 * SZREG(sp)
    REG_L   x8,   9 * SZREG(sp)
    REG_L   x9,  10 * SZREG(sp)
    REG_L   x10, 11 * SZREG(sp)
    REG_L   x11, 12 * SZREG(sp)
    REG_L   x12, 13 * SZREG(sp)
    REG_L   x13, 14 * SZREG(sp)
    REG_L   x14, 15 * SZREG(sp)
    REG_L   x15, 16 * SZREG(sp)
#ifndef ARCH_RISCV_32E
    REG_L   x16, 17 * SZREG(sp)
    REG_L   x17, 18 * SZREG(sp)
    REG_L   x18, 19 * SZREG(sp)
    REG_L   x19, 20 * SZREG(sp)
    REG_L   x20, 21 * SZREG(sp)
    REG_L   x21, 22 * SZREG(sp)
    REG_L   x22, 23 * SZREG(sp)
    REG_L   x23, 24 * SZREG(sp)
    REG_L   x24, 25 * SZREG(sp)
    REG_L   x25, 26 * SZREG(sp)
    REG_L   x26, 27 * SZREG(sp)
    REG_L   x27, 28 * SZREG(sp)
    REG_L   x28, 29 * SZREG(sp)
    REG_L   x29, 30 * SZREG(sp)
    REG_L   x30, 31 * SZREG(sp)
    REG_L   x31, 32 * SZREG(sp)
#endif /* !ARCH_RISCV_32E */

    /* Restore user sp */
    REG_L   sp, 33 * SZREG(sp)
.endm
#endif /* __GNUC__ */

#endif /* __ASM_H__ */
