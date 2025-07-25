 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * attention: don't modify this file as a suggest
 * you should copy from chip_riscv_dummy/include/asm/riscv_asm_macro.h and keep it newer
 * please contact xuantie-rtos os team if have question
 */

#ifndef __RISCV_ASM_MACRO_H__
#define __RISCV_ASM_MACRO_H__

#if (!defined(__riscv_flen)) && (CONFIG_CHECK_FPU_DIRTY)
#error "this cpu doesn't supprot FPU, but macro 'CONFIG_CHECK_FPU_DIRTY' is defined, please remove it."
#endif

#if (!defined(__riscv_vector)) && (CONFIG_CHECK_VECTOR_DIRTY)
#error "this cpu doesn't supprot vector, but macro 'CONFIG_CHECK_VECTOR_DIRTY' is defined, please remove it."
#endif

#if (!defined(__riscv_matrix) && !defined(__riscv_xtheadmatrix)) && (CONFIG_CHECK_MATRIX_DIRTY)
#error "this cpu doesn't supprot matrix, but macro 'CONFIG_CHECK_MATRIX_DIRTY' is defined, please remove it."
#endif

#include "riscv_csr.h"

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
.macro RESTORE_MSTATUS
    /* t0 and t1 are not restored before using */
    /* now, sp is at the top of the stack (the lowest address)*/
    li       t1, 0
#if __riscv_matrix || __riscv_xtheadmatrix  /* matrix registers */
#if __riscv_xlen == 64
    addi     t1, t1, (12 + 12)
#else
    addi     t1, t1, 12
#endif /*__riscv_xlen */
    csrr     t0, xmlenb
    slli     t0, t0, 3
    add      t1, t1, t0
#endif /* __riscv_matrix || __riscv_xtheadmatrix */

#ifdef __riscv_vector /* vector registers */
    csrr     t0, vlenb
    slli     t0, t0, 5
    add      t1, t1, t0
#if __riscv_xlen == 64
    addi     t1, t1, (20+20)
#else
    addi     t1, t1, 20
#endif  /* __riscv_xlen */
#endif  /* __riscv_vector */

#if __riscv_flen == 64 /* float registers */
#if __riscv_xlen == 64
    addi     t1, t1, 168
#else
    addi     t1, t1, 164
#endif /* __riscv_xlen */

#elif __riscv_flen == 32
    addi     t1, t1, 84
#endif /* __riscv_flen */

#ifdef __riscv_dsp  /* vxsat register, 32-bit cpu only */
    addi     t1, t1, 4
#endif /* __riscv_dsp */

#if __riscv_xlen == 64  /*general purpose registers*/
    addi     t1, t1, (72 + 72)
#elif __riscv_xlen == 32
    addi     t1, t1, 72
#endif
    add      sp, sp, t1

    /* now, sp is the position of mstatus */
    load_x   t3, (0)(sp)
    csrw     mstatus, t3
    sub      sp, sp, t1
.endm

.macro RESTORE_SSTATUS
    /* t0 and t1 are not restored before using */
    /* now, sp is at the top of the stack (the lowest address)*/
    li       t1, 0
#if __riscv_matrix || __riscv_xtheadmatrix /* matrix registers */
#if __riscv_xlen == 64
    addi     t1, t1, (12 + 12)
#else
    addi     t1, t1, 12
#endif /*__riscv_xlen */
    csrr     t0, xmlenb
    slli     t0, t0, 3
    add      t1, t1, t0
#endif /* __riscv_matrix || __riscv_xtheadmatrix */

#ifdef __riscv_vector /* vector registers */
    csrr     t0, vlenb
    slli     t0, t0, 5
    add      t1, t1, t0
#if __riscv_xlen == 64
    addi     t1, t1, (20+20)
#else
    addi     t1, t1, 20
#endif  /* __riscv_xlen */
#endif  /* __riscv_vector */

#if __riscv_flen == 64 /* float registers */
#if __riscv_xlen == 64
    addi     t1, t1, 168
#else
    addi     t1, t1, 164
#endif /* __riscv_xlen */

#elif __riscv_flen == 32
    addi     t1, t1, 84
#endif /* __riscv_flen */

