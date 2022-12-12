/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Jesven       the first version
 */

.macro SAVE_FPU, reg
    STR Q0, [\reg, #-0x10]!
    STR Q1, [\reg, #-0x10]!
    STR Q2, [\reg, #-0x10]!
    STR Q3, [\reg, #-0x10]!
    STR Q4, [\reg, #-0x10]!
    STR Q5, [\reg, #-0x10]!
    STR Q6, [\reg, #-0x10]!
    STR Q7, [\reg, #-0x10]!
    STR Q8, [\reg, #-0x10]!
    STR Q9, [\reg, #-0x10]!
    STR Q10, [\reg, #-0x10]!
    STR Q11, [\reg, #-0x10]!
    STR Q12, [\reg, #-0x10]!
    STR Q13, [\reg, #-0x10]!
    STR Q14, [\reg, #-0x10]!
    STR Q15, [\reg, #-0x10]!
.endm

.macro RESTORE_FPU, reg
    LDR Q15, [\reg], #0x10
    LDR Q14, [\reg], #0x10
    LDR Q13, [\reg], #0x10
    LDR Q12, [\reg], #0x10
    LDR Q11, [\reg], #0x10
    LDR Q10, [\reg], #0x10
    LDR Q9, [\reg], #0x10
    LDR Q8, [\reg], #0x10
    LDR Q7, [\reg], #0x10
    LDR Q6, [\reg], #0x10
    LDR Q5, [\reg], #0x10
    LDR Q4, [\reg], #0x10
    LDR Q3, [\reg], #0x10
    LDR Q2, [\reg], #0x10
    LDR Q1, [\reg], #0x10
    LDR Q0, [\reg], #0x10
.endm
