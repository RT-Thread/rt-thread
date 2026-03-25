/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
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
 * 2024-12-21     yuqingli     delete timer, using list
 * 2026-03-21     RyanCW       refine sync semantics and hot paths
 */

#include <rthw.h>
#include <rtdevice.h>

#ifdef RT_USING_HEAP

/* Queue idle means no running work and no pending work. */
rt_inline rt_bool_t _workqueue_is_idle_nolock(struct rt_workqueue *queue)
{
    return (queue->work_current == RT_NULL &&
            rt_list_isempty(&(queue->work_list)));
}

/* Move all nodes from src to dst. Caller keeps dst initialized. */
static void _workqueue_move_list_nolock(rt_list_t *dst, rt_list_t *src)
{
    if (rt_list_isempty(src))
    {
        return;
    }

    dst->next = src->next;
    dst->prev = src->prev;
    dst->next->prev = dst;
    dst->prev->next = dst;
    rt_list_init(src);
}

/* Detach all queued works with the spinlock held. */
static void _workqueue_detach_queued_nolock(struct rt_workqueue *queue,
                                            rt_list_t *pending_list,
                                            rt_list_t *delayed_list)
{
    struct rt_work *current = queue->work_current;

    if (current != RT_NULL &&
        current->list.next != &(current->list))
    {
        rt_list_remove(&(current->list));
        current->flags = (current->flags & RT_WORK_STATE_CANCELING) ? RT_WORK_STATE_CANCELING : RT_WORK_STATE_CANCELED;
    }
    _workqueue_move_list_nolock(pending_list, &queue->work_list);
    _workqueue_move_list_nolock(delayed_list, &queue->delayed_list);
}

/* The caller must ensure the running work has already been detached. */
static void _workqueue_cancel_detached_list(rt_list_t *list)
{
    struct rt_work *work;

    while (rt_list_isempty(list) == RT_FALSE)
    {
        work = rt_list_first_entry(list, struct rt_work, list);
        rt_list_remove(&(work->list));
        work->flags = RT_WORK_STATE_CANCELED;
        work->workqueue = RT_NULL;
    }
}

static rt_err_t _workqueue_prepare_destroy(struct rt_workqueue *queue,
                                           rt_bool_t sync,
                                           rt_list_t *pending_list,
                                           rt_list_t *delayed_list)
{
    rt_base_t level;
    rt_bool_t need_wakeup;

    if (sync && !rt_scheduler_is_available())
    {
        return -RT_EBUSY;
    }

    rt_list_init(pending_list);
    rt_list_init(delayed_list);

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    if (queue->flags & (RT_WORKQUEUE_FLAG_SYNC_WAITING | RT_WORKQUEUE_FLAG_DESTROYING))
    {
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);
        return -RT_EBUSY;
    }

    need_wakeup = _workqueue_is_idle_nolock(queue);
    if (sync)
    {
        queue->flags |= RT_WORKQUEUE_FLAG_SYNC_WAITING;
        if (queue->work_current != RT_NULL)
        {
            queue->work_current->flags |= RT_WORK_STATE_CANCELING;
        }
    }

    queue->flags |= RT_WORKQUEUE_FLAG_DESTROYING;
    _workqueue_detach_queued_nolock(queue, pending_list, delayed_list);
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    _workqueue_cancel_detached_list(pending_list);
    _workqueue_cancel_detached_list(delayed_list);
    if (need_wakeup)
    {
        rt_completion_done(&(queue->wakeup_completion));
    }

    return RT_EOK;
}

static rt_err_t _workqueue_destroy(struct rt_workqueue *queue, rt_bool_t sync)
{
    rt_err_t err;
    rt_list_t pending_list;
    rt_list_t delayed_list;

    if (!rt_in_thread_context() || queue->work_thread == rt_thread_self())
    {
        return -RT_EBUSY;
    }

    err = _workqueue_prepare_destroy(queue, sync, &pending_list, &delayed_list);
    if (err != RT_EOK)
    {
        return err;
    }

    if (!sync)
    {
        return RT_EOK;
    }

    rt_completion_wait(&(queue->sync_completion), RT_WAITING_FOREVER);
    RT_KERNEL_FREE(queue);

    return RT_EOK;
}

