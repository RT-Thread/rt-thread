/**
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-11     Meco Man     remove _gettimeofday_r() and _times_r()
 * 2021-02-13     Meco Man     re-implement exit() and abort()
 * 2021-02-21     Meco Man     improve and beautify syscalls
 * 2021-02-24     Meco Man     fix bug of _isatty_r()
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
#ifdef RT_USING_POSIX_STDIO
#include <posix/stdio.h>
#endif /* RT_USING_POSIX_STDIO */
#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif /* RT_USING_MODULE */
#include <compiler_private.h>
#define DBG_TAG "newlib.syscalls"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_HEAP /* Memory routine */

/**
 * @brief   Allocate memory from the heap.
 *
 * @param   ptr   is a pointer to the reentrancy structure.
 * @param   size  is the number of bytes to allocate.
 *
 * @return  A pointer to the allocated memory, or RT_NULL if heap support is not enabled.
 */
void *_malloc_r(struct _reent *ptr, size_t size)
{
    void *result;

    result = (void *)rt_malloc(size);
    if (result == RT_NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

/**
 * @brief   Resize a previously allocated memory block.
 *
 * @param   ptr     is a pointer to the reentrancy structure.
 * @param   old     is a pointer to the previously allocated memory block.
 * @param   newlen  is the new size in bytes to resize the block to.
 *
 * @return  A pointer to the resized memory block, or RT_NULL if heap support is not enabled.
 */
void *_realloc_r(struct _reent *ptr, void *old, size_t newlen)
{
    void *result;

    result = (void *)rt_realloc(old, newlen);
    if (result == RT_NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

/**
 * @brief   Allocate memory for an array with elements.
 *
 * @param   ptr   is a pointer to the reentrancy structure.
 * @param   size  is the number of elements to allocate.
 * @param   len   is the size of each element in bytes.
 *
 * @return  A pointer to the allocated memory, or RT_NULL if heap support is not enabled.
 */
void *_calloc_r(struct _reent *ptr, size_t size, size_t len)
{
    void *result;

    result = (void *)rt_calloc(size, len);
    if (result == RT_NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

/**
 * @brief   Free previously allocated memory.
 *
 * @param   ptr   is a pointer to the reentrancy structure.
 * @param   addr  is a pointer to the memory block to free.
 */
void _free_r(struct _reent *ptr, void *addr)
{
    rt_free(addr);
}

#else
/**
 * @brief   Sbrk function to allocate heap memory. (Not implemented)
 *
 * @param   ptr   is a pointer to the reentrancy structure.
 * @param   incr  is the size to increment.
 *
 * @return  Always returns RT_NULL, as this function should not be used without heap support.
 */
void *_sbrk_r(struct _reent *ptr, ptrdiff_t incr)
{
    LOG_E("Please enable RT_USING_HEAP");
    RT_ASSERT(0);
    return RT_NULL;
}
#endif /* RT_USING_HEAP */

/**
 * @brief   Initialize C++ object array. (Not used in this context)
 */
void __libc_init_array(void)
{
    /* we not use __libc init_aray to initialize C++ objects */
    /* __libc_init_array is ARM code, not Thumb; it will cause a hardfault. */
}

/* Reentrant versions of system calls. */

/**
 * @brief   Get the current process ID.
 *
 * @param   ptr   is a pointer to the reentrancy structure.
 *
 * @return  Always returns 0, as the process ID is not applicable in this context.
 */
int _getpid_r(struct _reent *ptr)
{
    return 0;
}

/**
 * @brief   Close a file descriptor.
 *
 * @param   ptr   is a pointer to the reentrancy structure.
 * @param   fd    is the file descriptor to be closed.
 *
 * @return  Returns -1 if not supported without file system (ENOTSUP).
 */
int _close_r(struct _reent *ptr, int fd)
{
#ifdef DFS_USING_POSIX
    return close(fd);
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* DFS_USING_POSIX */
}

/**
 * @brief   Execute a program. (Not supported)
 *
 * @param   ptr    is a pointer to the reentrancy structure.
 * @param   name   is the name of the program to be executed.
 * @param   argv   is an array of arguments.
 * @param   env    is an array of environment variables.
 *
 * @return  Returns -1 with ENOTSUP error, as program execution is not supported.
 */
int _execve_r(struct _reent *ptr, const char *name, char *const *argv, char *const *env)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

/**
 * @brief   Perform file control operation. (Not supported)
 *
 * @param   ptr   is a pointer to the reentrancy structure.
 * @param   fd    is the file descriptor to be controlled.
 * @param   cmd   is the control command.
 * @param   arg   is the control argument.
 *
 * @return  Returns -1 with ENOTSUP error, as file control operations are not supported.
 */
int _fcntl_r(struct _reent *ptr, int fd, int cmd, int arg)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

/**
 * @brief   Create a new process. (Not supported)
 *
 * @param   ptr   is a pointer to the reentrancy structure.
 *
 * @return  Returns -1 with ENOTSUP error, as process creation is not supported.
 */
int _fork_r(struct _reent *ptr)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

/**
 * @brief   Get file status. (Not supported)
 *
 * @param   ptr    is a pointer to the reentrancy structure.
 * @param   fd     is the file descriptor to get the status of.
 * @param   pstat  is a pointer to the stat structure.
 *
 * @return  Returns -1 with ENOTSUP error, as getting file status is not supported.
 */
int _fstat_r(struct _reent *ptr, int fd, struct stat *pstat)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

/**
 * @brief   Check if a file descriptor refers to a terminal.
 *
 * @param   ptr   is a pointer to the reentrancy structure.
 * @param   fd    is the file descriptor to be checked.
 *
 * @return  Returns 1 if the file descriptor refers to a terminal, 0 otherwise.
 */
int _isatty_r(struct _reent *ptr, int fd)
{
    if (fd >= 0 && fd < 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief   Terminate a process. (Not supported)
 *
 * @param   ptr   is a pointer to the reentrancy structure.
 * @param   pid   is the process ID to terminate.
 * @param   sig   is the signal number.
 *
 * @return  Returns -1 with ENOTSUP error, as process termination is not supported.
 */
int _kill_r(struct _reent *ptr, int pid, int sig)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

/**
 * @brief   Create a hard link between two files. (Not supported)
 *
 * @param   ptr   is a pointer to the reentrancy structure.
 * @param   old   is the path to the source file.
 * @param   new   is the path to the target file.
 *
 * @return  Returns -1 with ENOTSUP error, as creating hard links is not supported.
 */
int _link_r(struct _reent *ptr, const char *old, const char *new)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

/**
 * @brief   Wait for a process to terminate. (Not supported)
 *
 * @param   ptr     is a pointer to the reentrancy structure.
 * @param   status  is a pointer to store the process status.
 *
 * @return  Returns -1 with ENOTSUP error, as process waiting is not supported.
 */
int _wait_r(struct _reent *ptr, int *status)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

/**
 * @brief   Set the file creation mask. (Not used in this context)
 */
mode_t umask(mode_t mask)
{
    return 022;
}

/**
 * @brief   Apply or remove an advisory lock on an open file. (Not used in this context)
 */
int flock(int fd, int operation)
{
    return 0;
}

/**
 * @brief   Change the file offset. (Not supported)
 *
 * @param   ptr     is a pointer to the reentrancy structure.
 * @param   fd      is the file descriptor to change the offset of.
 * @param   pos     is the new offset position.
 * @param   whence  is the reference point.
 *
 * @return  Returns -1 with ENOTSUP error, as changing the file offset is not supported.
 */
_off_t _lseek_r(struct _reent *ptr, int fd, _off_t pos, int whence)
{
#ifdef DFS_USING_POSIX
    _off_t rc;
    rc = lseek(fd, pos, whence);
    return rc;
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* DFS_USING_POSIX */
}

/**
 * @brief   Create a new directory. (Not supported)
 *
 * @param   ptr    is a pointer to the reentrancy structure.
 * @param   name   is the name of the directory to create.
 * @param   mode   is the permission mode.
 *
 * @return  Returns -1 with ENOTSUP error, as creating directories is not supported.
 */
int _mkdir_r(struct _reent *ptr, const char *name, int mode)
{
#ifdef DFS_USING_POSIX
    int rc;
    rc = mkdir(name, mode);
    return rc;
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* DFS_USING_POSIX */
}

/**
 * @brief   Open a file. (Not supported)
 *
 * @param   ptr     is a pointer to the reentrancy structure.
 * @param   file    is the name of the file to be opened.
 * @param   flags   is the file open flags.
 * @param   mode    is the permission mode.
 *
 * @return  Returns -1 with ENOTSUP error, as opening files is not supported.
 */
int _open_r(struct _reent *ptr, const char *file, int flags, int mode)
{
#ifdef DFS_USING_POSIX
    int rc;
    rc = open(file, flags, mode);
    return rc;
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* DFS_USING_POSIX */
}

/**
 * @brief   Read data from a file descriptor.
 *
 * @param   ptr     is a pointer to the reentrancy structure.
 * @param   fd      is the file descriptor.
 * @param   buf     is the buffer to store the read data.
 * @param   nbytes  is the number of bytes to read.
 *
 * @return  The number of bytes read, or -1 if an error occurred.
 */
_ssize_t _read_r(struct _reent *ptr, int fd, void *buf, size_t nbytes)
{
#ifdef DFS_USING_POSIX
    _ssize_t rc;
    if (fd == STDIN_FILENO)
    {
#ifdef RT_USING_POSIX_STDIO
        if (rt_posix_stdio_get_console() < 0)
        {
            LOG_W("Do not invoke standard input before initializing Compiler");
            return 0;
        }
#else
        LOG_W("%s: %s", __func__, _WARNING_WITHOUT_STDIO);
        ptr->_errno = ENOTSUP;
        return -1;
#endif /* RT_USING_POSIX_STDIO */
    }
    else if (fd == STDOUT_FILENO || fd == STDERR_FILENO)
    {
        ptr->_errno = ENOTSUP;
        return -1;
    }

    rc = read(fd, buf, nbytes);
    return rc;
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* DFS_USING_POSIX */
}

/**
 * @brief   Rename a file or directory.
 *
 * @param   ptr     is a pointer to the reentrancy structure.
 * @param   old     is the old file or directory name.
 * @param   new     is the new file or directory name.
 *
 * @return  0 if successful, or -1 if an error occurred.
 */
int _rename_r(struct _reent *ptr, const char *old, const char *new)
{
#ifdef DFS_USING_POSIX
    int rc;
    rc = rename(old, new);
    return rc;
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* DFS_USING_POSIX */
}

/**
 * @brief   Get file status.
 *
 * @param   ptr     is a pointer to the reentrancy structure.
 * @param   file    is the path to the file or directory.
 * @param   pstat   is a pointer to a 'struct stat' object to store the file status.
 *
 * @return  0 if successful, or -1 if an error occurred.
 */
int _stat_r(struct _reent *ptr, const char *file, struct stat *pstat)
{
#ifdef DFS_USING_POSIX
    int rc;
    rc = stat(file, pstat);
    return rc;
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* DFS_USING_POSIX */
}

/**
 * @brief   Remove a file or directory.
 *
 * @param   ptr     is a pointer to the reentrancy structure.
 * @param   file    is the path to the file or directory to remove.
 *
 * @return  0 if successful, or -1 if an error occurred.
 */
int _unlink_r(struct _reent *ptr, const char *file)
{
#ifdef DFS_USING_POSIX
    return unlink(file);
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* DFS_USING_POSIX */
}

/**
 * @brief   Write data to a file descriptor.
 *
 * @param   ptr     is a pointer to the reentrancy structure.
 * @param   fd      is the file descriptor.
 * @param   buf     is the buffer containing the data to write.
 * @param   nbytes  is the number of bytes to write.
 *
 * @return  The number of bytes written, or -1 if an error occurred.
 */
_ssize_t _write_r(struct _reent *ptr, int fd, const void *buf, size_t nbytes)
{
#ifdef DFS_USING_POSIX
    _ssize_t rc;
#endif /* DFS_USING_POSIX */

    if (fd == STDOUT_FILENO || fd == STDERR_FILENO)
    {
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
        rt_device_t console;

        console = rt_console_get_device();
        if (console)
            return rt_device_write(console, -1, buf, nbytes);
#else
        ptr->_errno = ENOTSUP;
        return -1;
#endif /* defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE) */
    }
    else if (fd == STDIN_FILENO)
    {
        ptr->_errno = ENOTSUP;
        return -1;
    }

#ifdef DFS_USING_POSIX
    rc = write(fd, buf, nbytes);
    return rc;
#else
    LOG_W("%s: %s", __func__, _WARNING_WITHOUT_FS);
    ptr->_errno = ENOTSUP;
    return -1;
#endif /* DFS_USING_POSIX */
}

/* for exit() and abort() */
__attribute__((noreturn)) void _exit(int status)
{
    extern void __rt_libc_exit(int status);
    __rt_libc_exit(status);
    while (1)
        ;
}

/* These functions are implemented and replaced by the 'common/time.c' file
int _gettimeofday_r(struct _reent *ptr, struct timeval *__tp, void *__tzp);
_CLOCK_T_  _times_r(struct _reent *ptr, struct tms *ptms);
*/
