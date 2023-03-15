/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     WangXiaoyao  the first version
 */
#include <rtthread.h>

#ifdef RT_USING_SMART
#define DBG_TAG "mm.fault"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <lwp.h>
#include <lwp_syscall.h>
#include "mm_aspace.h"
#include "mm_fault.h"
#include "mm_flag.h"
#include "mm_private.h"
#include <mmu.h>
#include <tlb.h>

#define UNRECOVERABLE 0
#define RECOVERABLE   1

static int _fetch_page(rt_varea_t varea, struct rt_mm_fault_msg *msg)
{
    int err = UNRECOVERABLE;
    if (varea->mem_obj && varea->mem_obj->on_page_fault)
    {
        varea->mem_obj->on_page_fault(varea, msg);
        if (msg->response.status == MM_FAULT_STATUS_OK)
        {
            void *store = msg->response.vaddr;
            rt_size_t store_sz = msg->response.size;

            if (msg->vaddr + store_sz > varea->start + varea->size)
            {
                LOG_W("%s more size of buffer is provided than varea", __func__);
            }
            else
            {
                rt_hw_mmu_map(varea->aspace, msg->vaddr, store + PV_OFFSET,
                            store_sz, varea->attr);
                rt_hw_tlb_invalidate_range(varea->aspace, msg->vaddr, store_sz,
                                        ARCH_PAGE_SIZE);
                err = RECOVERABLE;
            }
        }
    }
    return err;
}

static int _read_fault(rt_varea_t varea, void *pa, struct rt_mm_fault_msg *msg)
{
    int err = UNRECOVERABLE;
    if (msg->fault_type == MM_FAULT_TYPE_PAGE_FAULT)
    {
        RT_ASSERT(pa == ARCH_MAP_FAILED);
        err = _fetch_page(varea, msg);
    }
    else
    {
        /* signal a fault to user? */
    }
    return err;
}

static int _write_fault(rt_varea_t varea, void *pa, struct rt_mm_fault_msg *msg)
{
    int err = UNRECOVERABLE;
    if (msg->fault_type == MM_FAULT_TYPE_PAGE_FAULT)
    {
        RT_ASSERT(pa == ARCH_MAP_FAILED);
        err = _fetch_page(varea, msg);
    }
    else if (msg->fault_type == MM_FAULT_TYPE_ACCESS_FAULT &&
             varea->flag & MMF_COW)
    {
    }
    else
    {
        /* signal a fault to user? */
    }
    return err;
}

static int _exec_fault(rt_varea_t varea, void *pa, struct rt_mm_fault_msg *msg)
{
    int err = UNRECOVERABLE;
    if (msg->fault_type == MM_FAULT_TYPE_PAGE_FAULT)
    {
        RT_ASSERT(pa == ARCH_MAP_FAILED);
        err = _fetch_page(varea, msg);
    }
    return err;
}

int rt_mm_fault_try_fix(struct rt_mm_fault_msg *msg)
{
    struct rt_lwp *lwp = lwp_self();
    int err = UNRECOVERABLE;
    uintptr_t va = (uintptr_t)msg->vaddr;
    va &= ~ARCH_PAGE_MASK;
    msg->vaddr = (void *)va;

    if (lwp)
    {
        rt_aspace_t aspace = lwp->aspace;
        rt_varea_t varea = _aspace_bst_search(aspace, msg->vaddr);
        if (varea)
        {
            void *pa = rt_hw_mmu_v2p(aspace, msg->vaddr);
            msg->off = (msg->vaddr - varea->start) >> ARCH_PAGE_SHIFT;

            /* permission checked by fault op */
            switch (msg->fault_op)
            {
            case MM_FAULT_OP_READ:
                err = _read_fault(varea, pa, msg);
                break;
            case MM_FAULT_OP_WRITE:
                err = _write_fault(varea, pa, msg);
                break;
            case MM_FAULT_OP_EXECUTE:
                err = _exec_fault(varea, pa, msg);
                break;
            }
        }
    }

    return err;
}

#endif /* RT_USING_SMART */