/* Promote due delayed works to work_list, and return next wait ticks. */
rt_inline rt_int32_t _workqueue_promote_delayed_nolock(struct rt_workqueue *queue)
{
    rt_int32_t delay_tick = RT_WAITING_FOREVER;
    rt_tick_t current_tick;
    rt_list_t *delayed_head = &(queue->delayed_list);
    rt_list_t *work_head = &(queue->work_list);
    rt_list_t *first_due;
    rt_list_t *first_non_due;
    rt_list_t *last_due;
    rt_list_t *delayed_tail;
    rt_list_t *work_tail;
    struct rt_work *work;

    if (rt_list_isempty(delayed_head))
    {
        return delay_tick;
    }

    /* delayed_list is sorted; only head may be due, promote consecutive due items. */
    current_tick = rt_tick_get();
    first_due = delayed_head->next;
    first_non_due = first_due;
    while (first_non_due != delayed_head)
    {
        work = rt_list_entry(first_non_due, struct rt_work, list);
        /* delayed_list is sorted by timeout_tick (wrap-safe compare). */
        if ((current_tick - work->timeout_tick) < RT_TICK_MAX / 2)
        {
            work->flags = RT_WORK_STATE_PENDING;
            first_non_due = first_non_due->next;
        }
        else
        {
            /* Next timeout not reached; record remaining delay. */
            delay_tick = work->timeout_tick - current_tick;
            break;
        }
    }

    if (first_non_due == first_due)
    {
        return delay_tick;
    }

    /* Move the whole due-prefix to work_list tail in one splice. */
    last_due = first_non_due->prev;
    delayed_tail = delayed_head->prev;
    delayed_head->next = first_non_due;
    first_non_due->prev = delayed_head;

    work_tail = work_head->prev;
    work_tail->next = first_due;
    first_due->prev = work_tail;
    last_due->next = work_head;
    work_head->prev = last_due;

    if (first_non_due == delayed_head)
    {
        delayed_head->prev = delayed_head;
    }
    else
    {
        delayed_head->prev = delayed_tail;
    }

    return delay_tick;
}

/* Insert delayed work into the sorted delayed list. */
rt_inline void _workqueue_insert_delayed_nolock(struct rt_workqueue *queue, struct rt_work *work)
{
    rt_list_t *list = &(queue->delayed_list);
    struct rt_work *first;
    struct rt_work *last;
    struct rt_work *iter;

    if (rt_list_isempty(list))
    {
        rt_list_insert_before(list, &(work->list));
        return;
    }

    /* Fast path: compare with head/tail to avoid full traversal. */
    first = rt_list_first_entry(list, struct rt_work, list);
    last = rt_list_entry(list->prev, struct rt_work, list);

    /* Wrap-safe compare: smaller timeout should be placed earlier in list. */
    if ((first->timeout_tick - work->timeout_tick) < RT_TICK_MAX / 2 &&
        first->timeout_tick != work->timeout_tick)
    {
        /* Same-timeout should keep FIFO order. */
        rt_list_insert_before(&(first->list), &(work->list));
        return;
    }
    if ((work->timeout_tick - last->timeout_tick) < RT_TICK_MAX / 2)
    {
        rt_list_insert_before(list, &(work->list));
        return;
    }

    /* Find the first element that should be after the new work. */
    rt_list_for_each_entry(iter, list, list)
    {
        if ((iter->timeout_tick - work->timeout_tick) == 0)
        {
            /* Keep FIFO order for equal timeout. */
            continue;
        }
        if ((iter->timeout_tick - work->timeout_tick) < RT_TICK_MAX / 2)
        {
            rt_list_insert_before(&(iter->list), &(work->list));
            return;
        }
    }
    rt_list_insert_before(list, &(work->list));
}