#if __riscv_xlen == 64  /*general purpose registers*/
    addi     t1, t1, (72 + 72)
#elif __riscv_xlen == 32
    addi     t1, t1, 72
#endif
    add      sp, sp, t1

    /* now, sp is the position of mstatus */
    load_x   t3, (0)(sp)
    csrw     sstatus, t3
    sub      sp, sp, t1
.endm

#endif /* CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY */

.macro SAVE_VECTOR_REGISTERS
    /* t0,t1 saved before using */
    /* mstatus->t3 */
#ifdef __riscv_vector
#if CONFIG_CHECK_VECTOR_DIRTY
    /* check if VS filed of MSTATUS is 'dirty' */
    li       t1, SR_VS_DIRTY
    and      t4, t3, t1
    bne      t4, t1, 1f
#endif /* CONFIG_CHECK_VECTOR_DIRTY */

    /* if dirty, save vector registers */
#if __riscv_xlen == 64
    addi     sp, sp, -(20+20)
    csrr     t0, vl
    store_x  t0,  (0  +0  )(sp)
    csrr     t0, vtype
    store_x  t0,  (4  +4  )(sp)
    csrr     t0, vstart
    store_x  t0,  (8  +8  )(sp)
    csrr     t0, vxsat
    store_x  t0,  (12 +12 )(sp)
    csrr     t0, vxrm
    store_x  t0,  (16 +16 )(sp)
#else
    addi     sp, sp, -20
    csrr     t0, vl
    store_x  t0,  (0)(sp)
    csrr     t0, vtype
    store_x  t0,  (4)(sp)
    csrr     t0, vstart
    store_x  t0,  (8)(sp)
    csrr     t0, vxsat
    store_x  t0,  (12)(sp)
    csrr     t0, vxrm
    store_x  t0,  (16)(sp)
#endif /*__riscv_xlen */

    csrr     t0, vlenb
    slli     t0, t0, 3
    slli     t1, t0, 2
    sub      sp, sp, t1
#if (__riscv_v == 7000)
    vsetvli  zero, zero, e8, m8
    vsb.v    v0, (sp)
    add      sp, sp, t0
    vsb.v    v8, (sp)
    add      sp, sp, t0
    vsb.v    v16, (sp)
    add      sp, sp, t0
    vsb.v    v24, (sp)
#elif (__riscv_v == 1000000)
    vsetvli  zero, zero, e8, m8, ta, ma
    vs8r.v   v0, (sp)
    add      sp, sp, t0
    vs8r.v   v8, (sp)
    add      sp, sp, t0
    vs8r.v   v16, (sp)
    add      sp, sp, t0
    vs8r.v   v24, (sp)
#endif
    sub      t0, t1, t0
    sub      sp, sp, t0
#if CONFIG_CHECK_VECTOR_DIRTY
    j        2f
1:  /* don't need to save vector registers, set sp */
#if __riscv_xlen == 64
    addi     sp, sp, -(20+20)
#else
    addi     sp, sp, -20
#endif
    csrr     t0, vlenb
    slli     t0, t0, 5
    sub      sp, sp, t0
2:
#endif /* CONFIG_CHECK_VECTOR_DIRTY */
#endif /*__riscv_vector*/
.endm

.macro RESTORE_VECTOR_REGISTERS
    /* t0,t1,t2 not restored before using, mstatus has been restored before using */
#ifdef __riscv_vector
#if CONFIG_CHECK_VECTOR_DIRTY
    /* check if VS filed of MSTATUS is 'dirty' */
    li       t1, SR_VS_DIRTY
    and      t4, t3, t1
    bne      t4, t1, 1f
#endif /* CONFIG_CHECK_VECTOR_DIRTY */

    /* get the range of register */
    csrr     t0, vlenb
    slli     t0, t0, 3

    /* save */
#if (__riscv_v == 7000)
    vsetvli  zero, zero, e8, m8
    vlb.v    v0, (sp)
    add      sp, sp, t0
    vlb.v    v8, (sp)
    add      sp, sp, t0
    vlb.v    v16, (sp)
    add      sp, sp, t0
    vlb.v    v24, (sp)
    add      sp, sp, t0
