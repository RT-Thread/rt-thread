/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-17     xqyjlj       the first version
 * 2023-11-28     Shell        Add reference management for pgrp;
 *                             Using lwp lock API and fix the dead lock problem
 */

#include "lwp.h"
#include "lwp_internal.h"
#include "lwp_syscall.h"

#define DBG_TAG "lwp.pgrp"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

void lwp_pgrp_dec_ref(rt_processgroup_t pgrp)
{
    if (rt_atomic_add(&pgrp->ref, -1) == 1)
    {
        rt_mutex_detach(&(pgrp->mutex));

        /* clear self pgid */
        pgrp->pgid = 0;
        rt_free(pgrp);
    }
}

rt_processgroup_t lwp_pgrp_find_and_inc_ref(pid_t pgid)
{
    rt_processgroup_t group;

    group = lwp_pgrp_find(pgid);
    if (group)
    {
        rt_atomic_add(&(group->ref), 1);
    }

    return group;
}

rt_processgroup_t lwp_pgrp_find(pid_t pgid)
{
    rt_base_t level;
    rt_processgroup_t group = RT_NULL;
    rt_list_t *node = RT_NULL;
    struct rt_object_information *information = RT_NULL;

    information = rt_object_get_information(RT_Object_Class_ProcessGroup);

    /* parameter check */
    if ((pgid < 0) || (information == RT_NULL))
    {
        return RT_NULL;
    }

    if (pgid == 0)
    {
        pgid = lwp_getpid();
    }

    /* enter critical */
    level = rt_spin_lock_irqsave(&(information->spinlock));

    /* try to find process group */
    rt_list_for_each(node, &(information->object_list))
    {
        group = (rt_processgroup_t)rt_list_entry(node, struct rt_object, list);
        if (group->pgid == pgid)
        {
            rt_spin_unlock_irqrestore(&(information->spinlock), level);

            return group;
        }
    }

    rt_spin_unlock_irqrestore(&(information->spinlock), level);

    LOG_I("cannot find(pgid:%d)() by (pid:%d, pgid:%d)", pgid, lwp_getpid(), lwp_pgid_get_byprocess(lwp_self()));

    return RT_NULL;
}

rt_processgroup_t lwp_pgrp_create(rt_lwp_t leader)
{
    rt_processgroup_t group = RT_NULL;

    /* parameter check */
    if (leader == RT_NULL)
    {
        return RT_NULL;
    }

    group = rt_malloc(sizeof(struct rt_processgroup));
    if (group != RT_NULL)
    {
        rt_object_init(&(group->object), RT_Object_Class_ProcessGroup, "pgrp");
        rt_list_init(&(group->process));
        rt_list_init(&(group->pgrp_list_node));
        rt_mutex_init(&(group->mutex), "pgrp", RT_IPC_FLAG_PRIO);
        group->leader = leader;
        group->sid = 0;
        group->session = RT_NULL;
        group->is_orphaned = 0;
        group->pgid = lwp_to_pid(leader);
        rt_atomic_store(&group->ref, 1);
    }

    LOG_I("create(ptr:%p, pgid:%d)() by pid:%d", group, group->pgid, lwp_getpid());

    return group;
}

#include <terminal/terminal.h>

int lwp_pgrp_delete(rt_processgroup_t group)
{
    int retry = 1;
    rt_session_t session = RT_NULL;
    int is_session_free = 0;
    lwp_tty_t ctty;

    /* parameter check */
    if (group == RT_NULL)
    {
        return -EINVAL;
    }

    LOG_I("delete(ptr:%p, pgid:%d)() by pid:%d", group, group->pgid, lwp_getpid());

    while (retry)
    {
        retry = 0;
        session = lwp_session_find(lwp_sid_get_bypgrp(group));
        if (session)
        {
            ctty = session->ctty;
            if (ctty)
            {
                /**
                 * Note: it's safe to release pgrp even we do this multiple,
                 * the neccessary check is done before the tty actually detach
                 */
                tty_lock(ctty);
                tty_rel_pgrp(ctty, group); // tty_unlock
            }

            SESS_LOCK(session);
            PGRP_LOCK_NESTED(group);
            if (group->session == session && session->ctty == ctty)
            {
                rt_object_detach(&(group->object));
                is_session_free = lwp_session_remove(session, group);
            }
            else
            {
                retry = 1;

            }

            PGRP_UNLOCK(group);
            if (is_session_free != 1)
                SESS_UNLOCK(session);
        }
        else
        {
            rt_object_detach(&(group->object));
        }
    }

    lwp_pgrp_dec_ref(group);
    return 0;
}

