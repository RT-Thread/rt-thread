/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     shaojinchun  first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "lwp.h"

#ifdef ARCH_MM_MMU
#include "lwp_user_mm.h"
#endif

#define DBG_TAG    "LWP_TID"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define TID_MAX 10000

#define TID_CT_ASSERT(name, x) \
    struct assert_##name {char ary[2 * (x) - 1];}

TID_CT_ASSERT(tid_min_nr, LWP_TID_MAX_NR > 1);
TID_CT_ASSERT(tid_max_nr, LWP_TID_MAX_NR < TID_MAX);

static struct lwp_avl_struct lwp_tid_ary[LWP_TID_MAX_NR];
static struct lwp_avl_struct *lwp_tid_free_head = RT_NULL;
static int lwp_tid_ary_alloced = 0;
static struct lwp_avl_struct *lwp_tid_root = RT_NULL;
static int current_tid = 0;

int lwp_tid_get(void)
{
    rt_base_t level;
    struct lwp_avl_struct *p;
    int tid = 0;

    level = rt_hw_interrupt_disable();
    p = lwp_tid_free_head;
    if (p)
    {
        lwp_tid_free_head = (struct lwp_avl_struct *)p->avl_right;
    }
    else if (lwp_tid_ary_alloced < LWP_TID_MAX_NR)
    {
        p = lwp_tid_ary + lwp_tid_ary_alloced;
        lwp_tid_ary_alloced++;
    }
    if (p)
    {
        int found_noused = 0;

        RT_ASSERT(p->data == RT_NULL);
        for (tid = current_tid + 1; tid < TID_MAX; tid++)
        {
            if (!lwp_avl_find(tid, lwp_tid_root))
            {
                found_noused = 1;
                break;
            }
        }
        if (!found_noused)
        {
            for (tid = 1; tid <= current_tid; tid++)
            {
                if (!lwp_avl_find(tid, lwp_tid_root))
                {
                    found_noused = 1;
                    break;
                }
            }
        }
        p->avl_key = tid;
        lwp_avl_insert(p, &lwp_tid_root);
        current_tid = tid;
    }
    rt_hw_interrupt_enable(level);
    return tid;
}

void lwp_tid_put(int tid)
{
    rt_base_t level;
    struct lwp_avl_struct *p;

    level = rt_hw_interrupt_disable();
    p  = lwp_avl_find(tid, lwp_tid_root);
    if (p)
    {
        p->data = RT_NULL;
        lwp_avl_remove(p, &lwp_tid_root);
        p->avl_right = lwp_tid_free_head;
        lwp_tid_free_head = p;
    }
    rt_hw_interrupt_enable(level);
}

rt_thread_t lwp_tid_get_thread(int tid)
{
    rt_base_t level;
    struct lwp_avl_struct *p;
    rt_thread_t thread = RT_NULL;

    level = rt_hw_interrupt_disable();
    p  = lwp_avl_find(tid, lwp_tid_root);
    if (p)
    {
        thread = (rt_thread_t)p->data;
    }
    rt_hw_interrupt_enable(level);
    return thread;
}

void lwp_tid_set_thread(int tid, rt_thread_t thread)
{
    rt_base_t level;
    struct lwp_avl_struct *p;

    level = rt_hw_interrupt_disable();
    p  = lwp_avl_find(tid, lwp_tid_root);
    if (p)
    {
        p->data = thread;
    }
    rt_hw_interrupt_enable(level);
}
