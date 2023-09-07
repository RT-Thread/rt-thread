/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-07     ZhaoMaosheng the first version
 */

#ifndef __MM_MEMBLOCK_H__
#define __MM_MEMBLOCK_H__

#include "mm_page.h"
#include <rtdef.h>

enum mmblk_flag
{
    MEMBLOCK_NONE       = 0x0,
    MEMBLOCK_HOTPLUG    = 0x1,
    MEMBLOCK_NOMAP      = 0x2,
};

/**
 * @struct rt_mmblk_reg
 *
 * @brief A structure representing a region in rt_memblock
 */
struct rt_mmblk_reg
{
    rt_ubase_t base;                ///< the beginning physical address of the region
    rt_size_t size;                 ///< the size of the region
    enum mmblk_flag flags;          ///< the flag of the region
};

/**
 * @struct rt_memblock
 *
 * @brief A structure representing physical memory block
 */
struct rt_memblock
{
    rt_uint32_t cnt;                ///< the count of current regions
    rt_uint32_t max;                ///< the max count of regions
    struct rt_mmblk_reg *regions;   ///< store the regions of the memory block
};

extern struct rt_memblock mmblk_memory;     ///< overall memory block
extern struct rt_memblock mmblk_reserved;   ///< reserved memory block

/**
 * @brief Add a physical address range to the overall memory region
 *
 * @note the new range is allowed to overlap with existing ones and don't affect them
 *
 * @param base the beginning of the physical address range
 * @param size the size of the physical address range
 */
void rt_memblock_add(rt_ubase_t base, rt_size_t size);

/**
 * @brief Add a physical address range to the overall memory region with certain flags
 *
 * @param base the beginning of the physical address range
 * @param size the size of the physical address range
 * @param flags the flags of the region
 */
void rt_memblock_add_ext(rt_ubase_t base, rt_size_t size, enum mmblk_flag flags);

/**
 * @brief Add a physical address range to the reserved memory region
 *
 * @param base the beginning of the physical address range
 * @param size the size of the physical address range
 */
void rt_memblock_reserve(rt_ubase_t base, rt_size_t size);

/**
 * @brief Print the information about overall and reserved memory regions
 */
void rt_memblock_dump();

/**
 * @brief Free the available to buddy system
 *
 * @return the freed memory size in bytes
 */
rt_size_t rt_memblock_end();

void rt_memblock_mark_hotplug(rt_ubase_t base, rt_size_t size);
void rt_memblock_clear_hotplug(rt_ubase_t base, rt_size_t size);
void rt_memblock_mark_nomap(rt_ubase_t base, rt_size_t size);
void rt_memblock_clear_nomap(rt_ubase_t base, rt_size_t size);

rt_inline rt_bool_t rt_memreg_is_hotpluggable(struct rt_mmblk_reg *m)
{
    return m->flags & MEMBLOCK_HOTPLUG;
}

rt_inline rt_bool_t rt_memreg_is_nomap(struct rt_mmblk_reg *m)
{
    return m->flags & MEMBLOCK_NOMAP;
}

#define for_each_region(i, memblock, rgn)           \
    for (i = 0, rgn = &memblock->regions[0];            \
         i < memblock->cnt;                 \
         i++, rgn = &memblock->regions[i])

/** just for for_each_free_region api */
void _next_free_region(rt_uint64_t *idx, enum mmblk_flag flags,
                      rt_ubase_t *out_start, rt_ubase_t *out_end);

#define for_each_free_region(i, flags, p_start, p_end)   \
    for (i = 0, _next_free_region(&i, flags, p_start, p_end);\
         i != ~(rt_uint64_t)0;\
         _next_free_region(&i, flags, p_start, p_end))

#endif
