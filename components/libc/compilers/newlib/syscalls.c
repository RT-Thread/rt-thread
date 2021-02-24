/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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
#include <errno.h>
#include <stdio.h>
#include <sys/time.h>

#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_posix.h>
#endif

#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif

/* Reentrant versions of system calls.  */

#ifndef _REENT_ONLY
int *
__errno ()
{
  return _rt_errno();
}
#endif

int
_getpid_r(struct _reent *ptr)
{
    return 0;
}

int
_close_r(struct _reent *ptr, int fd)
{
#ifndef RT_USING_DFS
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
#else
    return close(fd);
#endif
}

int
_execve_r(struct _reent *ptr, const char * name, char *const *argv, char *const *env)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_fcntl_r(struct _reent *ptr, int fd, int cmd, int arg)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_fork_r(struct _reent *ptr)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_fstat_r(struct _reent *ptr, int fd, struct stat *pstat)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_isatty_r(struct _reent *ptr, int fd)
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
int
_kill_r(struct _reent *ptr, int pid, int sig)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_link_r(struct _reent *ptr, const char *old, const char *new)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

_off_t
_lseek_r(struct _reent *ptr, int fd, _off_t pos, int whence)
{
#ifndef RT_USING_DFS
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
#else
    _off_t rc;

    rc = lseek(fd, pos, whence);
    return rc;
#endif
}

int
_mkdir_r(struct _reent *ptr, const char *name, int mode)
{
#ifndef RT_USING_DFS
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
#else
    int rc;

    rc = mkdir(name, mode);
    return rc;
#endif
}

int
_open_r(struct _reent *ptr, const char *file, int flags, int mode)
{
#ifndef RT_USING_DFS
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
#else
    int rc;

    rc = open(file, flags, mode);
    return rc;
#endif
}

_ssize_t
_read_r(struct _reent *ptr, int fd, void *buf, size_t nbytes)
{
#ifndef RT_USING_DFS
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
#else
    _ssize_t rc;

    rc = read(fd, buf, nbytes);
    return rc;
#endif
}

int
_rename_r(struct _reent *ptr, const char *old, const char *new)
{
#ifndef RT_USING_DFS
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
#else
    int rc;

    rc = rename(old, new);
    return rc;
#endif
}

void *
_sbrk_r(struct _reent *ptr, ptrdiff_t incr)
{
    /* no use this routine to get memory */
    return RT_NULL;
}

int
_stat_r(struct _reent *ptr, const char *file, struct stat *pstat)
{
#ifndef RT_USING_DFS
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
#else
    int rc;

    rc = stat(file, pstat);
    return rc;
#endif
}

int
_unlink_r(struct _reent *ptr, const char *file)
{
#ifndef RT_USING_DFS
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
#else
    return unlink(file);
#endif
}

int
_wait_r(struct _reent *ptr, int *status)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

_ssize_t
_write_r(struct _reent *ptr, int fd, const void *buf, size_t nbytes)
{
#ifndef RT_USING_DFS
#ifdef RT_USING_DEVICE
    if (fileno(stdout) == fd)
    {
        rt_device_t console;

        console = rt_console_get_device();
        if (console) return rt_device_write(console, -1, buf, nbytes);
    }

    return 0;
#else
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
#endif /*RT_USING_DEVICE*/
#else
    _ssize_t rc;

    rc = write(fd, buf, nbytes);
    return rc;
#endif
}

/* Memory routine */
void *
_malloc_r (struct _reent *ptr, size_t size)
{
    void* result;

    result = (void*)rt_malloc (size);
    if (result == RT_NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void *
_realloc_r (struct _reent *ptr, void *old, size_t newlen)
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

void
_free_r (struct _reent *ptr, void *addr)
{
    rt_free (addr);
}

/* for exit() and abort() */
__attribute__ ((noreturn)) void
_exit (int status)
{
    extern void __rt_libc_exit(int status);
    __rt_libc_exit(status);
    while(1);
}

void
_system(const char *s)
{
    extern int __rt_libc_system(const char *string);
    __rt_libc_system(s);
}

void __libc_init_array(void)
{
    /* we not use __libc init_aray to initialize C++ objects */
}

mode_t umask(mode_t mask)
{
    return 022;
}

int flock(int fd, int operation)
{
    return 0;
}

/*
These functions are implemented and replaced by the 'common/time.c' file
int _gettimeofday_r(struct _reent *ptr, struct timeval *__tp, void *__tzp);
_CLOCK_T_  _times_r(struct _reent *ptr, struct tms *ptms);
*/
