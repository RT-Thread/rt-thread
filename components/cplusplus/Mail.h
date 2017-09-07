/*
 * File      : Mail.h
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
#include <string.h>

#include <rtthread.h>

namespace rtthread {

/**
 * The Mail class allow to control, send, receive, or wait for mail.
 * A mail is a memory block that is send to a thread or interrupt service routine.
 * @param  T         data type of a single message element.
 * @param  queue_sz  maximum number of messages in queue.
 */

template<typename T, uint32_t queue_sz>
class Mail {
public:
    /** Create and Initialise Mail queue. */
    Mail(const char* name = "")
    {
        rt_mb_init(&mID, name, mPool, queue_sz, RT_IPC_FLAG_FIFO);
    }

    ~Mail()
    {
        rt_mb_detach(&mID);
    }

    /** Put a mail in the queue.
      @param   mptr  memory block previously allocated with Mail::alloc or Mail::calloc.
      @return  status code that indicates the execution status of the function.
    */
    bool put(T *mptr, int32_t millisec = 0)
    {
        rt_int32_t tick;

        if (millisec < 0)
            tick = -1;
        else
            tick = rt_tick_from_millisecond(millisec);

        return rt_mb_send_wait(&mID, (rt_uint32_t)mptr, tick) == RT_EOK;
    }

    /** Get a mail from a queue.
      @param   millisec  timeout value or 0 in case of no time-out. (default: osWaitForever).
      @return  event that contains mail information or error code.
    */
    T* get(int32_t millisec = -1)
    {
        T *t = NULL;
        rt_int32_t tick;

        if (millisec < 0)
            tick = -1;
        else
            tick = rt_tick_from_millisecond(millisec);

        rt_mb_recv(&mID, &t, tick);

        return t;
    }

private:
    struct rt_mailbox mID;
    T* mPool[queue_sz];
};

}
