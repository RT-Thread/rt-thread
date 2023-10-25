/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/01/02     bernard      the first version
 * 2022/12/18     bernard      fix the _m_lock to tid in user land.
 */

#include "lwp_internal.h"
#include <rtthread.h>
#ifdef ARCH_MM_MMU
#include <lwp_user_mm.h>
#endif
#include <sys/time.h>
#include <syscall_generic.h>

#define PMUTEX_NORMAL     0 /* Unable to recursion */
#define PMUTEX_RECURSIVE  1 /* Can be recursion */
#define PMUTEX_ERRORCHECK 2 /* This type of mutex provides error checking */

struct rt_pmutex
{
    union
    {
        rt_mutex_t kmutex;
        rt_sem_t ksem; /* use sem to emulate the mutex without recursive */
    } lock;

    struct lwp_avl_struct node;
    struct rt_object *custom_obj;
    rt_uint8_t type; /* pmutex type */
};

/*
 * userspace mutex definitions in musl
 */
struct rt_umutex
{
    union
    {
        int __i[6];
        volatile int __vi[6];
        volatile void *volatile __p[6];
    } __u;
};
#define _m_type     __u.__i[0]
#define _m_lock     __u.__vi[1]
#define _m_waiters  __u.__vi[2]
#define _m_prev     __u.__p[3]
#define _m_next     __u.__p[4]
#define _m_count    __u.__i[5]

static struct rt_mutex _pmutex_lock;

static int pmutex_system_init(void)
{
    rt_mutex_init(&_pmutex_lock, "pmtxLock", RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_PREV_EXPORT(pmutex_system_init);

static rt_err_t pmutex_destory(void *data)
{
    rt_err_t ret = -1;
    struct rt_pmutex *pmutex = (struct rt_pmutex *)data;

    if (pmutex)
    {
        lwp_mutex_take_safe(&_pmutex_lock, RT_WAITING_FOREVER, 0);
        /* remove pmutex from pmutext avl */
        lwp_avl_remove(&pmutex->node, (struct lwp_avl_struct **)pmutex->node.data);
        lwp_mutex_release_safe(&_pmutex_lock);

        if (pmutex->type == PMUTEX_NORMAL)
        {
            rt_sem_delete(pmutex->lock.ksem);
        }
        else
        {
            rt_mutex_delete(pmutex->lock.kmutex);
        }

        /* release object */
        rt_free(pmutex);
        ret = 0;
    }
    return ret;
}

static struct rt_pmutex* pmutex_create(void *umutex, struct rt_lwp *lwp)
{
    struct rt_pmutex *pmutex = RT_NULL;
    struct rt_object *obj = RT_NULL;
    rt_ubase_t type;

    if (!lwp)
    {
        return RT_NULL;
    }

    long *p = (long *)umutex;
    /* umutex[0] bit[0-1] saved mutex type */
    type = *p & 3;
    if (type != PMUTEX_NORMAL && type != PMUTEX_RECURSIVE && type != PMUTEX_ERRORCHECK)
    {
        return RT_NULL;
    }

    pmutex = (struct rt_pmutex *)rt_malloc(sizeof(struct rt_pmutex));
    if (!pmutex)
    {
        return RT_NULL;
    }

    if (type == PMUTEX_NORMAL)
    {
        pmutex->lock.ksem = rt_sem_create("pmutex", 1, RT_IPC_FLAG_PRIO);
        if (!pmutex->lock.ksem)
        {
            rt_free(pmutex);
            return RT_NULL;
        }
    }
    else
    {
        pmutex->lock.kmutex = rt_mutex_create("pmutex", RT_IPC_FLAG_PRIO);
        if (!pmutex->lock.kmutex)
        {
            rt_free(pmutex);
            return RT_NULL;
        }
    }

    obj = rt_custom_object_create("pmutex", (void *)pmutex, pmutex_destory);
    if (!obj)
    {
        if (pmutex->type == PMUTEX_NORMAL)
        {
            rt_sem_delete(pmutex->lock.ksem);
        }
        else
        {
            rt_mutex_delete(pmutex->lock.kmutex);
        }
        rt_free(pmutex);
        return RT_NULL;
    }
    pmutex->node.avl_key = (avl_key_t)umutex;
    pmutex->node.data = &lwp->address_search_head;
    pmutex->custom_obj = obj;
    pmutex->type = type;

    /* insert into pmutex head */
    lwp_avl_insert(&pmutex->node, &lwp->address_search_head);
    return pmutex;
}

static struct rt_pmutex* pmutex_get(void *umutex, struct rt_lwp *lwp)
{
    struct rt_pmutex *pmutex = RT_NULL;
    struct lwp_avl_struct *node = RT_NULL;

    node = lwp_avl_find((avl_key_t)umutex, lwp->address_search_head);
    if (!node)
    {
        return RT_NULL;
    }
    pmutex = rt_container_of(node, struct rt_pmutex, node);
    return pmutex;
}

static int _pthread_mutex_init(void *umutex)
{
    struct rt_lwp *lwp = RT_NULL;
    struct rt_pmutex *pmutex = RT_NULL;
    rt_err_t lock_ret = 0;

    /* umutex union is 6 x (void *) */
    if (!lwp_user_accessable(umutex, sizeof(void *) * 6))
    {
        rt_set_errno(EINVAL);
        return -EINVAL;
    }

    lock_ret = rt_mutex_take_interruptible(&_pmutex_lock, RT_WAITING_FOREVER);
    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EAGAIN);
        return -EAGAIN;
    }

    lwp = lwp_self();
    pmutex = pmutex_get(umutex, lwp);
    if (pmutex == RT_NULL)
    {
        /* create a pmutex according to this umutex */
        pmutex = pmutex_create(umutex, lwp);
        if (pmutex == RT_NULL)
        {
            rt_mutex_release(&_pmutex_lock);
            rt_set_errno(ENOMEM);
            return -ENOMEM;
        }
        if (lwp_user_object_add(lwp, pmutex->custom_obj) != 0)
        {
            rt_custom_object_destroy(pmutex->custom_obj);
            rt_set_errno(ENOMEM);
            return -ENOMEM;
        }
    }
    else
    {
        lwp_mutex_take_safe(&_pmutex_lock, RT_WAITING_FOREVER, 1);
        if (pmutex->type == PMUTEX_NORMAL)
        {
            pmutex->lock.ksem->value = 1;
        }
        else
        {
            pmutex->lock.kmutex->owner    = RT_NULL;
            pmutex->lock.kmutex->priority = 0xFF;
            pmutex->lock.kmutex->hold     = 0;
            pmutex->lock.kmutex->ceiling_priority = 0xFF;
        }
        lwp_mutex_release_safe(&_pmutex_lock);
    }

    rt_mutex_release(&_pmutex_lock);

    return 0;
}

