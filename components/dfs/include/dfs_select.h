#ifndef DFS_SELECT_H__
#define DFS_SELECT_H__

#include <libc/libc_fdset.h>

#ifdef __cplusplus
extern "C" {
#endif

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

#ifdef __cplusplus
}
#endif

#endif

