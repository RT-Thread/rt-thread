/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-05     Bernard      Implement dentry in dfs v2.0
 */

#ifndef __DFS_DENTRY_H__
#define __DFS_DENTRY_H__

#include "dfs_file.h"
#include "dfs_fs.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct dfs_mnt;
struct dfs_vnode;

struct dfs_dentry
{
    rt_list_t hashlist;

    uint32_t flags;

#define DENTRY_IS_MOUNTED   0x1 /* dentry is mounted */
#define DENTRY_IS_ALLOCED   0x2 /* dentry is allocated */
#define DENTRY_IS_ADDHASH   0x4 /* dentry was added into hash table */
#define DENTRY_IS_OPENED    0x8 /* dentry was opened. */
    char *pathname;             /* the pathname under mounted file sytem */

    struct dfs_vnode *vnode;    /* the vnode of this dentry */
    struct dfs_mnt *mnt;        /* which mounted file system does this dentry belong to */

    rt_atomic_t ref_count;    /* the reference count */
};

struct dfs_dentry *dfs_dentry_create(struct dfs_mnt *mnt, char *fullpath);
struct dfs_dentry *dfs_dentry_create_rela(struct dfs_mnt *mnt, char *rela_path);
struct dfs_dentry *dfs_dentry_unref(struct dfs_dentry *dentry);
struct dfs_dentry *dfs_dentry_ref(struct dfs_dentry *dentry);
void dfs_dentry_insert(struct dfs_dentry *dentry);
struct dfs_dentry *dfs_dentry_lookup(struct dfs_mnt *mnt, const char *path, uint32_t flags);

/* get full path of a dentry */
char* dfs_dentry_full_path(struct dfs_dentry* dentry);

/* get pathname (with mnt path) of a dentry */
char* dfs_dentry_pathname(struct dfs_dentry* dentry);

/* get full path crc32 */
uint32_t dfs_dentry_full_path_crc32(struct dfs_dentry* dentry);

int dfs_dentry_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DFS_DENTRY_H__*/
