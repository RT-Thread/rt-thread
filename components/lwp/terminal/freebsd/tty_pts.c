/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-07     Shell        init ver.
 */

#include <ipc/condvar.h>
#include <rid_bitmap.h>
#include <terminal/terminal.h>
#include <terminal/tty_internal.h>
#include <ptyfs.h>

#include <rtthread.h>

/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2008 Ed Schouten <ed@FreeBSD.org>
 * All rights reserved.
 *
 * Portions of this software were developed under sponsorship from Snow
 * B.V., the Netherlands.
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
#define PTS_EXTERNAL

/*
 * Per-PTS structure.
 *
 * List of locks
 * (t)  locked by tty_lock()
 * (c)  const until freeing
 */
struct pts_softc
{
    int pts_unit;           /* (c) Device unit number. */
    unsigned int pts_flags; /* (t) Device flags. */
#define PTS_PKT      0x1    /* Packet mode. */
#define PTS_FINISHED 0x2    /* Return errors on read()/write(). */
#define PTS_PTLOCKED 0x4    /* ioctl %TIOCSPTLCK/%TIOCGPTLCK */
    char pts_pkt;           /* (t) Unread packet mode data. */

    struct rt_condvar pts_inwait;  /* (t) Blocking write() on master. */
    struct rt_wqueue pts_inpoll;   /* (t) Select queue for write(). */
    struct rt_condvar pts_outwait; /* (t) Blocking read() on master. */
    struct rt_wqueue pts_outpoll;  /* (t) Select queue for read(). */

    struct ucred *pts_cred; /* (c) Resource limit. */
    rt_device_t pts_master; /** (c) Master device.
                             * (Note: in rtsmart kernel, we support
                             * multi-instance ptmx )
                             */
};

/**
 * Controller-side file operations.
 * (P)seudo-(T)erminal (M)ultiple(X)er
 */

static int ptsdev_read(struct lwp_tty *tp, struct uio *uio,
                       struct ucred *active_cred, int oflags,
                       struct rt_thread *td)
{
    struct pts_softc *psc = tty_softc(tp);
    int error = 0;
    char pkt;

    if (uio->uio_resid == 0)
        return (0);

    tty_lock(tp);

    for (;;)
    {
        /*
         * Implement packet mode. When packet mode is turned on,
         * the first byte contains a bitmask of events that
         * occurred (start, stop, flush, window size, etc).
         */
        if (psc->pts_flags & PTS_PKT && psc->pts_pkt)
        {
            pkt = psc->pts_pkt;
            psc->pts_pkt = 0;
            tty_unlock(tp);

            error = uiomove(&pkt, 1, uio);
            return (error);
        }

        /*
         * Transmit regular data.
         *
         * XXX: We shouldn't use ttydisc_getc_poll()! Even
         * though in this implementation, there is likely going
         * to be data, we should just call ttydisc_getc_uio()
         * and use its return value to sleep.
         */
        if (ttydisc_getc_poll(tp))
        {
            if (psc->pts_flags & PTS_PKT)
            {
                /*
                 * XXX: Small race. Fortunately PTY
                 * consumers aren't multithreaded.
                 */

                tty_unlock(tp);
                pkt = TIOCPKT_DATA;
                error = uiomove(&pkt, 1, uio);
                if (error)
                    return (error);
                tty_lock(tp);
            }

            error = ttydisc_getc_uio(tp, uio);
            break;
        }

        /* Maybe the device isn't used anyway. */
        if (psc->pts_flags & PTS_FINISHED)
            break;

        /* Wait for more data. */
        if (oflags & O_NONBLOCK)
        {
            error = EWOULDBLOCK;
            break;
        }
        error = cv_wait_sig(&psc->pts_outwait, tp->t_mtx);
        if (error != 0)
            break;
    }

    tty_unlock(tp);

    return (error);
}

static int ptsdev_write(struct lwp_tty *tp, struct uio *uio,
                        struct ucred *active_cred, int oflags,
                        struct rt_thread *td)
{
    struct pts_softc *psc = tty_softc(tp);
    char ib[256], *ibstart;
    size_t iblen, rintlen;
    int error = 0;

