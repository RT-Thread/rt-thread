/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-12     luckyzjq     the first version
 */

#include <rtthread.h>
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

            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(&timer.static_timer);
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

            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(&timer.static_timer);
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

            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(&timer.static_timer);
            uassert_true(result == RT_EOK);

            rt_thread_delay(1);

            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(&timer.static_timer);
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
    int set_data;
    int get_data;

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

    /* calc expect tick */
    timer.expect_tick = rt_tick_get() + set_data;

    /* start timer */
    result = rt_timer_start(&timer.static_timer);
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
        timer_call->expect_tick = rt_tick_get() + timer_call->static_timer.init_tick;
        result = rt_timer_start(&timer_call->static_timer);
    }
    else
    {
        timer_call->expect_tick = rt_tick_get() + timer_call->dynamic_timer->init_tick;
        result = rt_timer_start(timer_call->dynamic_timer);
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

            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(&timer.static_timer);
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

            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(&timer.static_timer);

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

            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(timer.dynamic_timer);
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

            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(timer.dynamic_timer);
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
    int set_data;
    int get_data;

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

    /* calc expect tick */
    timer.expect_tick = rt_tick_get() + set_data;

    /* start timer */
    result = rt_timer_start(timer.dynamic_timer);
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
            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(timer.dynamic_timer);
            uassert_true(result == RT_EOK);

            rt_thread_delay(1);

            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(timer.dynamic_timer);
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

            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(timer.dynamic_timer);
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
            /* calc expect tick */
            timer.expect_tick = rt_tick_get() + time_out;

            /* start timer */
            result = rt_timer_start(timer.dynamic_timer);

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

#define TEST_TIME_S 60      // test 60 seconds
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

    LOG_I("timer stress test begin, it will take %d seconds", 3*TEST_TIME_S);

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
            iters ++;
            cur_tick = rt_tick_get();
            if (cur_tick > next_print_time)
            {
                PRINT_PROGRESS(next_print_time);
                next_print_time = cur_tick + RT_TICK_PER_SECOND;
            }
        }

        for (int j = 0; j < STRESS_TIMERS; j++)
        {
            rt_timer_detach(&stress_timer[j]);
        }
    }

    LOG_I("success after %lu iterations", iters);
}

static rt_err_t utest_tc_init(void)
{
    timer.dynamic_timer = RT_NULL;
    timer.callbacks = 0;

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    timer.dynamic_timer = RT_NULL;
    timer.callbacks = 0;

    return RT_EOK;
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
UTEST_TC_EXPORT(testcase, "testcases.kernel.timer_tc", utest_tc_init, utest_tc_cleanup, 1000);

/*********************** end of file ****************************/
