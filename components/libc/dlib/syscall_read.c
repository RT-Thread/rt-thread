/*
 * File      : syscall_read.c
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

#pragma module_name = "?__read"
size_t __read(int handle, unsigned char *buf, size_t len)
{
#ifdef RT_USING_DFS
    int size;
#endif

    if (handle == _LLIO_STDIN)
    {
        /* TODO */
        return 0;
    }

    if ((handle == _LLIO_STDOUT) || (handle == _LLIO_STDERR))
        return _LLIO_ERROR;

#ifndef RT_USING_DFS
    return _LLIO_ERROR;
#else
    size = read(handle - _LLIO_STDERR - 1, buf, len);
    return size;
#endif
}
