/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include <mips.h>

    .section ".text", "ax"
    .set noreorder

    .globl  rt_cpu_early_init
rt_cpu_early_init:
_cache_init:
    /* init caches, assumes a 4way * 128set * 32byte I/D cache */
    mtc0    zero, CP0_TAGLO  /* TAGLO reg */
    mtc0    zero, CP0_TAGHI  /* TAGHI reg */
    li      t0, 3            /* enable cache for kseg0 accesses */
    mtc0    t0, CP0_CONFIG   /* CONFIG reg */
    la      t0, 0x80000000   /* an idx op should use an unmappable address */
    ori     t1, t0, 0x4000   /* 16kB cache */

_cache_loop:
    cache   0x8, 0(t0)       /* index store icache tag */
    cache   0x9, 0(t0)       /* index store dcache tag */
    bne     t0, t1, _cache_loop
    addiu   t0, t0, 0x20     /* 32 bytes per cache line */
    nop

    /* invalidate BTB */
    mfc0    t0, CP0_CONFIG
    nop
    ori     t0, 2
    mtc0    t0, CP0_CONFIG
    nop

    jr	ra
    nop