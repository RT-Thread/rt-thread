/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-02-27     Bernard      fix the re-work issue.
 * 2021-08-01     Meco Man     remove rt_delayed_work_init()
 * 2021-08-14     Jackistang   add comments for function interface
 * 2022-01-16     Meco Man     add rt_work_urgent()
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 */

#include <rthw.h>
#include <rtdevice.h>

#ifdef RT_USING_HEAP

static void _delayed_work_timeout_handler(void *parameter);

rt_inline rt_err_t _workqueue_work_completion(struct rt_workqueue *queue)
{
    rt_err_t result;

    while (1)
    {
        /* try to take condition semaphore */
        result = rt_sem_trytake(&(queue->sem));
        if (result == -RT_ETIMEOUT)
        {
            /* it's timeout, release this semaphore */
            rt_sem_release(&(queue->sem));
        }
        else if (result == RT_EOK)
        {
            /* keep the sem value = 0 */
            result = RT_EOK;
            break;
        }
        else
        {
            result = -RT_ERROR;
            break;
        }
    }

    return result;
}

static void _workqueue_thread_entry(void *parameter)
{
    rt_base_t level;
    struct rt_work *work;
    struct rt_workqueue *queue;

    queue = (struct rt_workqueue *) parameter;
    RT_ASSERT(queue != RT_NULL);

    while (1)
    {
        level = rt_spin_lock_irqsave(&(queue->spinlock));
        if (rt_list_isempty(&(queue->work_list)))
        {
            /* no software timer exist, suspend self. */
            rt_thread_suspend_with_flag(rt_thread_self(), RT_UNINTERRUPTIBLE);
            rt_spin_unlock_irqrestore(&(queue->spinlock), level);
            rt_schedule();
            continue;
        }

        /* we have work to do with. */
        work = rt_list_entry(queue->work_list.next, struct rt_work, list);
        rt_list_remove(&(work->list));
        queue->work_current = work;
        work->flags &= ~RT_WORK_STATE_PENDING;
        work->workqueue = RT_NULL;
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);

        /* do work */
        work->work_func(work, work->work_data);
        /* clean current work */
        queue->work_current = RT_NULL;

        /* ack work completion */
        _workqueue_work_completion(queue);
    }
}

static rt_err_t _workqueue_submit_work(struct rt_workqueue *queue,
                                       struct rt_work *work, rt_tick_t ticks)
{
    rt_base_t level;

    level = rt_spin_lock_irqsave(&(queue->spinlock));

    /* remove list */
    rt_list_remove(&(work->list));
    work->flags &= ~RT_WORK_STATE_PENDING;

    if (ticks == 0)
    {
        rt_list_insert_after(queue->work_list.prev, &(work->list));
        work->flags |= RT_WORK_STATE_PENDING;
        work->workqueue = queue;

        /* whether the workqueue is doing work */
        if (queue->work_current == RT_NULL &&
                ((queue->work_thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK))
        {
            /* resume work thread */
            rt_thread_resume(queue->work_thread);
            rt_spin_unlock_irqrestore(&(queue->spinlock), level);
            rt_schedule();
        }
        else
        {
            rt_spin_unlock_irqrestore(&(queue->spinlock), level);
        }
        return RT_EOK;
    }
    else if (ticks < RT_TICK_MAX / 2)
    {
        /* Timer started */
        if (work->flags & RT_WORK_STATE_SUBMITTING)
        {
            rt_timer_stop(&work->timer);
            rt_timer_control(&work->timer, RT_TIMER_CTRL_SET_TIME, &ticks);
        }
        else
        {
            rt_timer_init(&(work->timer), "work", _delayed_work_timeout_handler,
                          work, ticks, RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER);
            work->flags |= RT_WORK_STATE_SUBMITTING;
        }
        work->workqueue = queue;
        /* insert delay work list */
        rt_list_insert_after(queue->delayed_list.prev, &(work->list));
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);
        rt_timer_start(&(work->timer));
        return RT_EOK;
    }
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);
    return -RT_ERROR;
}

static rt_err_t _workqueue_cancel_work(struct rt_workqueue *queue, struct rt_work *work)
{
    rt_base_t level;
    rt_err_t err;

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    rt_list_remove(&(work->list));
    work->flags &= ~RT_WORK_STATE_PENDING;
    /* Timer started */
    if (work->flags & RT_WORK_STATE_SUBMITTING)
    {
        rt_timer_stop(&(work->timer));
        rt_timer_detach(&(work->timer));
        work->flags &= ~RT_WORK_STATE_SUBMITTING;
    }
    err = queue->work_current != work ? RT_EOK : -RT_EBUSY;
    work->workqueue = RT_NULL;
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);
    return err;
}

