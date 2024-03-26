/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-13     Shell        init ver.
 */
#include "../bsd_porting.h"
#include "../tty_config.h"
#include "../terminal.h"
#include "../tty_internal.h"

#include <rtdef.h>
#include <sys/ioctl.h>

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

static void tty_rel_free(struct lwp_tty *tp);

/* Character device of /dev/console. */
static struct rt_device *dev_console;
#ifdef USING_BSD_CONSOLE_NAME
static const char *dev_console_filename;
#endif

/*
 * Flags that are supported and stored by this implementation.
 */
#ifndef ALTWERASE
#define ALTWERASE 0
#endif
#ifndef NOKERNINFO
#define NOKERNINFO 0
#endif
#define TTYSUP_IFLAG                                                      \
    (IGNBRK | BRKINT | IGNPAR | PARMRK | INPCK | ISTRIP | INLCR | IGNCR | \
     ICRNL | IXON | IXOFF | IXANY | IMAXBEL | IUTF8)
#define TTYSUP_OFLAG (OPOST | ONLCR | TAB3 | ONOEOT | OCRNL | ONOCR | ONLRET)
#define TTYSUP_LFLAG                                                     \
    (ECHOKE | ECHOE | ECHOK | ECHO | ECHONL | ECHOPRT | ECHOCTL | ISIG | \
     ICANON | ALTWERASE | IEXTEN | TOSTOP | FLUSHO | NOKERNINFO | NOFLSH)
#define TTYSUP_CFLAG                                                       \
    (CIGNORE | CSIZE | CSTOPB | CREAD | PARENB | PARODD | HUPCL | CLOCAL | \
     CCTS_OFLOW | CRTS_IFLOW | CDTR_IFLOW | CDSR_OFLOW | CCAR_OFLOW |      \
     CNO_RTSDTR)

/*
 * Set TTY buffer sizes.
 */

#define TTYBUF_MAX 65536

#ifdef PRINTF_BUFR_SIZE
#define TTY_PRBUF_SIZE PRINTF_BUFR_SIZE
#else
#define TTY_PRBUF_SIZE 256
#endif

/* Note: access to struct cdev:si_drv0.
    Since pull-in, pull-out is not provided, this field
    is constant value 0 in smart system */
#define dev2unit(d)        (0)
#define TTY_CALLOUT(tp, d) (dev2unit(d) & TTYUNIT_CALLOUT)

/*
 * Allocate buffer space if necessary, and set low watermarks, based on speed.
 * Note that the ttyxxxq_setsize() functions may drop and then reacquire the tty
 * lock during memory allocation.  They will return ENXIO if the tty disappears
 * while unlocked.
 */
static int tty_watermarks(struct lwp_tty *tp)
{
    size_t bs = 0;
    int error;

    /* Provide an input buffer for 2 seconds of data. */
    if (tp->t_termios.c_cflag & CREAD)
        bs =
            MIN(bsd_speed_to_integer(tp->t_termios.__c_ispeed) / 5, TTYBUF_MAX);
    error = ttyinq_setsize(&tp->t_inq, tp, bs);
    if (error != 0)
        return error;

    /* Set low watermark at 10% (when 90% is available). */
    tp->t_inlow = (ttyinq_getallocatedsize(&tp->t_inq) * 9) / 10;

    /* Provide an output buffer for 2 seconds of data. */
    bs = MIN(bsd_speed_to_integer(tp->t_termios.__c_ospeed) / 5, TTYBUF_MAX);
    error = ttyoutq_setsize(&tp->t_outq, tp, bs);
    if (error != 0)
        return error;

    /* Set low watermark at 10% (when 90% is available). */
    tp->t_outlow = (ttyoutq_getallocatedsize(&tp->t_outq) * 9) / 10;

    return 0;
}

/**
 * Drain outq
 */
static int tty_drain(struct lwp_tty *tp, int leaving)
{
    rt_tick_t timeout_tick;
    size_t bytes;
    int error;

#ifdef USING_BSD_HOOK
    if (ttyhook_hashook(tp, getc_inject))
        /* buffer is inaccessible */
        return 0;
#endif /* USING_BSD_HOOK */

    /*
     * For close(), use the recent historic timeout of "1 second without
     * making progress".  For tcdrain(), use t_drainwait as the timeout,
     * with zero meaning "no timeout" which gives POSIX behavior.
     */
    if (leaving)
        timeout_tick = rt_tick_get() + RT_TICK_PER_SECOND;
    else if (tp->t_drainwait != 0)
        timeout_tick = rt_tick_get() + RT_TICK_PER_SECOND * tp->t_drainwait;
    else
        timeout_tick = 0;

    /*
     * Poll the output buffer and the hardware for completion, at 10 Hz.
     * Polling is required for devices which are not able to signal an
     * interrupt when the transmitter becomes idle (most USB serial devs).
     * The unusual structure of this loop ensures we check for busy one more
     * time after tty_timedwait() returns EWOULDBLOCK, so that success has
     * higher priority than timeout if the IO completed in the last 100mS.
     */
    error = 0;
    bytes = ttyoutq_bytesused(&tp->t_outq);
    for (;;)
    {
        if (ttyoutq_bytesused(&tp->t_outq) == 0 && !ttydevsw_busy(tp))
            return 0;
        if (error != 0)
            return error;
        ttydevsw_outwakeup(tp);
        error = tty_timedwait(tp, &tp->t_outwait, RT_TICK_PER_SECOND / 10);
        if (error != 0 && error != EWOULDBLOCK)
            return error;
        else if (timeout_tick == 0 || rt_tick_get() < timeout_tick)
            error = 0;
        else if (leaving && ttyoutq_bytesused(&tp->t_outq) < bytes)
        {
            /* In close, making progress, grant an extra second. */
            error = 0;
            timeout_tick += RT_TICK_PER_SECOND;
            bytes = ttyoutq_bytesused(&tp->t_outq);
        }
    }
}

