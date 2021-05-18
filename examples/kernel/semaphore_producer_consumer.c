/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 *
 */

/*
 * 程序清单：生产者消费者例子
 *
 * 这个例子中将创建两个线程用于实现生产者消费者问题
 */
#include <rtthread.h>
#include "tc_comm.h"

/* 定义最大5个元素能够被产生 */
#define MAXSEM 5

/* 用于放置生产的整数数组 */
rt_uint32_t array[MAXSEM];
/* 指向生产者、消费者在array数组中的读写位置 */
static rt_uint32_t set, get;

/* 指向线程控制块的指针 */
static rt_thread_t producer_tid = RT_NULL;
static rt_thread_t consumer_tid = RT_NULL;

struct rt_semaphore sem_lock;
struct rt_semaphore sem_empty, sem_full;

/* 生成者线程入口 */
void producer_thread_entry(void* parameter)
{
    int cnt = 0;

    /* 运行100次 */
    while( cnt < 100)
    {
        /* 获取一个空位 */
        rt_sem_take(&sem_empty, RT_WAITING_FOREVER);

        /* 修改array内容，上锁 */
        rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
        array[set%MAXSEM] = cnt + 1;
        rt_kprintf("the producer generates a number: %d\n", array[set%MAXSEM]);
        set++;
        rt_sem_release(&sem_lock);

        /* 发布一个满位 */
        rt_sem_release(&sem_full);
        cnt++;

        /* 暂停一段时间 */
        rt_thread_delay(50);
    }

    rt_kprintf("the producer exit!\n");
}

/* 消费者线程入口 */
void consumer_thread_entry(void* parameter)
{
    rt_uint32_t no;
    rt_uint32_t sum;

    /* 第n个线程，由入口参数传进来 */
    no = (rt_uint32_t)parameter;

    sum = 0;
    while(1)
    {
        /* 获取一个满位 */
        rt_sem_take(&sem_full, RT_WAITING_FOREVER);

        /* 临界区，上锁进行操作 */
        rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
        sum += array[get%MAXSEM];
        rt_kprintf("the consumer[%d] get a number: %d\n", no, array[get%MAXSEM] );
        get++;
        rt_sem_release(&sem_lock);

        /* 释放一个空位 */
        rt_sem_release(&sem_empty);

        /* 生产者生产到100个数目，停止，消费者线程相应停止 */
        if (get == 100) break;

        /* 暂停一小会时间 */
        rt_thread_delay(10);
    }

    rt_kprintf("the consumer[%d] sum is %d \n ", no, sum);
    rt_kprintf("the consumer[%d] exit!\n");
}

int semaphore_producer_consumer_init()
{
    /* 初始化3个信号量 */
    rt_sem_init(&sem_lock , "lock",     1,      RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_empty, "empty",    MAXSEM, RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_full , "full",     0,      RT_IPC_FLAG_FIFO);

    /* 创建线程1 */
    producer_tid = rt_thread_create("producer",
                                    producer_thread_entry, RT_NULL, /* 线程入口是producer_thread_entry, 入口参数是RT_NULL */
                                    THREAD_STACK_SIZE, THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    if (producer_tid != RT_NULL)
        rt_thread_startup(producer_tid);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    /* 创建线程2 */
    consumer_tid = rt_thread_create("consumer",
                                    consumer_thread_entry, RT_NULL, /* 线程入口是consumer_thread_entry, 入口参数是RT_NULL */
                                    THREAD_STACK_SIZE, THREAD_PRIORITY + 1, THREAD_TIMESLICE);
    if (consumer_tid != RT_NULL)
        rt_thread_startup(consumer_tid);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
    /* 调度器上锁，上锁后，将不再切换到其他线程，仅响应中断 */
    rt_enter_critical();

    rt_sem_detach(&sem_lock);
    rt_sem_detach(&sem_empty);
    rt_sem_detach(&sem_full);

    /* 删除线程 */
    if (producer_tid != RT_NULL && producer_tid->stat != RT_THREAD_CLOSE)
        rt_thread_delete(producer_tid);
    if (consumer_tid != RT_NULL && consumer_tid->stat != RT_THREAD_CLOSE)
        rt_thread_delete(consumer_tid);

    /* 调度器解锁 */
    rt_exit_critical();

    /* 设置TestCase状态 */
    tc_done(TC_STAT_PASSED);
}

int _tc_semaphore_producer_consumer()
{
    /* 设置TestCase清理回调函数 */
    tc_cleanup(_tc_cleanup);
    semaphore_producer_consumer_init();

    /* 返回TestCase运行的最长时间 */
    return 100;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_semaphore_producer_consumer, producer and consumer example);
#else
/* 用户应用入口 */
int rt_application_init()
{
    semaphore_producer_consumer_init();

    return 0;
}
#endif
