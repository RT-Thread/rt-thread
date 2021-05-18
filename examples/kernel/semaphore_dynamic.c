/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 *
 */

/*
 * 程序清单：动态信号量
 *
 * 这个例子中将创建一个动态信号量（初始值为0 ）及一个动态线程，在这个动态线程中
 * 将试图采用超时方式去持有信号量，应该超时返回。然后这个线程释放一次信号量，并
 * 在后面继续采用永久等待方式去持有信号量， 成功获得信号量后返回。
 */
#include <rtthread.h>
#include "tc_comm.h"

/* 指向线程控制块的指针 */
static rt_thread_t tid = RT_NULL;
/* 指向信号量的指针 */
static rt_sem_t sem = RT_NULL;
/* 线程入口 */
static void thread_entry(void* parameter)
{
    rt_err_t result;
    rt_tick_t tick;

    /* 获得当前的OS Tick */
    tick = rt_tick_get();

    /* 试图持有一个信号量，如果10个OS Tick依然没拿到，则超时返回 */
    result = rt_sem_take(sem, 10);
    if (result == -RT_ETIMEOUT)
    {
        rt_tick_t new_tick = rt_tick_get();
        /* 可以有两个 tick 的误差 */
        if (new_tick - tick >= 12)
        {
            rt_kprintf("tick error to large: expect: 10, get %d\n",
                       new_tick - tick);

            /* 如果失败，则测试失败 */
            tc_done(TC_STAT_FAILED);
            rt_sem_delete(sem);
            return;
        }
        rt_kprintf("take semaphore timeout\n");
    }
    else
    {
        /* 因为并没释放信号量，应该是超时返回，否则测试失败 */
        tc_done(TC_STAT_FAILED);
        rt_sem_delete(sem);
        return;
    }

    /* 释放一次信号量 */
    rt_sem_release(sem);

    /* 继续持有信号量，并永远等待直到持有到信号量 */
    result = rt_sem_take(sem, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        /* 返回不正确，测试失败 */
        tc_done(TC_STAT_FAILED);
        rt_sem_delete(sem);
        return;
    }

    /* 测试成功 */
    tc_done(TC_STAT_PASSED);
    /* 删除信号量 */
    rt_sem_delete(sem);
}

int semaphore_dynamic_init()
{
    /* 创建一个信号量，初始值是0 */
    sem = rt_sem_create("sem", 0, RT_IPC_FLAG_FIFO);
    if (sem == RT_NULL)
    {
        tc_stat(TC_STAT_END | TC_STAT_FAILED);
        return 0;
    }

    /* 创建线程 */
    tid = rt_thread_create("thread",
                           thread_entry, RT_NULL, /* 线程入口是thread_entry, 入口参数是RT_NULL */
                           THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
    /* 调度器上锁，上锁后，将不再切换到其他线程，仅响应中断 */
    rt_enter_critical();

    if (sem)
    {
        rt_sem_delete(sem);
        sem = RT_NULL;
    }

    /* 删除线程 */
    if (tid != RT_NULL && tid->stat != RT_THREAD_CLOSE)
    {
        rt_thread_delete(tid);
    }

    /* 调度器解锁 */
    rt_exit_critical();

    /* 设置TestCase状态 */
    tc_done(TC_STAT_PASSED);
}

int _tc_semaphore_dynamic()
{
    /* 设置TestCase清理回调函数 */
    tc_cleanup(_tc_cleanup);
    semaphore_dynamic_init();

    /* 返回TestCase运行的最长时间 */
    return 100;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_semaphore_dynamic, a dynamic semaphore example);
#else
/* 用户应用入口 */
int rt_application_init()
{
    semaphore_dynamic_init();

    return 0;
}
#endif
