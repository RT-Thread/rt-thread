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
#include <dfs_file.h>
#include <dfs_fs.h>
#include <tty.h>

#define DBG_TAG               "CONSOLE"
#ifdef RT_TTY_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_TTY_DEBUG */
#include <rtdbg.h>

#include <ipc/waitqueue.h>
#include <ipc/ringbuffer.h>

static struct tty_struct console_dev;
static struct rt_ringbuffer console_rx_ringbuffer;
static struct rt_wqueue console_rx_wqueue;
static rt_thread_t console_rx_thread;
static const size_t rb_bufsz = 0x1000;

static void console_rx_work(void *parameter)
{
    int len;
    char ch;
    int lens;
    static char buf[0x1000];

    struct tty_struct *console;
    console = &console_dev;

    while (1)
    {
        rt_wqueue_wait(&console_rx_wqueue, 0, RT_WAITING_FOREVER);
        lens = 0;

        while (lens < sizeof(buf))
        {
            len = rt_ringbuffer_get(&console_rx_ringbuffer, (void *)&ch, sizeof(ch));
            if (len == 0)
            {
                break;
            }
            lens += len;
            buf[lens-1] = ch;
        }

        if (lens && console->ldisc->ops->receive_buf)
        {
            console->ldisc->ops->receive_buf((struct tty_struct *)console, buf, lens);
        }
    }
}

static int rx_thread_init(void)
{
    void *rb_buffer;
    rt_thread_t thread;

    rb_buffer = rt_malloc(rb_bufsz);
    rt_ringbuffer_init(&console_rx_ringbuffer, rb_buffer, rb_bufsz);
    rt_wqueue_init(&console_rx_wqueue);

    thread = rt_thread_create("console_rx", console_rx_work, &console_dev, rb_bufsz, 10, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
        console_rx_thread = thread;
    }

    return 0;
}
INIT_COMPONENT_EXPORT(rx_thread_init);

static void console_rx_notify(struct rt_device *dev)
{
    struct tty_struct *console = NULL;
    int len = 0;
    int lens = 0;
    char ch = 0;

    console = (struct tty_struct *)dev;
    RT_ASSERT(console != RT_NULL);

    while (1)
    {
        len = rt_device_read(console->io_dev, -1, &ch, 1);
        if (len == 0)
        {
            break;
        }
        lens += len;
        rt_ringbuffer_put(&console_rx_ringbuffer, (void *)&ch, sizeof(ch));
        if (lens > rb_bufsz)
        {
            break;
        }
    }
    if (console_rx_thread)
        rt_wqueue_wakeup(&console_rx_wqueue, 0);
}

struct tty_struct *console_tty_get(void)
{
    return &console_dev;
}

static void iodev_close(struct tty_struct *console)
{
    struct rt_device_notify rx_notify;

    rx_notify.notify = RT_NULL;
    rx_notify.dev = RT_NULL;

    /* clear notify */
    rt_device_control(console->io_dev, RT_DEVICE_CTRL_NOTIFY_SET, &rx_notify);
    rt_device_close(console->io_dev);
}

static rt_err_t iodev_open(struct tty_struct *console)
{
    rt_err_t ret = RT_EOK;
    struct rt_device_notify rx_notify;
    rt_uint16_t oflags = 0;

    rt_device_control(console->io_dev, RT_DEVICE_CTRL_CONSOLE_OFLAG, &oflags);

    ret = rt_device_open(console->io_dev, oflags);
    if (ret != RT_EOK)
    {
        return -RT_ERROR;
    }

    rx_notify.notify = console_rx_notify;
    rx_notify.dev = (struct rt_device *)console;
    rt_device_control(console->io_dev, RT_DEVICE_CTRL_NOTIFY_SET, &rx_notify);
    return RT_EOK;
}

struct rt_device *console_get_iodev(void)
{
    return console_dev.io_dev;
}

struct rt_device *console_set_iodev(struct rt_device *iodev)
{
    rt_base_t level = 0;
    struct rt_device *io_before = RT_NULL;
    struct tty_struct *console = RT_NULL;

    RT_ASSERT(iodev != RT_NULL);

    console = &console_dev;

    level = rt_spin_lock_irqsave(&console->spinlock);

    RT_ASSERT(console->init_flag >= TTY_INIT_FLAG_REGED);

