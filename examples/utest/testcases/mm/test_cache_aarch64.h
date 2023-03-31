/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-17     WangXiaoyao  cache API unit test
 */
#ifndef __TEST_CACHE_AARCH64_H__
#define __TEST_CACHE_AARCH64_H__

#include "common.h"
#include <cache.h>

const char *platform_cache_not_guarantee = "Cannot guarantee cache operation works";

/**
 * ==============================================================
 * TEST FEATURE
 * API under cache.h
 *
 * void rt_hw_icache_invalidate_range(unsigned long start_addr, int size);
 * void rt_hw_cpu_icache_invalidate(void *addr, rt_size_t size);
 * void rt_hw_cpu_dcache_clean_and_invalidate(void *addr, rt_size_t size);
 * ==============================================================
 */

static int _get1_const(void)
{
    return 1;
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
static void _test_icache_invalidate_range(void)
{
    /* reset _get1 */
    rt_memcpy(_get1, _get1_const, _get2 - _get1);
    rt_hw_cpu_dcache_clean(_get1, _get2 - _get1);
    rt_hw_cpu_icache_invalidate(_get1, _get2 - _get1);
    uassert_true(1 == _get1());

    /* now copy _get2 to _get1 */
    rt_memcpy(_get1, _get2, _get2 - _get1);
    if (1 != _get1())
        LOG_W(platform_cache_not_guarantee);

    rt_hw_cpu_dcache_clean(_get1, _get2 - _get1);
    rt_hw_cpu_icache_invalidate(_get1, _get2 - _get1);
    __asm__ volatile("isb");
    uassert_true(2 == _get1());
    LOG_I("%s ok", __func__);
}

/* due to hardware feature of cortex-a, we should done this on 2 separated cpu */
static void _test_dcache_clean_and_invalidate(void)
{
    const size_t padding = 1024 * 2;
    const size_t buf_sz = ARCH_PAGE_SIZE * 2;
    volatile char *remap_nocache;
    char *page = rt_pages_alloc(rt_page_bits(buf_sz));
    uassert_true(!!page);

    rt_memset(page, 0xab, buf_sz);
    rt_hw_cpu_dcache_invalidate(page, buf_sz);

    int _outdate_flag = 0;
    if (memtest(page, 0xab, buf_sz))
        _outdate_flag = 1;

    /* after ioremap, we can access system memory to verify outcome */
    remap_nocache = rt_ioremap(page + PV_OFFSET, buf_sz);

    rt_hw_cpu_dcache_clean(page + padding, ARCH_PAGE_SIZE);
    memtest(remap_nocache + padding, 0xab, ARCH_PAGE_SIZE);

    if (!_outdate_flag)
        LOG_W(platform_cache_not_guarantee);
    else
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
    /* todo: format API under cache.h first */
    UTEST_UNIT_RUN(_test_icache_invalidate_range);
    UTEST_UNIT_RUN(_test_dcache_clean_and_invalidate);
}

UTEST_TC_EXPORT(testcase, "testcases.libcpu.cache", utest_tc_init, utest_tc_cleanup, 10);

#endif /* __TEST_CACHE_AARCH64_H__ */
