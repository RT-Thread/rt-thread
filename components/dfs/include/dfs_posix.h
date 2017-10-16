/*
 * File      : dfs_posix.h
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2012, RT-Thread Development Team
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
 * 2009-05-27     Yi.qiu       The first version.
 * 2010-07-18     Bernard      add stat and statfs structure definitions.
 * 2011-05-16     Yi.qiu       Change parameter name of rename, "new" is C++ key word.
 */

#ifndef __DFS_POSIX_H__
#define __DFS_POSIX_H__

#include <dfs_file.h>
#include <sys/time.h> /* for struct timeval */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int fd;     /* directory file */
    char buf[512];
    int num;
    int cur;
} DIR;

/* directory api*/
int mkdir(const char *path, mode_t mode);
DIR *opendir(const char *name);
struct dirent *readdir(DIR *d);
long telldir(DIR *d);
void seekdir(DIR *d, off_t offset);
void rewinddir(DIR *d);
int closedir(DIR* d);

/* file api*/
int open(const char *file, int flags, int mode);
int close(int d);
#ifdef RT_USING_NEWLIB
_READ_WRITE_RETURN_TYPE _EXFUN(read, (int __fd, void *__buf, size_t __nbyte));
_READ_WRITE_RETURN_TYPE _EXFUN(write, (int __fd, const void *__buf, size_t __nbyte));
#else
int read(int fd, void *buf, size_t len);
int write(int fd, const void *buf, size_t len);
#endif
off_t lseek(int fd, off_t offset, int whence);
int rename(const char *from, const char *to);
int unlink(const char *pathname);
int stat(const char *file, struct stat *buf);
int fstat(int fildes, struct stat *buf);
int fsync(int fildes);
int ioctl(int fildes, int cmd, void *data);

/* directory api*/
int rmdir(const char *path);
int chdir(const char *path);
char *getcwd(char *buf, size_t size);

/* file system api */
int statfs(const char *path, struct statfs *buf);

int access(const char *path, int amode);
int pipe(int fildes[2]);
int mkfifo(const char *path, mode_t mode);

/* poll and select */

#define POLLIN          (0x01)
#define POLLRDNORM      (0x01)
#define POLLRDBAND      (0x01)
#define POLLPRI         (0x01)

#define POLLOUT         (0x02)
#define POLLWRNORM      (0x02)
#define POLLWRBAND      (0x02)

#define POLLERR         (0x04)
#define POLLHUP         (0x08)
#define POLLNVAL        (0x10)

#define POLLMASK_DEFAULT (POLLIN | POLLOUT | POLLRDNORM | POLLWRNORM)

typedef unsigned int nfds_t;

struct pollfd
{
    int fd;
    short events;
    short revents;
};

int poll(struct pollfd *fds, nfds_t nfds, int timeout);


#ifdef RT_USING_LWIP
/* we use lwIP's structure definitions. */
#include <lwip/sockets.h>
#else

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

#endif

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

#ifdef __cplusplus
}
#endif

#endif
