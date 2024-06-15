/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Jesven       the first version
 * 2023-07-13     GuEe-GUI     append Q16 ~ Q31
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
    STR Q16, [\reg, #-0x10]!
    STR Q17, [\reg, #-0x10]!
    STR Q18, [\reg, #-0x10]!
    STR Q19, [\reg, #-0x10]!
    STR Q20, [\reg, #-0x10]!
    STR Q21, [\reg, #-0x10]!
    STR Q22, [\reg, #-0x10]!
    STR Q23, [\reg, #-0x10]!
    STR Q24, [\reg, #-0x10]!
    STR Q25, [\reg, #-0x10]!
    STR Q26, [\reg, #-0x10]!
    STR Q27, [\reg, #-0x10]!
    STR Q28, [\reg, #-0x10]!
    STR Q29, [\reg, #-0x10]!
    STR Q30, [\reg, #-0x10]!
    STR Q31, [\reg, #-0x10]!
.endm
.macro RESTORE_FPU, reg
    LDR Q31, [\reg], #0x10
    LDR Q30, [\reg], #0x10
    LDR Q29, [\reg], #0x10
    LDR Q28, [\reg], #0x10
    LDR Q27, [\reg], #0x10
    LDR Q26, [\reg], #0x10
    LDR Q25, [\reg], #0x10
    LDR Q24, [\reg], #0x10
    LDR Q23, [\reg], #0x10
    LDR Q22, [\reg], #0x10
    LDR Q21, [\reg], #0x10
    LDR Q20, [\reg], #0x10
    LDR Q19, [\reg], #0x10
    LDR Q18, [\reg], #0x10
    LDR Q17, [\reg], #0x10
    LDR Q16, [\reg], #0x10
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
