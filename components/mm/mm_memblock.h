/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-07     zmshahaha    the first version
 */

#ifndef __MM_MEMBLOCK_H__
#define __MM_MEMBLOCK_H__

#include "mm_page.h"
#include <rtdef.h>

enum mmblk_flag
{
    MEMBLOCK_NORMAL     = 0x0,      /**< normal region */
    MEMBLOCK_RESERVED   = 0x1,      /**< reserved memory region */
    MEMBLOCK_HOTPLUG    = 0x2,      /**< hotpluggable region */
    MEMBLOCK_NOMAP      = 0x4,      /**< don't add to kernel direct mapping */
};

typedef rt_uint32_t mmblk_flag_t;
/**
 * @struct rt_mmblk_reg
 *
 * @brief A structure representing a region in rt_memblock
 */
struct rt_mmblk_reg
{
    rt_region_t memreg;             /**< used to indicate the extent of this area */
    mmblk_flag_t flags;             /**< the flag of the region */
    rt_bool_t alloc;                /**< is the node allocated */
    rt_slist_t node;                /**< hook on rt_memblock */
};

/**
 * @struct rt_memblock
 *
 * @brief A structure representing physical memory block
 */
struct rt_memblock
{
    rt_uint32_t hint_idx;
    rt_slist_t reg_list;
};

extern struct rt_memblock mmblk_memory;     /**< overall memory block */

/**
 * @brief Add a physical address range to the overall memory region
 *
 * @note the new range is allowed to overlap with existing ones and don't affect them
 *
 * @param memory the physical address region of usable memory
 */
void rt_memblock_add_memory(rt_region_t *memory);

/**
 * @brief Add a physical address range to the overall memory region with certain flags
 *
 * @param memory the physical address region of usable memory
 * @param flags the flags of the region
 */
void rt_memblock_add_memory_ext(rt_region_t *memory, mmblk_flag_t flags);

/**
 * @brief Set a physical address region as reserved
 *
 * @param reserved the physical address region of reserved memory
 */
void rt_memblock_reserve(rt_region_t *reserved);

/**
 * @brief Set a physical address region as reserved with certain flags
 *
 * @param reserved the physical address region of reserved memory
 * @param flags the size of the region
 */
void rt_memblock_reserve_ext(rt_region_t *reserved, mmblk_flag_t flags);

/**
 * @brief Print the information about overall and reserved memory regions
 */
void rt_memblock_dump(void);

/**
 * @brief Free the available memory to buddy system
 *
 * @return the freed memory size in bytes
 */
rt_size_t rt_memblock_free_all(void);

rt_inline rt_bool_t rt_memreg_is_reserved(struct rt_mmblk_reg *m)
{
    return m->flags & MEMBLOCK_RESERVED;
}

rt_inline rt_bool_t rt_memreg_is_hotpluggable(struct rt_mmblk_reg *m)
{
    return m->flags & MEMBLOCK_HOTPLUG;
}

rt_inline rt_bool_t rt_memreg_is_nomap(struct rt_mmblk_reg *m)
{
    return m->flags & MEMBLOCK_NOMAP;
}

#endif
