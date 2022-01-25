/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#ifndef __STACKFRAME_H__
#define __STACKFRAME_H__

#include "asm.h"
#include "mips_regs.h"
#include "ptrace.h"

/* You MUST ensure FP is enabled before SAVE_FPU! */
    .macro SAVE_FPU
    .set push
    .set noreorder
#ifdef RT_USING_FPU
    /* Ensure CU1 (FPU) is enabled */
    MFC0 v1, CP0_STATUS
    lui t1, %hi(ST0_CU1)
    addiu t1, t1, %lo(ST0_CU1)
    or v1, v1, t1
    MTC0 v1, CP0_STATUS
    SSNOP
    cfc1 v1, fcr31
    /* Store as delay slot */
    s.d $f0, PT_FPU_R0(sp)
    s.d $f2, PT_FPU_R2(sp)
    s.d $f4, PT_FPU_R4(sp)
    s.d $f6, PT_FPU_R6(sp)
    s.d $f8, PT_FPU_R8(sp)
    s.d $f10, PT_FPU_R10(sp)
    s.d $f12, PT_FPU_R12(sp)
    s.d $f14, PT_FPU_R14(sp)
    s.d $f16, PT_FPU_R16(sp)
    s.d $f18, PT_FPU_R18(sp)
    s.d $f20, PT_FPU_R20(sp)
    s.d $f22, PT_FPU_R22(sp)
    s.d $f24, PT_FPU_R24(sp)
    s.d $f26, PT_FPU_R26(sp)
    s.d $f28, PT_FPU_R28(sp)
    s.d $f30, PT_FPU_R30(sp)
    LONG_S v1, PT_FPU_FCSR31(sp)
#endif
    .set reorder
    .set pop
    .endm

    .macro  SAVE_AT
    .set    push
    .set    noat
    LONG_S  $1, PT_R1(sp)
    .set    pop
    .endm

    .macro  SAVE_TEMP
    mfhi    v1
    LONG_S  $8, PT_R8(sp)
    LONG_S  $9, PT_R9(sp)
    sw  v1, PT_HI(sp)
    mflo    v1
    LONG_S  $10, PT_R10(sp)
    LONG_S  $11, PT_R11(sp)
    sw  v1,  PT_LO(sp)
    LONG_S  $12, PT_R12(sp)
    LONG_S  $13, PT_R13(sp)
    LONG_S  $14, PT_R14(sp)
    LONG_S  $15, PT_R15(sp)
    LONG_S  $24, PT_R24(sp)
    .endm

    .macro  SAVE_STATIC
    LONG_S  $16, PT_R16(sp)
    LONG_S  $17, PT_R17(sp)
    LONG_S  $18, PT_R18(sp)
    LONG_S  $19, PT_R19(sp)
    LONG_S  $20, PT_R20(sp)
    LONG_S  $21, PT_R21(sp)
    LONG_S  $22, PT_R22(sp)
    LONG_S  $23, PT_R23(sp)
    LONG_S  $30, PT_R30(sp)
    .endm

    .macro  SAVE_SOME
    .set    push
    .set    noat
    .set    reorder
    move    k1, sp
    move    k0, sp
    PTR_SUBU sp, k1, PT_SIZE
    LONG_S  k0, PT_R29(sp)
    LONG_S  $3, PT_R3(sp)
    LONG_S  $0, PT_R0(sp)
    MFC0    v1, CP0_STATUS
    LONG_S  $2, PT_R2(sp)
    LONG_S  v1, PT_STATUS(sp)
    LONG_S  $4, PT_R4(sp)
    MFC0    v1, CP0_CAUSE
    LONG_S  $5, PT_R5(sp)
    LONG_S  v1, PT_CAUSE(sp)
    LONG_S  $6, PT_R6(sp)
    MFC0    v1, CP0_EPC
    LONG_S  $7, PT_R7(sp)
    LONG_S  v1, PT_EPC(sp)
    LONG_S  $25, PT_R25(sp)
    LONG_S  $28, PT_R28(sp)
    LONG_S  $31, PT_R31(sp)
    .set    pop
    .endm

    .macro  SAVE_ALL
    SAVE_SOME
    SAVE_AT
    SAVE_TEMP
    SAVE_FPU
    SAVE_STATIC
    .endm

    .macro RESTORE_FPU
    .set push
    .set noreorder
