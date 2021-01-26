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

struct rt_pmutex
{
    rt_mutex_t kmutex;
    struct lwp_avl_struct node;
    struct rt_object *custom_obj;
};

static struct rt_mutex _pmutex_lock;

static int pmutex_system_init(void)
{
    rt_mutex_init(&_pmutex_lock, "pmtxLock", RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_PREV_EXPORT(pmutex_system_init);

static void pmutex_destory(void *data)
{
    rt_base_t level = 0;
    struct rt_pmutex *pmutex = (struct rt_pmutex *)data;

    if (pmutex)
    {
        level = rt_hw_interrupt_disable();
        /* remove pmutex from pmutext avl */
        lwp_avl_remove(&pmutex->node, (struct lwp_avl_struct **)pmutex->node.data);
        rt_hw_interrupt_enable(level);

        rt_mutex_delete(pmutex->kmutex);

        /* release object */
        rt_free(pmutex);
    }

    return ;
}

static struct rt_pmutex* pmutex_create(void *umutex, struct rt_lwp *lwp)
{
    struct rt_pmutex *pmutex = RT_NULL;
    struct rt_object *obj = RT_NULL;

    if (!lwp)
    {
        return RT_NULL;
    }
    pmutex = (struct rt_pmutex *)rt_malloc(sizeof(struct rt_pmutex));
    if (!pmutex)
    {
        return RT_NULL;
    }
    pmutex->kmutex = rt_mutex_create("pmutex", RT_IPC_FLAG_PRIO);
    if (!pmutex->kmutex)
    {
        rt_free(pmutex);
        return RT_NULL;
    }
    obj = rt_custom_object_create("pmutex", (void *)pmutex, pmutex_destory);
    if (!obj)
    {
        rt_mutex_delete(pmutex->kmutex);
        rt_free(pmutex);
        return RT_NULL;
    }

    pmutex->node.avl_key = (avl_key_t)umutex;
    pmutex->node.data = &lwp->address_search_head;
    pmutex->custom_obj = obj;

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

int sys_pthread_mutex_init(void *umutex)
{
    struct rt_lwp *lwp = RT_NULL;
    struct rt_pmutex *pmutex = RT_NULL;
    rt_err_t lock_ret = 0;

    /* umutex union is 6 x (void *) */
    if (!lwp_user_accessable(umutex, sizeof(void *) * 6))
    {
        rt_set_errno(EINVAL);
        return -RT_EINVAL;
    }

    lock_ret = rt_mutex_take_interruptible(&_pmutex_lock, RT_WAITING_FOREVER);
    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EAGAIN);
        return -RT_EINTR;
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
            return -RT_ENOMEM;
        }
    }
    else
    {
        rt_base_t level = rt_hw_interrupt_disable();

        pmutex->kmutex->value = 1;
        pmutex->kmutex->owner = RT_NULL;
        pmutex->kmutex->original_priority = 0xFF;
        pmutex->kmutex->hold  = 0;

        rt_hw_interrupt_enable(level);
    }

    rt_mutex_release(&_pmutex_lock);

    return 0;
}

int sys_pthread_mutex_lock_timeout(void *umutex, struct timespec *timeout)
{
    struct rt_lwp *lwp = RT_NULL;
    struct rt_pmutex *pmutex = RT_NULL;
    rt_err_t lock_ret = 0;
    rt_int32_t time = RT_WAITING_FOREVER;

    if (timeout)
    {
        if (!lwp_user_accessable((void *)timeout, sizeof(struct timespec)))
        {
            rt_set_errno(EINVAL);
            return -RT_EINVAL;
        }
        time = clock_time_to_tick(timeout);
    }

    lock_ret = rt_mutex_take_interruptible(&_pmutex_lock, RT_WAITING_FOREVER);
    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EAGAIN);
        return -RT_EINTR;
    }

    lwp = lwp_self();
    pmutex = pmutex_get(umutex, lwp);
    if (pmutex == RT_NULL)
    {
        rt_mutex_release(&_pmutex_lock);
        rt_set_errno(EINVAL);
        return -RT_EINVAL;
    }

    rt_mutex_release(&_pmutex_lock);

    lock_ret = rt_mutex_take_interruptible(pmutex->kmutex, time);
    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EAGAIN);
    }
    return lock_ret;
}

int sys_pthread_mutex_unlock(void *umutex)
{
    struct rt_lwp *lwp = RT_NULL;
    struct rt_pmutex *pmutex = RT_NULL;
    rt_err_t lock_ret = 0;

    lock_ret = rt_mutex_take_interruptible(&_pmutex_lock, RT_WAITING_FOREVER);
    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EAGAIN);
        return -RT_EINTR;
    }

    lwp = lwp_self();
    pmutex = pmutex_get(umutex, lwp);
    if (pmutex == RT_NULL)
    {
        rt_mutex_release(&_pmutex_lock);
        rt_set_errno(EINVAL);
        return -RT_EINVAL;
    }

    rt_mutex_release(&_pmutex_lock);

    lock_ret = rt_mutex_release(pmutex->kmutex);
    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EPERM);
    }
    return lock_ret;
}

int sys_pthread_mutex_destroy(void *umutex)
{
    struct rt_lwp *lwp = RT_NULL;
    struct rt_pmutex *pmutex = RT_NULL;
    rt_err_t lock_ret = 0;
    rt_base_t level = 0;

    lock_ret = rt_mutex_take_interruptible(&_pmutex_lock, RT_WAITING_FOREVER);
    if (lock_ret != RT_EOK)
    {
        rt_set_errno(EAGAIN);
        return -RT_EINTR;
    }

    lwp = lwp_self();
    pmutex = pmutex_get(umutex, lwp);
    if (pmutex == RT_NULL)
    {
        rt_mutex_release(&_pmutex_lock);
        rt_set_errno(EINVAL);
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();
    rt_custom_object_destroy(pmutex->custom_obj);
    rt_hw_interrupt_enable(level);

    rt_mutex_release(&_pmutex_lock);

    return RT_EOK;
}
