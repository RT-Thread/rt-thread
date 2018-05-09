/*
 * File      : Queue.h
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
 * The Queue class allow to control, send, receive, or wait for messages.
 * A message can be a integer or pointer value  to a certain type T that is send
 * to a thread or interrupt service routine.
 * @param  T         data type of a single message element.
 * @param  queue_sz  maximum number of messages in queue.
 */
template<typename T, uint32_t queue_sz>
class Queue
{
public:
    /** Create and initialise a message Queue. */
    Queue()
    {
        rt_mq_init(&mID, "mq", mPool, sizeof(T), sizeof(mPool), RT_IPC_FLAG_FIFO);
    };

    ~Queue()
    {
        rt_mq_detach(&mID);
    };

    /** Put a message in a Queue.
      @param   data      message pointer.
      @param   millisec  timeout value or 0 in case of no time-out. (default: 0)
      @return  status code that indicates the execution status of the function.
    */
    rt_err_t put(T& data, int32_t millisec = 0)
    {
        return rt_mq_send(&mID, &data, sizeof(data));
    }

    /** Get a message or Wait for a message from a Queue.
      @param   millisec  timeout value or 0 in case of no time-out. (default: osWaitForever).
      @return  bool .
    */
    bool get(T& data, int32_t millisec = WAIT_FOREVER)
    {
        rt_int32_t tick;

        if (millisec < 0)
            tick = -1;
        else
            tick = rt_tick_from_millisecond(millisec);

        return rt_mq_recv(&mID, &data, sizeof(data), tick) == RT_EOK;
    }

private:
    struct rt_messagequeue mID;

    char mPool[(sizeof(struct rt_messagequeue)+sizeof(T)) * queue_sz];
};

}
