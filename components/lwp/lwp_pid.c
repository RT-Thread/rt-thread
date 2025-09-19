/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-16     zhangjun     first version
 * 2021-02-20     lizhirui     fix warning
 * 2023-06-26     shell        clear ref to parent on waitpid()
 *                             Remove recycling of lwp on waitpid() and leave it to defunct routine
 * 2023-07-27     shell        Move the detach of children process on parent exit to lwp_terminate.
 *                             Make lwp_from_pid locked by caller to avoid possible use-after-free
 *                             error
 * 2023-10-27     shell        Format codes of sys_exit(). Fix the data racing where lock is missed
 *                             Add reference on pid/tid, so the resource is not freed while using.
 *                             Add support for waitpid(options=WNOHANG)
 * 2023-11-16     xqyjlj       Fix the case where pid is 0
 * 2023-11-17     xqyjlj       add process group and session support
 * 2023-11-24     shell        Support of waitpid(options=WNOTRACED|WCONTINUED);
 *                             Reimplement the waitpid with a wait queue method, and fixup problem
 *                             with waitpid(pid=-1)/waitpid(pid=-pgid)/waitpid(pid=0) that only one
 *                             process can be traced while waiter suspend
 * 2024-01-25     shell        porting to new sched API
 */

/* includes scheduler related API */
#define __RT_IPC_SOURCE__

/* for waitpid, we are compatible to GNU extension */
#define _GNU_SOURCE

#define DBG_TAG "lwp.pid"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "lwp_internal.h"

#include <rthw.h>
#include <rtthread.h>
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h> /* rename() */
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/statfs.h> /* statfs() */
#include <stdatomic.h>

#ifdef ARCH_MM_MMU
#include "lwp_user_mm.h"
#endif

#ifdef RT_USING_DFS_PROCFS
#include "proc.h"
#include "procfs.h"
#endif

#define PID_MAX 10000

#define PID_CT_ASSERT(name, x) \
    struct assert_##name {char ary[2 * (x) - 1];}

PID_CT_ASSERT(pid_min_nr, RT_LWP_MAX_NR > 1);
PID_CT_ASSERT(pid_max_nr, RT_LWP_MAX_NR < PID_MAX);

static struct lwp_avl_struct lwp_pid_ary[RT_LWP_MAX_NR];
static struct lwp_avl_struct *lwp_pid_free_head = RT_NULL;
static int lwp_pid_ary_alloced = 0;
static struct lwp_avl_struct *lwp_pid_root = RT_NULL;
static pid_t current_pid = 0;
static struct rt_mutex pid_mtx;
static struct rt_wqueue _pid_emptyq;

/**
 * @brief Initialize PID management structures
 *
 * @return int Always returns 0.
 */
int lwp_pid_init(void)
{
    rt_wqueue_init(&_pid_emptyq);
    rt_mutex_init(&pid_mtx, "pidmtx", RT_IPC_FLAG_PRIO);
    return 0;
}

/**
 * @brief Wait for an empty PID slot to become available
 *
 * @param[in] wait_flags Wait mode flags (RT_INTERRUPTIBLE, RT_KILLABLE or RT_UNINTERRUPTIBLE)
 * @param[in] to Timeout value in ticks (RT_WAITING_FOREVER for no timeout)
 *
 * @return int Error code (0 on success, negative on error)
 */
int lwp_pid_wait_for_empty(int wait_flags, rt_tick_t to)
{
    int error;

    if (wait_flags == RT_INTERRUPTIBLE)
    {
        error = rt_wqueue_wait_interruptible(&_pid_emptyq, 0, to);
    }
    else
    {
        error = rt_wqueue_wait_killable(&_pid_emptyq, 0, to);
    }
    return error;
}

/**
 * @brief Acquire the PID management mutex lock
 *
 * @note This is a blocking call that will wait indefinitely for the lock
 */
void lwp_pid_lock_take(void)
{
    LWP_DEF_RETURN_CODE(rc);

    rc = lwp_mutex_take_safe(&pid_mtx, RT_WAITING_FOREVER, 0);
    /* should never failed */
    RT_ASSERT(rc == RT_EOK);
    RT_UNUSED(rc);
}

/**
 * @brief Release the PID management mutex lock
 *
 * @note This function should be called after lwp_pid_lock_take()
 */
void lwp_pid_lock_release(void)
{
    /* should never failed */
    if (lwp_mutex_release_safe(&pid_mtx) != RT_EOK)
        RT_ASSERT(0);
}

/**
 * @brief Parameter structure for PID iteration callback
 *
 * @note This structure holds the callback function and context data used when
 *       iterating through process IDs.
 */
struct pid_foreach_param
{
    /**
     * @brief Callback function to execute for each PID
     * @param[in] pid The process ID being processed
     * @param[in,out] data User-provided context data
     * @return int Operation status (0 to continue, non-zero to stop)
     */
    int (*cb)(pid_t pid, void *data);
    void *data; /**< User-provided context data */
};

/**
 * @brief Callback function for PID iteration
 *
 * @param[in] node AVL tree node containing the PID
 * @param[in] data User-provided parameter structure
 *
 * @return int Operation status (0 to continue, non-zero to stop)
 */
static int _before_cb(struct lwp_avl_struct *node, void *data)
{
    struct pid_foreach_param *param = data;
    pid_t pid = node->avl_key;
    return param->cb(pid, param->data);
}

/**
 * @brief Iterate over all process IDs
 *
 * @param[in] cb Callback function to execute for each PID
 * @param[in] data User-provided context data
 *
 * @return int Error code (0 on success, negative on error)
 */
int lwp_pid_for_each(int (*cb)(pid_t pid, void *data), void *data)
{
    int error;
    struct pid_foreach_param buf =
    {
        .cb = cb,
        .data = data,
    };

    lwp_pid_lock_take();
    error = lwp_avl_traversal(lwp_pid_root, _before_cb, &buf);
    lwp_pid_lock_release();

    return error;
}

/**
 * @brief Get the PID array
 *
 * @return struct lwp_avl_struct* Pointer to the PID array
 */
struct lwp_avl_struct *lwp_get_pid_ary(void)
{
    return lwp_pid_ary;
}

/**
 * @brief Allocates a new PID while holding the PID management lock
 *
 * @return pid_t The newly allocated PID, or 0 if allocation failed
 *
 * @note This function attempts to allocate a new process ID (PID) from either:
 *       1. The free list (lwp_pid_free_head) if available
 *       2. The PID array (lwp_pid_ary) if within maximum limits
 *
 *       It then searches for an unused PID in two ranges:
 *       1. From current_pid+1 to PID_MAX
 *       2. From 1 to current_pid (if first search fails)
 *
 *       The allocated PID is inserted into the PID AVL tree (lwp_pid_root)
 *       and current_pid is updated to the new PID.
 */
static pid_t lwp_pid_get_locked(void)
{
    struct lwp_avl_struct *p;
    pid_t pid = 0;

    p = lwp_pid_free_head;
    if (p)
    {
        lwp_pid_free_head = (struct lwp_avl_struct *)p->avl_right;
    }
    else if (lwp_pid_ary_alloced < RT_LWP_MAX_NR)
    {
        p = lwp_pid_ary + lwp_pid_ary_alloced;
        lwp_pid_ary_alloced++;
    }
    if (p)
    {
        int found_noused = 0;

        RT_ASSERT(p->data == RT_NULL);
        for (pid = current_pid + 1; pid < PID_MAX; pid++)
        {
            if (!lwp_avl_find(pid, lwp_pid_root))
            {
                found_noused = 1;
                break;
            }
        }
        if (!found_noused)
        {
            for (pid = 1; pid <= current_pid; pid++)
            {
                if (!lwp_avl_find(pid, lwp_pid_root))
                {
                    found_noused = 1;
                    break;
                }
            }
        }
        p->avl_key = pid;
        lwp_avl_insert(p, &lwp_pid_root);
        current_pid = pid;
    }
    return pid;
}

/**
 * @brief Release a PID back to the free list while holding the PID lock
 *
 * @param[in] pid The process ID to release (must not be 0)
 *
 * @note This function removes the specified PID from the active PID tree and
 *       adds it to the free list. The operation is performed atomically while
 *       holding the PID management lock.
 */
static void lwp_pid_put_locked(pid_t pid)
{
    struct lwp_avl_struct *p;

    if (pid == 0)
    {
        return;
    }

    p  = lwp_avl_find(pid, lwp_pid_root);
    if (p)
    {
        p->data = RT_NULL;
        lwp_avl_remove(p, &lwp_pid_root);
        p->avl_right = lwp_pid_free_head;
        lwp_pid_free_head = p;
    }
}

#ifdef RT_USING_DFS_PROCFS
    /**
     * @brief Free the proc dentry for the given LWP
     *
     * @param[in] lwp The LWP whose proc dentry is to be freed
     */
    rt_inline void _free_proc_dentry(rt_lwp_t lwp)
    {
        char pid_str[64] = {0};

        rt_snprintf(pid_str, 64, "%d", lwp->pid);
        pid_str[63] = 0;
        proc_remove_dentry(pid_str, 0);
    }
