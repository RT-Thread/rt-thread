/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-17     xqyjlj       the first version
 * 2023-11-29     Shell        Add direct reference of sess for group
 */

#include "lwp.h"
#include "lwp_internal.h"
#include "lwp_syscall.h"
#include "terminal/terminal.h"

#define DBG_TAG "lwp.session"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

rt_session_t lwp_session_find(pid_t sid)
{
    rt_base_t level;
    rt_session_t session = RT_NULL;
    rt_list_t *node = RT_NULL;
    struct rt_object_information *information = RT_NULL;

    information = rt_object_get_information(RT_Object_Class_Session);

    /* parameter check */
    if ((sid < 0) || (information == RT_NULL))
    {
        return RT_NULL;
    }

    if (sid == 0)
    {
        sid = lwp_getpid();
    }

    /* enter critical */
    level = rt_spin_lock_irqsave(&(information->spinlock));

    /* try to find session */
    rt_list_for_each(node, &(information->object_list))
    {
        session = (rt_session_t)rt_list_entry(node, struct rt_object, list);
        if (session->sid == sid)
        {
            rt_spin_unlock_irqrestore(&(information->spinlock), level);

            return session;
        }
    }

    rt_spin_unlock_irqrestore(&(information->spinlock), level);

    return RT_NULL;
}

rt_session_t lwp_session_create(rt_processgroup_t leader)
{
    rt_session_t session = RT_NULL;

    /* parameter check */
    if (leader == RT_NULL)
    {
        return RT_NULL;
    }

    session = rt_malloc(sizeof(struct rt_session));
    if (session != RT_NULL)
    {
        rt_object_init(&(session->object), RT_Object_Class_Session, "session");
        rt_list_init(&(session->processgroup));
        rt_mutex_init(&(session->mutex), "session", RT_IPC_FLAG_PRIO);
        session->leader = leader;
        session->sid = leader->pgid;
        lwp_pgrp_update_children_info(leader, session->sid, leader->pgid);
        session->foreground_pgid = session->sid;
    }
    return session;
}

int lwp_session_delete(rt_session_t session)
{
    int retry = 0;
    lwp_tty_t ctty;

    /* parameter check */
    if (session == RT_NULL)
    {
        return -EINVAL;
    }

    /* clear children sid */
    lwp_session_update_children_info(session, 0);

    while (retry)
    {
        retry = 0;
        ctty = session->ctty;
        if (ctty)
            tty_lock(ctty);
        SESS_LOCK(session);

        if (session->ctty == ctty)
        {
            if (ctty)
                tty_rel_sess(ctty, session);
        }
        else
        {
            retry = 1;
        }

        SESS_UNLOCK(session);
        if (ctty)
            tty_unlock(ctty);
    }

    rt_object_detach(&(session->object));
    rt_mutex_detach(&(session->mutex));
    rt_free(session);

    return 0;
}

int lwp_session_insert(rt_session_t session, rt_processgroup_t group)
{
    /* parameter check */
    if (session == RT_NULL || group == RT_NULL)
    {
        return -EINVAL;
    }

    SESS_LOCK_NESTED(session);
    PGRP_LOCK_NESTED(group);

    group->sid = session->sid;
    group->session = session;
    lwp_pgrp_update_children_info(group, session->sid, group->pgid);
    rt_list_insert_after(&(session->processgroup), &(group->node));

    PGRP_UNLOCK(group);
    SESS_UNLOCK(session);

    return 0;
}

int lwp_session_remove(rt_session_t session, rt_processgroup_t group)
{
    rt_bool_t is_empty = RT_FALSE;

    /* parameter check */
    if (session == RT_NULL || group == RT_NULL)
    {
        return -EINVAL;
    }

    SESS_LOCK_NESTED(session);
    PGRP_LOCK_NESTED(group);

    rt_list_remove(&(group->node));
    /* clear children sid */
    lwp_pgrp_update_children_info(group, 0, group->pgid);
    group->sid = 0;
    group->session = RT_NULL;

    PGRP_UNLOCK(group);

    is_empty = rt_list_isempty(&(session->processgroup));

    SESS_UNLOCK(session);

    if (is_empty)
    {
        lwp_session_delete(session);
        return 1;
    }

    return 0;
}

int lwp_session_move(rt_session_t session, rt_processgroup_t group)
{
    rt_session_t prev_session;

    /* parameter check */
    if (session == RT_NULL || group == RT_NULL)
    {
        return -EINVAL;
    }

    if (lwp_sid_get_bysession(session) == lwp_sid_get_bypgrp(group))
    {
        return 0;
    }

    SESS_LOCK(session);

    prev_session = group->session;
    if (prev_session)
    {
        SESS_LOCK(prev_session);
        lwp_session_remove(prev_session, group);
        SESS_UNLOCK(prev_session);
    }

    lwp_session_insert(session, group);

    SESS_UNLOCK(session);

    return 0;
}

