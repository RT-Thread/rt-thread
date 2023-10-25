/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "dfs_file.h"
#include "dfs_dentry.h"
#include "dfs_mnt.h"

#define DBG_TAG "dfs.mmap"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#if defined(RT_USING_SMART) && defined(ARCH_MM_MMU) && defined(RT_USING_PAGECACHE)

#include "dfs_pcache.h"

#include <lwp.h>

#include <sys/mman.h>

#include <lwp_user_mm.h>
#include <mm_aspace.h>
#include <mm_fault.h>
#include <mm_flag.h>
#include <mm_page.h>
#include <mmu.h>
#include <page.h>
#include <tlb.h>

static rt_mem_obj_t dfs_get_mem_obj(struct dfs_file *file);
static void *dfs_mem_obj_get_file(rt_mem_obj_t mem_obj);

static void *_do_mmap(struct rt_lwp *lwp, void *map_vaddr, size_t map_size, size_t attr,
                      mm_flag_t flags, off_t pgoffset, void *data, rt_err_t *code)
{
    int ret = 0;
    void *vaddr = map_vaddr;
    rt_mem_obj_t mem_obj = dfs_get_mem_obj(data);

    ret = rt_aspace_map(lwp->aspace, &vaddr, map_size,
                        attr, flags, mem_obj, pgoffset);
    if (ret != RT_EOK)
    {
        vaddr = RT_NULL;
        LOG_E("failed to map %lx with size %lx with errno %d", map_vaddr,
              map_size, ret);
    }

    if (code)
    {
        *code = ret;
    }

    return vaddr;
}

static void *_map_data_to_uspace(struct dfs_mmap2_args *mmap2, void *data, rt_err_t *code)
{
    size_t offset = 0;
    void *map_vaddr = mmap2->addr;
    size_t map_size = mmap2->length;
    struct rt_lwp *lwp = mmap2->lwp;
    rt_size_t k_attr;
    rt_size_t k_flags;

    if (map_size)
    {
        offset = (size_t)map_vaddr & ARCH_PAGE_MASK;
        map_size += (offset + ARCH_PAGE_SIZE - 1);
        map_size &= ~ARCH_PAGE_MASK;
        map_vaddr = (void *)((size_t)map_vaddr & ~ARCH_PAGE_MASK);

        k_flags = lwp_user_mm_flag_to_kernel(mmap2->flags);
        k_attr = lwp_user_mm_attr_to_kernel(mmap2->prot);

        map_vaddr = _do_mmap(lwp, map_vaddr, map_size, k_attr, k_flags, mmap2->pgoffset, data, code);
    }

    return map_vaddr;
}

static void hint_free(rt_mm_va_hint_t hint)
{
}

static void on_page_fault(struct rt_varea *varea, struct rt_aspace_fault_msg *msg)
{
    void *page;
    struct dfs_file *file = dfs_mem_obj_get_file(varea->mem_obj);

    if (file)
    {
        LOG_I("%s varea: %p", __func__, varea);
        LOG_I("varea start: %p size: 0x%x offset: 0x%x attr: 0x%x flag: 0x%x",
               varea->start, varea->size, varea->offset, varea->attr, varea->flag);
        LOG_I("fault vaddr: %p", msg->fault_vaddr);

        if (file->dentry)
        {
            LOG_I("file: %s%s", file->dentry->mnt->fullpath, file->dentry->pathname);
        }

        page = dfs_aspace_mmap(file, varea, msg->fault_vaddr);
        if (page)
        {
            msg->response.status = MM_FAULT_STATUS_OK_MAPPED;
            msg->response.size = ARCH_PAGE_SIZE;
            msg->response.vaddr = page;
        }
        else
        {
            LOG_E("%s varea %p mmap failed at vaddr %p", __func__, varea, msg->fault_vaddr);
        }
    }
    else
    {
        LOG_E("%s varea %p not a file, vaddr %p", __func__, varea, varea->start);
    }
}

/* do pre open bushiness like inc a ref */
static void on_varea_open(struct rt_varea *varea)
{
    struct dfs_file *file = dfs_mem_obj_get_file(varea->mem_obj);
    varea->data = RT_NULL;
    rt_atomic_add(&(file->ref_count), 1);
}

/* do post close bushiness like def a ref */
static void on_varea_close(struct rt_varea *varea)
{
    struct dfs_file *file = dfs_mem_obj_get_file(varea->mem_obj);

    if (file)
    {
        LOG_I("%s varea: %p", __func__, varea);
        LOG_I("varea start: %p size: 0x%x offset: 0x%x attr: 0x%x flag: 0x%x",
               varea->start, varea->size, varea->offset, varea->attr, varea->flag);

        if (file->dentry)
        {
            LOG_I("file: %s%s", file->dentry->mnt->fullpath, file->dentry->pathname);
        }

        dfs_aspace_unmap(file, varea);
        dfs_file_lock();
        if (rt_atomic_load(&(file->ref_count)) == 1)
        {
            dfs_file_close(file);
        }
        else
        {
            rt_atomic_sub(&(file->ref_count), 1);
        }
        dfs_file_unlock();
    }
    else
    {
        LOG_E("%s varea %p not a file, vaddr %p", __func__, varea, varea->start);
    }
}

