/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
/**
 * SMCCC v0.2
 * ARM DEN0028E chapter 2.6
 */
    .macro SMCCC instr
    stp    x29, x30, [sp, #-16]!
    mov    x29, sp
    \instr    #0
    // store in arm_smccc_res
    ldr    x4, [sp, #16]
    stp    x0, x1, [x4, #0]
    stp    x2, x3, [x4, #16]
1:  
    ldp    x29, x30, [sp], #16
    ret
    .endm

.global arm_smccc_smc
arm_smccc_smc:
    SMCCC    smc

.global arm_smccc_hvc
arm_smccc_hvc:
    SMCCC    hvc
