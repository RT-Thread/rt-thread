/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-14     WangXiaoyao  the first version
 * 2023-03-20     WangXiaoyao  Format & add more testcases for API under mm_aspace.h
 * 2025-12-14     ChuanN-sudo  Add standardized utest documentation block
 */

/**
 * Test Case Name: MM API Test
 *
 * Test Objectives:
 * - Verify I/O remapping functionality with cached memory access.
 * - Test memory mapping flag creation and extraction mechanisms.
 * - Validate address space management operations.
 * - Test core APIs: rt_pages_alloc(), rt_ioremap_cached(), rt_iounmap(), rt_pages_free(),
 *      rt_pages_free(), MMF_CREATE(), MMF_GET_CNTL(), MMF_GET_ALIGN().
 *
 * Test Scenarios:
 * - Address Space Test (aspace_tc): Tests memory address space management APIs.
 * - I/O Remap Test (ioremap_tc): Allocates physical pages, maps to virtual address with cache, verifies data consistency, and cleans up resources.
 * - Flag Test (flag_tc): Creates memory mapping flags with different parameters and validates control bits and alignment values extraction.
 *
 * Verification Metrics:
 * - I/O remapping should correctly map physical to virtual addresses.
 * - Cached memory access should maintain data consistency between physical and virtual addresses.
 * - Memory mapping flags should correctly encode and decode control bits and alignment values.
 * - Flag creation with alignment should set MMF_REQUEST_ALIGN bit and store alignment value.
 * - Flag creation without alignment should not set alignment-related bits.
 *
  Dependencies:
 * - Hardware requirements: QEMU emulator or any hardware platform that supports RT-Thread with MMU.
 * - Software configuration:
 *     - RT_UTEST_MM_API must be enabled (enable via: RT-Thread Utestcases -> RT-Thread Utestcases -> Memory Management Subsystem Testcase -> Enable Utest for MM API).
 *     - RT_USING_SMART must be enabled (enable via:  Enable RT-Thread Kernel -> RT-Thread Smart (microkernel on kernel/userland)).
 * - Environmental Assumptions: MMU support must be available on the target platform.

 * Expected Results:
 * - Final output: "[ PASSED ] [ result ] testcase (testcases.mm.api_tc)"
 * - No assertion failures during test execution.
 */
#include "common.h"

/**
 * @brief Testing all APIs under components/mm
 */

void ioremap_tc(void);
void flag_tc(void);

#ifdef STANDALONE_TC
#define TC_ASSERT(expr)                                                        \
    ((expr)                                                                    \
         ? 0                                                                   \
         : rt_kprintf("AssertFault(%d): %s\n", __LINE__, RT_STRINGIFY(expr)))
#else
#define TC_ASSERT(expr) uassert_true(expr)
#endif

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

#include "test_aspace_api.h"

static void testcase(void)
{
    aspace_tc();
    ioremap_tc();
    flag_tc();
}
UTEST_TC_EXPORT(testcase, "testcases.mm.api_tc", utest_tc_init, utest_tc_cleanup, 20);

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

void flag_tc(void)
{
    size_t flags;

    flags = MMF_CREATE(MMF_MAP_FIXED, 0x4000);
    TC_ASSERT(MMF_GET_CNTL(flags) == (MMF_MAP_FIXED | MMF_REQUEST_ALIGN));
    TC_ASSERT((1 << MMF_GET_ALIGN(flags)) == 0x4000);

    flags = MMF_CREATE(MMF_MAP_FIXED, 0);
    TC_ASSERT(MMF_GET_CNTL(flags) == MMF_MAP_FIXED);
    TC_ASSERT(MMF_GET_ALIGN(flags) == 0);
}

#if 0

#define BUF_SIZE (4ul << 20)
static char ALIGN(BUF_SIZE) buf[BUF_SIZE];

void buddy_tc(void)
{
    size_t total, free;
    rt_page_get_info(&total, &free);

    rt_region_t region = {
        .start = (size_t)buf,
        .end = (size_t)buf + BUF_SIZE,
    };

    size_t new_total, new_free;
    rt_page_install(region);
    rt_page_get_info(&new_total, &new_free);
    TC_ASSERT(new_total - total == (BUF_SIZE >> ARCH_PAGE_SHIFT));
    TC_ASSERT(new_free > free);
}

void mmu_page_tc()
{
    mm_aspace_t aspace = ASPACE_NEW();
    size_t total, free;
    rt_page_get_info(&total, &free);
    rt_hw_mmu_map(aspace, (void *)0x3fffffffff, 0, ARCH_PAGE_SIZE,
                  MMU_MAP_K_RWCB);
    rt_hw_mmu_unmap(aspace, (void *)0x3fffffffff, ARCH_PAGE_SIZE);

    size_t new_total, new_free;
    rt_page_get_info(&new_total, &new_free);
    TC_ASSERT(new_free == free);
    mm_aspace_delete(aspace);
}
#endif
