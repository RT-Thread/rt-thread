/*
 * 程序清单：线程嵌套挂起
 *
 * 请在rtconfig.h中定义RT_USING_SUSPEND_NESTING以开启该功能
 *
 * 2020-10-26    Meco Man    First Version
 */

#include <rtthread.h>
#include "tc_comm.h"

#ifdef RT_USING_SUSPEND_NESTING

/* 指向线程控制块的指针 */
static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;
/* 线程1入口 */
static void thread1_entry(void* parameter)
{
    rt_uint32_t count = 0;
    
    while (1)
    {
        /* 线程1采用低优先级运行，一直打印计数值 */
        rt_kprintf("thread1 count: %d\n", count ++);
        rt_thread_delay(200);
    }
}

/* 线程2入口 */
static void thread2_entry(void* parameter)
{
    while(1)
    {
        /* 连续挂起5次线程1,测试嵌套挂起 */
        rt_thread_suspend(tid1);
        rt_thread_suspend(tid1);
        rt_thread_suspend(tid1);
        rt_thread_suspend(tid1);
        rt_thread_suspend(tid1);
        
        /* 打印此时thread1线程的嵌套挂起层数 */
        rt_kprintf("thread1 suspend_ctr: %d\n", tid1->suspend_ctr);
        
        /* 延时2000个OS Tick */
        rt_thread_delay(1000);
        
        /* 连续解挂5次线程1,测试嵌套解挂 */
        rt_thread_resume(tid1);
        rt_thread_resume(tid1);
        rt_thread_resume(tid1);
        rt_thread_resume(tid1);
        rt_thread_resume(tid1);
        
        /* 打印此时thread1线程的嵌套挂起层数 */
        rt_kprintf("thread1 suspend_ctr: %d\n", tid1->suspend_ctr);
        
        /* 延时2000个OS Tick */
        rt_thread_delay(1000);        
    }
}

int thread_suspend_init(void)
{
    /* 创建线程1 */
    tid1 = rt_thread_create("thread1",
        thread1_entry, RT_NULL, /* 线程入口是thread1_entry, 入口参数是RT_NULL */
        THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    /* 创建线程2 */
    tid2 = rt_thread_create("thread2",
        thread2_entry, RT_NULL, /* 线程入口是thread2_entry, 入口参数是RT_NULL */
        THREAD_STACK_SIZE, THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return 0;
}

#else
    #warning "请在rtconfig.h中定义RT_USING_SUSPEND_NESTING以开启该功能"
#endif
