/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * (tty_compat.c)
 * The compatible layer which interacts with process management core (lwp)
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-13     Shell        init ver.
 */

#define DBG_TAG "lwp.tty"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "../tty_config.h"
#include "../tty_internal.h"
#include "../terminal.h"

/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 1994-1995 Søren Schmidt
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* is the tty and session leader already binding ? */
static rt_bool_t _is_already_binding(lwp_tty_t tp, rt_lwp_t p)
{
    rt_bool_t rc;
    rt_processgroup_t pgrp = p->pgrp;

    /* lwp is already locked */
    RT_ASSERT(pgrp);

    /* Note: pgrp->session is constant after process group is created */
    if (tp->t_session && tp->t_session == pgrp->session)
    {
        rc = RT_TRUE;
    }
    else
    {
        rc = RT_FALSE;
    }
    return rc;
}

static rt_bool_t _is_tty_or_sess_busy(lwp_tty_t tp, rt_lwp_t p)
{
    rt_bool_t rc;
    rt_session_t sess = p->pgrp->session;

    SESS_LOCK(sess);
    if (sess->ctty)
    {
        rc = RT_TRUE;
    }
    else if (tp->t_session)
    {
        /**
         * TODO: allow TTY stolen if the sess leader is killed while resource
         * had not been collected
         */
        if (tp->t_session->leader == RT_NULL)
            rc = RT_FALSE;
        else
            rc = RT_TRUE;
    }
    else
    {
        rc = RT_FALSE;
    }
    SESS_UNLOCK(sess);
    return rc;
}

int lwp_tty_bg_stop(struct lwp_tty *tp, struct rt_condvar *cv)
{
    int error;
    int revokecnt = tp->t_revokecnt;
    rt_lwp_t self_lwp;
    rt_thread_t header_thr;
    rt_thread_t cur_thr = rt_thread_self();
    int jobctl_stopped;

    self_lwp = cur_thr->lwp;
    RT_ASSERT(self_lwp);

    jobctl_stopped = self_lwp->jobctl_stopped;

    tty_lock_assert(tp, MA_OWNED | MA_NOTRECURSED);
    MPASS(!tty_gone(tp));

    LWP_LOCK(self_lwp);
    header_thr = rt_list_entry(self_lwp->t_grp.prev, struct rt_thread, sibling);
    if (!jobctl_stopped && header_thr == cur_thr &&
        cur_thr->sibling.prev == &self_lwp->t_grp)
    {
        /* update lwp status */
        jobctl_stopped = self_lwp->jobctl_stopped = RT_TRUE;
    }
    LWP_UNLOCK(self_lwp);

    error = cv_wait(cv, tp->t_mtx);

    if (jobctl_stopped)
    {
        self_lwp->jobctl_stopped = RT_FALSE;
    }

    /* Bail out when the device slipped away. */
    if (tty_gone(tp))
        return -ENXIO;

    /* Restart the system call when we may have been revoked. */
    if (tp->t_revokecnt != revokecnt)
        return -ERESTART;

    return error;
}

/* process management */
int lwp_tty_set_ctrl_proc(lwp_tty_t tp, rt_thread_t td)
{
    int rc = -1;
    struct rt_lwp *p = td->lwp;

    tty_unlock(tp);
    LWP_LOCK(p);
    tty_lock(tp);

    if (is_sess_leader(p))
    {
        if (_is_already_binding(tp, p))
        {
            rc = 0;
        }
        else if (_is_tty_or_sess_busy(tp, p))
        {
            rc = -EPERM;
        }
        else
        {
            /**
             * Binding controlling process
             * note: p->pgrp is protected by lwp lock;
             *       pgrp->session is always constant.
             */
            tp->t_session = p->pgrp->session;
            tp->t_session->ctty = tp;
            tp->t_sessioncnt++;

            /* Assign foreground process group */
            tp->t_pgrp = p->pgrp;
            p->term_ctrlterm = RT_TRUE;

            LOG_D("%s(sid=%d)", __func__, tp->t_session->sid);
            rc = 0;
        }
    }
    else
    {
        rc = -EPERM;
    }

    LWP_UNLOCK(p);

    return rc;
}

