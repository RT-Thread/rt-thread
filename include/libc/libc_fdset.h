/*
 * File      : libc_errno.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
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
 * 2017-10-30     Bernard      The first version
 */

#ifndef LIBC_FDSET_H__
#define LIBC_FDSET_H__

#include <rtconfig.h>

#if defined(RT_USING_NEWLIB) || defined(_WIN32)
#include <sys/types.h>
#if defined(HAVE_SYS_SELECT_H)
#include <sys/select.h>
#endif

#else

#ifdef RT_USING_DFS_NET

#ifdef FD_SETSIZE
#undef FD_SETSIZE
#endif

#define FD_SETSIZE      DFS_FD_MAX
#endif

#  ifndef   FD_SETSIZE
#   define  FD_SETSIZE  32
#  endif

#  define   NBBY    8       /* number of bits in a byte */

typedef long    fd_mask;
#  define   NFDBITS (sizeof (fd_mask) * NBBY)   /* bits per mask */
#  ifndef   howmany
#   define  howmany(x,y)    (((x)+((y)-1))/(y))
#  endif

/* We use a macro for fd_set so that including Sockets.h afterwards
   can work.  */
typedef struct _types_fd_set {
    fd_mask fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} _types_fd_set;

#define fd_set _types_fd_set

#  define   FD_SET(n, p)    ((p)->fds_bits[(n)/NFDBITS] |= (1L << ((n) % NFDBITS)))
#  define   FD_CLR(n, p)    ((p)->fds_bits[(n)/NFDBITS] &= ~(1L << ((n) % NFDBITS)))
#  define   FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & (1L << ((n) % NFDBITS)))
#  define   FD_ZERO(p)      memset((void*)(p), 0, sizeof(*(p)))

#endif

#endif
