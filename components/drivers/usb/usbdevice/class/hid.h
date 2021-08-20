/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-03-13     Urey         the first version
 * 2017-11-16     ZYH          Update to common hid
 */
#ifndef _USBDEVICE_CLASS_HID_H_
#define _USBDEVICE_CLASS_HID_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <uapi/usb/hid.h>

#define MAX_REPORT_SIZE             64
#define HID_RX_BUFSIZE              64

#define HID_REPORT_ID_KEYBOARD1         1
#define HID_REPORT_ID_KEYBOARD2         2
#define HID_REPORT_ID_KEYBOARD3         3
#define HID_REPORT_ID_KEYBOARD4         7
#define HID_REPORT_ID_MEDIA             4
#define HID_REPORT_ID_GENERAL           5
#define HID_REPORT_ID_MOUSE             6


struct uhid_comm_descriptor
{
#ifdef RT_USB_DEVICE_COMPOSITE
    struct usb_interface_assoc_descriptor iad_desc;
#endif
    struct usb_interface_descriptor    intf_desc;
    struct usb_hid_descriptor       hid_desc;
    struct usb_endpoint_descriptor     ep_in_desc;
    struct usb_endpoint_descriptor     ep_out_desc;
};
typedef struct uhid_comm_descriptor* uhid_comm_desc_t;


#ifdef __cplusplus
}
#endif

#endif /* _USBDEVICE_CLASS_HID_H_ */
