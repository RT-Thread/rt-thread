/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-01     Yi Qiu       first version
 * 2012-12-12     heyuanjie87  change endpoint and function handler
 * 2013-04-26     aozima       add DEVICEQUALIFIER support.
 * 2017-11-15     ZYH          fix ep0 transform error
 */

#ifndef  __USB_DEVICE_H__
#define  __USB_DEVICE_H__

#include <rtthread.h>
#include "drivers/usb_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Vendor ID */
#ifdef USB_VENDOR_ID
#define _VENDOR_ID                  USB_VENDOR_ID
#else
#define _VENDOR_ID                  0x0EFF
#endif
/* Product ID */
#ifdef USB_PRODUCT_ID
#define _PRODUCT_ID                 USB_PRODUCT_ID
#else
#define _PRODUCT_ID                 0x0001
#endif

#ifndef MAX_INTF_STR
#define MAX_INTF_STR 20
#endif

#define USB_BCD_DEVICE              0x0200   /* USB Specification Release Number in Binary-Coded Decimal */
#define USB_BCD_VERSION             0x0200   /* USB 2.0 */
#define EP0_IN_ADDR                 0x80
#define EP0_OUT_ADDR                0x00
#define EP_HANDLER(ep, func, size)  RT_ASSERT(ep != RT_NULL); ep->handler(func, size)
#define EP_ADDRESS(ep)              ep->ep_desc->bEndpointAddress
#define EP_MAXPACKET(ep)            ep->ep_desc->wMaxPacketSize
#define FUNC_ENABLE(func)           do{                                             \
                                        if(func->ops->enable != RT_NULL &&          \
                                            func->enabled == RT_FALSE)              \
                                        {                                           \
                                            if(func->ops->enable(func) == RT_EOK)   \
                                                func->enabled = RT_TRUE;            \
                                        }                                           \
                                    }while(0)
#define FUNC_DISABLE(func)          do{                                             \
                                        if(func->ops->disable != RT_NULL &&         \
                                            func->enabled == RT_TRUE)               \
                                        {                                           \
                                                func->enabled = RT_FALSE;           \
                                                func->ops->disable(func);           \
                                        }                                           \
                                    }while(0)

struct ufunction;
struct udevice;
struct uendpoint;

typedef enum
{
    /* request to read full count */
    UIO_REQUEST_READ_FULL,
    /* request to read any count */
    UIO_REQUEST_READ_BEST,
    /* request to write full count */
    UIO_REQUEST_WRITE,
}UIO_REQUEST_TYPE;

struct udcd_ops
{
    rt_err_t (*set_address)(rt_uint8_t address);
    rt_err_t (*set_config)(rt_uint8_t address);
    rt_err_t (*ep_set_stall)(rt_uint8_t address);
    rt_err_t (*ep_clear_stall)(rt_uint8_t address);
    rt_err_t (*ep_enable)(struct uendpoint* ep);
    rt_err_t (*ep_disable)(struct uendpoint* ep);
    rt_size_t (*ep_read_prepare)(rt_uint8_t address, void *buffer, rt_size_t size);
    rt_size_t (*ep_read)(rt_uint8_t address, void *buffer);
    rt_size_t (*ep_write)(rt_uint8_t address, void *buffer, rt_size_t size);
    rt_err_t (*ep0_send_status)(void);
    rt_err_t (*suspend)(void);
    rt_err_t (*wakeup)(void);
};

struct ep_id
{
    rt_uint8_t  addr;
    rt_uint8_t  type;
    rt_uint8_t  dir;
    rt_uint16_t maxpacket;
    rt_uint8_t  status;
};

typedef rt_err_t (*udep_handler_t)(struct ufunction* func, rt_size_t size);

struct uio_request
{
    rt_list_t list;
    UIO_REQUEST_TYPE req_type;
    rt_uint8_t* buffer;
    rt_size_t size;
    rt_size_t remain_size;
};
typedef struct uio_request* uio_request_t;

struct uendpoint
{
    rt_list_t list;
    uep_desc_t ep_desc;
    rt_list_t request_list;
    struct uio_request request;
    rt_uint8_t* buffer;
    rt_bool_t stalled;
    struct ep_id* id;
    udep_handler_t handler;
    rt_err_t (*rx_indicate)(struct udevice* dev, rt_size_t size);
};
typedef struct uendpoint* uep_t;

struct udcd
{
    struct rt_device parent;
    const struct udcd_ops* ops;
    struct uendpoint ep0;
    uep0_stage_t stage;
    struct ep_id* ep_pool;
    rt_uint8_t device_is_hs;
};
typedef struct udcd* udcd_t;

