/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
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

/**
 * @brief Perform memory mapping operation
 *
 * @param[in] lwp Pointer to the lightweight process structure
 * @param[in] map_vaddr Requested virtual address for mapping (may be NULL)
 * @param[in] map_size Size of the memory region to map
 * @param[in] attr Memory attributes for the mapping
 * @param[in] flags Memory mapping flags
 * @param[in] pgoffset Offset in pages from the start of the memory object
 * @param[in] data Pointer to the file descriptor to be mapped
 * @param[out] code Pointer to store the operation result code
 *
 * @return void* The mapped virtual address on success, NULL on failure
 *
 * @note This is a low-level mapping function that interacts directly with the address space manager.
 *       The actual mapping is performed by rt_aspace_map().
 */
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

/**
 * @brief Map data to user space address
 *
 * @param[in,out] mmap2 Pointer to memory mapping arguments structure
 *                      - Input: Contains mapping parameters (addr, length, etc.)
 *                      - Output: Contains the mapped address in ret field if successful
 * @param[in] data Pointer to the file descriptor to be mapped
 * @param[out] code Pointer to store the error code if mapping fails
 *
 * @return void* The mapped virtual address on success, NULL on failure
 *
 * @note This function performs page alignment on the mapping parameters and
 *       converts user-space flags/attributes to kernel-space before mapping.
 */
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
        k_flags = MMF_CREATE(k_flags, mmap2->min_align_size);
        k_attr = lwp_user_mm_attr_to_kernel(mmap2->prot);

        map_vaddr = _do_mmap(lwp, map_vaddr, map_size, k_attr, k_flags, mmap2->pgoffset, data, code);
    }

    return map_vaddr;
}

static void hint_free(rt_mm_va_hint_t hint)
{
}

/**
 * @brief Handle page fault for memory mapped file
 *
 * @param[in] varea Pointer to the virtual memory area structure
 * @param[in,out] msg Pointer to the page fault message structure
 *                   - Input: Contains fault information (fault_vaddr, etc.)
 *                   - Output: Contains response status and mapped page address
 *
 * @note This function is called when a page fault occurs in a memory mapped file region.
 *       It attempts to map the faulting page and updates the response accordingly.
 */
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

/**
 * @brief Handle virtual memory area opening event
 *
 * @param[in] varea Pointer to the virtual memory area structure
 *
 * @note This function is called when a virtual memory area is opened.
 *       It increments the reference count of the associated file and
 *       initializes varea->data to NULL.
 */
static void on_varea_open(struct rt_varea *varea)
{
    struct dfs_file *file = dfs_mem_obj_get_file(varea->mem_obj);
    varea->data = RT_NULL;
    rt_atomic_add(&(file->ref_count), 1);
}

/**
 * @brief Handle virtual memory area closing event
 *
 * @param[in] varea Pointer to the virtual memory area structure
 *
 * @note This function is called when a virtual memory area is closed.
 *       It performs cleanup operations including:
 *       - Unmapping the file from memory
 *       - Decrementing file reference count
 *       - Closing and destroying file if reference count reaches zero
 */
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
            dfs_file_destroy(file);
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

/**
 * @brief Get the name of the memory mapped file
 *
 * @param[in] varea Pointer to the virtual memory area structure
 *
 * @return const char* The name of the mapped file if available,
 *                     otherwise returns "file-mapper" as default name
 *
 * @note This function retrieves the file name from the dentry structure
 *       associated with the memory mapped file.
 */
static const char *get_name(rt_varea_t varea)
{
    struct dfs_file *file = dfs_mem_obj_get_file(varea->mem_obj);

    return (file && file->dentry) ? file->dentry->pathname : "file-mapper";
}

/**
 * @brief Read data from memory mapped file page
 *
 * @param[in] varea Pointer to the virtual memory area structure
 * @param[in,out] msg Pointer to the I/O message structure
 *                   - Input: Contains read request information
 *                   - Output: Contains response status and read data
 *
 * @note This function handles page read operations for memory mapped files.
 *       If the read size is less than page size, it zero-fills the remaining space.
 */
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
        if (ret >= 0)
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

