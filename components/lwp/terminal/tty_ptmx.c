/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-07     Shell        init ver.
 */

#define DBG_TAG "lwp.tty"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "tty_config.h"
#include "tty_internal.h"
#include "bsd_porting.h"
#include "terminal.h"

#include <fcntl.h>

static struct dfs_file_ops ptm_fops;

static int ptm_fops_open(struct dfs_file *file)
{
    int rc;
    rt_uint32_t oflags = file->flags;
    rt_thread_t cur_thr = rt_thread_self();

    if (file->vnode && file->vnode->data)
    {
        /**
         * Filter out illegal flags
         */
        if ((oflags & ~(O_RDWR | O_NOCTTY | O_CLOEXEC | O_LARGEFILE)) == 0)
        {
            rc = pts_alloc(FFLAGS(oflags & O_ACCMODE), cur_thr, file);

            /* detached operation from devfs */
            if (rc == 0)
            {
                file->vnode->fops = &ptm_fops;
            }
        }
        else
        {
            rc = -EINVAL;
        }
    }
    else
    {
        rc = -EINVAL;
    }

    return rc;
}

static int ptm_fops_close(struct dfs_file *file)
{
    int rc;
    lwp_tty_t tp;
    rt_device_t device;

    if (file->data)
    {
        device = (rt_device_t)file->data;
        tp = rt_container_of(device, struct lwp_tty, parent);
        rc = bsd_ptsdev_methods.fo_close(tp, rt_thread_self());
    }
    else
    {
        rc = -EINVAL;
    }

    return rc;
}

static ssize_t ptm_fops_read(struct dfs_file *file, void *buf, size_t count,
                             off_t *pos)
{
    ssize_t rc = 0;
    int error;
    struct uio uio;
    struct iovec iov;
    rt_device_t device;
    struct lwp_tty *tp;
    int oflags = file->flags;

    if (file->data)
    {
        device = (rt_device_t)file->data;
        tp = rt_container_of(device, struct lwp_tty, parent);

        /* setup uio parameters */
        iov.iov_base = (void *)buf;
        iov.iov_len = count;
        uio.uio_offset = file->fpos;
        uio.uio_resid = count;
        uio.uio_iov = &iov;
        uio.uio_iovcnt = 1;
        uio.uio_rw = UIO_READ;

        rc = count;
        error =
            bsd_ptsdev_methods.fo_read(tp, &uio, 0, oflags, rt_thread_self());
        rc -= uio.uio_resid;
        if (error)
        {
            rc = error;
        }

        /* reset file context */
        file->fpos = uio.uio_offset;
    }

    return rc;
}

