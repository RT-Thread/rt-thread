/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#ifdef RT_USING_POSIX_STDIO
#include <posix/stdio.h>
#endif /* RT_USING_POSIX_STDIO */
#define DBG_TAG    "picolibc.iob"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifdef TINY_STDIO

static int __fputc(char c, FILE *file);
static int __fgetc(FILE *file);

static FILE __stdio_in = FDEV_SETUP_STREAM(NULL, __fgetc, NULL, _FDEV_SETUP_READ);
static FILE __stdio_out = FDEV_SETUP_STREAM(__fputc, NULL, NULL, _FDEV_SETUP_WRITE);

#ifdef __strong_reference
#define STDIO_ALIAS(x) __strong_reference(stdout, x);
#else
#define STDIO_ALIAS(x) FILE *const x = &__stdio_out;
#endif

FILE *const stdin = &__stdio_in;
FILE *const stdout = &__stdio_out;
STDIO_ALIAS(stderr);

static int __fputc(char c, FILE *file)
{
    if (file == &__stdio_out)
    {
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
        rt_device_t console = rt_console_get_device();
        if (console)
        {
            rt_ssize_t rc = rt_device_write(console, -1, &c, 1);
            return rc > 0 ? rc : -1;
        }
#endif /* defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE) */
    }

    return -1;
}

static int __fgetc(FILE *file)
{
    if (file == &__stdio_in)
    {
#ifdef RT_USING_POSIX_STDIO
        if (rt_posix_stdio_get_console() >= 0)
        {
            char c;
            int rc = read(STDIN_FILENO, &c, 1);
            return rc == 1 ? c : EOF;
        }
#endif /* RT_USING_POSIX_STDIO */
    }

    return EOF;
}

#endif