int lwp_pgrp_insert(rt_processgroup_t group, rt_lwp_t process)
{
    /* parameter check */
    if (group == RT_NULL || process == RT_NULL)
    {
        return -EINVAL;
    }

    PGRP_LOCK_NESTED(group);
    LWP_LOCK_NESTED(process);
    RT_ASSERT(rt_mutex_get_hold(&process->lwp_lock) <= rt_mutex_get_hold(&group->mutex));

    process->pgid = group->pgid;
    process->pgrp = group;
    process->sid = group->sid;
    rt_list_insert_after(&(group->process), &(process->pgrp_node));

    LWP_UNLOCK(process);
    PGRP_UNLOCK(group);

    return 0;
}

int lwp_pgrp_remove(rt_processgroup_t group, rt_lwp_t process)
{
    rt_bool_t is_empty = RT_FALSE;

    /* parameter check */
    if (group == RT_NULL || process == RT_NULL)
    {
        return -EINVAL;
    }

    PGRP_LOCK_NESTED(group);
    LWP_LOCK_NESTED(process);
    RT_ASSERT(rt_mutex_get_hold(&process->lwp_lock) <= rt_mutex_get_hold(&group->mutex));

    rt_list_remove(&(process->pgrp_node));
    /* clear children sid and pgid */
    process->pgrp = RT_NULL;
    process->pgid = 0;
    process->sid = 0;

    LWP_UNLOCK(process);

    is_empty = rt_list_isempty(&(group->process));

    PGRP_UNLOCK(group);

    if (is_empty)
    {
        lwp_pgrp_delete(group);
        return 1;
    }

    return 0;
}

int lwp_pgrp_move(rt_processgroup_t group, rt_lwp_t process)
{
    int retry = 1;
    rt_processgroup_t old_group;

    /* parameter check */
    if (group == RT_NULL || process == RT_NULL)
    {
        return -EINVAL;
    }

    if (lwp_pgid_get_bypgrp(group) == lwp_pgid_get_byprocess(process))
    {
        return 0;
    }

    PGRP_LOCK(group);
    while (retry)
    {
        retry = 0;
        old_group = lwp_pgrp_find_and_inc_ref(lwp_pgid_get_byprocess(process));

        PGRP_LOCK(old_group);
        LWP_LOCK(process);

        if (process->pgrp == old_group)
        {
            lwp_pgrp_remove(old_group, process);
            lwp_pgrp_insert(group, process);
        }
        else
        {
            retry = 1;
        }
        PGRP_UNLOCK(old_group);
        LWP_UNLOCK(process);

        lwp_pgrp_dec_ref(old_group);
    }
    PGRP_UNLOCK(group);

    return 0;
}

int lwp_pgrp_update_children_info(rt_processgroup_t group, pid_t sid, pid_t pgid)
{
    rt_list_t *node = RT_NULL;
    rt_lwp_t process = RT_NULL;

    if (group == RT_NULL)
    {
        return -EINVAL;
    }

    PGRP_LOCK_NESTED(group);

    /* try to find process group */
    rt_list_for_each(node, &(group->process))
    {
        process = (rt_lwp_t)rt_list_entry(node, struct rt_lwp, pgrp_node);
        LWP_LOCK(process);
        if (sid != -1)
        {
            process->sid = sid;
        }
        if (pgid != -1)
        {
            process->pgid = pgid;
            process->pgrp = group;
        }
        LWP_UNLOCK(process);
    }

    PGRP_UNLOCK(group);
    return 0;
}

/**
 * setpgid() sets the PGID of the process specified by pid to pgid.
 *  If pid is zero, then the process ID of the calling process is used.
 *  If pgid is zero, then the PGID of the process specified by pid is made the same as its process ID.
 *  If setpgid() is used to move a process from one process group to another (as is done by some shells when
 *      creating pipelines), both process groups must be part of the same session (see setsid(2) and credentials(7)).
 *      In this case, the pgid specifies an existing process group to be joined and the session ID of that group must
 *      match the session ID of the joining process.
 */
