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
#include <LowLevelIOInterface.h>
#include <unistd.h>
#ifdef RT_USING_POSIX_DEVIO
#include "libc.h"
#endif /* RT_USING_POSIX_DEVIO */

#define DBG_TAG    "dlib.syscall_read"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/*
 * The "__read" function reads a number of bytes, at most "size" into
 * the memory area pointed to by "buffer".  It returns the number of
 * bytes read, 0 at the end of the file, or _LLIO_ERROR if failure
 * occurs.
 *
 * The template implementation below assumes that the application
 * provides the function "MyLowLevelGetchar".  It should return a
 * character value, or -1 on failure.
 */

#pragma module_name = "?__read"

size_t __read(int handle, unsigned char *buf, size_t len)
{
#ifdef DFS_USING_POSIX
    int size;

    if (handle == _LLIO_STDIN)
    {
#ifdef RT_USING_POSIX_DEVIO
        if (libc_stdio_get_console() < 0)
        {
            LOG_W("Do not invoke standard input before initializing libc");
            return 0; /* error, but keep going */
        }
        return read(STDIN_FILENO, buf, len); /* return the length of the data read */
#else
        return _LLIO_ERROR;
#endif /* RT_USING_POSIX_DEVIO */
    }
    else if ((handle == _LLIO_STDOUT) || (handle == _LLIO_STDERR))
    {
        return _LLIO_ERROR;
    }

    size = read(handle, buf, len);
    return size; /* return the length of the data read */
#else
    return _LLIO_ERROR;
#endif /* DFS_USING_POSIX */
}
