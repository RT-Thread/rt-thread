/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-25     Shell        first version
 */

#define DBG_TAG "lwp.internal"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <stdlib.h>
#include "lwp_internal.h"

static rt_err_t _mutex_take_safe(rt_mutex_t mtx, rt_int32_t timeout, rt_bool_t interruptable)
{
    DEF_RETURN_CODE(rc);
    int retry;
    rt_int32_t effect_timeout;

#ifdef LWP_DEBUG
    rt_thread_t thread = rt_thread_self();
#endif

    if (mtx)
    {
        effect_timeout = timeout;
#if DBG_LVL == DBG_LOG && defined(LWP_DEBUG)
        int exception;
        rt_list_t *node = RT_NULL;
        struct rt_mutex *tak_obj = RT_NULL;
        if (!rt_list_isempty(&(thread->taken_object_list)) && timeout == RT_WAITING_FOREVER)
        {
            exception = 1;
            effect_timeout = 0;
        }
        else
        {
            exception = 0;
        }
#endif /* DBG_LOG && defined(LWP_DEBUG) */

        do {
            retry = 0;
            if (interruptable)
                rc = rt_mutex_take_interruptible(mtx, effect_timeout);
            else
                rc = rt_mutex_take(mtx, effect_timeout);

#ifdef LWP_DEBUG
            if (rc == RT_EOK)
            {
                if (rt_mutex_get_hold(mtx) > 1)
                {
                    LOG_W("Already hold the lock");
                    rt_backtrace();
                }
            }
            else if (rc == -RT_ETIMEOUT)
            {
#if DBG_LVL == DBG_LOG
                if (exception)
                {
                    rt_list_for_each(node, &(thread->taken_object_list))
                    {
                        tak_obj = rt_list_entry(node, struct rt_mutex, taken_list);
                        if (rt_mutex_get_owner(tak_obj)->stat & RT_THREAD_SUSPEND_MASK)
                            LOG_D("Potential dead lock - Taken: %s, Try take: %s",
                                tak_obj->parent.parent.name, mtx->parent.parent.name);
                    }
                    rt_backtrace();
                    retry = 1;
                    exception = 0;
                }
#endif
            }
            else if (rc != -RT_EINTR)
            {
                char tname[RT_NAME_MAX];
                rt_thread_get_name(thread, tname, sizeof(tname));
                LOG_W("Possible kernel corruption detected on thread %s with errno %ld", tname, rc);
            }
#endif /* LWP_DEBUG */
        } while (retry);
    }
    else
    {
        LOG_W("%s: mtx should not be NULL", __func__);
        RT_ASSERT(0);
    }

    RETURN(rc);
}

rt_err_t lwp_mutex_take_safe(rt_mutex_t mtx, rt_int32_t timeout, rt_bool_t interruptable)
{
    DEF_RETURN_CODE(rc);
    rc = _mutex_take_safe(mtx, timeout, interruptable);
    RETURN(rc);
}

rt_err_t lwp_mutex_release_safe(rt_mutex_t mtx)
{
    DEF_RETURN_CODE(rc);

    rc = rt_mutex_release(mtx);
    if (rc)
    {
        LOG_I("%s: release failed with code %ld", __func__, rc);
        rt_backtrace();
    }

    RETURN(rc);
}

rt_err_t lwp_critical_enter(struct rt_lwp *lwp)
{
    rt_err_t rc;
    rc = lwp_mutex_take_safe(&lwp->lwp_lock, RT_WAITING_FOREVER, 0);

    /* if current process is force killed */
    if (rc != RT_EOK)
    {
        if (rc == -RT_EINTR && lwp_self() != RT_NULL)
            sys_exit(EXIT_SUCCESS);
        else
            LOG_I("%s: unexpected return code = %ld", __func__, rc);
    }

    return rc;
}

rt_err_t lwp_critical_exit(struct rt_lwp *lwp)
{
    return lwp_mutex_release_safe(&lwp->lwp_lock);
}
