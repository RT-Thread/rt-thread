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
#include <mutex>

static void test_mutex(void) 
{
    std::mutex m;
    int count = 0;
    auto func = [&] () mutable 
    {
        std::lock_guard<std::mutex> lock(m);
        for (int i = 0; i < 1000; ++i) 
        {
            ++count;
        }
    };

    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    if (count != 2000)
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
    UTEST_UNIT_RUN(test_mutex);
}
UTEST_TC_EXPORT(testcase, "components.cplusplus.mutex_tc", utest_tc_init, utest_tc_cleanup, 10);
