/*
 * 程序清单：动态定时器例程
 *
 * 这个例程会创建1个动态周期型定时器对象，然后控制它进行定时时间长度的更改。
 */
#include <rtthread.h>
#include "tc_comm.h"

/* 定时器的控制块 */
static rt_timer_t timer1;
static rt_uint8_t count;

/* 定时器超时函数 */
static void timeout1(void* parameter)
{
    rt_tick_t timeout = 50;
    
    rt_kprintf("periodic timer is timeout\n");

    count ++;
    /* 停止定时器自身 */
    if (count >= 8)
    {
        /* 控制定时器然后更改超时时间长度 */
        rt_timer_control(timer1, RT_TIMER_CTRL_SET_TIME, (void *)&timeout);
        count = 0;
    }
}

void timer_control_init()
{
    /* 创建定时器1 */
    timer1 = rt_timer_create("timer1",  /* 定时器名字是 timer1 */
        timeout1, /* 超时时回调的处理函数 */
        RT_NULL, /* 超时函数的入口参数 */
        10, /* 定时长度，以OS Tick为单位，即10个OS Tick */
        RT_TIMER_FLAG_PERIODIC); /* 周期性定时器 */
    /* 启动定时器 */
    if (timer1 != RT_NULL)
        rt_timer_start(timer1);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
    /* 调度器上锁，上锁后，将不再切换到其他线程，仅响应中断 */
    rt_enter_critical();

    /* 删除定时器对象 */
    rt_timer_delete(timer1);
    timer1 = RT_NULL;

    /* 调度器解锁 */
    rt_exit_critical();

    /* 设置TestCase状态 */
    tc_done(TC_STAT_PASSED);
}

int _tc_timer_control()
{
    /* 设置TestCase清理回调函数 */
    tc_cleanup(_tc_cleanup);

    /* 执行定时器例程 */
    count = 0;
    timer_control_init();

    /* 返回TestCase运行的最长时间 */
    return 100;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_timer_control, a timer control example);
#else
/* 用户应用入口 */
int rt_application_init()
{
    timer_control_init();

    return 0;
}
#endif
