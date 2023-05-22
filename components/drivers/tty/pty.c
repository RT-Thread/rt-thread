/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021.12.07     linzhenxing      first version
 */
#include <rtthread.h>
#include <tty.h>
#include <tty_ldisc.h>

#define DBG_TAG               "PTY"
#ifdef RT_TTY_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_TTY_DEBUG */
#include <rtdbg.h>

#define PTY_PTS_SIZE 10
static struct tty_struct ptm_dev;
static struct tty_struct pts_devs[PTY_PTS_SIZE];
static int pts_index = 0;

static int pts_register(struct tty_struct *ptmx, struct tty_struct *pts, int pts_index);

/* check free pts device */
static struct tty_struct *find_freepts(void)
{
    for(int i = 0; i < PTY_PTS_SIZE; i++)
    {
        if (pts_devs[i].init_flag == TTY_INIT_FLAG_NONE)
        {
            pts_devs[i].init_flag = TTY_INIT_FLAG_ALLOCED;
            return &pts_devs[i];
        }
    }
    return RT_NULL;
}

/* Set the lock flag on a pty */
static int pty_set_lock(struct tty_struct *tty, int *arg)
{
    int val = *arg;

    if (val)
    {
        tty->pts_lock = val;
    }
    else
    {
        tty->pts_lock = val;
    }
    return 0;
}

static int pty_get_lock(struct tty_struct *tty, int *arg)
{
    *arg = tty->pts_lock;
    return 0;
}

static int pty_get_index(struct tty_struct *tty, int *arg)
{
    *arg = tty->index;
    return 0;
}
/* RT-Thread Device Interface */
/*
 * This function initializes console device.
 */
static rt_err_t pty_device_init(struct rt_device *dev)
{
    rt_ubase_t level = 0;
    rt_err_t result = RT_EOK;
    struct tty_struct *tty = RT_NULL;

    RT_ASSERT(dev != RT_NULL);
    tty = (struct tty_struct *)dev;

    level = rt_hw_interrupt_disable();
    RT_ASSERT(tty->init_flag == TTY_INIT_FLAG_REGED);
    tty->init_flag = TTY_INIT_FLAG_INITED;
    rt_hw_interrupt_enable(level);

    return result;
}

static rt_err_t pty_device_open(struct rt_device *dev, rt_uint16_t oflag)
{
    rt_err_t result = RT_EOK;
    return result;
}

static rt_err_t pty_device_close(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct tty_struct *tty = (struct tty_struct*)dev;
    //struct tty_struct *to = RT_NULL;

    if (tty->subtype == PTY_TYPE_MASTER)
    {
        // to = tty->other_struct;
        // to->init_flag = TTY_INIT_FLAG_NONE;
        // to->other_struct = RT_NULL;
        // to->foreground = RT_NULL;
        // to->index = -1;
        // tty_ldisc_kill(to);
        // tty->other_struct = RT_NULL;
    }
    else
    {
        // to = tty->other_struct;
        // to->other_struct = RT_NULL;
        // tty->init_flag = TTY_INIT_FLAG_NONE;
        // tty->other_struct = RT_NULL;
        // tty->foreground = RT_NULL;
        // tty->index = -1;
        // tty->other_struct = RT_NULL;
        // tty_ldisc_kill(tty);
    }

    return result;
}

static rt_ssize_t pty_device_read(struct rt_device *dev,
        rt_off_t          pos,
        void             *buffer,
        rt_size_t         size)
{
    rt_size_t len = 0;

    return len;
}

static rt_ssize_t pty_device_write(struct rt_device *dev,
        rt_off_t          pos,
        const void       *buffer,
        rt_size_t         size)
{
    rt_size_t len = 0;
    rt_base_t level = 0;
    struct tty_struct *tty = RT_NULL;
    struct tty_struct *to = RT_NULL;

    tty = (struct tty_struct *)dev;
    RT_ASSERT(tty != RT_NULL);
    RT_ASSERT(tty->init_flag == TTY_INIT_FLAG_INITED);
    to = tty->other_struct;

    level = rt_hw_interrupt_disable();
    if (to->ldisc->ops->receive_buf)
    {
        len = to->ldisc->ops->receive_buf(to, (char *)buffer, size);
    }
    rt_hw_interrupt_enable(level);

    return len;
}

static rt_err_t  pty_device_control(rt_device_t dev, int cmd, void *args)
{
    struct tty_struct *tty = (struct tty_struct *)dev;

    switch (cmd)
    {
    case TIOCSPTLCK: /* Set PT Lock (disallow slave open) */
        return pty_set_lock(tty, (int *)args);
    case TIOCGPTLCK: /* Get PT Lock status */
        return pty_get_lock(tty, (int *)args);
    case TIOCGPTN: /* Get PT Number */
        return pty_get_index(tty, (int *)args);
    }

    return -ENOIOCTLCMD;
}

