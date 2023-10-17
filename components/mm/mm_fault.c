/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     WangXiaoyao  the first version
 * 2023-08-19     Shell        Support PRIVATE mapping and COW
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

static int _fetch_page(rt_varea_t varea, struct rt_aspace_fault_msg *msg)
{
    int err = MM_FAULT_FIXABLE_FALSE;
    if (varea->mem_obj && varea->mem_obj->on_page_fault)
    {
        varea->mem_obj->on_page_fault(varea, msg);
        err = rt_varea_map_with_msg(varea, msg);
        err = (err == RT_EOK ? MM_FAULT_FIXABLE_TRUE : MM_FAULT_FIXABLE_FALSE);
    }
    return err;
}

static int _read_fault(rt_varea_t varea, void *pa, struct rt_aspace_fault_msg *msg)
{
    int err = MM_FAULT_FIXABLE_FALSE;
    if (msg->fault_type == MM_FAULT_TYPE_PAGE_FAULT)
    {
        RT_ASSERT(pa == ARCH_MAP_FAILED);
        RT_ASSERT(!(varea->flag & MMF_PREFETCH));
        err = _fetch_page(varea, msg);
    }
    else
    {
        /* signal a fault to user? */
    }
    return err;
}

static int _write_fault(rt_varea_t varea, void *pa, struct rt_aspace_fault_msg *msg)
{
    rt_aspace_t aspace = varea->aspace;
    int err = MM_FAULT_FIXABLE_FALSE;

    if (rt_varea_is_private_locked(varea))
    {
        if (VAREA_IS_WRITABLE(varea) && (
            msg->fault_type == MM_FAULT_TYPE_ACCESS_FAULT ||
            msg->fault_type == MM_FAULT_TYPE_PAGE_FAULT))
        {
            RDWR_LOCK(aspace);
            err = rt_varea_fix_private_locked(varea, pa, msg, RT_FALSE);
            RDWR_UNLOCK(aspace);
            if (err == MM_FAULT_FIXABLE_FALSE)
                LOG_I("%s: fix private failure", __func__);
        }
        else
        {
            LOG_I("%s: No permission on %s(attr=0x%lx)", __func__, VAREA_NAME(varea), varea->attr);
        }
    }
    else if (msg->fault_type == MM_FAULT_TYPE_PAGE_FAULT)
    {
        RT_ASSERT(pa == ARCH_MAP_FAILED);
        RT_ASSERT(!(varea->flag & MMF_PREFETCH));
        err = _fetch_page(varea, msg);
        if (err == MM_FAULT_FIXABLE_FALSE)
            LOG_I("%s: page fault failure", __func__);
    }
    else
    {
        LOG_D("%s: can not fix", __func__);
        /* signal a fault to user? */
    }
    return err;
}

static int _exec_fault(rt_varea_t varea, void *pa, struct rt_aspace_fault_msg *msg)
{
    int err = MM_FAULT_FIXABLE_FALSE;
    if (msg->fault_type == MM_FAULT_TYPE_PAGE_FAULT)
    {
        RT_ASSERT(pa == ARCH_MAP_FAILED);
        RT_ASSERT(!(varea->flag & MMF_PREFETCH));
        err = _fetch_page(varea, msg);
    }
    return err;
}

int rt_aspace_fault_try_fix(rt_aspace_t aspace, struct rt_aspace_fault_msg *msg)
{
    int err = MM_FAULT_FIXABLE_FALSE;
    uintptr_t va = (uintptr_t)msg->fault_vaddr;
    va &= ~ARCH_PAGE_MASK;
    msg->fault_vaddr = (void *)va;
    rt_mm_fault_res_init(&msg->response);

    RT_DEBUG_SCHEDULER_AVAILABLE(1);

    if (aspace)
    {
        rt_varea_t varea;

        RD_LOCK(aspace);
        varea = _aspace_bst_search(aspace, msg->fault_vaddr);
        if (varea)
        {
            void *pa = rt_hw_mmu_v2p(aspace, msg->fault_vaddr);
            if (pa != ARCH_MAP_FAILED && msg->fault_type == MM_FAULT_TYPE_PAGE_FAULT)
            {
                LOG_D("%s(fault=%p) has already fixed", __func__, msg->fault_vaddr);
                err = MM_FAULT_FIXABLE_TRUE;
            }
            else
            {
                LOG_D("%s(varea=%s,fault=%p,fault_op=%d,phy=%p)", __func__, VAREA_NAME(varea), msg->fault_vaddr, msg->fault_op, pa);
                msg->off = varea->offset + ((long)msg->fault_vaddr - (long)varea->start) / ARCH_PAGE_SIZE;

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
        else
        {
            LOG_I("%s: varea not found at 0x%lx", __func__, msg->fault_vaddr);
        }
        RD_UNLOCK(aspace);
    }

    return err;
}

#endif /* RT_USING_SMART */
