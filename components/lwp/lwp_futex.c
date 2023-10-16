/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/01/02     bernard      the first version
 * 2023-07-25     Shell        Remove usage of rt_hw_interrupt API in the lwp
 *                             Coding style: remove multiple `return` in a routine
 * 2023-08-08     Shell        Fix return value of futex(wait); Fix ops that only
 *                             FUTEX_PRIVATE is supported currently
 */
#define DBG_TAG "lwp.futex"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "lwp_internal.h"
#include "lwp_pid.h"

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

/* must have futex address_search_head taken */
static rt_err_t _futex_destroy_locked(void *data)
{
    rt_err_t ret = -1;
    struct rt_futex *futex = (struct rt_futex *)data;

    if (futex)
    {
        /**
         * Brief: Delete the futex from lwp address_search_head
         *
         * Note: Critical Section
         * - the lwp (READ. share by thread)
         * - the lwp address_search_head (RW. protected by caller. for destroy
         *   routine, it's always safe because it has already taken a write lock
         *    to the lwp.)
         */
        lwp_avl_remove(&futex->node, (struct lwp_avl_struct **)futex->node.data);

        /* release object */
        rt_free(futex);
        ret = 0;
    }
    return ret;
}

/* must have futex address_search_head taken */
static struct rt_futex *_futex_create_locked(int *uaddr, struct rt_lwp *lwp)
{
    struct rt_futex *futex = RT_NULL;
    struct rt_object *obj = RT_NULL;

    /**
     * Brief: Create a futex under current lwp
     *
     * Note: Critical Section
     * - lwp (READ; share with thread)
     */
    if (lwp)
    {
        futex = (struct rt_futex *)rt_malloc(sizeof(struct rt_futex));
        if (futex)
        {
            obj = rt_custom_object_create("futex", (void *)futex, _futex_destroy_locked);
            if (!obj)
            {
                rt_free(futex);
                futex = RT_NULL;
            }
            else
            {
                /**
                 * Brief: Add futex to user object tree for resource recycling
                 *
                 * Note: Critical Section
                 * - lwp user object tree (RW; protected by API)
                 * - futex (if the adding is successful, others can find the
                 *   unready futex. However, only the lwp_free will do this,
                 *   and this is protected by the ref taken by the lwp thread
                 *   that the lwp_free will never execute at the same time)
                 */
                if (lwp_user_object_add(lwp, obj))
                {
                    rt_object_delete(obj);
                    rt_free(futex);
                    futex = RT_NULL;
                }
                else
                {
                    futex->uaddr = uaddr;
                    futex->node.avl_key = (avl_key_t)uaddr;
                    futex->node.data = &lwp->address_search_head;
                    futex->custom_obj = obj;
                    rt_list_init(&(futex->waiting_thread));

                    /**
                     * Brief: Insert into futex head
                     *
                     * Note: Critical Section
                     * - lwp address_search_head (RW; protected by caller)
                     */
                    lwp_avl_insert(&futex->node, &lwp->address_search_head);
                }
            }
        }
    }
    return futex;
}

/* must have futex address_search_head taken */
static struct rt_futex *_futex_get_locked(void *uaddr, struct rt_lwp *lwp)
{
    struct rt_futex *futex = RT_NULL;
    struct lwp_avl_struct *node = RT_NULL;

    /**
     * Note: Critical Section
     * protect lwp address_search_head (READ)
     */
    node = lwp_avl_find((avl_key_t)uaddr, lwp->address_search_head);
    if (!node)
    {
        return RT_NULL;
    }
    futex = rt_container_of(node, struct rt_futex, node);
    return futex;
}

