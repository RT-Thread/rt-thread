/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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

#define DBG_TAG    "dlib.syscall_write"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

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
        if (libc_stdio_get_console() < 0)
        {
            LOG_W("Do not invoke standard output before initializing libc");
            return 0;
        }
        return write(STDOUT_FILENO, (void*)buf, len);
#else
        rt_device_t console_device;

        console_device = rt_console_get_device();
        if (console_device != 0)
        {
            rt_device_write(console_device, 0, buf, len);
        }

        return len;
#endif
#endif
    }
    else if (handle == _LLIO_STDIN)
    {
        return _LLIO_ERROR;
    }

#ifndef RT_USING_DFS
    return _LLIO_ERROR;
#else
    size = write(handle, buf, len);
    return size;
#endif
}

