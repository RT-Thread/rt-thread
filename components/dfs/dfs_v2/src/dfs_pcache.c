/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-05     RTT          Implement mnt in dfs v2.0
 * 2023-10-23     Shell        fix synchronization of data to icache
 */

#define DBG_TAG "dfs.pcache"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#include <dfs_pcache.h>
#include <dfs_dentry.h>
#include <dfs_mnt.h>

#include <rthw.h>

#ifdef RT_USING_PAGECACHE

#include <mm_page.h>
#include <mm_private.h>
#include <mmu.h>
#include <tlb.h>

#ifndef RT_PAGECACHE_COUNT
#define RT_PAGECACHE_COUNT          4096
#endif

#ifndef RT_PAGECACHE_ASPACE_COUNT
#define RT_PAGECACHE_ASPACE_COUNT   1024
#endif

#ifndef RT_PAGECACHE_PRELOAD
#define RT_PAGECACHE_PRELOAD        4
#endif

#ifndef RT_PAGECACHE_GC_WORK_LEVEL
#define RT_PAGECACHE_GC_WORK_LEVEL  90
#endif

#ifndef RT_PAGECACHE_GC_STOP_LEVEL
#define RT_PAGECACHE_GC_STOP_LEVEL  70
#endif

#define PCACHE_MQ_GC    1
#define PCACHE_MQ_WB    2

struct dfs_aspace_mmap_obj
{
    rt_uint32_t cmd;
    struct rt_mailbox *ack;
    struct dfs_file *file;
    struct rt_varea *varea;
    void *data;
};

struct dfs_pcache_mq_obj
{
    struct rt_mailbox *ack;
    rt_uint32_t cmd;
};

static struct dfs_page *dfs_page_lookup(struct dfs_file *file, off_t pos);
static void dfs_page_ref(struct dfs_page *page);
static int dfs_page_inactive(struct dfs_page *page);
static int dfs_page_remove(struct dfs_page *page);
static void dfs_page_release(struct dfs_page *page);
static int dfs_page_dirty(struct dfs_page *page);

static int dfs_aspace_release(struct dfs_aspace *aspace);

static int dfs_aspace_lock(struct dfs_aspace *aspace);
static int dfs_aspace_unlock(struct dfs_aspace *aspace);

static int dfs_pcache_lock(void);
static int dfs_pcache_unlock(void);


static struct dfs_pcache __pcache;

/**
 * @brief Perform garbage collection on an address space to release pages
 *
 * This function attempts to release a specified number of pages from both inactive
 * and active lists of the given address space. It prioritizes releasing pages from
 * the inactive list first before moving to the active list.
 *
 * @param[in] aspace Pointer to the address space structure to perform GC on
 * @param[in] count  Number of pages to attempt to release
 *
 * @return Number of pages actually released (count - remaining)
 */
static int dfs_aspace_gc(struct dfs_aspace *aspace, int count)
{
    int cnt = count;

    if (aspace)
    {
        dfs_aspace_lock(aspace);

        if (aspace->pages_count > 0)
        {
            struct dfs_page *page = RT_NULL;
            rt_list_t *node = aspace->list_inactive.next;

            while (cnt && node != &aspace->list_active)
            {
                page = rt_list_entry(node, struct dfs_page, space_node);
                node = node->next;
                if (dfs_page_remove(page) == 0)
                {
                    cnt --;
                }
            }

            node = aspace->list_active.next;
            while (cnt && node != &aspace->list_inactive)
            {
                page = rt_list_entry(node, struct dfs_page, space_node);
                node = node->next;
                if (dfs_page_remove(page) == 0)
                {
                    cnt --;
                }
            }
        }

        dfs_aspace_unlock(aspace);
    }

    return count - cnt;
}

/**
 * @brief Release page cache entries to free up memory
 *
 * This function attempts to release a specified number of page cache entries.
 * If count is 0, it calculates the number of pages to release based on the
 * current cache size and GC stop level. It first tries to release from inactive
 * list, then from active list if needed.
 *
 * @param[in] count Number of pages to release. If 0, calculates automatically
 *                  based on current cache size and GC stop level.
 *
 * @note The function uses LRU (Least Recently Used) policy by prioritizing
 *       inactive list over active list.
 */
void dfs_pcache_release(size_t count)
{
    rt_list_t *node = RT_NULL;
    struct dfs_aspace *aspace = RT_NULL;

    dfs_pcache_lock();

    if (count == 0)
    {
        count = rt_atomic_load(&(__pcache.pages_count)) - RT_PAGECACHE_COUNT * RT_PAGECACHE_GC_STOP_LEVEL / 100;
    }

    node = __pcache.list_inactive.next;
    while (count && node != &__pcache.list_active)
    {
        aspace = rt_list_entry(node, struct dfs_aspace, cache_node);
        node = node->next;
        if (aspace)
        {
            count -= dfs_aspace_gc(aspace, count);
            dfs_aspace_release(aspace);
        }
    }

    node = __pcache.list_active.next;
    while (count && node != &__pcache.list_inactive)
    {
        aspace = rt_list_entry(node, struct dfs_aspace, cache_node);
        node = node->next;
        if (aspace)
        {
            count -= dfs_aspace_gc(aspace, count);
        }
    }

    dfs_pcache_unlock();
}

/**
 * @brief Clean up page cache entries for a specific mount point
 *
 * This function iterates through both inactive and active lists of the page cache
 * to clean up entries associated with the given mount point. It performs cleanup
 * and calls the provided callback function for each matching address space.
 *
 * @param[in] mnt Pointer to the mount point structure to clean up
 * @param[in] cb  Callback function to be called for each matching address space
 *                The callback takes an address space pointer and returns an integer
 */
static void _pcache_clean(struct dfs_mnt *mnt, int (*cb)(struct dfs_aspace *aspace))
{
    rt_list_t *node = RT_NULL;
    struct dfs_aspace *aspace = RT_NULL;

    dfs_pcache_lock();

    node = __pcache.list_inactive.next;
    while (node != &__pcache.list_active)
    {
        aspace = rt_list_entry(node, struct dfs_aspace, cache_node);
        node = node->next;
        if (aspace && aspace->mnt == mnt)
        {
            dfs_aspace_clean(aspace);
            cb(aspace);
        }
    }

    node = __pcache.list_active.next;
    while (node != &__pcache.list_inactive)
    {
        aspace = rt_list_entry(node, struct dfs_aspace, cache_node);
        node = node->next;
        if (aspace && aspace->mnt == mnt)
        {
            dfs_aspace_clean(aspace);
            cb(aspace);
        }
    }

    dfs_pcache_unlock();
}

/**
 * @brief Unmount and clean up page cache for a specific mount point
 *
 * This function cleans up all page cache entries associated with the given mount point
 * by calling _pcache_clean() with dfs_aspace_release as the callback function.
 * It will release all address spaces and their pages belonging to this mount point.
 *
 * @param[in] mnt Pointer to the mount point structure to be unmounted
 *
 * @note This function is typically called during filesystem unmount operation
 * @see _pcache_clean()
 */
void dfs_pcache_unmount(struct dfs_mnt *mnt)
{
    _pcache_clean(mnt, dfs_aspace_release);
}

static int _dummy_cb(struct dfs_aspace *mnt)
{
    return 0;
}

/**
 * @brief Clean page cache for a specific mount point without releasing address spaces
 *
 * This function cleans up all page cache entries associated with the given mount point
 * but keeps the address spaces intact by using a dummy callback function.
 *
 * @param[in] mnt Pointer to the mount point structure to be cleaned
 *
 * @note Typical usage scenarios:
 * - Filesystem maintenance operations that require cache invalidation
 * - Force refreshing cached data without unmounting
 * - Handling external modifications to mounted filesystems
 *
 * @see _pcache_clean()
 */
