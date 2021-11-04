/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-27     flybreak     the first version.
 */

#include <arm-tpl.h>
#include "tpl.h"
#include <cstdio>
#include <pthread.h>

extern "C" int __ARM_TPL_thread_create(__ARM_TPL_thread_t *__t,
                                       void *(*__func)(void *),
                                       void *__arg)
{
    int ret = 0;
    /* TODO memory leek */
    pthread_t *pid = (pthread_t *)rt_malloc(sizeof(pthread_t));
    if (pid == nullptr)
        return -1;
    ret = pthread_create(pid, RT_NULL, __func, __arg);
    if (ret == 0)
    {
        __t->data = (std::uintptr_t)pid;
        return 0;
    }
    return -1;
}

extern "C" int __ARM_TPL_thread_id_compare(__ARM_TPL_thread_id __tid1,
        __ARM_TPL_thread_id __tid2)
{
    if (__tid1 > __tid2)
        return 1;
    else if (__tid1 < __tid2)
        return -1;
    else
        return 0;
}

extern "C" __ARM_TPL_thread_id __ARM_TPL_thread_get_current_id()
{
    return (__ARM_TPL_thread_id)pthread_self();
}

extern "C" __ARM_TPL_thread_id __ARM_TPL_thread_get_id(
    const __ARM_TPL_thread_t *__t)
{
    return (__ARM_TPL_thread_id)((*(pthread_t *)__t->data));
}

extern "C" int __ARM_TPL_thread_join(__ARM_TPL_thread_t *__t)
{
    pthread_join((*(pthread_t *)__t->data), RT_NULL);
    return 0;
}

extern "C" int __ARM_TPL_thread_detach(__ARM_TPL_thread_t *__t)
{
    pthread_detach((*(pthread_t *)__t->data));
    return 0;
}

extern "C" void __ARM_TPL_thread_yield()
{
    rt_thread_yield();
}

extern "C" int __ARM_TPL_thread_nanosleep(const __ARM_TPL_timespec_t *__req,
        __ARM_TPL_timespec_t *__rem)
{
    rt_tick_t tick;

    tick = __req->tv_sec * RT_TICK_PER_SECOND + (__req->tv_nsec * RT_TICK_PER_SECOND)/ 1000000000;
    rt_thread_delay(tick);

    if (__rem)
    {
        tick = rt_tick_get() - tick;
        /* get the passed time */
        __rem->tv_sec = tick/RT_TICK_PER_SECOND;
        __rem->tv_nsec = (tick%RT_TICK_PER_SECOND) * (1000000000/RT_TICK_PER_SECOND);
    }
    return 0;
}

extern "C" unsigned __ARM_TPL_thread_hw_concurrency()
{
    return 1;
}

extern "C" int __ARM_TPL_tls_create(__ARM_TPL_tls_key *__key,
                                    void (*__at_exit)(void *))
{
    pthread_key_t key; 
    
    if (pthread_key_create(&key, __at_exit) == 0)
    {
        *__key = key;
        return 0;
    }
    return -1;
}

extern "C" void *__ARM_TPL_tls_get(__ARM_TPL_tls_key __key)
{
    return pthread_getspecific(__key);
}

extern "C" int __ARM_TPL_tls_set(__ARM_TPL_tls_key __key, void *__p)
{
    if (pthread_setspecific(__key, (void*)__p) != 0)
    {
        return -1;
    }
    return 0;
}
