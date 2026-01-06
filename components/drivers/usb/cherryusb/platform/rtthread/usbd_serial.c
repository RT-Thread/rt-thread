/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "usbd_core.h"
#include "usbd_cdc_acm.h"

#define DEV_FORMAT_CDC_ACM "usb-acm%d"

#ifndef CONFIG_USBDEV_MAX_CDC_ACM_CLASS
#define CONFIG_USBDEV_MAX_CDC_ACM_CLASS (4)
#endif

#ifndef CONFIG_USBDEV_SERIAL_RX_BUFSIZE
#define CONFIG_USBDEV_SERIAL_RX_BUFSIZE (2048)
#endif

struct usbd_serial {
    struct rt_device parent;
    uint8_t busid;
    uint8_t in_ep;
    uint8_t out_ep;
    struct usbd_interface intf_ctrl;
    struct usbd_interface intf_data;
    usb_osal_sem_t tx_done;
    uint8_t minor;
    char name[32];
    struct rt_ringbuffer rx_rb;
    rt_uint8_t rx_rb_buffer[CONFIG_USBDEV_SERIAL_RX_BUFSIZE];
};

static uint32_t g_devinuse = 0;

static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_usbd_serial_cdc_acm_rx_buf[CONFIG_USBDEV_MAX_CDC_ACM_CLASS][USB_ALIGN_UP(512, CONFIG_USB_ALIGN_SIZE)];

static struct usbd_serial g_usbd_serial_cdc_acm[CONFIG_USBDEV_MAX_CDC_ACM_CLASS];

static struct usbd_serial *usbd_serial_alloc(void)
{
    uint8_t devno;
    struct usbd_serial *serial;

    for (devno = 0; devno < CONFIG_USBDEV_MAX_CDC_ACM_CLASS; devno++) {
        if ((g_devinuse & (1U << devno)) == 0) {
            g_devinuse |= (1U << devno);

            serial = &g_usbd_serial_cdc_acm[devno];
            memset(serial, 0, sizeof(struct usbd_serial));
            serial->minor = devno;
            snprintf(serial->name, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT_CDC_ACM, serial->minor);
            return serial;
        }
    }
    return NULL;
}

static void usbd_serial_free(struct usbd_serial *serial)
{
    uint8_t devno = serial->minor;

    if (devno < 32) {
        g_devinuse &= ~(1U << devno);
    }
    memset(serial, 0, sizeof(struct usbd_serial));
}

static rt_err_t usbd_serial_open(struct rt_device *dev, rt_uint16_t oflag)
{
    struct usbd_serial *serial;

    RT_ASSERT(dev != RT_NULL);

    serial = (struct usbd_serial *)dev;

    if (!usb_device_is_configured(serial->busid)) {
        USB_LOG_ERR("USB device is not configured\n");
        return -RT_EPERM;
    }

    usbd_ep_start_read(serial->busid, serial->out_ep,
                       g_usbd_serial_cdc_acm_rx_buf[serial->minor],
                       usbd_get_ep_mps(serial->busid, serial->out_ep));
    return RT_EOK;
}

static rt_ssize_t usbd_serial_read(struct rt_device *dev,
                                   rt_off_t pos,
                                   void *buffer,
                                   rt_size_t size)
{
    struct usbd_serial *serial;

    RT_ASSERT(dev != RT_NULL);

    serial = (struct usbd_serial *)dev;

    if (!usb_device_is_configured(serial->busid)) {
        return -RT_EPERM;
    }

    return rt_ringbuffer_get(&serial->rx_rb, (rt_uint8_t *)buffer, size);
}

