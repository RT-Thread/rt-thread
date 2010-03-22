/*
 * 程序清单：动态线程
 *
 * 这个程序会初始化2个动态线程，它们拥有共同的入口函数，但参数不相同
 */
#include <rtthread.h>
#include "tc_comm.h"

/* 指向线程控制块的指针 */
static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;
static rt_thread_t tid3 = RT_NULL;

static struct rt_messagequeue mq;
static char msg_pool[2048];

static void thread1_entry(void* parameter)
{
	char buf[128];

	while (1)
	{
		rt_memset(&buf[0], 0, sizeof(buf));

		if (rt_mq_recv(&mq, &buf[0], sizeof(buf), RT_WAITING_FOREVER) == RT_EOK)
		{
			rt_kprintf("thread1: recv msg from message queue, the content:%s\n", buf);
		}

		rt_thread_delay(100);
	}
}

static void thread2_entry(void* parameter)
{
	int i, result;
	char buf[] = "this is message No.x";

	while (1)
	{
		for (i = 0; i < 10; i++)
		{
			buf[sizeof(buf) - 2] = '0' + i;

			rt_kprintf("thread2: send message - %s\n", buf);
			result = rt_mq_send(&mq, &buf[0], sizeof(buf));
			if ( result == -RT_EFULL);
			{
				rt_kprintf("message queue full, delay 10s\n");
				rt_thread_delay(1000);
			}
		}

		rt_thread_delay(100);
	}
}

static void thread3_entry(void* parameter)
{
	char buf[] = "this is an urgent message!";

	while (1)
	{
		rt_kprintf("thread3: send an urgent message\n");
		rt_mq_urgent(&mq, &buf[0], sizeof(buf));

		rt_thread_delay(250);
	}
}

int messageq_simple_init()
{
	rt_mq_init(&mq, "mqt", &msg_pool[0], 128 - sizeof(void*), sizeof(msg_pool), RT_IPC_FLAG_FIFO);

	/* 创建线程1 */
	tid1 = rt_thread_create("t1",
		thread1_entry, RT_NULL, /* 线程入口是thread1_entry, 入口参数是RT_NULL */
		THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (tid1 != RT_NULL)
		rt_thread_startup(tid1);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	/* 创建线程2 */
	tid2 = rt_thread_create("t2",
		thread2_entry, RT_NULL, /* 线程入口是thread2_entry, 入口参数是RT_NULL */
		THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (tid2 != RT_NULL)
		rt_thread_startup(tid2);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	/* 创建线程3 */
	tid3 = rt_thread_create("t3",
		thread3_entry, RT_NULL, /* 线程入口是thread2_entry, 入口参数是RT_NULL */
		THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (tid3 != RT_NULL)
		rt_thread_startup(tid3);
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
	if (tid3 != RT_NULL && tid3->stat != RT_THREAD_CLOSE)
		rt_thread_delete(tid3);

	/* 执行消息队列脱离 */
	rt_mq_detach(&mq);

	/* 调度器解锁 */
	rt_exit_critical();

	/* 设置TestCase状态 */
	tc_done(TC_STAT_PASSED);
}

int _tc_messageq_simple()
{
	/* 设置TestCase清理回调函数 */
	tc_cleanup(_tc_cleanup);
	messageq_simple_init();

	/* 返回TestCase运行的最长时间 */
	return 100;
}
/* 输出函数命令到finsh shell中 */
FINSH_FUNCTION_EXPORT(_tc_messageq_simple, a simple message queue example);
#else
/* 用户应用入口 */
int rt_application_init()
{
	messageq_simple_init();

	return 0;
}
#endif
