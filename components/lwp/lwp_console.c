/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-23     Jesven      first version
 */

#include <rthw.h>
#include <rtdevice.h>

#include "lwp_console.h"

#define DBG_TAG    "CONSOLE"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define CHAR_CTRL_D 0x4
#define CHAR_CTRL_C 0x3

enum
{
    CONSOLE_INIT_FLAG_NONE = 0,
    CONSOLE_INIT_FLAG_REGED,
    CONSOLE_INIT_FLAG_INITED,
};

static struct rt_console_device _console;

rt_inline struct rt_wqueue *wait_queue_get(struct rt_lwp * lwp)
{
    if (lwp == RT_PROCESS_KERNEL)
    {
        return &_console.wait_queue;
    }
    return &lwp->wait_queue;
}

rt_inline struct rt_wqueue *wait_queue_current_get(void)
{
    return wait_queue_get(_console.foreground);
}

static void console_wakeup_check(struct rt_console_device *console)
{
    rt_size_t len;
    struct rt_wqueue *wq;

    len = rt_ringbuffer_data_len(&console->input_rb);
    if (len)
    {
        wq = wait_queue_current_get();
        rt_wqueue_wakeup(wq, (void*)POLLIN);
    }
}

static void console_rx_notify(struct rt_device *dev)
{
    struct rt_console_device *console;
    rt_size_t len;
    rt_uint8_t ch;

    console = (struct rt_console_device *)dev;
    RT_ASSERT(console != RT_NULL);

    while (1)
    {
        len = rt_device_read(console->iodev, -1, &ch, 1);
        if (len == 0)
        {
            break;
        }
        if (ch == CHAR_CTRL_D) /* ctrl-d */
        {
            console->foreground = RT_PROCESS_KERNEL;
        }
        else if (ch == CHAR_CTRL_C) /* ctrl-c */
        {
            struct rt_lwp *lwp = console->foreground;

            if (lwp)
            {
                lwp_kill(lwp_to_pid(lwp), SIGINT);
            }
        }
        else
        {
            rt_ringbuffer_put_force(&console->input_rb, &ch, 1);
        }
    }
    console_wakeup_check(console);
}

void rt_console_set_foreground(struct rt_lwp *lwp)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    if (_console.init_flag != CONSOLE_INIT_FLAG_INITED)
    {
        goto exit;
    }
    _console.foreground = lwp;
    console_wakeup_check(&_console);

exit:
    rt_hw_interrupt_enable(level);
}

struct rt_lwp * rt_console_get_foreground(void)
{
    struct rt_lwp *lwp;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    lwp = _console.foreground;
    rt_hw_interrupt_enable(level);

    return lwp;
}

static void iodev_close(struct rt_console_device *console)
{
    struct rt_device_notify rx_notify;

    rx_notify.notify = RT_NULL;
    rx_notify.dev = RT_NULL;

    /* clear notify */
    rt_device_control(console->iodev, RT_DEVICE_CTRL_NOTIFY_SET, &rx_notify);
    rt_device_close(console->iodev);
}

static rt_err_t iodev_open(struct rt_console_device *console)
{
    rt_err_t ret;
    struct rt_device_notify rx_notify;
    rt_uint16_t oflags;

    rt_device_control(console->iodev, RT_DEVICE_CTRL_CONSOLE_OFLAG, &oflags);

    ret = rt_device_open(console->iodev, oflags);
    if (ret != RT_EOK)
    {
        return RT_ERROR;
    }

    rx_notify.notify = console_rx_notify;
    rx_notify.dev = (struct rt_device *)console;
    rt_device_control(console->iodev, RT_DEVICE_CTRL_NOTIFY_SET, &rx_notify);
    return RT_EOK;
}

struct rt_device *rt_console_get_iodev(void)
{
    rt_base_t level;
    struct rt_device *iodev;

    level = rt_hw_interrupt_disable();
    iodev = _console.iodev;
    rt_hw_interrupt_enable(level);
    return iodev;
}

struct rt_device *rt_console_set_iodev(struct rt_device *iodev)
{
    rt_base_t level;
    struct rt_device *io_before;
    struct rt_console_device *console;

    RT_ASSERT(iodev != RT_NULL);

    console = &_console;

    level = rt_hw_interrupt_disable();