static void _delayed_work_timeout_handler(void *parameter)
{
    struct rt_work *work;
    struct rt_workqueue *queue;
    rt_base_t level;

    work = (struct rt_work *)parameter;
    queue = work->workqueue;
    RT_ASSERT(queue != RT_NULL);

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    rt_timer_detach(&(work->timer));
    work->flags &= ~RT_WORK_STATE_SUBMITTING;
    /* remove delay list */
    rt_list_remove(&(work->list));
    /* insert work queue */
    if (queue->work_current != work)
    {
        rt_list_insert_after(queue->work_list.prev, &(work->list));
        work->flags |= RT_WORK_STATE_PENDING;
    }
    /* whether the workqueue is doing work */
    if (queue->work_current == RT_NULL &&
            ((queue->work_thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK))
    {
        /* resume work thread */
        rt_thread_resume(queue->work_thread);
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);
        rt_schedule();
    }
    else
    {
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);
    }
}

/**
 * @brief Initialize a work item, binding with a callback function.
 *
 * @param work is a pointer to the work item object.
 *
 * @param work_func is a callback function that will be called when this work item is executed.
 *
 * @param work_data is a user data passed to the callback function as the second parameter.
 */
void rt_work_init(struct rt_work *work,
                  void (*work_func)(struct rt_work *work, void *work_data),
                  void *work_data)
{
    RT_ASSERT(work != RT_NULL);
    RT_ASSERT(work_func != RT_NULL);

    rt_list_init(&(work->list));
    work->work_func = work_func;
    work->work_data = work_data;
    work->workqueue = RT_NULL;
    work->flags = 0;
    work->type = 0;
}

/**
 * @brief Create a work queue with a thread inside.
 *
 * @param name is a name of the work queue thread.
 *
 * @param stack_size is stack size of the work queue thread.
 *
 * @param priority is a priority of the work queue thread.
 *
 * @return Return a pointer to the workqueue object. It will return RT_NULL if failed.
 */
struct rt_workqueue *rt_workqueue_create(const char *name, rt_uint16_t stack_size, rt_uint8_t priority)
{
    struct rt_workqueue *queue = RT_NULL;

    queue = (struct rt_workqueue *)RT_KERNEL_MALLOC(sizeof(struct rt_workqueue));
    if (queue != RT_NULL)
    {
        /* initialize work list */
        rt_list_init(&(queue->work_list));
        rt_list_init(&(queue->delayed_list));
        queue->work_current = RT_NULL;
        rt_sem_init(&(queue->sem), "wqueue", 0, RT_IPC_FLAG_FIFO);

        /* create the work thread */
        queue->work_thread = rt_thread_create(name, _workqueue_thread_entry, queue, stack_size, priority, 10);
        if (queue->work_thread == RT_NULL)
        {
            RT_KERNEL_FREE(queue);
            return RT_NULL;
        }

        rt_spin_lock_init(&(queue->spinlock));
        rt_thread_startup(queue->work_thread);
    }

    return queue;
}

/**
 * @brief Destroy a work queue.
 *
 * @param queue is a pointer to the workqueue object.
 *
 * @return RT_EOK     Success.
 */
rt_err_t rt_workqueue_destroy(struct rt_workqueue *queue)
{
    RT_ASSERT(queue != RT_NULL);

    rt_workqueue_cancel_all_work(queue);
    rt_thread_delete(queue->work_thread);
    rt_sem_detach(&(queue->sem));
    RT_KERNEL_FREE(queue);

    return RT_EOK;
}

/**
 * @brief Submit a work item to the work queue without delay.
 *
 * @param queue is a pointer to the workqueue object.
 *
 * @param work is a pointer to the work item object.
 *
 * @return RT_EOK       Success.
 *         -RT_EBUSY    This work item is executing.
 */
rt_err_t rt_workqueue_dowork(struct rt_workqueue *queue, struct rt_work *work)
{
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);

    return _workqueue_submit_work(queue, work, 0);
}

/**
 * @brief Submit a work item to the work queue with a delay.
 *
 * @param queue is a pointer to the workqueue object.
 *
 * @param work is a pointer to the work item object.
 *
 * @param ticks is the delay ticks for the work item to be submitted to the work queue.
 *
 *             NOTE: The max timeout tick should be no more than (RT_TICK_MAX/2 - 1)
 *
 * @return RT_EOK       Success.
 *         -RT_EBUSY    This work item is executing.
 *         -RT_ERROR    The ticks parameter is invalid.
 */
rt_err_t rt_workqueue_submit_work(struct rt_workqueue *queue, struct rt_work *work, rt_tick_t ticks)
{
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);
    RT_ASSERT(ticks < RT_TICK_MAX / 2);

    return _workqueue_submit_work(queue, work, ticks);
}

/**
 * @brief Submit a work item to the work queue without delay. This work item will be executed after the current work item.
 *
 * @param queue is a pointer to the workqueue object.
 *
 * @param work is a pointer to the work item object.
 *
 * @return RT_EOK   Success.
 */
