/*
 * File      : winusb.h
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
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


struct winusb_os_header_properties_descriptor
{
    rt_uint32_t dwLength;
    rt_uint16_t bcdVersion;
    rt_uint16_t wIndex;
    rt_uint16_t bCount;
};
typedef struct winusb_os_header_properties_descriptor * winusb_os_header_prop_desc_t;





#endif
