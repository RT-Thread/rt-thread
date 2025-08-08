/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "usbh_core.h"
#include "usbh_cdc_acm.h"
#include "usbh_ftdi.h"
#include "usbh_cp210x.h"
#include "usbh_ch34x.h"
#include "usbh_pl2303.h"

#define DEV_FORMAT_VENDOR  "ttyUSB%d"
#define DEV_FORMAT_CDC_ACM "ttyACM%d"

#define USBH_RX_MAX_SIZE 2048

#ifndef CONFIG_USBHOST_MAX_VENDOR_SERIAL_CLASS
#define CONFIG_USBHOST_MAX_VENDOR_SERIAL_CLASS (4)
#endif

#ifndef CONFIG_USBHOST_SERIAL_RX_BUFSIZE
#define CONFIG_USBHOST_SERIAL_RX_BUFSIZE (USBH_RX_MAX_SIZE * 2)
#endif

enum usbh_serial_type {
    USBH_SERIAL_TYPE_CDC_ACM = 0,
    USBH_SERIAL_TYPE_FTDI,
    USBH_SERIAL_TYPE_CP210X,
    USBH_SERIAL_TYPE_CH34X,
    USBH_SERIAL_TYPE_PL2303,
};

struct usbh_serial {
    struct rt_device parent;
    enum usbh_serial_type type;
    uint8_t minor;
    char name[CONFIG_USBHOST_DEV_NAMELEN];
    struct rt_ringbuffer rx_rb;
    rt_uint8_t rx_rb_buffer[CONFIG_USBHOST_SERIAL_RX_BUFSIZE];
};

static uint32_t g_devinuse_vendor = 0;
static uint32_t g_devinuse_cdc_acm = 0;

static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_usbh_serial_vendor_rx_buf[CONFIG_USBHOST_MAX_VENDOR_SERIAL_CLASS][USB_ALIGN_UP(USBH_RX_MAX_SIZE, CONFIG_USB_ALIGN_SIZE)];
static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_usbh_serial_cdc_acm_rx_buf[CONFIG_USBHOST_MAX_CDC_ACM_CLASS][USB_ALIGN_UP(USBH_RX_MAX_SIZE, CONFIG_USB_ALIGN_SIZE)];

static struct usbh_serial *usbh_serial_alloc(uint8_t type)
{
    uint8_t devno;
    struct usbh_serial *serial;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_VENDOR_SERIAL_CLASS; devno++) {
        if ((g_devinuse_vendor & (1U << devno)) == 0) {
            g_devinuse_vendor |= (1U << devno);

            serial = rt_malloc(sizeof(struct usbh_serial));
            memset(serial, 0, sizeof(struct usbh_serial));
            serial->type = type;
            serial->minor = devno;
            snprintf(serial->name, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT_VENDOR, serial->minor);
            return serial;
        }
    }
    return NULL;
}

static void usbh_serial_free(struct usbh_serial *serial)
{
    uint8_t devno = serial->minor;

    if (devno < 32) {
        g_devinuse_vendor &= ~(1U << devno);
    }
    memset(serial, 0, sizeof(struct usbh_serial));
    rt_free(serial);
}

static struct usbh_serial *usbh_serial_cdc_acm_alloc(uint8_t type)
{
    uint8_t devno;
    struct usbh_serial *serial;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_CDC_ACM_CLASS; devno++) {
        if ((g_devinuse_cdc_acm & (1U << devno)) == 0) {
            g_devinuse_cdc_acm |= (1U << devno);

            serial = rt_malloc(sizeof(struct usbh_serial));
            memset(serial, 0, sizeof(struct usbh_serial));
            serial->type = type;
            serial->minor = devno;
            snprintf(serial->name, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT_CDC_ACM, serial->minor);
            return serial;
        }
    }
    return NULL;
}

static void usbh_serial_cdc_acm_free(struct usbh_serial *serial)
{
    uint8_t devno = serial->minor;

    if (devno < 32) {
        g_devinuse_cdc_acm &= ~(1U << devno);
    }
    memset(serial, 0, sizeof(struct usbh_serial));
    rt_free(serial);
}

