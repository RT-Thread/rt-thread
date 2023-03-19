/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-14     WangXiaoyao  the first version
 */

/**
 * @brief Virtual Address Space
 */

#include <rtdef.h>
#include <rtthread.h>
#include <stddef.h>
#include <stdint.h>

#define DBG_TAG "mm.aspace"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "avl_adpt.h"
#include "mm_aspace.h"
#include "mm_fault.h"
#include "mm_flag.h"
#include "mm_page.h"
#include "mm_private.h"

#include <mmu.h>
#include <tlb.h>

static void _aspace_unmap(rt_aspace_t aspace, void *addr, rt_size_t length);
static void *_find_free(rt_aspace_t aspace, void *prefer, rt_size_t req_size,
                        void *limit_start, rt_size_t limit_size,
                        mm_flag_t flags);

struct rt_aspace rt_kernel_space;

rt_varea_t _varea_create(void *start, rt_size_t size)
{
    rt_varea_t varea;
    varea = (rt_varea_t)rt_malloc(sizeof(struct rt_varea));
    if (varea)
    {
        varea->start = start;
        varea->size = size;
    }
    return varea;
}

static inline void _varea_post_install(rt_varea_t varea, rt_aspace_t aspace,
                                       rt_size_t attr, rt_size_t flags,
                                       rt_mem_obj_t mem_obj, rt_size_t offset)
{
    varea->aspace = aspace;
    varea->attr = attr;
    varea->mem_obj = mem_obj;
    varea->flag = flags;
    varea->offset = offset;
    varea->frames = NULL;

    if (varea->mem_obj && varea->mem_obj->on_varea_open)
        varea->mem_obj->on_varea_open(varea);
}

/* restore context modified by varea install */
static inline void _varea_uninstall(rt_varea_t varea)
{
    rt_aspace_t aspace = varea->aspace;

    if (varea->mem_obj && varea->mem_obj->on_varea_close)
        varea->mem_obj->on_varea_close(varea);

    rt_varea_free_pages(varea);

    rt_hw_mmu_unmap(aspace, varea->start, varea->size);
    rt_hw_tlb_invalidate_range(aspace, varea->start, varea->size, ARCH_PAGE_SIZE);

    WR_LOCK(aspace);
    _aspace_bst_remove(aspace, varea);
    WR_UNLOCK(aspace);
}

int _init_lock(rt_aspace_t aspace)
{
    MM_PGTBL_LOCK_INIT(aspace);
    rt_mutex_init(&aspace->bst_lock, "", RT_IPC_FLAG_FIFO);

    return RT_EOK;
}

rt_aspace_t rt_aspace_create(void *start, rt_size_t length, void *pgtbl)
{
    rt_aspace_t aspace = NULL;
    void *page_table = pgtbl;

    if (page_table)
    {
        aspace = (rt_aspace_t)rt_malloc(sizeof(*aspace));
        if (aspace)
        {
            aspace->page_table = page_table;
            aspace->start = start;
            aspace->size = length;
            if (_init_lock(aspace) != RT_EOK ||
                _aspace_bst_init(aspace) != RT_EOK)
            {
                rt_free(aspace);
                aspace = NULL;
            }
        }
    }
    return aspace;
}

rt_aspace_t rt_aspace_init(rt_aspace_t aspace, void *start, rt_size_t length,
                           void *pgtbl)
{
    void *page_table = pgtbl;
    LOG_D("%s", __func__);

    if (page_table)
    {
        aspace->page_table = page_table;
        aspace->start = start;
        aspace->size = length;
        if (_init_lock(aspace) != RT_EOK || _aspace_bst_init(aspace) != RT_EOK)
        {
            aspace = NULL;
        }
    }
    return aspace;
}

void rt_aspace_detach(rt_aspace_t aspace)
{
    _aspace_unmap(aspace, aspace->start, aspace->size);
    rt_mutex_detach(&aspace->bst_lock);
}

void rt_aspace_delete(rt_aspace_t aspace)
{
    if (aspace)
    {
        rt_aspace_detach(aspace);
        rt_free(aspace);
    }
}

