/*
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include "utest.h"

/* These tests also run without ASan: size arithmetic must be safe in both modes. */
static void test_align_valid(void)
{
    static const rt_size_t sizes[] = { 1, 13, 16, 31, 32 };
    static const rt_size_t aligns[] = { 1, 2, sizeof(void *), 16, 64, 256 };
    rt_size_t i;
    rt_size_t j;

    for (i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++)
    {
        for (j = 0; j < sizeof(aligns) / sizeof(aligns[0]); j++)
        {
            char *p = (char *)rt_malloc_align(sizes[i], aligns[j]);
            uassert_not_null(p);
            if (!p)
            {
                return;
            }
            uassert_true(((rt_uintptr_t)p & (aligns[j] - 1)) == 0);
            rt_memset(p, 0x5a, sizes[i]);
            uassert_int_equal(p[0], 0x5a);
            uassert_int_equal(p[sizes[i] - 1], 0x5a);
            rt_free_align(p);
        }
    }
    rt_free_align(RT_NULL);
}

static void test_align_invalid(void)
{
    static const rt_size_t aligns[] = { 0, 3, 6, 12, (rt_size_t)-1 };
    rt_size_t i;
    void *p;

    for (i = 0; i < sizeof(aligns) / sizeof(aligns[0]); i++)
    {
        p = rt_malloc_align(16, aligns[i]);
        uassert_null(p);
        rt_free_align(p);
    }
    p = rt_malloc_align(0, 64);
    uassert_null(p);
    rt_free_align(p);
}

static void test_align_overflow(void)
{
    static const rt_size_t requests[][2] = {
        { (rt_size_t)-1, 64 },
        { (rt_size_t)-3, 64 },
        { (rt_size_t)-64, 64 },
        { (rt_size_t)-256, 256 },
        { (rt_size_t)-1 - sizeof(void *), 1 },
        { (rt_size_t)-1 - RT_ALIGN_SIZE, 1 },
        { (rt_size_t)-1 / 2 + 1, (rt_size_t)-1 / 2 + 1 },
    };
    rt_size_t i;

    for (i = 0; i < sizeof(requests) / sizeof(requests[0]); i++)
    {
        void *p = rt_malloc_align(requests[i][0], requests[i][1]);
        uassert_null(p);
        rt_free_align(p);
    }
}

static void testcase(void)
{
    rt_size_t failures = 0;

    /* Each unit resets the framework counters, so retain earlier failures. */
    UTEST_UNIT_RUN(test_align_valid);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_align_invalid);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_align_overflow);
    failures += utest_handle_get()->failed_num;
    uassert_int_equal(failures, 0);
}

UTEST_TC_EXPORT(testcase, "core.mem_align", RT_NULL, RT_NULL, 1000);
