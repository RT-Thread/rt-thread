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
#include <memory>

/**
 * @brief Test unique_ptr basic operations.
 */
static void test_unique_ptr(void)
{
    std::unique_ptr<int> p(new int(42));
    uassert_int_equal(*p, 42);
    *p = 24;
    uassert_int_equal(*p, 24);
}

/**
 * @brief Test shared_ptr basic operations.
 */
static void test_shared_ptr(void)
{
    std::shared_ptr<int> p1(new int(42));
    std::shared_ptr<int> p2 = p1;
    uassert_int_equal(*p1, 42);
    uassert_int_equal(*p2, 42);
    uassert_int_equal(p1.use_count(), 2);
}

/**
 * @brief Test case initialization function.
 * @return RT_EOK on success.
 */
static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

/**
 * @brief Test case cleanup function.
 * @return RT_EOK on success.
 */
static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

/**
 * @brief Main test case function that runs the test.
 */
static void testcase(void)
{
    /* Test unique_ptr basic operations */
    UTEST_UNIT_RUN(test_unique_ptr);
    /* Test shared_ptr basic operations */
    UTEST_UNIT_RUN(test_shared_ptr);
}

/* Export the test case with initialization and cleanup functions and a timeout of 10 ticks. */
UTEST_TC_EXPORT(testcase, "components.libc.cpp.smartptr_tc", utest_tc_init, utest_tc_cleanup, 10);