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
#include "rh850_core.h"

#if defined(RT_USING_FPU) && RH850_CORE_HAS_SYNCE
#define RH850_SYNCE 1
#endif
#if defined(RT_USING_FPU) && RH850_CORE_HAS_FPEC
#define RH850_FPEC 1
#endif

/* Layout of struct rt_hw_stack_frame */
    .macro SAVE_CONTEXT
#ifdef RH850_SYNCE
    /* FPU results and FPI reports are complete before FPSR is read */
    synce
#endif
    pushsp  r1-r2
    pushsp  r4-r31
    add     -16, sp
    rh850_stsr RH850_SR_EIPC, r10
    st.w    r10, 0[sp]
    rh850_stsr RH850_SR_EIPSW, r10
    st.w    r10, 4[sp]
#ifdef RT_USING_FPU
    rh850_stsr RH850_SR_FPSR, r10
    st.w    r10, 8[sp]
    rh850_stsr RH850_SR_FPEPC, r10
    st.w    r10, 12[sp]
#endif
    .endm

/* While FPEC.FPIVD is 1, keep FPEPC and the FPSR cause bits */
    .macro RESTORE_FPU
    ld.w    8[sp], r10
#ifdef RH850_FPEC
    rh850_stsr RH850_SR_FPEC, r11
    andi    RH850_FPEC_FPIVD, r11, r11
    bz      .Lfpu_frame\@
    rh850_stsr RH850_SR_FPSR, r11
    andi    RH850_FPSR_XC_MASK, r11, r11
    andi    RH850_FPSR_XC_MASK, r10, r12
    xor     r12, r10
    or      r11, r10
    ldsr    r10, RH850_SR_FPSR
    br      .Lfpu_done\@
.Lfpu_frame\@:
#endif
    ldsr    r10, RH850_SR_FPSR
    ld.w    12[sp], r10
    ldsr    r10, RH850_SR_FPEPC
.Lfpu_done\@:
    .endm

    .macro RESTORE_CONTEXT
#ifdef RT_USING_FPU
    RESTORE_FPU
#endif
    ld.w    4[sp], r10
    ldsr    r10, RH850_SR_EIPSW
    ld.w    0[sp], r10
    ldsr    r10, RH850_SR_EIPC
    addi    16, sp, sp
    popsp   r4-r31
    popsp   r1-r2
    eiret
    .endm

    .text

    .globl C_SYM(rt_hw_interrupt_disable)
    .type C_SYM(rt_hw_interrupt_disable), @function
C_SYM(rt_hw_interrupt_disable):
    stsr    5, r10, 0
    di
    jmp     [lp]

    .globl C_SYM(rt_hw_interrupt_enable)
    .type C_SYM(rt_hw_interrupt_enable), @function
C_SYM(rt_hw_interrupt_enable):
    andi    RH850_PSW_ID, r6, r10
    bnz     1f
    ei
1:
    jmp     [lp]

/* EP = 1, so that EIRET leaves ISPR as it is */
    .globl C_SYM(rt_hw_context_switch_to)
    .type C_SYM(rt_hw_context_switch_to), @function
C_SYM(rt_hw_context_switch_to):
    rh850_stsr RH850_SR_PSW, r10
    ori     RH850_PSW_EP | RH850_PSW_ID, r10, r10
    ldsr    r10, RH850_SR_PSW
    ld.w    0[r6], sp
    RESTORE_CONTEXT

/* PSW.ID is 1 here, so a pending FPI of this thread is reported as a fault */
    .globl C_SYM(rt_hw_context_switch)
    .type C_SYM(rt_hw_context_switch), @function
C_SYM(rt_hw_context_switch):
#ifdef RH850_FPEC
    synce
    rh850_stsr RH850_SR_FPEC, r10
    andi    RH850_FPEC_FPIVD, r10, r10
    bz      1f
    jr      C_SYM(rh850_fpi_pending)