static const char *get_name(rt_varea_t varea)
{
    struct dfs_file *file = dfs_mem_obj_get_file(varea->mem_obj);

    return (file && file->dentry) ? file->dentry->pathname : "file-mapper";
}

void page_read(struct rt_varea *varea, struct rt_aspace_io_msg *msg)
{
    rt_ubase_t ret;
    struct dfs_file *file = dfs_mem_obj_get_file(varea->mem_obj);

    if (file)
    {
        LOG_I("%s varea: %p", __func__, varea);
        LOG_I("varea start: %p size: 0x%x offset: 0x%x attr: 0x%x flag: 0x%x",
               varea->start, varea->size, varea->offset, varea->attr, varea->flag);

        ret = dfs_aspace_mmap_read(file, varea, msg);
        if (ret > 0)
        {
            msg->response.status = MM_FAULT_STATUS_OK;
            if (ret < ARCH_PAGE_SIZE)
            {
                memset((char *)msg->buffer_vaddr + ret, 0, ARCH_PAGE_SIZE - ret);
            }
        }
    }
    else
    {
        LOG_E("%s varea %p not a file, vaddr %p", __func__, varea, varea->start);
    }
}

void page_write(struct rt_varea *varea, struct rt_aspace_io_msg *msg)
{
    rt_ubase_t ret;
    struct dfs_file *file = dfs_mem_obj_get_file(varea->mem_obj);

    if (file)
    {
        LOG_I("%s varea: %p", __func__, varea);
        LOG_I("varea start: %p size: 0x%x offset: 0x%x attr: 0x%x flag: 0x%x",
               varea->start, varea->size, varea->offset, varea->attr, varea->flag);

        ret = dfs_aspace_mmap_write(file, varea, msg);
        if (ret > 0)
        {
            msg->response.status = MM_FAULT_STATUS_OK;
            if (ret < ARCH_PAGE_SIZE)
            {
                memset((char *)msg->buffer_vaddr + ret, 0, ARCH_PAGE_SIZE - ret);
            }
        }
    }
    else
    {
        LOG_E("%s varea %p not a file, vaddr %p", __func__, varea, varea->start);
    }
}

static rt_err_t unmap_pages(rt_varea_t varea, void *rm_start, void *rm_end)
{
    struct dfs_file *file = dfs_mem_obj_get_file(varea->mem_obj);

    if (file)
    {
        LOG_I("%s varea: %p start: %p end: %p", __func__, varea, rm_start, rm_end);

        RT_ASSERT(!((rt_ubase_t)rm_start & ARCH_PAGE_MASK));
        RT_ASSERT(!((rt_ubase_t)rm_end & ARCH_PAGE_MASK));
        while (rm_start != rm_end)
        {
            dfs_aspace_page_unmap(file, varea, rm_start);
            rm_start += ARCH_PAGE_SIZE;
        }

        return RT_EOK;
    }
    else
    {
        LOG_E("%s varea %p not a file, vaddr %p", __func__, varea, varea->start);
    }

    return -RT_ERROR;
}

rt_err_t on_varea_shrink(struct rt_varea *varea, void *new_vaddr, rt_size_t size)
{
    char *varea_start = varea->start;
    void *rm_start;
    void *rm_end;

    LOG_I("%s varea: %p", __func__, varea);
    LOG_I("varea start: %p size: 0x%x offset: 0x%x attr: 0x%x flag: 0x%x",
           varea->start, varea->size, varea->offset, varea->attr, varea->flag);
    LOG_I("new_vaddr: %p size: %p", new_vaddr, size);

    if (varea_start == (char *)new_vaddr)
    {
        rm_start = varea_start + size;
        rm_end = varea_start + varea->size;
    }
    else
    {
        rm_start = varea_start;
        rm_end = new_vaddr;
    }

    return unmap_pages(varea, rm_start, rm_end);
}

rt_err_t on_varea_expand(struct rt_varea *varea, void *new_vaddr, rt_size_t size)
{
    LOG_I("%s varea: %p", __func__, varea);
    LOG_I("varea start: %p size: 0x%x offset: 0x%x attr: 0x%x flag: 0x%x",
           varea->start, varea->size, varea->offset, varea->attr, varea->flag);
    LOG_I("new_vaddr: %p size: %p", new_vaddr, size);

    return RT_EOK;
}

