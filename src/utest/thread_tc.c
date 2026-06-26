 /*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09.01     yangjie      the first version
 * 2021-10.11     mazhiyuan    add idle, yield, suspend, control, priority, delay_until
 * 2025-11-12     Ze-Hou       add standardized utest documentation block
 */

/**
 * Test Case Name: Kernel Core Thread Test
 *
 * Test Objectives:
 * - Validate the core thread management features of the RT-Thread kernel:
 *   1. Thread creation methods (dynamic and static)
 *   2. Timing accuracy (resolution) of the rt_thread_delay API
 *   3. Use of the idle hook
 *   4. RT-Thread’s thread yield mechanism
 *   5. RT-Thread’s thread control interfaces
 *   6. Thread priorities
 *   7. Absolute delay functionality
 *   8. Time-slice scheduling among threads with the same priority
 *
 * Test Scenarios:
 * - Create, start, and delete a dynamic thread to verify dynamic thread lifecycle management
 * - Let a dynamic thread exit normally, then call rt_thread_delete again in cleanup to verify duplicate delete handling
 * - Delete an unstarted dynamic thread and reject another delete during its cleanup
 * - Initialize, start, and detach a static thread to verify static thread lifecycle management
 * - On UP without SMART, reject repeated static detach and reuse the TCB after complete cleanup
 * - On SMP, race two CPUs deleting one unstarted dynamic thread
 * - Delay a thread for a specific tick count and check timing accuracy
 * - Register and remove an idle hook, verifying it is called as expected
 * - Use thread yield to test scheduler fairness among threads of the same priority
 * - Use thread control APIs to start, change priority, and close a thread, verifying each operation
 * - Create a thread with a specific priority and verify it runs as expected
 * - Use rt_thread_delay_until to test absolute delay and periodic task timing
 * - Create multiple threads with the same priority and test time-slice scheduling fairness
 *
 * Verification Metrics:
 * - Threads are created, started, deleted, and detached successfully
 * - Repeated deletion after normal thread exit returns an error without abnormal cleanup
 * - Duplicate deletion/detachment cleans up each lifecycle once
 * - Concurrent deletion returns RT_EOK once and -RT_ERROR once
 * - The precision of both relative delay and absolute delay is correct.
 * - Idle hook is invoked as expected during thread idle periods
 * - Thread yield causes correct scheduling among threads of the same priority
 * - Thread control APIs (startup, change priority, close) work as intended and update thread state correctly
 * - Time-slice scheduling distributes CPU time fairly among threads of the same priority (difference < 30%)
 *
 * Dependencies:
 * - Enable Thread Test (RT-Thread Utestcases -> Kernel Core -> Thread Test)
 * - Test on any RT-Thread supported platform (e.g., qemu-virt64-riscv)
 *
 * Expected Results:
 * - After executing this test in msh, the expected output should be:
 *   "[  PASSED  ] [ result   ] testcase (core.thread_tc)"
 */

#define __RT_IPC_SOURCE__ /* include internal API for utest */

#include <rtthread.h>
#include <stdlib.h>
#include "utest.h"

#define THREAD_STACK_SIZE  UTEST_THR_STACK_SIZE
#define THREAD_TIMESLICE   10
#define THREAD_CLEANUP_TIMEOUT_MS 1000

rt_align(RT_ALIGN_SIZE)
static char thread2_stack[UTEST_THR_STACK_SIZE];
static struct rt_thread thread2;
#ifdef RT_USING_HEAP
    static rt_thread_t tid1 = RT_NULL;
    static rt_thread_t tid3 = RT_NULL;
    static rt_thread_t tid4 = RT_NULL;
    static rt_thread_t tid5 = RT_NULL;
    static rt_thread_t tid6 = RT_NULL;
    static rt_thread_t tid7 = RT_NULL;
    static rt_thread_t tid9 = RT_NULL;
#endif /* RT_USING_HEAP */

static volatile rt_uint32_t tid3_delay_pass_flag = 0;
static volatile rt_uint32_t tid3_finish_flag = 0;
static volatile rt_uint32_t tid4_finish_flag = 0;
static volatile rt_uint32_t tid6_finish_flag = 0;
static volatile rt_uint32_t thread5_source = 0;
static rt_atomic_t thread9_exit_flag = 0;
static rt_atomic_t thread9_cleanup_flag = 0;
static rt_atomic_t thread9_delete_ret = -RT_ERROR;
static rt_bool_t thread9_pending = RT_FALSE;

