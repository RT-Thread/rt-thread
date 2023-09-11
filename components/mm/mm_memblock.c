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

static struct rt_mmblk_reg _memreg[INIT_MEMORY_REGIONS];
static struct rt_mmblk_reg _resreg[INIT_RESERVED_REGIONS];

struct rt_memblock mmblk_memory = {
    .hint_idx = 1,
    .max = INIT_MEMORY_REGIONS,
    .regions = &_memreg[0],
};

struct rt_memblock mmblk_reserved = {
    .hint_idx = 1,
    .max = INIT_RESERVED_REGIONS,
    .regions = &_resreg[0],
};

/* adjust size to avoid exceed physical addr range */
rt_inline rt_size_t _adjust_size(rt_ubase_t base, rt_size_t *size)
{
    return *size = MIN(*size, PHYS_ADDR_MAX - base );
}

static struct rt_mmblk_reg *_dummy_malloc(struct rt_memblock *memblock, struct rt_mmblk_reg *prev)
{
    struct rt_mmblk_reg *ret = RT_NULL;
    
    for(int i = memblock->hint_idx; i < memblock->max; i++)
    {
        if(memblock->regions[i].size == 0)
        {
            memblock->regions[i].next = prev->next;
            prev->next = &memblock->regions[i];
            /* mark as alloced */
            memblock->regions[i].size = 1;
            memblock->hint_idx = i + 1;
            ret = &memblock->regions[i];
            break;
        }
    }

    if(ret == RT_NULL)
    {
        for(int i = 1; i < memblock->hint_idx; i++)
        {
            if(memblock->regions[i].size == 0)
            {
                memblock->regions[i].next = prev->next;
                prev->next = &memblock->regions[i];
                /* mark as alloced */
                memblock->regions[i].size = 1;
                memblock->hint_idx = i + 1;
                ret = &memblock->regions[i];
                break;
            } 
        }
    }

    return ret;
}

static void _dummy_free(struct rt_memblock *memblock, struct rt_mmblk_reg *prev)
{   
    if(prev->next == RT_NULL)
        return;

    prev->next->size = 0;
    prev->next = prev->next->next;
}

static void _reg_insert_after(struct rt_memblock *memblock, struct rt_mmblk_reg *reg,
                            rt_ubase_t base, rt_size_t size, enum mmblk_flag flags)
{
    struct rt_mmblk_reg *new_reg = _dummy_malloc(memblock, reg);

    if(!new_reg)
    {
        LOG_E("No enough space");
        RT_ASSERT(0);
    }

    new_reg->base = base;
    new_reg->size = size;
    new_reg->flags = flags;
}

static void _reg_remove_after(struct rt_memblock *memblock, struct rt_mmblk_reg *reg)
{
    _dummy_free(memblock, reg);
}

static void _memblock_merge_regions(struct rt_memblock *memblock)
{
    struct rt_mmblk_reg *reg = RT_NULL;

    /* test if a memblock can merge with next */
    for_each_region(memblock, reg)
    {
        /* skip the guard node */
        if(reg->size == 0)
            continue;
        
        /* 'reg' can merge with next*/
        while (reg->next && 
            reg->flags == reg->next->flags &&
            reg->base + reg->size == reg->next->base)
        {
            reg->size += reg->next->size;
            _reg_remove_after(memblock, reg);
        }

        /* avoid having 'reg' as the last range after executing '_reg_remove_after' */
        if(!reg->next)
            return;
    }
}

static void _memblock_add_range(struct rt_memblock *memblock,
                                    rt_ubase_t base, rt_size_t size,
                                    enum mmblk_flag flags)
{
    rt_ubase_t end = base + _adjust_size(base, &size);
    struct rt_mmblk_reg *reg = RT_NULL;

    if(!size)
        return ;

    for_each_region(memblock, reg)
    {
        rt_ubase_t rbase = reg->next->base;
        rt_ubase_t rend = rbase + reg->next->size;

        if(rbase >= end)
            break;
        if(rend <= base)
            continue;

        /* region to add overlaps with reg */
        if(rbase > base)
        {
            if(flags != reg->next->flags)
            {
                LOG_W("range [%p-%p) with flags %d overlaps region [%p-%p) with different flags %d",\
                            (void*)base, (void*)(base + size), flags, \
                            (void*)rbase, (void*)(rend), reg->next->flags);
                _reg_insert_after(memblock, reg, base, rbase - base, flags);
            }
            else
            {
                reg->next->base = base;
                reg->next->size += rbase - base;
            }   
        }
        base = MIN(rend, end);
    }

