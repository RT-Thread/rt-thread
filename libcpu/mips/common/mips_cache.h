/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-09-07     Urey         the first version
 */

#ifndef _MIPS_CACHE_H_
#define _MIPS_CACHE_H_

#ifndef __ASSEMBLER__
#include <rtdef.h>
#include <mips_cfg.h>

/*
 * Cache Operations available on all MIPS processors with R4000-style caches
 */
#define INDEX_INVALIDATE_I      0x00
#define INDEX_WRITEBACK_INV_D   0x01
#define INDEX_LOAD_TAG_I        0x04
#define INDEX_LOAD_TAG_D        0x05
#define INDEX_STORE_TAG_I       0x08
#define INDEX_STORE_TAG_D       0x09
#define HIT_INVALIDATE_I        0x10
#define HIT_INVALIDATE_D        0x11
#define HIT_WRITEBACK_INV_D     0x15

/*
 *The lock state is cleared by executing an Index
Invalidate, Index Writeback Invalidate, Hit
Invalidate, or Hit Writeback Invalidate
operation to the locked line, or via an Index
Store Tag operation with the lock bit reset in
the TagLo register.
 */
#define FETCH_AND_LOCK_I        0x1c
#define FETCH_AND_LOCK_D        0x1d


enum dma_data_direction
{
    DMA_BIDIRECTIONAL = 0,
    DMA_TO_DEVICE = 1,
    DMA_FROM_DEVICE = 2,
    DMA_NONE = 3,
};

/*
 * R4000-specific cacheops
 */
#define CREATE_DIRTY_EXCL_D     0x0d
#define FILL                    0x14
#define HIT_WRITEBACK_I         0x18
#define HIT_WRITEBACK_D         0x19

/*
 * R4000SC and R4400SC-specific cacheops
 */
#define INDEX_INVALIDATE_SI     0x02
#define INDEX_WRITEBACK_INV_SD  0x03
#define INDEX_LOAD_TAG_SI       0x06
#define INDEX_LOAD_TAG_SD       0x07
#define INDEX_STORE_TAG_SI      0x0A
#define INDEX_STORE_TAG_SD      0x0B
#define CREATE_DIRTY_EXCL_SD    0x0f
#define HIT_INVALIDATE_SI       0x12
#define HIT_INVALIDATE_SD       0x13
#define HIT_WRITEBACK_INV_SD    0x17
#define HIT_WRITEBACK_SD        0x1b
#define HIT_SET_VIRTUAL_SI      0x1e
#define HIT_SET_VIRTUAL_SD      0x1f

/*
 * R5000-specific cacheops
 */
#define R5K_PAGE_INVALIDATE_S   0x17

/*
 * RM7000-specific cacheops
 */
#define PAGE_INVALIDATE_T       0x16

/*
 * R10000-specific cacheops
 *
 * Cacheops 0x02, 0x06, 0x0a, 0x0c-0x0e, 0x16, 0x1a and 0x1e are unused.
 * Most of the _S cacheops are identical to the R4000SC _SD cacheops.
 */
#define INDEX_WRITEBACK_INV_S   0x03
#define INDEX_LOAD_TAG_S        0x07
#define INDEX_STORE_TAG_S       0x0B
#define HIT_INVALIDATE_S        0x13
#define CACHE_BARRIER           0x14
#define HIT_WRITEBACK_INV_S     0x17
#define INDEX_LOAD_DATA_I       0x18
#define INDEX_LOAD_DATA_D       0x19
#define INDEX_LOAD_DATA_S       0x1b
#define INDEX_STORE_DATA_I      0x1c
#define INDEX_STORE_DATA_D      0x1d
#define INDEX_STORE_DATA_S      0x1f

#define cache_op(op, addr)          \
    __asm__ __volatile__(        \
        ".set   push\n"             \
        ".set   noreorder\n"        \
        ".set   mips3\n"            \
        "cache  %0, %1\n"           \
        ".set   pop\n"              \
        :                           \
        : "i" (op), "R" (*(unsigned char *)(addr)))

