/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-10     RT-Thread    the first version,
 *                             compatible to riscv-v-spec-1.0
 */
#ifndef __RVV_CONTEXT_1_0_H__
#define __RVV_CONTEXT_1_0_H__

#include <csr.h>

#ifdef __ASSEMBLY__
#include "vector_encoding.h"
#endif

#if defined(ARCH_VECTOR_VLEN_128)
    #define CTX_VECTOR_VLEN 128
#elif defined(ARCH_VECTOR_VLEN_256)
    #define CTX_VECTOR_VLEN 256
#elif defined(ARCH_VECTOR_VLEN_512)
    #define CTX_VECTOR_VLEN 512
#elif defined(ARCH_VECTOR_VLEN_1024)
    #define CTX_VECTOR_VLEN 1024
#elif defined(ARCH_VECTOR_VLEN_2048)
    #define CTX_VECTOR_VLEN 2048
#elif defined(ARCH_VECTOR_VLEN_4096)
    #define CTX_VECTOR_VLEN 4096
#else
#error "No RISC-V vector length configured"
#endif /* VLEN */

/* Number of XLEN-sized stack slots occupied by vector CSRs and registers. */
#define CTX_VECTOR_REG_NR  ((CTX_VECTOR_VLEN * 32 / __riscv_xlen) + 4)

#ifdef __ASSEMBLY__

/**
 * ==================================
 * VECTOR EXTENSION
 * ==================================
 */

#define VEC_FRAME_VSTART    (0 * SZREG)
#define VEC_FRAME_VTYPE     (1 * SZREG)
#define VEC_FRAME_VL        (2 * SZREG)
#define VEC_FRAME_VCSR      (3 * SZREG)
#define VEC_FRAME_V0        (4 * SZREG)

.macro GET_VEC_FRAME_LEN, xreg
    csrr    \xreg, CSR_VLENB
    slli    \xreg, \xreg, 5
    addi    \xreg, \xreg, 4 * SZREG
.endm

/**
 * @brief save vector extension hardware state
 *
 * @param dst register storing bottom of storage block
 *
 */
.macro SAVE_VECTOR, dst
    mv      t1, \dst

    csrr    t0, CSR_VSTART
    REG_S   t0, VEC_FRAME_VSTART(t1)
    csrr    t0, CSR_VTYPE
    REG_S   t0, VEC_FRAME_VTYPE(t1)
    csrr    t0, CSR_VL
    REG_S   t0, VEC_FRAME_VL(t1)
    csrr    t0, CSR_VCSR
    REG_S   t0, VEC_FRAME_VCSR(t1)

    addi    t1, t1, VEC_FRAME_V0

    /*
     * config vector setting,
     * t2 is updated to length of a vector group in bytes
     */
    VEC_INSN_VSETVLI_T2_X0_E8_M8

    VEC_INSN_VSE8_V0_T1
    add     t1, t1, t2
    VEC_INSN_VSE8_V8_T1
    add     t1, t1, t2
    VEC_INSN_VSE8_V16_T1
    add     t1, t1, t2
    VEC_INSN_VSE8_V24_T1
.endm

/**
 * @brief restore vector extension hardware states
 *
 * @param dst register storing bottom of storage block
 *
 */
.macro RESTORE_VECTOR, dst
    /* Restore vector registers first since it will modify vector states */
    mv      t0, \dst
    addi    t1, t0, VEC_FRAME_V0

    VEC_INSN_VSETVLI_T2_X0_E8_M8

    VEC_INSN_VLE8_V0_T1
    add     t1, t1, t2
    VEC_INSN_VLE8_V8_T1
    add     t1, t1, t2
    VEC_INSN_VLE8_V16_T1
    add     t1, t1, t2
    VEC_INSN_VLE8_V24_T1

    mv      t1, t0

    REG_L   t0, VEC_FRAME_VSTART(t1)
    csrw    CSR_VSTART, t0
    REG_L   t0, VEC_FRAME_VCSR(t1)
    csrw    CSR_VCSR, t0

    REG_L   t0, VEC_FRAME_VTYPE(t1)
    REG_L   t3, VEC_FRAME_VL(t1)
    VEC_INSN_VSETVL_X0_T3_T0
.endm

#endif /* __ASSEMBLY__ */

#endif /* __RVV_CONTEXT_H__ */
