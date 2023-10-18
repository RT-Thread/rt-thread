/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-02-22     Bernard      The first version.
 * 2023-05-05     Bernard      change to dfs v2.0
 */

#ifndef __DFS_H__
#define __DFS_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../../libc/compilers/common/include/dirent.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <rtatomic.h>
#include <rtdevice.h>

#ifndef ATTR_ATIME_SET
#define ATTR_ATIME_SET	(1 << 7)
#endif

#ifndef ATTR_MTIME_SET
#define ATTR_MTIME_SET	(1 << 8)
#endif

#ifndef AT_SYMLINK_NOFOLLOW
#define AT_SYMLINK_NOFOLLOW 0x100
#endif

#ifndef UTIME_NOW
#define UTIME_NOW  0x3fffffff
#endif

#ifndef UTIME_OMIT
#define UTIME_OMIT 0x3ffffffe
#endif

#ifndef DFS_FD_MAX
#define DFS_FD_MAX              16
#endif

/*
 * skip stdin/stdout/stderr normally
 */
#ifndef DFS_STDIO_OFFSET
#define DFS_STDIO_OFFSET           3
#endif

#ifndef DFS_PATH_MAX
#define DFS_PATH_MAX             DIRENT_NAME_MAX
#endif

#ifndef SECTOR_SIZE
#define SECTOR_SIZE              512
#endif

#define DFS_FS_FLAG_DEFAULT     0x00    /* default flag */
#define DFS_FS_FLAG_FULLPATH    0x01    /* set full path to underlaying file system */

/* File flags */
#define DFS_F_FREAD     0x01
#define DFS_F_FWRITE    0x02

#ifdef __cplusplus
extern "C" {
#endif

rt_inline int dfs_fflags(int oflags)
{
    int rw = oflags & O_ACCMODE;

    oflags &= ~O_ACCMODE;
    return (rw + 1) | oflags;
}

rt_inline int dfs_oflags(int fflags)
{
    int rw = fflags & (DFS_F_FREAD | DFS_F_FWRITE);

    fflags &= ~(DFS_F_FREAD | DFS_F_FWRITE);
    return (rw - 1) | fflags;
}

struct dfs_fdtable
{
    uint32_t maxfd;
    struct dfs_file **fds;
};

/* Initialization of dfs */
int dfs_init(void);

char *dfs_normalize_path(const char *directory, const char *filename);
const char *dfs_subdir(const char *directory, const char *filename);

rt_err_t dfs_lock(void);
void dfs_unlock(void);

rt_err_t dfs_file_lock(void);
void dfs_file_unlock(void);

#ifdef DFS_USING_POSIX
/* FD APIs */
int fdt_fd_new(struct dfs_fdtable *fdt);
struct dfs_file *fdt_fd_get(struct dfs_fdtable* fdt, int fd);
void fdt_fd_release(struct dfs_fdtable* fdt, int fd);
int fd_new(void);
int fd_associate(struct dfs_fdtable *fdt, int fd, struct dfs_file *file);
struct dfs_file *fd_get(int fd);
int fd_get_fd_index(struct dfs_file *file);
void fd_release(int fd);

void fd_init(struct dfs_file *fd);

struct dfs_fdtable *dfs_fdtable_get(void);
struct dfs_fdtable *dfs_fdtable_get_global(void);
int dfs_dup(int oldfd, int startfd);
#endif /* DFS_USING_POSIX */

#ifdef __cplusplus
}
#endif

#endif
