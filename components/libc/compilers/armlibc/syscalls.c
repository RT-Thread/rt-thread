/**
 * @file    rt_sys.c
 *
 * @brief   System-level syscall implementations for RT-Thread.
 *
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-23     Yihui        The first version
 * 2013-11-24     aozima       Fixed _sys_read()/_sys_write() issues.
 * 2014-08-03     bernard      If using msh, use system() implementation in msh.
 * 2020-08-05     Meco Man     Fixed _sys_flen() compiling-warning when RT_USING_DFS is not defined
 * 2020-02-13     Meco Man     Re-implement exit() and abort()
 * 2020-02-14     Meco Man     Implement _sys_tmpnam()
 */

#include <rt_sys.h>
#include <rtthread.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <compiler_private.h>
#ifdef RT_USING_POSIX_STDIO
#include <posix/stdio.h>
#endif /* RT_USING_POSIX_STDIO */

#define DBG_TAG "armlibc.syscalls"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef __clang__
__asm(".global __use_no_semihosting\n\t");
#else
#pragma import(__use_no_semihosting_swi)
#endif

/* Standard IO device handles. */
#define STDIN 0
#define STDOUT 1
#define STDERR 2

/* Standard IO device name defines. */
const char __stdin_name[] = "STDIN";
const char __stdout_name[] = "STDOUT";
const char __stderr_name[] = "STDERR";

/**
 * Required by fopen() and freopen().
 *
 * @param name - file name with path.
 * @param openmode - a bitmap whose bits mostly correspond directly to
 *                     the ISO mode specification.
 * @return -1 if an error occurs.
 */
FILEHANDLE _sys_open(const char *name, int openmode)
{
#ifdef DFS_USING_POSIX
    int fd;
    int mode = O_RDONLY;
#endif /* DFS_USING_POSIX */

    /* Register standard Input Output devices. */
    if (strcmp(name, __stdin_name) == 0)
        return (STDIN);
    if (strcmp(name, __stdout_name) == 0)
        return (STDOUT);
    if (strcmp(name, __stderr_name) == 0)
        return (STDERR);

#ifndef DFS_USING_POSIX
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    return -1; /* error */
#else
    /* Correct openmode from fopen to open */
    if (openmode & OPEN_PLUS)
    {
        if (openmode & OPEN_W)
        {
            mode |= (O_RDWR | O_TRUNC | O_CREAT);
        }
        else if (openmode & OPEN_A)
        {
            mode |= (O_RDWR | O_APPEND | O_CREAT);
        }
        else
            mode |= O_RDWR;
    }
    else
    {
        if (openmode & OPEN_W)
        {
            mode |= (O_WRONLY | O_TRUNC | O_CREAT);
        }
        else if (openmode & OPEN_A)
        {
            mode |= (O_WRONLY | O_APPEND | O_CREAT);
        }
    }

    fd = open(name, mode, 0);
    if (fd < 0)
        return -1; /* error */
    else
        return fd;
#endif /* DFS_USING_POSIX */
}

int _sys_close(FILEHANDLE fh)
{
#ifdef DFS_USING_POSIX
    if (fh <= STDERR)
        return 0; /* error */

    return close(fh);
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    return 0; /* error */
#endif /* DFS_USING_POSIX */
}

int _sys_read(FILEHANDLE fh, unsigned char *buf, unsigned len, int mode)
{
#ifdef DFS_USING_POSIX
    int size;

    if (fh == STDIN)
    {
#ifdef RT_USING_POSIX_STDIO
        if (rt_posix_stdio_get_console() < 0)
        {
            LOG_W("Do not invoke standard output before initializing Compiler");
            return 0; /* error, but keep going */
        }
        size = read(STDIN_FILENO, buf, len);
        return len - size; /* success */
#else
        LOG_W("%s: %s", __func__, _WARNING_WITHOUT_STDIO);
        return 0; /* error */
#endif /* RT_USING_POSIX_STDIO */
    }
    else if (fh == STDOUT || fh == STDERR)
    {
        return -1; /* 100% error */
    }
    else
    {
        size = read(fh, buf, len);
        if (size >= 0)
        {
            return len - size; /* success */
        }
        else
        {
            return 0; /* error */
        }
    }
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    return 0;     /* error */
#endif /* DFS_USING_POSIX */
}

