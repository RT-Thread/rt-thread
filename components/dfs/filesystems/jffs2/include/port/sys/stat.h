#ifndef CYGONCE_ISO_SYS_TYPES_H
#define CYGONCE_ISO_SYS_TYPES_H
/*========================================================================
//
//      sys/types.h
//
//      POSIX types
//
//========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####
// -------------------------------------------
// This file is part of eCos, the Embedded Configurable Operating System.
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 or (at your option) any later
// version.
//
// eCos is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License
// along with eCos; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
// As a special exception, if other files instantiate templates or use
// macros or inline functions from this file, or you compile this file
// and link it with other works to produce a work based on this file,
// this file does not by itself cause the resulting work to be covered by
// the GNU General Public License. However the source code for this file
// must still be made available in accordance with section (3) of the GNU
// General Public License v2.
//
// This exception does not invalidate any other reasons why a work based
// on this file might be covered by the GNU General Public License.
// -------------------------------------------
// ####ECOSGPLCOPYRIGHTEND####
//========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):     jlarmour
// Contributors:
// Date:          2000-04-14
// Purpose:       This file provides various types required by POSIX 1003.1.
// Description:   The real contents of this file get set from the
//                configuration (set by the implementation)
// Usage:         #include <sys/types.h>
//
//####DESCRIPTIONEND####
//
//======================================================================
*/

/* CONFIGURATION */

//#include <pkgconf/system.h>
//#include <pkgconf/isoinfra.h>          /* Configuration header */

/* INCLUDES */

/* This is the "standard" way to get size_t from stddef.h,
 * which is the canonical location of the definition.
 */
//#define __need_size_t
//#include <stddef.h>
#include "port/codes.h"

/*
#ifndef dev_t
typedef short dev_t;
#endif

#ifndef ino_t
typedef unsigned int ino_t;
#endif

#ifndef mode_t
typedef unsigned int mode_t;
#endif
*/

typedef unsigned short nlink_t;
typedef long off_t;

typedef unsigned short gid_t;
typedef unsigned short uid_t;
typedef int pid_t;

//
typedef void *cyg_io_handle_t;

/* Variable names for pathconf()			*/
#define _PC_ASYNC_IO                 1
#define	_PC_CHOWN_RESTRICTED	     2
#define	_PC_LINK_MAX		         3
#define	_PC_MAX_CANON		         4
#define	_PC_MAX_INPUT		         5
#define	_PC_NAME_MAX		         6
#define	_PC_NO_TRUNC		         7
#define	_PC_PATH_MAX		         8
#define	_PC_PIPE_BUF		         9
#define _PC_PRIO_IO                 10
#define _PC_SYNC_IO                 11
#define	_PC_VDISABLE		        12

//limit.h
/* DEFINES */

/*-----------------------------------------------------------------------------
 * Minimum values from POSIX.1 tables 2-3, 2-7 and 2-7a.

 * These are the standard-mandated minimum values.
 * These values do not vary with the implementation - they may
 * simply be defined
 */

/* Minimum number of operations in one list I/O call.  */
#define _POSIX_AIO_LISTIO_MAX	2

/* Minimal number of outstanding asynchronous I/O operations.  */
#define _POSIX_AIO_MAX		1

/* Maximum length of arguments to `execve', including environment.  */
#define	_POSIX_ARG_MAX		4096

/* Maximum simultaneous processes per real user ID.  */
#define	_POSIX_CHILD_MAX	6

/* Minimal number of timer expiration overruns.  */
#define _POSIX_DELAYTIMER_MAX	32

/* Maximum link count of a file.  */
#define	_POSIX_LINK_MAX		8

/* Size of storage required for a login name */
#define _POSIX_LOGIN_NAME_MAX   9

/* Number of bytes in a terminal canonical input queue.  */
#define	_POSIX_MAX_CANON	255

/* Number of bytes for which space will be
   available in a terminal input queue.  */
#define	_POSIX_MAX_INPUT	255

/* Maximum number of message queues open for a process.  */
#define _POSIX_MQ_OPEN_MAX	8

/* Maximum number of supported message priorities.  */
#define _POSIX_MQ_PRIO_MAX	32

/* Number of bytes in a filename.  */
#define	_POSIX_NAME_MAX		14

/* Number of simultaneous supplementary group IDs per process.  */
#define	_POSIX_NGROUPS_MAX	0

/* Number of files one process can have open at once.  */
#define	_POSIX_OPEN_MAX		16

