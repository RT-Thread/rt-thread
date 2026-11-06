/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#include "rh850_core.h"

/* clang-format off */

    .macro rh850_core_clear_error_regs
    ldsr    r0, RH850_SR_MEA
    ldsr    r0, RH850_SR_MEI
    ldsr    r0, RH850_SR_RBIP
    .endm

/* PSW.CU0 must already be in effect */
    .macro rh850_core_init_fpu tmp
    ldsr    r0, RH850_SR_FPST
    ldsr    r0, RH850_SR_FPCC
    mov     hilo(RH850_FPSR_FS), \tmp
    ldsr    \tmp, RH850_SR_FPSR
    ldsr    r0, RH850_SR_FPEPC
    .endm

    .macro rh850_core_clear_mpu idx, end
    ldsr    r0, RH850_SR_MCA
    ldsr    r0, RH850_SR_MCS
    ldsr    r0, RH850_SR_MCR
    ldsr    r0, RH850_SR_MCI
    mov     r0, \idx
    movea   RH850_CORE_MPU_ENTRIES, r0, \end
1:
    ldsr    \idx, RH850_SR_MPIDX
    ldsr    r0, RH850_SR_MPLA
    ldsr    r0, RH850_SR_MPUA
    ldsr    r0, RH850_SR_MPAT
    add     1, \idx
    cmp     \end, \idx
    bl      1b
    ldsr    r0, RH850_SR_MPIDX
    ldsr    r0, RH850_SR_MPID0
    ldsr    r0, RH850_SR_MPID1
    ldsr    r0, RH850_SR_MPID2
    ldsr    r0, RH850_SR_MPID3
    ldsr    r0, RH850_SR_MPID4
    ldsr    r0, RH850_SR_MPID5
    ldsr    r0, RH850_SR_MPID6
    ldsr    r0, RH850_SR_MPID7
    .endm

    .macro rh850_core_clear_icache
    ldsr    r0, RH850_SR_ICTAGL
    ldsr    r0, RH850_SR_ICTAGH
    ldsr    r0, RH850_SR_ICDATL
    ldsr    r0, RH850_SR_ICDATH
    ldsr    r0, RH850_SR_ICERR
    .endm
