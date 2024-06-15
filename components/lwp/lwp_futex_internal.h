/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-01     Shell        Init ver.
 */
#ifndef __LWP_FUTEX_INTERNAL_H__
#define __LWP_FUTEX_INTERNAL_H__

#define DBG_TAG "lwp.futex"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rt_uthash.h"
#include "lwp_internal.h"
#include "lwp_pid.h"

#include <rtthread.h>
#include <lwp.h>

#ifdef ARCH_MM_MMU
#include <lwp_user_mm.h>
#endif /* ARCH_MM_MMU */

struct shared_futex_key
{
    rt_mem_obj_t mobj;
    rt_base_t offset;
};
DEFINE_RT_UTHASH_TYPE(shared_futex_entry, struct shared_futex_key, key);

struct rt_futex
{
    union {
        /* for private futex */
        struct lwp_avl_struct node;
        /* for shared futex */
        struct shared_futex_entry entry;
    };

    rt_list_t waiting_thread;
    struct rt_object *custom_obj;
    rt_mutex_t mutex;
};
typedef struct rt_futex *rt_futex_t;

rt_err_t futex_global_table_add(struct shared_futex_key *key, rt_futex_t futex);
rt_err_t futex_global_table_find(struct shared_futex_key *key, rt_futex_t *futex);
rt_err_t futex_global_table_delete(struct shared_futex_key *key);

#endif /* __LWP_FUTEX_INTERNAL_H__ */