rt_err_t on_varea_split(struct rt_varea *existed, void *unmap_start, rt_size_t unmap_len, struct rt_varea *subset)
{
    rt_err_t rc;
    struct dfs_file *file = dfs_mem_obj_get_file(existed->mem_obj);

    if (file)
    {
        LOG_I("%s varea: %p", __func__, existed);
        LOG_I("varea start: %p size: 0x%x offset: 0x%x attr: 0x%x flag: 0x%x",
               existed->start, existed->size, existed->offset, existed->attr, existed->flag);
        LOG_I("unmap_start: %p unmap_len: %p", unmap_start, unmap_len);

        if (file->dentry)
        {
            LOG_I("file: %s%s", file->dentry->mnt->fullpath, file->dentry->pathname);
        }

        rc = unmap_pages(existed, unmap_start, (char *)unmap_start + unmap_len);
        if (!rc)
        {
            rc = unmap_pages(existed, subset->start, (char *)subset->start + subset->size);
            if (!rc)
                on_varea_open(subset);
        }

        return rc;
    }
    else
    {
        LOG_E("%s varea %p not a file, vaddr %p", __func__, existed, existed->start);
    }

    return -RT_ERROR;
}

rt_err_t on_varea_merge(struct rt_varea *merge_to, struct rt_varea *merge_from)
{
    struct dfs_file *file = dfs_mem_obj_get_file(merge_from->mem_obj);

    if (file)
    {
        LOG_I("%s varea: %p", __func__, merge_from);
        LOG_I("varea start: %p size: 0x%x offset: 0x%x attr: 0x%x flag: 0x%x",
               merge_from->start, merge_from->size, merge_from->offset, merge_from->attr, merge_from->flag);

        if (file->dentry)
        {
            LOG_I("file: %s%s", file->dentry->mnt->fullpath, file->dentry->pathname);
        }

        dfs_aspace_unmap(file, merge_from);
        on_varea_close(merge_from);

        return RT_EOK;
    }
    else
    {
        LOG_E("%s varea %p not a file, vaddr %p", __func__, merge_from, merge_from->start);
    }

    return -RT_ERROR;
}

static struct rt_mem_obj _mem_obj =
{
    .hint_free      = hint_free,
    .on_page_fault  = on_page_fault,
    .on_varea_open  = on_varea_open,
    .on_varea_close = on_varea_close,
    .get_name       = get_name,

    .page_read      = page_read,
    .page_write     = page_write,

    .on_varea_shrink    = on_varea_shrink,
    .on_varea_expand    = on_varea_expand,
    .on_varea_split     = on_varea_split,
    .on_varea_merge     = on_varea_merge,
};

struct dfs_mem_obj {
    struct rt_mem_obj mem_obj;
    void *file;
};

static rt_mem_obj_t dfs_get_mem_obj(struct dfs_file *file)
{
    rt_mem_obj_t mobj = file->mmap_context;
    if (!mobj)
    {
        struct dfs_mem_obj *dfs_mobj;
        dfs_file_lock();
        dfs_mobj = rt_malloc(sizeof(*dfs_mobj));
        if (dfs_mobj)
        {
            dfs_mobj->file = file;
            mobj = &dfs_mobj->mem_obj;
            memcpy(mobj, &_mem_obj, sizeof(*mobj));
            file->mmap_context = mobj;
        }
        dfs_file_unlock();
    }
    return mobj;
}

static void *dfs_mem_obj_get_file(rt_mem_obj_t mem_obj)
{
    struct dfs_mem_obj *dfs_mobj;
    dfs_mobj = rt_container_of(mem_obj, struct dfs_mem_obj, mem_obj);
    return dfs_mobj->file;
}

int dfs_file_mmap(struct dfs_file *file, struct dfs_mmap2_args *mmap2)
{
    rt_err_t ret = -EINVAL;
    void *map_vaddr;

    LOG_I("mmap2 args addr: %p length: 0x%x prot: %d flags: 0x%x pgoffset: 0x%x",
           mmap2->addr, mmap2->length, mmap2->prot, mmap2->flags, mmap2->pgoffset);
    if (file && file->vnode)
    {
        if (file->vnode->aspace)
        {
            /* create a va area in user space (lwp) */
            map_vaddr = _map_data_to_uspace(mmap2, file, &ret);
            if (map_vaddr)
            {
                mmap2->ret = map_vaddr;
                LOG_I("file: %s%s", file->dentry->mnt->fullpath, file->dentry->pathname);
            }
        }
        else
        {
            LOG_E("File mapping is not supported, file: %s%s", file->dentry->mnt->fullpath, file->dentry->pathname);
        }
    }

    return ret;
}
#else
int dfs_file_mmap(struct dfs_file *file, struct dfs_mmap2_args *mmap2)
{
    LOG_E("File mapping support is not enabled, file: %s%s", file->dentry->mnt->fullpath, file->dentry->pathname);
    LOG_E("mmap2 args addr: %p length: 0x%x prot: %d flags: 0x%x pgoffset: 0x%x",
           mmap2->addr, mmap2->length, mmap2->prot, mmap2->flags, mmap2->pgoffset);

    return -EPERM;
}
#endif
