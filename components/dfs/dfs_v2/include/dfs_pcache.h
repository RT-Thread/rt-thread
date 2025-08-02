/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
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

struct rt_varea;
struct rt_aspace;
struct dfs_vnode;
struct dfs_dentry;
struct dfs_aspace;

/* Memory mapping structure for page cache */
struct dfs_mmap
{
    rt_list_t mmap_node;          /* List node for address space's mmap list */
    struct rt_aspace *aspace;     /* Address space this mapping belongs to */
    void *vaddr;                  /* Virtual address where the page is mapped */
};

/* Page structure for file system page cache */
struct dfs_page
{
    rt_list_t space_node;         /* Node for address space's page list */
    rt_list_t dirty_node;         /* Node for dirty page list */
    struct util_avl_struct avl_node; /* Node for AVL tree in address space */
    rt_list_t mmap_head;          /* Head of memory mappings list */

    rt_atomic_t ref_count;        /* Reference count for this page */

    void *page;                   /* Pointer to physical page data */
    off_t fpos;                   /* File position this page represents */
    size_t size;                  /* Total size of the page */
    size_t len;                   /* Valid data length in the page */
    int is_dirty;                 /* Dirty flag indicating if page needs writeback */
    rt_tick_t tick_ms;            /* Last access timestamp */

    struct dfs_aspace *aspace;    /* Address space this page belongs to */
};

/* Address space operations interface */
struct dfs_aspace_ops
{
    ssize_t (*read)(struct dfs_file *file, struct dfs_page *page);  /* Read operation for page cache */
    ssize_t (*write)(struct dfs_page *page);                       /* Write operation for page cache */
};

/* Address space structure for page cache management */
struct dfs_aspace
{
    rt_list_t hash_node, cache_node;  /* Nodes for hash table and cache lists */
    char *fullpath, *pathname;        /* Full path and relative path strings */
    struct dfs_mnt *mnt;              /* Mount point this space belongs to */

    rt_list_t list_active, list_inactive;  /* Active and inactive page lists */
    rt_list_t list_dirty;                  /* Dirty page list */
    size_t pages_count;                    /* Total pages in this space */

    struct util_avl_root avl_root;          /* AVL tree root for page lookup */
    struct dfs_page *avl_page;             /* Current AVL tree page */

    rt_bool_t is_active;                   /* Active/inactive status flag */

    struct rt_mutex lock;                  /* Mutex for thread safety */
    rt_atomic_t ref_count;                 /* Reference counter */

    struct dfs_vnode *vnode;               /* Associated vnode */
    const struct dfs_aspace_ops *ops;      /* Operations interface */
};

#ifndef RT_PAGECACHE_HASH_NR
#define RT_PAGECACHE_HASH_NR   1024
#endif

/* Global page cache management structure */
struct dfs_pcache
{
    rt_list_t head[RT_PAGECACHE_HASH_NR];  /* Hash table buckets for address spaces */
    rt_list_t list_active, list_inactive;  /* Active and inactive space lists */
    rt_atomic_t pages_count;              /* Total cached pages count */
    struct rt_mutex lock;                 /* Global lock for thread safety */
    struct rt_messagequeue *mqueue;       /* Message queue for sending GC/WB command.*/
    rt_tick_t last_time_wb;               /* Last writeback timestamp */
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
void dfs_pcache_clean(struct dfs_mnt *mnt);

#ifdef __cplusplus
}
#endif

#endif

#endif