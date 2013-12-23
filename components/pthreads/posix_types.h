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

/* errno definitions */
#define EPERM        1  /* Operation not permitted */
#define ENOENT       2  /* No such file or directory */
#define ESRCH        3  /* No such process */
#define EINTR        4  /* Interrupted system call */
#define EIO          5  /* I/O error */
#define ENXIO        6  /* No such device or address */
#define E2BIG        7  /* Arg list too long */
#define ENOEXEC      8  /* Exec format error */
#define EBADF        9  /* Bad file number */
#define ECHILD      10  /* No child processes */
#define EAGAIN      11  /* Try again */
#define ENOMEM      12  /* Out of memory */
#define EACCES      13  /* Permission denied */
#define EFAULT      14  /* Bad address */
#define ENOTBLK     15  /* Block device required */
#define EBUSY       16  /* Device or resource busy */
#define EEXIST      17  /* File exists */
#define EXDEV       18  /* Cross-device link */
#define ENODEV      19  /* No such device */
#define ENOTDIR     20  /* Not a directory */
#define EISDIR      21  /* Is a directory */
#define EINVAL      22  /* Invalid argument */
#define ENFILE      23  /* File table overflow */
#define EMFILE      24  /* Too many open files */
#define ENOTTY      25  /* Not a typewriter */
#define ETXTBSY     26  /* Text file busy */
#define EFBIG       27  /* File too large */
#define ENOSPC      28  /* No space left on device */
#define ESPIPE      29  /* Illegal seek */
#define EROFS       30  /* Read-only file system */
#define EMLINK      31  /* Too many links */
#define EPIPE       32  /* Broken pipe */
#define EDOM        33  /* Math argument out of domain of func */
#define ERANGE      34  /* Math result not representable */
#define ENOMSG      35  /* No message of desired type */
#define EIDRM       36  /* Identifier removed */
#define ECHRNG      37  /* Channel number out of range */
#define EL2NSYNC    38  /* Level 2 not synchronized */
#define EL3HLT      39  /* Level 3 halted */
#define EL3RST      40  /* Level 3 reset */
#define ELNRNG      41  /* Link number out of range */
#define EUNATCH     42  /* Protocol driver not attached */
#define ENOCSI      43  /* No CSI structure available */
#define EL2HLT      44  /* Level 2 halted */
#define EDEADLK     45  /* Resource deadlock would occur */
#define ENOLCK      46  /* No record locks available */
#define EBADE       50  /* Invalid exchange */
#define EBADR       51  /* Invalid request descriptor */
#define EXFULL      52  /* Exchange full */
#define ENOANO      53  /* No anode */
#define EBADRQC     54  /* Invalid request code */
#define EBADSLT     55  /* Invalid slot */
#define EDEADLOCK   56  /* File locking deadlock error */
#define EBFONT      59  /* Bad font file format */
#define ENOSTR      60  /* Device not a stream */
#define ENODATA     61  /* No data available */
#define ETIME       62  /* Timer expired */
#define ENOSR       63  /* Out of streams resources */
#define ENONET      64  /* Machine is not on the network */
#define ENOPKG      65  /* Package not installed */
#define EREMOTE     66  /* Object is remote */
#define ENOLINK     67  /* Link has been severed */
#define EADV        68  /* Advertise error */
#define ESRMNT      69  /* Srmount error */
#define ECOMM       70  /* Communication error on send */
#define EPROTO      71  /* Protocol error */
#define EDOTDOT     73  /* RFS specific error */
#define EMULTIHOP   74  /* Multihop attempted */
#define EBADMSG     77  /* Not a data message */
#define ENAMETOOLONG    78  /* File name too long */
#define EOVERFLOW   79  /* Value too large for defined data type */
#define ENOTUNIQ    80  /* Name not unique on network */
#define EBADFD      81  /* File descriptor in bad state */
#define EREMCHG     82  /* Remote address changed */
#define ELIBACC     83  /* Can not access a needed shared library */
#define ELIBBAD     84  /* Accessing a corrupted shared library */
#define ELIBSCN     85  /* .lib section in a.out corrupted */
#define ELIBMAX     86  /* Attempting to link in too many shared libraries */
#define ELIBEXEC    87  /* Cannot exec a shared library directly */
#define EILSEQ      88  /* Illegal byte sequence */
#define ENOSYS      89  /* Function not implemented */
#define ELOOP       90  /* Too many symbolic links encountered */
#define ERESTART    91  /* Interrupted system call should be restarted */
#define ESTRPIPE    92  /* Streams pipe error */
#define ENOTEMPTY   93  /* Directory not empty */
#define EUSERS      94  /* Too many users */
#define ENOTSOCK    95  /* Socket operation on non-socket */
#define EDESTADDRREQ    96  /* Destination address required */
#define EMSGSIZE    97  /* Message too long */
#define EPROTOTYPE  98  /* Protocol wrong type for socket */
#define ENOPROTOOPT 99  /* Protocol not available */
#define EPROTONOSUPPORT 120 /* Protocol not supported */
#define ESOCKTNOSUPPORT 121 /* Socket type not supported */
#define EOPNOTSUPP  122 /* Operation not supported on transport endpoint */
#define ENOTSUP     EOPNOTSUPP/* Operation not supported on transport endpoint */
#define EPFNOSUPPORT    123 /* Protocol family not supported */
#define EAFNOSUPPORT    124 /* Address family not supported by protocol */
#define EADDRINUSE  125 /* Address already in use */
#define EADDRNOTAVAIL   126 /* Cannot assign requested address */
#define ENETDOWN    127 /* Network is down */
#define ENETUNREACH 128 /* Network is unreachable */
#define ENETRESET   129 /* Network dropped connection because of reset */
#define ECONNABORTED    130 /* Software caused connection abort */
#define ECONNRESET  131 /* Connection reset by peer */
#define ENOBUFS     132 /* No buffer space available */
#define EISCONN     133 /* Transport endpoint is already connected */
#define ENOTCONN    134 /* Transport endpoint is not connected */
#define EUCLEAN     135 /* Structure needs cleaning */
#define ENOTNAM     137 /* Not a XENIX named type file */
#define ENAVAIL     138 /* No XENIX semaphores available */
#define EISNAM      139 /* Is a named type file */
#define EREMOTEIO   140 /* Remote I/O error */
#define EINIT       141 /* Reserved */
#define EREMDEV     142 /* Error 142 */
#define ESHUTDOWN   143 /* Cannot send after transport endpoint shutdown */
#define ETOOMANYREFS    144 /* Too many references: cannot splice */
#define ETIMEDOUT   145 /* Connection timed out */
#define ECONNREFUSED    146 /* Connection refused */
#define EHOSTDOWN   147 /* Host is down */
#define EHOSTUNREACH    148 /* No route to host */
#define EWOULDBLOCK EAGAIN  /* Operation would block */
#define EALREADY    149 /* Operation already in progress */
#define EINPROGRESS 150 /* Operation now in progress */
#define ESTALE      151 /* Stale NFS file handle */
#define ECANCELED   158 /* AIO operation canceled */
#define ENOMEDIUM   159 /* No medium found */
#define EMEDIUMTYPE 160 /* Wrong medium type */
#define ENOKEY      161 /* Required key not available */
#define EKEYEXPIRED 162 /* Key has expired */
#define EKEYREVOKED 163 /* Key has been revoked */
#define EKEYREJECTED    164 /* Key was rejected by service */
#define EDQUOT      1133    /* Quota exceeded */

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
