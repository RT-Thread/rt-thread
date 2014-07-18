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
    /* TODO: adjust open file mode */
    fd = open(name, openmode, 0);
    if(fd < 0)
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
    if(size >= 0)
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
        extern rt_device_t rt_console_get_device(void);

        console_device = rt_console_get_device();
        if (console_device != 0) rt_device_write(console_device, 0, buf, len);
        return len;
#endif
    }

    if(fh == STDIN)
        return -1;

#ifndef RT_USING_DFS
    return 0;
#else
    size = write(fh - STDERR - 1, buf, len);
    if(size >= 0)
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

void _ttywrch(int ch)
{
   /* TODO */
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

/* rename() is defined in dfs_posix.c instead */
#if 0
int rename(const char *old, const char *new)
{
    return -1;
}
#endif

int system(const char *string)
{
    RT_ASSERT(0);
    for(;;);
}


