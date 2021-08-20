/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     zyh          the first version
 */

#ifndef __UAPI_USB_HID_H__
#define __UAPI_USB_HID_H__

#include <rtdef.h>

/*
 * USB HID (Human Interface Device) interface class code
 */

#define USB_INTERFACE_CLASS_HID             (3U)

/*
 * USB HID interface subclass and protocol codes
 */

#define USB_INTERFACE_SUBCLASS_BOOT         (0x01U)
#define USB_INTERFACE_PROTOCOL_KEYBOARD     (0x01U)
#define USB_INTERFACE_PROTOCOL_MOUSE        (0x02U)

/*
 * HID class requests
 */

#define HID_REQ_GET_REPORT                  (0x01U)
#define HID_REQ_GET_IDLE                    (0x02U)
#define HID_REQ_GET_PROTOCOL                (0x03U)
#define HID_REQ_SET_REPORT                  (0x09U)
#define HID_REQ_SET_IDLE                    (0x0AU)
#define HID_REQ_SET_PROTOCOL                (0x0BU)

/*
 * HID class descriptor types
 */

#define HID_DT_HID                          (USB_TYPE_CLASS | 0x01)
#define HID_DT_REPORT                       (USB_TYPE_CLASS | 0x02)
#define HID_DT_PHYSICAL                     (USB_TYPE_CLASS | 0x03)

#ifndef HID_SUB_DESCRIPTOR_MAX
#define  HID_SUB_DESCRIPTOR_MAX        1
#endif

struct usb_hid_descriptor
{
    rt_uint8_t  bLength;
    rt_uint8_t  type;
    rt_le16_t   bcdHID;
    rt_uint8_t  bCountryCode;
    rt_uint8_t  bNumDescriptors;
    struct hid_descriptor_list
    {
        rt_uint8_t  type;
        rt_le16_t   wLength;
    }Descriptor[HID_SUB_DESCRIPTOR_MAX];
} __attribute__ ((packed));

#define HID_DT_HID_SIZE                         (sizeof(struct usb_hid_descriptor))

#define HID_MAX_DESCRIPTOR_SIZE             (4096U)

/* HID Report Items */

/* HID Report Types */
#define HID_REPORT_INPUT                    (0x01U)
#define HID_REPORT_OUTPUT                   (0x02U)
#define HID_REPORT_FEATURE                  (0x03U)

/* Usage Pages */
#define USAGEPAGE_UNDEFINED                 (0x00U)
#define USAGEPAGE_GENERIC                   (0x01U)
#define USAGEPAGE_SIMULATION                (0x02U)
#define USAGEPAGE_VR                        (0x03U)
#define USAGEPAGE_SPORT                     (0x04U)
#define USAGEPAGE_GAME                      (0x05U)
#define USAGEPAGE_DEV_CONTROLS              (0x06U)
#define USAGEPAGE_KEYBOARD                  (0x07U)
#define USAGEPAGE_LED                       (0x08U)
#define USAGEPAGE_BUTTON                    (0x09U)
#define USAGEPAGE_ORDINAL                   (0x0AU)
#define USAGEPAGE_TELEPHONY                 (0x0BU)
#define USAGEPAGE_CONSUMER                  (0x0CU)
#define USAGEPAGE_DIGITIZER                 (0x0DU)
#define USAGEPAGE_PIDPAGE                   (0x0FU)
#define USAGEPAGE_UNICODE                   (0x10U)
#define USAGEPAGE_ALPHANUMERIC              (0x14U)
#define USAGEPAGE_BARCODESCANNER            (0x8CU)

