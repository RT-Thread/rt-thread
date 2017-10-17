#ifndef DFS_SELECT_H__
#define DFS_SELECT_H__

#ifdef RT_USING_LWIP
/* we use lwIP's structure definitions. */
#include <lwip/sockets.h>
#elif defined(RT_USING_POSIX)

#ifndef FD_SET

/* Get the total number of descriptors that we will have to support */

#define FD_SETSIZE (12)

/* We will use a 32-bit bitsets to represent the set of descriptors.  How
 * many uint32_t's do we need to span all descriptors?
 */

#if FD_SETSIZE <= 32
#  define __SELECT_NUINT32 1
#elif FD_SETSIZE <= 64
#  define __SELECT_NUINT32 2
#elif FD_SETSIZE <= 96
#  define __SELECT_NUINT32 3
#elif FD_SETSIZE <= 128
#  define __SELECT_NUINT32 4
#elif FD_SETSIZE <= 160
#  define __SELECT_NUINT32 5
#elif FD_SETSIZE <= 192
#  define __SELECT_NUINT32 6
#elif FD_SETSIZE <= 224
#  define __SELECT_NUINT32 7
#elif FD_SETSIZE <= 256
#  define __SELECT_NUINT32 8
#else
#  warning "Larger fd_set needed"
#endif

/* These macros map a file descriptor to an index and bit number */

#define _FD_NDX(fd)    ((fd) >> 5)
#define _FD_BIT(fd)      ((fd) & 0x1f)

/* Standard helper macros */

#define FD_CLR(fd,set) \
  ((((fd_set*)(set))->arr)[_FD_NDX(fd)] &= ~(1 << _FD_BIT(fd)))
#define FD_SET(fd,set) \
  ((((fd_set*)(set))->arr)[_FD_NDX(fd)] |= (1 << _FD_BIT(fd)))
#define FD_ISSET(fd,set) \
  (((((fd_set*)(set))->arr)[_FD_NDX(fd)] & (1 << _FD_BIT(fd))) != 0)
#define FD_ZERO(set) \
   memset((set), 0, sizeof(fd_set))

typedef struct
{
    uint32_t arr[__SELECT_NUINT32];
}fd_set;
#endif

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

#endif  /* end of RT_USING_LWIP */

#endif
