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
#include <string.h>

namespace rtthread {

class Lock
{
public:
    Lock(Mutex& mutex) : m(mutex) {m.lock();}
    ~Lock() {m.unlock();}

protected:
    Mutex &m;
};

}