static int _do_named_map(rt_aspace_t aspace, void *vaddr, rt_size_t length,
                         rt_size_t offset, rt_size_t attr)
{
    LOG_D("%s: va %p length %p", __func__, vaddr, length);
    int err = RT_EOK;

    /* it's ensured by caller that (void*)end will not overflow */
    void *end = vaddr + length;
    void *phyaddr = (void *)(offset << MM_PAGE_SHIFT);
    while (vaddr != end)
    {
        /* TODO try to map with huge TLB, when flag & HUGEPAGE */
        rt_size_t pgsz = ARCH_PAGE_SIZE;
        void *ret = rt_hw_mmu_map(aspace, vaddr, phyaddr, pgsz, attr);
        if (ret == RT_NULL)
        {
            err = -RT_ERROR;
            break;
        }
        vaddr += pgsz;
        phyaddr += pgsz;
    }

    if (err == RT_EOK)
        rt_hw_tlb_invalidate_range(aspace, end - length, length, ARCH_PAGE_SIZE);

    return err;
}

rt_inline void _do_page_fault(struct rt_mm_fault_msg *msg, rt_size_t off,
                              void *vaddr, rt_mem_obj_t mem_obj,
                              rt_varea_t varea)
{
    msg->off = off;
    msg->vaddr = vaddr;
    msg->fault_op = MM_FAULT_OP_READ;
    msg->fault_type = MM_FAULT_TYPE_PAGE_FAULT;
    msg->response.status = -1;

    mem_obj->on_page_fault(varea, msg);
}

/* allocate memory page for mapping range */
static int _do_prefetch(rt_aspace_t aspace, rt_varea_t varea, void *start,
                        rt_size_t size)
{
    int err = RT_EOK;

    /* it's ensured by caller that start & size ara page-aligned */
    void *end = start + size;
    void *vaddr = start;
    rt_size_t off = varea->offset + ((start - varea->start) >> ARCH_PAGE_SHIFT);

    while (vaddr != end)
    {
        /* TODO try to map with huge TLB, when flag & HUGEPAGE */
        struct rt_mm_fault_msg msg;
        _do_page_fault(&msg, off, vaddr, varea->mem_obj, varea);

        if (msg.response.status == MM_FAULT_STATUS_OK)
        {
            void *store = msg.response.vaddr;
            rt_size_t store_sz = msg.response.size;

            if (store_sz + vaddr > end)
            {
                LOG_W("%s: too much (0x%lx) of buffer at vaddr %p is provided",
                      __func__, store_sz, vaddr);
                break;
            }

            void *map = rt_hw_mmu_map(aspace, vaddr, store + PV_OFFSET,
                                      store_sz, varea->attr);

            if (!map)
            {
                LOG_W("%s: MMU mapping failed for va %p to %p of %lx", __func__,
                      vaddr, store + PV_OFFSET, store_sz);
            }
            else
            {
                rt_hw_tlb_invalidate_range(aspace, vaddr, store_sz, ARCH_PAGE_SIZE);
            }
            vaddr += store_sz;
            off += store_sz >> ARCH_PAGE_SHIFT;
        }
        else
        {
            err = -RT_ENOMEM;
            LOG_W("%s failed because no memory is provided", __func__);
            break;
        }
    }

    return err;
}

int _varea_install(rt_aspace_t aspace, rt_varea_t varea, rt_mm_va_hint_t hint)
{
    void *alloc_va;
    int err = RT_EOK;

    /**
     * find a suitable va range.
     * even though this is sleepable, it's still ok for startup routine
     */
    alloc_va =
        _find_free(aspace, hint->prefer, hint->map_size, hint->limit_start,
                   hint->limit_range_size, hint->flags);

    /* TODO try merge surrounding regions to optimize memory footprint */

    if (alloc_va != RT_NULL)
    {
        varea->start = alloc_va;
        _aspace_bst_insert(aspace, varea);
    }
    else
    {
        err = -RT_ENOSPC;
    }

    return err;
}

static int _mm_aspace_map(rt_aspace_t aspace, rt_varea_t varea, rt_size_t attr,
                          mm_flag_t flags, rt_mem_obj_t mem_obj,
                          rt_size_t offset)
{
    int err = RT_EOK;

    WR_LOCK(aspace);
    struct rt_mm_va_hint hint = {.prefer = varea->start,
                                 .map_size = varea->size,
                                 .limit_start = aspace->start,
                                 .limit_range_size = aspace->size,
                                 .flags = flags};

    if (mem_obj->hint_free)
    {
        /* mem object can control mapping range and so by modifing hint */
        mem_obj->hint_free(&hint);
    }

    err = _varea_install(aspace, varea, &hint);
    WR_UNLOCK(aspace);

    if (err == RT_EOK)
    {
        /* fill in varea data */
        _varea_post_install(varea, aspace, attr, flags, mem_obj, offset);

        if (MMF_TEST_CNTL(flags, MMF_PREFETCH))
        {
            /* do the MMU & TLB business */
            err = _do_prefetch(aspace, varea, varea->start, varea->size);
            if (err)
            {
                /* restore data structure and MMU */
                _varea_uninstall(varea);
            }
        }
    }

    return err;
}

