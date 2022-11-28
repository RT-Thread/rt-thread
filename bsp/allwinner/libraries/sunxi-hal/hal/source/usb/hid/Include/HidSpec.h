/*
********************************************************************************
*                                USB Hid Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  HidSpec.h
*
* Author        :  Javen
*
* Date          :  2010.06.02
*
* Description   :  Hid 协议相关
*
* Others        :  NULL
*
* History:
*       <time>      <version >      <author>        <desc>
*      2010.06.02      1.0           Javen          build this file
*
********************************************************************************
*/
#ifndef  __HIDPUB_H__
#define  __HIDPUB_H__
#define __packed    __attribute__((__packed__))

//----------------------------------------------------------------------
// Hid Class descriptor
//----------------------------------------------------------------------
/* Sub Class */
#define  USB_HID_SUBCLASS_NONE              0x00
#define  USB_HID_SUBCLASS_BOOT_INTERFACE    0x01

/* Protocol */
#define  USB_HID_PROTOCOL_NONE              0x00
#define  USB_HID_PROTOCOL_KEYBOARD          0x01
#define  USB_HID_PROTOCOL_MOUSE             0x02

/* HID class requests */
#define  USB_HID_HID_REQ_GET_REPORT         0x01
#define  USB_HID_REQ_GET_IDLE               0x02
#define  USB_HID_REQ_GET_PROTOCOL           0x03
#define  USB_HID_REQ_SET_REPORT             0x09
#define  USB_HID_REQ_SET_IDLE               0x0A
#define  USB_HID_REQ_SET_PROTOCOL           0x0B

/* HID class descriptor types */
#define  USB_HID_DT_HID                     (USB_TYPE_CLASS | 0x01)
#define  USB_HID_DT_REPORT                  (USB_TYPE_CLASS | 0x02)
#define  USB_HID_DT_PHYSICAL                (USB_TYPE_CLASS | 0x03)

#define  USB_HID_MAX_DESCRIPTOR_SIZE        4096

/* hid spec 1.11. page 68 */
typedef struct _usbHidClassDescriptor{
    unsigned char  bDescriptorType;     /* Report descriptor type               */
    unsigned short wDescriptorLength;   /* Total length of report descriptor    */
}__packed usbHidClassDescriptor_t;


typedef struct _usbHidDescriptor{
    unsigned char  bLength;                 /* size of this descriptor                          */
    unsigned char  bDescriptorType;         /* Hid decriptor type                               */
    unsigned short bcdHID;                  /* Hid Class Specification release number in BCD    */
    unsigned char  bCountryCode;                /* Hardware target country                          */
    unsigned char  bNumDescriptors;         /* Number of HID class descriptor to follow         */

    usbHidClassDescriptor_t desc[1];    /* report descriptor */
}__packed usbHidDescriptor_t;

/* Hid Report type */
#define  USB_HID_REPORT_INPUT           0x00
#define  USB_HID_REPORT_OUTPUT          0x01
#define  USB_HID_REPORT_FEATURE         0x02



//----------------------------------------------------------------------
// Hid spec
//----------------------------------------------------------------------

/*
 * This is the local environment. It is persistent up the next main-item.
 */
#define USB_HID_MAX_USAGES                          8192
#define USB_HID_DEFAULT_NUM_COLLECTIONS             16

#define USB_HID_REPORT_TYPES        3

#define USB_HID_MIN_BUFFER_SIZE     64      /* make sure there is at least a packet size of space */
#define USB_HID_MAX_BUFFER_SIZE     4096    /* 4kb */
#define USB_HID_CONTROL_FIFO_SIZE   256     /* to init devices with >100 reports */
#define USB_HID_OUTPUT_FIFO_SIZE    64


/* HID report item format */
#define USB_HID_ITEM_FORMAT_SHORT                   0
#define USB_HID_ITEM_FORMAT_LONG                    1

/* Special tag indicating long items */
#define USB_HID_ITEM_TAG_LONG                       15

/* HID report descriptor item type (prefix bit 2,3) */
#define USB_HID_ITEM_TYPE_MAIN                      0
#define USB_HID_ITEM_TYPE_GLOBAL                    1
#define USB_HID_ITEM_TYPE_LOCAL                     2
#define USB_HID_ITEM_TYPE_RESERVED                  3

/* HID report descriptor main item tags */
#define USB_HID_MAIN_ITEM_TAG_INPUT                 8
#define USB_HID_MAIN_ITEM_TAG_OUTPUT                9
#define USB_HID_MAIN_ITEM_TAG_FEATURE               11
#define USB_HID_MAIN_ITEM_TAG_BEGIN_COLLECTION      10
#define USB_HID_MAIN_ITEM_TAG_END_COLLECTION        12