int lwp_tty_assign_foreground(lwp_tty_t tp, rt_thread_t td, int pgid)
{
    struct rt_processgroup *pg;
    rt_lwp_t cur_lwp = td->lwp;

    tty_unlock(tp);
    pg = lwp_pgrp_find_and_inc_ref(pgid);
    if (pg == NULL || cur_lwp == NULL)
    {
        tty_lock(tp);
        return -EPERM;
    }
    else
    {
        PGRP_LOCK(pg);

        if (pg->sid != cur_lwp->sid)
        {
            PGRP_UNLOCK(pg);
            lwp_pgrp_dec_ref(pg);
            LOG_D("%s: NoPerm current process (pid=%d, pgid=%d, sid=%d), "
                  "tagget group (pgid=%d, sid=%d)", __func__,
                  cur_lwp->pid, cur_lwp->pgid, cur_lwp->sid, pgid, pg->sid);
            tty_lock(tp);
            return -EPERM;
        }
    }
    tty_lock(tp);

    /**
     * Determine if this TTY is the controlling TTY after
     * relocking the TTY.
     */
    if (!tty_is_ctty(tp, td->lwp))
    {
        PGRP_UNLOCK(pg);
        LOG_D("%s: NoCTTY current process (pid=%d, pgid=%d, sid=%d), "
              "tagget group (pgid=%d, sid=%d)", __func__,
              cur_lwp->pid, cur_lwp->pgid, cur_lwp->sid, pgid, pg->sid);
        return -ENOTTY;
    }
    tp->t_pgrp = pg;
    PGRP_UNLOCK(pg);
    lwp_pgrp_dec_ref(pg);

    /* Wake up the background process groups. */
    cv_broadcast(&tp->t_bgwait);

    LOG_D("%s: Foreground group %p (pgid=%d)", __func__, tp->t_pgrp,
          tp->t_pgrp ? tp->t_pgrp->pgid : -1);

    return 0;
}

/**
 * Signalling processes.
 */

void lwp_tty_signal_sessleader(struct lwp_tty *tp, int sig)
{
    struct rt_lwp *p;
    struct rt_session *s;

    tty_assert_locked(tp);
    MPASS(sig >= 1 && sig < _LWP_NSIG);

    /* Make signals start output again. */
    tp->t_flags &= ~TF_STOPPED;
    tp->t_termios.c_lflag &= ~FLUSHO;

    /**
     * Load s.leader exactly once to avoid race where s.leader is
     * set to NULL by a concurrent invocation of killjobc() by the
     * session leader.  Note that we are not holding t_session's
     * lock for the read.
     */
    if ((s = tp->t_session) != NULL &&
        (p = (void *)rt_atomic_load((rt_atomic_t *)&s->leader)) != NULL)
    {
        lwp_signal_kill(p, sig, SI_KERNEL, 0);
    }
}

void lwp_tty_signal_pgrp(struct lwp_tty *tp, int sig)
{
    tty_assert_locked(tp);
    MPASS(sig >= 1 && sig < _LWP_NSIG);

    /* Make signals start output again. */
    tp->t_flags &= ~TF_STOPPED;
    tp->t_termios.c_lflag &= ~FLUSHO;

#ifdef USING_BSD_SIGINFO
    if (sig == SIGINFO && !(tp->t_termios.c_lflag & NOKERNINFO))
        tty_info(tp);
#endif /* USING_BSD_SIGINFO */

    if (tp->t_pgrp != NULL)
    {
        PGRP_LOCK(tp->t_pgrp);
        lwp_pgrp_signal_kill(tp->t_pgrp, sig, SI_KERNEL, 0);
        PGRP_UNLOCK(tp->t_pgrp);
    }
}

/* bsd_ttydev_methods.d_ioctl */

rt_inline size_t _copy_to_user(void *to, void *from, size_t n)
{
    return lwp_put_to_user(to, from, n) == n ? 0 : -EFAULT;
}

rt_inline size_t _copy_from_user(void *to, void *from, size_t n)
{
    return lwp_get_from_user(to, from, n) == n ? 0 : -EFAULT;
}

static void termios_to_termio(struct termios *tios, struct termio *tio)
{
    memset(tio, 0, sizeof(*tio));
    tio->c_iflag = tios->c_iflag;
    tio->c_oflag = tios->c_oflag;
    tio->c_cflag = tios->c_cflag;
    tio->c_lflag = tios->c_lflag;
    tio->c_line = tios->c_line;
    memcpy(tio->c_cc, tios->c_cc, NCC);
}

static void termio_to_termios(struct termio *tio, struct termios *tios)
{
    int i;

    tios->c_iflag = tio->c_iflag;
    tios->c_oflag = tio->c_oflag;
    tios->c_cflag = tio->c_cflag;
    tios->c_lflag = tio->c_lflag;
    for (i = NCC; i < NCCS; i++)
        tios->c_cc[i] = _POSIX_VDISABLE;
    memcpy(tios->c_cc, tio->c_cc, NCC);
}

#define IOCTL(cmd, data, fflags, td) \
    bsd_ttydev_methods.d_ioctl(tp, cmd, data, fflags, td)

