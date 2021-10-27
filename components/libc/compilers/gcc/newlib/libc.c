/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/15     bernard      the first version
 */
#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include "libc.h"

#ifdef RT_USING_PTHREADS
#include <pthread.h>
#endif

int libc_system_init(void)
{
#ifdef RT_USING_POSIX
    rt_device_t dev_console;

    dev_console = rt_console_get_device();
    if (dev_console)
    {
        libc_stdio_set_console(dev_console->parent.name, O_RDWR);
    }
#endif /* RT_USING_POSIX */

#if defined RT_USING_PTHREADS && !defined RT_USING_COMPONENTS_INIT
    pthread_system_init();
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(libc_system_init);