void dfs_pcache_clean(struct dfs_mnt *mnt)
{
    _pcache_clean(mnt, _dummy_cb);
}

/**
 * @brief Check and enforce page cache memory limit
 *
 * This function checks if the current page cache usage exceeds the working level threshold.
 * If exceeded, it will trigger page cache release up to 4 times to reduce cache size.
 *
 * @return Always returns 0 indicating success
 */
static int dfs_pcache_limit_check(void)
{
    int index = 4;

    while (index && rt_atomic_load(&(__pcache.pages_count)) > RT_PAGECACHE_COUNT * RT_PAGECACHE_GC_WORK_LEVEL / 100)
    {
        dfs_pcache_release(0);
        index --;
    }

    return 0;
}

/**
 * @brief Page cache management thread
 *
 * This is the main worker thread for page cache management. It handles:
 * - Garbage collection (GC) requests to free up memory
 * - Write-back (WB) requests to flush dirty pages to storage
 *
 * @param[in] parameter Thread parameter (unused)
 *
 * @note The thread runs in an infinite loop processing messages from the cache message queue:
 * - For GC commands: calls dfs_pcache_limit_check() to free pages when cache is full
 * - For WB commands: flushes dirty pages that have been dirty for at least 500ms
 * - Processes up to 4 dirty pages per WB command to prevent thread starvation
 */
static void dfs_pcache_thread(void *parameter)
{
    struct dfs_pcache_mq_obj work;

    while (1)
    {
        if (rt_mq_recv(__pcache.mqueue, &work, sizeof(work), RT_WAITING_FOREVER) == sizeof(work))
        {
            if (work.cmd == PCACHE_MQ_GC)
            {
                dfs_pcache_limit_check();
            }
            else if (work.cmd == PCACHE_MQ_WB)
            {
                int count = 0;
                rt_list_t *node;
                struct dfs_page *page = 0;

                while (1)
                {
                    /* try to get dirty page */
                    dfs_pcache_lock();
                    page = 0;
                    rt_list_for_each(node, &__pcache.list_active)
                    {
                        if (node != &__pcache.list_inactive)
                        {
                            struct dfs_aspace *aspace = rt_list_entry(node, struct dfs_aspace, cache_node);
                            dfs_aspace_lock(aspace);
                            if (aspace->list_dirty.next != &aspace->list_dirty)
                            {
                                page = rt_list_entry(aspace->list_dirty.next, struct dfs_page, dirty_node);
                                dfs_page_ref(page);
                                dfs_aspace_unlock(aspace);
                                break;
                            }
                            else
                            {
                                page = RT_NULL;
                            }
                            dfs_aspace_unlock(aspace);
                        }
                    }
                    dfs_pcache_unlock();

                    if (page)
                    {
                        struct dfs_aspace *aspace = page->aspace;

                        dfs_aspace_lock(aspace);
                        if (page->is_dirty == 1 && aspace->vnode)
                        {
                            if (rt_tick_get_millisecond() - page->tick_ms >= 500)
                            {
                                if (aspace->vnode->size < page->fpos + page->size)
                                {
                                    page->len = aspace->vnode->size - page->fpos;
                                }
                                else
                                {
                                    page->len = page->size;
                                }
                                if (aspace->ops->write)
                                {
                                    aspace->ops->write(page);
                                }

                                page->is_dirty = 0;

                                if (page->dirty_node.next != RT_NULL)
                                {
                                    rt_list_remove(&page->dirty_node);
                                    page->dirty_node.next = RT_NULL;
                                }
                            }
                        }
                        dfs_page_release(page);
                        dfs_aspace_unlock(aspace);
                    }
                    else
                    {
                        break;
                    }

                    rt_thread_mdelay(5);

                    count ++;
                    if (count >= 4)
                    {
                        break;
                    }
                }
            }
        }
    }
}

/**
 * @brief Initialize the page cache system
 *
 * This function initializes the global page cache structure including:
 * - Hash table for address space lookup
 * - Active and inactive page lists
 * - Page count tracking
 * - Mutex for thread safety
 * - Message queue for cache operations
 * - Worker thread for background tasks
 *
 * @return 0 on success, negative error code on failure
 *
 * @note This function is automatically called during system initialization
 * via INIT_PREV_EXPORT macro. It sets up all necessary infrastructure
 * for page cache management.
 */
static int dfs_pcache_init(void)
{
    rt_thread_t tid;

    for (int i = 0; i < RT_PAGECACHE_HASH_NR; i++)
    {
        rt_list_init(&__pcache.head[i]);
    }

    rt_list_init(&__pcache.list_active);
    rt_list_init(&__pcache.list_inactive);
    rt_list_insert_after(&__pcache.list_active, &__pcache.list_inactive);

    rt_atomic_store(&(__pcache.pages_count), 0);

    rt_mutex_init(&__pcache.lock, "pcache", RT_IPC_FLAG_PRIO);

    __pcache.mqueue = rt_mq_create("pcache", sizeof(struct dfs_pcache_mq_obj), 1024, RT_IPC_FLAG_FIFO);
    tid = rt_thread_create("pcache", dfs_pcache_thread, 0, 8192, 25, 5);
    if (tid)
    {
        rt_thread_startup(tid);
    }

    __pcache.last_time_wb = rt_tick_get_millisecond();

    return 0;
}
INIT_PREV_EXPORT(dfs_pcache_init);

/**
 * @brief Send a command to page cache message queue
 *
 * This function sends a command to the page cache message queue for processing
 * by the cache management thread. It waits for the message to be sent.
 *
 * @param[in] cmd The command to send (PCACHE_MQ_GC or PCACHE_MQ_WB)
 *
 * @return RT_EOK on success, error code on failure
 *
 * @note This is used to trigger garbage collection or write-back operations
 * asynchronously through the cache management thread.
 */
static rt_ubase_t dfs_pcache_mq_work(rt_uint32_t cmd)
{
    rt_err_t err;
    struct dfs_pcache_mq_obj work = { 0 };

    work.cmd = cmd;

    err = rt_mq_send_wait(__pcache.mqueue, (const void *)&work, sizeof(struct dfs_pcache_mq_obj), 0);

    return err;
}

/**
 * @brief Lock the page cache global mutex
 *
 * @return Always returns 0.
 */
static int dfs_pcache_lock(void)
{
    rt_mutex_take(&__pcache.lock, RT_WAITING_FOREVER);
    return 0;
}

/**
 * @brief Unlock the page cache global mutex
 *
 * @return Always returns 0.
 */
static int dfs_pcache_unlock(void)
{
    rt_mutex_release(&__pcache.lock);
    return 0;
}

/**
 * @brief Calculate hash value for address space lookup
 *
 * This function computes a hash value based on mount point and path string.
 * It uses a simple string hashing algorithm combined with mount point pointer.
 *
 * @param[in] mnt  Pointer to the mount point structure
 * @param[in] path Path string to be hashed (can be NULL)
 *
 * @return Computed hash value within range [0, RT_PAGECACHE_HASH_NR-1]
 *
 * @note The hash algorithm combines:
 * - DJB2 hash algorithm for the path string
 * - XOR with mount point pointer
 * - Modulo operation to fit hash table size
 */
static uint32_t dfs_aspace_hash(struct dfs_mnt *mnt, const char *path)
{
    uint32_t val = 0;

    if (path)
    {
        while (*path)
        {
            val = ((val << 5) + val) + *path++;
        }
    }

    return (val ^ (unsigned long)mnt) & (RT_PAGECACHE_HASH_NR - 1);
}

