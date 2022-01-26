/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-10     Bernard      first version
 */

#ifndef __LWP_MEMHEAP_H__
#define __LWP_MEMHEAP_H__

#include <stdint.h>
#include <rtthread.h>

/**
 * memory item on the heap
 */
struct rt_lwp_memheap_item
{
    rt_uint32_t                 magic;                  /**< magic number for memheap */
    struct rt_lwp_memheap      *pool_ptr;               /**< point of pool */

    struct rt_lwp_memheap_item *next;                   /**< next memheap item */
    struct rt_lwp_memheap_item *prev;                   /**< prev memheap item */

    struct rt_lwp_memheap_item *next_free;              /**< next free memheap item */
    struct rt_lwp_memheap_item *prev_free;              /**< prev free memheap item */
};

/**
 * Base structure of memory heap object
 */
struct rt_lwp_memheap
{
    struct rt_object        parent;                     /**< inherit from rt_object */

    void                   *start_addr;                 /**< pool start address and size */

    rt_uint32_t             pool_size;                  /**< pool size */
    rt_uint32_t             available_size;             /**< available size */
    rt_uint32_t             max_used_size;              /**< maximum allocated size */

    struct rt_lwp_memheap_item *block_list;             /**< used block list */
    struct rt_lwp_memheap_item *free_list;              /**< free block list */
    struct rt_lwp_memheap_item  free_header;            /**< free block list header */

    struct rt_semaphore     lock;                       /**< semaphore lock */

    rt_list_t mlist;
};

extern rt_err_t rt_lwp_memheap_init(struct rt_lwp_memheap *memheap, const char *name, void *start_addr, rt_uint32_t size);
extern void *rt_lwp_memheap_alloc(struct rt_lwp_memheap *heap, rt_uint32_t size);
extern void rt_lwp_memheap_free(void *ptr);
extern void *rt_lwp_memheap_realloc(struct rt_lwp_memheap *heap, void *ptr, rt_size_t newsize);
extern rt_bool_t rt_lwp_memheap_is_empty(struct rt_lwp_memheap *memheap);
extern rt_bool_t rt_lwp_memheap_unavailable_size_get(void);

#endif