/*
 * Though ttydev_enter() and ttydev_leave() seem to be related, they
 * don't have to be used together. ttydev_enter() is used by the cdev
 * operations to prevent an actual operation from being processed when
 * the TTY has been abandoned. ttydev_leave() is used by ttydev_open()
 * and ttydev_close() to determine whether per-TTY data should be
 * deallocated.
 */

rt_inline int ttydev_enter(struct lwp_tty *tp)
{
    rt_err_t error = tty_lock(tp);
    if (error)
        RT_ASSERT(0);

    if (tty_gone(tp) || !tty_opened(tp))
    {
        /* Device is already gone. */
        tty_unlock(tp);
        return -ENXIO;
    }

    return 0;
}

static void ttydev_leave(struct lwp_tty *tp)
{
    tty_assert_locked(tp);

    if (tty_opened(tp) || tp->t_flags & TF_OPENCLOSE)
    {
        /* Device is still opened somewhere. */
        tty_unlock(tp);
        return;
    }

    tp->t_flags |= TF_OPENCLOSE;

    /* Remove console TTY. */
    constty_clear(tp);

    /* Drain any output. */
    if (!tty_gone(tp))
        tty_drain(tp, 1);

    ttydisc_close(tp);

    /* Free i/o queues now since they might be large. */
    ttyinq_free(&tp->t_inq);
    tp->t_inlow = 0;
    ttyoutq_free(&tp->t_outq);
    tp->t_outlow = 0;

#ifdef USING_BSD_KNOTE
    knlist_clear(&tp->t_inpoll.si_note, 1);
    knlist_clear(&tp->t_outpoll.si_note, 1);
#endif

    if (!tty_gone(tp))
        ttydevsw_close(tp);

    tp->t_flags &= ~TF_OPENCLOSE;
    cv_broadcast(&tp->t_dcdwait);
    tty_rel_free(tp);
}

/*
 * Operations that are exposed through the character device in /dev.
 */
static int ttydev_open(struct lwp_tty *tp, int oflags, int devtype,
                       struct rt_thread *td)
{
    rt_device_t dev = &tp->parent;
    int error;

    error = 0;
    tty_lock(tp);
    if (tty_gone(tp))
    {
        /* Device is already gone. */
        tty_unlock(tp);
        return -ENXIO;
    }

    /*
     * Block when other processes are currently opening or closing
     * the TTY.
     */
    while (tp->t_flags & TF_OPENCLOSE)
    {
        error = tty_wait(tp, &tp->t_dcdwait);
        if (error != 0)
        {
            tty_unlock(tp);
            return error;
        }
    }
    tp->t_flags |= TF_OPENCLOSE;

    /*
     * Make sure the "tty" and "cua" device cannot be opened at the
     * same time.  The console is a "tty" device.
     */
    if (TTY_CALLOUT(tp, dev))
    {
        if (tp->t_flags & (TF_OPENED_CONS | TF_OPENED_IN))
        {
            error = EBUSY;
            goto done;
        }
    }
    else
    {
        if (tp->t_flags & TF_OPENED_OUT)
        {
            error = EBUSY;
            goto done;
        }
    }

    if (tp->t_flags & TF_EXCLUDE && priv_check(td, PRIV_TTY_EXCLUSIVE))
    {
        error = EBUSY;
        goto done;
    }

    if (!tty_opened(tp))
    {
        /* Set proper termios flags. */
        if (TTY_CALLOUT(tp, dev))
#ifdef USING_BSD_INIT_LOCK_DEVICE
            tp->t_termios = tp->t_termios_init_out;
#else
            ;
#endif /* USING_BSD_INIT_LOCK_DEVICE */
        else
            tp->t_termios = tp->t_termios_init_in;

        ttydevsw_param(tp, &tp->t_termios);
        /* Prevent modem control on callout devices and /dev/console. */
        if (TTY_CALLOUT(tp, dev) || dev == dev_console)
            tp->t_termios.c_cflag |= CLOCAL;

        if ((tp->t_termios.c_cflag & CNO_RTSDTR) == 0)
            ttydevsw_modem(tp, SER_DTR | SER_RTS, 0);

        error = ttydevsw_open(tp);
        if (error != 0)
            goto done;

        ttydisc_open(tp);
        error = tty_watermarks(tp);
        if (error != 0)
            goto done;
    }

    /* Wait for Carrier Detect. */
    if ((oflags & O_NONBLOCK) == 0 && (tp->t_termios.c_cflag & CLOCAL) == 0)
    {
        while ((ttydevsw_modem(tp, 0, 0) & SER_DCD) == 0)
        {
            error = tty_wait(tp, &tp->t_dcdwait);
            if (error != 0)
                goto done;
        }
    }

    if (dev == dev_console)
        tp->t_flags |= TF_OPENED_CONS;
    else if (TTY_CALLOUT(tp, dev))
        tp->t_flags |= TF_OPENED_OUT;
    else
        tp->t_flags |= TF_OPENED_IN;
    MPASS((tp->t_flags & (TF_OPENED_CONS | TF_OPENED_IN)) == 0 ||
          (tp->t_flags & TF_OPENED_OUT) == 0);

done:
    tp->t_flags &= ~TF_OPENCLOSE;
    cv_broadcast(&tp->t_dcdwait);
    ttydev_leave(tp);

    return error;
}

static int ttydev_close(struct lwp_tty *tp, int fflag, int devtype __unused,
                        struct rt_thread *td __unused)
{
    rt_device_t dev = &tp->parent;

