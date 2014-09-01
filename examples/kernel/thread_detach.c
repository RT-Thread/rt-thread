/*
 * 程序清单：线程脱离
 *
 * 这个例子会创建两个线程，在其中一个线程中执行对另一个线程的脱离。
 */
#include <rtthread.h>
#include "tc_comm.h"

/* 线程1控制块 */
static struct rt_thread thread1;
/* 线程1栈 */
static rt_uint8_t thread1_stack[THREAD_STACK_SIZE];
/* 线程2控制块 */
static struct rt_thread thread2;
/* 线程2栈 */
static rt_uint8_t thread2_stack[THREAD_STACK_SIZE];

/* 线程1入口 */
static void thread1_entry(void* parameter)
{
    rt_uint32_t count = 0;

    while (1)
    {
        /* 线程1采用低优先级运行，一直打印计数值 */
        rt_kprintf("thread count: %d\n", count ++);
    }
}

/* 线程2入口 */
static void thread2_entry(void* parameter)
{
    /* 线程2拥有较高的优先级，以抢占线程1而获得执行 */

    /* 线程2启动后先睡眠10个OS Tick */
    rt_thread_delay(10);

    /*
     * 线程2唤醒后直接执行线程1脱离，线程1将从就绪线程队列中删除
     */
    rt_thread_detach(&thread1);

    /*
     * 线程2继续休眠10个OS Tick然后退出
     */
    rt_thread_delay(10);

    /*
     * 线程2运行结束后也将自动被从就绪队列中删除，并脱离线程队列
     */
}

int thread_detach_init()
{
    rt_err_t result;

    /* 初始化线程1 */
    result = rt_thread_init(&thread1, "t1", /* 线程名：t1 */
        thread1_entry, RT_NULL, /* 线程的入口是thread1_entry，入口参数是RT_NULL*/
        &thread1_stack[0], sizeof(thread1_stack), /* 线程栈是thread1_stack */
        THREAD_PRIORITY, 10);
    if (result == RT_EOK) /* 如果返回正确，启动线程1 */
        rt_thread_startup(&thread1);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    /* 初始化线程2 */
    result = rt_thread_init(&thread2, "t2", /* 线程名：t2 */
        thread2_entry, RT_NULL, /* 线程的入口是thread2_entry，入口参数是RT_NULL*/
        &thread2_stack[0], sizeof(thread2_stack), /* 线程栈是thread2_stack */
        THREAD_PRIORITY - 1, 10);
    if (result == RT_EOK) /* 如果返回正确，启动线程2 */
        rt_thread_startup(&thread2);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
    /* 调度器上锁，上锁后，将不再切换到其他线程，仅响应中断 */
    rt_enter_critical();

    /* 执行线程脱离 */
    if (thread1.stat != RT_THREAD_CLOSE)
        rt_thread_detach(&thread1);
    if (thread2.stat != RT_THREAD_CLOSE)
        rt_thread_detach(&thread2);

    /* 调度器解锁 */
    rt_exit_critical();

    /* 设置TestCase状态 */
    tc_done(TC_STAT_PASSED);
}

int _tc_thread_detach()
{
    /* 设置TestCase清理回调函数 */
    tc_cleanup(_tc_cleanup);
    thread_detach_init();

    /* 返回TestCase运行的最长时间 */
    return 25;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_thread_detach, a static thread example);
#else
/* 用户应用入口 */
int rt_application_init()
{
    thread_detach_init();

    return 0;
}
#endif
