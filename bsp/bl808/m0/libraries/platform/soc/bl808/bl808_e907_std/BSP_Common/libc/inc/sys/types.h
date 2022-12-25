/*
 * sys/types.h
 */

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#include <stddef.h>
#include <stdint.h>

#define _SSIZE_T
typedef ptrdiff_t ssize_t;

#undef NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif

typedef int daddr_t;
typedef char *caddr_t;

/* BSD */
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

/* SysV */
typedef unsigned char unchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

/* More BSD */
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef uint64_t u_int64_t;

/* Time related */
typedef signed int sbintime_t;

/* Required by cyassl build */
typedef long off_t;
typedef short dev_t;
typedef unsigned short ino_t;
typedef unsigned short nlink_t;
typedef unsigned short uid_t;
typedef unsigned short mode_t;
typedef unsigned short gid_t;
typedef signed char pid_t;
typedef unsigned long useconds_t;

/*
 * Some headers seem to require this...
 */
#ifndef BITS_PER_LONG
# define BITS_PER_LONG 32
#endif

/*
 * The following FD_SET macros were added to solve the issue where the
 * lwip/sockets.h saw different sys/types.h files when built, and when its
 * header files sys/sockets file was included by the SDK.
 */
/*
 * Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields (the filesystem macros use chars).
 * FD_SETSIZE may be defined by the user, but the default here
 * should be >= NOFILE (param.h).
 */
#ifndef FD_SET
#ifndef FD_SETSIZE
#define  FD_SETSIZE      64
#endif
#define FD_SET(n, p)  ((p)->fd_bits[(n)/8] |=  (1 << ((n) & 7)))
#define FD_CLR(n, p)  ((p)->fd_bits[(n)/8] &= ~(1 << ((n) & 7)))
#define FD_ISSET(n, p) ((p)->fd_bits[(n)/8] &   (1 << ((n) & 7)))
#define FD_ZERO(p)    memset((void *)(p), 0, sizeof(*(p)))

typedef struct fd_set {
	unsigned char fd_bits[(FD_SETSIZE + 7) / 8];
} fd_set;
#endif /* FD_SET */

#ifndef __ICCARM__
/* wmsdk: Added from sys/times.h and machine/types.h */
#define	_CLOCK_T_	unsigned long		/* clock() */
#ifndef __clock_t_defined
typedef _CLOCK_T_ clock_t;
#define __clock_t_defined
#endif
#endif

#endif /* _SYS_TYPES_H */
