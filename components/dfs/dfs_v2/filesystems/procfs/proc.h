/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __PROC_H__
#define __PROC_H__

#include <dfs_file.h>
#include <dfs_seq_file.h>
#include <dfs_vfs.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct proc_dentry;

struct proc_ops
{
    struct proc_dentry *(*lookup)(struct proc_dentry *parent, const char *name);
    int (*readlink)(struct proc_dentry *dentry, char *buf, int len);
};

struct proc_dentry
{
    rt_uint32_t mode;
    rt_atomic_t ref_count;

    struct proc_dentry *parent;
    struct dfs_vfs_node node;

    const struct dfs_file_ops *fops;
    const struct proc_ops *ops;
    const struct dfs_seq_ops *seq_ops;
    int (*single_show)(struct dfs_seq_file *seq, void *data);

    int pid;

    char *name;
    void *data;
};

struct proc_dentry *dfs_proc_find(const char *name);

struct proc_dentry *proc_mkdir_data(const char *name, mode_t mode, struct proc_dentry *parent,
                                    const struct dfs_file_ops *fops, void *data);
struct proc_dentry *proc_mkdir_mode(const char *name, mode_t mode, struct proc_dentry *parent);
struct proc_dentry *proc_mkdir(const char *name, struct proc_dentry *parent);

struct proc_dentry *proc_create_data(const char *name, mode_t mode, struct proc_dentry *parent,
                                     const struct dfs_file_ops *fops, void *data);
struct proc_dentry *proc_create_single_data(const char *name, mode_t mode, struct proc_dentry *parent,
                                            int (*show)(struct dfs_seq_file *, void *), void *data);

struct proc_dentry *proc_symlink(const char *name, struct proc_dentry *parent, const char *dest);

struct proc_dentry *proc_acquire(struct proc_dentry *dentry);
void proc_release(struct proc_dentry *dentry);

void proc_remove(struct proc_dentry *dentry);
void proc_remove_dentry(const char *name, struct proc_dentry *parent);

int proc_pid(int pid);

#ifdef __cplusplus
}
#endif

#endif