/**
 * @brief Look up an address space in the page cache hash table
 *
 * This function searches for an address space matching the given dentry and operations
 * in the page cache hash table. If found, it increments the reference count of the
 * address space before returning it.
 *
 * @param[in] dentry Directory entry containing mount point and path information
 * @param[in] ops    Pointer to address space operations structure
 *
 * @return Pointer to the found address space on success, NULL if not found
 */
static struct dfs_aspace *dfs_aspace_hash_lookup(struct dfs_dentry *dentry, const struct dfs_aspace_ops *ops)
{
    struct dfs_aspace *aspace = RT_NULL;

    dfs_pcache_lock();
    rt_list_for_each_entry(aspace, &__pcache.head[dfs_aspace_hash(dentry->mnt, dentry->pathname)], hash_node)
    {

        if (aspace->mnt == dentry->mnt
            && aspace->ops == ops
            && !strcmp(aspace->pathname, dentry->pathname))
        {
            rt_atomic_add(&aspace->ref_count, 1);
            dfs_pcache_unlock();
            return aspace;
        }
    }
    dfs_pcache_unlock();

    return RT_NULL;
}

/**
 * @brief Insert an address space into page cache
 *
 * This function inserts the given address space into both the hash table and
 * inactive list of the page cache. It also increments the reference count of
 * the address space.
 *
 * @param[in,out] aspace Pointer to the address space to be inserted
 */
static void dfs_aspace_insert(struct dfs_aspace *aspace)
{
    uint32_t val = 0;

    val = dfs_aspace_hash(aspace->mnt, aspace->pathname);

    dfs_pcache_lock();
    rt_atomic_add(&aspace->ref_count, 1);
    rt_list_insert_after(&__pcache.head[val], &aspace->hash_node);
    rt_list_insert_before(&__pcache.list_inactive, &aspace->cache_node);
    dfs_pcache_unlock();
}

/**
 * @brief Remove an address space from page cache
 *
 * This function removes the given address space from both the hash table and
 * active/inactive lists of the page cache.
 *
 * @param[in,out] aspace Pointer to the address space to be removed
 */
static void dfs_aspace_remove(struct dfs_aspace *aspace)
{
    dfs_pcache_lock();
    if (aspace->hash_node.next != RT_NULL)
    {
        rt_list_remove(&aspace->hash_node);
    }
    if (aspace->cache_node.next != RT_NULL)
    {
        rt_list_remove(&aspace->cache_node);
    }
    dfs_pcache_unlock();
}

/**
 * @brief Move an address space to active list
 *
 * This function moves the specified address space from its current position
 * to the active list in the page cache. The active list contains frequently
 * accessed address spaces.
 *
 * @param[in,out] aspace Pointer to the address space to be activated
 *
 * @note Insert the address space before inactive list's head, means putting it
 *       to the end of the active list.
 *
 * @see dfs_aspace_inactive() for the opposite operation
 */
static void dfs_aspace_active(struct dfs_aspace *aspace)
{
    dfs_pcache_lock();
    if (aspace->cache_node.next != RT_NULL)
    {
        rt_list_remove(&aspace->cache_node);
        rt_list_insert_before(&__pcache.list_inactive, &aspace->cache_node);
    }
    dfs_pcache_unlock();
}

/**
 * @brief Move an address space to inactive list
 *
 * This function moves the specified address space from its current position
 * to the inactive list in the page cache. The inactive list contains less
 * frequently accessed address spaces that are candidates for eviction.
 *
 * @param[in,out] aspace Pointer to the address space to be deactivated
 */
static void dfs_aspace_inactive(struct dfs_aspace *aspace)
{
    dfs_pcache_lock();
    if (aspace->cache_node.next != RT_NULL)
    {
        rt_list_remove(&aspace->cache_node);
        rt_list_insert_before(&__pcache.list_active, &aspace->cache_node);
    }
    dfs_pcache_unlock();
}

/**
 * @brief Internal function to create a new address space for page cache
 *
 * This function allocates and initializes a new address space structure for page caching.
 * It sets up all necessary lists, locks, and initial values for the address space.
 *
 * @param[in] dentry Directory entry containing mount point and path information (can be NULL)
 * @param[in] vnode  Pointer to the vnode structure this address space will be associated with
 * @param[in] ops    Pointer to address space operations structure
 *
 * @return Pointer to the newly created address space on success, NULL on failure
 *
 * @note The created address space will be automatically inserted into the page cache
 * @see dfs_aspace_create() for the public interface to create address spaces
 */
static struct dfs_aspace *_dfs_aspace_create(struct dfs_dentry *dentry,
                                             struct dfs_vnode *vnode,
                                             const struct dfs_aspace_ops *ops)
{
    struct dfs_aspace *aspace;

    aspace = rt_calloc(1, sizeof(struct dfs_aspace));
    if (aspace)
    {
        rt_list_init(&aspace->list_active);
        rt_list_init(&aspace->list_inactive);
        rt_list_init(&aspace->list_dirty);
        rt_list_insert_after(&aspace->list_active, &aspace->list_inactive);

        aspace->avl_root.root_node = 0;
        aspace->avl_page = 0;

        rt_mutex_init(&aspace->lock, rt_thread_self()->parent.name, RT_IPC_FLAG_PRIO);
        rt_atomic_store(&aspace->ref_count, 1);

        aspace->pages_count = 0;
        aspace->vnode = vnode;
        aspace->ops = ops;

        if (dentry && dentry->mnt)
        {
            aspace->mnt = dentry->mnt;
            aspace->fullpath = rt_strdup(dentry->mnt->fullpath);
            aspace->pathname = rt_strdup(dentry->pathname);
        }

        dfs_aspace_insert(aspace);
    }

    return aspace;
}

/**
 * @brief Create or lookup an address space for page caching
 *
 * This function either creates a new address space or looks up an existing one
 * in the page cache hash table. If found, it updates the vnode reference and
 * activates the address space.
 *
 * @param[in] dentry Directory entry containing mount point and path info (can be NULL)
 * @param[in] vnode  Pointer to the vnode structure to associate with
 * @param[in] ops    Pointer to address space operations structure
 *
 * @return Pointer to the found/created address space on success, NULL on failure
 */
struct dfs_aspace *dfs_aspace_create(struct dfs_dentry *dentry,
                                     struct dfs_vnode *vnode,
                                     const struct dfs_aspace_ops *ops)
{
    struct dfs_aspace *aspace = RT_NULL;

    RT_ASSERT(vnode && ops);
    dfs_pcache_lock();
    if (dentry)
    {
        aspace = dfs_aspace_hash_lookup(dentry, ops);
    }

    if (!aspace)
    {
        aspace = _dfs_aspace_create(dentry, vnode, ops);
    }
    else
    {
        aspace->vnode = vnode;
        dfs_aspace_active(aspace);
    }
    dfs_pcache_unlock();
    return aspace;
}

/**
 * @brief Destroy an address space and release its resources
 *
 * This function decrements the reference count of the address space and marks it as inactive.
 * If the reference count reaches 1 and there are no pages left, it will be fully released.
 *
 * @param[in] aspace Pointer to the address space to be destroyed
 *
 * @return 0 on successful release, -EINVAL if aspace is NULL
 */
int dfs_aspace_destroy(struct dfs_aspace *aspace)
{
    int ret = -EINVAL;

    if (aspace)
    {
        dfs_pcache_lock();
        dfs_aspace_lock(aspace);
        rt_atomic_sub(&aspace->ref_count, 1);
        RT_ASSERT(rt_atomic_load(&aspace->ref_count) > 0);
        dfs_aspace_inactive(aspace);
        aspace->vnode = RT_NULL;
        if (dfs_aspace_release(aspace) != 0)
        {
            dfs_aspace_unlock(aspace);
        }
        dfs_pcache_unlock();
    }

    return ret;
}

