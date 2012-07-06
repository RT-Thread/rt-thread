#ifndef __ERRNO_H__
#define __ERRNO_H__

#ifdef RT_USING_DFS

#include <dfs_def.h>

/* using device error codes */
#define ENOENT		DFS_STATUS_ENOENT
#define EIO		 	DFS_STATUS_EIO
#define ENXIO		DFS_STATUS_ENXIO
#define EBADF		DFS_STATUS_EBADF
#define EAGAIN		DFS_STATUS_EAGAIN
#define ENOMEM		DFS_STATUS_ENOMEM
#define EBUSY		DFS_STATUS_EBUSY
#define EEXIST		DFS_STATUS_EEXIST
#define EXDEV		DFS_STATUS_EXDEV
#define ENODEV		DFS_STATUS_ENODEV
#define ENOTDIR		DFS_STATUS_ENOTDIR
#define EISDIR		DFS_STATUS_EISDIR
#define EINVAL		DFS_STATUS_EINVAL
#define ENOSPC		DFS_STATUS_ENOSPC
#define EROFS		DFS_STATUS_EROFS
#define ENOSYS		DFS_STATUS_ENOSYS
#define ENOTEMPTY	DFS_STATUS_ENOTEMPTY

#else

/* error codes */
#define ENOENT		2		/* No such file or directory */
#define EIO		 	5		/* I/O error */
#define ENXIO		6		/* No such device or address */
#define EBADF		9		/* Bad file number */
#define EAGAIN		11		/* Try again */
#define ENOMEM		12		/* no memory */
#define EBUSY		16		/* Device or resource busy */
#define EEXIST		17		/* File exists */
#define EXDEV		18		/* Cross-device link */
#define ENODEV		19		/* No such device */
#define ENOTDIR		20		/* Not a directory */
#define EISDIR		21		/* Is a directory */
#define EINVAL		22		/* Invalid argument */
#define ENOSPC		28		/* No space left on device */
#define EROFS		30		/* Read-only file system */
#define ENOSYS		38		/* Function not implemented */
#define ENOTEMPTY	39		/* Directory not empty */

#endif

#define	EPERM		1		/* Not super-user */
#define	ESRCH		3		/* No such process */
#define	EINTR		4		/* Interrupted system call */
#define	ENFILE		23		/* Too many open files in system */
#define	EDEADLK		45		/* Deadlock condition */
#define EBADMSG		77		/* Trying to read unreadable message */
#define ETIMEDOUT	116		/* Connection timed out */
#define ENOTSUP		134		/* Not supported */

#endif
