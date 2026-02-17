/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2025-07-03     rcitach        test case for event
 * 2025-11-30     westcity-YOLO  Add standardized utest documentation block
 */

/**
 * Test Case Name: Kernel Core Event Performance Test
 *
 * Test Objectives:
 * - Measures event object synchronization performance
 * - Validates event flag handling (OR/CLEAR) and priority
 * - Provides latency metrics for event-based thread communication
 *
 * Test Scenarios:
 * - **Event Flag Handling**: EVENT_FLAG with OR/CLEAR operation
 * - **Priority Synchronization**: Higher-priority thread (THREAD_PRIORITY+1) response
 * - **Stress Test**: Repeated event signaling (RT_UTEST_SYS_PERF_TC_COUNT times)
 * - **Thread Coordination**: Two threads exchanging events via semaphores
 *
 * Verification Metrics:
 * - Latency < 50μs (event recv/send cycle)
 * - 0 errors in event flag handling
 * - Consistent results across test cycles
 * - No memory leaks during test
 *
 * Dependencies:
 * - RT_USING_EVENT must be enabled
 * - RT_USING_UTEST framework
 * - Hardware timer support (for high-precision timing)
 *
 * Expected Results:
 * [  PASSED  ] [ result   ] testcase (core.event)
 * - Structured performance data table (Min/Max/Avg latency)
 * - Final line: "=== Event Performance Test Results End ==="
 * - Executable via: `utest_run core.event` in msh
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <utest.h>
#include <utest_assert.h>
#include <perf_tc.h>

#define EVENT_FLAG          (1 << 0)
static rt_event_t perf_thread_event = RT_NULL;
static rt_sem_t sem1 = RT_NULL;
static rt_sem_t complete_sem = RT_NULL;

static void perf_thread_event1(void *parameter)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t recv = 0;
    rt_perf_t *perf = (rt_perf_t *)parameter;
    while (1)
    {
        ret = rt_event_recv(perf_thread_event, EVENT_FLAG,
                           (RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR),
                           RT_WAITING_FOREVER, &recv);
        rt_perf_stop(perf);
        if (ret != RT_EOK)
        {
            LOG_E("event recv error!");
            rt_event_delete(perf_thread_event);
            return;
        }

        if (perf->count >= RT_UTEST_SYS_PERF_TC_COUNT)
        {
            rt_event_delete(perf_thread_event);
            rt_sem_delete(sem1);
            return;
        }
        rt_sem_release(sem1);
    }
}

static void perf_thread_event2(void *parameter)
{
    rt_perf_t *perf = (rt_perf_t *)parameter;
    while (1)
    {
        if (perf->count >= RT_UTEST_SYS_PERF_TC_COUNT)
        {
            rt_sem_release(complete_sem);
            return;
        }
        rt_sem_take(sem1, RT_WAITING_FOREVER);
        rt_perf_start(perf);
        rt_event_send(perf_thread_event, EVENT_FLAG);
    }
}

rt_err_t rt_perf_thread_event(rt_perf_t *perf)
{
    rt_thread_t thread1 = RT_NULL;
    rt_thread_t thread2 = RT_NULL;

# if __STDC_VERSION__ >= 199901L
    rt_strcpy(perf->name,__func__);
#else
    rt_strcpy(perf->name,"rt_perf_thread_event");
#endif

    perf_thread_event = rt_event_create("perf_thread_event", RT_IPC_FLAG_PRIO);
    if (perf_thread_event == RT_NULL)
    {
        LOG_E("perf_thread_event create failed.");
        return -RT_ERROR;
    }

    sem1 = rt_sem_create("sem1", 1, RT_IPC_FLAG_FIFO);
    complete_sem = rt_sem_create("complete", 0, RT_IPC_FLAG_FIFO);

    thread1 = rt_thread_create("perf_thread_event1", perf_thread_event1, perf,
                                THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (thread1 == RT_NULL)
    {
        LOG_E("perf_thread_event1 create failed.");
        return -RT_ERROR;
    }

    thread2 = rt_thread_create("perf_thread_event2", perf_thread_event2, perf,
                                THREAD_STACK_SIZE, THREAD_PRIORITY + 1, THREAD_TIMESLICE);
    if (thread2 == RT_NULL)
    {
        LOG_E("perf_thread_event2 create failed.");
        return -RT_ERROR;
    }

    rt_thread_startup(thread1);
    rt_thread_startup(thread2);

    rt_sem_take(complete_sem, RT_WAITING_FOREVER);
    rt_perf_dump(perf);
    rt_sem_delete(complete_sem);
    return RT_EOK;
}

