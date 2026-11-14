/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-12     luckyzjq     the first version
 * 2025-11-17     Ze-Hou       add standardized utest documentation block
 */

/**
 * Test Case Name: Kernel Core Timer Test
 *
 * Test Objectives:
 * - Validate the RT-Thread kernel timer (rt_timer) functionality
 * - Test static and dynamic timer creation, initialization, start, stop, delete,
 *   detach, and control APIs
 * - Verify one-shot and periodic timer behaviors, including hard and soft timer modes
 *
 * Test Scenarios:
 * - Initialize and start static timers in one-shot and periodic modes, with various flag combinations
 * - Start a timer twice before it expires to verify restart behavior
 * - Use timer control APIs to set and get timer period, and verify correct timing
 * - Start and stop timers within their callback functions to test reentrancy and robustness
 * - Create, start, stop, and delete dynamic timers, verifying correct operation and resource management
 * - Perform stress testing by rapidly starting and stopping a large number of timers concurrently
 *
 * Verification Metrics:
 * - All uassert assertions pass without failure
 * - Timers are created, started, stopped, detached, and deleted successfully
 * - Timer callbacks are invoked at the expected tick count
 * - Timer restart and control operations behave as expected
 *
 * Dependencies:
 * - Enable Timer Test (RT-Thread Utestcases -> Kernel Core -> Timer Test)
 * - Test on any RT-Thread supported platform (e.g., qemu-virt64-riscv)
 *
 * Expected Results:
 * - After executing this test in msh, the expected output should be:
 *   "[  PASSED  ] [ result   ] testcase (core.timer)"
 */

#include <rtthread.h>
#include <rthw.h>
#include <stdlib.h>
#include "utest.h"