/**
 * @brief Release an address space when its reference count reaches 1
 *
 * This function checks if the address space can be safely released by verifying:
 * - Reference count is 1 (only caller holds reference)
 * - No pages remain in the address space
 * If conditions are met, it removes the space from cache and frees all resources.
 *
 * @param[in] aspace Pointer to the address space to be released
 *
 * @return 0 on successful release, -1 if space cannot be released yet
 */
static int dfs_aspace_release(struct dfs_aspace *aspace)
{
    int ret = -1;

    if (aspace)
    {
        dfs_pcache_lock();
        dfs_aspace_lock(aspace);

        if (rt_atomic_load(&aspace->ref_count) == 1 && aspace->pages_count == 0)
        {
            dfs_aspace_remove(aspace);
            if (aspace->fullpath)
            {
                rt_free(aspace->fullpath);
            }
            if (aspace->pathname)
            {
                rt_free(aspace->pathname);
            }
            rt_mutex_detach(&aspace->lock);
            rt_free(aspace);
            ret = 0;
        }
        else
        {
            dfs_aspace_unlock(aspace);
        }
        dfs_pcache_unlock();
    }

    return ret;
}

/**
 * @brief Dump address space page information for debugging
 *
 * This function prints detailed information about pages in the given address space.
 * It can optionally filter to show only dirty pages or all pages.
 *
 * @param[in] aspace    Pointer to the address space to dump
 * @param[in] is_dirty  Flag indicating whether to show only dirty pages (1) or all pages (0)
 *
 * @return Always returns 0
 */
static int _dfs_aspace_dump(struct dfs_aspace *aspace, int is_dirty)
{
    if (aspace)
    {
        rt_list_t *next;
        struct dfs_page *page;

        dfs_aspace_lock(aspace);
        if (aspace->pages_count > 0)
        {
            rt_list_for_each(next, &aspace->list_inactive)
            {
                if (next != &aspace->list_active)
                {
                    page = rt_list_entry(next, struct dfs_page, space_node);
                    if (is_dirty && page->is_dirty)
                    {
                        rt_kprintf("    pages >> fpos: %d index :%d is_dirty: %d\n", page->fpos, page->fpos / ARCH_PAGE_SIZE, page->is_dirty);
                    }
                    else if (is_dirty == 0)
                    {
                        rt_kprintf("    pages >> fpos: %d index :%d is_dirty: %d\n", page->fpos, page->fpos / ARCH_PAGE_SIZE, page->is_dirty);
                    }
                }
            }
        }
        else
        {
            rt_kprintf("    pages >> empty\n");
        }
        dfs_aspace_unlock(aspace);
    }
    return 0;
}

/**
 * @brief Dump page cache information for debugging purposes
 *
 * This function prints detailed information about the page cache, including:
 * - Total page count and capacity
 * - File paths and page counts for each address space
 * - Optional detailed page information (with --dump or --dirty flags)
 *
 * @param[in] argc Number of command line arguments
 * @param[in] argv Command line arguments array
 *
 * @return Always returns 0
 *
 * @see _dfs_aspace_dump() for the actual page dumping implementation
 */
static int dfs_pcache_dump(int argc, char **argv)
{
    int dump = 0;
    rt_list_t *node;
    struct dfs_aspace *aspace;

    if (argc == 2)
    {
        if (strcmp(argv[1], "--dump") == 0)
        {
            dump = 1;
        }
        else if (strcmp(argv[1], "--dirty") == 0)
        {
            dump = 2;
        }
        else
        {
            rt_kprintf("dfs page cache dump\n");
            rt_kprintf("usage: dfs_cache\n");
            rt_kprintf("       dfs_cache --dump\n");
            rt_kprintf("       dfs_cache --dirty\n");
            return 0;
        }
    }

    dfs_pcache_lock();

    rt_kprintf("total pages count: %d / %d\n", rt_atomic_load(&(__pcache.pages_count)), RT_PAGECACHE_COUNT);

    rt_list_for_each(node, &__pcache.list_active)
    {
        if (node != &__pcache.list_inactive)
        {
            aspace = rt_list_entry(node, struct dfs_aspace, cache_node);

            if (aspace->mnt)
            {
                rt_kprintf("file: %s%s pages: %d\n", aspace->fullpath, aspace->pathname, aspace->pages_count);
            }
            else
            {
                rt_kprintf("unknown type, pages: %d\n", aspace->pages_count);
            }

            if (dump > 0)
            {
                _dfs_aspace_dump(aspace, dump == 2 ? 1 : 0);
            }
        }
    }

    dfs_pcache_unlock();

    return 0;
}
MSH_CMD_EXPORT_ALIAS(dfs_pcache_dump, dfs_cache, dump dfs page cache);

/**
 * @brief Unmap all memory mappings for a page
 *
 * This function unmaps all virtual memory areas that have mapped this physical page.
 * It also marks the page as dirty if it contains valid data that hasn't been written back.
 *
 * @param[in,out] page Pointer to the page structure to unmap
 *
 * @return Always returns 0
 */
static int dfs_page_unmap(struct dfs_page *page)
{
    rt_list_t *next;
    struct dfs_mmap *map;

    next = page->mmap_head.next;

    if (next != &page->mmap_head && page->fpos < page->aspace->vnode->size)
    {
        dfs_page_dirty(page);
    }

    while (next != &page->mmap_head)
    {
        map = rt_list_entry(next, struct dfs_mmap, mmap_node);
        next = next->next;

        if (map)
        {
            rt_varea_t varea;
            void *vaddr;

            varea = rt_aspace_query(map->aspace, map->vaddr);
            RT_ASSERT(varea);
            vaddr = dfs_aspace_vaddr(varea, page->fpos);

            rt_varea_unmap_page(varea, vaddr);

            rt_free(map);
        }
    }

    rt_list_init(&page->mmap_head);

    return 0;
}

/**
 * @brief Create a new page structure for page cache
 *
 * This function allocates and initializes a new page structure for the page cache.
 * It allocates physical memory for the page and initializes its metadata including:
 * - Memory mapping list head
 * - Reference count
 * - Physical page allocation with affinity hint
 *
 * @param[in] pos File position used to determine page allocation affinity
 *
 * @return Pointer to the newly created page structure on success, NULL on failure
 */
static struct dfs_page *dfs_page_create(off_t pos)
{
    struct dfs_page *page = RT_NULL;
    int affid = RT_PAGE_PICK_AFFID(pos);

    page = rt_calloc(1, sizeof(struct dfs_page));
    if (page)
    {
        page->page = rt_pages_alloc_tagged(0, affid, PAGE_ANY_AVAILABLE);
        if (page->page)
        {
            /* memset(page->page, 0x00, ARCH_PAGE_SIZE); */
            rt_list_init(&page->mmap_head);
            rt_atomic_store(&(page->ref_count), 1);
        }
        else
        {
            LOG_E("page alloc failed!\n");
            rt_free(page);
            page = RT_NULL;
        }
    }

    return page;
}

/**
 * @brief Increment the reference count of a page
 *
 * This function atomically increases the reference count of the specified page.
 * It is used to track how many times the page is being referenced/used.
 *
 * @param[in,out] page Pointer to the page structure whose reference count will be incremented
 */
static void dfs_page_ref(struct dfs_page *page)
{
    rt_atomic_add(&(page->ref_count), 1);
}

/**
 * @brief Release a page from page cache when reference count reaches zero
 *
 * This function decrements the reference count of a page and performs cleanup
 * when the count reaches zero. It handles:
 * - Unmapping all virtual mappings of the page
 * - Writing back dirty pages to storage
 * - Freeing physical memory and page structure
 *
 * @param[in,out] page Pointer to the page structure to be released
 */
