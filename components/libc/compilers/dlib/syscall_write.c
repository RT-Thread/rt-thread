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
#ifdef RT_USING_POSIX_STDIO
#include "libc.h"
#endif

#define DBG_TAG    "IAR.dlib.syscall_write"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#pragma module_name = "?__write"

size_t __write(int handle, const unsigned char *buf, size_t len)
{
#ifdef RT_USING_POSIX
    int size;
#endif /* RT_USING_POSIX */

    if ((handle == _LLIO_STDOUT) || (handle == _LLIO_STDERR))
    {
#ifdef RT_USING_CONSOLE
        rt_device_t console_device;

        console_device = rt_console_get_device();
        if (console_device)
        {
            rt_device_write(console_device, 0, buf, len);
        }

        return len; /* return the length of the data written */
#else
        return _LLIO_ERROR;
#endif /* RT_USING_CONSOLE */
    }
    else if (handle == _LLIO_STDIN)
    {
        return _LLIO_ERROR;
    }
    else
    {
#ifdef RT_USING_POSIX
        size = write(handle, buf, len);
        return size; /* return the length of the data written */
#else
        return _LLIO_ERROR;
#endif /* RT_USING_POSIX */
    }
}