#else
    #define _free_proc_dentry(lwp)
#endif

/**
 * @brief Release a process ID and clean up associated resources
 *
 * @param[in,out] lwp The lightweight process whose PID should be released
 */
void lwp_pid_put(struct rt_lwp *lwp)
{
    _free_proc_dentry(lwp);

    lwp_pid_lock_take();
    lwp_pid_put_locked(lwp->pid);
    if (lwp_pid_root == AVL_EMPTY)
    {
        rt_wqueue_wakeup_all(&_pid_emptyq, RT_NULL);
        /* refuse any new pid allocation now */
    }
    else
    {
        lwp_pid_lock_release();
    }

    /* reset pid field */
    lwp->pid = 0;
    /* clear reference */
    lwp_ref_dec(lwp);
}

/**
 * @brief Set the LWP for a given PID while holding the PID lock
 *
 * @param[in] pid The process ID to set the LWP for
 * @param[in] lwp The LWP to associate with the PID
 *
 * @note This function associates the specified LWP with the given PID in the
 *       PID AVL tree. It increments the LWP's reference count and updates the
 *       proc filesystem entry if the PID is non-zero.
 */
static void lwp_pid_set_lwp_locked(pid_t pid, struct rt_lwp *lwp)
{
    struct lwp_avl_struct *p;

    p  = lwp_avl_find(pid, lwp_pid_root);
    if (p)
    {
        p->data = lwp;
        lwp_ref_inc(lwp);

#ifdef RT_USING_DFS_PROCFS
        if (pid)
        {
            proc_pid(pid);
        }
#endif
    }
}

/**
 * @brief Close all open files for the given LWP
 *
 * @param[in] lwp The LWP whose files should be closed
 *
 * @note This function iterates through all file descriptors in the LWP's file
 *       descriptor table, closing each open file. It is typically called when
 *       an LWP is being destroyed or when the LWP is switching to a new thread.
 */
static void __exit_files(struct rt_lwp *lwp)
{
    int fd = lwp->fdt.maxfd - 1;

    while (fd >= 0)
    {
        struct dfs_file *d;

        d = lwp->fdt.fds[fd];
        if (d)
        {
            dfs_file_close(d);
            fdt_fd_release(&lwp->fdt, fd);
        }
        fd--;
    }
}

/**
 * @brief Initialize the user object lock for a lightweight process
 *
 * @param[in,out] lwp The lightweight process structure whose object lock needs initialization
 */
void lwp_user_object_lock_init(struct rt_lwp *lwp)
{
    rt_mutex_init(&lwp->object_mutex, "lwp_obj", RT_IPC_FLAG_PRIO);
}

/**
 * @brief Destroy the user object lock for a lightweight process
 *
 * @param[in,out] lwp The lightweight process structure whose object lock needs destruction
 */
void lwp_user_object_lock_destroy(struct rt_lwp *lwp)
{
    rt_mutex_detach(&lwp->object_mutex);
}

/**
 * @brief Lock the user object lock for a lightweight process
 *
 * @param[in,out] lwp The lightweight process structure whose object lock needs locking
 */
void lwp_user_object_lock(struct rt_lwp *lwp)
{
    if (lwp)
    {
        rt_mutex_take(&lwp->object_mutex, RT_WAITING_FOREVER);
    }
    else
    {
        RT_ASSERT(0);
    }
}

/**
 * @brief Unlock the user object lock for a lightweight process
 *
 * @param[in,out] lwp The lightweight process structure whose object lock needs unlocking
 */
void lwp_user_object_unlock(struct rt_lwp *lwp)
{
    if (lwp)
    {
        rt_mutex_release(&lwp->object_mutex);
    }
    else
    {
        RT_ASSERT(0);
    }
}

/**
 * @brief Add an object to the user object list of a lightweight process
 *
 * @param[in,out] lwp The lightweight process structure whose object list needs updating
 * @param[in] object The object to be added to the LWP's object list
 *
 * @return int Returns 0 on success, or -1 on failure
 */
int lwp_user_object_add(struct rt_lwp *lwp, rt_object_t object)
{
    int ret = -1;

    if (lwp && object)
    {
        lwp_user_object_lock(lwp);
        if (!lwp_avl_find((avl_key_t)object, lwp->object_root))
        {
            struct lwp_avl_struct *node;

            node = (struct lwp_avl_struct *)rt_malloc(sizeof(struct lwp_avl_struct));
            if (node)
            {
                rt_atomic_add(&object->lwp_ref_count, 1);
                node->avl_key = (avl_key_t)object;
                lwp_avl_insert(node, &lwp->object_root);
                ret = 0;
            }
        }
        lwp_user_object_unlock(lwp);
    }
    return ret;
}

/**
 * @brief Delete a node from the user object list of a lightweight process
 *
 * @param[in,out] lwp The lightweight process structure whose object list needs updating
 * @param[in] node The node to be deleted from the LWP's object list
 *
 * @return rt_err_t Returns 0 on success, or -1 on failure
 */
static rt_err_t _object_node_delete(struct rt_lwp *lwp, struct lwp_avl_struct *node)
{
    rt_err_t ret = -1;
    rt_object_t object;

    if (!lwp || !node)
    {
        return ret;
    }
    object = (rt_object_t)node->avl_key;
    object->lwp_ref_count--;
    if (object->lwp_ref_count == 0)
    {
        /* remove from kernel object list */
        switch (object->type)
        {
        case RT_Object_Class_Semaphore:
            ret = rt_sem_delete((rt_sem_t)object);
            break;
        case RT_Object_Class_Mutex:
            ret = rt_mutex_delete((rt_mutex_t)object);
            break;
        case RT_Object_Class_Event:
            ret = rt_event_delete((rt_event_t)object);
            break;
        case RT_Object_Class_MailBox:
            ret = rt_mb_delete((rt_mailbox_t)object);
            break;
        case RT_Object_Class_MessageQueue:
            ret = rt_mq_delete((rt_mq_t)object);
            break;
        case RT_Object_Class_Timer:
            ret = rt_timer_delete((rt_timer_t)object);
            break;
        case RT_Object_Class_Custom:
            ret = rt_custom_object_destroy(object);
            break;
        default:
            LOG_E("input object type(%d) error", object->type);
            break;
        }
    }
    else
    {
        ret = 0;
    }
    lwp_avl_remove(node, &lwp->object_root);
    rt_free(node);
    return ret;
}

/**
 * @brief Delete an object from the user object list of a lightweight process
 *
 * @param[in,out] lwp The lightweight process structure whose object list needs updating
 * @param[in] object The object to be deleted from the LWP's object list
 *
 * @return rt_err_t Returns 0 on success, or -1 on failure
 */
rt_err_t lwp_user_object_delete(struct rt_lwp *lwp, rt_object_t object)
{
    rt_err_t ret = -1;

    if (lwp && object)
    {
        struct lwp_avl_struct *node;

        lwp_user_object_lock(lwp);
        node = lwp_avl_find((avl_key_t)object, lwp->object_root);
        ret = _object_node_delete(lwp, node);
        lwp_user_object_unlock(lwp);
    }
    return ret;
}

/**
 * @brief Clear all objects from the user object list of a lightweight process
 *
 * @param[in,out] lwp The lightweight process structure whose object list needs clearing
 */
void lwp_user_object_clear(struct rt_lwp *lwp)
{
    struct lwp_avl_struct *node;

    lwp_user_object_lock(lwp);
    while ((node = lwp_map_find_first(lwp->object_root)) != RT_NULL)
    {
        _object_node_delete(lwp, node);
    }
    lwp_user_object_unlock(lwp);
}

/**
 * @brief Callback function for duplicating objects in AVL tree traversal
 *
 * @param[in] node The AVL tree node containing the object to duplicate
 * @param[in,out] arg The destination lightweight process (cast to struct rt_lwp *)
 * @return int Always returns 0 to continue traversal
 *
 * @note This function is used as a callback during AVL tree traversal
 *       to duplicate objects from one process to another
 */
static int _object_dup(struct lwp_avl_struct *node, void *arg)
{
    rt_object_t object;
    struct rt_lwp *dst_lwp = (struct rt_lwp *)arg;

    object = (rt_object_t)node->avl_key;
    lwp_user_object_add(dst_lwp, object);
    return 0;
}

/**
 * @brief Duplicate all objects from one lightweight process to another
 *
 * @param[in,out] dst_lwp The destination lightweight process structure
 * @param[in] src_lwp The source lightweight process structure
 *
 * @note This function duplicates all objects from the source LWP to the destination LWP
 *       by traversing the source LWP's object list and adding each object to the destination LWP
 */
void lwp_user_object_dup(struct rt_lwp *dst_lwp, struct rt_lwp *src_lwp)
{
    lwp_user_object_lock(src_lwp);
    lwp_avl_traversal(src_lwp->object_root, _object_dup, dst_lwp);
    lwp_user_object_unlock(src_lwp);
}

