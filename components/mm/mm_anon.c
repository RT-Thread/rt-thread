/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-19     Shell        Support PRIVATE mapping and COW
 */

#define DBG_TAG "mm.anon"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <string.h>
#include "mm_private.h"
#include <mmu.h>

/**
 * Anonymous Object directly represent the mappings without backup files in the
 * aspace. Their only backup is in the aspace->pgtbl.
 */

typedef struct rt_private_ctx {
    struct rt_mem_obj mem_obj;
    rt_aspace_t backup_aspace;
    /* both varea and aspace can holds a reference */
    rt_atomic_t reference;
    /* readonly `private` is shared object */
    long readonly;
} *rt_private_ctx_t;

rt_inline rt_aspace_t _anon_obj_get_backup(rt_mem_obj_t mobj)
{
    rt_private_ctx_t pctx;
    rt_aspace_t backup;
    pctx = rt_container_of(mobj, struct rt_private_ctx, mem_obj);
    backup = pctx->backup_aspace;
    return backup;
}

rt_inline rt_atomic_t *_anon_obj_get_reference(rt_mem_obj_t mobj)
{
    rt_private_ctx_t pctx;
    pctx = rt_container_of(mobj, struct rt_private_ctx, mem_obj);
    return &pctx->reference;
}

rt_inline rt_private_ctx_t _anon_mobj_to_pctx(rt_mem_obj_t mobj)
{
    return rt_container_of(mobj, struct rt_private_ctx, mem_obj);
}

static long rt_aspace_anon_ref_inc(rt_mem_obj_t aobj)
{
    long rc;
    if (aobj)
    {
        rc = rt_atomic_add(_anon_obj_get_reference(aobj), 1);
        LOG_D("%s(aobj=%p) Cur %ld", __func__, aobj, rc + 1);
    }
    else
        rc = -1;
    return rc;
}

rt_err_t rt_aspace_anon_ref_dec(rt_mem_obj_t aobj)
{
    rt_err_t rc;
    rt_aspace_t aspace;
    rt_private_ctx_t pctx;
    long former_reference;

    if (aobj)
    {
        pctx = _anon_mobj_to_pctx(aobj);
        RT_ASSERT(pctx);

        former_reference = rt_atomic_add(_anon_obj_get_reference(aobj), -1);
        LOG_D("%s(aobj=%p) Cur %ld", __func__, aobj, former_reference - 1);
        if (pctx->readonly)
        {
            if (former_reference - 1 <= pctx->readonly)
            {
                void *pgtbl;
                RT_ASSERT(former_reference - 1 == pctx->readonly);
                aspace = _anon_obj_get_backup(aobj);

                pctx->readonly = 0;
                pgtbl = aspace->page_table;
                rt_aspace_delete(aspace);
                rt_hw_mmu_pgtbl_delete(pgtbl);
            }
        }
        else if (former_reference < 2)
        {
            aspace = _anon_obj_get_backup(aobj);
            aspace->private_object = RT_NULL;

            rt_free(pctx);
        }
        rc = RT_EOK;
    }
    else
    {
        rc = -RT_EINVAL;
    }

    return rc;
}

static const char *_anon_get_name(rt_varea_t varea)
{
    return varea->aspace == _anon_obj_get_backup(varea->mem_obj) ? "anonymous" : "reference";
}

static void _anon_varea_open(struct rt_varea *varea)
{
    rt_aspace_anon_ref_inc(varea->mem_obj);

    if (varea->aspace == _anon_obj_get_backup(varea->mem_obj))
        varea->offset = MM_PA_TO_OFF(varea->start);

    varea->data = NULL;
}

static void _anon_varea_close(struct rt_varea *varea)
{
    rt_aspace_anon_ref_dec(varea->mem_obj);
    rt_mm_dummy_mapper.on_varea_close(varea);
}

static rt_err_t _anon_varea_expand(struct rt_varea *varea, void *new_vaddr, rt_size_t size)
{
    return RT_EOK;
}

static rt_err_t _anon_varea_shrink(rt_varea_t varea, void *new_start, rt_size_t size)
{
    return rt_mm_dummy_mapper.on_varea_shrink(varea, new_start, size);
}

static rt_err_t _anon_varea_split(struct rt_varea *existed, void *unmap_start, rt_size_t unmap_len, struct rt_varea *subset)
{
    _anon_varea_open(subset);
    return rt_mm_dummy_mapper.on_varea_split(existed, unmap_start, unmap_len, subset);
}