    if (uio->uio_resid == 0)
        return (0);

    for (;;)
    {
        ibstart = ib;
        iblen = MIN(uio->uio_resid, sizeof ib);
        error = uiomove(ib, iblen, uio);

        tty_lock(tp);
        if (error != 0)
        {
            iblen = 0;
            goto done;
        }

        /*
         * When possible, avoid the slow path. rint_bypass()
         * copies all input to the input queue at once.
         */
        MPASS(iblen > 0);
        do
        {
            rintlen = ttydisc_rint_simple(tp, ibstart, iblen);
            ibstart += rintlen;
            iblen -= rintlen;
            if (iblen == 0)
            {
                /* All data written. */
                break;
            }

            /* Maybe the device isn't used anyway. */
            if (psc->pts_flags & PTS_FINISHED)
            {
                error = -EIO;
                goto done;
            }

            /* Wait for more data. */
            if (oflags & O_NONBLOCK)
            {
                error = -EWOULDBLOCK;
                goto done;
            }

            /* Wake up users on the slave side. */
            ttydisc_rint_done(tp);
            error = cv_wait_sig(&psc->pts_inwait, tp->t_mtx);
            if (error != 0)
                goto done;
        } while (iblen > 0);

        if (uio->uio_resid == 0)
            break;
        tty_unlock(tp);
    }

done:
    ttydisc_rint_done(tp);
    tty_unlock(tp);

    /*
     * Don't account for the part of the buffer that we couldn't
     * pass to the TTY.
     */
    uio->uio_resid += iblen;
    return (error);
}

static int ptsdev_ioctl(struct lwp_tty *tp, rt_ubase_t cmd, void *data,
                        struct ucred *active_cred, int fflags,
                        struct rt_thread *td)
{
    struct pts_softc *psc = tty_softc(tp);
    int error = 0, sig;

    switch (cmd)
    {
#ifdef USING_BSD_IOCTL_EXT
        case FIODTYPE:
            *(int *)data = D_TTY;
            return (0);
#endif
        case FIONBIO:
            /* This device supports non-blocking operation. */
            return (0);
        case FIONREAD:
            tty_lock(tp);
            if (psc->pts_flags & PTS_FINISHED)
            {
                /* Force read() to be called. */
                *(int *)data = 1;
            }
            else
            {
                *(int *)data = ttydisc_getc_poll(tp);
            }
            tty_unlock(tp);
            return (0);
#ifdef USING_BSD_IOCTL_EXT
        case FIODGNAME:
#ifdef COMPAT_FREEBSD32
        case FIODGNAME_32:
#endif
        {
            struct fiodgname_arg *fgn;
            const char *p;
            int i;

            /* Reverse device name lookups, for ptsname() and ttyname(). */
            fgn = data;
            p = tty_devname(tp);
            i = strlen(p) + 1;
            if (i > fgn->len)
                return -EINVAL;
            return (copyout(p, fiodgname_buf_get_ptr(fgn, cmd), i));
        }
#endif
        /*
         * We need to implement TIOCGPGRP and TIOCGSID here again. When
         * called on the pseudo-terminal master, it should not check if
         * the terminal is the foreground terminal of the calling
         * process.
         *
         * TIOCGETA is also implemented here. Various Linux PTY routines
         * often call isatty(), which is implemented by tcgetattr().
         */
        case TIOCGETA:
            /* Obtain terminal flags through tcgetattr(). */
            tty_lock(tp);
            *(struct termios *)data = tp->t_termios;
            tty_unlock(tp);
            return (0);
        case TIOCSETAF:
        case TIOCSETAW:
            /*
             * We must make sure we turn tcsetattr() calls of TCSAFLUSH and
             * TCSADRAIN into something different. If an application would
             * call TCSAFLUSH or TCSADRAIN on the master descriptor, it may
             * deadlock waiting for all data to be read.
             */
            cmd = TIOCSETA;
            break;
        case TIOCGPTN:
            /*
             * Get the device unit number.
             */
            if (psc->pts_unit < 0)
                return -ENOTTY;
            *(unsigned int *)data = psc->pts_unit;
            return (0);
        case TIOCGPGRP:
            /* Get the foreground process group ID. */
            tty_lock(tp);
            if (tp->t_pgrp != NULL)
                *(int *)data = tp->t_pgrp->pgid;
            else
                *(int *)data = NO_PID;
            tty_unlock(tp);
            return (0);
        case TIOCGSID:
            /* Get the session leader process ID. */
            tty_lock(tp);
            if (tp->t_session == NULL)
                error = -ENOTTY;
            else
                *(int *)data = tp->t_session->sid;
            tty_unlock(tp);
            return (error);
#ifdef USING_BSD_IOCTL_EXT
        case TIOCPTMASTER:
            /* Yes, we are a pseudo-terminal master. */
            return (0);
#endif /* USING_BSD_IOCTL_EXT */
        case TIOCSIG:
            /* Signal the foreground process group. */
            sig = *(int *)data;
            if (sig < 1 || sig >= _LWP_NSIG)
                return -EINVAL;

            tty_lock(tp);
            lwp_tty_signal_pgrp(tp, sig);
            tty_unlock(tp);
            return (0);
        case TIOCPKT:
            /* Enable/disable packet mode. */
            tty_lock(tp);
            if (*(int *)data)
                psc->pts_flags |= PTS_PKT;
            else
                psc->pts_flags &= ~PTS_PKT;
            tty_unlock(tp);
            return (0);
    }

