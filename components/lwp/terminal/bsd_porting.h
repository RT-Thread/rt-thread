/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-13     Shell        Add compatible layer for FreeBSD
 */

#ifndef __LWP_TTY_BSD_PORTING_H__
#define __LWP_TTY_BSD_PORTING_H__

#include <rtthread.h>
#include <lwp_internal.h>
#define _KERNEL

#ifndef __unused
#define __unused __attribute__((__unused__))
#endif

/* functionability of bsd tty layer */
#if 0
#define USING_BSD_HOOK
#endif

/* Only for devfs d_close() flags. */
#define FLASTCLOSE O_DIRECTORY
#define FREVOKE    0x00200000

/*
 * Output flags - software output processing
 */
#if !((OPOST | OLCUC | ONLCR) & 0x8)
#define ONOEOT 0x0008 /* discard EOT's (^D) on output) */
#endif

/*
 * Kernel encoding of open mode; separate read and write bits that are
 * independently testable: 1 greater than the above.
 *
 * XXX
 * FREAD and FWRITE are excluded from the #ifdef _KERNEL so that TIOCFLUSH,
 * which was documented to use FREAD/FWRITE, continues to work.
 */
#define FREAD  0x0001
#define FWRITE 0x0002

/*
 * Flags to memory allocation functions.
 */
#define M_NOWAIT      0x0001 /* do not block */
#define M_WAITOK      0x0002 /* ok to block */
#define M_NORECLAIM   0x0080 /* do not reclaim after failure */
#define M_ZERO        0x0100 /* bzero the allocation */
#define M_NOVM        0x0200 /* don't ask VM for pages */
#define M_USE_RESERVE 0x0400 /* can alloc out of reserve memory */
#define M_NODUMP      0x0800 /* don't dump pages in this allocation */
#define M_FIRSTFIT    0x1000 /* only for vmem, fast fit */
#define M_BESTFIT     0x2000 /* only for vmem, low fragmentation */
#define M_EXEC        0x4000 /* allocate executable space */
#define M_NEXTFIT     0x8000 /* only for vmem, follow cursor */

#define M_VERSION 2020110501

/*
 * The INVARIANTS-enabled mtx_assert() functionality.
 *
 * The constants need to be defined for INVARIANT_SUPPORT infrastructure
 * support as _mtx_assert() itself uses them and the latter implies that
 * _mtx_assert() must build.
 */
#define MA_OWNED       (1)
#define MA_NOTOWNED    (2)
#define MA_RECURSED    (4)
#define MA_NOTRECURSED (8)

/*
 * Indentification of modem control signals.  These definitions match
 * the TIOCMGET definitions in <sys/ttycom.h> shifted a bit down, and
 * that identity is enforced with CTASSERT at the bottom of kern/tty.c
 * Both the modem bits and delta bits must fit in 16 bit.
 */
#define SER_DTR 0x0001 /* data terminal ready */
#define SER_RTS 0x0002 /* request to send */
#define SER_STX 0x0004 /* secondary transmit */
#define SER_SRX 0x0008 /* secondary receive */
#define SER_CTS 0x0010 /* clear to send */
#define SER_DCD 0x0020 /* data carrier detect */
#define SER_RI  0x0040 /* ring indicate */
#define SER_DSR 0x0080 /* data set ready */

#define SER_MASK_STATE 0x00ff

/*
 * Flags for ioflag. (high 16 bits used to ask for read-ahead and
 * help with write clustering)
 * NB: IO_NDELAY and IO_DIRECT are linked to fcntl.h
 */
#if 0
#define IO_UNIT   0x0001 /* do I/O as atomic unit */
#define IO_APPEND 0x0002 /* append write to end */
#endif                   /* not porting */

#define IO_NDELAY 0x0004 /* FNDELAY flag set in file table */
#if 0
#define IO_NODELOCKED  0x0008 /* underlying node already locked */
#define IO_ASYNC       0x0010 /* bawrite rather then bdwrite */
#define IO_VMIO        0x0020 /* data already in VMIO space */
#define IO_INVAL       0x0040 /* invalidate after I/O */
#define IO_SYNC        0x0080 /* do I/O synchronously */
#define IO_DIRECT      0x0100 /* attempt to bypass buffer cache */
#define IO_NOREUSE     0x0200 /* VMIO data won't be reused */
#define IO_EXT         0x0400 /* operate on external attributes */
#define IO_NORMAL      0x0800 /* operate on regular data */
#define IO_NOMACCHECK  0x1000 /* MAC checks unnecessary */
#define IO_BUFLOCKED   0x2000 /* ffs flag; indir buf is locked */
#define IO_RANGELOCKED 0x4000 /* range locked */
#define IO_DATASYNC    0x8000 /* do only data I/O synchronously */