static rt_err_t _anon_varea_merge(struct rt_varea *merge_to, struct rt_varea *merge_from)
{
    _anon_varea_close(merge_from);
    return rt_mm_dummy_mapper.on_varea_merge(merge_to, merge_from);
}

rt_inline void _map_page_in_varea(rt_aspace_t asapce, rt_varea_t varea,
                                  struct rt_aspace_fault_msg *msg, char *fault_addr)
{
    char *page_va = msg->response.vaddr;
    if (rt_varea_map_page(varea, fault_addr, page_va) == RT_EOK)
    {
        msg->response.status = MM_FAULT_STATUS_OK_MAPPED;
        rt_varea_pgmgr_insert(varea, page_va);
    }
    else
    {
        msg->response.status = MM_FAULT_STATUS_UNRECOVERABLE;
        LOG_W("%s: failed to map page into varea", __func__);
    }
}

static void *_get_page_from_backup(rt_aspace_t backup, rt_base_t offset_in_mobj)
{
    void *frame_pa;
    char *backup_addr;
    rt_varea_t backup_varea;
    void *rc = RT_NULL;

    backup_addr = (char *)(offset_in_mobj << MM_PAGE_SHIFT);
    backup_varea = rt_aspace_query(backup, backup_addr);

    if (backup_varea)
    {
        /* synchronize between multiple request by aspace lock of backup */
        WR_LOCK(backup);

        frame_pa = rt_hw_mmu_v2p(backup, backup_addr);
        if (frame_pa == ARCH_MAP_FAILED)
        {
            /* provide the page in backup varea */
            struct rt_aspace_fault_msg msg;
            msg.fault_op = MM_FAULT_OP_WRITE;
            msg.fault_type = MM_FAULT_TYPE_PAGE_FAULT;
            msg.fault_vaddr = backup_addr;
            msg.off = offset_in_mobj;
            rt_mm_fault_res_init(&msg.response);

            rt_mm_dummy_mapper.on_page_fault(backup_varea, &msg);
            if (msg.response.status != MM_FAULT_STATUS_UNRECOVERABLE)
            {
                _map_page_in_varea(backup, backup_varea, &msg, backup_addr);
                if (msg.response.status == MM_FAULT_STATUS_OK_MAPPED)
                {
                    rc = msg.response.vaddr;
                }
                rt_pages_free(msg.response.vaddr, 0);
            }
        }
        else
        {
            rc = rt_kmem_p2v(frame_pa);
            if (!rc)
                RT_ASSERT(0 && "No kernel address of target page frame");
        }
        WR_UNLOCK(backup);
    }
    else
    {
        /* out of range error */
        LOG_E("(backup_addr=%p): Page request out of range", backup_addr);
    }

    return rc;
}

/* get the backup page in kernel for the address in user space */
static void _fetch_page_for_varea(struct rt_varea *varea, struct rt_aspace_fault_msg *msg, rt_bool_t need_map)
{
    void *paddr;
    char *frame_ka;
    rt_aspace_t curr_aspace = varea->aspace;
    rt_aspace_t backup = _anon_obj_get_backup(varea->mem_obj);

    RDWR_LOCK(curr_aspace);

    /**
     * if the page is already mapped(this may caused by data race while other
     * thread success to take the lock and mapped the page before this), return okay
     */
    paddr = rt_hw_mmu_v2p(curr_aspace, msg->fault_vaddr);
    if (paddr == ARCH_MAP_FAILED)
    {
        if (backup == curr_aspace)
        {
            rt_mm_dummy_mapper.on_page_fault(varea, msg);
            if (msg->response.status != MM_FAULT_STATUS_UNRECOVERABLE)
            {
                /* if backup == curr_aspace, a page fetch always binding with a pte filling */
                _map_page_in_varea(backup, varea, msg, msg->fault_vaddr);
                if (msg->response.status != MM_FAULT_STATUS_UNRECOVERABLE)
                {
                    rt_pages_free(msg->response.vaddr, 0);
                }
            }
        }
        else
        {
            frame_ka = _get_page_from_backup(backup, msg->off);
            if (frame_ka)
            {
                msg->response.vaddr = frame_ka;
                msg->response.size = ARCH_PAGE_SIZE;
                if (!need_map)
                {
                    msg->response.status = MM_FAULT_STATUS_OK;
                }
                else
                {
                    _map_page_in_varea(curr_aspace, varea, msg, msg->fault_vaddr);
                }
            }
        }
    }
    else
    {
        msg->response.status = MM_FAULT_STATUS_OK_MAPPED;
    }
    RDWR_UNLOCK(curr_aspace);
}

