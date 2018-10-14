/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/15     bernard      the first version
 */
#include <stdio.h>
#include <stdlib.h>

#include <rtthread.h>

#include "libc.h"

#ifdef RT_USING_PTHREADS
#include <pthread.h>
#endif

int libc_system_init(void)
{
#if defined(RT_USING_DFS) & defined(RT_USING_DFS_DEVFS)
    rt_device_t dev_console;

    dev_console = rt_console_get_device();
    if (dev_console)
    {
    #if defined(RT_USING_POSIX)
        libc_stdio_set_console(dev_console->parent.name, O_RDWR);
    #else
        libc_stdio_set_console(dev_console->parent.name, O_WRONLY);
    #endif
    }
#endif

#if defined RT_USING_PTHREADS && !defined RT_USING_COMPONENTS_INIT
    pthread_system_init();
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(libc_system_init);