static void dfs_page_release(struct dfs_page *page)
{
    struct dfs_aspace *aspace = page->aspace;

    dfs_aspace_lock(aspace);

    rt_atomic_sub(&(page->ref_count), 1);

    if (rt_atomic_load(&(page->ref_count)) == 0)
    {
        dfs_page_unmap(page);

        if (page->is_dirty == 1 && aspace->vnode)
        {
            if (aspace->vnode->size < page->fpos + page->size)
            {
                page->len = aspace->vnode->size - page->fpos;
            }
            else
            {
                page->len = page->size;
            }
            if (aspace->ops->write)
            {
                aspace->ops->write(page);
            }
            page->is_dirty = 0;
        }
        RT_ASSERT(page->is_dirty == 0);

        rt_pages_free(page->page, 0);
        page->page = RT_NULL;
        rt_free(page);
    }

    dfs_aspace_unlock(aspace);
}

/**
 * @brief Compare file positions for page alignment
 *
 * This function compares two file positions to determine if they belong to the same page.
 * It aligns both positions to page boundaries before comparison.
 *
 * @param[in] fpos   File position to compare (byte offset)
 * @param[in] value  Reference file position to compare against (byte offset)
 *
 * @return 0 if positions are in the same page, negative if fpos is before value,
 *         positive if fpos is after value
 */
static int dfs_page_compare(off_t fpos, off_t value)
{
    return fpos / ARCH_PAGE_SIZE * ARCH_PAGE_SIZE - value;
}

/**
 * @brief Insert a page into the AVL tree of an address space
 *
 * This function inserts a page into the AVL tree of the specified address space.
 * The tree is ordered by the file position (fpos) of pages. If a page with the
 * same fpos already exists, the insertion fails.
 *
 * @param[in] aspace Pointer to the address space containing the AVL tree
 * @param[in,out] page Pointer to the page structure to be inserted
 *
 * @return 0 on successful insertion, -1 if a page with same fpos already exists
 *
 * @note The function:
 * - Maintains AVL tree balance after insertion
 * - Updates the aspace's avl_page pointer to the newly inserted page
 * - Uses file position (fpos) as the ordering key
 */
static int _dfs_page_insert(struct dfs_aspace *aspace, struct dfs_page *page)
{
    struct dfs_page *tmp;
    struct util_avl_struct *current = NULL;
    struct util_avl_struct **next = &(aspace->avl_root.root_node);

    /* Figure out where to put new node */
    while (*next)
    {
        current = *next;
        tmp = rt_container_of(current, struct dfs_page, avl_node);

        if (page->fpos < tmp->fpos)
            next = &(current->avl_left);
        else if (page->fpos > tmp->fpos)
            next = &(current->avl_right);
        else
            return -1;
    }

    /* Add new node and rebalance tree. */
    util_avl_link(&page->avl_node, current, next);
    util_avl_rebalance(current, &aspace->avl_root);
    aspace->avl_page = page;

    return 0;
}

/**
 * @brief Remove a page from the AVL tree of an address space
 *
 * This function removes a page from the AVL tree of the specified address space.
 * It also clears the cached AVL page pointer if it points to the page being removed.
 *
 * @param[in,out] aspace Pointer to the address space containing the AVL tree
 * @param[in,out] page   Pointer to the page structure to be removed
 */
static void _dfs_page_remove(struct dfs_aspace *aspace, struct dfs_page *page)
{
    if (aspace->avl_page && aspace->avl_page == page)
    {
        aspace->avl_page = 0;
    }

    util_avl_remove(&page->avl_node, &aspace->avl_root);
}

/**
 * @brief Lock an address space for thread-safe operations
 *
 * @param[in,out] aspace Pointer to the address space structure to be locked
 *
 * @return Always returns 0 indicating success
 *
 * @note The lock must be released using dfs_aspace_unlock()
 * @see dfs_aspace_unlock()
 */
static int dfs_aspace_lock(struct dfs_aspace *aspace)
{
    rt_mutex_take(&aspace->lock, RT_WAITING_FOREVER);
    return 0;
}

/**
 * @brief Unlock an address space after thread-safe operations
 *
 * @param[in,out] aspace Pointer to the address space structure to be unlocked
 *
 * @return Always returns 0 indicating success
 *
 * @note Must be called after dfs_aspace_lock() to release the lock
 * @see dfs_aspace_lock()
 */
static int dfs_aspace_unlock(struct dfs_aspace *aspace)
{
    rt_mutex_release(&aspace->lock);
    return 0;
}

/**
 * @brief Insert a page into the address space's page cache
 *
 * This function inserts a page into the active list of the address space's page cache.
 * It maintains the page count and performs eviction if the cache exceeds its capacity.
 *
 * @param[in] page Pointer to the page structure to be inserted
 *
 * @return Always returns 0 indicating success
 */
static int dfs_page_insert(struct dfs_page *page)
{
    struct dfs_aspace *aspace = page->aspace;

    dfs_aspace_lock(aspace);

    rt_list_insert_before(&aspace->list_inactive, &page->space_node);
    aspace->pages_count ++;

    if (_dfs_page_insert(aspace, page))
    {
        RT_ASSERT(0);
    }

    if (aspace->pages_count > RT_PAGECACHE_ASPACE_COUNT)
    {
        rt_list_t *next = aspace->list_active.next;

        if (next != &aspace->list_inactive)
        {
            struct dfs_page *tmp = rt_list_entry(next, struct dfs_page, space_node);
            dfs_page_inactive(tmp);
        }
    }

    rt_atomic_add(&(__pcache.pages_count), 1);

    dfs_aspace_unlock(aspace);

    return 0;
}

/**
 * @brief Remove a page from the address space's page cache
 *
 * This function safely removes a page from both the space and dirty lists of the address space.
 * It decrements the reference count and releases the page if it's the last reference.
 *
 * @param[in] page Pointer to the page structure to be removed
 *
 * @return 0 if the page was successfully removed, -1 if the page is still referenced
 */
static int dfs_page_remove(struct dfs_page *page)
{
    int ret = -1;
    struct dfs_aspace *aspace = page->aspace;

    dfs_aspace_lock(aspace);

    if (rt_atomic_load(&(page->ref_count)) == 1)
    {
        if (page->space_node.next != RT_NULL)
        {
            rt_list_remove(&page->space_node);
            page->space_node.next = RT_NULL;
            aspace->pages_count--;
            _dfs_page_remove(aspace, page);
        }
        if (page->dirty_node.next != RT_NULL)
        {
            rt_list_remove(&page->dirty_node);
            page->dirty_node.next = RT_NULL;
        }

        rt_atomic_sub(&(__pcache.pages_count), 1);

        dfs_page_release(page);
        ret = 0;
    }

    dfs_aspace_unlock(aspace);

    return ret;
}

/**
 * @brief Move a page to active list
 *
 * This function moves a page to the active list
 * within its associated address space.
 *
 * @param[in] page The page to be moved to active list
 * @return int Always returns 0 on success
 */
static int dfs_page_active(struct dfs_page *page)
{
    struct dfs_aspace *aspace = page->aspace;

    dfs_aspace_lock(aspace);
    if (page->space_node.next != RT_NULL)
    {
        rt_list_remove(&page->space_node);
        rt_list_insert_before(&aspace->list_inactive, &page->space_node);
    }
    dfs_aspace_unlock(aspace);

    return 0;
}

/**
 * @brief Move a page to inactive list
 *
 * This function moves a page to the inactive list
 * within its associated address space.
 *
 * @param[in] page The page to be moved to inactive list
 * @return int Always returns 0 on success
 */
