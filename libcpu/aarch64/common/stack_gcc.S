/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Jesven       the first version
 * 2023-06-24     Shell        Support debug frame for user thread
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "rtconfig.h"
#include "asm-generic.h"
#include "asm-fpu.h"
#include "armv8.h"

.section .text

START_POINT(_thread_start)
    mov     x0, x21
    blr     x19
    mov     x29, #0
    blr     x20
    b       .   /* never here */
START_POINT_END(_thread_start)