sysret_t sys_setpgid(pid_t pid, pid_t pgid)
{
    rt_lwp_t process, self_process;
    pid_t sid;
    rt_processgroup_t group;
    rt_session_t session;
    sysret_t err = 0;

    if (pgid == 0)
    {
        pgid = pid;
    }
    if (pgid < 0)
    {
        return -EINVAL;
    }

    self_process = lwp_self();

    if (pid == 0)
    {
        pid = self_process->pid;
        process = self_process;
    }
    else
    {
        lwp_pid_lock_take();
        process = lwp_from_pid_locked(pid);
        lwp_pid_lock_release();

        if (process == RT_NULL)
        {
            return -ESRCH;
        }
    }

    LWP_LOCK(process);

    if (process->parent == self_process)
    {
        /**
         * change the process group ID of one of the children of the calling process and the child was in
         *  a different session
         */
        if (lwp_sid_get_byprocess(process) != lwp_sid_get_byprocess(self_process))
        {
            err = -EPERM;
            LWP_UNLOCK(process);
            goto exit;
        }
        /**
         * An attempt was made to change the process group ID of one of the children of the calling process
         *  and the child had already performed an execve(2)
         */
        if (process->did_exec)
        {
            err = -EACCES;
            LWP_UNLOCK(process);
            goto exit;
        }
    }
    else
    {
        /**
         * pid is not the calling process and not a child of the calling process.
         */
        if (process != self_process)
        {
            err = -ESRCH;
            LWP_UNLOCK(process);
            goto exit;
        }
    }

    LWP_UNLOCK(process);

    sid = lwp_sid_get_byprocess(self_process);
    if (pgid != pid)
    {
        group = lwp_pgrp_find(pgid);
        if (group == RT_NULL)
        {
            group = lwp_pgrp_create(process);
        }
        else
        {
            /**
             * An attempt was made to move a process into a process group in a different session
             */
            if (sid != lwp_sid_get_bypgrp(group))
            {
                err = -EPERM;
                goto exit;
            }
            /**
             * or to change the process group ID of a session leader
             */
            if (sid == lwp_to_pid(process))
            {
                err = -EPERM;
                goto exit;
            }
            lwp_pgrp_move(group, process);
        }
    }
    else
    {
        group = lwp_pgrp_find(pgid);
        if (group == RT_NULL)
        {
            group = lwp_pgrp_create(process);
            lwp_pgrp_move(group, process);
            session = lwp_session_find(sid);
            if (session == RT_NULL)
            {
                LOG_E("the session of sid: %d cannot be found", sid);
                err = -EPERM;
                goto exit;
            }
            else
            {
                lwp_session_insert(session, group);
            }
        }
        else // this represents repeated calls
        {
            /**
             * or to change the process group ID of a session leader
             */
            if (lwp_sid_get_bypgrp(group) == lwp_pgid_get_bypgrp(group))
            {
                err = -EPERM;
                goto exit;
            }
            else
            {
                err = 0;
            }
        }
    }

exit:
    return err;
}

/**
 * getpgid() returns the PGID of the process specified by pid.
 *  If pid is zero, the process ID of the calling process is used. (Retrieving the PGID of a process other
 *      than the caller is rarely necessary, and the POSIX.1 getpgrp() is preferred for that task.)
 */
sysret_t sys_getpgid(pid_t pid)
{
    rt_lwp_t process;

    lwp_pid_lock_take();
    process = lwp_from_pid_locked(pid);
    lwp_pid_lock_release();

    if (process == RT_NULL)
    {
        return -ESRCH;
    }

    return lwp_pgid_get_byprocess(process);
}

#ifdef RT_USING_FINSH

#include "finsh.h"

long list_processgroup(void)
{
    int count = 0, index;
    rt_processgroup_t *groups;
    rt_processgroup_t group;
    rt_thread_t thread;
    char name[RT_NAME_MAX];

    rt_kprintf("PGID SID  leader process\n");
    rt_kprintf("---- ---- ----------------\n");

    count = rt_object_get_length(RT_Object_Class_ProcessGroup);
    if (count > 0)
    {
        /* get  pointers */
        groups = (rt_processgroup_t *)rt_calloc(count, sizeof(rt_processgroup_t));
        if (groups)
        {
            index = rt_object_get_pointers(RT_Object_Class_ProcessGroup, (rt_object_t *)groups, count);
            if (index > 0)
            {
                for (index = 0; index < count; index++)
                {
                    struct rt_processgroup pgrp;
                    group = groups[index];
                    PGRP_LOCK(group);
                    rt_memcpy(&pgrp, group, sizeof(struct rt_processgroup));
                    PGRP_UNLOCK(group);

                    if (pgrp.leader)
                    {
                        thread = rt_list_entry(pgrp.leader->t_grp.prev, struct rt_thread, sibling);
                        rt_strncpy(name, thread->parent.name, RT_NAME_MAX);
                    }
                    else
                    {
                        rt_strncpy(name, "nil", RT_NAME_MAX);
                    }

                    rt_kprintf("%4d %4d %-*.*s\n", pgrp.pgid, pgrp.sid, RT_NAME_MAX, RT_NAME_MAX, name);
                }
            }
            rt_free(groups);
        }
    }

    return 0;
}
MSH_CMD_EXPORT(list_processgroup, list process group);
#endif
