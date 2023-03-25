/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-20     WangXiaoyao  Complete testcase for mm_aspace.c
 */
#ifndef __TEST_ASPACE_API_H__
#define __TEST_ASPACE_API_H__

#include "common.h"
#include "test_aspace_api_internal.h"
#include "test_synchronization.h"

/**
 * @brief API for aspace create/destroy
 *
 * rt_aspace_t rt_aspace_create(void *start, rt_size_t length, void *pgtbl);
 * rt_aspace_t rt_aspace_init(rt_aspace_t aspace, void *start, rt_size_t length, void *pgtbl);
 * void rt_aspace_delete(rt_aspace_t aspace);
 * void rt_aspace_detach(rt_aspace_t aspace);
 *
 * the init & detach is covered by create & detach
 */

static void aspace_create_tc(void)
{
    /* test robustness, detect failure and recover status of overall system */
    rt_aspace_t aspace;

    CONSIST_HEAP(aspace = rt_aspace_create((void *)(0 - 0x1000), 0x1000, NULL));
    uassert_true(!aspace);
}

static void aspace_delete_tc(void)
{
    /**
     * @brief Requirements: delete should recycle all types of vareas properly inside
     * and release the resource allocated for it
     */
    rt_aspace_t aspace;
    struct rt_mm_va_hint hint = {.flags = 0,
                                 .map_size = 0x1000,
                                 .prefer = 0};
    struct rt_varea varea_phy;
    struct rt_varea varea_mobj;
    void *pgtbl;
    void *vaddr;

    pgtbl = rt_pages_alloc(0);
    uassert_true(!!pgtbl);  /* page must be usable */

    CONSIST_HEAP({
        aspace = rt_aspace_create((void *)USER_VADDR_START, USER_VADDR_TOP - USER_VADDR_START, pgtbl);
        uassert_true(!!aspace);

        /* insert 4 types of vareas into this aspace */
        hint.limit_start = aspace->start;
        hint.limit_range_size = aspace->size;
        uassert_true(!rt_aspace_map_phy(aspace, &hint, MMU_MAP_K_RWCB, 0, &vaddr));
        uassert_true(!rt_aspace_map_phy_static(aspace, &varea_phy, &hint, MMU_MAP_K_RWCB, 0, &vaddr));
        uassert_true(!rt_aspace_map(aspace, &vaddr, 0x1000, MMU_MAP_K_RWCB, 0, &rt_mm_dummy_mapper, 0));
        uassert_true(!rt_aspace_map_static(aspace, &varea_mobj, &vaddr, 0x1000, MMU_MAP_K_RWCB, 0, &rt_mm_dummy_mapper, 0));
        rt_aspace_delete(aspace);

        uassert_true(rt_pages_free(pgtbl, 0) == 1); /* page free must success */
    });
}

/**
 * @brief Memory Map on Virtual Address Space to Mappable Object
 * int rt_aspace_map(rt_aspace_t aspace, void **addr, rt_size_t length, rt_size_t attr,
 *                   mm_flag_t flags, rt_mem_obj_t mem_obj, rt_size_t offset);
 * int rt_aspace_map_static(rt_aspace_t aspace, rt_varea_t varea, void **addr,
 *                          rt_size_t length, rt_size_t attr, mm_flag_t flags,
 *                          rt_mem_obj_t mem_obj, rt_size_t offset);
 */
static void aspace_map_tc(void)
{
    /**
     * @brief Requirement:
     * Robustness, filter out invalid input
     */
    void *vaddr;
    uassert_true(rt_aspace_map(0, &vaddr, 0x1000, MMU_MAP_K_RWCB, 0, &rt_mm_dummy_mapper, 0));
    uassert_true(vaddr == RT_NULL);

    vaddr = (void *)0x100000;
    uassert_true(rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, 0, &rt_mm_dummy_mapper, 0));
    uassert_true(vaddr == RT_NULL);

    uassert_true(rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, 0x01000000, &rt_mm_dummy_mapper, 0));
    uassert_true(vaddr == RT_NULL);

    /**
     * @brief Requirement:
     * in _rt_aspace_map:_varea_install
     * not covering an existed varea if a named mapping is mandatory
     */
    vaddr = (void *)((rt_ubase_t)aspace_map_tc & ~ARCH_PAGE_MASK);
    CONSIST_HEAP(
        uassert_true(
            rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, MMF_MAP_FIXED, &rt_mm_dummy_mapper, 0)));
    uassert_true(vaddr == RT_NULL);

    /**
     * @brief Requirement:
     * in _rt_aspace_map:_varea_install:_find_free
     * verify that this routine can choose a free region with specified size
     * and specified alignment requirement
     */
    #define ALIGN_REQ (0x40000000)
    CONSIST_HEAP({
        uassert_true(!rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, MMF_CREATE(0, ALIGN_REQ), &rt_mm_dummy_mapper, 0));
        uassert_true(!((rt_ubase_t)vaddr & (ALIGN_REQ - 1)));
        rt_aspace_unmap(&rt_kernel_space, vaddr, 1);
    });

    /* test internal APIs */
    test_find_free();
}

/**
 * @brief Page frames mapping to varea
 * complete the page table on specified varea, and handle tlb maintenance
 */
static void varea_map_tc(void)
{
    ;
}

static void aspace_tc(void)
{
    UTEST_UNIT_RUN(aspace_create_tc);
    UTEST_UNIT_RUN(aspace_delete_tc);
    UTEST_UNIT_RUN(aspace_map_tc);
    UTEST_UNIT_RUN(varea_map_tc);
    UTEST_UNIT_RUN(synchronization_tc);
    return ;
}

#endif /* __TEST_ASPACE_API_H__ */
