/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
    int (*open)     (struct dfs_file *fd);
    int (*close)    (struct dfs_file *fd);
    int (*ioctl)    (struct dfs_file *fd, int cmd, void *args);
    int (*read)     (struct dfs_file *fd, void *buf, size_t count);
    int (*write)    (struct dfs_file *fd, const void *buf, size_t count);
    int (*flush)    (struct dfs_file *fd);
    int (*lseek)    (struct dfs_file *fd, off_t offset);
    int (*getdents) (struct dfs_file *fd, struct dirent *dirp, uint32_t count);

    int (*poll)     (struct dfs_file *fd, struct rt_pollreq *req);
};

/* file descriptor */
#define DFS_FD_MAGIC     0xfdfd

struct dfs_vnode
{
    uint16_t type;               /* Type (regular or socket) */

    char *path;                  /* Name (below mount point) */
    char *fullpath;              /* Full path is hash key */
    int ref_count;               /* Descriptor reference count */
    rt_list_t list;              /* The node of vnode hash table */

    struct dfs_filesystem *fs;
    const struct dfs_file_ops *fops;
    uint32_t flags;              /* self flags, is dir etc.. */

    size_t   size;               /* Size in bytes */
    void *data;                  /* Specific file system data */
};

struct dfs_file
{
    uint16_t magic;              /* file descriptor magic number */
    uint32_t flags;              /* Descriptor flags */
    int ref_count;               /* Descriptor reference count */
    off_t    pos;                /* Current file position */
    struct dfs_vnode *vnode;     /* file node struct */
    void *data;                  /* Specific fd data */
};

struct dfs_mmap2_args
{
    void *addr;
    size_t length;
    int prot;
    int flags;
    off_t pgoffset;

    void *ret;
};

void dfs_vnode_mgr_init(void);
int dfs_file_is_open(const char *pathname);
int dfs_file_open(struct dfs_file *fd, const char *path, int flags);
int dfs_file_close(struct dfs_file *fd);
int dfs_file_ioctl(struct dfs_file *fd, int cmd, void *args);
int dfs_file_read(struct dfs_file *fd, void *buf, size_t len);
int dfs_file_getdents(struct dfs_file *fd, struct dirent *dirp, size_t nbytes);
int dfs_file_unlink(const char *path);
int dfs_file_write(struct dfs_file *fd, const void *buf, size_t len);
int dfs_file_flush(struct dfs_file *fd);
int dfs_file_lseek(struct dfs_file *fd, off_t offset);

int dfs_file_stat(const char *path, struct stat *buf);
int dfs_file_rename(const char *oldpath, const char *newpath);
int dfs_file_ftruncate(struct dfs_file *fd, off_t length);
int dfs_file_mmap2(struct dfs_file *fd, struct dfs_mmap2_args *mmap2);

/* 0x5254 is just a magic number to make these relatively unique ("RT") */
#define RT_FIOFTRUNCATE  0x52540000U
#define RT_FIOGETADDR    0x52540001U
#define RT_FIOMMAP2      0x52540002U

#ifdef __cplusplus
}
#endif

#endif