static rt_ssize_t usbd_serial_write(struct rt_device *dev,
                                    rt_off_t pos,
                                    const void *buffer,
                                    rt_size_t size)
{
    struct usbd_serial *serial;
    int ret = 0;
    rt_uint8_t *align_buf;

    RT_ASSERT(dev != RT_NULL);

    serial = (struct usbd_serial *)dev;

    if (!usb_device_is_configured(serial->busid)) {
        return -RT_EPERM;
    }
    align_buf = (rt_uint8_t *)buffer;

#ifdef CONFIG_USB_DCACHE_ENABLE
    if ((uint32_t)buffer & (CONFIG_USB_ALIGN_SIZE - 1)) {
        align_buf = rt_malloc_align(size, CONFIG_USB_ALIGN_SIZE);
        if (!align_buf) {
            USB_LOG_ERR("serial get align buf failed\n");
            return 0;
        }

        usb_memcpy(align_buf, buffer, size);
    }
#endif
    usb_osal_sem_reset(serial->tx_done);
    usbd_ep_start_write(serial->busid, serial->in_ep, align_buf, size);
    ret = usb_osal_sem_take(serial->tx_done, 3000);
    if (ret < 0) {
        USB_LOG_ERR("serial write timeout\n");
        ret = -RT_ETIMEOUT;
    } else {
        ret = size;
    }

#ifdef CONFIG_USB_DCACHE_ENABLE
    if ((uint32_t)buffer & (CONFIG_USB_ALIGN_SIZE - 1)) {
        rt_free_align(align_buf);
    }
#endif

    return ret;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops usbd_serial_ops = {
    NULL,
    usbd_serial_open,
    NULL,
    usbd_serial_read,
    usbd_serial_write,
    NULL
};
#endif

rt_err_t usbd_serial_register(struct usbd_serial *serial,
                              void *data)
{
    rt_err_t ret;
    struct rt_device *device;
    RT_ASSERT(serial != RT_NULL);

    device = &(serial->parent);

    device->type = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops = &usbd_serial_ops;
#else
    device->init = NULL;
    device->open = usbd_serial_open;
    device->close = NULL;
    device->read = usbd_serial_read;
    device->write = usbd_serial_write;
    device->control = NULL;
#endif
    device->user_data = data;

    /* register a character device */
    ret = rt_device_register(device, serial->name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_REMOVABLE);

#ifdef RT_USING_POSIX_DEVIO
    /* set fops */
    device->fops = NULL;
#endif
    rt_ringbuffer_init(&serial->rx_rb, serial->rx_rb_buffer, sizeof(serial->rx_rb_buffer));

    return ret;
}

void usbd_cdc_acm_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    struct usbd_serial *serial;

    for (uint8_t devno = 0; devno < CONFIG_USBDEV_MAX_CDC_ACM_CLASS; devno++) {
        serial = &g_usbd_serial_cdc_acm[devno];
        if (serial->out_ep == ep) {
            rt_ringbuffer_put(&serial->rx_rb, g_usbd_serial_cdc_acm_rx_buf[serial->minor], nbytes);
            usbd_ep_start_read(serial->busid, serial->out_ep,
                g_usbd_serial_cdc_acm_rx_buf[serial->minor],
                usbd_get_ep_mps(serial->busid, serial->out_ep));

            if (serial->parent.rx_indicate) {
                serial->parent.rx_indicate(&serial->parent, nbytes);
            }
            break;
        }
    }
}

void usbd_cdc_acm_bulk_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    struct usbd_serial *serial;

    if ((nbytes % usbd_get_ep_mps(busid, ep)) == 0 && nbytes) {
        /* send zlp */
        usbd_ep_start_write(busid, ep, NULL, 0);
    } else {
        for (uint8_t devno = 0; devno < CONFIG_USBDEV_MAX_CDC_ACM_CLASS; devno++) {
            serial = &g_usbd_serial_cdc_acm[devno];
            if ((serial->in_ep == ep) && serial->tx_done) {
                usb_osal_sem_give(serial->tx_done);
                break;
            }
        }
    }
}

void usbd_cdc_acm_serial_init(uint8_t busid, uint8_t in_ep, uint8_t out_ep)
{
    struct usbd_serial *serial;

    struct usbd_endpoint cdc_out_ep = {
        .ep_addr = out_ep,
        .ep_cb = usbd_cdc_acm_bulk_out
    };

    struct usbd_endpoint cdc_in_ep = {
        .ep_addr = in_ep,
        .ep_cb = usbd_cdc_acm_bulk_in
    };

    serial = usbd_serial_alloc();
    if (serial == NULL) {
        USB_LOG_ERR("No more serial device available\n");
        return;
    }

    serial->busid = busid;
    serial->in_ep = in_ep;
    serial->out_ep = out_ep;
    serial->tx_done = usb_osal_sem_create(0);

    usbd_add_interface(busid, usbd_cdc_acm_init_intf(busid, &serial->intf_ctrl));
    usbd_add_interface(busid, usbd_cdc_acm_init_intf(busid, &serial->intf_data));
    usbd_add_endpoint(busid, &cdc_out_ep);
    usbd_add_endpoint(busid, &cdc_in_ep);

    if (usbd_serial_register(serial, NULL) != RT_EOK) {
        USB_LOG_ERR("Failed to register serial device\n");
        usbd_serial_free(serial);
        return;
    }

    USB_LOG_INFO("USB CDC ACM Serial Device %s initialized\n", serial->name);
}
