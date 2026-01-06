/*
 * Copyright (c) 2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-02     Rbb666       utest case for rt_thread_suspend comprehensive tests
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#define THREAD_STACK_SIZE    1024
#define THREAD_TIMESLICE     5
#define TEST_THREAD_PRIORITY 25

/* Global variables for normal usage test */
static rt_thread_t          target_thread     = RT_NULL;
static rt_thread_t          monitor_thread    = RT_NULL;
static rt_sem_t             sync_sem          = RT_NULL;
static volatile rt_uint32_t work_counter      = 0;
static volatile rt_bool_t   suspend_test_done = RT_FALSE;
static volatile rt_bool_t   suspend_success   = RT_FALSE;
static volatile rt_bool_t   resume_success    = RT_FALSE;

/* Global variables for deadlock test */
static rt_mutex_t           test_mutex         = RT_NULL;
static rt_thread_t          holder_thread      = RT_NULL;
static rt_thread_t          waiter_thread      = RT_NULL;
static volatile rt_uint32_t shared_counter     = 0;
static volatile rt_bool_t   holder_got_mutex   = RT_FALSE;
static volatile rt_bool_t   deadlock_detected  = RT_FALSE;
static volatile rt_bool_t   test_completed     = RT_FALSE;
static volatile rt_bool_t   thread_started     = RT_FALSE;
static volatile rt_bool_t   thread_should_exit = RT_FALSE;

/* Target work thread - the thread to be suspended */
static void target_work_thread(void *parameter)
{
    while (1)
    {
        if (!suspend_test_done)
        {
            work_counter++;
        }
        /* Yield CPU appropriately to simulate normal work */
        rt_thread_mdelay(10);
    }
}

/* Monitor thread - responsible for suspending and resuming target thread */
static void monitor_control_thread(void *parameter)
{
    rt_uint32_t counter_before, counter_after;

    /* Wait for target thread to start working */
    rt_thread_mdelay(300);

    /* Record counter value before suspend */
    counter_before = work_counter;

    /* Use rt_thread_suspend to suspend target thread */
    if (rt_thread_suspend(target_thread) == RT_EOK)
    {
        suspend_success = RT_TRUE;

        /* Trigger scheduling to ensure thread is suspended */
        rt_schedule();

        /* Wait for a while to verify thread is indeed suspended */
        rt_thread_mdelay(500);

        counter_after = work_counter;

        /* Verify thread is indeed suspended (counter should stop changing) */
        if (counter_after == counter_before)
        {
            /* Resume target thread */
            if (rt_thread_resume(target_thread) == RT_EOK)
            {
                resume_success = RT_TRUE;
                /* Wait for a while to verify thread resumes work */
                rt_thread_mdelay(200);
            }
        }
    }

    /* End test */
    suspend_test_done = RT_TRUE;

    /* Send semaphore to notify test completion */
    rt_sem_release(sync_sem);

    /* Keep running until deleted */
    while (1)
    {
        rt_thread_mdelay(100);
    }
}

/* Thread that holds the mutex */
static void mutex_holder_thread(void *parameter)
{
    if (rt_mutex_take(test_mutex, RT_WAITING_FOREVER) == RT_EOK)
    {
        holder_got_mutex = RT_TRUE;

        /* Simulate critical section work */
        for (int i = 0; i < 1000 && !test_completed; i++)
        {
            shared_counter++;
            if (i % 200 == 0)
            {
                rt_thread_mdelay(10);
            }
        }

        if (!test_completed)
        {
            rt_mutex_release(test_mutex);
        }
    }
    rt_kprintf("Holder thread exiting\n");

    /* Keep running until deleted */
    while (1)
    {
        rt_thread_mdelay(100);
    }
}

/* Thread that waits for the mutex */
static void mutex_waiter_thread(void *parameter)
{
    /* Wait a bit to ensure holder gets mutex first */
    rt_thread_mdelay(50);

    rt_err_t result = rt_mutex_take(test_mutex, rt_tick_from_millisecond(1500));
    if (result == RT_EOK)
    {
        shared_counter += 1000;
        rt_mutex_release(test_mutex);
    }
    else
    {
        /* Timeout indicates deadlock - holder is suspended and cannot release lock */
        deadlock_detected = RT_TRUE;
        rt_kprintf("Deadlock detected: waiter timeout (holder suspended with mutex)\n");
    }

    /* Keep running until deleted */
    while (1)
    {
        rt_thread_mdelay(100);
    }
}

void simple_thread_entry(void *param)
{
    volatile rt_bool_t *flag = (volatile rt_bool_t *)param;
    *flag                    = RT_TRUE;

    /* Keep the thread running until it's suspended and deleted */
    while (1)
    {
        rt_thread_mdelay(100);
    }
}