/* Generic Desktop Page (0x01) */
#define USAGE_GENERIC_POINTER               (0x01U)
#define USAGE_GENERIC_MOUSE                 (0x02U)
#define USAGE_GENERIC_JOYSTICK              (0x04U)
#define USAGE_GENERIC_GAMEPAD               (0x05U)
#define USAGE_GENERIC_KEYBOARD              (0x06U)
#define USAGE_GENERIC_KEYPAD                (0x07U)
#define USAGE_GENERIC_X                     (0x30U)
#define USAGE_GENERIC_Y                     (0x31U)
#define USAGE_GENERIC_Z                     (0x32U)
#define USAGE_GENERIC_RX                    (0x33U)
#define USAGE_GENERIC_RY                    (0x34U)
#define USAGE_GENERIC_RZ                    (0x35U)
#define USAGE_GENERIC_SLIDER                (0x36U)
#define USAGE_GENERIC_DIAL                  (0x37U)
#define USAGE_GENERIC_WHEEL                 (0x38U)
#define USAGE_GENERIC_HATSWITCH             (0x39U)
#define USAGE_GENERIC_COUNTED_BUFFER        (0x3AU)
#define USAGE_GENERIC_BYTE_COUNT            (0x3BU)
#define USAGE_GENERIC_MOTION_WAKEUP         (0x3CU)
#define USAGE_GENERIC_VX                    (0x40U)
#define USAGE_GENERIC_VY                    (0x41U)
#define USAGE_GENERIC_VZ                    (0x42U)
#define USAGE_GENERIC_VBRX                  (0x43U)
#define USAGE_GENERIC_VBRY                  (0x44U)
#define USAGE_GENERIC_VBRZ                  (0x45U)
#define USAGE_GENERIC_VNO                   (0x46U)
#define USAGE_GENERIC_SYSTEM_CTL            (0x80U)
#define USAGE_GENERIC_SYSCTL_POWER          (0x81U)
#define USAGE_GENERIC_SYSCTL_SLEEP          (0x82U)
#define USAGE_GENERIC_SYSCTL_WAKE           (0x83U)
#define USAGE_GENERIC_SYSCTL_CONTEXT_MENU   (0x84U)
#define USAGE_GENERIC_SYSCTL_MAIN_MENU      (0x85U)
#define USAGE_GENERIC_SYSCTL_APP_MENU       (0x86U)
#define USAGE_GENERIC_SYSCTL_HELP_MENU      (0x87U)
#define USAGE_GENERIC_SYSCTL_MENU_EXIT      (0x88U)
#define USAGE_GENERIC_SYSCTL_MENU_SELECT    (0x89U)
#define USAGE_GENERIC_SYSCTL_MENU_RIGHT     (0x8AU)
#define USAGE_GENERIC_SYSCTL_MENU_LEFT      (0x8BU)
#define USAGE_GENERIC_SYSCTL_MENU_UP        (0x8CU)
#define USAGE_GENERIC_SYSCTL_MENU_DOWN      (0x8DU)

/* Simulation Controls Page(0x02) */
#define USAGE_SIMCTRL_THROTTLE              (0xBBU)


/* Main Items */
#define HID_Input(x)            (0x81U),x
#define HID_Output(x)           (0x91U),x
#define HID_Feature(x)          (0xB1U),x
#define HID_Collection(x)       (0xA1U),x
#define HID_EndCollection()     (0xC0U)

/* Local Items */
#define HID_Usage(x)            (0x09U),x
#define HID_UsageMin(x)         (0x19U),x
#define HID_UsageMax(x)         (0x29U),x

