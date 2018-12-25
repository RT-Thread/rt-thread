/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-16     ZYH          first version
 * 2018-12-13     heyuanjie  add file operations
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtservice.h>
#include <rtdevice.h>
#include <drivers/usb_device.h>
#include "winusb.h"
/* need macro RT_USING_POSIX */
#include <dfs_file.h>
#include <dfs_poll.h>

/* default for ADB */
#ifndef WINUSB_MANUFAC_STRING
#define WINUSB_MANUFAC_STRING "RT-Thread Team"
#endif
#ifndef WINUSB_PRODUCT_STRING
#define WINUSB_PRODUCT_STRING "ADB Interface"
#endif
#ifndef WINUSB_INTERF_STRING
#define WINUSB_INTERF_STRING "ADB Interface"
#endif
#ifndef WINUSB_COMPATID_STRING
#define WINUSB_COMPATID_STRING "ADB"
#endif
#ifndef WINUSB_BCDDEVICE
#define WINUSB_BCDDEVICE 0x0318
#endif
#ifndef WINUSB_INTERF_SUBCLASS
#define WINUSB_INTERF_SUBCLASS 0x42
#endif
#ifndef WINUSB_INTERF_PROTOCOL
#define WINUSB_INTERF_PROTOCOL 0x01
#endif

struct winusb_device
{
    struct rt_device parent;
    void (*cmd_handler)(rt_uint8_t *buffer, rt_size_t size);
    rt_uint8_t cmd_buff[256];
    uep_t ep_out;
    uep_t ep_in;

    struct rt_wqueue wq;
    struct rt_wqueue rq;
    rt_uint16_t rdcnt;
    rt_uint16_t wrcnt;
    struct rt_ringbuffer *rrb;
};

typedef struct winusb_device * winusb_device_t;

ALIGN(4)
static struct udevice_descriptor dev_desc =
{
    USB_DESC_LENGTH_DEVICE,     //bLength;
    USB_DESC_TYPE_DEVICE,       //type;
    USB_BCD_VERSION,            //bcdUSB;
    0x00,                       //bDeviceClass;
    0x00,                       //bDeviceSubClass;
    0x00,                       //bDeviceProtocol;
    0x40,                       //bMaxPacketSize0;
    _VENDOR_ID,                 //idVendor;
    _PRODUCT_ID,                //idProduct;
    WINUSB_BCDDEVICE,           //bcdDevice;
    USB_STRING_MANU_INDEX,      //iManufacturer;
    USB_STRING_PRODUCT_INDEX,   //iProduct;
    USB_STRING_SERIAL_INDEX,    //iSerialNumber;
    USB_DYNAMIC,                //bNumConfigurations;
};

//FS and HS needed
ALIGN(4)
static struct usb_qualifier_descriptor dev_qualifier =
{
    sizeof(dev_qualifier),          //bLength
    USB_DESC_TYPE_DEVICEQUALIFIER,  //bDescriptorType
    0x0200,                         //bcdUSB
    0x00,                           //bDeviceClass
    0x00,                           //bDeviceSubClass
    0x00,                           //bDeviceProtocol
    64,                             //bMaxPacketSize0
    0x01,                           //bNumConfigurations
    0,
};

ALIGN(4)
struct winusb_descriptor _winusb_desc = 
{
#ifdef RT_USB_DEVICE_COMPOSITE
    /* Interface Association Descriptor */
    {
        USB_DESC_LENGTH_IAD,
        USB_DESC_TYPE_IAD,
        USB_DYNAMIC,
        0x01,
        0xFF,
        0x00,
        0x00,
        0x00,
    },
#endif
    /*interface descriptor*/
    {
        USB_DESC_LENGTH_INTERFACE,  //bLength;
        USB_DESC_TYPE_INTERFACE,    //type;
        USB_DYNAMIC,                //bInterfaceNumber;
        0x00,                       //bAlternateSetting;
        0x02,                       //bNumEndpoints
        0xFF,                       //bInterfaceClass;
        WINUSB_INTERF_SUBCLASS,     //bInterfaceSubClass;
        WINUSB_INTERF_PROTOCOL,     //bInterfaceProtocol;
        0x05,                       //iInterface;
    },
    /*endpoint descriptor*/
    {
        USB_DESC_LENGTH_ENDPOINT,
        USB_DESC_TYPE_ENDPOINT,
        USB_DYNAMIC | USB_DIR_OUT,
        USB_EP_ATTR_BULK,
        USB_DYNAMIC,
        0x00,
    },
    /*endpoint descriptor*/
    {
        USB_DESC_LENGTH_ENDPOINT,
        USB_DESC_TYPE_ENDPOINT,
        USB_DYNAMIC | USB_DIR_IN,
        USB_EP_ATTR_BULK,
        USB_DYNAMIC,
        0x00,
    },
};

