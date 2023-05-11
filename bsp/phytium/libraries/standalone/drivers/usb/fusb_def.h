/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fusb_def.h
 * Date: 2022-02-11 13:33:11
 * LastEditTime: 2022-02-18 09:18:24
 * Description:  This files is for definition of spec defined USB data structure
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#ifndef  FUSB_DEF_H
#define  FUSB_DEF_H

/***************************** Include Files *********************************/

#include "ftypes.h"


#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
typedef enum
{
    FUSB_UNKNOWN_SPEED = -1,
    FUSB_FULL_SPEED = 0,
    FUSB_LOW_SPEED = 1,
    FUSB_HIGH_SPEED = 2,
    FUSB_SUPER_SPEED = 3,
    FUSB_SUPER_SPEED_PLUS = 4,
} FUsbSpeed;

typedef enum
{
    FUSB_REQ_HOST_TO_DEVICE = 0,
    FUSB_REQ_DEVICE_TO_HOST = 1
} FUsbReqDirection;

typedef enum
{
    FUSB_REQ_TYPE_STANDARD = 0,
    FUSB_REQ_TYPE_CLASS = 1,
    FUSB_REQ_TYPE_VENDOR = 2,
    FUSB_REQ_TYPE_RESERVED = 3
} FUsbReqType;

typedef enum
{
    FUSB_REQ_RECP_DEV = 0,
    FUSB_REQ_RECP_IF = 1,
    FUSB_REQ_RECP_EP = 2,
    FUSB_REQ_RECP_OTHER = 3
} FUsbReqRecpient;

/* refer to Table 9-5. Descriptor Types in USB spec. for details */
typedef enum
{
    FUSB_DESC_TYPE_NONE = 0,
    FUSB_DESC_TYPE_DEVICE = 1,
    FUSB_DESC_TYPE_CONFIG = 2,
    FUSB_DESC_TYPE_STRING = 3,
    FUSB_DESC_TYPE_INTERFACE = 4,
    FUSB_DESC_TYPE_ENDPOINT = 5,
    FUSB_DESC_TYPE_HUB = 41,
    FUSB_DESC_TYPE_SUPER_SPEED_HUB = 42
} FUsbDescriptorType;

typedef enum
{
    FUSB_GET_STATUS = 0,
    FUSB_CLEAR_FEATURE = 1,
    FUSB_SET_FEATURE = 3,
    FUSB_SET_ADDRESS = 5,
    FUSB_GET_DESCRIPTOR = 6,
    FUSB_SET_DESCRIPTOR = 7,
    FUSB_GET_CONFIGURATION = 8,
    FUSB_SET_CONFIGURATION = 9,
    FUSB_GET_INTERFACE = 10,
    FUSB_SET_INTERFACE = 11,
    FUSB_SYNCH_FRAME = 12
} FUsbRequestCode;

typedef enum
{
    FUSB_ENDPOINT_HALT = 0,
    FUSB_DEVICE_REMOTE_WAKEUP = 1,
    FUSB_TEST_MODE = 2
} FUsbFeatureSelectors;

typedef enum
{
    FUSB_SETUP,
    FUSB_IN,
    FUSB_OUT
} FUsbDirection;

typedef enum
{
    FUSB_CONTROL_EP = 0,
    FUSB_ISOCHRONOUS_EP = 1,
    FUSB_BULK_EP = 2,
    FUSB_INTERRUPT_EP = 3
} FUsbEpType;

typedef enum
{
    FUSB_UNKOWN_DEVICE = 0x0,
    FUSB_AUDIO_DEVICE = 0x01,
    FUSB_COMM_DEVICE = 0x02,
    FUSB_HID_DEVICE = 0x03,
    FUSB_PHYSICAL_DEVICE = 0x05,
    FUSB_IMAGE_DEVICE = 0x06,
    FUSB_PRINTER_DEVICE = 0x07,
    FUSB_MASS_STORAGE_DEVICE = 0x08,
    FUSB_HUB_DEVICE = 0x09,
} FUsbDevClass; /* definition of device class */

/**************************** Type Definitions *******************************/

/* following data structure is defined according to spec. name their member
   may not compliant with code convention */
typedef struct
{
    unsigned char bDescLength;
    unsigned char bDescriptorType;
    unsigned char bNbrPorts; /*  Number of downstream facing ports supports */
    union
    {
        struct
        {
            unsigned long logicalPowerSwitchingMode: 2; /* BIT[1:0] */
            unsigned long isCompoundDevice: 1; /* BIT[2] */
            unsigned long overcurrentProtectionMode: 2; /* BIT[4:3] */
            unsigned long ttThinkTime: 2; /* BIT[6:5] */
            unsigned long arePortIndicatorsSupported: 1; /* BIT[7] */
            unsigned long: 8;
        } __attribute__((packed));
        unsigned short wHubCharacteristics;
    } __attribute__((packed));
    unsigned char bPowerOn2PwrGood; /* in 2 ms intervals */
    unsigned char bHubContrCurrent; /* max current requirements */
    char DeviceRemovable[]; /* indicates if a port has a removable device attached */
} __attribute__((packed)) FUsbHubDescriptor;

