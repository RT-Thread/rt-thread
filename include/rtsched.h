/*
 * Copyright (c) 2023-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-19     Shell        Seperate schduling statements from rt_thread_t
 *                             to rt_sched_thread_ctx. Add definitions of scheduler.
 */
#ifndef __RT_SCHED_H__
#define __RT_SCHED_H__

#include "rttypes.h"
#include "rtcompiler.h"

#ifdef __cplusplus
extern "C" {
#endif

struct rt_thread;

typedef rt_uint8_t rt_sched_thread_status_t;

#ifdef RT_USING_SCHED_THREAD_CTX

/**
 * Scheduler private status binding on thread. Caller should never accessing
 * these members.
 */
struct rt_sched_thread_priv
{
    rt_tick_t                   init_tick;              /**< thread's initialized tick */
    rt_tick_t                   remaining_tick;         /**< remaining tick */

    /* priority */
    rt_uint8_t                  current_priority;       /**< current priority */
    rt_uint8_t                  init_priority;          /**< initialized priority */
#if RT_THREAD_PRIORITY_MAX > 32
    rt_uint8_t                  number;                 /**< priority low number */
    rt_uint8_t                  high_mask;              /**< priority high mask */
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
    rt_uint32_t                 number_mask;            /**< priority number mask */

};

/**
 * Scheduler public status binding on thread. Caller must hold the scheduler
 * lock before access any one of its member.
 */
struct rt_sched_thread_ctx
{
    rt_list_t                   thread_list_node;       /**< node in thread list */

    rt_uint8_t                  stat;                   /**< thread status */
    rt_uint8_t                  sched_flag_locked:1;    /**< calling thread have the scheduler locked */
    rt_uint8_t                  sched_flag_ttmr_set:1;  /**< thread timer is start */

#ifdef RT_USING_SMP
    rt_uint8_t                  bind_cpu;               /**< thread is bind to cpu */
    rt_uint8_t                  oncpu;                  /**< process on cpu */

    rt_base_t                   critical_lock_nest;     /**< critical lock count */
#endif

    struct rt_sched_thread_priv sched_thread_priv;      /**< private context of scheduler */
};

#define RT_SCHED_THREAD_CTX struct rt_sched_thread_ctx sched_thread_ctx;

#define RT_SCHED_PRIV(thread) ((thread)->sched_thread_ctx.sched_thread_priv)
#define RT_SCHED_CTX(thread) ((thread)->sched_thread_ctx)

/**
 * Convert a list node in container RT_SCHED_CTX(thread)->thread_list_node
 * to a thread pointer.
 */
#define RT_THREAD_LIST_NODE_ENTRY(node)                                      \
    rt_container_of(                                                         \
        rt_list_entry((node), struct rt_sched_thread_ctx, thread_list_node), \
        struct rt_thread, sched_thread_ctx)
#define RT_THREAD_LIST_NODE(thread) (RT_SCHED_CTX(thread).thread_list_node)

#else /* !defined(RT_USING_SCHED_THREAD_CTX) */

#if RT_THREAD_PRIORITY_MAX > 32
#define _RT_SCHED_THREAD_CTX_PRIO_EXT                 \
    rt_uint8_t number;    /**< priority low number */ \
    rt_uint8_t high_mask; /**< priority high mask */

#else /* ! RT_THREAD_PRIORITY_MAX > 32 */

#define _RT_SCHED_THREAD_CTX_PRIO_EXT
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

#define RT_SCHED_THREAD_CTX                                                    \
    rt_list_t tlist;                    /**< node in thread list */            \
    rt_uint8_t stat;                    /**< thread status */                  \
    rt_uint8_t sched_flag_locked:1;                                            \
            /**< calling thread have the scheduler locked */                   \
    rt_uint8_t sched_flag_ttmr_set:1;   /**< thread timer is start */          \
    rt_tick_t init_tick;                /**< thread's initialized tick */      \
    rt_tick_t remaining_tick;           /**< remaining tick */                 \
    rt_uint8_t current_priority;        /**< current priority */               \
    rt_uint8_t init_priority;           /**< initialized priority */           \
    _RT_SCHED_THREAD_CTX_PRIO_EXT                                              \
    rt_uint32_t number_mask;            /**< priority number mask */

#define RT_SCHED_PRIV(thread) (*thread)
#define RT_SCHED_CTX(thread) (*thread)

/**
 * Convert a list node in container RT_SCHED_CTX(thread)->thread_list_node
 * to a thread pointer.
 */
#define RT_THREAD_LIST_NODE_ENTRY(node) rt_list_entry((node), struct rt_thread, tlist)
#define RT_THREAD_LIST_NODE(thread) (RT_SCHED_CTX(thread).tlist)

#endif /* RT_USING_SCHED_THREAD_CTX */

/**
 * System Scheduler Locking
 */

typedef rt_ubase_t rt_sched_lock_level_t;

rt_err_t rt_sched_lock(rt_sched_lock_level_t *plvl);
rt_err_t rt_sched_unlock(rt_sched_lock_level_t level);
rt_err_t rt_sched_unlock_n_resched(rt_sched_lock_level_t level);

rt_bool_t rt_sched_is_locked(void);

#ifdef RT_USING_SMP
#define RT_SCHED_DEBUG_IS_LOCKED do { RT_ASSERT(rt_sched_is_locked()); } while (0)
#define RT_SCHED_DEBUG_IS_UNLOCKED do { RT_ASSERT(!rt_sched_is_locked()); } while (0)

#else /* !RT_USING_SMP */

#define RT_SCHED_DEBUG_IS_LOCKED
#define RT_SCHED_DEBUG_IS_UNLOCKED
#endif /* RT_USING_SMP */

/**
 * NOTE: user should NEVER use these APIs directly. See rt_thread_.* or IPC
 * methods instead.
 */
#if defined(__RT_KERNEL_SOURCE__) || defined(__RT_IPC_SOURCE__)

/* thread initialization and startup routine */
void rt_sched_thread_init_ctx(struct rt_thread *thread, rt_uint32_t tick, rt_uint8_t priority);
void rt_sched_thread_init_priv(struct rt_thread *thread, rt_uint32_t tick, rt_uint8_t priority);
void rt_sched_thread_startup(struct rt_thread *thread);

/* scheduler related routine */
void rt_sched_post_ctx_switch(struct rt_thread *thread);
rt_err_t rt_sched_tick_increase(void);

/* thread status operation */
rt_uint8_t rt_sched_thread_get_stat(struct rt_thread *thread);
rt_uint8_t rt_sched_thread_get_curr_prio(struct rt_thread *thread);
rt_uint8_t rt_sched_thread_get_init_prio(struct rt_thread *thread);
rt_err_t rt_sched_thread_yield(struct rt_thread *thread);
rt_err_t rt_sched_thread_close(struct rt_thread *thread);
rt_err_t rt_sched_thread_ready(struct rt_thread *thread);
rt_err_t rt_sched_thread_suspend(struct rt_thread *thread, rt_sched_lock_level_t level);
rt_err_t rt_sched_thread_change_priority(struct rt_thread *thread, rt_uint8_t priority);
rt_err_t rt_sched_thread_bind_cpu(struct rt_thread *thread, int cpu);
rt_uint8_t rt_sched_thread_is_suspended(struct rt_thread *thread);
rt_err_t rt_sched_thread_timer_stop(struct rt_thread *thread);
rt_err_t rt_sched_thread_timer_start(struct rt_thread *thread);
void rt_sched_insert_thread(struct rt_thread *thread);
void rt_sched_remove_thread(struct rt_thread *thread);

#endif /* defined(__RT_KERNEL_SOURCE__) || defined(__RT_IPC_SOURCE__) */

#ifdef __cplusplus
}
#endif

#endif /* __RT_SCHED_H__ */
