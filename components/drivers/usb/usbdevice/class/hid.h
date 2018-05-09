/*
 * File      : hid.h
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
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

#define MAX_REPORT_SIZE             64
#define HID_RX_BUFSIZE              64

/* HID Report Types */
#define HID_REPORT_INPUT            0x01
#define HID_REPORT_OUTPUT           0x02
#define HID_REPORT_FEATURE          0x03

/* Usage Pages */
#define USAGEPAGE_UNDEFINED        0x00
#define USAGEPAGE_GENERIC          0x01
#define USAGEPAGE_SIMULATION       0x02
#define USAGEPAGE_VR               0x03
#define USAGEPAGE_SPORT            0x04
#define USAGEPAGE_GAME             0x05
#define USAGEPAGE_DEV_CONTROLS     0x06
#define USAGEPAGE_KEYBOARD         0x07
#define USAGEPAGE_LED              0x08
#define USAGEPAGE_BUTTON           0x09
#define USAGEPAGE_ORDINAL          0x0A
#define USAGEPAGE_TELEPHONY        0x0B
#define USAGEPAGE_CONSUMER         0x0C
#define USAGEPAGE_DIGITIZER        0x0D
#define USAGEPAGE_PIDPAGE          0x0F
#define USAGEPAGE_UNICODE          0x10
#define USAGEPAGE_ALPHANUMERIC     0x14
#define USAGEPAGE_BARCODESCANNER   0x8C

/* Generic Desktop Page (0x01) */
#define USAGE_GENERIC_POINTER               0x01
#define USAGE_GENERIC_MOUSE                 0x02
#define USAGE_GENERIC_JOYSTICK              0x04
#define USAGE_GENERIC_GAMEPAD               0x05
#define USAGE_GENERIC_KEYBOARD              0x06
#define USAGE_GENERIC_KEYPAD                0x07
#define USAGE_GENERIC_X                     0x30
#define USAGE_GENERIC_Y                     0x31
#define USAGE_GENERIC_Z                     0x32
#define USAGE_GENERIC_RX                    0x33
#define USAGE_GENERIC_RY                    0x34
#define USAGE_GENERIC_RZ                    0x35
#define USAGE_GENERIC_SLIDER                0x36
#define USAGE_GENERIC_DIAL                  0x37
#define USAGE_GENERIC_WHEEL                 0x38
#define USAGE_GENERIC_HATSWITCH             0x39
#define USAGE_GENERIC_COUNTED_BUFFER        0x3A
#define USAGE_GENERIC_BYTE_COUNT            0x3B
#define USAGE_GENERIC_MOTION_WAKEUP         0x3C
#define USAGE_GENERIC_VX                    0x40
#define USAGE_GENERIC_VY                    0x41
#define USAGE_GENERIC_VZ                    0x42
#define USAGE_GENERIC_VBRX                  0x43
#define USAGE_GENERIC_VBRY                  0x44
#define USAGE_GENERIC_VBRZ                  0x45
#define USAGE_GENERIC_VNO                   0x46
#define USAGE_GENERIC_SYSTEM_CTL            0x80
#define USAGE_GENERIC_SYSCTL_POWER          0x81
#define USAGE_GENERIC_SYSCTL_SLEEP          0x82
#define USAGE_GENERIC_SYSCTL_WAKE           0x83
#define USAGE_GENERIC_SYSCTL_CONTEXT_MENU   0x84
#define USAGE_GENERIC_SYSCTL_MAIN_MENU      0x85
#define USAGE_GENERIC_SYSCTL_APP_MENU       0x86
#define USAGE_GENERIC_SYSCTL_HELP_MENU      0x87
#define USAGE_GENERIC_SYSCTL_MENU_EXIT      0x88
#define USAGE_GENERIC_SYSCTL_MENU_SELECT    0x89
#define USAGE_GENERIC_SYSCTL_MENU_RIGHT     0x8A
#define USAGE_GENERIC_SYSCTL_MENU_LEFT      0x8B
#define USAGE_GENERIC_SYSCTL_MENU_UP        0x8C
#define USAGE_GENERIC_SYSCTL_MENU_DOWN      0x8D

/* Simulation Controls Page(0x02) */
#define USAGE_SIMCTRL_THROTTLE              0xBB

/* HID Report Items */

/* Main Items */
#define HID_Input(x)           0x81,x
#define HID_Output(x)          0x91,x
#define HID_Feature(x)         0xB1,x
#define HID_Collection(x)      0xA1,x
#define HID_EndCollection()    0xC0

/* Local Items */
#define HID_Usage(x)           0x09,x
#define HID_UsageMin(x)        0x19,x
#define HID_UsageMax(x)        0x29,x

