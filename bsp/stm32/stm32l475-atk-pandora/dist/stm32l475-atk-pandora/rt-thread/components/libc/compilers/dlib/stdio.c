/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/15     bernard      implement stdio for IAR dlib.
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

int libc_stdio_get_console(void) {
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