    tty_lock(tp);

    /*
     * Don't actually close the device if it is being used as the
     * console.
     */
    MPASS((tp->t_flags & (TF_OPENED_CONS | TF_OPENED_IN)) == 0 ||
          (tp->t_flags & TF_OPENED_OUT) == 0);
    if (dev == dev_console)
        tp->t_flags &= ~TF_OPENED_CONS;
    else
        tp->t_flags &= ~(TF_OPENED_IN | TF_OPENED_OUT);

    if (tp->t_flags & TF_OPENED)
    {
        tty_unlock(tp);
        return 0;
    }

    /* If revoking, flush output now to avoid draining it later. */
    if (fflag & FREVOKE)
        tty_flush(tp, FWRITE);

    tp->t_flags &= ~TF_EXCLUDE;

    /* Properly wake up threads that are stuck - revoke(). */
    tp->t_revokecnt++;
    tty_wakeup(tp, FREAD | FWRITE);
    cv_broadcast(&tp->t_bgwait);
    cv_broadcast(&tp->t_dcdwait);

    ttydev_leave(tp);

    return 0;
}

int tty_wait_background(struct lwp_tty *tp, struct rt_thread *td, int sig)
{
    struct rt_lwp *p;
    struct rt_processgroup *pg;
    int error;

    MPASS(sig == SIGTTIN || sig == SIGTTOU);
    tty_assert_locked(tp);

    p = td->lwp;
    for (;;)
    {
        pg = p->pgrp;
        PGRP_LOCK(pg);
        LWP_LOCK(p);

        /*
         * pg may no longer be our process group.
         * Re-check after locking.
         */
        if (p->pgrp != pg)
        {
            LWP_UNLOCK(p);
            PGRP_UNLOCK(pg);
            continue;
        }

        /*
         * The process should only sleep, when:
         * - This terminal is the controlling terminal
         * - Its process group is not the foreground process
         *   group
         * - The parent process isn't waiting for the child to
         *   exit
         * - the signal to send to the process isn't masked
         */
        if (!tty_is_ctty(tp, p) || pg == tp->t_pgrp)
        {
            /* Allow the action to happen. */
            LWP_UNLOCK(p);
            PGRP_UNLOCK(pg);
            return 0;
        }

        /* Note: process itself don't have a sigmask in smart */
        if (lwp_sigisign(p, sig) ||
            lwp_sigismember(&td->signal.sigset_mask, sig))
        {
            /* Only allow them in write()/ioctl(). */
            LWP_UNLOCK(p);
            PGRP_UNLOCK(pg);
            return (sig == SIGTTOU ? 0 : -EIO);
        }

#ifdef USING_VFORK_FLAG
        if ((p->p_flag & P_PPWAIT) != 0 || pg->is_orphaned)
#else
        if (pg->is_orphaned)
#endif
        {
            /* Don't allow the action to happen. */
            LWP_UNLOCK(p);
            PGRP_UNLOCK(pg);
            return -EIO;
        }
        LWP_UNLOCK(p);

        /*
         * Send the signal and sleep until we're the new
         * foreground process group.
         */
        if (sig != 0)
        {
            lwp_pgrp_signal_kill(pg, sig, SI_KERNEL, 0);
        }

        PGRP_UNLOCK(pg);

        error = tty_wait(tp, &tp->t_bgwait);
        if (error)
            return error;
    }
}

static int ttydev_read(struct lwp_tty *tp, struct uio *uio, int ioflag)
{
    int error;

    error = ttydev_enter(tp);
    if (error)
        goto done;
    error = ttydisc_read(tp, uio, ioflag);
    tty_unlock(tp);

    /*
     * The read() call should not throw an error when the device is
     * being destroyed. Silently convert it to an EOF.
     */
done:
    if (error == -ENXIO)
        error = 0;
    return error;
}

static int ttydev_write(struct lwp_tty *tp, struct uio *uio, int ioflag)
{
#ifdef USING_BSD_DEFER_STOP
    int defer;
#endif
    int error;

    error = ttydev_enter(tp);
    if (error)
        return error;

    if (tp->t_termios.c_lflag & TOSTOP)
    {
        error = tty_wait_background(tp, curthread, SIGTTOU);
        if (error)
            goto done;
    }

    if (ioflag & IO_NDELAY && tp->t_flags & TF_BUSY_OUT)
    {
        /* Allow non-blocking writes to bypass serialization. */
        error = ttydisc_write(tp, uio, ioflag);
    }
    else
    {
        /* Serialize write() calls. */
        while (tp->t_flags & TF_BUSY_OUT)
        {
            error = tty_wait(tp, &tp->t_outserwait);
            if (error)
                goto done;
        }

        tp->t_flags |= TF_BUSY_OUT;
#ifdef USING_BSD_DEFER_STOP
        defer = sigdeferstop(SIGDEFERSTOP_ERESTART);
#endif
        error = ttydisc_write(tp, uio, ioflag);
#ifdef USING_BSD_DEFER_STOP
        sigallowstop(defer);
#endif
        tp->t_flags &= ~TF_BUSY_OUT;
        cv_signal(&tp->t_outserwait);
    }

done:
    tty_unlock(tp);
    return error;
}

static int ttydev_ioctl(struct lwp_tty *tp, rt_ubase_t cmd, rt_caddr_t data, int fflag,
                        struct rt_thread *td)
{
    int error;

    error = ttydev_enter(tp);
    if (error)
        return (error);

