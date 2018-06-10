/*
 * File      : log_file.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 *                Bernard      the first version
 * 2013-06-26     Grissiom     refactor
 */
#include <rtthread.h>
#include <log_trace.h>

#ifdef RT_USING_DFS

#include <dfs_posix.h>

struct file_device
{
    struct rt_device parent;

    int  fd;
    char *filename;
};

/* file device for log trace */
static struct file_device _file_device;

/* common device interface */
static rt_err_t fdevice_open(rt_device_t dev, rt_uint16_t oflag)
{
    int fd;
    struct file_device *fdev = (struct file_device *)dev;

    if (fdev->fd >= 0)
        return -RT_EBUSY;

    /* test and open */
    fd = open(fdev->filename, O_RDONLY, 0);
    if (fd >= 0)
    {
        close(fd);
        fd = open(fdev->filename, O_WRONLY | O_APPEND, 0);
    }
    else
    {
        /* file not exists */
        fd = open(fdev->filename, O_WRONLY | O_CREAT, 0);
    }
    fdev->fd = fd;

    return RT_EOK;
}

static rt_err_t fdevice_close(rt_device_t dev)
{
    rt_err_t result;
    struct file_device *fdev = (struct file_device *)dev;

    if (fdev->fd < 0)
        return -RT_EBUSY;

    result = close(fdev->fd);
    if (result == 0)
    {
        fdev->fd = -1;
    }

    return result;
}

static rt_size_t fdevice_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct file_device *fdev = (struct file_device *)dev;

    if (fdev->fd < 0)
        return 0;

    return write(fdev->fd, buffer, size);
}

static rt_err_t fdevice_control(rt_device_t dev, int cmd, void *arg)
{
    struct file_device *fdev = (struct file_device *)dev;

    if (fdev->fd < 0)
        return 0;

    switch (cmd)
    {
    case LOG_TRACE_CTRL_FLUSH:
        if (fsync(fdev->fd) != 0)
            return RT_ERROR;
        break;
    default:
        break;
    }
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops log_trace_ops = 
{
    RT_NULL,
    fdevice_open,
    fdevice_close,
    RT_NULL,
    fdevice_write,
    fdevice_control
};
#endif

void log_trace_file_init(const char *filename)
{
    rt_device_t device;

    device = rt_device_find("logfile");
    if (device == RT_NULL)
    {
        rt_memset(&_file_device, 0x00, sizeof(_file_device));

        _file_device.parent.type  = RT_Device_Class_Char;

#ifdef RT_USING_DEVICE_OPS
        _file_device.parent.ops     = &log_trace_ops;
#else
        _file_device.parent.init    = RT_NULL;
        _file_device.parent.open    = fdevice_open;
        _file_device.parent.close   = fdevice_close;
        _file_device.parent.write   = fdevice_write;
        _file_device.parent.control = fdevice_control;
#endif

        rt_device_register(&_file_device.parent, "logfile", O_RDWR);
    }

    _file_device.filename = rt_strdup(filename);
    _file_device.fd = -1;
}

void log_trace_set_file(const char *filename)
{
    log_trace_file_init(filename);
    log_trace_set_device("logfile");
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(log_trace_set_file, log_file, set output filename of log trace);
#endif

#endif /* RT_USING_DFS */
