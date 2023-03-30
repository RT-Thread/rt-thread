/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-04-16                  first version
 */

#include <rtthread.h>

#define THREAD_STACK_SIZE   1024

#if 0
struct rt_semaphore sem1, sem2;
static struct rt_thread thread1;
rt_align(4)
static rt_uint8_t thread1_stack[THREAD_STACK_SIZE];
static struct rt_thread thread2;
rt_align(4)
static rt_uint8_t thread2_stack[THREAD_STACK_SIZE];

static void thread1_entry(void* parameter)
{
    while (1)
    {
        rt_sem_release(&sem2);
        rt_kprintf("thread1..: %s\n", rt_thread_self()->parent.name);
        rt_sem_take(&sem1, RT_WAITING_FOREVER);
        rt_kprintf("thread1..: %s\n", rt_thread_self()->parent.name);
    }
}

static void thread2_entry(void* parameter)
{
    while (1)
    {
        rt_sem_take(&sem2, RT_WAITING_FOREVER);
        rt_kprintf("thread2--->: %s\n", rt_thread_self()->parent.name);
        rt_sem_release(&sem1);
    }
}

/* user application */
int rt_application_init()
{
    rt_err_t result;

    rt_sem_init(&sem1, "s1", 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem2, "s2", 0, RT_IPC_FLAG_FIFO);

    result = rt_thread_init(&thread1, "t1", thread1_entry, RT_NULL,
        &thread1_stack[0], sizeof(thread1_stack), 10, 10);
    if (result == RT_EOK)
        rt_thread_startup(&thread1);

    result = rt_thread_init(&thread2, "t2", thread2_entry, RT_NULL,
        &thread2_stack[0], sizeof(thread2_stack), 18, 10);
    if (result == RT_EOK)
        rt_thread_startup(&thread2);

    return 0;
}
#else
static struct rt_thread thread1;
rt_align(4)
static rt_uint8_t thread1_stack[THREAD_STACK_SIZE];
rt_timer_t ttimer;

static void thread1_entry(void* parameter)
{
    rt_uint32_t count = 0;
    while (1)
    {
        rt_kprintf("%s: count = %d\n", rt_thread_self()->parent.name, count ++);

        rt_thread_delay(10);
    }
}

/* user application */
int rt_application_init()
{
    rt_err_t result;

    result = rt_thread_init(&thread1, "t1", thread1_entry, RT_NULL,
        &thread1_stack[0], sizeof(thread1_stack), 10, 10);

    ttimer = &(thread1.thread_timer);
    if (result == RT_EOK)
        rt_thread_startup(&thread1);

    return 0;
}
#endif
