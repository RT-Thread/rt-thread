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
#ifdef ARCH_MM_MMU
#include <lwp_user_mm.h>
#endif
#include "sys/time.h"

struct rt_futex
{
    int *uaddr;
    rt_list_t waiting_thread;
    struct lwp_avl_struct node;
    struct rt_object *custom_obj;
};

static struct rt_mutex _futex_lock;

static int futex_system_init(void)
{
    rt_mutex_init(&_futex_lock, "futexList", RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_PREV_EXPORT(futex_system_init);

rt_err_t futex_destory(void *data)
{
    rt_err_t ret = -1;
    rt_base_t level;
    struct rt_futex *futex = (struct rt_futex *)data;

    if (futex)
    {
        level = rt_hw_interrupt_disable();
        /* remove futex from futext avl */
        lwp_avl_remove(&futex->node, (struct lwp_avl_struct **)futex->node.data);
        rt_hw_interrupt_enable(level);

        /* release object */
        rt_free(futex);
        ret = 0;
    }
    return ret;
}

struct rt_futex *futex_create(int *uaddr, struct rt_lwp *lwp)
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
    futex->node.avl_key = (avl_key_t)uaddr;
    futex->node.data = &lwp->address_search_head;
    futex->custom_obj = obj;
    rt_list_init(&(futex->waiting_thread));

    /* insert into futex head */
    lwp_avl_insert(&futex->node, &lwp->address_search_head);
    return futex;
}

static struct rt_futex *futex_get(void *uaddr, struct rt_lwp *lwp)
{
    struct rt_futex *futex = RT_NULL;
    struct lwp_avl_struct *node = RT_NULL;

    node = lwp_avl_find((avl_key_t)uaddr, lwp->address_search_head);
    if (!node)
    {
        return RT_NULL;
    }
    futex = rt_container_of(node, struct rt_futex, node);
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
            rt_int32_t time = timeout->tv_sec * RT_TICK_PER_SECOND + timeout->tv_nsec * RT_TICK_PER_SECOND / NANOSECOND_PER_SECOND;

            if (time < 0)
            {
                time = 0;
            }

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
        rt_mutex_release(&_futex_lock);
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
        rt_list_remove(&(thread->tlist));

        thread->error = RT_EOK;
        /* resume the suspended thread */
        rt_thread_resume(thread);

        number--;
    }
    rt_mutex_release(&_futex_lock);
    rt_hw_interrupt_enable(level);

    /* do schedule */
    rt_schedule();
}

#include <syscall_generic.h>

sysret_t sys_futex(int *uaddr, int op, int val, const struct timespec *timeout,
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

    /**
     * if (op & (FUTEX_WAKE|FUTEX_FD|FUTEX_WAKE_BITSET|FUTEX_TRYLOCK_PI|FUTEX_UNLOCK_PI)) was TRUE
     * `timeout` should be ignored by implementation, according to POSIX futex(2) manual.
     * since only FUTEX_WAKE is implemented in rt-smart, only FUTEX_WAKE was omitted currently
     */
    if (timeout && !(op & (FUTEX_WAKE)))
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
        if (lwp_user_object_add(lwp, futex->custom_obj) != 0)
        {
            rt_custom_object_destroy(futex->custom_obj);
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
