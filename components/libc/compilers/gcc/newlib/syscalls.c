/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-11     Meco Man     remove _gettimeofday_r() and _times_r()
 * 2020-02-13     Meco Man     re-implement exit() and abort()
 * 2020-02-21     Meco Man     improve and beautify syscalls
 * 2020-02-24     Meco Man     fix bug of _isatty_r()
 */

#include <reent.h>
#include <rtthread.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/stat.h>
#ifdef RT_USING_POSIX
#include "libc.h"
#endif
#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif

#define DBG_TAG    "newlib.syscalls"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_HEAP /* Memory routine */
void *_malloc_r (struct _reent *ptr, size_t size)
{
    void* result;

    result = (void*)rt_malloc (size);
    if (result == RT_NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void *_realloc_r (struct _reent *ptr, void *old, size_t newlen)
{
    void* result;

    result = (void*)rt_realloc (old, newlen);
    if (result == RT_NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void *_calloc_r (struct _reent *ptr, size_t size, size_t len)
{
    void* result;

    result = (void*)rt_calloc (size, len);
    if (result == RT_NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void _free_r (struct _reent *ptr, void *addr)
{
    rt_free (addr);
}

#else
void *
_sbrk_r(struct _reent *ptr, ptrdiff_t incr)
{
    LOG_E("Please enable RT_USING_HEAP or RT_USING_LIBC");
    RT_ASSERT(0);
    return RT_NULL;
}
#endif /*RT_USING_HEAP*/

void __libc_init_array(void)
{
    /* we not use __libc init_aray to initialize C++ objects */
    /* __libc_init_array is ARM code, not Thumb; it will cause a hardfault. */
}

#ifdef RT_USING_LIBC

/* Reentrant versions of system calls.  */
#ifndef _REENT_ONLY
int *__errno ()
{
  return _rt_errno();
}
#endif

int _getpid_r(struct _reent *ptr)
{
    return 0;
}

int _close_r(struct _reent *ptr, int fd)
{
    return close(fd);
}

int _execve_r(struct _reent *ptr, const char * name, char *const *argv, char *const *env)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

int _fcntl_r(struct _reent *ptr, int fd, int cmd, int arg)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

int _fork_r(struct _reent *ptr)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

int _fstat_r(struct _reent *ptr, int fd, struct stat *pstat)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

int _isatty_r(struct _reent *ptr, int fd)
{
    if (fd >=0 && fd < 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int _kill_r(struct _reent *ptr, int pid, int sig)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

int _link_r(struct _reent *ptr, const char *old, const char *new)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

int _wait_r(struct _reent *ptr, int *status)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

mode_t umask(mode_t mask)
{
    return 022;
}

int flock(int fd, int operation)
{
    return 0;
}

_off_t _lseek_r(struct _reent *ptr, int fd, _off_t pos, int whence)
{
#ifdef RT_USING_POSIX
    _off_t rc;

    rc = lseek(fd, pos, whence);
    return rc;
#else
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* RT_USING_POSIX */
}

int _mkdir_r(struct _reent *ptr, const char *name, int mode)
{
#ifdef RT_USING_POSIX
    int rc;

    rc = mkdir(name, mode);
    return rc;
#else
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* RT_USING_POSIX */
}

int _open_r(struct _reent *ptr, const char *file, int flags, int mode)
{
#ifdef RT_USING_POSIX
    int rc;
    rc = open(file, flags, mode);
    return rc;
#else
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* RT_USING_POSIX */
}

_ssize_t _read_r(struct _reent *ptr, int fd, void *buf, size_t nbytes)
{
#ifdef RT_USING_POSIX
    _ssize_t rc;
    if (libc_stdio_get_console() < 0 && fd == STDIN_FILENO)
    {
        LOG_W("Do not invoke standard input before initializing libc");
        return 0;
    }
    rc = read(fd, buf, nbytes);
    return rc;
#else
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* RT_USING_POSIX */
}

int _rename_r(struct _reent *ptr, const char *old, const char *new)
{
#ifdef RT_USING_POSIX
    int rc;

    rc = rename(old, new);
    return rc;
#else
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* RT_USING_POSIX */
}

int _stat_r(struct _reent *ptr, const char *file, struct stat *pstat)
{
#ifdef RT_USING_POSIX
    int rc;

    rc = stat(file, pstat);
    return rc;
#else
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* RT_USING_POSIX */
}

int _unlink_r(struct _reent *ptr, const char *file)
{
#ifdef RT_USING_POSIX
    return unlink(file);
#else
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* RT_USING_POSIX */
}

_ssize_t _write_r(struct _reent *ptr, int fd, const void *buf, size_t nbytes)
{
#ifdef RT_USING_POSIX
    _ssize_t rc;
    if (libc_stdio_get_console() < 0 && fd == STDOUT_FILENO)
    {
        LOG_W("Do not invoke standard output before initializing libc");
        return 0;
    }
    rc = write(fd, buf, nbytes);
    return rc;
#elif defined(RT_USING_CONSOLE)
    if (STDOUT_FILENO == fd)
    {
        rt_device_t console;

        console = rt_console_get_device();
        if (console)
            return rt_device_write(console, -1, buf, nbytes);
    }
#endif /* RT_USING_POSIX */
    ptr->_errno = ENOTSUP;
    return -1;
}

/* for exit() and abort() */
__attribute__ ((noreturn)) void _exit (int status)
{
    extern void __rt_libc_exit(int status);
    __rt_libc_exit(status);
    while(1);
}

/*
These functions are implemented and replaced by the 'common/time.c' file
int _gettimeofday_r(struct _reent *ptr, struct timeval *__tp, void *__tzp);
_CLOCK_T_  _times_r(struct _reent *ptr, struct tms *ptms);
*/

#endif /* RT_USING_LIBC */
