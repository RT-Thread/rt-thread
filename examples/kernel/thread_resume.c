/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 *
 */

/*
 * 程序清单：唤醒线程
 *
 * 这个例子中将创建两个动态线程，低优先级线程将挂起自身，然后
 * 高优先级线程将在一定时刻后唤醒低优先级线程。
 */
#include <rtthread.h>
#include "tc_comm.h"

/* 指向线程控制块的指针 */
static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;
/* 线程1入口 */
static void thread1_entry(void* parameter)
{
    /* 低优先级线程1开始运行 */
    rt_kprintf("thread1 startup%d\n");

    /* 挂起自身 */
    rt_kprintf("suspend thread self\n");
    rt_thread_suspend(tid1);
    /* 主动执行线程调度 */
    rt_schedule();

    /* 当线程1被唤醒时 */
    rt_kprintf("thread1 resumed\n");
}
static void thread_cleanup(rt_thread_t tid)
{
    if (tid == tid1)
    {
        tid1 = RT_NULL;
    }
    if (tid == tid2)
    {
        tid = RT_NULL;
    }
}

/* 线程2入口 */
static void thread2_entry(void* parameter)
{
    /* 延时10个OS Tick */
    rt_thread_delay(10);

    /* 唤醒线程1 */
    rt_thread_resume(tid1);
    rt_kprintf("thread2: to resume thread1\n");

    /* 延时10个OS Tick */
    rt_thread_delay(10);

    /* 线程2自动退出 */
}

int thread_resume_init()
{
    /* 创建线程1 */
    tid1 = rt_thread_create("thread",
        thread1_entry, RT_NULL, /* 线程入口是thread1_entry, 入口参数是RT_NULL */
        THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
    {
        tid1->cleanup = thread_cleanup;
        rt_thread_startup(tid1);
    }
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    /* 创建线程2 */
    tid2 = rt_thread_create("thread",
        thread2_entry, RT_NULL, /* 线程入口是thread2_entry, 入口参数是RT_NULL */
        THREAD_STACK_SIZE, THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    if (tid2 != RT_NULL)
    {
        tid2->cleanup = thread_cleanup;
        rt_thread_startup(tid2);
    }
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

int _tc_thread_resume()
{
    /* 设置TestCase清理回调函数 */
    tc_cleanup(_tc_cleanup);
    thread_resume_init();

    /* 返回TestCase运行的最长时间 */
    return 25;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_thread_resume, a thread resume example);
#else
/* 用户应用入口 */
int rt_application_init()
{
    thread_resume_init();

    return 0;
}
#endif