/* The caller must ensure the work is queued on this queue. */
rt_inline rt_bool_t _workqueue_cancel_queued_work_nolock(struct rt_workqueue *queue,
                                                         struct rt_work *work)
{
    rt_tick_t old_head_timeout;
    rt_bool_t queue_idle = _workqueue_is_idle_nolock(queue);
    rt_bool_t had_head = RT_FALSE;

    if (queue_idle)
    {
        if (rt_list_isempty(&(queue->delayed_list)) == RT_FALSE)
        {
            old_head_timeout = rt_list_first_entry(&(queue->delayed_list), struct rt_work, list)->timeout_tick;
            had_head = RT_TRUE;
        }
    }

    rt_list_remove(&(work->list));
    work->workqueue = RT_NULL;
    work->flags = RT_WORK_STATE_CANCELED;

    if (!queue_idle)
    {
        return RT_FALSE;
    }

    if (rt_list_isempty(&(queue->delayed_list)))
    {
        return had_head;
    }

    return !had_head ||
           rt_list_first_entry(&(queue->delayed_list), struct rt_work, list)->timeout_tick != old_head_timeout;
}

/* workqueue thread entry */
static void _workqueue_thread_entry(void *parameter)
{
    rt_base_t level;
    struct rt_work *work;
    struct rt_workqueue *queue;
    rt_int32_t delay_tick;
    void (*work_func)(struct rt_work *work, void *work_data);
    void *work_data;
    rt_bool_t need_sync;
    rt_bool_t requeued;

    queue = (struct rt_workqueue *)parameter;
    RT_ASSERT(queue != RT_NULL);

    while (1)
    {
        level = rt_spin_lock_irqsave(&(queue->spinlock));

        /* Move due delayed work into pending list. */
        delay_tick = _workqueue_promote_delayed_nolock(queue);

        if ((queue->flags & RT_WORKQUEUE_FLAG_DESTROYING) &&
            queue->work_current == RT_NULL &&
            rt_list_isempty(&(queue->work_list)) &&
            rt_list_isempty(&(queue->delayed_list)))
        {
            need_sync = (queue->flags & RT_WORKQUEUE_FLAG_SYNC_WAITING) != 0;
            rt_spin_unlock_irqrestore(&(queue->spinlock), level);

            if (need_sync)
            {
                rt_completion_done(&(queue->sync_completion));
            }
            else
            {
                RT_KERNEL_FREE(queue);
            }
            return;
        }

        if (rt_list_isempty(&(queue->work_list)))
        {
            rt_spin_unlock_irqrestore(&(queue->spinlock), level);
            /* Wait for new work or delayed timeout refresh. */
            rt_completion_wait(&(queue->wakeup_completion), delay_tick);
            continue;
        }

        /* Fetch next pending work. */
        work = rt_list_first_entry(&(queue->work_list), struct rt_work, list);
        rt_list_remove(&(work->list));
        queue->work_current = work;
        work->flags = 0;
        work_func = work->work_func;
        work_data = work->work_data;
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);

        /* Execute work without holding lock. */
        work_func(work, work_data);
        need_sync = RT_FALSE;
        level = rt_spin_lock_irqsave(&(queue->spinlock));
        /* Finalize current work and wake sync waiter if any. */
        queue->work_current = RT_NULL;
        requeued = work->list.next != &(work->list);
        /* Wake up cancel_work_sync waiter if present. */
        if ((queue->flags & RT_WORKQUEUE_FLAG_SYNC_WAITING) &&
            (queue->flags & RT_WORKQUEUE_FLAG_DESTROYING) == 0)
        {
            /* Remove possible requeue before cancel_work_sync resumes. */
            if (requeued)
            {
                rt_list_remove(&(work->list));
                requeued = RT_FALSE;
            }
            queue->flags &= ~RT_WORKQUEUE_FLAG_SYNC_WAITING;
            need_sync = RT_TRUE;
        }
        if (!requeued)
        {
            /* Mark completion only when no requeue is pending. */
            work->flags = RT_WORK_STATE_DONE;
            /* Clear only when truly idle. */
            work->workqueue = RT_NULL;
        }
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);

        if (need_sync)
        {
            rt_completion_done(&(queue->sync_completion));
        }
    }
}

