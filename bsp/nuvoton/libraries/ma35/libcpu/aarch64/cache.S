/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author             Notes
 * 2020-03-17     bigmagic           first version
 */

/*
 * void __asm_dcache_level(level)
 *
 * flush or invalidate one level cache.
 *
 * x0: cache level
 * x1: 0 clean & invalidate, 1 invalidate only
 * x2~x9: clobbered
 */
.globl __asm_dcache_level
__asm_dcache_level:
    lsl    x12, x0, #1
    msr    csselr_el1, x12        /* select cache level */
    isb                /* sync change of cssidr_el1 */
    mrs    x6, ccsidr_el1        /* read the new cssidr_el1 */
    and    x2, x6, #7        /* x2 <- log2(cache line size)-4 */
    add    x2, x2, #4        /* x2 <- log2(cache line size) */
    mov    x3, #0x3ff
    and    x3, x3, x6, lsr #3    /* x3 <- max number of #ways */
    clz    w5, w3            /* bit position of #ways */
    mov    x4, #0x7fff
    and    x4, x4, x6, lsr #13    /* x4 <- max number of #sets */
    /* x12 <- cache level << 1 */
    /* x2 <- line length offset */
    /* x3 <- number of cache ways - 1 */
    /* x4 <- number of cache sets - 1 */
    /* x5 <- bit position of #ways */

loop_set:
    mov    x6, x3            /* x6 <- working copy of #ways */
loop_way:
    lsl    x7, x6, x5
    orr    x9, x12, x7        /* map way and level to cisw value */
    lsl    x7, x4, x2
    orr    x9, x9, x7        /* map set number to cisw value */
    tbz    w1, #0, 1f
    dc    isw, x9
    b    2f
1:    dc    cisw, x9        /* clean & invalidate by set/way */
2:    subs    x6, x6, #1        /* decrement the way */
    b.ge    loop_way
    subs    x4, x4, #1        /* decrement the set */
    b.ge    loop_set

    ret

/*
 * void __asm_flush_dcache_all(int invalidate_only)
 *
 * x0: 0 clean & invalidate, 1 invalidate only
 *
 * flush or invalidate all data cache by SET/WAY.
 */
.globl __asm_dcache_all
__asm_dcache_all:
    mov    x1, x0
    dsb    sy
    mrs    x10, clidr_el1        /* read clidr_el1 */
    lsr    x11, x10, #24
    and    x11, x11, #0x7        /* x11 <- loc */
    cbz    x11, finished        /* if loc is 0, exit */
    mov    x15, lr
    mov    x0, #0            /* start flush at cache level 0 */
    /* x0  <- cache level */
    /* x10 <- clidr_el1 */
    /* x11 <- loc */
    /* x15 <- return address */

loop_level:
    lsl    x12, x0, #1
    add    x12, x12, x0        /* x0 <- tripled cache level */
    lsr    x12, x10, x12
    and    x12, x12, #7        /* x12 <- cache type */
    cmp    x12, #2
    b.lt    skip            /* skip if no cache or icache */
    bl    __asm_dcache_level    /* x1 = 0 flush, 1 invalidate */
skip:
    add    x0, x0, #1        /* increment cache level */
    cmp    x11, x0
    b.gt    loop_level

    mov    x0, #0
    msr    csselr_el1, x0        /* restore csselr_el1 */
    dsb    sy
    isb
    mov    lr, x15

finished:
    ret

.globl __asm_flush_dcache_all
__asm_flush_dcache_all:
    mov    x0, #0
    b    __asm_dcache_all

.globl __asm_invalidate_dcache_all
__asm_invalidate_dcache_all:
    mov    x0, #0x1
    b    __asm_dcache_all

/*
 * void __asm_flush_dcache_range(start, end)
 *
 * clean & invalidate data cache in the range
 *
 * x0: start address
 * x1: end address
 */
.globl __asm_flush_dcache_range
__asm_flush_dcache_range:
    mrs    x3, ctr_el0
    lsr    x3, x3, #16
    and    x3, x3, #0xf
    mov    x2, #4
    lsl    x2, x2, x3        /* cache line size */

    /* x2 <- minimal cache line size in cache system */
    sub    x3, x2, #1
    bic    x0, x0, x3
1:    dc    civac, x0    /* clean & invalidate data or unified cache */
    add    x0, x0, x2
    cmp    x0, x1
    b.lo    1b
    dsb    sy
    ret

/*
 * void __asm_invalidate_icache_all(void)
 *
 * invalidate all tlb entries.
 */
.globl __asm_invalidate_icache_all
__asm_invalidate_icache_all:
    ic    ialluis
    isb    sy
    ret

.globl __asm_flush_l3_cache
__asm_flush_l3_cache:
    mov    x0, #0            /* return status as success */
    ret