    io_before = console->io_dev;
    if (iodev == io_before)
    {
        goto exit;
    }

    if (console->init_flag >= TTY_INIT_FLAG_INITED)
    {
        /* close old device */
        iodev_close(console);
    }

    console->io_dev = iodev;
    if (console->init_flag >= TTY_INIT_FLAG_INITED)
    {
        rt_err_t ret;
        /* open new device */
        ret = iodev_open(console);
        RT_ASSERT(ret == RT_EOK);
    }

exit:
    rt_spin_unlock_irqrestore(&console->spinlock, level);
    return io_before;
}

/* RT-Thread Device Interface */
/*
 * This function initializes console device.
 */
static rt_err_t rt_console_init(struct rt_device *dev)
{
    rt_base_t level = 0;
    rt_err_t result = RT_EOK;
    struct tty_struct *console = RT_NULL;

    RT_ASSERT(dev != RT_NULL);

    console = (struct tty_struct *)dev;

    level = rt_spin_lock_irqsave(&console->spinlock);

    RT_ASSERT(console->init_flag == TTY_INIT_FLAG_REGED);

    result = iodev_open(console);
    if (result != RT_EOK)
    {
        goto exit;
    }

    console->init_flag = TTY_INIT_FLAG_INITED;
exit:
    rt_spin_unlock_irqrestore(&console->spinlock, level);
    return result;
}

static rt_err_t rt_console_open(struct rt_device *dev, rt_uint16_t oflag)
{
    rt_err_t result = RT_EOK;
    struct tty_struct *console = RT_NULL;

    RT_ASSERT(dev != RT_NULL);
    console = (struct tty_struct *)dev;
    RT_ASSERT(console != RT_NULL);
    RT_ASSERT(console->init_flag == TTY_INIT_FLAG_INITED);
    return result;
}

static rt_err_t rt_console_close(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct tty_struct *console = RT_NULL;

    console = (struct tty_struct *)dev;
    RT_ASSERT(console != RT_NULL);
    RT_ASSERT(console->init_flag == TTY_INIT_FLAG_INITED);
    return result;
}

static rt_ssize_t rt_console_read(struct rt_device *dev,
        rt_off_t          pos,
        void             *buffer,
        rt_size_t         size)
{
    rt_size_t len = 0;
    return len;
}

static rt_ssize_t rt_console_write(struct rt_device *dev,
        rt_off_t          pos,
        const void       *buffer,
        rt_size_t         size)
{
    rt_size_t len = 0;
    struct tty_struct *console = RT_NULL;

    console = (struct tty_struct *)dev;
    RT_ASSERT(console != RT_NULL);
    RT_ASSERT(console->init_flag == TTY_INIT_FLAG_INITED);

    len = rt_device_write((struct rt_device *)console->io_dev, -1, buffer, size);

    return len;
}

static rt_err_t  rt_console_control(rt_device_t dev, int cmd, void *args)
{
    rt_size_t len = 0;
    struct tty_struct *console = RT_NULL;

    console = (struct tty_struct *)dev;
    RT_ASSERT(console != RT_NULL);
    RT_ASSERT(console->init_flag == TTY_INIT_FLAG_INITED);

    len = rt_device_control((struct rt_device *)console->io_dev, cmd, args);

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
    rt_console_control,
};
#endif

/*
 * console register
 */
static struct dfs_file_ops con_fops;
rt_err_t console_register(const char *name, struct rt_device *iodev)
{
    rt_err_t ret = RT_EOK;
    struct rt_device *device = RT_NULL;
    struct tty_struct *console = &console_dev;

    RT_ASSERT(iodev != RT_NULL);
    RT_ASSERT(console->init_flag == TTY_INIT_FLAG_NONE);

    tty_init(console, TTY_DRIVER_TYPE_CONSOLE, SERIAL_TYPE_NORMAL, iodev);
    console_ldata_init(console);

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
    device->control     = rt_console_control;
#endif

    /* register a character device */
    ret = rt_device_register(device, name, 0);
    if (ret != RT_EOK)
    {
        LOG_E("console driver register fail\n");
    }
    else
    {
#ifdef RT_USING_POSIX_DEVIO
        /* set fops */
        memcpy(&con_fops, tty_get_fops(), sizeof(struct dfs_file_ops));
        device->fops = &con_fops;
#endif
    }

    return ret;
}