static rt_err_t _workqueue_submit_work(struct rt_workqueue *queue,
                                       struct rt_work *work,
                                       rt_tick_t ticks,
                                       rt_bool_t urgent)
{
    rt_base_t level;
    rt_tick_t timeout_tick;
    rt_bool_t need_wakeup = RT_FALSE;
    rt_bool_t queue_idle;
    rt_tick_t old_head_timeout;
    rt_bool_t had_head = RT_FALSE;

    /* Validate input ticks. */
    if (ticks >= RT_TICK_MAX / 2)
    {
        return -RT_ERROR;
    }

    if (ticks != 0)
    {
        timeout_tick = rt_tick_get() + ticks;
    }

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    if ((queue->flags & RT_WORKQUEUE_FLAG_DESTROYING) ||
        (work->flags & RT_WORK_STATE_CANCELING) ||
        (work->workqueue != RT_NULL && work->workqueue != queue))
    {
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);
        return -RT_EBUSY;
    }
    /* Snapshot idle state before mutation to avoid unnecessary wakeups. */
    queue_idle = _workqueue_is_idle_nolock(queue);
    /* Remove list node to avoid duplicate queueing (safe on standalone node). */
    if (work->list.next != &(work->list))
    {
        rt_list_remove(&(work->list));
    }
    /* Clear queued/terminal state when resubmitting. */
    work->flags = 0;
    work->workqueue = queue;
    if (ticks == 0)
    {
        /* Enqueue immediate work to head or tail. */
        if (urgent)
        {
            rt_list_insert_after(&(queue->work_list), &(work->list));
        }
        else
        {
            rt_list_insert_before(&(queue->work_list), &(work->list));
        }
        work->flags = RT_WORK_STATE_PENDING;
        /* Wake up when queue was sleeping for delayed work or new work. */
        need_wakeup = queue_idle;
    }
    else
    {
        /* Enqueue delayed work (sorted by timeout). */
        if (queue_idle)
        {
            if (rt_list_isempty(&(queue->delayed_list)) == RT_FALSE)
            {
                old_head_timeout = rt_list_first_entry(&(queue->delayed_list), struct rt_work, list)->timeout_tick;
                had_head = RT_TRUE;
            }
        }
        work->flags = RT_WORK_STATE_SUBMITTING;
        work->timeout_tick = timeout_tick;

        _workqueue_insert_delayed_nolock(queue, work);
        /* Wake up only when queue is idle and timeout needs refresh. */
        if (queue_idle)
        {
            need_wakeup = !had_head ||
                          rt_list_first_entry(&(queue->delayed_list), struct rt_work, list)->timeout_tick != old_head_timeout;
        }
    }
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);
    if (need_wakeup)
    {
        rt_completion_done(&(queue->wakeup_completion));
    }
    return RT_EOK;
}

static rt_err_t _workqueue_cancel_core(struct rt_workqueue *queue,
                                       struct rt_work *work,
                                       rt_bool_t sync,
                                       rt_bool_t *need_wakeup,
                                       rt_bool_t *need_wait)
{
    rt_base_t level;
    rt_err_t err = RT_EOK;
    rt_bool_t sched_available = RT_FALSE;

    if (sync)
    {
        sched_available = rt_scheduler_is_available();
    }

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    if (work->workqueue != RT_NULL && work->workqueue != queue)
    {
        err = -RT_EBUSY;
        goto __exit;
    }

    if (sync)
    {
        if ((queue->flags & (RT_WORKQUEUE_FLAG_SYNC_WAITING | RT_WORKQUEUE_FLAG_DESTROYING)) ||
            (work->flags & RT_WORK_STATE_CANCELING))
        {
            err = -RT_EBUSY;
            goto __exit;
        }

        if (queue->work_current == work)
        {
            /* Only reject when cancel_sync would really block. */
            if (!sched_available)
            {
                err = -RT_EBUSY;
                goto __exit;
            }

            /* Mark canceling to block requeue in work callback. */
            work->flags |= RT_WORK_STATE_CANCELING;
            queue->flags |= RT_WORKQUEUE_FLAG_SYNC_WAITING;
            *need_wait = RT_TRUE;
            goto __exit;
        }
    }
    else if ((work->flags & RT_WORK_STATE_CANCELING) ||
             queue->work_current == work)
    {
        err = -RT_EBUSY;
        goto __exit;
    }

    if (work->list.next != &(work->list))
    {
        *need_wakeup = _workqueue_cancel_queued_work_nolock(queue, work);
    }

__exit:
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    return err;
}

