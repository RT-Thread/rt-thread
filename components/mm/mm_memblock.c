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

#define DBG_TAG "mm.memblock"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static rt_uint32_t _hint_idx = 1;
static rt_uint32_t _max_regions = RT_INIT_MEMORY_REGIONS;
static struct rt_mmblk_reg _memory_regions[RT_INIT_MEMORY_REGIONS];
struct rt_memblock mmblk_memory;

#define NEXT_MEMREG(prev) (prev->node.next ? rt_slist_entry(prev->node.next, struct rt_mmblk_reg, node) : RT_NULL)

static struct rt_mmblk_reg *_malloc_memreg(struct rt_mmblk_reg *prev)
{
    struct rt_mmblk_reg *ret = RT_NULL;

    for(int i = _hint_idx; i < _max_regions; i++)
    {
        if(_memory_regions[i].alloc == RT_FALSE)
        {
            rt_slist_insert(&(prev->node), &(_memory_regions[i].node));
            _memory_regions[i].alloc = RT_TRUE;
            _hint_idx = i + 1;
            ret = &_memory_regions[i];
            break;
        }
    }

    if(ret == RT_NULL)
    {
        for(int i = 0; i < _hint_idx; i++)
        {
            if(_memory_regions[i].alloc == RT_FALSE)
            {
                rt_slist_insert(&(prev->node), &(_memory_regions[i].node));
                _memory_regions[i].alloc = RT_TRUE;
                _hint_idx = i + 1;
                ret = &_memory_regions[i];
                break;
            }
        }
    }

    return ret;
}

static void _free_memreg(struct rt_mmblk_reg *prev)
{
    struct rt_mmblk_reg *next = NEXT_MEMREG(prev);

    next->alloc = RT_FALSE;
    rt_slist_remove(&(prev->node), prev->node.next);
}

static void _reg_insert_after(struct rt_mmblk_reg *prev, rt_region_t *reg,
                                mmblk_flag_t flags)
{
    struct rt_mmblk_reg *new_reg = _malloc_memreg(prev);

    if(!new_reg)
    {
        LOG_E("No enough space");
        RT_ASSERT(0);
    }

    rt_memcpy(&(new_reg->memreg), reg, sizeof(*reg));
    new_reg->flags = flags;
}

static void _reg_remove_after(struct rt_mmblk_reg *prev)
{
    _free_memreg(prev);
}

/* merge normal memory regions */
static void _memblock_merge_memory()
{
    struct rt_mmblk_reg *reg;

    rt_slist_for_each_entry(reg, &(mmblk_memory.reg_list), node)
    {
        while (reg->node.next &&
            reg->flags == MEMBLOCK_NORMAL &&
            NEXT_MEMREG(reg)->flags == MEMBLOCK_NORMAL &&
            reg->memreg.end == NEXT_MEMREG(reg)->memreg.start)
        {
            reg->memreg.end = NEXT_MEMREG(reg)->memreg.end;
            _reg_remove_after(reg);
        }
    }
}

/* this function simply adds the specified range without affecting existing regions */
static void _memblock_add_memory(rt_region_t *region, mm_flag_t flag)
{
    RT_ASSERT(region->start < region->end);

    struct rt_mmblk_reg *reg, *reg_next;
    rt_slist_t sentinel;
    rt_ubase_t start = (rt_ubase_t)region->start, end = (rt_ubase_t)region->end;

    sentinel.next = &(mmblk_memory.reg_list);

    rt_slist_for_each_entry(reg, &sentinel, node)
    {
        if(reg->node.next == RT_NULL)
            break;

        /* skip sentinel node */
        reg_next = NEXT_MEMREG(reg);
        rt_ubase_t rstart = reg_next->memreg.start;
        rt_ubase_t rend = reg_next->memreg.end;

        /* not overlap */
        if(rstart >= end)
            break;
        if(rend <= start)
            continue;

        if((reg_next->flags & MEMBLOCK_RESERVED) && (flag != MEMBLOCK_NORMAL))
        {
            LOG_W("reserve a non-normal region %s: [%p-%p) with flag 0x%x!", \
                reg_next->memreg.name, reg_next->memreg.start, \
                reg_next->memreg.end, reg_next->flags);
        }

        if(rstart > start)
        {
            _reg_insert_after(reg, &(rt_region_t)
            {
                .name = "memory",
                .start = (rt_size_t)start,
                .end = (rt_size_t)rstart,
            }, flag);
        }
        start = MIN(rend, end);
    }

    /* insert the remaining portion */
    if(start < end)
    {
        _reg_insert_after(reg, &(rt_region_t)
        {
            .name = "memory",
            .start = (rt_size_t)start,
            .end = (rt_size_t)end,
        }, flag);
    }
}

