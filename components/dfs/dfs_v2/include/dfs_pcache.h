/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-05     RTT          Implement dentry in dfs v2.0
 */

#ifndef DFS_PAGE_CACHE_H__
#define DFS_PAGE_CACHE_H__

#include <rtthread.h>

#ifdef RT_USING_PAGECACHE

#include <dfs_file.h>
#include <avl.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct dfs_vnode;
struct dfs_dentry;
struct dfs_aspace;

struct dfs_mmap
{
    rt_list_t mmap_node;
    struct rt_varea *varea;
};

struct dfs_page
{
    rt_list_t space_node;
    rt_list_t dirty_node;
    struct util_avl_struct avl_node;
    rt_list_t mmap_head;

    rt_atomic_t ref_count;

    void *page;
    off_t fpos;
    size_t size;
    size_t len;
    int is_dirty;
    rt_tick_t tick_ms;

    struct dfs_aspace *aspace;
};

struct dfs_aspace_ops
{
    ssize_t (*read)(struct dfs_file *file, struct dfs_page *page);
    ssize_t (*write)(struct dfs_page *page);
};

struct dfs_aspace
{
    rt_list_t hash_node, cache_node;
    char *fullpath, *pathname;
    struct dfs_mnt *mnt;

    rt_list_t list_active, list_inactive;
    rt_list_t list_dirty;
    size_t pages_count;

    struct util_avl_root avl_root;
    struct dfs_page *avl_page;

    rt_bool_t is_active;

    struct rt_mutex lock;
    rt_atomic_t ref_count;

    struct dfs_vnode *vnode;
    const struct dfs_aspace_ops *ops;
};

#ifndef RT_PAGECACHE_HASH_NR
#define RT_PAGECACHE_HASH_NR   1024
#endif

struct dfs_pcache
{
    rt_list_t head[RT_PAGECACHE_HASH_NR];
    rt_list_t list_active, list_inactive;
    rt_atomic_t pages_count;
    struct rt_mutex lock;
    struct rt_messagequeue *mqueue;
    rt_tick_t last_time_wb;
};

struct dfs_aspace *dfs_aspace_create(struct dfs_dentry *dentry, struct dfs_vnode *vnode, const struct dfs_aspace_ops *ops);
int dfs_aspace_destroy(struct dfs_aspace *aspace);

int dfs_aspace_read(struct dfs_file *file, void *buf, size_t count, off_t *pos);
int dfs_aspace_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos);
int dfs_aspace_flush(struct dfs_aspace *aspace);
int dfs_aspace_clean(struct dfs_aspace *aspace);

void *dfs_aspace_mmap(struct dfs_file *file, struct rt_varea *varea, void *vaddr);
int dfs_aspace_unmap(struct dfs_file *file, struct rt_varea *varea);
int dfs_aspace_page_unmap(struct dfs_file *file, struct rt_varea *varea, void *vaddr);
int dfs_aspace_page_dirty(struct dfs_file *file, struct rt_varea *varea, void *vaddr);

off_t dfs_aspace_fpos(struct rt_varea *varea, void *vaddr);
void *dfs_aspace_vaddr(struct rt_varea *varea, off_t fpos);

int dfs_aspace_mmap_read(struct dfs_file *file, struct rt_varea *varea, void *data);
int dfs_aspace_mmap_write(struct dfs_file *file, struct rt_varea *varea, void *data);

void dfs_pcache_release(size_t count);
void dfs_pcache_unmount(struct dfs_mnt *mnt);

#ifdef __cplusplus
}
#endif

#endif

#endif
