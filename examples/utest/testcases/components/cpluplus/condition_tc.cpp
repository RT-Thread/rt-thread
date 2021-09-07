/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-06     liukang      the first version
 */

#include <rtthread.h>
#include "utest.h"
#include <thread>
#include <mutex>
#include <condition_variable>
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

class TestConditon
{
    using scoped_lock = std::lock_guard<std::mutex>;
    using unique_lock = std::unique_lock<std::mutex>;

public:
    void test1()
    {
        scoped_time st;
        count_ = 10;
        std::thread t([this]
                      {
                          scoped_lock lock(mutex_);
                          while (count_ > 0)
                          {
                              --count_;
                              std::this_thread::sleep_for(std::chrono::milliseconds(100));
                          }
                          condition_.notify_one();
                      });
        t.detach();

        unique_lock lock(mutex_);
        condition_.wait(lock, [this]
                        { return count_ == 0; });
        auto span = st.span();
        if (span < 1000 || span > 1500)
        {
            uassert_false(1);
        }
    }

    void test2()
    {
        count_ = 5;
        std::thread t([this]
                      {
                          // notify 10 times in the first 1s
                          for (int i = 0; i < 5; ++i)
                          {
                              {
                                  scoped_lock lock(mutex_);
                                  --count_;
                              }
                              condition_.notify_one();
                              std::this_thread::sleep_for(std::chrono::milliseconds(100));
                          }
                          if (count_ != 0)
                          {
                              uassert_false(1);
                          }

                          // wait 2s
                          std::this_thread::sleep_for(std::chrono::milliseconds(2000));

                          // notify again
                          {
                              scoped_lock lock(mutex_);
                              --count_;
                          }

                          if (count_ != -1)
                          {
                              uassert_false(1);
                          }
                          condition_.notify_one();
                      });
        t.detach();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        int timeout_count = 0;
        int no_timeout_count = 0;
        unique_lock lock(mutex_);
        while (count_ >= 0)
        {
            auto status = condition_.wait_for(lock, std::chrono::milliseconds(1000));
            if (status == std::cv_status::timeout)
            {
                ++timeout_count;
            }
            else
            {
                ++no_timeout_count;
            }
        }
        if (timeout_count != 1)
        {
            uassert_false(1);
        }
        if (no_timeout_count != 1)
        {
            uassert_false(1);
        }
    }

private:
    int count_ = 0;
    std::mutex mutex_;
    std::condition_variable condition_;
};

static void test_condition(void)
{
    TestConditon tc;
    tc.test1();
    tc.test2();

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
    UTEST_UNIT_RUN(test_condition);
}
UTEST_TC_EXPORT(testcase, "components.cplusplus.condition_tc", utest_tc_init, utest_tc_cleanup, 10);