static rt_err_t usbh_serial_open(struct rt_device *dev, rt_uint16_t oflag)
{
    struct usbh_serial *serial;

    RT_ASSERT(dev != RT_NULL);

    serial = (struct usbh_serial *)dev;

    switch (serial->type) {
        case USBH_SERIAL_TYPE_CDC_ACM:
            break;
        case USBH_SERIAL_TYPE_FTDI:
            break;
        case USBH_SERIAL_TYPE_CP210X:
            break;
        case USBH_SERIAL_TYPE_CH34X:
            break;
        case USBH_SERIAL_TYPE_PL2303:
            break;

        default:
            break;
    }

    return RT_EOK;
}

static rt_err_t usbh_serial_close(struct rt_device *dev)
{
    struct usbh_serial *serial;

    RT_ASSERT(dev != RT_NULL);

    serial = (struct usbh_serial *)dev;

    switch (serial->type) {
        case USBH_SERIAL_TYPE_CDC_ACM:
            break;
        case USBH_SERIAL_TYPE_FTDI:
            break;
        case USBH_SERIAL_TYPE_CP210X:
            break;
        case USBH_SERIAL_TYPE_CH34X:
            break;
        case USBH_SERIAL_TYPE_PL2303:
            break;

        default:
            break;
    }

    return RT_EOK;
}

static rt_ssize_t usbh_serial_read(struct rt_device *dev,
                                   rt_off_t pos,
                                   void *buffer,
                                   rt_size_t size)
{
    struct usbh_serial *serial;

    RT_ASSERT(dev != RT_NULL);

    serial = (struct usbh_serial *)dev;

    return rt_ringbuffer_get(&serial->rx_rb, (rt_uint8_t *)buffer, size);
}

static rt_ssize_t usbh_serial_write(struct rt_device *dev,
                                    rt_off_t pos,
                                    const void *buffer,
                                    rt_size_t size)
{
    struct usbh_serial *serial;
    int ret = 0;
    rt_uint8_t *align_buf;

    RT_ASSERT(dev != RT_NULL);

    serial = (struct usbh_serial *)dev;

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

    switch (serial->type) {
#if defined(PKG_CHERRYUSB_HOST_CDC_ACM) || defined(RT_CHERRYUSB_HOST_CDC_ACM)
        case USBH_SERIAL_TYPE_CDC_ACM:
            ret = usbh_cdc_acm_bulk_out_transfer((struct usbh_cdc_acm *)dev->user_data, (uint8_t *)align_buf, size, RT_WAITING_FOREVER);
            if (ret < 0) {
                USB_LOG_ERR("usbh_cdc_acm_bulk_out_transfer failed: %d\n", ret);
#ifdef CONFIG_USB_DCACHE_ENABLE
                rt_free_align(align_buf);
#endif
                return 0;
            }
            break;
#endif
#if defined(PKG_CHERRYUSB_HOST_FTDI) || defined(RT_CHERRYUSB_HOST_FTDI)
        case USBH_SERIAL_TYPE_FTDI:
            ret = usbh_ftdi_bulk_out_transfer((struct usbh_ftdi *)dev->user_data, (uint8_t *)align_buf, size, RT_WAITING_FOREVER);
            if (ret < 0) {
                USB_LOG_ERR("usbh_ftdi_bulk_out_transfer failed: %d\n", ret);
#ifdef CONFIG_USB_DCACHE_ENABLE
                rt_free_align(align_buf);
#endif
                return 0;
            }
            break;
#endif
#if defined(PKG_CHERRYUSB_HOST_CH34X) || defined(RT_CHERRYUSB_HOST_CH34X)
        case USBH_SERIAL_TYPE_CH34X:
            ret = usbh_ch34x_bulk_out_transfer((struct usbh_ch34x *)dev->user_data, (uint8_t *)align_buf, size, RT_WAITING_FOREVER);
            if (ret < 0) {
                USB_LOG_ERR("usbh_ch34x_bulk_out_transfer failed: %d\n", ret);
#ifdef CONFIG_USB_DCACHE_ENABLE
                rt_free_align(align_buf);
#endif
                return 0;
            }
            break;
#endif
#if defined(PKG_CHERRYUSB_HOST_PL2303) || defined(RT_CHERRYUSB_HOST_PL2303)
        case USBH_SERIAL_TYPE_PL2303:
            ret = usbh_pl2303_bulk_out_transfer((struct usbh_pl2303 *)dev->user_data, (uint8_t *)align_buf, size, RT_WAITING_FOREVER);
            if (ret < 0) {
                USB_LOG_ERR("usbh_pl2303_bulk_out_transfer failed: %d\n", ret);
#ifdef CONFIG_USB_DCACHE_ENABLE
                rt_free_align(align_buf);
#endif
                return 0;
            }
            break;
#endif
        default:
            break;
    }

#ifdef CONFIG_USB_DCACHE_ENABLE
    if ((uint32_t)buffer & (CONFIG_USB_ALIGN_SIZE - 1)) {
        rt_free_align(align_buf);
    }
#endif

    return ret;
}

