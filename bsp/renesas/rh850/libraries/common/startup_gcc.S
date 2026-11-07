/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#include "rh850_asm.h"
#include "rh850_core.inc"

    .section .text.startup, "ax"
    .globl __start
__start:
    .irp n, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, \
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    mov     r0, r\n
    .endr

    ldsr    r0, RH850_SR_EIPC
    ldsr    r0, RH850_SR_FEPC
    ldsr    r0, RH850_SR_CTPC
    ldsr    r0, RH850_SR_EIWR
    ldsr    r0, RH850_SR_FEWR
    ldsr    r0, RH850_SR_INTBP
    rh850_core_clear_error_regs

    /* EBASE is written while PSW.EBV is 0 */
    mov     hilo(rh850_vectors), r10
    ldsr    r10, RH850_SR_EBASE
#if RH850_CORE_HAS_FPU
    mov     hilo(RH850_PSW_ID | RH850_PSW_EBV | RH850_PSW_CU0), r10
    ldsr    r10, RH850_SR_PSW
    /* CU0 must be in effect before the FPU registers are written */
    synci
    rh850_core_init_fpu r10
#else
    mov     hilo(RH850_PSW_ID | RH850_PSW_EBV), r10
    ldsr    r10, RH850_SR_PSW
#endif

    rh850_core_clear_mpu r10, r11
    rh850_core_clear_icache
    synci

    mov     hilo(__stack_top), sp

    mov     hilo(__data_load), r6
    mov     hilo(__data_start), r7
    mov     hilo(__data_end), r8
1:
    cmp     r8, r7
    bnl     2f
    ld.w    0[r6], r10
    st.w    r10, 0[r7]
    add     4, r6
    add     4, r7
    br      1b

2:
    mov     hilo(__bss_start), r7
    mov     hilo(__bss_end), r8
3:
    cmp     r8, r7
    bnl     4f
    st.w    r0, 0[r7]
    add     4, r7
    br      3b

4:
    jarl    C_SYM(entry), lp
5:
    halt
    br      5b