int _sys_write(FILEHANDLE fh, const unsigned char *buf, unsigned len, int mode)
{
#ifdef DFS_USING_POSIX
    int size;
#endif /* DFS_USING_POSIX */

    if (fh == STDOUT || fh == STDERR)
    {
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
        rt_device_t console;
        console = rt_console_get_device();
        if (console)
        {
            rt_device_write(console, -1, buf, len);
        }
        return 0; /* success */
#else
        return 0; /* error */
#endif /* defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE) */
    }
    else if (fh == STDIN)
    {
        return -1; /* 100% error */
    }
    else
    {
#ifdef DFS_USING_POSIX
        size = write(fh, buf, len);
        if (size >= 0)
        {
            /*
            fflush doesn't have a good solution in Keil-MDK,
            so it has to sync/flush when for each writen.
            */
            fsync(fh);
            return len - size; /* success */
        }
        else
        {
            return 0; /* error */
        }
#else
        LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
        return 0; /* error */
#endif /* DFS_USING_POSIX */
    }
}

int _sys_ensure(FILEHANDLE fh)
{
#ifdef DFS_USING_POSIX
    return fsync(fh);
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    return 0; /* error */
#endif /* DFS_USING_POSIX */
}

int _sys_seek(FILEHANDLE fh, long pos)
{
#ifdef DFS_USING_POSIX
    if (fh < STDERR)
        return 0; /* error */

    /* position is relative to the start of file fh */
    return lseek(fh, pos, 0);
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    return 0; /* error */
#endif /* DFS_USING_POSIX */
}

#if __ARMCC_VERSION >= 6190000
void _sys_tmpnam(char *name, int fileno, unsigned maxlength)
{
    rt_snprintf(name, maxlength, "tem%03d", fileno);
}
#else
int _sys_tmpnam(char *name, int fileno, unsigned maxlength)
{
    rt_snprintf(name, maxlength, "tem%03d", fileno);
    return 1;
}
#endif /* __ARMCC_VERSION >= 6190000 */

char *_sys_command_string(char *cmd, int len)
{
    /* No support. */
    return RT_NULL;
}

void _ttywrch(int ch)
{
#ifdef RT_USING_CONSOLE
    rt_kprintf("%c", (char)ch);
#endif /* RT_USING_CONSOLE */
}

rt_weak void _sys_exit(int return_code)
{
    extern void __rt_libc_exit(int status);
    __rt_libc_exit(return_code);
    while (1)
        ;
}

long _sys_flen(FILEHANDLE fh)
{
#ifdef DFS_USING_POSIX
    struct stat stat;

    if (fh < STDERR)
        return 0; /* error */

    fstat(fh, &stat);
    return stat.st_size;
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    return 0;
#endif /* DFS_USING_POSIX */
}

int _sys_istty(FILEHANDLE fh)
{
    if ((STDIN <= fh) && (fh <= STDERR))
        return 1;
    else
        return 0;
}

int remove(const char *filename)
{
#ifdef DFS_USING_POSIX
    return unlink(filename);
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    return 0; /* error */
#endif /* DFS_USING_POSIX */
}

#ifdef __MICROLIB
#include <stdio.h>

int fputc(int c, FILE *f)
{
#ifdef RT_USING_CONSOLE
    rt_kprintf("%c", (char)c);
    return 1;
#else
    return 0;     /* error */
#endif /* RT_USING_CONSOLE */
}

int fgetc(FILE *f)
{
#ifdef RT_USING_POSIX_STDIO
    char ch;

    if (rt_posix_stdio_get_console() < 0)
    {
        LOG_W("Do not invoke standard output before initializing Compiler");
        return 0;
    }

    if (read(STDIN_FILENO, &ch, 1) == 1)
        return ch;
#endif /* RT_USING_POSIX_STDIO */
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_STDIO);
    return 0; /* error */
}
#endif /* __MICROLIB */
