/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-07     ZhaoMaosheng the first version
 */

#include "mm_memblock.h"
#include "mm_page.h"
#include "mm_aspace.h"

#define DBG_TAG "mm.memblock"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define INIT_MEMORY_REGIONS 128
#define INIT_RESERVED_REGIONS 128

#define PHYS_ADDR_MAX (~(rt_ubase_t)0)

static struct rt_mmblk_reg _memory_init_regions[INIT_MEMORY_REGIONS];
static struct rt_mmblk_reg _reserved_init_regions[INIT_RESERVED_REGIONS];

struct rt_memblock mmblk_memory = {
    .cnt = 0,
    .max = INIT_MEMORY_REGIONS,
    .regions = _memory_init_regions,
};

struct rt_memblock mmblk_reserved = {
    .cnt = 0,
    .max = INIT_RESERVED_REGIONS,
    .regions = _reserved_init_regions,
};

/* adjust size to avoid exceed physical addr range */
rt_inline rt_size_t _adjust_size(rt_ubase_t base, rt_size_t *size)
{
    return *size = MIN(*size, PHYS_ADDR_MAX - base );
}

static void _memblock_insert_region(struct rt_memblock *memblock,
                                        rt_uint32_t idx, rt_ubase_t base,
                                        rt_size_t size,
                                        enum mmblk_flag flags)
{
    struct rt_mmblk_reg *rgn = &memblock->regions[idx];

    RT_ASSERT(idx <= memblock->cnt && memblock->cnt <= memblock->max);

    if(memblock->cnt == memblock->max)
    {
        LOG_E("No enough space to store region!");
        RT_ASSERT(0);
    }

    rt_memmove(rgn + 1, rgn, (memblock->cnt - idx)*sizeof(*rgn));
    rgn->flags = flags;
    rgn->base = base;
    rgn->size = size;
    memblock->cnt++;
}

static void _memblock_merge_regions(struct rt_memblock *memblock)
{
    rt_uint32_t i = 0;

    /* cnt never goes below 1 */
    while (i < memblock->cnt - 1) {
        struct rt_mmblk_reg *this = &memblock->regions[i];
        struct rt_mmblk_reg *next = &memblock->regions[i + 1];

        RT_ASSERT(this->base + this->size <= next->base);

        /* current region can't merge with next */
        if (this->base + this->size != next->base ||
            this->flags != next->flags) {
            i++;
            continue;
        }

        this->size += next->size;
        /* move forward from next + 1, index of which is i + 2 */
        rt_memmove(next, next + 1, (memblock->cnt - (i + 2)) * sizeof(*next));
        memblock->cnt--;
    }
}

static void _memblock_add_range(struct rt_memblock *memblock,
                                    rt_ubase_t base, rt_size_t size,
                                    enum mmblk_flag flags)
{
    rt_ubase_t end = base + _adjust_size(base, &size);
    struct rt_mmblk_reg *reg = RT_NULL;
    rt_uint32_t i = 0;

    if(!size)
        return ;

    for_each_region(i, memblock, reg)
    {
        rt_ubase_t rbase = reg->base;
        rt_ubase_t rend = rbase + reg->size;

        if(rbase >= end)
            break;
        if(rend <= base)
            continue;

        /* region to add overlaps with reg */
        if(rbase > base)
        {
            if(flags != reg->flags)
                LOG_W("range [%p-%p] with flags %d overlaps region [%p-%p] with different flags %d",\
                            (void*)base, (void*)(base+size), flags, \
                            (void*)rbase, (void*)(rbase+rend), reg->flags);
            _memblock_insert_region(memblock, i++, base, rbase - base, flags);
        }
        base = MIN(rend, end);
    }

    /* insert the remaining portion */
    if(base < end)
    {
        _memblock_insert_region(memblock, i, base, end - base, flags);
    }

    _memblock_merge_regions(memblock);
}

