/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-07     zmshahaha    the first version
 */

#include "mm_memblock.h"
#include "mm_page.h"
#include "mm_aspace.h"
#include <mmu.h>

#define DBG_TAG "mm.memblock"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define PHYS_ADDR_MAX (~((rt_size_t)0))

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#ifdef ARCH_CPU_64BIT
#define MIN_BIT   16
#else
#define MIN_BIT   8
#endif

#ifndef RT_INIT_MEMORY_REGIONS
#define RT_INIT_MEMORY_REGIONS 128
#endif

static struct rt_mmblk_reg _regions[RT_INIT_MEMORY_REGIONS];
static int _hint_idx;

static struct rt_memblock mmblk_memory;
static struct rt_memblock mmblk_reserved;

struct rt_memblock *rt_memblock_get_memory(void)
{
    return &mmblk_memory;
}

struct rt_memblock *rt_memblock_get_reserved(void)
{
    return &mmblk_reserved;
}

rt_inline struct rt_mmblk_reg *_next_region(struct rt_mmblk_reg *prev)
{
    if (prev && prev->node.next)
    {
        return rt_slist_entry(prev->node.next, struct rt_mmblk_reg, node);
    }
    else
    {
        return RT_NULL;
    }
}

static struct rt_mmblk_reg *_alloc_memreg(struct rt_mmblk_reg *prev)
{
    for (int i =_hint_idx; i < RT_INIT_MEMORY_REGIONS; i++)
    {
        if (_regions[i].alloc == RT_FALSE)
        {
            rt_slist_insert(&(prev->node), &(_regions[i].node));
            _regions[i].alloc = RT_TRUE;
            _hint_idx = i + 1;
            return &_regions[i];
        }
    }

    for (int i = 0; i < _hint_idx; i++)
    {
        if (_regions[i].alloc == RT_FALSE)
        {
            rt_slist_insert(&(prev->node), &(_regions[i].node));
            _regions[i].alloc = RT_TRUE;
            _hint_idx = i + 1;
            return &_regions[i];
        }
    }

    return RT_NULL;
}

static void _free_memreg(struct rt_mmblk_reg *prev)
{
    struct rt_mmblk_reg *next = _next_region(prev);

    next->alloc = RT_FALSE;
    rt_slist_remove(&(prev->node), prev->node.next);
}

static rt_err_t _reg_insert_after(struct rt_mmblk_reg *prev, rt_region_t *reg,
                                mmblk_flag_t flags)
{
    struct rt_mmblk_reg *new_reg = _alloc_memreg(prev);

    if (!new_reg)
    {
        LOG_E("No enough space");
        return -RT_ENOMEM;
    }

    rt_memcpy(&(new_reg->memreg), reg, sizeof(*reg));
    new_reg->flags = flags;
    return RT_EOK;
}

rt_inline void _reg_remove_after(struct rt_mmblk_reg *prev)
{
    _free_memreg(prev);
}

/* adding overlapped regions is banned */
static rt_err_t _memblock_add_range(struct rt_memblock *memblock,
                    const char *name, rt_size_t start, rt_size_t end, mm_flag_t flag)
{
    struct rt_mmblk_reg *reg = RT_NULL, *reg_next = RT_NULL;
    rt_slist_t sentinel;
    rt_region_t new_region;

    if (start >= end)
        return -RT_EINVAL;

    sentinel.next = &(memblock->reg_list);

    /* find suitable place */
    rt_slist_for_each_entry(reg, &sentinel, node)
    {
        reg_next = _next_region(reg);

        if (reg_next == RT_NULL)
            break;

        rt_size_t rstart = reg_next->memreg.start;
        rt_size_t rend = reg_next->memreg.end;

        /* not overlap */
        if (rstart >= end)
            break;
        if (rend <= start)
            continue;

        /* overlap */
        LOG_E("region to add %s: [%p-%p) overlap with existing region %s: [%p-%p)",\
                name, start, end, reg_next->memreg.name, rstart, rend);
        return -RT_EINVAL;
    }

    /* insert the region */
    new_region.name = name;
    new_region.start = start;
    new_region.end = end;
    return _reg_insert_after(reg, &new_region, flag);
}

rt_err_t rt_memblock_add_memory(const char *name, rt_size_t start, rt_size_t end, mmblk_flag_t flags)
{
    LOG_D("add physical address range [0x%.*lx-0x%.*lx) with flag 0x%x" \
            " to overall memory regions\n", MIN_BIT, base, MIN_BIT, base + size, flag);

    return _memblock_add_range(&mmblk_memory, name, start, end, flags);
}

