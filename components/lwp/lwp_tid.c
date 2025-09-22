/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     shaojinchun  first version
 * 2023-11-16     xqyjlj       Fix the case where tid is 0
 */

#define DBG_TAG    "lwp.tid"
#define DBG_LVL    DBG_LOG
#include <rtdbg.h>

#include <rthw.h>
#include <rtthread.h>

#include "lwp_internal.h"

#ifdef ARCH_MM_MMU
#include "lwp_user_mm.h"
#endif

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

static struct rt_mutex tid_lock;

/**
 * @brief Initialize the thread ID manager
 *
 * @return int Returns RT_EOK (0) on success, error code on failure
 *
 * @note This function initializes a mutex lock used for thread ID management.
 */
int lwp_tid_init(void)
{
    return rt_mutex_init(&tid_lock, "tidmtx", RT_IPC_FLAG_PRIO);
}

/**
 * @brief Allocates a thread ID (TID) from available resources
 *
 * @return int The allocated thread ID, or 0 if no TID available (with warning log)
 *
 * @note This function performs thread-safe allocation of a TID by:
 *       1. First checking the free list of available TIDs
 *       2. If none available, allocating from the TID array if space remains
 *       3. Performing a two-phase search for unused TIDs (current_tid+1 to TID_MAX, then 1 to current_tid)
 *       4. Inserting the allocated TID into the AVL tree for tracking
 */
int lwp_tid_get(void)
{
    struct lwp_avl_struct *p;
    int tid = 0;

    lwp_mutex_take_safe(&tid_lock, RT_WAITING_FOREVER, 0);
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
    lwp_mutex_release_safe(&tid_lock);

    if (tid <= 0)
    {
        LOG_W("resource TID exhausted.");
    }

    return tid;
}

/**
 * @brief Releases a thread ID (TID) and associated resources
 *
 * @param[in] tid The thread ID to release
 *
 * @note  This function performs thread-safe release of a TID by:
 *        1. Finding the TID in the AVL tree and removing it
 *        2. Adding the freed TID structure to the free list for reuse
 *        3. Handling thread reference counting and potential suspension
 */
void lwp_tid_put(int tid)
{
    struct lwp_avl_struct *p;
    rt_thread_t thread;
    rt_thread_t current;

    lwp_mutex_take_safe(&tid_lock, RT_WAITING_FOREVER, 0);
    p  = lwp_avl_find(tid, lwp_tid_root);
    if (p)
    {
        thread = p->data;
        p->data = RT_NULL;
        lwp_avl_remove(p, &lwp_tid_root);
        p->avl_right = lwp_tid_free_head;
        lwp_tid_free_head = p;
    }
    else
        thread = RT_NULL;

    if (thread && thread->tid_ref_count)
    {
        current = rt_thread_self();
        RT_ASSERT(thread->susp_recycler == RT_NULL);
        thread->susp_recycler = current;

        rt_enter_critical();
        rt_thread_suspend_with_flag(current, RT_UNINTERRUPTIBLE);
        lwp_mutex_release_safe(&tid_lock);
        rt_exit_critical();

        rt_schedule();
    }
    else
        lwp_mutex_release_safe(&tid_lock);
}

/**
 * @brief Retrieves the thread object associated with a thread ID (TID)
 *
 * @param[in] tid The thread ID to look up
 *
 * @return rt_thread_t The associated thread object, or RT_NULL if not found
 */
rt_thread_t lwp_tid_get_thread_raw(int tid)
{
    struct lwp_avl_struct *p;
    rt_thread_t thread = RT_NULL;

    p  = lwp_avl_find(tid, lwp_tid_root);
    if (p)
    {
        thread = (rt_thread_t)p->data;
    }
    return thread;
}

/**
 * @brief Retrieves a thread object by TID and increments its reference count
 *
 * @param[in] tid The thread ID to look up (0 means current thread)
 *
 * @return rt_thread_t The associated thread object, or RT_NULL if not found
 *
 * @note This function provides thread-safe access to a thread object while:
 *       1. Acquiring the tid_lock mutex for synchronization
 *       2. Looking up the thread by TID (or returning current thread if tid=0)
 *       3. Incrementing the thread's reference count if found
 *       4. Releasing the mutex before returning
 */
rt_thread_t lwp_tid_get_thread_and_inc_ref(int tid)
{
    rt_thread_t thread = RT_NULL;

    lwp_mutex_take_safe(&tid_lock, RT_WAITING_FOREVER, 0);
    thread = tid ? lwp_tid_get_thread_raw(tid) : rt_thread_self();
    if (thread != RT_NULL)
    {
        thread->tid_ref_count += 1;
    }
    lwp_mutex_release_safe(&tid_lock);
    return thread;
}

/**
 * @brief Decrement the reference count of a thread and potentially resume its suspender
 *
 * @param[in] thread The thread object whose reference count needs to be decremented
 *
 * @note This function safely decreases the reference count of a thread object. If the reference
 *       count reaches zero and there is a suspender thread waiting (susp_recycler), it will
 *       be resumed.
 */
void lwp_tid_dec_ref(rt_thread_t thread)
{
    rt_thread_t susp_putter;
    if (thread)
    {
        RT_ASSERT(rt_object_get_type(&thread->parent) == RT_Object_Class_Thread);
        susp_putter = thread->susp_recycler;
        lwp_mutex_take_safe(&tid_lock, RT_WAITING_FOREVER, 0);

        RT_ASSERT(thread->tid_ref_count > 0);
        thread->tid_ref_count -= 1;
        if (!thread->tid_ref_count && susp_putter)
        {
            rt_thread_resume(susp_putter);
        }
        lwp_mutex_release_safe(&tid_lock);
    }
}

/**
 * @brief Associate a thread with a given TID in the thread ID management system
 *
 * @param[in] tid The thread ID to associate with the thread
 * @param[in] thread The thread object to be associated with the TID
 *
 * @note This function safely associates a thread object with a specified thread ID (TID)
 *       in the system's AVL tree. The operation is protected by a mutex to ensure thread safety.
 */
void lwp_tid_set_thread(int tid, rt_thread_t thread)
{
    struct lwp_avl_struct *p;

    lwp_mutex_take_safe(&tid_lock, RT_WAITING_FOREVER, 0);
    p  = lwp_avl_find(tid, lwp_tid_root);
    if (p)
    {
        RT_ASSERT(p->data == RT_NULL);
        p->data = thread;
    }
    lwp_mutex_release_safe(&tid_lock);
}