    /* insert the remaining portion */
    if(base < end)
    {
        _reg_insert_after(memblock, reg, base, end - base, flags);
    }

    _memblock_merge_regions(memblock);
}

/* [*start_reg, *end_reg) is the isolated range */
static void _memblock_isolate_range(struct rt_memblock *memblock,
                    rt_ubase_t base, rt_size_t size,
                    struct rt_mmblk_reg **start_reg, struct rt_mmblk_reg **end_reg)
{
    rt_ubase_t end = base + _adjust_size(base, &size);
    struct rt_mmblk_reg *reg = RT_NULL;

    *start_reg = *end_reg = RT_NULL;

    if(!size)
        return ;

    for_each_region(memblock, reg)
    {
        rt_ubase_t rbase = reg->next->base;
        rt_ubase_t rend = rbase + reg->next->size;

        if (rbase >= end)
            break;
        if (rend <= base)
            continue;

        /* the beginning of the range separates its respective region */
        if(rbase < base)
        {
            reg->next->base = base;
            reg->next->size -= base - rbase;
            _reg_insert_after(memblock, reg, rbase, base - rbase, reg->flags);
        }
        /* the endpoint of the range separates its respective region */
        else if (rend > end)
        {
            reg->next->base = end;
            reg->next->size -= end - rbase;
            _reg_insert_after(memblock, reg, rbase, end - rbase, reg->flags);
            *end_reg = reg->next->next;
            break;
        }
        /* reg->next is fully contained in range */
        else
        {
            if(!*end_reg)
                *start_reg = reg->next;
            *end_reg = reg->next->next;
        }
    }
}

static void _memblock_setclr_flag(struct rt_memblock *memblock, 
                    rt_ubase_t base, rt_size_t size, 
                    rt_bool_t set, enum mmblk_flag flag)
{
    struct rt_mmblk_reg *start_reg = RT_NULL, *end_reg = RT_NULL;

    _memblock_isolate_range(memblock, base, size, &start_reg, &end_reg);

    if(start_reg == RT_NULL)
        return;

    RT_ASSERT(end_reg != RT_NULL);

    for (struct rt_mmblk_reg *iter = start_reg; iter != end_reg; iter = iter->next) {
        if (set)
            iter->flags |= flag;
        else
            iter->flags &= ~flag;
    }

    _memblock_merge_regions(memblock);
}

static rt_size_t _memblock_size(struct rt_memblock *memblock)
{
    rt_size_t size = 0;
    struct rt_mmblk_reg *reg = RT_NULL;

    for_each_region(memblock, reg)
    {
        size += reg->size;
    }
    return size;
}

static void _memblock_dump(struct rt_memblock *memblock)
{
    rt_uint32_t idx = 0;
    struct rt_mmblk_reg *reg;
    rt_ubase_t reg_end = 0, reg_begin = 0, reg_size = 0;

    for_each_region(memblock, reg)
    {
        reg_begin = reg->next->base;
        reg_end = reg->next->base + reg->next->size;
        reg_size = reg->next->size;
        rt_kprintf("[0x%x]\t[%p-%p) size: 0x%xBytes flags:0x%x\n",
            idx, (void*)reg_begin, (void*)reg_end, reg_size, reg->next->flags);
    }
}

/**
 * @brief Find the next free region
 * The free region is within the memory regions and not within the reserved regions.
 * The current free region is identified by *m and *r
 * 
 * @param m *m point to the current memory region
 * @param r *r point to the current reserved region
 * @param flags flags of desired regions
 * @param out_strat *out_start stores the returned free region's beginning
 * @param out_end *out_end stores the ending of the returned free region
 */
