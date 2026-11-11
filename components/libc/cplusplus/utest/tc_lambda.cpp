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

/**
 * @brief Test basic lambda expression.
 */
static void test_lambda_basic(void)
{
    auto lambda = []() { return 42; };
    if (lambda() != 42)
    {
        uassert_false(true);
    }
    uassert_true(true);
}

/**
 * @brief Test lambda with capture.
 */
static void test_lambda_capture(void)
{
    int x = 10;
    auto lambda = [x]() { return x * 2; };
    if (lambda() != 20)
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
    /* Test basic lambda expression */
    UTEST_UNIT_RUN(test_lambda_basic);
    /* Test lambda with capture */
    UTEST_UNIT_RUN(test_lambda_capture);
}
UTEST_TC_EXPORT(testcase, "components.libc.cpp.lambda_tc", utest_tc_init, utest_tc_cleanup, 10);