ALIGN(4)
const static char* _ustring[] =
{
    "Language",
    WINUSB_MANUFAC_STRING,
    WINUSB_PRODUCT_STRING,
    "32021919830108",
    "Configuration",
    WINUSB_INTERF_STRING,
    USB_STRING_OS//must be
};

ALIGN(4)
static struct usb_os_proerty winusb_proerty[] = 
{
    USB_OS_PROERTY_DESC(USB_OS_PROERTY_TYPE_REG_SZ,"DeviceInterfaceGUID",RT_WINUSB_GUID),
};

ALIGN(4)
static struct usb_os_function_comp_id_descriptor winusb_func_comp_id_desc = 
{
    .bFirstInterfaceNumber = USB_DYNAMIC,
    .reserved1          = 0x01,
    .compatibleID       = {WINUSB_COMPATID_STRING},
    .subCompatibleID    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .reserved2          = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

static int _readreq(ufunction_t func, struct winusb_device *wd)
{
    struct uio_request *req;

    req = &wd->ep_out->request;

    req->buffer = wd->ep_out->buffer;
    req->size = EP_MAXPACKET(wd->ep_out);
    req->req_type = UIO_REQUEST_READ_BEST;

    return rt_usbd_io_request(func->device, wd->ep_out, req);
}

static rt_err_t _ep_out_handler(ufunction_t func, rt_size_t size)
{
    winusb_device_t wd = (winusb_device_t)func->user_data;
    int space;

    space = rt_ringbuffer_space_len(wd->rrb);
    if (size <= space)
    {
        rt_ringbuffer_put(wd->rrb, wd->ep_out->buffer, size);
        size = 0;
    }
    else
        wd->rdcnt = size; /* let data pending in ep_out->buffer */
    rt_wqueue_wakeup(&(wd->rq), (void *)POLLIN);
    if (size == 0)
        _readreq(func, wd);

    return RT_EOK;
}

static rt_err_t _ep_in_handler(ufunction_t func, rt_size_t size)
{
    winusb_device_t wd = (winusb_device_t)func->user_data;

    wd->wrcnt -= size;
    rt_wqueue_wakeup(&(wd->wq), (void *)POLLOUT);

    return RT_EOK;
}

static ufunction_t cmd_func = RT_NULL;
static rt_err_t _ep0_cmd_handler(udevice_t device, rt_size_t size)
{
    winusb_device_t winusb_device;

    if (cmd_func != RT_NULL)
    {
        winusb_device = (winusb_device_t)cmd_func->user_data;
        cmd_func = RT_NULL;
        if (winusb_device->cmd_handler != RT_NULL)
        {
            winusb_device->cmd_handler(winusb_device->cmd_buff, size);
        }
    }
    dcd_ep0_send_status(device->dcd);
    return RT_EOK;
}

static rt_err_t _ep0_cmd_read(ufunction_t func, ureq_t setup)
{
    winusb_device_t winusb_device = (winusb_device_t)func->user_data;
    cmd_func = func;
    rt_usbd_ep0_read(func->device, winusb_device->cmd_buff, setup->wLength, _ep0_cmd_handler);
    return RT_EOK;
}

static rt_err_t _interface_handler(ufunction_t func, ureq_t setup)
{
    switch (setup->bRequest)
    {
    case 'A':
        switch (setup->wIndex)
        {
        case 0x05:
            usbd_os_proerty_descriptor_send(func, setup, winusb_proerty, sizeof(winusb_proerty) / sizeof(winusb_proerty[0]));
            break;
        }
        break;
    case 0x0A: //customer
        _ep0_cmd_read(func, setup);
        break;
    }

    return RT_EOK;
}

#ifdef RT_USING_POSIX
static int _ep_alloc_request(uep_t ep)
{
    int size;

    size = EP_MAXPACKET(ep);
    ep->buffer = rt_malloc(size);
    if (!ep->buffer)
        return -1;

    ep->request.buffer = ep->buffer;
    ep->request.size = size;
    ep->request.req_type = UIO_REQUEST_READ_BEST;

    return 0;
}
#endif

static rt_err_t _function_enable(ufunction_t func)
{
    struct winusb_device *wd;

    RT_ASSERT(func != RT_NULL);
    wd = func->user_data;

    wd->rdcnt = 0;
    wd->wrcnt = 0;

    if (_ep_alloc_request(wd->ep_out) != 0)
        return -1;
    if (_ep_alloc_request(wd->ep_in) != 0)
    {
        rt_free(wd->ep_out->buffer);
        return -1;
    }
    _readreq(func, wd);

    return RT_EOK;
}

static rt_err_t _function_disable(ufunction_t func)
{
    struct winusb_device *wd;

    RT_ASSERT(func != RT_NULL);
    wd = func->user_data;

    rt_free(wd->ep_out->buffer);
    rt_free(wd->ep_in->buffer);
    wd->ep_out->buffer = 0;
    wd->ep_in->buffer = 0;

    rt_wqueue_wakeup(&(wd->rq), (void *)POLLHUP);
    rt_wqueue_wakeup(&(wd->wq), (void *)POLLHUP);

    return RT_EOK;
}

static struct ufunction_ops ops =
{
    _function_enable,
    _function_disable,
    RT_NULL,
};

static rt_err_t _winusb_descriptor_config(winusb_desc_t winusb, rt_uint8_t cintf_nr, rt_uint8_t device_is_hs)
{
#ifdef RT_USB_DEVICE_COMPOSITE
    winusb->iad_desc.bFirstInterface = cintf_nr;
#endif
    winusb->ep_out_desc.wMaxPacketSize = device_is_hs ? 512 : 64;
    winusb->ep_in_desc.wMaxPacketSize = device_is_hs ? 512 : 64;
    winusb_func_comp_id_desc.bFirstInterfaceNumber = cintf_nr;
    return RT_EOK;
}

/* file operations */
static int _file_open(struct dfs_fd *fd)
{
    return 0;
}

static int _file_close(struct dfs_fd *fd)
{
    return 0;
}

static int _file_ioctl(struct dfs_fd *fd, int cmd, void *args)
{
    return 0;
}

static int _file_read(struct dfs_fd *fd, void *buf, size_t size)
{
    struct winusb_device *wd;
    struct ufunction *f;
    size_t rsize;

    wd = (struct winusb_device *)fd->data;
    f = (struct ufunction *)wd->parent.user_data;

    if (!f->enabled)
        return -ENODEV;

    while (!wd->rdcnt && !rt_ringbuffer_data_len(wd->rrb))
    {
        if (fd->flags & O_NONBLOCK)
            return -EAGAIN;

        rt_wqueue_wait(&wd->rq, 0, RT_WAITING_FOREVER);
        if (!f->enabled)
            return -ENODEV;
    }

    if (wd->rdcnt)
    {
        rsize = wd->rdcnt > size ? size : wd->rdcnt;
        rt_memcpy(buf, wd->ep_out->buffer, rsize);
        wd->rdcnt -= rsize;
    }
    else
    {
        rsize = rt_ringbuffer_data_len(wd->rrb);
        if (rsize > size)
            rsize = size;
        rt_ringbuffer_get(wd->rrb, buf, rsize);
    }

    if (wd->rdcnt == 0)
    {
        _readreq(f, wd);
    }

    return rsize;
}

static int _file_write(struct dfs_fd *fd, const void *buf, size_t size)
{
    struct winusb_device *wd;
    struct ufunction *f;
    struct uio_request *req;
    int wlen;

    wd = (struct winusb_device *)fd->data;
    f = (struct ufunction *)wd->parent.user_data;

    if (!f->enabled)
        return -ENODEV;

    while (wd->wrcnt)
    {
        if (fd->flags & O_NONBLOCK)
            return -EAGAIN;

        rt_wqueue_wait(&wd->wq, 0, RT_WAITING_FOREVER);
        if (!f->enabled)
            return -ENODEV;
    }

    req = &wd->ep_in->request;

    wlen = size > EP_MAXPACKET(wd->ep_in) ? EP_MAXPACKET(wd->ep_in) : size;
    wd->wrcnt = wlen;
    req->buffer = wd->ep_in->buffer;
    rt_memcpy(req->buffer, buf, wlen);
    req->size = wlen;
    req->req_type = UIO_REQUEST_WRITE;
    rt_usbd_io_request(f->device, wd->ep_in, req);

    return wlen;
}

static int _file_poll(struct dfs_fd *fd, struct rt_pollreq *req)
{
    int mask = 0;
    struct winusb_device *wd;
    struct ufunction *f;

    wd = (struct winusb_device *)fd->data;
    f = (struct ufunction *)wd->parent.user_data;

    if (!f->enabled)
        return POLLHUP;
    if (wd->rdcnt || rt_ringbuffer_data_len(wd->rrb))
        mask |= POLLIN;
    else
        rt_poll_add(&wd->rq, req);

    if (!wd->wrcnt)
        mask |= POLLOUT;
    else
        rt_poll_add(&wd->wq, req);

    return mask;
}

static const struct dfs_file_ops _fops =
{
    _file_open,
    _file_close,
    _file_ioctl,
    _file_read,
    _file_write,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _file_poll
};

static rt_err_t rt_usb_winusb_init(ufunction_t func)
{
    rt_err_t ret;

    winusb_device_t winusb_device = (winusb_device_t)func->user_data;
    winusb_device->parent.type = RT_Device_Class_Miscellaneous;

    winusb_device->parent.user_data = func;
    ret = rt_device_register(&winusb_device->parent, "winusb", RT_DEVICE_FLAG_RDWR);

    winusb_device->parent.fops = &_fops;
    rt_wqueue_init(&winusb_device->rq);
    rt_wqueue_init(&winusb_device->wq);
    winusb_device->rrb = rt_ringbuffer_create(512);

    return ret;
}

ufunction_t rt_usbd_function_winusb_create(udevice_t device)
{
    ufunction_t func;
    winusb_device_t winusb_device;

    uintf_t winusb_intf;
    ualtsetting_t winusb_setting;
    winusb_desc_t winusb_desc;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);

