/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-25     tangzz98     the first version
 */

#include <rtthread.h>
#include <mprotect.h>

#define THREAD_PRIORITY      25
#define THREAD_STACK_SIZE    512
#define THREAD_TIMESLICE     5

rt_align(MPU_MIN_REGION_SIZE) rt_uint8_t thread1_private_data[MPU_MIN_REGION_SIZE];

static void thread1_entry(void *parameter)
{
    (void)parameter;
    /* Thread 1 configures thread1_private_data for exclusive access */
    rt_kprintf("Thread 1 configures private data\n");
    rt_mprotect_add_exclusive_region((void *)thread1_private_data, MPU_MIN_REGION_SIZE);
    rt_kprintf("Thread 1 private data address: %p - %p\n", &thread1_private_data[0], &thread1_private_data[MPU_MIN_REGION_SIZE]);
    rt_kprintf("Thread 1 reads and writes to its private data\n");
    for (int i = 0; i < MPU_MIN_REGION_SIZE; i++)
    {
        /* Thread 1 has access to its private data */
        thread1_private_data[i] = i;
        rt_kprintf("thread1_private_data[%d] = %d\n", i, thread1_private_data[i]);
    }
}

static void thread2_entry(void *parameter)
{
    (void)parameter;
    rt_kprintf("Thread 2 writes to thread 1's private data\n");
    for (int i = 0; i < MPU_MIN_REGION_SIZE; i++)
    {
        /*
         * Thread 2 does not have access to thread 1's private data.
         * Access generates an exception.
         */
        thread1_private_data[i] = i;
    }
}

int mprotect_example_exclusive_region()
{
    extern void mprotect_example_exception_hook(rt_mem_exception_info_t *info);
    rt_hw_mpu_exception_set_hook(mprotect_example_exception_hook);
    rt_thread_t tid1 = RT_NULL;
    tid1 = rt_thread_create("thread1",
                           thread1_entry, RT_NULL,
                           THREAD_STACK_SIZE,
                           THREAD_PRIORITY - 1,
                           THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    rt_thread_t tid2 = RT_NULL;
    tid2 = rt_thread_create("thread2",
                           thread2_entry, RT_NULL,
                           THREAD_STACK_SIZE,
                           THREAD_PRIORITY,
                           THREAD_TIMESLICE);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);

    return 0;
}

MSH_CMD_EXPORT(mprotect_example_exclusive_region, Memory protection example (exclusive_region));
