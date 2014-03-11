/*
 * File      : posix_types.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-12-23     Bernard      Add the checking for ESHUTDOWN 
 */

#ifndef __POSIX_TYPES_H__
#define __POSIX_TYPES_H__

#include <rtthread.h>

/* compatible in different compiler and C runtime library */
#ifdef RT_USING_NEWLIB
/* normarlly, GNU GCC will use newlib as C runtime library */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/signal.h>
#include <sys/fcntl.h>

#include <errno.h>
#include <stdarg.h>

#ifndef ESHUTDOWN
#define ESHUTDOWN 180
#endif

#else

/* ARM compiler and IAR compiler */
#if defined(__CC_ARM) || defined(__IAR_SYSTEMS_ICC__)   
#include <stddef.h>
#include <stdarg.h>
#include <string.h>

typedef rt_int32_t clockid_t;
typedef rt_int32_t key_t;       /* Used for interprocess communication. */
typedef rt_int32_t pid_t;       /* Used for process IDs and process group IDs. */
typedef signed long ssize_t;    /* Used for a count of bytes or an error indication. */
typedef signed long time_t;     /* Used for time in seconds. */

struct timespec
{
    time_t tv_sec;          /* seconds */
    long tv_nsec;           /* nanoseconds */
};

struct timeval
{
    long    tv_sec;         /* seconds */
    long    tv_usec;        /* microseconds */
};

#ifdef RT_USING_LWIP
#include <lwip/arch.h>
#else
#define EPERM        1  /* Operation not permitted */
#define ENOENT       2  /* No such file or directory */
#define ESRCH        3  /* No such process */
#define EINTR        4  /* Interrupted system call */
#define EBADF        9  /* Bad file number */
#define EAGAIN      11  /* Try again */
#define ENOMEM      12  /* Out of memory */
#define EBUSY       16  /* Device or resource busy */
#define EEXIST      17  /* File exists */
#define EINVAL      22  /* Invalid argument */
#define ENFILE      23  /* File table overflow */
#define EDEADLK     45  /* Resource deadlock would occur */
#define EBADMSG     77  /* Not a data message */
#define ENOSYS      89  /* Function not implemented */
#define EOPNOTSUPP  122 /* Operation not supported on transport endpoint */
#define ETIMEDOUT   145 /* Connection timed out */
#endif

#ifdef RT_USING_DFS
#include <dfs_posix.h>
#else
typedef rt_uint16_t mode_t;
#define O_RDONLY        0x0000000
#define O_WRONLY        0x0000001
#define O_RDWR          0x0000002
#define O_ACCMODE       0x0000003
#define O_CREAT         0x0000100
#define O_EXCL          0x0000200
#define O_TRUNC         0x0001000
#define O_APPEND        0x0002000
#define O_DIRECTORY     0x0200000
#endif

#elif defined (__GNUC__)                    /* GNU GCC Compiler, with minilibc */
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#endif

#endif

#endif
