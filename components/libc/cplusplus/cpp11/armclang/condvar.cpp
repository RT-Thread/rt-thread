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
#include <new>
#include <cstdint>
#include <stdatomic.h>

arm_tpl_cv::arm_tpl_cv()
{
    s = rt_sem_create("semxs", 0, RT_IPC_FLAG_PRIO);
    if (s == nullptr)
        RT_ASSERT(0);
    h = rt_sem_create("semxh", 0, RT_IPC_FLAG_PRIO);
    if (h == nullptr)
    {
        rt_sem_delete(s);
        RT_ASSERT(0);
    }
    x = rt_mutex_create("mutx", RT_IPC_FLAG_PRIO);
    if (x == nullptr)
    {
        rt_sem_delete(s);
        rt_sem_delete(h);
        RT_ASSERT(0);
    }
}

arm_tpl_cv::~arm_tpl_cv()
{
    rt_mutex_delete(x);
    rt_sem_delete(h);
    rt_sem_delete(s);
}

void arm_tpl_cv::wait(rt_mutex_t lock, bool recursive)
{
    while (rt_mutex_take(x, ARM_TPL_MAX_DELAY) != 0);
    rt_sem_release(s);
    rt_mutex_release(x);
    if (recursive)
        rt_mutex_release(lock);
    else
        rt_mutex_release(lock);
    while (rt_sem_take(h, ARM_TPL_MAX_DELAY) != 0);
    if (recursive)
        while (rt_mutex_take(lock, ARM_TPL_MAX_DELAY) != 0);
    else
        while (rt_mutex_take(lock, ARM_TPL_MAX_DELAY) != 0);
}

int arm_tpl_cv::timedwait(rt_mutex_t lock, bool recursive, unsigned int timeout_ms)
{
    int result = 0;
    while (rt_mutex_take(x, ARM_TPL_MAX_DELAY) != 0);
    rt_sem_release(s);
    rt_mutex_release(x);
    if (recursive)
        rt_mutex_release(lock);
    else
        rt_mutex_release(lock);
    if (rt_sem_take(h, rt_tick_from_millisecond(timeout_ms)) != 0)
    {
        while (rt_mutex_take(x, ARM_TPL_MAX_DELAY) != 0);
        if (rt_sem_take(h, 0) != 0)
        {
            if (rt_sem_take(s, 0) != 0)
                result = -1;
            else
                result = 1;
        }
        rt_mutex_release(x);
    }
    if (recursive)
        while (rt_mutex_take(lock, ARM_TPL_MAX_DELAY) != 0);
    else
        while (rt_mutex_take(lock, ARM_TPL_MAX_DELAY) != 0);
    return result;
}

void arm_tpl_cv::signal()
{
    while (rt_mutex_take(x, ARM_TPL_MAX_DELAY) != 0);
    if (rt_sem_take(s, 0) == 0)
        rt_sem_release(h);
    rt_mutex_release(x);
}

void arm_tpl_cv::broadcast()
{
    while (rt_mutex_take(x, ARM_TPL_MAX_DELAY) != 0);
    auto count = s->value;
    for (auto i = 0; i < count; i++)
    {
        while (rt_sem_take(s, ARM_TPL_MAX_DELAY) != 0);
        rt_sem_release(h);
    }
    rt_mutex_release(x);
}

static int check_create(volatile __ARM_TPL_condvar_t *__vcv)
{
    if (__vcv->data == 0)
    {
        uintptr_t cv_new;
        cv_new = reinterpret_cast<uintptr_t>(new arm_tpl_cv());
        if (cv_new == 0)
        {
            return -1;
        }
        uintptr_t cv_null = 0;
        if (!atomic_compare_exchange_strong(&__vcv->data, &cv_null, cv_new))
            delete reinterpret_cast<arm_tpl_cv *>(cv_new);
    }
    return 0;
}

extern "C" int __ARM_TPL_condvar_wait(__ARM_TPL_condvar_t *__cv, __ARM_TPL_mutex_t *__m)
{
    volatile __ARM_TPL_condvar_t *__vcv = __cv;
    if (check_create(__vcv) != 0)
        return -1;
    struct arm_tpl_mutex_struct *tmutex = (struct arm_tpl_mutex_struct *)(__m->data);
    ((arm_tpl_cv *) __vcv->data)->wait(tmutex->mutex, tmutex->type == RECURSIVE);
    return 0;
}

extern "C" int __ARM_TPL_condvar_timedwait(__ARM_TPL_condvar_t *__cv,
                                __ARM_TPL_mutex_t *__m,
                                __ARM_TPL_timespec_t *__ts)
{
    volatile __ARM_TPL_condvar_t *__vcv = __cv;
    if (check_create(__vcv) != 0)
        return -1;
    __ARM_TPL_timespec_t now;
    if (__ARM_TPL_clock_realtime(&now) != 0)
        return -1;
    struct arm_tpl_mutex_struct *tmutex = (struct arm_tpl_mutex_struct *)(__m->data);
    unsigned int timeout_ms = (__ts->tv_sec - now.tv_sec) * 1000 + (__ts->tv_nsec - now.tv_nsec) / 1000000;
    if (((arm_tpl_cv *) __vcv->data)->timedwait(tmutex->mutex, tmutex->type == RECURSIVE, timeout_ms) < 0)
        return -1;
    return 0;
}

extern "C" int __ARM_TPL_condvar_signal(__ARM_TPL_condvar_t *__cv)
{
    volatile __ARM_TPL_condvar_t *__vcv = __cv;
    if (__vcv->data != 0)
        ((arm_tpl_cv *) __vcv->data)->signal();
    return 0;
}

extern "C" int __ARM_TPL_condvar_broadcast(__ARM_TPL_condvar_t *__cv)
{
    volatile __ARM_TPL_condvar_t *__vcv = __cv;
    if (__vcv->data != 0)
        ((arm_tpl_cv *) __vcv->data)->broadcast();
    return 0;
}

extern "C" int __ARM_TPL_condvar_destroy(__ARM_TPL_condvar_t *__cv)
{
    volatile __ARM_TPL_condvar_t *__vcv = __cv;
    if (__vcv->data != 0)
    {
        delete (arm_tpl_cv *) __vcv->data;
        __vcv->data = 0;
    }
    return 0;
}
