/*
 * File      : Thread.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2016, RT-Thread Development Team
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
 * 2016/10/1      Bernard      The first version
 */

#pragma once

#include <stdint.h>
#include <rtthread.h>

namespace rtthread
{

/** The Thread class allow defining, creating, and controlling thread functions in the system. */
class Thread
{
public:
    typedef void (*thread_func_t) (void *param);

    /** Allocate a new thread without starting execution
      @param   priority       initial priority of the thread function. (default: osPriorityNormal).
      @param   stack_size      stack size (in bytes) requirements for the thread function. (default: DEFAULT_STACK_SIZE).
      @param   stack_pointer  pointer to the stack area to be used by this thread (default: NULL).
    */
    Thread(rt_uint32_t stack_size = 2048,
           rt_uint8_t  priority = (RT_THREAD_PRIORITY_MAX * 2)/3,
           rt_uint32_t tick = 20,
           const char *name = "th");

    Thread(void (*entry)(void *p),
           void *p = RT_NULL,
           rt_uint32_t stack_size = 2048,
           rt_uint8_t  priority = (RT_THREAD_PRIORITY_MAX * 2)/3,
           rt_uint32_t tick = 20,
           const char *name = "th");

    virtual ~Thread();

    bool start();

    static void sleep(int32_t millisec);

    void wait(int32_t millisec);
    void join(int32_t millisec = -1);

protected:
    virtual void run();

private:
    static void func(Thread *pThis);

private:
    rt_thread_t _thread;

    thread_func_t _entry;
    void *_param;

    /* event for thread join */
    struct rt_event _event;
    bool started;
};

}
