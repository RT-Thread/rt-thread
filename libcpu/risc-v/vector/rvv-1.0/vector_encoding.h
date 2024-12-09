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

/* mstatus/sstatus */
#define MSTATUS_VS          0x00000600
#define SSTATUS_VS          0x00000600 /* Vector Status */
#define SSTATUS_VS_INITIAL  0x00000200
#define SSTATUS_VS_CLEAN    0x00000400
#define SSTATUS_VS_DIRTY    0x00000600

#ifdef __ASSEMBLY__

/**
 * assembler names used for vset{i}vli vtypei immediate
 */

#define VEC_IMM_SEW_8      e8
#define VEC_IMM_SEW_16     e16
#define VEC_IMM_SEW_32     e32
#define VEC_IMM_SEW_64     e64
/* group setting, encoding by multiplier */
#define VEC_IMM_LMUL_F8     mf8
#define VEC_IMM_LMUL_F4     mf4
#define VEC_IMM_LMUL_F2     mf2
#define VEC_IMM_LMUL_1      m1
#define VEC_IMM_LMUL_2      m2
#define VEC_IMM_LMUL_4      m4
#define VEC_IMM_LMUL_8      m8
/* TAIL & MASK agnostic bits */
#define VEC_IMM_TAIL_AGNOSTIC   ta
#define VEC_IMM_MASK_AGNOSTIC   ma
#define VEC_IMM_TAMA            VEC_IMM_TAIL_AGNOSTIC, VEC_IMM_MASK_AGNOSTIC
#define VEC_IMM_TAMU            VEC_IMM_TAIL_AGNOSTIC
#define VEC_IMM_TUMA            VEC_IMM_MASK_AGNOSTIC

/**
 * configuration setting instruction
 */
#define VEC_CONFIG_SETVLI(xVl, xAvl, vtype...)   vsetvli xVl, xAvl, ##vtype
#define VEC_CONFIG_SET_VL_VTYPE(xVl, xVtype)   vsetvl x0, xVl, xVtype

#endif

#endif /* __VECTOR_ENCODING_H__ */