/* Test normal usage of rt_thread_suspend function */
static void test_suspend_force_normal_usage(void)
{
    /* Reset global variables */
    work_counter      = 0;
    suspend_test_done = RT_FALSE;
    suspend_success   = RT_FALSE;
    resume_success    = RT_FALSE;

    /* Create synchronization semaphore */
    sync_sem = rt_sem_create("sync", 0, RT_IPC_FLAG_FIFO);
    uassert_not_null(sync_sem);

    /* Create target work thread */
    target_thread = rt_thread_create("target",
                                     target_work_thread,
                                     RT_NULL,
                                     THREAD_STACK_SIZE,
                                     TEST_THREAD_PRIORITY,
                                     THREAD_TIMESLICE);

    uassert_not_null(target_thread);

    /* Create monitor thread */
    monitor_thread = rt_thread_create("monitor",
                                      monitor_control_thread,
                                      RT_NULL,
                                      THREAD_STACK_SIZE,
                                      UTEST_THR_PRIORITY,
                                      THREAD_TIMESLICE);

    uassert_not_null(monitor_thread);

    /* Start threads */
    rt_thread_startup(target_thread);
    rt_thread_startup(monitor_thread);

    /* Wait for test completion */
    rt_sem_take(sync_sem, RT_WAITING_FOREVER);

    /* Wait for a while to ensure threads exit normally */
    rt_thread_mdelay(100);

    /* Verify test results */
    uassert_true(suspend_success);
    uassert_true(resume_success);
    uassert_true(work_counter > 0);

    /* Clean up resources */
    if (sync_sem)
    {
        rt_sem_delete(sync_sem);
        sync_sem = RT_NULL;
    }

    /* Delete threads */
    if (target_thread != RT_NULL)
    {
        rt_thread_delete(target_thread);
        target_thread = RT_NULL;
    }

    if (monitor_thread != RT_NULL)
    {
        rt_thread_delete(monitor_thread);
        monitor_thread = RT_NULL;
    }
}

/* Basic API test */
static void test_suspend_force_api_basic(void)
{
    rt_thread_t api_thread;

    /* Reset global variables */
    thread_started     = RT_FALSE;
    thread_should_exit = RT_FALSE;

    /* Create a simple test thread */
    api_thread = rt_thread_create("api_test",
                                  simple_thread_entry,
                                  (void *)&thread_started,
                                  THREAD_STACK_SIZE,
                                  UTEST_THR_PRIORITY,
                                  THREAD_TIMESLICE);

    uassert_not_null(api_thread);

    rt_thread_startup(api_thread);
    rt_thread_mdelay(50); /* Wait for thread to start */

    uassert_true(thread_started);

    /* Test basic suspend functionality */
    rt_err_t result = rt_thread_suspend(api_thread);
    uassert_true(result == RT_EOK);

    rt_schedule();
    rt_thread_mdelay(100);

    /* Resume thread */
    result = rt_thread_resume(api_thread);
    uassert_true(result == RT_EOK);

    rt_thread_mdelay(50);

    /* Clean up - delete the thread directly */
    if (api_thread != RT_NULL)
    {
        rt_thread_delete(api_thread);
        api_thread = RT_NULL;
    }

    /* Reset global variables for next test */
    thread_started     = RT_FALSE;
    thread_should_exit = RT_FALSE;
}

/* Test suspend on thread that is created but not started */
static void test_suspend_force_not_started_thread(void)
{
    rt_thread_t not_started_thread;

    /* Create a thread but don't start it */
    not_started_thread = rt_thread_create("not_started",
                                          simple_thread_entry,
                                          (void *)&thread_started,
                                          THREAD_STACK_SIZE,
                                          UTEST_THR_PRIORITY,
                                          THREAD_TIMESLICE);

    uassert_not_null(not_started_thread);

    /* Verify thread is in INIT state */
    uassert_true((RT_SCHED_CTX(not_started_thread).stat & RT_THREAD_STAT_MASK) == RT_THREAD_INIT);

    /* Try to suspend a thread that hasn't been started yet */
    rt_err_t suspend_result = rt_thread_suspend(not_started_thread);
    rt_schedule();
    uassert_true(suspend_result == -RT_ERROR);

    /* Try to resume the not-started thread */
    rt_err_t resume_result = rt_thread_resume(not_started_thread);
    uassert_true(resume_result == -RT_EINVAL);

    /* Now start the thread to see if it works normally */
    rt_err_t startup_result = rt_thread_startup(not_started_thread);
    uassert_true(startup_result == RT_EOK);

    /* Wait a bit to see if thread starts normally */
    rt_thread_mdelay(100);

    /* The thread should have started successfully despite previous suspend/resume calls */
    uassert_true(thread_started == RT_TRUE);

    /* Clean up */
    if (not_started_thread != RT_NULL)
    {
        rt_thread_delete(not_started_thread);
        not_started_thread = RT_NULL;
    }

    /* Reset flag for next test */
    thread_started = RT_FALSE;
}

