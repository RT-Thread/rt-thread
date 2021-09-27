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

#define DBG_TAG    "dlib.syscall_read"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#pragma module_name = "?__read"
size_t __read(int handle, unsigned char *buf, size_t len)
{
#ifdef RT_USING_DFS
    int size;
#endif

    if (handle == _LLIO_STDIN)
    {
#ifdef RT_USING_POSIX
        if (libc_stdio_get_console() < 0)
        {
            LOG_W("Do not invoke standard input before initializing libc");
            return 0;
        }
        return read(STDIN_FILENO, buf, len);
#else
        return _LLIO_ERROR;
#endif
    }
    else if ((handle == _LLIO_STDOUT) || (handle == _LLIO_STDERR))
    {
        return _LLIO_ERROR;
    }

#ifndef RT_USING_DFS
    return _LLIO_ERROR;
#else
    size = read(handle, buf, len);
    return size;
#endif
}
