/*
 * File      : mips_cache_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016Äê9ÔÂ19ÈÕ     Urey         the first version
 */

#ifndef __ASSEMBLY__
#	define	__ASSEMBLY__
#endif

#include "../common/mips.h"

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
