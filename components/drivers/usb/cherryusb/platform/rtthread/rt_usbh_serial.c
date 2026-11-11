/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "usbh_core.h"
#include "usbh_serial.h"

static rt_err_t rt_usbh_serial_open(struct rt_device *dev, rt_uint16_t oflag)
{
    struct usbh_serial *serial;

    RT_ASSERT(dev != RT_NULL && dev->user_data != RT_NULL);

    serial = (struct usbh_serial *)dev->user_data;

    serial = usbh_serial_open(serial->hport->config.intf[serial->intf].devname, USBH_SERIAL_O_RDWR | USBH_SERIAL_O_NONBLOCK);
    if (serial == RT_NULL) {
        USB_LOG_ERR("serial open failed\n");
        return -RT_ERROR;
    }

    struct usbh_serial_termios termios;

    memset(&termios, 0, sizeof(termios));
    termios.baudrate = 115200;
    termios.stopbits = 0;
    termios.parity = 0;
    termios.databits = 8;
    termios.rtscts = false;
    termios.rx_timeout = 0;

    usbh_serial_control(serial, USBH_SERIAL_CMD_SET_ATTR, &termios);

    return RT_EOK;
}

static rt_err_t rt_usbh_serial_close(struct rt_device *dev)
{
    struct usbh_serial *serial;

    RT_ASSERT(dev != RT_NULL && dev->user_data != RT_NULL);

    serial = (struct usbh_serial *)dev->user_data;

    usbh_serial_close(serial);

    return RT_EOK;
}

static rt_ssize_t rt_usbh_serial_read(struct rt_device *dev,
                                      rt_off_t pos,
                                      void *buffer,
                                      rt_size_t size)
{
    struct usbh_serial *serial;

    RT_ASSERT(dev != RT_NULL && dev->user_data != RT_NULL);

    serial = (struct usbh_serial *)dev->user_data;

    return usbh_serial_read(serial, buffer, size);
}

static rt_ssize_t rt_usbh_serial_write(struct rt_device *dev,
                                       rt_off_t pos,
                                       const void *buffer,
                                       rt_size_t size)
{
    struct usbh_serial *serial;
    int ret = 0;
    rt_uint8_t *align_buf;

    RT_ASSERT(dev != RT_NULL && dev->user_data != RT_NULL);

    serial = (struct usbh_serial *)dev->user_data;

    align_buf = (rt_uint8_t *)buffer;

    if ((uint32_t)buffer & (CONFIG_USB_ALIGN_SIZE - 1)) {
        align_buf = rt_malloc_align(USB_ALIGN_UP(size, CONFIG_USB_ALIGN_SIZE), CONFIG_USB_ALIGN_SIZE);
        if (!align_buf) {
            USB_LOG_ERR("serial get align buf failed\n");
            return 0;
        }

        usb_memcpy(align_buf, buffer, size);
    }

    ret = usbh_serial_write(serial, align_buf, size);

    if ((uint32_t)buffer & (CONFIG_USB_ALIGN_SIZE - 1)) {
        rt_free_align(align_buf);
    }

    return ret;
}

static rt_err_t rt_usbh_serial_control(struct rt_device *dev,
                                       int cmd,
                                       void *args)
{
    struct usbh_serial *serial;
    struct serial_configure *config;
    int ret = -RT_EINVAL;

    RT_ASSERT(dev != RT_NULL && dev->user_data != RT_NULL);

    serial = (struct usbh_serial *)dev->user_data;

    switch (cmd) {
        case RT_DEVICE_CTRL_CONFIG: {
            config = (struct serial_configure *)args;

            struct usbh_serial_termios termios;

            memset(&termios, 0, sizeof(termios));
            termios.baudrate = config->baud_rate;
            termios.stopbits = 0;
            termios.parity = config->parity;
            termios.databits = config->data_bits;
            termios.rtscts = false;
            termios.rx_timeout = 0;

            usbh_serial_control(serial, USBH_SERIAL_CMD_SET_ATTR, &termios);
        } break;

        default:
            break;
    }

    return ret;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops usbh_serial_ops = {
    NULL,
    rt_usbh_serial_open,
    rt_usbh_serial_close,
    rt_usbh_serial_read,
    rt_usbh_serial_write,
    rt_usbh_serial_control
};
#endif

static void rt_usbh_serial_rx_complete_callback(struct usbh_serial *serial, int nbytes)
{
    struct rt_device *device;
    RT_ASSERT(serial != RT_NULL && serial->user_data != RT_NULL);

    device = (struct rt_device *)serial->user_data;

    if (device->rx_indicate) {
        device->rx_indicate(device, nbytes);
    }
}

rt_err_t usbh_serial_register(struct usbh_serial *serial)
{
    rt_err_t ret;
    struct rt_device *device;
    RT_ASSERT(serial != RT_NULL);

    device = rt_malloc(sizeof(struct rt_device));
    if (device == RT_NULL) {
        USB_LOG_ERR("serial device malloc failed\n");
        return -RT_ENOMEM;
    }
    memset(device, 0, sizeof(struct rt_device));

    device->type = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops = &usbh_serial_ops;
#else
    device->init = NULL;
    device->open = rt_usbh_serial_open;
    device->close = rt_usbh_serial_close;
    device->read = rt_usbh_serial_read;
    device->write = rt_usbh_serial_write;
    device->control = rt_usbh_serial_control;
#endif
    device->user_data = serial;
    serial->user_data = device;
    serial->rx_complete_callback = rt_usbh_serial_rx_complete_callback;

    /* skip /dev/ to avoid BAD file */
    const char *dev_name = serial->hport->config.intf[serial->intf].devname;
    if (strncmp(dev_name, "/dev/", 5) == 0) {
        dev_name += 5;
    }

    /* register a character device */
    ret = rt_device_register(device, dev_name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_REMOVABLE);

#ifdef RT_USING_POSIX_DEVIO
    /* set fops */
    device->fops = &usbh_serial_fops;
#endif
    return ret;
}

void usbh_serial_unregister(struct usbh_serial *serial)
{
    struct rt_device *device;

    RT_ASSERT(serial != NULL && serial->user_data != NULL);

    device = (struct rt_device *)serial->user_data;

    rt_device_unregister(device);
    rt_free(device);
}

void usbh_serial_run(struct usbh_serial *serial)
{
    usbh_serial_register(serial);
}

void usbh_serial_stop(struct usbh_serial *serial)
{
    usbh_serial_unregister(serial);
}