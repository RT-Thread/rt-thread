/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-14     WangXiaoyao  the first version
 * 2023-03-20     WangXiaoyao  Format & add more testcases for API under mm_aspace.h
 * 2026-03-19     cl2t         Add standardized utest documentation block
 */

/**
 * Test Case Name: I/O Remap Test
 *
 * Test Objectives:
 * - Verify the rt_ioremap_cached() API for mapping physical addresses to
 *   virtual addresses with cached memory access.
 * - Test core APIs: rt_pages_alloc(), rt_ioremap_cached(), rt_iounmap(),
 *   rt_pages_free().
 *
 * Test Scenarios:
 * - Allocates a physical page (4KB), maps it to a virtual address using
 *   rt_ioremap_cached(), verifies data consistency between the physical
 *   and virtual addresses, then unmaps and frees the resources.
 *
 * Verification Metrics:
 * - The value read through the virtual address must equal the value at the
 *   corresponding physical address.
 * - No memory leaks after unmap and free operations (validated via
 *   CONSIST_HEAP wrapper).
 *
 * Dependencies:
 * - Software configuration: RT_USING_SMART must be enabled.
 * - Environmental assumptions: MMU support must be available on the target
 *   platform.
 *
 * Expected Results:
 * - Final output: "[ PASSED ] [ result ] testcase (testcases.mm.ioremap)"
 * - No assertion failures during test execution.
 */

#include "common.h"

void ioremap_tc(void)
{
    const size_t bufsz = 0x1000;
    void *paddr = (void *)rt_pages_alloc(rt_page_bits(bufsz)) + PV_OFFSET;
    int *vaddr;
    vaddr = rt_ioremap_cached(paddr, bufsz);
    if (vaddr)
    {
        TC_ASSERT(*vaddr == *(int *)(paddr - PV_OFFSET));

        rt_iounmap(vaddr);
        rt_pages_free(paddr - PV_OFFSET, 0);
    }
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void test_main(void)
{
    CONSIST_HEAP(ioremap_tc());
}
UTEST_TC_EXPORT(test_main, "testcases.mm.ioremap", utest_tc_init, utest_tc_cleanup, 20);
