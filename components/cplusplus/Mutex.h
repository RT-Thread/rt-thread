/*
 * File      : Mutex.h
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

namespace rtthread {

/** The Mutex class is used to synchronise the execution of threads.
 This is for example used to protect access to a shared resource.
*/
class Mutex {
public:
    /** Create and Initialize a Mutex object */
    Mutex(const char* name = "mutex");
    ~Mutex();

    /** Wait until a Mutex becomes available.
      @param   millisec  timeout value or 0 in case of no time-out. (default: WaitForever)
      @return  true if the mutex was acquired, false otherwise.
     */
    bool lock(int32_t millisec = -1);

    /** Try to lock the mutex, and return immediately
      @return  true if the mutex was acquired, false otherwise.
     */
    bool trylock();

    /** Unlock the mutex that has previously been locked by the same thread
     */
    void unlock();

private:
    struct rt_mutex mID;
};

}
