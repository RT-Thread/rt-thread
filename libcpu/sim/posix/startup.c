/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-10     flybreak     the first version
 */
#include <rtthread.h>
 
#if defined(__GNUC__)

int rtthread_startup(void);

static int start(void)
{
    rtthread_startup();
    return 0;
}
RT_SECTION(".init_array")  typeof(start) *__init = start;
#endif

