/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-23     WangXiaoyao  Complete testcase for internal APIs
 */
#ifndef __TEST_ASPACE_API_INTERNAL_H__
#define __TEST_ASPACE_API_INTERNAL_H__

#include "common.h"
#include "test_bst_adpt.h"

/**
 * @brief 3 cases for find free:
 * with prefer & MAP_FIXED
 * with prefer
 * without prefer
 *
 * the requirement of find free: 
 * it will return a subset in address space that is free
 * the subset contains `length` contiguous elements
 * the alignment is satisfied
 */
static void test_find_free(void)
{
    void *top_page = rt_kernel_space.start + rt_kernel_space.size - 0x1000;
    void *vaddr = top_page;

    CONSIST_HEAP({
        /* type 1, on success */
        uassert_true(!rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, MMF_MAP_FIXED, &rt_mm_dummy_mapper, 0));
        uassert_true(vaddr == top_page);
        /* type 1, on failure */
        uassert_true(rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, MMF_MAP_FIXED, &rt_mm_dummy_mapper, 0));
        uassert_true(!vaddr);

        /* type 2, on success */
        vaddr = top_page;
        uassert_true(!rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, 0, &rt_mm_dummy_mapper, 0));
        uassert_true(vaddr < top_page);
        uassert_true(!!vaddr);
        rt_aspace_unmap(&rt_kernel_space, vaddr, 1);
        /* type 2, on failure */
        vaddr = rt_kernel_space.start;
        uassert_true(-RT_ENOSPC == rt_aspace_map(&rt_kernel_space, &vaddr, rt_kernel_space.size - 0x40000000, MMU_MAP_K_RWCB, 0, &rt_mm_dummy_mapper, 0));
        uassert_true(!vaddr);

        /* type 3 is covered by ioremap */

        /* free top page */
        rt_aspace_unmap(&rt_kernel_space, top_page, 1);
    });

    /* test mm_private.h */
    CONSIST_HEAP(test_bst_adpt());
}

#endif /* __TEST_ASPACE_API_INTERNAL_H__ */
