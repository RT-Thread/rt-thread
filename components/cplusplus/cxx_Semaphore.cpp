/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "Semaphore.h"

using namespace rtthread;

Semaphore::Semaphore(const char *name, int32_t count)
{
    rt_sem_init(&mID, name, count, RT_IPC_FLAG_FIFO);
}

bool Semaphore::wait(int32_t millisec)
{
    rt_int32_t tick;

    if (millisec < 0)
        tick = -1;
    else
        tick = rt_tick_from_millisecond(millisec);

    return rt_sem_take(&mID, tick) == RT_EOK;
}

void Semaphore::release(void)
{
    rt_sem_release(&mID);
}

Semaphore::~Semaphore()
{
    rt_sem_detach(&mID);
}