/* HID report descriptor main item contents */
#define USB_HID_MAIN_ITEM_CONSTANT                  0x001
#define USB_HID_MAIN_ITEM_VARIABLE                  0x002
#define USB_HID_MAIN_ITEM_RELATIVE                  0x004
#define USB_HID_MAIN_ITEM_WRAP                      0x008
#define USB_HID_MAIN_ITEM_NONLINEAR                 0x010
#define USB_HID_MAIN_ITEM_NO_PREFERRED              0x020
#define USB_HID_MAIN_ITEM_NULL_STATE                0x040
#define USB_HID_MAIN_ITEM_VOLATILE                  0x080
#define USB_HID_MAIN_ITEM_BUFFERED_BYTE             0x100

/* HID report descriptor collection item types */
#define USB_HID_COLLECTION_PHYSICAL                 0x00
#define USB_HID_COLLECTION_APPLICATION              0x01
#define USB_HID_COLLECTION_LOGICAL                  0x02
#define USB_HID_COLLECTION_REPORT                   0x03
#define USB_HID_COLLECTION_NAMED_ARRAY              0x04
#define USB_HID_COLLECTION_USAGE_SWITCH             0x05
#define USB_HID_COLLECTION_USAGE_MODIFIER           0x06

/* HID report descriptor global item tags */
#define USB_HID_GLOBAL_ITEM_TAG_USAGE_PAGE          0
#define USB_HID_GLOBAL_ITEM_TAG_LOGICAL_MINIMUM     1
#define USB_HID_GLOBAL_ITEM_TAG_LOGICAL_MAXIMUM     2
#define USB_HID_GLOBAL_ITEM_TAG_PHYSICAL_MINIMUM    3
#define USB_HID_GLOBAL_ITEM_TAG_PHYSICAL_MAXIMUM    4
#define USB_HID_GLOBAL_ITEM_TAG_UNIT_EXPONENT       5
#define USB_HID_GLOBAL_ITEM_TAG_UNIT                6
#define USB_HID_GLOBAL_ITEM_TAG_REPORT_SIZE         7
#define USB_HID_GLOBAL_ITEM_TAG_REPORT_ID           8
#define USB_HID_GLOBAL_ITEM_TAG_REPORT_COUNT        9
#define USB_HID_GLOBAL_ITEM_TAG_PUSH                10
#define USB_HID_GLOBAL_ITEM_TAG_POP                 11

/* HID report descriptor local item tags */
#define USB_HID_LOCAL_ITEM_TAG_USAGE                0
#define USB_HID_LOCAL_ITEM_TAG_USAGE_MINIMUM        1
#define USB_HID_LOCAL_ITEM_TAG_USAGE_MAXIMUM        2
#define USB_HID_LOCAL_ITEM_TAG_DESIGNATOR_INDEX     3
#define USB_HID_LOCAL_ITEM_TAG_DESIGNATOR_MINIMUM   4
#define USB_HID_LOCAL_ITEM_TAG_DESIGNATOR_MAXIMUM   5
#define USB_HID_LOCAL_ITEM_TAG_STRING_INDEX         7
#define USB_HID_LOCAL_ITEM_TAG_STRING_MINIMUM       8
#define USB_HID_LOCAL_ITEM_TAG_STRING_MAXIMUM       9
#define USB_HID_LOCAL_ITEM_TAG_DELIMITER            10

/*
 * We parse each description item into this structure. Short items data
 * values are expanded to 32-bit signed int, long items contain a pointer
 * into the data area.
 */
typedef struct _usbHidItem{
    unsigned int  format;           /* Short items or long items                                */

    unsigned char      size;            /* Numeric expression specifying size of data               */
    unsigned char      type;            /* Numeric expression identifying type of item              */
    unsigned char      tag;         /* Numeric expression specifying the function of the item   */

    union {
        unsigned char   Data_u8;        /* 无符号8位数 */
        char   Data_s8;     /* 有符号8位数 */
        unsigned short  Data_u16;
        short  Data_s16;
        unsigned int  Data_u32;
        int  Data_s32;
        unsigned char  *longdata;
    } data;
}usbHidItem_t;

/* Usage Page. <<usb hid usage tables>> page14, table1 */
#define  USB_HID_USAGE_PAGE_UNDEFINED                       0x00