#define _IS_OVERFLOW(start, length) ((length) > (0ul - (uintptr_t)(start)))
#define _IS_OVERSIZE(start, length, limit_s, limit_sz) (((length) + (rt_size_t)((start) - (limit_start))) > (limit_size))

static inline int _not_in_range(void *start, rt_size_t length,
                                void *limit_start, rt_size_t limit_size)
{
    if (start != RT_NULL)
        LOG_D("%s: [%p : %p] [%p : %p]", __func__, start, length, limit_start, limit_size);
    /* assuming (base + length) will not overflow except (0) */
    return start != RT_NULL
               ? (_IS_OVERFLOW(start, length) || start < limit_start ||
                  _IS_OVERSIZE(start, length, limit_start, limit_size))
               : length > limit_size;
}

static inline int _not_align(void *start, rt_size_t length, rt_size_t mask)
{
    return (start != RT_NULL) &&
           (((uintptr_t)start & mask) || (length & mask));
}

static inline int _not_support(rt_size_t flags)
{
    rt_size_t support_ops = (MMF_PREFETCH | MMF_MAP_FIXED | MMF_TEXT);
    return flags & ~(support_ops | _MMF_ALIGN_MASK);
}

int rt_aspace_map(rt_aspace_t aspace, void **addr, rt_size_t length,
                  rt_size_t attr, mm_flag_t flags, rt_mem_obj_t mem_obj,
                  rt_size_t offset)
{
    /* TODO check not in atomic context: irq, spinlock, local intr disable... */
    int err;
    rt_varea_t varea;

    if (!aspace || !addr || !mem_obj || length == 0 ||
        _not_in_range(*addr, length, aspace->start, aspace->size))
    {
        err = -RT_EINVAL;
        LOG_I("%s: Invalid input", __func__);
    }
    else if (_not_support(flags))
    {
        LOG_I("%s: no support flags 0x%p", __func__, flags);
        err = -RT_ENOSYS;
    }
    else
    {
        varea = _varea_create(*addr, length);

        if (varea)
        {
            err = _mm_aspace_map(aspace, varea, attr, flags, mem_obj, offset);
            if (err != RT_EOK)
            {
                rt_free(varea);
            }
        }
        else
        {
            LOG_W("%s: mm aspace map failed", __func__);
            err = -RT_ENOMEM;
        }
    }

    if (err != RT_EOK)
    {
        *addr = NULL;
    }
    else
    {
        *addr = varea->start;
    }
    return err;
}

int rt_aspace_map_static(rt_aspace_t aspace, rt_varea_t varea, void **addr,
                         rt_size_t length, rt_size_t attr, mm_flag_t flags,
                         rt_mem_obj_t mem_obj, rt_size_t offset)
{
    int err;

    if (!aspace || !varea || !addr || !mem_obj || length == 0 ||
        _not_in_range(*addr, length, aspace->start, aspace->size))
    {
        err = -RT_EINVAL;
        LOG_W("%s: Invalid input", __func__);
    }
    else if (_not_support(flags))
    {
        LOG_W("%s: no support flags", __func__);
        err = -RT_ENOSYS;
    }
    else
    {
        varea->size = length;
        varea->start = *addr;
        flags |= MMF_STATIC_ALLOC;
        err = _mm_aspace_map(aspace, varea, attr, flags, mem_obj, offset);
    }

    if (err != RT_EOK)
    {
        *addr = NULL;
    }
    else
    {
        *addr = varea->start;
    }
    return err;
}

int _mm_aspace_map_phy(rt_aspace_t aspace, rt_varea_t varea,
                       rt_mm_va_hint_t hint, rt_size_t attr, rt_size_t pa_off,
                       void **ret_va)
{
    int err;
    void *vaddr;

    if (!aspace || !hint || !hint->limit_range_size || !hint->map_size)
    {
        LOG_W("%s: Invalid input", __func__);
        err = -RT_EINVAL;
    }
    else if (_not_align(hint->prefer, hint->map_size, ARCH_PAGE_MASK))
    {
        LOG_W("%s: not aligned", __func__);
        err = -RT_EINVAL;
    }
    else if (_not_in_range(hint->limit_start, hint->limit_range_size, aspace->start,
                      aspace->size) ||
        _not_in_range(hint->prefer, hint->map_size, aspace->start,
                      aspace->size))
    {
        LOG_W("%s: not in range", __func__);
        err = -RT_EINVAL;
    }
    else
    {
        WR_LOCK(aspace);
        err = _varea_install(aspace, varea, hint);
        WR_UNLOCK(aspace);

        if (err == RT_EOK)
        {
            _varea_post_install(varea, aspace, attr, 0, NULL, pa_off);

            vaddr = varea->start;

            err = _do_named_map(aspace, varea->start, varea->size,
                                (rt_size_t)pa_off, attr);

            if (err != RT_EOK)
            {
                _varea_uninstall(varea);
            }
        }
    }

    if (ret_va)
    {
        if (err == RT_EOK)
            *ret_va = vaddr;
        else
            *ret_va = RT_NULL;
    }

    return err;
}

