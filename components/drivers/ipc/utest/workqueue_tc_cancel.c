/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-06     tyx          first commit
 * 2024-12-31     rbb666       Adding Test Cases
 * 2025-11-16     ChuanN-sudo  add standardized utest documentation block
 * 2026-03-20     RyanCW       split workqueue utest and cover cancel/sync paths
 */

/**
 * Test Case Name: IPC Workqueue Test
 *
 * Test Objectives:
 * - Validate cancel, cancel sync, and cancel-all behaviors with expected return codes.
 * - Verify cancel sync waits for running work and blocks requeue attempts.
 * - Verify cross-queue operations are rejected.
 * - Test core APIs: rt_workqueue_cancel_work(), rt_workqueue_cancel_work_sync(),
 *   rt_workqueue_cancel_all_work().
 *
 * Test Scenarios:
 * - Cancel pending and delayed work items.
 * - Cancel sync waits for running work and rejects requeue attempts.
 * - Cross-queue operations are rejected for safety.
 * - Cancel-all keeps running work and drops queued items.
 *
 * Verification Metrics:
 * - Pending/delayed cancels prevent execution.
 * - Cancel sync waits for running work and returns busy on invalid waiters.
 * - Requeue attempts during cancel sync are rejected.
 * - Cancel-all keeps running work and removes queued work.
 * - Cross-queue operations return busy.
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
/* Workqueue cancel/sync tests: cancel, cancel_sync, cancel_all, cross-queue. */
#include "rtthread.h"
#include "rtdevice.h"
#include "utest.h"
#include "rtatomic.h"

#ifdef RT_USING_DEVICE_IPC

/* Testcase entry is defined in workqueue_tc_basic.c. */
extern rt_uint8_t wq_get_test_thread_priority(rt_int8_t pos);

struct wq_sync_ctx
{
    struct rt_workqueue *queue;
    struct rt_semaphore started;
    struct rt_semaphore allow_finish;
    volatile int phase;
    volatile int count;
    volatile int released;
    volatile int submit_ret;
    volatile int run_count;
    volatile int done;
};

struct wq_done_ctx
{
    struct rt_semaphore done;
    volatile int flag;
};

struct wq_requeue_early_ctx
{
    struct rt_workqueue *queue;
    struct rt_semaphore started;
    struct rt_semaphore allow_finish;
    volatile int run_count;
    volatile rt_err_t submit_ret;
};

struct wq_release_ctx
{
    struct rt_semaphore *sem;
    rt_tick_t delay;
};

struct wq_cancel_wait_ctx
{
    struct rt_workqueue *queue;
    struct rt_work *work;
    struct rt_semaphore started;
    struct rt_semaphore done;
    volatile rt_err_t err;
};

struct wq_cancel_all_ctx
{
    struct rt_workqueue *queue;
    struct rt_semaphore started;
    struct rt_semaphore allow_finish;
    struct rt_semaphore done;
    volatile rt_err_t submit_ret1;
    volatile rt_err_t submit_ret2;
};

struct wq_self_cancel_ctx
{
    struct rt_workqueue *queue;
    struct rt_semaphore done;
    volatile rt_err_t err;
};

struct wq_stress_item;

struct wq_stress_group
{
    struct rt_workqueue *queue;
    rt_atomic_t submit_cnt[8];
    rt_atomic_t exec_cnt[8];
    struct wq_stress_item *items;
};

struct wq_stress_item
{
    struct rt_work work;
    struct wq_stress_group *group;
    rt_uint8_t index;
};

struct wq_stress_thread_ctx
{
    struct wq_stress_group *group;
    struct rt_semaphore done;
    rt_uint32_t seed;
};

static rt_bool_t wq_timeout_shifted_later(rt_tick_t new_tick,
                                          rt_tick_t old_tick,
                                          rt_tick_t min_delta)
{
    rt_tick_t delta = new_tick - old_tick;

    return (delta < RT_TICK_MAX / 2) && (delta >= min_delta);
}

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

static void wq_requeue_work_fun(struct rt_work *work, void *work_data)
{
    struct wq_sync_ctx *ctx = (struct wq_sync_ctx *)work_data;

    ctx->run_count += 1;
    rt_sem_release(&ctx->started);
    rt_sem_take(&ctx->allow_finish, RT_WAITING_FOREVER);
    /* Requeue in callback should be rejected during cancel_sync. */
    ctx->submit_ret = rt_workqueue_submit_work(ctx->queue, work, 0);
}

static void wq_inc_work_fun(struct rt_work *work, void *work_data)
{
    *((int *)work_data) += 1;
}

