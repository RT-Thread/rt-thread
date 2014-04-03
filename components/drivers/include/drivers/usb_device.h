/*
 * File      : usb_device.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
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
 * 2012-10-01     Yi Qiu       first version
 * 2012-12-12     heyuanjie87  change endpoint and class handler
 */

#ifndef  __USB_DEVICE_H__
#define  __USB_DEVICE_H__

#include <rtthread.h>
#include "usb_common.h"

/* Vendor ID */
#ifdef USB_VENDOR_ID
#define _VENDOR_ID USB_VENDOR_ID
#else
#define _VENDOR_ID 0x0EFF
#endif
/* Product ID */
#ifdef USB_PRODUCT_ID
#define _PRODUCT_ID USB_PRODUCT_ID
#else
#define _PRODUCT_ID 0x0001
#endif

#define USB_BCD_DEVICE                  0x0200   /* USB Specification Release Number in Binary-Coded Decimal */
#define USB_BCD_VERSION                 0x0200   /* USB 2.0 */

struct uclass;
struct udevice;
struct uendpoint;

struct udcd_ops
{
    rt_err_t (*set_address)(rt_uint8_t value);
    rt_err_t (*clear_feature)(rt_uint16_t value, rt_uint16_t index);
    rt_err_t (*set_feature)(rt_uint16_t value, rt_uint16_t index);
    rt_err_t (*ep_alloc)(struct uendpoint* ep);
    rt_err_t (*ep_free)(struct uendpoint* ep);
    rt_err_t (*ep_stall)(struct uendpoint* ep);
    rt_err_t (*ep_run)(struct uendpoint* ep);
    rt_err_t (*ep_stop)(struct uendpoint* ep);
    rt_err_t (*ep_read)(struct uendpoint* ep, void *buffer, rt_size_t size);
    rt_size_t (*ep_write)(struct uendpoint* ep, void *buffer, rt_size_t size);
    rt_err_t (*send_status)(void);
};

struct udcd
{
    struct rt_device parent;
    struct udcd_ops* ops;
    struct rt_completion completion;
};
typedef struct udcd* udcd_t;

typedef rt_err_t (*udep_handler_t)(struct udevice* device, struct uclass* cls, rt_size_t size);

struct uendpoint
{
    rt_list_t list;
    rt_uint8_t* buffer;
    uep_desc_t ep_desc;
    udep_handler_t handler;
    rt_bool_t is_stall;
};
typedef struct uendpoint* uep_t;

struct ualtsetting
{
    rt_list_t list;
    uintf_desc_t intf_desc;
    void* desc;
    rt_size_t desc_size;
    rt_list_t ep_list;
};
typedef struct ualtsetting* ualtsetting_t;

typedef rt_err_t (*uintf_handler_t)(struct udevice* device, struct uclass* cls, ureq_t setup);

struct uinterface
{
    rt_list_t list;
    rt_uint8_t intf_num;
    ualtsetting_t curr_setting;
    rt_list_t setting_list;
    uintf_handler_t handler;
};
typedef struct uinterface* uintf_t;

struct uclass_ops
{
    rt_err_t (*run)(struct udevice* device, struct uclass* cls);
    rt_err_t (*stop)(struct udevice* device, struct uclass* cls);
    rt_err_t (*sof_handler)(struct udevice* device, struct uclass* cls);
};
typedef struct uclass_ops* uclass_ops_t;

struct uclass
{
    rt_list_t list;
    uclass_ops_t ops;
    void* eps;
    struct udevice* device;
    udev_desc_t dev_desc;
    void* user_data;

    rt_list_t intf_list;
};
typedef struct uclass* uclass_t;

struct uconfig
{
    rt_list_t list;
    struct uconfig_descriptor cfg_desc;
    rt_list_t cls_list;
};
typedef struct uconfig* uconfig_t;

struct udevice
{
    rt_list_t list;
    struct udevice_descriptor dev_desc;
    const char** str;

    udevice_state_t state;
    rt_list_t cfg_list;
    uconfig_t curr_cfg;
    rt_uint8_t nr_intf;

    udcd_t dcd;
};
typedef struct udevice* udevice_t;

enum udev_msg_type
{
    USB_MSG_SETUP_NOTIFY,
    USB_MSG_DATA_NOTIFY,
    USB_MSG_SOF,
    USB_MSG_RESET,
    /* we don't need to add a "PLUG_IN" event because after the cable is
     * plugged in(before any SETUP) the classed have nothing to do. If the host
     * is ready, it will send RESET and we will have USB_MSG_RESET. So, a RESET
     * should reset and run the class while plug_in is not. */
    USB_MSG_PLUG_OUT,
};
typedef enum udev_msg_type udev_msg_type;

struct udev_msg
{
    udev_msg_type type;
    udcd_t dcd;
    union
    {
        struct
        {
            rt_size_t size;
            rt_uint8_t ep_addr;
        } ep_msg;
        struct
        {
            rt_uint32_t* packet;
        } setup_msg;
    } content;
};
typedef struct udev_msg* udev_msg_t;

udevice_t rt_usbd_device_create(void);
uconfig_t rt_usbd_config_create(void);
uclass_t rt_usbd_class_create(udevice_t    device,
                              udev_desc_t  dev_desc,
                              uclass_ops_t ops);
