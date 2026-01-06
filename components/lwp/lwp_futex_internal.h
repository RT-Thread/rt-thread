/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
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

/**
 * @brief Shared futex key structure
 *
 * @note This structure represents a key used to identify shared futexes
 *       in the system.
 */
struct shared_futex_key
{
    rt_mem_obj_t mobj; /**< Memory object associated with the futex */
    rt_base_t offset;  /**< Offset within the memory object */
};
DEFINE_RT_UTHASH_TYPE(shared_futex_entry, struct shared_futex_key, key);

/**
 * @brief Futex structure for thread synchronization
 *
 * @note This structure represents a futex used for thread synchronization.
 *       It can be either private (process-local) or shared between processes.
 */
struct rt_futex
{
    union
    {
        /* for private futex */
        struct lwp_avl_struct node;       /**< AVL tree node for private futex */
        /* for shared futex */
        struct shared_futex_entry entry;  /**< Entry for shared futex */
    };

    rt_list_t waiting_thread;             /**< List of threads waiting on the futex */
    struct rt_object *custom_obj;         /**< Custom object associated with the futex */
    rt_mutex_t mutex;                     /**< kernel mutex object for futex */
};
typedef struct rt_futex *rt_futex_t;

rt_err_t futex_global_table_add(struct shared_futex_key *key, rt_futex_t futex);
rt_err_t futex_global_table_find(struct shared_futex_key *key, rt_futex_t *futex);
rt_err_t futex_global_table_delete(struct shared_futex_key *key);

#endif /* __LWP_FUTEX_INTERNAL_H__ */
