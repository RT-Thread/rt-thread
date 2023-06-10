/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-02-22     Bernard      The first version.
 * 2023-05-05     Bernard      Change to dfs v2.0
 */

#ifndef __DFS_FS_H__
#define __DFS_FS_H__

#include <dfs.h>
#include <dfs_file.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* file system partition table */
struct dfs_partition
{
    uint8_t type; /* file system type */
    off_t offset; /* partition start offset */
    size_t size;  /* partition size */
    rt_sem_t lock;
};

struct dfs_attr
{
    mode_t  st_mode;
};

struct dfs_mnt;
struct dfs_dentry;
struct dfs_vnode;

struct statfs;

struct dfs_filesystem_ops
{
    const char *name;
    uint32_t flags;
#define FS_NEED_DEVICE 0x1

    const struct dfs_file_ops *default_fops;

    int (*mount)(struct dfs_mnt *mnt, unsigned long rwflag, const void *data);
    int (*umount)(struct dfs_mnt *mnt);

    int (*mkfs)(rt_device_t devid, const char *fs_name);

    int (*readlink)(struct dfs_dentry *dentry, char *buf, int len);
    int (*link)(struct dfs_dentry *src_dentry, struct dfs_dentry *dst_dentry); /*hard link interface */
    int (*unlink)(struct dfs_dentry *dentry);
    int (*symlink)(struct dfs_dentry *parent_dentry, const char *target, const char *newpath); /*soft link interface*/

    int (*rename)(struct dfs_dentry *old_dentry, struct dfs_dentry *new_dentry);
    int (*stat)(struct dfs_dentry *dentry, struct stat *buf);

    int (*statfs)(struct dfs_mnt *mnt, struct statfs *buf);

    int (*setattr) (struct dfs_dentry *dentry, struct dfs_attr *attr);

    struct dfs_vnode* (*lookup)(struct dfs_dentry *dentry);

    struct dfs_vnode* (*create_vnode)(struct dfs_dentry *dentry, int type, mode_t mode);
    int (*free_vnode)(struct dfs_vnode* vnode);
};

struct dfs_filesystem_type
{
    const struct dfs_filesystem_ops *fs_ops;
    struct dfs_filesystem_type *next;
};

int dfs_unregister(struct dfs_filesystem_type *fs);
int dfs_register(struct dfs_filesystem_type *fs);
const char *dfs_filesystem_get_mounted_path(struct rt_device *device);

int dfs_mount(const char *device_name,
            const char *path,
            const char *filesystemtype,
            unsigned long rwflag,
            const void *data);
int dfs_umount(const char *specialfile);
int dfs_unmount(const char *specialfile);
int dfs_mkfs(const char *fs_name, const char *device_name);
int dfs_statfs(const char *path, struct statfs *buffer);
int dfs_filesystem_get_partition(struct dfs_partition *part,
                                uint8_t *buf,
                                uint32_t pindex);

#ifdef __cplusplus
}
#endif

#endif
