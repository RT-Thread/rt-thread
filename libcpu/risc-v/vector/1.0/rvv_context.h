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

#if defined(ARCH_VECTOR_VLEN_128)
    #define CTX_VECTOR_REGS 64
#elif defined(ARCH_VECTOR_VLEN_256)
    #define CTX_VECTOR_REGS 128
#else
#error "No supported VLEN"
#endif /* VLEN */

#define CTX_VECTOR_REG_NR  (CTX_VECTOR_REGS + 4)

#ifdef __ASSEMBLY__

/**
 * ==================================
 * VECTOR EXTENSION
 * ==================================
 */

#define VEC_FRAME_VSTART    (0 * REGBYTES)
#define VEC_FRAME_VTYPE     (1 * REGBYTES)
#define VEC_FRAME_VL        (2 * REGBYTES)
#define VEC_FRAME_VCSR      (3 * REGBYTES)
#define VEC_FRAME_V0        (4 * REGBYTES)

.macro GET_VEC_FRAME_LEN, xreg
    csrr    \xreg, vlenb
    slli    \xreg, \xreg, 5
    addi    \xreg, \xreg, 4 * REGBYTES
.endm

/**
 * @brief save vector extension hardware state
 *
 * @param dst register storing bottom of storage block
 *
 */
.macro SAVE_VECTOR, dst
    mv      t1, \dst

    csrr    t0, vstart
    STORE   t0, VEC_FRAME_VSTART(t1)
    csrr    t0, vtype
    STORE   t0, VEC_FRAME_VTYPE(t1)
    csrr    t0, vl
    STORE   t0, VEC_FRAME_VL(t1)
    csrr    t0, vcsr
    STORE   t0, VEC_FRAME_VCSR(t1)

    addi    t1, t1, VEC_FRAME_V0

    // config vector setting,
    // t2 is updated to length of a vector group in bytes
    VEC_CONFIG_SETVLI(t2, x0, VEC_IMM_SEW_8, VEC_IMM_LMUL_8)

    vse8.v  v0, (t1)
    add     t1, t1, t2
    vse8.v  v8, (t1)
    add     t1, t1, t2
    vse8.v  v16, (t1)
    add     t1, t1, t2
    vse8.v  v24, (t1)
.endm

/**
 * @brief restore vector extension hardware states
 *
 * @param dst register storing bottom of storage block
 *
 */
.macro RESTORE_VECTOR, dst
    // restore vector registers first since it will modify vector states
    mv      t0, \dst
    addi    t1, t0, VEC_FRAME_V0

    VEC_CONFIG_SETVLI(t2, x0, VEC_IMM_SEW_8, VEC_IMM_LMUL_8)

    vle8.v  v0, (t1)
    add     t1, t1, t2
    vle8.v  v8, (t1)
    add     t1, t1, t2
    vle8.v  v16, (t1)
    add     t1, t1, t2
    vle8.v  v24, (t1)

    mv      t1, t0

    LOAD    t0, VEC_FRAME_VSTART(t1)
    csrw    vstart, t0
    LOAD    t0, VEC_FRAME_VCSR(t1)
    csrw    vcsr, t0

    LOAD    t0, VEC_FRAME_VTYPE(t1)
    LOAD    t3, VEC_FRAME_VL(t1)
    VEC_CONFIG_SET_VL_VTYPE(t3, t0)
.endm

#endif

#endif /* __RVV_CONTEXT_H__ */
