/*
 * File      : workqueue.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-02-27     bernard      fix the re-work issue.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_HEAP
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

static void _workqueue_thread_entry(void* parameter)
{
    rt_base_t level;
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
        level = rt_hw_interrupt_disable();
        work = rt_list_entry(queue->work_list.next, struct rt_work, list);
        rt_list_remove(&(work->list));
        queue->work_current = work;
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

struct rt_workqueue *rt_workqueue_create(const char* name, rt_uint16_t stack_size, rt_uint8_t priority)
{
    struct rt_workqueue *queue = RT_NULL;

    queue = (struct rt_workqueue*)RT_KERNEL_MALLOC(sizeof(struct rt_workqueue));
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

rt_err_t rt_workqueue_destroy(struct rt_workqueue* queue)
{
    RT_ASSERT(queue != RT_NULL);

    rt_thread_delete(queue->work_thread);
    RT_KERNEL_FREE(queue);

    return RT_EOK;
}

rt_err_t rt_workqueue_dowork(struct rt_workqueue* queue, struct rt_work* work)
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
    /* whether the workqueue is doing work */
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

rt_err_t rt_workqueue_critical_work(struct rt_workqueue* queue, struct rt_work* work)
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

rt_err_t rt_workqueue_cancel_work(struct rt_workqueue* queue, struct rt_work* work)
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
    rt_list_remove(&(work->list));
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t rt_workqueue_cancel_work_sync(struct rt_workqueue* queue, struct rt_work* work)
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
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t rt_workqueue_cancel_all_work(struct rt_workqueue* queue)
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

#endif