#ifndef RT_USING_SMP
    static volatile rt_uint32_t thread_yield_flag = 0;
#endif
static volatile rt_uint32_t entry_idle_hook_times = 0;
static rt_thread_t __current_thread;
static rt_uint8_t change_priority;
static volatile rt_uint32_t count = 0;

void thread1_entry(void *param)
{
    while (1);
}

static void test_dynamic_thread(void)
{
    rt_err_t ret_startup = -RT_ERROR;
    rt_err_t ret_delete = -RT_ERROR;

    tid1 = rt_thread_create("thread1",
                            thread1_entry,
                            (void *)1,
                            THREAD_STACK_SIZE,
                            UTEST_THR_PRIORITY + 1,
                            THREAD_TIMESLICE - 5);
    if (tid1 == RT_NULL)
    {
        uassert_false(tid1 == RT_NULL);
        goto __exit;
    }

    ret_startup = rt_thread_startup(tid1);
    if (ret_startup != RT_EOK)
    {
        uassert_false(ret_startup != RT_EOK);
        goto __exit;
    }

    ret_delete = rt_thread_delete(tid1);
    if (ret_delete != RT_EOK)
    {
        uassert_false(ret_delete != RT_EOK);
        goto __exit;
    }

    uassert_true(tid1 != RT_NULL && ret_startup == RT_EOK && ret_delete == RT_EOK);

__exit:
    if (tid1 != RT_NULL && ret_delete != RT_EOK)
    {
        rt_thread_delete(tid1);
    }
    return;
}

void thread2_entry(void *param)
{
    while (1);
}

static void test_static_thread(void)
{
    rt_err_t ret_init = -RT_ERROR;
    rt_err_t ret_startup = -RT_ERROR;
    rt_err_t ret_detach = -RT_ERROR;

    ret_init = rt_thread_init(&thread2,
                              "thread2",
                              thread2_entry,
                              (void *)2,
                              &thread2_stack[0],
                              sizeof(thread2_stack),
                              UTEST_THR_PRIORITY + 1,
                              THREAD_TIMESLICE);
    if (ret_init != RT_EOK)
    {
        uassert_false(ret_init != RT_EOK);
        goto __exit;
    }

    ret_startup = rt_thread_startup(&thread2);
    if (ret_startup != RT_EOK)
    {
        uassert_false(ret_startup != RT_EOK);
        goto __exit;
    }

    ret_detach = rt_thread_detach(&thread2);
    if (ret_detach != RT_EOK)
    {
        uassert_false(ret_detach != RT_EOK);
        goto __exit;
    }

    uassert_true(ret_init == RT_EOK && ret_startup == RT_EOK && ret_detach == RT_EOK);

__exit:
    if (ret_init == RT_EOK && ret_detach != RT_EOK)
    {
        rt_thread_detach(&thread2);
    }
    return;
}

static void thread3_entry(void *parameter)
{
    rt_tick_t tick, latency_tick;
    tick = rt_tick_get();
    rt_thread_delay(15);
    latency_tick = rt_tick_get() - tick;
    if (latency_tick > 16 || latency_tick < 15)
    {
        tid3_finish_flag = 1;
        tid3_delay_pass_flag = 0;
        return;
    }
    tid3_delay_pass_flag = 1;
    tid3_finish_flag = 1;
}

static void test_thread_delay(void)
{
    rt_err_t ret_startup = -RT_ERROR;

    tid3 = rt_thread_create("thread3",
                            thread3_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            UTEST_THR_PRIORITY - 1,
                            THREAD_TIMESLICE);
    if (tid3 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid3 == RT_NULL);
        goto __exit;
    }

    ret_startup = rt_thread_startup(tid3);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        goto __exit;
    }

    while (tid3_finish_flag != 1);
    uassert_true(tid3_delay_pass_flag == 1);

__exit:
    return;
}

static void idle_hook(void)
{
    entry_idle_hook_times ++;
}

static void thread4_entry(void *parameter)
{
    rt_uint32_t delay_times = 5;
    while (delay_times --)
    {
        rt_thread_mdelay(300);
    }
    rt_thread_idle_delhook(idle_hook);
    tid4_finish_flag = 1;
}

