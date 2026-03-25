/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-03-20     RyanCW       split workqueue utest, cover destroy APIs and add recreate stress
 */

/**
 * Test Case Name: IPC Workqueue Test
 *
 * Test Objectives:
 * - Validate destroy and destroy-sync behaviors with expected return codes.
 * - Verify destroy-sync waits for running work and drops queued work.
 * - Verify destroying flag rejects new submissions and urgent work.
 * - Stress repeated concurrent create/destroy_sync lifecycle paths.
 * - Test core APIs: rt_workqueue_destroy(), rt_workqueue_destroy_sync().
 *
 * Test Scenarios:
 * - Destroy sync waits for running work to finish.
 * - Destroy returns busy when sync waiter or destroying flag exists.
 * - Destroying queue rejects new submit and urgent requests.
 * - Destroy from workqueue thread returns busy.
 * - Multiple workqueues run repeated create/destroy_sync pressure loops.
 *
 * Verification Metrics:
 * - Destroy-sync waits for running work to finish.
 * - Destroy returns busy when sync waiter or destroying flag exists.
 * - Destroying queue rejects submit/urgent/cancel sync.
 * - Destroy called in workqueue thread returns busy.
 * - Pending and delayed works are dropped during destroy-sync.
 * - Concurrent queue recreate/destroy_sync loops stay stable.
 *
 * Dependencies:
 * - Hardware requirements: QEMU emulator or any hardware platform that supports RT-Thread.
 * - Software configuration:
 *     - RT_USING_UTEST must be enabled (select "RT-Thread Utestcases" in menuconfig).
 *     - RT_UTEST_WORKQUEUE must be enabled
 *       (enable via: RT-Thread Utestcases -> Kernel Components -> Drivers -> IPC Test -> IPC Workqueue Test).
 * - Environmental Assumptions: System scheduler working normally.
 *
 * Expected Results:
 * - Final output: "[ PASSED ] [ result ] testcase (components.drivers.ipc.workqueue_tc)"
 * - No memory leaks or race condition detections in logs.
 * - No assertions triggered during test execution.
 */
/* Workqueue destroy tests: destroy, destroy_sync, destroying rejects. */
#include "rtthread.h"
#include "rtdevice.h"
#include "utest.h"

#ifdef RT_USING_DEVICE_IPC

/* Testcase entry is defined in workqueue_tc_basic.c. */
extern rt_uint8_t wq_get_test_thread_priority(rt_int8_t pos);

struct wq_sync_ctx
{
    struct rt_semaphore started;
    struct rt_semaphore allow_finish;
    volatile int phase;
    volatile int count;
    volatile int released;
    volatile int done;
};

struct wq_destroy_ctx
{
    struct rt_workqueue *queue;
    struct rt_semaphore done;
    volatile rt_err_t err;
};

struct wq_destroy_wait_ctx
{
    struct rt_workqueue *queue;
    struct rt_semaphore started;
    struct rt_semaphore done;
    volatile rt_err_t err;
};

struct wq_cancel_wait_ctx
{
    struct rt_workqueue *queue;
    struct rt_work *work;
    struct rt_semaphore started;
    struct rt_semaphore done;
    volatile rt_err_t err;
};

struct wq_destroy_status_ctx
{
    struct rt_workqueue *queue;
    struct rt_semaphore started;
    struct rt_semaphore allow_finish;
    volatile rt_err_t submit_ret;
};

#define WQ_DESTROY_STRESS_THREADS 4
#define WQ_DESTROY_STRESS_LOOPS   100

struct wq_destroy_stress_ctx
{
    struct rt_semaphore done;
    char thread_name[8];
    char queue_name[8];
    volatile rt_bool_t started;
    volatile rt_int32_t run_count;
    volatile rt_int32_t delayed_count;
    volatile rt_int32_t loops_done;
    volatile rt_err_t err;
};

