/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
#include <mm_page.h>
#include <mm_private.h>
#include <mmu.h>
#include <tlb.h>

#include <rthw.h>

#ifdef RT_USING_PAGECACHE

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

void dfs_pcache_unmount(struct dfs_mnt *mnt)
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
            dfs_aspace_release(aspace);
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
            dfs_aspace_release(aspace);
        }
    }

    dfs_pcache_unlock();
}

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

static rt_ubase_t dfs_pcache_mq_work(rt_uint32_t cmd)
{
    rt_err_t err;
    struct dfs_pcache_mq_obj work = { 0 };

    work.cmd = cmd;

    err = rt_mq_send_wait(__pcache.mqueue, (const void *)&work, sizeof(struct dfs_pcache_mq_obj), 0);

    return err;
}

static int dfs_pcache_lock(void)
{
    rt_mutex_take(&__pcache.lock, RT_WAITING_FOREVER);
    return 0;
}

static int dfs_pcache_unlock(void)
{
    rt_mutex_release(&__pcache.lock);
    return 0;
}

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

static struct dfs_page *dfs_page_create(void)
{
    struct dfs_page *page = RT_NULL;

    page = rt_calloc(1, sizeof(struct dfs_page));
    if (page)
    {
        page->page = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
        if (page->page)
        {
            //memset(page->page, 0x00, ARCH_PAGE_SIZE);
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

static void dfs_page_ref(struct dfs_page *page)
{
    rt_atomic_add(&(page->ref_count), 1);
}

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

static int dfs_page_compare(off_t fpos, off_t value)
{
    return fpos / ARCH_PAGE_SIZE * ARCH_PAGE_SIZE - value;
}

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

static void _dfs_page_remove(struct dfs_aspace *aspace, struct dfs_page *page)
{
    if (aspace->avl_page && aspace->avl_page == page)
    {
        aspace->avl_page = 0;
    }

    util_avl_remove(&page->avl_node, &aspace->avl_root);
}

static int dfs_aspace_lock(struct dfs_aspace *aspace)
{
    rt_mutex_take(&aspace->lock, RT_WAITING_FOREVER);
    return 0;
}

static int dfs_aspace_unlock(struct dfs_aspace *aspace)
{
    rt_mutex_release(&aspace->lock);
    return 0;
}

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

static struct dfs_page *dfs_aspace_load_page(struct dfs_file *file, off_t pos)
{
    struct dfs_page *page = RT_NULL;

    if (file && file->vnode && file->vnode->aspace)
    {
        struct dfs_vnode *vnode = file->vnode;
        struct dfs_aspace *aspace = vnode->aspace;

        page = dfs_page_create();
        if (page)
        {
            page->aspace = aspace;
            page->size = ARCH_PAGE_SIZE;
            page->fpos = pos / ARCH_PAGE_SIZE * ARCH_PAGE_SIZE;
            aspace->ops->read(file, page);
            page->ref_count ++;

            dfs_page_insert(page);
        }
    }

    return page;
}

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

int dfs_aspace_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
{
    int ret = -EINVAL;

    if (file && file->vnode && file->vnode->aspace)
    {
        if (!(file->vnode->aspace->ops->write))
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

off_t dfs_aspace_fpos(struct rt_varea *varea, void *vaddr)
{
    return (off_t)(intptr_t)vaddr - (off_t)(intptr_t)varea->start + varea->offset * ARCH_PAGE_SIZE;
}

void *dfs_aspace_vaddr(struct rt_varea *varea, off_t fpos)
{
    return varea->start + fpos - varea->offset * ARCH_PAGE_SIZE;
}

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