#define IO_SEQMAX   0x7F /* seq heuristic max value */
#define IO_SEQSHIFT 16   /* seq heuristic in upper 16 bits */
#endif                   /* not porting */

/** Used to distinguish between normal, callout, lock and init devices.
 * Note: this is not used in smart system.
 */
#define TTYUNIT_INIT    0x1
#define TTYUNIT_LOCK    0x2
#define TTYUNIT_CALLOUT 0x4

/*
 * TTY privileges.
 */
#define PRIV_TTY_CONSOLE   250 /* Set console to tty. */
#define PRIV_TTY_DRAINWAIT 251 /* Set tty drain wait time. */
#define PRIV_TTY_DTRWAIT   252 /* Set DTR wait on tty. */
#define PRIV_TTY_EXCLUSIVE 253 /* Override tty exclusive flag. */
#define _PRIV_TTY_PRISON   254 /* Removed. */
#define PRIV_TTY_STI       255 /* Simulate input on another tty. */
#define PRIV_TTY_SETA      256 /* Set tty termios structure. */

#define MPASS(ex) RT_ASSERT(ex)

#if !defined(MIN)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#if !defined(MAX)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#define curthread rt_thread_self()

#ifdef USING_BSD_HOOK
#define ttyhook_hashook(tp, hook) \
    ((tp)->t_hook != NULL && (tp)->t_hook->th_##hook != NULL)
#else
#define ttyhook_hashook(tp, hook) (RT_FALSE)
#endif

/* condvar API */
#include <rtdevice.h>

#define cv_init(cvp, name) rt_condvar_init(cvp, name)
#define cv_destroy(cvp)    rt_condvar_detach(cvp)
#define cv_wait(cvp, mp) \
    rt_condvar_timedwait(cvp, mp, RT_KILLABLE, RT_WAITING_FOREVER)
#define cv_wait_sig(cvp, mp) \
    rt_condvar_timedwait(cvp, mp, RT_INTERRUPTIBLE, RT_WAITING_FOREVER)
#define cv_signal(cvp)           rt_condvar_signal(cvp)
#define cv_broadcast(cvp)        rt_condvar_broadcast(cvp)
#define cv_timedwait(cvp, mp, t) rt_condvar_timedwait(cvp, mp, RT_KILLABLE, t)
#define cv_timedwait_sig(cvp, mp, t) \
    rt_condvar_timedwait(cvp, mp, RT_INTERRUPTIBLE, t)

struct lwp_tty;
struct uio;

/* TODO: just a place holder since devfs is not capable of doing this currently
 */
struct file
{
};

typedef rt_base_t sbintime_t;
typedef rt_ubase_t vm_offset_t;
typedef rt_base_t vm_ooffset_t;
typedef rt_ubase_t vm_paddr_t;
typedef rt_ubase_t vm_pindex_t;
typedef rt_ubase_t vm_size_t;
typedef char *rt_caddr_t;

/*
 * The exact set of memory attributes is machine dependent.  However,
 * every machine is required to define VM_MEMATTR_DEFAULT and
 * VM_MEMATTR_UNCACHEABLE.
 */
typedef char vm_memattr_t; /* memory attribute codes */

typedef int d_open_t(struct lwp_tty *tp, int oflags, int devtype,
                     struct rt_thread *td);
typedef int d_fdopen_t(struct lwp_tty *tp, int oflags, struct rt_thread *td,
                       struct file *fp);
typedef int d_close_t(struct lwp_tty *tp, int fflag, int devtype,
                      struct rt_thread *td);

#ifdef USING_BSD_DEVICE_STRATEGY
typedef void d_strategy_t(struct bio *bp);
#endif

typedef int d_ioctl_t(struct lwp_tty *tp, rt_ubase_t cmd, rt_caddr_t data,
                      int fflag, struct rt_thread *td);

typedef int d_read_t(struct lwp_tty *tp, struct uio *uio, int ioflag);
typedef int d_write_t(struct lwp_tty *tp, struct uio *uio, int ioflag);
typedef int d_poll_t(struct lwp_tty *tp, rt_pollreq_t *req,
                     struct rt_thread *td);

#ifdef USING_BSD_KNOTE
typedef int d_kqfilter_t(struct lwp_tty *tp, struct knote *kn);
#endif /* USING_BSD_KNOTE */

typedef int d_mmap_t(struct lwp_tty *tp, vm_ooffset_t offset, vm_paddr_t *paddr,
                     int nprot, vm_memattr_t *memattr);

#ifdef USING_BSD_MMAP_SINGLE
typedef int d_mmap_single_t(struct cdev *cdev, vm_ooffset_t *offset,
                            vm_size_t size, struct vm_object **object,
                            int nprot);
#endif /* USING_BSD_MMAP_SINGLE */

typedef void d_purge_t(struct lwp_tty *tp);

/*
 * Character device switch table
 */
struct cdevsw
{
#ifdef USING_BSD_RAW_CDEVSW
    int d_version;
    u_int d_flags;
    const char *d_name;
#endif /* USING_BSD_RAW_CDEVSW */

    d_open_t *d_open;
    d_fdopen_t *d_fdopen;
    d_close_t *d_close;
    d_read_t *d_read;
    d_write_t *d_write;
    d_ioctl_t *d_ioctl;
    d_poll_t *d_poll;
    d_mmap_t *d_mmap;
#ifdef USING_BSD_DEVICE_STRATEGY
    d_strategy_t *d_strategy;
#endif /* USING_BSD_DEVICE_STRATEGY */

#ifdef USING_BSD_RAW_CDEVSW
    void *d_spare0;
    d_kqfilter_t *d_kqfilter;
    d_purge_t *d_purge;
    d_mmap_single_t *d_mmap_single;

    int32_t d_spare1[3];
    void *d_spare2[3];

    /* These fields should not be messed with by drivers */
    LIST_HEAD(, cdev) d_devs;
    int d_spare3;
    union
    {
        struct cdevsw *gianttrick;
        SLIST_ENTRY(cdevsw) postfree_list;
    } __d_giant;
#endif
};

struct iovec
{
    void *iov_base; /* Base address. */
    size_t iov_len; /* Length. */
};

enum uio_rw
{
    UIO_READ,
    UIO_WRITE
};

struct uio
{
    struct iovec *uio_iov; /* scatter/gather list */
    int uio_iovcnt;        /* length of scatter/gather list */
    off_t uio_offset;      /* offset in target object */
    ssize_t uio_resid;     /* remaining bytes to process */
#ifdef USING_BSD_UIO
    enum uio_seg uio_segflg; /* address space */
#endif
    enum uio_rw uio_rw; /* operation */
#ifdef USING_BSD_UIO
    struct rt_thread *uio_td; /* owner */

#endif /* USING_BSD_UIO */
};

#include <lwp_user_mm.h>
rt_inline int uiomove(void *operand, int n, struct uio *uio)
{
    switch (uio->uio_rw)
    {
        case UIO_READ:
            memcpy(uio->uio_iov->iov_base, operand, n);
            break;
        case UIO_WRITE:
            memcpy(operand, uio->uio_iov->iov_base, n);
            break;
        default:
            return -1;
    }

    uio->uio_iov->iov_base += n;
    uio->uio_iov->iov_len--;
    uio->uio_offset += n;
    uio->uio_resid -= n;
    return 0;
}

/* privileges checking: 0 if okay */
rt_inline int priv_check(struct rt_thread *td, int priv)
{
    return 0;
}

/* Disable console redirection to a tty. */
rt_inline int constty_clear(struct lwp_tty *tp)
{
    // rt_kprintf("\nTODO: %s unimplemented!\n", __func__);
    return 0;
}

rt_inline int constty_set(struct lwp_tty *tp)
{
    // rt_kprintf("\nTODO: %s unimplemented!\n", __func__);
    return 0;
}

/**
 * UMA (Universal Memory Allocator)
 */
#define UMA_ALIGN_PTR (sizeof(void *) - 1) /* Alignment fit for ptr */

typedef int (*uma_ctor)(void *mem, int size, void *arg, int flags);
typedef void (*uma_dtor)(void *mem, int size, void *arg);
typedef int (*uma_init)(void *mem, int size, int flags);
typedef void (*uma_fini)(void *mem, int size);

struct uma_zone
{
    char *name;
    int align;
    int size;
};

/* Opaque type used as a handle to the zone */
typedef struct uma_zone *uma_zone_t;

rt_inline uma_zone_t uma_zcreate(char *name, int size, uma_ctor ctor,
                                 uma_dtor dtor, uma_init zinit, uma_fini zfini,
                                 int align, uint16_t flags)
{
    uma_zone_t zone = rt_malloc(sizeof(struct uma_zone));
    if (zone)
    {
        RT_ASSERT(ctor == RT_NULL);
        RT_ASSERT(dtor == RT_NULL);
        RT_ASSERT(zinit == RT_NULL);
        RT_ASSERT(zfini == RT_NULL);

        zone->size = size;
        zone->name = name;
        zone->align = align;
    }
    return zone;
}

rt_inline void *uma_zalloc(uma_zone_t zone, int flags)
{
    void *buf = rt_malloc_align(zone->size, zone->align + 1);
    if (buf)
        rt_memset(buf, 0, sizeof(zone->size));
    return buf;
}

rt_inline void uma_zfree(uma_zone_t zone, void *item)
{
    rt_free_align(item);
}

/**
 * bsd type of speed to linux type.
 * Note: with switch blocks, compiler can generate the optimized version for us
 */
#include <termios.h>
rt_inline long bsd_speed_to_integer(speed_t speed)
{
    long speed_value;
    switch (speed)
    {
        case B0:
            speed_value = 0;
            break;
        case B50:
            speed_value = 50;
            break;
        case B75:
            speed_value = 75;
            break;
        case B110:
            speed_value = 110;
            break;
        case B134:
            speed_value = 134;
            break;
        case B150:
            speed_value = 150;
            break;
        case B200:
            speed_value = 200;
            break;
        case B300:
            speed_value = 300;
            break;
        case B600:
            speed_value = 600;
            break;
        case B1200:
            speed_value = 1200;
            break;
        case B1800:
            speed_value = 1800;
            break;
        case B2400:
            speed_value = 2400;
            break;
        case B4800:
            speed_value = 4800;
            break;
        case B9600:
            speed_value = 9600;
            break;
        case B19200:
            speed_value = 19200;
            break;
        case B38400:
            speed_value = 38400;
            break;
        case B57600:
            speed_value = 57600;
            break;
        case B115200:
            speed_value = 115200;
            break;
        case B230400:
            speed_value = 230400;
            break;
        case B460800:
            speed_value = 460800;
            break;
        case B500000:
            speed_value = 500000;
            break;
        case B576000:
            speed_value = 576000;
            break;
        case B921600:
            speed_value = 921600;
            break;
        case B1000000:
            speed_value = 1000000;
            break;
        case B1152000:
            speed_value = 1152000;
            break;
        case B1500000:
            speed_value = 1500000;
            break;
        case B2000000:
            speed_value = 2000000;
            break;
        case B2500000:
            speed_value = 2500000;
            break;
        case B3000000:
            speed_value = 3000000;
            break;
        case B3500000:
            speed_value = 3500000;
            break;
        case B4000000:
            speed_value = 4000000;
            break;
        default:
            speed_value = -1; // invalid speed
            break;
    }
    return speed_value;
}

/* time.h */

/* Operations on timevals. */

#define timevalclear(tvp) ((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define timevalisset(tvp) ((tvp)->tv_sec || (tvp)->tv_usec)
#define timevalcmp(tvp, uvp, cmp)                                          \
    (((tvp)->tv_sec == (uvp)->tv_sec) ? ((tvp)->tv_usec cmp(uvp)->tv_usec) \
                                      : ((tvp)->tv_sec cmp(uvp)->tv_sec))

rt_inline void getmicrotime(struct timeval *now)
{
    gettimeofday(now, RT_NULL);
}

rt_inline void timevalfix(struct timeval *tv)
{
    if (tv->tv_usec < 0)
    {
        tv->tv_sec--;
        tv->tv_usec += 1000000;
    }
    if (tv->tv_usec >= 1000000)
    {
        tv->tv_sec++;
        tv->tv_usec -= 1000000;
    }
}

rt_inline void timevaladd(struct timeval *op1, const struct timeval *op2)
{
    op1->tv_sec += op2->tv_sec;
    op1->tv_usec += op2->tv_usec;
    timevalfix(op1);
}

rt_inline void timevalsub(struct timeval *op1, const struct timeval *op2)
{
    op1->tv_sec -= op2->tv_sec;
    op1->tv_usec -= op2->tv_usec;
    timevalfix(op1);
}

rt_inline rt_tick_t tvtohz(struct timeval *tv)
{
    rt_tick_t rc;
    rc = tv->tv_sec * RT_TICK_PER_SECOND;
    rc += tv->tv_usec * RT_TICK_PER_SECOND / MICROSECOND_PER_SECOND;
    return rc;
}

/* ioctl */
#define _BSD_TIOCTL(val) ((val) << 16)
enum bsd_ioctl_cmd
{
    BSD_TIOCDRAIN = 1,
    BSD_TIOCFLUSH,
    BSD_TIOCSTART,
    BSD_TIOCSTOP,
    BSD_TIOCSTAT,
    BSD_TIOCGDRAINWAIT,
    BSD_TIOCSDRAINWAIT,
    BSD_TIOCSDTR,
    BSD_TIOCCDTR,
};

#ifndef TIOCGETA /* get termios struct */
#define TIOCGETA TCGETS
#endif
#ifndef TIOCSETA /* set termios struct */
#define TIOCSETA TCSETS
#endif
#ifndef TIOCSETAW /* drain output, set */
#define TIOCSETAW TCSETSW
#endif
#ifndef TIOCSETAF /* drn out, fls in, set */
#define TIOCSETAF TCSETSF
#endif
#ifndef TIOCDRAIN /* wait till output drained */
#define TIOCDRAIN _BSD_TIOCTL(BSD_TIOCDRAIN)
#endif
#ifndef TIOCFLUSH /* flush buffers */
#define TIOCFLUSH _BSD_TIOCTL(BSD_TIOCFLUSH)
#endif
#ifndef TIOCSTART /* start output, like ^Q */
#define TIOCSTART _BSD_TIOCTL(BSD_TIOCSTART)
#endif
#ifndef TIOCSTOP /* stop output, like ^S */
#define TIOCSTOP _BSD_TIOCTL(BSD_TIOCSTOP)
#endif
#ifndef TIOCSTAT /* simulate ^T status message */
#define TIOCSTAT _BSD_TIOCTL(BSD_TIOCSTAT)
#endif
#ifndef TIOCGDRAINWAIT /* get ttywait timeout */
#define TIOCGDRAINWAIT _BSD_TIOCTL(BSD_TIOCGDRAINWAIT)
#endif
#ifndef TIOCSDRAINWAIT /* set ttywait timeout */
#define TIOCSDRAINWAIT _BSD_TIOCTL(BSD_TIOCSDRAINWAIT)
#endif
#ifndef TIOCSDTR /* set data terminal ready */
#define TIOCSDTR _BSD_TIOCTL(BSD_TIOCSDTR)
#endif
#ifndef TIOCCDTR /* clear data terminal ready */
#define TIOCCDTR _BSD_TIOCTL(BSD_TIOCCDTR)
#endif

#define ENOIOCTL ENOSYS
#define NO_PID   -1

/* line discipline */
#define TTYDISC      0 /* termios tty line discipline */
#define SLIPDISC     4 /* serial IP discipline */
#define PPPDISC      5 /* PPP discipline */
#define NETGRAPHDISC 6 /* Netgraph tty node discipline */
#define H4DISC       7 /* Netgraph Bluetooth H4 discipline */

/*
 * Control flags - hardware control of terminal
 */
#if __BSD_VISIBLE
#define CIGNORE    0x00000001 /* ignore control flags */
#define CCTS_OFLOW 0x00010000 /* CTS flow control of output */
#define CRTSCTS    (CCTS_OFLOW | CRTS_IFLOW)
#define CRTS_IFLOW 0x00020000 /* RTS flow control of input */
#define CDTR_IFLOW 0x00040000 /* DTR flow control of input */
#define CDSR_OFLOW 0x00080000 /* DSR flow control of output */
#define CCAR_OFLOW 0x00100000 /* DCD flow control of output */
#define CNO_RTSDTR 0x00200000 /* Do not assert RTS or DTR automatically */
#else
#define CIGNORE    0 /* ignore control flags */
#define CCTS_OFLOW 0 /* CTS flow control of output */
#define CRTS_IFLOW 0 /* RTS flow control of input */
#define CDTR_IFLOW 0 /* DTR flow control of input */
#define CDSR_OFLOW 0 /* DSR flow control of output */
#define CCAR_OFLOW 0 /* DCD flow control of output */
#define CNO_RTSDTR 0 /* Do not assert RTS or DTR automatically */
#endif

#ifndef CRTSCTS
#define CRTSCTS (CCTS_OFLOW | CRTS_IFLOW)
#endif

#ifndef howmany
#define howmany(x, y) (((x) + ((y)-1)) / (y))
#endif

struct ucred
{
};
#define NOCRED ((struct ucred *)0)  /* no credential available */
#define FSCRED ((struct ucred *)-1) /* filesystem credential */

/* convert from open() flags to/from fflags; convert O_RD/WR to FREAD/FWRITE */
#include <fcntl.h>
#define FFLAGS(oflags) ((oflags)&O_EXEC ? (oflags) : (oflags) + 1)
#define OFLAGS(fflags) \
    (((fflags) & (O_EXEC | O_PATH)) != 0 ? (fflags) : (fflags)-1)

typedef int fo_rdwr_t(struct lwp_tty *tp, struct uio *uio,
                      struct ucred *active_cred, int flags,
                      struct rt_thread *td);
typedef int fo_truncate_t(struct lwp_tty *tp, off_t length,
                          struct ucred *active_cred, struct rt_thread *td);
typedef int fo_ioctl_t(struct lwp_tty *tp, rt_ubase_t com, void *data,
                       struct ucred *active_cred, int fflags, struct rt_thread *td);
typedef int fo_poll_t(struct lwp_tty *tp, struct rt_pollreq *rq, struct ucred *active_cred,
                      struct rt_thread *td);
typedef int fo_stat_t(struct lwp_tty *tp, struct stat *sb,
                      struct ucred *active_cred);
typedef int fo_close_t(struct lwp_tty *tp, struct rt_thread *td);

#ifdef USING_BSD_FO_EXT
typedef int fo_chmod_t(struct file *fp, mode_t mode, struct ucred *active_cred,
                       struct rt_thread *td);
typedef int fo_chown_t(struct file *fp, uid_t uid, gid_t gid,
                       struct ucred *active_cred, struct rt_thread *td);
typedef int fo_sendfile_t(struct file *fp, int sockfd, struct uio *hdr_uio,
                          struct uio *trl_uio, off_t offset, size_t nbytes,
                          off_t *sent, int flags, struct rt_thread *td);
typedef int fo_seek_t(struct file *fp, off_t offset, int whence,
                      struct rt_thread *td);

typedef int fo_kqfilter_t(struct file *fp, struct knote *kn);
typedef int fo_fill_kinfo_t(struct file *fp, struct kinfo_file *kif,
                            struct filedesc *fdp);
typedef int fo_mmap_t(struct file *fp, vm_map_t map, vm_offset_t *addr,
                      vm_size_t size, vm_prot_t prot, vm_prot_t cap_maxprot,
                      int flags, vm_ooffset_t foff, struct rt_thread *td);
typedef int fo_aio_queue_t(struct file *fp, struct kaiocb *job);

typedef int fo_add_seals_t(struct file *fp, int flags);
typedef int fo_get_seals_t(struct file *fp, int *flags);
typedef int fo_fallocate_t(struct file *fp, off_t offset, off_t len,
                           struct rt_thread *td);
typedef int fo_fspacectl_t(struct file *fp, int cmd, off_t *offset,
                           off_t *length, int flags, struct ucred *active_cred,
                           struct rt_thread *td);
typedef int fo_spare_t(struct file *fp);
#endif /* USING_BSD_FO_EXT */

typedef int fo_flags_t;

struct bsd_fileops
{
    fo_rdwr_t *fo_read;
    fo_rdwr_t *fo_write;
    fo_truncate_t *fo_truncate;
    fo_ioctl_t *fo_ioctl;
    fo_poll_t *fo_poll;
    fo_stat_t *fo_stat;
    fo_close_t *fo_close;
#ifdef USING_BSD_FO_EXT
    fo_chmod_t *fo_chmod;
    fo_chown_t *fo_chown;
    fo_sendfile_t *fo_sendfile;
    fo_seek_t *fo_seek;
    fo_kqfilter_t *fo_kqfilter;
    fo_fill_kinfo_t *fo_fill_kinfo;
    fo_mmap_t *fo_mmap;
    fo_aio_queue_t *fo_aio_queue;
    fo_add_seals_t *fo_add_seals;
    fo_get_seals_t *fo_get_seals;
    fo_fallocate_t *fo_fallocate;
    fo_fspacectl_t *fo_fspacectl;
    fo_spare_t *fo_spares[8]; /* Spare slots */
#endif
    fo_flags_t fo_flags; /* DFLAG_* below */
};

#define DFLAG_PASSABLE	0x01	/* may be passed via unix sockets. */
#define DFLAG_SEEKABLE	0x02	/* seekable / nonsequential */

#endif /* __LWP_TTY_BSD_PORTING_H__ */
