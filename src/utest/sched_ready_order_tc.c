/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-20     Yunlk        the first version
 */

/**
 * Test Case Name: Ready List Insertion Order Test (core.scheduler_ready_order)
 *
 * Test Objectives:
 * - Verify that same-priority threads are inserted into the ready list in a
 *   first-in-first-out manner, so that the execution order matches the order in
 *   which they became ready.
 * - Cover the two paths that currently bypass the FIFO order:
 * - Threads resumed from an IPC (semaphore) pending list.
 * - Threads started back-to-back via rt_thread_startup().
 * - List specific functions or APIs to be tested:
 * - rt_sem_create / rt_sem_take / rt_sem_release
 * - rt_thread_create / rt_thread_startup
 * - rt_schedule_insert_thread (indirectly, through the two paths above)
 *
 * Test Scenarios:
 * - **Semaphore Wakeup Order:**
 * 1. Create a semaphore with RT_IPC_FLAG_PRIO and two same-priority worker threads.
 * 2. Start the worker A first and let it block on the semaphore, then start B and
 * let it block as well. The pending list is therefore deterministically A -> B.
 * 3. Release the semaphore twice, which wakes A first and then B.
 * 4. Let the workers run and record their execution order.
 *
 * - **Startup Order:**
 * 1. Create two same-priority worker threads C and D.
 * 2. Startup C and then D without yielding in between.
 * 3. Let them run and record their execution order.
 *
 * Verification Metrics:
 * - **Pass:** The semaphore case records "AB", i.e. the thread woken first runs first.
 * - **Pass:** The startup case records "CD", i.e. the thread started first runs first.
 * - On SMP the workers are bound to the CPU running this test case, so that the
 * insertion order is observable without cross-core scheduling noise.
 *
 * Dependencies:
 * - Hardware requirements
 * - None. A single core is enough; more cores are also supported by binding.
 * (This is met by the qemu-vexpress-a9 / qemu-virt64-riscv BSP).
 * - Software configuration
 * - `RT_USING_UTEST` must be enabled (`RT-Thread Utestcases`).
 * - `Scheduler Test` must be enabled (`RT-Thread Utestcases` -> `Kernel Core` -> 'Scheduler Test').
 * - `RT_USING_SEMAPHORE` must be enabled.
 * - Environmental assumptions
 * - `RT_THREAD_PRIORITY_MAX` must leave at least one priority level between the
 * utest thread and the idle thread.
 * - Run the test case from the msh prompt:
 * `utest_run core.scheduler_ready_order`
 *
 * Expected Results:
 * - The console prints the observed execution order for both scenarios.
 * - Final Output: `[ PASSED ] [ result ] testcase (core.scheduler_ready_order)`
 */

#define __RT_IPC_SOURCE__

#include <rtthread.h>
#include "rthw.h"
#include "utest.h"

/*
 * The worker priority is derived from the thread that actually runs the testcase,
 * not from UTEST_THR_PRIORITY. utest can be started either on its own thread or
 * directly from the caller's context (`utest_run -thread` versus plain
 * `utest_run`), and UTEST_THR_PRIORITY may be reconfigured per BSP; reading the
 * running thread keeps the "lower priority than the test body" precondition true
 * in both cases.
 */
#define TEST_THREAD_PRIORITY_OFFSET 2

static rt_uint8_t _test_thread_priority(void)
{
    rt_uint8_t priority = (rt_uint8_t)(RT_SCHED_PRIV(rt_thread_self()).current_priority +
                                       TEST_THREAD_PRIORITY_OFFSET);

    /* stay above idle, and leave room for the ready list ordering to matter */
    if (priority >= RT_THREAD_PRIORITY_MAX - 1)
    {
        priority = RT_THREAD_PRIORITY_MAX - 2;
    }

    return priority;
}

#define TEST_ORDER_MAX 8

static rt_sem_t _order_sem;
static char _run_order[TEST_ORDER_MAX];
static rt_size_t _run_count;

/*
 * utest_unit_run() resets local_utest.failed_num at the start of every unit and
 * the testcase is reported as PASSED based on the value left by the last one, so
 * a failure in an earlier unit would be masked by a later passing unit. Collect
 * the per-unit verdicts here and assert them together at the very end.
 */
