#include <rtthread.h>
#include "tc_comm.h"

static rt_sem_t sem;
static rt_thread_t t1, worker;

#define BUFFER_SIZE		256
#define DATA_ITEM_SIZE	32

static rt_uint8_t working_buffer[BUFFER_SIZE];
static rt_uint16_t write_index, read_index;

static void thread1_entry(void* parameter)
{
	rt_err_t result;
	rt_uint16_t next_index;
	rt_uint8_t data[DATA_ITEM_SIZE];

	while (1)
	{
		/* take a semaphore */
		result = rt_sem_take(sem, RT_WAITING_FOREVER);
		if (result != RT_EOK)
		{
			tc_done(TC_STAT_FAILED);
			return;
		}

		/* read buffer */

		/* release semaphore */
		rt_sem_release(sem);
	}
}

static void worker_thread_entry(void* parameter)
{
	rt_err_t result;
	rt_uint16_t next_index;
	rt_uint8_t data[DATA_ITEM_SIZE];

	while (1)
	{
		/* take a semaphore */
		result = rt_sem_take(sem, RT_WAITING_FOREVER);
		if (result != RT_EOK)
		{
			tc_done(TC_STAT_FAILED);
			return;
		}

		/* write buffer */

		/* release semaphore */
		rt_sem_release(sem);
	}
}

int semaphore_buffer_worker_init()
{
	sem = rt_sem_create("sem", 0, RT_IPC_FLAG_FIFO);
	if (sem == RT_NULL)
	{
		tc_stat(TC_STAT_END | TC_STAT_FAILED);
		return 0;
	}

	write_index = read_index = 0;

	t1 = rt_thread_create("t1",
		thread1_entry, RT_NULL,
		THREAD_STACK_SIZE, THREAD_PRIORITY + 1, THREAD_TIMESLICE);
	if (t1 != RT_NULL)
		rt_thread_startup(t1);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	worker = rt_thread_create("worker",
		worker_thread_entry, RT_NULL,
		THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (worker != RT_NULL)
		rt_thread_startup(worker);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	return 0;
}

#ifdef RT_USING_TC
static void _tc_cleanup()
{
	/* lock scheduler */
	rt_enter_critical();

	/* delete t1, t2 and worker thread */
	rt_thread_delete(t1);
	rt_thread_delete(worker);

	tc_stat(TC_STAT_PASSED);

	/* unlock scheduler */
	rt_exit_critical();
}

int _tc_semaphore_buffer_worker()
{
	/* set tc cleanup */
	tc_cleanup(_tc_cleanup);
	semaphore_buffer_worker_init();

	return 50;
}
FINSH_FUNCTION_EXPORT(_tc_semaphore_buffer_worker, two threads working on a buffer example);
#else
int rt_application_init()
{
	semaphore_buffer_worker_init();

	return 0;
}
#endif