/**
 * @brief Write data to memory mapped file page
 *
 * @param[in] varea Pointer to the virtual memory area structure
 * @param[in,out] msg Pointer to the I/O message structure
 *                   - Input: Contains write request information
 *                   - Output: Contains response status and write result
 *
 * @note This function handles page write operations for memory mapped files.
 *       If the write size is less than page size, it zero-fills the remaining space.
 */
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

/**
 * @brief Unmap pages from virtual memory area
 *
 * @param[in] varea Pointer to the virtual memory area structure
 * @param[in] rm_start Starting address of the range to unmap (must be page aligned)
 * @param[in] rm_end Ending address of the range to unmap (must be page aligned)
 *
 * @return rt_err_t Error code:
 *                  - RT_EOK: Success
 *                  - -RT_ERROR: Failure (varea not associated with a file)
 *
 * @note This function performs page-by-page unmapping.
 *       Both rm_start and rm_end must be page-aligned (checked by RT_ASSERT).
 */
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

/**
 * @brief Handle virtual memory area shrinking operation
 *
 * @param[in] varea Pointer to the virtual memory area structure
 * @param[in] new_vaddr New starting address after shrinking
 * @param[in] size New size of the virtual memory area
 *
 * @return rt_err_t Error code:
 *                  - RT_EOK: Success
 *                  - Other errors from unmap_pages()
 *
 * @note This function determines the range of pages to unmap based on whether
 *       the varea is shrinking from the start or end.
 */
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

/**
 * @brief Handle virtual memory area expansion operation
 *
 * @param[in] varea Pointer to the virtual memory area structure
 * @param[in] new_vaddr New starting address after expansion
 * @param[in] size New size of the expanded virtual memory area
 *
 * @return rt_err_t returns RT_EOK (success).
 *
 * @note This function is currently not implemented.
 */
rt_err_t on_varea_expand(struct rt_varea *varea, void *new_vaddr, rt_size_t size)
{
    LOG_I("%s varea: %p", __func__, varea);
    LOG_I("varea start: %p size: 0x%x offset: 0x%x attr: 0x%x flag: 0x%x",
           varea->start, varea->size, varea->offset, varea->attr, varea->flag);
    LOG_I("new_vaddr: %p size: %p", new_vaddr, size);

    return RT_EOK;
}

/**
 * @brief Handle virtual memory area splitting operation
 *
 * @param[in] existed Pointer to the existing virtual memory area to be split
 * @param[in] unmap_start Starting address of the range to unmap
 * @param[in] unmap_len Length of the range to unmap
 * @param[in,out] subset Pointer to the new subset virtual memory area
 *                      - Input: Contains new varea parameters
 *                      - Output: Contains initialized varea after splitting
 *
 * @return rt_err_t Error code:
 *                  - RT_EOK: Success
 *                  - -RT_ERROR: Failure (varea not associated with a file)
 *
 * @note This function splits an existing virtual memory area into two parts.
 *       It unmaps the specified range and initializes the new subset area.
 */
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

/**
 * @brief Handle virtual memory area merging operation
 *
 * @param[in] merge_to Pointer to the target virtual memory area that will receive the merge
 * @param[in] merge_from Pointer to the source virtual memory area to be merged
 *
 * @return rt_err_t Error code:
 *                  - RT_EOK: Success
 *                  - -RT_ERROR: Failure (varea not associated with a file)
 */
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

/**
 * @brief Handle virtual memory area remapping operation
 *
 * @param[in] varea Pointer to the virtual memory area structure
 * @param[in] new_size New size of the virtual memory area after remapping
 * @param[in] flags Remapping flags (e.g., MREMAP_MAYMOVE)
 * @param[in] new_address New starting address after remapping (optional)
 *
 * @return void* Pointer to the new virtual memory area after remapping
 *               - Returns RT_NULL if remapping fails
 *
 * @note This function remaps a virtual memory area to a new address or size.
 *       It currently supports the MREMAP_MAYMOVE flag.
 */