static rt_bool_t _sem_order_ok;
static rt_bool_t _startup_order_ok;
static rt_bool_t _same_priority_ok;
static rt_bool_t _reset_priority_ok;

static void _order_reset(void)
{
    rt_size_t i;

    for (i = 0; i < TEST_ORDER_MAX; i++)
    {
        _run_order[i] = '\0';
    }
    _run_count = 0;
}

/* the workers run one at a time on the same core, but keep it interrupt-safe */
static void _order_record(char c)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    if (_run_count < TEST_ORDER_MAX - 1)
    {
        _run_order[_run_count++] = c;
    }
    rt_hw_interrupt_enable(level);
}

static void _start_worker(rt_thread_t thread)
{
#ifdef RT_USING_SMP
    /* keep the worker on this core, otherwise it may be picked up by an idle
     * core immediately and the insertion order cannot be observed at all */
    rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU,
                      (void *)(rt_ubase_t)rt_hw_cpu_id());
#endif /* RT_USING_SMP */

    rt_thread_startup(thread);
}

static void _worker_wait_sem(void *parameter)
{
    rt_sem_take(_order_sem, RT_WAITING_FOREVER);
    _order_record((char)(rt_ubase_t)parameter);
}

static void _worker_run(void *parameter)
{
    _order_record((char)(rt_ubase_t)parameter);
}

/* ------------------------------------------------------------------ */

static void _sem_wakeup_order(void)
{
    rt_thread_t worker_a;
    rt_thread_t worker_b;

    _order_reset();

    _order_sem = rt_sem_create("order", 0, RT_IPC_FLAG_PRIO);
    uassert_not_null(_order_sem);

    worker_a = rt_thread_create("owA", _worker_wait_sem, (void *)'A',
                                UTEST_THR_STACK_SIZE, _test_thread_priority(), 5);
    worker_b = rt_thread_create("owB", _worker_wait_sem, (void *)'B',
                                UTEST_THR_STACK_SIZE, _test_thread_priority(), 5);
    uassert_not_null(worker_a);
    uassert_not_null(worker_b);

    /* start A and let it block first, then B: pending list is A -> B */
    _start_worker(worker_a);
    rt_thread_mdelay(50);
    _start_worker(worker_b);
    rt_thread_mdelay(50);

    /* wake them in pending order, A first and B second */
    rt_sem_release(_order_sem);
    rt_sem_release(_order_sem);

    /* let the ready threads run */
    rt_thread_mdelay(100);

    LOG_I("semaphore wakeup order: \"%s\", expect \"AB\"", _run_order);
    _sem_order_ok = (rt_strcmp(_run_order, "AB") == 0);
    uassert_true(_sem_order_ok);

    rt_sem_delete(_order_sem);
    _order_sem = RT_NULL;
}

static void _startup_order(void)
{
    rt_thread_t worker_c;
    rt_thread_t worker_d;

    _order_reset();

    worker_c = rt_thread_create("owC", _worker_run, (void *)'C',
                                UTEST_THR_STACK_SIZE, _test_thread_priority(), 5);
    worker_d = rt_thread_create("owD", _worker_run, (void *)'D',
                                UTEST_THR_STACK_SIZE, _test_thread_priority(), 5);
    uassert_not_null(worker_c);
    uassert_not_null(worker_d);

    /* startup C then D without yielding in between */
    _start_worker(worker_c);
    _start_worker(worker_d);

    rt_thread_mdelay(100);

    LOG_I("startup order: \"%s\", expect \"CD\"", _run_order);
    _startup_order_ok = (rt_strcmp(_run_order, "CD") == 0);
    uassert_true(_startup_order_ok);
}

/*
 * Re-applying the priority a ready thread already has must not move it. Both
 * workers stay READY (they are below the test thread and nothing yields before
 * the check), and the update goes through the same remove + insert path that
 * used to append the thread to the tail of its own ready queue.
 */