static ssize_t ptm_fops_write(struct dfs_file *file, const void *buf,
                              size_t count, off_t *pos)
{
    ssize_t rc = 0;
    int error;
    struct uio uio;
    struct iovec iov;
    rt_device_t device;
    struct lwp_tty *tp;
    int oflags = file->flags;

    if (file->data)
    {
        device = (rt_device_t)file->data;
        tp = rt_container_of(device, struct lwp_tty, parent);

        /* setup uio parameters */
        iov.iov_base = (void *)buf;
        iov.iov_len = count;
        uio.uio_offset = file->fpos;
        uio.uio_resid = count;
        uio.uio_iov = &iov;
        uio.uio_iovcnt = 1;
        uio.uio_rw = UIO_WRITE;

        rc = count;
        error =
            bsd_ptsdev_methods.fo_write(tp, &uio, 0, oflags, rt_thread_self());
        if (error)
        {
            rc = error;
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

enum lwp_ptmx_ioctl_arg_type lwp_ptmx_ioctl_arg_type(rt_ubase_t cmd)
{
    switch (cmd)
    {
    case TIOCSDTR:
    case TIOCCDTR:
    case TIOCNOTTY:
    case TIOCSCTTY:
    case TIOCDRAIN:
    case TIOCEXCL:
    case TIOCNXCL:
    case TIOCSTOP:
    case TIOCSTART:
    case TIOCSTAT:
    case TIOCSBRK:
    case TIOCCBRK:
        return LWP_PTMX_IOCTL_NONE;

    case TIOCPKT:
    case TIOCSIG:
    case FIONBIO:
    case TIOCSPGRP:
    case TIOCMSET:
    case TIOCMBIS:
    case TIOCMBIC:
    case FIOASYNC:
    case FIOSETOWN:
    case TIOCFLUSH:
    case TIOCSDRAINWAIT:
    case TIOCCONS:
    case TIOCSETD:
        return LWP_PTMX_IOCTL_INT_IN;

    case TIOCGPGRP:
    case TIOCGSID:
    case FIONREAD:
    case TIOCOUTQ:
    case FIONWRITE:
    case TIOCMGET:
    case FIOGETOWN:
    case TIOCGETD:
    case TIOCGDRAINWAIT:
        return LWP_PTMX_IOCTL_INT_OUT;

    case TIOCGPTN:
        return LWP_PTMX_IOCTL_UINT_OUT;

    case TIOCSTI:
        return LWP_PTMX_IOCTL_CHAR_IN;

    case TIOCSWINSZ:
        return LWP_PTMX_IOCTL_WINSIZE_IN;

    case TIOCGWINSZ:
        return LWP_PTMX_IOCTL_WINSIZE_OUT;

    case TCSETS:
    case TCSETSW:
    case TCSETSF:
        return LWP_PTMX_IOCTL_TERMIOS_IN;

    case TCGETS:
        return LWP_PTMX_IOCTL_TERMIOS_OUT;

    default:
        return LWP_PTMX_IOCTL_UNSUPPORTED;
    }
}

int lwp_ptmx_ioctl_forward(rt_ubase_t cmd, void *arg,
                           lwp_ptmx_copy_fn copy_from_user,
                           lwp_ptmx_copy_fn copy_to_user,
                           lwp_ptmx_ioctl_fn ioctl, void *context)
{
    int rc;
    rt_size_t arg_size = 0;
    rt_bool_t copy_out = RT_FALSE;
    void *kernel_arg = RT_NULL;
    enum lwp_ptmx_ioctl_arg_type arg_type;
    union
    {
        int int_value;
        unsigned int uint_value;
        char char_value;
        struct winsize winsize_value;
        struct termios termios_value;
    } value;

    arg_type = lwp_ptmx_ioctl_arg_type(cmd);
    switch (arg_type)
    {
    case LWP_PTMX_IOCTL_NONE:
        break;
    case LWP_PTMX_IOCTL_INT_IN:
        kernel_arg = &value.int_value;
        arg_size = sizeof(value.int_value);
        break;
    case LWP_PTMX_IOCTL_INT_OUT:
        kernel_arg = &value.int_value;
        arg_size = sizeof(value.int_value);
        copy_out = RT_TRUE;
        break;
    case LWP_PTMX_IOCTL_UINT_OUT:
        kernel_arg = &value.uint_value;
        arg_size = sizeof(value.uint_value);
        copy_out = RT_TRUE;
        break;
    case LWP_PTMX_IOCTL_CHAR_IN:
        kernel_arg = &value.char_value;
        arg_size = sizeof(value.char_value);
        break;
    case LWP_PTMX_IOCTL_WINSIZE_IN:
        kernel_arg = &value.winsize_value;
        arg_size = sizeof(value.winsize_value);
        break;
    case LWP_PTMX_IOCTL_WINSIZE_OUT:
        kernel_arg = &value.winsize_value;
        arg_size = sizeof(value.winsize_value);
        copy_out = RT_TRUE;
        break;
    case LWP_PTMX_IOCTL_TERMIOS_IN:
        kernel_arg = &value.termios_value;
        arg_size = sizeof(value.termios_value);
        break;
    case LWP_PTMX_IOCTL_TERMIOS_OUT:
        kernel_arg = &value.termios_value;
        arg_size = sizeof(value.termios_value);
        copy_out = RT_TRUE;
        break;
    default:
        return -ENOTTY;
    }

    if (arg_size && !copy_out &&
        copy_from_user(kernel_arg, arg, arg_size, context) != arg_size)
    {
        return -EFAULT;
    }

    rc = ioctl(cmd, kernel_arg, context);
    if (!rc && copy_out &&
        copy_to_user(arg, kernel_arg, arg_size, context) != arg_size)
    {
        rc = -EFAULT;
    }

    return rc;
}

struct ptm_ioctl_context
{
    struct dfs_file *file;
    lwp_tty_t tp;
};

static rt_size_t ptm_copy_from_user(void *dst, void *src, rt_size_t size,
                                    void *context)
{
    RT_UNUSED(context);
    return lwp_get_from_user(dst, src, size);
}

static rt_size_t ptm_copy_to_user(void *dst, void *src, rt_size_t size,
                                  void *context)
{
    RT_UNUSED(context);
    return lwp_put_to_user(dst, src, size);
}

static int ptm_ioctl_backend(rt_ubase_t cmd, void *arg, void *context)
{
    struct ptm_ioctl_context *ptm_context = context;

    return bsd_ptsdev_methods.fo_ioctl(
        ptm_context->tp, cmd, arg, 0, FFLAGS(ptm_context->file->flags),
        rt_thread_self());
}

static int ptm_ioctl_forward(struct dfs_file *file, lwp_tty_t tp,
                             rt_ubase_t cmd, void *arg)
{
    struct ptm_ioctl_context context = {
        .file = file,
        .tp = tp,
    };

    return lwp_ptmx_ioctl_forward(cmd, arg, ptm_copy_from_user,
                                  ptm_copy_to_user, ptm_ioctl_backend, &context);
}

static int ptm_fops_ioctl(struct dfs_file *file, int cmd, void *arg)
{
    int rc;
    lwp_tty_t tp;
    rt_device_t device;
    rt_ubase_t cmd_normal = (unsigned int)cmd;

    if (file->data)
    {
        device = (rt_device_t)file->data;
        tp = rt_container_of(device, struct lwp_tty, parent);

        switch (cmd_normal)
        {
        case TIOCSPTLCK:
        {
            int is_lock;
            if (lwp_get_from_user(&is_lock, arg, sizeof(int)) != sizeof(int))
            {
                return -EFAULT;
            }
            pts_set_lock(tp, is_lock);
            rc = 0;
        }
        break;
        case TIOCGPTLCK:
        {
            int is_lock = pts_is_locked(tp);
            if (lwp_put_to_user(arg, &is_lock, sizeof(int)) != sizeof(int))
            {
                return -EFAULT;
            }
            rc = 0;
        }
        break;
        case TIOCGPKT:
        {
            int pktmode = pts_get_pktmode(tp);
            if (lwp_put_to_user(arg, &pktmode, sizeof(int)) != sizeof(int))
            {
                return -EFAULT;
            }
            rc = 0;
        }
        break;
        default:
            rc = ptm_ioctl_forward(file, tp, cmd_normal, arg);
            break;
        }
    }
    else
    {
        rc = -EINVAL;
    }

    return rc;
}

static int ptm_fops_flush(struct dfs_file *file)
{
    return -EINVAL;
}

static off_t ptm_fops_lseek(struct dfs_file *file, off_t offset, int wherece)
{
    return -EINVAL;
}

static int ptm_fops_truncate(struct dfs_file *file, off_t offset)
{
    return -EINVAL;
}

static int ptm_fops_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    int rc;
    rt_device_t device;
    struct lwp_tty *tp;

    if (file->data)
    {
        device = (rt_device_t)file->data;
        tp = rt_container_of(device, struct lwp_tty, parent);

        rc = bsd_ptsdev_methods.fo_poll(tp, req, 0, rt_thread_self());
    }
    else
    {
        rc = -1;
    }

    return rc;
}

static int ptm_fops_mmap(struct dfs_file *file, struct lwp_avl_struct *mmap)
{
    return -EINVAL;
}

static int ptm_fops_lock(struct dfs_file *file, struct file_lock *flock)
{
    return -EINVAL;
}

static int ptm_fops_flock(struct dfs_file *file, int operation, struct file_lock *flock)
{
    return -EINVAL;
}

static struct dfs_file_ops ptm_fops = {
    .open = ptm_fops_open,
    .close = ptm_fops_close,
    .ioctl = ptm_fops_ioctl,
    .read = ptm_fops_read,
    .write = ptm_fops_write,
    .flush = ptm_fops_flush,
    .lseek = ptm_fops_lseek,
    .truncate = ptm_fops_truncate,
    .poll = ptm_fops_poll,
    .mmap = ptm_fops_mmap,
    .lock = ptm_fops_lock,
    .flock = ptm_fops_flock,
};

rt_err_t lwp_ptmx_init(rt_device_t ptmx_device, const char *root_path)
{
    char *device_name;
    int root_len;
    const char *dev_rel_path;
    rt_err_t rc;

    root_len = strlen(root_path);
    dev_rel_path = "/ptmx";
    device_name = rt_malloc(root_len + sizeof("/ptmx"));

    if (device_name)
    {
        /* Register device */
        snprintf(device_name, root_len + sizeof("/ptmx"), "%s%s", root_path, dev_rel_path);
        rt_device_register(ptmx_device, device_name, 0);

        /* Setup fops */
        ptmx_device->fops = &ptm_fops;

        rt_free(device_name);

        rc = RT_EOK;
    }
    else
    {
        rc = -RT_ENOMEM;
    }

    return rc;
}

/* system level ptmx */
static struct rt_device sysptmx;

static struct dfs_file_ops sysptmx_file_ops;

static rt_err_t sysptmx_readlink(struct rt_device *dev, char *buf, int len)
{
    int rc = 0;

    /* TODO: support multi-root ? */
    snprintf(buf, len, "pts/ptmx");

    return rc;
}

static int _sys_ptmx_init(void)
{
    rt_err_t rc;
    rt_device_t sysptmx_rtdev = &sysptmx;

    /* setup system level device */
    sysptmx_rtdev->type = RT_Device_Class_Char;
    sysptmx_rtdev->ops = RT_NULL;
    rc = rt_device_register(sysptmx_rtdev, "ptmx", RT_DEVICE_FLAG_DYNAMIC);
    if (rc == RT_EOK)
    {
        sysptmx_rtdev->readlink = &sysptmx_readlink;
        sysptmx_rtdev->fops = &sysptmx_file_ops;
    }
    return rc;
}
INIT_DEVICE_EXPORT(_sys_ptmx_init);
