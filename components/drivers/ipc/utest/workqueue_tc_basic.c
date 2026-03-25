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
 * 2026-03-20     RyanCW       split workqueue utest and cover basic/status APIs
 */

/**
 * Test Case Name: IPC Workqueue Test
 *
 * Test Objectives:
 * - Validate workqueue creation, submission, and execution mechanisms.
 * - Verify FIFO, urgent insertion, and delayed ordering behaviors.
 * - Verify reschedule and repeat submission semantics.
 * - Test core APIs: rt_workqueue_create(), rt_workqueue_submit_work(),
 *   rt_workqueue_dowork(), rt_workqueue_urgent_work().
 * - Test system workqueue APIs: rt_work_submit(), rt_work_urgent(),
 *   rt_work_cancel(), rt_work_cancel_sync(), rt_work_get_status().
 *
 * Test Scenarios:
 * - Multiple work items with varying delays validate ordering and scheduling.
 * - Urgent insertion runs ahead of pending items.
 * - Reschedule path (delayed <-> immediate) executes once as expected.
 * - Repeat submissions for pending/running/delayed items behave correctly.
 * - System workqueue APIs are validated when enabled.
 *
 * Verification Metrics:
 * - Submitted work items execute with expected order and parameters.
 * - Same-timeout delayed items keep FIFO order.
 * - Rescheduled work executes once per cycle.
 * - Repeat submissions follow defined semantics (pending once, running twice).
 * - System workqueue APIs return expected results when enabled.
 * - System workqueue cancel_sync waits for running work and status reflects DONE/CANCELED.
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
/* Workqueue basic tests: submit/order/urgent/reschedule/repeat/system APIs. */
#include "rtthread.h"
#include "rtdevice.h"
#include <rthw.h>
#include "utest.h"

#ifdef RT_USING_DEVICE_IPC

/* Other workqueue test groups. */
extern void workqueue_cancel_testcase(void);
extern void workqueue_destroy_testcase(void);