/**
 * @brief Create a new lightweight process (LWP)
 *
 * @param[in] flags Creation flags that control LWP behavior
 *        - LWP_CREATE_FLAG_NOTRACE_EXEC: Don't trace exec operations
 *        - LWP_CREATE_FLAG_ALLOC_PID: Allocate a PID for the LWP
 *        - LWP_CREATE_FLAG_INIT_USPACE: Initialize user space
 *
 * @return Pointer to newly created LWP structure on success
 *        - RT_NULL on failure (pid allocation failed or user space init failed)
 */
rt_lwp_t lwp_create(rt_base_t flags)
{
    pid_t pid;
    rt_lwp_t new_lwp = rt_calloc(1, sizeof(struct rt_lwp));

    if (new_lwp)
    {
        /* minimal setup of lwp object */
        new_lwp->ref = 1;
#ifdef RT_USING_SMP
        new_lwp->bind_cpu = RT_CPUS_NR;
#endif
        new_lwp->exe_file = RT_NULL;
        rt_list_init(&new_lwp->t_grp);
        rt_list_init(&new_lwp->pgrp_node);
        rt_list_init(&new_lwp->timer);
        lwp_user_object_lock_init(new_lwp);
        rt_wqueue_init(&new_lwp->wait_queue);
        rt_wqueue_init(&new_lwp->waitpid_waiters);
        lwp_signal_init(&new_lwp->signal);
        rt_mutex_init(&new_lwp->lwp_lock, "lwp_lock", RT_IPC_FLAG_PRIO);

        if (flags & LWP_CREATE_FLAG_NOTRACE_EXEC)
            new_lwp->did_exec = RT_TRUE;

        /* lwp with pid */
        if (flags & LWP_CREATE_FLAG_ALLOC_PID)
        {
            lwp_pid_lock_take();
            pid = lwp_pid_get_locked();
            if (pid == 0)
            {
                lwp_user_object_lock_destroy(new_lwp);
                rt_free(new_lwp);
                new_lwp = RT_NULL;
                LOG_E("%s: pid slot fulled", __func__);
            }
            else
            {
                new_lwp->pid = pid;
                lwp_pid_set_lwp_locked(pid, new_lwp);
            }
            lwp_pid_lock_release();
        }
        rt_memset(&new_lwp->rt_rusage,0, sizeof(new_lwp->rt_rusage));

        if (flags & LWP_CREATE_FLAG_INIT_USPACE)
        {
            rt_err_t error = lwp_user_space_init(new_lwp, 0);
            if (error)
            {
                lwp_pid_put(new_lwp);
                lwp_user_object_lock_destroy(new_lwp);
                rt_free(new_lwp);
                new_lwp = RT_NULL;
                LOG_E("%s: failed to initialize user space", __func__);
            }
        }
    }

    LOG_D("%s(pid=%d) => %p", __func__, new_lwp ? new_lwp->pid : -1, new_lwp);
    return new_lwp;
}

/**
 * @brief Free all resources associated with a lightweight process (LWP)
 *
 * @param[in,out] lwp Lightweight process to be freed
 *
 * @note when reference is 0, a lwp can be released
 */
void lwp_free(struct rt_lwp* lwp)
{
    rt_processgroup_t group = RT_NULL;

    if (lwp == RT_NULL)
    {
        return;
    }

    /**
     * Brief: Recycle the lwp when reference is cleared
     *
     * Note: Critical Section
     * - lwp (RW. there is no other writer/reader compete with lwp_free, since
     *   all the reference is clear)
     */
    LOG_D("lwp free: %p", lwp);
    rt_free(lwp->exe_file);
    group = lwp_pgrp_find(lwp_pgid_get_byprocess(lwp));
    if (group)
        lwp_pgrp_remove(group, lwp);

    LWP_LOCK(lwp);

    if (lwp->args != RT_NULL)
    {
#ifndef ARCH_MM_MMU
        lwp->args_length = RT_NULL;
#ifndef ARCH_MM_MPU
        rt_free(lwp->args);
#endif /* not defined ARCH_MM_MPU */
#endif /* ARCH_MM_MMU */
        lwp->args = RT_NULL;
    }

    lwp_user_object_clear(lwp);
    lwp_user_object_lock_destroy(lwp);

    /* free data section */
    if (lwp->data_entry != RT_NULL)
    {
#ifdef ARCH_MM_MMU
        rt_free_align(lwp->data_entry);
#else
#ifdef ARCH_MM_MPU
        rt_lwp_umap_user(lwp, lwp->text_entry, 0);
        rt_lwp_free_user(lwp, lwp->data_entry, lwp->data_size);
#else
        rt_free_align(lwp->data_entry);
#endif /* ARCH_MM_MPU */
#endif /* ARCH_MM_MMU */
        lwp->data_entry = RT_NULL;
    }

    /* free text section */
    if (lwp->lwp_type == LWP_TYPE_DYN_ADDR)
    {
        if (lwp->text_entry)
        {
            LOG_D("lwp text free: %p", lwp->text_entry);
#ifndef ARCH_MM_MMU
            rt_free((void*)lwp->text_entry);
#endif /* not defined ARCH_MM_MMU */
            lwp->text_entry = RT_NULL;
        }
    }

#ifdef ARCH_MM_MMU
    lwp_unmap_user_space(lwp);
#endif
    timer_list_free(&lwp->timer);

    LWP_UNLOCK(lwp);
    RT_ASSERT(lwp->lwp_lock.owner == RT_NULL);
    rt_mutex_detach(&lwp->lwp_lock);

    /**
     * pid must have release before enter lwp_free()
     * otherwise this is a data racing
     */
    RT_ASSERT(lwp->pid == 0);
    rt_free(lwp);
}

/**
 * @brief Handle thread exit cleanup for a lightweight process
 *
 * @param[in,out] lwp Lightweight process containing the thread
 * @param[in,out] thread Thread to be exited
 *
 * @note This function performs the following operations:
 *       - Updates process resource usage statistics (system and user time)
 *       - Removes thread from process sibling list
 *       - Handles futex robust list cleanup
 *       - Releases thread ID (TID)
 *       - Deletes the thread
 *       - Enters infinite loop (noreturn function)
 */
rt_inline rt_noreturn
void _thread_exit(rt_lwp_t lwp, rt_thread_t thread)
{
    LWP_LOCK(lwp);
    lwp->rt_rusage.ru_stime.tv_sec += thread->system_time / RT_TICK_PER_SECOND;
    lwp->rt_rusage.ru_stime.tv_usec += thread->system_time % RT_TICK_PER_SECOND * (1000000 / RT_TICK_PER_SECOND);
    lwp->rt_rusage.ru_utime.tv_sec += thread->user_time / RT_TICK_PER_SECOND;
    lwp->rt_rusage.ru_utime.tv_usec += thread->user_time % RT_TICK_PER_SECOND * (1000000 / RT_TICK_PER_SECOND);
    rt_list_remove(&thread->sibling);
    LWP_UNLOCK(lwp);
    lwp_futex_exit_robust_list(thread);

    /**
     * Note: the tid tree always hold a reference to thread, hence the tid must
     * be release before cleanup of thread
     */
    lwp_tid_put(thread->tid);
    thread->tid = 0;

    rt_thread_delete(thread);
    rt_schedule();
    while (1) ;
}

/**
 * @brief Clear child thread ID notification for parent process
 *
 * @param[in,out] thread Thread whose child tid needs to be cleared
 *
 * @note This function performs the following operations:
 *       - Checks if clear_child_tid pointer is set
 *       - Writes 0 to user-space memory location if set
 *       - Wakes any futex waiters on that location
 *       - Clears the thread's clear_child_tid pointer
 */
rt_inline void _clear_child_tid(rt_thread_t thread)
{
    if (thread->clear_child_tid)
    {
        int t = 0;
        int *clear_child_tid = thread->clear_child_tid;

        thread->clear_child_tid = RT_NULL;
        lwp_put_to_user(clear_child_tid, &t, sizeof t);
        sys_futex(clear_child_tid, FUTEX_WAKE, 1, RT_NULL, RT_NULL, 0);
    }
}

/**
 * @brief Terminates a lightweight process and cleans up its resources
 *
 * @param[in,out] lwp The lightweight process to terminate
 * @param[in] status The exit status to set for the process
 *
 * @note This function handles both MMU and non-MMU architectures differently.
 *       For MMU architectures, it clears child TID, sets exit status, and terminates.
 *       For non-MMU, it terminates the main thread and all subthreads.
 */
void lwp_exit(rt_lwp_t lwp, lwp_status_t status)
{
    rt_thread_t thread;

    if (!lwp)
    {
        LOG_W("%s: lwp should not be null", __func__);
        return ;
    }

    thread = rt_thread_self();
    RT_ASSERT((struct rt_lwp *)thread->lwp == lwp);
    LOG_D("process(lwp.pid=%d) exit", lwp->pid);

#ifdef ARCH_MM_MMU
    _clear_child_tid(thread);

    LWP_LOCK(lwp);
    /**
     * Brief: only one thread should calls exit_group(),
     * but we can not ensured that during run-time
     */
    lwp->lwp_status = status;
    LWP_UNLOCK(lwp);

    lwp_terminate(lwp);
#else
    main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
    if (main_thread == tid)
    {
        rt_thread_t sub_thread;
        rt_list_t *list;

        lwp_terminate(lwp);

        /* delete all subthread */
        while ((list = tid->sibling.prev) != &lwp->t_grp)
        {
            sub_thread = rt_list_entry(list, struct rt_thread, sibling);
            rt_list_remove(&sub_thread->sibling);
            rt_thread_delete(sub_thread);
        }
        lwp->lwp_ret = value;
    }
#endif /* ARCH_MM_MMU */

    _thread_exit(lwp, thread);
}