static int dfs_page_inactive(struct dfs_page *page)
{
    struct dfs_aspace *aspace = page->aspace;

    dfs_aspace_lock(aspace);
    if (page->space_node.next != RT_NULL)
    {
        rt_list_remove(&page->space_node);
        rt_list_insert_before(&aspace->list_active, &page->space_node);
    }
    dfs_aspace_unlock(aspace);

    return 0;
}

/**
 * @brief Mark a page as dirty and manage dirty list
 *
 * This function marks a page as dirty and adds it to the dirty list if not already present.
 * It also triggers a write-back operation if more than 1 second has passed since last write-back.
 *
 * @param[in] page The page to be marked as dirty
 * @return int Always returns 0 on success
 */
static int dfs_page_dirty(struct dfs_page *page)
{
    struct dfs_aspace *aspace = page->aspace;

    dfs_aspace_lock(aspace);

    if (page->dirty_node.next == RT_NULL && page->space_node.next != RT_NULL)
    {
        rt_list_insert_before(&aspace->list_dirty, &page->dirty_node);
    }

    page->is_dirty = 1;
    page->tick_ms = rt_tick_get_millisecond();

    if (rt_tick_get_millisecond() - __pcache.last_time_wb >= 1000)
    {
        dfs_pcache_mq_work(PCACHE_MQ_WB);
        __pcache.last_time_wb = rt_tick_get_millisecond();
    }

    dfs_aspace_unlock(aspace);

    return 0;
}

/**
 * @brief Search for a page in the address space AVL tree
 *
 * This function searches for a page at the specified file position in the address space's AVL tree.
 * If found, it marks the page as active and increments its reference count.
 *
 * @param[in] aspace The address space to search in
 * @param[in] fpos The file position to search for
 * @return struct dfs_page* The found page, or RT_NULL if not found
 */
static struct dfs_page *dfs_page_search(struct dfs_aspace *aspace, off_t fpos)
{
    int cmp;
    struct dfs_page *page;
    struct util_avl_struct *avl_node;

    dfs_aspace_lock(aspace);

    if (aspace->avl_page && dfs_page_compare(fpos, aspace->avl_page->fpos) == 0)
    {
        page = aspace->avl_page;
        dfs_page_active(page);
        dfs_page_ref(page);
        dfs_aspace_unlock(aspace);
        return page;
    }

    avl_node = aspace->avl_root.root_node;
    while (avl_node)
    {
        page = rt_container_of(avl_node, struct dfs_page, avl_node);
        cmp = dfs_page_compare(fpos, page->fpos);

        if (cmp < 0)
        {
            avl_node = avl_node->avl_left;
        }
        else if (cmp > 0)
        {
            avl_node = avl_node->avl_right;
        }
        else
        {
            aspace->avl_page = page;
            dfs_page_active(page);
            dfs_page_ref(page);
            dfs_aspace_unlock(aspace);
            return page;
        }
    }

    dfs_aspace_unlock(aspace);

    return RT_NULL;
}

/**
 * @brief Load a page from file into address space cache
 *
 * This function creates a new page cache entry for the specified file position,
 * reads the content from the file into the page, and inserts it into the cache.
 * The page's reference count is incremented to prevent c eviction.
 *
 * @param[in] file Pointer to the file structure containing the vnode and aspace
 * @param[in] pos  File position to load (will be page-aligned)
 *
 * @return Pointer to the newly created and loaded page on success,
 *         NULL on failure or invalid parameters
 */
static struct dfs_page *dfs_aspace_load_page(struct dfs_file *file, off_t pos)
{
    struct dfs_page *page = RT_NULL;

    if (file && file->vnode && file->vnode->aspace)
    {
        struct dfs_vnode *vnode = file->vnode;
        struct dfs_aspace *aspace = vnode->aspace;

        page = dfs_page_create(pos);
        if (page)
        {
            page->aspace = aspace;
            page->size = ARCH_PAGE_SIZE;
            page->fpos = RT_ALIGN_DOWN(pos, ARCH_PAGE_SIZE);
            aspace->ops->read(file, page);
            page->ref_count ++;

            dfs_page_insert(page);
        }
    }

    return page;
}

/**
 * @brief Look up a page in the cache and load it if not found
 *
 * This function searches for a page at the specified position in the file's address space.
 * If the page isn't found, it preloads multiple pages (RT_PAGECACHE_PRELOAD count) next to the requested position.
 * It also triggers garbage collection when the cache reaches certain thresholds.
 *
 * @param[in] file Pointer to the file structure containing the vnode and aspace
 * @param[in] pos  File position to look up (will be page-aligned)
 *
 * @return Pointer to the found or newly loaded page on success,
 *         NULL if the page couldn't be found or loaded
 */
static struct dfs_page *dfs_page_lookup(struct dfs_file *file, off_t pos)
{
    struct dfs_page *page = RT_NULL;
    struct dfs_aspace *aspace = file->vnode->aspace;

    dfs_aspace_lock(aspace);
    page = dfs_page_search(aspace, pos);
    if (!page)
    {
        int count = RT_PAGECACHE_PRELOAD;
        struct dfs_page *tmp = RT_NULL;
        off_t fpos = pos / ARCH_PAGE_SIZE * ARCH_PAGE_SIZE;

        do
        {
            page = dfs_aspace_load_page(file, fpos);
            if (page)
            {
                if (tmp == RT_NULL)
                {
                    tmp = page;
                }
                else
                {
                    dfs_page_release(page);
                }
            }
            else
            {
                break;
            }

            fpos += ARCH_PAGE_SIZE;
            page = dfs_page_search(aspace, fpos);
            if (page)
            {
                dfs_page_release(page);
            }
            count --;

        } while (count && page == RT_NULL);

        page = tmp;
        if (page)
        {
            dfs_aspace_unlock(aspace);

            if (rt_atomic_load(&(__pcache.pages_count)) >= RT_PAGECACHE_COUNT)
            {
                dfs_pcache_limit_check();
            }
            else if (rt_atomic_load(&(__pcache.pages_count)) >= RT_PAGECACHE_COUNT * RT_PAGECACHE_GC_WORK_LEVEL / 100)
            {
                dfs_pcache_mq_work(PCACHE_MQ_GC);
            }

            return page;
        }
    }
    dfs_aspace_unlock(aspace);

    return page;
}

/**
 * @brief Read data from file through address space page cache
 *
 * This function reads data from a file using its address space page cache. It handles
 * the lookup of pages containing the requested data, copies the data to the provided
 * buffer, and manages page references.
 *
 * @param[in] file  Pointer to the file structure containing vnode and aspace
 * @param[in] buf   Buffer to store the read data
 * @param[in] count Number of bytes to read
 * @param[in,out] pos Pointer to the file position (updated during reading)
 *
 * @return Number of bytes successfully read, or negative error code
 */
int dfs_aspace_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    int ret = -EINVAL;

    if (file && file->vnode && file->vnode->aspace)
    {
        if (!(file->vnode->aspace->ops->read))
            return ret;
        struct dfs_vnode *vnode = file->vnode;
        struct dfs_aspace *aspace = vnode->aspace;

        struct dfs_page *page;
        char *ptr = (char *)buf;

        ret = 0;

        while (count)
        {
            page = dfs_page_lookup(file, *pos);
            if (page)
            {
                off_t len;

                dfs_aspace_lock(aspace);
                if (aspace->vnode->size < page->fpos + ARCH_PAGE_SIZE)
                {
                    len = aspace->vnode->size - *pos;
                }
                else
                {
                    len = page->fpos + ARCH_PAGE_SIZE - *pos;
                }

                len = count > len ? len : count;
                if (len > 0)
                {
                    rt_memcpy(ptr, page->page + *pos - page->fpos, len);
                    ptr += len;
                    *pos += len;
                    count -= len;
                    ret += len;
                }
                else
                {
                    dfs_page_release(page);
                    dfs_aspace_unlock(aspace);
                    break;
                }
                dfs_page_release(page);
                dfs_aspace_unlock(aspace);
            }
            else
            {
                break;
            }
        }
    }

    return ret;
}

