/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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

static struct tty_struct console_driver;

static void console_rx_notify(struct rt_device *dev)
{
    struct tty_struct *console = NULL;
    int len = 0;
    int lens = 0;
    char ch = 0;
    char buf[1024] = {0};

    console = (struct tty_struct *)dev;
    RT_ASSERT(console != RT_NULL);

    while (1)
    {
        len = rt_device_read(console->driver, -1, &ch, 1);
        if (len == 0)
        {
            break;
        }
        lens += len;
        buf[lens-1] = ch;
        if (lens > 1024)
        {
            break;
        }
    }

    if (console->ldisc->ops->receive_buf)
    {
        console->ldisc->ops->receive_buf((struct tty_struct *)console, buf, lens);
    }
}

struct tty_struct *console_tty_get(void)
{
    return &console_driver;
}

static void iodev_close(struct tty_struct *console)
{
    struct rt_device_notify rx_notify;

    rx_notify.notify = RT_NULL;
    rx_notify.dev = RT_NULL;

    /* clear notify */
    rt_device_control(console->driver, RT_DEVICE_CTRL_NOTIFY_SET, &rx_notify);
    rt_device_close(console->driver);
}

static rt_err_t iodev_open(struct tty_struct *console)
{
    rt_err_t ret = RT_EOK;
    struct rt_device_notify rx_notify;
    rt_uint16_t oflags = 0;

    rt_device_control(console->driver, RT_DEVICE_CTRL_CONSOLE_OFLAG, &oflags);

    ret = rt_device_open(console->driver, oflags);
    if (ret != RT_EOK)
    {
        return RT_ERROR;
    }

    rx_notify.notify = console_rx_notify;
    rx_notify.dev = (struct rt_device *)console;
    rt_device_control(console->driver, RT_DEVICE_CTRL_NOTIFY_SET, &rx_notify);
    return RT_EOK;
}

struct rt_device *console_get_iodev(void)
{
    rt_base_t level = 0;
    struct rt_device *iodev = RT_NULL;

    level = rt_hw_interrupt_disable();
    iodev = console_driver.driver;
    rt_hw_interrupt_enable(level);
    return iodev;
}

struct rt_device *console_set_iodev(struct rt_device *iodev)
{
    rt_base_t level = 0;
    struct rt_device *io_before = RT_NULL;
    struct tty_struct *console = RT_NULL;

    RT_ASSERT(iodev != RT_NULL);

    console = &console_driver;

    level = rt_hw_interrupt_disable();

    RT_ASSERT(console->init_flag >= TTY_INIT_FLAG_REGED);

    io_before = console->driver;

    if (iodev == io_before)
    {
        goto exit;
    }

    if (console->init_flag >= TTY_INIT_FLAG_INITED)
    {
        /* close old device */
        iodev_close(console);
    }

    console->driver = iodev;

    if (console->init_flag >= TTY_INIT_FLAG_INITED)
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

    level = rt_hw_interrupt_disable();

    RT_ASSERT(console->init_flag == TTY_INIT_FLAG_REGED);

    result = iodev_open(console);
    if (result != RT_EOK)
    {
        goto exit;
    }

    console->init_flag = TTY_INIT_FLAG_INITED;
exit:
    rt_hw_interrupt_enable(level);
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

    len = rt_device_write((struct rt_device *)console->driver, -1, buffer, size);

    return len;
}

static rt_err_t  rt_console_control(rt_device_t dev, int cmd, void *args)
{
    rt_size_t len = 0;
    struct tty_struct *console = RT_NULL;

    console = (struct tty_struct *)dev;
    RT_ASSERT(console != RT_NULL);
    RT_ASSERT(console->init_flag == TTY_INIT_FLAG_INITED);

    len = rt_device_control((struct rt_device *)console->driver, cmd, args);

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
    rt_base_t level = 0;
    rt_err_t ret = RT_EOK;
    struct rt_device *device = RT_NULL;
    struct tty_struct *console = &console_driver;

    level = rt_hw_interrupt_disable();
    RT_ASSERT(console->init_flag == TTY_INIT_FLAG_NONE);
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
    device->control     = rt_console_control;
#endif


    /* register a character device */
    ret = rt_device_register(device, name, 0);
    if (ret != RT_EOK)
    {
        LOG_E("console driver register fail\n");
        goto exit;
    }

#ifdef RT_USING_POSIX_DEVIO
    /* set fops */
    console_set_fops(&con_fops);
    device->fops = &con_fops;
#endif
    console->type = TTY_DRIVER_TYPE_CONSOLE;
    console->subtype = SERIAL_TYPE_NORMAL;
    console->driver = iodev;
    console->head = rt_calloc(1, sizeof(struct tty_node));
    if (!console->head)
    {
        return -RT_ENOMEM;
    }
    tty_initstack(console->head);

    rt_mutex_init(&console->lock, "ttylock", RT_IPC_FLAG_PRIO);
    console->pgrp = -1;
    console->session = -1;
    console->foreground = RT_NULL;
    rt_wqueue_init(&console->wait_queue);

    tty_ldisc_init(console);

extern struct termios tty_std_termios;
    console->init_termios = tty_std_termios;
    console->init_termios.c_cflag =
        B9600 | CS8 | CREAD | HUPCL; /* is normally B9600 default... */
    console->init_termios.__c_ispeed = 9600;
    console->init_termios.__c_ospeed = 9600;

    console_ldata_init(console);
    console->init_flag = TTY_INIT_FLAG_REGED;
exit:
    rt_hw_interrupt_enable(level);
    return ret;
}