/**
 * @brief Handles thread exit for a lightweight process
 *
 * @param[in,out] thread The thread that is exiting
 * @param[in] status The exit status to set for the thread
 *
 * @note For MMU architectures, this function checks if the exiting thread is the
 *       header thread (main thread). If so, it treats it as a process exit.
 */
void lwp_thread_exit(rt_thread_t thread, int status)
{
    rt_thread_t header_thr;
    struct rt_lwp *lwp;

    LOG_D("%s", __func__);

    RT_ASSERT(thread == rt_thread_self());
    lwp = (struct rt_lwp *)thread->lwp;
    RT_ASSERT(lwp != RT_NULL);

#ifdef ARCH_MM_MMU
    _clear_child_tid(thread);

    LWP_LOCK(lwp);
    header_thr = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
    if (header_thr == thread && thread->sibling.prev == &lwp->t_grp)
    {
        /**
         * if thread exit, treated as process exit normally.
         * This is reasonable since trap event is exited through lwp_exit()
         */
        lwp->lwp_status = LWP_CREATE_STAT_EXIT(status);
        LWP_UNLOCK(lwp);

        lwp_terminate(lwp);
    }
    else
    {
        LWP_UNLOCK(lwp);
    }
#endif /* ARCH_MM_MMU */

    _thread_exit(lwp, thread);
}

/**
 * @brief Increments the reference count of a lightweight process
 *
 * @param[in,out] lwp The lightweight process whose reference count is to be incremented
 *
 * @return int The updated reference count after incrementing
 *
 * @note the reference is not for synchronization, but for the release of resource. the synchronization is done through lwp & pid lock.
 */
int lwp_ref_inc(struct rt_lwp *lwp)
{
    int ref;
    ref = rt_atomic_add(&lwp->ref, 1);
    LOG_D("%s(%p(%s)): before %d", __func__, lwp, lwp->cmd, ref);

    return ref;
}

/**
 * @brief Decrements the reference count of a lightweight process (LWP)
 *
 * @param[in,out] lwp The lightweight process whose reference count to decrement
 *
 * @return int The reference count before decrementing
 *
 * @note This function atomically decrements the LWP's reference count.
 *       When the count reaches 1 (meaning this was the last reference):
 *       - For debug builds, sends a message to GDB server channel
 *       - For non-MMU architectures with shared memory support, frees shared memory
 *       - Calls lwp_free() to release all LWP resources
 */
int lwp_ref_dec(struct rt_lwp *lwp)
{
    int ref;

    ref = rt_atomic_add(&lwp->ref, -1);
    LOG_D("%s(lwp=%p,lwp->cmd=%s): before ref=%d", __func__, lwp, lwp->cmd, ref);

    if (ref == 1)
    {
        struct rt_channel_msg msg;

        if (lwp->debug)
        {
            memset(&msg, 0, sizeof msg);
            rt_raw_channel_send(gdb_server_channel(), &msg);
        }

#ifndef ARCH_MM_MMU
#ifdef RT_LWP_USING_SHM
        lwp_shm_lwp_free(lwp);
#endif /* RT_LWP_USING_SHM */
#endif /* not defined ARCH_MM_MMU */
        lwp_free(lwp);
    }
    else
    {
        /* reference must be a positive integer */
        RT_ASSERT(ref > 1);
    }

    return ref;
}

/**
 * @brief Retrieves a lightweight process (LWP) by its PID while holding the lock
 *
 * @param[in] pid The process ID to look up
 *
 * @return struct rt_lwp* Pointer to the LWP structure if found, RT_NULL otherwise
 *
 * @note This function performs a raw lookup in the PID AVL tree while assuming
 *       the caller already holds the necessary locks. It's a lower-level version
 *       of lwp_from_pid() that doesn't handle locking internally.
 */
struct rt_lwp* lwp_from_pid_raw_locked(pid_t pid)
{
    struct lwp_avl_struct *p;
    struct rt_lwp *lwp = RT_NULL;

    p  = lwp_avl_find(pid, lwp_pid_root);
    if (p)
    {
        lwp = (struct rt_lwp *)p->data;
    }

    return lwp;
}

/**
 * @brief Retrieves a lightweight process (LWP) by PID with lock handling
 *
 * @param[in] pid The process ID to look up (0 means current process)
 *
 * @return struct rt_lwp* Pointer to the LWP structure if found, current LWP if pid=0
 *
 * @note This is a convenience wrapper that:
 *       - If pid is non-zero, calls lwp_from_pid_raw_locked()
 *       - If pid is zero, returns the current LWP via lwp_self()
 */
struct rt_lwp* lwp_from_pid_locked(pid_t pid)
{
    struct rt_lwp* lwp;
    lwp = pid ? lwp_from_pid_raw_locked(pid) : lwp_self();
    return lwp;
}

/**
 * @brief Converts a lightweight process (LWP) to its PID
 *
 * @param[in] lwp The LWP structure to convert
 *
 * @return pid_t The PID of the LWP, or 0 if lwp is NULL
 */
pid_t lwp_to_pid(struct rt_lwp* lwp)
{
    if (!lwp)
    {
        return 0;
    }
    return lwp->pid;
}

/**
 * @brief Convert process ID to process name
 *
 * @param[in] pid Process ID to look up
 *
 * @return char* Pointer to the process name (without path) if found, or RT_NULL if not found
 */
char* lwp_pid2name(int32_t pid)
{
    struct rt_lwp *lwp;
    char* process_name = RT_NULL;

    lwp_pid_lock_take();
    lwp = lwp_from_pid_locked(pid);
    if (lwp)
    {
        process_name = strrchr(lwp->cmd, '/');
        process_name = process_name? process_name + 1: lwp->cmd;
    }
    lwp_pid_lock_release();

    return process_name;
}

/**
 * @brief Convert process name to process ID
 *
 * @param[in] name Process name to look up (without path)
 *
 * @return pid_t Process ID if found, or 0 if not found
 *
 * @note The function only returns PIDs for processes whose main thread
 *          is not in CLOSED state.
 */
pid_t lwp_name2pid(const char *name)
{
    int idx;
    pid_t pid = 0;
    rt_thread_t main_thread;
    char* process_name = RT_NULL;
    rt_sched_lock_level_t slvl;

    lwp_pid_lock_take();
    for (idx = 0; idx < RT_LWP_MAX_NR; idx++)
    {
        /* 0 is reserved */
        struct rt_lwp *lwp = (struct rt_lwp *)lwp_pid_ary[idx].data;

        if (lwp)
        {
            process_name = strrchr(lwp->exe_file, '/');
            process_name = process_name? process_name + 1: lwp->cmd;
            if (!rt_strncmp(name, process_name, RT_NAME_MAX))
            {
                main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
                rt_sched_lock(&slvl);
                if (!(rt_sched_thread_get_stat(main_thread) == RT_THREAD_CLOSE))
                {
                    pid = lwp->pid;
                }
                rt_sched_unlock(slvl);
            }
        }
    }
    lwp_pid_lock_release();
    return pid;
}

/**
 * @brief Get the process ID of the current lightweight process (LWP)
 *
 * @return pid_t Process ID of the current LWP
 */
int lwp_getpid(void)
{
    rt_lwp_t lwp = lwp_self();
    return lwp ? lwp->pid : 1;
    /* return ((struct rt_lwp *)rt_thread_self()->lwp)->pid; */
}

/**
 * @brief Update resource usage statistics from child to parent process
 *
 * @param[in] child Child process containing resource usage data
 * @param[in] self_lwp Current lightweight process (parent)
 * @param[in,out] uru Pointer to user-space rusage structure to update
 *
 * @note This function:
 *       - Copies system and user time from child process
 *       - Only updates if uru pointer is not NULL
 *       - Uses lwp_data_put to safely write to user-space memory
 */
rt_inline void _update_ru(struct rt_lwp *child, struct rt_lwp *self_lwp, struct rusage *uru)
{
    struct rusage rt_rusage;
    if (uru != RT_NULL)
    {
        rt_rusage.ru_stime.tv_sec = child->rt_rusage.ru_stime.tv_sec;
        rt_rusage.ru_stime.tv_usec = child->rt_rusage.ru_stime.tv_usec;
        rt_rusage.ru_utime.tv_sec = child->rt_rusage.ru_utime.tv_sec;
        rt_rusage.ru_utime.tv_usec = child->rt_rusage.ru_utime.tv_usec;
        lwp_data_put(self_lwp, uru, &rt_rusage, sizeof(*uru));
    }
}