static void _same_priority_update_keeps_position(void)
{
    rt_thread_t worker_a;
    rt_thread_t worker_b;
    rt_uint8_t priority = _test_thread_priority();

    _order_reset();

    worker_a = rt_thread_create("owA", _worker_run, (void *)'A',
                                UTEST_THR_STACK_SIZE, priority, 5);
    worker_b = rt_thread_create("owB", _worker_run, (void *)'B',
                                UTEST_THR_STACK_SIZE, priority, 5);
    uassert_not_null(worker_a);
    uassert_not_null(worker_b);

    /* queue A then B without yielding, so the ready order is A -> B */
    _start_worker(worker_a);
    _start_worker(worker_b);

    /* ask A to take the priority it already has */
    uassert_int_equal(rt_thread_control(worker_a, RT_THREAD_CTRL_CHANGE_PRIORITY,
                                        &priority), RT_EOK);

    rt_thread_mdelay(100);

    LOG_I("order after a same-priority update: \"%s\", expect \"AB\"", _run_order);
    _same_priority_ok = (rt_strcmp(_run_order, "AB") == 0);
    uassert_true(_same_priority_ok);
}

/*
 * A same-value update still has to refresh init_priority when it comes from
 * RT_THREAD_CTRL_RESET_PRIORITY: that is the only caller that asks for it, and
 * it is legal to reset a thread to the priority it currently runs at.
 */
static void _reset_priority_updates_init(void)
{
    rt_thread_t worker;
    rt_uint8_t base = _test_thread_priority() - 1;
    rt_uint8_t moved = _test_thread_priority();

    worker = rt_thread_create("owR", _worker_run, (void *)'R',
                              UTEST_THR_STACK_SIZE, base, 5);
    uassert_not_null(worker);
    if (worker == RT_NULL)
    {
        return;
    }

    /* base -> moved: current == moved, init still base */
    uassert_int_equal(rt_thread_control(worker, RT_THREAD_CTRL_CHANGE_PRIORITY,
                                        &moved), RT_EOK);
    uassert_int_equal(RT_SCHED_PRIV(worker).current_priority, moved);
    uassert_int_equal(RT_SCHED_PRIV(worker).init_priority, base);

    /* reset to the priority it already runs at: init has to follow */
    uassert_int_equal(rt_thread_control(worker, RT_THREAD_CTRL_RESET_PRIORITY,
                                        &moved), RT_EOK);
    uassert_int_equal(RT_SCHED_PRIV(worker).current_priority, moved);
    uassert_int_equal(RT_SCHED_PRIV(worker).init_priority, moved);

    _reset_priority_ok = (RT_SCHED_PRIV(worker).init_priority == moved) &&
                         (RT_SCHED_PRIV(worker).current_priority == moved);
}

/*
 * Final verdict, asserted from the last unit so that the value
 * utest_unit_run() leaves in local_utest.failed_num is the one that reflects the
 * whole testcase. Without this a failing _sem_wakeup_order() followed by a
 * passing _startup_order() would be reported as PASSED.
 */
static void _order_summary(void)
{
    LOG_I("semaphore order: %s, startup order: %s",
          _sem_order_ok ? "ok" : "FAILED",
          _startup_order_ok ? "ok" : "FAILED");

    uassert_true(_sem_order_ok);
    uassert_true(_startup_order_ok);
    uassert_true(_same_priority_ok);
    uassert_true(_reset_priority_ok);
}

static rt_err_t utest_tc_init(void)
{
    _order_sem = RT_NULL;
    _order_reset();
    _sem_order_ok = RT_TRUE;
    _startup_order_ok = RT_TRUE;
    _same_priority_ok = RT_TRUE;
    _reset_priority_ok = RT_TRUE;

#ifdef RT_USING_SMP
    /*
     * Pin the thread that runs the testcase as well. The workers are bound to
     * rt_hw_cpu_id() when they are started, so the test body has to stay on the
     * same core throughout; otherwise it can migrate between prepare and check
     * and the workers would be pinned to a core the test body no longer runs on.
     */
    rt_thread_control(rt_thread_self(), RT_THREAD_CTRL_BIND_CPU,
                      (void *)(rt_ubase_t)rt_hw_cpu_id());
#endif /* RT_USING_SMP */

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(_sem_wakeup_order);
    UTEST_UNIT_RUN(_startup_order);
    UTEST_UNIT_RUN(_same_priority_update_keeps_position);
    UTEST_UNIT_RUN(_reset_priority_updates_init);
    UTEST_UNIT_RUN(_order_summary);
}
UTEST_TC_EXPORT(testcase, "core.scheduler_ready_order", utest_tc_init, utest_tc_cleanup, 10);