    switch (cmd)
    {
        case TIOCCBRK:
        case TIOCCONS:
        case TIOCDRAIN:
        case TIOCEXCL:
        case TIOCFLUSH:
        case TIOCNXCL:
        case TIOCSBRK:
        case TIOCSCTTY:
        case TIOCSETA:
        case TIOCSETAF:
        case TIOCSETAW:
        case TIOCSPGRP:
        case TIOCSTART:
        case TIOCSTAT:
        case TIOCSTI:
        case TIOCSTOP:
        case TIOCSWINSZ:
#if 0
	case TIOCSDRAINWAIT:
	case TIOCSETD:
#endif
#ifdef COMPAT_43TTY
        case TIOCLBIC:
        case TIOCLBIS:
        case TIOCLSET:
        case TIOCSETC:
        case OTIOCSETD:
        case TIOCSETN:
        case TIOCSETP:
        case TIOCSLTC:
#endif /* COMPAT_43TTY */
            /*
             * If the ioctl() causes the TTY to be modified, let it
             * wait in the background.
             */
            error = tty_wait_background(tp, curthread, SIGTTOU);
            if (error)
                goto done;
    }

#ifdef USING_BSD_INIT_LOCK_DEVICE
    if (cmd == TIOCSETA || cmd == TIOCSETAW || cmd == TIOCSETAF)
    {
        struct termios *old = &tp->t_termios;
        struct termios *new = (struct termios *)data;
        struct termios *lock = TTY_CALLOUT(tp, dev) ? &tp->t_termios_lock_out
                                                    : &tp->t_termios_lock_in;
        int cc;

        /*
         * Lock state devices.  Just overwrite the values of the
         * commands that are currently in use.
         */
        new->c_iflag =
            (old->c_iflag & lock->c_iflag) | (new->c_iflag & ~lock->c_iflag);
        new->c_oflag =
            (old->c_oflag & lock->c_oflag) | (new->c_oflag & ~lock->c_oflag);
        new->c_cflag =
            (old->c_cflag & lock->c_cflag) | (new->c_cflag & ~lock->c_cflag);
        new->c_lflag =
            (old->c_lflag & lock->c_lflag) | (new->c_lflag & ~lock->c_lflag);
        for (cc = 0; cc < NCCS; ++cc)
            if (lock->c_cc[cc])
                new->c_cc[cc] = old->c_cc[cc];
        if (lock->__c_ispeed)
            new->__c_ispeed = old->__c_ispeed;
        if (lock->__c_ospeed)
            new->__c_ospeed = old->__c_ospeed;
    }
#endif /* USING_BSD_INIT_LOCK_DEVICE */

    error = tty_ioctl(tp, cmd, data, fflag, td);
done:
    tty_unlock(tp);

    return (error);
}

static int ttydev_poll(struct lwp_tty *tp, rt_pollreq_t *req, struct rt_thread *td)
{
    int events = req->_key;
    int error, revents = 0;

    error = ttydev_enter(tp);
    if (error)
        return ((events & (POLLIN | POLLRDNORM)) | POLLHUP);

    if (events & (POLLIN | POLLRDNORM))
    {
        /* See if we can read something. */
        if (ttydisc_read_poll(tp) > 0)
            revents |= events & (POLLIN | POLLRDNORM);
    }

    if (tp->t_flags & TF_ZOMBIE)
    {
        /* Hangup flag on zombie state. */
        revents |= POLLHUP;
    }
    else if (events & (POLLOUT | POLLWRNORM))
    {
        /* See if we can write something. */
        if (ttydisc_write_poll(tp) > 0)
            revents |= events & (POLLOUT | POLLWRNORM);
    }

    if (revents == 0)
    {
        if (events & (POLLIN | POLLRDNORM))
            rt_poll_add(&tp->t_inpoll, req);
        if (events & (POLLOUT | POLLWRNORM))
            rt_poll_add(&tp->t_outpoll, req);
    }

    tty_unlock(tp);

    return revents;
}

static struct cdevsw ttydev_cdevsw = {
    .d_open = ttydev_open,
    .d_close = ttydev_close,
    .d_read = ttydev_read,
    .d_write = ttydev_write,
    .d_ioctl = ttydev_ioctl,
#if 0
    .d_kqfilter = ttydev_kqfilter,
#endif
    .d_poll = ttydev_poll,
#if 0
    .d_mmap = ttydev_mmap,
#endif

#ifdef USING_BSD_RAW_CDEVSW
    .d_version = D_VERSION.d_name = "ttydev",
    .d_flags = D_TTY,
#endif /* USING_BSD_RAW_CDEVSW */
};

extern struct cdevsw bsd_ttydev_methods __attribute__((alias("ttydev_cdevsw")));

/*
 * Standard device routine implementations, mostly meant for
 * pseudo-terminal device drivers. When a driver creates a new terminal
 * device class, missing routines are patched.
 */
#define panic(msg) RT_ASSERT(0 && msg)

static int ttydevsw_defopen(struct lwp_tty *tp __unused)
{
    return 0;
}

static void ttydevsw_defclose(struct lwp_tty *tp __unused)
{
}

static void ttydevsw_defoutwakeup(struct lwp_tty *tp __unused)
{
    panic("Terminal device has output, while not implemented");
}

static void ttydevsw_definwakeup(struct lwp_tty *tp __unused)
{
}

static int ttydevsw_defioctl(struct lwp_tty *tp __unused, rt_ubase_t cmd __unused,
                             rt_caddr_t data __unused,
                             struct rt_thread *td __unused)
{
    return -ENOSYS;
}

static int ttydevsw_defcioctl(struct lwp_tty *tp __unused, int unit __unused,
                              rt_ubase_t cmd __unused, rt_caddr_t data __unused,
                              struct rt_thread *td __unused)
{
    return -ENOSYS;
}

