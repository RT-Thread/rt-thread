/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-20     Shell        Support of condition variable
 */
#define DBG_TAG "ipc.condvar"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <rtdevice.h>
#include <rtatomic.h>
#include <rtthread.h>

static struct rt_spinlock _local_cv_queue_lock = RT_SPINLOCK_INIT;

#define CV_ASSERT_LOCKED(cv)                                       \
    RT_ASSERT(!(cv)->waiting_mtx ||                                \
              rt_mutex_get_owner((rt_mutex_t)(cv)->waiting_mtx) == \
                  rt_thread_self())

void rt_condvar_init(rt_condvar_t cv, char *name)
{
#ifdef USING_RT_OBJECT
    /* TODO: support rt object */
    rt_object_init();
#endif

    rt_wqueue_init(&cv->event);
    rt_atomic_store(&cv->waiters_cnt, 0);
    rt_atomic_store(&cv->waiting_mtx, 0);
}

static int _waitq_inqueue(rt_wqueue_t *queue, struct rt_wqueue_node *node,
                          rt_tick_t timeout, int suspend_flag)
{
    rt_thread_t tcb = node->polling_thread;
    rt_timer_t timer = &(tcb->thread_timer);
    rt_err_t ret;

    if (queue->flag != RT_WQ_FLAG_WAKEUP)
    {
        ret = rt_thread_suspend_with_flag(tcb, suspend_flag);
        if (ret == RT_EOK)
        {
            rt_wqueue_add(queue, node);
            if (timeout != RT_WAITING_FOREVER)
            {
                rt_timer_control(timer, RT_TIMER_CTRL_SET_TIME, &timeout);

                rt_timer_start(timer);
            }
        }
    }
    else
    {
        ret = RT_EOK;
    }

    return ret;
}

#define INIT_WAITQ_NODE(node)                                  \
    {                                                          \
        .polling_thread = rt_thread_self(), .key = 0,          \
        .wakeup = __wqueue_default_wake, .wqueue = &cv->event, \
        .list = RT_LIST_OBJECT_INIT(node.list)                 \
    }

int rt_condvar_timedwait(rt_condvar_t cv, rt_mutex_t mtx, int suspend_flag,
                         rt_tick_t timeout)
{
    rt_err_t acq_mtx_succ, rc;
    rt_atomic_t waiting_mtx;
    struct rt_wqueue_node node = INIT_WAITQ_NODE(node);

    /* not allowed in IRQ & critical section */
    RT_DEBUG_SCHEDULER_AVAILABLE(1);
    CV_ASSERT_LOCKED(cv);

    /**
     * for the worst case, this is racy with the following works to reset field
     * before mutex is taken. The spinlock then comes to rescue.
     */
    rt_spin_lock(&_local_cv_queue_lock);
    waiting_mtx = rt_atomic_load(&cv->waiting_mtx);
    if (!waiting_mtx)
        acq_mtx_succ = rt_atomic_compare_exchange_strong(
            &cv->waiting_mtx, &waiting_mtx, (size_t)mtx);
    else
        acq_mtx_succ = 0;

    rt_spin_unlock(&_local_cv_queue_lock);

    if (acq_mtx_succ == 1 || waiting_mtx == (size_t)mtx)
    {
        rt_atomic_add(&cv->waiters_cnt, 1);

        rt_enter_critical();

        if (suspend_flag == RT_INTERRUPTIBLE)
            rc = _waitq_inqueue(&cv->event, &node, timeout, RT_INTERRUPTIBLE);
        else /* UNINTERRUPTIBLE is forbidden, since it's not safe for user space */
            rc = _waitq_inqueue(&cv->event, &node, timeout, RT_KILLABLE);

        acq_mtx_succ = rt_mutex_release(mtx);
        RT_ASSERT(acq_mtx_succ == 0);
        rt_exit_critical();

        if (rc == RT_EOK)
        {
            rt_schedule();

            rc = rt_get_errno();
            rc = rc > 0 ? -rc : rc;
        }
        else
        {
            LOG_D("%s() failed to suspend", __func__);
        }

        rt_wqueue_remove(&node);

        rt_spin_lock(&_local_cv_queue_lock);
        if (rt_atomic_add(&cv->waiters_cnt, -1) == 1)
        {
            waiting_mtx = (size_t)mtx;
            acq_mtx_succ = rt_atomic_compare_exchange_strong(&cv->waiting_mtx,
                                                      &waiting_mtx, 0);
            RT_ASSERT(acq_mtx_succ == 1);
        }
        rt_spin_unlock(&_local_cv_queue_lock);

        acq_mtx_succ = rt_mutex_take(mtx, RT_WAITING_FOREVER);
        RT_ASSERT(acq_mtx_succ == 0);
    }
    else
    {
        LOG_D("%s: conflict waiting mutex", __func__);
        rc = -EBUSY;
    }

    return rc;
}

/** Keep in mind that we always operating when cv.waiting_mtx is taken */

int rt_condvar_signal(rt_condvar_t cv)
{
    CV_ASSERT_LOCKED(cv);

    /* to avoid spurious wakeups */
    if (rt_atomic_load(&cv->waiters_cnt) > 0)
        rt_wqueue_wakeup(&cv->event, 0);

    cv->event.flag = 0;
    return 0;
}

int rt_condvar_broadcast(rt_condvar_t cv)
{
    CV_ASSERT_LOCKED(cv);

    /* to avoid spurious wakeups */
    if (rt_atomic_load(&cv->waiters_cnt) > 0)
        rt_wqueue_wakeup_all(&cv->event, 0);

    cv->event.flag = 0;
    return 0;
}