static void _anon_page_fault(struct rt_varea *varea, struct rt_aspace_fault_msg *msg)
{
    _fetch_page_for_varea(varea, msg, RT_TRUE);
}

static void read_by_mte(rt_aspace_t aspace, struct rt_aspace_io_msg *iomsg)
{
    if (rt_aspace_page_get_phy(aspace, iomsg->fault_vaddr, iomsg->buffer_vaddr) == RT_EOK)
        iomsg->response.status = MM_FAULT_STATUS_OK;
}

static void _anon_page_read(struct rt_varea *varea, struct rt_aspace_io_msg *iomsg)
{
    rt_aspace_t curr_aspace = varea->aspace;
    rt_aspace_t backup = _anon_obj_get_backup(varea->mem_obj);

    if (rt_hw_mmu_v2p(curr_aspace, iomsg->fault_vaddr) == ARCH_MAP_FAILED)
    {
        struct rt_aspace_fault_msg msg;
        msg.fault_op = MM_FAULT_OP_READ;
        msg.fault_type = MM_FAULT_TYPE_PAGE_FAULT;
        msg.fault_vaddr = iomsg->fault_vaddr;
        msg.off = iomsg->off;
        rt_mm_fault_res_init(&msg.response);

        _fetch_page_for_varea(varea, &msg, RT_FALSE);
        if (msg.response.status != MM_FAULT_STATUS_UNRECOVERABLE)
        {
            void *saved_fault_va = iomsg->fault_vaddr;
            iomsg->fault_vaddr = (void *)(iomsg->off << MM_PAGE_SHIFT);
            read_by_mte(backup, iomsg);
            iomsg->fault_vaddr = saved_fault_va;
        }
    }
    else
    {
        read_by_mte(curr_aspace, iomsg);
    }
}

static void write_by_mte(rt_aspace_t aspace, struct rt_aspace_io_msg *iomsg)
{
    if (rt_aspace_page_put_phy(aspace, iomsg->fault_vaddr, iomsg->buffer_vaddr) == RT_EOK)
        iomsg->response.status = MM_FAULT_STATUS_OK;
}

static void _anon_page_write(struct rt_varea *varea, struct rt_aspace_io_msg *iomsg)
{
    rt_aspace_t from_aspace = varea->aspace;
    rt_aspace_t backup = _anon_obj_get_backup(varea->mem_obj);

    if (from_aspace != backup)
    {
        /* varea in guest aspace cannot modify the page */
        iomsg->response.status = MM_FAULT_STATUS_UNRECOVERABLE;
    }
    else if (rt_hw_mmu_v2p(from_aspace, iomsg->fault_vaddr) == ARCH_MAP_FAILED)
    {
        struct rt_aspace_fault_msg msg;
        msg.fault_op = MM_FAULT_OP_WRITE;
        msg.fault_type = MM_FAULT_TYPE_PAGE_FAULT;
        msg.fault_vaddr = iomsg->fault_vaddr;
        msg.off = iomsg->off;
        rt_mm_fault_res_init(&msg.response);

        _fetch_page_for_varea(varea, &msg, RT_TRUE);
        if (msg.response.status == MM_FAULT_STATUS_OK_MAPPED)
        {
            write_by_mte(backup, iomsg);
        }
        else
        {
            /* mapping failed, report an error */
            iomsg->response.status = MM_FAULT_STATUS_UNRECOVERABLE;
        }
    }
    else
    {
        write_by_mte(backup, iomsg);
    }
}

static struct rt_private_ctx _priv_obj = {
    .mem_obj.get_name = _anon_get_name,
    .mem_obj.on_page_fault = _anon_page_fault,
    .mem_obj.hint_free = NULL,
    .mem_obj.on_varea_open = _anon_varea_open,
    .mem_obj.on_varea_close = _anon_varea_close,
    .mem_obj.on_varea_shrink = _anon_varea_shrink,
    .mem_obj.on_varea_split = _anon_varea_split,
    .mem_obj.on_varea_expand = _anon_varea_expand,
    .mem_obj.on_varea_merge = _anon_varea_merge,
    .mem_obj.page_read = _anon_page_read,
    .mem_obj.page_write = _anon_page_write,
};

