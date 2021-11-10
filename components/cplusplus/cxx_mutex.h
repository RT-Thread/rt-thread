/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
    Mutex(const char *name = "mutex");
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
