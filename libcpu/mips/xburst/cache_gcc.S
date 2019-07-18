/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 * 2019-07-19     Zhou Yanjie  clean up code
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "../common/mips_def.h"
#include "../common/mipsregs.h"
#include "../common/stackframe.h"

    .text
    .set noreorder

    .globl  cache_init
    .ent    cache_init
cache_init:
    .set    noreorder
    mtc0    zero, CP0_TAGLO
    move    t0, a0                  // cache total size
    move    t1, a1                  // cache line size
    li      t2, 0x80000000
    addu    t3, t0, t2

_cache_init_loop:
    cache   8, 0(t2)                // icache_index_store_tag
    cache   9, 0(t2)                // dcache_index_store_tag
    addu    t2, t1
    bne     t2, t3, _cache_init_loop
    nop

    mfc0    t0, CP0_CONFIG
    li      t1, 0x7
    not     t1
    and     t0, t0, t1
    or      t0, 0x3                 // cacheable, noncoherent, write-back, write allocate
    mtc0    t0, CP0_CONFIG

    jr      ra
    nop

    .set    reorder
    .end    cache_init
