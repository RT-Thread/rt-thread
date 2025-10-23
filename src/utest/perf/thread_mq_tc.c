/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-03     rcitach      test case for messagequeue
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <utest.h>
#include <utest_assert.h>
#include <perf_tc.h>

static rt_sem_t sem1 = RT_NULL;
static rt_sem_t complete_sem = RT_NULL;
static rt_mq_t perf_thread_mq = RT_NULL;

static void perf_thread_mq1(void *parameter)
{
    char recv = 0;
    rt_perf_t *perf = (rt_perf_t *)parameter;
    while (1)
    {
        rt_mq_recv(perf_thread_mq, &recv, 1, RT_WAITING_FOREVER);
        rt_perf_stop(perf);
        if (recv != 'A')
        {
            LOG_E("mq recv value error!");
            rt_mq_delete(perf_thread_mq);
            return;
        }

        if (perf->count >= RT_UTEST_SYS_PERF_TC_COUNT)
        {
            rt_mq_delete(perf_thread_mq);
            rt_sem_delete(sem1);
            return;
        }
        rt_sem_release(sem1);
    }
}

static void perf_thread_mq2(void *parameter)
{
    rt_perf_t *perf = (rt_perf_t *)parameter;
    char send = 'A';
    while (1)
    {
        if (perf->count >= RT_UTEST_SYS_PERF_TC_COUNT)
        {
            rt_sem_release(complete_sem);
            return;
        }
        rt_sem_take(sem1, RT_WAITING_FOREVER);
        rt_perf_start(perf);
        rt_mq_send(perf_thread_mq, &send, 1);
    }
}

rt_err_t rt_perf_thread_mq(rt_perf_t *perf)
{
    rt_thread_t thread1 = RT_NULL;
    rt_thread_t thread2 = RT_NULL;

# if __STDC_VERSION__ >= 199901L
    rt_strcpy(perf->name,__func__);
#else
    rt_strcpy(perf->name,"rt_perf_thread_mq");
#endif

    perf_thread_mq = rt_mq_create("perf_thread_mq", 1, 1, RT_IPC_FLAG_PRIO);
    if (perf_thread_mq == RT_NULL)
    {
        LOG_E("perf_thread_mq create failed.");
        return -RT_ERROR;
    }

    sem1 = rt_sem_create("sem1", 1, RT_IPC_FLAG_FIFO);
    complete_sem = rt_sem_create("complete", 0, RT_IPC_FLAG_FIFO);

    thread1 = rt_thread_create("perf_thread_mq1", perf_thread_mq1, perf,
                                THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (thread1 == RT_NULL)
    {
        LOG_E("perf_thread_mq1 create failed.");
        return -RT_ERROR;
    }

    thread2 = rt_thread_create("perf_thread_mq2", perf_thread_mq2, perf,
                                THREAD_STACK_SIZE, THREAD_PRIORITY + 1, THREAD_TIMESLICE);
    if (thread2 == RT_NULL)
    {
        LOG_E("perf_thread_mq2 create failed.");
        return -RT_ERROR;
    }

    rt_thread_startup(thread1);
    rt_thread_startup(thread2);

    rt_sem_take(complete_sem, RT_WAITING_FOREVER);
    rt_perf_dump(perf);
    rt_sem_delete(complete_sem);
    return RT_EOK;
}