#undef uassert_true
#define uassert_true(value)                                 \
    do                                                      \
    {                                                       \
        if (!(value))                                       \
        {                                                   \
            __utest_assert(value, "(" #value ") is false"); \
        }                                                   \
    } while (0)

/* notify user that the test is not corrupted */
#define PRINT_PROGRESS(id) LOG_I("Testing on %d", id)

static rt_uint8_t timer_flag_oneshot[] = {
    RT_TIMER_FLAG_ONE_SHOT,
    RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_HARD_TIMER,
    RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER,
};

static rt_uint8_t timer_flag_periodic[] = {
    RT_TIMER_FLAG_PERIODIC,
    RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_HARD_TIMER,
    RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER,
};

typedef struct test_timer_struct
{
    struct rt_timer static_timer; /* static timer handler */
    rt_timer_t dynamic_timer;     /* dynamic timer pointer */
    rt_tick_t expect_tick;        /* expect tick */
    rt_ubase_t callbacks;         /* timer callback times */
    rt_bool_t is_static;          /* static or dynamic timer */
} timer_struct;
static timer_struct timer;

#ifdef RT_USING_SMP
static rt_ubase_t saved_bind_cpu;
static rt_bool_t stress_pending;
#ifdef RT_USING_TIMER_SOFT
static rt_thread_t soft_timer_thread;
static rt_ubase_t saved_timer_bind_cpu;
#endif

static rt_err_t timer_test_bind(void)
{
    rt_err_t result;

    /* CPU 0 runs hard timers. Keep teardown from overlapping their callbacks. */
    result = rt_thread_control(rt_thread_self(), RT_THREAD_CTRL_BIND_CPU, (void *)0);
    if (result != RT_EOK)
    {
        return result;
    }
#ifdef RT_USING_TIMER_SOFT
    result = rt_thread_control(soft_timer_thread, RT_THREAD_CTRL_BIND_CPU, (void *)0);
    if (result == RT_EOK)
    {
        rt_tick_t start = rt_tick_get();

        /* Binding a remote running thread requests migration asynchronously. */
        do
        {
            rt_sched_lock_level_t level;
            rt_uint8_t cpu;

            rt_sched_lock(&level);
            cpu = RT_SCHED_CTX(soft_timer_thread).oncpu;
            rt_sched_unlock(level);
            if (cpu == 0 || cpu == RT_CPU_DETACHED)
            {
                return RT_EOK;
            }
            rt_thread_delay(1);
        } while ((rt_tick_t)(rt_tick_get() - start) < RT_TICK_PER_SECOND);
        return -RT_ETIMEOUT;
    }
#endif
    return result;
}

static rt_err_t timer_test_restore(void)
{
    rt_err_t result = RT_EOK;
    rt_err_t self_result;
#ifdef RT_USING_TIMER_SOFT
    result = rt_thread_control(soft_timer_thread, RT_THREAD_CTRL_BIND_CPU,
                               (void *)saved_timer_bind_cpu);
#endif
    self_result = rt_thread_control(rt_thread_self(), RT_THREAD_CTRL_BIND_CPU,
                                    (void *)saved_bind_cpu);
    return result != RT_EOK ? result : self_result;
}
#endif /* RT_USING_SMP */

static rt_err_t timer_test_start(rt_timer_t target, rt_tick_t timeout)
{
    rt_base_t level;
    rt_err_t result;

    /* Sample the expected deadline and arm the timer in the same tick. */
    level = rt_hw_local_irq_disable();
    timer.expect_tick = rt_tick_get() + timeout;
    result = rt_timer_start(target);
    rt_hw_local_irq_enable(level);
    return result;
}

static void timer_oneshot(void *param)
{
    timer_struct *timer_call;
    timer_call = (timer_struct *)param;
    timer_call->callbacks++;

    uassert_true(rt_tick_get() == timer_call->expect_tick);
}

static void timer_periodic(void *param)
{
    rt_err_t result;
    timer_struct *timer_call;
    timer_call = (timer_struct *)param;
    timer_call->callbacks++;

    uassert_true(rt_tick_get() == timer_call->expect_tick);

    if (timer_call->is_static)
    {
        timer_call->expect_tick = rt_tick_get() + timer_call->static_timer.init_tick;
    }
    else
    {
        timer_call->expect_tick = rt_tick_get() + timer_call->dynamic_timer->init_tick;
    }

    if (timer_call->callbacks == 5)
    {
        /* periodic timer can stop */
        if (timer_call->is_static)
        {
            result = rt_timer_stop(&timer_call->static_timer);
        }
        else
        {
            result = rt_timer_stop(timer_call->dynamic_timer);
        }

        uassert_true(result == RT_EOK);
    }
}

static void test_static_timer(void)
{
    rt_err_t result;

    timer.callbacks = 0;
    timer.is_static = RT_TRUE;

    /* one shot timer test */
    for (int time_out = 1; time_out < 10; time_out++)
    {
        for (int i = 0; i < sizeof(timer_flag_oneshot); i++)
        {
            rt_timer_init(&timer.static_timer,
                          "static_timer",
                          timer_oneshot,
                          &timer,
                          time_out,
                          timer_flag_oneshot[i]);

            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(&timer.static_timer, time_out);
            uassert_true(result == RT_EOK);

            /* wait for timerout */
            rt_thread_delay(3 * time_out + 1);

            uassert_true(timer.callbacks == 1);

            /* detach timer */
            result = rt_timer_detach(&timer.static_timer);
            uassert_true(result == RT_EOK);
            timer.callbacks = 0;
        }
    }

    /* periodic timer test */
    for (int time_out = 1; time_out < 10; time_out++)
    {
        for (int i = 0; i < sizeof(timer_flag_periodic); i++)
        {
            rt_timer_init(&timer.static_timer,
                          "static_timer",
                          timer_periodic,
                          &timer,
                          time_out,
                          timer_flag_periodic[i]);

            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(&timer.static_timer, time_out);
            uassert_true(result == RT_EOK);

            /* wait for timerout */
            rt_thread_delay(5 * time_out + 1);

            uassert_true(timer.callbacks >= 5);

            /* detach timer */
            result = rt_timer_detach(&timer.static_timer);
            uassert_true(result == RT_EOK);
            timer.callbacks = 0;
        }
    }
}

static void test_static_timer_start_twice(void)
{
    rt_err_t result;

    timer.callbacks = 0;
    timer.is_static = RT_TRUE;

    /* timer start twice test */
    for (int time_out = 2; time_out < 10; time_out++)
    {
        for (int i = 0; i < sizeof(timer_flag_oneshot); i++)
        {
            rt_timer_init(&timer.static_timer,
                          "static_timer",
                          timer_oneshot,
                          &timer,
                          time_out,
                          timer_flag_oneshot[i]);

            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(&timer.static_timer, time_out);
            uassert_true(result == RT_EOK);

            rt_thread_delay(1);

            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(&timer.static_timer, time_out);
            uassert_true(result == RT_EOK);

            /* wait for timerout */
            rt_thread_delay(3 * time_out + 1);

            uassert_true(timer.callbacks == 1);

            /* detach timer */
            result = rt_timer_detach(&timer.static_timer);
            uassert_true(result == RT_EOK);
            timer.callbacks = 0;
        }
    }
}

static void timer_control(void *param)
{
    rt_err_t result;
    timer_struct *timer_call;
    timer_call = (timer_struct *)param;
    timer_call->callbacks++;

    uassert_true(rt_tick_get() == timer_call->expect_tick);

    /* periodic timer can stop */
    if (timer_call->is_static)
    {
        result = rt_timer_stop(&timer_call->static_timer);
    }
    else
    {
        result = rt_timer_stop(timer_call->dynamic_timer);
    }

    uassert_true(result == RT_EOK);
}

static void test_static_timer_control(void)
{
    rt_err_t result;
    rt_tick_t set_data;
    rt_tick_t get_data;

    timer.callbacks = 0;
    timer.is_static = RT_TRUE;

    rt_timer_init(&timer.static_timer,
                  "static_timer",
                  timer_control,
                  &timer,
                  5,
                  RT_TIMER_FLAG_PERIODIC);

    /* test set data */
    set_data = 10;
    result = rt_timer_control(&timer.static_timer, RT_TIMER_CTRL_SET_TIME, &set_data);

    uassert_true(result == RT_EOK);

    /* test get data */
    result = rt_timer_control(&timer.static_timer, RT_TIMER_CTRL_GET_TIME, &get_data);

    uassert_true(result == RT_EOK);
    uassert_true(set_data == get_data);

    /* Sample the expected deadline and start the timer. */
    result = timer_test_start(&timer.static_timer, set_data);
    uassert_true(result == RT_EOK);

    rt_thread_delay(3 * set_data + 1);

    /* detach timer */
    result = rt_timer_detach(&timer.static_timer);
    uassert_true(result == RT_EOK);
    uassert_true(timer.callbacks == 1);
}

static void timer_start_in_callback(void *param)
{
    rt_err_t result;
    timer_struct *timer_call;
    timer_call = (timer_struct *)param;
    timer_call->callbacks++;

    uassert_true(rt_tick_get() == timer_call->expect_tick);

    if (timer_call->is_static)
    {
        result = timer_test_start(&timer_call->static_timer, timer_call->static_timer.init_tick);
    }
    else
    {
        result = timer_test_start(timer_call->dynamic_timer, timer_call->dynamic_timer->init_tick);
    }

    uassert_true(result == RT_EOK);
}

static void timer_start_stop_in_callback(void *param)
{
    rt_err_t result;
    timer_struct *timer_call;
    timer_call = (timer_struct *)param;
    timer_call->callbacks++;

    uassert_true(rt_tick_get() == timer_call->expect_tick);

    if (timer_call->is_static)
    {
        result = rt_timer_start(&timer_call->static_timer);
    }
    else
    {
        result = rt_timer_start(timer_call->dynamic_timer);
    }

    uassert_true(result == RT_EOK);

    if (timer_call->is_static)
    {
        result = rt_timer_stop(&timer_call->static_timer);
    }
    else
    {
        result = rt_timer_stop(timer_call->dynamic_timer);
    }

    uassert_true(result == RT_EOK);
}

static void test_static_timer_op_in_callback(void)
{
    rt_err_t result;

    timer.callbacks = 0;
    timer.is_static = RT_TRUE;

    /* start in callback test */
    for (int time_out = 1; time_out < 10; time_out++)
    {
        for (int i = 0; i < sizeof(timer_flag_oneshot); i++)
        {
            rt_timer_init(&timer.static_timer,
                          "static_timer",
                          timer_start_in_callback,
                          &timer,
                          time_out,
                          timer_flag_oneshot[i]);

            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(&timer.static_timer, time_out);
            uassert_true(result == RT_EOK);

            /* wait for timerout */
            rt_thread_delay(5 * time_out + 1);

            uassert_true(timer.callbacks >= 5);

            /* detach timer */
            result = rt_timer_detach(&timer.static_timer);
            uassert_true(result == RT_EOK);

            timer.callbacks = 0;
        }
    }

    /* start & stop in callback test */
    for (int time_out = 1; time_out < 10; time_out++)
    {
        for (int i = 0; i < sizeof(timer_flag_periodic); i++)
        {
            rt_timer_init(&timer.static_timer,
                          "static_timer",
                          timer_start_stop_in_callback,
                          &timer,
                          time_out,
                          timer_flag_periodic[i]);

            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(&timer.static_timer, time_out);

            uassert_true(result == RT_EOK);

            /* wait for timerout */
            rt_thread_delay(3 * time_out + 1);

            uassert_true(timer.callbacks == 1);

            /* detach timer */
            result = rt_timer_detach(&timer.static_timer);

            uassert_true(result == RT_EOK);

            timer.callbacks = 0;
        }
    }
}

#ifdef RT_USING_HEAP

static void test_dynamic_timer(void)
{
    rt_err_t result;

    timer.callbacks = 0;
    timer.is_static = RT_FALSE;

    /* one shot timer test */
    for (int time_out = 1; time_out < 10; time_out++)
    {
        for (int i = 0; i < sizeof(timer_flag_oneshot); i++)
        {
            timer.dynamic_timer = rt_timer_create("dynamic_timer",
                                                  timer_oneshot,
                                                  &timer,
                                                  time_out,
                                                  timer_flag_oneshot[i]);

            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(timer.dynamic_timer, time_out);
            uassert_true(result == RT_EOK);

            /* wait for timerout */
            rt_thread_delay(3 * time_out + 1);
            uassert_true(timer.callbacks == 1);

            /* detach timer */
            result = rt_timer_delete(timer.dynamic_timer);
            uassert_true(result == RT_EOK);
            timer.callbacks = 0;
        }
    }

    /* periodic timer test */
    for (int time_out = 1; time_out < 10; time_out++)
    {
        for (int i = 0; i < sizeof(timer_flag_periodic); i++)
        {
            timer.dynamic_timer = rt_timer_create("dynamic_timer",
                                                  timer_periodic,
                                                  &timer,
                                                  time_out,
                                                  timer_flag_periodic[i]);

            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(timer.dynamic_timer, time_out);
            uassert_true(result == RT_EOK);

            /* wait for timerout */
            rt_thread_delay(5 * time_out + 1);
            uassert_true(timer.callbacks >= 5);

            /* detach timer */
            result = rt_timer_delete(timer.dynamic_timer);
            uassert_true(result == RT_EOK);
            timer.callbacks = 0;
        }
    }
}

static void test_dynamic_timer_control(void)
{
    rt_err_t result;
    rt_tick_t set_data;
    rt_tick_t get_data;

    timer.callbacks = 0;
    timer.is_static = RT_FALSE;

    timer.dynamic_timer = rt_timer_create("dynamic_timer",
                                          timer_control,
                                          &timer,
                                          5,
                                          RT_TIMER_FLAG_PERIODIC);

    /* test set data */
    set_data = 10;
    result = rt_timer_control(timer.dynamic_timer, RT_TIMER_CTRL_SET_TIME, &set_data);
    uassert_true(result == RT_EOK);

    /* test get data */
    result = rt_timer_control(timer.dynamic_timer, RT_TIMER_CTRL_GET_TIME, &get_data);

    uassert_true(result == RT_EOK);
    uassert_true(set_data == get_data);

    /* Sample the expected deadline and start the timer. */
    result = timer_test_start(timer.dynamic_timer, set_data);
    uassert_true(result == RT_EOK);

    rt_thread_delay(3 * set_data + 1);

    /* detach timer */
    result = rt_timer_delete(timer.dynamic_timer);
    uassert_true(result == RT_EOK);
    uassert_true(timer.callbacks == 1);
}

static void test_dynamic_timer_start_twice(void)
{
    rt_err_t result;

    timer.callbacks = 0;
    timer.is_static = RT_FALSE;

    /* timer start twice test */
    for (int time_out = 2; time_out < 10; time_out++)
    {
        for (int i = 0; i < sizeof(timer_flag_oneshot); i++)
        {
            timer.dynamic_timer = rt_timer_create("dynamic_timer",
                                                  timer_oneshot,
                                                  &timer,
                                                  time_out,
                                                  timer_flag_oneshot[i]);
            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(timer.dynamic_timer, time_out);
            uassert_true(result == RT_EOK);

            rt_thread_delay(1);

            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(timer.dynamic_timer, time_out);
            uassert_true(result == RT_EOK);

            /* wait for timerout */
            rt_thread_delay(3 * time_out + 1);

            uassert_true(timer.callbacks == 1);

            /* detach timer */
            result = rt_timer_delete(timer.dynamic_timer);
            uassert_true(result == RT_EOK);
            timer.callbacks = 0;
        }
    }
}

static void test_dynamic_timer_op_in_callback(void)
{
    rt_err_t result;

    timer.callbacks = 0;
    timer.is_static = RT_FALSE;

    /* start in callback test */
    for (int time_out = 1; time_out < 10; time_out++)
    {
        for (int i = 0; i < sizeof(timer_flag_oneshot); i++)
        {
            timer.dynamic_timer = rt_timer_create("dynamic_timer",
                                                  timer_start_in_callback,
                                                  &timer,
                                                  time_out,
                                                  timer_flag_oneshot[i]);

            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(timer.dynamic_timer, time_out);
            uassert_true(result == RT_EOK);

            /* wait for timerout */
            rt_thread_delay(5 * time_out + 1);

            uassert_true(timer.callbacks >= 5);

            /* detach timer */
            result = rt_timer_delete(timer.dynamic_timer);
            uassert_true(result == RT_EOK);

            timer.callbacks = 0;
        }
    }

    /* start & stop in callback test */
    for (int time_out = 1; time_out < 10; time_out++)
    {
        for (int i = 0; i < sizeof(timer_flag_periodic); i++)
        {
            timer.dynamic_timer = rt_timer_create("dynamic_timer",
                                                  timer_start_stop_in_callback,
                                                  &timer,
                                                  time_out,
                                                  timer_flag_periodic[i]);
            /* Sample the expected deadline and start the timer. */
            result = timer_test_start(timer.dynamic_timer, time_out);

            uassert_true(result == RT_EOK);

            /* wait for timerout */
            rt_thread_delay(3 * time_out + 1);

            uassert_true(timer.callbacks == 1);

            /* detach timer */
            result = rt_timer_delete(timer.dynamic_timer);

            uassert_true(result == RT_EOK);

            timer.callbacks = 0;
        }
    }
}
#endif /* RT_USING_HEAP */

#define TEST_TIME_S   60 // test 60 seconds
#define STRESS_TIMERS 100

static struct rt_timer stress_timer[STRESS_TIMERS];

static void timer_stress(void *param)
{
    rt_timer_t stress_timer = (rt_timer_t)param;

    if (rand() % 2 == 0)
    {
        rt_timer_start(stress_timer);
    }
    else
    {
        rt_timer_stop(stress_timer);
    }
}

static void test_timer_stress(void)
{
    rt_tick_t start;
    rt_ubase_t iters = 0;
    rt_ubase_t cur_tick;
    rt_ubase_t next_print_time;

    LOG_I("timer stress test begin, it will take %d seconds", 3 * TEST_TIME_S);

    for (int i = 0; i < sizeof(timer_flag_periodic); i++)
    {
        for (int j = 0; j < STRESS_TIMERS; j++)
        {
            rt_timer_init(&stress_timer[j],
                          "stress_timer",
                          timer_stress,
                          &stress_timer[j],
                          j + 1,
                          timer_flag_periodic[i]);
        }

        start = rt_tick_get();
        cur_tick = rt_tick_get();
        next_print_time = cur_tick + RT_TICK_PER_SECOND;
#ifdef RT_USING_SMP
        /* Keep the stress workload concurrent; serialize only its lifetime. */
        stress_pending = RT_TRUE;
        uassert_true(timer_test_restore() == RT_EOK);
#endif
        while (cur_tick - start <= TEST_TIME_S * RT_TICK_PER_SECOND)
        {
            for (int j = 0; j < STRESS_TIMERS; j++)
            {
                if (rand() % 2 == 0)
                {
                    rt_timer_start(&stress_timer[j]);
                }
                else
                {
                    rt_timer_stop(&stress_timer[j]);
                }
            }
            iters++;
            cur_tick = rt_tick_get();
            if (cur_tick > next_print_time)
            {
                PRINT_PROGRESS(next_print_time);
                next_print_time = cur_tick + RT_TICK_PER_SECOND;
            }
        }

#ifdef RT_USING_SMP
        if (timer_test_bind() != RT_EOK)
        {
            uassert_true(RT_FALSE);
            return;
        }
#endif
        for (int j = 0; j < STRESS_TIMERS; j++)
        {
            rt_timer_detach(&stress_timer[j]);
        }
#ifdef RT_USING_SMP
        stress_pending = RT_FALSE;
#endif
    }

    LOG_I("success after %lu iterations", iters);
}

static rt_err_t utest_tc_init(void)
{
#ifdef RT_USING_SMP
    /* A failed migration must not allow reuse of timers still in flight. */
    if (stress_pending)
    {
        return -RT_ERROR;
    }
#endif
    timer.dynamic_timer = RT_NULL;
    timer.callbacks = 0;

#ifdef RT_USING_SMP
    rt_thread_t self = rt_thread_self();
    rt_sched_lock_level_t level;
    rt_err_t result;

#ifdef RT_USING_TIMER_SOFT
    soft_timer_thread = rt_thread_find("timer");
    if (soft_timer_thread == RT_NULL)
    {
        return -RT_ERROR;
    }
#endif
    rt_sched_lock(&level);
    saved_bind_cpu = RT_SCHED_CTX(self).bind_cpu;
#ifdef RT_USING_TIMER_SOFT
    saved_timer_bind_cpu = RT_SCHED_CTX(soft_timer_thread).bind_cpu;
    /* A soft callback must return before the controller can reuse its timer. */
    if (RT_SCHED_PRIV(soft_timer_thread).current_priority >= RT_SCHED_PRIV(self).current_priority)
    {
        rt_sched_unlock(level);
        return -RT_EINVAL;
    }
#endif
    rt_sched_unlock(level);
    result = timer_test_bind();
    if (result != RT_EOK)
    {
        timer_test_restore();
    }
    return result;
#else
    return RT_EOK;
#endif
}

static rt_err_t utest_tc_cleanup(void)
{
    timer.dynamic_timer = RT_NULL;
    timer.callbacks = 0;

#ifdef RT_USING_SMP
    return timer_test_restore();
#else
    return RT_EOK;
#endif
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_static_timer);
    PRINT_PROGRESS(__LINE__);
    UTEST_UNIT_RUN(test_static_timer_control);
    PRINT_PROGRESS(__LINE__);
    UTEST_UNIT_RUN(test_static_timer_start_twice);
    PRINT_PROGRESS(__LINE__);
    UTEST_UNIT_RUN(test_static_timer_op_in_callback);
    PRINT_PROGRESS(__LINE__);
#ifdef RT_USING_HEAP
    UTEST_UNIT_RUN(test_dynamic_timer);
    PRINT_PROGRESS(__LINE__);
    UTEST_UNIT_RUN(test_dynamic_timer_control);
    PRINT_PROGRESS(__LINE__);
    UTEST_UNIT_RUN(test_dynamic_timer_start_twice);
    PRINT_PROGRESS(__LINE__);
    UTEST_UNIT_RUN(test_dynamic_timer_op_in_callback);
    PRINT_PROGRESS(__LINE__);
#endif /* RT_USING_HEAP */
    UTEST_UNIT_RUN(test_timer_stress);
    PRINT_PROGRESS(__LINE__);
}
UTEST_TC_EXPORT(testcase, "core.timer", utest_tc_init, utest_tc_cleanup, 1000);

/*********************** end of file ****************************/