rt_err_t rt_workqueue_urgent_work(struct rt_workqueue *queue, struct rt_work *work)
{
    rt_base_t level;

    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    /* NOTE: the work MUST be initialized firstly */
    rt_list_remove(&(work->list));
    rt_list_insert_after(&queue->work_list, &(work->list));
    /* whether the workqueue is doing work */
    if (queue->work_current == RT_NULL &&
            ((queue->work_thread->stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK))
    {
        /* resume work thread */
        rt_thread_resume(queue->work_thread);
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);
        rt_schedule();
    }
    else
    {
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);
    }

    return RT_EOK;
}

/**
 * @brief Cancel a work item in the work queue.
 *
 * @param queue is a pointer to the workqueue object.
 *
 * @param work is a pointer to the work item object.
 *
 * @return RT_EOK       Success.
 *         -RT_EBUSY    This work item is executing.
 */
rt_err_t rt_workqueue_cancel_work(struct rt_workqueue *queue, struct rt_work *work)
{
    RT_ASSERT(work != RT_NULL);
    RT_ASSERT(queue != RT_NULL);

    return _workqueue_cancel_work(queue, work);
}

/**
 * @brief Cancel a work item in the work queue. If the work item is executing, this function will block until it is done.
 *
 * @param queue is a pointer to the workqueue object.
 *
 * @param work is a pointer to the work item object.
 *
 * @return RT_EOK       Success.
 */
rt_err_t rt_workqueue_cancel_work_sync(struct rt_workqueue *queue, struct rt_work *work)
{
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);

    if (queue->work_current == work) /* it's current work in the queue */
    {
        /* wait for work completion */
        rt_sem_take(&(queue->sem), RT_WAITING_FOREVER);
    }
    else
    {
        _workqueue_cancel_work(queue, work);
    }

    return RT_EOK;
}

/**
 * @brief This function will cancel all work items in work queue.
 *
 * @param queue is a pointer to the workqueue object.
 *
 * @return RT_EOK       Success.
 */
rt_err_t rt_workqueue_cancel_all_work(struct rt_workqueue *queue)
{
    struct rt_work *work;

    RT_ASSERT(queue != RT_NULL);

    /* cancel work */
    rt_enter_critical();
    while (rt_list_isempty(&queue->work_list) == RT_FALSE)
    {
        work = rt_list_first_entry(&queue->work_list, struct rt_work, list);
        _workqueue_cancel_work(queue, work);
    }
    /* cancel delay work */
    while (rt_list_isempty(&queue->delayed_list) == RT_FALSE)
    {
        work = rt_list_first_entry(&queue->delayed_list, struct rt_work, list);
        _workqueue_cancel_work(queue, work);
    }
    rt_exit_critical();

    return RT_EOK;
}

#ifdef RT_USING_SYSTEM_WORKQUEUE

static struct rt_workqueue *sys_workq; /* system work queue */

/**
 * @brief Submit a work item to the system work queue with a delay.
 *
 * @param work is a pointer to the work item object.
 *
 * @param ticks is the delay OS ticks for the work item to be submitted to the work queue.
 *
 *             NOTE: The max timeout tick should be no more than (RT_TICK_MAX/2 - 1)
 *
 * @return RT_EOK       Success.
 *         -RT_EBUSY    This work item is executing.
 *         -RT_ERROR    The ticks parameter is invalid.
 */
rt_err_t rt_work_submit(struct rt_work *work, rt_tick_t ticks)
{
    return rt_workqueue_submit_work(sys_workq, work, ticks);
}

/**
 * @brief Submit a work item to the system work queue without delay. This work item will be executed after the current work item.
 *
 * @param work is a pointer to the work item object.
 *
 * @return RT_EOK   Success.
 */
rt_err_t rt_work_urgent(struct rt_work *work)
{
    return rt_workqueue_urgent_work(sys_workq, work);
}

/**
 * @brief Cancel a work item in the system work queue.
 *
 * @param work is a pointer to the work item object.
 *
 * @return RT_EOK       Success.
 *         -RT_EBUSY    This work item is executing.
 */
rt_err_t rt_work_cancel(struct rt_work *work)
{
    return rt_workqueue_cancel_work(sys_workq, work);
}

static int rt_work_sys_workqueue_init(void)
{
    if (sys_workq != RT_NULL)
        return RT_EOK;

    sys_workq = rt_workqueue_create("sys workq", RT_SYSTEM_WORKQUEUE_STACKSIZE,
                                    RT_SYSTEM_WORKQUEUE_PRIORITY);
    RT_ASSERT(sys_workq != RT_NULL);

    return RT_EOK;
}
INIT_PREV_EXPORT(rt_work_sys_workqueue_init);
#endif /* RT_USING_SYSTEM_WORKQUEUE */
#endif /* RT_USING_HEAP */
