/*
 * 程序清单：定时器例程
 *
 * 这个程序会初始化2个静态定时器，一个是一次定时，一个是周期性的定时
 */
#include <rtthread.h>
#include "tc_comm.h"

/* 定时器的控制块 */
struct rt_timer timer1;
struct rt_timer timer2;

/* 定时器1超时函数 */
void timeout1(void* parameter)
{
	rt_kprintf("periodic timer is timeout\n");
}

/* 定时器2超时函数 */
void timeout2(void* parameter)
{
	rt_kprintf("one shot timer is timeout\n");
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
	/* 调度器上锁，上锁后，将不再切换到其他线程，仅响应中断 */
	rt_enter_critical();

	/* 执行定时器脱离 */
	rt_timer_detach(&timer1);
	rt_timer_detach(&timer2);

	/* 调度器解锁 */
	rt_exit_critical();

	/* 设置TestCase状态 */
	tc_done(TC_STAT_PASSED);
}

int _tc_thread_timer_simple()
{
	/* 设置TestCase清理回调函数 */
	tc_cleanup(_tc_cleanup);

	rt_timer_init(&timer1, "timer1", timeout1, RT_NULL, 10, RT_TIMER_FLAG_PERIODIC);
	rt_timer_init(&timer2, "timer2", timeout2, RT_NULL, 30, RT_TIMER_FLAG_ONE_SHOT);

	rt_timer_start(&timer1);
	rt_timer_start(&timer2);

	/* 返回TestCase运行的最长时间 */
	return 100;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_thread_timer_simple, a simple timer example);
#else
/* 用户应用入口 */
int rt_application_init()
{
	_tc_thread_timer_simple();

	return 0;
}
#endif
