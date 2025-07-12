/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-03     rcitach      test case for context_switch
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <utest.h>
#include <utest_assert.h>
#include <perf_tc.h>

typedef struct rt_perf_array
{
    rt_uint32_t count;
    rt_uint32_t *raw_times;
    rt_uint32_t *local_times;
    rt_uint32_t *net_times;
} rt_perf_array_t;

static rt_sem_t sem1, sem2;
static rt_sem_t complete_sem = RT_NULL;

void rt_perf_array_destroy(rt_perf_array_t *arr)
{
    if (arr)
    {
        if (arr->raw_times)   rt_free(arr->raw_times);
        if (arr->local_times) rt_free(arr->local_times);
        if (arr->net_times)   rt_free(arr->net_times);
        rt_free(arr);
    }
}

rt_perf_array_t *rt_perf_array_create(rt_uint32_t count)
{
    rt_perf_array_t *arr = rt_calloc(1, sizeof(rt_perf_array_t));
    if (!arr)
        return RT_NULL;

    arr->count = count;
    arr->raw_times = rt_calloc(count, sizeof(rt_uint32_t));
    arr->local_times = rt_calloc(count, sizeof(rt_uint32_t));
    arr->net_times = rt_calloc(count, sizeof(rt_uint32_t));

    if (!arr->raw_times || !arr->local_times || !arr->net_times)
    {
        rt_perf_array_destroy(arr);
        return RT_NULL;
    }

    return arr;
}

void rt_perf_array_compute(rt_perf_array_t *arr, rt_perf_t *perf)
{
    rt_uint32_t i;
    rt_uint32_t tot_time = 0;
    rt_uint32_t max_time = 0;
    rt_uint32_t min_time = 0xFFFFFFFF;

    for (i = 0; i < arr->count; i++)
    {
        rt_uint32_t net = (arr->raw_times[i] > arr->local_times[i]) ?
                          (arr->raw_times[i] - arr->local_times[i]) : 0;
        arr->net_times[i] = net;

        tot_time += net;
        if (net > max_time) max_time = net;
        if (net < min_time) min_time = net;
    }

    perf->count = arr->count;
    perf->tot_time = tot_time;
    perf->max_time = max_time;
    perf->min_time = min_time;
}

static void perf_thread_event1(void *parameter)
{
    while (1)
    {
        rt_sem_take(sem1, RT_WAITING_FOREVER);
        rt_sem_release(sem2);
    }
}

static void perf_thread_event2(void *parameter)
{
    rt_perf_t *perf = (rt_perf_t *)parameter;
    rt_perf_t *perf_local = (rt_perf_t *)rt_calloc(1,sizeof(rt_perf_t));
    rt_uint32_t i;

    rt_perf_array_t *perf_arr = rt_perf_array_create(UTEST_SYS_PERF_TC_COUNT);
    if (!perf_arr)
    {
        LOG_E("Failed to allocate performance arrays");
        return;
    }

    for (i = 0; i < UTEST_SYS_PERF_TC_COUNT; i++)
    {
        rt_perf_start(perf_local);
        rt_sem_take(sem2, RT_WAITING_FOREVER);
        rt_sem_release(sem2);
        rt_perf_stop(perf_local);
        perf_arr->local_times[i] = perf_local->real_time;
    }

    for (i = 0; i < UTEST_SYS_PERF_TC_COUNT; i++)
    {
        rt_perf_start(perf);
        rt_sem_take(sem2, RT_WAITING_FOREVER);
        rt_sem_release(sem1);
        rt_perf_stop(perf);
        perf_arr->raw_times[i] = perf->real_time;
    }

    rt_perf_array_compute(perf_arr, perf);
    rt_perf_array_destroy(perf_arr);
    rt_free(perf_local);
    rt_sem_release(complete_sem);
}

rt_err_t context_switch_test(rt_perf_t *perf)
{
    rt_thread_t thread1 = RT_NULL;
    rt_thread_t thread2 = RT_NULL;

# if __STDC_VERSION__ >= 199901L
    rt_strcpy(perf->name,__func__);
#else
    rt_strcpy(perf->name,"context_switch_test");
#endif

    sem1 = rt_sem_create("sem1", 1, RT_IPC_FLAG_FIFO);
    sem2 = rt_sem_create("sem2", 0, RT_IPC_FLAG_FIFO);
    complete_sem = rt_sem_create("complete_sem", 0, RT_IPC_FLAG_FIFO);

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
    rt_thread_delete(thread1);
    rt_sem_delete(complete_sem);
    rt_sem_delete(sem1);
    rt_sem_delete(sem2);

    return RT_EOK;
}

