/*!
    \file  usb_std.h
    \brief USB 2.0 standard defines
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef USB_STD_H
#define USB_STD_H

#include "usb_conf.h"

#define USB_DEV_QUALIFIER_DESC_LEN                     0x0AU       /*!< USB device qualifier descriptor length */
#define USB_DEV_DESC_LEN                               0x12U       /*!< USB device descriptor length */
#define USB_CFG_DESC_LEN                               0x09U       /*!< USB device configuration descriptor length */
#define USB_IF_DESC_LEN                                0x09U       /*!< USB device interface descriptor length */
#define USB_EP_DESC_LEN                                0x07U       /*!< USB device endpoint descriptor length */
#define USB_OTG_DESC_LEN                               0x03U       /*!< USB device OTG descriptor length */

/* bit 7 of bmRequestType: data phase transfer direction */
#define USB_DIR_MASK                                   0x80U       /*!< USB transfer direction mask */
#define USB_DIR_OUT                                    0x00U       /*!< USB transfer OUT direction */
#define USB_DIR_IN                                     0x80U       /*!< USB transfer IN direction */

/* bit 6..5 of bmRequestType: request type */
#define USB_STANDARD_REQ                               0x00U       /*!< USB standard request */
#define USB_CLASS_REQ                                  0x20U       /*!< USB class request */
#define USB_VENDOR_REQ                                 0x40U       /*!< USB vebdor request */
#define USB_REQ_MASK                                   0x60U       /*!< USB request mask */

/* bit 4..0 of bmRequestType: recipient type */
#define USB_REQTYPE_DEVICE                             0x00U       /*!< USB device request type */
#define USB_REQTYPE_INTERFACE                          0x01U       /*!< USB interface request type*/
#define USB_REQTYPE_ENDPOINT                           0x02U       /*!< USB endpoint request type*/
#define USB_REQTYPE_MASK                               0x03U       /*!< USB request type mask*/

/* bRequest value */
#define USBREQ_GET_STATUS                              0x00U       /*!< USB get status request*/
#define USBREQ_CLEAR_FEATURE                           0x01U       /*!< USB clear feature request*/
#define USBREQ_SET_FEATURE                             0x03U       /*!< USB set feature request*/
#define USBREQ_SET_ADDRESS                             0x05U       /*!< USB set address request*/
#define USBREQ_GET_DESCRIPTOR                          0x06U       /*!< USB get descriptor request*/
#define USBREQ_SET_DESCRIPTOR                          0x07U       /*!< USB set descriptor request*/
#define USBREQ_GET_CONFIGURATION                       0x08U       /*!< USB get configuration request*/
#define USBREQ_SET_CONFIGURATION                       0x09U       /*!< USB set configuration request*/
#define USBREQ_GET_INTERFACE                           0x0AU       /*!< USB get interface request*/
#define USBREQ_SET_INTERFACE                           0x0BU       /*!< USB set interface request*/
#define USBREQ_SYNCH_FRAME                             0x0CU       /*!< USB synchronize frame request*/

/* descriptor types of usb specifications */
#define USB_DESCTYPE_DEVICE                            0x01U       /*!< USB device descriptor type*/
#define USB_DESCTYPE_CONFIGURATION                     0x02U       /*!< USB configuration descriptor type*/
#define USB_DESCTYPE_STRING                            0x03U       /*!< USB string descriptor type*/
#define USB_DESCTYPE_INTERFACE                         0x04U       /*!< USB interface descriptor type*/
#define USB_DESCTYPE_ENDPOINT                          0x05U       /*!< USB endpoint descriptor type*/
#define USB_DESCTYPE_DEVICE_QUALIFIER                  0x06U       /*!< USB device qualtfier descriptor type*/
#define USB_DESCTYPE_OTHER_SPEED_CONFIGURATION         0x07U       /*!< USB other speed configuration descriptor type*/
#define USB_DESCTYPE_INTERFACE_POWER                   0x08U       /*!< USB interface power descriptor type*/