#ifdef RT_USING_FPU
    /* Ensure CU1 (FPU) is enabled */
    MFC0 v1, CP0_STATUS
    lui t1, %hi(ST0_CU1)
    addiu t1, t1, %lo(ST0_CU1)
    or v1, v1, t1
    MTC0 v1, CP0_STATUS
    SSNOP
    LONG_L v1, PT_FPU_FCSR31(sp)
    ctc1 v1, fcr31
    l.d $f0, PT_FPU_R0(sp)
    l.d $f2, PT_FPU_R2(sp)
    l.d $f4, PT_FPU_R4(sp)
    l.d $f6, PT_FPU_R6(sp)
    l.d $f8, PT_FPU_R8(sp)
    l.d $f10, PT_FPU_R10(sp)
    l.d $f12, PT_FPU_R12(sp)
    l.d $f14, PT_FPU_R14(sp)
    l.d $f16, PT_FPU_R16(sp)
    l.d $f18, PT_FPU_R18(sp)
    l.d $f20, PT_FPU_R20(sp)
    l.d $f22, PT_FPU_R22(sp)
    l.d $f24, PT_FPU_R24(sp)
    l.d $f26, PT_FPU_R26(sp)
    l.d $f28, PT_FPU_R28(sp)
    l.d $f30, PT_FPU_R30(sp)
#endif
    .set reorder
    .set pop
    .endm

    .macro  RESTORE_AT
    .set    push
    .set    noat
    LONG_L  $1,  PT_R1(sp)
    .set    pop
    .endm

    .macro  RESTORE_TEMP
    lw  $24, PT_LO(sp)
    LONG_L  $8, PT_R8(sp)
    LONG_L  $9, PT_R9(sp)
    mtlo    $24
    lw  $24, PT_HI(sp)
    LONG_L  $10, PT_R10(sp)
    LONG_L  $11, PT_R11(sp)
    mthi    $24
    LONG_L  $12, PT_R12(sp)
    LONG_L  $13, PT_R13(sp)
    LONG_L  $14, PT_R14(sp)
    LONG_L  $15, PT_R15(sp)
    LONG_L  $24, PT_R24(sp)
    .endm

    .macro  RESTORE_STATIC
    LONG_L  $16, PT_R16(sp)
    LONG_L  $17, PT_R17(sp)
    LONG_L  $18, PT_R18(sp)
    LONG_L  $19, PT_R19(sp)
    LONG_L  $20, PT_R20(sp)
    LONG_L  $21, PT_R21(sp)
    LONG_L  $22, PT_R22(sp)
    LONG_L  $23, PT_R23(sp)
    LONG_L  $30, PT_R30(sp)
    .endm

#define STATMASK 0x1f

    .macro  RESTORE_SOME
    .set    push
    .set    reorder
    .set    noat
    mfc0    a0, CP0_STATUS
    ori a0, STATMASK
    xori    a0, STATMASK
    mtc0    a0, CP0_STATUS
    li  v1, (ST0_CU1 | ST0_FR | ST0_IM)
    and a0, v1, a0
    LONG_L  v0, PT_STATUS(sp)
    li  v1, ~(ST0_CU1 | ST0_FR | ST0_IM)
    and v0, v1
    or  v0, a0
    li  v1, (ST0_KX | ST0_SX | ST0_UX)
    or  v0, v1
    mtc0    v0, CP0_STATUS
    LONG_L  v1, PT_EPC(sp)
    MTC0    v1, CP0_EPC
    LONG_L  $31, PT_R31(sp)
    LONG_L  $28, PT_R28(sp)
    LONG_L  $25, PT_R25(sp)
    LONG_L  $7,  PT_R7(sp)
    LONG_L  $6,  PT_R6(sp)
    LONG_L  $5,  PT_R5(sp)
    LONG_L  $4,  PT_R4(sp)
    LONG_L  $3,  PT_R3(sp)
    LONG_L  $2,  PT_R2(sp)
    .set    pop
    .endm

    .macro  RESTORE_SP_AND_RET
    LONG_L  sp, PT_R29(sp)
    eret
    nop
    .endm


    .macro  RESTORE_SP
    LONG_L  sp, PT_R29(sp)
    .endm

    .macro  RESTORE_ALL
    RESTORE_TEMP
    RESTORE_FPU
    RESTORE_STATIC
    RESTORE_AT
    RESTORE_SOME
    RESTORE_SP
    .endm

    .macro  RESTORE_ALL_AND_RET
    RESTORE_TEMP
    RESTORE_FPU
    RESTORE_STATIC
    RESTORE_AT
    RESTORE_SOME
    RESTORE_SP_AND_RET
    .endm

#endif /* end of __STACKFRAME_H__ */