/**
 * @brief Collects statistics and reaps a terminated child process
 *
 * @param[in] child The child process to collect statistics from
 * @param[in] cur_thr The current thread context
 * @param[in,out] self_lwp The parent process (current LWP)
 * @param[out] ustatus Pointer to store child's exit status (optional)
 * @param[in] options Wait options (e.g., WNOWAIT)
 * @param[in,out] uru Pointer to resource usage structure to update (optional)
 *
 * @return rt_err_t Returns RT_EOK on success
 *
 * @note Updates resource usage statistics and optionally reaps the child process
 */
static rt_err_t _stats_and_reap_child(rt_lwp_t child, rt_thread_t cur_thr,
                                      struct rt_lwp *self_lwp, int *ustatus,
                                      int options, struct rusage *uru)
{
    int lwp_stat = child->lwp_status;

    /* report statistical data to process */
    _update_ru(child, self_lwp, uru);

    if (child->terminated && !(options & WNOWAIT))
    {
        /** Reap the child process if it's exited */
        LOG_D("func %s: child detached", __func__);
        lwp_pid_put(child);
        lwp_children_unregister(self_lwp, child);
    }

    if (ustatus)
        lwp_data_put(self_lwp, ustatus, &lwp_stat, sizeof(*ustatus));

    return RT_EOK;
}

#define HAS_CHILD_BUT_NO_EVT (-1024)

/**
 * @brief Queries process state change events from a child process
 *
 * @param[in] child The child process to query
 * @param[in] cur_thr The current thread context
 * @param[in] self_lwp The parent process (current LWP)
 * @param[in] options Wait options (e.g., WSTOPPED)
 * @param[out] status Pointer to store child's status (optional)
 *
 * @return sysret_t Returns child PID if event found, or HAS_CHILD_BUT_NO_EVT
 *
 * @note Checks for termination or stopped state changes in child process
 */
static sysret_t _query_event_from_lwp(rt_lwp_t child, rt_thread_t cur_thr, rt_lwp_t self_lwp,
                                      int options, int *status)
{
    sysret_t rc;

    LWP_LOCK(child);
    if (child->terminated)
    {
        rc = child->pid;
    }
    else if ((options & WSTOPPED) && child->jobctl_stopped && !child->wait_reap_stp)
    {
        child->wait_reap_stp = 1;
        rc = child->pid;
    }
    else
    {
        rc = HAS_CHILD_BUT_NO_EVT;
    }
    LWP_UNLOCK(child);

    LOG_D("%s(child_pid=%d ('%s'), stopped=%d) => %d", __func__, child->pid, child->cmd, child->jobctl_stopped, rc);
    return rc;
}

/**
 * @brief Verifies and reaps a child process if conditions are met
 *
 * @param[in] cur_thr Current thread context
 * @param[in] self_lwp Parent process (current LWP)
 * @param[in] wait_pid PID of child process to verify
 * @param[in] options Wait options (e.g., WNOHANG)
 * @param[out] ustatus Pointer to store child's exit status (optional)
 * @param[in,out] uru Pointer to resource usage structure (optional)
 *
 * @return pid_t Returns child PID if valid and event found, error code otherwise
 *
 * @note Verifies child-parent relationship and checks for termination/stopped state
 */
static pid_t _verify_child_and_reap(rt_thread_t cur_thr, rt_lwp_t self_lwp,
                                       pid_t wait_pid, int options, int *ustatus,
                                       struct rusage *uru)
{
    sysret_t rc;
    struct rt_lwp *child;

    /* check if pid is reference to a valid child */
    lwp_pid_lock_take();
    child = lwp_from_pid_locked(wait_pid);
    if (!child)
        rc = -EINVAL;
    else if (child->parent != self_lwp)
        rc = -ESRCH;
    else
        rc = wait_pid;

    lwp_pid_lock_release();

    if (rc > 0)
    {
        rc = _query_event_from_lwp(child, cur_thr, self_lwp, options, ustatus);
        if (rc > 0)
        {
            _stats_and_reap_child(child, cur_thr, self_lwp, ustatus, options, uru);
        }
    }
    return rc;
}

/**
 * @brief Reaps any child process with given pair_pgid that has terminated or stopped
 *
 * @param[in] cur_thr Current thread context
 * @param[in] self_lwp Parent process (current LWP)
 * @param[in] pair_pgid Process group ID to match (0 for any)
 * @param[in] options Wait options (e.g., WNOHANG)
 * @param[out] ustatus Pointer to store child's exit status (optional)
 * @param[in,out] uru Pointer to resource usage structure (optional)
 *
 * @return pid_t Returns child PID if found and event occurred, error code otherwise
 *
 * @note Iterates through child processes to find one that matches given pair_pgid
 */
static pid_t _reap_any_child_pid(rt_thread_t cur_thr, rt_lwp_t self_lwp, pid_t pair_pgid,
                                 int options, int *ustatus, struct rusage *uru)
{
    sysret_t rc = -ECHILD;
    struct rt_lwp *child;

    LWP_LOCK(self_lwp);
    child = self_lwp->first_child;

    /* find a exited child if any */
    while (child)
    {
        if (pair_pgid && child->pgid != pair_pgid)
            continue;

        rc = _query_event_from_lwp(child, cur_thr, self_lwp, options, ustatus);
        if (rc > 0)
            break;

        child = child->sibling;
    }
    LWP_UNLOCK(self_lwp);

    if (rc > 0)
    {
        _stats_and_reap_child(child, cur_thr, self_lwp, ustatus, options, uru);
    }
    return rc;
}

/**
 * @brief Wakes up processes waiting for a child process status change
 *
 * @param[in] parent Parent process to notify
 * @param[in] self_lwp Child process that triggered the wakeup
 *
 * @return rt_err_t Returns RT_EOK on success
 *
 * @note Uses wait queue to notify parent process about child status changes
 */
rt_err_t lwp_waitpid_kick(rt_lwp_t parent, rt_lwp_t self_lwp)
{
    /* waker provide the message mainly through its lwp_status */
    rt_wqueue_wakeup(&parent->waitpid_waiters, self_lwp);
    return RT_EOK;
}

/**
 * @brief Waitpid handle structure for process status change notifications
 *
 * @note This structure is used to manage wait queue entries for processes waiting
 *       for child process status changes.
 */
struct waitpid_handle {
    struct rt_wqueue_node wq_node; /**< Wait queue node for process status change notifications */
    int options;                   /**< Wait options (e.g., WNOHANG, WUNTRACED) */
    rt_lwp_t waker_lwp;            /**< LWP that triggered the wakeup */
};

/**
 * @brief Filter function for wait queue to determine if a process status change event should be accepted
 *
 * @param[in] wait_node Wait queue node containing filter criteria
 * @param[in] key Pointer to the lightweight process (waker_lwp) triggering the event
 *
 * @return int 0 if event should be accepted (matches criteria), 1 if event should be discarded
 *
 * @note The function handles three cases for process matching:
 *       - Positive destiny: Exact PID match
 *       - destiny == -1: Any child process of waiter
 *       - destiny == 0/-pgid: Process group matching
 */
static int _waitq_filter(struct rt_wqueue_node *wait_node, void *key)
{
    int can_accept_evt = 0;
    rt_thread_t waiter = wait_node->polling_thread;
    pid_t destiny = (pid_t)wait_node->key;
    rt_lwp_t waker_lwp = key;
    struct waitpid_handle *handle;
    rt_ubase_t options;

    handle = rt_container_of(wait_node, struct waitpid_handle, wq_node);

    RT_ASSERT(waiter != RT_NULL);
    options = handle->options;

    /* filter out if waker is not the one */
    if (destiny > 0)
    {
        /**
         * in waitpid immediately return routine, we already do the check
         * that pid is one of the child process of waiting thread
         */
        can_accept_evt = waker_lwp->pid == destiny;
    }
    else if (destiny == -1)
    {
        can_accept_evt = waker_lwp->parent == waiter->lwp;
    }
    else
    {
        /* destiny == 0 || destiny == -pgid */
        pid_t waiter_pgid;
        if (destiny == 0)
        {
            waiter_pgid = lwp_pgid_get_byprocess(waiter->lwp);
        }
        else
        {
            waiter_pgid = -destiny;
        }
        can_accept_evt = waiter_pgid == lwp_pgid_get_byprocess(waker_lwp);
    }

    /* filter out if event is not desired */
    if (can_accept_evt)
    {
        if ((options & WEXITED) && waker_lwp->terminated)
            can_accept_evt = 1;
        else if ((options & WSTOPPED) && WIFSTOPPED(waker_lwp->lwp_status))
            can_accept_evt = 1;
        else if ((options & WCONTINUED) && WIFCONTINUED(waker_lwp->lwp_status))
            can_accept_evt = 1;
        else
            can_accept_evt = 0;
    }

    /* setup message for waiter if accepted */
    if (can_accept_evt)
        handle->waker_lwp = waker_lwp;

    /* 0 if event is accepted, otherwise discard */
    return !can_accept_evt;
}

