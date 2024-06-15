/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-07     Shell        First version
 */

#include "rid_bitmap.h"
#include <bitmap.h>
#include <rtdef.h>

void rid_bitmap_init(rid_bitmap_t mgr, int min_id, int total_id_count,
                     rt_bitmap_t *set, struct rt_mutex *id_lock)
{
    mgr->min_id = min_id;
    mgr->total_id_count = total_id_count;
    mgr->bitset = set;
    mgr->id_lock = id_lock;

    return;
}

long rid_bitmap_get(rid_bitmap_t mgr)
{
    long id;
    long overflow;
    if (mgr->id_lock)
    {
        rt_mutex_take(mgr->id_lock, RT_WAITING_FOREVER);
    }

    overflow = mgr->total_id_count;
    id = rt_bitmap_next_clear_bit(mgr->bitset, 0, overflow);
    if (id == overflow)
    {
        id = -1;
    }
    else
    {
        rt_bitmap_set_bit(mgr->bitset, id);
        id += mgr->min_id;
    }

    if (mgr->id_lock)
    {
        rt_mutex_release(mgr->id_lock);
    }
    return id;
}

long rid_bitmap_get_named(rid_bitmap_t mgr, long no)
{
    long id_relative;
    long overflow;
    long min;

    if (mgr->id_lock)
    {
        rt_mutex_take(mgr->id_lock, RT_WAITING_FOREVER);
    }

    min = mgr->min_id;
    id_relative = no - min;
    overflow = mgr->total_id_count;
    if (id_relative >= min && id_relative < overflow)
    {
        if (rt_bitmap_test_bit(mgr->bitset, id_relative))
        {
            id_relative = -RT_EBUSY;
        }
        else
        {
            rt_bitmap_set_bit(mgr->bitset, id_relative);
            id_relative += min;
        }
    }
    else
    {
        id_relative = -1;
    }

    if (mgr->id_lock)
    {
        rt_mutex_release(mgr->id_lock);
    }
    return id_relative;
}

void rid_bitmap_put(rid_bitmap_t mgr, long no)
{
    long id_relative;
    long overflow;
    long min;

    if (mgr->id_lock)
    {
        rt_mutex_take(mgr->id_lock, RT_WAITING_FOREVER);
    }

    min = mgr->min_id;
    id_relative = no - min;
    overflow = mgr->total_id_count;
    if (id_relative >= min && id_relative < overflow &&
        rt_bitmap_test_bit(mgr->bitset, id_relative))
    {
        rt_bitmap_clear_bit(mgr->bitset, id_relative);
    }

    if (mgr->id_lock)
    {
        rt_mutex_release(mgr->id_lock);
    }
}
