/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-10     Piyush Patle  Add RVV restore regression probe
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
    .option push
    .option arch, +v

    /* a0: expected frame, a1: observed frame, a2: caller's vector frame. */
    .globl rvv_vstart_probe
    .type rvv_vstart_probe, @function
rvv_vstart_probe:
    /* Keep interrupts masked until the caller's complete state is restored. */
    csrrc   a3, sstatus, 2
    li      t0, SSTATUS_VS
    csrs    sstatus, t0
    SAVE_VECTOR a2

    RESTORE_VECTOR a0
    /* SAVE_VECTOR records vstart before issuing any vector instruction. */
    SAVE_VECTOR a1

    RESTORE_VECTOR a2
    csrw    sstatus, a3
    ret
    .size rvv_vstart_probe, . - rvv_vstart_probe

    .option pop
