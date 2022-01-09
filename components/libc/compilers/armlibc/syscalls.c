/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-23     Yihui        The first version
 * 2013-11-24     aozima       fixed _sys_read()/_sys_write() issues.
 * 2014-08-03     bernard      If using msh, use system() implementation
 *                             in msh.
 * 2020-08-05     Meco Man     fixed _sys_flen() compiling-warning when
 *                             RT_USING_DFS is not defined
 * 2020-02-13     Meco Man     re-implement exit() and abort()
 * 2020-02-14     Meco Man     implement _sys_tmpnam()
 */

#include <rt_sys.h>
#include <rtthread.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <compiler_private.h>
#ifdef RT_USING_POSIX_STDIO
#include "libc.h"
#endif /* RT_USING_POSIX_STDIO */

#define DBG_TAG    "armlibc.syscalls"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifdef __clang__
__asm(".global __use_no_semihosting\n\t");
#else
#pragma import(__use_no_semihosting_swi)
#endif

/* Standard IO device handles. */
#define STDIN       0
#define STDOUT      1
#define STDERR      2

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
    return 0; /* error */
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
        return 0; /* error */
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
    return 0;
#endif /* DFS_USING_POSIX */
}

/*
 * Read from a file. Can return:
 *  - zero if the read was completely successful
 *  - the number of bytes _not_ read, if the read was partially successful
 *  - the number of bytes not read, plus the top bit set (0x80000000), if
 *    the read was partially successful due to end of file
 *  - -1 if some error other than EOF occurred
 *
 * It is also legal to signal EOF by returning no data but
 * signalling no error (i.e. the top-bit-set mechanism need never
 * be used).
 *
 * So if (for example) the user is trying to read 8 bytes at a time
 * from a file in which only 5 remain, this routine can do three
 * equally valid things:
 *
 *  - it can return 0x80000003 (3 bytes not read due to EOF)
 *  - OR it can return 3 (3 bytes not read), and then return
 *    0x80000008 (8 bytes not read due to EOF) on the next attempt
 *  - OR it can return 3 (3 bytes not read), and then return
 *    8 (8 bytes not read, meaning 0 read, meaning EOF) on the next
 *    attempt
 *
 * `mode' exists for historical reasons and must be ignored.
 */
int _sys_read(FILEHANDLE fh, unsigned char *buf, unsigned len, int mode)
{
#ifdef DFS_USING_POSIX
    int size;

    if (fh == STDIN)
    {
#ifdef RT_USING_POSIX_STDIO
        if (libc_stdio_get_console() < 0)
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
    return 0; /* error */
#endif /* DFS_USING_POSIX */
}

/*
 * Write to a file. Returns 0 on success, negative on error, and
 * the number of characters _not_ written on partial success.
 * `mode' exists for historical reasons and must be ignored.
 * The return value is either:
 * A positive number representing the number of characters not written
 * (so any nonzero return value denotes a failure of some sort).
 * A negative number indicating an error.
 */
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

/*
 * Move the file position to a given offset from the file start.
 * Returns >=0 on success, <0 on failure.
 */
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

/**
 * used by tmpnam() or tmpfile()
 */
int _sys_tmpnam(char *name, int fileno, unsigned maxlength)
{
    rt_snprintf(name, maxlength, "tem%03d", fileno);
    return 1;
}

char *_sys_command_string(char *cmd, int len)
{
    /* no support */
    return RT_NULL;
}

/* This function writes a character to the console. */
void _ttywrch(int ch)
{
#ifdef RT_USING_CONSOLE
    rt_kprintf("%c", (char)ch);
#endif /* RT_USING_CONSOLE */
}

/* for exit() and abort() */
RT_WEAK void _sys_exit(int return_code)
{
    extern void __rt_libc_exit(int status);
    __rt_libc_exit(return_code);
    while(1);
}

/**
 * return current length of file.
 *
 * @param fh - file handle
 * @return file length, or -1 on failed
 */
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
    if((STDIN <= fh) && (fh <= STDERR))
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
    return 0; /* error */
#endif /* RT_USING_CONSOLE */
}

int fgetc(FILE *f)
{
#ifdef RT_USING_POSIX_STDIO
    char ch;

    if (libc_stdio_get_console() < 0)
    {
        LOG_W("Do not invoke standard output before initializing Compiler");
        return 0;
    }

    if(read(STDIN_FILENO, &ch, 1) == 1)
        return ch;
#endif /* RT_USING_POSIX_STDIO */
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_STDIO);
    return 0; /* error */
}

#endif /* __MICROLIB */
