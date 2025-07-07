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

static rt_sem_t sem1, sem2;
static rt_thread_t thread1, thread2;
#define THREAD_STACK_SIZE       1024
#define THREAD_PRIORITY         10
#define THREAD_TIMESLICE        5

#define SWITCH_COUNT 1000  /* Number of context switches */

#ifdef USING_HWTIME_AS_TIME_REF
static rt_device_t hw_dev = RT_NULL;

static rt_size_t get_timer_us(rt_hwtimerval_t *timeout_s)
{
    if (hw_dev)
        return rt_device_read(hw_dev, 0, timeout_s, sizeof(rt_hwtimerval_t));
    return 0;
}
#endif

static void thread1_entry(void *parameter)
{
    while (1)
    {
        rt_sem_take(sem1, RT_WAITING_FOREVER);
        rt_sem_release(sem2);
    }
}

static void thread2_entry(void *parameter)
{
    rt_uint32_t total_time = 0;
    rt_uint32_t sem_op_time = 0;
    rt_uint32_t i;
#ifdef USING_HWTIME_AS_TIME_REF
    rt_hwtimerval_t start_time, end_time;
    rt_uint16_t ret;
    /* Getting Signal Time */
    ret = get_timer_us(&start_time);
    for (i = 0; i < SWITCH_COUNT; i++)
    {
        rt_sem_take(sem2, RT_WAITING_FOREVER);
        rt_sem_release(sem2);
    }
    ret +=get_timer_us(&end_time);
    sem_op_time = (end_time.sec - start_time.sec) * 1000000u + (end_time.usec - start_time.usec);

    ret += get_timer_us(&start_time);
    for (i = 0; i < SWITCH_COUNT; i++)
    {
        rt_sem_take(sem2, RT_WAITING_FOREVER);
        rt_sem_release(sem1);
    }
    ret +=get_timer_us(&end_time);
    total_time = (end_time.sec - start_time.sec) * 1000000u + (end_time.usec - start_time.usec);
#else
    rt_uint32_t start_time, end_time;
    /* Getting Signal Time */
    start_time = rt_tick_get();
    for (i = 0; i < SWITCH_COUNT; i++)
    {
        rt_sem_take(sem2, RT_WAITING_FOREVER);
        rt_sem_release(sem2);
    }
    end_time = rt_tick_get();
    sem_op_time = (end_time - start_time) / RT_TICK_PER_SECOND;
    sem_op_time += ((end_time - start_time) % RT_TICK_PER_SECOND) * (1000000u / RT_TICK_PER_SECOND);

    start_time = rt_tick_get();
    for (i = 0; i < SWITCH_COUNT; i++)
    {
       rt_sem_take(sem2, RT_WAITING_FOREVER);
       rt_sem_release(sem1);
    }
    end_time = rt_tick_get();
    total_time = (end_time - start_time) / RT_TICK_PER_SECOND;
    total_time += ((end_time - start_time) % RT_TICK_PER_SECOND) * (1000000u / RT_TICK_PER_SECOND);
#endif

    rt_uint32_t single_switch_time = total_time / SWITCH_COUNT; /* Total single switching time */
    rt_uint32_t single_sem_op_time = sem_op_time / SWITCH_COUNT; /* Single semaphore operation time */
    rt_uint32_t context_switch_time = single_switch_time - single_sem_op_time; /* Context switching time */

    LOG_I("Total time for %d switches: %d us", SWITCH_COUNT, total_time);
    LOG_I("Single switch time (including semaphore): %d us", single_switch_time);
    LOG_I("Semaphore operation time: %d us", single_sem_op_time);
    LOG_I("Pure context switch time: %d us", context_switch_time);
}

void context_switch_test(void)
{
    thread1 = rt_thread_create("thread1", thread1_entry, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (thread1 != RT_NULL)
    {
        rt_thread_startup(thread1);
    }

    thread2 = rt_thread_create("thread2", thread2_entry, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (thread2 != RT_NULL)
    {
        rt_thread_startup(thread2);
    }
}

static rt_err_t utest_tc_init(void)
{
    int ret = RT_EOK;
#ifdef USING_HWTIME_AS_TIME_REF
    rt_hwtimerval_t timeout_s;

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

    timeout_s.sec  = 5;      /* s  */
    timeout_s.usec = 0;     /* us */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(rt_hwtimerval_t)) != sizeof(rt_hwtimerval_t))
    {
        ret = RT_ERROR;
        LOG_E("set timeout value failed");
        return ret;
    }
#endif
    sem1 = rt_sem_create("sem1", 1, RT_IPC_FLAG_FIFO);
    sem2 = rt_sem_create("sem2", 0, RT_IPC_FLAG_FIFO);
    if (sem1 == RT_NULL || sem2 == RT_NULL)
    {
        ret = RT_ERROR;
        LOG_E("Semaphore create failed!");
        return ret;
    }
    return ret;
}

static rt_err_t utest_tc_cleanup(void)
{
    if (thread1) rt_thread_delete(thread1);
    if(sem1) rt_sem_delete(sem1);
    if(sem2) rt_sem_delete(sem2);
#ifdef USING_HWTIME_AS_TIME_REF
    if(hw_dev) rt_device_close(hw_dev);
#endif
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(context_switch_test);
}

UTEST_TC_EXPORT(testcase, "testcase.pref.context", utest_tc_init, utest_tc_cleanup, 10);