static void wq_delay_flag_work_fun(struct rt_work *work, void *work_data)
{
    rt_thread_delay(rt_tick_from_millisecond(10));
    *((int *)work_data) = 1;
}

static void wq_done_work_fun(struct rt_work *work, void *work_data)
{
    struct wq_done_ctx *ctx = (struct wq_done_ctx *)work_data;

    ctx->flag = 1;
    rt_sem_release(&ctx->done);
}

static void wq_release_sem_entry(void *parameter)
{
    struct wq_release_ctx *ctx = (struct wq_release_ctx *)parameter;

    rt_thread_delay(ctx->delay);
    rt_sem_release(ctx->sem);
}

static void wq_cancel_wait_entry(void *parameter)
{
    struct wq_cancel_wait_ctx *ctx = (struct wq_cancel_wait_ctx *)parameter;

    rt_sem_release(&ctx->started);
    ctx->err = rt_workqueue_cancel_work_sync(ctx->queue, ctx->work);
    rt_sem_release(&ctx->done);
}

static void wq_cancel_sync_self_fun(struct rt_work *work, void *work_data)
{
    struct wq_self_cancel_ctx *ctx = (struct wq_self_cancel_ctx *)work_data;

    ctx->err = rt_workqueue_cancel_work_sync(ctx->queue, work);
    rt_sem_release(&ctx->done);
}

static void wq_cancel_all_requeue_fun(struct rt_work *work, void *work_data)
{
    struct wq_cancel_all_ctx *ctx = (struct wq_cancel_all_ctx *)work_data;

    /* Requeue early before cancel_sync marks canceling. */
    ctx->submit_ret1 = rt_workqueue_submit_work(ctx->queue, work, 0);
    rt_sem_release(&ctx->started);
    rt_sem_take(&ctx->allow_finish, RT_WAITING_FOREVER);
    /* Requeue after cancel_all while cancel_sync is waiting. */
    ctx->submit_ret2 = rt_workqueue_submit_work(ctx->queue, work, 0);
    rt_sem_release(&ctx->done);
}

static rt_uint32_t wq_lcg_next(rt_uint32_t *seed)
{
    *seed = (*seed * 1103515245u) + 12345u;
    return *seed;
}

static void wq_stress_work_fun(struct rt_work *work, void *work_data)
{
    struct wq_stress_item *item = (struct wq_stress_item *)work_data;

    rt_atomic_add(&item->group->exec_cnt[item->index], 1);
}

static void wq_stress_thread_entry(void *parameter)
{
    struct wq_stress_thread_ctx *ctx = (struct wq_stress_thread_ctx *)parameter;
    struct wq_stress_group *group = ctx->group;
    rt_uint32_t seed = ctx->seed;
    rt_int32_t i;

    for (i = 0; i < 80; i++)
    {
        rt_uint32_t rand = wq_lcg_next(&seed);
        rt_uint32_t idx = rand % 8;
        rt_uint32_t op = (rand >> 8) % 3;
        rt_err_t err;

        if (op == 0)
        {
            err = rt_workqueue_submit_work(group->queue, &group->items[idx].work, 0);
            if (err == RT_EOK)
            {
                rt_atomic_add(&group->submit_cnt[idx], 1);
            }
        }
        else if (op == 1)
        {
            rt_tick_t ticks = rt_tick_from_millisecond(5 * (1 + (wq_lcg_next(&seed) % 3)));

            err = rt_workqueue_submit_work(group->queue, &group->items[idx].work, ticks);
            if (err == RT_EOK)
            {
                rt_atomic_add(&group->submit_cnt[idx], 1);
            }
        }
        else
        {
            (void)rt_workqueue_cancel_work(group->queue, &group->items[idx].work);
        }

        if ((i & 0x7) == 0)
        {
            rt_thread_delay(rt_tick_from_millisecond(5));
        }
    }

    ctx->seed = seed;
    rt_sem_release(&ctx->done);
}

static void wq_requeue_early_work_fun(struct rt_work *work, void *work_data)
{
    struct wq_requeue_early_ctx *ctx = (struct wq_requeue_early_ctx *)work_data;

    ctx->run_count += 1;
    ctx->submit_ret = rt_workqueue_submit_work(ctx->queue, work, 0);
    rt_sem_release(&ctx->started);
    rt_sem_take(&ctx->allow_finish, RT_WAITING_FOREVER);
}

