/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-14     WangXiaoyao  the first version
 * 2023-08-17     Shell        Add unmap_range for MAP_PRIVATE
 *                             Support MAP_FIXED in aspace_map(), and
 *                             Add better support of permission in mmap
 */

/**
 * @brief Virtual Address Space
 */

#include <rtthread.h>

#define DBG_TAG "mm.aspace"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "avl_adpt.h"
#include "mm_private.h"

#include <mmu.h>
#include <tlb.h>

#include <stddef.h>
#include <stdint.h>

#define ALIGNED(addr) (!((rt_size_t)(addr) & ARCH_PAGE_MASK))

static void *_find_free(rt_aspace_t aspace, void *prefer, rt_size_t req_size,
                        void *limit_start, rt_size_t limit_size,
                        mm_flag_t flags);
static int _unmap_range_locked(rt_aspace_t aspace, void *addr, size_t length);

struct rt_aspace rt_kernel_space;

static int _init_lock(rt_aspace_t aspace)
{
    int err;
    MM_PGTBL_LOCK_INIT(aspace);
    err = rt_mutex_init(&aspace->bst_lock, "aspace", RT_IPC_FLAG_FIFO);

    return err;
}

rt_err_t rt_aspace_init(rt_aspace_t aspace, void *start, rt_size_t length, void *pgtbl)
{
    int err = RT_EOK;

    if (pgtbl)
    {
        aspace->page_table = pgtbl;
        aspace->start = start;
        aspace->size = length;
        aspace->private_object = RT_NULL;

        err = _aspace_bst_init(aspace);
        if (err == RT_EOK)
        {
            /**
             * It has the side effect that lock will be added to object
             * system management. So it must be paired with a detach once
             * the initialization return successfully.
             */
            err = _init_lock(aspace);
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_aspace_t rt_aspace_create(void *start, rt_size_t length, void *pgtbl)
{
    rt_aspace_t aspace = NULL;
    int err;

    RT_ASSERT(length <= 0 - (rt_size_t)start);
    aspace = (rt_aspace_t)rt_malloc(sizeof(*aspace));
    if (aspace)
    {
        rt_memset(aspace, 0, sizeof(*aspace));

        err = rt_aspace_init(aspace, start, length, pgtbl);

        if (err != RT_EOK)
        {
            LOG_W("%s(%p, %lx, %p): failed with code %d\n", __func__,
                start, length, pgtbl, err);
            rt_free(aspace);
            aspace = RT_NULL;
        }
    }
    return aspace;
}

void rt_aspace_detach(rt_aspace_t aspace)
{
    rt_varea_t varea;

    WR_LOCK(aspace);
    varea = ASPACE_VAREA_FIRST(aspace);
    while (varea)
    {
        rt_varea_t prev = varea;
        varea = ASPACE_VAREA_NEXT(varea);

        _varea_uninstall_locked(prev);
        if (VAREA_NOT_STATIC(prev))
        {
            rt_free(prev);
        }
    }
    WR_UNLOCK(aspace);

    rt_aspace_anon_ref_dec(aspace->private_object);

    rt_mutex_detach(&aspace->bst_lock);
}

void rt_aspace_delete(rt_aspace_t aspace)
{
    RT_ASSERT(aspace);
    rt_aspace_detach(aspace);
    rt_free(aspace);
}

rt_inline rt_size_t _get_effect_attr(rt_aspace_t aspace, rt_varea_t varea)
{
    rt_size_t attr = varea->attr;

    /* not write permission for user on private mapping */
    if (rt_varea_is_private_locked(varea))
        attr = rt_hw_mmu_attr_rm_perm(attr, RT_HW_MMU_PROT_USER | RT_HW_MMU_PROT_WRITE);

    return attr;
}

static int _do_named_map(rt_aspace_t aspace, rt_varea_t varea, void *vaddr,
                         rt_size_t length, rt_size_t offset, rt_size_t attr)
{
    LOG_D("%s: va %p length %p", __func__, vaddr, length);
    int err = RT_EOK;

    /* it's ensured by caller that (void*)end will not overflow */
    void *phyaddr = (void *)(offset << MM_PAGE_SHIFT);
    void *ret;

    attr = _get_effect_attr(aspace, varea);
    ret = rt_hw_mmu_map(aspace, vaddr, phyaddr, length, attr);
    if (ret == RT_NULL)
    {
        err = -RT_ERROR;
    }

    if (err == RT_EOK)
        rt_hw_tlb_invalidate_range(aspace, vaddr, length, ARCH_PAGE_SIZE);

    return err;
}

rt_inline void _do_page_fault(struct rt_aspace_fault_msg *msg, rt_size_t off,
                              void *vaddr, rt_mem_obj_t mem_obj,
                              rt_varea_t varea)
{
    msg->off = off;
    msg->fault_vaddr = vaddr;
    msg->fault_op = MM_FAULT_OP_READ;
    msg->fault_type = MM_FAULT_TYPE_PAGE_FAULT;
    msg->response.status = MM_FAULT_STATUS_UNRECOVERABLE;
    msg->response.vaddr = 0;
    msg->response.size = 0;

    RT_ASSERT(mem_obj->on_page_fault);
    mem_obj->on_page_fault(varea, msg);
}

int rt_varea_map_with_msg(rt_varea_t varea, struct rt_aspace_fault_msg *msg)
{
    rt_aspace_t aspace;
    int err = -RT_ERROR;
    if (msg->response.status == MM_FAULT_STATUS_OK)
    {
        /**
         * the page returned by handler is not checked
         * cause no much assumption can make on it
         */
        char *store = msg->response.vaddr;
        rt_size_t store_sz = msg->response.size;
        if ((char *)msg->fault_vaddr + store_sz > (char *)varea->start + varea->size)
        {
            LOG_W("%s: too much (0x%lx) of buffer on vaddr %p is provided",
                    __func__, store_sz, msg->fault_vaddr);
        }
        else
        {
            void *map;
            rt_size_t attr;
            void *v_addr = msg->fault_vaddr;
            void *p_addr = store + PV_OFFSET;

            aspace = varea->aspace;
            RT_ASSERT(aspace);

            attr = _get_effect_attr(aspace, varea);
            map = rt_hw_mmu_map(aspace, v_addr, p_addr, store_sz, attr);

            if (!map)
            {
                LOG_W("%s: MMU mapping failed for va %p to %p of %lx", __func__,
                    msg->fault_vaddr, store + PV_OFFSET, store_sz);
            }
            else
            {
                rt_hw_tlb_invalidate_range(varea->aspace, v_addr, store_sz, ARCH_PAGE_SIZE);
                err = RT_EOK;
            }
        }
    }
    else if (msg->response.status == MM_FAULT_STATUS_OK_MAPPED)
    {
        if (rt_hw_mmu_v2p(varea->aspace, msg->fault_vaddr) == ARCH_MAP_FAILED)
        {
            LOG_D("%s: no page is mapped on %p", __func__, msg->fault_vaddr);
        }
        err = RT_EOK;
    }
    else
    {
        LOG_W("%s: failed on va %p inside varea %p(%s)", __func__, msg->fault_vaddr, varea,
            varea->mem_obj->get_name ? varea->mem_obj->get_name(varea) : "unknow");
    }
    return err;
}

/* allocate memory page for mapping range */
static int _do_prefetch(rt_aspace_t aspace, rt_varea_t varea, void *start,
                        rt_size_t size)
{
    int err = RT_EOK;

    /* it's ensured by caller that start & size ara page-aligned */
    char *end = (char *)start + size;
    char *vaddr = start;
    rt_size_t off = varea->offset + ((vaddr - (char *)varea->start) >> ARCH_PAGE_SHIFT);

    while (vaddr != end)
    {
        /* TODO try to map with huge TLB, when flag & HUGEPAGE */
        struct rt_aspace_fault_msg msg;
        _do_page_fault(&msg, off, vaddr, varea->mem_obj, varea);

        if (rt_varea_map_with_msg(varea, &msg))
        {
            err = -RT_ENOMEM;
            break;
        }
        /**
         * It's hard to identify the mapping pattern on a customized handler
         * So we terminate the prefetch process on that case
         */
        if (msg.response.status == MM_FAULT_STATUS_OK_MAPPED)
            break;

        vaddr += msg.response.size;
        off += msg.response.size >> ARCH_PAGE_SHIFT;
    }

    return err;
}

static rt_err_t _expand_varea(rt_varea_t varea, void *new_va, rt_size_t size)
{
    rt_err_t error;
    rt_aspace_t aspace;
    void *old_va;

    if (varea->mem_obj && varea->mem_obj->on_varea_expand)
        error = varea->mem_obj->on_varea_expand(varea, new_va, size);
    else
        error = -RT_EPERM;

    if (error == RT_EOK)
    {
        aspace = varea->aspace;
        old_va = varea->start;
        varea->size = size;

        if (old_va != new_va)
        {
            varea->start = new_va;
            varea->offset += ((long)new_va - (long)old_va) >> MM_PAGE_SHIFT;
            _aspace_bst_remove(aspace, varea);
            _aspace_bst_insert(aspace, varea);
        }
    }
    return error;
}

struct _mapping_property {
    rt_size_t attr;
    rt_size_t flags;
    rt_size_t offset;
    struct rt_mem_obj *mem_obj;
};

#define INIT_PROP(obj,off,fl,attr)  \
    {.mem_obj = (obj),              \
    .offset = (off),                \
    .flags = (fl),                  \
    .attr = (attr),}

static rt_bool_t _contiguous_offset(rt_varea_t neighbour, rt_size_t map_size,
                                    struct _mapping_property *prop)
{
    rt_size_t n_off = neighbour->offset;
    rt_size_t map_off = prop->offset;
    return n_off < map_off ?
        n_off + (neighbour->size >> MM_PAGE_SHIFT) == map_off :
        map_off + (map_size >> MM_PAGE_SHIFT) == n_off;
}

static rt_bool_t _compatible(rt_varea_t neighbour, rt_size_t map_size,
                             struct _mapping_property *prop)
{
    return (prop->attr == neighbour->attr && prop->flags == neighbour->flag &&
            prop->mem_obj == neighbour->mem_obj &&
            _contiguous_offset(neighbour, map_size, prop));
}

rt_inline rt_err_t _migrate_and_release_varea(rt_aspace_t aspace, rt_varea_t to, rt_varea_t from,
    rt_err_t (*on_varea_merge)(struct rt_varea *to, struct rt_varea *from))
{
    rt_err_t error;
    error = on_varea_merge(to, from);
    if (error == RT_EOK)
    {
        /* uninstall operand & release the varea */
        _aspace_bst_remove(aspace, from);
        to->size += from->size;

        if (VAREA_NOT_STATIC(from))
            rt_free(from);
    }
    return error;
}

static rt_varea_t _merge_surrounding(rt_aspace_t aspace, rt_varea_t operand,
                               struct _mapping_property *prop)
{
    int again;
    rt_err_t error;
    int can_merge_fw;
    int can_merge_bw;
    rt_varea_t neighbour;
    char *operand_start;
    size_t operand_size;
    rt_err_t (*on_varea_merge)(struct rt_varea *to, struct rt_varea *from);

    if (operand->mem_obj && operand->mem_obj->on_varea_merge)
    {
        on_varea_merge = operand->mem_obj->on_varea_merge;
        do {
            operand_start = operand->start;
            operand_size = operand->size;
            LOG_D("search op_start=%p,op_size=0x%lx", operand_start, operand_size);

            /* find a compatible neighbour if any and setup direction */
            can_merge_fw = can_merge_bw = 0;
            neighbour = _aspace_bst_search(aspace, operand_start - 1);
            if (!neighbour || !_compatible(neighbour, operand_size, prop))
            {
                neighbour = _aspace_bst_search(aspace, operand_start + operand_size);
                if (neighbour && _compatible(neighbour, operand_size, prop))
                    can_merge_bw = 1;
            }
            else
                can_merge_fw = 1;

            if (can_merge_fw || can_merge_bw)
            {
                /* merge operand with its predecessor or successor */
                if (can_merge_fw)
                {
                    error = _migrate_and_release_varea(aspace, neighbour, operand, on_varea_merge);
                    operand = neighbour;
                }
                else
                    error = _migrate_and_release_varea(aspace, operand, neighbour, on_varea_merge);

                if (error == RT_EOK)
                    again = 1;
            }
            else
                again = 0;

        } while (again);
    }
    return operand;
}

/**
 * Brief: expand and merge surrounding until not possible and
 * setup the pvarea if new virt address region is installed
 */
static rt_bool_t _try_expand_and_merge_okay(rt_aspace_t aspace, rt_varea_t *pvarea,
                                             void *alloc_va, rt_mm_va_hint_t hint,
                                             struct _mapping_property *prop)
{
    int can_expand_fw;
    int can_expand_bw;
    rt_varea_t neighbour;
    rt_varea_t new_region_at = RT_NULL;
    rt_bool_t install_ok = RT_FALSE;
    char *operand_start = alloc_va;
    size_t operand_size = hint->map_size;

    /* find a compatible neighbour if any and setup direction */
    LOG_D("search op_start=%p,op_size=0x%lx", operand_start, operand_size);
    can_expand_fw = can_expand_bw = 0;
    neighbour = _aspace_bst_search(aspace, operand_start - 1);
    if (!neighbour || !_compatible(neighbour, operand_size, prop))
    {
        neighbour = _aspace_bst_search(aspace, operand_start + operand_size);
        if (neighbour && _compatible(neighbour, operand_size, prop))
            can_expand_bw = 1;
    }
    else
        can_expand_fw = 1;

    if (can_expand_fw || can_expand_bw)
    {
        /* expand varea at head or tailing */
        if (can_expand_fw)
            operand_start = neighbour->start;
        operand_size += neighbour->size;

        LOG_D("expand op_start=%p,op_size=0x%lx", operand_start, operand_size);

        if (_expand_varea(neighbour, operand_start, operand_size) == RT_EOK)
        {
            new_region_at = _merge_surrounding(aspace, neighbour, prop);
            *pvarea = new_region_at;
            install_ok = RT_TRUE;
        }
    }

    return install_ok;
}

static rt_varea_t _varea_create(void *start, rt_size_t size);

static int _insert_new_varea(rt_aspace_t aspace, rt_varea_t *pvarea,
                             void *alloc_va, rt_mm_va_hint_t hint)
{
    int err;
    rt_varea_t varea = *pvarea;
    if (varea == RT_NULL)
    {
        /* no preallocate buffer is provided, then create one */
        varea = _varea_create(hint->prefer, hint->map_size);
        hint->flags &= ~MMF_STATIC_ALLOC;
        *pvarea = varea;
    }

    if (varea)
    {
        varea->start = alloc_va;
        _aspace_bst_insert(aspace, varea);
        err = RT_EOK;
    }
    else
    {
        LOG_W("%s: Out of memory", __func__);
        err = -RT_ENOMEM;
    }

    return err;
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

    if (varea->mem_obj && varea->mem_obj->on_varea_open)
        varea->mem_obj->on_varea_open(varea);
}

/**
 * Install new virtual address region into address space
 * The pvarea will be set to the varea where new virt memory installed which can
 * be a newly created or existed one.
 *
 * Note: caller must hold the aspace lock
 */
static int _varea_install(rt_aspace_t aspace, rt_varea_t *pvarea,
                          rt_mm_va_hint_t hint, struct _mapping_property *prop,
                          void **pva)
{
    void *alloc_va;
    int err = RT_EOK;

    if (hint->flags & MMF_MAP_FIXED)
    {
        alloc_va = hint->prefer;
        err = _unmap_range_locked(aspace, alloc_va, hint->map_size);
        if (err != RT_EOK)
        {
            /* Note: MAP_FIXED must failed if unable to unmap existing mapping */
            LOG_I("%s: unmap range failed in %p with size 0x%lx, error=%d", __func__, alloc_va, hint->map_size, err);
        }
    }
    else
    {
        alloc_va =
            _find_free(aspace, hint->prefer, hint->map_size, hint->limit_start,
                       hint->limit_range_size, hint->flags);
        if (alloc_va == RT_NULL)
            err = -RT_ENOSPC;
    }

    if (alloc_va != RT_NULL)
    {
        /* TODO: fix to private mapping directly */
        if (!_try_expand_and_merge_okay(aspace, pvarea, alloc_va, hint, prop))
        {
            err = _insert_new_varea(aspace, pvarea, alloc_va, hint);

            if (err == RT_EOK)
                _varea_post_install(*pvarea, aspace, prop->attr, prop->flags,
                                    prop->mem_obj, prop->offset);
        }

        if (err == RT_EOK)
        {
            RT_ASSERT(*pvarea);
            *pva = alloc_va;
        }
    }

    return err;
}

/**
 * restore context modified by varea install
 */
void _varea_uninstall_locked(rt_varea_t varea)
{
    rt_aspace_t aspace = varea->aspace;

    if (varea->mem_obj && varea->mem_obj->on_varea_close)
        varea->mem_obj->on_varea_close(varea);
    else
    {
        rt_hw_mmu_unmap(aspace, varea->start, varea->size);
        rt_hw_tlb_invalidate_range(aspace, varea->start, varea->size, ARCH_PAGE_SIZE);
    }

    _aspace_bst_remove(aspace, varea);
}

int _mm_aspace_map(rt_aspace_t aspace, rt_varea_t *pvarea, void **addr,
                   rt_size_t length, rt_size_t attr, mm_flag_t flags,
                   rt_mem_obj_t mem_obj, rt_size_t offset)
{
    int err = RT_EOK;
    rt_varea_t varea;
    struct _mapping_property prop = INIT_PROP(mem_obj, offset, flags, attr);

    WR_LOCK(aspace);

    /**
     * @brief .prefer & .map_size are scratched from varea which setup by caller
     * .limit_start & .limit_range_size have default to be in range of aspace
     * .flags is from parameter, and will be fill in varea if install successfully
     */
    struct rt_mm_va_hint hint = {.prefer = *addr,
                                 .map_size = length,
                                 .limit_start = aspace->start,
                                 .limit_range_size = aspace->size,
                                 .flags = flags};

    if (mem_obj->hint_free)
    {
        /* mem object can control mapping range and so by modifing hint */
        mem_obj->hint_free(&hint);
    }

    /* try to allocate a virtual address region for varea */
    err = _varea_install(aspace, pvarea, &hint, &prop, addr);

    if (err == RT_EOK)
    {
        varea = *pvarea;
        if (MMF_TEST_CNTL(flags, MMF_PREFETCH))
        {
            /* do the MMU & TLB business */
            err = _do_prefetch(aspace, varea, varea->start, varea->size);
            if (err)
            {
                LOG_I("%s: failed to prefetch page into varea(%s)",
                      __func__, VAREA_NAME(varea));

                /* restore data structure and MMU */
                _varea_uninstall_locked(varea);
                if (!(varea->flag & MMF_STATIC_ALLOC))
                    rt_free(varea);
            }
        }
    }

    WR_UNLOCK(aspace);

    return err;
}

static rt_varea_t _varea_create(void *start, rt_size_t size)
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

#define _IS_OVERFLOW(start, length) ((length) > (0ul - (uintptr_t)(start)))
#define _IS_OVERSIZE(start, length, limit_s, limit_sz) (((length) + (rt_size_t)((char *)(start) - (char *)(limit_start))) > (limit_size))

static inline int _not_in_range(void *start, rt_size_t length,
                                void *limit_start, rt_size_t limit_size)
{
    /* assuming (base + length) will not overflow except (0) */
    int rc = start != RT_NULL
               ? (_IS_OVERFLOW(start, length) || start < limit_start ||
                  _IS_OVERSIZE(start, length, limit_start, limit_size))
               : length > limit_size;
    if (rc)
        LOG_D("%s: [%p : %p] [%p : %p]", __func__, start, length, limit_start, limit_size);
    return rc;
}

static inline int _not_align(void *start, rt_size_t length, rt_size_t mask)
{
    return (start != RT_NULL) &&
           (((uintptr_t)start & mask) || (length & mask));
}

/** if the flag is currently supported */
static inline int _not_support(rt_size_t flags)
{
    rt_size_t support_ops = MMF_CREATE(((__MMF_INVALID - 1) << 1) - 1, 1);
    return flags & ~(support_ops);
}

int rt_aspace_map(rt_aspace_t aspace, void **addr, rt_size_t length,
                  rt_size_t attr, mm_flag_t flags, rt_mem_obj_t mem_obj,
                  rt_size_t offset)
{
    int err;
    rt_varea_t varea = RT_NULL;

    RT_DEBUG_SCHEDULER_AVAILABLE(1);

    if (!aspace || !addr || !mem_obj || length == 0)
    {
        err = -RT_EINVAL;
        LOG_I("%s(%p, %p, %lx, %lx, %lx, %p, %lx): Invalid input",
            __func__, aspace, addr, length, attr, flags, mem_obj, offset);
    }
    else if (_not_in_range(*addr, length, aspace->start, aspace->size))
    {
        err = -RT_EINVAL;
        LOG_I("%s(addr:%p, len:%lx): out of range", __func__, *addr, length);
    }
    else if (_not_support(flags))
    {
        LOG_I("%s: no support flags 0x%lx", __func__, flags);
        err = -RT_ENOSYS;
    }
    else
    {
        RT_ASSERT((length & ARCH_PAGE_MASK) == 0);
        RT_ASSERT(((long)*addr & ARCH_PAGE_MASK) == 0);
        err = _mm_aspace_map(aspace, &varea, addr, length, attr, flags, mem_obj, offset);
    }

    if (err != RT_EOK)
    {
        *addr = NULL;
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

        /**
         * todo: fix if mapping expand, the static varea is not used at all
         */
        err = _mm_aspace_map(aspace, &varea, addr, length, attr, flags, mem_obj, offset);
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
        struct _mapping_property prop = INIT_PROP(0, pa_off, hint->flags, attr);

        WR_LOCK(aspace);
        err = _varea_install(aspace, &varea, hint, &prop, &vaddr);
        if (err == RT_EOK)
        {
            err = _do_named_map(aspace, varea, varea->start, varea->size,
                                (rt_size_t)pa_off, attr);

            if (err != RT_EOK)
            {
                _varea_uninstall_locked(varea);
            }
        }

        WR_UNLOCK(aspace);
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
            hint->flags &= ~MMF_STATIC_ALLOC;
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
        hint->flags |= (MMF_STATIC_ALLOC);
        LOG_D("%s: start %p size %p phy at %p", __func__, varea->start, varea->size, pa_off << MM_PAGE_SHIFT);
        err = _mm_aspace_map_phy(aspace, varea, hint, attr, pa_off, ret_va);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

int _aspace_unmap(rt_aspace_t aspace, void *addr)
{
    int error;
    rt_varea_t varea;

    WR_LOCK(aspace);
    varea = _aspace_bst_search(aspace, addr);

    if (varea == RT_NULL)
    {
        LOG_D("%s: No such entry found at %p\n", __func__, addr);
        error = -RT_ENOENT;
    }
    else
    {
        _varea_uninstall_locked(varea);
        if (!(varea->flag & MMF_STATIC_ALLOC))
        {
            rt_free(varea);
        }
        error = RT_EOK;
    }

    WR_UNLOCK(aspace);
    return error;
}

int rt_aspace_unmap(rt_aspace_t aspace, void *addr)
{
    int error;
    if (!aspace)
    {
        LOG_I("%s: Invalid input", __func__);
        error = -RT_EINVAL;
    }
    else if (_not_in_range(addr, 1, aspace->start, aspace->size))
    {
        LOG_I("%s: %lx not in range of aspace[%lx:%lx]", __func__, addr,
              aspace->start, (char *)aspace->start + aspace->size);
        error = -RT_EINVAL;
    }
    else
    {
        error = _aspace_unmap(aspace, addr);
    }

    return error;
}

/**
 * modify the property of existed varea by shrink its size. Mem_obj is
 * notified to released the resource.
 */
static rt_err_t _shrink_varea(rt_varea_t varea, void *new_va, rt_size_t size)
{
    rt_err_t error;
    rt_aspace_t aspace;
    void *old_va;

    if (varea->mem_obj && varea->mem_obj->on_varea_shrink)
        error = varea->mem_obj->on_varea_shrink(varea, new_va, size);
    else
        error = -RT_EPERM;

    if (error == RT_EOK)
    {
        aspace = varea->aspace;
        old_va = varea->start;
        varea->size = size;

        if (old_va != new_va)
        {
            varea->start = new_va;
            varea->offset += ((long)new_va - (long)old_va) >> MM_PAGE_SHIFT;
            _aspace_bst_remove(aspace, varea);
            _aspace_bst_insert(aspace, varea);
        }
    }
    return error;
}

static rt_err_t _split_varea(rt_varea_t existed, char *ex_end, char *unmap_start, char *unmap_end, rt_size_t unmap_len)
{
    int error;
    size_t rela_offset;
    rt_varea_t subset;
    char *subset_start;
    size_t subset_size;

    if (existed->mem_obj && existed->mem_obj->on_varea_split)
    {
        subset_start = unmap_end;
        subset_size = ex_end - subset_start;
        subset = _varea_create(subset_start, subset_size);
        if (subset)
        {
            rela_offset = MM_PA_TO_OFF(subset_start - (char *)existed->start);
            subset->aspace = existed->aspace;
            subset->attr = existed->attr;
            subset->mem_obj = existed->mem_obj;
            subset->flag = existed->flag & ~MMF_STATIC_ALLOC;
            subset->offset = existed->offset + rela_offset;

            error = existed->mem_obj->on_varea_split(existed, unmap_start, unmap_len, subset);
            if (error == RT_EOK)
            {
                existed->size = unmap_start - (char *)existed->start;
                _aspace_bst_insert(existed->aspace, subset);
            }

            if (error != RT_EOK)
                rt_free(subset);
        }
        else
            error = -RT_ENOMEM;
    }
    else
        error = -RT_EPERM;

    return error;
}

/* remove overlapped pages from varea */
static int _remove_overlapped_varea(rt_varea_t existed, char *unmap_start, rt_size_t unmap_len)
{
    int error;
    char *ex_start = existed->start;
    char *ex_end = ex_start + existed->size;
    char *unmap_end = unmap_start + unmap_len;

    if (ex_start < unmap_start)
    {
        if (ex_end > unmap_end)
            error = _split_varea(existed, ex_end, unmap_start, unmap_end, unmap_len);
        else
            error = _shrink_varea(existed, ex_start, unmap_start - ex_start);
    }
    else if (ex_end > unmap_end)
        error = _shrink_varea(existed, unmap_end, ex_end - unmap_end);
    else
    {
        _varea_uninstall_locked(existed);
        if (VAREA_NOT_STATIC(existed))
        {
            rt_free(existed);
        }
        error = RT_EOK;
    }

    return error;
}

static int _unmap_range_locked(rt_aspace_t aspace, void *addr, size_t length)
{
    int error = RT_EOK;
    rt_varea_t existed;
    struct _mm_range unmap_range;

    unmap_range.start = addr;
    unmap_range.end = addr + length - 1;

    existed = _aspace_bst_search_overlap(aspace, unmap_range);
    while (existed)
    {
        error = _remove_overlapped_varea(existed, addr, length);

        if (error == RT_EOK)
            existed = _aspace_bst_search_overlap(aspace, unmap_range);
        else
            break;
    }

    return error;
}

int rt_aspace_unmap_range(rt_aspace_t aspace, void *addr, size_t length)
{
    int error;

    if (!aspace)
    {
        LOG_I("%s: Invalid input", __func__);
        error = -RT_EINVAL;
    }
    else if (_not_in_range(addr, length, aspace->start, aspace->size))
    {
        LOG_I("%s: %lx not in range of aspace[%lx:%lx]", __func__, addr,
              aspace->start, (char *)aspace->start + aspace->size);
        error = -RT_EINVAL;
    }
    else if (!ALIGNED(addr))
    {
        LOG_I("%s(addr=%p): Unaligned address", __func__, addr);
        error = -RT_EINVAL;
    }
    else
    {
        /**
         * Brief: re-arrange the address space to remove existing pages mapping
         * in [unmap_start, unmap_start + unmap_len)
         */
        length = RT_ALIGN(length, ARCH_PAGE_SIZE);

        WR_LOCK(aspace);
        error = _unmap_range_locked(aspace, addr, length);
        WR_UNLOCK(aspace);
    }

    return error;
}

void *rt_aspace_mremap_range(rt_aspace_t aspace, void *old_address, size_t old_size,
                                size_t new_size, int flags, void *new_address)
{
    void *ret = RT_NULL;

    if (!aspace)
    {
        LOG_I("%s: Invalid input", __func__);
    }
    else if (_not_in_range(old_address, old_size, aspace->start, aspace->size))
    {
        LOG_I("%s: %lx not in range of aspace[%lx:%lx]", __func__, old_address,
              aspace->start, (char *)aspace->start + aspace->size);
    }
    else if (!ALIGNED(old_address))
    {
        LOG_I("%s(old_address=%p): Unaligned address", __func__, old_address);
    }
    else
    {
        /**
         * Brief: re-arrange the address space to remove existing pages mapping
         * in [unmap_start, unmap_start + unmap_len)
         */
        old_size = RT_ALIGN(old_size, ARCH_PAGE_SIZE);

        WR_LOCK(aspace);
        {
            rt_varea_t existed;
            struct _mm_range unmap_range;

            unmap_range.start = old_address;
            unmap_range.end = old_address + old_size - 1;

            existed = _aspace_bst_search_overlap(aspace, unmap_range);
            if (existed && existed->mem_obj && existed->mem_obj->on_varea_mremap)
            {
                ret = existed->mem_obj->on_varea_mremap(existed, new_size, flags, new_address);
            }
        }
        WR_UNLOCK(aspace);

        if (ret)
        {
            int error = rt_aspace_unmap_range(aspace, old_address, old_size);
            if (error != RT_EOK)
            {
                LOG_I("%s: unmap old failed, addr %p size %p", __func__, old_address, old_size);
            }
        }
    }

    return ret;
}

static inline void *_lower(void *a, void *b)
{
    return a < b ? a : b;
}

static inline void *_align(void *va, rt_ubase_t align_mask)
{
    return (void *)((rt_ubase_t)((char *)va + ~align_mask) & align_mask);
}

static void *_ascending_search(rt_varea_t varea, rt_size_t req_size,
                               rt_ubase_t align_mask, struct _mm_range limit)
{
    void *ret = RT_NULL;
    while (varea && varea->start < limit.end)
    {
        char *candidate = (char *)varea->start + varea->size;
        candidate = _align(candidate, align_mask);

        if (candidate > (char *)limit.end || (char *)limit.end - candidate + 1 < req_size)
            break;

        rt_varea_t nx_va = ASPACE_VAREA_NEXT(varea);
        if (nx_va)
        {
            rt_size_t gap_size =
                (char *)_lower(limit.end, (char *)nx_va->start - 1) - candidate + 1;
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
        char *candidate = _align(limit.start, align_mask);
        rt_size_t gap_size = (char *)varea->start - candidate;
        if (gap_size >= req_size)
        {
            rt_varea_t former = _aspace_bst_search(aspace, limit.start);
            if (former)
            {
                candidate = _align((char *)former->start + former->size, align_mask);
                gap_size = (char *)varea->start - candidate;

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
        char *candidate;
        rt_size_t gap_size;

        candidate = limit.start;
        candidate = _align(candidate, align_mask);
        gap_size = (char *)limit.end - candidate + 1;

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
    struct _mm_range limit = {limit_start, (char *)limit_start + limit_size - 1};

    rt_ubase_t align_mask = ~0ul;
    if (flags & MMF_REQUEST_ALIGN)
    {
        align_mask = ~((1 << MMF_GET_ALIGN(flags)) - 1);
    }

    if (prefer != RT_NULL)
    {
        /* if prefer and free, just return the prefer region */
        prefer = _align(prefer, align_mask);
        struct _mm_range range = {prefer, (char *)prefer + req_size - 1};
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
            /* search from `varea` in ascending order */
            va = _ascending_search(varea, req_size, align_mask, limit);
            if (va == RT_NULL)
            {
                /* rewind to first range */
                limit.end = (char *)varea->start - 1;
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
    rt_varea_t varea;
    char *end = (char *)addr + (npage << ARCH_PAGE_SHIFT);

    WR_LOCK(aspace);
    varea = _aspace_bst_search(aspace, addr);
    WR_UNLOCK(aspace);

    if (!varea)
    {
        LOG_W("%s: varea not exist", __func__);
        err = -RT_ENOENT;
    }
    else if ((char *)addr >= end || (rt_size_t)addr & ARCH_PAGE_MASK ||
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

int rt_varea_map_page(rt_varea_t varea, void *vaddr, void *page)
{
    int err = RT_EOK;
    void *page_pa = rt_kmem_v2p(page);

    if (!varea || !vaddr || !page)
    {
        LOG_W("%s(%p,%p,%p): invalid input", __func__, varea, vaddr, page);
        err = -RT_EINVAL;
    }
    else if (page_pa == ARCH_MAP_FAILED)
    {
        LOG_W("%s: page is not in kernel space", __func__);
        err = -RT_ERROR;
    }
    else if (_not_in_range(vaddr, ARCH_PAGE_SIZE, varea->start, varea->size))
    {
        LOG_W("%s(%p,%lx): not in range of varea(%p,%lx)", __func__,
            vaddr, ARCH_PAGE_SIZE, varea->start, varea->size);
        err = -RT_EINVAL;
    }
    else
    {
        err = _do_named_map(
            varea->aspace,
            varea,
            vaddr,
            ARCH_PAGE_SIZE,
            MM_PA_TO_OFF(page_pa),
            varea->attr
        );
    }

    return err;
}

int rt_varea_unmap_page(rt_varea_t varea, void *vaddr)
{
    void *va_aligned = (void *)RT_ALIGN_DOWN((rt_base_t)vaddr, ARCH_PAGE_SIZE);
    return rt_varea_unmap_range(varea, va_aligned, ARCH_PAGE_SIZE);
}

/**
 * @note Caller should take care of synchronization of its varea among all the map/unmap operation
 */
int rt_varea_map_range(rt_varea_t varea, void *vaddr, void *paddr, rt_size_t length)
{
    int err;
    if (!varea || !vaddr || !paddr || !length ||
        !ALIGNED(vaddr) || !ALIGNED(paddr) || !(ALIGNED(length)))
    {
        LOG_W("%s(%p,%p,%p,%lx): invalid input", __func__, varea, vaddr, paddr, length);
        err = -RT_EINVAL;
    }
    else if (_not_in_range(vaddr, length, varea->start, varea->size))
    {
        LOG_W("%s(%p,%lx): not in range of varea(%p,%lx)", __func__,
            vaddr, length, varea->start, varea->size);
        err = -RT_EINVAL;
    }
    else
    {
        err = _do_named_map(
            varea->aspace,
            varea,
            vaddr,
            length,
            MM_PA_TO_OFF(paddr),
            varea->attr
        );
    }
    return err;
}

/**
 * @note Caller should take care of synchronization of its varea among all the map/unmap operation
 */
int rt_varea_unmap_range(rt_varea_t varea, void *vaddr, rt_size_t length)
{
    int err;
    rt_base_t va_align;

    if (!varea || !vaddr || !length)
    {
        LOG_W("%s(%p,%p,%lx): invalid input", __func__, varea, vaddr, length);
        err = -RT_EINVAL;
    }
    else if (_not_in_range(vaddr, length, varea->start, varea->size))
    {
        LOG_W("%s(%p,%lx): not in range of varea(%p,%lx)", __func__,
            vaddr, length, varea->start, varea->size);
        err = -RT_EINVAL;
    }
    else
    {
        va_align = RT_ALIGN_DOWN((rt_base_t)vaddr, ARCH_PAGE_SIZE);
        rt_hw_mmu_unmap(varea->aspace, (void *)va_align, length);
        rt_hw_tlb_invalidate_range(varea->aspace, (void *)va_align, length, ARCH_PAGE_SIZE);
        err = RT_EOK;
    }
    return err;
}

int rt_aspace_offload_page(rt_aspace_t aspace, void *addr, rt_size_t npage)
{
    return -RT_ENOSYS;
}

int rt_aspace_control(rt_aspace_t aspace, void *addr, enum rt_mmu_cntl cmd)
{
    int err;
    rt_varea_t varea;

    WR_LOCK(aspace);
    varea = _aspace_bst_search(aspace, addr);
    WR_UNLOCK(aspace);

    if (varea)
    {
        err = rt_hw_mmu_control(aspace, varea->start, varea->size, cmd);
        if (err == RT_EOK)
        {
            rt_hw_tlb_invalidate_range(aspace, varea->start, varea->size, ARCH_PAGE_SIZE);
        }
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
    rt_varea_t varea;
    rt_varea_t next;
    WR_LOCK(aspace);
    varea = ASPACE_VAREA_FIRST(aspace);
    while (varea)
    {
        next = ASPACE_VAREA_NEXT(varea);
        fn(varea, arg);
        varea = next;
    }
    WR_UNLOCK(aspace);

    return 0;
}

static int _dump(rt_varea_t varea, void *arg)
{
    if (varea->mem_obj && varea->mem_obj->get_name)
    {
        rt_kprintf("[%p - %p] %s\n", varea->start, (char *)varea->start + varea->size,
                   varea->mem_obj->get_name(varea));
    }
    else
    {
        rt_kprintf("[%p - %p] phy-map\n", varea->start, (char *)varea->start + varea->size);
        rt_kprintf("\t\\_ paddr = %p\n",  varea->offset << MM_PAGE_SHIFT);
    }
    return 0;
}

void rt_aspace_print_all(rt_aspace_t aspace)
{
    rt_aspace_traversal(aspace, _dump, NULL);
}

static int _count_vsz(rt_varea_t varea, void *arg)
{
    rt_base_t *pvsz = arg;
    RT_ASSERT(varea);
    *pvsz = *pvsz + varea->size;
    return 0;
}

rt_base_t rt_aspace_count_vsz(rt_aspace_t aspace)
{
    rt_base_t vsz = 0;
    rt_aspace_traversal(aspace, _count_vsz, &vsz);
    return vsz;
}

static int _dup_varea(rt_varea_t src_varea, void *arg)
{
    int err;
    rt_aspace_t dst = arg;
    rt_aspace_t src = src_varea->aspace;

    void *pa = RT_NULL;
    void *va = RT_NULL;
    rt_mem_obj_t mem_obj = src_varea->mem_obj;

    if (!mem_obj)
    {
        /* duplicate a physical mapping */
        pa = rt_hw_mmu_v2p(src, (void *)src_varea->start);
        RT_ASSERT(pa != ARCH_MAP_FAILED);
        struct rt_mm_va_hint hint = {.flags = src_varea->flag,
                                     .limit_range_size = dst->size,
                                     .limit_start = dst->start,
                                     .prefer = src_varea->start,
                                     .map_size = src_varea->size};
        err = rt_aspace_map_phy(dst, &hint, src_varea->attr,
                                MM_PA_TO_OFF(pa), &va);
        if (err != RT_EOK)
        {
            LOG_W("%s: aspace map failed at %p with size %p", __func__,
                  src_varea->start, src_varea->size);
        }
    }
    else
    {
        /* duplicate a mem_obj backing mapping */
        rt_base_t flags = src_varea->flag | MMF_MAP_FIXED;
        flags &= ~MMF_STATIC_ALLOC;
        flags &= ~MMF_PREFETCH;
        va = src_varea->start;

        err = rt_aspace_map(dst, &va, src_varea->size, src_varea->attr,
                            flags, mem_obj, src_varea->offset);
        if (err != RT_EOK)
        {
            LOG_W("%s: aspace map failed at %p with size %p", __func__,
                  src_varea->start, src_varea->size);
        }
    }

    if (va != (void *)src_varea->start)
    {
        return -1;
    }
    return 0;
}

struct _compare_param {
    rt_aspace_t dst;
    int rc;
};

rt_err_t rt_aspace_duplicate_locked(rt_aspace_t src, rt_aspace_t dst)
{
    return rt_aspace_traversal(src, _dup_varea, dst);
}

rt_inline int _varea_same(rt_varea_t a, rt_varea_t b)
{
    return a->attr == b->attr && a->flag == b->flag && a->mem_obj == b->mem_obj;
}

rt_inline void _dump_varea(rt_varea_t varea)
{
    LOG_W("%s(attr=0x%lx, flags=0x%lx, start=0x%lx, size=0x%lx, mem_obj=%p)", VAREA_NAME(varea), varea->attr, varea->flag, varea->start, varea->size, varea->mem_obj);
}

static int _compare_varea(rt_varea_t src_varea, void *arg)
{
    struct _compare_param *param = arg;
    rt_varea_t dst_varea;
    rt_aspace_t dst = param->dst;
    rt_aspace_t src = src_varea->aspace;

    dst_varea = _aspace_bst_search(dst, src_varea->start);
    if (dst_varea)
    {
        char *buf1 = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
        char *buf2 = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
        char *vend = src_varea->start + src_varea->size;
        for (char *i = src_varea->start; i < vend; i += ARCH_PAGE_SIZE)
        {
            int rc;
            rt_aspace_page_get(src, i, buf1);
            rt_aspace_page_get(dst, i, buf2);
            rc = memcmp(buf1, buf2, ARCH_PAGE_SIZE);
            if (rc)
            {
                if (param->rc == 0)
                    param->rc = rc;
                LOG_E("%s(a_varea=%s, b_varea=%s)", __func__, VAREA_NAME(src_varea), VAREA_NAME(dst_varea));
                _dump_varea(src_varea);
                _dump_varea(dst_varea);
                RT_ASSERT(0);
            }
        }

        rt_pages_free(buf1, 0);
        rt_pages_free(buf2, 0);
    }
    else
    {
        param->rc = -RT_ENOENT;
    }

    return 0;
}

rt_err_t rt_aspace_compare(rt_aspace_t src, rt_aspace_t dst)
{
    struct _compare_param param = {.rc = 0, .dst = dst};
    rt_aspace_traversal(src, _compare_varea, &param);
    return param.rc;
}

/* dst are page aligned */
rt_inline rt_err_t _page_put(rt_varea_t varea, void *page_va, void *buffer)
{
    struct rt_aspace_io_msg iomsg;
    rt_err_t rc;

    rt_mm_io_msg_init(&iomsg, VAREA_VA_TO_OFFSET(varea, page_va), page_va, buffer);
    varea->mem_obj->page_write(varea, &iomsg);

    if (iomsg.response.status == MM_FAULT_STATUS_UNRECOVERABLE)
        rc = -RT_ERROR;
    else
        rc = RT_EOK;
    return rc;
}

/* dst are page aligned */
rt_inline rt_err_t _page_get(rt_varea_t varea, void *page_va, void *buffer)
{
    struct rt_aspace_io_msg iomsg;
    rt_err_t rc;

    rt_mm_io_msg_init(&iomsg, VAREA_VA_TO_OFFSET(varea, page_va), page_va, buffer);
    varea->mem_obj->page_read(varea, &iomsg);

    if (iomsg.response.status == MM_FAULT_STATUS_UNRECOVERABLE)
        rc = -RT_ERROR;
    else
        rc = RT_EOK;
    return rc;
}

#ifdef RT_USING_SMART
#include "lwp.h"
rt_inline rt_aspace_t _current_uspace(void)
{
    rt_lwp_t this_proc = lwp_self();
    return this_proc ? this_proc->aspace : RT_NULL;
}
#else
rt_inline rt_aspace_t _current_uspace(void)
{
    return RT_NULL;
}
#endif

rt_err_t rt_aspace_page_get_phy(rt_aspace_t aspace, void *page_va, void *buffer)
{
    rt_err_t rc = -RT_ERROR;

    char *frame_ka = rt_hw_mmu_v2p(aspace, page_va);
    if (frame_ka != ARCH_MAP_FAILED)
    {
        frame_ka = rt_kmem_p2v(frame_ka);
        if (frame_ka)
        {
            rt_memcpy(buffer, frame_ka, ARCH_PAGE_SIZE);
            rc = RT_EOK;
        }
        else if (aspace == _current_uspace() || aspace == &rt_kernel_space)
        {
            /* direct IO */
            rt_memcpy(buffer, page_va, ARCH_PAGE_SIZE);
            rc = RT_EOK;
        }
        else
        {
            /* user memory region remap ? */
            LOG_W("%s(aspace=0x%lx,va=%p): Operation not support",
                __func__, aspace, page_va);
            rc = -RT_ENOSYS;
        }
    }
    else
    {
        LOG_W("%s(aspace=0x%lx,va=%p): PTE not existed",
            __func__, aspace, page_va);
        rc = -RT_ENOENT;
    }
    return rc;
}

rt_err_t rt_aspace_page_put_phy(rt_aspace_t aspace, void *page_va, void *buffer)
{
    rt_err_t rc = -RT_ERROR;

    char *frame_ka = rt_hw_mmu_v2p(aspace, page_va);
    if (frame_ka != ARCH_MAP_FAILED)
    {
        frame_ka = rt_kmem_p2v(frame_ka);
        if (frame_ka)
        {
            rt_memcpy(frame_ka, buffer, ARCH_PAGE_SIZE);
            rc = RT_EOK;
        }
        else if (aspace == _current_uspace() || aspace == &rt_kernel_space)
        {
            /* direct IO */
            rt_memcpy(page_va, buffer, ARCH_PAGE_SIZE);
            rc = RT_EOK;
        }
        else
        {
            /* user memory region remap ? */
            LOG_W("%s(aspace=0x%lx,va=%p): Operation not support",
                __func__, aspace, page_va);
            rc = -RT_ENOSYS;
        }
    }
    else
    {
        LOG_W("%s(aspace=0x%lx,va=%p): PTE not existed",
            __func__, aspace, page_va);
        rc = -RT_ENOENT;
    }

    return rc;
}

rt_err_t rt_aspace_page_put(rt_aspace_t aspace, void *page_va, void *buffer)
{
    rt_err_t rc = -RT_ERROR;
    rt_varea_t varea;

    RT_ASSERT(aspace);
    RD_LOCK(aspace);
    varea = _aspace_bst_search(aspace, page_va);
    if (varea && ALIGNED(page_va))
    {
        if (varea->mem_obj)
        {
            if (varea->mem_obj->page_write)
            {
                if (rt_varea_is_private_locked(varea))
                {
                    RDWR_LOCK(aspace);
                    struct rt_aspace_fault_msg msg;
                    msg.fault_op = MM_FAULT_OP_WRITE;
                    msg.fault_type = MM_FAULT_TYPE_ACCESS_FAULT;
                    msg.fault_vaddr = page_va;
                    rc = rt_varea_fix_private_locked(varea, rt_hw_mmu_v2p(aspace, page_va),
                                                    &msg, RT_TRUE);
                    RDWR_UNLOCK(aspace);
                    if (rc == MM_FAULT_FIXABLE_TRUE)
                    {
                        varea = _aspace_bst_search(aspace, page_va);
                        rc = _page_put(varea, page_va, buffer);
                    }
                    else
                        rc = -RT_ERROR;
                }
                else
                    rc = _page_put(varea, page_va, buffer);
            }
            else
            {
                rc = -RT_EINVAL;
                LOG_I("%s: Operation not allowed", __func__);
            }
        }
        else
        {
            rc = rt_aspace_page_put_phy(aspace, page_va, buffer);
        }
    }
    else
        rc = -RT_EINVAL;
    RD_UNLOCK(aspace);

    return rc;
}

rt_err_t rt_aspace_page_get(rt_aspace_t aspace, void *page_va, void *buffer)
{
    rt_err_t rc = -RT_ERROR;
    rt_varea_t varea;

    /* TODO: cache the last search item */
    RT_ASSERT(aspace);
    RD_LOCK(aspace);
    varea = _aspace_bst_search(aspace, page_va);
    if (varea && ALIGNED(page_va))
    {
        if (varea->mem_obj)
        {
            if (varea->mem_obj->page_read)
            {
                rc = _page_get(varea, page_va, buffer);
            }
            else
            {
                LOG_I("%s: Operation not allowed", __func__);
            }
        }
        else
        {
            rc = rt_aspace_page_get_phy(aspace, page_va, buffer);
        }
    }
    else
    {
        rc = -RT_EINVAL;
        LOG_D("%s(va=%p,varea=0x%lx): Invalid address",
            __func__, page_va, varea);
    }
    RD_UNLOCK(aspace);

    return rc;
}

rt_varea_t rt_aspace_query(rt_aspace_t aspace, void *vaddr)
{
    return _aspace_bst_search(aspace, vaddr);
}
