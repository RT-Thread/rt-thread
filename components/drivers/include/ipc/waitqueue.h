/*
 * File      : waitqueue.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * 2018/06/26     Bernard      Fix the wait queue issue when wakeup a soon 
 *                             to blocked thread.
 */

#ifndef WAITQUEUE_H__
#define WAITQUEUE_H__

#include <rtthread.h>

#define RT_WQ_FLAG_CLEAN    0x00
#define RT_WQ_FLAG_WAKEUP   0x01

struct rt_wqueue_node;
typedef int (*rt_wqueue_func_t)(struct rt_wqueue_node *wait, void *key);

struct rt_wqueue_node
{
    rt_thread_t polling_thread;
    rt_list_t   list;

    rt_wqueue_func_t wakeup;
    rt_uint32_t key;
};
typedef struct rt_wqueue_node rt_wqueue_node_t;

int __wqueue_default_wake(struct rt_wqueue_node *wait, void *key);

rt_inline void rt_wqueue_init(rt_wqueue_t *queue)
{
    RT_ASSERT(queue != RT_NULL);

    queue->flag = RT_WQ_FLAG_CLEAN;
    rt_list_init(&(queue->waiting_list));
}

void rt_wqueue_add(rt_wqueue_t *queue, struct rt_wqueue_node *node);
void rt_wqueue_remove(struct rt_wqueue_node *node);
int  rt_wqueue_wait(rt_wqueue_t *queue, int condition, int timeout);
void rt_wqueue_wakeup(rt_wqueue_t *queue, void *key);

#define DEFINE_WAIT_FUNC(name, function)                \
    struct rt_wqueue_node name = {                      \
        rt_current_thread,                              \
        RT_LIST_OBJECT_INIT(((name).list)),             \
                                                        \
        function,                                       \
        0                                               \
    }

#define DEFINE_WAIT(name) DEFINE_WAIT_FUNC(name, __wqueue_default_wake)

#endif