int lwp_tty_ioctl_adapter(lwp_tty_t tp, int cmd, int oflags, void *args, rt_thread_t td)
{
    long fflags = FFLAGS(oflags);
    struct termios tios;
    struct termio tio;
    int error;

    LOG_D("%s(cmd=0x%x, args=%p)", __func__, cmd, args);
    switch (cmd & 0xffff)
    {
        case TCGETS:
            error = IOCTL(TIOCGETA, (rt_caddr_t)&tios, fflags, td);
            if (error)
                break;
            error = _copy_to_user(args, &tios, sizeof(tios));
            break;

        case TCSETS:
            error = _copy_from_user(&tios, args, sizeof(tios));
            if (error)
                break;
            error = (IOCTL(TIOCSETA, (rt_caddr_t)&tios, fflags, td));
            break;

        case TCSETSW:
            error = _copy_from_user(&tios, args, sizeof(tios));
            if (error)
                break;
            error = (IOCTL(TIOCSETAW, (rt_caddr_t)&tios, fflags, td));
            break;

        case TCSETSF:
            error = _copy_from_user(&tios, args, sizeof(tios));
            if (error)
                break;
            error = (IOCTL(TIOCSETAF, (rt_caddr_t)&tios, fflags, td));
            break;

        case TCGETA:
            error = IOCTL(TIOCGETA, (rt_caddr_t)&tios, fflags, td);
            if (error)
                break;
            termios_to_termio(&tios, &tio);
            error = _copy_to_user((void *)args, &tio, sizeof(tio));
            break;

        case TCSETA:
            error = _copy_from_user(&tio, (void *)args, sizeof(tio));
            if (error)
                break;
            termio_to_termios(&tio, &tios);
            error = (IOCTL(TIOCSETA, (rt_caddr_t)&tios, fflags, td));
            break;

        case TCSETAW:
            error = _copy_from_user(&tio, (void *)args, sizeof(tio));
            if (error)
                break;
            termio_to_termios(&tio, &tios);
            error = (IOCTL(TIOCSETAW, (rt_caddr_t)&tios, fflags, td));
            break;

        case TCSETAF:
            error = _copy_from_user(&tio, (void *)args, sizeof(tio));
            if (error)
                break;
            termio_to_termios(&tio, &tios);
            error = (IOCTL(TIOCSETAF, (rt_caddr_t)&tios, fflags, td));
            break;

        case TCSBRK:
            if (args != 0)
            {
                /**
                 * Linux manual: SVr4, UnixWare, Solaris, and Linux treat
                 * tcsendbreak(fd,arg) with nonzero arg like tcdrain(fd).
                 */
                error = IOCTL(TIOCDRAIN, (rt_caddr_t)&tios, fflags, td);
            }
            else
            {
                /**
                 * Linux manual: If the terminal is using asynchronous serial
                 * data transmission, and arg is zero, then send a break (a
                 * stream of zero bits) for between 0.25 and 0.5 seconds.
                 */
                LOG_D("%s: ioctl TCSBRK arg 0 not implemented", __func__);
                error = -ENOSYS;
            }
            break;

#ifdef USING_BSD_IOCTL_EXT
        /* Software flow control */
        case TCXONC: {
            switch (args->arg)
            {
                case TCOOFF:
                    args->cmd = TIOCSTOP;
                    break;
                case TCOON:
                    args->cmd = TIOCSTART;
                    break;
                case TCIOFF:
                case TCION: {
                    int c;
                    struct write_args wr;
                    error = IOCTL(TIOCGETA, (rt_caddr_t)&tios, fflags,
                                     td);
                    if (error)
                        break;
                    fdrop(fp, td);
                    c = (args->arg == TCIOFF) ? VSTOP : VSTART;
                    c = tios.c_cc[c];
                    if (c != _POSIX_VDISABLE)
                    {
                        wr.fd = args->fd;
                        wr.buf = &c;
                        wr.nbyte = sizeof(c);
                        return (sys_write(td, &wr));
                    }
                    else
                        return 0;
                }
                default:
                    fdrop(fp, td);
                    return -EINVAL;
            }
            args->arg = 0;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;
        }
#endif /* USING_BSD_IOCTL_EXT */
        case TCFLSH: {
            int val;
            error = 0;
            switch ((rt_base_t)args)
            {
                case TCIFLUSH:
                    val = FREAD;
                    break;
                case TCOFLUSH:
                    val = FWRITE;
                    break;
                case TCIOFLUSH:
                    val = FREAD | FWRITE;
                    break;
                default:
                    error = -EINVAL;
                    break;
            }
            if (!error)
                error = (IOCTL(TIOCFLUSH, (rt_caddr_t)&val, fflags, td));
            break;
        }

#ifdef USING_BSD_IOCTL_EXT
        case TIOCEXCL:
            args->cmd = TIOCEXCL;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

        case TIOCNXCL:
            args->cmd = TIOCNXCL;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;
#endif /* USING_BSD_IOCTL_EXT */

        /* Controlling terminal */
        case TIOCSCTTY:
        case TIOCNOTTY:

        /* Process group and session ID */
        case TIOCGPGRP:
        case TIOCSPGRP:
        case TIOCGSID:

            /* TIOCOUTQ */
            /* TIOCSTI */
        case TIOCGWINSZ:
        case TIOCSWINSZ:
            error = IOCTL(cmd, (rt_caddr_t)args, fflags, td);
            break;
#ifdef USING_BSD_IOCTL_EXT
        case TIOCMGET:
            args->cmd = TIOCMGET;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

        case TIOCMBIS:
            args->cmd = TIOCMBIS;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

        case TIOCMBIC:
            args->cmd = TIOCMBIC;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

        case TIOCMSET:
            args->cmd = TIOCMSET;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

            /* TIOCGSOFTCAR */
            /* TIOCSSOFTCAR */

        case FIONREAD: /* TIOCINQ */
            args->cmd = FIONREAD;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

            /* TIOCLINUX */

        case TIOCCONS:
            args->cmd = TIOCCONS;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

        case TIOCGSERIAL: {
            struct linux_serial_struct lss;

            bzero(&lss, sizeof(lss));
            lss.type = PORT_16550A;
            lss.flags = 0;
            lss.close_delay = 0;
            error = copyout(&lss, (void *)args->arg, sizeof(lss));
            break;
        }

        case TIOCSSERIAL: {
            struct linux_serial_struct lss;
            error = copyin((void *)args->arg, &lss, sizeof(lss));
            if (error)
                break;
            /* XXX - It really helps to have an implementation that
             * does nothing. NOT!
             */
            error = 0;
            break;
        }

        case TIOCPKT:
            args->cmd = TIOCPKT;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

        case FIONBIO:
            args->cmd = FIONBIO;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

        case TIOCSETD: {
            int line;
            switch (args->arg)
            {
                case N_TTY:
                    line = TTYDISC;
                    break;
                case N_SLIP:
                    line = SLIPDISC;
                    break;
                case N_PPP:
                    line = PPPDISC;
                    break;
                default:
                    fdrop(fp, td);
                    return -EINVAL;
            }
            error = (ioctl_emit(TIOCSETD, (rt_caddr_t)&line, fflags, td));
            break;
        }

        case TIOCGETD: {
            int linux_line;
            int bsd_line = TTYDISC;
            error =
                ioctl_emit(TIOCGETD, (rt_caddr_t)&bsd_line, fflags, td);
            if (error)
                break;
            switch (bsd_line)
            {
                case TTYDISC:
                    linux_line = N_TTY;
                    break;
                case SLIPDISC:
                    linux_line = N_SLIP;
                    break;
                case PPPDISC:
                    linux_line = N_PPP;
                    break;
                default:
                    fdrop(fp, td);
                    return -EINVAL;
            }
            error = (copyout(&linux_line, (void *)args->arg, sizeof(int)));
            break;
        }

            /* TCSBRKP */
            /* TIOCTTYGSTRUCT */

        case FIONCLEX:
            args->cmd = FIONCLEX;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

        case FIOCLEX:
            args->cmd = FIOCLEX;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

        case FIOASYNC:
            args->cmd = FIOASYNC;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

            /* TIOCSERCONFIG */
            /* TIOCSERGWILD */
            /* TIOCSERSWILD */
            /* TIOCGLCKTRMIOS */
            /* TIOCSLCKTRMIOS */

        case TIOCSBRK:
            args->cmd = TIOCSBRK;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;

        case TIOCCBRK:
            args->cmd = TIOCCBRK;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;
        case TIOCGPTN: {
            int nb;

            error = ioctl_emit(TIOCGPTN, (rt_caddr_t)&nb, fflags, td);
            if (!error)
                error = copyout(&nb, (void *)args->arg, sizeof(int));
            break;
        }
        case TIOCGPTPEER:
            linux_msg(td, "unsupported ioctl TIOCGPTPEER");
            error = -ENOIOCTL;
            break;
        case TIOCSPTLCK:
            /*
             * Our unlockpt() does nothing. Check that fd refers
             * to a pseudo-terminal master device.
             */
            args->cmd = TIOCPTMASTER;
            error = (sys_ioctl(td, (struct ioctl_args *)args));
            break;
#endif /* USING_BSD_IOCTL_EXT */

        /**
         * those are for current implementation of devfs, and we dont want to
         * log them
         */
        case F_DUPFD:
        case F_DUPFD_CLOEXEC:
        case F_GETFD:
        case F_SETFD:
        case F_GETFL:
        case F_SETFL:
            /* fall back to fs */
            error = -ENOIOCTL;
            break;
        default:
            LOG_I("%s: unhandle commands 0x%x", __func__, cmd);
            error = -ENOSYS;
            break;
    }

    return (error);
}
