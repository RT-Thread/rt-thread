/*
 * File     : stubs.c
 * Brief    : reimplement some basic functions of arm standard c library
 *
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-23     Yihui        The first version
 * 2013-11-24     aozima       fixed _sys_read()/_sys_write() issues.
 * 2014-08-03     bernard      If using msh, use system() implementation
 *                             in msh.
 */

#include <string.h>
#include <rt_sys.h>

#include "rtthread.h"

#ifdef RT_USING_DFS
#include "dfs_posix.h"
#endif

#pragma import(__use_no_semihosting_swi)

/* TODO: Standard IO device handles. */
#define STDIN       1
#define STDOUT      2
#define STDERR      3

/* Standard IO device name defines. */
const char __stdin_name[]  = "STDIN";
const char __stdout_name[] = "STDOUT";
const char __stderr_name[] = "STDERR";

/**
 * required by fopen() and freopen().
 *
 * @param name - file name with path.
 * @param openmode - a bitmap hose bits mostly correspond directly to
 *                     the ISO mode specification.
 * @return  -1 if an error occurs.
 */
FILEHANDLE _sys_open(const char *name, int openmode)
{
#ifdef RT_USING_DFS
    int fd;
    int mode = O_RDONLY;
#endif

    /* Register standard Input Output devices. */
    if (strcmp(name, __stdin_name) == 0)
        return (STDIN);
    if (strcmp(name, __stdout_name) == 0)
        return (STDOUT);
    if (strcmp(name, __stderr_name) == 0)
        return (STDERR);

#ifndef RT_USING_DFS
    return -1;
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
        return -1;
    else
        return fd + STDERR + 1;
#endif
}

int _sys_close(FILEHANDLE fh)
{
#ifndef RT_USING_DFS
    return 0;
#else
    if (fh < STDERR)
        return 0;

    return close(fh - STDERR - 1);
#endif
}

/**
 * read data
 *
 * @param fh - file handle
 * @param buf - buffer to save read data
 * @param len - max length of data buffer
 * @param mode - useless, for historical reasons
 * @return The number of bytes not read.
 */
int _sys_read(FILEHANDLE fh, unsigned char *buf, unsigned len, int mode)
{
#ifdef RT_USING_DFS
    int size;
#endif

    if (fh == STDIN)
    {
        /* TODO */
        return 0;
    }

    if ((fh == STDOUT) || (fh == STDERR))
        return -1;

#ifndef RT_USING_DFS
    return 0;
#else
    size = read(fh - STDERR - 1, buf, len);
    if (size >= 0)
        return len - size;
    else
        return -1;
#endif
}

/**
 * write data
 *
 * @param fh - file handle
 * @param buf - data buffer
 * @param len - buffer length
 * @param mode - useless, for historical reasons
 * @return a positive number representing the number of characters not written.
 */
int _sys_write(FILEHANDLE fh, const unsigned char *buf, unsigned len, int mode)
{
#ifdef RT_USING_DFS
    int size;
#endif

    if ((fh == STDOUT) || (fh == STDERR))
    {
#ifndef RT_USING_CONSOLE
        return 0;
#else
        rt_device_t console_device;

        console_device = rt_console_get_device();
        if (console_device != 0) rt_device_write(console_device, 0, buf, len);

        return 0;
#endif
    }

    if (fh == STDIN)
        return -1;

#ifndef RT_USING_DFS
    return 0;
#else
    size = write(fh - STDERR - 1, buf, len);
    if (size >= 0)
        return len - size;
    else
        return -1;
#endif
}

/**
 * put he file pointer at offset pos from the beginning of the file.
 *
 * @param pos - offset
 * @return the current file position, or -1 on failed
 */
int _sys_seek(FILEHANDLE fh, long pos)
{
    if (fh < STDERR)
        return -1;

#ifndef RT_USING_DFS
    return -1;
#else

    /* position is relative to the start of file fh */
    return lseek(fh - STDERR - 1, pos, 0);
#endif
}

/**
 * used by tmpnam() or tmpfile()
 */
int _sys_tmpnam(char *name, int fileno, unsigned maxlength)
{
    return -1;
}

char *_sys_command_string(char *cmd, int len)
{
    /* no support */
    return cmd;
}

/* This function writes a character to the console. */
void _ttywrch(int ch)
{
#ifdef RT_USING_CONSOLE
    char c;

    c = (char)ch;
    rt_kprintf(&c);
#endif
}

void _sys_exit(int return_code)
{
    /* TODO: perhaps exit the thread which is invoking this function */
    while (1);
}

/**
 * return current length of file.
 *
 * @param fh - file handle
 * @return file length, or -1 on failed
 */
long _sys_flen(FILEHANDLE fh)
{
    return -1;
}

int _sys_istty(FILEHANDLE fh)
{
    return 0;
}

int remove(const char *filename)
{
#ifndef RT_USING_DFS
    return -1;
#else
    return unlink(filename);
#endif
}

#if defined(RT_USING_FINSH) && defined(FINSH_USING_MSH) && defined(RT_USING_MODULE) && defined(RT_USING_DFS)
/* use system(const char *string) implementation in the msh */
#else
int system(const char *string)
{
    RT_ASSERT(0);
    for (;;);
}
#endif
