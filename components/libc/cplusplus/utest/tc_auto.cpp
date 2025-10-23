/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-19     Rbb666       the first version
 */

#include <rtthread.h>
#include "utest.h"
#include <vector>

/**
 * @brief Test auto keyword.
 */
static void test_auto(void)
{
    auto x = 42;
    auto y = 3.14;
    if (x != 42 || y != 3.14)
    {
        uassert_false(true);
    }
    uassert_true(true);
}

/**
 * @brief Test range-based for loop.
 */
static void test_range_for(void)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    int sum = 0;
    for (auto i : v)
    {
        sum += i;
    }
    if (sum != 15)
    {
        uassert_false(true);
    }
    uassert_true(true);
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
    /* Test auto keyword */
    UTEST_UNIT_RUN(test_auto);
    /* Test range-based for loop */
    UTEST_UNIT_RUN(test_range_for);
}
UTEST_TC_EXPORT(testcase, "components.libc.cpp.auto_tc", utest_tc_init, utest_tc_cleanup, 10);
