/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-04-01     Keith Packard Port to picolibc
 * 2021-02-11     Meco Man     remove _gettimeofday_r() and _times_r()
 * 2020-02-13     Meco Man     re-implement exit() and abort()
 * 2020-02-21     Meco Man     improve and beautify syscalls
 * 2020-02-24     Meco Man     fix bug of _isatty_r()
 */

#include <rtthread.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#ifdef RT_USING_POSIX_STDIO
#include "libc.h"
#endif /* RT_USING_POSIX_STDIO */
#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif /* RT_USING_MODULE */
#include <compiler_private.h>
#define DBG_TAG    "picolibc.syscalls"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_HEAP /* Memory routine */
void *malloc (size_t size)
{
    void* result;

    result = (void*)rt_malloc (size);
    if (result == RT_NULL)
    {
        errno = ENOMEM;
    }

    return result;
}

void *realloc (void *old, size_t newlen)
{
    void* result;

    result = (void*)rt_realloc (old, newlen);
    if (result == RT_NULL)
    {
        errno = ENOMEM;
    }

    return result;
}

void *calloc (size_t size, size_t len)
{
    void* result;

    result = (void*)rt_calloc (size, len);
    if (result == RT_NULL)
    {
        errno = ENOMEM;
    }

    return result;
}

void free (void *addr)
{
    rt_free (addr);
}

#else
void *
sbrk(ptrdiff_t incr)
{
    LOG_E("Please enable RT_USING_HEAP");
    RT_ASSERT(0);
    return RT_NULL;
}
#endif /*RT_USING_HEAP*/

void __libc_init_array(void)
{
    /* we not use __libc init_aray to initialize C++ objects */
    /* __libc_init_array is ARM code, not Thumb; it will cause a hardfault. */
}

mode_t umask(mode_t mask)
{
    return 022;
}

int flock(int fd, int operation)
{
    return 0;
}

#include <rthw.h>

#ifdef RT_USING_CONSOLE
int
rt_getc(FILE *file)
{
    (void) file;
    rt_size_t len = 0;
    char c = 0;
#ifdef RT_USING_DEVICE
    rt_device_t console = rt_console_get_device();
    if (console != RT_NULL)
        len = rt_device_read(console, 0, &c, 1);
#endif
    if (len != 1)
    {
        return _FDEV_ERR;
    }
    return (int) (unsigned char) c;
}

int
rt_putc(char c, FILE *file)
{
    (void) file;
#ifdef RT_USING_DEVICE
    rt_device_t console = rt_console_get_device();
    if (console != RT_NULL) {
        rt_device_write(console, 0, &c, 1);
        return 0;
    }
#endif
    char buf[2] = { c, 0 };
    rt_hw_console_output(buf);
    return 0;
}

static FILE __stdio = FDEV_SETUP_STREAM(rt_putc, rt_getc, NULL, __SRD|__SWR);

FILE *const stdin = &__stdio;
FILE *const stdout = &__stdio;
FILE *const stderr = &__stdio;

#endif