static void test_idle_hook(void)
{
    rt_err_t ret_startup = -RT_ERROR;

    rt_thread_idle_sethook(idle_hook);

    tid4 = rt_thread_create("thread4",
                            thread4_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            UTEST_THR_PRIORITY - 1,
                            THREAD_TIMESLICE);
    if (tid4 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid4 == RT_NULL);
        goto __exit;
    }

    ret_startup = rt_thread_startup(tid4);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        goto __exit;
    }

    while (tid4_finish_flag != 1)
    {
        rt_thread_mdelay(200);
    }
    uassert_true(entry_idle_hook_times > 0);

__exit:
    return;
}

static void thread5_entry(void *parameter)
{
    while (1)
    {
        thread5_source ++;
        rt_thread_delay(5);
        if (thread5_source == 5)
        {
            rt_thread_yield();
        }
    }
}

static void thread6_entry(void *parameter)
{
    while (++ thread5_source <= 9);
    tid6_finish_flag = 1;
}

static void test_thread_yield(void)
{
    rt_err_t ret_startup = -RT_ERROR;
    thread5_source = 0;
    tid5 = rt_thread_create("thread5",
                            thread5_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            UTEST_THR_PRIORITY - 1,
                            THREAD_TIMESLICE);
    if (tid5 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid5 == RT_NULL);
        goto __exit;
    }
    ret_startup = rt_thread_startup(tid5);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        goto __exit;
    }
    tid6 = rt_thread_create("thread6",
                            thread6_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            UTEST_THR_PRIORITY - 1,
                            THREAD_TIMESLICE);
    if (tid6 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid6 == RT_NULL);
        goto __exit;
    }
    ret_startup = rt_thread_startup(tid6);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        goto __exit;
    }

    while (tid6_finish_flag != 1);
    uassert_true(thread5_source == 10);

__exit:
    if (tid5 != RT_NULL)
    {
        rt_thread_delete(tid5);
    }
    return;
}

static void thread7_entry(void *parameter)
{
    while (1);
}

static void test_thread_control(void)
{
    rt_err_t ret_control = -RT_ERROR;
    rt_err_t rst_delete = -RT_ERROR;
    rt_sched_lock_level_t slvl;

    tid7 = rt_thread_create("thread7",
                            thread7_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            UTEST_THR_PRIORITY + 1,
                            THREAD_TIMESLICE);
    if (tid7 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid7 == RT_NULL);
        goto __exit;
    }

    ret_control = rt_thread_control(tid7, RT_THREAD_CTRL_STARTUP, RT_NULL);
    if (ret_control != RT_EOK)
    {
        LOG_E("rt_thread_control failed!");
        uassert_false(1);
        goto __exit;
    }
    rt_thread_mdelay(200);
    rt_thread_control(tid7, RT_THREAD_CTRL_CHANGE_PRIORITY, &change_priority);

    rt_sched_lock(&slvl);
    if (rt_sched_thread_get_curr_prio(tid7) != change_priority)
    {
        LOG_E("rt_thread_control failed!");
        uassert_false(1);
        rt_sched_unlock(slvl);
        goto __exit;
    }
    rt_sched_unlock(slvl);

    rst_delete = rt_thread_control(tid7, RT_THREAD_CTRL_CLOSE, RT_NULL);
    if (rst_delete != RT_EOK)
    {
        LOG_E("rt_thread_control failed!");
        uassert_false(rst_delete != RT_EOK);
        goto __exit;
    }

    uassert_true(1);

__exit:
    if (tid7 != RT_NULL && rst_delete != RT_EOK)
    {
        rt_thread_delete(tid7);
    }
    return;
}

static void thread8_entry(void *parameter)
{
    for (; count < 10; count ++);
}

static void test_thread_priority(void)
{
    rt_err_t ret_startup = -RT_ERROR;
    rt_thread_t tid8 = RT_NULL;

    tid8 = rt_thread_create("thread8",
                            thread8_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            UTEST_THR_PRIORITY - 1,
                            THREAD_TIMESLICE);
    if (tid8 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid8 == RT_NULL);
        return;
    }
    count = 0;
    ret_startup = rt_thread_startup(tid8);
    if (ret_startup != RT_EOK)
    {
        uassert_false(ret_startup != RT_EOK);
        return ;
    }
    uassert_true(count == 10);

    return;
}