    /* set usb device string description */
    rt_usbd_device_set_string(device, _ustring);

    /* create a cdc function */
    func = rt_usbd_function_new(device, &dev_desc, &ops);
    rt_usbd_device_set_qualifier(device, &dev_qualifier);

    /* allocate memory for cdc vcom data */
    winusb_device = (winusb_device_t)rt_malloc(sizeof(struct winusb_device));
    rt_memset((void *)winusb_device, 0, sizeof(struct winusb_device));
    func->user_data = (void *)winusb_device;
    /* create an interface object */
    winusb_intf = rt_usbd_interface_new(device, _interface_handler);

    /* create an alternate setting object */
    winusb_setting = rt_usbd_altsetting_new(sizeof(struct winusb_descriptor));

    /* config desc in alternate setting */
    rt_usbd_altsetting_config_descriptor(winusb_setting, &_winusb_desc, (rt_off_t) & ((winusb_desc_t)0)->intf_desc);

    /* configure the hid interface descriptor */
    _winusb_descriptor_config(winusb_setting->desc, winusb_intf->intf_num, device->dcd->device_is_hs);

    /* create endpoint */
    winusb_desc = (winusb_desc_t)winusb_setting->desc;
    winusb_device->ep_out = rt_usbd_endpoint_new(&winusb_desc->ep_out_desc, _ep_out_handler);
    winusb_device->ep_in = rt_usbd_endpoint_new(&winusb_desc->ep_in_desc, _ep_in_handler);

    /* add the int out and int in endpoint to the alternate setting */
    rt_usbd_altsetting_add_endpoint(winusb_setting, winusb_device->ep_out);
    rt_usbd_altsetting_add_endpoint(winusb_setting, winusb_device->ep_in);

    /* add the alternate setting to the interface, then set default setting */
    rt_usbd_interface_add_altsetting(winusb_intf, winusb_setting);
    rt_usbd_set_altsetting(winusb_intf, 0);

    /* add the interface to the mass storage function */
    rt_usbd_function_add_interface(func, winusb_intf);

    rt_usbd_os_comp_id_desc_add_os_func_comp_id_desc(device->os_comp_id_desc, &winusb_func_comp_id_desc);
    /* initilize winusb */
    rt_usb_winusb_init(func);
    return func;
}

struct udclass winusb_class =
{
    .rt_usbd_function_create = rt_usbd_function_winusb_create
};

int rt_usbd_winusb_class_register(void)
{
    rt_usbd_class_register(&winusb_class);
    return 0;
}
INIT_PREV_EXPORT(rt_usbd_winusb_class_register);
