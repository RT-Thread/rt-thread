/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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

int lwp_pid_init(void)
{
    rt_mutex_init(&pid_mtx, "pidmtx", RT_IPC_FLAG_PRIO);
    return 0;
}

void lwp_pid_lock_take(void)
{
    LWP_DEF_RETURN_CODE(rc);

    rc = lwp_mutex_take_safe(&pid_mtx, RT_WAITING_FOREVER, 0);
    /* should never failed */
    RT_ASSERT(rc == RT_EOK);
}

void lwp_pid_lock_release(void)
{
    /* should never failed */
    if (lwp_mutex_release_safe(&pid_mtx) != RT_EOK)
        RT_ASSERT(0);
}

struct lwp_avl_struct *lwp_get_pid_ary(void)
{
    return lwp_pid_ary;
}

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

void lwp_pid_put(struct rt_lwp *lwp)
{
    _free_proc_dentry(lwp);

    lwp_pid_lock_take();
    lwp_pid_put_locked(lwp->pid);
    lwp_pid_lock_release();

    /* reset pid field */
    lwp->pid = 0;
    /* clear reference */
    lwp_ref_dec(lwp);
}

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

void lwp_user_object_lock_init(struct rt_lwp *lwp)
{
    rt_mutex_init(&lwp->object_mutex, "lwp_obj", RT_IPC_FLAG_PRIO);
}

void lwp_user_object_lock_destroy(struct rt_lwp *lwp)
{
    rt_mutex_detach(&lwp->object_mutex);
}

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

static int _object_dup(struct lwp_avl_struct *node, void *arg)
{
    rt_object_t object;
    struct rt_lwp *dst_lwp = (struct rt_lwp *)arg;

    object = (rt_object_t)node->avl_key;
    lwp_user_object_add(dst_lwp, object);
    return 0;
}

void lwp_user_object_dup(struct rt_lwp *dst_lwp, struct rt_lwp *src_lwp)
{
    lwp_user_object_lock(src_lwp);
    lwp_avl_traversal(src_lwp->object_root, _object_dup, dst_lwp);
    lwp_user_object_unlock(src_lwp);
}

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

/** when reference is 0, a lwp can be released */
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

/** @note the reference is not for synchronization, but for the release of resource. the synchronization is done through lwp & pid lock */
int lwp_ref_inc(struct rt_lwp *lwp)
{
    int ref;
    ref = rt_atomic_add(&lwp->ref, 1);
    LOG_D("%s(%p(%s)): before %d", __func__, lwp, lwp->cmd, ref);

    return ref;
}

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

struct rt_lwp* lwp_from_pid_locked(pid_t pid)
{
    struct rt_lwp* lwp;
    lwp = pid ? lwp_from_pid_raw_locked(pid) : lwp_self();
    return lwp;
}

pid_t lwp_to_pid(struct rt_lwp* lwp)
{
    if (!lwp)
    {
        return 0;
    }
    return lwp->pid;
}

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
            process_name = strrchr(lwp->cmd, '/');
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

int lwp_getpid(void)
{
    rt_lwp_t lwp = lwp_self();
    return lwp ? lwp->pid : 1;
    // return ((struct rt_lwp *)rt_thread_self()->lwp)->pid;
}

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

/* do statistical summary and reap the child if neccessary */
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

/* check if the process is already terminate */
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

/* verify if the process is child, and reap it */
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

/* try to reap any child */
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

rt_err_t lwp_waitpid_kick(rt_lwp_t parent, rt_lwp_t self_lwp)
{
    /* waker provide the message mainly through its lwp_status */
    rt_wqueue_wakeup(&parent->waitpid_waiters, self_lwp);
    return RT_EOK;
}

struct waitpid_handle {
    struct rt_wqueue_node wq_node;
    int options;
    rt_lwp_t waker_lwp;
};

/* the IPC message is setup and notify the parent */
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

/* the waiter cleanup IPC message and wait for desired event here */
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

/* wait for IPC event and do the cleanup if neccessary */
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

pid_t waitpid(pid_t pid, int *status, int options)
{
    return lwp_waitpid(pid, status, options, RT_NULL);
}

