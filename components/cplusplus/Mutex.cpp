/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include "Mutex.h"

using namespace rtthread;

Mutex::Mutex(const char *name)
{
    rt_mutex_init(&mID, name, RT_IPC_FLAG_FIFO);
}

bool Mutex::lock(int32_t millisec)
{
    rt_int32_t tick;

    if (millisec < 0)
        tick = -1;
    else
        tick = rt_tick_from_millisecond(millisec);

    return rt_mutex_take(&mID, tick) == RT_EOK;
}

bool Mutex::trylock()
{
    return lock(0);
}

void Mutex::unlock()
{
    rt_mutex_release(&mID);
}

Mutex::~Mutex()
{
    rt_mutex_detach(&mID);
}
