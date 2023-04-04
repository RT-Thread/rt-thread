/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-17     WangXiaoyao  cache API unit test
 */

#ifndef __TEST_CACHE_RV64_H
#define __TEST_CACHE_RV64_H

#ifdef ARCH_RISCV64
#include "riscv_mmu.h"
#include <utest.h>
#include <cache.h>
#include <page.h>
#include <mmu.h>
#include <ioremap.h>

/**
 * ==============================================================
 * TEST FEATURE
 * API under cache.h
 * rt_hw_sync_cache_local
 *
 * rt_hw_cpu_dcache_clean
 * rt_hw_cpu_dcache_invalidate
 * rt_hw_cpu_dcache_clean_invalidate
 * rt_hw_cpu_dcache_clean_all
 * rt_hw_cpu_dcache_invalidate_all // meaningless
 * rt_hw_cpu_dcache_clean_invalidate_all
 * rt_hw_cpu_icache_invalidate
 * rt_hw_cpu_icache_invalidate_all
 * ==============================================================
 */

/* Ensure the ISA is valid for target ARCHITECTURE */
static void _illegal_instr(void)
{
    rt_hw_sync_cache_local(_illegal_instr, 64);
    rt_hw_cpu_dcache_clean(_illegal_instr, 64);
    rt_hw_cpu_dcache_invalidate(_illegal_instr, 64);
    // rt_hw_cpu_dcache_clean_invalidate(_illegal_instr, 64); // C908 ONLY
    rt_hw_cpu_dcache_clean_all();
    rt_hw_cpu_dcache_invalidate_all(); // !CAREFUL must be inline
    // rt_hw_cpu_dcache_clean_invalidate_all(); // C908 ONLY
    rt_hw_cpu_icache_invalidate(_illegal_instr, 64);
    rt_hw_cpu_icache_invalidate_all();
    uassert_true(1);
    LOG_I("All ok!");
}

static int _get1(void)
{
    return 1;
}

static int _get2(void)
{
    return 2;
}

/* hot patching codes and test if the value can be seen by icache */
static void _test_cache_sync(void)
{
    uassert_true(1 == _get1());
    rt_memcpy(_get1, _get2, _get2 - _get1);
    uassert_true(1 == _get1());
    rt_hw_sync_cache_local(_get1, _get2 - _get1);
    uassert_true(2 == _get1());
    LOG_I("%s ok", __func__);
}

/* test clean operation should do and only effect the range specified by writing to a page */
static void _test_dcache_clean(void)
{
    const size_t padding = 1024 * 3;
    const size_t buf_sz = ARCH_PAGE_SIZE * 2;

    char *page = rt_pages_alloc(rt_page_bits(buf_sz));
    uassert_true(!!page);

    /* after ioremap, we can access system memory to verify outcome */
    volatile char *remap_nocache = rt_ioremap(page + PV_OFFSET, buf_sz);
    rt_memset(page, 0xab, buf_sz);
    rt_hw_cpu_sync();

    int _outdate_flag = 0;
    for (size_t i = padding; i < ARCH_PAGE_SIZE; i++)
    {
        if (remap_nocache[i] != 0xab)
        {
            _outdate_flag = 1;
            break;
        }
    }

    page[padding - 1] = 0xac;
    page[padding + ARCH_PAGE_SIZE] = 0xac;
    rt_hw_cpu_dcache_clean(page + padding, ARCH_PAGE_SIZE);

    /* free some space in dcache to avoid padding data being written back */
    rt_hw_cpu_dcache_invalidate(page + padding, ARCH_PAGE_SIZE);
    uassert_true(remap_nocache[padding - 1] != 0xac);
    uassert_true(remap_nocache[padding + ARCH_PAGE_SIZE] != 0xac);

    int _test_ok = 1;
    for (size_t i = padding; i < ARCH_PAGE_SIZE; i++)
    {
        if (remap_nocache[i] != 0xab)
        {
            _test_ok = 0;
            break;
        }
    }
    uassert_true(_test_ok);

    if (!_outdate_flag)
        LOG_W("Cannot guarantee clean works");
    else
        LOG_I("%s ok", __func__);

    rt_pages_free(page, 0);
    rt_iounmap(remap_nocache);
}

/* test clean op should do and only effect the range */
static void _test_dcache_invalidate(void)
{
    const size_t padding = 1024 * 3;
    const size_t buf_sz = ARCH_PAGE_SIZE * 2;

    /* prepare */
    char *page = rt_pages_alloc(rt_page_bits(buf_sz));
    uassert_true(!!page);

    volatile char *remap_nocache = rt_ioremap(page + PV_OFFSET, buf_sz);
    rt_memset(page, 0x0, buf_sz);
    rt_hw_cpu_sync();

    int _outdate_flag = 0;
    for (size_t i = padding; i < ARCH_PAGE_SIZE; i++)
    {
        remap_nocache[i] = 0xab;
        rt_hw_cpu_dcache_invalidate((void *)&remap_nocache[i], 1);
    }

    rt_hw_cpu_dcache_clean_all();

    int _test_ok = 1;
    for (size_t i = padding; i < ARCH_PAGE_SIZE; i++)
    {
        if (remap_nocache[i] == 0xab)
        {
            _test_ok = 0;
            break;
        }
    }
    uassert_true(_test_ok);

    LOG_I("%s ok", __func__);

    rt_pages_free(page, 0);
    rt_iounmap(remap_nocache);
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
    UTEST_UNIT_RUN(_illegal_instr);
#ifdef BOARD_allwinnerd1s
    /* thead ISA extension */
    UTEST_UNIT_RUN(_test_cache_sync);
    /* part of it is hard to test on simulation machine */
    UTEST_UNIT_RUN(_test_dcache_clean);
    UTEST_UNIT_RUN(_test_dcache_invalidate);
#endif
}

UTEST_TC_EXPORT(testcase, "testcases.libcpu.cache", utest_tc_init, utest_tc_cleanup, 10);

#endif /* ARCH_RISCV64 */
#endif /* __TEST_CACHE_RV64_H */
