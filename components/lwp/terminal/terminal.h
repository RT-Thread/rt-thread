/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-13     Shell        init ver.
 */

#ifndef __LWP_TERMINAL_H__
#define __LWP_TERMINAL_H__

#include "bsd_ttyqueue.h"
#include "bsd_ttydisc.h"

#ifdef USING_BSD_HOOK
#include "bsd_ttyhook.h"
#endif

#include <lwp.h>
#include <rtdef.h>

/* include kernel header for termios base definitions */
#include <termios.h>
/* for _POSIX_VDISABLE */
#include <unistd.h>

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

struct lwp_tty;

/*
 * Driver routines that are called from the line discipline to adjust
 * hardware parameters and such.
 */
typedef int tsw_open_t(struct lwp_tty *tp);
typedef void tsw_close_t(struct lwp_tty *tp);
typedef void tsw_outwakeup_t(struct lwp_tty *tp);
typedef void tsw_inwakeup_t(struct lwp_tty *tp);
typedef int tsw_ioctl_t(struct lwp_tty *tp, rt_ubase_t cmd, rt_caddr_t data,
                        struct rt_thread *td);
typedef int tsw_cioctl_t(struct lwp_tty *tp, int unit, rt_ubase_t cmd, rt_caddr_t data,
                         struct rt_thread *td);
typedef int tsw_param_t(struct lwp_tty *tp, struct termios *t);
typedef int tsw_modem_t(struct lwp_tty *tp, int sigon, int sigoff);
typedef int tsw_mmap_t(struct lwp_tty *tp, vm_ooffset_t offset,
                       vm_paddr_t *paddr, int nprot, vm_memattr_t *memattr);

typedef void tsw_pktnotify_t(struct lwp_tty *tp, char event);
typedef void tsw_free_t(void *softc);
typedef rt_bool_t tsw_busy_t(struct lwp_tty *tp);

struct lwp_ttydevsw
{
    unsigned int tsw_flags; /* Default TTY flags. */

    tsw_open_t *tsw_open;   /* Device opening. */
    tsw_close_t *tsw_close; /* Device closure. */

    tsw_outwakeup_t *tsw_outwakeup; /* Output available. */
    tsw_inwakeup_t *tsw_inwakeup;   /* Input can be stored again. */

    tsw_ioctl_t *tsw_ioctl;   /* ioctl() hooks. */
    tsw_cioctl_t *tsw_cioctl; /* ioctl() on control devices. */
    tsw_param_t *tsw_param;   /* TIOCSETA device parameter setting. */
    tsw_modem_t *tsw_modem;   /* Modem sigon/sigoff. */

    tsw_mmap_t *tsw_mmap;           /* mmap() hooks. */
    tsw_pktnotify_t *tsw_pktnotify; /* TIOCPKT events. */

    tsw_free_t *tsw_free; /* Destructor. */

    tsw_busy_t *tsw_busy; /* Draining output. */

    void *tsw_spare[3]; /* For future use. */
};
typedef struct lwp_ttydevsw *lwp_ttydevsw_t;

