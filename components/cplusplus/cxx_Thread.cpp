/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "Thread.h"

using namespace rtthread;

Thread::Thread(rt_uint32_t stack_size,
               rt_uint8_t  priority,
               rt_uint32_t tick,
               const char *name)
    : _entry(RT_NULL), _param(RT_NULL), started(false)
{
    rt_event_init(&_event, name, 0);

    _thread = rt_thread_create(name,
                               (thread_func_t)func,
                               this,
                               stack_size,
                               priority,
                               tick);
}

Thread::Thread(void (*entry)(void *p),
               void *p,
               rt_uint32_t stack_size,
               rt_uint8_t  priority,
               rt_uint32_t tick,
               const char *name)
    : _entry(entry), _param(p), started(false)
{
    rt_event_init(&_event, name, 0);

    _thread = rt_thread_create(name,
                               (thread_func_t)func,
                               this,
                               stack_size,
                               priority,
                               tick);
}

Thread::~Thread()
{
    rt_event_detach(&_event);
    rt_thread_delete(_thread);
}

bool Thread::start()
{
    if (rt_thread_startup(_thread) == RT_EOK)
    {
        started = true;
    }

    return started;
}

void Thread::sleep(int32_t millisec)
{
    rt_int32_t tick;

    if (millisec < 0)
        tick = 1;
    else
        tick = rt_tick_from_millisecond(millisec);

    rt_thread_delay(tick);
}

void Thread::func(Thread *pThis)
{
    if (pThis->_entry != RT_NULL)
    {
        pThis->_entry(pThis->_param);
    }
    else
    {
        pThis->run(pThis->_param);
    }

    rt_event_send(&pThis->_event, 1);
}

void Thread::run(void *parameter)
{
    /* please overload this method */
}

rt_err_t Thread::wait(int32_t millisec)
{
    return join(millisec);
}

rt_err_t Thread::join(int32_t millisec)
{
    if (started)
    {
        rt_int32_t tick;

        if (millisec < 0)
            tick = -1;
        else
            tick = rt_tick_from_millisecond(millisec);

        return rt_event_recv(&_event, 1, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, tick, RT_NULL);
    }
    else
    {
        return -RT_ENOSYS;
    }
}