static void wq_sync_work_fun(struct rt_work *work, void *work_data)
{
    struct wq_sync_ctx *ctx = (struct wq_sync_ctx *)work_data;

    if (ctx->phase == 1)
    {
        /* Block here to simulate a running work. */
        rt_sem_release(&ctx->started);
        rt_sem_take(&ctx->allow_finish, RT_WAITING_FOREVER);
    }

    ctx->count += 1;
    ctx->done = 1;
}

static void wq_release_entry(void *parameter)
{
    struct wq_sync_ctx *ctx = (struct wq_sync_ctx *)parameter;

    rt_thread_delay(rt_tick_from_millisecond(20));
    /* Release blocked work. */
    ctx->released = 1;
    rt_sem_release(&ctx->allow_finish);
}

static void wq_destroy_sync_work_fun(struct rt_work *work, void *work_data)
{
    struct wq_destroy_ctx *ctx = (struct wq_destroy_ctx *)work_data;

    ctx->err = rt_workqueue_destroy_sync(ctx->queue);
    rt_sem_release(&ctx->done);
}

static void wq_destroy_work_fun(struct rt_work *work, void *work_data)
{
    struct wq_destroy_ctx *ctx = (struct wq_destroy_ctx *)work_data;

    ctx->err = rt_workqueue_destroy(ctx->queue);
    rt_sem_release(&ctx->done);
}

static void wq_destroy_wait_entry(void *parameter)
{
    struct wq_destroy_wait_ctx *ctx = (struct wq_destroy_wait_ctx *)parameter;

    rt_sem_release(&ctx->started);
    ctx->err = rt_workqueue_destroy_sync(ctx->queue);
    rt_sem_release(&ctx->done);
}

static void wq_cancel_wait_entry(void *parameter)
{
    struct wq_cancel_wait_ctx *ctx = (struct wq_cancel_wait_ctx *)parameter;

    rt_sem_release(&ctx->started);
    ctx->err = rt_workqueue_cancel_work_sync(ctx->queue, ctx->work);
    rt_sem_release(&ctx->done);
}

static void wq_inc_work_fun(struct rt_work *work, void *work_data)
{
    *((int *)work_data) += 1;
}

static void wq_destroy_status_work_fun(struct rt_work *work, void *work_data)
{
    struct wq_destroy_status_ctx *ctx = (struct wq_destroy_status_ctx *)work_data;

    /* Requeue before destroy_sync marks canceling to reproduce status transition. */
    ctx->submit_ret = rt_workqueue_submit_work(ctx->queue, work, 0);
    rt_sem_release(&ctx->started);
    rt_sem_take(&ctx->allow_finish, RT_WAITING_FOREVER);
}

static void wq_destroy_stress_run_fun(struct rt_work *work, void *work_data)
{
    struct wq_destroy_stress_ctx *ctx = (struct wq_destroy_stress_ctx *)work_data;

    ctx->started = RT_TRUE;
    rt_thread_delay(rt_tick_from_millisecond(5));
    ctx->run_count += 1;
}

static void wq_destroy_stress_delayed_fun(struct rt_work *work, void *work_data)
{
    struct wq_destroy_stress_ctx *ctx = (struct wq_destroy_stress_ctx *)work_data;

    ctx->delayed_count += 1;
}