#define  USB_HID_USAGE_PAGE_GENERIC_DESKTOP_CONTROLS        0x01
#define  USB_HID_USAGE_PAGE_SIMULATION_CONTROLS             0x02
#define  USB_HID_USAGE_PAGE_VR_CONTROLS                     0x03
#define  USB_HID_USAGE_PAGE_SPORT_CONTROLS                  0x04
#define  USB_HID_USAGE_PAGE_GAME_CONTROLS                   0x05
#define  USB_HID_USAGE_PAGE_GENERIC_DEVICE_CONTROLS         0x06
#define  USB_HID_USAGE_PAGE_KEYBOARD_KEYPAD                 0x07
#define  USB_HID_USAGE_PAGE_LEDS                            0x08
#define  USB_HID_USAGE_PAGE_BUTTON                          0x09
#define  USB_HID_USAGE_PAGE_ORDINAL                         0x0A
#define  USB_HID_USAGE_PAGE_TELEPHONE                       0x0B
#define  USB_HID_USAGE_PAGE_CONSUMER                        0x0C
#define  USB_HID_USAGE_PAGE_DIGITIZER                       0x0D
#define  USB_HID_USAGE_PAGE_PID_PAGE                        0x0F
#define  USB_HID_USAGE_PAGE_UNICODE                         0x10
#define  USB_HID_USAGE_PAGE_ALPHANUMERIC_DISPLAY            0x14
#define  USB_HID_USAGE_PAGE_MEDICAL_INSTRUMENTS             0x40
#define  USB_HID_USAGE_PAGE_MONITOR_PAGES                   0x80  //???????
#define  USB_HID_USAGE_PAGE_POWER_PAGES                     0x84  //???????
#define  USB_HID_USAGE_PAGE_BAR_CODE_SCANNER_PAGE           0x8C
#define  USB_HID_USAGE_PAGE_SCALE_PAGE                      0x8D
#define  USB_HID_USAGE_PAGE_MEGNETIC_STRIPE_READING_DEVICE  0x8E
#define  USB_HID_USAGE_PAGE_RESEVERED_POINT_OF_SALE_PAGES   0x8F
#define  USB_HID_USAGE_PAGE_CAMERA_CONTROL_PAGE             0x90
#define  USB_HID_USAGE_PAGE_ARCADE_PAGE                     0x91

#define  USB_HID_USAGE_PAGE_VENDOR_DEFINED                  0xFF00

/* Usage Types. <<usb hid usage tables>> page17~21 */
#define  USB_HID_USAGE_TYPES_UNDEFINED                  0x00

#define  USB_HID_USAGE_TYPES_CONTROL_UNDEFINED          0x01
#define  USB_HID_USAGE_TYPES_CONTROL_LINER              0x02
#define  USB_HID_USAGE_TYPES_CONTROL_ON_OFF             0x03
#define  USB_HID_USAGE_TYPES_CONTROL_MOMENTARY          0x04
#define  USB_HID_USAGE_TYPES_CONTROL_ONE_SHOT           0x05

#define  USB_HID_USAGE_TYPES_DATA_UNDEFINED             0x06
#define  USB_HID_USAGE_TYPES_DATA_SELECTOR              0x07
#define  USB_HID_USAGE_TYPES_DATA_STATIC_VALUE          0x08
#define  USB_HID_USAGE_TYPES_DATA_STATIC_FLAG           0x09
#define  USB_HID_USAGE_TYPES_DATA_DYNAMIC_VALUE         0x0A
#define  USB_HID_USAGE_TYPES_DATA_DYNAMIC_FLAG          0x0B

#define  USB_HID_USAGE_TYPES_COLLECTION_UNDEFINED       0x0C
#define  USB_HID_USAGE_TYPES_COLLECTION_NAMED_ARRAY     0x0D
#define  USB_HID_USAGE_TYPES_COLLECTION_APPLICATION     0x0E
#define  USB_HID_USAGE_TYPES_COLLECTION_LOGICAL         0x0F
#define  USB_HID_USAGE_TYPES_COLLECTION_PHYSICAL        0x10
#define  USB_HID_USAGE_TYPES_COLLECTION_USAGE_SWITCH    0x11
#define  USB_HID_USAGE_TYPES_COLLECTION_USAGE_MODIFIER  0x12

/* Generic DeskTop Page. <<usb hid usage tables>> page126 */
#define  USB_HID_GENERIC_DESKTOP_PAGE_UNDEFINED                 0x00
#define  USB_HID_GENERIC_DESKTOP_PAGE_PONITER                   0x01
#define  USB_HID_GENERIC_DESKTOP_PAGE_MOUSE                     0x02

#define  USB_HID_GENERIC_DESKTOP_PAGE_JOYSTICK                  0x04
#define  USB_HID_GENERIC_DESKTOP_PAGE_GAMEPAD                   0x05
#define  USB_HID_GENERIC_DESKTOP_PAGE_KEYBOARD                  0x06
#define  USB_HID_GENERIC_DESKTOP_PAGE_KEYPAD                    0x07
#define  USB_HID_GENERIC_DESKTOP_PAGE_MULTIAXIS_CONTROLLER      0x08
#define  USB_HID_GENERIC_DESKTOP_PAGE_TABLET_PC_SYSTEM_CONTROLS 0x09

