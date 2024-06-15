/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-30     Shell        init ver.
 */

/**
 * Test Case for rt_completion API
 *
 * The test simulates a producer-consumer interaction where a producer thread
 * generates data, and a consumer thread consumes the data after waiting for its
 * availability using rt_completion synchronization primitives.
 *
 * Test Criteria:
 * - The producer produces data correctly and notifies the consumer thread.
 * - The consumer receives data correctly and acknowledges receipt to the
 *   producer.
 * - The producer and consumer threads synchronize their operations effectively.
 * - Verify the correctness of data production and consumption between producer
 *   and consumer threads.
 * - The asynchronous woken of consumer thread was handled properly so the
 *   consumer don't lose woken from producer.
 *
 * Test APIs:
 * - rt_completion_init()
 * - rt_completion_wakeup()
 * - rt_completion_wait_flags()
 */

#define TEST_LATENCY_TICK (1)
#define TEST_LOOP_TIMES   (60 * RT_TICK_PER_SECOND)
#define TEST_PROGRESS_ON  (RT_TICK_PER_SECOND)

#include "utest.h"

#include <ipc/completion.h>
#include <rtthread.h>
#include <stdlib.h>

static struct rt_completion _prod_completion;
static struct rt_completion _cons_completion;
static int _test_data;
static int _async_intr_count;
static rt_atomic_t _progress_counter;
static struct rt_semaphore _thr_exit_sem;

static void _test_thread_exit_failure(char *string)
{
    LOG_E("\t[TEST failed] %s", string);

    rt_sem_release(&_thr_exit_sem);
    rt_thread_delete(rt_thread_self());
}

static void done_safely(struct rt_completion *completion)
{
    rt_err_t error;

    /* Signal completion */
    error = rt_completion_wakeup(completion);

    /* try again if failed to produce */
    if (error == -RT_EEMPTY)
    {
        rt_thread_yield();
    }
    else if (error)
    {
        uassert_true(error == RT_EOK);
        _test_thread_exit_failure("unexpected error");
    }
}

static void wait_safely(struct rt_completion *completion)
{
    int try_times = 3;
    rt_err_t error;
    do
    {
        /* wait for one tick, to add more random */
        error = rt_completion_wait_flags(completion, 1, RT_INTERRUPTIBLE);
        if (error)
        {
            if (error == -RT_ETIMEOUT || error == -RT_EINTR)
            {
                _async_intr_count++;
            }
            else
            {
                LOG_I("Async event %d\n", error);
                uassert_true(0);
            }
            rt_thread_yield();
        }
        else
        {
            break;
        }
    } while (try_times--);

    if (error != RT_EOK)
    {
        uassert_true(error == RT_EOK);
        _test_thread_exit_failure("wait failed");
    }
}

static void producer_thread_entry(void *parameter)
{
    for (size_t i = 0; i < TEST_LOOP_TIMES; i++)
    {
        /* Produce data */
        _test_data++;

        /* Delay before producing next data */
        rt_thread_delay(TEST_LATENCY_TICK);

        /* notify consumer */
        done_safely(&_prod_completion);

        /* sync with consumer */
        wait_safely(&_cons_completion);
    }

    rt_sem_release(&_thr_exit_sem);
}

static void consumer_thread_entry(void *parameter)
{
    int local_test_data = 0;

    rt_thread_startup(parameter);

    for (size_t i = 0; i < TEST_LOOP_TIMES; i++)
    {
        /* Wait for data update */
        wait_safely(&_prod_completion);

        /* Consume data */
        if (local_test_data + 1 != _test_data)
        {
            LOG_I("local test data is %d, shared test data is %d",
                  local_test_data, _test_data);
            uassert_true(0);
        }
        else if (rt_atomic_add(&_progress_counter, 1) % TEST_PROGRESS_ON == 0)
        {
            uassert_true(1);
        }

        local_test_data = _test_data;
        done_safely(&_cons_completion);
    }

    rt_sem_release(&_thr_exit_sem);
}

rt_thread_t _watching_thread1;
rt_thread_t _watching_thread2;

static void testcase(void)
{
    /* Initialize completion object */
    rt_completion_init(&_prod_completion);
    rt_completion_init(&_cons_completion);

    /* Create producer and consumer threads */
    rt_thread_t producer_thread =
        rt_thread_create("producer", producer_thread_entry, RT_NULL,
                         UTEST_THR_STACK_SIZE, UTEST_THR_PRIORITY, 100);
    rt_thread_t consumer_thread =
        rt_thread_create("consumer", consumer_thread_entry, producer_thread,
                         UTEST_THR_STACK_SIZE, UTEST_THR_PRIORITY, 100);
    uassert_true(producer_thread != RT_NULL);
    uassert_true(consumer_thread != RT_NULL);
    _watching_thread1 = consumer_thread;
    _watching_thread2 = producer_thread;

    rt_thread_startup(consumer_thread);

    for (size_t i = 0; i < 2; i++)
    {
        rt_sem_take(&_thr_exit_sem, RT_WAITING_FOREVER);
    }

    LOG_I("Summary:\n"
          "\tTest times: %ds(%d times)\n"
          "\tAsync interruption count: %d\n",
          TEST_LOOP_TIMES / RT_TICK_PER_SECOND, TEST_LOOP_TIMES,
          _async_intr_count);
}

static rt_err_t utest_tc_init(void)
{
    _test_data = 0;
    _progress_counter = 0;
    _async_intr_count = 0;
    rt_sem_init(&_thr_exit_sem, "test", 0, RT_IPC_FLAG_PRIO);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_detach(&_thr_exit_sem);
    return RT_EOK;
}

UTEST_TC_EXPORT(testcase, "testcases.drivers.ipc.rt_completion.timeout",
                utest_tc_init, utest_tc_cleanup, 1000);
