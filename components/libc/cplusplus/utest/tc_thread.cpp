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


/**
 * @brief Function to test thread functionality.
 */
static void test_thread(void)
{
    int count = 0;

    /* Lambda function to increment the count. */
    auto func = [&]() mutable {
        for (int i = 0; i < 100; ++i)
        {
            ++count;
        }
    };

    /* Create and run a thread executing the lambda function. */
    std::thread t1(func);
    /* Wait for the thread to finish execution. */
    t1.join();

    /* Verify if the count is as expected after the first thread execution. */
    if (count != 100)
    {
        uassert_false(1);
    }

    /* Create and run another thread executing the same lambda function. */
    std::thread t2(func);
    t2.join();

    if (count != 200)
    {
        uassert_false(1);
    }

    /* If both assertions passed, the test is successful. */
    uassert_true(1);
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
    UTEST_UNIT_RUN(test_thread);
}

/* Export the test case with initialization and cleanup functions and a timeout of 10 ticks. */
UTEST_TC_EXPORT(testcase, "components.libc.cpp.thread_tc", utest_tc_init, utest_tc_cleanup, 10);