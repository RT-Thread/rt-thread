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
#include "mm_fault.h"
#include "mm_flag.h"
#include "mm_page.h"

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

#define VAREA_NOT_STATIC(varea) (!((varea)->flag & MMF_STATIC_ALLOC))
#define VAREA_NAME(varea)                                                      \
  ((!varea->mem_obj || !varea->mem_obj->get_name)                              \
       ? "unknow"                                                              \
       : varea->mem_obj->get_name(varea))
#define VAREA_IS_WRITABLE(varea)                                               \
  (rt_hw_mmu_attr_test_perm(varea->attr,                                       \
                            RT_HW_MMU_PROT_USER | RT_HW_MMU_PROT_WRITE))
#define VAREA_VA_TO_OFFSET(varea, va)                                          \
    ((varea)->offset + MM_PA_TO_OFF((long)(va) - (long)(varea)->start))

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

void rt_varea_pgmgr_pop_all(rt_varea_t varea);

int rt_varea_fix_private_locked(rt_varea_t ex_varea, void *pa,
                                struct rt_aspace_fault_msg *msg,
                                rt_bool_t dont_copy);

int rt_varea_map_with_msg(rt_varea_t varea, struct rt_aspace_fault_msg *msg);

void _varea_uninstall_locked(rt_varea_t varea);

int _mm_aspace_map(rt_aspace_t aspace, rt_varea_t *pvarea, void **addr,
                   rt_size_t length, rt_size_t attr, mm_flag_t flags,
                   rt_mem_obj_t mem_obj, rt_size_t offset);

rt_inline rt_bool_t rt_varea_is_private_locked(rt_varea_t varea)
{
    rt_base_t flags = varea->flag;
    return !!(
        (flags & (MMF_MAP_PRIVATE | MMF_MAP_PRIVATE_DONT_SYNC))
        && (varea->aspace->private_object != varea->mem_obj)
    );
}

rt_err_t rt_aspace_anon_ref_dec(rt_mem_obj_t aobj);
rt_err_t rt_aspace_page_get_phy(rt_aspace_t aspace, void *page_va, void *buffer);
rt_err_t rt_aspace_page_put_phy(rt_aspace_t aspace, void *page_va, void *buffer);

#endif /* __MM_PRIVATE_H__ */