#define USB_DESCTYPE_HID                               0x21U       /*!< USB HID descriptor type*/
#define USB_DESCTYPE_HID_REPORT                        0x22U       /*!< USB HID report descriptor type*/

#define USB_DEVDESC_SIZE                               18U         /*!< USB device descriptor size*/
#define USB_CFGDESC_SIZE                               9U          /*!< USB configure descriptor size*/
#define USB_INTDESC_SIZE                               9U          /*!< USB interface descriptor size*/
#define USB_EPDESC_SIZE                                7U          /*!< USB endpoint descriptor size*/

/* descriptor type and descriptor index  */
/* use the following values when USB host need to get descriptor  */
#define  USB_DEVDESC                    ((USB_DESCTYPE_DEVICE                    << 8U) & 0xFF00U)  /*!< USB device operation marco */
#define  USB_CFGDESC                    ((USB_DESCTYPE_CONFIGURATION             << 8U) & 0xFF00U)  /*!< USB configuration operation marco */
#define  USB_STRDESC                    ((USB_DESCTYPE_STRING                    << 8U) & 0xFF00U)  /*!< USB string operation marco */
#define  USB_INTDESC                    ((USB_DESCTYPE_INTERFACE                 << 8U) & 0xFF00U)  /*!< USB interface operation marco */
#define  USB_EPDESC                     ((USB_DESCTYPE_INTERFACE                 << 8U) & 0xFF00U)  /*!< USB endpoint operation marco */
#define  USB_DEVQUADESC                 ((USB_DESCTYPE_DEVICE_QUALIFIER          << 8U) & 0xFF00U)  /*!< USB device qualifier operation marco */
#define  USB_OSPCFGDESC                 ((USB_DESCTYPE_OTHER_SPEED_CONFIGURATION << 8U) & 0xFF00U)  /*!< USB other speed configuration operation marco */
#define  USB_INTPWRDESC                 ((USB_DESCTYPE_INTERFACE_POWER           << 8U) & 0xFF00U)  /*!< USB interface power operation marco */
#define  USB_HIDREPDESC                 ((USB_DESCTYPE_HID_REPORT                << 8U) & 0xFF00U)  /*!< USB HID report operation marco */
#define  USB_HIDDESC                    ((USB_DESCTYPE_HID                       << 8U) & 0xFF00U)  /*!< USB HID operation marco */

#define SWAPBYTE(addr)       (((uint16_t)(*((uint8_t *)(addr)))) + \
                             (uint16_t)(((uint16_t)(*(((uint8_t *)(addr)) + 1U))) << 8U))

/* supported classes */
#define USB_MSC_CLASS                                   0x08U     /*!< USB MSC class*/
#define USB_HID_CLASS                                   0x03U     /*!< USB HID class*/

/* interface descriptor field values for hid boot protocol */
#define HID_BOOT_CODE                                   0x01U     /*!< USB HID boot code*/
#define HID_KEYBRD_BOOT_CODE                            0x01U     /*!< USB HID keyboard boot code*/
#define HID_MOUSE_BOOT_CODE                             0x02U     /*!< USB HID mouse boot code*/

/* as per usb specs 9.2.6.4 :standard request with data request timeout: 5sec
   standard request with no data stage timeout : 50ms */
#define DATA_STAGE_TIMEOUT                              5000U     /*!< USB data stage timeout*/
#define NODATA_STAGE_TIMEOUT                            50U       /*!< USB no data stage timeout*/

#define USBH_CFG_DESC_SET_SIZE (USB_CFGDESC_SIZE + USB_INTDESC_SIZE \
                                + (USBH_MAX_EP_NUM * USB_EPDESC_SIZE))    /*!< USB host set configuration descriptor size */

#pragma pack(1)

