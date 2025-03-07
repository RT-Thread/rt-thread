/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_adb.h"

/*!< endpoint address */
#define WINUSB_IN_EP       0x81
#define WINUSB_OUT_EP      0x02

#define USBD_VID           0xFFFF
#define USBD_PID           0xFFFF
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

/*!< config descriptor size */
#define USB_CONFIG_SIZE    (9 + 9 + 7 + 7)

#ifdef CONFIG_USB_HS
#define WINUSB_MAX_MPS 512
#else
#define WINUSB_MAX_MPS 64
#endif

#define WCID_VENDOR_CODE 0x17
#define ADB_INTF_NUM 0

__ALIGN_BEGIN const uint8_t WCID_StringDescriptor_MSOS[18] __ALIGN_END = {
    ///////////////////////////////////////
    /// MS OS string descriptor
    ///////////////////////////////////////
    0x12,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    /* MSFT100 */
    'M', 0x00, 'S', 0x00, 'F', 0x00, 'T', 0x00, /* wcChar_7 */
    '1', 0x00, '0', 0x00, '0', 0x00,            /* wcChar_7 */
    WCID_VENDOR_CODE,                           /* bVendorCode */
    0x00,                                       /* bReserved */
};

__ALIGN_BEGIN const uint8_t WINUSB_WCIDDescriptor[40] __ALIGN_END = {
    ///////////////////////////////////////
    /// WCID descriptor
    ///////////////////////////////////////
    0x28, 0x00, 0x00, 0x00,                   /* dwLength */
    0x00, 0x01,                               /* bcdVersion */
    0x04, 0x00,                               /* wIndex */
    0x01,                                     /* bCount */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* bReserved_7 */

    ///////////////////////////////////////
    /// WCID function descriptor
    ///////////////////////////////////////
    ADB_INTF_NUM, /* bFirstInterfaceNumber */
    0x01, /* bReserved */
    /* Compatible ID */
    'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00, /* cCID_8: WINUSB */
    /*  */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* cSubCID_8 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             /* bReserved_6 */
};

__ALIGN_BEGIN const uint8_t WINUSB_IF0_WCIDProperties[142] __ALIGN_END = {
    ///////////////////////////////////////
    /// WCID property descriptor
    ///////////////////////////////////////
    0x8e, 0x00, 0x00, 0x00, /* dwLength */
    0x00, 0x01,             /* bcdVersion */
    0x05, 0x00,             /* wIndex */
    0x01, 0x00,             /* wCount */

    ///////////////////////////////////////
    /// registry propter descriptor
    ///////////////////////////////////////
    0x84, 0x00, 0x00, 0x00, /* dwSize */
    0x01, 0x00, 0x00, 0x00, /* dwPropertyDataType */
    0x28, 0x00,             /* wPropertyNameLength */
    /* DeviceInterfaceGUID */
    'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,  /* wcName_20 */
    'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,  /* wcName_20 */
    't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,  /* wcName_20 */
    'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,  /* wcName_20 */
    'U', 0x00, 'I', 0x00, 'D', 0x00, 0x00, 0x00, /* wcName_20 */
    0x4e, 0x00, 0x00, 0x00,                      /* dwPropertyDataLength */
    /* {1D4B2365-4749-48EA-B38A-7C6FDDDD7E26} */
    '{', 0x00, '1', 0x00, 'D', 0x00, '4', 0x00, /* wcData_39 */
    'B', 0x00, '2', 0x00, '3', 0x00, '6', 0x00, /* wcData_39 */
    '5', 0x00, '-', 0x00, '4', 0x00, '7', 0x00, /* wcData_39 */
    '4', 0x00, '9', 0x00, '-', 0x00, '4', 0x00, /* wcData_39 */
    '8', 0x00, 'E', 0x00, 'A', 0x00, '-', 0x00, /* wcData_39 */
    'B', 0x00, '3', 0x00, '8', 0x00, 'A', 0x00, /* wcData_39 */
    '-', 0x00, '7', 0x00, 'C', 0x00, '6', 0x00, /* wcData_39 */
    'F', 0x00, 'D', 0x00, 'D', 0x00, 'D', 0x00, /* wcData_39 */
    'D', 0x00, '7', 0x00, 'E', 0x00, '2', 0x00, /* wcData_39 */
    '6', 0x00, '}', 0x00, 0x00, 0x00,           /* wcData_39 */
};

