/*
 * File      : hid.h
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017Äê3ÔÂ13ÈÕ     Urey         the first version
 */
#ifndef _USBDEVICE_CLASS_HID_H_
#define _USBDEVICE_CLASS_HID_H_

#ifdef __cplusplus
extern "C" {
#endif

#define HID_DESCRIPTOR_TYPE             0x21
#define HID_DESCRIPTOR_SIZE             0x09
#define HID_OFF_HID_DESC                0x12

#define USB_HID_SUBCLASS_BOOT           0x01
#define USB_HID_SUBCLASS_NOBOOT         0x00

#define USB_HID_PROTOCOL_NONE           0x00
#define USB_HID_PROTOCOL_KEYBOARD       0x01
#define USB_HID_PROTOCOL_MOUSE          0x02


#define USB_HID_REQ_GET_REPORT      0x01
#define USB_HID_REQ_GET_IDLE        0x02
#define USB_HID_REQ_GET_PROTOCOL    0x03
#define USB_HID_REQ_SET_REPORT      0x09
#define USB_HID_REQ_SET_IDLE        0x0a
#define USB_HID_REQ_SET_PROTOCOL    0x0b

#define MAX_REPORT_SIZE             8
#define HID_RX_BUFSIZE              64

struct uhid_comm_descriptor
{
#ifdef RT_USB_DEVICE_COMPOSITE
    struct uiad_descriptor iad_desc;
#endif
    struct uinterface_descriptor    intf_desc;
    struct uhid_descriptor          hid_desc;
    struct uendpoint_descriptor     ep_in_desc;
    struct uendpoint_descriptor     ep_out_desc;
};
typedef struct uhid_comm_descriptor* uhid_comm_desc_t;


#ifdef __cplusplus
}
#endif

#endif /* _USBDEVICE_CLASS_HID_H_ */