static int _futex_wait(struct rt_futex *futex, struct rt_lwp *lwp, int value, const struct timespec *timeout)
{
    rt_thread_t thread;
    rt_err_t ret = -RT_EINTR;

    /**
     * Brief: Remove current thread from scheduler, besides appends it to
     * the waiting thread list of the futex. If the timeout is specified
     * a timer will be setup for current thread
     *
     * Note: Critical Section
     * - futex (RW; Protected by lwp_lock)
     * - the local cpu
     */
    LWP_LOCK(lwp);
    if (*(futex->uaddr) == value)
    {
        thread = rt_thread_self();

        rt_enter_critical();

        ret = rt_thread_suspend_with_flag(thread, RT_INTERRUPTIBLE);

        if (ret == RT_EOK)
        {
            /**
             * Brief: Add current thread into futex waiting thread list
             *
             * Note: Critical Section
             * - the futex waiting_thread list (RW)
             */
            rt_list_insert_before(&(futex->waiting_thread), &(thread->tlist));

            if (timeout)
            {
                /* start the timer of thread */
                rt_int32_t time = timeout->tv_sec * RT_TICK_PER_SECOND + timeout->tv_nsec * RT_TICK_PER_SECOND / NANOSECOND_PER_SECOND;

                if (time < 0)
                {
                    time = 0;
                }

                rt_timer_control(&(thread->thread_timer),
                                 RT_TIMER_CTRL_SET_TIME,
                                 &time);
                rt_timer_start(&(thread->thread_timer));
            }
        }
        else
        {
            ret = EINTR;
        }

        LWP_UNLOCK(lwp);
        rt_exit_critical();

        if (ret == RT_EOK)
        {
            /* do schedule */
            rt_schedule();
            /* check errno */
            ret = rt_get_errno();
        }

        ret = ret > 0 ? -ret : ret;
        switch (ret)
        {
            case RT_EOK:
                ret = 0;
                break;
            case -RT_EINTR:
                ret = -EINTR;
                break;
            default:
                ret = -EAGAIN;
                break;
        }
    }
    else
    {
        LWP_UNLOCK(lwp);
        ret = -EAGAIN;
        rt_set_errno(EAGAIN);
    }

    return ret;
}

static long _futex_wake(struct rt_futex *futex, struct rt_lwp *lwp, int number)
{
    long woken_cnt = 0;
    int is_empty = 0;
    rt_thread_t thread;

    /**
     * Brief: Wakeup a suspended thread on the futex waiting thread list
     *
     * Note: Critical Section
     * - the futex waiting_thread list (RW)
     */
    while (number && !is_empty)
    {
        LWP_LOCK(lwp);
        is_empty = rt_list_isempty(&(futex->waiting_thread));
        if (!is_empty)
        {
            thread = rt_list_entry(futex->waiting_thread.next, struct rt_thread, tlist);
            /* remove from waiting list */
            rt_list_remove(&(thread->tlist));

            thread->error = RT_EOK;
            /* resume the suspended thread */
            rt_thread_resume(thread);

            number--;
            woken_cnt++;
        }
        LWP_UNLOCK(lwp);
    }

    /* do schedule */
    rt_schedule();
    return woken_cnt;
}

#include <syscall_generic.h>

rt_inline rt_bool_t _timeout_ignored(int op)
{
    /**
     * if (op & (FUTEX_WAKE|FUTEX_FD|FUTEX_WAKE_BITSET|FUTEX_TRYLOCK_PI|FUTEX_UNLOCK_PI)) was TRUE
     * `timeout` should be ignored by implementation, according to POSIX futex(2) manual.
     * since only FUTEX_WAKE is implemented in rt-smart, only FUTEX_WAKE was omitted currently
     */
    return (op & (FUTEX_WAKE));
}

sysret_t sys_futex(int *uaddr, int op, int val, const struct timespec *timeout,
                   int *uaddr2, int val3)
{
    struct rt_lwp *lwp = RT_NULL;
    struct rt_futex *futex = RT_NULL;
    sysret_t ret = 0;

    if (!lwp_user_accessable(uaddr, sizeof(int)))
    {
        ret = -EINVAL;
    }
    else if (timeout && !_timeout_ignored(op) && !lwp_user_accessable((void *)timeout, sizeof(struct timespec)))
    {
        ret = -EINVAL;
    }
    else
    {
        lwp = lwp_self();
        ret = lwp_futex(lwp, futex, uaddr, op, val, timeout);
    }

    return ret;
}

rt_err_t lwp_futex(struct rt_lwp *lwp, struct rt_futex *futex, int *uaddr, int op, int val, const struct timespec *timeout)
{
    rt_err_t rc = 0;

    /**
     * Brief: Check if the futex exist, otherwise create a new one
     *
     * Note: Critical Section
     * - lwp address_search_head (READ)
     */
    LWP_LOCK(lwp);
    futex = _futex_get_locked(uaddr, lwp);
    if (futex == RT_NULL)
    {
        /* create a futex according to this uaddr */
        futex = _futex_create_locked(uaddr, lwp);
        if (futex == RT_NULL)
        {
            rc = -ENOMEM;
        }
    }
    LWP_UNLOCK(lwp);

    if (!rc)
    {
        if (!(op & FUTEX_PRIVATE))
            rc = -ENOSYS;
        else
        {
            op &= ~FUTEX_PRIVATE;
            switch (op)
            {
                case FUTEX_WAIT:
                    rc = _futex_wait(futex, lwp, val, timeout);
                    break;
                case FUTEX_WAKE:
                    rc = _futex_wake(futex, lwp, val);
                    break;
                default:
                    LOG_W("User require op=%d which is not implemented", op);
                    rc = -ENOSYS;
                    break;
            }
        }
    }

    return rc;
}
