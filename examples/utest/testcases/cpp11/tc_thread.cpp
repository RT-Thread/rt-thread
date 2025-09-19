/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-03     liukang      the first version
 */

#include <rtthread.h>
#include "utest.h"
#include <thread>

static void test_thread(void)
{
    int count = 0;
    auto func = [&]() mutable
    {
        for (int i = 0; i < 100; ++i)
        {
            ++count;
        }
    };

    std::thread t1(func);
    t1.join();

    if (count != 100)
    {
        uassert_false(1);
    }

    std::thread t2(func);
    t2.join();

    if (count != 200)
    {
        uassert_false(1);
    }

    uassert_true(1);
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
    UTEST_UNIT_RUN(test_thread);
}
UTEST_TC_EXPORT(testcase, "testcases.cpp11.thread_tc", utest_tc_init, utest_tc_cleanup, 10);