    /* Just redirect this ioctl to the slave device. */
    tty_lock(tp);
    error = tty_ioctl(tp, cmd, data, fflags, td);
    tty_unlock(tp);
    if (error == -ENOIOCTL)
        error = -ENOTTY;

    return error;
}

static int ptsdev_poll(struct lwp_tty *tp, struct rt_pollreq *req,
                       struct ucred *active_cred, struct rt_thread *td)
{
    struct pts_softc *psc = tty_softc(tp);
    int revents = 0;
    int events = req->_key;

    tty_lock(tp);

    if (psc->pts_flags & PTS_FINISHED)
    {
        /* Slave device is not opened. */
        tty_unlock(tp);
        return ((events & (POLLIN | POLLRDNORM)) | POLLHUP);
    }

    if (events & (POLLIN | POLLRDNORM))
    {
        /* See if we can getc something. */
        if (ttydisc_getc_poll(tp) || (psc->pts_flags & PTS_PKT && psc->pts_pkt))
            revents |= events & (POLLIN | POLLRDNORM);
    }
    if (events & (POLLOUT | POLLWRNORM))
    {
        /* See if we can rint something. */
        if (ttydisc_rint_poll(tp))
            revents |= events & (POLLOUT | POLLWRNORM);
    }

    /*
     * No need to check for POLLHUP here. This device cannot be used
     * as a callout device, which means we always have a carrier,
     * because the master is.
     */

    if (revents == 0)
    {
        /*
         * This code might look misleading, but the naming of
         * poll events on this side is the opposite of the slave
         * device.
         */
        if (events & (POLLIN | POLLRDNORM))
            rt_poll_add(&psc->pts_outpoll, req);
        if (events & (POLLOUT | POLLWRNORM))
            rt_poll_add(&psc->pts_inpoll, req);
    }

    tty_unlock(tp);

    return (revents);
}

#if USING_BSD_KQUEUE
/*
 * kqueue support.
 */

static void pts_kqops_read_detach(struct knote *kn)
{
    struct file *fp = kn->kn_fp;
    struct lwp_tty *tp = fp->f_data;
    struct pts_softc *psc = tty_softc(tp);

    knlist_remove(&psc->pts_outpoll.si_note, kn, 0);
}

static int pts_kqops_read_event(struct knote *kn, long hint)
{
    struct file *fp = kn->kn_fp;
    struct lwp_tty *tp = fp->f_data;
    struct pts_softc *psc = tty_softc(tp);

    if (psc->pts_flags & PTS_FINISHED)
    {
        kn->kn_flags |= EV_EOF;
        return (1);
    }
    else
    {
        kn->kn_data = ttydisc_getc_poll(tp);
        return (kn->kn_data > 0);
    }
}

