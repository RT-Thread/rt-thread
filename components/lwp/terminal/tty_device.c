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

#define TTY_CONF_INCLUDE_CCHARS
#include "tty_config.h"
#include "tty_internal.h"
#include "terminal.h"

/* configure option: timeout of tty drain wait */
static int tty_drainwait = 5 * 60;

#define TTY_NAME_PREFIX "tty"
static char *alloc_device_name(const char *name)
{
    char *tty_dev_name;
    long name_buf_len = (sizeof(TTY_NAME_PREFIX) - 1) /* raw prefix */
                        + rt_strlen(name)             /* custom name */
                        + 1;                          /* tailing \0 */

    tty_dev_name = rt_malloc(name_buf_len);
    if (tty_dev_name)
        sprintf(tty_dev_name, "%s%s", TTY_NAME_PREFIX, name);
    return tty_dev_name;
}

/* character device for tty */
#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops tty_dev_ops = {
    /* IO directly through device is not allowed */
};
#else
#error Must enable RT_USING_DEVICE_OPS in Kconfig
#endif

static int tty_fops_open(struct dfs_file *file)
{
    int rc;
    lwp_tty_t tp;
    rt_device_t device;
    int devtype = 0; /* unused */

    if (file->vnode && file->vnode->data)
    {
        if (file->vnode->ref_count != 1)
        {
            rc = 0;
        }
        else
        {
            device = (rt_device_t)file->vnode->data;
            tp = rt_container_of(device, struct lwp_tty, parent);
            rc = bsd_ttydev_methods.d_open(tp, file->flags, devtype,
                                           rt_thread_self());
        }
    }
    else
    {
        rc = -EINVAL;
    }

    return rc;
}

static int tty_fops_close(struct dfs_file *file)
{
    int rc;
    lwp_tty_t tp;
    rt_device_t device;
    int fflags = FFLAGS(file->flags);
    int devtype = 0; /* unused */

    if (file->vnode && file->vnode->data)
    {
        if (file->vnode->ref_count != 1)
        {
            rc = 0;
        }
        else
        {
            device = (rt_device_t)file->vnode->data;
            tp = rt_container_of(device, struct lwp_tty, parent);
            rc = bsd_ttydev_methods.d_close(tp, fflags, devtype, rt_thread_self());
        }
    }
    else
    {
        rc = -EINVAL;
    }

    return rc;
}

static int tty_fops_ioctl(struct dfs_file *file, int cmd, void *arg)
{
    int rc;
    lwp_tty_t tp;
    rt_device_t device;

    if (file->vnode && file->vnode->data)
    {
        device = (rt_device_t)file->vnode->data;
        tp = rt_container_of(device, struct lwp_tty, parent);
        rc = lwp_tty_ioctl_adapter(tp, cmd, file->flags, arg, rt_thread_self());
    }
    else
    {
        rc = -EINVAL;
    }

    return rc;
}

static ssize_t tty_fops_read(struct dfs_file *file, void *buf, size_t count,
                             off_t *pos)
{
    ssize_t rc = 0;
    int error;
    struct uio uio;
    struct iovec iov;
    rt_device_t device;
    struct lwp_tty *tp;
    int ioflags;
    int oflags = file->flags;

    if (file->vnode && file->vnode->data)
    {
        device = (rt_device_t)file->vnode->data;
        tp = rt_container_of(device, struct lwp_tty, parent);

        /* setup ioflags */
        ioflags = 0;
        if (oflags & O_NONBLOCK)
            ioflags |= IO_NDELAY;

        /* setup uio parameters */
        iov.iov_base = (void *)buf;
        iov.iov_len = count;
        uio.uio_offset = file->fpos;
        uio.uio_resid = count;
        uio.uio_iov = &iov;
        uio.uio_iovcnt = 1;
        uio.uio_rw = UIO_READ;

        rc = count;
        error = bsd_ttydev_methods.d_read(tp, &uio, ioflags);
        rc -= uio.uio_resid;
        if (error)
        {
            LOG_D("%s: failed to write %d bytes of data. error code %d",
                  __func__, uio.uio_resid, error);
            rc = error;
        }

        /* reset file context */
        file->fpos = uio.uio_offset;
    }

    if (rc)
        LOG_D("%s(len=%d, buf=%c \"%d\")", __func__, rc, *((char *)buf),
              *((char *)buf));
    return rc;
}