void *on_varea_mremap(struct rt_varea *varea, rt_size_t new_size, int flags, void *new_address)
{
    void *vaddr = RT_NULL;
    struct dfs_file *file = dfs_mem_obj_get_file(varea->mem_obj);

#ifndef MREMAP_MAYMOVE
#define MREMAP_MAYMOVE 1
#endif

    if (file && flags == MREMAP_MAYMOVE)
    {
        int ret;
        rt_mem_obj_t mem_obj = dfs_get_mem_obj(file);

        vaddr = new_address ? new_address : varea->start;
        new_size = (new_size + ARCH_PAGE_SIZE - 1);
        new_size &= ~ARCH_PAGE_MASK;
        ret = rt_aspace_map(varea->aspace, &vaddr, new_size, varea->attr, varea->flag, mem_obj, varea->offset);
        if (ret != RT_EOK)
        {
            LOG_E("failed to map %lx with size %lx with errno %d", vaddr, new_size, ret);
            vaddr = RT_NULL;
        }
        else
        {
            LOG_I("old: %p size: %p new: %p size: %p", varea->start, varea->size, vaddr, new_size);
        }
    }

    return vaddr;
}

/**
 * @brief Memory object operations structure
 *
 * Defines function pointers for various virtual memory area (varea) operations,
 * including memory management, page fault handling, and lifecycle callbacks.
 */
static struct rt_mem_obj _mem_obj =
{
    .hint_free      = hint_free,       /* Free memory hint function */
    .on_page_fault  = on_page_fault,   /* Page fault handler */
    .on_varea_open  = on_varea_open,   /* Varea open callback */
    .on_varea_close = on_varea_close,  /* Varea close callback */
    .get_name       = get_name,        /* Get mapped file name */

    .page_read      = page_read,       /* Page read operation */
    .page_write     = page_write,      /* Page write operation */

    .on_varea_shrink    = on_varea_shrink,    /* Varea shrink handler */
    .on_varea_expand    = on_varea_expand,    /* Varea expand handler */
    .on_varea_split     = on_varea_split,     /* Varea split handler */
    .on_varea_merge     = on_varea_merge,     /* Varea merge handler */

    .on_varea_mremap    = on_varea_mremap,    /* Varea remap handler */
};

/**
 * @brief DFS memory object structure
 *
 * Contains a standard memory object and an associated file pointer,
 * used to maintain the relationship between memory mappings and files.
 */
struct dfs_mem_obj {
    struct rt_mem_obj mem_obj;  /* Base memory object */
    void *file;                 /* Associated file pointer */
};

/**
 * @brief Get or create memory mapping object for a file
 *
 * @param[in] file Pointer to the file descriptor structure
 *
 * @return rt_mem_obj_t Memory mapping object associated with the file
 *                      - Returns existing object if already created
 *                      - Creates and initializes new object if not exists
 */
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

/**
 * @brief Get the file descriptor from memory mapping object
 *
 * @param[in] mem_obj Pointer to the memory mapping object
 *
 * @return void* Pointer to the associated file descriptor structure
 *
 * @note This function uses rt_container_of macro to get the containing
 *       dfs_mem_obj structure from its mem_obj member.
 */
static void *dfs_mem_obj_get_file(rt_mem_obj_t mem_obj)
{
    struct dfs_mem_obj *dfs_mobj;
    dfs_mobj = rt_container_of(mem_obj, struct dfs_mem_obj, mem_obj);
    return dfs_mobj->file;
}

/**
 * @brief Map a file into memory
 *
 * @param[in] file Pointer to the file descriptor structure
 * @param[in,out] mmap2 Pointer to memory mapping arguments structure
 *                      - Input: Contains mapping parameters (addr, length, etc.)
 *                      - Output: Contains the mapped address in ret field if successful
 *
 * @return int Error code:
 *             - EINVAL: Invalid parameters
 *             - Other errors from underlying mapping operations
 *
 * @note This function creates a virtual address area in user space (lwp) for the file mapping.
 *       The actual mapping is performed by _map_data_to_uspace().
 */
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