static void pts_kqops_write_detach(struct knote *kn)
{
    struct file *fp = kn->kn_fp;
    struct lwp_tty *tp = fp->f_data;
    struct pts_softc *psc = tty_softc(tp);

    knlist_remove(&psc->pts_inpoll.si_note, kn, 0);
}

static int pts_kqops_write_event(struct knote *kn, long hint)
{
    struct file *fp = kn->kn_fp;
    struct lwp_tty *tp = fp->f_data;
    struct pts_softc *psc = tty_softc(tp);

    if (psc->pts_flags & PTS_FINISHED)
    {
        kn->kn_flags |= EV_EOF;
        return (1);
    }
    else
    {
        kn->kn_data = ttydisc_rint_poll(tp);
        return (kn->kn_data > 0);
    }
}

static struct filterops pts_kqops_read = {
    .f_isfd = 1,
    .f_detach = pts_kqops_read_detach,
    .f_event = pts_kqops_read_event,
};
static struct filterops pts_kqops_write = {
    .f_isfd = 1,
    .f_detach = pts_kqops_write_detach,
    .f_event = pts_kqops_write_event,
};

static int ptsdev_kqfilter(struct file *fp, struct knote *kn)
{
    struct lwp_tty *tp = fp->f_data;
    struct pts_softc *psc = tty_softc(tp);
    int error = 0;

    tty_lock(tp);

    switch (kn->kn_filter)
    {
        case EVFILT_READ:
            kn->kn_fop = &pts_kqops_read;
            knlist_add(&psc->pts_outpoll.si_note, kn, 1);
            break;
        case EVFILT_WRITE:
            kn->kn_fop = &pts_kqops_write;
            knlist_add(&psc->pts_inpoll.si_note, kn, 1);
            break;
        default:
            error = EINVAL;
            break;
    }

    tty_unlock(tp);
    return (error);
}
#endif

#if USING_BSD_STAT
static int ptsdev_stat(struct file *fp, struct stat *sb,
                       struct ucred *active_cred)
{
    struct lwp_tty *tp = fp->f_data;
#ifdef PTS_EXTERNAL
    struct pts_softc *psc = tty_softc(tp);
#endif /* PTS_EXTERNAL */
    struct cdev *dev = tp->t_dev;

    /*
     * According to POSIX, we must implement an fstat(). This also
     * makes this implementation compatible with Linux binaries,
     * because Linux calls fstat() on the pseudo-terminal master to
     * obtain st_rdev.
     *
     * XXX: POSIX also mentions we must fill in st_dev, but how?
     */

    bzero(sb, sizeof *sb);
#ifdef PTS_EXTERNAL
    if (psc->pts_cdev != NULL)
        sb->st_ino = sb->st_rdev = dev2udev(psc->pts_cdev);
    else
#endif /* PTS_EXTERNAL */
        sb->st_ino = sb->st_rdev = tty_udev(tp);

    sb->st_atim = dev->si_atime;
    sb->st_ctim = dev->si_ctime;
    sb->st_mtim = dev->si_mtime;
    sb->st_uid = dev->si_uid;
    sb->st_gid = dev->si_gid;
    sb->st_mode = dev->si_mode | S_IFCHR;

    return (0);
}
#endif

static int ptsdev_close(struct lwp_tty *tp, struct rt_thread *td)
{
    /* Deallocate TTY device. */
    tty_lock(tp);
    tty_rel_gone(tp);

#ifdef USING_BSD_VNODE
    /* TODO: consider the vnode operation on DFS */

    /*
     * Open of /dev/ptmx or /dev/ptyXX changes the type of file
     * from DTYPE_VNODE to DTYPE_PTS. vn_open() increases vnode
     * use count, we need to decrement it, and possibly do other
     * required cleanup.
     */
    if (fp->f_vnode != NULL)
        return (vnops.fo_close(fp, td));
#endif /* USING_BSD_VNODE */

    return 0;
}

#ifdef USING_BSD_KINFO
static int ptsdev_fill_kinfo(struct file *fp, struct kinfo_file *kif,
                             struct filedesc *fdp)
{
    struct lwp_tty *tp;