static ssize_t tty_fops_write(struct dfs_file *file, const void *buf,
                              size_t count, off_t *pos)
{
    ssize_t rc = 0;
    int error;
    struct uio uio;
    struct iovec iov;
    rt_device_t device;
    struct lwp_tty *tp;
    int ioflags;
    int oflags = file->flags;

    if (file->vnode && file->vnode->data)
    {
        device = (rt_device_t)file->vnode->data;
        tp = rt_container_of(device, struct lwp_tty, parent);

        /* setup ioflags */
        ioflags = 0;
        if (oflags & O_NONBLOCK)
            ioflags |= IO_NDELAY;

        /* setup uio parameters */
        iov.iov_base = (void *)buf;
        iov.iov_len = count;
        uio.uio_offset = file->fpos;
        uio.uio_resid = count;
        uio.uio_iov = &iov;
        uio.uio_iovcnt = 1;
        uio.uio_rw = UIO_WRITE;

        rc = count;
        error = bsd_ttydev_methods.d_write(tp, &uio, ioflags);
        if (error)
        {
            rc = error;
            LOG_D("%s: failed to write %d bytes of data. error code %d",
                  __func__, uio.uio_resid, error);
        }
        else
        {
            rc -= uio.uio_resid;
        }

        /* reset file context */
        file->fpos = uio.uio_offset;
    }
    return rc;
}

static int tty_fops_flush(struct dfs_file *file)
{
    return -EINVAL;
}

static off_t tty_fops_lseek(struct dfs_file *file, off_t offset, int wherece)
{
    return -EINVAL;
}

static int tty_fops_truncate(struct dfs_file *file, off_t offset)
{
    /**
     * regarding to POSIX.1, TRUNC is not supported for tty device.
     * return 0 always to make filesystem happy
     */
    return 0;
}

static int tty_fops_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    int rc;
    rt_device_t device;
    struct lwp_tty *tp;

    if (file->vnode && file->vnode->data)
    {
        device = (rt_device_t)file->vnode->data;
        tp = rt_container_of(device, struct lwp_tty, parent);

        rc = bsd_ttydev_methods.d_poll(tp, req, rt_thread_self());
    }
    else
    {
        rc = -1;
    }

    return rc;
}

static int tty_fops_mmap(struct dfs_file *file, struct lwp_avl_struct *mmap)
{
    return -EINVAL;
}

static int tty_fops_lock(struct dfs_file *file, struct file_lock *flock)
{
    return -EINVAL;
}

static int tty_fops_flock(struct dfs_file *file, int operation, struct file_lock *flock)
{
    return -EINVAL;
}

static struct dfs_file_ops tty_file_ops = {
    .open = tty_fops_open,
    .close = tty_fops_close,
    .ioctl = tty_fops_ioctl,
    .read = tty_fops_read,
    .write = tty_fops_write,
    .flush = tty_fops_flush,
    .lseek = tty_fops_lseek,
    .truncate = tty_fops_truncate,
    .poll = tty_fops_poll,
    .mmap = tty_fops_mmap,
    .lock = tty_fops_lock,
    .flock = tty_fops_flock,
};

rt_inline void device_setup(lwp_tty_t terminal)
{
    terminal->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    terminal->parent.ops = &tty_dev_ops;
#else
#error Must enable RT_USING_DEVICE_OPS in Kconfig
#endif
}

/* register TTY device */
rt_err_t lwp_tty_register(lwp_tty_t terminal, const char *name)
{
    rt_err_t rc = -RT_ENOMEM;
    const char *tty_name;
    char *alloc_name;

    if (terminal->t_devsw->tsw_flags & TF_NOPREFIX)
    {
        alloc_name = RT_NULL;
        tty_name = name;
    }
    else
    {
        alloc_name = alloc_device_name(name);
        tty_name = alloc_name;
    }

    if (tty_name)
    {
        device_setup(terminal);
        rc = rt_device_register(&terminal->parent, tty_name, 0);
        if (rc == RT_EOK)
        {
            terminal->parent.fops = &tty_file_ops;

            LOG_D("%s() /dev/%s device registered", __func__, tty_name);
        }

        rt_free(alloc_name);
    }
    return rc;
}