#ifdef RT_USING_HEAP
static rt_bool_t thread_wait_count(rt_atomic_t *value, rt_atomic_t expected)
{
    rt_tick_t start = rt_tick_get();
    rt_tick_t timeout = rt_tick_from_millisecond(THREAD_CLEANUP_TIMEOUT_MS);

    while (rt_atomic_load(value) < expected)
    {
        if (rt_tick_get() - start >= timeout)
        {
            return RT_FALSE;
        }
        rt_thread_mdelay(1);
    }

    return RT_TRUE;
}

static void thread9_entry(void *parameter)
{
    RT_UNUSED(parameter);

    while (rt_atomic_load(&thread9_exit_flag) == 0)
    {
        rt_thread_mdelay(1);
    }
}

static void thread9_cleanup(struct rt_thread *thread)
{
    rt_atomic_store(&thread9_delete_ret, rt_thread_delete(thread));
    rt_atomic_add(&thread9_cleanup_flag, 1);
}

static void thread_test_delete_again(rt_bool_t exit_normally)
{
    rt_err_t ret;

    if (thread9_pending && !thread_wait_count(&thread9_cleanup_flag, 1))
    {
        uassert_true(RT_FALSE);
        return;
    }
    thread9_pending = RT_FALSE;
    rt_atomic_store(&thread9_exit_flag, 0);
    rt_atomic_store(&thread9_cleanup_flag, 0);
    rt_atomic_store(&thread9_delete_ret, RT_EOK);

    tid9 = rt_thread_create("thread9",
                            thread9_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            UTEST_THR_PRIORITY - 1,
                            THREAD_TIMESLICE);
    if (tid9 == RT_NULL)
    {
        LOG_E("rt_thread_create failed!");
        uassert_false(tid9 == RT_NULL);
        return;
    }

    tid9->cleanup = thread9_cleanup;
    thread9_pending = RT_TRUE;

    if (exit_normally)
    {
        ret = rt_thread_startup(tid9);
        if (ret != RT_EOK)
        {
            uassert_int_equal(ret, RT_EOK);
            rt_thread_delete(tid9);
            return;
        }
        rt_atomic_store(&thread9_exit_flag, 1);
    }
    else
    {
        uassert_int_equal(rt_thread_delete(tid9), RT_EOK);
    }

    /* The callback owns the still-live dynamic object during the second delete. */
    uassert_true(thread_wait_count(&thread9_cleanup_flag, 1));
    uassert_int_equal(rt_atomic_load(&thread9_cleanup_flag), 1);
    uassert_int_equal(rt_atomic_load(&thread9_delete_ret), -RT_ERROR);
}

static void test_thread_exit_delete_again(void)
{
    thread_test_delete_again(RT_TRUE);
}

static void test_thread_delete_again(void)
{
    thread_test_delete_again(RT_FALSE);
}

#if !defined(RT_USING_SMP) && !defined(RT_USING_SMART)
static struct rt_thread detach_thread;
rt_align(RT_ALIGN_SIZE)
static char detach_stack[THREAD_STACK_SIZE];
static rt_thread_t detach_fence;
static rt_atomic_t detach_cleanup_count;
static rt_atomic_t detach_fence_done;
static rt_atomic_t detach_fence_ret;
static rt_bool_t detach_pending;

static void detach_entry(void *parameter)
{
    RT_UNUSED(parameter);
}

static void detach_fence_cleanup(struct rt_thread *thread)
{
    RT_UNUSED(thread);
    rt_atomic_store(&detach_fence_done, 1);
}

static void detach_cleanup(struct rt_thread *thread)
{
    RT_UNUSED(thread);
    rt_atomic_add(&detach_cleanup_count, 1);
    /* Its cleanup runs after the reaper has finished accessing this static TCB. */
    rt_atomic_store(&detach_fence_ret, rt_thread_delete(detach_fence));
}