static int ttydevsw_defparam(struct lwp_tty *tp __unused, struct termios *t)
{
    /*
     * Allow the baud rate to be adjusted for pseudo-devices, but at
     * least restrict it to 115200 to prevent excessive buffer
     * usage.  Also disallow 0, to prevent foot shooting.
     */
    if (t->__c_ispeed < B50)
        t->__c_ispeed = B50;
    else if (t->__c_ispeed > B115200)
        t->__c_ispeed = B115200;
    if (t->__c_ospeed < B50)
        t->__c_ospeed = B50;
    else if (t->__c_ospeed > B115200)
        t->__c_ospeed = B115200;
    t->c_cflag |= CREAD;

    return 0;
}

static int ttydevsw_defmodem(struct lwp_tty *tp __unused, int sigon __unused,
                             int sigoff __unused)
{
    /* Simulate a carrier to make the TTY layer happy. */
    return (SER_DCD);
}

static int ttydevsw_defmmap(struct lwp_tty *tp __unused,
                            vm_ooffset_t offset __unused,
                            vm_paddr_t *paddr __unused, int nprot __unused,
                            vm_memattr_t *memattr __unused)
{
    return (-1);
}

static void ttydevsw_defpktnotify(struct lwp_tty *tp __unused,
                                  char event __unused)
{
}

static void ttydevsw_deffree(void *softc __unused)
{
    panic("Terminal device freed without a free-handler");
}

static rt_bool_t ttydevsw_defbusy(struct lwp_tty *tp __unused)
{
    return (RT_FALSE);
}