rt_err_t rt_memblock_reserve_memory(const char *name, rt_size_t start, rt_size_t end, mmblk_flag_t flags)
{
    LOG_D("add physical address range %s [0x%.*lx-0x%.*lx) to reserved memory regions\n",
                                     name, MIN_BIT, start, MIN_BIT, end);

    return _memblock_add_range(&mmblk_reserved, name, start, end, flags);
}

/* [*start_reg, *end_reg) is the isolated range */
static rt_err_t _memblock_separate_range(struct rt_memblock *memblock,
                    rt_size_t start, rt_size_t end,
                    struct rt_mmblk_reg **start_reg, struct rt_mmblk_reg **end_reg)
{
    struct rt_mmblk_reg *reg = RT_NULL;
    rt_region_t new_region;
    rt_err_t err = RT_EOK;

    *start_reg = *end_reg = RT_NULL;

    rt_slist_for_each_entry(reg, &(memblock->reg_list), node)
    {
        rt_size_t rstart = reg->memreg.start;
        rt_size_t rend = reg->memreg.end;

        if (rstart >= end)
            break;
        if (rend <= start)
            continue;

        /* the beginning of the range separates its respective region */
        if (rstart < start)
        {
            new_region.start = start;
            new_region.end = rend;
            new_region.name = reg->memreg.name;
            err = _reg_insert_after(reg, &new_region, reg->flags);

            if (err != RT_EOK)
                return err;

            reg->memreg.end = start;

            *start_reg = _next_region(reg);
            *end_reg = _next_region(*start_reg);
        }
        /* the endpoint of the range separates its respective region */
        else if (rend > end)
        {
            new_region.start = end;
            new_region.end = rend;
            new_region.name = reg->memreg.name;
            err = _reg_insert_after(reg, &new_region, reg->flags);

            if (err != RT_EOK)
                return err;

            reg->memreg.end = end;

            *end_reg = _next_region(reg);
            break;
        }
        /* reg->next is fully contained in range */
        else
        {
            if (!*end_reg)
                *start_reg = reg;
            *end_reg = _next_region(reg);
        }
    }

    return err;
}

static void _memblock_set_flag(struct rt_mmblk_reg *start_reg, struct rt_mmblk_reg *end_reg, \
                        mmblk_flag_t flags)
{
    if (start_reg == RT_NULL)
        return;

    for (struct rt_mmblk_reg *iter = start_reg; iter != end_reg; iter = _next_region(iter)) {
        iter->flags |= flags;
    }
}

static void _next_free_region(struct rt_mmblk_reg **m, struct rt_mmblk_reg **r, mmblk_flag_t flags,
                      rt_size_t *out_start, rt_size_t *out_end)
{
    /* memory related data */
    rt_size_t m_start = 0;
    rt_size_t m_end = 0;

    /* reserved related data */
    rt_size_t r_start = 0;
    rt_size_t r_end = 0;
    struct rt_mmblk_reg *r_sentinel = rt_slist_entry(&(mmblk_reserved.reg_list), struct rt_mmblk_reg, node);

    for (; *m != RT_NULL; *m = _next_region(*m))
    {
        if ((*m)->flags != flags)
            continue;

        m_start = (*m)->memreg.start;
        m_end = (*m)->memreg.end;

        for (; *r != RT_NULL; *r = _next_region(*r))
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
            r_start = (*r == r_sentinel) ? 0 : (*r)->memreg.end;
            r_end = (_next_region(*r)) ? _next_region(*r)->memreg.start : PHYS_ADDR_MAX;

            /* two reserved region are adjacent */
            if (r_start == r_end)
                continue;

            if (r_start >= m_end)
                break;

            if (m_start < r_end)
            {
                *out_start = MAX(m_start, r_start);
                *out_end = MIN(m_end, r_end);

                if (m_end <= r_end)
                    *m = _next_region(*m);
                else
                    *r = _next_region(*r);
                return;
            }
        }
    }

    /* all regions found */
    *m = rt_slist_entry(&(mmblk_memory.reg_list), struct rt_mmblk_reg, node);
}