/* Test deadlock risk */
static void test_suspend_force_deadlock_risk(void)
{
    /* Reset global variables */
    shared_counter    = 0;
    holder_got_mutex  = RT_FALSE;
    deadlock_detected = RT_FALSE;
    test_completed    = RT_FALSE;

    /* Create mutex */
    test_mutex = rt_mutex_create("test_mutex", RT_IPC_FLAG_PRIO);
    uassert_not_null(test_mutex);

    /* Create and start holder thread */
    holder_thread = rt_thread_create("holder", mutex_holder_thread, RT_NULL,
                                     THREAD_STACK_SIZE, UTEST_THR_PRIORITY, THREAD_TIMESLICE);
    uassert_not_null(holder_thread);
    rt_thread_startup(holder_thread);

    /* Create and start waiter thread */
    waiter_thread = rt_thread_create("waiter", mutex_waiter_thread, RT_NULL,
                                     THREAD_STACK_SIZE, UTEST_THR_PRIORITY + 1, THREAD_TIMESLICE);
    uassert_not_null(waiter_thread);
    /* Now start waiter thread, it will try to acquire mutex held by suspended thread */
    rt_thread_startup(waiter_thread);

    /* Wait for holder to get mutex */
    int timeout = 100; /* 1 second timeout */
    while (!holder_got_mutex && timeout-- > 0)
    {
        rt_thread_mdelay(10);
    }

    uassert_true(holder_got_mutex);

    /* This is the critical test! Suspend thread that holds the mutex */
    rt_err_t suspend_result = rt_thread_suspend(holder_thread);
    uassert_true(suspend_result == RT_EOK);
    rt_kprintf("Suspended holder thread (which holds the mutex)\n");

    rt_schedule();

    /* Wait for waiter thread to try acquiring lock */
    rt_thread_mdelay(2000);

    uassert_true(deadlock_detected == RT_TRUE);

    /* Resume thread */
    rt_err_t resume_result = rt_thread_resume(holder_thread);
    uassert_true(resume_result == RT_EOK);
    rt_kprintf("Resumed holder thread\n");

    test_completed = RT_TRUE;

    /* Wait for threads to complete */
    rt_thread_mdelay(1000);

    /* Verify rt_thread_suspend and rt_thread_resume executed successfully */
    uassert_true(suspend_result == RT_EOK);
    uassert_true(resume_result == RT_EOK);

    /* Verify system didn't crash, threads can work normally */
    uassert_true(shared_counter > 0);

    /* Clean up resources */
    if (test_mutex)
    {
        rt_mutex_delete(test_mutex);
        test_mutex = RT_NULL;
    }

    /* Delete threads */
    if (holder_thread != RT_NULL)
    {
        rt_thread_delete(holder_thread);
        holder_thread = RT_NULL;
    }

    if (waiter_thread != RT_NULL)
    {
        rt_thread_delete(waiter_thread);
        waiter_thread = RT_NULL;
    }

    /* Wait again to ensure threads are cleaned up */
    rt_thread_mdelay(200);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    /* Reset all global variables to ensure clean state between tests */
    work_counter       = 0;
    suspend_test_done  = RT_FALSE;
    suspend_success    = RT_FALSE;
    resume_success     = RT_FALSE;
    shared_counter     = 0;
    holder_got_mutex   = RT_FALSE;
    deadlock_detected  = RT_FALSE;
    test_completed     = RT_FALSE;
    thread_started     = RT_FALSE;
    thread_should_exit = RT_FALSE;

    /* Clean up any remaining resources - safety check */
    if (sync_sem != RT_NULL)
    {
        rt_sem_delete(sync_sem);
        sync_sem = RT_NULL;
    }

    if (test_mutex != RT_NULL)
    {
        rt_mutex_delete(test_mutex);
        test_mutex = RT_NULL;
    }

    /* Ensure all thread pointers are NULL */
    target_thread  = RT_NULL;
    monitor_thread = RT_NULL;
    holder_thread  = RT_NULL;
    waiter_thread  = RT_NULL;

    /* Give system time to complete cleanup */
    rt_thread_mdelay(50);

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_suspend_force_api_basic);
    UTEST_UNIT_RUN(test_suspend_force_not_started_thread);
    UTEST_UNIT_RUN(test_suspend_force_normal_usage);
    UTEST_UNIT_RUN(test_suspend_force_deadlock_risk);
}
UTEST_TC_EXPORT(testcase, "core.thread_suspend", utest_tc_init, utest_tc_cleanup, 30);

