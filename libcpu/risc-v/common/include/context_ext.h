/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-10     RT-Thread    the first version
 */

#ifndef __CONTEXT_EXT_H__
#define __CONTEXT_EXT_H__

#include <asm-generic.h>

#ifdef ARCH_RISCV_FPU
#ifndef __riscv_flen
#error "ARCH_RISCV_FPU requires a toolchain target with F or D extension"
#endif
/* Number of XLEN-sized stack slots occupied by 32 floating-point registers. */
#define CTX_FPU_REG_NR  (32 * __riscv_flen / __riscv_xlen)
#else
#define CTX_FPU_REG_NR  0
#endif

#ifdef __ASSEMBLY__

/**
 * ==================================
 * RISC-V D ISA (Floating)
 * ==================================
 */

#ifdef ARCH_RISCV_FPU
#define FPU_CTX_REG_OFF(n) ((__riscv_flen / 8) * (n))
#define FPU_CTX_F0_OFF     FPU_CTX_REG_OFF(0)
#define FPU_CTX_F1_OFF     FPU_CTX_REG_OFF(1)
#define FPU_CTX_F2_OFF     FPU_CTX_REG_OFF(2)
#define FPU_CTX_F3_OFF     FPU_CTX_REG_OFF(3)
#define FPU_CTX_F4_OFF     FPU_CTX_REG_OFF(4)
#define FPU_CTX_F5_OFF     FPU_CTX_REG_OFF(5)
#define FPU_CTX_F6_OFF     FPU_CTX_REG_OFF(6)
#define FPU_CTX_F7_OFF     FPU_CTX_REG_OFF(7)
#define FPU_CTX_F8_OFF     FPU_CTX_REG_OFF(8)
#define FPU_CTX_F9_OFF     FPU_CTX_REG_OFF(9)
#define FPU_CTX_F10_OFF    FPU_CTX_REG_OFF(10)
#define FPU_CTX_F11_OFF    FPU_CTX_REG_OFF(11)
#define FPU_CTX_F12_OFF    FPU_CTX_REG_OFF(12)
#define FPU_CTX_F13_OFF    FPU_CTX_REG_OFF(13)
#define FPU_CTX_F14_OFF    FPU_CTX_REG_OFF(14)
#define FPU_CTX_F15_OFF    FPU_CTX_REG_OFF(15)
#define FPU_CTX_F16_OFF    FPU_CTX_REG_OFF(16)
#define FPU_CTX_F17_OFF    FPU_CTX_REG_OFF(17)
#define FPU_CTX_F18_OFF    FPU_CTX_REG_OFF(18)
#define FPU_CTX_F19_OFF    FPU_CTX_REG_OFF(19)
#define FPU_CTX_F20_OFF    FPU_CTX_REG_OFF(20)
#define FPU_CTX_F21_OFF    FPU_CTX_REG_OFF(21)
#define FPU_CTX_F22_OFF    FPU_CTX_REG_OFF(22)
#define FPU_CTX_F23_OFF    FPU_CTX_REG_OFF(23)
#define FPU_CTX_F24_OFF    FPU_CTX_REG_OFF(24)
#define FPU_CTX_F25_OFF    FPU_CTX_REG_OFF(25)
#define FPU_CTX_F26_OFF    FPU_CTX_REG_OFF(26)
#define FPU_CTX_F27_OFF    FPU_CTX_REG_OFF(27)
#define FPU_CTX_F28_OFF    FPU_CTX_REG_OFF(28)
#define FPU_CTX_F29_OFF    FPU_CTX_REG_OFF(29)
#define FPU_CTX_F30_OFF    FPU_CTX_REG_OFF(30)
#define FPU_CTX_F31_OFF    FPU_CTX_REG_OFF(31)

#if __riscv_flen == 64
#define CTX_FREG_L fld
#define CTX_FREG_S fsd
#elif __riscv_flen == 32
#define CTX_FREG_L flw
#define CTX_FREG_S fsw
#else
#error "Unexpected __riscv_flen"
#endif
#endif /* ARCH_RISCV_FPU */

#endif /* __ASSEMBLY__ */

#ifdef ARCH_RISCV_VECTOR
#include "rvv_context.h"
#else /* !ARCH_RISCV_VECTOR */
#define CTX_VECTOR_REG_NR  0
#endif /* ARCH_RISCV_VECTOR */

#endif /* __CONTEXT_EXT_H__ */