rt_inline rt_private_ctx_t rt_private_obj_create_n_bind(rt_aspace_t aspace)
{
    rt_private_ctx_t private_object;
    private_object = rt_malloc(sizeof(struct rt_private_ctx));
    if (private_object)
    {
        memcpy(&private_object->mem_obj, &_priv_obj, sizeof(_priv_obj));

        /* hold a init ref from backup aspace */
        rt_atomic_store(&private_object->reference, 1);

        private_object->readonly = RT_FALSE;
        private_object->backup_aspace = aspace;
        aspace->private_object = &private_object->mem_obj;
    }

    return private_object;
}

rt_inline rt_mem_obj_t _get_private_obj(rt_aspace_t aspace)
{
    rt_private_ctx_t priv;
    rt_mem_obj_t rc;
    rc = aspace->private_object;
    if (!aspace->private_object)
    {
        priv = rt_private_obj_create_n_bind(aspace);
        if (priv)
        {
            rc = &priv->mem_obj;
            aspace->private_object = rc;
        }
    }
    return rc;
}

static int _override_map(rt_varea_t varea, rt_aspace_t aspace, void *fault_vaddr, struct rt_aspace_fault_msg *msg, void *page)
{
    int rc = MM_FAULT_FIXABLE_FALSE;
    rt_mem_obj_t private_object;
    rt_varea_t map_varea = RT_NULL;
    rt_err_t error;
    rt_size_t flags;
    rt_size_t attr;

    LOG_D("%s", __func__);

    private_object = _get_private_obj(aspace);

    if (private_object)
    {
        flags = varea->flag | MMF_MAP_FIXED;
        /* don't prefetch and do it latter */
        flags &= ~MMF_PREFETCH;
        attr = rt_hw_mmu_attr_add_perm(varea->attr, RT_HW_MMU_PROT_USER | RT_HW_MMU_PROT_WRITE);

        /* override existing mapping at fault_vaddr */
        error = _mm_aspace_map(
            aspace, &map_varea, &fault_vaddr, ARCH_PAGE_SIZE, attr,
            flags, private_object, MM_PA_TO_OFF(fault_vaddr));

        if (error == RT_EOK)
        {
            msg->response.status = MM_FAULT_STATUS_OK;
            msg->response.vaddr = page;
            msg->response.size = ARCH_PAGE_SIZE;
            if (rt_varea_map_with_msg(map_varea, msg) != RT_EOK)
            {
                LOG_E("%s: fault_va=%p,(priv_va=%p,priv_sz=0x%lx) at %s", __func__, msg->fault_vaddr, map_varea->start, map_varea->size, VAREA_NAME(map_varea));
                RT_ASSERT(0 && "should never failed");
            }
            RT_ASSERT(rt_hw_mmu_v2p(aspace, msg->fault_vaddr) == (page + PV_OFFSET));
            rc = MM_FAULT_FIXABLE_TRUE;
            rt_varea_pgmgr_insert(map_varea, page);
            rt_pages_free(page, 0);
        }
        else
        {
            /* private object will be release on destruction of aspace */
            rt_free(map_varea);
        }
    }
    else
    {
        LOG_I("%s: out of memory", __func__);
        rc = MM_FAULT_FIXABLE_FALSE;
    }

    return rc;
}

/**
 * replace an existing mapping to a private one, this is identical to:
 * => aspace_unmap(ex_varea, )
 * => aspace_map()
 */
