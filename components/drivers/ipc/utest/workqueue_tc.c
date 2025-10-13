/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-06     tyx          first commit
 * 2024-12-31     rbb666       Adding Test Cases
 */

#include "rtthread.h"
#include "rtdevice.h"
#include "utest.h"

#ifdef RT_USING_DEVICE_IPC

static rt_uint8_t get_test_thread_priority(rt_int8_t pos)
{
    rt_int16_t priority;

    priority =  RT_SCHED_PRIV(rt_thread_self()).init_priority;
    if (pos == 0)
    {
        return priority;
    }
    else
    {
        priority += pos;
    }
    if (priority < 0)
    {
        return 0;
    }
    else if (priority >= RT_THREAD_PRIORITY_MAX)
    {
        return RT_THREAD_PRIORITY_MAX - 1;
    }
    else
    {
        return (rt_uint8_t)priority;
    }
}

static void do_work_test_fun(struct rt_work *work, void *work_data)
{
    *((int *)work_data) = 1;
}

static void do_work_test(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 higher priority than the current test thread */
    curr_priority = get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    rt_work_init(&work, do_work_test_fun, (void *)&work_flag);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    /* Delay 5 ticks to ensure that the task has been executed */
    rt_thread_delay(5);
    uassert_int_equal(work_flag, 1);

    rt_thread_delay(100);
    rt_workqueue_destroy(queue);
}

static void do_delay_work_test_fun(struct rt_work *work, void *work_data)
{
    *((rt_tick_t *)work_data) = rt_tick_get();
}

static void do_delay_work_test(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile rt_tick_t work_start = 0;
    volatile rt_tick_t work_end = 0;
    rt_err_t err;

    /* 1 higher priority than the current test thread */
    curr_priority = get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    rt_work_init(&work, do_delay_work_test_fun, (void *)&work_end);
    work_start = rt_tick_get();
    /* Normal delayed work submission test */
    err = rt_workqueue_submit_work(queue, &work, 10);
    uassert_int_equal(err, RT_EOK);

    /* Ensure that the delayed work has been executed */
    rt_thread_delay(15);
    /* Check if the delayed task is executed after 10 ticks */
    if (work_end < work_start || work_end - work_start < 10)
    {
        uassert_false(1);
    }
    rt_thread_delay(100);
    rt_workqueue_destroy(queue);
}

static void cancle_work_test01_fun(struct rt_work *work, void *work_data)
{
    *((int *)work_data) = 1;
}

static void cancle_work_test01(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 lower priority than the current test thread */
    curr_priority = get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    work_flag = 0;
    rt_work_init(&work, cancle_work_test01_fun, (void *)&work_flag);
    /* Cancel the work before it is executed */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    /* Cancel Now */
    err = rt_workqueue_cancel_work(queue, &work);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(5);
    uassert_int_equal(work_flag, 0);

    rt_thread_delay(100);
    rt_workqueue_destroy(queue);
}

static void cancle_work_test02_fun(struct rt_work *work, void *work_data)
{
    rt_thread_delay(10);
}

static void cancle_work_test02(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    rt_err_t err;

    /* 1 higher priority than the current test thread */
    curr_priority = get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    rt_work_init(&work, cancle_work_test02_fun, RT_NULL);
    /* Cancel the work while it is in progress */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(5);
    err = rt_workqueue_cancel_work(queue, &work);
    uassert_int_equal(err, -RT_EBUSY);

    rt_thread_delay(100);
    rt_workqueue_destroy(queue);
}

static void cancle_work_test03_fun(struct rt_work *work, void *work_data)
{
    rt_thread_delay(5);
}

static void cancle_work_test03(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    rt_err_t err;

    /* 1 lower priority than the current test thread */
    curr_priority = get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    rt_work_init(&work, cancle_work_test03_fun, RT_NULL);
    /* Canceling a work after it has been executed */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(10);
    err = rt_workqueue_cancel_work(queue, &work);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(100);
    rt_workqueue_destroy(queue);
}

static void cancle_work_test04_fun(struct rt_work *work, void *work_data)
{
    rt_thread_delay(10);
    *((int *)work_data) = 1;
}

