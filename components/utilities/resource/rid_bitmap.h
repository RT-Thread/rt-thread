/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-07     Shell        First version
 */

#ifndef  __RID_BITMAP_H__
#define  __RID_BITMAP_H__

#include <rthw.h>
#include <rtthread.h>
#include <bitmap.h>

#define RESOURCE_ID_INIT {0}

typedef struct rid_bitmap
{
    struct rt_mutex *id_lock;
    long min_id;
    long total_id_count;
    rt_bitmap_t *bitset;
} *rid_bitmap_t;

void rid_bitmap_init(rid_bitmap_t mgr, int min_id, int total_id_count,
                     rt_bitmap_t *set, struct rt_mutex *id_lock);
long rid_bitmap_get(rid_bitmap_t mgr);
long rid_bitmap_get_named(rid_bitmap_t mgr, long no);
void rid_bitmap_put(rid_bitmap_t mgr, long no);

#endif  /* __RID_BITMAP_H__ */
