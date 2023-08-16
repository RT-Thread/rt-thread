/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/15     bernard      the first version
 * 2023/08/07     Meco Man     rename as posix/stdio.c
 */

#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/errno.h>
#include "posix/stdio.h"

#define STDIO_DEVICE_NAME_MAX   32

int sys_dup2(int oldfd, int new);

int rt_posix_stdio_init(void)
{
    rt_device_t dev_console;

    dev_console = rt_console_get_device();
    if (dev_console)
    {
        int fd = rt_posix_stdio_set_console(dev_console->parent.name, O_RDWR);
        if (fd < 0)
        {
            return -1;
        }
        /* set fd (0, 1, 2) */
        sys_dup2(fd, 0);
        sys_dup2(fd, 1);
        sys_dup2(fd, 2);
    }
    return 0;
}
INIT_ENV_EXPORT(rt_posix_stdio_init);

#if defined(RT_USING_NEWLIBC)

#define NEWLIB_VERSION_NUM (__NEWLIB__ * 10000U + __NEWLIB_MINOR__ * 100U + __NEWLIB_PATCHLEVEL__)

static FILE* std_console = NULL;
int rt_posix_stdio_set_console(const char* device_name, int mode)
{
    FILE *fp;
    char name[STDIO_DEVICE_NAME_MAX];
    char *file_mode;

    rt_snprintf(name, sizeof(name) - 1, "/dev/%s", device_name);
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

#if (NEWLIB_VERSION_NUM < 30400U) || (NEWLIB_VERSION_NUM >= 40000U && NEWLIB_VERSION_NUM < 40300U)
        _GLOBAL_REENT->__sdidinit = 1; /* __sdidinit is obselete */
#endif
    }

    if (std_console)
        return fileno(std_console);

    return -1;
}

int rt_posix_stdio_get_console(void)
{
    if (std_console)
        return fileno(std_console);
    else
        return -1;
}

#elif defined(RT_USING_MUSLLIBC)

static FILE* std_console = NULL;

int rt_posix_stdio_set_console(const char* device_name, int mode)
{
    FILE *fp;
    char name[STDIO_DEVICE_NAME_MAX];
    char *file_mode;

    rt_snprintf(name, sizeof(name) - 1, "/dev/%s", device_name);
    name[STDIO_DEVICE_NAME_MAX - 1] = '\0';

    if (mode == O_RDWR) file_mode = "r+";
    else if (mode == O_WRONLY) file_mode = "wb";
    else file_mode = "rb";

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
    }

    if (std_console)
    {
        int fd = fileno(std_console);

        return fd;
    }

    return -1;
}

int rt_posix_stdio_get_console(void)
{
    int ret = -1;
    if (std_console)
    {
        ret = fileno(std_console);
    }

    return ret;
}

#else

static int std_fd = -1;
int rt_posix_stdio_set_console(const char* device_name, int mode)
{
    int fd;
    char name[STDIO_DEVICE_NAME_MAX];

    rt_snprintf(name, sizeof(name) - 1, "/dev/%s", device_name);
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

int rt_posix_stdio_get_console(void) {
    return std_fd;
}
#endif /* defined(RT_USING_NEWLIBC) */

ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream)
{
    char *cur_pos, *new_lineptr;
    size_t new_lineptr_len;
    int c;

    if (lineptr == NULL || n == NULL || stream == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    if (*lineptr == NULL)
    {
        *n = 128; /* init len */
        if ((*lineptr = (char *)malloc(*n)) == NULL)
        {
            errno = ENOMEM;
            return -1;
        }
    }

    cur_pos = *lineptr;
    for (;;)
    {
        c = getc(stream);

        if (ferror(stream) || (c == EOF && cur_pos == *lineptr))
            return -1;

        if (c == EOF)
            break;

        if ((*lineptr + *n - cur_pos) < 2)
        {
            if (LONG_MAX / 2 < *n)
            {
#ifdef EOVERFLOW
                errno = EOVERFLOW;
#else
                errno = ERANGE; /* no EOVERFLOW defined */
#endif
                return -1;
            }
            new_lineptr_len = *n * 2;

            if ((new_lineptr = (char *)realloc(*lineptr, new_lineptr_len)) == NULL)
            {
                errno = ENOMEM;
                return -1;
            }
            cur_pos = new_lineptr + (cur_pos - *lineptr);
            *lineptr = new_lineptr;
            *n = new_lineptr_len;
        }

        *cur_pos++ = (char)c;

        if (c == delim)
            break;
    }

    *cur_pos = '\0';
    return (ssize_t)(cur_pos - *lineptr);
}

ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
    return getdelim(lineptr, n, '\n', stream);
}