    kif->kf_type = KF_TYPE_PTS;
    tp = fp->f_data;
    kif->kf_un.kf_pts.kf_pts_dev = tty_udev(tp);
    kif->kf_un.kf_pts.kf_pts_dev_freebsd11 =
        kif->kf_un.kf_pts.kf_pts_dev; /* truncate */
    strlcpy(kif->kf_path, tty_devname(tp), sizeof(kif->kf_path));
    return (0);
}
#endif

struct bsd_fileops bsd_ptsdev_methods = {
    .fo_read = ptsdev_read,
    .fo_write = ptsdev_write,
    // .fo_truncate = invfo_truncate,
    .fo_ioctl = ptsdev_ioctl,
    .fo_poll = ptsdev_poll,
    // .fo_kqfilter = ptsdev_kqfilter,
    // .fo_stat = ptsdev_stat,
    .fo_close = ptsdev_close,
    // .fo_chmod = invfo_chmod,
    // .fo_chown = invfo_chown,
    // .fo_sendfile = invfo_sendfile,
    // .fo_fill_kinfo = ptsdev_fill_kinfo,
    .fo_flags = DFLAG_PASSABLE,
};

/*
 * Driver-side hooks.
 */

static void ptsdrv_outwakeup(struct lwp_tty *tp)
{
    struct pts_softc *psc = tty_softc(tp);

    cv_broadcast(&psc->pts_outwait);
    rt_wqueue_wakeup_all(&psc->pts_outpoll, (void *)POLLIN);
}

static void ptsdrv_inwakeup(struct lwp_tty *tp)
{
    struct pts_softc *psc = tty_softc(tp);

    cv_broadcast(&psc->pts_inwait);
    rt_wqueue_wakeup_all(&psc->pts_inpoll, (void *)POLLOUT);
}

static int ptsdrv_open(struct lwp_tty *tp)
{
    struct pts_softc *psc = tty_softc(tp);

    /* for ioctl(TIOCSPTLCK) */
    if (psc->pts_flags & PTS_PTLOCKED)
        return -EIO;

    psc->pts_flags &= ~PTS_FINISHED;

    return 0;
}

static void ptsdrv_close(struct lwp_tty *tp)
{
    struct pts_softc *psc = tty_softc(tp);

    /* Wake up any blocked readers/writers. */
    psc->pts_flags |= PTS_FINISHED;
    ptsdrv_outwakeup(tp);
    ptsdrv_inwakeup(tp);
}

static void ptsdrv_pktnotify(struct lwp_tty *tp, char event)
{
    struct pts_softc *psc = tty_softc(tp);

    /*
     * Clear conflicting flags.
     */

    switch (event)
    {
        case TIOCPKT_STOP:
            psc->pts_pkt &= ~TIOCPKT_START;
            break;
        case TIOCPKT_START:
            psc->pts_pkt &= ~TIOCPKT_STOP;
            break;
        case TIOCPKT_NOSTOP:
            psc->pts_pkt &= ~TIOCPKT_DOSTOP;
            break;
        case TIOCPKT_DOSTOP:
            psc->pts_pkt &= ~TIOCPKT_NOSTOP;
            break;
    }

    psc->pts_pkt |= event;

    /**
     * Note: on smart, we don't wakeup master until it's willing to accept
     * packet event. Because on poll, we setup POLLIN for PTS_PKT only. So There
     * is a chance when we wakeup ipc but we can't wakeup user again. Since
     * current wakeup will remove the wakequeue node on the meanwhile
     */
    if (psc->pts_flags & PTS_PKT)
        ptsdrv_outwakeup(tp);
}

static void ptsdrv_free(void *softc)
{
    struct pts_softc *psc = softc;

    /* Make device number available again. */
    if (psc->pts_unit >= 0)
        ptyfs_unregister_pts(psc->pts_master, psc->pts_unit);

#ifdef USING_BSD_UCRED
    chgptscnt(psc->pts_cred->cr_ruidinfo, -1, 0);
    racct_sub_cred(psc->pts_cred, RACCT_NPTS, 1);
    crfree(psc->pts_cred);
#endif

    rt_wqueue_wakeup_all(&psc->pts_inpoll, (void *)POLLHUP);
    rt_wqueue_wakeup_all(&psc->pts_outpoll, (void *)POLLHUP);

    rt_free(psc);
}

