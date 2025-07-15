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
#include <perf_tc.h>

static rt_sem_t perf_thread_sem = RT_NULL;
static rt_event_t perf_thread_event = RT_NULL;
static rt_sem_t complete_sem = RT_NULL;

#define EVENT_FLAG          (1 << 0)
static void perf_thread_sem1(void *parameter)
{
    rt_err_t ret = RT_EOK;
    rt_perf_t *perf = (rt_perf_t *)parameter;
    rt_event_send(perf_thread_event, EVENT_FLAG);
    while (1)
    {
        ret = rt_sem_take(perf_thread_sem, RT_WAITING_FOREVER);
        rt_perf_stop(perf);
        if(ret != RT_EOK)
        {
            LOG_E("Sem recv error!");
            rt_sem_delete(perf_thread_sem);
            return;
        }

        if (perf->count >= UTEST_SYS_PERF_TC_COUNT)
        {
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
    rt_perf_t *perf = (rt_perf_t *)parameter;
    rt_uint32_t recv = 0;
    while (1)
    {
        if (perf->count >= UTEST_SYS_PERF_TC_COUNT)
        {
            rt_sem_release(complete_sem);
            return;
        }
        ret = rt_event_recv(perf_thread_event, EVENT_FLAG,
                (RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR),
                RT_WAITING_FOREVER, &recv);
        if(ret != RT_EOK)
        {
            LOG_E("Event reception failed");
            rt_event_delete(perf_thread_event);
            rt_sem_release(complete_sem);
            return;
        }
        rt_perf_start(perf);
        rt_sem_release(perf_thread_sem);
    }
}

rt_err_t rt_perf_thread_sem(rt_perf_t *perf)
{
    rt_thread_t thread1 = RT_NULL;
    rt_thread_t thread2 = RT_NULL;

# if __STDC_VERSION__ >= 199901L
    rt_strcpy(perf->name,__func__);
#else
    rt_strcpy(perf->name,"rt_perf_thread_sem");
#endif

    perf_thread_sem = rt_sem_create("perf_thread_sem", 0, RT_IPC_FLAG_FIFO);
    if (perf_thread_sem == RT_NULL)
    {
        LOG_E("perf_thread_sem create failed.");
        return -RT_ERROR;
    }

    perf_thread_event = rt_event_create("perf_thread_event", RT_IPC_FLAG_PRIO);
    complete_sem = rt_sem_create("complete", 0, RT_IPC_FLAG_FIFO);

    thread1 = rt_thread_create("perf_thread_sem1", perf_thread_sem1, perf,
                                THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (thread1 == RT_NULL)
    {
        LOG_E("perf_thread_sem1 create failed.");
        return -RT_ERROR;
    }

    thread2 = rt_thread_create("perf_thread_sem2", perf_thread_sem2, perf,
                                THREAD_STACK_SIZE, THREAD_PRIORITY + 1, THREAD_TIMESLICE);
    if (thread2 == RT_NULL)
    {
        LOG_E("perf_thread_sem2 create failed.");
        return -RT_ERROR;
    }

    rt_thread_startup(thread1);
    rt_thread_startup(thread2);

    rt_sem_take(complete_sem, RT_WAITING_FOREVER);
    rt_perf_dump(perf);
    rt_sem_delete(complete_sem);
    return RT_EOK;
}