rt_uint8_t wq_get_test_thread_priority(rt_int8_t pos)
{
    rt_int16_t priority;

    priority = RT_SCHED_PRIV(rt_thread_self()).init_priority;
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

struct wq_flag_ctx
{
    struct rt_semaphore done;
    volatile int flag;
};

struct wq_order_ctx
{
    struct rt_semaphore done;
    struct rt_semaphore start;
    struct rt_semaphore finish;
    volatile int seq;
    volatile int order_first;
    volatile int order_second;
};

struct wq_order_item
{
    struct wq_order_ctx *ctx;
    volatile int *target;
    volatile rt_tick_t *stamp;
};

struct wq_repeat_ctx
{
    struct rt_workqueue *queue;
    struct rt_semaphore done;
    volatile int count;
};

struct wq_sys_block_ctx
{
    struct rt_semaphore started;
    struct rt_semaphore allow_finish;
};

struct wq_sys_release_ctx
{
    struct rt_semaphore *sem;
    rt_tick_t delay;
};

static rt_bool_t wq_timeout_shifted_later(rt_tick_t new_tick,
                                          rt_tick_t old_tick,
                                          rt_tick_t min_delta)
{
    rt_tick_t delta = new_tick - old_tick;

    return (delta < RT_TICK_MAX / 2) && (delta >= min_delta);
}

static void wq_flag_work_fun(struct rt_work *work, void *work_data)
{
    struct wq_flag_ctx *ctx = (struct wq_flag_ctx *)work_data;

    ctx->flag = 1;
    rt_sem_release(&ctx->done);
}

static void wq_order_work_fun(struct rt_work *work, void *work_data)
{
    struct wq_order_item *item = (struct wq_order_item *)work_data;

    *item->target = ++item->ctx->seq;
    if (item->stamp != RT_NULL)
    {
        *item->stamp = rt_tick_get();
    }
    rt_sem_release(&item->ctx->done);
}

static void wq_urgent_block_fun(struct rt_work *work, void *work_data)
{
    struct wq_order_ctx *ctx = (struct wq_order_ctx *)work_data;

    rt_sem_release(&ctx->start);
    rt_sem_take(&ctx->finish, RT_WAITING_FOREVER);
}

static void wq_inc_work_fun(struct rt_work *work, void *work_data)
{
    *((int *)work_data) += 1;
}

static void wq_inc_delay_work_fun(struct rt_work *work, void *work_data)
{
    rt_thread_delay(rt_tick_from_millisecond(10));
    *((int *)work_data) += 1;
}

static void wq_sys_block_fun(struct rt_work *work, void *work_data)
{
    struct wq_sys_block_ctx *ctx = (struct wq_sys_block_ctx *)work_data;

    rt_sem_release(&ctx->started);
    rt_sem_take(&ctx->allow_finish, RT_WAITING_FOREVER);
}

static void wq_sys_release_entry(void *parameter)
{
    struct wq_sys_release_ctx *ctx = (struct wq_sys_release_ctx *)parameter;

    rt_thread_delay(ctx->delay);
    rt_sem_release(ctx->sem);
}

static void wq_repeat_requeue_fun(struct rt_work *work, void *work_data)
{
    struct wq_repeat_ctx *ctx = (struct wq_repeat_ctx *)work_data;

    /* Requeue itself to build a deterministic count. */
    ctx->count += 1;
    if (ctx->count < 20)
    {
        rt_workqueue_submit_work(ctx->queue, work, 0);
    }
    else
    {
        rt_sem_release(&ctx->done);
    }
}

static void test_workqueue_submit_immediate(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_flag_ctx ctx;
    rt_err_t err;

    /* 1 higher priority than the current test thread */
    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.done, "wqdw", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.flag = 0;

    rt_work_init(&work, wq_flag_work_fun, (void *)&ctx);
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(ctx.flag, 1);

    /* Dowork API should behave the same as immediate submit. */
    ctx.flag = 0;
    rt_work_init(&work, wq_flag_work_fun, (void *)&ctx);
    err = rt_workqueue_dowork(queue, &work);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(ctx.flag, 1);

    rt_sem_detach(&ctx.done);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_submit_invalid_tick(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;
    rt_tick_t invalid_tick;

    curr_priority = wq_get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    invalid_tick = (rt_tick_t)(RT_TICK_MAX / 2);
    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);
    err = rt_workqueue_submit_work(queue, &work, invalid_tick);
    uassert_int_equal(err, -RT_ERROR);
    uassert_int_equal(work_flag, 0);

    rt_workqueue_destroy(queue);
}

static void test_workqueue_ordering(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work1;
    struct rt_work work2;
    struct rt_work work_block;
    struct rt_work work_urgent;
    struct rt_work work_normal;
    struct wq_order_ctx ctx;
    struct wq_order_item item1;
    struct wq_order_item item2;
    struct wq_order_item item_urgent;
    struct wq_order_item item_normal;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.done, "wqfo", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.seq = 0;
    ctx.order_first = 0;
    ctx.order_second = 0;

    /* Phase: FIFO order. */
    item1.ctx = &ctx;
    item1.target = &ctx.order_first;
    item2.ctx = &ctx;
    item2.target = &ctx.order_second;
    item1.stamp = RT_NULL;
    item2.stamp = RT_NULL;

    rt_work_init(&work1, wq_order_work_fun, (void *)&item1);
    rt_work_init(&work2, wq_order_work_fun, (void *)&item2);

    err = rt_workqueue_submit_work(queue, &work1, 0);
    uassert_int_equal(err, RT_EOK);
    err = rt_workqueue_submit_work(queue, &work2, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(ctx.order_first, 1);
    uassert_int_equal(ctx.order_second, 2);

    rt_sem_detach(&ctx.done);
    /* Phase: urgent order. */
    err = rt_sem_init(&ctx.start, "wqus", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.finish, "wquf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.done, "wqud", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.seq = 0;
    ctx.order_first = 0;
    ctx.order_second = 0;

    item_urgent.ctx = &ctx;
    item_urgent.target = &ctx.order_first;
    item_normal.ctx = &ctx;
    item_normal.target = &ctx.order_second;
    item_urgent.stamp = RT_NULL;
    item_normal.stamp = RT_NULL;

    rt_work_init(&work_block, wq_urgent_block_fun, (void *)&ctx);
    rt_work_init(&work_urgent, wq_order_work_fun, (void *)&item_urgent);
    rt_work_init(&work_normal, wq_order_work_fun, (void *)&item_normal);

    err = rt_workqueue_submit_work(queue, &work_block, 0);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_take(&ctx.start, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_submit_work(queue, &work_normal, 0);
    uassert_int_equal(err, RT_EOK);
    err = rt_workqueue_urgent_work(queue, &work_urgent);
    uassert_int_equal(err, RT_EOK);

    rt_sem_release(&ctx.finish);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(ctx.order_first, 1);
    uassert_int_equal(ctx.order_second, 2);

    rt_sem_detach(&ctx.done);
    rt_sem_detach(&ctx.finish);
    rt_sem_detach(&ctx.start);

    /* Phase: urgent on already queued work (move to head). */
    err = rt_sem_init(&ctx.start, "wqup", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.finish, "wquq", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.done, "wqux", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.seq = 0;
    ctx.order_first = 0;
    ctx.order_second = 0;

    item_urgent.ctx = &ctx;
    item_urgent.target = &ctx.order_first;
    item_normal.ctx = &ctx;
    item_normal.target = &ctx.order_second;
    item_urgent.stamp = RT_NULL;
    item_normal.stamp = RT_NULL;

    rt_work_init(&work_block, wq_urgent_block_fun, (void *)&ctx);
    rt_work_init(&work_urgent, wq_order_work_fun, (void *)&item_urgent);
    rt_work_init(&work_normal, wq_order_work_fun, (void *)&item_normal);

    err = rt_workqueue_submit_work(queue, &work_block, 0);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_take(&ctx.start, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    err = rt_workqueue_submit_work(queue, &work_normal, 0);
    uassert_int_equal(err, RT_EOK);
    err = rt_workqueue_submit_work(queue, &work_urgent, 0);
    uassert_int_equal(err, RT_EOK);
    /* Move an already queued work to the head. */
    err = rt_workqueue_urgent_work(queue, &work_urgent);
    uassert_int_equal(err, RT_EOK);

    rt_sem_release(&ctx.finish);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(ctx.order_first, 1);
    uassert_int_equal(ctx.order_second, 2);

    rt_sem_detach(&ctx.done);
    rt_sem_detach(&ctx.finish);
    rt_sem_detach(&ctx.start);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_delayed_order(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work_long;
    struct rt_work work_mid;
    struct rt_work work_short;
    struct wq_order_ctx ctx;
    struct wq_order_item item_long;
    struct wq_order_item item_mid;
    struct wq_order_item item_short;
    volatile int order_long = 0;
    volatile rt_tick_t long_at = 0;
    volatile rt_tick_t mid_at = 0;
    volatile rt_tick_t short_at = 0;
    rt_tick_t short_submit_at;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.done, "wqdo", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.seq = 0;
    ctx.order_first = 0;
    ctx.order_second = 0;

    item_long.ctx = &ctx;
    item_long.target = &order_long;
    item_long.stamp = &long_at;
    item_mid.ctx = &ctx;
    item_mid.target = &ctx.order_second;
    item_mid.stamp = &mid_at;
    item_short.ctx = &ctx;
    item_short.target = &ctx.order_first;
    item_short.stamp = &short_at;

    rt_work_init(&work_long, wq_order_work_fun, (void *)&item_long);
    rt_work_init(&work_mid, wq_order_work_fun, (void *)&item_mid);
    rt_work_init(&work_short, wq_order_work_fun, (void *)&item_short);

    /* Phase: delayed order + reschedule. */
    /* Submit a long delay first so the queue can sleep on delayed_list. */
    err = rt_workqueue_submit_work(queue, &work_long, rt_tick_from_millisecond(80));
    uassert_int_equal(err, RT_EOK);
    rt_thread_delay(rt_tick_from_millisecond(5));
    short_submit_at = rt_tick_get();
    /* Submit a shorter delay; it should wake and run earlier. */
    err = rt_workqueue_submit_work(queue, &work_short, rt_tick_from_millisecond(20));
    uassert_int_equal(err, RT_EOK);
    /* Insert a medium delay to exercise middle insertion. */
    err = rt_workqueue_submit_work(queue, &work_mid, rt_tick_from_millisecond(50));
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(ctx.order_first, 1);
    uassert_int_equal(ctx.order_second, 2);
    uassert_int_equal(order_long, 3);
    uassert_true(short_at != 0);
    uassert_true(mid_at != 0);
    uassert_true(long_at != 0);
    if (short_at != 0)
    {
        uassert_true((short_at - short_submit_at) >= rt_tick_from_millisecond(20));
    }
    if (short_at != 0 && mid_at != 0)
    {
        /* Mid delay should finish after short delay (wrap-safe compare). */
        uassert_true((mid_at - short_at) < RT_TICK_MAX / 2);
    }
    if (mid_at != 0 && long_at != 0)
    {
        /* Long delay should finish after mid delay (wrap-safe compare). */
        uassert_true((long_at - mid_at) < RT_TICK_MAX / 2);
    }

    rt_sem_detach(&ctx.done);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_delayed_same_timeout_fifo(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work_block;
    struct rt_work work1;
    struct rt_work work2;
    struct rt_work work3;
    struct wq_order_ctx ctx;
    struct wq_order_item item1;
    struct wq_order_item item2;
    struct wq_order_item item3;
    volatile int order1 = 0;
    volatile int order2 = 0;
    volatile int order3 = 0;
    rt_tick_t ticks;
    rt_base_t level;
    rt_err_t err;
    rt_err_t err1;
    rt_err_t err2;
    rt_err_t err3;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.done, "wqef", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.start, "wqes", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&ctx.finish, "wqee", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.seq = 0;
    ctx.order_first = 0;
    ctx.order_second = 0;

    item1.ctx = &ctx;
    item1.target = &order1;
    item1.stamp = RT_NULL;
    item2.ctx = &ctx;
    item2.target = &order2;
    item2.stamp = RT_NULL;
    item3.ctx = &ctx;
    item3.target = &order3;
    item3.stamp = RT_NULL;

    rt_work_init(&work1, wq_order_work_fun, (void *)&item1);
    rt_work_init(&work2, wq_order_work_fun, (void *)&item2);
    rt_work_init(&work3, wq_order_work_fun, (void *)&item3);

    /* Phase: same-timeout FIFO order for delayed list. */
    rt_work_init(&work_block, wq_urgent_block_fun, (void *)&ctx);
    err = rt_workqueue_submit_work(queue, &work_block, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.start, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    ticks = rt_tick_from_millisecond(100);
    uassert_true(ticks > 0 && ticks < RT_TICK_MAX / 2);
    /* Disable interrupts to keep the same tick for FIFO ordering. */
    level = rt_hw_interrupt_disable();
    err1 = rt_workqueue_submit_work(queue, &work1, ticks);
    err2 = rt_workqueue_submit_work(queue, &work2, ticks);
    err3 = rt_workqueue_submit_work(queue, &work3, ticks);
    rt_hw_interrupt_enable(level);

    uassert_int_equal(err1, RT_EOK);
    uassert_int_equal(err2, RT_EOK);
    uassert_int_equal(err3, RT_EOK);

    rt_sem_release(&ctx.finish);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(300));
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(300));
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(300));
    uassert_int_equal(err, RT_EOK);

    uassert_int_equal(order1, 1);
    uassert_int_equal(order2, 2);
    uassert_int_equal(order3, 3);

    rt_sem_detach(&ctx.finish);
    rt_sem_detach(&ctx.start);
    rt_sem_detach(&ctx.done);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_urgent_delayed(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_order_ctx ctx;
    struct wq_order_item item;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.done, "wqud", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.seq = 0;
    ctx.order_first = 0;
    ctx.order_second = 0;

    item.ctx = &ctx;
    item.target = &ctx.order_first;
    item.stamp = RT_NULL;

    rt_work_init(&work, wq_order_work_fun, (void *)&item);
    err = rt_workqueue_submit_work(queue, &work, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);
    rt_thread_delay(rt_tick_from_millisecond(5));

    /* Phase: urgent moves delayed work to head and wakes sleeper. */
    err = rt_workqueue_urgent_work(queue, &work);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(60));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(ctx.order_first, 1);

    rt_sem_detach(&ctx.done);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_reschedule_switch(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_order_ctx ctx;
    struct wq_order_item item;
    rt_err_t err;

    curr_priority = wq_get_test_thread_priority(1);
    queue = rt_workqueue_create("test", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.done, "wqrs", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.seq = 0;
    ctx.order_first = 0;
    ctx.order_second = 0;

    item.ctx = &ctx;
    item.target = &ctx.order_first;
    item.stamp = RT_NULL;

    rt_work_init(&work, wq_order_work_fun, (void *)&item);

    /* Phase: delayed -> immediate reschedule (execute once). */
    err = rt_workqueue_submit_work(queue, &work, rt_tick_from_millisecond(40));
    uassert_int_equal(err, RT_EOK);
    rt_thread_delay(rt_tick_from_millisecond(5));
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(ctx.order_first, 1);

    rt_thread_delay(rt_tick_from_millisecond(60));
    uassert_int_equal(ctx.order_first, 1);

    rt_sem_detach(&ctx.done);
    err = rt_sem_init(&ctx.done, "wqrs", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);

    ctx.seq = 0;
    ctx.order_first = 0;

    rt_work_init(&work, wq_order_work_fun, (void *)&item);

    /* Phase: immediate -> delayed reschedule (execute after delay). */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);
    err = rt_workqueue_submit_work(queue, &work, rt_tick_from_millisecond(30));
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(10));
    uassert_int_equal(ctx.order_first, 0);

    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(ctx.order_first, 1);

    rt_sem_detach(&ctx.done);
    rt_workqueue_destroy(queue);
}

static void test_workqueue_reschedule_delayed_head_refresh(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
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

    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);
    err = rt_workqueue_submit_work(queue, &work, rt_tick_from_millisecond(60));
    uassert_int_equal(err, RT_EOK);

    /* White-box regression: worker timeout should refresh after delaying the head further. */
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

    err = rt_workqueue_submit_work(queue, &work, rt_tick_from_millisecond(140));
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
    uassert_int_equal(work_flag, 0);

    err = rt_workqueue_destroy_sync(queue);
    uassert_int_equal(err, RT_EOK);
}

static void test_workqueue_repeat_submit(void)
{
    struct rt_workqueue *queue;
    rt_uint8_t curr_priority;
    struct rt_work work;
    volatile int work_flag = 0;
    rt_err_t err;

    /* 1 lower priority than the current test thread */
    curr_priority = wq_get_test_thread_priority(1);
    queue = rt_workqueue_create("test01", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    work_flag = 0;
    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);
    /* Multiple submissions of the same work */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    /* Phase: repeat submit while pending (execute once). */
    /* The same work, before it is executed, can be submitted repeatedly and executed only once */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);
    rt_thread_delay(rt_tick_from_millisecond(10));
    /* Check if it was executed only once */
    uassert_int_equal(work_flag, 1);

    rt_thread_delay(rt_tick_from_millisecond(100));
    rt_workqueue_destroy(queue);
    /* Phase: repeat submit while running (execute twice). */
    curr_priority = wq_get_test_thread_priority(-1);
    queue = rt_workqueue_create("test02", 2048, curr_priority);
    uassert_not_null(queue);
    if (queue == RT_NULL)
    {
        return;
    }

    work_flag = 0;
    rt_work_init(&work, wq_inc_delay_work_fun, (void *)&work_flag);
    /* Submit work with high queue priority that will be executed immediately */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(5));
    /* Re-submission of work in progress */
    err = rt_workqueue_submit_work(queue, &work, 0);
    uassert_int_equal(err, RT_EOK);
    rt_thread_delay(rt_tick_from_millisecond(10));
    uassert_int_equal(work_flag, 1);

    rt_thread_delay(rt_tick_from_millisecond(10));
    uassert_int_equal(work_flag, 2);

    rt_workqueue_destroy(queue);
}

static void test_workqueue_repeat_requeue_limit(void)
{
    rt_uint8_t curr_priority;
    struct rt_work work;
    struct wq_repeat_ctx ctx;
    rt_err_t err;

    /* 1 priority higher than current test thread */
    curr_priority = wq_get_test_thread_priority(-1);
    ctx.queue = rt_workqueue_create("test03", 2048, curr_priority);
    uassert_not_null(ctx.queue);
    if (ctx.queue == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&ctx.done, "wqrr", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    ctx.count = 0;

    rt_work_init(&work, wq_repeat_requeue_fun, (void *)&ctx);
    /* Submit work with high queue priority that will be executed immediately */
    err = rt_workqueue_submit_work(ctx.queue, &work, 0);
    uassert_int_equal(err, RT_EOK);

    /* Wait for the work to be executed 20 times with a timeout */
    err = rt_sem_take(&ctx.done, rt_tick_from_millisecond(500));
    uassert_int_equal(err, RT_EOK);

    /* Check if the work was executed 20 times */
    uassert_int_equal(ctx.count, 20);

    rt_sem_detach(&ctx.done);
    rt_workqueue_destroy(ctx.queue);
}

static void test_workqueue_repeat_delay(void)
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

    work_flag = 0;
    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);

    err = rt_workqueue_submit_work(queue, &work, rt_tick_from_millisecond(20));
    uassert_int_equal(err, RT_EOK);

    /* Phase: delayed repeat before run (execute once). */
    /* At this point the delayed work has not been executed */
    rt_thread_delay(rt_tick_from_millisecond(10));
    /* Re-submission of time-delayed work */
    err = rt_workqueue_submit_work(queue, &work, rt_tick_from_millisecond(20));
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(15));
    uassert_int_equal(work_flag, 0);

    /* Waiting for delayed task execution */
    rt_thread_delay(rt_tick_from_millisecond(15));
    uassert_int_equal(work_flag, 1);

    /* Phase: delayed repeat after run (execute twice). */
    work_flag = 0;
    rt_work_init(&work, wq_inc_delay_work_fun, (void *)&work_flag);

    err = rt_workqueue_submit_work(queue, &work, rt_tick_from_millisecond(20));
    uassert_int_equal(err, RT_EOK);

    /* Waiting for delayed work execution */
    rt_thread_delay(rt_tick_from_millisecond(25));
    err = rt_workqueue_submit_work(queue, &work, rt_tick_from_millisecond(20));
    uassert_int_equal(err, RT_EOK);

    /* Check if the delayed work has been run only once */
    rt_thread_delay(rt_tick_from_millisecond(10));
    uassert_int_equal(work_flag, 1);

    rt_thread_delay(rt_tick_from_millisecond(25));
    /* Check if the delayed work is executed twice */
    uassert_int_equal(work_flag, 2);

    rt_thread_delay(rt_tick_from_millisecond(100));
    rt_workqueue_destroy(queue);
}

static void test_workqueue_state_query(void)
{
    struct rt_workqueue *queue_low;
    struct rt_workqueue *queue_other;
    struct rt_workqueue *queue_high;
    struct rt_work work;
    struct wq_sys_block_ctx block_ctx;
    rt_uint16_t status;
    rt_err_t err;
    volatile int work_flag = 0;

    /* Phase: idle/pending/other-queue states. */
    queue_low = rt_workqueue_create("test", 2048, wq_get_test_thread_priority(1));
    uassert_not_null(queue_low);
    if (queue_low == RT_NULL)
    {
        return;
    }

    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);
    status = rt_workqueue_get_work_status(queue_low, &work);
    uassert_int_equal(status, RT_WORK_STATUS_IDLE);

    err = rt_workqueue_submit_work(queue_low, &work, 0);
    uassert_int_equal(err, RT_EOK);
    status = rt_workqueue_get_work_status(queue_low, &work);
    uassert_true(status & RT_WORK_STATUS_PENDING);

    queue_other = rt_workqueue_create("testo", 2048, wq_get_test_thread_priority(1));
    uassert_not_null(queue_other);
    if (queue_other != RT_NULL)
    {
        status = rt_workqueue_get_work_status(queue_other, &work);
        uassert_int_equal(status, RT_WORK_STATUS_OTHER_QUEUE);
        rt_workqueue_destroy(queue_other);
    }

    err = rt_workqueue_cancel_work(queue_low, &work);
    uassert_int_equal(err, RT_EOK);
    rt_workqueue_destroy(queue_low);

    /* Phase: running state. */
    queue_high = rt_workqueue_create("testr", 2048, wq_get_test_thread_priority(-1));
    uassert_not_null(queue_high);
    if (queue_high == RT_NULL)
    {
        return;
    }

    err = rt_sem_init(&block_ctx.started, "wqst", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&block_ctx.allow_finish, "wqsf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);

    rt_work_init(&work, wq_sys_block_fun, (void *)&block_ctx);
    err = rt_workqueue_submit_work(queue_high, &work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&block_ctx.started, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    status = rt_workqueue_get_work_status(queue_high, &work);
    uassert_true(status & RT_WORK_STATUS_RUNNING);

    rt_sem_release(&block_ctx.allow_finish);
    rt_thread_delay(rt_tick_from_millisecond(5));

    rt_sem_detach(&block_ctx.allow_finish);
    rt_sem_detach(&block_ctx.started);
    rt_workqueue_destroy(queue_high);
}

#ifdef RT_USING_SYSTEM_WORKQUEUE
static void test_workqueue_sys_apis(void)
{
    struct rt_work block_work;
    struct rt_work work;
    struct wq_flag_ctx flag_ctx;
    struct wq_sys_block_ctx block_ctx;
    struct wq_sys_release_ctx release_ctx;
    rt_thread_t release_thread;
    volatile int work_flag;
    rt_uint16_t status;
    rt_err_t err;

    /* Phase: system submit. */
    err = rt_sem_init(&flag_ctx.done, "wqss", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    flag_ctx.flag = 0;

    rt_work_init(&work, wq_flag_work_fun, (void *)&flag_ctx);
    err = rt_work_submit(&work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&flag_ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(flag_ctx.flag, 1);

    rt_sem_detach(&flag_ctx.done);

    /* Phase: system urgent. */
    err = rt_sem_init(&flag_ctx.done, "wqsu", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    flag_ctx.flag = 0;

    rt_work_init(&work, wq_flag_work_fun, (void *)&flag_ctx);
    err = rt_work_urgent(&work);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&flag_ctx.done, rt_tick_from_millisecond(200));
    uassert_int_equal(err, RT_EOK);
    uassert_int_equal(flag_ctx.flag, 1);

    rt_sem_detach(&flag_ctx.done);

    /* Phase: system cancel + status query. */
    err = rt_sem_init(&block_ctx.started, "wqcs", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);
    err = rt_sem_init(&block_ctx.allow_finish, "wqcf", 0, RT_IPC_FLAG_FIFO);
    uassert_int_equal(err, RT_EOK);

    rt_work_init(&block_work, wq_sys_block_fun, (void *)&block_ctx);
    err = rt_work_submit(&block_work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_sem_take(&block_ctx.started, rt_tick_from_millisecond(100));
    uassert_int_equal(err, RT_EOK);

    status = rt_work_get_status(&block_work);
    uassert_true(status & RT_WORK_STATUS_RUNNING);

    err = rt_work_cancel(&block_work);
    uassert_int_equal(err, -RT_EBUSY);

    release_ctx.sem = &block_ctx.allow_finish;
    release_ctx.delay = rt_tick_from_millisecond(40);
    release_thread = rt_thread_create("wqsr", wq_sys_release_entry, &release_ctx,
                                      1024, wq_get_test_thread_priority(1), 10);
    uassert_not_null(release_thread);
    if (release_thread == RT_NULL)
    {
        rt_sem_release(&block_ctx.allow_finish);
        rt_thread_delay(rt_tick_from_millisecond(5));
        rt_sem_detach(&block_ctx.allow_finish);
        rt_sem_detach(&block_ctx.started);
        return;
    }
    rt_thread_startup(release_thread);

    err = rt_work_cancel_sync(&block_work);
    uassert_int_equal(err, RT_EOK);
    status = rt_work_get_status(&block_work);
    uassert_true(status & RT_WORK_STATUS_DONE);

    work_flag = 0;
    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);
    err = rt_work_submit(&work, 0);
    uassert_int_equal(err, RT_EOK);

    err = rt_work_cancel(&work);
    uassert_int_equal(err, RT_EOK);

    rt_thread_delay(rt_tick_from_millisecond(20));
    uassert_int_equal(work_flag, 0);

    /* Phase: system cancel sync on delayed work should report canceled. */
    work_flag = 0;
    rt_work_init(&work, wq_inc_work_fun, (void *)&work_flag);
    err = rt_work_submit(&work, rt_tick_from_millisecond(30));
    uassert_int_equal(err, RT_EOK);
    err = rt_work_cancel_sync(&work);
    uassert_int_equal(err, RT_EOK);
    status = rt_work_get_status(&work);
    uassert_true(status & RT_WORK_STATUS_CANCELED);

    rt_thread_delay(rt_tick_from_millisecond(40));
    uassert_int_equal(work_flag, 0);

    rt_sem_detach(&block_ctx.allow_finish);
    rt_sem_detach(&block_ctx.started);
}
#endif /* RT_USING_SYSTEM_WORKQUEUE */

void workqueue_basic_testcase(void)
{
    /* General work queue test */
    UTEST_UNIT_RUN(test_workqueue_submit_immediate);
    /* Invalid tick submit should return error (non-assert builds) */
    UTEST_UNIT_RUN(test_workqueue_submit_invalid_tick);
    /* Workqueue ordering (FIFO + urgent) */
    UTEST_UNIT_RUN(test_workqueue_ordering);
    /* Delayed work order + reschedule test */
    UTEST_UNIT_RUN(test_workqueue_delayed_order);
    /* Same timeout delayed work keeps FIFO order */
    UTEST_UNIT_RUN(test_workqueue_delayed_same_timeout_fifo);
    /* Urgent on delayed work should run immediately */
    UTEST_UNIT_RUN(test_workqueue_urgent_delayed);
    /* Cross-type reschedule (delay <-> immediate) */
    UTEST_UNIT_RUN(test_workqueue_reschedule_switch);
    /* Delayed-head reschedule should refresh worker timeout */
    UTEST_UNIT_RUN(test_workqueue_reschedule_delayed_head_refresh);
#ifdef RT_USING_SYSTEM_WORKQUEUE
    /* System workqueue APIs test */
    UTEST_UNIT_RUN(test_workqueue_sys_apis);
#endif /* RT_USING_SYSTEM_WORKQUEUE */
    /* Multiple submissions of the same work prior to implementation */
    UTEST_UNIT_RUN(test_workqueue_repeat_submit);
    /* Submitting the same task multiple times in a mission */
    UTEST_UNIT_RUN(test_workqueue_repeat_requeue_limit);
    /* Multiple submissions of the same delayed task before execution */
    UTEST_UNIT_RUN(test_workqueue_repeat_delay);
    /* Work status query API */
    UTEST_UNIT_RUN(test_workqueue_state_query);
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
    workqueue_basic_testcase();
    workqueue_cancel_testcase();
    workqueue_destroy_testcase();
}
/* Workqueue testcase entry. */
UTEST_TC_EXPORT(testcase, "components.drivers.ipc.workqueue_tc", utest_tc_init, utest_tc_cleanup, 300);

#endif /* RT_USING_DEVICE_IPC */
