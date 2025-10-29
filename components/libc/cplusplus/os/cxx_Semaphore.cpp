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
 * @brief Semaphore class implementation.
 */
Semaphore::Semaphore(const char *name, int32_t count)
{
    // Initialize the semaphore with a specified count and FIFO order.
    rt_sem_init(&mID, name, count, RT_IPC_FLAG_FIFO);
}

/** 
 * @brief Wait on the semaphore.
 * @param millisec Timeout in milliseconds.
 * @return Boolean indicating if the semaphore was successfully taken.
 */
bool Semaphore::wait(int32_t millisec)
{
    rt_int32_t tick;

    // Convert milliseconds to system ticks.
    if (millisec < 0)
        tick = -1;
    else
        tick = rt_tick_from_millisecond(millisec);

    // Attempt to take the semaphore.
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
 * Detach the semaphore when the object is destroyed.
 */
Semaphore::~Semaphore()
{
    rt_sem_detach(&mID);
}