int lwp_session_update_children_info(rt_session_t session, pid_t sid)
{
    rt_list_t *node = RT_NULL;
    rt_processgroup_t group = RT_NULL;

    if (session == RT_NULL)
    {
        return -EINVAL;
    }

    SESS_LOCK_NESTED(session);

    rt_list_for_each(node, &(session->processgroup))
    {
        group = (rt_processgroup_t)rt_list_entry(node, struct rt_processgroup, node);
        PGRP_LOCK_NESTED(group);
        if (sid != -1)
        {
            group->sid = sid;
            group->session = session;
            lwp_pgrp_update_children_info(group, sid, group->pgid);
        }
        PGRP_UNLOCK(group);
    }

    SESS_UNLOCK(session);
    return 0;
}

int lwp_session_set_foreground(rt_session_t session, pid_t pgid)
{
    rt_processgroup_t group = RT_NULL;
    rt_list_t *node = RT_NULL;
    rt_bool_t is_contains = RT_FALSE;

    /* parameter check */
    if (session == RT_NULL || pgid <= 0)
    {
        return -EINVAL;
    }

    SESS_LOCK(session);

    rt_list_for_each(node, &(session->processgroup))
    {
        group = (rt_processgroup_t)rt_list_entry(node, struct rt_processgroup, node);
        PGRP_LOCK(group);
        if (group->pgid == pgid)
        {
            is_contains = RT_TRUE;
        }
        PGRP_UNLOCK(group);
    }

    if (is_contains)
    {
        session->foreground_pgid = pgid;
        // TODO: maybe notify tty
    }

    SESS_UNLOCK(session);

    return is_contains ? 0 : -EINVAL;
}

/**
 * setsid() creates a new session if the calling process is not a process group leader.
 *  The calling process is the leader of the new session (i.e., its session ID is made the same as its process ID).
 *  The calling process also becomes the process group leader of a new process group in the session
 *      (i.e., its process group ID is made the same as its process ID).
 */
sysret_t sys_setsid(void)
{
    rt_lwp_t process;
    pid_t pid;
    rt_processgroup_t group;
    rt_session_t session;
    sysret_t err = 0;

    process = lwp_self();
    pid = lwp_to_pid(process);

    /**
     * if the calling process is already a process group leader.
     */
    if (lwp_pgrp_find(pid))
    {
        err = -EPERM;
        goto exit;
    }

    group = lwp_pgrp_create(process);
    if (group)
    {
        lwp_pgrp_move(group, process);
        session = lwp_session_create(group);
        if (session)
        {
            lwp_session_move(session, group);
        }
        else
        {
            lwp_pgrp_delete(group);
        }
    }

    err = lwp_sid_get_bysession(session);

exit:
    return err;
}

/**
 * getsid() returns the session ID of the process with process ID pid.
 *  If pid is 0, getsid() returns the session ID of the calling process.
 */
sysret_t sys_getsid(pid_t pid)
{
    rt_lwp_t process, self_process;
    pid_t sid;

    lwp_pid_lock_take();
    process = lwp_from_pid_locked(pid);
    lwp_pid_lock_release();

    if (process == RT_NULL)
    {
        return -ESRCH;
    }

    self_process = lwp_self();
    sid = lwp_sid_get_byprocess(process);

    if (sid != lwp_sid_get_byprocess(self_process))
    {
        /**
         * A process with process ID pid exists, but it is not in the same session as the calling process,
         *  and the implementation considers this an error.
         *
         * Note: Linux does not return EPERM.
         */
        return -EPERM;
    }

    return sid;
}

#ifdef RT_USING_FINSH

#include "finsh.h"

long list_session(void)
{
    int count = 0, index;
    rt_session_t *sessions;
    rt_session_t session;
    rt_thread_t thread;
    char name[RT_NAME_MAX];

    rt_kprintf("SID  leader process\n");
    rt_kprintf("---- ----------------\n");

    count = rt_object_get_length(RT_Object_Class_Session);
    if (count > 0)
    {
        /* get  pointers */
        sessions = (rt_session_t *)rt_calloc(count, sizeof(rt_session_t));
        if (sessions)
        {
            index = rt_object_get_pointers(RT_Object_Class_Session, (rt_object_t *)sessions, count);
            if (index > 0)
            {
                for (index = 0; index < count; index++)
                {
                    struct rt_session se;
                    session = sessions[index];
                    SESS_LOCK(session);
                    rt_memcpy(&se, session, sizeof(struct rt_session));
                    SESS_UNLOCK(session);

                    if (se.leader && se.leader->leader)
                    {
                        thread = rt_list_entry(se.leader->leader->t_grp.prev, struct rt_thread, sibling);
                        rt_strncpy(name, thread->parent.name, RT_NAME_MAX);
                    }
                    else
                    {
                        rt_strncpy(name, "nil", RT_NAME_MAX);
                    }

                    rt_kprintf("%4d %-*.*s\n", se.sid, RT_NAME_MAX, RT_NAME_MAX, name);
                }
            }
            rt_free(sessions);
        }
    }

    return 0;
}
MSH_CMD_EXPORT(list_session, list session);
#endif
