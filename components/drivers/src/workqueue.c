/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-02-27     bernard      fix the re-work issue.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_HEAP

static void _delayed_work_timeout_handler(void *parameter);

rt_inline rt_err_t _workqueue_work_completion(struct rt_workqueue *queue)
{
    rt_err_t result;

    rt_enter_critical();
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
    rt_exit_critical();

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
        if (rt_list_isempty(&(queue->work_list)))
        {
            /* no software timer exist, suspend self. */
            rt_thread_suspend(rt_thread_self());
            rt_schedule();
        }

        /* we have work to do with. */
        level = rt_hw_interrupt_disable();
        work = rt_list_entry(queue->work_list.next, struct rt_work, list);
        rt_list_remove(&(work->list));
        queue->work_current = work;
        work->flags &= ~RT_WORK_STATE_PENDING;
        rt_hw_interrupt_enable(level);

        /* do work */
        work->work_func(work, work->work_data);
        level = rt_hw_interrupt_disable();
        /* clean current work */
        queue->work_current = RT_NULL;
        rt_hw_interrupt_enable(level);

        /* ack work completion */
        _workqueue_work_completion(queue);
    }
}

static rt_err_t _workqueue_submit_work(struct rt_workqueue *queue, struct rt_work *work)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    if (work->flags & RT_WORK_STATE_PENDING)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }

    if (queue->work_current == work)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }

    /* NOTE: the work MUST be initialized firstly */
    rt_list_remove(&(work->list));

    rt_list_insert_after(queue->work_list.prev, &(work->list));
    work->flags |= RT_WORK_STATE_PENDING;

    /* whether the workqueue is doing work */
    if (queue->work_current == RT_NULL)
    {
        rt_hw_interrupt_enable(level);
        /* resume work thread */
        rt_thread_resume(queue->work_thread);
        rt_schedule();
    }
    else
    {
        rt_hw_interrupt_enable(level);
    }

    return RT_EOK;
}

static rt_err_t _workqueue_cancel_work(struct rt_workqueue *queue, struct rt_work *work)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    if (queue->work_current == work)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }
    rt_list_remove(&(work->list));
    work->flags &= ~RT_WORK_STATE_PENDING;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t _workqueue_cancel_delayed_work(struct rt_delayed_work *work)
{
    rt_base_t level;
    int ret = RT_EOK;

    if (!work->workqueue)
    {
        ret = -EINVAL;
        goto __exit;
    }

    if (work->work.flags & RT_WORK_STATE_PENDING)
    {
        /* Remove from the queue if already submitted */
        ret = rt_workqueue_cancel_work(work->workqueue, &(work->work));
        if (ret)
        {
            goto __exit;
        }
    }
    else
    {
        if (work->work.flags & RT_WORK_STATE_SUBMITTING)
        {
            level = rt_hw_interrupt_disable();
            rt_timer_stop(&(work->timer));
            rt_timer_detach(&(work->timer));
            work->work.flags &= ~RT_WORK_STATE_SUBMITTING;
            rt_hw_interrupt_enable(level);
        }
    }

    level = rt_hw_interrupt_disable();
    /* Detach from workqueue */
    work->workqueue = RT_NULL;
    work->work.flags &= ~(RT_WORK_STATE_PENDING);
    rt_hw_interrupt_enable(level);

__exit:
    return ret;
}

static rt_err_t _workqueue_submit_delayed_work(struct rt_workqueue *queue,
        struct rt_delayed_work *work, rt_tick_t ticks)
{
    rt_base_t level;
    int ret = RT_EOK;


    /* Work cannot be active in multiple queues */
    if (work->workqueue && work->workqueue != queue)
    {
        ret = -RT_EINVAL;
        goto __exit;
    }

    /* Cancel if work has been submitted */
    if (work->workqueue == queue)
    {
        ret = _workqueue_cancel_delayed_work(work);
        if (ret < 0)
        {
            goto __exit;
        }
    }

    level = rt_hw_interrupt_disable();
    /* Attach workqueue so the timeout callback can submit it */
    work->workqueue = queue;
    rt_hw_interrupt_enable(level);

    if (!ticks)
    {
        /* Submit work if no ticks is 0 */
        _workqueue_submit_work(work->workqueue, &(work->work));
    }
    else
    {
        level = rt_hw_interrupt_disable();
        /* Add timeout */
        work->work.flags |= RT_WORK_STATE_SUBMITTING;
        rt_timer_init(&(work->timer), "work", _delayed_work_timeout_handler, work, ticks,
                      RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER);
        rt_hw_interrupt_enable(level);
        rt_timer_start(&(work->timer));
    }

__exit:
    return ret;
}

