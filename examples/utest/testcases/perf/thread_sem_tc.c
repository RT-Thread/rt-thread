/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-03     rcitach      test case for semaphore
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <utest.h>
#include <utest_assert.h>

#define PERF_COUNT 1000
#define TIME_OUT_TIME 10
#define OUTTIME_TICK (RT_TICK_PER_SECOND * TIME_OUT_TIME)
static rt_sem_t perf_thread_sem = RT_NULL;
static rt_event_t perf_thread_event = RT_NULL;
volatile static uint16_t thread_event_count = 0;

#define EVENT_FLAG          (1 << 0)

#define THREAD_STACK_SIZE       1024
#define THREAD_PRIORITY         10
#define THREAD_TIMESLICE        5

struct perf_time
{
    rt_uint32_t start_time;
    rt_uint32_t end_time;
    rt_uint32_t use_time;
};
static struct perf_time use_time[PERF_COUNT];

#ifdef USING_HWTIME_AS_TIME_REF
static rt_device_t hw_dev = RT_NULL;
static rt_hwtimerval_t timer_val;

static rt_uint32_t get_timer_us(void)
{
    if (hw_dev && rt_device_read(hw_dev, 0, &timer_val, sizeof(rt_hwtimerval_t)))
    {
        return (rt_uint32_t)(timer_val.sec * 1000000 + timer_val.usec);
    }
    return 0;
}
#endif

static void perf_thread_sem1(void *parameter)
{
    rt_uint32_t total_time = 0;
    rt_err_t ret;
    rt_event_send(perf_thread_event, EVENT_FLAG);
    while (1)
    {
        ret = rt_sem_take(perf_thread_sem, RT_WAITING_FOREVER);
#ifdef USING_HWTIME_AS_TIME_REF
        use_time[thread_event_count].end_time = get_timer_us();
        use_time[thread_event_count].use_time = use_time[thread_event_count].end_time - use_time[thread_event_count].start_time;
#else
        use_time[thread_event_count].end_time = rt_tick_get();
        use_time[thread_event_count].use_time = (use_time[thread_event_count].end_time - use_time[thread_event_count].start_time) / RT_TICK_PER_SECOND;
        use_time[thread_event_count].use_time += ((use_time[thread_event_count].end_time - use_time[thread_event_count].start_time) % RT_TICK_PER_SECOND) * (1000000u / RT_TICK_PER_SECOND);
#endif
        if(ret != RT_EOK)
        {
            LOG_E("Sem recv error!");
            rt_sem_delete(perf_thread_sem);
            return;
        }
        total_time += use_time[thread_event_count].use_time;
        thread_event_count ++;
        if (thread_event_count >= PERF_COUNT)
        {
            LOG_I("Semaphore test completed: %d iterations, total time = %lu us, average = %lu us per semaphore",
                PERF_COUNT, total_time, total_time / PERF_COUNT);

            rt_event_delete(perf_thread_event);
            rt_sem_delete(perf_thread_sem);
            return;
        }
        rt_event_send(perf_thread_event, EVENT_FLAG);
    }
}

static void perf_thread_sem2(void *parameter)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t recv = 0;
    while (1)
    {
        if (thread_event_count >= PERF_COUNT)
        {
            return;
        }
        ret = rt_event_recv(perf_thread_event, EVENT_FLAG,
                (RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR),
                RT_WAITING_FOREVER, &recv);
        if(ret == -RT_ETIMEOUT)
        {
            LOG_W("Timeout when waiting for event");
            rt_event_delete(perf_thread_event);
            return;
        }
#ifdef USING_HWTIME_AS_TIME_REF
        use_time[thread_event_count].start_time = get_timer_us();
#else
        use_time[thread_event_count].start_time = rt_tick_get();
#endif
        rt_sem_release(perf_thread_sem);
    }
}

static void rt_perf_thread_sem(void)
{
    rt_thread_t thread1 = RT_NULL;
    rt_thread_t thread2 = RT_NULL;

    perf_thread_sem = rt_sem_create("perf_thread_sem", 0, RT_IPC_FLAG_FIFO);
    if (perf_thread_sem == RT_NULL)
    {
        LOG_E("perf_thread_sem create failed.");
        return;
    }
    perf_thread_event = rt_event_create("perf_thread_event", RT_IPC_FLAG_PRIO);
    thread1 = rt_thread_create("perf_thread_sem1", perf_thread_sem1, RT_NULL,
                                THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (thread1 == RT_NULL)
    {
        LOG_E("perf_thread_sem1 create failed.");
        return;
    }

    thread2 = rt_thread_create("perf_thread_sem2", perf_thread_sem2, RT_NULL,
                                THREAD_STACK_SIZE, THREAD_PRIORITY + 1, THREAD_TIMESLICE);
    if (thread2 == RT_NULL)
    {
        LOG_E("perf_thread_sem2 create failed.");
        return;
    }

    rt_thread_startup(thread1);
    rt_thread_startup(thread2);
}

static rt_err_t utest_tc_init(void)
{
#ifdef USING_HWTIME_AS_TIME_REF
    rt_hwtimerval_t timeout_s;
    int ret = RT_EOK;
    hw_dev = rt_device_find(UTEST_HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        ret = RT_ERROR;
        LOG_E("hwtimer sample run failed! can't find %s device!", UTEST_HWTIMER_DEV_NAME);
        return ret;
    }

    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        LOG_E("open %s device failed!", UTEST_HWTIMER_DEV_NAME);
        return ret;
    }

    timeout_s.sec  = TIME_OUT_TIME;      /* s  */
    timeout_s.usec = 0;     /* us */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(rt_hwtimerval_t)) != sizeof(rt_hwtimerval_t))
    {
        ret = RT_ERROR;
        LOG_E("set timeout value failed");
        return ret;
    }
#endif

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
#ifdef USING_HWTIME_AS_TIME_REF
    if (hw_dev) rt_device_close(hw_dev);
#endif
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(rt_perf_thread_sem);
}

UTEST_TC_EXPORT(testcase, "testcase.pref.semaphore", utest_tc_init, utest_tc_cleanup, 10);