#define  USB_HID_GENERIC_DESKTOP_PAGE_X                         0x30
#define  USB_HID_GENERIC_DESKTOP_PAGE_Y                         0x31
#define  USB_HID_GENERIC_DESKTOP_PAGE_Z                         0x32
#define  USB_HID_GENERIC_DESKTOP_PAGE_RX                        0x33
#define  USB_HID_GENERIC_DESKTOP_PAGE_RY                        0x34
#define  USB_HID_GENERIC_DESKTOP_PAGE_RZ                        0x35
#define  USB_HID_GENERIC_DESKTOP_PAGE_SLIDER                    0x36
#define  USB_HID_GENERIC_DESKTOP_PAGE_DIAL                      0x37
#define  USB_HID_GENERIC_DESKTOP_PAGE_WHEEL                     0x38
#define  USB_HID_GENERIC_DESKTOP_PAGE_HAT_SWITCH                0x39
#define  USB_HID_GENERIC_DESKTOP_PAGE_COUNTED_BUFFER            0x3A
#define  USB_HID_GENERIC_DESKTOP_PAGE_BYTE_COUNT                0x3B
#define  USB_HID_GENERIC_DESKTOP_PAGE_MOTION_WAKEUP             0x3C
#define  USB_HID_GENERIC_DESKTOP_PAGE_START                     0x3D
#define  USB_HID_GENERIC_DESKTOP_PAGE_SELECT                    0x3E

#define  USB_HID_GENERIC_DESKTOP_PAGE_VX                        0x40
#define  USB_HID_GENERIC_DESKTOP_PAGE_VY                        0x41
#define  USB_HID_GENERIC_DESKTOP_PAGE_VZ                        0x42
#define  USB_HID_GENERIC_DESKTOP_PAGE_VBRX                      0x43
#define  USB_HID_GENERIC_DESKTOP_PAGE_VBRY                      0x44
#define  USB_HID_GENERIC_DESKTOP_PAGE_VBRZ                      0x45
#define  USB_HID_GENERIC_DESKTOP_PAGE_VNO                       0x46
#define  USB_HID_GENERIC_DESKTOP_PAGE_FEATURE_NOTIFICATION      0x47


/* Global Items. <<Device Class Definition for Human Interface Devices (HID)>> page35 */
typedef struct _usbHidGlobalItems{
    unsigned int UsagePage;         /* 用途类页                     */

    int LogicalMinimum;     /* 最小逻辑值                    */
    int LogicalMaximum;     /* 最大逻辑值                    */
    int PhysicalMinimum;        /* 最小物理值                    */
    int PhysicalMaximum;        /* 最大物理值                    */
    int UnitExponent;           /* 单位指数                     */
    unsigned int Unit;                  /* 单位                       */
    unsigned int ReportSize;            /* 报告大小                     */
    unsigned int ReportId;              /* 报告ID                         */
    unsigned int ReportCount;           /* 报告的个数                    */
    unsigned int Push;                  /* 项目状态表暂存到stack        */
    unsigned int Pop;                   /* 取回stack最顶层的项目状态表     */

    unsigned int Reserved;
}__packed usbHidGlobalItems_t;

/* Local Items. <<Device Class Definition for Human Interface Devices (HID)>> page39 */
typedef __packed struct _usbHidLocalItems{
    unsigned int usage[USB_HID_MAX_USAGES];                 /* usage array */
    unsigned int collection_index[USB_HID_MAX_USAGES];  /* collection index array */
    unsigned int usage_index;
    unsigned int usage_minimum;
    unsigned int delimiter_depth;
    unsigned int delimiter_branch;
}usbHidLocalItems_t;

/* Collection Items */
typedef struct _usbHidCollectionItems{
    unsigned int Type;      /* type of collection */
    unsigned int Usage; /* 用途类页 */
    unsigned int Level; /* the level of collection items */
}__packed usbHidCollectionItems_t;

typedef struct _usbHidUsage{
    unsigned int hid;               /* hid usage code, 高16为usage page, 低16位usage */
    unsigned int collection_index;  /* index into collection array  */

    /* hidinput data */
    unsigned short code;                /* input driver code            */
    unsigned char  type;                /* input driver type            */
    char  hat_min;          /* hat switch fun               */
    char  hat_max;          /* ditto                        */
    char  hat_dir;          /* ditto                        */
}usbHidUsage_t;

#endif   //__HIDPUB_H__


