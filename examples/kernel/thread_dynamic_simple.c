#include <rtthread.h>
#include "tc_comm.h"

/*
 * This is an example for dynamic thread
 */
static rt_thread_t tid1 = RT_NULL, tid2 = RT_NULL;
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

int thread_dynamic_simple_init()
{
	tid1 = rt_thread_create("t1",
		thread_entry, (void*)1,
		THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (tid1 != RT_NULL)
		rt_thread_startup(tid1);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	tid2 = rt_thread_create("t2",
		thread_entry, (void*)2,
		THREAD_STACK_SIZE, THREAD_PRIORITY + 1, THREAD_TIMESLICE);
	if (tid2 != RT_NULL)
		rt_thread_startup(tid2);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
	/* lock scheduler */
	rt_enter_critical();

	/* delete thread */
	if (tid1 != RT_NULL && tid1->stat != RT_THREAD_CLOSE)
		rt_thread_delete(tid1);
	if (tid2 != RT_NULL && tid2->stat != RT_THREAD_CLOSE)
		rt_thread_delete(tid2);

	/* unlock scheduler */
	rt_exit_critical();

	tc_done(TC_STAT_PASSED);
}

int _tc_thread_dynamic_simple()
{
	/* set tc cleanup */
	tc_cleanup(_tc_cleanup);
	thread_dynamic_simple_init();

	return 100;
}
FINSH_FUNCTION_EXPORT(_tc_thread_dynamic_simple, a dynamic thread example);
#else
int rt_application_init()
{
	thread_dynamic_simple_init();

	return 0;
}
#endif
