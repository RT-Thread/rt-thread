/*
 * File      : lwp_mem.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-24     Tanek        the first version
 */

#include <rtthread.h>
#include <lwp.h>

#define DBG_ENABLE
#define DBG_SECTION_NAME    "[LWPMEM]"
#define DBG_COLOR
#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

// todo: remove repleat code
#define RT_MEMHEAP_SIZE         RT_ALIGN(sizeof(struct rt_lwp_memheap_item), RT_ALIGN_SIZE)
#define MEMITEM_SIZE(item)      ((rt_uint32_t)item->next - (rt_uint32_t)item - RT_MEMHEAP_SIZE)

#ifndef LWP_MEM_PAGE_SIZE
    #define LWP_MEM_PAGE_SIZE       (4 * 1024)
#endif

#ifndef LWP_MEM_MAX_PAGE_COUNT
    #define LWP_MEM_MAX_PAGE_COUNT  (256 * 4)
#endif

static void *rt_lwp_malloc_page(struct rt_lwp *lwp, rt_size_t npages)
{
    void *chunk;
    char name[6];
    struct rt_lwp_memheap *lwp_heap;
    rt_size_t page_cnt;

    RT_ASSERT(lwp != RT_NULL);

    page_cnt = lwp->heap_cnt + npages;
    if (page_cnt > LWP_MEM_MAX_PAGE_COUNT)
    {
        dbg_log(DBG_ERROR, "alloc new page failed, lwp memory size out of limited: %d\n", page_cnt);
        return RT_NULL;
    }

    lwp_heap = rt_malloc(sizeof(struct rt_lwp_memheap));
    if (lwp_heap == RT_NULL)
    {
        dbg_log(DBG_ERROR, "alloc new page head failed, out of memory : %d\n", page_cnt);
        return RT_NULL;
    }

    chunk = rt_malloc(npages * LWP_MEM_PAGE_SIZE);
    if (chunk == RT_NULL)
    {
        dbg_log(DBG_ERROR, "alloc new page buffer failed, out of memory : %d\n", page_cnt);
        rt_free(lwp_heap);
        return RT_NULL;
    }

    dbg_log(DBG_LOG, "lwp alloc page: %d\n", npages);

    rt_sprintf(name, "lwp%02x", lwp->heap_cnt);
    rt_lwp_memheap_init(lwp_heap, name, chunk, npages * LWP_MEM_PAGE_SIZE);

    rt_list_insert_before(&lwp->hlist, &lwp_heap->mlist);

    lwp->heap_cnt += npages;

    return chunk;
}

static void rt_lwp_free_page(struct rt_lwp *lwp, struct rt_lwp_memheap *lwp_heap)
{
    rt_size_t npages;

    RT_ASSERT(lwp != RT_NULL);
    RT_ASSERT(lwp_heap != RT_NULL);
    RT_ASSERT(lwp_heap->start_addr != RT_NULL);

    npages = lwp_heap->pool_size / LWP_MEM_PAGE_SIZE;
    lwp->heap_cnt -= npages;

    dbg_log(DBG_LOG, "lwp free page: %d\n", npages);

    rt_list_remove(&lwp_heap->mlist);

    rt_free(lwp_heap->start_addr);
    rt_free(lwp_heap);
}

void rt_lwp_mem_init(struct rt_lwp *lwp)
{
    RT_ASSERT(lwp != RT_NULL);
    rt_list_init(&lwp->hlist);
}

void rt_lwp_mem_deinit(struct rt_lwp *lwp)
{
    struct rt_list_node *node;
    
    RT_ASSERT(lwp != RT_NULL);

    for (node  = lwp->hlist.next; node != &(lwp->hlist); node = node->next)
    {
        struct rt_lwp_memheap *lwp_heap;
        lwp_heap = rt_list_entry(node, struct rt_lwp_memheap, mlist);
        
        RT_ASSERT(lwp_heap != RT_NULL);

        rt_lwp_free_page(lwp, lwp_heap);
    }
}

void *rt_lwp_mem_malloc(rt_uint32_t size)
{
    struct rt_lwp *lwp;
    struct rt_list_node *node;
    void *addr = RT_NULL;
    rt_uint32_t npages;

    if (size == 0)
        return RT_NULL;

    lwp = rt_lwp_self();
    RT_ASSERT(lwp != RT_NULL);

    for (node  = lwp->hlist.next; node != &(lwp->hlist); node = node->next)
    {
        struct rt_lwp_memheap *lwp_heap;
        lwp_heap = rt_list_entry(node, struct rt_lwp_memheap, mlist);

        addr = rt_lwp_memheap_alloc(lwp_heap, size);
        if (addr != RT_NULL)
        {
            dbg_log(DBG_LOG, "lwp alloc 0x%x/%d\n", addr, size);
            return addr;
        }
    }

    npages = (size + rt_lwp_memheap_unavailable_size_get() + LWP_MEM_PAGE_SIZE) / LWP_MEM_PAGE_SIZE;
    if (RT_NULL != rt_lwp_malloc_page(lwp, npages))
        return rt_lwp_mem_malloc(size);
    else
        return RT_NULL;
}

void rt_lwp_mem_free(void *addr)
{
    struct rt_lwp_memheap_item *header_ptr;
    struct rt_lwp_memheap *lwp_heap;

    if (addr == RT_NULL)
        return ;

    /* get memory item */
    header_ptr = (struct rt_lwp_memheap_item *)((rt_uint8_t *)addr - RT_MEMHEAP_SIZE);
    RT_ASSERT(header_ptr);
    
    lwp_heap = header_ptr->pool_ptr;
    RT_ASSERT(lwp_heap);

    dbg_log(DBG_LOG, "lwp free 0x%x\n", addr);
    rt_lwp_memheap_free((void *)addr);

    if (rt_lwp_memheap_is_empty(lwp_heap))
    {
        rt_lwp_free_page(rt_lwp_self(), lwp_heap);
    }
}

void *rt_lwp_mem_realloc(void *rmem, rt_size_t newsize)
{
    void *new_ptr;
    struct rt_lwp_memheap_item *header_ptr;

    if (rmem == RT_NULL)
        return rt_lwp_mem_malloc(newsize);

    if (newsize == 0)
    {
        rt_lwp_mem_free(rmem);
        return RT_NULL;
    }

    /* get old memory item */
    header_ptr = (struct rt_lwp_memheap_item *)
                 ((rt_uint8_t *)rmem - RT_MEMHEAP_SIZE);

    new_ptr = rt_lwp_memheap_realloc(header_ptr->pool_ptr, rmem, newsize);
    if (new_ptr == RT_NULL)
    {
        /* allocate memory block from other memheap */
        new_ptr = rt_lwp_mem_malloc(newsize);
        if (new_ptr != RT_NULL && rmem != RT_NULL)
        {
            rt_size_t oldsize;

            /* get the size of old memory block */
            oldsize = MEMITEM_SIZE(header_ptr);
            if (newsize > oldsize)
                rt_memcpy(new_ptr, rmem, oldsize);
            else
                rt_memcpy(new_ptr, rmem, newsize);

            dbg_log(DBG_LOG, "lwp realloc with memcpy 0x%x -> 0x%x/%d\n", rmem, new_ptr, newsize);
            rt_lwp_mem_free(rmem);

        }
    }

    dbg_log(DBG_LOG, "lwp realloc in same address 0x%x/%d\n", rmem, newsize);

    return new_ptr;
}
