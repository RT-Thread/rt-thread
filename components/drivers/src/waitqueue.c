/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/06/26     Bernard      Fix the wait queue issue when wakeup a soon 
 *                             to blocked thread.
 */

#include <stdint.h>

#include <rthw.h>
#include <rtdevice.h>
#include <rtservice.h>

void rt_wqueue_add(rt_wqueue_t *queue, struct rt_wqueue_node *node)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    rt_list_insert_before(&(queue->waiting_list), &(node->list));
    rt_hw_interrupt_enable(level);
}

void rt_wqueue_remove(struct rt_wqueue_node *node)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    rt_list_remove(&(node->list));
    rt_hw_interrupt_enable(level);
}

int __wqueue_default_wake(struct rt_wqueue_node *wait, void *key)
{
    return 0;
}

void rt_wqueue_wakeup(rt_wqueue_t *queue, void *key)
{
    rt_base_t level;
    register int need_schedule = 0;

    rt_list_t *queue_list;
    struct rt_list_node *node;
    struct rt_wqueue_node *entry;

    queue_list = &(queue->waiting_list);

    level = rt_hw_interrupt_disable();
    /* set wakeup flag in the queue */
    queue->flag = RT_WQ_FLAG_WAKEUP;

    if (!(rt_list_isempty(queue_list)))
    {
        for (node = queue_list->next; node != queue_list; node = node->next)
        {
            entry = rt_list_entry(node, struct rt_wqueue_node, list);
            if (entry->wakeup(entry, key) == 0)
            {
                rt_thread_resume(entry->polling_thread);
                need_schedule = 1;

                rt_wqueue_remove(entry);
                break;
            }
        }
    }
    rt_hw_interrupt_enable(level);

    if (need_schedule)
        rt_schedule();
}

int rt_wqueue_wait(rt_wqueue_t *queue, int condition, int msec)
{
    int tick;
    rt_thread_t tid = rt_thread_self();
    rt_timer_t  tmr = &(tid->thread_timer);
    struct rt_wqueue_node __wait;
    rt_base_t level;

    /* current context checking */
    RT_DEBUG_NOT_IN_INTERRUPT;

    tick = rt_tick_from_millisecond(msec);

    if ((condition) || (tick == 0))
        return 0;

    __wait.polling_thread = rt_thread_self();
    __wait.key = 0;
    __wait.wakeup = __wqueue_default_wake;
    rt_list_init(&__wait.list);

    level = rt_hw_interrupt_disable();
    if (queue->flag == RT_WQ_FLAG_WAKEUP)
    {
        /* already wakeup */
        goto __exit_wakeup;
    }

    rt_wqueue_add(queue, &__wait);
    rt_thread_suspend(tid);

    /* start timer */
    if (tick != RT_WAITING_FOREVER)
    {
        rt_timer_control(tmr,
                         RT_TIMER_CTRL_SET_TIME,
                         &tick);

        rt_timer_start(tmr);
    }
    rt_hw_interrupt_enable(level);

    rt_schedule();

    level = rt_hw_interrupt_disable();

__exit_wakeup:
    queue->flag = 0;
    rt_hw_interrupt_enable(level);

    rt_wqueue_remove(&__wait);

    return 0;
}