/* Global Items */
#define HID_UsagePage(x)       0x05,x
#define HID_UsagePageVendor(x) 0x06,x,0xFF
#define HID_LogicalMin(x)      0x15,x
#define HID_LogicalMinS(x)     0x16,(x&0xFF),((x>>8)&0xFF)
#define HID_LogicalMinL(x)     0x17,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_LogicalMax(x)      0x25,x
#define HID_LogicalMaxS(x)     0x26,(x&0xFF),((x>>8)&0xFF)
#define HID_LogicalMaxL(x)     0x27,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_PhysicalMin(x)     0x35,x
#define HID_PhysicalMinS(x)    0x36,(x&0xFF),((x>>8)&0xFF)
#define HID_PhysicalMinL(x)    0x37,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_PhysicalMax(x)     0x45,x
#define HID_PhysicalMaxS(x)    0x46,(x&0xFF),((x>>8)&0xFF)
#define HID_PhysicalMaxL(x)    0x47,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_UnitExponent(x)    0x55,x
#define HID_Unit(x)            0x65,x
#define HID_UnitS(x)           0x66,(x&0xFF),((x>>8)&0xFF)
#define HID_UnitL(x)           0x67,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_ReportSize(x)      0x75,x
#define HID_ReportSizeS(x)     0x76,(x&0xFF),((x>>8)&0xFF))
#define HID_ReportSizeL(x)     0x77,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_ReportID(x)        0x85,x
#define HID_ReportCount(x)     0x95,x
#define HID_ReportCountS(x)    0x96,(x&0xFF),((x>>8)&0xFF)
#define HID_ReportCountL(x)    0x97,(x&0xFF),((x>>8)&0xFF),((x>>16)&0xFF),((x>>24)&0xFF)
#define HID_Push()             0xA4
#define HID_Pop()              0xB4

/* Input, Output, Feature Data */
#define HID_DATA               (0<<0)
#define HID_CONST              (1<<0)
#define HID_ARRAY              (0<<1)
#define HID_VAR                (1<<1)
#define HID_ABS                (0<<2)
#define HID_REL                (1<<2)
#define HID_NOWRAP             (0<<3)
#define HID_WRAP               (1<<3)
#define HID_LINEAR             (0<<4)
#define HID_NONLINEAR          (1<<4)
#define HID_PREFERREDSTATE     (0<<5)
#define HID_NOPREFERRED        (1<<5)
#define HID_NONULLPOSITION     (0<<6)
#define HID_NULLSTATE          (1<<6)
#define HID_NONVOLATILE        (0<<7)
#define HID_VOLATILE           (1<<7)

/* Collection Data */
#define HID_PHYSICAL           0x00
#define HID_APPLICATION        0x01
#define HID_LOGICAL            0x02
#define HID_REPORT             0x03
#define HID_NAMEDARRAY         0x04
#define HID_USAGESWITCH        0x05
#define HID_USAGEMODIFIER      0x06

//HID_MBED_DEFINE
#define HID_VERSION_1_11    (0x0111)

/* HID Class */
#define HID_CLASS             (3)
#define HID_SUBCLASS_NONE     (0)
#define HID_SUBCLASS_BOOT     (1)
#define HID_PROTOCOL_NONE     (0)
#define HID_PROTOCOL_KEYBOARD (1)
#define HID_PROTOCOL_MOUSE    (2)

/* Descriptors */
#define HID_DESCRIPTOR          (33)
#define HID_DESCRIPTOR_LENGTH   (0x09)
#define REPORT_DESCRIPTOR       (34)

/* Class requests */
#define GET_REPORT (0x1)
#define GET_IDLE   (0x2)
#define SET_REPORT (0x9)
#define SET_IDLE   (0xa)

/* HID Class Report Descriptor */
/* Short items: size is 0, 1, 2 or 3 specifying 0, 1, 2 or 4 (four) bytes */
/* of data as per HID Class standard */

/* Main items */
#define INPUT(size)             (0x80 | size)
#define OUTPUT(size)            (0x90 | size)
#define FEATURE(size)           (0xb0 | size)
#define COLLECTION(size)        (0xa0 | size)
#define END_COLLECTION(size)    (0xc0 | size)

/* Global items */
#define USAGE_PAGE(size)        (0x04 | size)
#define LOGICAL_MINIMUM(size)   (0x14 | size)
#define LOGICAL_MAXIMUM(size)   (0x24 | size)
#define PHYSICAL_MINIMUM(size)  (0x34 | size)
#define PHYSICAL_MAXIMUM(size)  (0x44 | size)
#define UNIT_EXPONENT(size)     (0x54 | size)
#define UNIT(size)              (0x64 | size)
#define REPORT_SIZE(size)       (0x74 | size)
#define REPORT_ID(size)         (0x84 | size)
#define REPORT_COUNT(size)      (0x94 | size)
#define PUSH(size)              (0xa4 | size)
#define POP(size)               (0xb4 | size)

/* Local items */
#define USAGE(size)                 (0x08 | size)
#define USAGE_MINIMUM(size)         (0x18 | size)
#define USAGE_MAXIMUM(size)         (0x28 | size)
#define DESIGNATOR_INDEX(size)      (0x38 | size)
#define DESIGNATOR_MINIMUM(size)    (0x48 | size)
#define DESIGNATOR_MAXIMUM(size)    (0x58 | size)
#define STRING_INDEX(size)          (0x78 | size)
#define STRING_MINIMUM(size)        (0x88 | size)
#define STRING_MAXIMUM(size)        (0x98 | size)
#define DELIMITER(size)             (0xa8 | size)

#define LSB(n)  ((n)&0xff)
#define MSB(n)  (((n)&0xff00)>>8)
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
