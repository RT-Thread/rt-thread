/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-13     Shell        init ver.
 */
#ifndef __LWP_TTY_INTERNAL_H__
#define __LWP_TTY_INTERNAL_H__

#include "lwp.h"
#include "terminal.h"

extern struct cdevsw bsd_ttydev_methods;

extern struct bsd_fileops bsd_ptsdev_methods;

/* bsd devsw porting */
void bsd_devsw_init(struct lwp_ttydevsw *tsw);

/**
 * Do not assert RTS or DTR automatically. If CNO_RTSDTR is set then the RTS and
 * DTR lines will not be asserted when the device is opened. As a result, this
 * flag is only useful on initial-state devices.
 *
 * Note: this feature is not using on smart system, so this flag is always 0.
 */
#define CNO_RTSDTR 0

/* Waking up readers/writers. */
int tty_wait(struct lwp_tty *tp, struct rt_condvar *cv);
int tty_wait_background(struct lwp_tty *tp, struct rt_thread *td, int sig);
int tty_timedwait(struct lwp_tty *tp, struct rt_condvar *cv, rt_tick_t timeout);
void tty_wakeup(struct lwp_tty *tp, int flags);

void tty_info(struct lwp_tty *tp);

void pts_set_lock(lwp_tty_t pts, rt_bool_t is_lock);
rt_bool_t pts_is_locked(lwp_tty_t pts);
int pts_get_pktmode(lwp_tty_t pts);
int pts_alloc(int fflags, struct rt_thread *td, struct dfs_file *ptm_file);

int lwp_tty_ioctl_adapter(lwp_tty_t tp, int cmd, int oflags, void *args, rt_thread_t td);

int lwp_tty_set_ctrl_proc(lwp_tty_t tp, rt_thread_t td);
int lwp_tty_assign_foreground(lwp_tty_t tp, rt_thread_t td, int pgid);
int lwp_tty_bg_stop(struct lwp_tty *tp, struct rt_condvar *cv);

rt_inline rt_bool_t is_sess_leader(rt_lwp_t p)
{
    /**
     * Note: a pgrp leader is never lose its group, so once it's
     * true then it's always true
     */
    return p->pid == p->sid;
}

rt_inline int tty_is_ctty(struct lwp_tty *tp, struct rt_lwp *p)
{
    tty_assert_locked(tp);

    return p->pgrp->session == tp->t_session && p->term_ctrlterm;
}

#endif /* __LWP_TTY_INTERNAL_H__ */
