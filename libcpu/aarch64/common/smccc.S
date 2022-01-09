/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     GuEe-GUI     The first version
 */

/*
 * smc calling convention call
 */
.macro SMCCC_CALL INS
    stp     x8, x29, [sp,#-16]! /* push the frame pointer (x29) for the purposes of AAPCS64 compatibility */
    \INS    #0
    ldp     x8, x29, [sp], #16

    stp     x0, x1, [x8]
    stp     x2, x3, [x8, #16]
    str     x6, [x8, #32]
    ret
.endm

/*
 * smc call
 */
.globl arm_smc_call
arm_smc_call:
    SMCCC_CALL smc

/*
 * hvc call
 */
.globl arm_hvc_call
arm_hvc_call:
    SMCCC_CALL hvc
