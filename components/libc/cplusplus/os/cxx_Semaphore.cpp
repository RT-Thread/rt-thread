/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "cxx_semaphore.h"

using namespace rtthread;

/** 
 * @brief Semaphore class constructor.
 * @param name Semaphore name
 * @param count Initial semaphore count
 */
Semaphore::Semaphore(const char *name, int32_t count)
{
    rt_sem_init(&mID, name, count, RT_IPC_FLAG_FIFO);
}

/** 
 * @brief Wait on the semaphore.
 * @param millisec Timeout in milliseconds (-1 for infinite wait).
 * @return true if the semaphore was successfully taken, false on timeout.
 */
bool Semaphore::wait(int32_t millisec)
{
    rt_int32_t tick;

    if (millisec < 0)
        tick = -1;
    else
        tick = rt_tick_from_millisecond(millisec);

    return rt_sem_take(&mID, tick) == RT_EOK;
}

/** 
 * @brief Release the semaphore.
 */
void Semaphore::release(void)
{
    rt_sem_release(&mID);
}

/** 
 * @brief Detach the semaphore when the object is destroyed.
 */
Semaphore::~Semaphore()
{
    rt_sem_detach(&mID);
}
