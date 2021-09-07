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
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <climits>
#include <limits>
#include <functional>

#include <fs_util.h>
#include <sys/stat.h>
#include <dirent.h>

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

class scoped_time
{
    using time_point = std::chrono::steady_clock::time_point;

public:
    scoped_time() { reset(); }
    ~scoped_time() {}

    void reset() { time_ = std::chrono::steady_clock::now(); }

    long long span() const
    {
        auto time = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(time - time_).count();
    }

private:
    time_point time_;
};

class file_info
{
public:
    bool is_dir() const
    {
        return S_ISDIR(st.st_mode);
    }

    bool is_regular() const
    {
        return S_ISREG(st.st_mode);
    }

    bool is_other() const
    {
        return !is_dir() && !is_regular();
    }

public:
    struct stat st;
    size_t depth;
    char pathname[PATH_MAX + 1];
};

static void test_time_run_thread_withsleep(void)
{
    int count = 0;
    auto func = [&] () mutable 
    {
        for (int i = 0; i < 100; ++i) 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            ++count;
        }
    };

    scoped_time st;
    std::thread t1(func);
    t1.join();
    auto span = st.span();

    if (count != 100)
    {
        uassert_false(1);
    }

    if (span < 1000 || span > 1500)
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
    UTEST_UNIT_RUN(test_time_run_thread_withsleep);
}
UTEST_TC_EXPORT(testcase, "components.cplusplus.time_tc", utest_tc_init, utest_tc_cleanup, 10);

