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
    struct rt_lwp *lwp;
    rt_list_t waiting_thread;
};
static rt_list_t _futex_list = RT_LIST_OBJECT_INIT(_futex_list);

struct rt_futex* futex_create(int *uaddr, struct rt_lwp *lwp)
{
    struct rt_futex *futex = RT_NULL;

    futex = (struct rt_futex *)rt_malloc(sizeof(struct rt_futex));
    if (futex)
    {
        futex->uaddr = uaddr;
        futex->lwp = lwp;

        rt_list_init(&(futex->list));
        rt_list_init(&(futex->waiting_thread));

        /* insert into futex list */
        rt_list_insert_before(&_futex_list, &(futex->list));
    }
    return futex;
}

void futex_destory(struct rt_futex *futex)
{
    rt_base_t level = 0;

    if (futex)
    {
        level = rt_hw_interrupt_disable();
        /* remove futex from list */
        rt_list_remove(&(futex->list));
        rt_hw_interrupt_enable(level);

        /* wakeup all threads in suspending list */

        /* release object */
        rt_free(futex);
    }

    return ;
}

static struct rt_futex* futex_get(void *uaddr, struct rt_lwp *lwp)
{
    rt_base_t level = 0;
    struct rt_futex *futex = RT_NULL;
    rt_list_t *node = RT_NULL;

    level = rt_hw_interrupt_disable();

    rt_list_for_each(node, &_futex_list)
    {
        futex = rt_list_entry(node, struct rt_futex, list);

        if (futex->uaddr == uaddr && futex->lwp == lwp) break;
    }
    rt_hw_interrupt_enable(level);

    /* no this futex in the list */
    if (node == &_futex_list) futex = RT_NULL;

    return futex;
}

int futex_wait(struct rt_futex *futex, int value, const struct timespec *timeout)
{
    rt_base_t level = 0;
    rt_err_t ret = -RT_EINTR;

    level = rt_hw_interrupt_disable();
    if (*(futex->uaddr) == value)
    {
        rt_thread_t thread = rt_thread_self();

        ret = rt_thread_suspend_with_flag(thread, RT_INTERRUPTIBLE);

        if (ret < 0)
        {
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
        rt_hw_interrupt_enable(level);

        /* do schedule */
        rt_schedule();

        ret = thread->error;
        /* check errno */
    }
    else
    {
        rt_hw_interrupt_enable(level);
        rt_set_errno(EAGAIN);
    }

    return ret;
}

void futex_wake(struct rt_futex *futex, int number)
{
    rt_base_t level = 0;

    level = rt_hw_interrupt_disable();
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
    rt_hw_interrupt_enable(level);

    /* do schedule */
    rt_schedule();
}

int sys_futex(int *uaddr, int op, int val, const struct timespec *timeout,
          int *uaddr2, int val3)
{
    rt_base_t level = 0;
    struct rt_futex *futex = RT_NULL;
    struct rt_lwp *lwp = lwp_self();
    int ret = 0;

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

    level = rt_hw_interrupt_disable();
    futex = futex_get(uaddr, lwp);
    if (futex == RT_NULL)
    {
        /* create a futex according to this uaddr */
        futex = futex_create(uaddr, lwp);
        if (futex == RT_NULL)
        {
            rt_hw_interrupt_enable(level);
            rt_set_errno(ENOMEM);
            return -RT_ENOMEM;
        }
    }
    rt_hw_interrupt_enable(level);

    switch (op)
    {
        case FUTEX_WAIT:
            ret = futex_wait(futex, val, timeout);
            break;

        case FUTEX_WAKE:
            futex_wake(futex, val);
            break;

        default:
            rt_set_errno(ENOSYS);
            ret = -ENOSYS;
            break;
    }

    return ret;
}