void _next_free_region(struct rt_mmblk_reg **m, struct rt_mmblk_reg **r, enum mmblk_flag flags,
                      rt_ubase_t *out_start, rt_ubase_t *out_end)
{
    /* memory related data */
    rt_ubase_t m_start = 0;
    rt_ubase_t m_end = 0;

    /* reserved related data */
    rt_ubase_t r_start = 0;
    rt_ubase_t r_end = 0;

    for (; *m != RT_NULL; *m = (*m)->next) 
    {
        if((*m)->flags != flags)
            continue;

        m_start = (*m)->base;
        m_end = (*m)->base + (*m)->size;

        for(; *r != RT_NULL; *r = (*r)->next)
        {
            /*
             * r started with _resreg_guard
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
            r_start = (*r)->base + (*r)->size;
            r_end = ((*r)->next) ? (*r)->next->base : PHYS_ADDR_MAX;

            /* reserved memory */
            if(r_start >= m_end)
                break;

            /* free memory */
            if(m_start < r_end)
            {
                *out_start = MAX(m_start, r_start);
                *out_end = MIN(m_end, r_end);

                if(m_end <= r_end)
                    *m = (*m)->next;
                else
                    *r = (*r)->next;
                return;
            }
        }
    }

    /* all regions found */
    *m = mmblk_memory.regions;
}

void rt_memblock_add(rt_ubase_t base, rt_size_t size)
{
    LOG_D("add physical address range [%p-%p) to overall memory regions\n",\
                                        base, base + size);

    _memblock_add_range(&mmblk_memory, base, size, 0);
}

void rt_memblock_add_ext(rt_ubase_t base, rt_size_t size, enum mmblk_flag flags)
{
    LOG_D("add physical address range [%p-%p) with flag 0x%x" \
            " to overall memory regions\n", base, base + size, flag);

    _memblock_add_range(&mmblk_memory, base, size, flags);
}

void rt_memblock_reserve(rt_ubase_t base, rt_size_t size)
{
    LOG_D("add physical address range [%p-%p) to reserved memory regions\n",\
                                        base, base + size);

    _memblock_add_range(&mmblk_reserved, base, size, 0);
}

void rt_memblock_reserve_ext(rt_ubase_t base, rt_size_t size, enum mmblk_flag flags)
{
    LOG_D("add physical address range [%p-%p) with flag 0x%x" \
            " to reserved memory regions\n",\
                                        base, base + size);

    _memblock_add_range(&mmblk_reserved, base, size, flags);
}

rt_size_t rt_memblock_end()
{
    rt_bool_t init = RT_TRUE;
    rt_size_t mem = 0;
    rt_ubase_t start = 0, end = 0;
    rt_region_t reg = {
        .start = 0,
        .end = 0,
    };

    /* make sure region is compact */
    _memblock_merge_regions(&mmblk_memory);

    struct rt_mmblk_reg *m, *r;

    for_each_free_region(m, r, MEMBLOCK_NONE, &start, &end)
    {
        reg.start = (rt_size_t)start - PV_OFFSET;
        reg.end = (rt_size_t)end - PV_OFFSET;

        if(init)
        {
            rt_page_init(reg);
            init = RT_FALSE;
        }
        else
        {
            rt_page_install(reg);
        }
        LOG_D("region [%p-%p) added to buddy system\n", reg.start, reg.end);
        mem += reg.end - reg.start;
    }

    LOG_D("0x%lx(%ld) bytes memory added to buddy system\n", mem, mem);
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
    rt_kprintf("Total reserved size: 0x%lx(%ld) bytes\n\n", reserved_size, reserved_size);
}

void rt_memblock_mark_hotplug(rt_ubase_t base, rt_size_t size)
{
    _memblock_setclr_flag(&mmblk_memory, base, size, 1, MEMBLOCK_HOTPLUG);
}

void rt_memblock_clear_hotplug(rt_ubase_t base, rt_size_t size)
{
    _memblock_setclr_flag(&mmblk_memory, base, size, 0, MEMBLOCK_HOTPLUG);
}

void rt_memblock_mark_nomap(rt_ubase_t base, rt_size_t size)
{
    _memblock_setclr_flag(&mmblk_memory, base, size, 1, MEMBLOCK_NOMAP);
}

void rt_memblock_clear_nomap(rt_ubase_t base, rt_size_t size)
{
    _memblock_setclr_flag(&mmblk_memory, base, size, 0, MEMBLOCK_NOMAP);
}