#define cache16_unroll32(base, op)                  \
    __asm__ __volatile__(                       \
    "   .set noreorder                  \n" \
    "   .set mips3                  \n" \
    "   cache %1, 0x000(%0); cache %1, 0x010(%0)    \n" \
    "   cache %1, 0x020(%0); cache %1, 0x030(%0)    \n" \
    "   cache %1, 0x040(%0); cache %1, 0x050(%0)    \n" \
    "   cache %1, 0x060(%0); cache %1, 0x070(%0)    \n" \
    "   cache %1, 0x080(%0); cache %1, 0x090(%0)    \n" \
    "   cache %1, 0x0a0(%0); cache %1, 0x0b0(%0)    \n" \
    "   cache %1, 0x0c0(%0); cache %1, 0x0d0(%0)    \n" \
    "   cache %1, 0x0e0(%0); cache %1, 0x0f0(%0)    \n" \
    "   cache %1, 0x100(%0); cache %1, 0x110(%0)    \n" \
    "   cache %1, 0x120(%0); cache %1, 0x130(%0)    \n" \
    "   cache %1, 0x140(%0); cache %1, 0x150(%0)    \n" \
    "   cache %1, 0x160(%0); cache %1, 0x170(%0)    \n" \
    "   cache %1, 0x180(%0); cache %1, 0x190(%0)    \n" \
    "   cache %1, 0x1a0(%0); cache %1, 0x1b0(%0)    \n" \
    "   cache %1, 0x1c0(%0); cache %1, 0x1d0(%0)    \n" \
    "   cache %1, 0x1e0(%0); cache %1, 0x1f0(%0)    \n" \
    "   .set mips0                  \n" \
    "   .set reorder                    \n" \
        :                           \
        : "r" (base),                       \
          "i" (op));


static inline void flush_icache_line_indexed(rt_ubase_t addr)
{
    cache_op(INDEX_INVALIDATE_I, addr);
}

static inline void flush_dcache_line_indexed(rt_ubase_t addr)
{
    cache_op(INDEX_WRITEBACK_INV_D, addr);
}

static inline void flush_icache_line(rt_ubase_t addr)
{
    cache_op(HIT_INVALIDATE_I, addr);
}

static inline void lock_icache_line(rt_ubase_t addr)
{
    cache_op(FETCH_AND_LOCK_I, addr);
}

static inline void lock_dcache_line(rt_ubase_t addr)
{
    cache_op(FETCH_AND_LOCK_D, addr);
}

static inline void flush_dcache_line(rt_ubase_t addr)
{
    cache_op(HIT_WRITEBACK_INV_D, addr);
}

static inline void invalidate_dcache_line(rt_ubase_t addr)
{
    cache_op(HIT_INVALIDATE_D, addr);
}
static inline void blast_dcache16(void)
{
    rt_ubase_t start = KSEG0BASE;
    rt_ubase_t end = start + g_mips_core.dcache_size;
    rt_ubase_t addr;

    for (addr = start; addr < end; addr += g_mips_core.dcache_line_size)
        cache16_unroll32(addr, INDEX_WRITEBACK_INV_D);
}

static inline void inv_dcache16(void)
{
    rt_ubase_t start = KSEG0BASE;
    rt_ubase_t end = start + g_mips_core.dcache_size;
    rt_ubase_t addr;

    for (addr = start; addr < end; addr += g_mips_core.dcache_line_size)
        cache16_unroll32(addr, HIT_INVALIDATE_D);
}

static inline void blast_icache16(void)
{
    rt_ubase_t start = KSEG0BASE;
    rt_ubase_t end = start + g_mips_core.icache_size;
    rt_ubase_t addr;

    for (addr = start; addr < end; addr += g_mips_core.icache_line_size)
        cache16_unroll32(addr, INDEX_INVALIDATE_I);
}

void r4k_cache_init(void);
void r4k_cache_flush_all(void);
void r4k_icache_flush_all(void);
void r4k_icache_flush_range(rt_ubase_t addr, rt_ubase_t size);
void r4k_icache_lock_range(rt_ubase_t addr, rt_ubase_t size);
void r4k_dcache_inv(rt_ubase_t addr, rt_ubase_t size);
void r4k_dcache_wback_inv(rt_ubase_t addr, rt_ubase_t size);
void r4k_dma_cache_sync(rt_ubase_t addr, rt_size_t size, enum dma_data_direction direction);
#endif

#endif /* _MIPS_CACHE_H_ */