    RT_ASSERT(console->init_flag >= CONSOLE_INIT_FLAG_REGED);

    io_before = console->iodev;

    if (iodev == io_before)
    {
        goto exit;
    }

    if (console->init_flag >= CONSOLE_INIT_FLAG_INITED)
    {
        /* close old device */
        iodev_close(console);
    }

    console->iodev = iodev;

    if (console->init_flag >= CONSOLE_INIT_FLAG_INITED)
    {
        rt_err_t ret;
        /* open new device */
        ret = iodev_open(console);
        RT_ASSERT(ret == RT_EOK);
    }

exit:
    rt_hw_interrupt_enable(level);
    return io_before;
}

#ifdef RT_USING_POSIX

/* fops for console */
static int console_fops_open(struct dfs_fd *fd)
{
    int ret;
    struct rt_device * device;

    device = (struct rt_device *)fd->data;
    RT_ASSERT(device != RT_NULL);

    ret = rt_device_open(device, fd->flags);
    return ret;
}

static int console_fops_close(struct dfs_fd *fd)
{
    int ret;
    struct rt_device * device;

    device = (struct rt_device *)fd->data;
    RT_ASSERT(device != RT_NULL);

    ret = rt_device_close(device);
    return ret;
}

static int console_fops_read(struct dfs_fd *fd, void *buf, size_t count)
{
    rt_base_t level;
    int size = 0;
    struct rt_console_device *console;
    struct rt_lwp *lwp;
    struct rt_wqueue *wq;
    int wait_ret;

    console = (struct rt_console_device *)fd->data;
    RT_ASSERT(console != RT_NULL);
    RT_ASSERT(console->init_flag == CONSOLE_INIT_FLAG_INITED);

    lwp = (struct rt_lwp *)(rt_thread_self()->lwp);

    wq = wait_queue_get(lwp);

    level = rt_hw_interrupt_disable();
    while (count)
    {
        size = rt_device_read((struct rt_device *)console, -1, buf, count);
        if (size > 0)
        {
            break;
        }
        if (fd->flags & O_NONBLOCK)
        {
            break;
        }
        wait_ret = rt_wqueue_wait_interruptible(wq, 0, RT_WAITING_FOREVER);
        if (wait_ret != 0)
        {
            break;
        }
    }
    rt_hw_interrupt_enable(level);
    if (size < 0)
    {
        size = 0;
    }
    return size;
}

static int console_fops_write(struct dfs_fd *fd, const void *buf, size_t count)
{
    int size;
    struct rt_device * device;

    device = (struct rt_device *)fd->data;
    RT_ASSERT(device != RT_NULL);
    size = rt_device_write(device, -1, buf, count);
    return size;
}

static int console_fops_poll(struct dfs_fd *fd, struct rt_pollreq *req)
{
    rt_base_t level;
    int mask = POLLOUT;
    struct rt_device * device;
    struct rt_console_device *console;
    struct rt_wqueue *wq;
    struct rt_lwp *lwp;

    device = (struct rt_device *)fd->data;
    RT_ASSERT(device != RT_NULL);

    console = (struct rt_console_device *)device;
    RT_ASSERT(console->init_flag == CONSOLE_INIT_FLAG_INITED);

    lwp = (struct rt_lwp *)(rt_thread_self()->lwp);
    wq = wait_queue_get(lwp);
    rt_poll_add(wq, req);

    level = rt_hw_interrupt_disable();
    if (lwp == console->foreground)
    {
        rt_size_t len;

        len = rt_ringbuffer_data_len(&console->input_rb);
        if (len)
        {
            mask |= POLLIN;
        }
    }
    rt_hw_interrupt_enable(level);

    return mask;
}

const static struct dfs_file_ops _console_fops =
{
    console_fops_open,
    console_fops_close,
    RT_NULL,
    console_fops_read,
    console_fops_write,
    RT_NULL, /* flush */
    RT_NULL, /* lseek */
    RT_NULL, /* getdents */
    console_fops_poll,
};

#endif

/* RT-Thread Device Interface */
/*
 * This function initializes console device.
 */
