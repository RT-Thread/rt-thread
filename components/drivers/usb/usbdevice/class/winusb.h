/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-16     ZYH          first version
 */
#ifndef __WINUSB_H__
#define __WINUSB_H__
#include <rtthread.h>
struct winusb_descriptor
{
#ifdef RT_USB_DEVICE_COMPOSITE
    struct usb_interface_assoc_descriptor iad_desc;
#endif
    struct usb_interface_descriptor intf_desc;
    struct usb_endpoint_descriptor ep_out_desc;
    struct usb_endpoint_descriptor ep_in_desc;
};
typedef struct winusb_descriptor* winusb_desc_t;

#endif
