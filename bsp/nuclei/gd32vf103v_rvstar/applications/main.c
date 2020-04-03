/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-23     tyustli      first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define THREAD_PRIORITY 2
#define THREAD_STACK_SIZE 512
#define THREAD_TIMESLICE 5
#define THREAD_NUM      20

/*　Align stack when using static thread　*/
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t thread_stack[THREAD_NUM][THREAD_STACK_SIZE];
static struct rt_thread tid[THREAD_NUM];

/* Thread entry function */
static void thread_entry(void *parameter)
{
    rt_uint32_t count = 0;

    while (1) {
        rt_kprintf("thread %d count: %d\n", (rt_uint32_t)parameter, count++);
        rt_thread_mdelay(500);
    }
}

/* Thread demo */
int create_thread_demo(void)
{
    int i;
    for (i = 0; i < THREAD_NUM; i ++) {
        /* Create static threads */
        rt_thread_init(&tid[i], "thread", thread_entry, (void *)i, thread_stack[i],
                   THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    }

    /* Startup threads  */
    for (i = 0; i < THREAD_NUM; i ++) {
        rt_thread_startup(&tid[i]);
    }

    return 0;
}

int main(void)
{
    rt_uint32_t count = 0;

    create_thread_demo();

    while (1) {
        rt_kprintf("Main thread count: %d\n", count++);
        rt_thread_mdelay(1000);
    }
}

/******************** end of file *******************/

