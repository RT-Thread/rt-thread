/*!
    \file  usbd_std.h
    \brief USB standard definitions 
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-02-10, V1.0.0, firmware for GD32F30x
*/

#ifndef USBD_STD_H
#define USBD_STD_H

#include "usbd_core.h"
#include <wchar.h>

#ifndef NULL
#define NULL                                           0U
#endif

/* constants definitions */
#define USB_DEV_QUALIFIER_DESC_LEN                     0x0AU  /* device qualifier descriptor length */
#define USB_CFG_DESC_LEN                               0x09U  /* configuration descriptor length */

#define USBD_LANGID_STR_IDX                            0x00U  /* language ID string index */
#define USBD_MFC_STR_IDX                               0x01U  /* manufacturer string index */
#define USBD_PRODUCT_STR_IDX                           0x02U  /* product string index */
#define USBD_SERIAL_STR_IDX                            0x03U  /* serial string index */
#define USBD_CONFIG_STR_IDX                            0x04U  /* configuration string index */
#define USBD_INTERFACE_STR_IDX                         0x05U  /* interface string index */

#define USB_STANDARD_REQ                               0x00U  /* standard request */
#define USB_CLASS_REQ                                  0x20U  /* device class request */
#define USB_VENDOR_REQ                                 0x40U  /* vendor request */
#define USB_REQ_MASK                                   0x60U  /* request type mask */

#define USB_REQTYPE_DEVICE                             0x00U  /* request recipient is device */
#define USB_REQTYPE_INTERFACE                          0x01U  /* request recipient is interface */
#define USB_REQTYPE_ENDPOINT                           0x02U  /* request recipient is endpoint */
#define USB_REQ_RECIPIENT_MASK                         0x1fU  /* request recipient mask */

#define USBREQ_GET_STATUS                              0x00U  /* Get_Status standard requeset */
#define USBREQ_CLEAR_FEATURE                           0x01U  /* Clear_Feature standard requeset */
#define USBREQ_SET_FEATURE                             0x03U  /* Set_Feature standard requeset */
#define USBREQ_SET_ADDRESS                             0x05U  /* Set_Address standard requeset */
#define USBREQ_GET_DESCRIPTOR                          0x06U  /* Get_Descriptor standard requeset */
#define USBREQ_GET_CONFIGURATION                       0x08U  /* Get_Configuration standard requeset */
#define USBREQ_SET_CONFIGURATION                       0x09U  /* Set_Configuration standard requeset */
#define USBREQ_GET_INTERFACE                           0x0AU  /* Get_Interface standard requeset */
#define USBREQ_SET_INTERFACE                           0x0BU  /* Set_Interface standard requeset */

#define USB_DESCTYPE_DEVICE                            0x01U  /* device descriptor type */
#define USB_DESCTYPE_CONFIGURATION                     0x02U  /* configuration descriptor type */
#define USB_DESCTYPE_STRING                            0x03U  /* string descriptor type */
#define USB_DESCTYPE_INTERFACE                         0x04U  /* interface descriptor type */
#define USB_DESCTYPE_ENDPOINT                          0x05U  /* endpoint descriptor type */
#define USB_DESCTYPE_DEVICE_QUALIFIER                  0x06U  /* device qualifier descriptor type */
#define USB_DESCTYPE_OTHER_SPEED_CONFIGURATION         0x07U  /* other speed configuration descriptor type */
#define USB_DESCTYPE_BOS                               0x0FU  /* BOS descriptor type */

#define USB_STATUS_REMOTE_WAKEUP                       2U     /* USB is in remote wakeup status */
#define USB_STATUS_SELF_POWERED                        1U     /* USB is in self powered status */

#define USB_FEATURE_ENDP_HALT                          0U     /* USB has endpoint halt feature */
#define USB_FEATURE_REMOTE_WAKEUP                      1U     /* USB has endpoint remote wakeup feature */
#define USB_FEATURE_TEST_MODE                          2U     /* USB has endpoint test mode feature */

#define ENG_LANGID                                     0x0409U  /* english language ID */
#define CHN_LANGID                                     0x0804U  /* chinese language ID */

#define USB_EPTYPE_MASK                                0x03U

#define USB_DEVICE_DESC_SIZE                           0x12U

/* USB device exported macros */
#define SWAPBYTE(addr)       (((uint16_t)(*((uint8_t *)(addr)))) + \
                             (uint16_t)(((uint16_t)(*(((uint8_t *)(addr)) + 1U))) << 8U))

#define LOWBYTE(x)           ((uint8_t)((x) & 0x00FFU))
#define HIGHBYTE(x)          ((uint8_t)(((x) & 0xFF00U) >> 8U))

#define MIN(a, b)            (((a) < (b)) ? (a) : (b))

#define IS_NOT_EP0(ep_addr)  (((ep_addr) != 0x00U) && ((ep_addr) != 0x80U))

#define WIDE_STRING(string)  _WIDE_STRING(string)
#define _WIDE_STRING(string) L##string

#define USBD_STRING_DESC(string) \
    (void *)&(const struct { \
        uint8_t _len; \
        uint8_t _type; \
        wchar_t _data[sizeof(string)]; \
    }) { \
        sizeof(WIDE_STRING(string)) + 2U - 2U, \
        USB_DESCTYPE_STRING, \
        WIDE_STRING(string) \
    }

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

#pragma pack(1)

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

#pragma pack()

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

#pragma pack(1)

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

/* function declarations */
/* USB SETUP transaction processing */
uint8_t  usbd_setup_transaction (usbd_core_handle_struct *pudev);
/* USB OUT transaction processing */
uint8_t  usbd_out_transaction (usbd_core_handle_struct *pudev, uint8_t ep_num);
/* USB IN transaction processing */
uint8_t  usbd_in_transaction (usbd_core_handle_struct *pudev, uint8_t ep_num);

/* handle USB standard device request */
uint8_t  usbd_standard_request (usbd_core_handle_struct *pudev, usb_device_req_struct *req);
/* handle device class request */
uint8_t  usbd_device_class_request (usbd_core_handle_struct *pudev, usb_device_req_struct *req);
/* handle USB vendor request */
uint8_t  usbd_vendor_request (usbd_core_handle_struct *pudev, usb_device_req_struct *req);

/* decode setup data packet */
void  usbd_setup_request_parse (usbd_core_handle_struct *pudev, usb_device_req_struct *req);
/* handle USB enumeration error event */
void  usbd_enum_error (usbd_core_handle_struct *pudev, usb_device_req_struct *req);

#endif /* USBD_STD_H */
