/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-10     RT-Thread    the first version,
 *                             compatible to riscv-v-spec-1.0
 */
#ifndef __EXT_CONTEXT_H__
#define __EXT_CONTEXT_H__

#ifdef __ASSEMBLY__

/**
 * extension context maintenance
 */

#include "cpuport.h"
#include "encoding.h"
#include "vector_encoding.h"

/**
 * ==================================
 * FPU EXTENSION
 * ==================================
 */

#ifdef ENABLE_FPU
#define FPU_CTX_F0_OFF   0   /* offsetof(fpu_context_t, fpustatus.f[0])  - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F1_OFF   8   /* offsetof(fpu_context_t, fpustatus.f[1])  - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F2_OFF   16  /* offsetof(fpu_context_t, fpustatus.f[2])  - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F3_OFF   24  /* offsetof(fpu_context_t, fpustatus.f[3])  - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F4_OFF   32  /* offsetof(fpu_context_t, fpustatus.f[4])  - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F5_OFF   40  /* offsetof(fpu_context_t, fpustatus.f[5])  - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F6_OFF   48  /* offsetof(fpu_context_t, fpustatus.f[6])  - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F7_OFF   56  /* offsetof(fpu_context_t, fpustatus.f[7])  - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F8_OFF   64  /* offsetof(fpu_context_t, fpustatus.f[8])  - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F9_OFF   72  /* offsetof(fpu_context_t, fpustatus.f[9])  - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F10_OFF  80  /* offsetof(fpu_context_t, fpustatus.f[10]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F11_OFF  88  /* offsetof(fpu_context_t, fpustatus.f[11]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F12_OFF  96  /* offsetof(fpu_context_t, fpustatus.f[12]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F13_OFF  104 /* offsetof(fpu_context_t, fpustatus.f[13]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F14_OFF  112 /* offsetof(fpu_context_t, fpustatus.f[14]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F15_OFF  120 /* offsetof(fpu_context_t, fpustatus.f[15]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F16_OFF  128 /* offsetof(fpu_context_t, fpustatus.f[16]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F17_OFF  136 /* offsetof(fpu_context_t, fpustatus.f[17]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F18_OFF  144 /* offsetof(fpu_context_t, fpustatus.f[18]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F19_OFF  152 /* offsetof(fpu_context_t, fpustatus.f[19]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F20_OFF  160 /* offsetof(fpu_context_t, fpustatus.f[20]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F21_OFF  168 /* offsetof(fpu_context_t, fpustatus.f[21]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F22_OFF  176 /* offsetof(fpu_context_t, fpustatus.f[22]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F23_OFF  184 /* offsetof(fpu_context_t, fpustatus.f[23]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F24_OFF  192 /* offsetof(fpu_context_t, fpustatus.f[24]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F25_OFF  200 /* offsetof(fpu_context_t, fpustatus.f[25]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F26_OFF  208 /* offsetof(fpu_context_t, fpustatus.f[26]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F27_OFF  216 /* offsetof(fpu_context_t, fpustatus.f[27]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F28_OFF  224 /* offsetof(fpu_context_t, fpustatus.f[28]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F29_OFF  232 /* offsetof(fpu_context_t, fpustatus.f[29]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F30_OFF  240 /* offsetof(fpu_context_t, fpustatus.f[30]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#define FPU_CTX_F31_OFF  248 /* offsetof(fpu_context_t, fpustatus.f[31]) - offsetof(fpu_context_t, fpustatus.f[0]) */
#endif /* ENABLE_FPU */

/**
 * ==================================
 * VECTOR EXTENSION
 * ==================================
 */

#ifdef ENABLE_VECTOR

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

#endif /* ENABLE_VECTOR */

#endif /* __ASSEMBLY__ */

#endif /* __EXT_CONTEXT_H__ */