static void test_thread_detach_again(void)
{
    rt_sched_lock_level_t level;
    rt_uint8_t priority;
    rt_err_t ret, ret_again;
    int cycle;

    rt_sched_lock(&level);
    priority = rt_sched_thread_get_curr_prio(rt_thread_self());
    rt_sched_unlock(level);

    for (cycle = 0; cycle < 2; cycle++)
    {
        if (detach_pending && !thread_wait_count(&detach_fence_done, 1))
        {
            uassert_true(RT_FALSE);
            return;
        }
        detach_pending = RT_FALSE;
        rt_atomic_store(&detach_cleanup_count, 0);
        rt_atomic_store(&detach_fence_done, 0);
        rt_atomic_store(&detach_fence_ret, -RT_ERROR);
        detach_fence = rt_thread_create("detach_fence", detach_entry, RT_NULL,
                                        THREAD_STACK_SIZE, priority, THREAD_TIMESLICE);
        uassert_not_null(detach_fence);
        if (detach_fence == RT_NULL)
        {
            return;
        }
        detach_fence->cleanup = detach_fence_cleanup;
        detach_pending = RT_TRUE;

        ret = rt_thread_init(&detach_thread, "detach_again", detach_entry, RT_NULL,
                             detach_stack, sizeof(detach_stack),
                             priority ? priority - 1 : 0, THREAD_TIMESLICE);
        uassert_int_equal(ret, RT_EOK);
        if (ret != RT_EOK)
        {
            rt_thread_delete(detach_fence);
            return;
        }
        detach_thread.cleanup = detach_cleanup;

        /* This READY test thread keeps the UP idle reaper from running. */
        if (cycle == 0)
        {
            ret = rt_thread_detach(&detach_thread);
        }
        else
        {
            /* Reuse the same TCB after the previous lifecycle was fully reaped. */
            ret = rt_thread_startup(&detach_thread);
            if (ret != RT_EOK)
            {
                uassert_int_equal(ret, RT_EOK);
                rt_thread_detach(&detach_thread);
                return;
            }
            rt_thread_yield();
        }
        ret_again = rt_thread_detach(&detach_thread);
        uassert_int_equal(ret, RT_EOK);
        uassert_int_equal(ret_again, -RT_ERROR);

        uassert_true(thread_wait_count(&detach_fence_done, 1));
        uassert_int_equal(rt_atomic_load(&detach_cleanup_count), 1);
        uassert_int_equal(rt_atomic_load(&detach_fence_ret), RT_EOK);
    }
}
#endif /* !RT_USING_SMP && !RT_USING_SMART */

#if defined(RT_USING_SMP) && RT_CPUS_NR > 1
static struct
{
    struct rt_spinlock lock;
    rt_thread_t target;
    rt_atomic_t ready, start, done, active, attempts;
    rt_atomic_t cleanup_count, cleanup_done, cleanup_timeout, result[2];
    rt_bool_t accepting, pending;
    int started;
} delete_race;

static void delete_race_cleanup(struct rt_thread *thread)
{
    rt_base_t level;
    RT_UNUSED(thread);

    rt_atomic_add(&delete_race.cleanup_count, 1);
    /* SMP has a dedicated reaper; never block an UP idle cleanup this way. */
    if (!thread_wait_count(&delete_race.done, delete_race.started))
    {
        rt_atomic_store(&delete_race.cleanup_timeout, 1);
    }
    level = rt_spin_lock_irqsave(&delete_race.lock);
    delete_race.accepting = RT_FALSE;
    rt_spin_unlock_irqrestore(&delete_race.lock, level);

    /* Close admission before releasing any TCB. A stuck kernel call needs a watchdog. */
    while (rt_atomic_load(&delete_race.active) != 0)
    {
        rt_thread_mdelay(1);
    }
    rt_atomic_store(&delete_race.cleanup_done, 1);
}

static void delete_race_entry(void *parameter)
{
    rt_ubase_t index = (rt_ubase_t)parameter;
    rt_base_t level;
    rt_bool_t admitted = RT_FALSE;
    rt_err_t ret = -RT_ETIMEOUT;

    rt_atomic_add(&delete_race.ready, 1);
    if (thread_wait_count(&delete_race.start, 1) &&
        rt_atomic_load(&delete_race.start) == 1)
    {
        level = rt_spin_lock_irqsave(&delete_race.lock);
        if (delete_race.accepting)
        {
            rt_atomic_add(&delete_race.active, 1);
            admitted = RT_TRUE;
        }
        rt_spin_unlock_irqrestore(&delete_race.lock, level);
        if (admitted)
        {
            rt_atomic_add(&delete_race.attempts, 1);
            ret = rt_thread_delete(delete_race.target);
            rt_atomic_sub(&delete_race.active, 1);
        }
    }
    rt_atomic_store(&delete_race.result[index], ret);
    rt_atomic_add(&delete_race.done, 1);
}

