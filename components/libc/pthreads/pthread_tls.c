/*
 * File      : pthread_tls.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#include <pthread.h>
#include "pthread_internal.h"

_pthread_key_data_t _thread_keys[PTHREAD_KEY_MAX];

void pthread_key_system_init()
{
    rt_memset(&_thread_keys[0], 0, sizeof(_thread_keys));
}

void *pthread_getspecific(pthread_key_t key)
{
    struct _pthread_data* ptd;

    ptd = _pthread_get_data(rt_thread_self());
    RT_ASSERT(ptd != NULL);

    if (ptd->tls == NULL)
        return NULL;

    if ((key < PTHREAD_KEY_MAX) && (_thread_keys[key].is_used))
        return ptd->tls[key];

    return NULL;
}
RTM_EXPORT(pthread_getspecific);

int pthread_setspecific(pthread_key_t key, const void *value)
{
    struct _pthread_data* ptd;

    ptd = _pthread_get_data(rt_thread_self());
    RT_ASSERT(ptd != NULL);

    /* check tls area */
    if (ptd->tls == NULL)
    {
        ptd->tls = (void**)rt_malloc(sizeof(void*) * PTHREAD_KEY_MAX);
    }

    if ((key < PTHREAD_KEY_MAX) && _thread_keys[key].is_used)
    {
        ptd->tls[key] = (void *)value;

        return 0;
    }

    return EINVAL;
}
RTM_EXPORT(pthread_setspecific);

int pthread_key_create(pthread_key_t *key, void (*destructor)(void*))
{
    rt_uint32_t index;

    rt_enter_critical();
    for (index = 0; index < PTHREAD_KEY_MAX; index ++)
    {
        if (_thread_keys[index].is_used == 0)
        {
            _thread_keys[index].is_used = 1;
            _thread_keys[index].destructor = destructor;

            *key = index;

            rt_exit_critical();

            return 0;
        }
    }

    rt_exit_critical();

    return EAGAIN;
}
RTM_EXPORT(pthread_key_create);

int pthread_key_delete(pthread_key_t key)
{
    if (key >= PTHREAD_KEY_MAX)
        return EINVAL;

    rt_enter_critical();
    _thread_keys[key].is_used = 0;
    _thread_keys[key].destructor = 0;
    rt_exit_critical();

    return 0;
}
RTM_EXPORT(pthread_key_delete);

