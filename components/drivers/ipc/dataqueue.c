/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-30     Bernard      first version.
 * 2016-10-31     armink       fix some resume push and pop thread bugs
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 * 2024-01-25     Shell        porting to susp_list API
 */

#include <rthw.h>
#include <rtdevice.h>

#define DATAQUEUE_MAGIC  0xbead0e0e

struct rt_data_item
{
    const void *data_ptr;
    rt_size_t data_size;
};

/**
 * @brief    This function will initialize the data queue. Calling this function will
 *           initialize the data queue control block and set the notification callback function.
 *
 * @param    queue is a pointer to the data queue object.
 *
 * @param    size is the maximum number of data in the data queue.
 *
 * @param    lwm is low water mark.
 *           When the number of data in the data queue is less than this value, this function will
 *           wake up the thread waiting for write data.
 *
 * @param    evt_notify is the notification callback function.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *           When the return value is -RT_ENOMEM, it means insufficient memory allocation failed.
 */
rt_err_t
rt_data_queue_init(struct rt_data_queue *queue,
                   rt_uint16_t size,
                   rt_uint16_t lwm,
                   void (*evt_notify)(struct rt_data_queue *queue, rt_uint32_t event))
{
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(size > 0);

    queue->evt_notify = evt_notify;

    queue->magic = DATAQUEUE_MAGIC;
    queue->size = size;
    queue->lwm = lwm;

    queue->get_index = 0;
    queue->put_index = 0;
    queue->is_empty = 1;
    queue->is_full = 0;

    rt_spin_lock_init(&(queue->spinlock));

    rt_list_init(&(queue->suspended_push_list));
    rt_list_init(&(queue->suspended_pop_list));

    queue->queue = (struct rt_data_item *)rt_malloc(sizeof(struct rt_data_item) * size);
    if (queue->queue == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    return RT_EOK;
}
RTM_EXPORT(rt_data_queue_init);

/**
 * @brief    This function will write data to the data queue. If the data queue is full,
 *           the thread will suspend for the specified amount of time.
 *
 * @param    queue is a pointer to the data queue object.
 * .
 * @param    data_ptr is the buffer pointer of the data to be written.
 *
 * @param    size is the size in bytes of the data to be written.
 *
 * @param    timeout is the waiting time.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           When the return value is -RT_ETIMEOUT, it means the specified time out.
 */
rt_err_t rt_data_queue_push(struct rt_data_queue *queue,
                            const void *data_ptr,
                            rt_size_t data_size,
                            rt_int32_t timeout)
{
    rt_base_t level;
    rt_thread_t thread;
    rt_err_t    result;

    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(queue->magic == DATAQUEUE_MAGIC);

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(timeout != 0);

    result = RT_EOK;
    thread = rt_thread_self();

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    while (queue->is_full)
    {
        /* queue is full */
        if (timeout == 0)
        {
            result = -RT_ETIMEOUT;

            goto __exit;
        }

        /* reset thread error number */
        thread->error = RT_EOK;

        /* suspend thread on the push list */
        result = rt_thread_suspend_to_list(thread, &queue->suspended_push_list,
                                           RT_IPC_FLAG_FIFO, RT_UNINTERRUPTIBLE);
        if (result == RT_EOK)
        {
            /* start timer */
            if (timeout > 0)
            {
                /* reset the timeout of thread timer and start it */
                rt_timer_control(&(thread->thread_timer),
                                RT_TIMER_CTRL_SET_TIME,
                                &timeout);
                rt_timer_start(&(thread->thread_timer));
            }

            /* enable interrupt */
            rt_spin_unlock_irqrestore(&(queue->spinlock), level);

            /* do schedule */
            rt_schedule();

            /* thread is waked up */
            level = rt_spin_lock_irqsave(&(queue->spinlock));

            /* error may be modified by waker, so take the lock before accessing it */
            result = thread->error;
        }
        if (result != RT_EOK) goto __exit;
    }

    queue->queue[queue->put_index].data_ptr  = data_ptr;
    queue->queue[queue->put_index].data_size = data_size;
    queue->put_index += 1;
    if (queue->put_index == queue->size)
    {
        queue->put_index = 0;
    }
    queue->is_empty = 0;
    if (queue->put_index == queue->get_index)
    {
        queue->is_full = 1;
    }

    /* there is at least one thread in suspended list */
    if (rt_susp_list_dequeue(&queue->suspended_pop_list,
                             RT_THREAD_RESUME_RES_THR_ERR))
    {
        /* unlock and perform a schedule */
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);

        /* perform a schedule */
        rt_schedule();

        return result;
    }

__exit:
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);
    if ((result == RT_EOK) && queue->evt_notify != RT_NULL)
    {
        queue->evt_notify(queue, RT_DATAQUEUE_EVENT_PUSH);
    }

    return result;
}
RTM_EXPORT(rt_data_queue_push);