static void test_thread_delete_race(void)
{
    rt_thread_t worker;
    rt_base_t level;
    rt_err_t ret;
    rt_bool_t delete_unused;
    int i;

    if (delete_race.pending &&
        (!thread_wait_count(&delete_race.done, delete_race.started) ||
         !thread_wait_count(&delete_race.cleanup_done, 1)))
    {
        uassert_true(RT_FALSE);
        return;
    }
    rt_memset(&delete_race, 0, sizeof(delete_race));
    rt_spin_lock_init(&delete_race.lock);
    delete_race.accepting = RT_TRUE;

    /* Keep the target unstarted: running-thread reclamation is a separate issue. */
    delete_race.target = rt_thread_create("delete_race", thread9_entry, RT_NULL,
                                          THREAD_STACK_SIZE, UTEST_THR_PRIORITY, THREAD_TIMESLICE);
    uassert_not_null(delete_race.target);
    if (delete_race.target == RT_NULL)
    {
        return;
    }
    delete_race.target->cleanup = delete_race_cleanup;
    delete_race.pending = RT_TRUE;

    for (i = 0; i < 2; i++)
    {
        worker = rt_thread_create("delete_worker", delete_race_entry, (void *)(rt_ubase_t)i,
                                  THREAD_STACK_SIZE, UTEST_THR_PRIORITY, THREAD_TIMESLICE);
        uassert_not_null(worker);
        if (worker == RT_NULL)
        {
            goto __exit;
        }
        ret = rt_thread_control(worker, RT_THREAD_CTRL_BIND_CPU, (void *)(rt_ubase_t)i);
        if (ret == RT_EOK)
        {
            ret = rt_thread_startup(worker);
        }
        uassert_int_equal(ret, RT_EOK);
        if (ret != RT_EOK)
        {
            rt_thread_delete(worker);
            goto __exit;
        }
        delete_race.started++;
    }
    if (!thread_wait_count(&delete_race.ready, 2))
    {
        uassert_true(RT_FALSE);
        goto __exit;
    }
    rt_atomic_store(&delete_race.start, 1);
    uassert_true(thread_wait_count(&delete_race.done, 2));

__exit:
    rt_atomic_store(&delete_race.start, 2);
    uassert_true(thread_wait_count(&delete_race.done, delete_race.started));
    level = rt_spin_lock_irqsave(&delete_race.lock);
    delete_race.accepting = RT_FALSE;
    delete_unused = rt_atomic_load(&delete_race.attempts) == 0;
    if (delete_unused)
    {
        /* Protect the fallback delete from an already-admitted, delayed worker. */
        rt_atomic_add(&delete_race.active, 1);
    }
    rt_spin_unlock_irqrestore(&delete_race.lock, level);
    if (delete_unused)
    {
        rt_thread_delete(delete_race.target);
        rt_atomic_sub(&delete_race.active, 1);
    }
    uassert_true(thread_wait_count(&delete_race.cleanup_done, 1));
    uassert_int_equal(rt_atomic_load(&delete_race.cleanup_timeout), 0);
    uassert_int_equal(rt_atomic_load(&delete_race.cleanup_count), 1);
    uassert_true((rt_atomic_load(&delete_race.result[0]) == RT_EOK &&
                  rt_atomic_load(&delete_race.result[1]) == -RT_ERROR) ||
                 (rt_atomic_load(&delete_race.result[1]) == RT_EOK &&
                  rt_atomic_load(&delete_race.result[0]) == -RT_ERROR));
}
#endif /* RT_USING_SMP && RT_CPUS_NR > 1 */
#endif /* RT_USING_HEAP */

static void test_delay_until(void)
{
    rt_tick_t tick;
    rt_tick_t check_tick = 0;
    rt_tick_t delta = 0;

    tick = rt_tick_get();

    check_tick = tick;
    rt_thread_delay_until(&tick, 100);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[100] -> %d\n", delta);
    uassert_int_equal(delta, 100);

    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 200);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[200] -> %d\n", delta);
    uassert_int_equal(delta, 200);

    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 300);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[300] -> %d\n", delta);
    uassert_int_equal(delta, 300);

    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 100);
    delta = rt_tick_get() - check_tick;
    uassert_int_equal(delta, 100);

    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 50);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[50] -> %d\n", delta);
    uassert_int_equal(delta, 50);

    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 20);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[20] -> %d\n", delta);
    uassert_int_equal(delta, 20);

    /**
     * the rt_kprints above can take few ticks to complete, maybe more than 10
     */
    tick = rt_tick_get();
    check_tick = tick;
    rt_thread_delay(2);
    rt_thread_delay_until(&tick, 10);
    delta = rt_tick_get() - check_tick;
    rt_kprintf("delta[10] -> %d\n", delta);
    uassert_int_equal(delta, 10);
}

