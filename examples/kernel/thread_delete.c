#include <rtthread.h>
#include "tc_comm.h"

/*
 * This is an example for dynamic thread
 */
static rt_thread_t tid1 = RT_NULL, tid2 = RT_NULL;
static void thread1_entry(void* parameter)
{
	rt_uint32_t count = 0;

	while (1)
	{
		rt_kprintf("thread count: %d\n", count ++);
	}
}

static void thread2_entry(void* parameter)
{
	rt_thread_delay(10);
	rt_thread_delete(tid1);

	/* delay thread2 to switch to idle thread */
	rt_thread_delay(10);
}

int thread_delete_init()
{
	tid1 = rt_thread_create("t1",
		thread1_entry, (void*)1,
		THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (tid1 != RT_NULL)
		rt_thread_startup(tid1);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	tid2 = rt_thread_create("t2",
		thread2_entry, (void*)2,
		THREAD_STACK_SIZE, THREAD_PRIORITY - 1, THREAD_TIMESLICE);
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
		tc_stat(TC_STAT_FAILED);
	if (tid2 != RT_NULL && tid2->stat != RT_THREAD_CLOSE)
		tc_stat(TC_STAT_FAILED);

	/* unlock scheduler */
	rt_exit_critical();
}

int _tc_thread_delete()
{
	/* set tc cleanup */
	tc_cleanup(_tc_cleanup);
	thread_delete_init();

	return 100;
}
FINSH_FUNCTION_EXPORT(_tc_thread_delete, a thread delete example);
#else
int rt_application_init()
{
	thread_delete_init();

	return 0;
}
#endif