static void tty_init_termios(lwp_tty_t tp)
{
    struct termios *t = &tp->t_termios_init_in;

    t->c_cflag = TTYDEF_CFLAG;
    t->c_iflag = TTYDEF_IFLAG;
    t->c_lflag = TTYDEF_LFLAG;
    t->c_oflag = TTYDEF_OFLAG;
    t->__c_ispeed = TTYDEF_SPEED;
    t->__c_ospeed = TTYDEF_SPEED;

    memcpy(&t->c_cc, tty_ctrl_charset,
           sizeof(tty_ctrl_charset) / sizeof(tty_ctrl_charset[0]));

#ifdef USING_BSD_INIT_LOCK_DEVICE
    tp->t_termios_init_out = *t;
#endif /* USING_BSD_INIT_LOCK_DEVICE */
}

lwp_tty_t lwp_tty_create_ext(lwp_ttydevsw_t handle, void *softc,
                             rt_mutex_t custom_mtx)
{
    lwp_tty_t tp;

    tp = rt_calloc(1, sizeof(struct lwp_tty)
    #ifdef USING_BSD_SIGINFO
            + LWP_TTY_PRBUF_SIZE
    #endif
            );

    if (!tp)
        return tp;

    bsd_devsw_init(handle);

#ifdef USING_BSD_SIGINFO
    tp->t_prbufsz = LWP_TTY_PRBUF_SIZE;
#endif
    tp->t_devsw = handle;
    tp->t_devswsoftc = softc;
    tp->t_flags = handle->tsw_flags;
    tp->t_drainwait = tty_drainwait;

    tty_init_termios(tp);

    cv_init(&tp->t_inwait, "ttyin");
    cv_init(&tp->t_outwait, "ttyout");
    cv_init(&tp->t_outserwait, "ttyosr");
    cv_init(&tp->t_bgwait, "ttybg");
    cv_init(&tp->t_dcdwait, "ttydcd");

    rt_wqueue_init(&tp->t_inpoll);
    rt_wqueue_init(&tp->t_outpoll);

    /* Allow drivers to use a custom mutex to lock the TTY. */
    if (custom_mtx != NULL)
    {
        tp->t_mtx = custom_mtx;
    }
    else
    {
        tp->t_mtx = &tp->t_mtxobj;
        rt_mutex_init(&tp->t_mtxobj, "ttydev", RT_IPC_FLAG_PRIO);
    }

#ifdef USING_BSD_POLL
    knlist_init_mtx(&tp->t_inpoll.si_note, tp->t_mtx);
    knlist_init_mtx(&tp->t_outpoll.si_note, tp->t_mtx);
#endif

    return tp;
}

lwp_tty_t lwp_tty_create(lwp_ttydevsw_t handle, void *softc)
{
    return lwp_tty_create_ext(handle, softc, NULL);
}

void lwp_tty_delete(lwp_tty_t tp)
{
    /*
     * ttyydev_leave() usually frees the i/o queues earlier, but it is
     * not always called between queue allocation and here.  The queues
     * may be allocated by ioctls on a pty control device without the
     * corresponding pty slave device ever being open, or after it is
     * closed.
     */
    ttyinq_free(&tp->t_inq);
    ttyoutq_free(&tp->t_outq);
    rt_wqueue_wakeup_all(&tp->t_inpoll, (void *)POLLHUP);
    rt_wqueue_wakeup_all(&tp->t_outpoll, (void *)POLLHUP);

#ifdef USING_BSD_POLL
    knlist_destroy(&tp->t_inpoll.si_note);
    knlist_destroy(&tp->t_outpoll.si_note);
#endif

    cv_destroy(&tp->t_inwait);
    cv_destroy(&tp->t_outwait);
    cv_destroy(&tp->t_bgwait);
    cv_destroy(&tp->t_dcdwait);
    cv_destroy(&tp->t_outserwait);

    if (tp->t_mtx == &tp->t_mtxobj)
        rt_mutex_detach(&tp->t_mtxobj);
    ttydevsw_free(tp);
    rt_device_unregister(&tp->parent);
    rt_free(tp);
}

/*
 * Report on state of foreground process group.
 */
void tty_info(struct lwp_tty *tp)
{
    /* TODO */
    return;
}