static rt_thread_t tidA, tidB1, tidB2;
static uint32_t timeslice_cntA, timeslice_cntB1, timeslice_cntB2;

static void test_timeslice_threadA_entry(void *parameter)
{
    while (1)
    {
        rt_thread_delay(2);
        timeslice_cntA++;
        if (timeslice_cntA > 10) return;
    }
}
static void test_timeslice_threadB1_entry(void *parameter)
{
    while (1)
    {
        timeslice_cntB1++;
        if (timeslice_cntA > 10) return;
    }
}
static void test_timeslice_threadB2_entry(void *parameter)
{
    while (1)
    {
        timeslice_cntB2++;
        if (timeslice_cntA > 10) return;
    }
}

void test_timeslice(void)
{
    rt_err_t ret_startup = -RT_ERROR;
    uint32_t diff;

    timeslice_cntA = 0;
    timeslice_cntB1 = 0;
    timeslice_cntB2 = 0;

    tidA = rt_thread_create("timeslice", test_timeslice_threadA_entry, RT_NULL,
                           2048, UTEST_THR_PRIORITY + 1, 10);
    if (!tidA)
    {
        LOG_E("rt_thread_create failed!");
        return;
    }

    rt_thread_control(tidA, RT_THREAD_CTRL_BIND_CPU, (void *)1);
    ret_startup = rt_thread_startup(tidA);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        return ;
    }

    tidB1 = rt_thread_create("timeslice", test_timeslice_threadB1_entry, RT_NULL,
                           2048, UTEST_THR_PRIORITY + 2, 2);
    if (!tidB1)
    {
        LOG_E("rt_thread_create failed!");
        return;
    }

    rt_thread_control(tidB1, RT_THREAD_CTRL_BIND_CPU, (void *)1);
    ret_startup = rt_thread_startup(tidB1);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        return ;
    }

    tidB2 = rt_thread_create("timeslice", test_timeslice_threadB2_entry, RT_NULL,
                           2048, UTEST_THR_PRIORITY + 2, 2);
    if (!tidB2)
    {
        LOG_E("rt_thread_create failed!");
        return;
    }

    rt_thread_control(tidB2, RT_THREAD_CTRL_BIND_CPU, (void *)1);
    ret_startup = rt_thread_startup(tidB2);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        return ;
    }
    do{
        rt_thread_delay(2 * 20);
    }while(timeslice_cntA <= 10);

    rt_kprintf("A:%d,B1:%d,B2:%d\n", timeslice_cntA, timeslice_cntB1, timeslice_cntB2);
    diff = abs(timeslice_cntB1 - timeslice_cntB2);
    uassert_true(diff * 100 / timeslice_cntB1 < 30);
    uassert_true(timeslice_cntA == 11);
}

#ifndef RT_USING_SMP
static volatile rt_uint32_t yield_count;

static void test_thread_yield_inc_entry(void *parameter)
{
    rt_uint32_t loop = 0;

    while (1)
    {
        if (loop++ > 10001)
            break;
        yield_count++;
        rt_thread_yield();
    }
}

static void test_thread_yield_entry(void *parameter)
{
    rt_err_t ret_startup = -RT_ERROR;

    rt_thread_t tid;
    rt_uint32_t loop = 0;
    rt_uint32_t count_before;

    tid = rt_thread_create("inc", test_thread_yield_inc_entry, RT_NULL,
                           2048, 1, 10);
    if (!tid)
    {
        LOG_E("rt_thread_create failed!");
        return;
    }

    ret_startup = rt_thread_startup(tid);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        return ;
    }

    while (1)
    {
        if (loop++ > 10000)
            break;

        count_before = yield_count;
        rt_thread_yield();
        if (yield_count == count_before)
        {
            LOG_E("yield error!");
            return;
        }
    }
    thread_yield_flag = 1;
}

