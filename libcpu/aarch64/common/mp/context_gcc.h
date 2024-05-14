/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-25     Shell        Trimming unecessary ops and
 *                             improve the performance of ctx switch
 */

#ifndef __ARM64_CONTEXT_H__
#define __ARM64_CONTEXT_H__

#include "../include/context_gcc.h"

#include <rtconfig.h>
#include <asm-generic.h>
#include <asm-fpu.h>
#include <armv8.h>

.macro RESTORE_CONTEXT_SWITCH
    /* Set the SP to point to the stack of the task being restored. */
    mov     sp, x0

    _RESTORE_CONTEXT_SWITCH
.endm

#endif /* __ARM64_CONTEXT_H__ */