static void wq_destroy_stress_entry(void *parameter)
{
    struct wq_destroy_stress_ctx *ctx = (struct wq_destroy_stress_ctx *)parameter;
    struct rt_workqueue *queue = RT_NULL;
    struct rt_work work_run;
    struct rt_work work_delayed;
    rt_int32_t loop;
    rt_int32_t tries;
    rt_err_t err = RT_EOK;

    for (loop = 0; loop < WQ_DESTROY_STRESS_LOOPS; loop++)
    {
        ctx->started = RT_FALSE;
        queue = rt_workqueue_create(ctx->queue_name, 2048, wq_get_test_thread_priority(-1));
        if (queue == RT_NULL)
        {
            err = -RT_ENOMEM;
            break;
        }

        rt_work_init(&work_run, wq_destroy_stress_run_fun, (void *)ctx);
        rt_work_init(&work_delayed, wq_destroy_stress_delayed_fun, (void *)ctx);

        err = rt_workqueue_submit_work(queue, &work_delayed, rt_tick_from_millisecond(30));
        if (err != RT_EOK)
        {
            rt_workqueue_destroy_sync(queue);
            break;
        }

        err = rt_workqueue_submit_work(queue, &work_run, 0);
        if (err != RT_EOK)
        {
            rt_workqueue_destroy_sync(queue);
            break;
        }

        for (tries = 0; tries < 20; tries++)
        {
            if (ctx->started)
            {
                break;
            }
            rt_thread_delay(rt_tick_from_millisecond(5));
        }
        if (ctx->started == RT_FALSE)
        {
            err = -RT_ETIMEOUT;
            rt_workqueue_destroy_sync(queue);
            break;
        }

        err = rt_workqueue_destroy_sync(queue);
        if (err != RT_EOK)
        {
            break;
        }

        if (ctx->run_count != loop + 1 || ctx->delayed_count != 0)
        {
            err = -RT_ERROR;
            break;
        }

        ctx->loops_done = loop + 1;
        queue = RT_NULL;
    }

    ctx->err = err;
    rt_sem_release(&ctx->done);
}