void test_thread_yield_nosmp(void)
{
    rt_err_t ret_startup = -RT_ERROR;

    rt_thread_t tid;

    yield_count = 0;

    tid = rt_thread_create("chkcnt", test_thread_yield_entry, RT_NULL,
                           2048, 1, 10);
    if (!tid)
    {
        LOG_E("rt_thread_create failed!");
        return;
    }

    ret_startup = rt_thread_startup(tid);
    if (ret_startup != RT_EOK)
    {
        LOG_E("rt_thread_startup failed!");
        uassert_false(1);
        return ;
    }

    uassert_true(thread_yield_flag == 1);
}

// static rt_uint32_t thread9_count = 0;
// static void thread9_entry(void *parameter)
// {
//     while (1)
//     {
//         thread9_count ++;
//     }

// }
// static void test_thread_suspend(void)
// {
//     static rt_thread_t tid;
//     rt_err_t ret_startup = -RT_ERROR;
//     uint32_t count_before_suspend, count_before_resume, count_after_resume;
//     tid = rt_thread_create("thread9",
//                            thread9_entry,
//                            RT_NULL,
//                            THREAD_STACK_SIZE,
//                            UTEST_THR_PRIORITY + 1,
//                            THREAD_TIMESLICE);
//     if (tid == RT_NULL)
//     {
//         LOG_E("rt_thread_create failed!");
//         uassert_false(tid4 == RT_NULL);
//         goto __exit;
//     }

//     ret_startup = rt_thread_startup(tid);
//     if (ret_startup != RT_EOK)
//     {
//         LOG_E("rt_thread_startup failed!");
//         uassert_false(1);
//         goto __exit;
//     }
//     rt_thread_delay(5);
//     rt_thread_suspend(tid);
//     count_before_suspend = thread9_count;
//     uassert_true(count_before_suspend != 0);
//     rt_thread_delay(5);
//     count_before_resume = thread9_count;
//     uassert_true(count_before_suspend == count_before_resume);
//     rt_thread_resume(tid);
//     rt_thread_delay(5);
//     count_after_resume = thread9_count;
//     uassert_true(count_after_resume != count_before_resume);

// __exit:
//     if (tid != RT_NULL)
//     {
//         rt_thread_delete(tid);
//     }
//     return;
// }
#endif

static rt_err_t utest_tc_init(void)
{
    __current_thread = rt_thread_self();
    change_priority = UTEST_THR_PRIORITY + 5;
    tid3_delay_pass_flag = 0;
    tid3_finish_flag = 0;
    tid4_finish_flag = 0;
    tid6_finish_flag = 0;
    entry_idle_hook_times = 0;
    count = 0;
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    /* init, detach */
    UTEST_UNIT_RUN(test_static_thread);
    /* create, delete */
    UTEST_UNIT_RUN(test_dynamic_thread);
    /* exit, duplicate delete */
#ifdef RT_USING_HEAP
    UTEST_UNIT_RUN(test_thread_exit_delete_again);
    UTEST_UNIT_RUN(test_thread_delete_again);
#if !defined(RT_USING_SMP) && !defined(RT_USING_SMART)
    UTEST_UNIT_RUN(test_thread_detach_again);
#endif
#if defined(RT_USING_SMP) && RT_CPUS_NR > 1
    UTEST_UNIT_RUN(test_thread_delete_race);
#endif
#endif
    /* delay */
    UTEST_UNIT_RUN(test_thread_delay);
    /* idle_sethook, idle_delhook */
    UTEST_UNIT_RUN(test_idle_hook);
    /* yield */
    UTEST_UNIT_RUN(test_thread_yield);
#ifndef RT_USING_SMP
    /* yield_nosmp */
    UTEST_UNIT_RUN(test_thread_yield_nosmp);
    /* suspend, resume */
    // UTEST_UNIT_RUN(test_thread_suspend);
#endif
    /* control */
    UTEST_UNIT_RUN(test_thread_control);
    UTEST_UNIT_RUN(test_thread_priority);
    /* delay_until */
    UTEST_UNIT_RUN(test_delay_until);
    /* timeslice */
    // UTEST_UNIT_RUN(test_timeslice); /* Can not running in Github Action QEMU */
}


UTEST_TC_EXPORT(testcase, "core.thread_tc", utest_tc_init, utest_tc_cleanup, 1000);

/********************* end of file ************************/