/* Global Items */
#define HID_UsagePage(x)        (0x05U),x
#define HID_UsagePageVendor(x)  (0x06U),x,(0xFFU)
#define HID_LogicalMin(x)       (0x15U),x
#define HID_LogicalMinS(x)      (0x16U),(x&(0xFFU)),((x>>8)&(0xFFU))
#define HID_LogicalMinL(x)      (0x17U),(x&(0xFFU)),((x>>8)&(0xFFU)),((x>>16)&(0xFFU)),((x>>24)&(0xFFU))
#define HID_LogicalMax(x)       (0x25U),x
#define HID_LogicalMaxS(x)      (0x26U),(x&(0xFFU)),((x>>8)&(0xFFU))
#define HID_LogicalMaxL(x)      (0x27U),(x&(0xFFU)),((x>>8)&(0xFFU)),((x>>16)&(0xFFU)),((x>>24)&(0xFFU))
#define HID_PhysicalMin(x)      (0x35U),x
#define HID_PhysicalMinS(x)     (0x36U),(x&(0xFFU)),((x>>8)&(0xFFU))
#define HID_PhysicalMinL(x)     (0x37U),(x&(0xFFU)),((x>>8)&(0xFFU)),((x>>16)&(0xFFU)),((x>>24)&(0xFFU))
#define HID_PhysicalMax(x)      (0x45U),x
#define HID_PhysicalMaxS(x)     (0x46U),(x&(0xFFU)),((x>>8)&(0xFFU))
#define HID_PhysicalMaxL(x)     (0x47U),(x&(0xFFU)),((x>>8)&(0xFFU)),((x>>16)&(0xFFU)),((x>>24)&(0xFFU))
#define HID_UnitExponent(x)     (0x55U),x
#define HID_Unit(x)             (0x65U),x
#define HID_UnitS(x)            (0x66U),(x&(0xFFU)),((x>>8)&(0xFFU))
#define HID_UnitL(x)            (0x67U),(x&(0xFFU)),((x>>8)&(0xFFU)),((x>>16)&(0xFFU)),((x>>24)&(0xFFU))
#define HID_ReportSize(x)       (0x75U),x
#define HID_ReportSizeS(x)      (0x76U),(x&(0xFFU)),((x>>8)&(0xFFU)))
#define HID_ReportSizeL(x)      (0x77U),(x&(0xFFU)),((x>>8)&(0xFFU)),((x>>16)&(0xFFU)),((x>>24)&(0xFFU))
#define HID_ReportID(x)         (0x85U),x
#define HID_ReportCount(x)      (0x95U),x
#define HID_ReportCountS(x)     (0x96U),(x&(0xFFU)),((x>>8)&(0xFFU))
#define HID_ReportCountL(x)     (0x97U),(x&(0xFFU)),((x>>8)&(0xFFU)),((x>>16)&(0xFFU)),((x>>24)&(0xFFU))
#define HID_Push()              (0xA4U)
#define HID_Pop()               (0xB4U)

/* Input, Output, Feature Data */
#define HID_DATA                ((0x00U)<<0)
#define HID_CONST               ((0x01U)<<0)
#define HID_ARRAY               ((0x00U)<<1)
#define HID_VAR                 ((0x01U)<<1)
#define HID_ABS                 ((0x00U)<<2)
#define HID_REL                 ((0x01U)<<2)
#define HID_NOWRAP              ((0x00U)<<3)
#define HID_WRAP                ((0x01U)<<3)
#define HID_LINEAR              ((0x00U)<<4)
#define HID_NONLINEAR           ((0x01U)<<4)
#define HID_PREFERREDSTATE      ((0x00U)<<5)
#define HID_NOPREFERRED         ((0x01U)<<5)
#define HID_NONULLPOSITION      ((0x00U)<<6)
#define HID_NULLSTATE           ((0x01U)<<6)
#define HID_NONVOLATILE         ((0x00U)<<7)
#define HID_VOLATILE            ((0x01U)<<7)

/* Collection Data */
#define HID_PHYSICAL            (0x00U)
#define HID_APPLICATION         (0x01U)
#define HID_LOGICAL             (0x02U)
#define HID_REPORT              (0x03U)
#define HID_NAMEDARRAY          (0x04U)
#define HID_USAGESWITCH         (0x05U)
#define HID_USAGEMODIFIER       (0x06U)

#define HID_VERSION_1_11        (0x0111)

#endif /* __UAPI_USB_HID_H__ */