static void test_workqueue_cancel_sync_pending(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_sync_ctx ctx;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    ctx.count = 0;
    ctx.phase = 0;
    ctx.done = 0;

    /* Phase: cancel sync on pending work. */
    rt_work_init(&work, wq_sync_work_fun, (void *)&ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_cancel_work_sync(queue, &work);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(10));
    uassert_int_equal(ctx.count, 0);

    /* Phase: cancel sync on delayed pending work. */
    ctx.count = 0;
    ctx.phase = 0;
    ctx.done = 0;
    rt_work_init(&work, wq_sync_work_fun, (void *)&ctx);
    err = rt_workqueue_submit_work(queue, &work, rt_tick_from_millisecond(20));
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_cancel_work_sync(queue, &work);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(25));
    uassert_int_equal(ctx.count, 0);

    rt_workqueue_destroy(queue);
}

static void test_workqueue_cancel_sync_pending_scheduler_unavailable_ok(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    rt_base_t critical_level;
    volatile int work_flag = 0;
    rt_err_t err;

    /* White-box regression: pending cancel_sync should keep the no-wait fast path. */
    curr_priority = wq_get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    critical_level = rt_enter_critical();
    err = rt_workqueue_cancel_work_sync(queue, &work);
    rt_exit_critical_safe(critical_level);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(10));
    uassert_int_equal(work_flag, 0);

    err = rt_workqueue_destroy(queue);
    uassert_int_equal(err, RT_EOK);
}

static void test_workqueue_cancel_sync_scheduler_unavailable_busy(void)
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

    /* White-box regression: running cancel_sync must reject unavailable scheduler. */
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
    err = rt_workqueue_cancel_work_sync(queue, &work);
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

