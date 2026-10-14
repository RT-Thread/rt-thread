/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif
#define REGBYTES 8
#define STORE sd
#define LOAD ld

#include <rtconfig.h>
#include "vector_encoding.h"
#include "rvv_context.h"

    .text
    .align 2

    /* Test-only helpers; SAVE_VECTOR must not change the caller's controls. */
    .globl rt_hw_vector_ctx_save
    .type rt_hw_vector_ctx_save, @function
rt_hw_vector_ctx_save:
    csrrci  a3, sstatus, 2
    li      t0, SSTATUS_VS
    csrs    sstatus, t0
    SAVE_VECTOR a0
    RESTORE_VECTOR a0
    csrw    sstatus, a3
    ret
    .size rt_hw_vector_ctx_save, . - rt_hw_vector_ctx_save

    .globl rt_hw_vector_ctx_restore
    .type rt_hw_vector_ctx_restore, @function
rt_hw_vector_ctx_restore:
    csrrci  a3, sstatus, 2
    li      t0, SSTATUS_VS
    csrs    sstatus, t0
    RESTORE_VECTOR a0
    csrw    sstatus, a3
    ret
    .size rt_hw_vector_ctx_restore, . - rt_hw_vector_ctx_restore