/**
 * @brief    This function will pop data from the data queue. If the data queue is empty,the thread
 *           will suspend for the specified amount of time.
 *
 * @note     When the number of data in the data queue is less than lwm(low water mark), will
 *           wake up the thread waiting for write data.
 *
 * @param    queue is a pointer to the data queue object.
 *
 * @param    data_ptr is the buffer pointer of the data to be fetched.
 *
 * @param    size is the size in bytes of the data to be fetched.
 *
 * @param    timeout is the waiting time.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           When the return value is -RT_ETIMEOUT, it means the specified time out.
 */
rt_err_t rt_data_queue_pop(struct rt_data_queue *queue,
                           const void **data_ptr,
                           rt_size_t *size,
                           rt_int32_t timeout)
{
    rt_base_t level;
    rt_thread_t thread;
    rt_err_t    result;

    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(queue->magic == DATAQUEUE_MAGIC);
    RT_ASSERT(data_ptr != RT_NULL);
    RT_ASSERT(size != RT_NULL);

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(timeout != 0);

    result = RT_EOK;
    thread = rt_thread_self();

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    while (queue->is_empty)
    {
        /* queue is empty */
        if (timeout == 0)
        {
            result = -RT_ETIMEOUT;
            goto __exit;
        }

        /* reset thread error number */
        thread->error = RT_EOK;

        /* suspend thread on the pop list */
        result = rt_thread_suspend_to_list(thread, &queue->suspended_pop_list,
                                           RT_IPC_FLAG_FIFO, RT_UNINTERRUPTIBLE);
        if (result == RT_EOK)
        {
            /* start timer */
            if (timeout > 0)
            {
                /* reset the timeout of thread timer and start it */
                rt_timer_control(&(thread->thread_timer),
                                RT_TIMER_CTRL_SET_TIME,
                                &timeout);
                rt_timer_start(&(thread->thread_timer));
            }

            /* enable interrupt */
            rt_spin_unlock_irqrestore(&(queue->spinlock), level);

            /* do schedule */
            rt_schedule();

            /* thread is waked up */
            level  = rt_spin_lock_irqsave(&(queue->spinlock));
            result = thread->error;
            if (result != RT_EOK)
                goto __exit;
        }
    }

    *data_ptr = queue->queue[queue->get_index].data_ptr;
    *size     = queue->queue[queue->get_index].data_size;
    queue->get_index += 1;
    if (queue->get_index == queue->size)
    {
        queue->get_index = 0;
    }
    queue->is_full = 0;
    if (queue->put_index == queue->get_index)
    {
        queue->is_empty = 1;
    }

    if (rt_data_queue_len(queue) <= queue->lwm)
    {
        /* there is at least one thread in suspended list */
        if (rt_susp_list_dequeue(&queue->suspended_push_list,
                                       RT_THREAD_RESUME_RES_THR_ERR))
        {
            /* unlock and perform a schedule */
            rt_spin_unlock_irqrestore(&(queue->spinlock), level);

            /* perform a schedule */
            rt_schedule();
        }
        else
        {
            rt_spin_unlock_irqrestore(&(queue->spinlock), level);
        }

        if (queue->evt_notify != RT_NULL)
            queue->evt_notify(queue, RT_DATAQUEUE_EVENT_LWM);

        return result;
    }

__exit:
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);
    if ((result == RT_EOK) && (queue->evt_notify != RT_NULL))
    {
        queue->evt_notify(queue, RT_DATAQUEUE_EVENT_POP);
    }

    return result;
}
RTM_EXPORT(rt_data_queue_pop);