struct ualtsetting
{
    rt_list_t list;
    uintf_desc_t intf_desc;
    void* desc;
    rt_size_t desc_size;
    rt_list_t ep_list;
};
typedef struct ualtsetting* ualtsetting_t;

typedef rt_err_t (*uintf_handler_t)(struct ufunction* func, ureq_t setup);

struct uinterface
{
    rt_list_t list;
    rt_uint8_t intf_num;
    ualtsetting_t curr_setting;
    rt_list_t setting_list;
    uintf_handler_t handler;
};
typedef struct uinterface* uintf_t;

struct ufunction_ops
{
    rt_err_t (*enable)(struct ufunction* func);
    rt_err_t (*disable)(struct ufunction* func);
    rt_err_t (*sof_handler)(struct ufunction* func);
};
typedef struct ufunction_ops* ufunction_ops_t;

struct ufunction
{
    rt_list_t list;
    ufunction_ops_t ops;
    struct udevice* device;
    udev_desc_t dev_desc;
    void* user_data;
    rt_bool_t enabled;

    rt_list_t intf_list;
};
typedef struct ufunction* ufunction_t;

struct uconfig
{
    rt_list_t list;
    struct uconfig_descriptor cfg_desc;
    rt_list_t func_list;
};
typedef struct uconfig* uconfig_t;

struct udevice
{
    rt_list_t list;
    struct udevice_descriptor dev_desc;

    struct usb_qualifier_descriptor * dev_qualifier;
    usb_os_comp_id_desc_t    os_comp_id_desc;
    const char** str;
    const char *str_intf[MAX_INTF_STR];
    udevice_state_t state;
    rt_list_t cfg_list;
    uconfig_t curr_cfg;
    rt_uint8_t nr_intf;

    udcd_t dcd;
};
typedef struct udevice* udevice_t;

struct udclass
{
    rt_list_t list;
    ufunction_t (*rt_usbd_function_create)(udevice_t device);
};
typedef struct udclass* udclass_t;

enum udev_msg_type
{
    USB_MSG_SETUP_NOTIFY,
    USB_MSG_DATA_NOTIFY,
    USB_MSG_EP0_OUT,
    USB_MSG_EP_CLEAR_FEATURE,
    USB_MSG_SOF,
    USB_MSG_RESET,
    USB_MSG_PLUG_IN,
    /* we don't need to add a "PLUG_IN" event because after the cable is
     * plugged in(before any SETUP) the classed have nothing to do. If the host
     * is ready, it will send RESET and we will have USB_MSG_RESET. So, a RESET
     * should reset and run the class while plug_in is not. */
    USB_MSG_PLUG_OUT,
};
typedef enum udev_msg_type udev_msg_type;

struct ep_msg
{
    rt_size_t size;
    rt_uint8_t ep_addr;
};

struct udev_msg
{
    udev_msg_type type;
    udcd_t dcd;
    union
    {
        struct ep_msg   ep_msg;
        struct urequest setup;
    } content;
};
typedef struct udev_msg* udev_msg_t;

int rt_usbd_class_list_init(void);
udevice_t rt_usbd_device_new(void);
uconfig_t rt_usbd_config_new(void);
ufunction_t rt_usbd_function_new(udevice_t device, udev_desc_t dev_desc,
                              ufunction_ops_t ops);
uintf_t rt_usbd_interface_new(udevice_t device, uintf_handler_t handler);
uep_t rt_usbd_endpoint_new(uep_desc_t ep_desc, udep_handler_t handler);
ualtsetting_t rt_usbd_altsetting_new(rt_size_t desc_size);

rt_err_t rt_usbd_core_init(void);
rt_err_t rt_usb_device_init(void);
rt_err_t rt_usbd_event_signal(struct udev_msg* msg);
rt_err_t rt_usbd_device_set_controller(udevice_t device, udcd_t dcd);
rt_err_t rt_usbd_device_set_descriptor(udevice_t device, udev_desc_t dev_desc);
rt_err_t rt_usbd_device_set_string(udevice_t device, const char** ustring);
rt_err_t rt_usbd_device_set_interface_string(udevice_t device, int index, const char* string);
rt_err_t rt_usbd_device_set_qualifier(udevice_t device, struct usb_qualifier_descriptor* qualifier);
rt_err_t rt_usbd_device_set_os_comp_id_desc(udevice_t device, usb_os_comp_id_desc_t os_comp_id_desc);
rt_err_t rt_usbd_device_add_config(udevice_t device, uconfig_t cfg);
rt_err_t rt_usbd_config_add_function(uconfig_t cfg, ufunction_t func);
rt_err_t rt_usbd_class_register(udclass_t udclass);
rt_err_t rt_usbd_function_add_interface(ufunction_t func, uintf_t intf);
rt_err_t rt_usbd_interface_add_altsetting(uintf_t intf, ualtsetting_t setting);
rt_err_t rt_usbd_altsetting_add_endpoint(ualtsetting_t setting, uep_t ep);
rt_err_t rt_usbd_os_comp_id_desc_add_os_func_comp_id_desc(usb_os_comp_id_desc_t os_comp_id_desc, usb_os_func_comp_id_desc_t os_func_comp_id_desc);
rt_err_t rt_usbd_altsetting_config_descriptor(ualtsetting_t setting, const void* desc, rt_off_t intf_pos);
rt_err_t rt_usbd_set_config(udevice_t device, rt_uint8_t value);
rt_err_t rt_usbd_set_altsetting(uintf_t intf, rt_uint8_t value);

