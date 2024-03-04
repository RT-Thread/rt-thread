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
 * 2023-11-03     Shell        Add Support for ~FUTEX_PRIVATE
 * 2023-11-16     xqyjlj       Add Support for futex requeue and futex pi
 */
#define __RT_IPC_SOURCE__

#include "lwp_futex_internal.h"
#include "sys/time.h"
#include <stdatomic.h>

struct rt_mutex _glob_futex;

rt_err_t lwp_futex_init(void)
{
    return rt_mutex_init(&_glob_futex, "glob_ftx", RT_IPC_FLAG_PRIO);
}

static void _futex_lock(rt_lwp_t lwp, int op_flags)
{
    rt_err_t error;
    if (op_flags & FUTEX_PRIVATE)
    {
        LWP_LOCK(lwp);
    }
    else
    {
        error = lwp_mutex_take_safe(&_glob_futex, RT_WAITING_FOREVER, 0);
        if (error)
        {
            LOG_E("%s: Should not failed", __func__);
            RT_ASSERT(0);
        }
    }
}

static void _futex_unlock(rt_lwp_t lwp, int op_flags)
{
    rt_err_t error;
    if (op_flags & FUTEX_PRIVATE)
    {
        LWP_UNLOCK(lwp);
    }
    else
    {
        error = lwp_mutex_release_safe(&_glob_futex);
        if (error)
        {
            LOG_E("%s: Should not failed", __func__);
            RT_ASSERT(0);
        }
    }
}

/**
 * Destroy a Private FuTeX (pftx)
 * Note: must have futex address_search_head taken
 */
static rt_err_t _pftx_destroy_locked(void *data)
{
    rt_err_t ret = -1;
    rt_futex_t futex = (rt_futex_t)data;

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
        lwp_avl_remove(&futex->node,
                       (struct lwp_avl_struct **)futex->node.data);

        /* release object */
        if (futex->mutex)
        {
            rt_mutex_delete(futex->mutex);
            futex->mutex = RT_NULL;
        }
        rt_free(futex);
        ret = 0;
    }
    return ret;
}

/**
 * Create a Private FuTeX (pftx)
 * Note: must have futex address_search_head taken
 */
