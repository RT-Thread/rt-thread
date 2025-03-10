/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-30     WangXiaoyao  the first version
 * 2023-08-19     Shell        Support varea modification handler
 * 2023-10-13     Shell        Replace the page management algorithm of pgmgr
 */

#define DBG_TAG "mm.object"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <rtthread.h>

#include "mm_aspace.h"
#include "mm_fault.h"
#include "mm_page.h"
#include <mmu.h>

#include <string.h>
#include <stdlib.h>

/** varea based dummy memory object whose data comes directly from page frame */

static const char *get_name(rt_varea_t varea)
{
    return "dummy-mapper";
}

static void on_page_fault(struct rt_varea *varea, struct rt_aspace_fault_msg *msg)
{
    void *page;
    int affid = RT_PAGE_PICK_AFFID(msg->fault_vaddr);
    page = rt_pages_alloc_tagged(0, affid, PAGE_ANY_AVAILABLE);

    if (!page)
    {
        LOG_W("%s: page alloc failed", __func__);
        return;
    }

    msg->response.status = MM_FAULT_STATUS_OK;
    msg->response.size = ARCH_PAGE_SIZE;
    msg->response.vaddr = page;
}

static void on_varea_open(struct rt_varea *varea)
{
    varea->data = NULL;
}

static void on_varea_close(struct rt_varea *varea)
{
}

static rt_err_t on_varea_expand(struct rt_varea *varea, void *new_vaddr, rt_size_t size)
{
    return RT_EOK;
}

static rt_err_t on_varea_shrink(rt_varea_t varea, void *new_start, rt_size_t size)
{
    return RT_EOK;
}

static rt_err_t on_varea_split(struct rt_varea *existed, void *unmap_start, rt_size_t unmap_len, struct rt_varea *subset)
{
    return RT_EOK;
}

static rt_err_t on_varea_merge(struct rt_varea *merge_to, struct rt_varea *merge_from)
{
    return RT_EOK;
}

static void page_read(struct rt_varea *varea, struct rt_aspace_io_msg *msg)
{
    char *dst_k;
    rt_aspace_t aspace = varea->aspace;
    dst_k = rt_hw_mmu_v2p(aspace, msg->fault_vaddr);
    if (dst_k != ARCH_MAP_FAILED)
    {
        RT_ASSERT(!((long)dst_k & ARCH_PAGE_MASK));
        dst_k = (void *)((char *)dst_k - PV_OFFSET);
        memcpy(msg->buffer_vaddr, dst_k, ARCH_PAGE_SIZE);
        msg->response.status = MM_FAULT_STATUS_OK;
    }
}

static void page_write(struct rt_varea *varea, struct rt_aspace_io_msg *msg)
{
    void *dst_k;
    rt_aspace_t aspace = varea->aspace;
    dst_k = rt_hw_mmu_v2p(aspace, msg->fault_vaddr);
    if (dst_k != ARCH_MAP_FAILED)
    {
        RT_ASSERT(!((long)dst_k & ARCH_PAGE_MASK));
        dst_k = (void *)((char *)dst_k - PV_OFFSET);
        memcpy(dst_k, msg->buffer_vaddr, ARCH_PAGE_SIZE);
        msg->response.status = MM_FAULT_STATUS_OK;
    }
}

struct rt_mem_obj rt_mm_dummy_mapper = {
    .get_name = get_name,
    .on_page_fault = on_page_fault,
    .hint_free = NULL,
    .on_varea_open = on_varea_open,
    .on_varea_close = on_varea_close,

    .on_varea_shrink = on_varea_shrink,
    .on_varea_split = on_varea_split,
    .on_varea_expand = on_varea_expand,
    .on_varea_merge = on_varea_merge,

    .page_write = page_write,
    .page_read = page_read,
};
