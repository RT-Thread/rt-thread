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
#include "mm_aspace.h"
#include "mm_flag.h"
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

#if 1 /* make it clear to identify the block :) */
    /* for testing on _aspace_traverse */
    static void *_prev_end;
    static size_t _count;
    static int _test_increase(rt_varea_t varea, void *param)
    {
        uassert_true(varea->start >= _prev_end);
        _prev_end = varea->start + varea->size;
        _count += 1;
        return 0;
    }
#endif

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

    /* compatible to armv7a */
    pgtbl = rt_pages_alloc(2);
    uassert_true(!!pgtbl);  /* page must be usable */
    rt_memset(pgtbl, 0, ARCH_PAGE_SIZE);

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

        /* for testing on _aspace_traverse */
        _count = 0;
        _prev_end = 0;
        uassert_true(!rt_aspace_traversal(aspace, _test_increase, 0));
        /* ensure the mapping is done */
        uassert_true(_count == 4);

        rt_aspace_delete(aspace);

        uassert_true(rt_pages_free(pgtbl, 2) == 1); /* page free must success */
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
    void *vaddr = RT_NULL;
    uassert_true(rt_aspace_map(0, &vaddr, 0x1000, MMU_MAP_K_RWCB, 0, &rt_mm_dummy_mapper, 0));
    uassert_true(vaddr == RT_NULL);

    vaddr = (void *)USER_VADDR_START;
    uassert_true(rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, 0, &rt_mm_dummy_mapper, 0));
    uassert_true(vaddr == RT_NULL);

    uassert_true(rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, -1, &rt_mm_dummy_mapper, 0));
    uassert_true(vaddr == RT_NULL);

    /**
     * @brief Requirement:
     * in _rt_aspace_map:_varea_install
     * not covering an existed varea if a named mapping is mandatory
     */
    // vaddr = (void *)((rt_ubase_t)aspace_map_tc & ~ARCH_PAGE_MASK);
    // CONSIST_HEAP(
        //     uassert_true(
            //         rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, 0, &rt_mm_dummy_mapper, 0)));
    // uassert_true(vaddr == RT_NULL);

    /**
     * @brief Requirement:
     * in _rt_aspace_map:_varea_install:_find_free
     * verify that this routine can choose a free region with specified size
     * and specified alignment requirement
     */
    #define ALIGN_REQ (0x04000000)
    CONSIST_HEAP({
        uassert_true(!rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, MMF_CREATE(0, ALIGN_REQ), &rt_mm_dummy_mapper, 0));
        uassert_true(!((rt_ubase_t)vaddr & (ALIGN_REQ - 1)));
        rt_aspace_unmap(&rt_kernel_space, vaddr);
    });

    /* test internal APIs */
    test_find_free();
}

/**
 * @brief Page frames mapping to varea
 * complete the page table on specified varea, and handle tlb maintenance
 * There are 2 variants of this API
 *
 * int rt_varea_map_page(rt_varea_t varea, void *vaddr, void *page);
 * int rt_varea_map_range(rt_varea_t varea, void *vaddr, void *paddr, rt_size_t length);
 */

static rt_varea_t _create_varea(const size_t size)
{
    rt_varea_t varea;
    void *vaddr = rt_ioremap_start;

    varea = rt_malloc(sizeof(*varea));
    uassert_true(!!varea);
    uassert_true(!rt_aspace_map_static(&rt_kernel_space, varea, &vaddr, size, MMU_MAP_K_RWCB, 0, &rt_mm_dummy_mapper, 0));
    varea->flag &= ~MMF_STATIC_ALLOC;
    uassert_true(!!vaddr);
    return varea;
}

static void test_varea_map_page(void)
{
    /**
     * @brief rt_varea_map_page
     * Requirements: complete the page table entry
     */
    const size_t buf_sz = 4 * ARCH_PAGE_SIZE;
    rt_varea_t varea = _create_varea(buf_sz);
    for (size_t i = 0; i < buf_sz; i += ARCH_PAGE_SIZE)
    {
        void *page = rt_pages_alloc(0);
        uassert_true(!!page);
        uassert_true(!rt_varea_map_page(varea, varea->start + i, page));
        uassert_true(rt_kmem_v2p(varea->start + i) == (page + PV_OFFSET));

        /* let page manager handle the free of page */
        rt_varea_pgmgr_insert(varea, page);
        uassert_true(rt_kmem_v2p(varea->start + i) == (page + PV_OFFSET));
    }

    uassert_true(!rt_aspace_unmap(&rt_kernel_space, varea->start));
}

static void test_varea_map_range(void)
{
    /**
     * @brief rt_varea_map_range
     * Requirements: complete the page table entry
     */
    const size_t buf_sz = 4 * ARCH_PAGE_SIZE;
    rt_varea_t varea = _create_varea(buf_sz);
    void *page = rt_pages_alloc(rt_page_bits(buf_sz));
    uassert_true(!!page);
    uassert_true(!rt_varea_map_range(varea, varea->start, page + PV_OFFSET, buf_sz));
    for (size_t i = 0; i < buf_sz; i += ARCH_PAGE_SIZE)
    {
        uassert_true(rt_kmem_v2p(varea->start + i) == (page + i + PV_OFFSET));
    }

    uassert_true(rt_pages_free(page, rt_page_bits(buf_sz)));
    uassert_true(!rt_aspace_unmap(&rt_kernel_space, varea->start));
}