/* for each region in memory with flags and not reserved */
#define for_each_free_region(m, r, flags, p_start, p_end)                               \
    m = rt_slist_entry(&(mmblk_memory.reg_list.next), struct rt_mmblk_reg, node);       \
    r = rt_slist_entry(&(mmblk_reserved.reg_list), struct rt_mmblk_reg, node);          \
    for (_next_free_region(&m, &r, flags, p_start, p_end);                              \
         m != rt_slist_entry(&(mmblk_memory.reg_list), struct rt_mmblk_reg, node);      \
         _next_free_region(&m, &r, flags, p_start, p_end))

/* merge normal memory regions */
static void _memblock_merge_memory(void)
{
    struct rt_mmblk_reg *reg = RT_NULL;

    rt_slist_for_each_entry(reg, &(mmblk_memory.reg_list), node)
    {
        while (_next_region(reg) &&
            reg->flags == _next_region(reg)->flags &&
            reg->memreg.end == _next_region(reg)->memreg.start)
        {
            reg->memreg.end = _next_region(reg)->memreg.end;
            _reg_remove_after(reg);
        }
    }
}

void rt_memblock_setup_memory_environment(void)
{
    struct rt_mmblk_reg *iter = RT_NULL, *start_reg = RT_NULL, *end_reg = RT_NULL;
    rt_region_t reg = {0};
    rt_size_t mem = 0;
    struct rt_mmblk_reg *m, *r;
    void *err;

    _memblock_merge_memory();

    LOG_I("System memory:");

    rt_slist_for_each_entry(iter, &(mmblk_memory.reg_list), node)
    {
        LOG_I("  %-*.s [0x%.*lx, 0x%.*lx]", RT_NAME_MAX, iter->memreg.name, MIN_BIT, iter->memreg.start, MIN_BIT, iter->memreg.end);
    }

    LOG_I("Reserved memory:");

    rt_slist_for_each_entry(iter, &(mmblk_reserved.reg_list), node)
    {
        LOG_I("  %-*.s [0x%.*lx, 0x%.*lx]", RT_NAME_MAX, iter->memreg.name, MIN_BIT, iter->memreg.start, MIN_BIT, iter->memreg.end);

        if (iter->flags != MEMBLOCK_NONE)
        {
            _memblock_separate_range(&mmblk_memory, iter->memreg.start, iter->memreg.end, &start_reg, &end_reg);
            _memblock_set_flag(start_reg, end_reg, iter->flags);
        }
    }

    /* install usable memory to system page */
    for_each_free_region(m, r, MEMBLOCK_NONE, &reg.start, &reg.end)
    {
        reg.start = RT_ALIGN(reg.start, ARCH_PAGE_SIZE);
        reg.end   = RT_ALIGN_DOWN(reg.end, ARCH_PAGE_SIZE);

        if (reg.start >= reg.end)
            continue;

        LOG_I("physical memory region [%p-%p] installed to system page", reg.start, reg.end);

        reg.start -= PV_OFFSET;
        reg.end -= PV_OFFSET;

        struct rt_mm_va_hint hint = {.flags = MMF_MAP_FIXED,
                                    .limit_start = rt_kernel_space.start,
                                    .limit_range_size = rt_kernel_space.size,
                                    .map_size = reg.end - reg.start,
                                    .prefer = (void *)reg.start};

        rt_aspace_map_phy(&rt_kernel_space, &hint, MMU_MAP_K_RWCB, (reg.start + PV_OFFSET) >> MM_PAGE_SHIFT, &err);
        rt_page_install(reg);
        mem += reg.end - reg.start;
    }

    LOG_I("%ld MB memory installed to system page", mem/1000000);
}

#ifdef UTEST_MM_API_TC
/* functions below are only used for utest */
void rt_memblock_merge(void)
{
    _memblock_merge_memory();
}

static struct rt_mmblk_reg *mem;
static struct rt_mmblk_reg *res;

void rt_memblock_next_free_region_init(void)
{
    mem = rt_slist_entry(&(mmblk_memory.reg_list.next), struct rt_mmblk_reg, node);
    res = rt_slist_entry(&(mmblk_reserved.reg_list), struct rt_mmblk_reg, node);
}

void rt_memblock_next_free_region(mmblk_flag_t flags, rt_size_t *out_start, rt_size_t *out_end)
{
    _next_free_region(&mem, &res, flags, out_start, out_end);
}

rt_bool_t rt_memblock_is_last_free(void)
{
    return mem == rt_slist_entry(&(mmblk_memory.reg_list), struct rt_mmblk_reg, node);
}

#endif /* UTEST_MM_API_TC */
