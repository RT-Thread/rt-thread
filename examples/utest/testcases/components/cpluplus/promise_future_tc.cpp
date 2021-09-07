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
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <future>
#include <cassert>

class timed_worker
{
public:
    timed_worker() : interval_(0), thread_(nullptr), promise_(nullptr) {}
    ~timed_worker() { assert(thread_ == nullptr); }

    timed_worker(const timed_worker &&) = delete;
    timed_worker &operator=(const timed_worker &&) = delete;

    void set_interval(size_t interval) { interval_ = interval; }

    void start(std::function<void()> func)
    {
        assert(interval_ > 0);
        std::lock_guard<std::mutex> lock(mutex_);
        if (thread_ != nullptr)
        {
            return;
        }

        promise_ = new std::promise<int>;
        auto future = promise_->get_future();
        if (!future.valid())
        {
            uassert_false(1);
        }
        thread_ = new std::thread([this, future = std::move(future), func = std::move(func)]() mutable
                                  {
                                      //printf("$$$ timed_worker::start\n");
                                      std::future_status status;
                                      do
                                      {
                                          status = future.wait_for(std::chrono::milliseconds(interval_));
                                          if (status == std::future_status::timeout)
                                          {
                                              //printf("$$$ timed_worker timeout\n");
                                              if (func)
                                              {
                                                  func();
                                              }
                                          }
                                          else
                                          {
                                              //printf("$$$ timed_worker ready\n");
                                          }
                                      } while (status != std::future_status::ready);
                                      //printf("$$$ timed_worker::stop\n");
                                      if (!future.valid())
                                      {
                                          uassert_false(1);
                                      }
                                      int val = future.get();
                                      if (val != 999)
                                      {
                                          uassert_false(1);
                                      }
                                      if (future.valid())
                                      {
                                          uassert_false(1);
                                      }
                                  });
    }

    void stop()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (thread_ == nullptr)
        {
            return;
        }

        promise_->set_value(999);
        thread_->join();
        delete thread_;
        delete promise_;
        thread_ = nullptr;
        promise_ = nullptr;
    }

private:
    std::atomic<size_t> interval_;
    std::thread *thread_;
    std::promise<int> *promise_;
    std::mutex mutex_;
};

int g_count = 0;

static void start_timed_worker(timed_worker &worker)
{
    worker.set_interval(200);
    worker.start([]
                 { ++g_count; });
}

static void stop_timed_worker(timed_worker &worker)
{
    worker.stop();
}

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

static void test_promise_future_basic(void)
{
    if (g_count != 0)
    {
        uassert_false(1);
    }

    timed_worker worker;
    start_timed_worker(worker);
    std::this_thread::sleep_for(std::chrono::milliseconds(2150));
    stop_timed_worker(worker);

    if (g_count != 10)
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void test_promise_future_void(void)
{
    scoped_time st;
    g_count = 0;

    std::promise<void> pro;
    std::future<void> fut = pro.get_future();
    std::thread t([&]() mutable
                  {
                      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                      g_count = 10;
                      pro.set_value();
                  });
    t.detach();

    fut.wait();
    auto span = st.span();

    if (g_count != 10)
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
    UTEST_UNIT_RUN(test_promise_future_basic);
    UTEST_UNIT_RUN(test_promise_future_void);
}
UTEST_TC_EXPORT(testcase, "components.cplusplus.promise_future_tc", utest_tc_init, utest_tc_cleanup, 10);

