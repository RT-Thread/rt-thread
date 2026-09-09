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

#ifndef __VECTOR_ENCODING_1_0_H__
#define __VECTOR_ENCODING_1_0_H__

#ifdef __ASSEMBLY__

/**
 * assembler names used for vset{i}vli vtypei immediate
 */

#define VEC_IMM_SEW_8           e8
#define VEC_IMM_SEW_16          e16
#define VEC_IMM_SEW_32          e32
#define VEC_IMM_SEW_64          e64
/* group setting, encoding by multiplier */
#define VEC_IMM_LMUL_F8         mf8
#define VEC_IMM_LMUL_F4         mf4
#define VEC_IMM_LMUL_F2         mf2
#define VEC_IMM_LMUL_1          m1
#define VEC_IMM_LMUL_2          m2
#define VEC_IMM_LMUL_4          m4
#define VEC_IMM_LMUL_8          m8
/* TAIL & MASK agnostic bits */
#define VEC_IMM_TAIL_AGNOSTIC   ta
#define VEC_IMM_MASK_AGNOSTIC   ma
#define VEC_IMM_TAMA            VEC_IMM_TAIL_AGNOSTIC, VEC_IMM_MASK_AGNOSTIC
#define VEC_IMM_TAMU            VEC_IMM_TAIL_AGNOSTIC
#define VEC_IMM_TUMA            VEC_IMM_MASK_AGNOSTIC

/**
 * configuration setting instruction
 */
#define VEC_CONFIG_SETVLI(xVl, xAvl, vtype...)  vsetvli xVl, xAvl, ##vtype
#define VEC_CONFIG_SET_VL_VTYPE(xVl, xVtype)    vsetvl x0, xVl, xVtype

/*
 * Some maintained RISC-V GCC 10 based toolchains can build RT-Thread but use
 * binutils without RVV mnemonic support. Keep the fixed encodings used by the
 * context save/restore path here so ARCH_RISCV_VECTOR does not require a newer
 * assembler just to build the trap entry.
 */
#define VEC_INSN_VSETVLI_T2_X0_E8_M8            .word 0x003073d7
#define VEC_INSN_VSETVL_X0_T3_T0                .word 0x805e7057

#define VEC_INSN_VLE8_V0_T1                     .word 0x02030007
#define VEC_INSN_VLE8_V8_T1                     .word 0x02030407
#define VEC_INSN_VLE8_V16_T1                    .word 0x02030807
#define VEC_INSN_VLE8_V24_T1                    .word 0x02030c07

#define VEC_INSN_VSE8_V0_T1                     .word 0x02030027
#define VEC_INSN_VSE8_V8_T1                     .word 0x02030427
#define VEC_INSN_VSE8_V16_T1                    .word 0x02030827
#define VEC_INSN_VSE8_V24_T1                    .word 0x02030c27

#endif /* __ASSEMBLY__ */

#endif /* __VECTOR_ENCODING_H__ */