static void cancle_work_test04(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 lower priority than the current test thread */
    curr_priority = get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    rt_work_init(&work, cancle_work_test04_fun, (void *)&work_flag);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(5);
    /* Synchronized cancellation work */
    err = rt_workqueue_cancel_work_sync(queue, &work);
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(work_flag, 1);

    rt_thread_delay(100);
    rt_workqueue_destroy(queue);
}

static void cancle_delay_work_test01_fun(struct rt_work *work, void *work_data)
{
    *((int *)work_data) = 1;
}

static void cancle_delay_work_test01(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 lower priority than the current test thread */
    curr_priority = get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    work_flag = 0;
    rt_work_init(&work, cancle_delay_work_test01_fun, (void *)&work_flag);
    err = rt_workqueue_submit_work(queue, &work, 20);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(10);
    /* Cancel work */
    err = rt_workqueue_cancel_work(queue, &work);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(15);
    uassert_int_equal(work_flag, 0);

    rt_thread_delay(100);
    rt_workqueue_destroy(queue);
}

static void repeat_work_test01_fun(struct rt_work *work, void *work_data)
{
    *((int *)work_data) += 1;
}

static void repeat_work_test01(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 lower priority than the current test thread */
    curr_priority = get_test_thread_priority(1);
    queue = rt_workqueue_create("test01", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    work_flag = 0;
    rt_work_init(&work, repeat_work_test01_fun, (void *)&work_flag);
    /* Multiple submissions of the same work */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    /* The same work, before it is executed, can be submitted repeatedly and executed only once */
    err = rt_workqueue_submit_work(queue, &work, 0);
    if (err != RT_EOK)
    {
        LOG_E("L:%d err. %d", __LINE__, err);
    }
    rt_thread_delay(10);
    /* Check if it was executed only once */
    uassert_int_equal(work_flag, 1);

    rt_thread_delay(100);
    rt_workqueue_destroy(queue);
}

static void repeat_work_test02_fun(struct rt_work *work, void *work_data)
{
    rt_thread_delay(10);
    *((int *)work_data) += 1;
}

static void repeat_work_test02(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 priority higher than current test thread */
    curr_priority = get_test_thread_priority(-1);
    queue = rt_workqueue_create("test02", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    rt_work_init(&work, repeat_work_test02_fun, (void *)&work_flag);
    /* Submit work with high queue priority that will be executed immediately */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(5);
    /* Re-submission of work in progress */
    err = rt_workqueue_submit_work(queue, &work, 0);
    if (err != RT_EOK)
    {
        LOG_E("L:%d err. %d", __LINE__, err);
    }
    rt_thread_delay(10);
    uassert_int_equal(work_flag, 1);

    rt_thread_delay(10);
    uassert_int_equal(work_flag, 2);

    rt_workqueue_destroy(queue);
}

static struct rt_workqueue *queue_3;

static void repeat_work_test03_fun(struct rt_work *work, void *work_data)
{
    int *work_flag = (int *)work_data;
    (*work_flag) += 1;
    rt_kprintf("work_flag:%d\n", *work_flag);
    if (*work_flag < 20)
    {
        rt_workqueue_submit_work(queue_3, work, 0);
    }
}

static void repeat_work_test03(void)
{
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 priority higher than current test thread */
    curr_priority = get_test_thread_priority(-1);
    queue_3 = rt_workqueue_create("test03", 2048, curr_priority);
    if (queue_3 == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    rt_work_init(&work, repeat_work_test03_fun, (void *)&work_flag);
    /* Submit work with high queue priority that will be executed immediately */
    err = rt_workqueue_submit_work(queue_3, &work, 0);
    uassert_int_equal(err, RT_EOK);

    /* Wait for the work to be executed 20 times with a timeout */
    err = rt_workqueue_cancel_work_sync(queue_3, &work);
    uassert_int_equal(err, RT_EOK);

    /* Check if the work was executed 20 times */
    uassert_int_equal(work_flag, 20);

    rt_workqueue_destroy(queue_3);
}

static void repeat_delay_work_test01_fun(struct rt_work *work, void *work_data)
{
    *((int *)work_data) += 1;
}

static void repeat_delay_work_test01(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 lower priority than the current test thread */
    curr_priority = get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    work_flag = 0;
    rt_work_init(&work, repeat_delay_work_test01_fun, (void *)&work_flag);

    err = rt_workqueue_submit_work(queue, &work, 20);
    uassert_int_equal(err, RT_EOK);

    /* At this point the delayed work has not been executed */
    rt_thread_delay(10);
    /* Re-submission of time-delayed work */
    err = rt_workqueue_submit_work(queue, &work, 20);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(15);
    uassert_int_equal(work_flag, 0);

    /* Waiting for delayed task execution */
    rt_thread_delay(15);
    uassert_int_equal(work_flag, 1);

    rt_thread_delay(100);
    rt_workqueue_destroy(queue);
}

static void repeat_delay_work_test02_fun(struct rt_work *work, void *work_data)
{
    rt_thread_delay(10);
    *((int *)work_data) += 1;
}

static void repeat_delay_work_test02(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 lower priority than the current test thread */
    curr_priority = get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    work_flag = 0;
    rt_work_init(&work, repeat_delay_work_test02_fun, (void *)&work_flag);

    err = rt_workqueue_submit_work(queue, &work, 20);
    uassert_int_equal(err, RT_EOK);

    /* Waiting for delayed work execution */
    rt_thread_delay(25);
    err = rt_workqueue_submit_work(queue, &work, 20);
    uassert_int_equal(err, RT_EOK);

    /* Check if the delayed work has been run only once */
    rt_thread_delay(10);
    uassert_int_equal(work_flag, 1);

    rt_thread_delay(25);
    /* Check if the delayed work is executed twice */
    uassert_int_equal(work_flag, 2);

    rt_thread_delay(100);
    rt_workqueue_destroy(queue);
}

static void cancel_all_work_test_fun(struct rt_work *work, void *work_data)
{
    *((int *)work_data) += 1;
}

static void cancel_all_work_test(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work1;
    struct rt_work work2;
    struct rt_work work3;
    struct rt_work work4;
    volatile int work_flag = 0;
    rt_err_t err;

    curr_priority = get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    if (queue == RT_NULL)
    {
        LOG_E("queue create failed, L:%d", __LINE__);
        return;
    }
    work_flag = 0;
    rt_work_init(&work1, cancel_all_work_test_fun, (void *)&work_flag);
    rt_work_init(&work2, cancel_all_work_test_fun, (void *)&work_flag);
    rt_work_init(&work3, cancel_all_work_test_fun, (void *)&work_flag);
    rt_work_init(&work4, cancel_all_work_test_fun, (void *)&work_flag);

    err = rt_workqueue_submit_work(queue, &work1, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_submit_work(queue, &work2, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_submit_work(queue, &work3, 10);
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_submit_work(queue, &work4, 10);
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_cancel_all_work(queue);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(20);
    uassert_int_equal(work_flag, 0);

    rt_thread_delay(100);
    rt_workqueue_destroy(queue);
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
    /* General work queue test */
    UTEST_UNIT_RUN(do_work_test);
    /* Delayed work queue test */
    UTEST_UNIT_RUN(do_delay_work_test);
    /* Cancellation of work prior to implementation */
    UTEST_UNIT_RUN(cancle_work_test01);
    /* Cancellation of work during execution */
    UTEST_UNIT_RUN(cancle_work_test02);
    /* Cancellation of work after implementation */
    UTEST_UNIT_RUN(cancle_work_test03);
    /* Synchronized cancellation of work during execution */
    UTEST_UNIT_RUN(cancle_work_test04);
    /* Cancel delayed work before execution */
    UTEST_UNIT_RUN(cancle_delay_work_test01);
    /* Multiple submissions of the same work prior to implementation */
    UTEST_UNIT_RUN(repeat_work_test01);
    /* Multiple submissions of the same work during execution */
    UTEST_UNIT_RUN(repeat_work_test02);
    /* Submitting the same task multiple times in a mission */
    UTEST_UNIT_RUN(repeat_work_test03);
    /* Multiple submissions of the same delayed task before execution */
    UTEST_UNIT_RUN(repeat_delay_work_test01);
    /* Multiple submissions of the same delayed task during execution */
    UTEST_UNIT_RUN(repeat_delay_work_test02);
    /* Cancel all works */
    UTEST_UNIT_RUN(cancel_all_work_test);
}
UTEST_TC_EXPORT(testcase, "components.drivers.ipc.workqueue_tc", utest_tc_init, utest_tc_cleanup, 300);
#endif