struct lwp_tty
{
    struct rt_device parent;  /* inherit from Class:RT_Device */
    struct rt_mutex *t_mtx;   /* TTY lock. */
    struct rt_mutex t_mtxobj; /* Per-TTY lock (when not borrowing). */
    rt_list_t t_list;         /* (l) TTY list entry. */
    int t_drainwait;          /* (t) TIOCDRAIN timeout seconds. */
    unsigned int t_flags;     /* (t) Terminal option flags. */
/* Keep flags in sync with db_show_tty and pstat(8). */
#define TF_NOPREFIX    0x00001 /* Don't prepend "tty" to device name. */
#define TF_INITLOCK    0x00002 /* Create init/lock state devices. */
#define TF_CALLOUT     0x00004 /* Create "cua" devices. */
#define TF_OPENED_IN   0x00008 /* "tty" node is in use. */
#define TF_OPENED_OUT  0x00010 /* "cua" node is in use. */
#define TF_OPENED_CONS 0x00020 /* Device in use as console. */
#define TF_OPENED      (TF_OPENED_IN | TF_OPENED_OUT | TF_OPENED_CONS)
#define TF_GONE        0x00040 /* Device node is gone. */
#define TF_OPENCLOSE   0x00080 /* Device is in open()/close(). */
#define TF_ASYNC       0x00100 /* Asynchronous I/O enabled. */
#define TF_LITERAL     0x00200 /* Accept the next character literally. */
#define TF_HIWAT_IN    0x00400 /* We've reached the input watermark. */
#define TF_HIWAT_OUT   0x00800 /* We've reached the output watermark. */
#define TF_HIWAT       (TF_HIWAT_IN | TF_HIWAT_OUT)
#define TF_STOPPED     0x01000 /* Output flow control - stopped. */
#define TF_EXCLUDE     0x02000 /* Exclusive access. */
#define TF_BYPASS      0x04000 /* Optimized input path. */
#define TF_ZOMBIE      0x08000 /* Modem disconnect received. */
#define TF_HOOK        0x10000 /* TTY has hook attached. */
#define TF_BUSY_IN     0x20000 /* Process busy in read() -- not supported. */
#define TF_BUSY_OUT    0x40000 /* Process busy in write(). */
#define TF_BUSY        (TF_BUSY_IN | TF_BUSY_OUT)
    unsigned int t_revokecnt; /* (t) revoke() count. */

    /* Buffering mechanisms. */
    struct ttyinq t_inq;   /* (t) Input queue. */
    size_t t_inlow;        /* (t) Input low watermark. */
    struct ttyoutq t_outq; /* (t) Output queue. */
    size_t t_outlow;       /* (t) Output low watermark. */

    /* Sleeping mechanisms. */
    struct rt_condvar t_inwait;     /* (t) Input wait queue. */
    struct rt_condvar t_outwait;    /* (t) Output wait queue. */
    struct rt_condvar t_outserwait; /* (t) Serial output wait queue. */
    struct rt_condvar t_bgwait;     /* (t) Background wait queue. */
    struct rt_condvar t_dcdwait;    /* (t) Carrier Detect wait queue. */

    struct rt_wqueue t_inpoll;  /* (t) Input poll queue. */
    struct rt_wqueue t_outpoll; /* (t) Output poll queue. */

#ifdef USING_BSD_AIO
    struct sigio *t_sigio; /* (t) Asynchronous I/O. */
#endif

    struct termios t_termios; /* (t) I/O processing flags. */
    struct winsize t_winsize; /* (t) Window size. */
    unsigned int t_column;    /* (t) Current cursor position. */
    unsigned int t_writepos;  /* (t) Where input was interrupted. */
    int t_compatflags;        /* (t) COMPAT_43TTY flags. */

    /* Init/lock-state devices. */
    struct termios t_termios_init_in; /* tty%s.init. */
    struct termios t_termios_lock_in;  /* tty%s.lock. */
#ifdef USING_BSD_INIT_LOCK_DEVICE
    struct termios t_termios_init_out; /* cua%s.init. */
    struct termios t_termios_lock_out; /* cua%s.lock. */

#endif /* USING_BSD_INIT_LOCK_DEVICE */

    struct lwp_ttydevsw *t_devsw; /* (c) Driver hooks. */
#ifdef USING_BSD_HOOK
    struct lwp_ttyhook *t_hook; /* (t) Capture/inject hook. */
#endif

    /* Process signal delivery. */
    struct rt_processgroup *t_pgrp; /* (t) Foreground process group. */
    struct rt_session *t_session;   /* (t) Associated session. */
    unsigned int t_sessioncnt;      /* (t) Backpointing sessions. */

    void *t_devswsoftc; /* (c) Soft config, for drivers. */
#ifdef USING_BSD_HOOK
    void *t_hooksoftc; /* (t) Soft config, for hooks. */
#endif
#ifdef USING_BSD_CHAR_DEVICE
    struct cdev *t_dev; /* (c) Primary character device. */
#endif                  /* USING_BSD_CHAR_DEVICE */
#ifdef USING_BSD_SIGINFO
    size_t t_prbufsz; /* (t) SIGINFO buffer size. */
    char t_prbuf[];   /* (t) SIGINFO buffer. */
#endif /* USING_BSD_SIGINFO */
};
typedef struct lwp_tty *lwp_tty_t;

