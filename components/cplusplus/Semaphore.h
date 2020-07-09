/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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
