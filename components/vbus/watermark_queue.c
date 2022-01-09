/*
 * COPYRIGHT (C) 2011-2021, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-04-16     Grissiom     first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "watermark_queue.h"

void rt_wm_que_set_mark(struct rt_watermark_queue *wg,
                             unsigned int low, unsigned int high)
{
    RT_ASSERT(low <= high);

    wg->high_mark = high;
    wg->low_mark = low;
}

void rt_wm_que_init(struct rt_watermark_queue *wg,
                         unsigned int low, unsigned int high)
{
    rt_wm_que_set_mark(wg, low, high);
    rt_list_init(&wg->suspended_threads);
    wg->level = 0;
}

void rt_wm_que_dump(struct rt_watermark_queue *wg)
{
    struct rt_list_node *node;

    rt_kprintf("wg %p: low: %d, high: %d, cur: %d\n",
               wg, wg->low_mark, wg->high_mark, wg->level);
    rt_kprintf("thread suspend:");
    for (node = wg->suspended_threads.next;
         node != &wg->suspended_threads;
         node = node->next)
    {
        rt_thread_t thread;

        thread = rt_list_entry(wg->suspended_threads.next,
                               struct rt_thread,
                               tlist);
        rt_kprintf(" %.*s", RT_NAME_MAX, thread->parent.name);
    }
    rt_kprintf("\n");
}