static void test_workqueue_cancel_sync_reuse_completion(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_sync_ctx ctx;
    rt_thread_t release_thread;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.started, "wqrs", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.allow_finish, "wqrf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);

    ctx.phase = 0;
    ctx.count = 0;
    ctx.released = 0;
    ctx.done = 0;

    rt_work_init(&work, wq_sync_work_fun, (void *)&ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(10));
    uassert_int_equal(ctx.count, 1);

    ctx.phase = 1;
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    release_thread = rt_thread_create("wqrel", wq_release_entry, &ctx,
                                      1024, curr_priority, 10);
    uassert_not_null(release_thread);
    if (release_thread == RT_NULL)
    {
        rt_sem_detach(&ctx.allow_finish);
        rt_sem_detach(&ctx.started);
        rt_workqueue_destroy(queue);
        return;
    }
    rt_thread_startup(release_thread);

    /* Phase: cancel sync reuse completion. */
    err = rt_workqueue_cancel_work_sync(queue, &work);
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(ctx.released, 1);
    uassert_int_equal(ctx.count, 2);

    rt_sem_detach(&ctx.allow_finish);
    rt_sem_detach(&ctx.started);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_cancel_sync_requeue(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_sync_ctx ctx;
    rt_thread_t release_thread;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.started, "wqrc", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.allow_finish, "wqrf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.queue = queue;
    ctx.submit_ret = 0;
    ctx.run_count = 0;

    /* Phase: requeue in callback should be rejected during cancel_sync. */
    rt_work_init(&work, wq_requeue_work_fun, (void *)&ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    release_thread = rt_thread_create("wqrrel", wq_release_entry, &ctx,
                                      1024, curr_priority, 10);
    uassert_not_null(release_thread);
    if (release_thread == RT_NULL)
    {
        rt_sem_detach(&ctx.allow_finish);
        rt_sem_detach(&ctx.started);
        rt_workqueue_destroy(queue);
        return;
    }
    rt_thread_startup(release_thread);

    err = rt_workqueue_cancel_work_sync(queue, &work);
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(ctx.run_count, 1);
    uassert_int_equal(ctx.submit_ret, -RT_EBUSY);

    rt_sem_detach(&ctx.allow_finish);
    rt_sem_detach(&ctx.started);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_cancel_sync_requeue_early(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_requeue_early_ctx ctx;
    struct wq_release_ctx release_ctx;
    rt_thread_t release_thread;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.started, "wqes", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.allow_finish, "wqef", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.queue = queue;
    ctx.run_count = 0;
    ctx.submit_ret = -RT_ERROR;

    /* Phase: requeue early before cancel_sync blocks, should be removed later. */
    rt_work_init(&work, wq_requeue_early_work_fun, (void *)&ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    release_ctx.sem = &ctx.allow_finish;
    release_ctx.delay = rt_tick_from_millisecond(20);
    release_thread = rt_thread_create("wqerl", wq_release_sem_entry, &release_ctx,
                                      1024, curr_priority, 10);
    uassert_not_null(release_thread);
    if (release_thread == RT_NULL)
    {
        rt_sem_detach(&ctx.allow_finish);
        rt_sem_detach(&ctx.started);
        rt_workqueue_destroy(queue);
        return;
    }
    rt_thread_startup(release_thread);

    err = rt_workqueue_cancel_work_sync(queue, &work);
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(ctx.submit_ret, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(10));
    uassert_int_equal(ctx.run_count, 1);

    rt_sem_detach(&ctx.allow_finish);
    rt_sem_detach(&ctx.started);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_cancel_sync_double_waiter_busy(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_sync_ctx run_ctx;
    struct wq_cancel_wait_ctx wait_ctx1;
    struct wq_cancel_wait_ctx wait_ctx2;
    rt_thread_t thread1;
    rt_thread_t thread2;
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

    err = rt_sem_init(&run_ctx.started, "wqcs", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&run_ctx.allow_finish, "wqcf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    run_ctx.phase = 1;
    run_ctx.count = 0;
    run_ctx.done = 0;

    rt_work_init(&work, wq_sync_work_fun, (void *)&run_ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&run_ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_init(&wait_ctx1.started, "wqc1s", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&wait_ctx1.done, "wqc1d", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    wait_ctx1.queue = queue;
    wait_ctx1.work = &work;
    wait_ctx1.err = RT_EOK;

    err = rt_sem_init(&wait_ctx2.started, "wqc2s", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&wait_ctx2.done, "wqc2d", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    wait_ctx2.queue = queue;
    wait_ctx2.work = &work;
    wait_ctx2.err = RT_EOK;

    thread1 = rt_thread_create("wqc1", wq_cancel_wait_entry, &wait_ctx1,
                               1024, curr_priority, 10);
    uassert_not_null(thread1);
    if (thread1 == RT_NULL)
    {
        rt_sem_detach(&wait_ctx2.done);
        rt_sem_detach(&wait_ctx2.started);
        rt_sem_detach(&wait_ctx1.done);
        rt_sem_detach(&wait_ctx1.started);
        rt_sem_detach(&run_ctx.allow_finish);
        rt_sem_detach(&run_ctx.started);
        rt_workqueue_destroy(queue);
        return;
    }
    rt_thread_startup(thread1);

    err = rt_sem_take(&wait_ctx1.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);
    /* Wait until the first cancel_sync waiter is registered. */
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
    if (!sync_waiting)
    {
        rt_sem_release(&run_ctx.allow_finish);
        rt_sem_take(&wait_ctx1.done, rt_tick_from_millisecond(200));
        rt_sem_detach(&wait_ctx2.done);
        rt_sem_detach(&wait_ctx2.started);
        rt_sem_detach(&wait_ctx1.done);
        rt_sem_detach(&wait_ctx1.started);
        rt_sem_detach(&run_ctx.allow_finish);
        rt_sem_detach(&run_ctx.started);
        rt_workqueue_destroy(queue);
        return;
    }

    /* Second cancel_sync waiter should return busy. */
    thread2 = rt_thread_create("wqc2", wq_cancel_wait_entry, &wait_ctx2,
                               1024, curr_priority, 10);
    uassert_not_null(thread2);
    if (thread2 == RT_NULL)
    {
        rt_sem_release(&run_ctx.allow_finish);
        rt_sem_take(&wait_ctx1.done, rt_tick_from_millisecond(200));
        rt_sem_detach(&wait_ctx2.done);
        rt_sem_detach(&wait_ctx2.started);
        rt_sem_detach(&wait_ctx1.done);
        rt_sem_detach(&wait_ctx1.started);
        rt_sem_detach(&run_ctx.allow_finish);
        rt_sem_detach(&run_ctx.started);
        rt_workqueue_destroy(queue);
        return;
    }
    rt_thread_startup(thread2);

    err = rt_sem_take(&wait_ctx2.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(wait_ctx2.err, -RT_EBUSY);

    rt_sem_release(&run_ctx.allow_finish);
    err = rt_sem_take(&wait_ctx1.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(wait_ctx1.err, RT_EOK);

    rt_sem_detach(&wait_ctx2.done);
    rt_sem_detach(&wait_ctx2.started);
    rt_sem_detach(&wait_ctx1.done);
    rt_sem_detach(&wait_ctx1.started);
    rt_sem_detach(&run_ctx.allow_finish);
    rt_sem_detach(&run_ctx.started);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_cancel_sync_in_callback_busy(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_self_cancel_ctx ctx;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.done, "wqcb", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.queue = queue;
    ctx.err = RT_EOK;

    /* cancel_sync in callback should return busy. */
    rt_work_init(&work, wq_cancel_sync_self_fun, (void *)&ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(ctx.err, -RT_EBUSY);

    rt_sem_detach(&ctx.done);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_status_canceling(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_sync_ctx run_ctx;
    struct wq_cancel_wait_ctx wait_ctx;
    rt_thread_t cancel_thread;
    rt_base_t level;
    rt_bool_t canceling = RT_FALSE;
    rt_uint16_t status;
    rt_err_t err;
    int tries;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&run_ctx.started, "wqss", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&run_ctx.allow_finish, "wqsf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    run_ctx.phase = 1;
    run_ctx.count = 0;
    run_ctx.done = 0;

    rt_work_init(&work, wq_sync_work_fun, (void *)&run_ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&run_ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_init(&wait_ctx.started, "wqcs", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&wait_ctx.done, "wqcd", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    wait_ctx.queue = queue;
    wait_ctx.work = &work;
    wait_ctx.err = RT_EOK;

    cancel_thread = rt_thread_create("wqst", wq_cancel_wait_entry, &wait_ctx,
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
        canceling = (work.flags & RT_WORK_STATE_CANCELING) ? RT_TRUE : RT_FALSE;
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);
        if (canceling)
        {
            break;
        }
        rt_thread_delay(rt_tick_from_millisecond(5));
    }
    uassert_true(canceling);

    status = rt_workqueue_get_work_status(queue, &work);
    uassert_true(status & RT_WORK_STATUS_CANCELING);
    uassert_true(status & RT_WORK_STATUS_RUNNING);

    rt_sem_release(&run_ctx.allow_finish);
    err = rt_sem_take(&wait_ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(wait_ctx.err, RT_EOK);

    status = rt_workqueue_get_work_status(queue, &work);
    uassert_true((status & RT_WORK_STATUS_CANCELING) == 0);
    uassert_true(status & RT_WORK_STATUS_DONE);

    rt_sem_detach(&wait_ctx.done);
    rt_sem_detach(&wait_ctx.started);
    rt_sem_detach(&run_ctx.allow_finish);
    rt_sem_detach(&run_ctx.started);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_cancel_all_keep_canceling(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_cancel_all_ctx ctx;
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

    err = rt_sem_init(&ctx.started, "wqcs", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.allow_finish, "wqcf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.done, "wqcd", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.queue = queue;
    ctx.submit_ret1 = -RT_ERROR;
    ctx.submit_ret2 = -RT_ERROR;

    rt_work_init(&work, wq_cancel_all_requeue_fun, (void *)&ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.started, rt_tick_from_millisecond(100));
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
        rt_sem_detach(&ctx.done);
        rt_sem_detach(&ctx.allow_finish);
        rt_sem_detach(&ctx.started);
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

    /* cancel_all must preserve CANCELING on the running work. */
    err = rt_workqueue_cancel_all_work(queue);
    uassert_int_equal(err, RT_EOK);

    rt_sem_release(&ctx.allow_finish);
    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&wait_ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(wait_ctx.err, RT_EOK);
    uassert_int_equal(ctx.submit_ret1, RT_EOK);
    uassert_int_equal(ctx.submit_ret2, -RT_EBUSY);

    rt_sem_detach(&wait_ctx.done);
    rt_sem_detach(&wait_ctx.started);
    rt_sem_detach(&ctx.done);
    rt_sem_detach(&ctx.allow_finish);
    rt_sem_detach(&ctx.started);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_stress_submit_cancel(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct wq_stress_group group;
    struct wq_stress_item items[8];
    struct wq_stress_thread_ctx ctx1;
    struct wq_stress_thread_ctx ctx2;
    rt_thread_t thread1;
    rt_thread_t thread2;
    rt_err_t err;
    rt_int32_t i;
    rt_int32_t total_submit = 0;
    rt_int32_t total_exec = 0;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    rt_memset(&group, 0, sizeof(group));
    group.queue = queue;
    group.items = items;

    for (i = 0; i < 8; i++)
    {
        rt_atomic_store(&group.submit_cnt[i], 0);
        rt_atomic_store(&group.exec_cnt[i], 0);
        items[i].group = &group;
        items[i].index = (rt_uint8_t)i;
        rt_work_init(&items[i].work, wq_stress_work_fun, (void *)&items[i]);
    }

    err = rt_sem_init(&ctx1.done, "wqs1", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx2.done, "wqs2", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx1.group = &group;
    ctx2.group = &group;
    ctx1.seed = 0x12345678u;
    ctx2.seed = 0x87654321u;

    thread1 = rt_thread_create("wqs1", wq_stress_thread_entry, &ctx1,
                               1024, wq_get_test_thread_priority(1), 10);
    uassert_not_null(thread1);
    if (thread1 == RT_NULL)
    {
        rt_sem_detach(&ctx2.done);
        rt_sem_detach(&ctx1.done);
        rt_workqueue_destroy(queue);
        return;
    }
    thread2 = rt_thread_create("wqs2", wq_stress_thread_entry, &ctx2,
                               1024, wq_get_test_thread_priority(1), 10);
    uassert_not_null(thread2);
    if (thread2 == RT_NULL)
    {
        rt_thread_delete(thread1);
        rt_sem_detach(&ctx2.done);
        rt_sem_detach(&ctx1.done);
        rt_workqueue_destroy(queue);
        return;
    }

    rt_thread_startup(thread1);
    rt_thread_startup(thread2);

    err = rt_sem_take(&ctx1.done, rt_tick_from_millisecond(500));
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_take(&ctx2.done, rt_tick_from_millisecond(500));
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_destroy_sync(queue);
    uassert_int_equal(err, RT_EOK);

    for (i = 0; i < 8; i++)
    {
        rt_atomic_t submits = rt_atomic_load(&group.submit_cnt[i]);
        rt_atomic_t execs = rt_atomic_load(&group.exec_cnt[i]);

        uassert_true(execs <= submits);
        total_submit += submits;
        total_exec += execs;
    }

    uassert_true(total_submit > 0);
    uassert_true(total_exec <= total_submit);

    rt_sem_detach(&ctx2.done);
    rt_sem_detach(&ctx1.done);
}

static void test_workqueue_cross_queue_running_reject(void)
{
    struct rt_workqueue *queue1;
    struct rt_workqueue *queue2;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_sync_ctx ctx;
    volatile int work_flag = 0;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(-1);
    queue1 = rt_workqueue_create("test1", 2048, curr_priority);
    uassert_not_null(queue1);
    if (queue1 == RT_NULL)
    {
        return;
    }
    queue2 = rt_workqueue_create("test2", 2048, curr_priority);
    uassert_not_null(queue2);
    if (queue2 == RT_NULL)
    {
        rt_workqueue_destroy(queue1);
        return;
    }

    err = rt_sem_init(&ctx.started, "wqrs", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.allow_finish, "wqrf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.phase = 1;
    ctx.count = 0;
    ctx.done = 0;

    rt_work_init(&work, wq_sync_work_fun, (void *)&ctx);
    err = rt_workqueue_submit_work(queue1, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    /* Phase: reject cross-queue ops while running. */
    err = rt_workqueue_submit_work(queue2, &work, 0);
    uassert_int_equal(err, -RT_EBUSY);
    err = rt_workqueue_urgent_work(queue2, &work);
    uassert_int_equal(err, -RT_EBUSY);
    err = rt_workqueue_cancel_work(queue2, &work);
    uassert_int_equal(err, -RT_EBUSY);
    err = rt_workqueue_cancel_work_sync(queue2, &work);
    uassert_int_equal(err, -RT_EBUSY);

    rt_sem_release(&ctx.allow_finish);
    rt_thread_delay(rt_tick_from_millisecond(10));
    uassert_int_equal(ctx.count, 1);

    /* Phase: reject cross-queue ops while pending/delayed. */
    work_flag = 0;
    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);
    err = rt_workqueue_submit_work(queue1, &work, rt_tick_from_millisecond(50));
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_submit_work(queue2, &work, 0);
    uassert_int_equal(err, -RT_EBUSY);
    err = rt_workqueue_urgent_work(queue2, &work);
    uassert_int_equal(err, -RT_EBUSY);
    err = rt_workqueue_cancel_work(queue2, &work);
    uassert_int_equal(err, -RT_EBUSY);
    err = rt_workqueue_cancel_work_sync(queue2, &work);
    uassert_int_equal(err, -RT_EBUSY);

    err = rt_workqueue_cancel_work(queue1, &work);
    uassert_int_equal(err, RT_EOK);

    rt_sem_detach(&ctx.allow_finish);
    rt_sem_detach(&ctx.started);
    rt_workqueue_destroy_sync(queue1);
    rt_workqueue_destroy(queue2);
}

static void test_workqueue_cancel_pending(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_uint16_t status;
    rt_err_t err;

    /* 1 lower priority than the current test thread */
    curr_priority = wq_get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }
    work_flag = 0;
    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);
    /* Cancel the work before it is executed */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    /* Cancel pending work. */
    err = rt_workqueue_cancel_work(queue, &work);
    uassert_int_equal(err, RT_EOK);
    status = rt_workqueue_get_work_status(queue, &work);
    uassert_true(status & RT_WORK_STATUS_CANCELED);

    rt_thread_delay(rt_tick_from_millisecond(5));
    uassert_int_equal(work_flag, 0);

    /* Cancel delayed pending work. */
    work_flag = 0;
    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);
    err = rt_workqueue_submit_work(queue, &work, rt_tick_from_millisecond(20));
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(10));
    err = rt_workqueue_cancel_work(queue, &work);
    uassert_int_equal(err, RT_EOK);
    status = rt_workqueue_get_work_status(queue, &work);
    uassert_true(status & RT_WORK_STATUS_CANCELED);

    rt_thread_delay(rt_tick_from_millisecond(15));
    uassert_int_equal(work_flag, 0);

    rt_thread_delay(rt_tick_from_millisecond(100));
    rt_workqueue_destroy(queue);
}

static void test_workqueue_cancel_delayed_head_refresh(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work_head;
    struct rt_work work_next;
    volatile int work_flag1 = 0;
    volatile int work_flag2 = 0;
    rt_tick_t old_timeout_tick = 0;
    rt_tick_t new_timeout_tick = 0;
    rt_err_t err;
    int tries;
    rt_bool_t refreshed = RT_FALSE;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    rt_work_init(&work_head, wq_inc_work_fun, (void *)&work_flag1);
    rt_work_init(&work_next, wq_inc_work_fun, (void *)&work_flag2);

    err = rt_workqueue_submit_work(queue, &work_head, rt_tick_from_millisecond(60));
    uassert_int_equal(err, RT_EOK);
    err = rt_workqueue_submit_work(queue, &work_next, rt_tick_from_millisecond(140));
    uassert_int_equal(err, RT_EOK);

    /* White-box regression: canceling delayed head should refresh the worker timeout. */
    for (tries = 0; tries < 10; tries++)
    {
        old_timeout_tick = queue->work_thread->thread_timer.timeout_tick;
        if ((old_timeout_tick - rt_tick_get()) < RT_TICK_MAX / 2 &&
            old_timeout_tick != 0)
        {
            break;
        }
        rt_thread_delay(rt_tick_from_millisecond(5));
    }
    uassert_true(old_timeout_tick != 0);

    err = rt_workqueue_cancel_work(queue, &work_head);
    uassert_int_equal(err, RT_EOK);

    for (tries = 0; tries < 10; tries++)
    {
        new_timeout_tick = queue->work_thread->thread_timer.timeout_tick;
        if (wq_timeout_shifted_later(new_timeout_tick,
                                     old_timeout_tick,
                                     rt_tick_from_millisecond(40)))
        {
            refreshed = RT_TRUE;
            break;
        }
        rt_thread_delay(rt_tick_from_millisecond(5));
    }
    uassert_true(refreshed);
    uassert_int_equal(work_flag1, 0);
    uassert_int_equal(work_flag2, 0);

    err = rt_workqueue_destroy_sync(queue);
    uassert_int_equal(err, RT_EOK);
}

static void test_workqueue_cancel_after_done(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_done_ctx ctx;
    rt_err_t err;

    /* 1 higher priority than the current test thread */
    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.done, "wqcd", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.flag = 0;

    rt_work_init(&work, wq_done_work_fun, (void *)&ctx);
    /* Cancel after completion should succeed. */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(ctx.flag, 1);
    /* Ensure the workqueue thread finishes cleanup before cancel. */
    rt_thread_delay(rt_tick_from_millisecond(5));

    err = rt_workqueue_cancel_work(queue, &work);
    uassert_int_equal(err, RT_EOK);

    /* cancel_sync after completion should also succeed. */
    err = rt_workqueue_cancel_work_sync(queue, &work);
    uassert_int_equal(err, RT_EOK);

    rt_sem_detach(&ctx.done);
    rt_thread_delay(rt_tick_from_millisecond(100));
    rt_workqueue_destroy(queue);
}

static void test_workqueue_cancel_sync_running_waits_done(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 lower priority than the current test thread */
    curr_priority = wq_get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }
    rt_work_init(&work, wq_delay_flag_work_fun, (void *)&work_flag);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(5));
    /* Cancel should report busy while running. */
    err = rt_workqueue_cancel_work(queue, &work);
    uassert_int_equal(err, -RT_EBUSY);
    /* cancel_sync waits for the running work. */
    err = rt_workqueue_cancel_work_sync(queue, &work);
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(work_flag, 1);

    rt_thread_delay(rt_tick_from_millisecond(100));
    rt_workqueue_destroy(queue);
}

static void test_workqueue_cancel_not_queued(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    /* Canceling an unqueued work item is a no-op. */
    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);
    err = rt_workqueue_cancel_work(queue, &work);
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(work_flag, 0);

    err = rt_workqueue_cancel_work_sync(queue, &work);
    uassert_int_equal(err, RT_EOK);

    rt_workqueue_destroy(queue);
}
static void test_workqueue_cancel_all_keep_running(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work_running;
    struct rt_work work_pending;
    struct rt_work work_delayed;
    struct wq_sync_ctx ctx;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 higher priority than the current test thread */
    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.started, "wqca", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.allow_finish, "wqcf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.phase = 1;
    ctx.count = 0;
    ctx.done = 0;

    rt_work_init(&work_running, wq_sync_work_fun, (void *)&ctx);
    rt_work_init(&work_pending, wq_inc_work_fun, (void *)&work_flag);
    rt_work_init(&work_delayed, wq_inc_work_fun, (void *)&work_flag);

    err = rt_workqueue_submit_work(queue, &work_running, 0);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_take(&ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_submit_work(queue, &work_pending, 0);
    uassert_int_equal(err, RT_EOK);
    err = rt_workqueue_submit_work(queue, &work_delayed, rt_tick_from_millisecond(20));
    uassert_int_equal(err, RT_EOK);

    /* cancel_all keeps running work. */
    err = rt_workqueue_cancel_all_work(queue);
    uassert_int_equal(err, RT_EOK);

    rt_sem_release(&ctx.allow_finish);
    rt_thread_delay(rt_tick_from_millisecond(10));

    uassert_int_equal(ctx.count, 1);
    uassert_int_equal(work_flag, 0);

    rt_sem_detach(&ctx.allow_finish);
    rt_sem_detach(&ctx.started);
    rt_workqueue_destroy(queue);

    /* cancel_all on a delayed-only list. */
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    work_flag = 0;
    rt_work_init(&work_delayed, wq_inc_work_fun, (void *)&work_flag);
    err = rt_workqueue_submit_work(queue, &work_delayed, rt_tick_from_millisecond(30));
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_cancel_all_work(queue);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(40));
    uassert_int_equal(work_flag, 0);

    rt_workqueue_destroy(queue);
}

void workqueue_cancel_testcase(void)
{
    /* Cancel sync on pending work. */
    UTEST_UNIT_RUN(test_workqueue_cancel_sync_pending);
    /* Pending cancel_sync should stay on the no-wait path. */
    UTEST_UNIT_RUN(test_workqueue_cancel_sync_pending_scheduler_unavailable_ok);
    /* Running cancel_sync returns busy when scheduler is unavailable */
    UTEST_UNIT_RUN(test_workqueue_cancel_sync_scheduler_unavailable_busy);
    /* cancel_sync should reuse completion after the first run. */
    UTEST_UNIT_RUN(test_workqueue_cancel_sync_reuse_completion);
    /* Cancel sync rejects callback requeue. */
    UTEST_UNIT_RUN(test_workqueue_cancel_sync_requeue);
    /* Cancel sync removes early callback requeue. */
    UTEST_UNIT_RUN(test_workqueue_cancel_sync_requeue_early);
    /* Second cancel_sync waiter returns busy. */
    UTEST_UNIT_RUN(test_workqueue_cancel_sync_double_waiter_busy);
    /* cancel_sync inside callback returns busy. */
    UTEST_UNIT_RUN(test_workqueue_cancel_sync_in_callback_busy);
    /* Status query should report canceling while cancel_sync waits */
    UTEST_UNIT_RUN(test_workqueue_status_canceling);
    /* cancel_all must preserve CANCELING. */
    UTEST_UNIT_RUN(test_workqueue_cancel_all_keep_canceling);
    /* Stress submit/cancel with fixed seed */
    UTEST_UNIT_RUN(test_workqueue_stress_submit_cancel);
    /* Reject cross-queue operations (running + pending/delayed) */
    UTEST_UNIT_RUN(test_workqueue_cross_queue_running_reject);
    /* Cancel pending and delayed work. */
    UTEST_UNIT_RUN(test_workqueue_cancel_pending);
    /* Canceling delayed head should refresh worker timeout */
    UTEST_UNIT_RUN(test_workqueue_cancel_delayed_head_refresh);
    /* Cancel after completion should succeed. */
    UTEST_UNIT_RUN(test_workqueue_cancel_after_done);
    /* Cancel running work returns busy; cancel_sync waits for completion. */
    UTEST_UNIT_RUN(test_workqueue_cancel_sync_running_waits_done);
    /* Cancel on an unqueued work item should be a no-op. */
    UTEST_UNIT_RUN(test_workqueue_cancel_not_queued);
    /* cancel_all keeps running work. */
    UTEST_UNIT_RUN(test_workqueue_cancel_all_keep_running);
}

#endif /* RT_USING_DEVICE_IPC */
