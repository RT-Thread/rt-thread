/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-13     Shell        init ver.
 */

#define DBG_TAG "lwp.tty"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <terminal/terminal.h>
#include "lwp_internal.h"

static void jobctrl_set_pgrp_orphaned(struct rt_processgroup *pgrp)
{
    rt_lwp_t proc, nx_proc;
    PGRP_LOCK(pgrp);

    pgrp->is_orphaned = 1;
    rt_list_for_each_entry(proc, &pgrp->process, pgrp_node)
    {
        LWP_LOCK(proc);
        if (proc->jobctl_stopped)
        {
            LWP_UNLOCK(proc);
            rt_list_for_each_entry_safe(proc, nx_proc, &pgrp->process, pgrp_node)
            {
                LWP_LOCK(proc);
                lwp_signal_kill(proc, SIGHUP, SI_KERNEL, 0);
                lwp_signal_kill(proc, SIGCONT, SI_KERNEL, 0);
                LWP_UNLOCK(proc);
            }
        }
        LWP_UNLOCK(proc);
    }

    PGRP_UNLOCK(pgrp);
}

void lwp_jobctrl_on_exit(struct rt_lwp *lwp)
{
    rt_processgroup_t pgrp;
    rt_session_t session;
    lwp_tty_t tp;

    pgrp = lwp->pgrp;
    RT_ASSERT(pgrp);
    session = pgrp->session;
    RT_ASSERT(session);

    /**
     * as a session leader, we have to mark tty as freed. So others can race to
     * take it before we actually close and released that tty
     */
    SESS_LOCK(session);
    if (session->sid == lwp->pid)
    {
        tp = session->ctty;
        session->leader = 0;

        /* signal to foreground group that modem is disconnected */
        if (tp)
        {
            tty_lock(tp);
            if (tp->t_session == session)
                lwp_tty_signal_pgrp(tp, SIGHUP);
            tty_unlock(tp);
        }

        /* revoke tty vnode ? */

        rt_list_for_each_entry(pgrp, &session->processgroup, pgrp_list_node)
        {
            jobctrl_set_pgrp_orphaned(pgrp);
        }

    }
    SESS_UNLOCK(session);

    /* release tty */
    /* allow tty stolen? */
}