/* Number of bytes in a pathname.  */
#define	_POSIX_PATH_MAX		255

/* Number of bytes than can be written atomically to a pipe.  */
#define	_POSIX_PIPE_BUF		512

/* Minimal number of realtime signals reserved for the application.  */
#define _POSIX_RTSIG_MAX	8

/* Number of semaphores a process can have.  */
#define _POSIX_SEM_NSEMS_MAX	256

/* Maximal value of a semaphore.  */
#define _POSIX_SEM_VALUE_MAX	32767

/* Number of pending realtime signals.  */
#define _POSIX_SIGQUEUE_MAX	32

/* Largest value of a `ssize_t'.  */
#define	_POSIX_SSIZE_MAX	32767

/* Number of streams a process can have open at once.  */
#define	_POSIX_STREAM_MAX	8

/* Controlling the iterations of destructors for thread-specific data.  */
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS	4

/* The number of data keys per process.  */
#define _POSIX_THREAD_KEYS_MAX	128

/* The number of threads per process.  */
#define _POSIX_THREAD_THREADS_MAX	64

/* Maximum number of characters in a tty name.  */
#define	_POSIX_TTY_NAME_MAX	9

/* Number of timer for a process.  */
#define _POSIX_TIMER_MAX	32

/* Maximum length of a timezone name (element of `tzname').  */
#define	_POSIX_TZNAME_MAX	3

/* Maximum clock resolution in nanoseconds.  */
#define _POSIX_CLOCKRES_MIN	20000000


#ifdef CYGBLD_ISO_SSIZET_HEADER
# include CYGBLD_ISO_SSIZET_HEADER
#else
# ifndef __STRICT_ANSI__
#  define SSIZE_MAX LONG_MAX
# endif
#endif

/* INCLUDES */

#ifdef CYGBLD_ISO_OPEN_MAX_HEADER
# include CYGBLD_ISO_OPEN_MAX_HEADER
#else
# ifndef __STRICT_ANSI__
#  define OPEN_MAX _POSIX_OPEN_MAX
# endif
#endif

#ifdef CYGBLD_ISO_LINK_MAX_HEADER
# include CYGBLD_ISO_LINK_MAX_HEADER
#else
# ifndef __STRICT_ANSI__
#  define LINK_MAX _POSIX_LINK_MAX
# endif
#endif

#ifdef CYGBLD_ISO_NAME_MAX_HEADER
# include CYGBLD_ISO_NAME_MAX_HEADER
#else
# ifndef __STRICT_ANSI__
#  define NAME_MAX _POSIX_NAME_MAX
# endif
#endif

#ifdef CYGBLD_ISO_PATH_MAX_HEADER
# include CYGBLD_ISO_PATH_MAX_HEADER
#else
# ifndef __STRICT_ANSI__
#  define PATH_MAX _POSIX_PATH_MAX
# endif
#endif

#if CYGINT_ISO_POSIX_LIMITS
# ifdef CYGBLD_ISO_POSIX_LIMITS_HEADER
#  include CYGBLD_ISO_POSIX_LIMITS_HEADER
# endif
#endif


#define CYGNUM_FILEIO_MTAB_MAX  16

//-----------------------------------------------
//  stat.h need by fs-ecos.h
//-----------------------------------------------
#define __stat_mode_DIR    (1<<0)
#define __stat_mode_CHR    (1<<1)
#define __stat_mode_BLK    (1<<2)
#define __stat_mode_REG    (1<<3)
#define __stat_mode_FIFO   (1<<4)
#define __stat_mode_MQ     (1<<5)
#define __stat_mode_SEM    (1<<6)
#define __stat_mode_SHM    (1<<7)
#define __stat_mode_LNK    (1<<8)
#define __stat_mode_SOCK   (1<<9)

#if defined(MSVC)
/* for time_t */
#include <time.h>
typedef unsigned long mode_t;
typedef unsigned int ino_t;
typedef unsigned int dev_t;
typedef long ssize_t;
#elif defined(__CC_ARM)  
#define mode_t unsigned long
typedef unsigned int ino_t;
typedef unsigned int dev_t;
typedef long ssize_t;
typedef long time_t;
#elif defined(__GNUC__) && !defined(__CC_ARM)
#include <sys/types.h>
#endif

#endif /* CYGONCE_ISO_SYS_TYPES_H multiple inclusion protection */

/* EOF sys/types.h */

