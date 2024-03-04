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

    /* we don't check refcnt because each open will create a new device */
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
                file->vnode->fops = &ptm_fops;
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
            rc = bsd_ptsdev_methods.fo_close(tp, rt_thread_self());
        }
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

    if (file->vnode && file->vnode->data)
    {
        device = (rt_device_t)file->vnode->data;
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

    if (file->vnode && file->vnode->data)
    {
        device = (rt_device_t)file->vnode->data;
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

static int ptm_fops_ioctl(struct dfs_file *file, int cmd, void *arg)
{
    int rc;
    lwp_tty_t tp;
    rt_device_t device;
    rt_ubase_t cmd_normal = (unsigned int)cmd;

    if (file->vnode && file->vnode->data)
    {
        device = (rt_device_t)file->vnode->data;
        tp = rt_container_of(device, struct lwp_tty, parent);

        switch (cmd_normal)
        {
            case TIOCSPTLCK:
            {
                int is_lock;
                if (lwp_get_from_user(&is_lock, arg, sizeof(int)) != sizeof(int))
                    return -EFAULT;
                pts_set_lock(tp, is_lock);
                rc = 0;
            }
            break;
            case TIOCGPTLCK:
            {
                int is_lock = pts_is_locked(tp);
                if (lwp_put_to_user(arg, &is_lock, sizeof(int)) != sizeof(int))
                    return -EFAULT;
                rc = 0;
            }
            break;
            case TIOCGPKT:
            {
                int pktmode = pts_get_pktmode(tp);
                if (lwp_put_to_user(arg, &pktmode, sizeof(int)) != sizeof(int))
                    return -EFAULT;
                rc = 0;
            }
            break;
            default:
                rc = bsd_ptsdev_methods.fo_ioctl(
                    tp, cmd_normal, arg, 0, FFLAGS(file->flags), rt_thread_self());
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

    if (file->vnode && file->vnode->data)
    {
        device = (rt_device_t)file->vnode->data;
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
        sprintf(device_name, "%s%s", root_path, dev_rel_path);
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
    strncpy(buf, "pts/ptmx", len);

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
