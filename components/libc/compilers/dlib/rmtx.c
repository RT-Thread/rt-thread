/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

