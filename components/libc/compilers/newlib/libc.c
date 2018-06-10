/*
 * File     : libc.c
 * Brief    : gcc libc header file
 *
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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

int	_EXFUN(putenv,(char *__string));

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

    /* set PATH and HOME */
    putenv("PATH=/bin");
    putenv("HOME=/home");

#if defined RT_USING_PTHREADS && !defined RT_USING_COMPONENTS_INIT
    pthread_system_init();
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(libc_system_init);