/**
 * @brief Wait for a child process status change event
 *
 * @param[in] cur_thr Current thread context that will be suspended
 * @param[in] self_lwp Lightweight process (parent) waiting for the event
 * @param[in,out] handle Waitpid handle containing filter criteria and wait queue node
 * @param[in] destiny Process ID or process group to wait for (-1 for any child, -pgid for process group)
 *
 * @return rt_err_t RT_EOK on success, negative error code on failure
 *
 * @note This function suspends the current thread to wait for a child process status change
 *       event that matches the specified criteria (process ID or process group).
 */
static rt_err_t _wait_for_event(rt_thread_t cur_thr, rt_lwp_t self_lwp,
                                struct waitpid_handle *handle, pid_t destiny)
{
    rt_err_t ret;

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(RT_TRUE);

    handle->wq_node.polling_thread = cur_thr;
    handle->wq_node.key = destiny;
    handle->wq_node.wakeup = _waitq_filter;
    handle->wq_node.wqueue = &self_lwp->waitpid_waiters;
    rt_list_init(&handle->wq_node.list);

    cur_thr->error = RT_EOK;

    LOG_D("%s(self_lwp=%d) wait for event", __func__, self_lwp->pid);

    rt_enter_critical();
    ret = rt_thread_suspend_with_flag(cur_thr, RT_INTERRUPTIBLE);
    if (ret == RT_EOK)
    {
        rt_wqueue_add(handle->wq_node.wqueue, &handle->wq_node);
        rt_exit_critical();

        rt_schedule();

        ret = cur_thr->error;

        /**
         * cur_thr error is a positive value, but some legacy implementation
         * use a negative one. So we check to avoid errors
         */
        ret = ret > 0 ? -ret : ret;

        /**
         * we dont rely on this actually, but we cleanup it since wakeup API
         * set this up durint operation, and this will cause some messy condition
         */
        handle->wq_node.wqueue->flag = RT_WQ_FLAG_CLEAN;
        rt_wqueue_remove(&handle->wq_node);
    }
    else
    {
        /* failed to suspend, return immediately with failure */
        rt_exit_critical();
    }

    return ret;
}

/**
 * @brief Wait for and reap a child process status change
 *
 * @param[in] cur_thr Current thread context
 * @param[in] self_lwp Lightweight process (parent) waiting for the child
 * @param[in] pid Process ID to wait for (-1 for any child, -pgid for process group)
 * @param[in] options Wait options (WNOHANG, WUNTRACED, etc.)
 * @param[out] ustatus Pointer to store child exit status
 * @param[in,out] uru Pointer to resource usage structure to update
 *
 * @return sysret_t PID of the child process that changed status, or error code
 *
 * @note The function:
 *       - Uses _wait_for_event to wait for status changes
 *       - Calls _stats_and_reap_child if a matching child is found
 */
static sysret_t _wait_and_reap(rt_thread_t cur_thr, rt_lwp_t self_lwp, const pid_t pid,
                               int options, int *ustatus, struct rusage *uru)
{
    sysret_t rc;
    struct waitpid_handle handle;
    rt_lwp_t waker;

    /* wait for SIGCHLD or other async events */
    handle.options = options;
    handle.waker_lwp = 0;
    rc = _wait_for_event(cur_thr, self_lwp, &handle, pid);

    waker = handle.waker_lwp;
    if (waker != RT_NULL)
    {
        rc = waker->pid;

        /* check out if any process exited */
        LOG_D("%s: woken up by lwp=%d", __func__, waker->pid);
        _stats_and_reap_child(waker, cur_thr, self_lwp, ustatus, options, uru);
    }
    /**
     * else if (rc != RT_EOK)
     * unable to do a suspend, or wakeup unexpectedly
     * -> then returned a failure
     */

    return rc;
}

/**
 * @brief Wait for process termination and return status
 *
 * @param[in] pid Process ID to wait for:
 *                >0 - specific child process
 *                -1 - any child process
 *                -pgid - any child in process group
 *                0 - any child in caller's process group
 * @param[out] status Pointer to store child exit status (optional)
 * @param[in] options Wait options (WNOHANG, WUNTRACED, etc.)
 * @param[in,out] ru Pointer to resource usage structure (optional)
 *
 * @return pid_t PID of the child that changed state, or:
 *         -1 on error
 *         0 if WNOHANG and no child status available
 *
 * @note The function handles three cases:
 *       - Specific PID wait (pid > 0)
 *       - Any child wait (pid == -1)
 *       - Process group wait (pid == 0 or pid < -1)
 */
pid_t lwp_waitpid(const pid_t pid, int *status, int options, struct rusage *ru)
{
    pid_t rc = -1;
    struct rt_thread *cur_thr;
    struct rt_lwp *self_lwp;

    cur_thr = rt_thread_self();
    self_lwp = lwp_self();

    if (!cur_thr || !self_lwp)
    {
        rc = -EINVAL;
    }
    else
    {
        /* check if able to reap desired child immediately */
        if (pid > 0)
        {
            /* if pid is child then try to reap it */
            rc = _verify_child_and_reap(cur_thr, self_lwp, pid, options, status, ru);
        }
        else if (pid == -1)
        {
            /* any terminated child */
            rc = _reap_any_child_pid(cur_thr, self_lwp, 0, options, status, ru);
        }
        else
        {
            /**
             * (pid < -1 || pid == 0)
             * any terminated child with matched pgid
             */

            pid_t pair_pgid;
            if (pid == 0)
            {
                pair_pgid = lwp_pgid_get_byprocess(self_lwp);
            }
            else
            {
                pair_pgid = -pid;
            }
            rc = _reap_any_child_pid(cur_thr, self_lwp, pair_pgid, options, status, ru);
        }

        if (rc == HAS_CHILD_BUT_NO_EVT)
        {
            if (!(options & WNOHANG))
            {
                /* otherwise, arrange a suspend and wait for async event */
                options |= WEXITED;
                rc = _wait_and_reap(cur_thr, self_lwp, pid, options, status, ru);
            }
            else
            {
                /**
                 * POSIX.1: If waitpid() was invoked with WNOHANG set in options,
                 * it has at least one child process specified by pid for which
                 * status is not available, and status is not available for any
                 * process specified by pid, 0 is returned
                 */
                rc = 0;
            }
        }
        else
        {
            RT_ASSERT(rc != 0);
        }
    }

    LOG_D("waitpid() => %d, *status=0x%x", rc, status ? *status:0);
    return rc;
}

/**
 * @brief Waits for a child process to terminate
 *
 * @param[in] pid The process ID to wait for
 * @param[out] status Pointer to store child exit status (optional)
 * @param[in] options Wait options (e.g., WNOHANG, WUNTRACED)
 *
 * @return pid_t The process ID of the child whose state changed,
 *         -1 on error, or 0 if WNOHANG was specified and no child was available
 *
 * @note This is a wrapper function that calls lwp_waitpid with NULL for the resource usage parameter
 */
pid_t waitpid(pid_t pid, int *status, int options)
{
    return lwp_waitpid(pid, status, options, RT_NULL);
}

#ifdef RT_USING_FINSH
/**
 * @brief Prints a line of dashes for visual separation
 *
 * @param[in] len Number of dashes to print
 */
static void object_split(int len)
{
    while (len--)
    {
        rt_kprintf("-");
    }
}

/**
 * @brief Prints detailed information about a thread
 *
 * @param[in] thread Pointer to the thread structure to print information about
 * @param[in] maxlen Maximum length for thread name display
 *
 * @note This function prints:
 *       - CPU core (SMP only) and priority
 *       - Thread state (ready, suspended, init, close, running)
 *       - Stack information (usage percentage, size, etc.)
 *       - Remaining tick count and error code
 *       - Thread name
 */
