/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-01-26     Bernard      The first version.
 */

#ifndef __DFS_FILE_H__
#define __DFS_FILE_H__

#include <dfs.h>
#include <dfs_fs.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rt_pollreq;

struct dfs_file_ops
{
    int (*open)     (struct dfs_fd *fd);
    int (*close)    (struct dfs_fd *fd);
    int (*ioctl)    (struct dfs_fd *fd, int cmd, void *args);
    int (*read)     (struct dfs_fd *fd, void *buf, size_t count);
    int (*write)    (struct dfs_fd *fd, const void *buf, size_t count);
    int (*flush)    (struct dfs_fd *fd);
    int (*lseek)    (struct dfs_fd *fd, off_t offset);
    int (*getdents) (struct dfs_fd *fd, struct dirent *dirp, uint32_t count);

    int (*poll)     (struct dfs_fd *fd, struct rt_pollreq *req);
};

/* file descriptor */
#define DFS_FD_MAGIC     0xfdfd
struct dfs_fd
{
    uint16_t magic;              /* file descriptor magic number */
    uint16_t type;               /* Type (regular or socket) */

    char *path;                  /* Name (below mount point) */
    int ref_count;               /* Descriptor reference count */

    struct dfs_filesystem *fs;
    const struct dfs_file_ops *fops;

    uint32_t flags;              /* Descriptor flags */
    size_t   size;               /* Size in bytes */
    off_t    pos;                /* Current file position */

    void *data;                  /* Specific file system data */
};

int dfs_file_open(struct dfs_fd *fd, const char *path, int flags);
int dfs_file_close(struct dfs_fd *fd);
int dfs_file_ioctl(struct dfs_fd *fd, int cmd, void *args);
int dfs_file_read(struct dfs_fd *fd, void *buf, size_t len);
int dfs_file_getdents(struct dfs_fd *fd, struct dirent *dirp, size_t nbytes);
int dfs_file_unlink(const char *path);
int dfs_file_write(struct dfs_fd *fd, const void *buf, size_t len);
int dfs_file_flush(struct dfs_fd *fd);
int dfs_file_lseek(struct dfs_fd *fd, off_t offset);

int dfs_file_stat(const char *path, struct stat *buf);
int dfs_file_rename(const char *oldpath, const char *newpath);
int dfs_file_ftruncate(struct dfs_fd *fd, off_t length);

/* 0x5254 is just a magic number to make these relatively unique ("RT") */
#define RT_FIOFTRUNCATE 0x52540000U

#ifdef __cplusplus
}
#endif

#endif
