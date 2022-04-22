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
#include <cstdint>
#include <stdatomic.h>
#include "tpl.h"

static int check_create(volatile __ARM_TPL_mutex_t *__vm, bool recursive = false)
{
    if (__vm->data == 0)
    {
        uintptr_t mut_null = 0;
        arm_tpl_mutex_struct *mutex_p = (arm_tpl_mutex_struct *)rt_malloc(sizeof(arm_tpl_mutex_struct));
        if (mutex_p == nullptr) return -1;

        if (recursive)
            mutex_p->mutex = rt_mutex_create("mutexx", RT_IPC_FLAG_PRIO);
        else
            mutex_p->mutex = rt_mutex_create("mutexx", RT_IPC_FLAG_PRIO);

        if (mutex_p->mutex == nullptr)
        {
            rt_free(mutex_p);
            return -1;
        }
        mutex_p->type = recursive ? RECURSIVE : NORMAL;
        uintptr_t mut_new = reinterpret_cast<uintptr_t>(mutex_p);
        if (!atomic_compare_exchange_strong(&__vm->data, &mut_null, mut_new))
        {
            rt_mutex_delete(mutex_p->mutex);
            rt_free(mutex_p);
        }
    }
    return 0;
}

static int mutexLock(arm_tpl_mutex_struct *mutex_p, rt_tick_t timeOut)
{
    if (mutex_p->type == RECURSIVE)
    {
        if (rt_mutex_take(mutex_p->mutex, timeOut) == 0)
            return 0;
    }
    else
    {
        if (rt_mutex_take(mutex_p->mutex, timeOut) == 0)
            return 0;
    }
    return -1;
}

static int mutexUnlock(arm_tpl_mutex_struct *mutex_p)
{
    if (mutex_p->type == RECURSIVE)
        rt_mutex_release(mutex_p->mutex);
    else
        rt_mutex_release(mutex_p->mutex);
    return 0;
}

extern "C" int __ARM_TPL_recursive_mutex_init(__ARM_TPL_mutex_t *__m)
{
    volatile __ARM_TPL_mutex_t *__vm = __m;
    return check_create(__vm, true);
}

extern "C" int __ARM_TPL_mutex_lock(__ARM_TPL_mutex_t *__m)
{
    volatile __ARM_TPL_mutex_t *__vm = __m;
    if (check_create(__vm))
        return -1;
    while (mutexLock((arm_tpl_mutex_struct *)(__vm->data), ARM_TPL_MAX_DELAY) != 0);
    return 0;
}

extern "C" int __ARM_TPL_mutex_trylock(__ARM_TPL_mutex_t *__m)
{
    volatile __ARM_TPL_mutex_t *__vm = __m;
    if (check_create(__vm))
        return -1;
    return mutexLock((arm_tpl_mutex_struct *)(__vm->data), 0);
}

extern "C" int __ARM_TPL_mutex_unlock(__ARM_TPL_mutex_t *__m)
{
    volatile __ARM_TPL_mutex_t *__vm = __m;
    return mutexUnlock((arm_tpl_mutex_struct *)(__vm->data));
}

extern "C" int __ARM_TPL_mutex_destroy(__ARM_TPL_mutex_t *__m)
{
    volatile __ARM_TPL_mutex_t *__vm = __m;
    if (__vm->data != 0)
    {
        rt_mutex_delete(((arm_tpl_mutex_struct *)(__vm->data))->mutex);
        rt_free((void *)(__vm->data));
        __vm->data = 0;
    }
    return 0;
}