static void _memblock_isolate_range(struct rt_memblock *memblock,
                    rt_ubase_t base, rt_size_t size,
                    rt_uint32_t *start_reg, rt_uint32_t *end_reg)
{
    rt_ubase_t end = base + _adjust_size(base, &size);
    rt_uint32_t idx = 0;
    struct rt_mmblk_reg *reg;

    *start_reg = *end_reg = 0;

    if(!size)
        return ;

    for_each_region(idx, memblock, reg)
    {
        rt_ubase_t rbase = reg->base;
        rt_ubase_t rend = rbase + reg->size;

        if (rbase >= end)
            break;
        if (rend <= base)
            continue;

        /* the beginning of the range separates its respective region */
        if(rbase < base)
        {
            reg->base = base;
            reg->size -= base - rbase;
            _memblock_insert_region(memblock, idx, rbase, base - rbase, reg->flags);
        }
        /* the endpoint of the range separates its respective region */
        else if (rend > end)
        {
            reg->base = end;
            reg->size -= end - rbase;
            _memblock_insert_region(memblock, idx--, rbase, end - rbase, reg->flags);
        }
        /* start and end index of isolated range to return */
        else
        {
            if(!*end_reg)
                *start_reg = idx;
            *end_reg = idx + 1;
        }
    }
}

static void _memblock_setclr_flag(rt_ubase_t base,
                rt_size_t size, rt_bool_t set, enum mmblk_flag flag)
{
    rt_uint32_t i, start_rgn, end_rgn;

    _memblock_isolate_range(&mmblk_memory, base, size, &start_rgn, &end_rgn);

    for (i = start_rgn; i < end_rgn; i++) {
        struct rt_mmblk_reg *reg = &(mmblk_memory.regions[i]);

        if (set)
            reg->flags |= flag;
        else
            reg->flags &= ~flag;
    }

    _memblock_merge_regions(&mmblk_memory);
}

static rt_size_t _memblock_size(struct rt_memblock *memblock)
{
    rt_size_t mmblk_size = 0;

    for(int i = 0; i < memblock->cnt; i++)
    {
        mmblk_size += memblock->regions[i].size;
    }

    return mmblk_size;
}

static void _memblock_dump(struct rt_memblock *memblock)
{
    rt_uint32_t idx = 0;
    struct rt_mmblk_reg *reg;
    rt_ubase_t reg_end = 0;

    for_each_region(idx, memblock, reg)
    {
        reg_end = reg->base + reg->size - 1;
        rt_kprintf("[0x%x]\t[%p-%p] size: 0x%xBytes flags:0x%x\n",
            idx, (void*)reg->base, (void*)reg_end, reg->size, reg->flags);
    }
}

void _next_free_region(rt_uint64_t *idx, enum mmblk_flag flags,
                      rt_ubase_t *out_start, rt_ubase_t *out_end)
{
    rt_uint32_t idx_memory = *idx & 0xffffffff;
    rt_uint32_t idx_reserved = *idx >> 32;

    /* memory related data */
    struct rt_mmblk_reg *m = RT_NULL;
    rt_ubase_t m_start = 0;
    rt_ubase_t m_end = 0;

    /* reserved related data */
    struct rt_mmblk_reg *r = RT_NULL;
    rt_ubase_t r_start = 0;
    rt_ubase_t r_end = 0;

    for (; idx_memory < mmblk_memory.cnt; idx_memory++) {
        m = &mmblk_memory.regions[idx_memory];

        if(m->flags != flags)
            continue;

        m_start = m->base;
        m_end = m->base + m->size;

        for(; idx_reserved < mmblk_reserved.cnt+1; idx_reserved++)
        {
            /*
             * Find the complement of reserved memblock.
             * For example, if reserved memblock is following:
             *
             *  0:[8-16), 1:[32-48), 2:[128-130)
             *
             * The upper 32bit indexes the following regions.
             *
             *  0:[0-8), 1:[16-32), 2:[48-128), 3:[130-MAX)
             *
             * So we can find intersecting region other than excluding.
             */
            r = &mmblk_reserved.regions[idx_reserved];
            r_start = idx_reserved ? r[-1].base + r[-1].size : 0;
            r_end = idx_reserved < mmblk_reserved.cnt ? r->base : PHYS_ADDR_MAX;

            /* reserved */
            if(r_start >= m_end)
                break;

            /* freed memory */
            if(m_start < r_end)
            {
                *out_start = MAX(m_start, r_start);
                *out_end = MIN(m_end, r_end);

                if(m_end <= r_end)
                    idx_memory++;
                else
                    idx_reserved++;

                *idx = idx_memory | (rt_uint64_t)idx_reserved << 32;
                return;
            }
        }
    }

    /* found all regions */
    *idx = ~(rt_uint64_t)0;
}

