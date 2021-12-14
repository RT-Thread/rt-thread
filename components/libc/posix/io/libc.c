/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/15     bernard      the first version
 */
#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include "libc.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef RT_USING_PTHREADS
#include <pthread.h>
#endif

int libc_system_init(void)
{
#ifdef RT_USING_POSIX_DEVIO
    rt_device_t dev_console;

    dev_console = rt_console_get_device();
    if (dev_console)
    {
        libc_stdio_set_console(dev_console->parent.name, O_RDWR);
    }
#endif /* RT_USING_POSIX_DEVIO */

#if defined RT_USING_PTHREADS && !defined RT_USING_COMPONENTS_INIT
    pthread_system_init();
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(libc_system_init);

#ifdef RT_USING_POSIX_DEVIO
#if defined(RT_USING_LIBC) && defined(RT_USING_NEWLIB)
#define STDIO_DEVICE_NAME_MAX   32
static FILE* std_console = NULL;
int libc_stdio_set_console(const char* device_name, int mode)
{
    FILE *fp;
    char name[STDIO_DEVICE_NAME_MAX];
    char *file_mode;

    snprintf(name, sizeof(name) - 1, "/dev/%s", device_name);
    name[STDIO_DEVICE_NAME_MAX - 1] = '\0';

    if (mode == O_RDWR)
    {
        file_mode = "r+";
    }
    else if (mode == O_WRONLY)
    {
        file_mode = "wb";
    }
    else
    {
        file_mode = "rb";
    }

    fp = fopen(name, file_mode);
    if (fp)
    {
        setvbuf(fp, NULL, _IONBF, 0);

        if (std_console)
        {
            fclose(std_console);
            std_console = NULL;
        }
        std_console = fp;

        if (mode == O_RDWR)
        {
            _GLOBAL_REENT->_stdin  = std_console;
        }
        else
        {
            _GLOBAL_REENT->_stdin  = NULL;
        }

        if (mode == O_RDONLY)
        {
            _GLOBAL_REENT->_stdout = NULL;
            _GLOBAL_REENT->_stderr = NULL;
        }
        else
        {
            _GLOBAL_REENT->_stdout = std_console;
            _GLOBAL_REENT->_stderr = std_console;
        }

        _GLOBAL_REENT->__sdidinit = 1;
    }

    if (std_console)
        return fileno(std_console);

    return -1;
}

int libc_stdio_get_console(void)
{
    if (std_console)
        return fileno(std_console);
    else
        return -1;
}

#else
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
#endif /* defined(RT_USING_LIBC) && defined(RT_USING_NEWLIB) */
#endif /* RT_USING_POSIX_DEVIO */
