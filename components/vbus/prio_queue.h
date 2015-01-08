/*
 * Priority Queue
 *
 * COPYRIGHT (C) 2013-2015, Shanghai Real-Thread Technology Co., Ltd
 *      http://www.rt-thread.com
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *
 *  All rights reserved.
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
