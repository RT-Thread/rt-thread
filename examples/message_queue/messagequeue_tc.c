/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-23     xin-zheqi    the first version
 */
/*
 * 程序清单：消息队列例程
 *
 * 
 * 
 */
#include <rtthread.h>
#define THREAD_PRIORITY      25
#define THREAD_TIMESLICE     5
/* 消息队列控制块 */
static struct rt_messagequeue mq;
/* 消息队列中用到的放置消息的内存池 */
static rt_uint8_t msg_pool[2048];
ALIGN(RT_ALIGN_SIZE)
static char thread1_stack[1024];
static struct rt_thread thread1;
/* 线程1入口函数 */
static void thread1_entry(void *parameter)
{
    char buf[10] = 0;
    rt_size_t length = 0;
    rt_uint8_t cnt = 0;
    while (1)
    {
        /* 从消息队列中接收消息 */
        if ((length = rt_mq_recv(&mq, buf, sizeof(buf), RT_WAITING_FOREVER)) >= 0)
        {
            rt_kprintf("thread1: recv msg from msg queue,the message's length is:%d, the content:%s\n", length, buf);
            if (cnt == 19)
            {
                break;
            }
        }
        /* 延时50ms */
        cnt++;
        rt_thread_mdelay(50);
    }
    rt_kprintf("thread1: detach mq \n");
    rt_mq_detach(&mq);
}
ALIGN(RT_ALIGN_SIZE)
static char thread2_stack[1024];
static struct rt_thread thread2;
/* 线程2入口 */
static void thread2_entry(void *parameter)
{
    int result;
    char buf[10] = "ABC";

    rt_uint8_t cnt = 0;
    while (1)
    {
        if (cnt == 8)
        {
            /* 发送紧急消息到消息队列中 */
            result = rt_mq_urgent(&mq, buf1, 3);
            if (result != RT_EOK)
            {
                rt_kprintf("rt_mq_urgent ERR\n");
            }
            else
            {
                rt_kprintf("thread2: send urgent message - %s\n", buf);
            }
        }
        else if (cnt >= 20)/* 发送20次消息之后退出 */
        {
            rt_kprintf("message queue stop send, thread2 quit\n");
            break;
        }
        else
        {
            /* 发送消息到消息队列中 */
            result = rt_mq_send(&mq, buf, 3);
            if (result != RT_EOK)
            {
                rt_kprintf("rt_mq_send ERR\n");
            }
            rt_kprintf("thread2: send message - %s\n", buf);
        }
        buf++;
        cnt++;
        /* 延时5ms */
        rt_thread_mdelay(5);
    }
}
/* 消息队列示例的初始化 */
int msgq_sample(void)
{
    rt_err_t result;
    /* 初始化消息队列 */
    result = rt_mq_init(&mq,
                        "mqt",
                        &msg_pool[0],               /* 内存池指向msg_pool */
                        3,                          /* 每个消息的大小是 3 字节 */
                        sizeof(msg_pool),           /* 内存池的大小是msg_pool的大小 */
                        RT_IPC_FLAG_FIFO);          /* 如果有多个线程等待，按照先来先得到的方法分配消息 */
    if (result != RT_EOK)
    {
        rt_kprintf("init message queue failed.\n");
        return -1;
    }
    rt_thread_init(&thread1,
                   "thread1",
                   thread1_entry,
                   RT_NULL,
                   &thread1_stack[0],
                   sizeof(thread1_stack),
                   THREAD_PRIORITY, THREAD_TIMESLICE);
    rt_thread_startup(&thread1);
    rt_thread_init(&thread2,
                   "thread2",
                   thread2_entry,
                   RT_NULL,
                   &thread2_stack[0],
                   sizeof(thread2_stack),
                   THREAD_PRIORITY, THREAD_TIMESLICE);
    rt_thread_startup(&thread2);
    return 0;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(msgq_sample, msgq sample);