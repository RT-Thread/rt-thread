/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 * 2010-09-11     bernard      port to Loongson SoC3210
 * 2011-08-08     lgnq         port to Loongson LS1B
 * 2015-07-08     chinesebear  port to Loongson LS1C
 * 2019-07-19     Zhou Yanjie  clean up code
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include <mips.h>
#include "cache.h"

    .ent	cache_init
    .global cache_init
    .set noreorder
cache_init:
        move t1,ra
####part 2####
cache_detect_4way:
        mfc0    t4, CP0_CONFIG
        andi    t5, t4, 0x0e00
        srl     t5, t5, 9     #ic
        andi    t6, t4, 0x01c0
        srl     t6, t6, 6     #dc
        addiu   t8, $0, 1
        addiu   t9, $0, 2
                                #set dcache way
        beq     t6, $0,  cache_d1way
        addiu   t7, $0, 1       #1 way
        beq     t6, t8,  cache_d2way
        addiu   t7, $0, 2       #2 way
        beq     $0, $0, cache_d4way
        addiu   t7, $0, 4       #4 way
cache_d1way:
        beq     $0, $0, 1f
        addiu   t6, t6, 12      #1 way
cache_d2way:
        beq     $0, $0, 1f
        addiu   t6, t6, 11      #2 way
cache_d4way:
        addiu   t6, t6, 10      #4 way (10), 2 way(11), 1 way(12)
1:                              #set icache way
        beq     t5, $0,  cache_i1way
        addiu   t3, $0, 1       #1 way
        beq     t5, t8,  cache_i2way
        addiu   t3, $0, 2       #2 way
        beq     $0, $0, cache_i4way
        addiu   t3, $0, 4       #4 way
cache_i1way:
        beq     $0, $0, 1f
        addiu   t5, t5, 12
cache_i2way:
        beq     $0, $0, 1f
        addiu   t5, t5, 11
cache_i4way:
        addiu   t5, t5, 10      #4 way (10), 2 way(11), 1 way(12)

1:      addiu   t4, $0, 1
        sllv    t6, t4, t6
        sllv    t5, t4, t5
#if 0
    la	t0, memvar
    sw	t7, 0x0(t0) #ways
    sw	t5, 0x4(t0) #icache size
    sw	t6, 0x8(t0) #dcache size
#endif
####part 3####
    .set	mips3
    lui	a0, 0x8000
    addu	a1, $0, t5
    addu	a2, $0, t6
cache_init_d2way:
#a0=0x80000000, a1=icache_size, a2=dcache_size
#a3, v0 and v1 used as local registers
    mtc0	$0, CP0_TAGHI
    addu	v0, $0, a0
    addu	v1, a0, a2
1:	slt	a3, v0, v1
    beq	a3, $0, 1f
    nop
    mtc0	$0, CP0_TAGLO
    beq	t7, 1, 4f
    cache	Index_Store_Tag_D, 0x0(v0)	# 1 way
    beq	t7, 2 ,4f
    cache	Index_Store_Tag_D, 0x1(v0)	# 2 way
    cache	Index_Store_Tag_D, 0x2(v0)	# 4 way
    cache	Index_Store_Tag_D, 0x3(v0)
4:	beq	$0, $0, 1b
    addiu	v0, v0, 0x20
1:
cache_flush_i2way:
    addu	v0, $0, a0
    addu	v1, a0, a1
1:	slt	a3, v0, v1
    beq	a3, $0, 1f
    nop
    beq	t3, 1, 4f
    cache	Index_Invalidate_I, 0x0(v0)	# 1 way
    beq	t3, 2, 4f
    cache	Index_Invalidate_I, 0x1(v0)	# 2 way
    cache	Index_Invalidate_I, 0x2(v0)
    cache	Index_Invalidate_I, 0x3(v0)	# 4 way
4:	beq	$0, $0, 1b
    addiu	v0, v0, 0x20
1:
cache_flush_d2way:
    addu	v0, $0, a0
    addu	v1, a0, a2
1:	slt	a3, v0, v1
    beq	a3, $0, 1f
    nop
    beq	t7, 1, 4f
    cache	Index_Writeback_Inv_D, 0x0(v0) 	#1 way
    beq	t7, 2, 4f
    cache	Index_Writeback_Inv_D, 0x1(v0)	# 2 way
    cache	Index_Writeback_Inv_D, 0x2(v0)
    cache	Index_Writeback_Inv_D, 0x3(v0)	# 4 way
4:	beq	$0, $0, 1b
    addiu	v0, v0, 0x20
1:
cache_init_finish:
    jr	t1
    nop
    .set reorder
    .end cache_init

###########################
#  Enable CPU cache       #
###########################

LEAF(enable_cpu_cache)
    .set noreorder
    mfc0	t0, CP0_CONFIG
    nop
    and		t0, ~0x03
    or		t0, 0x03
    mtc0	t0, CP0_CONFIG
    nop
    .set reorder
    j	ra
END (enable_cpu_cache)
    
###########################
#  disable CPU cache      #
###########################

LEAF(disable_cpu_cache)
    .set noreorder
    mfc0	t0, CP0_CONFIG
    nop
    and		t0, ~0x03
    or 		t0, 0x2
    mtc0	t0, CP0_CONFIG
    nop
    .set reorder
    j	ra
END (disable_cpu_cache)

/**********************************/
/* Invalidate Instruction Cache	  */
/**********************************/
LEAF(Clear_TagLo)
    .set 	noreorder
    mtc0	zero, CP0_TAGLO
    nop
    .set 	reorder
    j		ra
END(Clear_TagLo)

    .set mips3
/**********************************/
/* Invalidate Instruction Cache	  */
/**********************************/
LEAF(Invalidate_Icache_Ls1c)
    .set	noreorder
    cache	Index_Invalidate_I,0(a0)
    cache	Index_Invalidate_I,1(a0)
    cache	Index_Invalidate_I,2(a0)
    cache	Index_Invalidate_I,3(a0)
    .set	reorder
    j		ra
END(Invalidate_Icache_Ls1c)

/**********************************/
/* Invalidate Data Cache		  */
/**********************************/
LEAF(Invalidate_Dcache_ClearTag_Ls1c)
    .set	noreorder
    cache	Index_Store_Tag_D, 0(a0)	# BDSLOT: clear tag
    cache	Index_Store_Tag_D, 1(a0)	# BDSLOT: clear tag
    .set	reorder
    j		ra
END(Invalidate_Dcache_ClearTag_Ls1c)

LEAF(Invalidate_Dcache_Fill_Ls1c)
    .set	noreorder
    cache	Index_Writeback_Inv_D, 0(a0)	# BDSLOT: clear tag
    cache	Index_Writeback_Inv_D, 1(a0)	# BDSLOT: clear tag
    .set	reorder
    j		ra
END(Invalidate_Dcache_Fill_Ls1c)

LEAF(Writeback_Invalidate_Dcache)
    .set noreorder
    cache	Hit_Writeback_Inv_D, (a0)
    .set reorder
    j	ra
END(Writeback_Invalidate_Dcache)
    .set mips0
