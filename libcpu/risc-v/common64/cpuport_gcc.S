/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     RT-Thread    the first version
 */

#include "cpuport.h"
#include "stackframe.h"
#include "asm-generic.h"

START_POINT(_rt_thread_entry)
    LOAD    ra, REGBYTES(sp)    /* thread exit */
    addi    sp, sp, 2 * REGBYTES
    LOAD    a0, (sp)            /* parameter */
    LOAD    t0, REGBYTES(sp)    /* tentry */
    addi    sp, sp, 2 * REGBYTES
    mv      s1, ra
    jalr    t0
    jalr    s1
    j       .           /* never here */
START_POINT_END(_rt_thread_entry)
