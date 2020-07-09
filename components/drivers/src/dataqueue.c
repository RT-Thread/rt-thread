/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-30     Bernard      first version.
 * 2016-10-31     armink       fix some resume push and pop thread bugs
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#define DATAQUEUE_MAGIC  0xbead0e0e

struct rt_data_item
{
    const void *data_ptr;
    rt_size_t data_size;
};

rt_err_t
rt_data_queue_init(struct rt_data_queue *queue,
                   rt_uint16_t size,
                   rt_uint16_t lwm,
                   void (*evt_notify)(struct rt_data_queue *queue, rt_uint32_t event))
{
    RT_ASSERT(queue != RT_NULL);

    queue->evt_notify = evt_notify;

    queue->magic = DATAQUEUE_MAGIC;
    queue->size = size;
    queue->lwm = lwm;

    queue->get_index = 0;
    queue->put_index = 0;

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

rt_err_t rt_data_queue_push(struct rt_data_queue *queue,
                            const void *data_ptr,
                            rt_size_t data_size,
                            rt_int32_t timeout)
{
    rt_ubase_t  level;
    rt_thread_t thread;
    rt_err_t    result;
    
    RT_ASSERT(queue->magic == DATAQUEUE_MAGIC);
    RT_ASSERT(queue != RT_NULL);

    result = RT_EOK;
    thread = rt_thread_self();

    level = rt_hw_interrupt_disable();
    while (queue->put_index - queue->get_index == queue->size)
    {
        /* queue is full */
        if (timeout == 0)
        {
            result = -RT_ETIMEOUT;

            goto __exit;
        }

        /* current context checking */
        RT_DEBUG_NOT_IN_INTERRUPT;

        /* reset thread error number */
        thread->error = RT_EOK;
        
        /* suspend thread on the push list */
        rt_thread_suspend(thread);
        rt_list_insert_before(&(queue->suspended_push_list), &(thread->tlist));
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
        rt_hw_interrupt_enable(level);

        /* do schedule */
        rt_schedule();

        /* thread is waked up */
        result = thread->error;
        level = rt_hw_interrupt_disable();
        if (result != RT_EOK) goto __exit;
    }

    queue->queue[queue->put_index % queue->size].data_ptr  = data_ptr;
    queue->queue[queue->put_index % queue->size].data_size = data_size;
    queue->put_index += 1;

    /* there is at least one thread in suspended list */
    if (!rt_list_isempty(&(queue->suspended_pop_list)))
    {
        /* get thread entry */
        thread = rt_list_entry(queue->suspended_pop_list.next,
                               struct rt_thread,
                               tlist);

        /* resume it */
        rt_thread_resume(thread);
        rt_hw_interrupt_enable(level);

        /* perform a schedule */
        rt_schedule();

        return result;
    }

__exit:
    rt_hw_interrupt_enable(level);
    if ((result == RT_EOK) && queue->evt_notify != RT_NULL)
    {
        queue->evt_notify(queue, RT_DATAQUEUE_EVENT_PUSH);
    }

    return result;
}
RTM_EXPORT(rt_data_queue_push);

rt_err_t rt_data_queue_pop(struct rt_data_queue *queue,
                           const void** data_ptr,
                           rt_size_t *size, 
                           rt_int32_t timeout)
{
    rt_ubase_t  level;
    rt_thread_t thread;
    rt_err_t    result;
    
    RT_ASSERT(queue->magic == DATAQUEUE_MAGIC);
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(data_ptr != RT_NULL);
    RT_ASSERT(size != RT_NULL);

    result = RT_EOK;
    thread = rt_thread_self();

    level = rt_hw_interrupt_disable();
    while (queue->get_index == queue->put_index)
    {
        /* queue is empty */
        if (timeout == 0)
        {
            result = -RT_ETIMEOUT;
            goto __exit;
        }

        /* current context checking */
        RT_DEBUG_NOT_IN_INTERRUPT;

        /* reset thread error number */
        thread->error = RT_EOK;
        
        /* suspend thread on the pop list */
        rt_thread_suspend(thread);
        rt_list_insert_before(&(queue->suspended_pop_list), &(thread->tlist));
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
        rt_hw_interrupt_enable(level);

        /* do schedule */
        rt_schedule();

        /* thread is waked up */
        result = thread->error;
        level  = rt_hw_interrupt_disable();
        if (result != RT_EOK)
            goto __exit;
    }

    *data_ptr = queue->queue[queue->get_index % queue->size].data_ptr;
    *size     = queue->queue[queue->get_index % queue->size].data_size;

    queue->get_index += 1;

    if ((queue->put_index - queue->get_index) <= queue->lwm)
    {
        /* there is at least one thread in suspended list */
        if (!rt_list_isempty(&(queue->suspended_push_list)))
        {
            /* get thread entry */
            thread = rt_list_entry(queue->suspended_push_list.next,
                                   struct rt_thread,
                                   tlist);

            /* resume it */
            rt_thread_resume(thread);
            rt_hw_interrupt_enable(level);

            /* perform a schedule */
            rt_schedule();
        }
        else
        {
            rt_hw_interrupt_enable(level);
        }

        if (queue->evt_notify != RT_NULL)
            queue->evt_notify(queue, RT_DATAQUEUE_EVENT_LWM);

        return result;
    }

__exit:
    rt_hw_interrupt_enable(level);
    if ((result == RT_EOK) && (queue->evt_notify != RT_NULL))
    {
        queue->evt_notify(queue, RT_DATAQUEUE_EVENT_POP);
    }

    return result;
}
RTM_EXPORT(rt_data_queue_pop);

rt_err_t rt_data_queue_peak(struct rt_data_queue *queue,
                            const void** data_ptr,
                            rt_size_t *size)
{
    rt_ubase_t  level;
    
    RT_ASSERT(queue->magic == DATAQUEUE_MAGIC);
    RT_ASSERT(queue != RT_NULL);

    level = rt_hw_interrupt_disable();

    if (queue->get_index == queue->put_index) 
    {
        rt_hw_interrupt_enable(level);
        
        return -RT_EEMPTY;
    }

    *data_ptr = queue->queue[queue->get_index % queue->size].data_ptr;
    *size     = queue->queue[queue->get_index % queue->size].data_size;

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
RTM_EXPORT(rt_data_queue_peak);

void rt_data_queue_reset(struct rt_data_queue *queue)
{
    struct rt_thread *thread;
    register rt_ubase_t temp;
    
    RT_ASSERT(queue->magic == DATAQUEUE_MAGIC);
    
    rt_enter_critical();
    /* wakeup all suspend threads */

    /* resume on pop list */
    while (!rt_list_isempty(&(queue->suspended_pop_list)))
    {
        /* disable interrupt */
        temp = rt_hw_interrupt_disable();

        /* get next suspend thread */
        thread = rt_list_entry(queue->suspended_pop_list.next,
                               struct rt_thread,
                               tlist);
        /* set error code to RT_ERROR */
        thread->error = -RT_ERROR;

        /*
         * resume thread
         * In rt_thread_resume function, it will remove current thread from
         * suspend list
         */
        rt_thread_resume(thread);

        /* enable interrupt */
        rt_hw_interrupt_enable(temp);
    }

    /* resume on push list */
    while (!rt_list_isempty(&(queue->suspended_push_list)))
    {
        /* disable interrupt */
        temp = rt_hw_interrupt_disable();

        /* get next suspend thread */
        thread = rt_list_entry(queue->suspended_push_list.next,
                               struct rt_thread,
                               tlist);
        /* set error code to RT_ERROR */
        thread->error = -RT_ERROR;

        /*
         * resume thread
         * In rt_thread_resume function, it will remove current thread from
         * suspend list
         */
        rt_thread_resume(thread);

        /* enable interrupt */
        rt_hw_interrupt_enable(temp);
    }
    rt_exit_critical();

    rt_schedule();
}
RTM_EXPORT(rt_data_queue_reset);

rt_err_t rt_data_queue_deinit(struct rt_data_queue *queue)
{
    rt_ubase_t level;

    RT_ASSERT(queue->magic == DATAQUEUE_MAGIC);
    RT_ASSERT(queue != RT_NULL);

    level = rt_hw_interrupt_disable();

    /* wakeup all suspend threads */
    rt_data_queue_reset(queue);

    queue->magic = 0;
    rt_free(queue->queue);
    
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
RTM_EXPORT(rt_data_queue_deinit);
