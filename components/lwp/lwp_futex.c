/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/01/02     bernard      the first version
 */

#include <rtthread.h>
#include <lwp.h>
#ifdef RT_USING_USERSPACE
#include <lwp_user_mm.h>
#endif
#include "clock_time.h"

struct rt_futex
{
    int *uaddr;
    rt_list_t list;
    rt_list_t waiting_thread;
};

static struct rt_mutex _futex_lock;

static int futex_system_init(void)
{
    rt_mutex_init(&_futex_lock, "futexList", RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_PREV_EXPORT(futex_system_init);

void futex_destory(void *data)
{
    rt_base_t level = 0;
    struct rt_futex *futex = (struct rt_futex *)data;

    if (futex)
    {
        level = rt_hw_interrupt_disable();
        /* remove futex from list */
        rt_list_remove(&(futex->list));
        rt_hw_interrupt_enable(level);

        /* release object */
        rt_free(futex);
    }

    return ;
}

struct rt_futex* futex_create(int *uaddr, struct rt_lwp *lwp)
{
    struct rt_futex *futex = RT_NULL;
    struct rt_object *obj = RT_NULL;

    if (!lwp)
    {
        return RT_NULL;
    }
    futex = (struct rt_futex *)rt_malloc(sizeof(struct rt_futex));
    if (!futex)
    {
        return RT_NULL;
    }
    obj = rt_custom_object_create("futex", (void *)futex, futex_destory);
    if (!obj)
    {
        rt_free(futex);
        return RT_NULL;
    }

    futex->uaddr = uaddr;
    rt_list_init(&(futex->list));
    rt_list_init(&(futex->waiting_thread));

    /* insert into futex list */
    rt_list_insert_before(&lwp->futex_list, &(futex->list));
    return futex;
}

static struct rt_futex* futex_get(void *uaddr, struct rt_lwp *lwp)
{
    struct rt_futex *futex = RT_NULL;
    rt_list_t *node = RT_NULL;

    rt_list_for_each(node, &lwp->futex_list)
    {
        futex = rt_list_entry(node, struct rt_futex, list);

        if (futex->uaddr == uaddr) break;
    }

    /* no this futex in the list */
    if (node == &lwp->futex_list) futex = RT_NULL;

    return futex;
}

int futex_wait(struct rt_futex *futex, int value, const struct timespec *timeout)
{
    rt_base_t level = 0;
    rt_err_t ret = -RT_EINTR;

    if (*(futex->uaddr) == value)
    {
        rt_thread_t thread = rt_thread_self();

        level = rt_hw_interrupt_disable();
        ret = rt_thread_suspend_with_flag(thread, RT_INTERRUPTIBLE);

        if (ret < 0)
        {
            rt_mutex_release(&_futex_lock);
            rt_hw_interrupt_enable(level);
            rt_set_errno(EINTR);
            return ret;
        }

        /* add into waiting thread list */
        rt_list_insert_before(&(futex->waiting_thread), &(thread->tlist));

        /* with timeout */
        if (timeout)
        {
            rt_int32_t time = clock_time_to_tick(timeout);

            /* start the timer of thread */
            rt_timer_control(&(thread->thread_timer),
                    RT_TIMER_CTRL_SET_TIME,
                    &time);
            rt_timer_start(&(thread->thread_timer));
        }
        rt_mutex_release(&_futex_lock);
        rt_hw_interrupt_enable(level);

        /* do schedule */
        rt_schedule();

        ret = thread->error;
        /* check errno */
    }
    else
    {
        rt_set_errno(EAGAIN);
    }

    return ret;
}

void futex_wake(struct rt_futex *futex, int number)
{
    rt_base_t level = rt_hw_interrupt_disable();

    while (!rt_list_isempty(&(futex->waiting_thread)) && number)
    {
        rt_thread_t thread;

        thread = rt_list_entry(futex->waiting_thread.next, struct rt_thread, tlist);
        /* remove from waiting list */
        rt_list_remove(&(thread->list));

        thread->error = RT_EOK;
        /* resume the suspended thread */
        rt_thread_resume(thread);

        number --;
    }
    rt_mutex_release(&_futex_lock);
    rt_hw_interrupt_enable(level);

    /* do schedule */
    rt_schedule();
}

int sys_futex(int *uaddr, int op, int val, const struct timespec *timeout,
          int *uaddr2, int val3)
{
    struct rt_lwp *lwp = RT_NULL;
    struct rt_futex *futex = RT_NULL;
    int ret = 0;
    rt_err_t lock_ret = 0;

    if (!lwp_user_accessable(uaddr, sizeof(int)))
    {
        rt_set_errno(EINVAL);
        return -RT_EINVAL;
    }
    if (timeout)
    {
        if (!lwp_user_accessable((void *)timeout, sizeof(struct timespec)))
        {
            rt_set_errno(EINVAL);
            return -RT_EINVAL;
        }
    }

    lock_ret = rt_mutex_take_interruptible(&_futex_lock, RT_WAITING_FOREVER);
    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EAGAIN);
        return -RT_EINTR;
    }

    lwp = lwp_self();
    futex = futex_get(uaddr, lwp);
    if (futex == RT_NULL)
    {
        /* create a futex according to this uaddr */
        futex = futex_create(uaddr, lwp);
        if (futex == RT_NULL)
        {
            rt_mutex_release(&_futex_lock);
            rt_set_errno(ENOMEM);
            return -RT_ENOMEM;
        }
    }

    switch (op)
    {
        case FUTEX_WAIT:
            ret = futex_wait(futex, val, timeout);
            /* _futex_lock is released by futex_wait */
            break;

        case FUTEX_WAKE:
            futex_wake(futex, val);
            /* _futex_lock is released by futex_wake */
            break;

        default:
            rt_mutex_release(&_futex_lock);
            rt_set_errno(ENOSYS);
            ret = -ENOSYS;
            break;
    }

    return ret;
}
