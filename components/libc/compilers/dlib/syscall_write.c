/*
 * File      : syscall_write.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
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

