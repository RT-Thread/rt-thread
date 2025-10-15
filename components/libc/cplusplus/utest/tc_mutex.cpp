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
#include <thread>
#include <mutex>
#include <chrono>

/**
 * @brief Test basic mutex operations with lock_guard.
 */
static void test_mutex(void)
{
    std::mutex m;
    int        count = 0;
    auto       func  = [&]() mutable {
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

    uassert_int_equal(count, 2000);
}

/**
 * @brief Test recursive mutex allowing multiple locks by the same thread.
 */
static void test_recursive_mutex(void)
{
    std::recursive_mutex rm;
    int                  count = 0;
    auto                 func  = [&]() mutable {
        std::lock_guard<std::recursive_mutex> lock1(rm);
        std::lock_guard<std::recursive_mutex> lock2(rm);
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
        uassert_false(true);
    }
    uassert_true(true);
}

/**
 * @brief Test try_lock on mutex.
 */
static void test_try_lock(void)
{
    std::mutex m;
    if (m.try_lock())
    {
        m.unlock();
        uassert_true(true);
    }
    else
    {
        uassert_false(true);
    }
}

/**
 * @brief Test locking multiple mutexes with std::lock.
 */
static void test_lock_multiple(void)
{
    std::mutex m1, m2;
    std::lock(m1, m2);
    m1.unlock();
    m2.unlock();
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
    /* Test basic mutex operations with lock_guard */
    UTEST_UNIT_RUN(test_mutex);
    /* Test recursive mutex allowing multiple locks by the same thread */
    UTEST_UNIT_RUN(test_recursive_mutex);
    /* Test try_lock on mutex */
    UTEST_UNIT_RUN(test_try_lock);
    /* Test locking multiple mutexes with std::lock */
    UTEST_UNIT_RUN(test_lock_multiple);
}
UTEST_TC_EXPORT(testcase, "components.libc.cpp.mutex_tc", utest_tc_init, utest_tc_cleanup, 10);
