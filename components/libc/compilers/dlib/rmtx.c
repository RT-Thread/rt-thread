/*
 * File      : rmtx.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
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
 * 2015-01-28     Bernard      first version
 */
#include <rtthread.h>
#include <yfuns.h>

/*
 * for IAR compiler, we recommand to define _DLIB_THREAD_SUPPORT
 * as 2 for dlib multi-thread support.
 */

#if _DLIB_THREAD_SUPPORT
typedef void* _Rmtx;
void _Mtxinit(_Rmtx *m)
{
    rt_mutex_t mutex;

    RT_ASSERT(m != RT_NULL);
    
    mutex = (rt_mutex_t)m;
    rt_mutex_init(mutex, "iarMtx", RT_IPC_FLAG_FIFO);
}

void _Mtxdst(_Rmtx *m)
{
    rt_mutex_t mutex;

    RT_ASSERT(m != RT_NULL);

    mutex = (rt_mutex_t)m;
    rt_mutex_detach(mutex);
}

void _Mtxlock(_Rmtx *m)
{
    rt_mutex_t mutex;

    RT_ASSERT(m != RT_NULL);

    mutex = (rt_mutex_t)m;
    rt_mutex_take(mutex, RT_WAITING_FOREVER);
}

void _Mtxunlock(_Rmtx *m)
{
    rt_mutex_t mutex;

    RT_ASSERT(m != RT_NULL);

    mutex = (rt_mutex_t)m;
    rt_mutex_release(mutex);
}
#endif