static void print_thread_info(struct rt_thread* thread, int maxlen)
{
    rt_uint8_t *ptr;
    rt_uint8_t stat;

#ifdef RT_USING_SMP
    if (RT_SCHED_CTX(thread).oncpu != RT_CPU_DETACHED)
        rt_kprintf("%3d %3d ", RT_SCHED_CTX(thread).oncpu, RT_SCHED_PRIV(thread).current_priority);
    else
        rt_kprintf("N/A %3d ", RT_SCHED_PRIV(thread).current_priority);
#else
    rt_kprintf("%3d ", RT_SCHED_PRIV(thread).current_priority);
#endif /*RT_USING_SMP*/

    stat = (RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_MASK);
    if (stat == RT_THREAD_READY)        rt_kprintf(" ready  ");
    else if ((stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK) rt_kprintf(" suspend");
    else if (stat == RT_THREAD_INIT)    rt_kprintf(" init   ");
    else if (stat == RT_THREAD_CLOSE)   rt_kprintf(" close  ");
    else if (stat == RT_THREAD_RUNNING) rt_kprintf(" running");

#if defined(ARCH_CPU_STACK_GROWS_UPWARD)
    ptr = (rt_uint8_t *)thread->stack_addr + thread->stack_size;
    while (*ptr == '#')ptr--;

    rt_kprintf(" 0x%08x 0x%08x    %02d%%   0x%08x %03d\n",
            ((rt_uint32_t)thread->sp - (rt_uint32_t)thread->stack_addr),
            thread->stack_size,
            ((rt_uint32_t)ptr - (rt_uint32_t)thread->stack_addr) * 100 / thread->stack_size,
            thread->remaining_tick,
            thread->error);
#else
    ptr = (rt_uint8_t *)thread->stack_addr;
    while (*ptr == '#')ptr++;

    rt_kprintf(" 0x%08x 0x%08x    %02d%%   0x%08x %03d",
            (thread->stack_size + (rt_uint32_t)(rt_size_t)thread->stack_addr - (rt_uint32_t)(rt_size_t)thread->sp),
            thread->stack_size,
            (thread->stack_size + (rt_uint32_t)(rt_size_t)thread->stack_addr - (rt_uint32_t)(rt_size_t)ptr) * 100
            / thread->stack_size,
            RT_SCHED_PRIV(thread).remaining_tick,
            thread->error);
#endif
    rt_kprintf("   %-.*s\n",rt_strlen(thread->parent.name), thread->parent.name);
}

/**
 * @brief Lists all processes and threads in the system
 *
 * @return long Returns 0 on success
 *
 * @note This function:
 *       - Prints a header with process/thread information columns
 *       - Lists all kernel threads (without LWP association)
 *       - Lists all user processes (LWPs) with their threads
 *       - For each thread, displays:
 *         - PID/TID (process/thread IDs)
 *         - Priority, status, stack information
 *         - Remaining tick count and error code
 *         - Thread name/command
 */
long list_process(void)
{
    int index;
    int maxlen;
    rt_ubase_t level;
    struct rt_thread *thread;
    struct rt_list_node *node, *list;
    const char *item_title = "thread";

    int count = 0;
    struct rt_thread **threads;

    maxlen = RT_NAME_MAX;
#ifdef RT_USING_SMP
    rt_kprintf("%-*.s %-*.s %-*.s cpu pri  status      sp     stack size max used left tick  error %-*.s\n", 4, "PID", 4, "TID", maxlen, item_title, maxlen, "cmd");
    object_split(4);rt_kprintf(" ");object_split(4);rt_kprintf(" ");object_split(maxlen);rt_kprintf(" ");
    rt_kprintf(                  "--- ---  ------- ---------- ---------- -------- ---------- -----");rt_kprintf(" ");object_split(maxlen);rt_kprintf("\n");
#else
    rt_kprintf("%-*.s %-*.s %-*.s pri  status      sp     stack size max used left tick  error\n", 4, "PID", 4, "TID", maxlen, item_title, maxlen, "cmd");
    object_split(4);rt_kprintf(" ");object_split(4);rt_kprintf(" ");object_split(maxlen);rt_kprintf(" ");
    rt_kprintf(                  "---  ------- ---------- ---------- -------- ---------- -----");rt_kprintf(" ");object_split(maxlen);rt_kprintf("\n");
#endif /*RT_USING_SMP*/

    count = rt_object_get_length(RT_Object_Class_Thread);
    if (count > 0)
    {
        /* get thread pointers */
        threads = (struct rt_thread **)rt_calloc(count, sizeof(struct rt_thread *));
        if (threads)
        {
            index = rt_object_get_pointers(RT_Object_Class_Thread, (rt_object_t *)threads, count);

            if (index > 0)
            {
                for (index = 0; index <count; index++)
                {
                    struct rt_thread th;

                    thread = threads[index];

                    level = rt_spin_lock_irqsave(&thread->spinlock);
                    if ((rt_object_get_type(&thread->parent) & ~RT_Object_Class_Static) != RT_Object_Class_Thread)
                    {
                        rt_spin_unlock_irqrestore(&thread->spinlock, level);
                        continue;
                    }

                    rt_memcpy(&th, thread, sizeof(struct rt_thread));
                    rt_spin_unlock_irqrestore(&thread->spinlock, level);

                    if (th.lwp == RT_NULL)
                    {
                        rt_kprintf("          %-*.*s ", maxlen, RT_NAME_MAX, "kernel");
                        print_thread_info(&th, maxlen);
                    }
                }
            }
            rt_free(threads);
        }
    }

    for (index = 0; index < RT_LWP_MAX_NR; index++)
    {
        struct rt_lwp *lwp = (struct rt_lwp *)lwp_pid_ary[index].data;

        if (lwp)
        {
            list = &lwp->t_grp;
            for (node = list->next; node != list; node = node->next)
            {
                thread = rt_list_entry(node, struct rt_thread, sibling);
                rt_kprintf("%4d %4d %-*.*s ", lwp_to_pid(lwp), thread->tid, maxlen, RT_NAME_MAX, lwp->cmd);
                print_thread_info(thread, maxlen);
            }
        }
    }
    return 0;
}
MSH_CMD_EXPORT(list_process, list process);

/**
 * @brief Command handler for killing processes
 *
 * @param[in] argc Argument count
 * @param[in] argv Argument vector (contains PID and optional signal)
 *
 * @note Usage:
 *       - kill <pid>
 *       - kill <pid> -s <signal>
 *       Default signal is SIGKILL (9)
 */
static void cmd_kill(int argc, char** argv)
{
    int pid;
    int sig = SIGKILL;

    if (argc < 2)
    {
        rt_kprintf("kill pid or kill pid -s signal\n");
        return;
    }

    pid = atoi(argv[1]);
    if (argc >= 4)
    {
        if (argv[2][0] == '-' && argv[2][1] == 's')
        {
            sig = atoi(argv[3]);
        }
    }
    lwp_pid_lock_take();
    lwp_signal_kill(lwp_from_pid_raw_locked(pid), sig, SI_USER, 0);
    lwp_pid_lock_release();
}
MSH_CMD_EXPORT_ALIAS(cmd_kill, kill, send a signal to a process);

/**
 * @brief Kills all processes matching the given name
 *
 * @param[in] argc Argument count (must be >= 2)
 * @param[in] argv Argument vector containing process name to kill
 *
 * @note Sends SIGKILL signal to all processes with the specified name.
 *       Requires at least 2 arguments (command name + process name)
 */
static void cmd_killall(int argc, char** argv)
{
    int pid;
    if (argc < 2)
    {
        rt_kprintf("killall processes_name\n");
        return;
    }

    while((pid = lwp_name2pid(argv[1])) > 0)
    {
        lwp_pid_lock_take();
        lwp_signal_kill(lwp_from_pid_raw_locked(pid), SIGKILL, SI_USER, 0);
        lwp_pid_lock_release();
        rt_thread_mdelay(100);
    }
}
MSH_CMD_EXPORT_ALIAS(cmd_killall, killall, kill processes by name);

#endif

/**
 * @brief Checks if the current thread has received an exit request
 *
 * @return int Returns:
 *             - 0 if no exit request or not an LWP thread
 *             - 1 if exit request was triggered and set to IN_PROCESS
 *
 * @note Verifies if the current lightweight process thread has been requested to exit
 *       by checking the exit_request atomic flag.
 */
int lwp_check_exit_request(void)
{
    rt_thread_t thread = rt_thread_self();
    rt_size_t expected = LWP_EXIT_REQUEST_TRIGGERED;

    if (!thread->lwp)
    {
        return 0;
    }

    return atomic_compare_exchange_strong(&thread->exit_request, &expected,
                                          LWP_EXIT_REQUEST_IN_PROCESS);
}

static void _wait_sibling_exit(rt_lwp_t lwp, rt_thread_t curr_thread);
static void _resr_cleanup(struct rt_lwp *lwp);

/**
 * @brief Terminates a lightweight process (LWP)
 *
 * @param[in,out] lwp Pointer to the lightweight process structure to terminate
 *
 * @note Safely terminates an LWP by marking it as terminated, waiting for sibling threads,
 *       and cleaning up resources.
 */
void lwp_terminate(struct rt_lwp *lwp)
{
    if (!lwp)
    {
        /* kernel thread not support */
        return;
    }

    LOG_D("%s(lwp=%p \"%s\")", __func__, lwp, lwp->cmd);

    LWP_LOCK(lwp);

    if (!lwp->terminated)
    {
        /* stop the receiving of signals */
        lwp->terminated = RT_TRUE;
        LWP_UNLOCK(lwp);

        _wait_sibling_exit(lwp, rt_thread_self());
        _resr_cleanup(lwp);
    }
    else
    {
        LWP_UNLOCK(lwp);
    }
}

/**
 * @brief Waits for sibling threads to exit during process termination
 *
 * @param[in] lwp Pointer to the lightweight process structure
 * @param[in] curr_thread Current thread context making the termination request
 *
 * @note Details for this function:
 *       - Broadcast Exit Request: Broadcasts exit requests to all sibling threads.
 *       - Wake Suspended Threads: Wakes up any suspended threads by setting their error status to RT_EINTR.
 *       - Wait for Termination: it enters a loop waiting for all sibling threads to terminate.
 *       - Cleanup Terminated Threads: Once threads are in the INIT state, it removes them from the sibling list
 *         and deletes their thread control blocks.
 */
static void _wait_sibling_exit(rt_lwp_t lwp, rt_thread_t curr_thread)
{
    rt_sched_lock_level_t slvl;
    rt_list_t *list;
    rt_thread_t thread;
    rt_size_t expected = LWP_EXIT_REQUEST_NONE;

    /* broadcast exit request for sibling threads */
    LWP_LOCK(lwp);
    for (list = lwp->t_grp.next; list != &lwp->t_grp; list = list->next)
    {
        thread = rt_list_entry(list, struct rt_thread, sibling);

        atomic_compare_exchange_strong(&thread->exit_request, &expected,
                                       LWP_EXIT_REQUEST_TRIGGERED);

        rt_sched_lock(&slvl);
        /* dont release, otherwise thread may have been freed */
        if (rt_sched_thread_is_suspended(thread))
        {
            thread->error = RT_EINTR;
            rt_sched_unlock(slvl);

            rt_thread_wakeup(thread);
        }
        else
        {
            rt_sched_unlock(slvl);
        }
    }
    LWP_UNLOCK(lwp);

    while (1)
    {
        int subthread_is_terminated;
        LOG_D("%s: wait for subthread exiting", __func__);

        /**
         * Brief: wait for all *running* sibling threads to exit
         *
         * Note: Critical Section
         * - sibling list of lwp (RW. It will clear all siblings finally)
         */
        LWP_LOCK(lwp);
        subthread_is_terminated = (int)(curr_thread->sibling.prev == &lwp->t_grp);
        if (!subthread_is_terminated)
        {
            rt_sched_lock_level_t slvl;
            rt_thread_t sub_thread;
            rt_list_t *list;
            int all_subthread_in_init = 1;

            /* check all subthread is in init state */
            for (list = curr_thread->sibling.prev; list != &lwp->t_grp; list = list->prev)
            {
                rt_sched_lock(&slvl);
                sub_thread = rt_list_entry(list, struct rt_thread, sibling);
                if (rt_sched_thread_get_stat(sub_thread) != RT_THREAD_INIT)
                {
                    rt_sched_unlock(slvl);
                    all_subthread_in_init = 0;
                    break;
                }
                else
                {
                    rt_sched_unlock(slvl);
                }
            }
            if (all_subthread_in_init)
            {
                /* delete all subthread */
                while ((list = curr_thread->sibling.prev) != &lwp->t_grp)
                {
                    sub_thread = rt_list_entry(list, struct rt_thread, sibling);
                    rt_list_remove(&sub_thread->sibling);

                    /**
                     * Note: Critical Section
                     * - thread control block (RW. Since it will free the thread
                     *   control block, it must ensure no one else can access
                     *   thread any more)
                     */
                    lwp_tid_put(sub_thread->tid);
                    sub_thread->tid = 0;
                    rt_thread_delete(sub_thread);
                }
                subthread_is_terminated = 1;
            }
        }
        LWP_UNLOCK(lwp);

        if (subthread_is_terminated)
        {
            break;
        }
        rt_thread_mdelay(10);
    }
}

/**
 * @brief Notifies parent process about child process termination
 *
 * @param[in,out] lwp The child lightweight process structure
 *
 * @note This function sends SIGCHLD signal to parent process with termination details.
 *       It handles both signaled (killed/dumped) and normal exit cases.
 */
static void _notify_parent(rt_lwp_t lwp)
{
    int si_code;
    int signo_or_exitcode;
    lwp_siginfo_ext_t ext;
    lwp_status_t lwp_status = lwp->lwp_status;
    rt_lwp_t parent = lwp->parent;

    if (WIFSIGNALED(lwp_status))
    {
        si_code = (lwp_status & LWP_COREDUMP_FLAG) ? CLD_DUMPED : CLD_KILLED;
        signo_or_exitcode = WTERMSIG(lwp_status);
    }
    else
    {
        si_code = CLD_EXITED;
        signo_or_exitcode = WEXITSTATUS(lwp->lwp_status);
    }

    lwp_waitpid_kick(parent, lwp);

    ext = rt_malloc(sizeof(struct lwp_siginfo));

    if (ext)
    {
        rt_thread_t cur_thr = rt_thread_self();
        ext->sigchld.status = signo_or_exitcode;
        ext->sigchld.stime = cur_thr->system_time;
        ext->sigchld.utime = cur_thr->user_time;
    }
    lwp_signal_kill(parent, SIGCHLD, si_code, ext);
}

/**
 * @brief Clean up resources when a lightweight process (LWP) terminates
 *
 * @param[in,out] lwp The lightweight process structure to clean up
 *
 * @note This function handles the cleanup of various resources associated with an LWP
 *       when it terminates, including:
 *       - Job control cleanup
 *       - Signal detachment
 *       - Child process handling
 *       - Parent notification
 *       - File descriptor cleanup
 *       - PID resource release
 */
static void _resr_cleanup(struct rt_lwp *lwp)
{
    int need_cleanup_pid = RT_FALSE;
    lwp_jobctrl_on_exit(lwp);

    LWP_LOCK(lwp);
    lwp_signal_detach(&lwp->signal);

    /**
     * @brief Detach children from lwp
     *
     * @note Critical Section
     * - the lwp (RW. Release lwp)
     * - the pid resource manager (RW. Release the pid)
     */
    while (lwp->first_child)
    {
        struct rt_lwp *child;

        child = lwp->first_child;
        lwp->first_child = child->sibling;

        /** @note safe since the slist node is release */
        LWP_UNLOCK(lwp);
        LWP_LOCK(child);
        if (child->terminated)
        {
            lwp_pid_put(child);
        }
        else
        {
            child->sibling = RT_NULL;
            /* info: this may cause an orphan lwp */
            child->parent = RT_NULL;
        }

        LWP_UNLOCK(child);
        lwp_ref_dec(child);
        lwp_ref_dec(lwp);

        LWP_LOCK(lwp);
    }
    LWP_UNLOCK(lwp);

    /**
     * @brief Wakeup parent if it's waiting for this lwp, otherwise a signal
     *        will be sent to parent
     *
     * @note Critical Section
     * - the parent lwp (RW.)
     */
    LWP_LOCK(lwp);
    if (lwp->parent &&
        !lwp_sigismember(&lwp->parent->signal.sig_action_nocldwait, SIGCHLD))
    {
        /* if successfully race to setup lwp->terminated before parent detach */
        LWP_UNLOCK(lwp);

        /**
         * Note: children cannot detach itself and must wait for parent to take
         * care of it
         */
        _notify_parent(lwp);
    }
    else
    {
        LWP_UNLOCK(lwp);

        /**
         * if process is orphan, it doesn't have parent to do the recycling.
         * Otherwise, its parent had setup a flag to mask out recycling event
         */
        need_cleanup_pid = RT_TRUE;
    }

    LWP_LOCK(lwp);
    if (lwp->fdt.fds != RT_NULL)
    {
        struct dfs_file **fds;

        /* auto clean fds */
        __exit_files(lwp);
        fds = lwp->fdt.fds;
        lwp->fdt.fds = RT_NULL;
        LWP_UNLOCK(lwp);

        rt_free(fds);
    }
    else
    {
        LWP_UNLOCK(lwp);
    }

    if (need_cleanup_pid)
    {
        lwp_pid_put(lwp);
    }
}

/**
 * @brief Set CPU affinity for a thread
 *
 * @param[in] tid The thread ID to set affinity for
 * @param[in] cpu The target CPU core number
 *
 * @return 0 on success, -1 on failure (invalid thread ID)
 *
 * @note This function binds a thread to a specific CPU core in SMP systems.
 *       It handles thread reference counting and returns operation status.
 */
static int _lwp_setaffinity(int tid, int cpu)
{
    rt_thread_t thread;
    int ret = -1;

    thread = lwp_tid_get_thread_and_inc_ref(tid);

    if (thread)
    {
#ifdef RT_USING_SMP
        rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void *)(rt_ubase_t)cpu);
#endif
        ret = 0;
    }
    lwp_tid_dec_ref(thread);
    return ret;
}