int rt_aspace_map_phy(rt_aspace_t aspace, rt_mm_va_hint_t hint, rt_size_t attr,
                      rt_size_t pa_off, void **ret_va)
{
    int err;

    if (hint)
    {
        rt_varea_t varea = _varea_create(hint->prefer, hint->map_size);
        if (varea)
        {
            err = _mm_aspace_map_phy(aspace, varea, hint, attr, pa_off, ret_va);
            if (err != RT_EOK)
            {
                rt_free(varea);
            }
        }
        else
        {
            err = -RT_ENOMEM;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

int rt_aspace_map_phy_static(rt_aspace_t aspace, rt_varea_t varea,
                             rt_mm_va_hint_t hint, rt_size_t attr,
                             rt_size_t pa_off, void **ret_va)
{
    int err;

    if (varea && hint)
    {
        varea->start = hint->prefer;
        varea->size = hint->map_size;
        hint->flags |= (MMF_MAP_FIXED | MMF_STATIC_ALLOC);
        LOG_D("%s: start %p size %p phy at %p", __func__, varea->start, varea->size, pa_off << MM_PAGE_SHIFT);
        err = _mm_aspace_map_phy(aspace, varea, hint, attr, pa_off, ret_va);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

void _aspace_unmap(rt_aspace_t aspace, void *addr, rt_size_t length)
{
    struct _mm_range range = {addr, addr + length - 1};
    rt_varea_t varea = _aspace_bst_search_overlap(aspace, range);

    if (varea == RT_NULL)
    {
        LOG_I("%s: No such entry found at %p with %lx bytes\n", __func__, addr, length);
    }

    while (varea)
    {
        _varea_uninstall(varea);
        if (!(varea->flag & MMF_STATIC_ALLOC))
        {
            rt_free(varea);
        }
        varea = _aspace_bst_search_overlap(aspace, range);
    }
}

int rt_aspace_unmap(rt_aspace_t aspace, void *addr, rt_size_t length)
{
    if (!aspace)
    {
        LOG_I("%s: Invalid input", __func__);
        return -RT_EINVAL;
    }

    if (_not_in_range(addr, length, aspace->start, aspace->size))
    {
        LOG_I("%s: %lx not in range of aspace[%lx:%lx]", __func__, addr,
              aspace->start, aspace->start + aspace->size);
        return -RT_EINVAL;
    }

    _aspace_unmap(aspace, addr, length);

    return RT_EOK;
}

static inline void *_lower(void *a, void *b)
{
    return a < b ? a : b;
}

static inline void *_align(void *va, rt_ubase_t align_mask)
{
    return (void *)((rt_ubase_t)(va + ~align_mask) & align_mask);
}

static void *_ascending_search(rt_varea_t varea, rt_size_t req_size,
                               rt_ubase_t align_mask, struct _mm_range limit)
{
    void *ret = RT_NULL;
    while (varea && varea->start < limit.end)
    {
        void *candidate = varea->start + varea->size;
        candidate = _align(candidate, align_mask);

        if (candidate > limit.end || limit.end - candidate + 1 < req_size)
            break;

        rt_varea_t nx_va = ASPACE_VAREA_NEXT(varea);
        if (nx_va)
        {
            rt_size_t gap_size =
                _lower(limit.end, nx_va->start - 1) - candidate + 1;
            if (gap_size >= req_size)
            {
                ret = candidate;
                break;
            }
        }
        else
        {
            ret = candidate;
        }
        varea = nx_va;
    }
    return ret;
}

/** find suitable place in [limit_start, limit_end] */
static void *_find_head_and_asc_search(rt_aspace_t aspace, rt_size_t req_size,
                                       rt_ubase_t align_mask,
                                       struct _mm_range limit)
{
    void *va = RT_NULL;

    rt_varea_t varea = _aspace_bst_search_exceed(aspace, limit.start);
    if (varea)
    {
        void *candidate = _align(limit.start, align_mask);
        rt_size_t gap_size = varea->start - candidate;
        if (gap_size >= req_size)
        {
            rt_varea_t former = _aspace_bst_search(aspace, limit.start);
            if (former)
            {
                candidate = _align(former->start + former->size, align_mask);
                gap_size = varea->start - candidate;

                if (gap_size >= req_size)
                    va = candidate;
                else
                    va = _ascending_search(varea, req_size, align_mask, limit);
            }
            else
            {
                va = candidate;
            }
        }
        else
        {
            va = _ascending_search(varea, req_size, align_mask, limit);
        }
    }
    else
    {
        void *candidate;
        rt_size_t gap_size;
        rt_varea_t former = _aspace_bst_search(aspace, limit.start);

        candidate = former ? former->start + former->size : limit.start;
        candidate = _align(candidate, align_mask);
        gap_size = limit.end - candidate + 1;

        if (gap_size >= req_size)
            va = candidate;
    }

    return va;
}

static void *_find_free(rt_aspace_t aspace, void *prefer, rt_size_t req_size,
                        void *limit_start, rt_size_t limit_size,
                        mm_flag_t flags)
{
    rt_varea_t varea = NULL;
    void *va = RT_NULL;
    struct _mm_range limit = {limit_start, limit_start + limit_size - 1};

    rt_ubase_t align_mask = ~0ul;
    if (flags & MMF_REQUEST_ALIGN)
    {
        align_mask = ~((1 << MMF_GET_ALIGN(flags)) - 1);
    }

    if (prefer != RT_NULL)
    {
        prefer = _align(prefer, align_mask);
        struct _mm_range range = {prefer, prefer + req_size - 1};
        varea = _aspace_bst_search_overlap(aspace, range);

        if (!varea)
        {
            va = prefer;
        }
        else if (flags & MMF_MAP_FIXED)
        {
            /* OVERLAP */
        }
        else
        {
            va = _ascending_search(varea, req_size, align_mask, limit);
            if (va == RT_NULL)
            {
                limit.end = varea->start - 1;
                va = _find_head_and_asc_search(aspace, req_size, align_mask,
                                               limit);
            }
        }
    }
    else
    {
        va = _find_head_and_asc_search(aspace, req_size, align_mask, limit);
    }

    return va;
}

int rt_aspace_load_page(rt_aspace_t aspace, void *addr, rt_size_t npage)
{
    int err = RT_EOK;
    rt_varea_t varea = _aspace_bst_search(aspace, addr);
    void *end = addr + (npage << ARCH_PAGE_SHIFT);

    if (!varea)
    {
        LOG_W("%s: varea not exist", __func__);
        err = -RT_ENOENT;
    }
    else if (addr >= end || (rt_size_t)addr & ARCH_PAGE_MASK ||
             _not_in_range(addr, npage << ARCH_PAGE_SHIFT, varea->start,
                           varea->size))
    {
        LOG_W("%s: Unaligned parameter or out of range", __func__);
        err = -RT_EINVAL;
    }
    else
    {
        err = _do_prefetch(aspace, varea, addr, npage << ARCH_PAGE_SHIFT);
    }
    return err;
}

int rt_aspace_offload_page(rt_aspace_t aspace, void *addr, rt_size_t npage)
{
    return -RT_ENOSYS;
}

int mm_aspace_control(rt_aspace_t aspace, void *addr, enum rt_mmu_cntl cmd)
{
    int err;
    rt_varea_t varea = _aspace_bst_search(aspace, addr);
    if (varea)
    {
        err = rt_hw_mmu_control(aspace, varea->start, varea->size, cmd);
    }
    else
    {
        err = -RT_ENOENT;
    }

    return err;
}

int rt_aspace_traversal(rt_aspace_t aspace,
                        int (*fn)(rt_varea_t varea, void *arg), void *arg)
{
    rt_varea_t varea = ASPACE_VAREA_FIRST(aspace);
    while (varea)
    {
        fn(varea, arg);
        varea = ASPACE_VAREA_NEXT(varea);
    }

    return 0;
}

static int _dump(rt_varea_t varea, void *arg)
{
    if (varea->mem_obj && varea->mem_obj->get_name)
    {
        rt_kprintf("[%p - %p] %s\n", varea->start, varea->start + varea->size,
                   varea->mem_obj->get_name(varea));
    }
    else
    {
        rt_kprintf("[%p - %p] phy-map\n", varea->start, varea->start + varea->size);
        rt_kprintf("\t\\_ paddr = %p\n",  varea->offset << MM_PAGE_SHIFT);
    }
    return 0;
}

void rt_aspace_print_all(rt_aspace_t aspace)
{
    rt_aspace_traversal(aspace, _dump, NULL);
}
