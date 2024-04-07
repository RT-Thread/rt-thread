/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-25     Shell        the first version
 */
#include <rtthread.h>
#include "utest.h"

#define TEST_LOOP_TIMES 20

static struct rt_semaphore _thr_exit_sem;

static void _thread_entry(void *param)
{
    for (size_t i = 0; i < TEST_LOOP_TIMES; i++)
    {
        rt_kprintf("This is thread %p\n", rt_thread_self());
        rt_thread_mdelay(1);
    }

    rt_sem_release(&_thr_exit_sem);
    return;
}

#define TEST_THREAD_COUNT 16

static void mtsafe_kprint_tc(void)
{
    for (size_t i = 0; i < TEST_THREAD_COUNT; i++)
    {
        rt_thread_t new_thread =
            rt_thread_create(
                "test",
                _thread_entry,
                NULL,
                UTEST_THR_STACK_SIZE,
                UTEST_THR_PRIORITY,
                100);
        rt_thread_startup(new_thread);
    }

    for (size_t i = 0; i < TEST_THREAD_COUNT; i++)
    {
        rt_sem_take(&_thr_exit_sem, RT_WAITING_FOREVER);
    }
}

static rt_err_t utest_tc_init(void)
{
    rt_sem_init(&_thr_exit_sem, "test", 0, RT_IPC_FLAG_PRIO);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_detach(&_thr_exit_sem);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(mtsafe_kprint_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.mtsafe_kprint", utest_tc_init, utest_tc_cleanup, 10);
