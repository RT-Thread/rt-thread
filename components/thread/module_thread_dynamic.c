#include <rtthread.h>

static void thread_entry(void* parameter)
{
	rt_kprintf("thread dynamicly created ok\n");
	rt_thread_delay(10);
	rt_kprintf("thread exit\n");
}

int rtm_main()
{
	rt_thread_t tid;

	tid = rt_thread_create("test",
		thread_entry, RT_NULL,
		THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (tid != RT_NULL)
		rt_thread_startup(tid);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	return 0;
}