static struct lwp_ttydevsw pts_class = {
    .tsw_flags = TF_NOPREFIX,
    .tsw_outwakeup = ptsdrv_outwakeup,
    .tsw_inwakeup = ptsdrv_inwakeup,
    .tsw_open = ptsdrv_open,
    .tsw_close = ptsdrv_close,
    .tsw_pktnotify = ptsdrv_pktnotify,
    .tsw_free = ptsdrv_free,
};

int pts_alloc(int fflags, struct rt_thread *td, struct dfs_file *ptm_file)
{
    int unit;
    struct lwp_tty *tp;
    struct pts_softc *psc;
    char name_buf[DIRENT_NAME_MAX];
    const char *rootpath;
    rt_device_t ptmx_device = ptm_file->vnode->data;

#ifdef USING_BSD_UCRED
    struct rt_lwp *p = td->lwp;
    int ok, error;
    struct ucred *cred = td->td_ucred;
#endif

    /* Resource limiting. */
#ifdef USING_BSD_UCRED
    LWP_LOCK(p);
    error = racct_add(p, RACCT_NPTS, 1);
    if (error != 0)
    {
        LWP_UNLOCK(p);
        return -EAGAIN;
    }
    ok = chgptscnt(cred->cr_ruidinfo, 1, lim_cur(td, RLIMIT_NPTS));
    if (!ok)
    {
        racct_sub(p, RACCT_NPTS, 1);
        LWP_UNLOCK(p);
        return -EAGAIN;
    }
    LWP_UNLOCK(p);
#endif

    /* Allocate TTY and softc. */
    psc = rt_calloc(1, sizeof(struct pts_softc));
    cv_init(&psc->pts_inwait, "ptsin");
    cv_init(&psc->pts_outwait, "ptsout");
    rt_wqueue_init(&psc->pts_inpoll);
    rt_wqueue_init(&psc->pts_outpoll);

    psc->pts_master = ptmx_device;
#ifdef USING_BSD_UCRED
    psc->pts_cred = crhold(cred);
#else
    psc->pts_cred = 0;
#endif

    tp = lwp_tty_create(&pts_class, psc);
    if (!tp)
    {
        rt_free(psc);
        rt_condvar_detach(&psc->pts_inwait);
        rt_condvar_detach(&psc->pts_outwait);
        return -ENOMEM;
    }

    /* Try to allocate a new pts uint*/
    unit = ptyfs_register_pts(ptmx_device, &tp->parent);
    if (unit < 0)
    {
#ifdef USING_BSD_UCRED
        racct_sub(p, RACCT_NPTS, 1);
        chgptscnt(cred->cr_ruidinfo, -1, 0);
#endif
        lwp_tty_delete(tp);
        return -EAGAIN;
    }
    psc->pts_unit = unit;

    /* Expose the slave device as well. */
#ifdef USING_BSD_UCRED
    tty_makedev(tp, td->td_ucred, "pts/%u", psc->pts_unit);
#else
    rootpath = ptyfs_get_rootpath(ptmx_device);
    RT_ASSERT(rootpath[strlen(rootpath) - 1] != '/');
    snprintf(name_buf, DIRENT_NAME_MAX, "%s/%d", rootpath, psc->pts_unit);

    /* setup the pts */
    lwp_tty_register(tp, name_buf);

    /* now this file operating on new pty */
    ptm_file->data = tp;
#endif

    return 0;
}

void pts_set_lock(lwp_tty_t pts, rt_bool_t is_lock)
{
    struct pts_softc *psc = tty_softc(pts);
    if (is_lock)
        psc->pts_flags |= PTS_PTLOCKED;
    else
        psc->pts_flags &= ~PTS_PTLOCKED;
}

rt_bool_t pts_is_locked(lwp_tty_t pts)
{
    struct pts_softc *psc = tty_softc(pts);
    return !!(psc->pts_flags & PTS_PTLOCKED);
}

int pts_get_pktmode(lwp_tty_t pts)
{
    struct pts_softc *psc = tty_softc(pts);
    return !!(psc->pts_flags & PTS_PKT);
}