int rt_varea_fix_private_locked(rt_varea_t ex_varea, void *pa,
                                struct rt_aspace_fault_msg *msg,
                                rt_bool_t dont_copy)
{
    /**
     * todo: READ -> WRITE lock here
     */
    void *page;
    void *fault_vaddr;
    rt_aspace_t aspace;
    rt_mem_obj_t ex_obj;
    int rc = MM_FAULT_FIXABLE_FALSE;
    ex_obj = ex_varea->mem_obj;

    if (ex_obj)
    {
        fault_vaddr = msg->fault_vaddr;
        aspace = ex_varea->aspace;
        RT_ASSERT(!!aspace);

        /**
         * todo: what if multiple pages are required?
         */
        if (aspace->private_object == ex_obj)
        {
            RT_ASSERT(0 && "recursion");
        }
        else if (ex_obj->page_read)
        {
            page = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
            if (page)
            {
                /** setup message & fetch the data from source object */
                if (!dont_copy)
                {
                    struct rt_aspace_io_msg io_msg;
                    rt_mm_io_msg_init(&io_msg, msg->off, msg->fault_vaddr, page);
                    ex_obj->page_read(ex_varea, &io_msg);
                    /**
                     * Note: if ex_obj have mapped into varea, it's still okay since
                     * we will override it latter
                     */
                    if (io_msg.response.status != MM_FAULT_STATUS_UNRECOVERABLE)
                    {
                        rc = _override_map(ex_varea, aspace, fault_vaddr, msg, page);
                    }
                    else
                    {
                        rt_pages_free(page, 0);
                        LOG_I("%s: page read(va=%p) fault from %s(start=%p,size=%p)", __func__,
                            msg->fault_vaddr, VAREA_NAME(ex_varea), ex_varea->start, ex_varea->size);
                    }
                }
                else
                {
                    rc = _override_map(ex_varea, aspace, fault_vaddr, msg, page);
                }
            }
            else
            {
                LOG_I("%s: pages allocation failed", __func__);
            }
        }
        else
        {
            LOG_I("%s: no page read method provided from %s", __func__, VAREA_NAME(ex_varea));
        }
    }
    else
    {
        LOG_I("%s: unavailable memory object", __func__);
    }

    return rc;
}

int rt_aspace_map_private(rt_aspace_t aspace, void **addr, rt_size_t length,
                          rt_size_t attr, mm_flag_t flags)
{
    int rc;
    rt_mem_obj_t priv_obj;

    if (flags & MMF_STATIC_ALLOC)
    {
        rc = -RT_EINVAL;
    }
    else
    {
        priv_obj = _get_private_obj(aspace);
        if (priv_obj)
        {
            flags |= MMF_MAP_PRIVATE;
            flags &= ~MMF_PREFETCH;
            rc = rt_aspace_map(aspace, addr, length, attr, flags, priv_obj, 0);
        }
        else
        {
            rc = -RT_ENOMEM;
        }
    }
    return rc;
}

static int _release_shared(rt_varea_t varea, void *arg)
{
    rt_aspace_t src = varea->aspace;
    rt_mem_obj_t mem_obj = varea->mem_obj;

    if (mem_obj != _get_private_obj(src))
    {
        _varea_uninstall_locked(varea);
        if (VAREA_NOT_STATIC(varea))
        {
            rt_free(varea);
        }
    }

    return 0;
}

static rt_err_t _convert_readonly(rt_aspace_t aspace, long base_reference)
{
    rt_mem_obj_t aobj;
    rt_private_ctx_t pctx;
    aobj = _get_private_obj(aspace);
    pctx = _anon_mobj_to_pctx(aobj);

    LOG_D("Ref(cur=%d,base=%d)", pctx->reference, base_reference);
    rt_aspace_traversal(aspace, _release_shared, 0);
    pctx->readonly = base_reference;
    return 0;
}

rt_inline void _switch_aspace(rt_aspace_t *pa, rt_aspace_t *pb)
{
    rt_aspace_t temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

rt_err_t rt_aspace_fork(rt_aspace_t *psrc, rt_aspace_t *pdst)
{
    rt_err_t rc;
    void *pgtbl;
    rt_aspace_t backup;
    rt_aspace_t src = *psrc;
    rt_aspace_t dst = *pdst;
    long base_reference;

    pgtbl = rt_hw_mmu_pgtbl_create();
    if (pgtbl)
    {
        backup = rt_aspace_create(src->start, src->size, pgtbl);
        if (backup)
        {
            WR_LOCK(src);
            base_reference = rt_atomic_load(_anon_obj_get_reference(src->private_object));
            rc = rt_aspace_duplicate_locked(src, dst);
            WR_UNLOCK(src);

            if (!rc)
            {
                /* WR_LOCK(dst) is not necessary since dst is not available currently */
                rc = rt_aspace_duplicate_locked(dst, backup);
                if (!rc)
                {
                    _switch_aspace(psrc, &backup);
                    _convert_readonly(backup, base_reference);
                }
            }
        }
        else
        {
            rc = -RT_ENOMEM;
        }
    }
    else
    {
        rc = -RT_ENOMEM;
    }

    return rc;
}
