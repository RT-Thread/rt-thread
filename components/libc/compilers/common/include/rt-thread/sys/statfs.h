/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-27     xqyjlj       adapt musl
 */

#ifndef __SYS_STATFS_H__
#define __SYS_STATFS_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_MUSLLIBC
/* this is required for musl <sys/statfs.h> */
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#include_next <sys/statfs.h>
/* limiting influence of _POSIX_SOURCE */
#undef _POSIX_SOURCE

#else /* def _POSIX_SOURCE */
#include_next <sys/statfs.h>
#endif
#else
struct statfs
{
    size_t f_bsize;   /* block size */
    size_t f_blocks;  /* total data blocks in file system */
    size_t f_bfree;   /* free blocks in file system */
    size_t f_bavail;  /* free blocks available to unprivileged user*/
};

int statfs(const char *path, struct statfs *buf);
int fstatfs(int fd, struct statfs *buf);

#endif

#ifdef __cplusplus
}
#endif

#endif