/**
 * @brief rt_varea_unmap_page
 * Requirements: cancel the page table entry
 */
static void test_varea_unmap_page(void)
{
    /* Prepare environment */
    const size_t buf_sz = 4 * ARCH_PAGE_SIZE;
    rt_varea_t varea = _create_varea(buf_sz);
    for (size_t i = 0; i < buf_sz; i += ARCH_PAGE_SIZE)
    {
        void *page = rt_pages_alloc(0);
        uassert_true(!!page);
        uassert_true(!rt_varea_map_page(varea, varea->start + i, page));

        /* let page manager handle the free of page */
        rt_varea_pgmgr_insert(varea, page);
        uassert_true(rt_kmem_v2p(varea->start + i) == (page + PV_OFFSET));
    }

    /* test if unmap is success */
    for (size_t i = 0; i < buf_sz; i += ARCH_PAGE_SIZE)
    {
        uassert_true(rt_varea_unmap_page(varea, varea->start + i) == RT_EOK);
        uassert_true(rt_kmem_v2p(varea->start + i) == ARCH_MAP_FAILED);
    }

    uassert_true(!rt_aspace_unmap(&rt_kernel_space, varea->start));
}

/**
 * @brief rt_varea_map_range
 * Requirements: complete the page table entry
 */
static void test_varea_unmap_range(void)
{
    const size_t buf_sz = 4 * ARCH_PAGE_SIZE;
    rt_varea_t varea = _create_varea(buf_sz);
    void *page = rt_pages_alloc(rt_page_bits(buf_sz));
    uassert_true(!!page);
    uassert_true(!rt_varea_map_range(varea, varea->start, page + PV_OFFSET, buf_sz));
    for (size_t i = 0; i < buf_sz; i += ARCH_PAGE_SIZE)
    {
        uassert_true(rt_kmem_v2p(varea->start + i) == (page + i + PV_OFFSET));
    }

    /* test if unmap is success */
    uassert_true(rt_varea_unmap_range(varea, varea->start, buf_sz) == RT_EOK);
    for (size_t i = 0; i < buf_sz; i += ARCH_PAGE_SIZE)
    {
        uassert_true(rt_kmem_v2p(varea->start + i) == ARCH_MAP_FAILED);
    }

    uassert_true(rt_pages_free(page, rt_page_bits(buf_sz)));
    uassert_true(!rt_aspace_unmap(&rt_kernel_space, varea->start));
}

static void varea_map_tc(void)
{
    CONSIST_HEAP(test_varea_map_page());
    CONSIST_HEAP(test_varea_map_range());
    CONSIST_HEAP(test_varea_unmap_page());
    CONSIST_HEAP(test_varea_unmap_range());
}

static void aspace_traversal_tc(void)
{
    /**
     * @brief Requirement
     * Iterate over each varea in the kernel space
     */
    CONSIST_HEAP(aspace_delete_tc());
    uassert_true(4 == _count);
}

#ifdef ARCH_ARMV8
static void aspace_control_tc(void)
{
    /* this case is designed only for one page size */
    const size_t buf_sz = ARCH_PAGE_SIZE;
    void *vaddr = RT_NULL;
    volatile char *remap_nocache;
    int platform_cache_probe;
    uassert_true(!rt_aspace_map(&rt_kernel_space, &vaddr, 0x1000, MMU_MAP_K_RWCB, MMF_PREFETCH, &rt_mm_dummy_mapper, 0));
    uassert_true(!!vaddr);

    /* map non-cacheable region to verify cache */
    remap_nocache = rt_ioremap(rt_kmem_v2p(vaddr), buf_sz);
    uassert_true(!!remap_nocache);

    /* pre probing */
    rt_memset(vaddr, 0xba, buf_sz);
    /* no need to sync transaction on same core */
    platform_cache_probe = memtest(remap_nocache, 0xab, buf_sz);

    if (!platform_cache_probe)
    {
        LOG_I("Cannot distinguish cache attribution on current platform");
    }
    else
    {
        LOG_I("Ready to verify attribution of cached & non-cacheable");
    }

    /* verify cache */
    uassert_true(!rt_aspace_control(&rt_kernel_space, vaddr, MMU_CNTL_NONCACHE));
    rt_memset(vaddr, 0, buf_sz);
    uassert_true(!memtest(remap_nocache, 0, buf_sz));

    /* another option as MMU_CNTL_CACHE */
    uassert_true(!rt_aspace_control(&rt_kernel_space, vaddr, MMU_CNTL_CACHE));

    rt_iounmap(remap_nocache);
    uassert_true(!rt_aspace_unmap(&rt_kernel_space, vaddr));
}
#endif

static void aspace_tc(void)
{
    UTEST_UNIT_RUN(aspace_create_tc);
    UTEST_UNIT_RUN(aspace_delete_tc);
    UTEST_UNIT_RUN(aspace_map_tc);
    UTEST_UNIT_RUN(aspace_traversal_tc);
#ifdef ARCH_ARMV8
    UTEST_UNIT_RUN(aspace_control_tc);
#endif
    UTEST_UNIT_RUN(varea_map_tc);

    /* functionality */
    UTEST_UNIT_RUN(synchronization_tc);
    return ;
}

#endif /* __TEST_ASPACE_API_H__ */
