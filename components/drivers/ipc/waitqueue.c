/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/06/26     Bernard      Fix the wait queue issue when wakeup a soon
 *                             to blocked thread.
 * 2022-01-24     THEWON       let rt_wqueue_wait return thread->error when using signal
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 * 2023-11-21     Shell        Support wakeup_all
 */
#define DBG_TAG "ipc.waitqueue"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <stdint.h>
#include <rthw.h>
#include <rtdevice.h>

/**
 * @brief    This function will insert a node to the wait queue.
 *
 * @param    queue is a pointer to the wait queue.
 *
 * @param    node is a pointer to the node to be inserted.
 */
void rt_wqueue_add(rt_wqueue_t *queue, struct rt_wqueue_node *node)
{
    rt_base_t level;

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    node->wqueue = queue;
    rt_list_insert_before(&(queue->waiting_list), &(node->list));
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);
}

/**
 * @brief    This function will remove a node from the wait queue.
 *
 * @param    node is a pointer to the node to be removed.
 */
void rt_wqueue_remove(struct rt_wqueue_node *node)
{
    rt_base_t level;

    RT_ASSERT(node->wqueue != RT_NULL);

    level = rt_spin_lock_irqsave(&(node->wqueue->spinlock));
    rt_list_remove(&(node->list));
    rt_spin_unlock_irqrestore(&(node->wqueue->spinlock), level);
}

/**
 * @brief    This function is the default wakeup function, but it doesn't do anything in actual.
 *           It always return 0, user should define their own wakeup function.
 *
 * @param    wait is a pointer to the wait queue.
 *
 * @param    key is the wakeup condition.
 *
 * @return   always return 0.
 */
int __wqueue_default_wake(struct rt_wqueue_node *wait, void *key)
{
    return 0;
}

/**
 * @brief    This function will wake up a pending thread on the specified
 * waiting queue that meets the conditions.
 *
 * @param    queue is a pointer to the wait queue.
 *
 * @param    key is the wakeup conditions, but it is not effective now, because
 *           default wakeup function always return 0.
 *           If user wants to use it, user should define their own wakeup function.
 */
void rt_wqueue_wakeup(rt_wqueue_t *queue, void *key)
{
    rt_base_t level;
    int need_schedule = 0;

    rt_list_t *queue_list;
    struct rt_list_node *node;
    struct rt_wqueue_node *entry;

    queue_list = &(queue->waiting_list);

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    /* set wakeup flag in the queue */
    queue->flag = RT_WQ_FLAG_WAKEUP;

    if (!(rt_list_isempty(queue_list)))
    {
        for (node = queue_list->next; node != queue_list; node = node->next)
        {
            entry = rt_list_entry(node, struct rt_wqueue_node, list);
            if (entry->wakeup(entry, key) == 0)
            {
                /**
                 * even though another thread may interrupt the thread and
                 * wakeup it meanwhile, we can asuume that condition is ready
                 */
                entry->polling_thread->error = RT_EOK;
                if (!rt_thread_resume(entry->polling_thread))
                {
                    need_schedule = 1;

                    rt_list_remove(&(entry->list));

                    break;
                }
            }
        }
    }
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);
    if (need_schedule)
        rt_schedule();

    return;
}

/**
 * @brief    This function will wake up all pending thread on the specified
 *           waiting queue that meets the conditions.
 *
 * @param    queue is a pointer to the wait queue.
 *
 * @param    key is the wakeup conditions, but it is not effective now, because
 *           default wakeup function always return 0.
 *           If user wants to use it, user should define their own wakeup
 *           function.
 */