#elif (__riscv_v == 1000000)
    vsetvli  zero, zero, e8, m8, ta, ma
    vl8r.v   v0, (sp)
    add      sp, sp, t0
    vl8r.v   v8, (sp)
    add      sp, sp, t0
    vl8r.v   v16, (sp)
    add      sp, sp, t0
    vl8r.v   v24, (sp)
    add      sp, sp, t0
#endif
#if __riscv_xlen == 64
    load_x   t0, (0 +0)(sp)
    load_x   t1, (4 +4)(sp)
    load_x   t2, (8 +8)(sp)
    vsetvl   zero, t0, t1
    csrw     vstart, t2
    load_x   t2, (12 +12)(sp)
    csrw     vxsat, t2
    load_x   t2, (16 +16)(sp)
    csrw     vxrm, t2
    addi     sp, sp, (20+20)
#else
    load_x   t0, (0)(sp)
    load_x   t1, (4)(sp)
    load_x   t2, (8)(sp)
    vsetvl   zero, t0, t1
    csrw     vstart, t2
    load_x   t2, (12)(sp)
    csrw     vxsat, t2
    load_x   t2, (16)(sp)
    csrw     vxrm, t2
    addi     sp, sp, 20
#endif /*__riscv_xlen */
#if CONFIG_CHECK_VECTOR_DIRTY
    j        2f
1:
    /* don't restore, move sp only */
#if __riscv_xlen == 64
    addi     sp, sp, (20+20)
#else
    addi     sp, sp, (20)
#endif
    csrr     t0, vlenb
    slli     t0, t0, 5
    add      sp, sp, t0
2:
#endif /* CONFIG_CHECK_VECTOR_DIRTY */
#endif /*__riscv_vector*/
.endm


.macro SAVE_FLOAT_REGISTERS
    /* t0, t1 saved before using */
#if __riscv_flen == 64
#if CONFIG_CHECK_FPU_DIRTY
    /* check if FS filed of MSTATUS is 'dirty' */
    li       t1, SR_FS_DIRTY
    and      t4, t3, t1
    bne      t4, t1, 1f
#endif /*CONFIG_CHECK_FPU_DIRTY*/

    /* save */
#if __riscv_xlen == 64
    addi     sp, sp, -(4+4)
    frcsr    t0
    store_x  t0, (0  +0  )(sp)
#else
    addi     sp, sp, -4
    frcsr    t0
    store_x  t0, 0(sp)
#endif /*__riscv_xlen */

    addi     sp,  sp, -160
    fstore_x ft0, (0 +0 )(sp)
    fstore_x ft1, (4 +4 )(sp)
    fstore_x ft2, (8 +8 )(sp)
    fstore_x ft3, (12+12)(sp)
    fstore_x ft4, (16+16)(sp)
    fstore_x ft5, (20+20)(sp)
    fstore_x ft6, (24+24)(sp)
    fstore_x ft7, (28+28)(sp)
    fstore_x fa0, (32+32)(sp)
    fstore_x fa1, (36+36)(sp)
    fstore_x fa2, (40+40)(sp)
    fstore_x fa3, (44+44)(sp)
    fstore_x fa4, (48+48)(sp)
    fstore_x fa5, (52+52)(sp)
    fstore_x fa6, (56+56)(sp)
    fstore_x fa7, (60+60)(sp)
    fstore_x ft8, (64+64)(sp)
    fstore_x ft9, (68+68)(sp)
    fstore_x ft10,(72+72)(sp)
    fstore_x ft11,(76+76)(sp)
#elif __riscv_flen == 32
#if CONFIG_CHECK_FPU_DIRTY
    /* check if FS filed of MSTATUS is 'dirty' */
    li       t1, SR_FS_DIRTY
    and      t4, t3, t1
    bne      t4, t1, 1f
