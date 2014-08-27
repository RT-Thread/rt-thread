#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_HEAP
static void _workqueue_thread_entry(void* parameter)
{
	struct rt_work* work;
	struct rt_workqueue* queue;
	
	queue = (struct rt_workqueue*) parameter;
	RT_ASSERT(queue != RT_NULL);

	while (1)
	{
		if (rt_list_isempty(&(queue->work_list)))
		{
			/* no software timer exist, suspend self. */
			rt_thread_suspend(rt_thread_self());
			rt_schedule();
		}

		/* we have work to do with. */
		rt_enter_critical();
		work = rt_list_entry(queue->work_list.next, struct rt_work, list);
		rt_list_remove(&(work->list));
		rt_exit_critical();

		/* do work */
		work->work_func(work, work->work_data);
	}
}

struct rt_workqueue *rt_workqueue_create(const char* name, rt_uint16_t stack_size, rt_uint8_t priority)
{
	struct rt_workqueue *queue = RT_NULL;

	queue = (struct rt_workqueue*)RT_KERNEL_MALLOC(sizeof(struct rt_workqueue));
	if (queue != RT_NULL)
	{
        /* initialize work list */
        rt_list_init(&(queue->work_list));
        
		/* create the work thread */
		queue->work_thread = rt_thread_create(name, _workqueue_thread_entry, queue, stack_size, priority, 10);
		if (queue->work_thread == RT_NULL)
		{
			RT_KERNEL_FREE(queue);
			return RT_NULL;
		}

		rt_thread_startup(queue->work_thread);
	}

	return queue;
}

rt_err_t rt_workqueue_destroy(struct rt_workqueue* queue)
{
	RT_ASSERT(queue != RT_NULL);

	rt_thread_delete(queue->work_thread);
	RT_KERNEL_FREE(queue);

	return RT_EOK;
}

rt_err_t rt_workqueue_dowork(struct rt_workqueue* queue, struct rt_work* work)
{
	RT_ASSERT(queue != RT_NULL);
	RT_ASSERT(work != RT_NULL);

	rt_enter_critical();
	/* NOTE: the work MUST be initialized firstly */
	rt_list_remove(&(work->list));

	rt_list_insert_after(queue->work_list.prev, &(work->list));
	if (queue->work_thread->stat != RT_THREAD_READY)
	{
		rt_exit_critical();
		/* resume work thread */
		rt_thread_resume(queue->work_thread);
		rt_schedule();
	}
	else rt_exit_critical();

	return RT_EOK;
}

rt_err_t rt_workqueue_cancel_work(struct rt_workqueue* queue, struct rt_work* work)
{
	RT_ASSERT(queue != RT_NULL);
	RT_ASSERT(work != RT_NULL);

	rt_enter_critical();
	rt_list_remove(&(work->list));
	rt_exit_critical();

	return RT_EOK;
}

#endif