static int _pthread_mutex_lock_timeout(void *umutex, struct timespec *timeout)
{
    struct rt_lwp *lwp = RT_NULL;
    struct rt_pmutex *pmutex = RT_NULL;
    struct rt_umutex *umutex_p = (struct rt_umutex*)umutex;
    rt_err_t lock_ret = 0;
    rt_int32_t time = RT_WAITING_FOREVER;

    if (!lwp_user_accessable((void *)umutex, sizeof(struct rt_umutex)))
    {
        rt_set_errno(EINVAL);
        return -EINVAL;
    }

    if (timeout)
    {
        if (!lwp_user_accessable((void *)timeout, sizeof(struct timespec)))
        {
            rt_set_errno(EINVAL);
            return -EINVAL;
        }
        time = rt_timespec_to_tick(timeout);
    }

    lock_ret = rt_mutex_take_interruptible(&_pmutex_lock, RT_WAITING_FOREVER);
    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EINTR);
        return -EINTR;
    }

    lwp = lwp_self();
    pmutex = pmutex_get(umutex, lwp);
    if (pmutex == RT_NULL)
    {
        rt_mutex_release(&_pmutex_lock);
        rt_set_errno(EINVAL);
        return -ENOMEM;  /* umutex not recored in kernel */
    }

    rt_mutex_release(&_pmutex_lock);

    switch (pmutex->type)
    {
    case PMUTEX_NORMAL:
        lock_ret = rt_sem_take_interruptible(pmutex->lock.ksem, time);
        break;
    case PMUTEX_RECURSIVE:
        lock_ret = rt_mutex_take_interruptible(pmutex->lock.kmutex, time);
        if (lock_ret == RT_EOK)
        {
            umutex_p->_m_lock = rt_thread_self()->tid;
        }
        break;
    case PMUTEX_ERRORCHECK:
        lock_ret = lwp_mutex_take_safe(&_pmutex_lock, RT_WAITING_FOREVER, 1);
        if (lock_ret != RT_EOK)
        {
            return -EINTR;
        }
        if (pmutex->lock.kmutex->owner == rt_thread_self())
        {
            lwp_mutex_release_safe(&_pmutex_lock);
            return -EDEADLK;
        }
        lock_ret = rt_mutex_take_interruptible(pmutex->lock.kmutex, time);
        if (lock_ret == RT_EOK)
        {
            umutex_p->_m_lock = rt_thread_self()->tid;
        }
        lwp_mutex_release_safe(&_pmutex_lock);
        break;
    default: /* unknown type */
        return -EINVAL;
    }

    if (lock_ret != RT_EOK)
    {
        if (lock_ret == -RT_ETIMEOUT)
        {
            if (time == 0) /* timeout is 0, means try lock failed */
            {
                rt_set_errno(EBUSY);
                return -EBUSY;
            }
            else
            {
                rt_set_errno(ETIMEDOUT);
                return -ETIMEDOUT;
            }
        }
        else if (lock_ret == -RT_EINTR)
        {
            rt_set_errno(EINTR);
            return -EINTR;
        }
        else
        {
            rt_set_errno(EAGAIN);
            return -EAGAIN;
        }
    }
    return 0;
}