static rt_futex_t _pftx_create_locked(int *uaddr, struct rt_lwp *lwp)
{
    rt_futex_t futex = RT_NULL;
    struct rt_object *obj = RT_NULL;

    /**
     * Brief: Create a futex under current lwp
     *
     * Note: Critical Section
     * - lwp (READ; share with thread)
     */
    if (lwp)
    {
        futex = (rt_futex_t)rt_malloc(sizeof(struct rt_futex));
        if (futex)
        {
            /* Create a Private FuTeX (pftx) */
            obj = rt_custom_object_create("pftx", (void *)futex,
                                          _pftx_destroy_locked);
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
                    /* this will call a _pftx_destroy_locked, but that's okay */
                    rt_object_delete(obj);
                    rt_free(futex);
                    futex = RT_NULL;
                }
                else
                {
                    futex->node.avl_key = (avl_key_t)uaddr;
                    futex->node.data = &lwp->address_search_head;
                    futex->custom_obj = obj;
                    futex->mutex = RT_NULL;
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

/**
 * Get a Private FuTeX (pftx) match the (lwp, uaddr, op)
 */
static rt_futex_t _pftx_get(void *uaddr, struct rt_lwp *lwp, int op,
                            rt_err_t *rc)
{
    struct lwp_avl_struct *node = RT_NULL;
    rt_futex_t futex = RT_NULL;
    rt_err_t error = -1;

    LWP_LOCK(lwp);

    /**
     * Note: Critical Section
     * protect lwp address_search_head (READ)
     */
    node = lwp_avl_find((avl_key_t)uaddr, lwp->address_search_head);
    if (node)
    {
        futex = rt_container_of(node, struct rt_futex, node);
        error = 0;
    }
    else
    {
        /* create a futex according to this uaddr */
        futex = _pftx_create_locked(uaddr, lwp);

        if (!futex)
            error = -ENOMEM;
        else
            error = 0;
    }
    LWP_UNLOCK(lwp);

    *rc = error;
    return futex;
}

/**
 * Destroy a Shared FuTeX (pftx)
 * Note: must have futex address_search_head taken
 */
static rt_err_t _sftx_destroy(void *data)
{
    rt_err_t ret = -1;
    rt_futex_t futex = (rt_futex_t)data;

    if (futex)
    {
        /* delete it even it's not in the table */
        futex_global_table_delete(&futex->entry.key);
        if (futex->mutex)
        {
            rt_mutex_delete(futex->mutex);
            futex->mutex = RT_NULL;
        }
        rt_free(futex);
        ret = 0;
    }
    return ret;
}

/**
 * Create a Shared FuTeX (sftx)
 */
static rt_futex_t _sftx_create(struct shared_futex_key *key, struct rt_lwp *lwp)
{
    rt_futex_t futex = RT_NULL;
    struct rt_object *obj = RT_NULL;

    if (lwp)
    {
        futex = (rt_futex_t)rt_calloc(1, sizeof(struct rt_futex));
        if (futex)
        {
            /* create a Shared FuTeX (sftx) */
            obj = rt_custom_object_create("sftx", (void *)futex, _sftx_destroy);
            if (!obj)
            {
                rt_free(futex);
                futex = RT_NULL;
            }
            else
            {
                if (futex_global_table_add(key, futex))
                {
                    rt_object_delete(obj);
                    rt_free(futex);
                    futex = RT_NULL;
                }
                else
                {
                    futex->mutex = RT_NULL;
                    rt_list_init(&(futex->waiting_thread));
                    futex->custom_obj = obj;
                }
            }
        }
    }
    return futex;
}

/**
 * Get a Shared FuTeX (sftx) match the (lwp, uaddr, op)
 */
static rt_futex_t _sftx_get(void *uaddr, struct rt_lwp *lwp, int op,
                            rt_err_t *rc)
{
    rt_futex_t futex = RT_NULL;
    struct shared_futex_key key;
    rt_varea_t varea;
    rt_err_t error = -1;

    RD_LOCK(lwp->aspace);
    varea = rt_aspace_query(lwp->aspace, uaddr);
    if (varea)
    {
        key.mobj = varea->mem_obj;
        key.offset = ((varea->offset) << MM_PAGE_SHIFT) |
                     ((long)uaddr & ((1 << MM_PAGE_SHIFT) - 1));
        RD_UNLOCK(lwp->aspace);

        /* query for the key */
        _futex_lock(lwp, op & ~FUTEX_PRIVATE);
        error = futex_global_table_find(&key, &futex);
        if (error != RT_EOK)
        {
            /* not found, do allocation */
            futex = _sftx_create(&key, lwp);
            if (!futex)
                error = -ENOMEM;
            else
                error = 0;
        }
        _futex_unlock(lwp, op & ~FUTEX_PRIVATE);
    }
    else
    {
        RD_UNLOCK(lwp->aspace);
    }

    *rc = error;
    return futex;
}

/* must have futex address_search_head taken */
static rt_futex_t _futex_get(void *uaddr, struct rt_lwp *lwp, int op_flags,
                             rt_err_t *rc)
{
    rt_futex_t futex = RT_NULL;

    if (op_flags & FUTEX_PRIVATE)
    {
        futex = _pftx_get(uaddr, lwp, op_flags, rc);
    }
    else
    {
        futex = _sftx_get(uaddr, lwp, op_flags, rc);
    }

    return futex;
}

static rt_err_t _suspend_thread_timeout_locked(rt_thread_t thread,
                                               rt_futex_t futex,
                                               rt_tick_t timeout)
{
    rt_err_t rc;

    /**
     * Brief: Add current thread into futex waiting thread list
     *
     * Note: Critical Section
     * - the futex waiting_thread list (RW)
     */
    rc = rt_thread_suspend_to_list(thread, &futex->waiting_thread,
                                   RT_IPC_FLAG_FIFO, RT_INTERRUPTIBLE);

    if (rc == RT_EOK)
    {
        /* start the timer of thread */
        rt_timer_control(&(thread->thread_timer), RT_TIMER_CTRL_SET_TIME,
                         &timeout);
        rt_timer_start(&(thread->thread_timer));
        rt_set_errno(ETIMEDOUT);
    }

    return rc;
}

static rt_err_t _suspend_thread_locked(rt_thread_t thread, rt_futex_t futex)
{
    /**
     * Brief: Add current thread into futex waiting thread list
     *
     * Note: Critical Section
     * - the futex waiting_thread list (RW)
     */
    return rt_thread_suspend_to_list(thread, &futex->waiting_thread,
                                     RT_IPC_FLAG_FIFO, RT_INTERRUPTIBLE);
}

rt_inline int _futex_cmpxchg_value(int *curval, int *uaddr, int uval,
                                   int newval)
{
    int err = 0;

    if (!lwp_user_accessable((void *)uaddr, sizeof(*uaddr)))
    {
        err = -EFAULT;
        goto exit;
    }

    if (!atomic_compare_exchange_strong(uaddr, &uval, newval))
    {
        *curval = uval;
        err = -EAGAIN;
    }

exit:
    return err;
}

static int _futex_wait(rt_futex_t futex, struct rt_lwp *lwp, int *uaddr,
                       int value, const struct timespec *timeout, int op_flags)
{
    rt_tick_t to;
    rt_thread_t thread;
    rt_err_t rc = -RT_EINTR;

    /**
     * Brief: Remove current thread from scheduler, besides appends it to
     * the waiting thread list of the futex. If the timeout is specified
     * a timer will be setup for current thread
     *
     * Note: Critical Section
     * - futex.waiting (RW; Protected by lwp_lock)
     * - the local cpu
     */
    _futex_lock(lwp, op_flags);
    if (*uaddr == value)
    {
        thread = rt_thread_self();

        if (timeout)
        {
            to = timeout->tv_sec * RT_TICK_PER_SECOND;
            to +=
                (timeout->tv_nsec * RT_TICK_PER_SECOND) / NANOSECOND_PER_SECOND;

            if (to < 0)
            {
                rc = -EINVAL;
                _futex_unlock(lwp, op_flags);
            }
            else
            {
                rt_enter_critical();
                rc = _suspend_thread_timeout_locked(thread, futex, to);
                _futex_unlock(lwp, op_flags);
                rt_exit_critical();
            }
        }
        else
        {
            rt_enter_critical();
            rc = _suspend_thread_locked(thread, futex);
            _futex_unlock(lwp, op_flags);
            rt_exit_critical();
        }

        if (rc == RT_EOK)
        {
            /* do schedule */
            rt_schedule();
            /* check errno */
            rc = rt_get_errno();
            rc = rc > 0 ? -rc : rc;
        }
    }
    else
    {
        _futex_unlock(lwp, op_flags);
        rc = -EAGAIN;
        rt_set_errno(EAGAIN);
    }

    return rc;
}

static long _futex_wake(rt_futex_t futex, struct rt_lwp *lwp, int number,
                        int op_flags)
{
    long woken_cnt = 0;
    int is_empty = 0;

    /**
     * Brief: Wakeup a suspended thread on the futex waiting thread list
     *
     * Note: Critical Section
     * - the futex waiting_thread list (RW)
     */
    while (number && !is_empty)
    {
        _futex_lock(lwp, op_flags);
        if (rt_susp_list_dequeue(&futex->waiting_thread, RT_EOK))
        {
            number--;
            woken_cnt++;
            is_empty = RT_FALSE;
        }
        else
        {
            is_empty = RT_TRUE;
        }
        _futex_unlock(lwp, op_flags);
    }

    /* do schedule */
    rt_schedule();
    return woken_cnt;
}

/**
 *  Brief: Wake up to nr_wake futex1 threads.
 *      If there are more waiters waiting on futex1 than nr_wake,
 *      insert the remaining at most nr_requeue waiters waiting
 *      on futex1 into the waiting queue of futex2.
 */
static long _futex_requeue(rt_futex_t futex1, rt_futex_t futex2,
                           struct rt_lwp *lwp, int nr_wake, int nr_requeue,
                           int opflags)
{
    long rtn;
    long woken_cnt = 0;
    int is_empty = 0;
    rt_thread_t thread;

    if (futex1 == futex2)
    {
        return -EINVAL;
    }

    /**
     * Brief: Wakeup a suspended thread on the futex waiting thread list
     *
     * Note: Critical Section
     * - the futex waiting_thread list (RW)
     */
    while (nr_wake && !is_empty)
    {
        if (rt_susp_list_dequeue(&futex1->waiting_thread, RT_EOK))
        {
            nr_wake--;
            woken_cnt++;
            is_empty = RT_FALSE;
        }
        else
        {
            is_empty = RT_TRUE;
        }
    }
    rtn = woken_cnt;

    /**
     * Brief: Requeue
     *
     * Note: Critical Section
     * - the futex waiting_thread list (RW)
     */
    while (!is_empty && nr_requeue)
    {
        rt_sched_lock_level_t slvl;
        rt_sched_lock(&slvl);

        /* moving from one susp list to another */
        is_empty = rt_list_isempty(&(futex1->waiting_thread));

        if (!is_empty)
        {
            thread = RT_THREAD_LIST_NODE_ENTRY(futex1->waiting_thread.next);
            rt_list_remove(&RT_THREAD_LIST_NODE(thread));
            rt_list_insert_before(&(futex2->waiting_thread),
                                  &RT_THREAD_LIST_NODE(thread));
            nr_requeue--;
            rtn++;
        }
        rt_sched_unlock(slvl);
    }

    /* do schedule */
    rt_schedule();

    return rtn;
}

/* timeout argument measured against the CLOCK_REALTIME clock. */
static long _futex_lock_pi(rt_futex_t futex, struct rt_lwp *lwp, int *uaddr,
                           const struct timespec *timeout, int op_flags,
                           rt_bool_t trylock)
{
    int word = 0, nword, cword;
    int tid = 0;
    rt_err_t err = 0;
    rt_thread_t thread = RT_NULL, current_thread = RT_NULL;
    rt_tick_t to = RT_WAITING_FOREVER;

    if (!lwp_user_accessable((void *)uaddr, sizeof(*uaddr)))
    {
        return -EFAULT;
    }

    current_thread = rt_thread_self();

    _futex_lock(lwp, op_flags);

    lwp_get_from_user(&word, (void *)uaddr, sizeof(int));
    tid = word & FUTEX_TID_MASK;
    if (word == 0)
    {
        /* If the value is 0, then the kernel tries
             to atomically set the futex value to the caller's TID.  */
        nword = current_thread->tid;
        if (_futex_cmpxchg_value(&cword, uaddr, word, nword))
        {
            _futex_unlock(lwp, op_flags);
            return -EAGAIN;
        }
        _futex_unlock(lwp, op_flags);
        return 0;
    }
    else
    {
        thread = lwp_tid_get_thread_and_inc_ref(tid);
        if (thread == RT_NULL)
        {
            _futex_unlock(lwp, op_flags);
            return -ESRCH;
        }
        lwp_tid_dec_ref(thread);

        nword =
            word | FUTEX_WAITERS;
        if (_futex_cmpxchg_value(&cword, uaddr, word, nword))
        {
            _futex_unlock(lwp, op_flags);
            return -EAGAIN;
        }
        word = nword;
    }

    if (futex->mutex == RT_NULL)
    {
        futex->mutex = rt_mutex_create("futexpi", RT_IPC_FLAG_PRIO);
        if (futex->mutex == RT_NULL)
        {
            _futex_unlock(lwp, op_flags);
            return -ENOMEM;
        }

        /* set mutex->owner */
        rt_spin_lock(&(futex->mutex->spinlock));
        futex->mutex->owner = thread;
        futex->mutex->hold = 1;
        rt_spin_unlock(&(futex->mutex->spinlock));
    }
    if (timeout)
    {
        to = rt_timespec_to_tick(timeout);
    }

    if (trylock)
    {
        to = RT_WAITING_NO;
    }
    _futex_unlock(lwp, op_flags);

    err = rt_mutex_take_interruptible(futex->mutex, to);
    if (err == -RT_ETIMEOUT)
    {
        err = -EDEADLK;
    }

    _futex_lock(lwp, op_flags);
    nword = current_thread->tid | FUTEX_WAITERS;
    if (_futex_cmpxchg_value(&cword, uaddr, word, nword))
    {
        err = -EAGAIN;
    }
    _futex_unlock(lwp, op_flags);

    return err;
}

static long _futex_unlock_pi(rt_futex_t futex, struct rt_lwp *lwp, int op_flags)
{
    rt_err_t err = 0;
    _futex_lock(lwp, op_flags);
    if (!futex->mutex)
    {
        _futex_unlock(lwp, op_flags);
        return -EPERM;
    }
    _futex_unlock(lwp, op_flags);

    err = rt_mutex_release(futex->mutex);
    return err;
}

#include <syscall_generic.h>

rt_inline rt_bool_t _timeout_ignored(int op)
{
    /**
     * if (op &
     * (FUTEX_WAKE|FUTEX_FD|FUTEX_WAKE_BITSET|FUTEX_TRYLOCK_PI|FUTEX_UNLOCK_PI))
     * was TRUE `timeout` should be ignored by implementation, according to
     * POSIX futex(2) manual. since only FUTEX_WAKE is implemented in rt-smart,
     * only FUTEX_WAKE was omitted currently
     */
    return ((op & (FUTEX_WAKE)) || (op & (FUTEX_REQUEUE)) ||
            (op & (FUTEX_CMP_REQUEUE)) || (op & (FUTEX_UNLOCK_PI)) ||
            (op & (FUTEX_TRYLOCK_PI)));
}

sysret_t sys_futex(int *uaddr, int op, int val, const struct timespec *timeout,
                   int *uaddr2, int val3)
{
    struct rt_lwp *lwp = RT_NULL;
    sysret_t ret = 0;

    if (!lwp_user_accessable(uaddr, sizeof(int)))
    {
        ret = -EFAULT;
    }
    else if (timeout && !_timeout_ignored(op) &&
             !lwp_user_accessable((void *)timeout, sizeof(struct timespec)))
    {
        ret = -EINVAL;
    }
    else
    {
        lwp = lwp_self();
        ret = lwp_futex(lwp, uaddr, op, val, timeout, uaddr2, val3);
    }

    return ret;
}

#define FUTEX_FLAGS (FUTEX_PRIVATE | FUTEX_CLOCK_REALTIME)
rt_err_t lwp_futex(struct rt_lwp *lwp, int *uaddr, int op, int val,
                   const struct timespec *timeout, int *uaddr2, int val3)
{
    rt_futex_t futex, futex2;
    rt_err_t rc = 0;
    int op_type = op & ~FUTEX_FLAGS;
    int op_flags = op & FUTEX_FLAGS;

    futex = _futex_get(uaddr, lwp, op_flags, &rc);
    if (!rc)
    {
        switch (op_type)
        {
            case FUTEX_WAIT:
                rc = _futex_wait(futex, lwp, uaddr, val, timeout, op_flags);
                break;
            case FUTEX_WAKE:
                rc = _futex_wake(futex, lwp, val, op_flags);
                break;
            case FUTEX_REQUEUE:
                futex2 = _futex_get(uaddr2, lwp, op_flags, &rc);
                if (!rc)
                {
                    _futex_lock(lwp, op_flags);
                    rc = _futex_requeue(futex, futex2, lwp, val, (long)timeout,
                                        op_flags);
                    _futex_unlock(lwp, op_flags);
                }
                break;
            case FUTEX_CMP_REQUEUE:
                futex2 = _futex_get(uaddr2, lwp, op_flags, &rc);
                _futex_lock(lwp, op_flags);
                if (*uaddr == val3)
                {
                    rc = 0;
                }
                else
                {
                    rc = -EAGAIN;
                }
                if (rc == 0)
                {
                    rc = _futex_requeue(futex, futex2, lwp, val,
                                        (long)timeout, op_flags);
                }
                _futex_unlock(lwp, op_flags);
                break;
            case FUTEX_LOCK_PI:
                rc = _futex_lock_pi(futex, lwp, uaddr, timeout, op_flags,
                                    RT_FALSE);
                break;
            case FUTEX_UNLOCK_PI:
                rc = _futex_unlock_pi(futex, lwp, op_flags);
                break;
            case FUTEX_TRYLOCK_PI:
                rc = _futex_lock_pi(futex, lwp, uaddr, 0, op_flags, RT_TRUE);
                break;
            default:
                LOG_W("User require op=%d which is not implemented", op);
                rc = -ENOSYS;
                break;
        }
    }

    return rc;
}

rt_inline int _fetch_robust_entry(struct robust_list **entry,
                                  struct robust_list **head, rt_bool_t *is_pi)
{
    unsigned long uentry;

    if (!lwp_user_accessable((void *)head, sizeof(*head)))
    {
        return -EFAULT;
    }

    if (lwp_get_from_user(&uentry, (void *)head, sizeof(*head)) !=
        sizeof(*head))
    {
        return -EFAULT;
    }

    *entry = (void *)(uentry & ~1UL);
    *is_pi = uentry & 1;

    return 0;
}

static int _handle_futex_death(int *uaddr, rt_thread_t thread, rt_bool_t is_pi,
                               rt_bool_t is_pending_op)
{
    int word, cword = 0, nword;
    rt_err_t rc;
    struct rt_lwp *lwp;
    rt_futex_t futex;

    /* Futex address must be 32bit aligned */
    if ((((unsigned long)uaddr) % sizeof(*uaddr)) != 0)
        return -1;

    lwp = thread->lwp;
retry:

    if (!lwp_user_accessable((void *)uaddr, sizeof(*uaddr)))
    {
        return -1;
    }

    if (lwp_get_from_user(&word, (void *)uaddr, sizeof(*uaddr)) !=
        sizeof(*uaddr))
    {
        return -1;
    }

    futex = _futex_get(uaddr, lwp, FUTEX_PRIVATE, &rc);
    if (is_pending_op && !is_pi && !word)
    {
        _futex_wake(futex, lwp, 1, FUTEX_PRIVATE);
        return 0;
    }

    if ((word & FUTEX_TID_MASK) != thread->tid)
        return 0;

    nword = (word & FUTEX_WAITERS) | FUTEX_OWNER_DIED;

    if ((rc = _futex_cmpxchg_value(&cword, uaddr, word, nword)))
    {
        switch (rc)
        {
            case -EFAULT:
                return -1;
            case -EAGAIN:
                rt_schedule();
                goto retry;
            default:
                LOG_W("unknown errno: %d in '%s'", rc, __FUNCTION__);
                return rc;
        }
    }

    if (cword != word)
        goto retry;

    if (!is_pi && (word & FUTEX_WAITERS))
        _futex_wake(futex, lwp, 1, FUTEX_PRIVATE);

    return 0;
}

/**
 *  Brief: Walk thread->robust_list mark
 *      any locks found there dead, and notify any waiters.
 *
 *  note: very carefully, it's a userspace list!
 */
void lwp_futex_exit_robust_list(rt_thread_t thread)
{
    struct robust_list *entry = RT_NULL;
    struct robust_list *next_entry = RT_NULL;
    struct robust_list *pending = RT_NULL;
    struct robust_list_head *head;
    unsigned int limit = 2048;
    rt_bool_t pi, pip, next_pi;
    unsigned long futex_offset;
    int rc;

    head = thread->robust_list;

    if (head == RT_NULL)
        return;

    if (_fetch_robust_entry(&entry, &head->list.next, &pi))
        return;

    if (!lwp_user_accessable((void *)&head->futex_offset,
                             sizeof(head->futex_offset)))
    {
        return;
    }

    if (lwp_get_from_user(&futex_offset, (void *)&head->futex_offset,
                          sizeof(head->futex_offset)) !=
        sizeof(head->futex_offset))
    {
        return;
    }

    if (_fetch_robust_entry(&pending, &head->list_op_pending, &pip))
    {
        return;
    }

    while (entry != &head->list)
    {
        rc = _fetch_robust_entry(&next_entry, &entry->next, &next_pi);
        if (entry != pending)
        {
            if (_handle_futex_death((void *)entry + futex_offset, thread, pi,
                                    RT_FALSE))
                return;
        }
        if (rc)
            return;
        entry = next_entry;
        pi = next_pi;

        if (!--limit)
            break;
    }

    if (pending)
    {
        _handle_futex_death((void *)pending + futex_offset, thread, pip,
                            RT_TRUE);
    }
}