/* Allocation and deallocation. */
void tty_rel_pgrp(struct lwp_tty *tp, struct rt_processgroup *pgrp);
void tty_rel_sess(struct lwp_tty *tp, struct rt_session *sess);
void tty_rel_gone(struct lwp_tty *tp);

/* tty locking mechanism */
#define tty_getlock(tp) ((tp)->t_mtx)
#define tty_lock(tp)    rt_mutex_take(tty_getlock(tp), RT_WAITING_FOREVER);
#define tty_unlock(tp)  rt_mutex_release(tty_getlock(tp))
#define tty_lock_owned(tp) \
    (rt_mutex_get_owner(tty_getlock(tp)) == rt_thread_self())
#define tty_lock_notrecused(tp) (rt_mutex_get_hold(tty_getlock(tp)) == 1)
#define tty_assert_locked(tp)   RT_ASSERT(tty_lock_owned(tp))
#define tty_lock_assert(tp, option)                        \
    RT_ASSERT(((option) == (MA_OWNED | MA_NOTRECURSED)) && \
    (tty_lock_owned(tp) && tty_lock_notrecused(tp)))

/* System messages. */
int tty_checkoutq(struct lwp_tty *tp);
int tty_putchar(struct lwp_tty *tp, char c);
int tty_putstrn(struct lwp_tty *tp, const char *p, size_t n);

int tty_ioctl(struct lwp_tty *tp, rt_ubase_t cmd, void *data, int fflag,
              struct rt_thread *td);
int tty_ioctl_compat(struct lwp_tty *tp, rt_ubase_t cmd, rt_caddr_t data, int fflag,
                     struct rt_thread *td);
void tty_set_winsize(struct lwp_tty *tp, const struct winsize *wsz);
void tty_init_console(struct lwp_tty *tp, speed_t speed);
void tty_flush(struct lwp_tty *tp, int flags);
void tty_hiwat_in_block(struct lwp_tty *tp);
void tty_hiwat_in_unblock(struct lwp_tty *tp);
dev_t tty_udev(struct lwp_tty *tp);

/* tesing on tty */
#define tty_opened(tp)  ((tp)->t_flags & TF_OPENED)
#define tty_gone(tp)    ((tp)->t_flags & TF_GONE)
#define tty_softc(tp)   ((tp)->t_devswsoftc)
#define tty_devname(tp) ((tp)->parent.parent.name)

/**
 * @brief TTY registeration on device subsystem
 *
 * @warning It's the duty of the caller to ensure that the name is not
 *          identical to any existed registered devices.
 *
 * @param terminal the target tty device
 * @param name name of the device (must be exclusive)
 * @return rt_err_t RT_EOK on success
 */
rt_err_t lwp_tty_register(lwp_tty_t terminal, const char *name);

/**
 * @brief TTY allocation and deallocation. TTY devices can be deallocated when
 *        the driver doesn't use it anymore, when the TTY isn't a session's
 *        controlling TTY and when the device node isn't opened through devfs.
 *
 * @param handle device handle of tty
 * @param softc device configuration binding on tty
 * @param prefix device name prefix
 * @param cutom_mtx the lock provided to protect tty
 * @return lwp_tty_t NULL on failure
 */
lwp_tty_t lwp_tty_create_ext(lwp_ttydevsw_t handle, void *softc,
                             rt_mutex_t custom_mtx);

/**
 * @brief Handful version of lwp_tty_create_ext
 *
 * @param softc device configuration binding on tty
 * @param cutom_mtx the lock provided to protect tty
 * @param prefix device name prefix
 * @return lwp_tty_t NULL on failure
 */
lwp_tty_t lwp_tty_create(lwp_ttydevsw_t handle, void *softc);

void lwp_tty_delete(lwp_tty_t tp);

void lwp_tty_signal_sessleader(struct lwp_tty *tp, int sig);

void lwp_tty_signal_pgrp(struct lwp_tty *tp, int sig);

/**
 * @brief Create a new pseudo-terminal multiplexer
 *
 * @param root_path path of root mount point of ptyfs
 * @return rt_device_t new device object if succeed, otherwise NULL
 */
