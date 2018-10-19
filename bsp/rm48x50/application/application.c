/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-24     Grissiom     first version
 */

#include <rtthread.h>

#include "system.h"
#include "het.h"

static rt_uint8_t user_thread_stack[512];
static struct rt_thread user_thread;
static void user_thread_entry(void *p)
{
    int i;

    gioSetDirection(hetPORT1, 0xFFFFFFFF);

    for(i = 0; ;i++)
    {
        gioSetBit(hetPORT1, 17, gioGetBit(hetPORT1, 17) ^ 1);
        rt_thread_delay(100);
    }
}

int rt_application_init()
{
    rt_thread_init(&user_thread, "user1", user_thread_entry, RT_NULL,
            user_thread_stack, sizeof(user_thread_stack), 21, 20);
    rt_thread_startup(&user_thread);
    return 0;
}