/**
 * @brief Write data to file through address space page cache
 *
 * This function writes data to a file using its address space page cache. It handles
 * page lookup, data copying, dirty page marking, and synchronization operations.
 *
 * @param[in] file  Pointer to the file structure containing vnode and aspace
 * @param[in] buf   Buffer containing data to write
 * @param[in] count Number of bytes to write
 * @param[in,out] pos Pointer to the file position (updated during writing)
 *
 * @return Number of bytes successfully written, or negative error code
 */
int dfs_aspace_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
{
    int ret = -EINVAL;

    if (file && file->vnode && file->vnode->aspace)
    {
        struct dfs_vnode *vnode = file->vnode;
        struct dfs_aspace *aspace = vnode->aspace;

        struct dfs_page *page;
        char *ptr = (char *)buf;

        if (!(aspace->ops->write))
        {
            return ret;
        }
        else if (aspace->mnt && (aspace->mnt->flags & MNT_RDONLY))
        {
            return -EROFS;
        }

        ret = 0;

        while (count)
        {
            page = dfs_page_lookup(file, *pos);
            if (page)
            {
                off_t len;

                dfs_aspace_lock(aspace);
                len = page->fpos + ARCH_PAGE_SIZE - *pos;
                len = count > len ? len : count;
                rt_memcpy(page->page + *pos - page->fpos, ptr, len);
                ptr += len;
                *pos += len;
                count -= len;
                ret += len;

                if (*pos > aspace->vnode->size)
                {
                    aspace->vnode->size = *pos;
                }

                if (file->flags & O_SYNC)
                {
                    if (aspace->vnode->size < page->fpos + page->size)
                    {
                        page->len = aspace->vnode->size - page->fpos;
                    }
                    else
                    {
                        page->len = page->size;
                    }

                    aspace->ops->write(page);
                    page->is_dirty = 0;
                }
                else
                {
                    dfs_page_dirty(page);
                }

                dfs_page_release(page);
                dfs_aspace_unlock(aspace);
            }
            else
            {
                break;
            }
        }
    }

    return ret;
}

/**
 * @brief Flush dirty pages in an address space to storage
 *
 * This function writes all dirty pages in the specified address space to storage,
 * ensuring data persistence. It handles page size adjustments and clears dirty flags
 * after successful writes.
 *
 * @param[in] aspace Pointer to the address space containing dirty pages
 *
 * @return Always returns 0 (success)
 */
int dfs_aspace_flush(struct dfs_aspace *aspace)
{
    if (aspace)
    {
        rt_list_t *next;
        struct dfs_page *page;

        dfs_aspace_lock(aspace);

        if (aspace->pages_count > 0 && aspace->vnode)
        {
            rt_list_for_each(next, &aspace->list_dirty)
            {
                page = rt_list_entry(next, struct dfs_page, dirty_node);
                if (page->is_dirty == 1 && aspace->vnode)
                {
                    if (aspace->vnode->size < page->fpos + page->size)
                    {
                        page->len = aspace->vnode->size - page->fpos;
                    }
                    else
                    {
                        page->len = page->size;
                    }

                    if (aspace->ops->write)
                    {
                        aspace->ops->write(page);
                    }

                    page->is_dirty = 0;
                }
                RT_ASSERT(page->is_dirty == 0);
            }
        }

        dfs_aspace_unlock(aspace);
    }
    return 0;
}

/**
 * @brief Clean all pages from an address space
 *
 * This function removes all active pages from the specified address space while
 * maintaining thread safety through proper locking. It skips inactive pages
 * during the cleanup process.
 *
 * @param[in] aspace Pointer to the address space structure to clean
 *
 * @return 0 on success, negative value on error
 */
int dfs_aspace_clean(struct dfs_aspace *aspace)
{
    if (aspace)
    {
        dfs_aspace_lock(aspace);

        if (aspace->pages_count > 0)
        {
            rt_list_t *next = aspace->list_active.next;
            struct dfs_page *page;

            while (next && next != &aspace->list_active)
            {
                if (next == &aspace->list_inactive)
                {
                    next = next->next;
                    continue;
                }
                page = rt_list_entry(next, struct dfs_page, space_node);
                next = next->next;
                dfs_page_remove(page);
            }
        }

        dfs_aspace_unlock(aspace);
    }

    return 0;
}

/**
 * @brief Map a file page into virtual address space
 *
 * This function maps a file page into the specified virtual address space, handling
 * memory allocation, page lookup, and cache synchronization. It ensures proper
 * memory visibility across different CPU architectures with cache operations.
 *
 * @param[in] file    Pointer to the file structure
 * @param[in] varea   Pointer to the virtual address area structure
 * @param[in] vaddr   Virtual address to map the page to
 *
 * @return Pointer to the mapped page on success, NULL on failure
 *
 * @note This function handles cache synchronization for architectures with weak
 *       memory models or Harvard architectures to ensure data visibility. It also
 *       manages the mapping structure lifecycle through proper allocation/free.
 */
void *dfs_aspace_mmap(struct dfs_file *file, struct rt_varea *varea, void *vaddr)
{
    void *ret = RT_NULL;
    struct dfs_page *page;
    struct dfs_aspace *aspace = file->vnode->aspace;
    rt_aspace_t target_aspace = varea->aspace;

    page = dfs_page_lookup(file, dfs_aspace_fpos(varea, vaddr));
    if (page)
    {
        struct dfs_mmap *map = (struct dfs_mmap *)rt_calloc(1, sizeof(struct dfs_mmap));
        if (map)
        {
            void *pg_vaddr = page->page;
            void *pg_paddr = rt_kmem_v2p(pg_vaddr);
            int err = rt_varea_map_range(varea, vaddr, pg_paddr, page->size);
            if (err == RT_EOK)
            {
                /**
                 * Note: While the page is mapped into user area, the data writing into the page
                 * is not guaranteed to be visible for machines with the *weak* memory model and
                 * those Harvard architecture (especially for those ARM64) cores for their
                 * out-of-order pipelines of data buffer. Besides if the instruction cache in the
                 * L1 memory system is a VIPT cache, there are chances to have the alias matching
                 * entry if we reuse the same page frame and map it into the same virtual address
                 * of the previous one.
                 *
                 * That's why we have to do synchronization and cleanup manually to ensure that
                 * fetching of the next instruction can see the coherent data with the data cache,
                 * TLB, MMU, main memory, and all the other observers in the computer system.
                 */
                rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, vaddr, ARCH_PAGE_SIZE);
                rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, vaddr, ARCH_PAGE_SIZE);

                ret = pg_vaddr;
                map->aspace = target_aspace;
                map->vaddr = vaddr;
                dfs_aspace_lock(aspace);
                rt_list_insert_after(&page->mmap_head, &map->mmap_node);
                dfs_page_release(page);
                dfs_aspace_unlock(aspace);
            }
            else
            {
                dfs_page_release(page);
                rt_free(map);
            }
        }
        else
        {
            dfs_page_release(page);
        }
    }

    return ret;
}

/**
 * @brief Unmap pages from virtual address space
 *
 * This function removes mappings of file pages within the specified virtual address range.
 * It handles cache synchronization and maintains page dirty status when unmapping.
 *
 * @param[in] file    Pointer to the file structure
 * @param[in] varea   Pointer to the virtual address area to unmap
 *
 * @return 0 on success
 *
 * @note This function handles both private and shared mappings, ensuring proper
 *       cache synchronization and page dirty status maintenance during unmapping.
 */
