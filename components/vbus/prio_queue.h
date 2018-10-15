/*
 * COPYRIGHT (C) 2018, Real-Thread Information Technology Ltd
 * 
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-04     Grissiom     add comment
 */

#ifndef __PRIO_QUEUE_H__
#define __PRIO_QUEUE_H__

#include <rtthread.h>

#define RT_PRIO_QUEUE_PRIO_MAX  32

struct rt_prio_queue_item;

struct rt_prio_queue {
    rt_uint32_t bitmap;
    struct rt_prio_queue_item *head[RT_PRIO_QUEUE_PRIO_MAX];
    struct rt_prio_queue_item *tail[RT_PRIO_QUEUE_PRIO_MAX];
    /* push thread suspend on the mempool, not queue */
    rt_list_t suspended_pop_list;
    rt_size_t item_sz;

    struct rt_mempool pool;
};

rt_err_t rt_prio_queue_init(struct rt_prio_queue *que,
                            const char *name,
                            void *buf,
                            rt_size_t bufsz,
                            rt_size_t itemsz);
void rt_prio_queue_detach(struct rt_prio_queue *que);

rt_err_t rt_prio_queue_push(struct rt_prio_queue *que,
                            rt_uint8_t prio,
                            void *data,
                            rt_int32_t timeout);
rt_err_t rt_prio_queue_pop(struct rt_prio_queue *que,
                           void *data,
                           rt_int32_t timeout);
#ifdef RT_USING_HEAP
struct rt_prio_queue* rt_prio_queue_create(const char *name,
                                           rt_size_t item_nr,
                                           rt_size_t item_sz);
void rt_prio_queue_delete(struct rt_prio_queue *que);
#endif

void rt_prio_queue_dump(struct rt_prio_queue *que);

#endif /* end of include guard: __PRIO_QUEUE_H__ */