/**
 * @brief Initialize a work item.
 *
 * @param work Work item.
 * @param work_func Work callback.
 * @param work_data Callback argument.
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
 * @brief Create a work queue.
 *
 * @param name Worker thread name.
 * @param stack_size Worker thread stack size.
 * @param priority Worker thread priority.
 *
 * @return Work queue object, or RT_NULL on failure.
 */
struct rt_workqueue *rt_workqueue_create(const char *name, rt_uint16_t stack_size, rt_uint8_t priority)
{
    struct rt_workqueue *queue;

    queue = (struct rt_workqueue *)RT_KERNEL_MALLOC(sizeof(struct rt_workqueue));
    if (queue != RT_NULL)
    {
        rt_list_init(&(queue->work_list));
        rt_list_init(&(queue->delayed_list));
        queue->work_current = RT_NULL;
        queue->flags = 0;
        rt_completion_init(&(queue->wakeup_completion));
        rt_completion_init(&(queue->sync_completion));

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
 * @param queue Work queue.
 *
 * @return RT_EOK on success.
 *         -RT_EBUSY if the queue is destroying, has a sync waiter, or the
 *         call is made outside thread context or from the worker thread.
 *
 * @note This API does not wait for the running work to finish. Use
 *       rt_workqueue_destroy_sync() if the caller must wait.
 */
rt_err_t rt_workqueue_destroy(struct rt_workqueue *queue)
{
    RT_ASSERT(queue != RT_NULL);
    return _workqueue_destroy(queue, RT_FALSE);
}

/**
 * @brief Destroy a work queue synchronously.
 *
 * @param queue Work queue.
 *
 * @return RT_EOK on success.
 *         -RT_EBUSY if the queue is destroying, has a sync waiter, the call
 *         is made outside thread context or from the worker thread, or the
 *         required wait cannot be performed while scheduler is unavailable.
 */
rt_err_t rt_workqueue_destroy_sync(struct rt_workqueue *queue)
{
    RT_ASSERT(queue != RT_NULL);
    return _workqueue_destroy(queue, RT_TRUE);
}

/**
 * @brief Submit a work item without delay.
 *
 * @param queue Work queue.
 * @param work Work item.
 *
 * @return RT_EOK on success.
 */
rt_err_t rt_workqueue_dowork(struct rt_workqueue *queue, struct rt_work *work)
{
    return rt_workqueue_submit_work(queue, work, 0);
}

/**
 * @brief Submit a work item with delay.
 *
 * @param queue Work queue.
 * @param work Work item.
 * @param ticks Delay ticks. The value must be less than RT_TICK_MAX / 2.
 *
 * @return RT_EOK on success.
 *         -RT_ERROR if ticks is invalid.
 *         -RT_EBUSY if the work belongs to another queue, is canceling, or
 *         the queue is destroying.
 */
rt_err_t rt_workqueue_submit_work(struct rt_workqueue *queue, struct rt_work *work, rt_tick_t ticks)
{
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);
    return _workqueue_submit_work(queue, work, ticks, RT_FALSE);
}

/**
 * @brief Submit a work item urgently.
 *
 * @param queue Work queue.
 * @param work Work item.
 *
 * @return RT_EOK on success.
 *         -RT_EBUSY if the work belongs to another queue, is canceling, or
 *         the queue is destroying.
 *
 * @note The work runs before queued pending works, but after the current
 *       running work.
 */
rt_err_t rt_workqueue_urgent_work(struct rt_workqueue *queue, struct rt_work *work)
{
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);
    return _workqueue_submit_work(queue, work, 0, RT_TRUE);
}