typedef struct
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned short bcdUSB;
    unsigned char bDeviceClass;
    unsigned char bDeviceSubClass;
    unsigned char bDeviceProtocol;
    unsigned char bMaxPacketSize0;
    unsigned short idVendor;
    unsigned short idProduct;
    unsigned short bcdDevice;
    unsigned char iManufacturer;
    unsigned char iProduct;
    unsigned char iSerialNumber;
    unsigned char bNumConfigurations;
} __attribute__((packed)) FUsbDeviceDescriptor;

typedef struct
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned short wTotalLength;
    unsigned char bNumInterfaces;
    unsigned char bConfigurationValue;
    unsigned char iConfiguration;
    unsigned char bmAttributes;
#define FUSB_CONFIG_DESC_ATTR_REMOTE_WEAKUP     BIT(5) /* 1: remote wakeup feature */
#define FUSB_CONFIG_DESC_ATTR_SELF_POWER        BIT(6) /* 1: self-powered 0: bus-powered */
#define FUSB_CONFIG_DESC_ATTR_USB1_COMPATIABLE  BIT(7) /* 1: compatibility with USB 1.0 */
    unsigned char bMaxPower;
    /* configuration descriptor may follow more buffers, need to allocate dynamic memory for all contents */
} __attribute__((packed)) FUsbConfigurationDescriptor;

typedef struct
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bInterfaceNumber;
    unsigned char bAlternateSetting;
    unsigned char bNumEndpoints;
    unsigned char bInterfaceClass;
    unsigned char bInterfaceSubClass;
    unsigned char bInterfaceProtocol;
    unsigned char iInterface;
} __attribute__((packed)) FUsbInterfaceDescriptor;

typedef struct
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bEndpointAddress;
    /* Low-speed devices can have a maximum of 3 endpoint, other devices can have 16 (0–15) */
#define FUSB_EP_DESC_EP_NUM(x)      (GENMASK(3, 0) & (x))   /* endpoint number */
#define FUSB_EP_DESC_EP_DIR_IN      BIT(7)                  /* direction, 0: OUT, 1: IN */
    unsigned char bmAttributes;
#define FUSB_EP_DESC_TRANS_TYPE(x)      (GENMASK(1, 0) & (x))
#define FUSB_EP_DESC_TRANS_CTRL     0b00    /* control */
#define FUSB_EP_DESC_TRANS_ISOC     0b01    /* isochronous */
#define FUSB_EP_DESC_TRANS_BULK     0b10    /* bulk */
#define FUSB_EP_DESC_TRANS_INTR     0b11    /* interrupt */
    unsigned short wMaxPacketSize;
#define FUSB_EP_DESC_MAX_PACKET_SZ      GENMASK(10, 0)
    unsigned char bInterval;
} __attribute__((packed)) FUsbEndpointDescriptor;

typedef union
{
    struct
    {
        u8  len;
        u8  type;
    } header;
#define FUSB_DESCRIPTOR_HEADER_SIZE     2
    FUsbConfigurationDescriptor configuration;
    FUsbInterfaceDescriptor     interface;
    FUsbEndpointDescriptor      endpoint;
} __attribute__((packed)) FUsbDescriptor;

typedef struct
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned short bcdHID;
    unsigned char bCountryCode;
    unsigned char bNumDescriptors;
    unsigned char bReportDescriptorType;
    unsigned short wReportDescriptorLength;
} __attribute__((packed)) FUsbHidDescriptor;

typedef struct
{
    u8  len;        /* Descriptor size in bytes (variable) */
    u8  type;       /* The constant String (0x03 DESCRIPTOR_STRING) */
    u16 string[0];  /* Unicode UTF- 16LE string */
} __attribute__((packed)) FUsbStringDescriptor;

typedef struct
{
    union
    {
        struct
        {
            FUsbReqRecpient req_recp: 5;
            FUsbReqType req_type: 2;
            FUsbReqDirection data_dir: 1;
        } __attribute__((packed));
        unsigned char bmRequestType;
    } __attribute__((packed));
    unsigned char bRequest;
    unsigned short wValue;
    unsigned short wIndex;
    unsigned short wLength;
} __attribute__((packed)) FUsbDevReq;

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FUSB_DEFAULT_LANG_ID                0x409 /* English */

/************************** Function Prototypes ******************************/


#ifdef __cplusplus
}
#endif


#endif