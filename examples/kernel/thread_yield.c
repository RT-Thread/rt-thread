/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 *
 */

#include <rtthread.h>
#include "tc_comm.h"

/* 指向线程控制块的指针 */
static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;
/* 线程1入口 */
static void thread1_entry(void* parameter)
{
    rt_uint32_t count = 0;

    while (1)
    {
        /* 打印线程1的输出 */
        rt_kprintf("thread1: count = %d\n", count ++);

        /* 执行yield后应该切换到thread2执行 */
        rt_thread_yield();
    }
}

/* 线程2入口 */
static void thread2_entry(void* parameter)
{
    rt_uint32_t count = 0;

    while (1)
    {
        /* 打印线程2的输出 */
        rt_kprintf("thread2: count = %d\n", count ++);

        /* 执行yield后应该切换到thread1执行 */
        rt_thread_yield();
    }
}

int thread_yield_init()
{
    /* 创建线程1 */
    tid1 = rt_thread_create("thread",
        thread1_entry, RT_NULL, /* 线程入口是thread1_entry, 入口参数是RT_NULL */
        THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    /* 创建线程2 */
    tid2 = rt_thread_create("thread",
        thread2_entry, RT_NULL, /* 线程入口是thread2_entry, 入口参数是RT_NULL */
        THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
    /* 调度器上锁，上锁后，将不再切换到其他线程，仅响应中断 */
    rt_enter_critical();

    /* 删除线程 */
    if (tid1 != RT_NULL && tid1->stat != RT_THREAD_CLOSE)
        rt_thread_delete(tid1);
    if (tid2 != RT_NULL && tid2->stat != RT_THREAD_CLOSE)
        rt_thread_delete(tid2);

    /* 调度器解锁 */
    rt_exit_critical();

    /* 设置TestCase状态 */
    tc_done(TC_STAT_PASSED);
}

int _tc_thread_yield()
{
    /* 设置TestCase清理回调函数 */
    tc_cleanup(_tc_cleanup);
    thread_yield_init();

    /* 返回TestCase运行的最长时间 */
    return 30;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_thread_yield, a thread yield example);
#else
/* 用户应用入口 */
int rt_application_init()
{
    thread_yield_init();

    return 0;
}
#endif