/*
 * set the reserved range's name and flag, this range should be normal memory in memblock before
 * Note: this function will fully cover the range's name and flag
 */
static void _memblock_set_reserve(rt_region_t *range, mmblk_flag_t flag)
{
    RT_ASSERT(range->start < range->end);

    struct rt_mmblk_reg *reg, *reg_next, *start_reg_prev, *end_reg_next;
    rt_slist_t sentinel;

    start_reg_prev = end_reg_next = RT_NULL;
    sentinel.next = &(mmblk_memory.reg_list);

    /* find the start_reg_prev and end_reg_prev of this range */
    rt_slist_for_each_entry(reg, &sentinel, node)
    {
        if(reg->node.next == RT_NULL)
            break;

        reg_next = NEXT_MEMREG(reg);
        rt_ubase_t rstart = reg_next->memreg.start;
        rt_ubase_t rend = reg_next->memreg.end;

        if (rstart >= range->end)
            break;
        if (rend <= range->start)
            continue;

        /* the beginning of the range separates its respective region */
        if(rstart < range->start)
        {
            _reg_insert_after(reg_next, &(rt_region_t)
            {
                .name = reg_next->memreg.name,
                .start = (rt_size_t)range->start,
                .end = (rt_size_t)reg_next->memreg.end,
            }, reg_next->flags);
            reg_next->memreg.end = range->start;

            start_reg_prev = reg_next;
            end_reg_next = NEXT_MEMREG(NEXT_MEMREG(reg_next));
        }
        /* the endpoint of the range separates its respective region */
        else if(rend > range->end)
        {
            _reg_insert_after(reg, &(rt_region_t)
            {
                .name = reg_next->memreg.name,
                .start = (rt_size_t)reg_next->memreg.start,
                .end = (rt_size_t)range->end,
            }, reg_next->flags);
            reg_next->memreg.start = range->end;

            end_reg_next = NEXT_MEMREG(NEXT_MEMREG(reg));
            break;
        }
        /* reg->next is fully contained in range */
        else
        {
            if(end_reg_next == RT_NULL)
                start_reg_prev = reg;
            end_reg_next = NEXT_MEMREG(reg_next);
        }
    }

    /* delete origin overlay regions */
    for(reg = start_reg_prev; NEXT_MEMREG(reg) != end_reg_next;)
    {
        if(NEXT_MEMREG(reg)->flags != MEMBLOCK_NORMAL)
        {
            LOG_W("reserve a non-normal region %s: [%p-%p) with flag 0x%x!", \
                NEXT_MEMREG(reg)->memreg.name, NEXT_MEMREG(reg)->memreg.start, \
                NEXT_MEMREG(reg)->memreg.end, NEXT_MEMREG(reg)->flags);
        }
        _free_memreg(reg);
    }

    /* insert new region */
    _reg_insert_after(start_reg_prev, &(rt_region_t)
    {
        .name = range->name,
        .start = (rt_size_t)range->start,
        .end = (rt_size_t)range->end,
    }, flag);
}

void _check_overlap_region(rt_region_t *region)
{
    struct rt_mmblk_reg *reg;

    rt_slist_for_each_entry(reg, &(mmblk_memory.reg_list), node)
    {
        if(!(reg->flags & MEMBLOCK_RESERVED))
        {
            /* overlap */
            if(!(region->end < reg->memreg.start || region->start > reg->memreg.end))
            {
                LOG_W("memory region overlap");
                LOG_W("\tregion to add: %s [%p-%p)", region->name, region->start, region->end);
                LOG_W("\toverlaped with: %s [%p-%p)", reg->memreg.name, reg->memreg.start, reg->memreg.end);
            }
        }
    }
}

