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
#include <compiler_private.h>
#define DBG_TAG    "dlib.syscall.write"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/*
 * The "__write" function should output "size" number of bytes from
 * "buffer" in some application-specific way.  It should return the
 * number of characters written, or _LLIO_ERROR on failure.
 *
 * If "buffer" is zero then __write should perform flushing of
 * internal buffers, if any.  In this case "handle" can be -1 to
 * indicate that all handles should be flushed.
 *
 * The template implementation below assumes that the application
 * provides the function "MyLowLevelPutchar".  It should return the
 * character written, or -1 on failure.
 */

#pragma module_name = "?__write"

size_t __write(int handle, const unsigned char *buf, size_t len)
{
#ifdef DFS_USING_POSIX
    int size;
#endif /* DFS_USING_POSIX */

    if ((handle == _LLIO_STDOUT) || (handle == _LLIO_STDERR))
    {
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
        rt_device_t console_device;

        console_device = rt_console_get_device();
        if (console_device)
        {
            rt_device_write(console_device, 0, buf, len);
        }

        return len; /* return the length of the data written */
#else
        return _LLIO_ERROR;
#endif /* defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE) */
    }
    else if (handle == _LLIO_STDIN)
    {
        return _LLIO_ERROR;
    }
    else
    {
#ifdef DFS_USING_POSIX
        size = write(handle, buf, len);
        return size; /* return the length of the data written */
#else
        LOG_W(_WARNING_WITHOUT_FS);
        return _LLIO_ERROR;
#endif /* DFS_USING_POSIX */
    }
}