/**
 * @brief    This function will fetch but retaining data in the data queue.
 *
 * @param    queue is a pointer to the data queue object.
 *
 * @param    data_ptr is the buffer pointer of the data to be fetched.
 *
 * @param    size is the size in bytes of the data to be fetched.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 *           When the return value is -RT_EEMPTY, it means the data queue is empty.
 */
rt_err_t rt_data_queue_peek(struct rt_data_queue *queue,
                            const void **data_ptr,
                            rt_size_t *size)
{
    rt_base_t level;

    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(queue->magic == DATAQUEUE_MAGIC);

    if (queue->is_empty)
    {
        return -RT_EEMPTY;
    }

    level = rt_spin_lock_irqsave(&(queue->spinlock));

    *data_ptr = queue->queue[queue->get_index].data_ptr;
    *size     = queue->queue[queue->get_index].data_size;

    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    return RT_EOK;
}
RTM_EXPORT(rt_data_queue_peek);

/**
 * @brief    This function will reset the data queue.
 *
 * @note     Calling this function will wake up all threads on the data queue
 *           that are hanging and waiting.
 *
 * @param    queue is a pointer to the data queue object.
 */
void rt_data_queue_reset(struct rt_data_queue *queue)
{
    rt_base_t level;

    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(queue->magic == DATAQUEUE_MAGIC);

    level = rt_spin_lock_irqsave(&(queue->spinlock));

    queue->get_index = 0;
    queue->put_index = 0;
    queue->is_empty = 1;
    queue->is_full = 0;

    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    rt_enter_critical();
    /* wakeup all suspend threads */

    /* resume on pop list */
    rt_susp_list_resume_all_irq(&queue->suspended_pop_list, RT_ERROR,
                                &(queue->spinlock));

    /* resume on push list */
    rt_susp_list_resume_all_irq(&queue->suspended_push_list, RT_ERROR,
                                &(queue->spinlock));

    rt_exit_critical();

    rt_schedule();
}
RTM_EXPORT(rt_data_queue_reset);

/**
 * @brief    This function will deinit the data queue.
 *
 * @param    queue is a pointer to the data queue object.
 *
 * @return   Return the operation status. When the return value is RT_EOK, the operation is successful.
 */
rt_err_t rt_data_queue_deinit(struct rt_data_queue *queue)
{
    rt_base_t level;

    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(queue->magic == DATAQUEUE_MAGIC);

    /* wakeup all suspend threads */
    rt_data_queue_reset(queue);

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    queue->magic = 0;
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    rt_free(queue->queue);

    return RT_EOK;
}
RTM_EXPORT(rt_data_queue_deinit);

/**
 * @brief    This function will get the number of data in the data queue.
 *
 * @param    queue is a pointer to the data queue object.
 *
 * @return   Return the number of data in the data queue.
 */
rt_uint16_t rt_data_queue_len(struct rt_data_queue *queue)
{
    rt_base_t level;
    rt_int16_t len;

    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(queue->magic == DATAQUEUE_MAGIC);

    if (queue->is_empty)
    {
        return 0;
    }

    level = rt_spin_lock_irqsave(&(queue->spinlock));

    if (queue->put_index > queue->get_index)
    {
        len = queue->put_index - queue->get_index;
    }
    else
    {
        len = queue->size + queue->put_index - queue->get_index;
    }

    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    return len;
}
RTM_EXPORT(rt_data_queue_len);

