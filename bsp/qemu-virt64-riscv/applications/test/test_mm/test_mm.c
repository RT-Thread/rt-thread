/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_UTEST

#include "riscv_mmu.h"
#include "mmu.h"
#include "utest.h"

#define MAPPED 0
#define UNMAPPED 1

/**
 * @brief Meta data to test V2P API, its structure:
 * 
 * {va_start, va_end(included), pa_start, [mapped/unmapped]}
 */
struct mem_desc test_mem_desc[] = {
    // mapped region
    {0x80000000, 0x80000000 + 0x10000000 - 1, 0x80000000, MAPPED},  // kernel ram region
    {0x0, 0x80000000 - 1, 0x0, MAPPED},                             // MMIO region 1

    // unmapped region
    {0x100000000, 0x110000000 - 1, 0x100000000, UNMAPPED},          // region for IOREMAP
};

#define NUM_MEM_DESC (sizeof(test_mem_desc) / sizeof(test_mem_desc[0]))

extern rt_mmu_info mmu_info;

#define TEST_GRANULE_POWER 20
#define TEST_GRANULE_SIZE (1 << TEST_GRANULE_POWER)

// test board mem region
static void test_v2p(void)
{
    struct mem_desc *desc = test_mem_desc;

    // test on mapped region
    for (size_t i = 0; i < NUM_MEM_DESC; i++, desc += 1)
    {
        size_t count = (desc->vaddr_end - desc->vaddr_start + 1) >> TEST_GRANULE_POWER;
        void *vstart = (void *)desc->vaddr_start;
        void *pstart = (void *)desc->paddr_start;
        LOG_I("v2p test on VA region [%016lx-%016lx]", vstart, desc->vaddr_end + 1);

        int err_flag = 0;
        for (size_t j = 0; j < count; j++, vstart += TEST_GRANULE_SIZE, pstart += TEST_GRANULE_SIZE)
        {
            void *pa = rt_hw_mmu_v2p(&mmu_info, vstart);
            if ((desc->attr == MAPPED && pa != pstart) ||
                (desc->attr == UNMAPPED && pa != 0))
                err_flag = 1;
        }
        uassert_true(err_flag == 0);
    }
}

// TODO use arrary for test region
#define MAP_PA ((void *)0xe0001000)

// test va recollection after unmap
static void test_find_vaddr_recol(void)
{
    void *map;
    map = rt_hw_mmu_map(&mmu_info, RT_NULL, MAP_PA, 4096, MMU_MAP_K_RWCB);
    rt_hw_mmu_unmap(&mmu_info, map, 4096);
    void *remap;
    remap = rt_hw_mmu_map(&mmu_info, RT_NULL, MAP_PA, 4096, MMU_MAP_K_RWCB);
    rt_hw_mmu_unmap(&mmu_info, map, 4096);

    uassert_true(map == remap);
}

// find vaddr should return a valid VA for rt_hw_mmu_map
static void test_find_vaddr_valid(void)
{
    size_t map;
    map = (size_t)rt_hw_mmu_map(&mmu_info, RT_NULL, MAP_PA, 4096, MMU_MAP_K_RWCB);
    rt_hw_mmu_unmap(&mmu_info, (void*)map, 4096);
    LOG_I("Mapped pa %p to %p, %p", MAP_PA, map, mmu_info.vend);
    uassert_true((map >= (mmu_info.vstart << 30)) && (map <= (((mmu_info.vend - mmu_info.vstart) ? mmu_info.vend : mmu_info.vend + 1) << 30)));
}

// ioremap functionality
static void test_ioremap(void)
{

}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_v2p);
    UTEST_UNIT_RUN(test_find_vaddr_recol);
    UTEST_UNIT_RUN(test_find_vaddr_valid);
    UTEST_UNIT_RUN(test_ioremap);
}

UTEST_TC_EXPORT(testcase, "testcases.libcpu.mmu", utest_tc_init, utest_tc_cleanup, 10);
#endif /* RT_USING_UTEST */
