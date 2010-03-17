#include <rtthread.h>
#include "tc_comm.h"

static struct rt_semaphore sem;
struct rt_thread thread;
static char thread_stack[THREAD_STACK_SIZE];
static void thread_entry(void* parameter)
{
	rt_err_t result;
	rt_tick_t tick;

	/* get current tick */
	tick = rt_tick_get();

	/* take a semaphore for 10 OS Tick */
	result = rt_sem_take(&sem, 10);
	if (result == -RT_ETIMEOUT)
	{
		if (rt_tick_get() - tick != 10)
		{
			tc_done(TC_STAT_FAILED);
			rt_sem_detach(&sem);
			return;
		}
		rt_kprintf("take semaphore timeout");
	}
	else
	{
		tc_done(TC_STAT_FAILED);
		rt_sem_detach(&sem);
		return;
	}

	/* release semaphore one time */
	rt_sem_release(&sem);

	result = rt_sem_take(&sem, RT_WAITING_FOREVER);
	if (result != RT_EOK)
	{
		tc_done(TC_STAT_FAILED);
		rt_sem_detach(&sem);
		return;
	}

	/* testcase passed */
	tc_done(TC_STAT_PASSED);
	/* detach semaphore */
	rt_sem_detach(&sem);
}

int semaphore_static_init()
{
	rt_err_t result;

	result = rt_sem_init(&sem, "sem", 0, RT_IPC_FLAG_FIFO);
	if (result != RT_EOK)
	{
		tc_stat(TC_STAT_END | TC_STAT_FAILED);
		return 0;
	}

	result = rt_thread_init(&thread, "test",
		thread_entry, RT_NULL,
		thread_stack, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (result == RT_EOK)
		rt_thread_startup(&thread);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
	/* lock scheduler */
	rt_enter_critical();

	if (thread.stat != RT_THREAD_CLOSE)
		rt_thread_detach(&thread);

	/* unlock scheduler */
	rt_exit_critical();
}

int _tc_semaphore_static()
{
	/* set tc cleanup */
	tc_cleanup(_tc_cleanup);
	semaphore_static_init();

	return 30;
}
FINSH_FUNCTION_EXPORT(_tc_semaphore_static, a static semaphore test);
#else
int rt_application_init()
{
	semaphore_static_init();

	return 0;
}
#endif