void rt_memblock_add(rt_ubase_t base, rt_size_t size)
{
    LOG_D("add physical address range [%p-%p] to overall memory regions\n",\
                                        base, base + size - 1);

    _memblock_add_range(&mmblk_memory, base, size, 0);
}

void rt_memblock_add_ext(rt_ubase_t base, rt_size_t size, enum mmblk_flag flags)
{
    LOG_D("add physical address range [%p-%p] with flag 0x%x" \
            " to overall memory regions\n", base, base + size - 1, flag);

    _memblock_add_range(&mmblk_memory, base, size, flags);
}

void rt_memblock_reserve(rt_ubase_t base, rt_size_t size)
{
    LOG_D("add physical address range [%p-%p] to reserved memory regions\n",\
                                        base, base + size - 1);

    _memblock_add_range(&mmblk_reserved, base, size, 0);
}

rt_size_t rt_memblock_end()
{
    rt_uint64_t i = 0;
    rt_bool_t init = RT_TRUE;
    rt_region_t reg;
    rt_size_t mem = 0;

    /* make sure region is compact */
    _memblock_merge_regions(&mmblk_memory);

    for_each_free_region(i, MEMBLOCK_NONE, &reg.start, &reg.end)
    {
        reg.start -= PV_OFFSET;
        reg.end -= PV_OFFSET;

        if(init)
        {
            rt_page_init(reg);
            init = RT_FALSE;
        }
        else
        {
            rt_page_install(reg);
        }
        rt_kprintf("region [%p-%p] added to buddy system", reg.start, reg.end);
        mem += reg.end - reg.start;
    }

    rt_kprintf("0x%lx(%ld) bytes memory added to buddy system", mem, mem);
    return mem;
}

void rt_memblock_dump()
{
    rt_size_t mem_size = _memblock_size(&mmblk_memory);
    rt_size_t reserved_size = _memblock_size(&mmblk_reserved);

    rt_kprintf("Memory info:\n");
    _memblock_dump(&mmblk_memory);
    rt_kprintf("Total memory size: 0x%lx(%ld) bytes\n", mem_size, mem_size);

    rt_kprintf("\nReserved memory info:\n");
    _memblock_dump(&mmblk_reserved);
    rt_kprintf("Total reserved size: 0x%lx(%ld) bytes\n", reserved_size, reserved_size);
}

void rt_memblock_mark_hotplug(rt_ubase_t base, rt_size_t size)
{
    _memblock_setclr_flag(base, size, 1, MEMBLOCK_HOTPLUG);
}

void rt_memblock_clear_hotplug(rt_ubase_t base, rt_size_t size)
{
    _memblock_setclr_flag(base, size, 0, MEMBLOCK_HOTPLUG);
}

void rt_memblock_mark_nomap(rt_ubase_t base, rt_size_t size)
{
    _memblock_setclr_flag(base, size, 1, MEMBLOCK_NOMAP);
}

void rt_memblock_clear_nomap(rt_ubase_t base, rt_size_t size)
{
    _memblock_setclr_flag(base, size, 0, MEMBLOCK_NOMAP);
}