udevice_t rt_usbd_find_device(udcd_t dcd);
uconfig_t rt_usbd_find_config(udevice_t device, rt_uint8_t value);
uintf_t rt_usbd_find_interface(udevice_t device, rt_uint8_t value, ufunction_t *pfunc);
uep_t rt_usbd_find_endpoint(udevice_t device, ufunction_t* pfunc, rt_uint8_t ep_addr);
rt_size_t rt_usbd_io_request(udevice_t device, uep_t ep, uio_request_t req);
rt_size_t rt_usbd_ep0_write(udevice_t device, void *buffer, rt_size_t size);
rt_size_t rt_usbd_ep0_read(udevice_t device, void *buffer, rt_size_t size,
    rt_err_t (*rx_ind)(udevice_t device, rt_size_t size));

int rt_usbd_vcom_class_register(void);
int rt_usbd_ecm_class_register(void);
int rt_usbd_hid_class_register(void);
int rt_usbd_msc_class_register(void);
int rt_usbd_rndis_class_register(void);
int rt_usbd_winusb_class_register(void);

#ifdef RT_USB_DEVICE_COMPOSITE
rt_err_t rt_usbd_function_set_iad(ufunction_t func, uiad_desc_t iad_desc);
#endif

rt_err_t rt_usbd_set_feature(udevice_t device, rt_uint16_t value, rt_uint16_t index);
rt_err_t rt_usbd_clear_feature(udevice_t device, rt_uint16_t value, rt_uint16_t index);
rt_err_t rt_usbd_ep_set_stall(udevice_t device, uep_t ep);
rt_err_t rt_usbd_ep_clear_stall(udevice_t device, uep_t ep);
rt_err_t rt_usbd_ep0_set_stall(udevice_t device);
rt_err_t rt_usbd_ep0_clear_stall(udevice_t device);
rt_err_t rt_usbd_ep0_setup_handler(udcd_t dcd, struct urequest* setup);
rt_err_t rt_usbd_ep0_in_handler(udcd_t dcd);
rt_err_t rt_usbd_ep0_out_handler(udcd_t dcd, rt_size_t size);
rt_err_t rt_usbd_ep_in_handler(udcd_t dcd, rt_uint8_t address, rt_size_t size);
rt_err_t rt_usbd_ep_out_handler(udcd_t dcd, rt_uint8_t address, rt_size_t size);
rt_err_t rt_usbd_reset_handler(udcd_t dcd);
rt_err_t rt_usbd_connect_handler(udcd_t dcd);
rt_err_t rt_usbd_disconnect_handler(udcd_t dcd);
rt_err_t rt_usbd_sof_handler(udcd_t dcd);

rt_inline rt_err_t dcd_set_address(udcd_t dcd, rt_uint8_t address)
{
    RT_ASSERT(dcd != RT_NULL);
    RT_ASSERT(dcd->ops != RT_NULL);
    RT_ASSERT(dcd->ops->set_address != RT_NULL);

    return dcd->ops->set_address(address);
}

rt_inline rt_err_t dcd_set_config(udcd_t dcd, rt_uint8_t address)
{
    RT_ASSERT(dcd != RT_NULL);
    RT_ASSERT(dcd->ops != RT_NULL);
    RT_ASSERT(dcd->ops->set_config != RT_NULL);

    return dcd->ops->set_config(address);
}

rt_inline rt_err_t dcd_ep_enable(udcd_t dcd, uep_t ep)
{
    RT_ASSERT(dcd != RT_NULL);
    RT_ASSERT(dcd->ops != RT_NULL);
    RT_ASSERT(dcd->ops->ep_enable != RT_NULL);

    return dcd->ops->ep_enable(ep);
}

