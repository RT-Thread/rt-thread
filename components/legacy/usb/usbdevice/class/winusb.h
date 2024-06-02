/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
    struct uiad_descriptor iad_desc;
#endif
    struct uinterface_descriptor intf_desc;
    struct uendpoint_descriptor ep_out_desc;
    struct uendpoint_descriptor ep_in_desc;
};
typedef struct winusb_descriptor* winusb_desc_t;

#endif
