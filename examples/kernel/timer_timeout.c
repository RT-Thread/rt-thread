/*
 * 程序清单：消息队列例程
 *
 * 这个程序会创建3个动态线程，一个线程会从消息队列中收取消息；一个线程会定时给消
 * 息队列发送消息；一个线程会定时给消息队列发送紧急消息。
 */
#include <rtthread.h>
#include "tc_comm.h"

/* 指向线程控制块的指针 */
static rt_thread_t tid = RT_NULL;

/* 消息队列控制块 */
static struct rt_messagequeue mq;
/* 消息队列中用到的放置消息的内存池 */
static char msg_pool[2048];

/* 定时器的控制块 */
static struct rt_timer timer;
static rt_uint16_t no = 0;
static void timer_timeout(void* parameter)
{
    char buf[32];
    rt_uint32_t length;

    length = rt_snprintf(buf, sizeof(buf), "message %d", no++);
    rt_mq_send(&mq, &buf[0], length);
}

/* 线程入口函数 */
static void thread_entry(void* parameter)
{
    char buf[64];
    rt_err_t result;

    /* 初始化定时器 */
    rt_timer_init(&timer, "timer",  /* 定时器名字是 timer1 */
        timer_timeout, /* 超时时回调的处理函数 */
        RT_NULL, /* 超时函数的入口参数 */
        1, /* 定时长度，以OS Tick为单位，即1个OS Tick */
        RT_TIMER_FLAG_PERIODIC); /* 周期性定时器 */

    while (1)
    {
        rt_memset(&buf[0], 0, sizeof(buf));

        /* 从消息队列中接收消息 */
        result = rt_mq_recv(&mq, &buf[0], sizeof(buf), 1);
        if (result == RT_EOK)
        {
            rt_kprintf("recv msg: %s\n", buf);
        }
        else if (result == -RT_ETIMEOUT)
        {
            rt_kprintf("recv msg timeout\n");
        }
    }
}

int timer_timeout_init()
{
    /* 初始化消息队列 */
    rt_mq_init(&mq, "mqt", 
        &msg_pool[0], /* 内存池指向msg_pool */ 
        128 - sizeof(void*), /* 每个消息的大小是 128 - void* */
        sizeof(msg_pool), /* 内存池的大小是msg_pool的大小 */
        RT_IPC_FLAG_FIFO); /* 如果有多个线程等待，按照先来先得到的方法分配消息 */

    /* 创建线程 */
    tid = rt_thread_create("t",
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

    /* 删除线程 */
    if (tid != RT_NULL && tid->stat != RT_THREAD_CLOSE)
        rt_thread_delete(tid);

    /* 执行消息队列对象脱离 */
    rt_mq_detach(&mq);
    /* 执行定时器脱离 */
    rt_timer_detach(&timer);

    /* 调度器解锁 */
    rt_exit_critical();

    /* 设置TestCase状态 */
    tc_done(TC_STAT_PASSED);
}

int _tc_timer_timeout()
{
    /* 设置TestCase清理回调函数 */
    tc_cleanup(_tc_cleanup);
    timer_timeout_init();

    /* 返回TestCase运行的最长时间 */
    return 100;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_timer_timeout, a thread timer testcase);
#else
/* 用户应用入口 */
int rt_application_init()
{
    timer_timeout_init();

    return 0;
}
#endif