void bsd_devsw_init(struct lwp_ttydevsw *tsw)
{
    /* Make sure the driver defines all routines. */
#define PATCH_FUNC(x)                       \
    do                                      \
    {                                       \
        if (tsw->tsw_##x == NULL)           \
            tsw->tsw_##x = ttydevsw_def##x; \
    } while (0)

    PATCH_FUNC(open);
    PATCH_FUNC(close);
    PATCH_FUNC(outwakeup);
    PATCH_FUNC(inwakeup);
    PATCH_FUNC(ioctl);
    PATCH_FUNC(cioctl);
    PATCH_FUNC(param);
    PATCH_FUNC(modem);
    PATCH_FUNC(mmap);
    PATCH_FUNC(pktnotify);
    PATCH_FUNC(free);
    PATCH_FUNC(busy);
#undef PATCH_FUNC
}

/* release tty, and free the cdev resource */
static void tty_rel_free(struct lwp_tty *tp)
{
#ifdef USING_BSD_CHAR_DEVICE
    struct cdev *dev;
#endif

    tty_assert_locked(tp);

#define TF_ACTIVITY (TF_GONE | TF_OPENED | TF_HOOK | TF_OPENCLOSE)
    if (tp->t_sessioncnt != 0 || (tp->t_flags & TF_ACTIVITY) != TF_GONE)
    {
        /* TTY is still in use. */
        tty_unlock(tp);
        return;
    }

#ifdef USING_BSD_AIO
    /* Stop asynchronous I/O. */
    funsetown(&tp->t_sigio);
#endif /* USING_BSD_AIO */

#ifdef USING_BSD_CHAR_DEVICE
    /* TTY can be deallocated. */
    dev = tp->t_dev;
    tp->t_dev = NULL;
#endif /* USING_BSD_CHAR_DEVICE */

    tty_unlock(tp);

#ifdef USING_BSD_CHAR_DEVICE
    if (dev != NULL)
    {
        sx_xlock(&tty_list_sx);
        TAILQ_REMOVE(&tty_list, tp, t_list);
        tty_list_count--;
        sx_xunlock(&tty_list_sx);
        destroy_dev_sched_cb(dev, tty_dealloc, tp);
    }
#else
    lwp_tty_delete(tp);
#endif
}

void tty_rel_pgrp(struct lwp_tty *tp, struct rt_processgroup *pg)
{
    MPASS(tp->t_sessioncnt > 0);
    tty_assert_locked(tp);

    if (tp->t_pgrp == pg)
        tp->t_pgrp = NULL;

    tty_unlock(tp);
}

void tty_rel_sess(struct lwp_tty *tp, struct rt_session *sess)
{
    MPASS(tp->t_sessioncnt > 0);

    /* Current session has left. */
    if (tp->t_session == sess)
    {
        tp->t_session = NULL;
        MPASS(tp->t_pgrp == NULL);
    }
    tp->t_sessioncnt--;
    tty_rel_free(tp);
}

/* deallocate the tty */
void tty_rel_gone(struct lwp_tty *tp)
{
    tty_assert_locked(tp);
    MPASS(!tty_gone(tp));

    /* Simulate carrier removal. */
    ttydisc_modem(tp, 0);

    /* Wake up all blocked threads. */
    tty_wakeup(tp, FREAD | FWRITE);
    cv_broadcast(&tp->t_bgwait);
    cv_broadcast(&tp->t_dcdwait);

    tp->t_flags |= TF_GONE;
    tty_rel_free(tp);
}

static int tty_drop_ctty(struct lwp_tty *tp, struct rt_lwp *p)
{
    struct rt_session *session;
#ifdef USING_BSD_VNODE
    struct vnode *vp;
#endif

    /*
     * This looks terrible, but it's generally safe as long as the tty
     * hasn't gone away while we had the lock dropped.  All of our sanity
     * checking that this operation is OK happens after we've picked it back
     * up, so other state changes are generally not fatal and the potential
     * for this particular operation to happen out-of-order in a
     * multithreaded scenario is likely a non-issue.
     */
    tty_unlock(tp);
    LWP_LOCK(p);
    tty_lock(tp);
    if (tty_gone(tp))
    {
        LWP_UNLOCK(p);
        return -ENODEV;
    }

    /*
     * If the session doesn't have a controlling TTY, or if we weren't
     * invoked on the controlling TTY, we'll return ENOIOCTL as we've
     * historically done.
     */
    session = p->pgrp->session;
    if (session->ctty == NULL || session->ctty != tp)
    {
        LWP_UNLOCK(p);
        return -ENOTTY;
    }

    if (!is_sess_leader(p))
    {
        LWP_UNLOCK(p);
        return -EPERM;
    }

    SESS_LOCK(session);
#ifdef USING_BSD_VNODE
    vp = session->s_ttyvp;
#endif
    session->ctty = NULL;
#ifdef USING_BSD_VNODE
    session->s_ttyvp = NULL;
    session->s_ttydp = NULL;
#endif
    SESS_UNLOCK(session);

    tp->t_sessioncnt--;
    p->term_ctrlterm = RT_FALSE;
    LWP_UNLOCK(p);

#ifdef USING_BSD_VNODE
    /*
     * If we did have a vnode, release our reference.  Ordinarily we manage
     * these at the devfs layer, but we can't necessarily know that we were
     * invoked on the vnode referenced in the session (i.e. the vnode we
     * hold a reference to).  We explicitly don't check VBAD/VIRF_DOOMED here
     * to avoid a vnode leak -- in circumstances elsewhere where we'd hit a
     * VIRF_DOOMED vnode, release has been deferred until the controlling TTY
     * is either changed or released.
     */
    if (vp != NULL)
        devfs_ctty_unref(vp);
#endif

    return 0;
}

void tty_wakeup(struct lwp_tty *tp, int flags)
{
#ifdef USING_BSD_AIO
    if (tp->t_flags & TF_ASYNC && tp->t_sigio != NULL)
        pgsigio(&tp->t_sigio, SIGIO, (tp->t_session != NULL));
#endif

    if (flags & FWRITE)
    {
        cv_broadcast(&tp->t_outwait);
#ifdef USING_BSD_POLL
        selwakeup(&tp->t_outpoll);
        KNOTE_LOCKED(&tp->t_outpoll.si_note, 0);
#else
        rt_wqueue_wakeup_all(&tp->t_outpoll, (void *)POLLOUT);
#endif
    }
    if (flags & FREAD)
    {
        cv_broadcast(&tp->t_inwait);
#ifdef USING_BSD_POLL
        selwakeup(&tp->t_inpoll);
        KNOTE_LOCKED(&tp->t_inpoll.si_note, 0);
#else
        rt_wqueue_wakeup_all(&tp->t_inpoll, (void *)POLLIN);
#endif
    }
}

int tty_wait(struct lwp_tty *tp, struct rt_condvar *cv)
{
    int error;
    int revokecnt = tp->t_revokecnt;

    tty_lock_assert(tp, MA_OWNED | MA_NOTRECURSED);
    MPASS(!tty_gone(tp));

    error = cv_wait_sig(cv, tp->t_mtx);

    /* Bail out when the device slipped away. */
    if (tty_gone(tp))
        return -ENXIO;

    /* Restart the system call when we may have been revoked. */
    if (tp->t_revokecnt != revokecnt)
        return -ERESTART;

    return error;
}

int tty_timedwait(struct lwp_tty *tp, struct rt_condvar *cv, rt_tick_t timeout)
{
    int error;
    int revokecnt = tp->t_revokecnt;

    tty_lock_assert(tp, MA_OWNED | MA_NOTRECURSED);
    MPASS(!tty_gone(tp));

    error = cv_timedwait_sig(cv, tp->t_mtx, timeout);

    /* Bail out when the device slipped away. */
    if (tty_gone(tp))
        return -ENXIO;

    /* Restart the system call when we may have been revoked. */
    if (tp->t_revokecnt != revokecnt)
        return -ERESTART;

    return error;
}

/* discard data in I/O buffers */
void tty_flush(struct lwp_tty *tp, int flags)
{
    if (flags & FWRITE)
    {
        tp->t_flags &= ~TF_HIWAT_OUT;
        ttyoutq_flush(&tp->t_outq);
        tty_wakeup(tp, FWRITE);
        if (!tty_gone(tp))
        {
            ttydevsw_outwakeup(tp);
            ttydevsw_pktnotify(tp, TIOCPKT_FLUSHWRITE);
        }
    }
    if (flags & FREAD)
    {
        tty_hiwat_in_unblock(tp);
        ttyinq_flush(&tp->t_inq);
        tty_wakeup(tp, FREAD);
        if (!tty_gone(tp))
        {
            ttydevsw_inwakeup(tp);
            ttydevsw_pktnotify(tp, TIOCPKT_FLUSHREAD);
        }
    }
}

void tty_set_winsize(struct lwp_tty *tp, const struct winsize *wsz)
{
    if (memcmp(&tp->t_winsize, wsz, sizeof(*wsz)) == 0)
        return;
    tp->t_winsize = *wsz;
    lwp_tty_signal_pgrp(tp, SIGWINCH);
}

static int tty_generic_ioctl(struct lwp_tty *tp, rt_ubase_t cmd, void *data,
                             int fflag, struct rt_thread *td)
{
    int error;

    switch (cmd)
    {
        /*
         * Modem commands.
         * The SER_* and TIOCM_* flags are the same, but one bit
         * shifted. I don't know why.
         */
        case TIOCSDTR:
            ttydevsw_modem(tp, SER_DTR, 0);
            return 0;
        case TIOCCDTR:
            ttydevsw_modem(tp, 0, SER_DTR);
            return 0;
        case TIOCMSET: {
            int bits = *(int *)data;
            ttydevsw_modem(tp, (bits & (TIOCM_DTR | TIOCM_RTS)) >> 1,
                           ((~bits) & (TIOCM_DTR | TIOCM_RTS)) >> 1);
            return 0;
        }
        case TIOCMBIS: {
            int bits = *(int *)data;
            ttydevsw_modem(tp, (bits & (TIOCM_DTR | TIOCM_RTS)) >> 1, 0);
            return 0;
        }
        case TIOCMBIC: {
            int bits = *(int *)data;
            ttydevsw_modem(tp, 0, (bits & (TIOCM_DTR | TIOCM_RTS)) >> 1);
            return 0;
        }
        case TIOCMGET:
            *(int *)data = TIOCM_LE + (ttydevsw_modem(tp, 0, 0) << 1);
            return 0;

        case FIOASYNC:
            if (*(int *)data)
                tp->t_flags |= TF_ASYNC;
            else
                tp->t_flags &= ~TF_ASYNC;
            return 0;
        case FIONBIO:
            /* This device supports non-blocking operation. */
            return 0;
        case FIONREAD:
            *(int *)data = ttyinq_bytescanonicalized(&tp->t_inq);
            return 0;
        case FIONWRITE:
        case TIOCOUTQ:
            *(int *)data = ttyoutq_bytesused(&tp->t_outq);
            return 0;
#if BSD_USING_FIO_OWNERSHIP
        case FIOSETOWN:
            if (tp->t_session != NULL && !tty_is_ctty(tp, td->lwp))
                /* Not allowed to set ownership. */
                return -ENOTTY;

            /* Temporarily unlock the TTY to set ownership. */
            tty_unlock(tp);
            error = fsetown(*(int *)data, &tp->t_sigio);
            tty_lock(tp);
            return (error);
        case FIOGETOWN:
            if (tp->t_session != NULL && !tty_is_ctty(tp, td->lwp))
                /* Not allowed to set ownership. */
                return -ENOTTY;

            /* Get ownership. */
            *(int *)data = fgetown(&tp->t_sigio);
            return 0;
#endif
        case TIOCGETA:
            /* Obtain terminal flags through tcgetattr(). */
            *(struct termios *)data = tp->t_termios;
            return 0;
        case TIOCSETA:
        case TIOCSETAW:
        case TIOCSETAF: {
            struct termios *t = data;

            /*
             * Who makes up these funny rules? According to POSIX,
             * input baud rate is set equal to the output baud rate
             * when zero.
             */
            if (t->__c_ispeed == 0)
                t->__c_ispeed = t->__c_ospeed;

            /* Discard any unsupported bits. */
            t->c_iflag &= TTYSUP_IFLAG;
            t->c_oflag &= TTYSUP_OFLAG;
            t->c_lflag &= TTYSUP_LFLAG;
            t->c_cflag &= TTYSUP_CFLAG;

            /* Set terminal flags through tcsetattr(). */
            if (cmd == TIOCSETAW || cmd == TIOCSETAF)
            {
                error = tty_drain(tp, 0);
                if (error)
                    return (error);
                if (cmd == TIOCSETAF)
                    tty_flush(tp, FREAD);
            }

            /*
             * Only call param() when the flags really change.
             */
            if ((t->c_cflag & CIGNORE) == 0 &&
                (tp->t_termios.c_cflag != t->c_cflag ||
                 ((tp->t_termios.c_iflag ^ t->c_iflag) &
                  (IXON | IXOFF | IXANY)) ||
                 tp->t_termios.__c_ispeed != t->__c_ispeed ||
                 tp->t_termios.__c_ospeed != t->__c_ospeed))
            {
                error = ttydevsw_param(tp, t);
                if (error)
                    return (error);

                /* XXX: CLOCAL? */

                tp->t_termios.c_cflag = t->c_cflag & ~CIGNORE;
                tp->t_termios.__c_ispeed = t->__c_ispeed;
                tp->t_termios.__c_ospeed = t->__c_ospeed;

                /* Baud rate has changed - update watermarks. */
                error = tty_watermarks(tp);
                if (error)
                    return (error);
            }

            /* Copy new non-device driver parameters. */
            tp->t_termios.c_iflag = t->c_iflag;
            tp->t_termios.c_oflag = t->c_oflag;
            tp->t_termios.c_lflag = t->c_lflag;
            memcpy(&tp->t_termios.c_cc, t->c_cc, sizeof t->c_cc);

            ttydisc_optimize(tp);

            if ((t->c_lflag & ICANON) == 0)
            {
                /*
                 * When in non-canonical mode, wake up all
                 * readers. Canonicalize any partial input. VMIN
                 * and VTIME could also be adjusted.
                 */
                ttyinq_canonicalize(&tp->t_inq);
                tty_wakeup(tp, FREAD);
            }

            /**
             * For packet mode: notify the PTY consumer that VSTOP
             * and VSTART may have been changed.
             *
             * TODO: change the _CONTROL('S') to a CSTOP?
             */
            if (tp->t_termios.c_iflag & IXON &&
                tp->t_termios.c_cc[VSTOP] == _CONTROL('S') &&
                tp->t_termios.c_cc[VSTART] == _CONTROL('Q'))
                ttydevsw_pktnotify(tp, TIOCPKT_DOSTOP);
            else
                ttydevsw_pktnotify(tp, TIOCPKT_NOSTOP);
            return 0;
        }
        case TIOCGETD:
            /* For compatibility - we only support TTYDISC. */
            *(int *)data = TTYDISC;
            return 0;
        case TIOCGPGRP:
            if (!tty_is_ctty(tp, td->lwp))
                return -ENOTTY;

            if (tp->t_pgrp != NULL)
                *(int *)data = tp->t_pgrp->pgid;
            else
                *(int *)data = NO_PID;
            return 0;
        case TIOCGSID:
            if (!tty_is_ctty(tp, td->lwp))
                return -ENOTTY;

            MPASS(tp->t_session);
            *(int *)data = tp->t_session->sid;
            return 0;
        case TIOCNOTTY:
            return tty_drop_ctty(tp, td->lwp);
        case TIOCSCTTY:
            return lwp_tty_set_ctrl_proc(tp, td);
        case TIOCSPGRP: {
            int pgid;
            if (lwp_in_user_space((void *)data))
            {
                if (lwp_get_from_user(&pgid, data, sizeof(int)) != sizeof(int))
                    return -EFAULT;
            }
            else
            {
                pgid = *(int *)data;
            }
            return lwp_tty_assign_foreground(tp, td, pgid);
        }
        case TIOCFLUSH: {
            int flags = *(int *)data;

            if (flags == 0)
                flags = (FREAD | FWRITE);
            else
                flags &= (FREAD | FWRITE);
            tty_flush(tp, flags);
            return 0;
        }
        case TIOCDRAIN:
            /* Drain TTY output. */
            return tty_drain(tp, 0);
        case TIOCGDRAINWAIT:
            *(int *)data = tp->t_drainwait;
            return 0;
        case TIOCSDRAINWAIT:
            error = priv_check(td, PRIV_TTY_DRAINWAIT);
            if (error == 0)
                tp->t_drainwait = *(int *)data;
            return (error);
        case TIOCCONS:
            /* Set terminal as console TTY. */
            if (*(int *)data)
            {
                error = priv_check(td, PRIV_TTY_CONSOLE);
                if (error)
                    return (error);
                error = constty_set(tp);
            }
            else
            {
                error = constty_clear(tp);
            }
            return (error);
        case TIOCGWINSZ:
            /* Obtain window size. */
            *(struct winsize *)data = tp->t_winsize;
            return 0;
        case TIOCSWINSZ:
            /* Set window size. */
            tty_set_winsize(tp, data);
            return 0;
        case TIOCEXCL:
            tp->t_flags |= TF_EXCLUDE;
            return 0;
        case TIOCNXCL:
            tp->t_flags &= ~TF_EXCLUDE;
            return 0;
        case TIOCSTOP:
            tp->t_flags |= TF_STOPPED;
            ttydevsw_pktnotify(tp, TIOCPKT_STOP);
            return 0;
        case TIOCSTART:
            tp->t_flags &= ~TF_STOPPED;
            tp->t_termios.c_lflag &= ~FLUSHO;
            ttydevsw_outwakeup(tp);
            ttydevsw_pktnotify(tp, TIOCPKT_START);
            return 0;
        case TIOCSTAT:
            tty_info(tp);
            return 0;
        case TIOCSTI:
            if ((fflag & FREAD) == 0 && priv_check(td, PRIV_TTY_STI))
                return -EPERM;
            if (!tty_is_ctty(tp, td->lwp) && priv_check(td, PRIV_TTY_STI))
                return -EACCES;
            ttydisc_rint(tp, *(char *)data, 0);
            ttydisc_rint_done(tp);
            return 0;
    }

#ifdef COMPAT_43TTY
    return tty_ioctl_compat(tp, cmd, data, fflag, td);
#else  /* !COMPAT_43TTY */
    return -ENOIOCTL;
#endif /* COMPAT_43TTY */
}

int tty_ioctl(struct lwp_tty *tp, rt_ubase_t cmd, void *data, int fflag,
              struct rt_thread *td)
{
    int error;

    tty_assert_locked(tp);

    if (tty_gone(tp))
        return -ENXIO;

    error = ttydevsw_ioctl(tp, cmd, data, td);
    if (error == -ENOIOCTL)
        error = tty_generic_ioctl(tp, cmd, data, fflag, td);

    return error;
}

int tty_checkoutq(struct lwp_tty *tp)
{
    /* 256 bytes should be enough to print a log message. */
    return (ttyoutq_bytesleft(&tp->t_outq) >= 256);
}

void tty_hiwat_in_block(struct lwp_tty *tp)
{
    if ((tp->t_flags & TF_HIWAT_IN) == 0 && tp->t_termios.c_iflag & IXOFF &&
        tp->t_termios.c_cc[VSTOP] != _POSIX_VDISABLE)
    {
        /*
         * Input flow control. Only enter the high watermark when we
         * can successfully store the VSTOP character.
         */
        if (ttyoutq_write_nofrag(&tp->t_outq, &tp->t_termios.c_cc[VSTOP], 1) ==
            0)
            tp->t_flags |= TF_HIWAT_IN;
    }
    else
    {
        /* No input flow control. */
        tp->t_flags |= TF_HIWAT_IN;
    }
}

void tty_hiwat_in_unblock(struct lwp_tty *tp)
{
    if (tp->t_flags & TF_HIWAT_IN && tp->t_termios.c_iflag & IXOFF &&
        tp->t_termios.c_cc[VSTART] != _POSIX_VDISABLE)
    {
        /*
         * Input flow control. Only leave the high watermark when we
         * can successfully store the VSTART character.
         */
        if (ttyoutq_write_nofrag(&tp->t_outq, &tp->t_termios.c_cc[VSTART], 1) ==
            0)
            tp->t_flags &= ~TF_HIWAT_IN;
    }
    else
    {
        /* No input flow control. */
        tp->t_flags &= ~TF_HIWAT_IN;
    }

    if (!tty_gone(tp))
        ttydevsw_inwakeup(tp);
}
