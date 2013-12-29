/*
 * 程序清单：静态信号量
 *
 * 这个例子中将创建一个静态信号量（初始值为0 ）及一个静态线程，在这个静态线程中
 * 将试图采用超时方式去持有信号量，应该超时返回。然后这个线程释放一次信号量，并
 * 在后面继续采用永久等待方式去持有信号量， 成功获得信号量后返回。
 */
#include <rtthread.h>
#include "tc_comm.h"

/* 线程控制块及栈 */
static struct rt_thread thread;
static rt_uint8_t thread_stack[THREAD_STACK_SIZE];
/* 信号量控制块 */
static struct rt_semaphore sem;

/* 线程入口 */
static void thread_entry(void* parameter)
{
    rt_err_t result;
    rt_tick_t tick;

    /* 获得当前的OS Tick */
    tick = rt_tick_get();

    /* 试图持有信号量，最大等待10个OS Tick后返回 */
    result = rt_sem_take(&sem, 10);
    if (result == -RT_ETIMEOUT)
    {
        rt_tick_t new_tick = rt_tick_get();
        /* 可以有两个 tick 的误差 */
        if (new_tick - tick >= 12)
        {
            rt_kprintf("tick error to large: expect: 10, get %d\n",
                       new_tick - tick);

            tc_done(TC_STAT_FAILED);
            rt_sem_detach(&sem);
            return;
        }
        rt_kprintf("take semaphore timeout\n");
    }
    else
    {
        /* 因为没有其他地方是否信号量，所以不应该成功持有信号量，否则测试失败 */
        tc_done(TC_STAT_FAILED);
        rt_sem_detach(&sem);
        return;
    }

    /* 释放一次信号量 */
    rt_sem_release(&sem);

    /* 永久等待方式持有信号量 */
    result = rt_sem_take(&sem, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        /* 不成功则测试失败 */
        tc_done(TC_STAT_FAILED);
        rt_sem_detach(&sem);
        return;
    }

    /* 测试通过 */
    tc_done(TC_STAT_PASSED);
    /* 脱离信号量对象 */
    rt_sem_detach(&sem);
}

int semaphore_static_init(void)
{
    rt_err_t result;

    /* 初始化信号量，初始值是0 */
    result = rt_sem_init(&sem, "sem", 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        tc_stat(TC_STAT_END | TC_STAT_FAILED);
        return 0;
    }

    /* 初始化线程1 */
    result = rt_thread_init(&thread, "thread", /* 线程名：thread */
                            thread_entry, RT_NULL, /* 线程的入口是thread_entry，入口参数是RT_NULL*/
                            &thread_stack[0], sizeof(thread_stack), /* 线程栈是thread_stack */
                            THREAD_PRIORITY, 10);
    if (result == RT_EOK) /* 如果返回正确，启动线程1 */
        rt_thread_startup(&thread);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup(void)
{
    /* 调度器上锁，上锁后，将不再切换到其他线程，仅响应中断 */
    rt_enter_critical();

    /* 执行线程脱离 */
    if (thread.stat != RT_THREAD_CLOSE)
    {
        rt_thread_detach(&thread);

        /* 执行信号量对象脱离 */
        rt_sem_detach(&sem);
    }

    /* 调度器解锁 */
    rt_exit_critical();

    /* 设置TestCase状态 */
    tc_done(TC_STAT_PASSED);
}

int _tc_semaphore_static(void)
{
    /* 设置TestCase清理回调函数 */
    tc_cleanup(_tc_cleanup);
    semaphore_static_init();

    /* 返回TestCase运行的最长时间 */
    return 100;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_semaphore_static, a static semaphore example);
#else
/* 用户应用入口 */
int rt_application_init(void)
{
    semaphore_static_init();

    return 0;
}
#endif
