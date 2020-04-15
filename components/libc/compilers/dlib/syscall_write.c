/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-28     Bernard      first version
 */

#include <rtthread.h>
#ifdef RT_USING_DFS
#include <dfs_posix.h>
#endif
#include <yfuns.h>
#include "libc.h"

#pragma module_name = "?__write"

size_t __write(int handle, const unsigned char *buf, size_t len)
{
#ifdef RT_USING_DFS
    int size;
#endif

    if ((handle == _LLIO_STDOUT) || (handle == _LLIO_STDERR))
    {
#ifndef RT_USING_CONSOLE
        return _LLIO_ERROR;
#else

#ifdef RT_USING_POSIX
        return libc_stdio_write((void*)buf, len);
#else
        rt_device_t console_device;

        console_device = rt_console_get_device();
        if (console_device != 0) rt_device_write(console_device, 0, buf, len);

        return len;
#endif
#endif
    }

    if (handle == _LLIO_STDIN) return _LLIO_ERROR;

#ifndef RT_USING_DFS
    return _LLIO_ERROR;
#else
    size = write(handle, buf, len);
    return size;
#endif
}

