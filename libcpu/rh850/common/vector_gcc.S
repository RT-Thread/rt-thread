/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#include <rtconfig.h>
#include "rh850_asm.h"

    .macro vector target
    .balign 16
    jr      \target
    .endm

    .section .vectors, "ax"
    .balign 512
    .globl rh850_vectors
rh850_vectors:
    vector  __start             /* 000H RESET */
    vector  rh850_fe_fault      /* 010H SYSERR */
    vector  rh850_fe_fault      /* 020H reserved */
    vector  rh850_fe_fault      /* 030H FETRAP */
    vector  rh850_trap0_entry   /* 040H TRAP0 */
    vector  rh850_ei_fault      /* 050H TRAP1 */
    vector  rh850_fe_fault      /* 060H RIE */
    vector  rh850_ei_fault      /* 070H FPE, FPI */
    vector  rh850_fe_fault      /* 080H UCPOP */
    vector  rh850_fe_fault      /* 090H MIP, MDP */
    vector  rh850_fe_fault      /* 0A0H PIE */
    vector  rh850_fe_fault      /* 0B0H reserved */
    vector  rh850_fe_fault      /* 0C0H MAE */
    vector  rh850_fe_fault      /* 0D0H reserved */
    vector  rh850_fe_fault      /* 0E0H FENMI */
    vector  rh850_fe_fault      /* 0F0H FEINT */
    .rept 16
    vector  rh850_eiint_entry   /* 100H-1F0H EIINT priority 0-15 */
    .endr

    .text

    .macro FAULT_FRAME pcid, pcsel, pswid, pswsel
    pushsp  r1-r2
    pushsp  r4-r31
    add     -16, sp
    rh850_stsr \pcid, \pcsel, r10
    st.w    r10, 0[sp]
    rh850_stsr \pswid, \pswsel, r10
    st.w    r10, 4[sp]
#ifdef RT_USING_FPU
    rh850_stsr RH850_SR_FPSR, r10
    st.w    r10, 8[sp]
    rh850_stsr RH850_SR_FPEPC, r10
    st.w    r10, 12[sp]
#else
    st.w    r0, 8[sp]
    st.w    r0, 12[sp]
#endif
    mov     sp, r8
    .endm

rh850_fe_fault:
    FAULT_FRAME RH850_SR_FEPC, RH850_SR_FEPSW
    mov     1, r6
    rh850_stsr RH850_SR_FEIC, r7
    jr      C_SYM(rh850_fault)

rh850_ei_fault:
    FAULT_FRAME RH850_SR_EIPC, RH850_SR_EIPSW
    mov     0, r6
    rh850_stsr RH850_SR_EIIC, r7
    jr      C_SYM(rh850_fault)
