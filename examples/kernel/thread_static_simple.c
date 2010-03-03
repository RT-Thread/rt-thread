#include <rtthread.h>
#include "tc_comm.h"

/*
 * This is an example for static thread
 */
static struct rt_thread thread1;
static struct rt_thread thread2;
static char thread1_stack[THREAD_STACK_SIZE];
static char thread2_stack[THREAD_STACK_SIZE];

static void thread_entry(void* parameter)
{
	rt_uint32_t count = 0;
	rt_uint32_t no = (rt_uint32_t) parameter;

	while (1)
	{
		rt_kprintf("thread%d count: %d\n", no, count ++);
		rt_thread_delay(10);
	}
}

rt_err_t thread_static_simple_init()
{
	rt_err_t result;

	result = rt_thread_init(&thread1,
		"t1",
		thread_entry, (void*)1,
		&thread1_stack[0], sizeof(thread1_stack),
		THREAD_PRIORITY, 10);
	if (result == RT_EOK)
		rt_thread_startup(&thread1);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	result = rt_thread_init(&thread2,
		"t2",
		thread_entry, (void*)2,
		&thread2_stack[0], sizeof(thread2_stack),
		THREAD_PRIORITY + 1, 10);
	if (result == RT_EOK)
		rt_thread_startup(&thread2);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	return result;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
	/* lock scheduler */
	rt_enter_critical();

	if (thread1.stat != RT_THREAD_CLOSE)
		rt_thread_detach(&thread1);
	if (thread2.stat != RT_THREAD_CLOSE)
		rt_thread_detach(&thread2);

	/* unlock scheduler */
	rt_exit_critical();
}

int _tc_thread_static_simple()
{
	/* set tc cleanup */
	tc_cleanup(_tc_cleanup);
	thread_static_simple_init();

	return 20;
}
FINSH_FUNCTION_EXPORT(_tc_thread_static_simple, a static thread example);
#else
int rt_application_init()
{
	thread_static_simple_init();

	return 0;
}
#endif

