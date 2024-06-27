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
#ifndef __ARM64_ASM_FPU_H__
#define __ARM64_ASM_FPU_H__

.macro SAVE_FPU, reg
    str q0, [\reg, #-0x10]!
    str q1, [\reg, #-0x10]!
    str q2, [\reg, #-0x10]!
    str q3, [\reg, #-0x10]!
    str q4, [\reg, #-0x10]!
    str q5, [\reg, #-0x10]!
    str q6, [\reg, #-0x10]!
    str q7, [\reg, #-0x10]!
    str q8, [\reg, #-0x10]!
    str q9, [\reg, #-0x10]!
    str q10, [\reg, #-0x10]!
    str q11, [\reg, #-0x10]!
    str q12, [\reg, #-0x10]!
    str q13, [\reg, #-0x10]!
    str q14, [\reg, #-0x10]!
    str q15, [\reg, #-0x10]!
    str q16, [\reg, #-0x10]!
    str q17, [\reg, #-0x10]!
    str q18, [\reg, #-0x10]!
    str q19, [\reg, #-0x10]!
    str q20, [\reg, #-0x10]!
    str q21, [\reg, #-0x10]!
    str q22, [\reg, #-0x10]!
    str q23, [\reg, #-0x10]!
    str q24, [\reg, #-0x10]!
    str q25, [\reg, #-0x10]!
    str q26, [\reg, #-0x10]!
    str q27, [\reg, #-0x10]!
    str q28, [\reg, #-0x10]!
    str q29, [\reg, #-0x10]!
    str q30, [\reg, #-0x10]!
    str q31, [\reg, #-0x10]!
.endm
.macro RESTORE_FPU, reg
    ldr q31, [\reg], #0x10
    ldr q30, [\reg], #0x10
    ldr q29, [\reg], #0x10
    ldr q28, [\reg], #0x10
    ldr q27, [\reg], #0x10
    ldr q26, [\reg], #0x10
    ldr q25, [\reg], #0x10
    ldr q24, [\reg], #0x10
    ldr q23, [\reg], #0x10
    ldr q22, [\reg], #0x10
    ldr q21, [\reg], #0x10
    ldr q20, [\reg], #0x10
    ldr q19, [\reg], #0x10
    ldr q18, [\reg], #0x10
    ldr q17, [\reg], #0x10
    ldr q16, [\reg], #0x10
    ldr q15, [\reg], #0x10
    ldr q14, [\reg], #0x10
    ldr q13, [\reg], #0x10
    ldr q12, [\reg], #0x10
    ldr q11, [\reg], #0x10
    ldr q10, [\reg], #0x10
    ldr q9, [\reg], #0x10
    ldr q8, [\reg], #0x10
    ldr q7, [\reg], #0x10
    ldr q6, [\reg], #0x10
    ldr q5, [\reg], #0x10
    ldr q4, [\reg], #0x10
    ldr q3, [\reg], #0x10
    ldr q2, [\reg], #0x10
    ldr q1, [\reg], #0x10
    ldr q0, [\reg], #0x10
.endm

#endif /* __ARM64_ASM_FPU_H__ */