/**
 * @brief Cancel a work item.
 *
 * @param queue Work queue.
 * @param work Work item.
 *
 * @return RT_EOK on success.
 *         -RT_EBUSY if the work is executing, canceling, or belongs to
 *         another queue.
 */
rt_err_t rt_workqueue_cancel_work(struct rt_workqueue *queue, struct rt_work *work)
{
    rt_err_t err;
    rt_bool_t need_wakeup = RT_FALSE;

    RT_ASSERT(work != RT_NULL);
    RT_ASSERT(queue != RT_NULL);
    err = _workqueue_cancel_core(queue, work, RT_FALSE, &need_wakeup, RT_NULL);
    if (err == RT_EOK && need_wakeup)
    {
        rt_completion_done(&(queue->wakeup_completion));
    }

    return err;
}

/**
 * @brief Get work status in a work queue.
 *
 * @param queue Work queue.
 * @param work Work item.
 *
 * @return Status bits defined by RT_WORK_STATUS_*.
 *
 * @note If the work is not bound to any queue, this API returns the last
 *       terminal state if present, or RT_WORK_STATUS_IDLE otherwise.
 */
rt_uint16_t rt_workqueue_get_work_status(struct rt_workqueue *queue, struct rt_work *work)
{
    rt_base_t level;
    rt_uint16_t status = RT_WORK_STATUS_IDLE;

    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    if (work->workqueue != queue)
    {
        if (work->workqueue != RT_NULL)
        {
            status = RT_WORK_STATUS_OTHER_QUEUE;
        }
        else
        {
            /* Idle work reports its last terminal state if any. */
            status = work->flags & (RT_WORK_STATUS_DONE | RT_WORK_STATUS_CANCELED);
        }
        goto __exit;
    }

    status = work->flags & (RT_WORK_STATUS_PENDING |
                            RT_WORK_STATUS_SUBMITTING |
                            RT_WORK_STATUS_CANCELING |
                            RT_WORK_STATUS_DONE |
                            RT_WORK_STATUS_CANCELED);
    if (queue->work_current == work)
    {
        status |= RT_WORK_STATUS_RUNNING;
    }

__exit:
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    return status;
}

/**
 * @brief Cancel a work item synchronously.
 *
 * @param queue Work queue.
 * @param work Work item.
 *
 * @return RT_EOK on success. If the work is executing and the caller may
 *         block, this API waits for completion and still returns RT_EOK.
 *         -RT_EBUSY if the work is canceling, belongs to another queue, the
 *         queue is destroying, another sync waiter exists, the call is made
 *         outside thread context or from the worker thread, or the required
 *         wait cannot be performed while scheduler is unavailable.
 *
 * @note This API must be called in thread context and not from the worker
 *       thread.
 */
rt_err_t rt_workqueue_cancel_work_sync(struct rt_workqueue *queue, struct rt_work *work)
{
    rt_bool_t need_wait = RT_FALSE;
    rt_bool_t need_wakeup = RT_FALSE;
    rt_err_t err;

    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);
    if (!rt_in_thread_context() || queue->work_thread == rt_thread_self())
    {
        return -RT_EBUSY;
    }

    err = _workqueue_cancel_core(queue, work, RT_TRUE, &need_wakeup, &need_wait);
    if (err != RT_EOK)
    {
        return err;
    }

    if (need_wakeup)
    {
        rt_completion_done(&(queue->wakeup_completion));
    }
    if (!need_wait)
    {
        return RT_EOK;
    }

    /* Wait for current work done. */
    rt_completion_wait(&(queue->sync_completion), RT_WAITING_FOREVER);

    return RT_EOK;
}

