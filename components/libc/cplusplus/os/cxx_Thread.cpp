/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "cxx_thread.h"

using namespace rtthread;

/** 
 * @brief Thread class constructor with parameters for stack size, priority, tick, and name.
 * @param stack_size Stack size in bytes
 * @param priority Thread priority
 * @param tick Time slice in ticks
 * @param name Thread name
 */
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

/** 
 * @brief Thread class constructor with entry function and parameters.
 * @param entry The entry function pointer for the thread.
 * @param p The parameter to pass to the entry function.
 * @param stack_size The size of the thread stack in bytes.
 * @param priority The priority of the thread.
 * @param tick The time slice (tick) for the thread.
 * @param name The name of the thread.
 */
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

/** 
 * @brief Detach the event and delete the thread when the object is destroyed.
 */
Thread::~Thread()
{
    rt_event_detach(&_event);
    rt_thread_delete(_thread);
}

/** 
 * @brief Start the thread execution.
 * @return true if the thread was successfully started.
 */
bool Thread::start()
{
    if (rt_thread_startup(_thread) == RT_EOK)
    {
        started = true;
    }

    return started;
}

/** 
 * @brief Make the thread sleep for a specified duration.
 * @param millisec Duration in milliseconds.
 */
void Thread::sleep(int32_t millisec)
{
    rt_int32_t tick;

    if (millisec < 0)
        tick = 1;
    else
        tick = rt_tick_from_millisecond(millisec);

    rt_thread_delay(tick);
}

/** 
 * @brief Function to run the thread's entry function.
 */
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

/** 
 * @brief Default run function that can be overridden by subclasses.
 */
void Thread::run(void *parameter)
{
    /* please overload this method */
}

/** 
 * @brief Wait for the thread to complete with a timeout.
 * @param millisec Timeout in milliseconds.
 * @return RT_EOK if the thread completed within the timeout, error code otherwise.
 */
rt_err_t Thread::wait(int32_t millisec)
{
    return join(millisec);
}

/** 
 * @brief Join the thread with a timeout.
 * @param millisec Timeout in milliseconds.
 * @return RT_EOK if the thread completed within the timeout, error code otherwise.
 */
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