1:
#endif
    trap    0
    jmp     [lp]

    .globl rh850_trap0_entry
rh850_trap0_entry:
    SAVE_CONTEXT
    st.w    sp, 0[r6]
    ld.w    0[r7], sp
    RESTORE_CONTEXT

/* Return state and the GCC call-used registers of a nested interrupt */
    .macro SAVE_NESTED
#ifdef RH850_SYNCE
    synce
#endif
    pushsp  r1-r2
    pushsp  r5-r19
    pushsp  r30-r31
    add     -16, sp
    rh850_stsr RH850_SR_EIPC, r10
    st.w    r10, 0[sp]
    rh850_stsr RH850_SR_EIPSW, r10
    st.w    r10, 4[sp]
#ifdef RT_USING_FPU
    rh850_stsr RH850_SR_FPSR, r10
    st.w    r10, 8[sp]
    rh850_stsr RH850_SR_FPEPC, r10
    st.w    r10, 12[sp]
#endif
    .endm

    .macro RESTORE_NESTED
#ifdef RT_USING_FPU
    RESTORE_FPU
#endif
    ld.w    4[sp], r10
    ldsr    r10, RH850_SR_EIPSW
    ld.w    0[sp], r10
    ldsr    r10, RH850_SR_EIPC
    addi    16, sp, sp
    popsp   r30-r31
    popsp   r5-r19
    popsp   r1-r2
    eiret
    .endm

    .globl rh850_eiint_entry
rh850_eiint_entry:
    addi    -8, sp, sp
    st.w    r10, 0[sp]
    st.w    r11, 4[sp]
    mov     hilo(C_SYM(rh850_irq_nest)), r10
    ld.w    0[r10], r11
    cmp     r0, r11
    ld.w    0[sp], r10
    ld.w    4[sp], r11
    /* movea keeps the flags of cmp */
    movea   8, sp, sp
    bne     1f

    SAVE_CONTEXT
    mov     hilo(C_SYM(rh850_thread_sp)), r10
    st.w    sp, 0[r10]
    mov     hilo(__stack_top), sp
    br      2f

1:
    SAVE_NESTED

2:
    mov     hilo(C_SYM(rh850_irq_nest)), r10
    ld.w    0[r10], r11
    add     1, r11
    st.w    r11, 0[r10]
    /* EIIC is read before EI: a nested interrupt overwrites it */
    rh850_stsr RH850_SR_EIIC, r6
    jarl    C_SYM(rh850_irq_handle), lp
    mov     hilo(C_SYM(rh850_irq_nest)), r10
    ld.w    0[r10], r11
    add     -1, r11
    st.w    r11, 0[r10]
    cmp     r0, r11
    bne     3f

    mov     hilo(C_SYM(rt_thread_switch_interrupt_flag)), r10
    ld.w    0[r10], r11
    cmp     r0, r11
    be      4f
#ifdef RH850_FPEC
    /* A pending FPI is taken after EIRET: keep the switch for a later exit */
    rh850_stsr RH850_SR_FPEC, r11
    andi    RH850_FPEC_FPIVD, r11, r11
    bnz     4f
#endif
    st.w    r0, 0[r10]
    mov     hilo(C_SYM(rh850_thread_sp)), r10
    ld.w    0[r10], r11
    mov     hilo(C_SYM(rt_interrupt_from_thread)), r10
    ld.w    0[r10], r10
    st.w    r11, 0[r10]
    mov     hilo(C_SYM(rt_interrupt_to_thread)), r10
    ld.w    0[r10], r10
    ld.w    0[r10], sp
    /* EIRET with EP = 0 ends the interrupt in ISPR */
    RESTORE_CONTEXT

4:
    mov     hilo(C_SYM(rh850_thread_sp)), r10
    ld.w    0[r10], sp
    RESTORE_CONTEXT

3:
    RESTORE_NESTED
