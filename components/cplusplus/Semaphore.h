/*
 * File      : Semaphore.h
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

/** The Semaphore class is used to manage and protect access to a set of shared resources. */
class Semaphore
{
public:
    /** Create and Initialize a Semaphore object used for managing resources.
      @param number of available resources; maximum index value is (count-1).
    */
    Semaphore(const char *name = "sem", int32_t count = 0);
    ~Semaphore();

    /** Wait until a Semaphore resource becomes available.
      @param   millisec  timeout value or 0 in case of no time-out.
      @return  true on success.
    */
    bool wait(int32_t millisec = -1);

    /** Release a Semaphore resource that was obtain with Semaphore::wait.
    */
    void release(void);

private:
    struct rt_semaphore mID;
};

}
