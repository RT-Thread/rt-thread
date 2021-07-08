/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-16     MurphyZhao   the first version
 */

#include <rtthread.h>
#include "utest.h"

static void test_assert_pass(void)
{
    uassert_true(1);
    uassert_false(0);

    uassert_null(RT_NULL);
    uassert_not_null(!RT_NULL);

    uassert_int_equal(1, 1);
    uassert_int_not_equal(1, 2);

    uassert_str_equal("Hello RT-Thread!", "Hello RT-Thread!");
    uassert_str_not_equal("Hello RT-Thread!", "Hello");

    uassert_in_range(2048, 1024, 4096);
    uassert_not_in_range(0, 1024, 4096);
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
    UTEST_UNIT_RUN(test_assert_pass);
}
UTEST_TC_EXPORT(testcase, "testcases.utest.pass_tc", utest_tc_init, utest_tc_cleanup, 10);
