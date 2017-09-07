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

#include <rthw.h>
#include <rtthread.h>

#include "prio_queue.h"

struct rt_prio_queue_item {
    struct rt_prio_queue_item *next;
    /* data follows */
};

static void _do_push(struct rt_prio_queue *que,
                     rt_uint8_t prio,
                     struct rt_prio_queue_item *item)
{
    if (que->head[prio] == RT_NULL)
    {
        que->head[prio] = item;
        que->bitmap |= 1 << prio;
    }
    else
    {
        RT_ASSERT(que->tail[prio]);
        que->tail[prio]->next = item;
    }
    que->tail[prio] = item;
}

static struct rt_prio_queue_item* _do_pop(struct rt_prio_queue *que)
{
    int ffs;
    struct rt_prio_queue_item *item;

    ffs = __rt_ffs(que->bitmap);
    if (ffs == 0)
        return RT_NULL;
    ffs--;

    item = que->head[ffs];
    RT_ASSERT(item);

    que->head[ffs] = item->next;
    if (que->head[ffs] == RT_NULL)
    {
        que->bitmap &= ~(1 << ffs);
    }

    return item;
}

rt_err_t rt_prio_queue_init(struct rt_prio_queue *que,
                            const char *name,
                            void *buf,
                            rt_size_t bufsz,
                            rt_size_t itemsz)
{
    RT_ASSERT(que);

    rt_memset(que, 0, sizeof(*que));

    rt_list_init(&(que->suspended_pop_list));

    rt_mp_init(&que->pool, name, buf, bufsz,
               sizeof(struct rt_prio_queue_item) + itemsz);

    que->item_sz = itemsz;

    return RT_EOK;
}

void rt_prio_queue_detach(struct rt_prio_queue *que)
{
    /* wake up all suspended pop threads, push thread is suspended on mempool.
     */
    while (!rt_list_isempty(&(que->suspended_pop_list)))
    {
        rt_thread_t thread;

        /* disable interrupt */
        rt_ubase_t temp = rt_hw_interrupt_disable();

        /* get next suspend thread */
        thread = rt_list_entry(que->suspended_pop_list.next, struct rt_thread, tlist);
        /* set error code to RT_ERROR */
        thread->error = -RT_ERROR;

        rt_thread_resume(thread);

        /* enable interrupt */
        rt_hw_interrupt_enable(temp);
    }
    rt_mp_detach(&que->pool);
}

#ifdef RT_USING_HEAP
struct rt_prio_queue* rt_prio_queue_create(const char *name,
                                           rt_size_t item_nr,
                                           rt_size_t item_sz)
{
    struct rt_prio_queue *que;
    rt_size_t bufsz;

    bufsz = item_nr * (sizeof(struct rt_prio_queue_item)
                       + item_sz
                       + sizeof(void*));

    RT_ASSERT(item_nr);

    que = rt_malloc(sizeof(*que) + bufsz);
    if (!que)
        return RT_NULL;

    rt_prio_queue_init(que, name, que+1, bufsz, item_sz);

    return que;
}

void rt_prio_queue_delete(struct rt_prio_queue *que)
{
    rt_prio_queue_detach(que);
    rt_free(que);
}
#endif

rt_err_t rt_prio_queue_push(struct rt_prio_queue *que,
                            rt_uint8_t prio,
                            void *data,
                            rt_int32_t timeout)
{
    rt_ubase_t level;
    struct rt_prio_queue_item *item;

    RT_ASSERT(que);

    if (prio >= RT_PRIO_QUEUE_PRIO_MAX)
        return -RT_ERROR;

    item = rt_mp_alloc(&que->pool, timeout);
    if (item == RT_NULL)
        return -RT_ENOMEM;

    rt_memcpy(item+1, data, que->item_sz);
    item->next = RT_NULL;

    level = rt_hw_interrupt_disable();

    _do_push(que, prio, item);

    if (!rt_list_isempty(&(que->suspended_pop_list)))
    {
        rt_thread_t thread;

        /* get thread entry */
        thread = rt_list_entry(que->suspended_pop_list.next,
                               struct rt_thread,
                               tlist);
        /* resume it */
        rt_thread_resume(thread);
        rt_hw_interrupt_enable(level);

        /* perform a schedule */
        rt_schedule();

        return RT_EOK;
    }

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t rt_prio_queue_pop(struct rt_prio_queue *que,
                           void *data,
                           rt_int32_t timeout)
{
    rt_ubase_t level;
    struct rt_prio_queue_item *item;

    RT_ASSERT(que);
    RT_ASSERT(data);

    level = rt_hw_interrupt_disable();
    for (item = _do_pop(que);
         item == RT_NULL;
         item = _do_pop(que))
    {
        rt_thread_t thread;

        if (timeout == 0)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ETIMEOUT;
        }

        RT_DEBUG_NOT_IN_INTERRUPT;

        thread = rt_thread_self();
        thread->error = RT_EOK;
        rt_thread_suspend(thread);

        rt_list_insert_before(&(que->suspended_pop_list), &(thread->tlist));

        if (timeout > 0)
        {
            rt_timer_control(&(thread->thread_timer),
                             RT_TIMER_CTRL_SET_TIME,
                             &timeout);
            rt_timer_start(&(thread->thread_timer));
        }

        rt_hw_interrupt_enable(level);

        rt_schedule();

        /* thread is waked up */
        if (thread->error != RT_EOK)
            return thread->error;
        level = rt_hw_interrupt_disable();
    }

    rt_hw_interrupt_enable(level);

    rt_memcpy(data, item+1, que->item_sz);
    rt_mp_free(item);

    return RT_EOK;
}

void rt_prio_queue_dump(struct rt_prio_queue *que)
{
    int level = 0;

    rt_kprintf("bitmap: %08x\n", que->bitmap);
    for (level = 0; level < RT_PRIO_QUEUE_PRIO_MAX; level++)
    {
        struct rt_prio_queue_item *item;

        rt_kprintf("%2d: ", level);
        for (item = que->head[level];
             item;
             item = item->next)
        {
            rt_kprintf("%p, ", item);
        }
        rt_kprintf("\n");
    }
}