static int _pthread_mutex_unlock(void *umutex)
{
    rt_err_t lock_ret = 0;
    struct rt_lwp *lwp = RT_NULL;
    struct rt_pmutex *pmutex = RT_NULL;
    struct rt_umutex *umutex_p = (struct rt_umutex*)umutex;

    lock_ret = rt_mutex_take_interruptible(&_pmutex_lock, RT_WAITING_FOREVER);
    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EAGAIN);
        return -EAGAIN;
    }

    lwp = lwp_self();
    pmutex = pmutex_get(umutex, lwp);
    if (pmutex == RT_NULL)
    {
        rt_mutex_release(&_pmutex_lock);
        rt_set_errno(EPERM);
        return -EPERM;//unlock static mutex of unlock state
    }

    rt_mutex_release(&_pmutex_lock);

    switch (pmutex->type)
    {
    case PMUTEX_NORMAL:
        if(pmutex->lock.ksem->value >=1)
        {
            rt_set_errno(EPERM);
            return -EPERM;//unlock dynamic mutex of unlock state
        }
        else
        {
            lock_ret = rt_sem_release(pmutex->lock.ksem);
        }
        break;
    case PMUTEX_RECURSIVE:
    case PMUTEX_ERRORCHECK:
        lock_ret = rt_mutex_release(pmutex->lock.kmutex);
        if ((lock_ret == RT_EOK) && pmutex->lock.kmutex->owner == NULL)
        {
            umutex_p->_m_lock = 0;
        }
        break;
    default: /* unknown type */
        return -EINVAL;
    }

    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EPERM);
        return -EPERM;
    }
    return 0;
}

static int _pthread_mutex_destroy(void *umutex)
{
    struct rt_lwp *lwp = RT_NULL;
    struct rt_pmutex *pmutex = RT_NULL;
    rt_err_t lock_ret = 0;

    lock_ret = rt_mutex_take_interruptible(&_pmutex_lock, RT_WAITING_FOREVER);
    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EAGAIN);
        return -EAGAIN;
    }

    lwp = lwp_self();
    pmutex = pmutex_get(umutex, lwp);
    if (pmutex == RT_NULL)
    {
        rt_mutex_release(&_pmutex_lock);
        rt_set_errno(EINVAL);
        return -EINVAL;
    }

    lwp_user_object_delete(lwp, pmutex->custom_obj);
    rt_mutex_release(&_pmutex_lock);

    return 0;
}

sysret_t sys_pmutex(void *umutex, int op, void *arg)
{
    int ret = -EINVAL;

    switch (op)
    {
        case PMUTEX_INIT:
            ret = _pthread_mutex_init(umutex);
            break;
        case PMUTEX_LOCK:
            ret = _pthread_mutex_lock_timeout(umutex, (struct timespec*)arg);
            if (ret == -ENOMEM)
            {
                /* lock not init, try init it and lock again. */
                ret = _pthread_mutex_init(umutex);
                if (ret == 0)
                {
                    ret = _pthread_mutex_lock_timeout(umutex, (struct timespec*)arg);
                }
            }
            break;
        case PMUTEX_UNLOCK:
            ret = _pthread_mutex_unlock(umutex);
            break;
        case PMUTEX_DESTROY:
            ret = _pthread_mutex_destroy(umutex);
            break;
        default:
            rt_set_errno(EINVAL);
            break;
    }
    return ret;
}