rt_inline rt_err_t dcd_ep_disable(udcd_t dcd, uep_t ep)
{
    RT_ASSERT(dcd != RT_NULL);
    RT_ASSERT(dcd->ops != RT_NULL);
    RT_ASSERT(dcd->ops->ep_disable != RT_NULL);

    return dcd->ops->ep_disable(ep);
}

rt_inline rt_size_t dcd_ep_read_prepare(udcd_t dcd, rt_uint8_t address, void *buffer,
                               rt_size_t size)
{
    RT_ASSERT(dcd != RT_NULL);
    RT_ASSERT(dcd->ops != RT_NULL);

    if(dcd->ops->ep_read_prepare != RT_NULL)
    {
        return dcd->ops->ep_read_prepare(address, buffer, size);
    }
    else
    {
        return 0;
    }
}

rt_inline rt_size_t dcd_ep_read(udcd_t dcd, rt_uint8_t address, void *buffer)
{
    RT_ASSERT(dcd != RT_NULL);
    RT_ASSERT(dcd->ops != RT_NULL);

    if(dcd->ops->ep_read != RT_NULL)
    {
        return dcd->ops->ep_read(address, buffer);
    }
    else
    {
        return 0;
    }
}

rt_inline rt_size_t dcd_ep_write(udcd_t dcd, rt_uint8_t address, void *buffer,
                                 rt_size_t size)
{
    RT_ASSERT(dcd != RT_NULL);
    RT_ASSERT(dcd->ops != RT_NULL);
    RT_ASSERT(dcd->ops->ep_write != RT_NULL);

    return dcd->ops->ep_write(address, buffer, size);
}

rt_inline rt_err_t dcd_ep0_send_status(udcd_t dcd)
{
    RT_ASSERT(dcd != RT_NULL);
    RT_ASSERT(dcd->ops != RT_NULL);
    RT_ASSERT(dcd->ops->ep0_send_status != RT_NULL);

    return dcd->ops->ep0_send_status();
}

rt_inline rt_err_t dcd_ep_set_stall(udcd_t dcd, rt_uint8_t address)
{
    RT_ASSERT(dcd != RT_NULL);
    RT_ASSERT(dcd->ops != RT_NULL);
    RT_ASSERT(dcd->ops->ep_set_stall != RT_NULL);

    return dcd->ops->ep_set_stall(address);
}

rt_inline rt_err_t dcd_ep_clear_stall(udcd_t dcd, rt_uint8_t address)
{
    RT_ASSERT(dcd != RT_NULL);
    RT_ASSERT(dcd->ops != RT_NULL);
    RT_ASSERT(dcd->ops->ep_clear_stall != RT_NULL);

    return dcd->ops->ep_clear_stall(address);
}
rt_inline void usbd_os_proerty_descriptor_send(ufunction_t func, ureq_t setup, usb_os_proerty_t usb_os_proerty, rt_uint8_t number_of_proerty)
{
    struct usb_os_property_header header;
    static rt_uint8_t * data;
    rt_uint8_t * pdata;
    rt_uint8_t index,i;
    if(data == RT_NULL)
    {
        header.dwLength = sizeof(struct usb_os_property_header);
        header.bcdVersion = 0x0100;
        header.wIndex = 0x05;
        header.wCount = number_of_proerty;
        for(index = 0;index < number_of_proerty;index++)
        {
            header.dwLength += usb_os_proerty[index].dwSize;
        }
        data = (rt_uint8_t *)rt_malloc(header.dwLength);
        RT_ASSERT(data != RT_NULL);
        pdata = data;
        rt_memcpy((void *)pdata,(void *)&header,sizeof(struct usb_os_property_header));
        pdata += sizeof(struct usb_os_property_header);
        for(index = 0;index < number_of_proerty;index++)
        {
            rt_memcpy((void *)pdata,(void *)&usb_os_proerty[index],10);
            pdata += 10;
            for(i = 0;i < usb_os_proerty[index].wPropertyNameLength/2;i++)
            {
                *pdata = usb_os_proerty[index].bPropertyName[i];
                pdata++;
                *pdata = 0;
                pdata++;
            }
            *((rt_uint32_t *)pdata) = usb_os_proerty[index].dwPropertyDataLength;
            pdata += 4;
            for(i = 0;i < usb_os_proerty[index].dwPropertyDataLength/2;i++)
            {
                *pdata = usb_os_proerty[index].bPropertyData[i];
                pdata++;
                *pdata = 0;
                pdata++;
            }
        }
    }
    rt_usbd_ep0_write(func->device, data, setup->wLength);
}

#ifdef __cplusplus
}
#endif

#endif
