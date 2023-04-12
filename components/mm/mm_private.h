/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-14     WangXiaoyao  the first version
 */
#ifndef __MM_PRIVATE_H__
#define __MM_PRIVATE_H__

#include "mm_aspace.h"
#include <rtdef.h>
#include <stddef.h>

/**
 * @brief DATA STRUCTURE & API USED INTERNALLY
 *
 * This is mainly a wrapper layer to actual data structure.
 * In this way, we can switch to any BST we like by adding new
 * wrapper code.
 * Every BST must satisfy the API to support MM
 *
 * *INFO: varea range convention
 * For API, a range is specified by a base and its length.
 * This provides a clear interface without ambiguity.
 * For implementation, a range is specified by [start, end] tuple
 * where both start and end are inclusive.
 */

struct _mm_range
{
    void *start;
    void *end;
};

/**
 * @brief
 *
 * @param aspace
 * @return rt_err_t
 */
rt_err_t _aspace_bst_init(struct rt_aspace *aspace);

/**
 * @brief Retrieve any varea if start in [varea->start, varea->end]
 *
 * @param aspace
 * @param start
 * @return struct rt_varea*
 */
struct rt_varea *_aspace_bst_search(struct rt_aspace *aspace, void *start);

/**
 * @brief Retrieve lowest varea satisfies (varea->start >= start)
 *
 * @param aspace
 * @param length
 * @param struct _mm_range
 * @return struct rt_varea*
 */
struct rt_varea *_aspace_bst_search_exceed(struct rt_aspace *aspace,
                                           void *start);

/**
 * @brief Retrieve any varea overlaps a specified address range
 *
 * @param aspace
 * @param start
 * @param length
 * @return struct rt_varea*
 */
struct rt_varea *_aspace_bst_search_overlap(struct rt_aspace *aspace,
                                            struct _mm_range range);

/**
 * @brief Insert a varea into the bst
 *
 * @param aspace
 * @param varea
 */
void _aspace_bst_insert(struct rt_aspace *aspace, struct rt_varea *varea);

/**
 * @brief Remove a varea from the bst
 *
 * @param aspace
 * @param varea
 */
void _aspace_bst_remove(struct rt_aspace *aspace, struct rt_varea *varea);

void rt_varea_pgmgr_pop(rt_varea_t varea, void *vaddr, rt_size_t size);

void rt_varea_pgmgr_pop_all(rt_varea_t varea);

int _varea_map_with_msg(rt_varea_t varea, struct rt_aspace_fault_msg *msg);

#endif /* __MM_PRIVATE_H__ */
