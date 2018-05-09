/*
 * File     : stdio.c
 * Brief    : stdio/console
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
 * 2017/10/15     bernard      implement stdio for armcc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rtthread.h>
#include "libc.h"

#if defined(RT_USING_DFS) && defined(RT_USING_DFS_DEVFS)
#include <dfs_posix.h>

#define STDIO_DEVICE_NAME_MAX   32

static int std_fd = -1;
int libc_stdio_set_console(const char* device_name, int mode)
{
    int fd;
    char name[STDIO_DEVICE_NAME_MAX];

    snprintf(name, sizeof(name) - 1, "/dev/%s", device_name);
    name[STDIO_DEVICE_NAME_MAX - 1] = '\0';

    fd = open(name, mode, 0);
    if (fd >= 0)
    {
        if (std_fd >= 0)
        {
            close(std_fd);
        }
        std_fd = fd;
    }

    return std_fd;
}

int libc_stdio_get_console(void)
{
    return std_fd;
}

int libc_stdio_read(void *buffer, size_t size)
{
    return read(std_fd, buffer, size);
}

int libc_stdio_write(const void *buffer, size_t size)
{
    return write(std_fd, buffer, size);
}
#endif