#endif  /* CONFIG_CHECK_FPU_DIRTY */

    addi     sp, sp, -4
    frcsr    t0
    store_x  t0, 0(sp)

    addi     sp,  sp, -80
    fstore_x ft0, 0(sp)
    fstore_x ft1, 4(sp)
    fstore_x ft2, 8(sp)
    fstore_x ft3, 12(sp)
    fstore_x ft4, 16(sp)
    fstore_x ft5, 20(sp)
    fstore_x ft6, 24(sp)
    fstore_x ft7, 28(sp)
    fstore_x fa0, 32(sp)
    fstore_x fa1, 36(sp)
    fstore_x fa2, 40(sp)
    fstore_x fa3, 44(sp)
    fstore_x fa4, 48(sp)
    fstore_x fa5, 52(sp)
    fstore_x fa6, 56(sp)
    fstore_x fa7, 60(sp)
    fstore_x ft8, 64(sp)
    fstore_x ft9, 68(sp)
    fstore_x ft10,72(sp)
    fstore_x ft11,76(sp)
#endif /*__riscv_flen */
#if CONFIG_CHECK_FPU_DIRTY
    j        2f
1:
    /* don't store, move sp only */
#if __riscv_flen == 64
#if __riscv_xlen == 64
    addi     sp, sp, -168
#else
    addi     sp, sp, -164
#endif /*__riscv_xlen */
#elif __riscv_flen == 32
    addi     sp, sp, -84
#endif /* __riscv_xlen */
2:
#endif
.endm

.macro RESTORE_FLOAT_REGISTERS
    /* t0 and t1 are not restored before using, mstatus has been restored before using */
#if __riscv_flen == 64
#if CONFIG_CHECK_FPU_DIRTY
    /* check if FS filed of MSTATUS is 'dirty' */
    li       t1, SR_FS_DIRTY
    and      t4, t3, t1
    bne      t4, t1, 1f
#endif /* CONFIG_CHECK_FPU_DIRTY */

    /* restore */
    fload_x  ft0, (0 +0 )(sp)
    fload_x  ft1, (4 +4 )(sp)
    fload_x  ft2, (8 +8 )(sp)
    fload_x  ft3, (12+12)(sp)
    fload_x  ft4, (16+16)(sp)
    fload_x  ft5, (20+20)(sp)
    fload_x  ft6, (24+24)(sp)
    fload_x  ft7, (28+28)(sp)
    fload_x  fa0, (32+32)(sp)
    fload_x  fa1, (36+36)(sp)
    fload_x  fa2, (40+40)(sp)
    fload_x  fa3, (44+44)(sp)
    fload_x  fa4, (48+48)(sp)
    fload_x  fa5, (52+52)(sp)
    fload_x  fa6, (56+56)(sp)
    fload_x  fa7, (60+60)(sp)
    fload_x  ft8, (64+64)(sp)
    fload_x  ft9, (68+68)(sp)
    fload_x  ft10,(72+72)(sp)
    fload_x  ft11,(76+76)(sp)
    addi     sp, sp, 160

#if __riscv_xlen == 64
    load_x   t0, (0 +0)(sp)
    fscsr    t0
    addi     sp, sp, (4+4)
#else
    load_x   t0, 0(sp)
    fscsr    t0
    addi     sp, sp, 4
#endif /*__riscv_xlen */
#elif __riscv_flen == 32
#if CONFIG_CHECK_FPU_DIRTY
    /* check if FS filed of MSTATUS is 'dirty' */
    li       t1, SR_FS_DIRTY
    and      t4, t3, t1
    bne      t4, t1, 1f
#endif /* CONFIG_CHECK_FPU_DIRTY */

    /* restore */
    fload_x  ft0, 0(sp)
    fload_x  ft1, 4(sp)
    fload_x  ft2, 8(sp)
    fload_x  ft3, 12(sp)
    fload_x  ft4, 16(sp)
    fload_x  ft5, 20(sp)
    fload_x  ft6, 24(sp)
    fload_x  ft7, 28(sp)
    fload_x  fa0, 32(sp)
    fload_x  fa1, 36(sp)
    fload_x  fa2, 40(sp)
    fload_x  fa3, 44(sp)
    fload_x  fa4, 48(sp)
    fload_x  fa5, 52(sp)
    fload_x  fa6, 56(sp)
    fload_x  fa7, 60(sp)
    fload_x  ft8, 64(sp)
    fload_x  ft9, 68(sp)
    fload_x  ft10,72(sp)
    fload_x  ft11,76(sp)
    addi     sp, sp, 80

    load_x   t0, 0(sp)
    fscsr    t0
    addi     sp, sp, 4