static int ptmx_open(struct dfs_file *fd)
{
    int ret = 0;
    struct tty_struct *tty = RT_NULL;
    struct tty_struct *pts = RT_NULL;
    struct tty_ldisc *ld = RT_NULL;
    struct rt_lwp *lwp = RT_NULL;
    struct rt_wqueue *wq = RT_NULL;

    tty = (struct tty_struct *)fd->vnode->data;
    RT_ASSERT(tty != RT_NULL);

    pts = find_freepts();
    if (pts == RT_NULL)
    {
        LOG_E("No free PTS device found.\n");
        return -1;
    }
    ret = pts_register(tty, pts, pts_index);
    if (ret < 0)
    {
        LOG_E("pts register fail\n");
        rt_free(pts);
        return -1;
    }
    pts_index++;
    lwp = lwp_self();
    wq = wait_queue_get(lwp, tty);
    pts->wait_queue = *wq;
    tty->other_struct = pts;

    ld = tty->ldisc;
    if (ld->ops->open)
    {
        ret = ld->ops->open(fd);
    }

    rt_device_t device = (rt_device_t)fd->vnode->data;
    if(fd->vnode->ref_count == 1)
    {
        ret = rt_device_open(device, fd->flags);
    }

    return ret;
}
#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops pty_device_ops =
{
    pty_device_init,
    pty_device_open,
    pty_device_close,
    pty_device_read,
    pty_device_write,
    pty_device_control,
};
#endif /* RT_USING_DEVICE_OPS */

static struct dfs_file_ops pts_fops;
static struct dfs_file_ops ptmx_fops;
static int pts_register(struct tty_struct *ptmx, struct tty_struct *pts, int pts_index)
{
    char name[20];
    rt_err_t ret = RT_EOK;
    struct rt_device *device = RT_NULL;

    RT_ASSERT(ptmx!=RT_NULL);

    if (pts->init_flag != TTY_INIT_FLAG_ALLOCED)
    {
        LOG_E("pts%d has been registered\n", pts_index);
        ret = (-RT_EBUSY);
    }
    else
    {
        tty_init(pts, TTY_DRIVER_TYPE_PTY, PTY_TYPE_SLAVE, NULL);
        pts->index = pts_index;
        pts->pts_lock = 1;
        pts->other_struct = ptmx;

        device = &pts->parent;
        device->type    = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
        device->ops     = &pty_device_ops;
#else
        device->init    = pty_device_init;
        device->open    = pty_device_open;
        device->close   = pty_device_close;
        device->read    = pty_device_read;
        device->write   = pty_device_write;
        device->control = pty_device_control;
#endif /* RT_USING_DEVICE_OPS */

        rt_snprintf(name, sizeof(name), "pts%d", pts_index);
        ret = rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);
        if (ret != RT_EOK)
        {
            LOG_E("pts%d register failed\n", pts_index);
            ret = -RT_EIO;
        }
        else
        {
#ifdef RT_USING_POSIX_DEVIO
            /* set fops */
            memcpy(&pts_fops, tty_get_fops(), sizeof(struct dfs_file_ops));
            device->fops = &pts_fops;
#endif
        }
    }

    return ret;
}

static int ptmx_register(void)
{
    rt_err_t ret = RT_EOK;
    struct rt_device *device = RT_NULL;
    struct tty_struct *ptmx = &ptm_dev;

    RT_ASSERT(ptmx->init_flag == TTY_INIT_FLAG_NONE);

    tty_init(ptmx, TTY_DRIVER_TYPE_PTY, PTY_TYPE_MASTER, NULL);

    device = &(ptmx->parent);
    device->type = RT_Device_Class_Char;

#ifdef RT_USING_DEVICE_OPS
    device->ops     = &pty_device_ops;
#else
    device->init    = pty_device_init;
    device->open    = pty_device_open;
    device->close   = pty_device_close;
    device->read    = pty_device_read;
    device->write   = pty_device_write;
    device->control = pty_device_control;
#endif /* RT_USING_DEVICE_OPS */

    ret = rt_device_register(device, "ptmx", RT_DEVICE_FLAG_RDWR);
    if (ret != RT_EOK)
    {
        LOG_E("ptmx register fail\n");
        ret = -RT_EIO;
    }
    else
    {
#ifdef RT_USING_POSIX_DEVIO
        /* set fops */
        memcpy(&ptmx_fops, tty_get_fops(), sizeof(struct dfs_file_ops));
        ptmx_fops.open = ptmx_open;
        device->fops = &ptmx_fops;
#endif
    }

    return ret;
}
INIT_DEVICE_EXPORT(ptmx_register);
