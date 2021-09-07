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
#include <atomic>
#include <cstdint>

static void test_atomic_load_sotre_int32(void) 
{
    constexpr int kRound = 10000000;
    std::atomic<int32_t> thread_count(0);
    std::atomic<int32_t> count(100);
    if (count != 100) {
        uassert_false(1);
    }

    auto func1 = [&] () mutable 
    {
        for (int i = 0; i < kRound; ++i) 
        {
            ++count;
        }
        ++thread_count;
    };

    auto func2 = [&] () mutable 
    {
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

    if (count != 100) 
    {
        uassert_false(1);
    }

    if (thread_count != 2) 
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void test_atomic_load_sotre_int64(void) 
{
    constexpr int kRound = 10000000;
    std::atomic<int64_t> thread_count(0);
    std::atomic<int64_t> count(100);
    if (count != 100) {
        uassert_false(1);
    }

    auto func1 = [&] () mutable 
    {
        for (int i = 0; i < kRound; ++i) 
        {
            ++count;
        }
        ++thread_count;
    };

    auto func2 = [&] () mutable 
    {
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

    if (count != 100) 
    {
        uassert_false(1);
    }

    if (thread_count != 2) 
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void test_atmic_basic_int32(void) 
{
    std::atomic<int32_t> val;
    val = 10;
    if (val.load() != 10)
    {
        uassert_false(1);
    }

    val++;

    if (val.load() != 11)
    {
        uassert_false(1);
    }

    val--;
    if (val.load() != 10)
    {
        uassert_false(1);
    }

    auto a = val.load();
    val.store(a);
    val.fetch_add(1);
    if (val.load() != 11)
    {
        uassert_false(1);
    }
    val.fetch_sub(1);
    if (val.load() != 10)
    {
        uassert_false(1);
    }

    val.fetch_and(14);
    if (val.load() != 10)
    {
        uassert_false(1);
    }

    val.fetch_or(11);//1010
    if (val.load() != 11)
    {
        uassert_false(1);
    }

    val.fetch_xor(4);
    if (val.load() != 15)
    {
        uassert_false(1);
    }

    val.exchange(1);
    if (val.load() != 1)
    {
        uassert_false(1);
    }

    int32_t x = 2;
    int32_t y = 3;
    bool exchanged = val.compare_exchange_strong(x, y);
    if (exchanged)
    {
        uassert_false(1);
    }
    if (val.load() != 1 || x != 1)
    {
        uassert_false(1);
    }
    exchanged = val.compare_exchange_strong(x, y);
    if (!exchanged)
    {
        uassert_false(1);
    }
    if (val.load() != 3 || x != 1)
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void test_atmic_basic_int64(void) 
{
    std::atomic<int64_t> val;
    val = 10;
    if (val.load() != 10)
    {
        uassert_false(1);
    }

    val++;
    if (val.load() != 11)
    {
        uassert_false(1);
    }

    val--;
    if (val.load() != 10)
    {
        uassert_false(1);
    }

    auto a = val.load();
    val.store(a);
    val.fetch_add(1);
    if (val.load() != 11)
    {
        uassert_false(1);
    }
    val.fetch_sub(1);
    if (val.load() != 10)
    {
        uassert_false(1);
    }

    val.fetch_and(14);
    if (val.load() != 10)
    {
        uassert_false(1);
    }

    val.fetch_or(11);//1010
    if (val.load() != 11)
    {
        uassert_false(1);
    }

    val.fetch_xor(4);
    if (val.load() != 15)
    {
        uassert_false(1);
    }

    val.exchange(1);
    if (val.load() != 1)
    {
        uassert_false(1);
    }

    int64_t x = 2;
    int64_t y = 3;
    bool exchanged = val.compare_exchange_strong(x, y);
    if (exchanged)
    {
        uassert_false(1);
    }
    if (val.load() != 1 || x != 1)
    {
        uassert_false(1);
    }
    exchanged = val.compare_exchange_strong(x, y);
    if (!exchanged)
    {
        uassert_false(1);
    }
    if (val.load() != 3 || x != 1)
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
    UTEST_UNIT_RUN(test_atomic_load_sotre_int32);
    UTEST_UNIT_RUN(test_atomic_load_sotre_int64);
    UTEST_UNIT_RUN(test_atmic_basic_int32);
    UTEST_UNIT_RUN(test_atmic_basic_int32);
}
UTEST_TC_EXPORT(testcase, "components.cplusplus.atomic_tc", utest_tc_init, utest_tc_cleanup, 10);
