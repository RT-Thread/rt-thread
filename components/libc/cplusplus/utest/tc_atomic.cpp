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
#include <atomic>
#include <cstdint>

/**
 * @brief Test load and store operations for int32_t atomic variables in multi-threaded environment.
 *        Verifies atomicity by performing increment and decrement operations concurrently.
 */
static void test_atomic_load_store_int32(void)
{
    constexpr int        kRound = 10000000;
    std::atomic<int32_t> thread_count(0);
    std::atomic<int32_t> count(100);
    uassert_int_equal(count.load(), 100);

    auto func1 = [&]() mutable {
        for (int i = 0; i < kRound; ++i)
        {
            ++count;
        }
        ++thread_count;
    };

    auto func2 = [&]() mutable {
        for (int i = 0; i < kRound; ++i)
        {
            --count;
        }
        ++thread_count;
    };

    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();

    uassert_int_equal(count.load(), 100);
    uassert_int_equal(thread_count.load(), 2);
}

/**
 * @brief Test load and store operations for int64_t atomic variables in multi-threaded environment.
 *        Verifies atomicity by performing increment and decrement operations concurrently.
 */
static void test_atomic_load_store_int64(void)
{
    constexpr int        kRound = 10000000;
    std::atomic<int64_t> thread_count(0);
    std::atomic<int64_t> count(100);
    uassert_int_equal(count.load(), 100);

    auto func1 = [&]() mutable {
        for (int i = 0; i < kRound; ++i)
        {
            ++count;
        }
        ++thread_count;
    };

    auto func2 = [&]() mutable {
        for (int i = 0; i < kRound; ++i)
        {
            --count;
        }
        ++thread_count;
    };

    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();

    uassert_int_equal(count.load(), 100);
    uassert_int_equal(thread_count.load(), 2);
}

/**
 * @brief Test basic atomic operations for int32_t, including load, store, fetch_add, fetch_sub,
 *        fetch_and, fetch_or, fetch_xor, exchange, and compare_exchange_strong.
 */
static void test_atomic_basic_int32(void)
{
    std::atomic<int32_t> val;
    val = 10;
    uassert_int_equal(val.load(), 10);

    val++;
    uassert_int_equal(val.load(), 11);

    val--;
    uassert_int_equal(val.load(), 10);

    auto a = val.load();
    val.store(a);
    val.fetch_add(1);
    uassert_int_equal(val.load(), 11);
    val.fetch_sub(1);
    uassert_int_equal(val.load(), 10);

    val.fetch_and(14);
    uassert_int_equal(val.load(), 10);

    val.fetch_or(11); //1010
    uassert_int_equal(val.load(), 11);

    val.fetch_xor(4);
    uassert_int_equal(val.load(), 15);

    val.exchange(1);
    uassert_int_equal(val.load(), 1);

    int32_t x         = 2;
    int32_t y         = 3;
    bool    exchanged = val.compare_exchange_strong(x, y);
    uassert_false(exchanged);
    uassert_int_equal(val.load(), 1);
    uassert_int_equal(x, 1);
    exchanged = val.compare_exchange_strong(x, y);
    uassert_true(exchanged);
    uassert_int_equal(val.load(), 3);
    uassert_int_equal(x, 1);
}

/**
 * @brief Test basic atomic operations for int64_t, including load, store, fetch_add, fetch_sub,
 *        fetch_and, fetch_or, fetch_xor, exchange, and compare_exchange_strong.
 */
static void test_atomic_basic_int64(void)
{
    std::atomic<int64_t> val;
    val = 10;
    uassert_int_equal(val.load(), 10);

    val++;
    uassert_int_equal(val.load(), 11);

    val--;
    uassert_int_equal(val.load(), 10);

    auto a = val.load();
    val.store(a);
    val.fetch_add(1);
    uassert_int_equal(val.load(), 11);
    val.fetch_sub(1);
    uassert_int_equal(val.load(), 10);

    val.fetch_and(14);
    uassert_int_equal(val.load(), 10);

    val.fetch_or(11); //1010
    uassert_int_equal(val.load(), 11);

    val.fetch_xor(4);
    uassert_int_equal(val.load(), 15);

    val.exchange(1);
    uassert_int_equal(val.load(), 1);

    int64_t x         = 2;
    int64_t y         = 3;
    bool    exchanged = val.compare_exchange_strong(x, y);
    uassert_false(exchanged);
    uassert_int_equal(val.load(), 1);
    uassert_int_equal(x, 1);
    exchanged = val.compare_exchange_strong(x, y);
    uassert_true(exchanged);
    uassert_int_equal(val.load(), 3);
    uassert_int_equal(x, 1);
}

/**
 * @brief Test atomic operations for bool type, including store, load, exchange, and compare_exchange_strong.
 */
static void test_atomic_bool(void)
{
    std::atomic<bool> flag(false);
    flag.store(true);
    uassert_true(flag.load());
    flag.exchange(false);
    uassert_false(flag.load());
    bool expected = false;
    bool desired  = true;
    uassert_true(flag.compare_exchange_strong(expected, desired));
    uassert_true(flag.load());
}

/**
 * @brief Test atomic operations for pointer type (int*), including store, load, and exchange.
 */
static void test_atomic_pointer(void)
{
    int                a = 1, b = 2;
    std::atomic<int *> ptr(&a);
    ptr.store(&b);
    uassert_int_equal(*ptr.load(), 2);
    int *old = ptr.exchange(&a);
    uassert_ptr_equal(old, &b);
    uassert_int_equal(*ptr.load(), 1);
}

/**
 * @brief Test memory ordering constraints using memory_order_release and memory_order_acquire.
 */
static void test_memory_order(void)
{
    std::atomic<int> x(0);
    std::atomic<int> y(0);
    // Simple test for memory order
    x.store(1, std::memory_order_release);
    y.store(2, std::memory_order_release);
    uassert_int_equal(x.load(std::memory_order_acquire), 1);
    uassert_int_equal(y.load(std::memory_order_acquire), 2);
}

/**
 * @brief Test compare_exchange_weak operation, which may fail spuriously and requires looping.
 */
static void test_compare_exchange_weak(void)
{
    std::atomic<int> val(1);
    int              expected = 1;
    int              desired  = 2;
    while (!val.compare_exchange_weak(expected, desired))
    {
        expected = 1; // reset
    }
    uassert_int_equal(val.load(), 2);
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
    /* Test load and store operations for int32_t atomic variables in multi-threaded environment */
    UTEST_UNIT_RUN(test_atomic_load_store_int32);
    /* Test load and store operations for int64_t atomic variables in multi-threaded environment */
    UTEST_UNIT_RUN(test_atomic_load_store_int64);
    /* Test basic atomic operations for int32_t */
    UTEST_UNIT_RUN(test_atomic_basic_int32);
    /* Test basic atomic operations for int64_t */
    UTEST_UNIT_RUN(test_atomic_basic_int64);
    /* Test atomic operations for bool type */
    UTEST_UNIT_RUN(test_atomic_bool);
    /* Test atomic operations for pointer type */
    UTEST_UNIT_RUN(test_atomic_pointer);
    /* Test memory ordering constraints */
    UTEST_UNIT_RUN(test_memory_order);
    /* Test compare_exchange_weak operation */
    UTEST_UNIT_RUN(test_compare_exchange_weak);
}
UTEST_TC_EXPORT(testcase, "components.libc.cpp.atomic_tc", utest_tc_init, utest_tc_cleanup, 10);