#endif /*__riscv_flen */
#if CONFIG_CHECK_FPU_DIRTY
    j        2f
1:
    /* don't restore, move sp only */
#if __riscv_flen == 64
#if __riscv_xlen == 64
    addi     sp, sp, 168
#elif __riscv_xlen == 32
    addi     sp, sp, 164
#endif
#elif __riscv_flen == 32
    addi     sp, sp, 84
#endif /* __riscv_flen */
2:
#endif /* CONFIG_CHECK_FPU_DIRTY */
.endm

.macro SAVE_MATRIX_REGISTERS
    /* t0,t1 saved before using */

#if __riscv_matrix || __riscv_xtheadmatrix
#if CONFIG_CHECK_MATRIX_DIRTY
    /* check if FS filed of MSTATUS is 'dirty' */
    li       t1, SR_MS_DIRTY
    and      t4, t3, t1
    bne      t4, t1, 1f
#endif /* CONFIG_CHECK_MATRIX_DIRTY */

    /* store */
#if __riscv_xlen == 64
    addi     sp, sp, -(12+12)
    csrr     t0, xmrstart
    store_x  t0,  (0  +0  )(sp)
    csrr     t0, xmcsr
    store_x  t0,  (4  +4  )(sp)
    csrr     t0, xmsize
    store_x  t0,  (8  +8  )(sp)
#else
    addi     sp, sp, -12
    csrr     t0, xmrstart
    store_x  t0,  (0)(sp)
    csrr     t0, xmcsr
    store_x  t0,  (4)(sp)
    csrr     t0, xmsize
    store_x  t0,  (8)(sp)
#endif /*__riscv_xlen */

    csrr     t0, xmlenb
    slli     t1, t0, 3
    sub      sp, sp, t1
    csrw     xmrstart, x0
    mst8mb   m0, (sp)
#if CONFIG_CHECK_MATRIX_DIRTY
    j        2f
1:
    /* don't save, move sp only */
    csrr     t0, xmlenb
    slli     t1, t0, 3
    sub      sp, sp, t1
#if __riscv_xlen == 64
    addi     sp, sp, -24
#else
    addi     sp, sp, -12
#endif
2:
#endif /* CONFIG_CHECK_MATRIX_DIRTY */
#endif /* __riscv_matrix || __riscv_xtheadmatrix */
.endm

.macro RESTORE_MATRIX_REGISTERS
    /* t0 and t1 are not restored before using, mstatus has been restored before using */

#if __riscv_matrix || __riscv_xtheadmatrix
#if CONFIG_CHECK_MATRIX_DIRTY
    /* check if FS filed of MSTATUS is 'dirty' */
    li       t1, SR_MS_DIRTY
    and      t4, t3, t1
    bne      t4, t1, 1f
#endif /* CONFIG_CHECK_MATRIX_DIRTY */

    /* restore */
    csrr     t0, xmlenb
    slli     t1, t0, 3
    csrw     xmrstart, x0
    mld8mb   m0, (sp)
    add      sp, sp, t1
#if __riscv_xlen == 64
    load_x   t0, (0 + 0)(sp)
    csrw     xmrstart, t0
    load_x   t0, (4 + 4)(sp)
    csrw     xmcsr, t0
    load_x   t0, (8 + 8)(sp)
    csrw     xmsize, t0
    addi     sp, sp, (12+12)
#else
    load_x   t0, (0)(sp)
    csrw     xmrstart, t0
    load_x   t0, (4)(sp)
    csrw     xmcsr, t0
    load_x   t0, (8)(sp)
    csrw     xmsize, t0
    addi     sp, sp, 12
#endif /*__riscv_xlen */
#if CONFIG_CHECK_MATRIX_DIRTY
    j        2f
1:
    /* don't restore, move sp only */
    csrr     t0, xmlenb
    slli     t1, t0, 3
    add      sp, sp, t1
#if __riscv_xlen == 64
    addi     sp, sp, 24
#else
    addi     sp, sp, 12
#endif
2:
#endif /* CONFIG_CHECK_MATRIX_DIRTY */
#endif /* __riscv_matrix || __riscv_xtheadmatrix */
.endm



#endif /* __RISCV_ASM_MACRO_H__ */

