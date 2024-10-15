/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-13     RV           the first version
 */

#include <rtthread.h>
#include "utest.h"
#include <interrupt.h>

/**
 * @brief   Spinlock testcase.
 *
 * @note    Create multiple threads and use spinlocks to protect shared memory
 */

#define THREAD_PRIORITY   20
#define THREAD_TIMESLICE  20
#define THREAD_STACK_SIZE UTEST_THR_STACK_SIZE
static rt_thread_t        thread1;
static rt_thread_t        thread2;
static rt_uint8_t         finsh_flag = 0;
static struct rt_spinlock lock;
static rt_uint8_t         number1, number2 = 0;

static void rt_thread_entry1(void *parameter)
{
    while (1)
    {
        rt_spin_lock(&lock);
        number1++;
        rt_thread_yield();
        number2++;
        rt_spin_unlock(&lock);
        rt_thread_delay(5);
    }
}

static void rt_thread_entry2(void *parameter)
{
    while (1)
    {
        rt_spin_lock(&lock);
        uassert_int_equal(number1, number2);
        number1++;
        number2++;
        rt_spin_unlock(&lock);
        if (number1 >= 10)
        {
            finsh_flag = 1;
        }
        rt_thread_delay(5);
    }
}

static void smp_spinlock_tc(void)
{
    thread1 = rt_thread_create("T1", rt_thread_entry1, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY, 20);
    if (thread1 != RT_NULL)
    {
        rt_thread_startup(thread1);
    }

    thread2 = rt_thread_create("T2", rt_thread_entry2, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY - 1, 20);
    if (thread2 != RT_NULL)
    {
        rt_thread_startup(thread2);
    }
    while (finsh_flag == 0);
}

static rt_err_t utest_tc_init(void)
{
    rt_spin_lock_init(&lock);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_thread_delete(thread1);
    rt_thread_delete(thread2);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(smp_spinlock_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.smp.spinlock_tc", utest_tc_init, utest_tc_cleanup, 10);
