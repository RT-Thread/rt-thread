/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-05     Bernard      Implement dentry in dfs v2.0
 */

#ifndef DFS_MNT_H__
#define DFS_MNT_H__

#include <rtservice.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct dfs_mnt;
struct dfs_dentry;
struct dfs_filesystem_ops;

struct dfs_mnt
{
    struct dfs_mnt *parent;         /* the parent mounted file system */

    rt_list_t sibling;              /* the sibling node for mounted list */
    rt_list_t child;                /* the child node for mounted list */

    char *fullpath;                 /* the fullpath of this mounted file system */
    int flags;                      /* the falgs of this mounted file system */

#define MNT_IS_ALLOCED 0x1          /* the mnt struct is allocated */
#define MNT_IS_ADDLIST 0x2          /* the mnt struct is added into list */
#define MNT_IS_MOUNTED 0x4          /* the mnt struct is mounted */
#define MNT_IS_UMOUNT  0x8          /* the mnt is unmount */
#define MNT_IS_LOCKED  0x10         /* the mnt is locked */
#define MNT_FORCE      0x20         /* the mnt force unmount */
#define MNT_LAZY_UMNT  0x40         /* the mnt has pending umount */
#define MNT_RDONLY     0x80         /* the mnt is read only */

    rt_atomic_t ref_count;          /* reference count */

    rt_device_t dev_id;             /* the mounted device id */
    const struct dfs_filesystem_ops *fs_ops;

    void *data;
};

struct dfs_mnt *dfs_mnt_create(const char *path);
int dfs_mnt_destroy(struct dfs_mnt* mnt);
int dfs_mnt_list(struct dfs_mnt* mnt);
int dfs_mnt_insert(struct dfs_mnt* mnt, struct dfs_mnt* child);

struct dfs_mnt *dfs_mnt_dev_lookup(rt_device_t dev_id);
struct dfs_mnt *dfs_mnt_lookup(const char *path);
const char *dfs_mnt_get_mounted_path(struct rt_device *device);

struct dfs_mnt* dfs_mnt_ref(struct dfs_mnt* mnt);
int dfs_mnt_unref(struct dfs_mnt* mnt);

int dfs_mnt_umount(struct dfs_mnt *mnt, int flags);
int dfs_mnt_setflags(struct dfs_mnt *mnt, int flags);

rt_bool_t dfs_mnt_has_child_mnt(struct dfs_mnt *mnt, const char* fullpath);

int dfs_mnt_foreach(struct dfs_mnt* (*func)(struct dfs_mnt *mnt, void *parameter), void *parameter);
int dfs_mnt_umount_iter(rt_bool_t (*filter)(struct dfs_mnt *mnt, void *parameter), void *parameter);

typedef void (*dfs_mnt_umnt_cb_t)(struct dfs_mnt *mnt);
RT_OBJECT_HOOKLIST_DECLARE(dfs_mnt_umnt_cb_t, dfs_mnt_umnt);

#ifdef __cplusplus
}
#endif

#endif
