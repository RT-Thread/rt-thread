/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-30     WangXiaoyao  the first version
 */

#include <rtthread.h>

#include "mm_aspace.h"
#include "mm_fault.h"
#include "mm_page.h"
#include <mmu.h>

#define DBG_TAG "mm.object"
#define DBG_LVL DBG_INFO
#include "rtdbg.h"

static const char *get_name(rt_varea_t varea)
{
    return "dummy-mapper";
}

void rt_varea_pgmgr_insert(rt_varea_t varea, void *page_addr)
{
    rt_page_t page = rt_page_addr2page(page_addr);

    if (varea->frames == NULL)
    {
        varea->frames = page;
        page->next = NULL;
    }
    else
    {
        varea->frames->pre = page;
        page->next = varea->frames;
        varea->frames = page;
    }
}

void rt_varea_pgmgr_pop_all(rt_varea_t varea)
{
    rt_page_t page = varea->frames;

    while (page)
    {
        rt_page_t next = page->next;
        void *pg_va = rt_page_page2addr(page);
        rt_pages_free(pg_va, 0);
        page = next;
    }
}

void rt_varea_pgmgr_pop(rt_varea_t varea, void *vaddr, rt_size_t size)
{
    void *vend = (char *)vaddr + size;
    while (vaddr != vend)
    {
        rt_page_t page = rt_page_addr2page(vaddr);
        page->pre->next = page->next;
        page->next->pre = page->pre;
        rt_pages_free(vaddr, 0);
        vaddr = (char *)vaddr + ARCH_PAGE_SIZE;
    }
}

static void on_page_fault(struct rt_varea *varea, struct rt_aspace_fault_msg *msg)
{
    void *page;
    page = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);

    if (!page)
    {
        LOG_W("%s: page alloc failed", __func__);
        return;
    }

    msg->response.status = MM_FAULT_STATUS_OK;
    msg->response.size = ARCH_PAGE_SIZE;
    msg->response.vaddr = page;

    rt_varea_pgmgr_insert(varea, page);
}

static void on_varea_open(struct rt_varea *varea)
{
    varea->data = NULL;
}

static void on_varea_close(struct rt_varea *varea)
{
}

static void on_page_offload(rt_varea_t varea, void *vaddr, rt_size_t size)
{
    rt_varea_pgmgr_pop(varea, vaddr, size);
}

struct rt_mem_obj rt_mm_dummy_mapper = {
    .get_name = get_name,
    .on_page_fault = on_page_fault,
    .hint_free = NULL,
    .on_varea_open = on_varea_open,
    .on_varea_close = on_varea_close,
    .on_page_offload = on_page_offload,
};