#ifdef RT_USING_FINSH
/* copy from components/finsh/cmd.c */
static void object_split(int len)
{
    while (len--)
    {
        rt_kprintf("-");
    }
}

static void print_thread_info(struct rt_thread* thread, int maxlen)
{
    rt_uint8_t *ptr;
    rt_uint8_t stat;

#ifdef RT_USING_SMP
    if (RT_SCHED_CTX(thread).oncpu != RT_CPU_DETACHED)
        rt_kprintf("%-*.*s %3d %3d ", maxlen, RT_NAME_MAX, thread->parent.name, RT_SCHED_CTX(thread).oncpu, RT_SCHED_PRIV(thread).current_priority);
    else
        rt_kprintf("%-*.*s N/A %3d ", maxlen, RT_NAME_MAX, thread->parent.name, RT_SCHED_PRIV(thread).current_priority);
#else
    rt_kprintf("%-*.*s %3d ", maxlen, RT_NAME_MAX, thread->parent.name, RT_SCHED_PRIV(thread).current_priority);
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

    rt_kprintf(" 0x%08x 0x%08x    %02d%%   0x%08x %03d\n",
            (thread->stack_size + (rt_uint32_t)(rt_size_t)thread->stack_addr - (rt_uint32_t)(rt_size_t)thread->sp),
            thread->stack_size,
            (thread->stack_size + (rt_uint32_t)(rt_size_t)thread->stack_addr - (rt_uint32_t)(rt_size_t)ptr) * 100
            / thread->stack_size,
            RT_SCHED_PRIV(thread).remaining_tick,
            thread->error);
#endif
}

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
    rt_kprintf("%-*.s %-*.s %-*.s cpu pri  status      sp     stack size max used left tick  error\n", 4, "PID", maxlen, "CMD", maxlen, item_title);
    object_split(4);rt_kprintf(" ");object_split(maxlen);rt_kprintf(" ");object_split(maxlen);rt_kprintf(" ");
    rt_kprintf(                  "--- ---  ------- ---------- ----------  ------  ---------- ---\n");
#else
    rt_kprintf("%-*.s %-*.s %-*.s pri  status      sp     stack size max used left tick  error\n", 4, "PID", maxlen, "CMD", maxlen, item_title);
    object_split(4);rt_kprintf(" ");object_split(maxlen);rt_kprintf(" ");object_split(maxlen);rt_kprintf(" ");
    rt_kprintf(                  "---  ------- ---------- ----------  ------  ---------- ---\n");
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
                        rt_kprintf("     %-*.*s ", maxlen, RT_NAME_MAX, "kernel");
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
                rt_kprintf("%4d %-*.*s ", lwp_to_pid(lwp), maxlen, RT_NAME_MAX, lwp->cmd);
                print_thread_info(thread, maxlen);
            }
        }
    }
    return 0;
}
MSH_CMD_EXPORT(list_process, list process);

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

static void _resr_cleanup(struct rt_lwp *lwp)
{
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
        lwp_pid_put(lwp);
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
}

static int _lwp_setaffinity(pid_t pid, int cpu)
{
    struct rt_lwp *lwp;
    int ret = -1;

    lwp_pid_lock_take();
    lwp = lwp_from_pid_locked(pid);

    if (lwp)
    {
#ifdef RT_USING_SMP
        rt_list_t *list;

        lwp->bind_cpu = cpu;
        for (list = lwp->t_grp.next; list != &lwp->t_grp; list = list->next)
        {
            rt_thread_t thread;

            thread = rt_list_entry(list, struct rt_thread, sibling);
            rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void *)(rt_size_t)cpu);
        }
#endif
        ret = 0;
    }
    lwp_pid_lock_release();
    return ret;
}

int lwp_setaffinity(pid_t pid, int cpu)
{
    int ret;

#ifdef RT_USING_SMP
    if (cpu < 0 || cpu > RT_CPUS_NR)
    {
        cpu = RT_CPUS_NR;
    }
#endif
    ret = _lwp_setaffinity(pid, cpu);
    return ret;
}

#ifdef RT_USING_SMP
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