typedef union
{
    uint8_t data[8];

    struct _setup_packet_struct
    {
        uint8_t           bmRequestType;  /*!< type of request */
        uint8_t           bRequest;       /*!< request of setup packet */
        uint16_t          wValue;         /*!< value of setup packet */
        uint16_t          wIndex;         /*!< index of setup packet */
        uint16_t          wLength;        /*!< length of setup packet */
    } b;
}usb_setup_union;

typedef struct
{
    uint8_t bLength;                      /*!< size of the descriptor */
    uint8_t bDescriptorType;              /*!< type of the descriptor */
} usb_descriptor_header_struct;

typedef struct
{
    usb_descriptor_header_struct Header;  /*!< descriptor header, including type and size */

    uint16_t bcdUSB;                      /*!< BCD of the supported USB specification */
    uint8_t  bDeviceClass;                /*!< USB device class */
    uint8_t  bDeviceSubClass;             /*!< USB device subclass */
    uint8_t  bDeviceProtocol;             /*!< USB device protocol */
    uint8_t  bMaxPacketSize0;             /*!< size of the control (address 0) endpoint's bank in bytes */
    uint16_t idVendor;                    /*!< vendor ID for the USB product */
    uint16_t idProduct;                   /*!< unique product ID for the USB product */
    uint16_t bcdDevice;                   /*!< product release (version) number */
    uint8_t  iManufacturer;               /*!< string index for the manufacturer's name */
    uint8_t  iProduct;                    /*!< string index for the product name/details */
    uint8_t  iSerialNumber;               /*!< string index for the product's globally unique hexadecimal serial number */
    uint8_t  bNumberConfigurations;       /*!< total number of configurations supported by the device */
} usb_descriptor_device_struct;

typedef struct
{
    usb_descriptor_header_struct Header;  /*!< descriptor header, including type and size */

    uint16_t wTotalLength;                /*!< size of the configuration descriptor header,and all sub descriptors inside the configuration */
    uint8_t  bNumInterfaces;              /*!< total number of interfaces in the configuration */
    uint8_t  bConfigurationValue;         /*!< configuration index of the current configuration */
    uint8_t  iConfiguration;              /*!< index of a string descriptor describing the configuration */
    uint8_t  bmAttributes;                /*!< configuration attributes */
    uint8_t  bMaxPower;                   /*!< maximum power consumption of the device while in the current configuration */
} usb_descriptor_configuration_struct;

typedef struct
{
    usb_descriptor_header_struct Header;  /*!< descriptor header, including type and size */

    uint8_t bInterfaceNumber;             /*!< index of the interface in the current configuration */
    uint8_t bAlternateSetting;            /*!< alternate setting for the interface number */
    uint8_t bNumEndpoints;                /*!< total number of endpoints in the interface */
    uint8_t bInterfaceClass;              /*!< interface class ID */
    uint8_t bInterfaceSubClass;           /*!< interface subclass ID */
    uint8_t bInterfaceProtocol;           /*!< interface protocol ID */
    uint8_t iInterface;                   /*!< index of the string descriptor describing the interface */
} usb_descriptor_interface_struct;

typedef struct
{
    usb_descriptor_header_struct Header;  /*!< descriptor header, including type and size. */

    uint8_t  bEndpointAddress;            /*!< logical address of the endpoint */
    uint8_t  bmAttributes;                /*!< endpoint attributes */
    uint16_t wMaxPacketSize;              /*!< size of the endpoint bank, in bytes */
    uint8_t  bInterval;                   /*!< polling interval in milliseconds for the endpoint if it is an INTERRUPT or ISOCHRONOUS type */
} usb_descriptor_endpoint_struct;

typedef struct
{
    usb_descriptor_header_struct Header;  /*!< descriptor header, including type and size. */
    uint16_t wLANGID;                     /*!< LANGID code */
}usb_descriptor_language_id_struct;

#pragma pack()

#endif /* USB_STD_H */
