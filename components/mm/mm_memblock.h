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
    MEMBLOCK_NONE       = 0x0,      /**< normal region */
    MEMBLOCK_HOTPLUG    = 0x1,      /**< hotpluggable region */
    MEMBLOCK_NOMAP      = 0x2,      /**< don't add to kernel direct mapping */
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
    rt_slist_t reg_list;           /**< store the regions of the memory block */
};

/**
 * @brief Add a physical address range to the overall memory region
 *
 * @note The newly added region is strictly prohibited from overlapping with existing regions.
 *
 * @param name the name of the region
 * @param start the beginning of the physical address range
 * @param end the size of the physical address range
 * @param flags the flags of the region
 */
rt_err_t rt_memblock_add_memory(char *name, rt_size_t start, rt_size_t end, mmblk_flag_t flags);

/**
 * @brief Add a physical address range to the reserved memory region
 *
 * @note The newly added region is strictly prohibited from overlapping with existing regions.
 *
 * @param name the name of the reseved region
 * @param start the beginning of the physical address range
 * @param end the size of the physical address range
 * @param flags the flags of the region
 */
rt_err_t rt_memblock_reserve_memory(char *name, rt_size_t start, rt_size_t end, mmblk_flag_t flags);

/**
 * @brief To conclude the management of memory by the memblock.
 *
 * @note This function will free all usable to buddy system and map all memory without
 * specified MEMBLOCK_NOMAP.
 */
void rt_memblock_setup_memory_environment(void);

/**
 * @brief Get the memory memblock.
 *
 * @return Overall memory memblock.
 */
struct rt_memblock *rt_memblock_get_memory(void);

/**
 * @brief Get the reserved memory memblock.
 *
 * @return Reserved memory memblock.
 */
struct rt_memblock *rt_memblock_get_reserved(void);

#endif /* __MM_MEMBLOCK_H__ */
