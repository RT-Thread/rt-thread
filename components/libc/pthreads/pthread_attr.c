/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#include <rtthread.h>
#include "pthread.h"
#include "sched.h"
#include <string.h>

#define DEFAULT_STACK_SIZE  2048
#define DEFAULT_PRIORITY    (RT_THREAD_PRIORITY_MAX/2 + RT_THREAD_PRIORITY_MAX/4)

const pthread_attr_t pthread_default_attr = 
{
    0,                          /* stack base */
    DEFAULT_STACK_SIZE,         /* stack size */
    DEFAULT_PRIORITY,           /* priority */
    PTHREAD_CREATE_JOINABLE,    /* detach state */
    SCHED_FIFO,                 /* scheduler policy */
    PTHREAD_INHERIT_SCHED       /* Inherit parent prio/policy */
};

int pthread_attr_init(pthread_attr_t *attr)
{
    RT_ASSERT(attr != RT_NULL);

    *attr = pthread_default_attr;

    return 0;
}
RTM_EXPORT(pthread_attr_init);

int pthread_attr_destroy(pthread_attr_t *attr)
{
    RT_ASSERT(attr != RT_NULL);

    memset(attr, 0, sizeof(pthread_attr_t));

    return 0;
}
RTM_EXPORT(pthread_attr_destroy);

int pthread_attr_setdetachstate(pthread_attr_t *attr, int state)
{
    RT_ASSERT(attr != RT_NULL);

    if (state != PTHREAD_CREATE_JOINABLE && state != PTHREAD_CREATE_DETACHED)
        return EINVAL;

    attr->detachstate = state;

    return 0;
}
RTM_EXPORT(pthread_attr_setdetachstate);

int pthread_attr_getdetachstate(pthread_attr_t const *attr, int *state)
{
    RT_ASSERT(attr != RT_NULL);

    *state = (int)attr->detachstate;

    return 0;
}
RTM_EXPORT(pthread_attr_getdetachstate);

int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy)
{
    RT_ASSERT(attr != RT_NULL);

    attr->policy = policy;

    return 0;
}
RTM_EXPORT(pthread_attr_setschedpolicy);

int pthread_attr_getschedpolicy(pthread_attr_t const *attr, int *policy)
{
    RT_ASSERT(attr != RT_NULL);

    *policy = (int)attr->policy;

    return 0;
}
RTM_EXPORT(pthread_attr_getschedpolicy);

int pthread_attr_setschedparam(pthread_attr_t           *attr,
                               struct sched_param const *param)
{
    RT_ASSERT(attr != RT_NULL);
    RT_ASSERT(param != RT_NULL);

    attr->priority = param->sched_priority;

    return 0;
}
RTM_EXPORT(pthread_attr_setschedparam);

int pthread_attr_getschedparam(pthread_attr_t const *attr,
                               struct sched_param   *param)
{
    RT_ASSERT(attr != RT_NULL);
    RT_ASSERT(param != RT_NULL);

    param->sched_priority = attr->priority;

    return 0;
}
RTM_EXPORT(pthread_attr_getschedparam);

int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stack_size)
{
    RT_ASSERT(attr != RT_NULL);

    attr->stack_size = stack_size;

    return 0;
}
RTM_EXPORT(pthread_attr_setstacksize);

int pthread_attr_getstacksize(pthread_attr_t const *attr, size_t *stack_size)
{
    RT_ASSERT(attr != RT_NULL);

    *stack_size = attr->stack_size;

    return 0;
}
RTM_EXPORT(pthread_attr_getstacksize);

int pthread_attr_setstackaddr(pthread_attr_t *attr, void *stack_addr)
{
    RT_ASSERT(attr != RT_NULL);

    return EOPNOTSUPP;
}
RTM_EXPORT(pthread_attr_setstackaddr);

int pthread_attr_getstackaddr(pthread_attr_t const *attr, void **stack_addr)
{
    RT_ASSERT(attr != RT_NULL);

    return EOPNOTSUPP;
}
RTM_EXPORT(pthread_attr_getstackaddr);

int pthread_attr_setstack(pthread_attr_t *attr,
                          void           *stack_base,
                          size_t          stack_size)
{
    RT_ASSERT(attr != RT_NULL);

    attr->stack_base = stack_base;
    attr->stack_size = RT_ALIGN_DOWN(stack_size, RT_ALIGN_SIZE);

    return 0;
}
RTM_EXPORT(pthread_attr_setstack);

int pthread_attr_getstack(pthread_attr_t const *attr,
                          void                **stack_base,
                          size_t               *stack_size)
{
    RT_ASSERT(attr != RT_NULL);

    *stack_base = attr->stack_base;
    *stack_size = attr->stack_size;

    return 0;
}
RTM_EXPORT(pthread_attr_getstack);

int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guard_size)
{
    return EOPNOTSUPP;
}

int pthread_attr_getguardsize(pthread_attr_t const *attr, size_t *guard_size)
{
    return EOPNOTSUPP;
}
RTM_EXPORT(pthread_attr_getguardsize);

int pthread_attr_setscope(pthread_attr_t *attr, int scope)
{
    if (scope == PTHREAD_SCOPE_SYSTEM)
        return 0;
    if (scope == PTHREAD_SCOPE_PROCESS)
        return EOPNOTSUPP;

    return EINVAL;
}
RTM_EXPORT(pthread_attr_setscope);

int pthread_attr_getscope(pthread_attr_t const *attr)
{
    return PTHREAD_SCOPE_SYSTEM;
}
RTM_EXPORT(pthread_attr_getscope);