uintf_t rt_usbd_interface_create(udevice_t device, uintf_handler_t handler);
uep_t rt_usbd_endpoint_create(uep_desc_t ep_desc, udep_handler_t handler);
ualtsetting_t rt_usbd_altsetting_create(rt_size_t desc_size);

rt_err_t rt_usbd_core_init(void);
rt_err_t rt_usb_device_init(const char *udc_name);
rt_err_t rt_usbd_post_event(struct udev_msg *msg, rt_size_t size);
rt_err_t rt_usbd_free_device(udevice_t device);
rt_err_t rt_usbd_device_set_controller(udevice_t device, udcd_t dcd);
rt_err_t rt_usbd_device_set_descriptor(udevice_t device, udev_desc_t dev_desc);
rt_err_t rt_usbd_device_set_string(udevice_t device, const char** ustring);
rt_err_t rt_usbd_device_add_config(udevice_t device, uconfig_t cfg);
rt_err_t rt_usbd_config_add_class(uconfig_t cfg, uclass_t cls);
rt_err_t rt_usbd_class_add_interface(uclass_t cls, uintf_t intf);
rt_err_t rt_usbd_interface_add_altsetting(uintf_t intf, ualtsetting_t setting);
rt_err_t rt_usbd_altsetting_add_endpoint(ualtsetting_t setting, uep_t ep);
rt_err_t rt_usbd_altsetting_config_descriptor(ualtsetting_t setting,
                                              const void   *desc,
                                              rt_off_t      intf_pos);
rt_err_t rt_usbd_set_config(udevice_t device, rt_uint8_t value);
rt_err_t rt_usbd_set_altsetting(uintf_t intf, rt_uint8_t value);

udevice_t rt_usbd_find_device(udcd_t dcd);
uconfig_t rt_usbd_find_config(udevice_t device, rt_uint8_t value);
uintf_t rt_usbd_find_interface(udevice_t  device,
                               rt_uint8_t value,
                               uclass_t  *pcls);
uep_t rt_usbd_find_endpoint(udevice_t  device,
                            uclass_t  *pcls,
                            rt_uint8_t ep_addr);

uclass_t rt_usbd_class_mstorage_create(udevice_t device);
uclass_t rt_usbd_class_cdc_create(udevice_t device);
uclass_t rt_usbd_class_rndis_create(udevice_t device);
uclass_t rt_usbd_class_dap_create(udevice_t device);

#ifdef RT_USB_DEVICE_COMPOSITE
rt_err_t rt_usbd_class_set_iad(uclass_t cls, uiad_desc_t iad_desc);
#endif

rt_inline rt_err_t dcd_set_address(udcd_t dcd, rt_uint8_t value)
{
    RT_ASSERT(dcd != RT_NULL);

    return dcd->ops->set_address(value);
}

rt_inline rt_err_t dcd_clear_feature(udcd_t      dcd,
                                     rt_uint16_t value,
                                     rt_uint16_t index)
{
    RT_ASSERT(dcd != RT_NULL);

    return dcd->ops->clear_feature(value, index);
}

rt_inline rt_err_t dcd_set_feature(udcd_t      dcd,
                                   rt_uint8_t  value,
                                   rt_uint16_t index)
{
    RT_ASSERT(dcd != RT_NULL);

    return dcd->ops->set_feature(value, index);
}

rt_inline rt_err_t dcd_ep_stall(udcd_t dcd, uep_t ep)
{
    RT_ASSERT(dcd != RT_NULL);

    return dcd->ops->ep_stall(ep);
}

rt_inline rt_uint8_t dcd_ep_alloc(udcd_t dcd, uep_t ep)
{
    RT_ASSERT(dcd != RT_NULL);

    return dcd->ops->ep_alloc(ep);
}

rt_inline rt_err_t dcd_ep_free(udcd_t dcd, uep_t ep)
{
    RT_ASSERT(dcd != RT_NULL);

    return dcd->ops->ep_free(ep);
}

rt_inline rt_err_t dcd_ep_run(udcd_t dcd, uep_t ep)
{
    RT_ASSERT(dcd != RT_NULL);

    return dcd->ops->ep_run(ep);
}

rt_inline rt_err_t dcd_ep_stop(udcd_t dcd, uep_t ep)
{
    RT_ASSERT(dcd != RT_NULL);

    return dcd->ops->ep_stop(ep);
}

rt_inline rt_err_t dcd_ep_read(udcd_t dcd, uep_t ep, void *buffer,
                               rt_size_t size)
{
    RT_ASSERT(dcd != RT_NULL);

    return dcd->ops->ep_read(ep, buffer, size);
}

rt_inline rt_size_t dcd_ep_write(udcd_t    dcd,
                                 uep_t     ep,
                                 void     *buffer,
                                 rt_size_t size)
{
    RT_ASSERT(dcd != RT_NULL);

    return dcd->ops->ep_write(ep, buffer, size);
}

rt_inline rt_err_t dcd_send_status(udcd_t dcd)
{
    RT_ASSERT(dcd != RT_NULL);

    return dcd->ops->send_status();
}

#endif
