#include <rtthread.h>
#include "tc_comm.h"

static rt_sem_t sem;
static void thread_entry(void* parameter)
{
	rt_err_t result;
	rt_tick_t tick;

	/* get current tick */
	tick = rt_tick_get();

	/* take a semaphore for 10 OS Tick */
	result = rt_sem_take(sem, 10);
	if (result == -RT_ETIMEOUT)
	{
		if (rt_tick_get() - tick != 10)
		{
			tc_done(TC_STAT_FAILED);
			rt_sem_delete(sem);
			return;
		}
		rt_kprintf("take semaphore timeout");
	}
	else
	{
		tc_done(TC_STAT_FAILED);
		rt_sem_delete(sem);
		return;
	}

	/* release semaphore one time */
	rt_sem_release(sem);

	result = rt_sem_take(sem, RT_WAITING_FOREVER);
	if (result != RT_EOK)
	{
		tc_done(TC_STAT_FAILED);
		rt_sem_delete(sem);
		return;
	}

	/* testcase passed */
	tc_done(TC_STAT_PASSED);
	/* delete semaphore */
	rt_sem_delete(sem);
}

int semaphore_dynamic_init()
{
	rt_thread_t tid;

	sem = rt_sem_create("sem", 0, RT_IPC_FLAG_FIFO);
	if (sem == RT_NULL)
	{
		tc_stat(TC_STAT_END | TC_STAT_FAILED);
		return 0;
	}

	tid = rt_thread_create("test",
		thread_entry, RT_NULL,
		THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (tid != RT_NULL)
		rt_thread_startup(tid);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	return 0;
}

#ifdef RT_USING_TC
int _tc_semaphore_dynamic()
{
	semaphore_dynamic_init();

	return 30;
}
FINSH_FUNCTION_EXPORT(_tc_semaphore_dynamic, a dynamic semaphore test);
#else
int rt_application_init()
{
	semaphore_dynamic_init();

	return 0;
}
#endif