/**
 * @brief Sets CPU affinity for a thread
 *
 * @param[in] tid The thread ID to set affinity for
 * @param[in] cpu The target CPU core number (0 to RT_CPUS_NR-1)
 *
 * @return int 0 on success, -1 on failure
 *
 * @note wrapper function for _lwp_setaffinity
 */
int lwp_setaffinity(int tid, int cpu)
{
    int ret;

#ifdef RT_USING_SMP
    if (cpu < 0 || cpu > RT_CPUS_NR)
    {
        cpu = RT_CPUS_NR;
    }
#endif
    ret = _lwp_setaffinity(tid, cpu);
    return ret;
}

#ifdef RT_USING_SMP
/**
 * @brief Command handler for CPU binding operation
 *
 * @param[in] argc Number of command arguments
 * @param[in] argv Array of command argument strings
 *
 * @note Requires exactly 2 arguments: pid (process ID) and cpu (CPU core number)
 */
static void cmd_cpu_bind(int argc, char** argv)
{
    int pid;
    int cpu;

    if (argc < 3)
    {
        rt_kprintf("Useage: cpu_bind pid cpu\n");
        return;
    }

    pid = atoi(argv[1]);
    cpu = atoi(argv[2]);
    lwp_setaffinity((pid_t)pid, cpu);
}
MSH_CMD_EXPORT_ALIAS(cmd_cpu_bind, cpu_bind, set a process bind to a cpu);
#endif