/**
 * @brief Cancel all queued work items.
 *
 * @param queue Work queue.
 *
 * @return RT_EOK on success.
 *
 * @note This API does not stop the running work.
 */
rt_err_t rt_workqueue_cancel_all_work(struct rt_workqueue *queue)
{
    rt_base_t level;
    rt_bool_t need_wakeup;
    rt_list_t pending_list;
    rt_list_t delayed_list;

    RT_ASSERT(queue != RT_NULL);
    rt_list_init(&pending_list);
    rt_list_init(&delayed_list);
    /* Cancel queued work. */
    level = rt_spin_lock_irqsave(&(queue->spinlock));
    need_wakeup = _workqueue_is_idle_nolock(queue) &&
                  rt_list_isempty(&(queue->delayed_list)) == RT_FALSE;
    _workqueue_detach_queued_nolock(queue, &pending_list, &delayed_list);
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    _workqueue_cancel_detached_list(&pending_list);
    _workqueue_cancel_detached_list(&delayed_list);
    if (need_wakeup)
    {
        rt_completion_done(&(queue->wakeup_completion));
    }

    return RT_EOK;
}

#ifdef RT_USING_SYSTEM_WORKQUEUE

static struct rt_workqueue *sys_workq; /* system work queue */

/**
 * @brief Submit a work item to the system work queue with a delay.
 *
 * @param work Work item.
 * @param ticks Delay ticks. The value must be less than RT_TICK_MAX / 2.
 *
 * @return RT_EOK on success.
 *         -RT_ERROR if ticks is invalid.
 *         -RT_EBUSY if the work belongs to another queue, is canceling, or
 *         the queue is destroying.
 */
rt_err_t rt_work_submit(struct rt_work *work, rt_tick_t ticks)
{
    RT_ASSERT(sys_workq != RT_NULL);
    return rt_workqueue_submit_work(sys_workq, work, ticks);
}

/**
 * @brief Submit a work item urgently to the system work queue.
 *
 * @param work Work item.
 *
 * @return RT_EOK on success.
 *         -RT_EBUSY if the work belongs to another queue, is canceling, or
 *         the queue is destroying.
 */
rt_err_t rt_work_urgent(struct rt_work *work)
{
    RT_ASSERT(sys_workq != RT_NULL);
    return rt_workqueue_urgent_work(sys_workq, work);
}

/**
 * @brief Cancel a work item in the system work queue.
 *
 * @param work Work item.
 *
 * @return RT_EOK on success.
 *         -RT_EBUSY if the work is executing, canceling, or belongs to
 *         another queue.
 */
rt_err_t rt_work_cancel(struct rt_work *work)
{
    RT_ASSERT(sys_workq != RT_NULL);
    return rt_workqueue_cancel_work(sys_workq, work);
}

/**
 * @brief Cancel a work item in the system work queue synchronously.
 *
 * @param work Work item.
 *
 * @return RT_EOK on success. If the work is executing and the caller may
 *         block, this API waits for completion and still returns RT_EOK.
 *         -RT_EBUSY if the work is canceling, belongs to another queue, the
 *         queue is destroying, another sync waiter exists, the call is made
 *         outside thread context or from the system worker thread, or the
 *         required wait cannot be performed while scheduler is unavailable.
 */
rt_err_t rt_work_cancel_sync(struct rt_work *work)
{
    RT_ASSERT(sys_workq != RT_NULL);
    return rt_workqueue_cancel_work_sync(sys_workq, work);
}

/**
 * @brief Get work status in the system work queue.
 *
 * @param work Work item.
 *
 * @return Status bits defined by RT_WORK_STATUS_*.
 */
rt_uint16_t rt_work_get_status(struct rt_work *work)
{
    RT_ASSERT(sys_workq != RT_NULL);
    return rt_workqueue_get_work_status(sys_workq, work);
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