const uint8_t *WINUSB_IFx_WCIDProperties[] = {
    WINUSB_IF0_WCIDProperties,
};

struct usb_msosv1_descriptor msosv1_desc = {
    .string = WCID_StringDescriptor_MSOS,
    .vendor_code = WCID_VENDOR_CODE,
    .compat_id = WINUSB_WCIDDescriptor,
    .comp_id_property = WINUSB_IFx_WCIDProperties,
};

#ifdef CONFIG_USBDEV_ADVANCE_DESC
static const uint8_t device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0100, 0x01)
};

static const uint8_t config_descriptor[] = {
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x01, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    ADB_DESCRIPTOR_INIT(ADB_INTF_NUM, WINUSB_IN_EP, WINUSB_OUT_EP, WINUSB_MAX_MPS)
};

static const uint8_t device_quality_descriptor[] = {
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x00,
    0x00,
};

static const char *string_descriptors[] = {
    (const char[]){ 0x09, 0x04 }, /* Langid */
    "CherryUSB",                  /* Manufacturer */
    "CherryADB",                  /* Product */
    "CherryADB2024",              /* Serial Number */
};

static const uint8_t *device_descriptor_callback(uint8_t speed)
{
    return device_descriptor;
}

static const uint8_t *config_descriptor_callback(uint8_t speed)
{
    return config_descriptor;
}

static const uint8_t *device_quality_descriptor_callback(uint8_t speed)
{
    return device_quality_descriptor;
}

static const char *string_descriptor_callback(uint8_t speed, uint8_t index)
{
    if (index > 3) {
        return NULL;
    }
    return string_descriptors[index];
}

const struct usb_descriptor msc_bootuf2_descriptor = {
    .device_descriptor_callback = device_descriptor_callback,
    .config_descriptor_callback = config_descriptor_callback,
    .device_quality_descriptor_callback = device_quality_descriptor_callback,
    .string_descriptor_callback = string_descriptor_callback,
    .msosv1_descriptor = &msosv1_desc
};
#else
/*!< global descriptor */
static const uint8_t adb_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0100, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x01, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    ADB_DESCRIPTOR_INIT(ADB_INTF_NUM, WINUSB_IN_EP, WINUSB_OUT_EP, WINUSB_MAX_MPS),
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x14,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x14,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'A', 0x00,                  /* wcChar6 */
    'D', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x1C,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'A', 0x00,                  /* wcChar6 */
    'D', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    '2', 0x00,                  /* wcChar9 */
    '0', 0x00,                  /* wcChar10 */
    '2', 0x00,                  /* wcChar11 */
    '4', 0x00,                  /* wcChar12 */
#ifdef CONFIG_USB_HS
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x00,
    0x00,
#endif
    0x00
};
#endif

static void usbd_event_handler(uint8_t busid, uint8_t event)
{
    switch (event) {
        case USBD_EVENT_RESET:
            break;
        case USBD_EVENT_CONNECTED:
            break;
        case USBD_EVENT_DISCONNECTED:
            break;
        case USBD_EVENT_RESUME:
            break;
        case USBD_EVENT_SUSPEND:
            break;
        case USBD_EVENT_CONFIGURED:

            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}

static struct usbd_interface intf0;

extern int shell_init(bool need_login);
void cherryadb_init(uint8_t busid, uint32_t reg_base)
{
    /* default password is : 12345678 */
    /* shell_init() must be called in-task */
    if (0 != shell_init(false)) {
        /* shell failed to be initialized */
        printf("Failed to initialize shell\r\n");
        for (;;) {
            ;
        }
    }

#ifdef CONFIG_USBDEV_ADVANCE_DESC
    usbd_desc_register(busid, &adb_descriptor);
#else
    usbd_desc_register(busid, adb_descriptor);
#endif
#ifndef CONFIG_USBDEV_ADVANCE_DESC
    usbd_msosv1_desc_register(busid, &msosv1_desc);
#endif
    usbd_add_interface(busid, usbd_adb_init_intf(busid, &intf0, WINUSB_IN_EP, WINUSB_OUT_EP));
    usbd_initialize(busid, reg_base, usbd_event_handler);
}