static rt_err_t rt_console_init(struct rt_device *dev)
{
    rt_base_t level;
    rt_err_t result;
    struct rt_console_device *console;

    RT_ASSERT(dev != RT_NULL);

    console = (struct rt_console_device *)dev;

    level = rt_hw_interrupt_disable();

    RT_ASSERT(console->init_flag == CONSOLE_INIT_FLAG_REGED);

    result = iodev_open(console);
    if (result != RT_EOK)
    {
        goto exit;
    }

    console->init_flag = CONSOLE_INIT_FLAG_INITED;
exit:
    rt_hw_interrupt_enable(level);
    return result;
}

static rt_err_t rt_console_open(struct rt_device *dev, rt_uint16_t oflag)
{
    rt_err_t result = RT_EOK;
    struct rt_console_device *console;

    RT_ASSERT(dev != RT_NULL);
    console = (struct rt_console_device *)dev;
    RT_ASSERT(console != RT_NULL);
    RT_ASSERT(console->init_flag == CONSOLE_INIT_FLAG_INITED);
    return result;
}

static rt_err_t rt_console_close(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_console_device *console;

    console = (struct rt_console_device *)dev;
    RT_ASSERT(console != RT_NULL);
    RT_ASSERT(console->init_flag == CONSOLE_INIT_FLAG_INITED);
    return result;
}

static rt_size_t rt_console_read(struct rt_device *dev,
        rt_off_t          pos,
        void             *buffer,
        rt_size_t         size)
{
    rt_base_t level;
    rt_size_t len = 0;
    struct rt_lwp *lwp;
    struct rt_console_device *console;

    console = (struct rt_console_device *)dev;
    RT_ASSERT(console != RT_NULL);
    RT_ASSERT(console->init_flag == CONSOLE_INIT_FLAG_INITED);

    level = rt_hw_interrupt_disable();
    if (size)
    {
        lwp = lwp_self();
        if (lwp == console->foreground)
        {
            len = rt_ringbuffer_data_len(&console->input_rb);
            if (len > size)
            {
                len = size;
            }
            if (len)
            {
                len = rt_ringbuffer_get(&console->input_rb, buffer, len);
            }
        }
    }
    rt_hw_interrupt_enable(level);

    return len;
}

static rt_size_t rt_console_write(struct rt_device *dev,
        rt_off_t          pos,
        const void       *buffer,
        rt_size_t         size)
{
    rt_base_t level;
    rt_size_t len = 0;
    struct rt_console_device *console;

    console = (struct rt_console_device *)dev;
    RT_ASSERT(console != RT_NULL);
    RT_ASSERT(console->init_flag == CONSOLE_INIT_FLAG_INITED);

    level = rt_hw_interrupt_disable();
    len = rt_device_write((struct rt_device *)console->iodev, -1, buffer, size);
    rt_hw_interrupt_enable(level);

    return len;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops console_ops =
{
    rt_console_init,
    rt_console_open,
    rt_console_close,
    rt_console_read,
    rt_console_write,
    RT_NULL,
};
#endif

/*
 * console register
 */
rt_err_t rt_console_register(const char *name, struct rt_device *iodev)
{
    rt_base_t level;
    rt_err_t ret;
    struct rt_device *device;
    struct rt_console_device *console = &_console;

    level = rt_hw_interrupt_disable();
    RT_ASSERT(console->init_flag == CONSOLE_INIT_FLAG_NONE);
    RT_ASSERT(iodev != RT_NULL);

    device = &(console->parent);

    device->type        = RT_Device_Class_Char;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &console_ops;
#else
    device->init        = rt_console_init;
    device->open        = rt_console_open;
    device->close       = rt_console_close;
    device->read        = rt_console_read;
    device->write       = rt_console_write;
    device->control     = RT_NULL;
#endif

    /* register a character device */
    ret = rt_device_register(device, name, 0);
    if (ret != RT_EOK)
    {
        goto exit;
    }

#ifdef RT_USING_POSIX
    /* set fops */
    device->fops = &_console_fops;
#endif

    console->iodev = iodev;
    console->foreground = RT_PROCESS_KERNEL;
    rt_wqueue_init(&(console->wait_queue));

    RT_ASSERT(LWP_CONSOLE_INPUT_BUFFER_SIZE > 0);
    rt_ringbuffer_init(&console->input_rb, console->input_buf, LWP_CONSOLE_INPUT_BUFFER_SIZE);

    console->init_flag = CONSOLE_INIT_FLAG_REGED;
exit:
    rt_hw_interrupt_enable(level);
    return ret;
}