static rt_err_t usbh_serial_control(struct rt_device *dev,
                                    int cmd,
                                    void *args)
{
    struct usbh_serial *serial;
    struct serial_configure *config;
    struct cdc_line_coding line_coding;
    int ret = -RT_EINVAL;

    RT_ASSERT(dev != RT_NULL);

    serial = (struct usbh_serial *)dev;

    switch (serial->type) {
#if defined(PKG_CHERRYUSB_HOST_CDC_ACM) || defined(RT_CHERRYUSB_HOST_CDC_ACM)
        case USBH_SERIAL_TYPE_CDC_ACM:
            if (cmd == RT_DEVICE_CTRL_CONFIG) {
                struct usbh_cdc_acm *cdc_acm_class;
                cdc_acm_class = (struct usbh_cdc_acm *)dev->user_data;

                config = (struct serial_configure *)args;

                line_coding.dwDTERate = config->baud_rate;
                line_coding.bDataBits = config->data_bits;
                line_coding.bCharFormat = 0; // STOP_BITS_1
                line_coding.bParityType = config->parity;

                usbh_cdc_acm_set_line_coding(cdc_acm_class, &line_coding);
            }

            ret = RT_EOK;
            break;
#endif
#if defined(PKG_CHERRYUSB_HOST_FTDI) || defined(RT_CHERRYUSB_HOST_FTDI)
        case USBH_SERIAL_TYPE_FTDI:
            if (cmd == RT_DEVICE_CTRL_CONFIG) {
                struct usbh_ftdi *ftdi_class;
                ftdi_class = (struct usbh_ftdi *)dev->user_data;

                config = (struct serial_configure *)args;

                line_coding.dwDTERate = config->baud_rate;
                line_coding.bDataBits = config->data_bits;
                line_coding.bCharFormat = 0; // STOP_BITS_1
                line_coding.bParityType = config->parity;

                usbh_ftdi_set_line_coding(ftdi_class, &line_coding);
            }

            ret = RT_EOK;
            break;
#endif
#if defined(PKG_CHERRYUSB_HOST_CP210X) || defined(RT_CHERRYUSB_HOST_CP210X)
        case USBH_SERIAL_TYPE_CP210X:
            if (cmd == RT_DEVICE_CTRL_CONFIG) {
                struct usbh_cp210x *cp210x_class;
                cp210x_class = (struct usbh_cp210x *)dev->user_data;

                config = (struct serial_configure *)args;

                line_coding.dwDTERate = config->baud_rate;
                line_coding.bDataBits = config->data_bits;
                line_coding.bCharFormat = 0; // STOP_BITS_1
                line_coding.bParityType = config->parity;

                usbh_cp210x_set_line_coding(cp210x_class, &line_coding);
            }

            ret = RT_EOK;
            break;
#endif
#if defined(PKG_CHERRYUSB_HOST_CH34X) || defined(RT_CHERRYUSB_HOST_CH34X)
        case USBH_SERIAL_TYPE_CH34X:
            if (cmd == RT_DEVICE_CTRL_CONFIG) {
                struct usbh_ch34x *ch34x_class;
                ch34x_class = (struct usbh_ch34x *)dev->user_data;

                config = (struct serial_configure *)args;

                line_coding.dwDTERate = config->baud_rate;
                line_coding.bDataBits = config->data_bits;
                line_coding.bCharFormat = 0; // STOP_BITS_1
                line_coding.bParityType = config->parity;

                usbh_ch34x_set_line_coding(ch34x_class, &line_coding);
            }

            ret = RT_EOK;
            break;
#endif
#if defined(PKG_CHERRYUSB_HOST_PL2303) || defined(RT_CHERRYUSB_HOST_PL2303)
        case USBH_SERIAL_TYPE_PL2303:
            if (cmd == RT_DEVICE_CTRL_CONFIG) {
                struct usbh_pl2303 *pl2303_class;
                pl2303_class = (struct usbh_pl2303 *)dev->user_data;

                config = (struct serial_configure *)args;

                line_coding.dwDTERate = config->baud_rate;
                line_coding.bDataBits = config->data_bits;
                line_coding.bCharFormat = 0; // STOP_BITS_1
                line_coding.bParityType = config->parity;

                usbh_pl2303_set_line_coding(pl2303_class, &line_coding);
            }

            ret = RT_EOK;
            break;
#endif
        default:
            break;
    }

    return ret;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops usbh_serial_ops = {
    NULL,
    usbh_serial_open,
    usbh_serial_close,
    usbh_serial_read,
    usbh_serial_write,
    usbh_serial_control
};
#endif

#ifdef RT_USING_POSIX_DEVIO
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <dfs_file.h>

#ifdef RT_USING_POSIX_TERMIOS
#include <termios.h>
#endif

static rt_err_t usbh_serial_fops_rx_ind(rt_device_t dev, rt_size_t size)
{
    rt_wqueue_wakeup(&(dev->wait_queue), (void*)POLLIN);

    return RT_EOK;
}

/* fops for serial */
static int usbh_serial_fops_open(struct dfs_file *fd)
{
    rt_err_t ret = 0;
    rt_uint16_t flags = 0;
    rt_device_t device;

    device = (rt_device_t)fd->vnode->data;
    RT_ASSERT(device != RT_NULL);

    switch (fd->flags & O_ACCMODE)
    {
    case O_RDONLY:
        USB_LOG_DBG("fops open: O_RDONLY!");
        flags = RT_DEVICE_FLAG_RDONLY;
        break;
    case O_WRONLY:
        USB_LOG_DBG("fops open: O_WRONLY!");
        flags = RT_DEVICE_FLAG_WRONLY;
        break;
    case O_RDWR:
        USB_LOG_DBG("fops open: O_RDWR!");
        flags = RT_DEVICE_FLAG_RDWR;
        break;
    default:
        USB_LOG_ERR("fops open: unknown mode - %d!", fd->flags & O_ACCMODE);
        break;
    }

    if ((fd->flags & O_ACCMODE) != O_WRONLY)
        rt_device_set_rx_indicate(device, usbh_serial_fops_rx_ind);
    ret = rt_device_open(device, flags);
    if (ret == RT_EOK) return 0;

    return ret;
}

static int usbh_serial_fops_close(struct dfs_file *fd)
{
    rt_device_t device;

    device = (rt_device_t)fd->vnode->data;

    rt_device_set_rx_indicate(device, RT_NULL);
    rt_device_close(device);

    return 0;
}

static int usbh_serial_fops_ioctl(struct dfs_file *fd, int cmd, void *args)
{
    rt_device_t device;
    int flags = (int)(rt_base_t)args;
    int mask  = O_NONBLOCK | O_APPEND;

    device = (rt_device_t)fd->vnode->data;
    switch (cmd)
    {
    case FIONREAD:
        break;
    case FIONWRITE:
        break;
    case F_SETFL:
        flags &= mask;
        fd->flags &= ~mask;
        fd->flags |= flags;
        break;
    }

    return rt_device_control(device, cmd, args);
}

static int usbh_serial_fops_read(struct dfs_file *fd, void *buf, size_t count)
{
    int size = 0;
    rt_device_t device;

    device = (rt_device_t)fd->vnode->data;

    do
    {
        size = rt_device_read(device, -1,  buf, count);
        if (size <= 0)
        {
            if (fd->flags & O_NONBLOCK)
            {
                size = -EAGAIN;
                break;
            }

            rt_wqueue_wait(&(device->wait_queue), 0, RT_WAITING_FOREVER);
        }
    }while (size <= 0);

    return size;
}

static int usbh_serial_fops_write(struct dfs_file *fd, const void *buf, size_t count)
{
    rt_device_t device;

    device = (rt_device_t)fd->vnode->data;
    return rt_device_write(device, -1, buf, count);
}

static int usbh_serial_fops_poll(struct dfs_file *fd, struct rt_pollreq *req)
{
    int mask = 0;
    int flags = 0;
    rt_device_t device;
    struct usbh_serial *serial;

    device = (rt_device_t)fd->vnode->data;
    RT_ASSERT(device != RT_NULL);

    serial = (struct usbh_serial *)device;

    /* only support POLLIN */
    flags = fd->flags & O_ACCMODE;
    if (flags == O_RDONLY || flags == O_RDWR)
    {
        rt_base_t level;

        rt_poll_add(&(device->wait_queue), req);

        level = rt_hw_interrupt_disable();

        if (rt_ringbuffer_data_len(&serial->rx_rb))
            mask |= POLLIN;
        rt_hw_interrupt_enable(level);
    }
    // mask|=POLLOUT;
   return mask;
}

const static struct dfs_file_ops usbh_serial_fops =
{
    usbh_serial_fops_open,
    usbh_serial_fops_close,
    usbh_serial_fops_ioctl,
    usbh_serial_fops_read,
    usbh_serial_fops_write,
    RT_NULL, /* flush */
    RT_NULL, /* lseek */
    RT_NULL, /* getdents */
    usbh_serial_fops_poll,
};
#endif /* RT_USING_POSIX_DEVIO */

rt_err_t usbh_serial_register(struct usbh_serial *serial,
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
    device->ops = &usbh_serial_ops;
#else
    device->init = NULL;
    device->open = usbh_serial_open;
    device->close = usbh_serial_close;
    device->read = usbh_serial_read;
    device->write = usbh_serial_write;
    device->control = usbh_serial_control;
#endif
    device->user_data = data;

    /* register a character device */
    ret = rt_device_register(device, serial->name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_REMOVABLE);

#ifdef RT_USING_POSIX_DEVIO
    /* set fops */
    device->fops = &usbh_serial_fops;
#endif
    rt_ringbuffer_init(&serial->rx_rb, serial->rx_rb_buffer, sizeof(serial->rx_rb_buffer));

    return ret;
}

void usbh_serial_unregister(struct usbh_serial *serial)
{
    RT_ASSERT(serial != NULL);

    rt_device_unregister(&serial->parent);

    if (serial->type == USBH_SERIAL_TYPE_CDC_ACM) {
        usbh_serial_cdc_acm_free(serial);
    } else {
        usbh_serial_free(serial);
    }
}

#if defined(PKG_CHERRYUSB_HOST_CDC_ACM) || defined(RT_CHERRYUSB_HOST_CDC_ACM)
void usbh_cdc_acm_callback(void *arg, int nbytes)
{
    struct usbh_cdc_acm *cdc_acm_class = (struct usbh_cdc_acm *)arg;
    struct usbh_serial *serial;
    int ret;
    struct usbh_urb *urb = &cdc_acm_class->bulkin_urb;

    if (nbytes > 0) {
        serial = (struct usbh_serial *)cdc_acm_class->user_data;
        rt_ringbuffer_put(&serial->rx_rb, g_usbh_serial_cdc_acm_rx_buf[serial->minor], nbytes);

        if (serial->parent.rx_indicate) {
            serial->parent.rx_indicate(&serial->parent, nbytes);
        }

        usbh_bulk_urb_fill(urb, cdc_acm_class->hport, cdc_acm_class->bulkin, g_usbh_serial_cdc_acm_rx_buf[serial->minor], sizeof(g_usbh_serial_cdc_acm_rx_buf[serial->minor]), 0, usbh_cdc_acm_callback, cdc_acm_class);
        ret = usbh_submit_urb(urb);
        if (ret < 0) {
            USB_LOG_ERR("usbh_submit_urb failed: %d\n", ret);
        }
    }
}

void usbh_cdc_acm_run(struct usbh_cdc_acm *cdc_acm_class)
{
    struct usbh_serial *serial;
    int ret;
    struct usbh_urb *urb = &cdc_acm_class->bulkin_urb;

    serial = usbh_serial_cdc_acm_alloc(USBH_SERIAL_TYPE_CDC_ACM);
    cdc_acm_class->user_data = serial;

    usbh_serial_register(serial, cdc_acm_class);

    struct cdc_line_coding linecoding;
    linecoding.dwDTERate = 115200;
    linecoding.bDataBits = 8;
    linecoding.bParityType = 0;
    linecoding.bCharFormat = 0;
    usbh_cdc_acm_set_line_coding(cdc_acm_class, &linecoding);

    usbh_bulk_urb_fill(urb, cdc_acm_class->hport, cdc_acm_class->bulkin, g_usbh_serial_cdc_acm_rx_buf[serial->minor], sizeof(g_usbh_serial_cdc_acm_rx_buf[serial->minor]), 0, usbh_cdc_acm_callback, cdc_acm_class);
    ret = usbh_submit_urb(urb);
    if (ret < 0) {
        USB_LOG_ERR("usbh_submit_urb failed: %d\n", ret);
        usbh_serial_unregister(serial);
        return;
    }
}

void usbh_cdc_acm_stop(struct usbh_cdc_acm *cdc_acm_class)
{
    struct usbh_serial *serial;

    serial = (struct usbh_serial *)cdc_acm_class->user_data;
    usbh_serial_unregister(serial);
}
#endif

#if defined(PKG_CHERRYUSB_HOST_FTDI) || defined(RT_CHERRYUSB_HOST_FTDI)
void usbh_ftdi_callback(void *arg, int nbytes)
{
    struct usbh_ftdi *ftdi_class = (struct usbh_ftdi *)arg;
    struct usbh_serial *serial;
    int ret;
    struct usbh_urb *urb = &ftdi_class->bulkin_urb;

    if (nbytes >= 2) {
        serial = (struct usbh_serial *)ftdi_class->user_data;

        nbytes -= 2; // Skip the first two bytes (header)
        rt_ringbuffer_put(&serial->rx_rb, &g_usbh_serial_vendor_rx_buf[serial->minor][2], nbytes);

        if (serial->parent.rx_indicate && nbytes) {
            serial->parent.rx_indicate(&serial->parent, nbytes);
        }

        usbh_bulk_urb_fill(urb, ftdi_class->hport, ftdi_class->bulkin, g_usbh_serial_vendor_rx_buf[serial->minor], sizeof(g_usbh_serial_vendor_rx_buf[serial->minor]), 0, usbh_ftdi_callback, ftdi_class);
        ret = usbh_submit_urb(urb);
        if (ret < 0) {
            USB_LOG_ERR("usbh_submit_urb failed: %d\n", ret);
        }
    }
}

void usbh_ftdi_run(struct usbh_ftdi *ftdi_class)
{
    struct usbh_serial *serial;
    int ret;
    struct usbh_urb *urb = &ftdi_class->bulkin_urb;

    serial = usbh_serial_alloc(USBH_SERIAL_TYPE_FTDI);
    ftdi_class->user_data = serial;

    usbh_serial_register(serial, ftdi_class);

    struct cdc_line_coding linecoding;
    linecoding.dwDTERate = 115200;
    linecoding.bDataBits = 8;
    linecoding.bParityType = 0;
    linecoding.bCharFormat = 0;
    usbh_ftdi_set_line_coding(ftdi_class, &linecoding);

    usbh_bulk_urb_fill(urb, ftdi_class->hport, ftdi_class->bulkin, g_usbh_serial_vendor_rx_buf[serial->minor], sizeof(g_usbh_serial_vendor_rx_buf[serial->minor]), 0, usbh_ftdi_callback, ftdi_class);
    ret = usbh_submit_urb(urb);
    if (ret < 0) {
        USB_LOG_ERR("usbh_submit_urb failed: %d\n", ret);
        usbh_serial_unregister(serial);
        return;
    }
}

void usbh_ftdi_stop(struct usbh_ftdi *ftdi_class)
{
    struct usbh_serial *serial;

    serial = (struct usbh_serial *)ftdi_class->user_data;
    usbh_serial_unregister(serial);
}
#endif

#if defined(PKG_CHERRYUSB_HOST_CH34X) || defined(RT_CHERRYUSB_HOST_CH34X)
void usbh_ch34x_callback(void *arg, int nbytes)
{
    struct usbh_ch34x *ch34x_class = (struct usbh_ch34x *)arg;
    struct usbh_serial *serial;
    int ret;
    struct usbh_urb *urb = &ch34x_class->bulkin_urb;

    if (nbytes > 0) {
        serial = (struct usbh_serial *)ch34x_class->user_data;
        rt_ringbuffer_put(&serial->rx_rb, g_usbh_serial_vendor_rx_buf[serial->minor], nbytes);

        if (serial->parent.rx_indicate) {
            serial->parent.rx_indicate(&serial->parent, nbytes);
        }

        usbh_bulk_urb_fill(urb, ch34x_class->hport, ch34x_class->bulkin, g_usbh_serial_vendor_rx_buf[serial->minor], sizeof(g_usbh_serial_vendor_rx_buf[serial->minor]), 0, usbh_ch34x_callback, ch34x_class);
        ret = usbh_submit_urb(urb);
        if (ret < 0) {
            USB_LOG_ERR("usbh_submit_urb failed: %d\n", ret);
        }
    }
}

void usbh_ch34x_run(struct usbh_ch34x *ch34x_class)
{
    struct usbh_serial *serial;
    int ret;
    struct usbh_urb *urb = &ch34x_class->bulkin_urb;

    serial = usbh_serial_alloc(USBH_SERIAL_TYPE_CH34X);
    ch34x_class->user_data = serial;

    usbh_serial_register(serial, ch34x_class);

    struct cdc_line_coding linecoding;
    linecoding.dwDTERate = 115200;
    linecoding.bDataBits = 8;
    linecoding.bParityType = 0;
    linecoding.bCharFormat = 0;
    usbh_ch34x_set_line_coding(ch34x_class, &linecoding);

    usbh_bulk_urb_fill(urb, ch34x_class->hport, ch34x_class->bulkin, g_usbh_serial_vendor_rx_buf[serial->minor], sizeof(g_usbh_serial_vendor_rx_buf[serial->minor]), 0, usbh_ch34x_callback, ch34x_class);
    ret = usbh_submit_urb(urb);
    if (ret < 0) {
        USB_LOG_ERR("usbh_submit_urb failed: %d\n", ret);
        usbh_serial_unregister(serial);
        return;
    }
}

void usbh_ch34x_stop(struct usbh_ch34x *ch34x_class)
{
    struct usbh_serial *serial;

    serial = (struct usbh_serial *)ch34x_class->user_data;
    usbh_serial_unregister(serial);
}
#endif

#if defined(PKG_CHERRYUSB_HOST_CP210X) || defined(RT_CHERRYUSB_HOST_CP210X)
void usbh_cp210x_callback(void *arg, int nbytes)
{
    struct usbh_cp210x *cp210x_class = (struct usbh_cp210x *)arg;
    struct usbh_serial *serial;
    int ret;
    struct usbh_urb *urb = &cp210x_class->bulkin_urb;

    if (nbytes > 0) {
        serial = (struct usbh_serial *)cp210x_class->user_data;
        rt_ringbuffer_put(&serial->rx_rb, g_usbh_serial_vendor_rx_buf[serial->minor], nbytes);

        if (serial->parent.rx_indicate) {
            serial->parent.rx_indicate(&serial->parent, nbytes);
        }

        usbh_bulk_urb_fill(urb, cp210x_class->hport, cp210x_class->bulkin, g_usbh_serial_vendor_rx_buf[serial->minor], sizeof(g_usbh_serial_vendor_rx_buf[serial->minor]), 0, usbh_cp210x_callback, cp210x_class);
        ret = usbh_submit_urb(urb);
        if (ret < 0) {
            USB_LOG_ERR("usbh_submit_urb failed: %d\n", ret);
        }
    }
}

void usbh_cp210x_run(struct usbh_cp210x *cp210x_class)
{
    struct usbh_serial *serial;
    int ret;
    struct usbh_urb *urb = &cp210x_class->bulkin_urb;

    serial = usbh_serial_alloc(USBH_SERIAL_TYPE_CP210X);
    cp210x_class->user_data = serial;

    usbh_serial_register(serial, cp210x_class);

    struct cdc_line_coding linecoding;
    linecoding.dwDTERate = 115200;
    linecoding.bDataBits = 8;
    linecoding.bParityType = 0;
    linecoding.bCharFormat = 0;
    usbh_cp210x_set_line_coding(cp210x_class, &linecoding);

    usbh_bulk_urb_fill(urb, cp210x_class->hport, cp210x_class->bulkin, g_usbh_serial_vendor_rx_buf[serial->minor], sizeof(g_usbh_serial_vendor_rx_buf[serial->minor]), 0, usbh_cp210x_callback, cp210x_class);
    ret = usbh_submit_urb(urb);
    if (ret < 0) {
        USB_LOG_ERR("usbh_submit_urb failed: %d\n", ret);
        usbh_serial_unregister(serial);
        return;
    }
}

void usbh_cp210x_stop(struct usbh_cp210x *cp210x_class)
{
    struct usbh_serial *serial;

    serial = (struct usbh_serial *)cp210x_class->user_data;
    usbh_serial_unregister(serial);
}
#endif

#if defined(PKG_CHERRYUSB_HOST_PL2303) || defined(RT_CHERRYUSB_HOST_PL2303)
void usbh_pl2303_callback(void *arg, int nbytes)
{
    struct usbh_pl2303 *pl2303_class = (struct usbh_pl2303 *)arg;
    struct usbh_serial *serial;
    int ret;
    struct usbh_urb *urb = &pl2303_class->bulkin_urb;

    if (nbytes > 0) {
        serial = (struct usbh_serial *)pl2303_class->user_data;
        rt_ringbuffer_put(&serial->rx_rb, g_usbh_serial_vendor_rx_buf[serial->minor], nbytes);

        if (serial->parent.rx_indicate) {
            serial->parent.rx_indicate(&serial->parent, nbytes);
        }

        usbh_bulk_urb_fill(urb, pl2303_class->hport, pl2303_class->bulkin, g_usbh_serial_vendor_rx_buf[serial->minor], sizeof(g_usbh_serial_vendor_rx_buf[serial->minor]), 0, usbh_pl2303_callback, pl2303_class);
        ret = usbh_submit_urb(urb);
        if (ret < 0) {
            USB_LOG_ERR("usbh_submit_urb failed: %d\n", ret);
        }
    }
}

void usbh_pl2303_run(struct usbh_pl2303 *pl2303_class)
{
    struct usbh_serial *serial;
    int ret;
    struct usbh_urb *urb = &pl2303_class->bulkin_urb;

    serial = usbh_serial_alloc(USBH_SERIAL_TYPE_PL2303);
    pl2303_class->user_data = serial;

    usbh_serial_register(serial, pl2303_class);

    struct cdc_line_coding linecoding;
    linecoding.dwDTERate = 115200;
    linecoding.bDataBits = 8;
    linecoding.bParityType = 0;
    linecoding.bCharFormat = 0;
    usbh_pl2303_set_line_coding(pl2303_class, &linecoding);

    usbh_bulk_urb_fill(urb, pl2303_class->hport, pl2303_class->bulkin, g_usbh_serial_vendor_rx_buf[serial->minor], sizeof(g_usbh_serial_vendor_rx_buf[serial->minor]), 0, usbh_pl2303_callback, pl2303_class);
    ret = usbh_submit_urb(urb);
    if (ret < 0) {
        USB_LOG_ERR("usbh_submit_urb failed: %d\n", ret);
        usbh_serial_unregister(serial);
        return;
    }
}

void usbh_pl2303_stop(struct usbh_pl2303 *pl2303_class)
{
    struct usbh_serial *serial;

    serial = (struct usbh_serial *)pl2303_class->user_data;
    usbh_serial_unregister(serial);
}
#endif
