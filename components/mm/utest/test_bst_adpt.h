/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-23     WangXiaoyao  Complete testcase for internal APIs
 */
#ifndef __TEST_BST_ADPT_H__
#define __TEST_BST_ADPT_H__

#include "common.h"

#ifdef RT_USING_SMART
#include "lwp_user_mm.h"
#include "mm_aspace.h"
#include "mm_flag.h"
#include <mm_private.h>
#include <lwp_pid.h>

void test_bst_adpt(void)
{
    size_t flags = MMF_MAP_FIXED;
    void *target_va = (void *)USER_VADDR_START + 0x3000;
    size_t map_size = 0x1000;
    void *prev_va = target_va - map_size;
    void *next_va = target_va + map_size + 1;
    struct rt_lwp *lwp;
    rt_aspace_t aspace;
    rt_mem_obj_t mem_obj;

    /* create aspace by lwp */
    lwp = lwp_create(LWP_CREATE_FLAG_NONE);
    uassert_true(!!lwp);
    uassert_true(!lwp_user_space_init(lwp, 0));
    aspace = lwp->aspace;
    mem_obj = &rt_mm_dummy_mapper;
    uassert_true(!!aspace);
    uassert_true(!!mem_obj);

    /* _aspace_bst_search not cover */
    uassert_true(!_aspace_bst_search(aspace, target_va)); // ret == NULL

    uassert_true(
        !rt_aspace_map(aspace, &target_va, map_size, MMU_MAP_K_RWCB, flags, mem_obj, 0));
    /* 2 wrappers */
    uassert_true(
        !rt_aspace_map(aspace, &prev_va, map_size, MMU_MAP_K_RWCB, flags, mem_obj, 0));
    uassert_true(
        !rt_aspace_map(aspace, &next_va, map_size, MMU_MAP_K_RWCB, flags, mem_obj, 0));

    /* _aspace_bst_search */
    uassert_true(!!_aspace_bst_search(aspace, target_va));
    uassert_true(!_aspace_bst_search(aspace, target_va + map_size));
    uassert_true(!_aspace_bst_search(aspace, target_va - 1));

    /**
     * @brief _aspace_bst_search_exceed
     * for given map [start, end]
     */
    rt_varea_t find;
    find = _aspace_bst_search_exceed(aspace, target_va);
    uassert_true(!!find);
    uassert_true(find->start == target_va);

    rt_varea_t last = ASPACE_VAREA_LAST(aspace);
    find = _aspace_bst_search_exceed(aspace, last->start + 1);
    uassert_true(!find);

    /**
     * @brief _aspace_bst_search_overlap
     * for given map [start, end], five types of overlapping
     */
    /* 1. all below */
    struct _mm_range range = {.start = prev_va - 2, .end = prev_va - 1};
    find = _aspace_bst_search_overlap(aspace, range);
    uassert_true(!find);
    /* 2. start below */
    range.end = prev_va;
    find = _aspace_bst_search_overlap(aspace, range);
    uassert_true(!!find);
    uassert_true(find->start == prev_va);
    /* 3. all wrapped */
    range.start = prev_va;
    range.end = prev_va + 1;
    find = _aspace_bst_search_overlap(aspace, range);
    uassert_true(!!find);
    uassert_true(find->start == prev_va);
    /* 4. end exceed */
    range.start = next_va;
    range.end = next_va + map_size + 1;
    find = _aspace_bst_search_overlap(aspace, range);
    uassert_true(!!find);
    uassert_true(find->start == next_va);
    /* 5. all exceed */
    range.start = next_va + map_size;
    find = _aspace_bst_search_overlap(aspace, range);
    uassert_true(!find);

    lwp_ref_dec(lwp);
}

#endif /* RT_USING_SMART */

#endif /* __TEST_BST_ADPT_H__ */