void rt_memblock_add_memory(rt_region_t *memory)
{
    LOG_D("add physical address range %s: [%p-%p) to overall memory regions\n",\
                                    memory->name, memory->start, memory->end);
    _check_overlap_region(memory);
    _memblock_add_memory(memory, MEMBLOCK_NORMAL);
    _memblock_merge_memory();
}

void rt_memblock_add_memory_ext(rt_region_t *memory, mmblk_flag_t flags)
{
    LOG_D("add physical address range %s: [%p-%p) with flag 0x%x" \
            " to overall memory regions\n", memory->name, \
            memory->start, memory->end, flags);

    _check_overlap_region(memory);
    _memblock_add_memory(memory, flags);
    _memblock_merge_memory();
}

void rt_memblock_reserve(rt_region_t *reserved)
{
    LOG_D("set physical address range %s: [%p-%p) reserved\n",\
                                    memory->name, memory->start, memory->end);

    _memblock_add_memory(reserved, MEMBLOCK_NORMAL);
    _memblock_set_reserve(reserved, MEMBLOCK_RESERVED);
}

void rt_memblock_reserve_ext(rt_region_t *reserved, mmblk_flag_t flags)
{
    LOG_D("set physical address range %s: [%p-%p) with flag 0x%x" \
            " reserved\n", memory->name, memory->start, memory->end, flags);

    _memblock_add_memory(reserved, MEMBLOCK_NORMAL);
    _memblock_set_reserve(reserved, flags | MEMBLOCK_RESERVED);
}

rt_size_t rt_memblock_free_all(void)
{
    rt_bool_t init = RT_TRUE;
    rt_size_t mem = 0;
    struct rt_mmblk_reg *reg;

    /* make sure region is compact */
    _memblock_merge_memory();

    rt_slist_for_each_entry(reg, &(mmblk_memory.reg_list), node)
    {
        if(reg->flags == MEMBLOCK_NORMAL)
        {
            if(init)
            {
                rt_page_init(reg->memreg);
                init = RT_FALSE;
            }
            else
            {
                rt_page_install(reg->memreg);
            }
            mem += reg->memreg.end - reg->memreg.start;
        }
    }

    LOG_D("0x%lx(%ld) bytes memory added to buddy system\n", mem, mem);
    return mem;
}

void rt_memblock_dump(void)
{
    rt_size_t usable = 0, reserved = 0;
    struct rt_mmblk_reg *reg;

    rt_slist_for_each_entry(reg, &(mmblk_memory.reg_list), node)
    {
        if(rt_memreg_is_reserved(reg))
        {
            reserved += reg->memreg.end - reg->memreg.start;
        }
        else
        {
            usable += reg->memreg.end - reg->memreg.start;
        }
    }

    rt_kprintf("Usable memory info:\n");
    rt_slist_for_each_entry(reg, &(mmblk_memory.reg_list), node)
    {
        if(!rt_memreg_is_reserved(reg))
        {
            rt_kprintf("  %-*.s [%p, %p) flags: 0x%x\n", \
                RT_NAME_MAX, reg->memreg.name, reg->memreg.start, reg->memreg.end, reg->flags);
        }
    }
    rt_kprintf("Total usable memory size: 0x%lx(%ld) bytes\n", usable, usable);

    rt_kprintf("Reserved memory info:\n");
    rt_slist_for_each_entry(reg, &(mmblk_memory.reg_list), node)
    {
        if(rt_memreg_is_reserved(reg))
        {
            rt_kprintf("  %-*.s [%p, %p) flags: 0x%x\n", \
                RT_NAME_MAX, reg->memreg.name, reg->memreg.start, reg->memreg.end, reg->flags);
        }
    }
    rt_kprintf("Total reserved memory size: 0x%lx(%ld) bytes\n", reserved, reserved);
}
