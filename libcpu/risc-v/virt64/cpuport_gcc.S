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

.global _rt_thread_entry
_rt_thread_entry:
    LOAD    ra, (sp)    /* texit */
    addi    sp, sp, 8
    LOAD    a0, (sp)    /* parameter */
    addi    sp, sp, 8
    LOAD    t0, (sp)    /* tentry */
    addi    sp, sp, 8
    jr      t0