void rt_wqueue_wakeup_all(rt_wqueue_t *queue, void *key)
{
    rt_base_t level;
    int need_schedule = 0;

    rt_list_t *queue_list;
    struct rt_list_node *node;
    struct rt_wqueue_node *entry;

    queue_list = &(queue->waiting_list);

    level = rt_spin_lock_irqsave(&(queue->spinlock));
    /* set wakeup flag in the queue */
    queue->flag = RT_WQ_FLAG_WAKEUP;

    if (!(rt_list_isempty(queue_list)))
    {
        for (node = queue_list->next; node != queue_list; )
        {
            entry = rt_list_entry(node, struct rt_wqueue_node, list);
            if (entry->wakeup(entry, key) == 0)
            {
                /**
                 * even though another thread may interrupt the thread and
                 * wakeup it meanwhile, we can asuume that condition is ready
                 */
                entry->polling_thread->error = RT_EOK;
                if (!rt_thread_resume(entry->polling_thread))
                {
                    need_schedule = 1;
                }
                else
                {
                    /* wakeup happened too soon that waker hadn't slept */
                    LOG_D("%s: Thread resume failed", __func__);
                }
                node = node->next;
            }
            else
            {
                node = node->next;
            }
        }
    }
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);
    if (need_schedule)
        rt_schedule();

    return;
}

/**
 * @brief    This function will join a thread to the specified waiting queue, the thread will holds a wait or
 *           timeout return on the specified wait queue.
 *
 * @param    queue is a pointer to the wait queue.
 *
 * @param    condition is parameters compatible with POSIX standard interface (currently meaningless, just pass in 0).
 *
 * @param    msec is the timeout value, unit is millisecond.
 *
 * @return   Return 0 if the thread is woken up.
 */
static int _rt_wqueue_wait(rt_wqueue_t *queue, int condition, int msec, int suspend_flag)
{
    int tick;
    rt_thread_t tid = rt_thread_self();
    rt_timer_t  tmr = &(tid->thread_timer);
    struct rt_wqueue_node __wait;
    rt_base_t level;
    rt_err_t ret;

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(RT_TRUE);

    tick = rt_tick_from_millisecond(msec);

    if ((condition) || (tick == 0))
        return 0;

    __wait.polling_thread = rt_thread_self();
    __wait.key = 0;
    __wait.wakeup = __wqueue_default_wake;
    __wait.wqueue = queue;
    rt_list_init(&__wait.list);

    level = rt_spin_lock_irqsave(&(queue->spinlock));

    /* reset thread error */
    tid->error = RT_EOK;

    if (queue->flag == RT_WQ_FLAG_WAKEUP)
    {
        /* already wakeup */
        goto __exit_wakeup;
    }

    ret = rt_thread_suspend_with_flag(tid, suspend_flag);
    if (ret != RT_EOK)
    {
        rt_spin_unlock_irqrestore(&(queue->spinlock), level);
        /* suspend failed */
        return -RT_EINTR;
    }

    rt_list_insert_before(&(queue->waiting_list), &(__wait.list));

    /* start timer */
    if (tick != RT_WAITING_FOREVER)
    {
        rt_timer_control(tmr,
                         RT_TIMER_CTRL_SET_TIME,
                         &tick);

        rt_timer_start(tmr);
    }
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    rt_schedule();

    level = rt_spin_lock_irqsave(&(queue->spinlock));

__exit_wakeup:
    queue->flag = RT_WQ_FLAG_CLEAN;
    rt_spin_unlock_irqrestore(&(queue->spinlock), level);

    rt_wqueue_remove(&__wait);

    return tid->error > 0 ? -tid->error : tid->error;
}

int rt_wqueue_wait(rt_wqueue_t *queue, int condition, int msec)
{
    return _rt_wqueue_wait(queue, condition, msec, RT_UNINTERRUPTIBLE);
}

int rt_wqueue_wait_killable(rt_wqueue_t *queue, int condition, int msec)
{
    return _rt_wqueue_wait(queue, condition, msec, RT_KILLABLE);
}

int rt_wqueue_wait_interruptible(rt_wqueue_t *queue, int condition, int msec)
{
    return _rt_wqueue_wait(queue, condition, msec, RT_INTERRUPTIBLE);
}