static void _delayed_work_timeout_handler(void *parameter)
{
    struct rt_delayed_work *delayed_work;
    rt_base_t level;

    delayed_work = (struct rt_delayed_work *)parameter;
    level = rt_hw_interrupt_disable();
    rt_timer_stop(&(delayed_work->timer));
    rt_timer_detach(&(delayed_work->timer));
    delayed_work->work.flags &= ~RT_WORK_STATE_SUBMITTING;
    rt_hw_interrupt_enable(level);
    _workqueue_submit_work(delayed_work->workqueue, &(delayed_work->work));
}

struct rt_workqueue *rt_workqueue_create(const char *name, rt_uint16_t stack_size, rt_uint8_t priority)
{
    struct rt_workqueue *queue = RT_NULL;

    queue = (struct rt_workqueue *)RT_KERNEL_MALLOC(sizeof(struct rt_workqueue));
    if (queue != RT_NULL)
    {
        /* initialize work list */
        rt_list_init(&(queue->work_list));
        queue->work_current = RT_NULL;
        rt_sem_init(&(queue->sem), "wqueue", 0, RT_IPC_FLAG_FIFO);

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

rt_err_t rt_workqueue_destroy(struct rt_workqueue *queue)
{
    RT_ASSERT(queue != RT_NULL);

    rt_thread_delete(queue->work_thread);
    RT_KERNEL_FREE(queue);

    return RT_EOK;
}

rt_err_t rt_workqueue_dowork(struct rt_workqueue *queue, struct rt_work *work)
{
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);

    return _workqueue_submit_work(queue, work);
}

rt_err_t rt_workqueue_submit_work(struct rt_workqueue *queue, struct rt_work *work, rt_tick_t time)
{
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);

    if (work->type & RT_WORK_TYPE_DELAYED)
    {
        return _workqueue_submit_delayed_work(queue, (struct rt_delayed_work *)work, time);
    }
    else
    {
        return _workqueue_submit_work(queue, work);
    }
}

rt_err_t rt_workqueue_critical_work(struct rt_workqueue *queue, struct rt_work *work)
{
    rt_base_t level;
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);

    level = rt_hw_interrupt_disable();
    if (queue->work_current == work)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }

    /* NOTE: the work MUST be initialized firstly */
    rt_list_remove(&(work->list));

    rt_list_insert_after(queue->work_list.prev, &(work->list));
    if (queue->work_current == RT_NULL)
    {
        rt_hw_interrupt_enable(level);
        /* resume work thread */
        rt_thread_resume(queue->work_thread);
        rt_schedule();
    }
    else rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t rt_workqueue_cancel_work(struct rt_workqueue *queue, struct rt_work *work)
{
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);

    if (work->type & RT_WORK_TYPE_DELAYED)
    {
        return _workqueue_cancel_delayed_work((struct rt_delayed_work *)work);
    }
    else
    {
        return _workqueue_cancel_work(queue, work);
    }
}

rt_err_t rt_workqueue_cancel_work_sync(struct rt_workqueue *queue, struct rt_work *work)
{
    rt_base_t level;

    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);

    level = rt_hw_interrupt_disable();
    if (queue->work_current == work) /* it's current work in the queue */
    {
        /* wait for work completion */
        rt_sem_take(&(queue->sem), RT_WAITING_FOREVER);
    }
    else
    {
        rt_list_remove(&(work->list));
    }
    work->flags &= ~RT_WORK_STATE_PENDING;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t rt_workqueue_cancel_all_work(struct rt_workqueue *queue)
{
    struct rt_list_node *node, *next;
    RT_ASSERT(queue != RT_NULL);

    rt_enter_critical();
    for (node = queue->work_list.next; node != &(queue->work_list); node = next)
    {
        next = node->next;
        rt_list_remove(node);
    }
    rt_exit_critical();

    return RT_EOK;
}

void rt_delayed_work_init(struct rt_delayed_work *work, void (*work_func)(struct rt_work *work,
                          void *work_data), void *work_data)
{
    rt_work_init(&(work->work), work_func, work_data);
    work->work.type = RT_WORK_TYPE_DELAYED;
}

#ifdef RT_USING_SYSTEM_WORKQUEUE
static struct rt_workqueue *sys_workq;

rt_err_t rt_work_submit(struct rt_work *work, rt_tick_t time)
{
    return rt_workqueue_submit_work(sys_workq, work, time);
}

rt_err_t rt_work_cancel(struct rt_work *work)
{
    return rt_workqueue_cancel_work(sys_workq, work);
}

static int rt_work_sys_workqueue_init(void)
{
    sys_workq = rt_workqueue_create("sys_work", RT_SYSTEM_WORKQUEUE_STACKSIZE,
                                    RT_SYSTEM_WORKQUEUE_PRIORITY);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_work_sys_workqueue_init);
#endif
#endif