int dfs_aspace_unmap(struct dfs_file *file, struct rt_varea *varea)
{
    struct dfs_vnode *vnode = file->vnode;
    struct dfs_aspace *aspace = vnode->aspace;
    void *unmap_start = varea->start;
    void *unmap_end = (char *)unmap_start + varea->size;

    if (aspace)
    {
        rt_list_t *next;
        struct dfs_page *page;

        dfs_aspace_lock(aspace);
        if (aspace->pages_count > 0)
        {
            rt_list_for_each(next, &aspace->list_active)
            {
                if (next != &aspace->list_inactive)
                {
                    page = rt_list_entry(next, struct dfs_page, space_node);
                    if (page)
                    {
                        rt_list_t *node, *tmp;
                        struct dfs_mmap *map;
                        rt_varea_t map_varea = RT_NULL;

                        node = page->mmap_head.next;

                        while (node != &page->mmap_head)
                        {
                            rt_aspace_t map_aspace;
                            map = rt_list_entry(node, struct dfs_mmap, mmap_node);
                            tmp = node;
                            node = node->next;

                            if (map && varea->aspace == map->aspace
                                && map->vaddr >= unmap_start && map->vaddr < unmap_end)
                            {
                                void *vaddr = map->vaddr;
                                map_aspace = map->aspace;

                                if (!map_varea || map_varea->aspace != map_aspace ||
                                    vaddr < map_varea->start ||
                                    vaddr >= map_varea->start + map_varea->size)
                                {
                                    /* lock the tree so we don't access uncompleted data */
                                    map_varea = rt_aspace_query(map_aspace, vaddr);
                                }

                                rt_varea_unmap_page(map_varea, vaddr);

                                if (!rt_varea_is_private_locked(varea) &&
                                    page->fpos < page->aspace->vnode->size)
                                {
                                    dfs_page_dirty(page);
                                }
                                rt_list_remove(tmp);
                                rt_free(map);
                                break;
                            }
                        }
                    }
                }
            }
        }
        dfs_aspace_unlock(aspace);
    }

    return 0;
}

/**
 * Unmap a page from virtual address space.
 *
 * @param[in] file    The file object containing the page
 * @param[in] varea   The virtual memory area
 * @param[in] vaddr   The virtual address to unmap
 *
 * @return Always returns 0 on success
 *
 * @note This function removes the mapping between a virtual address and a physical page.
 *          It handles cleanup of mmap structures and marks pages dirty if needed.
 */
int dfs_aspace_page_unmap(struct dfs_file *file, struct rt_varea *varea, void *vaddr)
{
    struct dfs_page *page;
    struct dfs_aspace *aspace = file->vnode->aspace;

    if (aspace)
    {
        dfs_aspace_lock(aspace);

        page = dfs_page_search(aspace, dfs_aspace_fpos(varea, vaddr));
        if (page)
        {
            rt_list_t *node, *tmp;
            struct dfs_mmap *map;
            rt_varea_unmap_page(varea, vaddr);

            node = page->mmap_head.next;

            while (node != &page->mmap_head)
            {
                map = rt_list_entry(node, struct dfs_mmap, mmap_node);
                tmp = node;
                node = node->next;

                if (map && varea->aspace == map->aspace && vaddr == map->vaddr)
                {
                    if (!rt_varea_is_private_locked(varea))
                    {
                        dfs_page_dirty(page);
                    }
                    rt_list_remove(tmp);
                    rt_free(map);
                    break;
                }
            }

            dfs_page_release(page);
        }

        dfs_aspace_unlock(aspace);
    }

    return 0;
}

/**
 * Mark a page as dirty in the address space.
 *
 * @param[in] file    The file object containing the page
 * @param[in] varea   The virtual memory area
 * @param[in] vaddr   The virtual address of the page
 *
 * @return Always returns 0 on success
 *
 * @note This function marks a specific page as dirty in the file's address space.
 *          The page is released after being marked dirty.
 */
int dfs_aspace_page_dirty(struct dfs_file *file, struct rt_varea *varea, void *vaddr)
{
    struct dfs_page *page;
    struct dfs_aspace *aspace = file->vnode->aspace;

    if (aspace)
    {
        dfs_aspace_lock(aspace);

        page = dfs_page_search(aspace, dfs_aspace_fpos(varea, vaddr));
        if (page)
        {
            dfs_page_dirty(page);
            dfs_page_release(page);
        }

        dfs_aspace_unlock(aspace);
    }

    return 0;
}

/**
 * Calculate file position from virtual address.
 *
 * @param[in] varea   The virtual memory area
 * @param[in] vaddr   The virtual address to convert
 *
 * @return The calculated file position offset
 */
off_t dfs_aspace_fpos(struct rt_varea *varea, void *vaddr)
{
    return (off_t)(intptr_t)vaddr - (off_t)(intptr_t)varea->start + varea->offset * ARCH_PAGE_SIZE;
}

/**
 * Get the virtual address corresponding to a file position in a virtual area.
 *
 * @param[in] varea The virtual area structure
 * @param[in] fpos  The file position to convert
 *
 * @return The virtual address corresponding to the file position
 */
void *dfs_aspace_vaddr(struct rt_varea *varea, off_t fpos)
{
    return varea->start + fpos - varea->offset * ARCH_PAGE_SIZE;
}

/**
 * @brief Read data from memory-mapped file space
 *
 * This function handles read operations for memory-mapped file regions by
 * translating virtual addresses to file positions and performing the actual
 * read operation through dfs_aspace_read.
 *
 * @param[in] file   Pointer to the file structure being mapped
 * @param[in] varea  Pointer to the virtual memory area structure
 * @param[in] data   Pointer to the I/O message containing read details
 *                    (includes fault address and buffer address)
 *
 * @return Number of bytes successfully read (ARCH_PAGE_SIZE on success)
 *         0 if any parameter is invalid
 */
int dfs_aspace_mmap_read(struct dfs_file *file, struct rt_varea *varea, void *data)
{
    int ret = 0;

    if (file && varea)
    {
        struct rt_aspace_io_msg *msg = (struct rt_aspace_io_msg *)data;
        if (msg)
        {
            off_t fpos = dfs_aspace_fpos(varea, msg->fault_vaddr);
            return dfs_aspace_read(file, msg->buffer_vaddr, ARCH_PAGE_SIZE, &fpos);
        }
    }

    return ret;
}

/**
 * @brief Write data to memory-mapped file space
 *
 * This function handles write operations for memory-mapped file regions by
 * translating virtual addresses to file positions and performing the actual
 * write operation through dfs_aspace_write.
 *
 * @param[in] file   Pointer to the file structure being mapped
 * @param[in] varea  Pointer to the virtual memory area structure
 * @param[in] data   Pointer to the I/O message containing write details
 *                    (includes fault address and buffer address)
 *
 * @return Number of bytes successfully written (ARCH_PAGE_SIZE on success)
 *         0 if any parameter is invalid
 */
int dfs_aspace_mmap_write(struct dfs_file *file, struct rt_varea *varea, void *data)
{
    int ret = 0;

    if (file && varea)
    {
        struct rt_aspace_io_msg *msg = (struct rt_aspace_io_msg *)data;
        if (msg)
        {
            off_t fpos = dfs_aspace_fpos(varea, msg->fault_vaddr);
            return dfs_aspace_write(file, msg->buffer_vaddr, ARCH_PAGE_SIZE, &fpos);
        }
    }

    return ret;
}

#endif