static void test_workqueue_destroy_sync_behaviors(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_destroy_ctx destroy_ctx;
    struct wq_sync_ctx sync_ctx;
    rt_thread_t release_thread;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(-1);

    /* Phase: destroy sync called inside workqueue thread should return busy. */
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&destroy_ctx.done, "wqdb", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    destroy_ctx.queue = queue;
    destroy_ctx.err = RT_EOK;

    rt_work_init(&work, wq_destroy_sync_work_fun, (void *)&destroy_ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&destroy_ctx.done, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(destroy_ctx.err, -RT_EBUSY);

    rt_sem_detach(&destroy_ctx.done);
    rt_workqueue_destroy(queue);

    /* Phase: destroy sync should wait for running work to finish. */
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&sync_ctx.started, "wqds", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&sync_ctx.allow_finish, "wqdf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    sync_ctx.phase = 1;
    sync_ctx.count = 0;
    sync_ctx.released = 0;
    sync_ctx.done = 0;

    rt_work_init(&work, wq_sync_work_fun, (void *)&sync_ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&sync_ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    release_thread = rt_thread_create("wqdrel", wq_release_entry, &sync_ctx,
                                      1024, curr_priority, 10);
    uassert_not_null(release_thread);
    if (release_thread == RT_NULL)
    {
        rt_sem_detach(&sync_ctx.allow_finish);
        rt_sem_detach(&sync_ctx.started);
        rt_workqueue_destroy(queue);
        return;
    }
    rt_thread_startup(release_thread);

    /* Destroy sync should wait current work done. */
    err = rt_workqueue_destroy_sync(queue);
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(sync_ctx.done, 1);

    rt_sem_detach(&sync_ctx.allow_finish);
    rt_sem_detach(&sync_ctx.started);

    /* Phase: destroy sync with pending and delayed work. */
    {
        struct rt_work work_pending;
        struct rt_work work_delayed;
        volatile int work_flag = 0;
        volatile int delayed_flag = 0;

        curr_priority = wq_get_test_thread_priority(1);
        queue = rt_workqueue_create("test", 2048, curr_priority);
        uassert_not_null(queue);
        if (queue == RT_NULL)
        {
            return;
        }

        rt_work_init(&work_pending, wq_inc_work_fun, (void *)&work_flag);
        rt_work_init(&work_delayed, wq_inc_work_fun, (void *)&delayed_flag);

        err = rt_workqueue_submit_work(queue, &work_pending, 0);
        uassert_int_equal(err, RT_EOK);
        err = rt_workqueue_submit_work(queue, &work_delayed, rt_tick_from_millisecond(40));
        uassert_int_equal(err, RT_EOK);

        err = rt_workqueue_destroy_sync(queue);
        uassert_int_equal(err, RT_EOK);

        rt_thread_delay(rt_tick_from_millisecond(60));
        uassert_int_equal(work_flag, 0);
        uassert_int_equal(delayed_flag, 0);
    }
}

static void test_workqueue_destroy_sync_scheduler_unavailable_busy(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    rt_base_t level;
    rt_base_t critical_level;
    rt_uint8_t queue_flags;
    rt_uint16_t work_flags;
    volatile int work_flag = 0;
    rt_err_t err;

    /* White-box regression: running destroy_sync must reject unavailable scheduler. */
    curr_priority = wq_get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    queue->work_current = &work;
    work.workqueue = queue;
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    critical_level = rt_enter_critical();
    err = rt_workqueue_destroy_sync(queue);
    rt_exit_critical_safe(critical_level);
    uassert_int_equal(err, -RT_EBUSY);

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    queue_flags = queue->flags;
    work_flags = work.flags;
    queue->work_current = RT_NULL;
    work.workqueue = RT_NULL;
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    uassert_int_equal(queue_flags, 0);
    uassert_true((work_flags & RT_WORK_STATE_CANCELING) == 0);
    uassert_int_equal(work_flag, 0);

    err = rt_workqueue_destroy(queue);
    uassert_int_equal(err, RT_EOK);
}

static void test_workqueue_destroy_in_callback_busy(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_destroy_ctx destroy_ctx;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&destroy_ctx.done, "wqdi", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    destroy_ctx.queue = queue;
    destroy_ctx.err = RT_EOK;

    /* Phase: destroy called inside workqueue thread should return busy. */
    rt_work_init(&work, wq_destroy_work_fun, (void *)&destroy_ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&destroy_ctx.done, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(destroy_ctx.err, -RT_EBUSY);

    rt_sem_detach(&destroy_ctx.done);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_destroy_busy_when_sync_waiting(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_sync_ctx run_ctx;
    struct wq_cancel_wait_ctx wait_ctx;
    rt_thread_t cancel_thread;
    rt_base_t level;
    rt_bool_t sync_waiting = RT_FALSE;
    rt_err_t err;
    int tries;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&run_ctx.started, "wqbs", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&run_ctx.allow_finish, "wqbf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    run_ctx.phase = 1;
    run_ctx.count = 0;
    run_ctx.done = 0;

    rt_work_init(&work, wq_sync_work_fun, (void *)&run_ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&run_ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_init(&wait_ctx.started, "wqws", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&wait_ctx.done, "wqwd", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    wait_ctx.queue = queue;
    wait_ctx.work = &work;
    wait_ctx.err = RT_EOK;

    cancel_thread = rt_thread_create("wqwc", wq_cancel_wait_entry, &wait_ctx,
                                     1024, curr_priority, 10);
    uassert_not_null(cancel_thread);
    if (cancel_thread == RT_NULL)
    {
        rt_sem_detach(&wait_ctx.done);
        rt_sem_detach(&wait_ctx.started);
        rt_sem_detach(&run_ctx.allow_finish);
        rt_sem_detach(&run_ctx.started);
        rt_workqueue_destroy(queue);
        return;
    }
    rt_thread_startup(cancel_thread);

    err = rt_sem_take(&wait_ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    for (tries = 0; tries < 10; tries++)
    {
        level = rt_spin_lock_irqsave(&(queue->spinlock));
        sync_waiting = (queue->flags & RT_WORKQUEUE_FLAG_SYNC_WAITING) ? RT_TRUE : RT_FALSE;
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);
        if (sync_waiting)
        {
            break;
        }
        rt_thread_delay(rt_tick_from_millisecond(5));
    }
    uassert_true(sync_waiting);

    err = rt_workqueue_destroy_sync(queue);
    uassert_int_equal(err, -RT_EBUSY);

    /* Phase: destroy while sync waiter should return busy. */
    err = rt_workqueue_destroy(queue);
    uassert_int_equal(err, -RT_EBUSY);

    rt_sem_release(&run_ctx.allow_finish);
    err = rt_sem_take(&wait_ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(wait_ctx.err, RT_EOK);

    err = rt_workqueue_destroy_sync(queue);
    uassert_int_equal(err, RT_EOK);

    rt_sem_detach(&wait_ctx.done);
    rt_sem_detach(&wait_ctx.started);
    rt_sem_detach(&run_ctx.allow_finish);
    rt_sem_detach(&run_ctx.started);
}

static void test_workqueue_destroy_busy_when_destroying(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    rt_base_t level;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    /* Phase: simulate destroying flag and ensure destroy returns busy. */
    level = rt_spin_lock_irqsave(&(queue->spinlock));
    queue->flags |= RT_WORKQUEUE_FLAG_DESTROYING;
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    err = rt_workqueue_destroy(queue);
    uassert_int_equal(err, -RT_EBUSY);

    /* Cleanup: clear flag and destroy again. */
    level = rt_spin_lock_irqsave(&(queue->spinlock));
    queue->flags &= ~RT_WORKQUEUE_FLAG_DESTROYING;
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    err = rt_workqueue_destroy(queue);
    uassert_int_equal(err, RT_EOK);
}

static void test_workqueue_destroying_reject_submit_urgent(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work_running;
    struct rt_work work_submit;
    struct rt_work work_urgent;
    struct wq_sync_ctx run_ctx;
    struct wq_destroy_wait_ctx destroy_ctx;
    rt_thread_t destroy_thread;
    rt_base_t level;
    rt_bool_t destroying = RT_FALSE;
    volatile int work_flag = 0;
    volatile int work_urgent_flag = 0;
    rt_err_t err;
    int tries;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&run_ctx.started, "wqds", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&run_ctx.allow_finish, "wqdf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    run_ctx.phase = 1;
    run_ctx.count = 0;
    run_ctx.done = 0;

    rt_work_init(&work_running, wq_sync_work_fun, (void *)&run_ctx);
    err = rt_workqueue_submit_work(queue, &work_running, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&run_ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_init(&destroy_ctx.started, "wqdy", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&destroy_ctx.done, "wqdd", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    destroy_ctx.queue = queue;
    destroy_ctx.err = RT_EOK;

    destroy_thread = rt_thread_create("wqdsy", wq_destroy_wait_entry, &destroy_ctx,
                                      1024, curr_priority, 10);
    uassert_not_null(destroy_thread);
    if (destroy_thread == RT_NULL)
    {
        rt_sem_detach(&destroy_ctx.done);
        rt_sem_detach(&destroy_ctx.started);
        rt_sem_detach(&run_ctx.allow_finish);
        rt_sem_detach(&run_ctx.started);
        rt_workqueue_destroy(queue);
        return;
    }
    rt_thread_startup(destroy_thread);

    err = rt_sem_take(&destroy_ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    /* Wait until destroy_sync marks the queue as destroying. */
    for (tries = 0; tries < 10; tries++)
    {
        level = rt_spin_lock_irqsave(&(queue->spinlock));
        destroying = (queue->flags & RT_WORKQUEUE_FLAG_DESTROYING) ? RT_TRUE : RT_FALSE;
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);
        if (destroying)
        {
            break;
        }
        rt_thread_delay(rt_tick_from_millisecond(5));
    }
    uassert_true(destroying);

    rt_work_init(&work_submit, wq_inc_work_fun, (void *)&work_flag);
    err = rt_workqueue_submit_work(queue, &work_submit, 0);
    uassert_int_equal(err, -RT_EBUSY);

    rt_work_init(&work_urgent, wq_inc_work_fun, (void *)&work_urgent_flag);
    err = rt_workqueue_urgent_work(queue, &work_urgent);
    uassert_int_equal(err, -RT_EBUSY);
    err = rt_workqueue_cancel_work_sync(queue, &work_running);
    uassert_int_equal(err, -RT_EBUSY);

    rt_sem_release(&run_ctx.allow_finish);
    err = rt_sem_take(&destroy_ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(destroy_ctx.err, RT_EOK);
    uassert_int_equal(work_flag, 0);
    uassert_int_equal(work_urgent_flag, 0);

    if (destroy_ctx.err != RT_EOK)
    {
        rt_workqueue_destroy(queue);
    }

    rt_sem_detach(&destroy_ctx.done);
    rt_sem_detach(&destroy_ctx.started);
    rt_sem_detach(&run_ctx.allow_finish);
    rt_sem_detach(&run_ctx.started);
}

static void test_workqueue_destroy_sync_status_no_canceled_while_running(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_destroy_status_ctx run_ctx;
    struct wq_destroy_wait_ctx destroy_ctx;
    rt_thread_t destroy_thread;
    rt_uint16_t status = RT_WORK_STATUS_IDLE;
    rt_err_t err;
    int tries;
    rt_bool_t canceling = RT_FALSE;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&run_ctx.started, "wqzs", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&run_ctx.allow_finish, "wqzf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    run_ctx.queue = queue;
    run_ctx.submit_ret = -RT_ERROR;

    rt_work_init(&work, wq_destroy_status_work_fun, (void *)&run_ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&run_ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(run_ctx.submit_ret, RT_EOK);

    err = rt_sem_init(&destroy_ctx.started, "wqzt", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&destroy_ctx.done, "wqzd", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    destroy_ctx.queue = queue;
    destroy_ctx.err = RT_EOK;

    destroy_thread = rt_thread_create("wqzdy", wq_destroy_wait_entry, &destroy_ctx,
                                      1024, curr_priority, 10);
    uassert_not_null(destroy_thread);
    if (destroy_thread == RT_NULL)
    {
        rt_sem_detach(&destroy_ctx.done);
        rt_sem_detach(&destroy_ctx.started);
        rt_sem_detach(&run_ctx.allow_finish);
        rt_sem_detach(&run_ctx.started);
        rt_workqueue_destroy(queue);
        return;
    }
    rt_thread_startup(destroy_thread);

    err = rt_sem_take(&destroy_ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    for (tries = 0; tries < 10; tries++)
    {
        status = rt_workqueue_get_work_status(queue, &work);
        canceling = (status & RT_WORK_STATUS_CANCELING) ? RT_TRUE : RT_FALSE;
        if (canceling)
        {
            break;
        }
        rt_thread_delay(rt_tick_from_millisecond(5));
    }
    uassert_true(canceling);
    uassert_true(status & RT_WORK_STATUS_RUNNING);
    uassert_true((status & RT_WORK_STATUS_CANCELED) == 0);

    rt_sem_release(&run_ctx.allow_finish);
    err = rt_sem_take(&destroy_ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(destroy_ctx.err, RT_EOK);

    rt_sem_detach(&destroy_ctx.done);
    rt_sem_detach(&destroy_ctx.started);
    rt_sem_detach(&run_ctx.allow_finish);
    rt_sem_detach(&run_ctx.started);
}

static void test_workqueue_multi_queue_recreate_stress(void)
{
    struct wq_destroy_stress_ctx ctx[WQ_DESTROY_STRESS_THREADS];
    rt_thread_t threads[WQ_DESTROY_STRESS_THREADS];
    rt_uint8_t curr_priority;
    rt_err_t err;
    rt_int32_t created = 0;
    rt_int32_t i;
    rt_int32_t j;

    curr_priority = wq_get_test_thread_priority(0);
    rt_memset(ctx, 0, sizeof(ctx));
    rt_memset(threads, 0, sizeof(threads));

    for (i = 0; i < WQ_DESTROY_STRESS_THREADS; i++)
    {
        err = rt_sem_init(&ctx[i].done, "wqmd", 0, RT_IPC_FLAG_FIFO);
        uassert_int_equal(err, RT_EOK);
        if (err != RT_EOK)
        {
            while (--created >= 0)
            {
                rt_thread_delete(threads[created]);
                rt_sem_detach(&ctx[created].done);
            }
            return;
        }

        rt_snprintf(ctx[i].thread_name, sizeof(ctx[i].thread_name), "wqm%d", i);
        rt_snprintf(ctx[i].queue_name, sizeof(ctx[i].queue_name), "wqq%d", i);
        ctx[i].err = RT_EOK;

        threads[i] = rt_thread_create(ctx[i].thread_name,
                                      wq_destroy_stress_entry,
                                      &ctx[i],
                                      1536,
                                      curr_priority,
                                      10);
        uassert_not_null(threads[i]);
        if (threads[i] == RT_NULL)
        {
            rt_sem_detach(&ctx[i].done);
            while (--created >= 0)
            {
                rt_thread_delete(threads[created]);
                rt_sem_detach(&ctx[created].done);
            }
            return;
        }

        created += 1;
    }

    for (i = 0; i < created; i++)
    {
        err = rt_thread_startup(threads[i]);
        uassert_int_equal(err, RT_EOK);
        if (err != RT_EOK)
        {
            for (j = 0; j < i; j++)
            {
                rt_sem_take(&ctx[j].done, RT_WAITING_FOREVER);
            }
            for (j = i; j < created; j++)
            {
                rt_thread_delete(threads[j]);
            }
            for (j = 0; j < created; j++)
            {
                rt_sem_detach(&ctx[j].done);
            }
            return;
        }
    }

    for (i = 0; i < created; i++)
    {
        err = rt_sem_take(&ctx[i].done, rt_tick_from_millisecond(10000));
        uassert_int_equal(err, RT_EOK);
        uassert_int_equal(ctx[i].err, RT_EOK);
        uassert_int_equal(ctx[i].loops_done, WQ_DESTROY_STRESS_LOOPS);
        uassert_int_equal(ctx[i].run_count, WQ_DESTROY_STRESS_LOOPS);
        uassert_int_equal(ctx[i].delayed_count, 0);
    }

    for (i = 0; i < created; i++)
    {
        rt_sem_detach(&ctx[i].done);
    }
}

void workqueue_destroy_testcase(void)
{
    /* Destroy sync behaviors (busy in thread + wait running) */
    UTEST_UNIT_RUN(test_workqueue_destroy_sync_behaviors);
    /* Running destroy_sync returns busy when scheduler is unavailable */
    UTEST_UNIT_RUN(test_workqueue_destroy_sync_scheduler_unavailable_busy);
    /* Destroy in callback should return busy */
    UTEST_UNIT_RUN(test_workqueue_destroy_in_callback_busy);
    /* Destroy returns busy when sync waiter exists */
    UTEST_UNIT_RUN(test_workqueue_destroy_busy_when_sync_waiting);
    /* Destroy returns busy when destroying flag already set */
    UTEST_UNIT_RUN(test_workqueue_destroy_busy_when_destroying);
    /* Destroying queue rejects new submit and urgent */
    UTEST_UNIT_RUN(test_workqueue_destroying_reject_submit_urgent);
    /* Destroy sync should not expose CANCELED on running work */
    UTEST_UNIT_RUN(test_workqueue_destroy_sync_status_no_canceled_while_running);
    /* Multiple workqueues recreate and destroy_sync stress */
    UTEST_UNIT_RUN(test_workqueue_multi_queue_recreate_stress);
}

#endif /* RT_USING_DEVICE_IPC */