rt_err_t lwp_ptmx_init(rt_device_t ptmx_device, const char *root_path);

#define LWP_CONSOLE_LOWEST_PRIOR 0
#define LWP_CONSOLE_HIGHEST_PRIO INT_MAX
/**
 * @brief Register an alternative backend tty device as console
 */
rt_err_t lwp_console_register_backend(struct rt_device *bakdev, int prio);

rt_inline int ttydevsw_open(struct lwp_tty *tp)
{
    tty_assert_locked(tp);
    MPASS(!tty_gone(tp));

    return (tp->t_devsw->tsw_open(tp));
}

rt_inline void ttydevsw_close(struct lwp_tty *tp)
{
    tty_assert_locked(tp);
    MPASS(!tty_gone(tp));

    tp->t_devsw->tsw_close(tp);
}

rt_inline void ttydevsw_outwakeup(struct lwp_tty *tp)
{
    tty_assert_locked(tp);
    MPASS(!tty_gone(tp));

    /* Prevent spurious wakeups. */
    if (ttydisc_getc_poll(tp) == 0)
        return;

    tp->t_devsw->tsw_outwakeup(tp);
}

rt_inline void ttydevsw_inwakeup(struct lwp_tty *tp)
{
    tty_assert_locked(tp);
    MPASS(!tty_gone(tp));

    /* Prevent spurious wakeups. */
    if (tp->t_flags & TF_HIWAT_IN)
        return;

    tp->t_devsw->tsw_inwakeup(tp);
}

rt_inline int ttydevsw_ioctl(struct lwp_tty *tp, rt_ubase_t cmd, rt_caddr_t data,
                             struct rt_thread *td)
{
    tty_assert_locked(tp);
    MPASS(!tty_gone(tp));

    return (tp->t_devsw->tsw_ioctl(tp, cmd, data, td));
}

rt_inline int ttydevsw_cioctl(struct lwp_tty *tp, int unit, rt_ubase_t cmd,
                              rt_caddr_t data, struct rt_thread *td)
{
    tty_assert_locked(tp);
    MPASS(!tty_gone(tp));

    return (tp->t_devsw->tsw_cioctl(tp, unit, cmd, data, td));
}

rt_inline int ttydevsw_param(struct lwp_tty *tp, struct termios *t)
{
    MPASS(!tty_gone(tp));

    return (tp->t_devsw->tsw_param(tp, t));
}

rt_inline int ttydevsw_modem(struct lwp_tty *tp, int sigon, int sigoff)
{
    MPASS(!tty_gone(tp));

    return (tp->t_devsw->tsw_modem(tp, sigon, sigoff));
}

rt_inline int ttydevsw_mmap(struct lwp_tty *tp, vm_ooffset_t offset,
                            vm_paddr_t *paddr, int nprot, vm_memattr_t *memattr)
{
    MPASS(!tty_gone(tp));

    return (tp->t_devsw->tsw_mmap(tp, offset, paddr, nprot, memattr));
}

rt_inline void ttydevsw_pktnotify(struct lwp_tty *tp, char event)
{
    tty_assert_locked(tp);
    MPASS(!tty_gone(tp));

    tp->t_devsw->tsw_pktnotify(tp, event);
}

rt_inline void ttydevsw_free(struct lwp_tty *tp)
{
    MPASS(tty_gone(tp));

    tp->t_devsw->tsw_free(tty_softc(tp));
}

rt_inline rt_bool_t ttydevsw_busy(struct lwp_tty *tp)
{
    tty_assert_locked(tp);
    MPASS(!tty_gone(tp));

    return (tp->t_devsw->tsw_busy(tp));
}

rt_inline size_t ttydisc_read_poll(struct lwp_tty *tp)
{
    tty_assert_locked(tp);

    return ttyinq_bytescanonicalized(&tp->t_inq);
}

rt_inline size_t ttydisc_write_poll(struct lwp_tty *tp)
{
    tty_assert_locked(tp);

    return ttyoutq_bytesleft(&tp->t_outq);
}

#endif /* __LWP_TERMINAL_H__ */
