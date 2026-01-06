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

static rt_sem_t sem1, sem2;
static rt_sem_t complete_sem = RT_NULL;

static void local_modify_time(rt_perf_t *perf)
{
    if(perf)
        perf->real_time = perf->real_time - perf->tmp_time;
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

    for (rt_uint32_t i = 0; i < RT_UTEST_SYS_PERF_TC_COUNT; i++)
    {
        perf->tmp_time = 0;
        rt_perf_start(perf);
        rt_sem_take(sem2, RT_WAITING_FOREVER);
        rt_sem_release(sem2);
        rt_perf_stop(perf);

        rt_mutex_take(perf->lock,RT_WAITING_FOREVER);
        perf->count -= 1;
        perf->tmp_time = perf->real_time;
        rt_mutex_release(perf->lock);

        rt_perf_start(perf);
        rt_sem_take(sem2, RT_WAITING_FOREVER);
        rt_sem_release(sem1);
        rt_perf_stop(perf);
    }
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

    perf->local_modify = local_modify_time;
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

    rt_perf_dump(perf);
    rt_thread_delete(thread1);
    rt_sem_delete(complete_sem);
    rt_sem_delete(sem1);
    rt_sem_delete(sem2);

    return RT_EOK;
}

