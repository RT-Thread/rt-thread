/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     RT-Thread    the first version
 */

#include "asm-generic.h"

    .section ".text","ax"

START_POINT(_thread_start)
    REG_L   ra, SZREG(sp)       /* thread exit */
    addi    sp, sp, 2 * SZREG
    REG_L   a0, (sp)            /* parameter */
    REG_L   t0, SZREG(sp)       /* tentry */
    addi    sp, sp, 2 * SZREG
    mv      s1, ra
    jalr    t0
    jalr    s1
    j       .                   /* never here */
START_POINT_END(_thread_start)
