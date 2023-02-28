/***************************************************************************//**
* \file cy_usb_dev_descr.h
* \version 2.10
*
* Provides device definition structures and descriptors structures.
* The descriptor structures can be used to access particular descriptors.
*
********************************************************************************
* \copyright
* (c) 2018-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_USB_DEV_DESCR_H)
#define CY_USB_DEV_DESCR_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "cy_usb_dev_audio_descr.h"
#include "cy_usb_dev_cdc_descr.h"
#include "cy_usb_dev_hid_descr.h"

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
*          Type Definitions
*******************************************************************************/

/**
* \addtogroup group_usb_dev_structures_device
* \{
*/

/** USBFS Device endpointDescriptor structure */
typedef struct
{
    /** Pointer to the endpointDescriptor Descriptor in the Configuration Descriptor */
    const uint8_t *endpointDescriptor;

} cy_stc_usb_dev_endpoint_t;


/** USBFS Device HID structure */
typedef struct
{
    /** Pointer to the HID Class Descriptor in the Configuration Descriptor */
    const uint8_t *hidDescriptor;

    /** Pointer to uint8_t array that stores HID Report Descriptor */
    const uint8_t *reportDescriptor;

    /** HID Report Descriptor size */
    uint16_t reportDescriptorSize;

    /** Start position of input report IDs in the array */
    uint8_t inputReportPos;

    /** Number of input report IDs */
    uint8_t numInputReports;

    /** Array of indexes for input report IDs */
    const uint8_t *inputReportIdx;

    /** Number of elements in the array of indexes */
    uint8_t inputReportIdxSize;

} cy_stc_usb_dev_hid_t;


/** USBFS Device Alternate Interface structure */
typedef struct
{
    /** Pointer to the Interface Descriptor in the Configuration Descriptor */
    const uint8_t *interfaceDescriptor;

    /** Pointer to array of pointers to structure that stores Endpoints information */
    const cy_stc_usb_dev_endpoint_t **endpoints;

    /** Number of endpoints that belong to this interface alternates */
    uint8_t numEndpoints;

    /** Pointer to the HID information structure */
    const cy_stc_usb_dev_hid_t *hid;
} cy_stc_usb_dev_alternate_t;


/** USBFS Device Interface structure */
typedef struct
{
    /** Number of supported alternate settings  */
    uint8_t numAlternates;

    /** Pointer to array of pointers to structure that stores Interface Alternates information */
    const cy_stc_usb_dev_alternate_t **alternates;

    /** Mask that represents endpoints that belong to Interface Alternates */
    uint16_t endpointsMask;
} cy_stc_usb_dev_interface_t;


/** USBFS Device Configuration structure */
typedef struct
{
    /** Number of supported interfaces */
    uint8_t   numInterfaces;

    /** Pointer to uint8_t array that stores Configuration Descriptor */
    const uint8_t  *configDescriptor;

    /** Pointer to array of pointers to structure that store Interface information */
    const cy_stc_usb_dev_interface_t **interfaces;
} cy_stc_usb_dev_configuration_t;

/** USBFS Device MS OS String Descriptors structure */
typedef struct
{
    /** Pointer to MS OS String descriptor */
    const uint8_t  *msOsDescriptor;

    /** Vendor code to get Extended Compat ID and Properties OS Descriptors */
    uint8_t msVendorCode;

    /** Pointer to Extended Compat ID OS Descriptor */
     const uint8_t  *extCompatIdDescriptor;

    /** Pointer to Extended Properties OS Descriptor */
    const uint8_t  *extPropertiesDescriptor;
} cy_stc_usb_dev_ms_os_string_t;

/** USBFS Device String Descriptors structure */
typedef struct
{
    /** Number of String Descriptors */
    uint8_t  numStrings;

    /** Defines whether the MS OS String is enabled */
    bool     enableWindowsOsDescriptor;

    /** Defines MS OS Strings structures */
    const cy_stc_usb_dev_ms_os_string_t *osStringDescriptors;

    /** Pointer to array of pointers to String Descriptors  */
    const uint8_t  **stringDescriptors;
} cy_stc_usb_dev_string_t;


/** USBFS Device structure */
typedef struct
{
    /** Pointer to uint8_t array that stores Device Descriptor */
    const uint8_t *deviceDescriptor;

    /** Pointer to uint8_t array that stores BOS Descriptor */
    const uint8_t *bosDescriptor;

    /** Pointer to structure that stores Strings Descriptors information */
    const cy_stc_usb_dev_string_t *strings;

    /** Number of supported configurations */
    uint8_t numConfigurations;

    /** Pointer to array of pointers to structure that stores Configuration information */
    const cy_stc_usb_dev_configuration_t **configurations;

} cy_stc_usb_dev_device_t;

/** \} group_usb_dev_structures_device */


/**
* \addtogroup group_usb_dev_structures_device_descr
* \{
*/

/** Device descriptor */
typedef struct
{
    uint8_t  bLength;           /**< Size of the Descriptor in Bytes  */
    uint8_t  bDescriptorType;   /**< Constant Device Descriptor */
    uint16_t bcdUSB;            /**< USB Specification Number to which the device complies */
    uint8_t  bDeviceClass;      /**< Class Code (Assigned by USB Org):
                                    * If equal to Zero, each interface specifies its own class code
                                    * If equal to 0xFF, the class code is vendor specified.
                                    * Otherwise, field is valid Class Code.
                                */
    uint8_t  bDeviceSubClass;   /**< Subclass Code (Assigned by USB Org) */
    uint8_t  bDeviceProtocol;   /**< Protocol Code (Assigned by USB Org) */
    uint8_t  bMaxPacketSize;    /**< Maximum Packet Size for Zero Endpoint. Valid Sizes are 8, 16, 32, 64 */
    uint16_t idVendor;          /**< Vendor ID (Assigned by USB Org) */
    uint16_t idProduct;         /**< Product ID (Assigned by Manufacturer) */
    uint16_t bcdDevice;         /**< Release Number */
    uint8_t  iManufacturer;     /**< Index of Manufacturer String Descriptor */
    uint8_t  iProduct;          /**< Index of Product String Descriptor */
    uint8_t  iSerialNumber;     /**< Index of Serial Number String Descriptor */
    uint8_t  bNumConfigurations;/**< Number of Possible Configurations */
} cy_stc_usbdev_device_descr_t;

/** Configuration descriptor */
typedef struct
{
    uint8_t  bLength;               /**< Size of Descriptor in Bytes */
    uint8_t  bDescriptorType;       /**< Configuration Descriptor */
    uint16_t wTotalLength;          /**< Total length in bytes of data returned */
    uint8_t  bNumInterfaces;        /**< Number of Interfaces */
    uint8_t  bConfigurationValue;   /**< Value to use as an argument to select this configuration */
    uint8_t  iConfiguration;        /**< Index of String Descriptor describing this configuration */
    uint8_t  bmAttributes;          /**< Bitmap:
                                    * D7 Reserved, set to 1. (USB 1.0 Bus Powered)
                                    * D6 Self Powered
                                    * D5 Remote Wakeup
                                    * D4..0 Reserved, set to 0.
                                    */
    uint8_t  bMaxPower;             /**< Maximum Power Consumption in 2 mA units */
} cy_stc_usbdev_config_descr_t;

/** Interface descriptor */
typedef struct
{
    uint8_t bLength;            /**< Size of Descriptor in Bytes (9 Bytes) */
    uint8_t bDescriptorType;    /**< Interface Descriptor */
    uint8_t bInterfaceNumber;   /**< Number of Interface */
    uint8_t bAlternateSetting;  /**< Value used to select alternative setting */
    uint8_t bNumEndpoints;      /**< Number of Endpoints used for this interface */
    uint8_t bInterfaceClass;    /**< Class Code (Assigned by USB Org) */
    uint8_t bInterfaceSubClass; /**< Subclass Code (Assigned by USB Org) */
    uint8_t bInterfaceProtocol; /**< Protocol Code (Assigned by USB Org) */
    uint8_t iInterface;         /**< Index of String Descriptor describing this interface */
} cy_stc_usbdev_interface_descr_t;


/** Endpoint descriptor */
typedef struct
{
    uint8_t  bLength;           /**< Size of Descriptor in Bytes */
    uint8_t  bDescriptorType;   /**< Endpoint Descriptor  */
    uint8_t  bEndpointAddress;  /**< Endpoint Address:
                                * Bits 0..3 Endpoint Number.
                                * Bits 4..6 Reserved. Set to Zero
                                * Bit 7 Direction 0 = Out, 1 = In (Ignored for Control Endpoints)
                                */
    uint8_t  bmAttributes;      /**< Bitmap:
                                * Bits 0..1 Transfer Type: 00 = Control, 01 = Isochronous, 10 = Bulk, 11 = Interrupt
                                * Bits 2..7 are reserved. If Isochronous endpoint,
                                * Bits 3..2: Synchronization
                                * Type (Iso Mode): 00 = No Synchronization, 01 = Asynchronous, 10 = Adaptive, 11 = Synchronous
                                * Bits 5..4 = Usage Type (Iso Mode): 00 = Data Endpoint, 01 = Feedback Endpoint,
                                *  10 = Explicit Feedback Data Endpoint, 11 = Reserved
                                */
    uint16_t wMaxPacketSize;    /**< Maximum Packet Size this endpoint is capable of sending or receiving */
    uint8_t  bInterval;         /**< Interval for polling endpoint data transfers. Value in frame counts.
                                * Ignored for Bulk & Control Endpoints.
                                * Isochronous must equal 1 and field may range from 1 to 255 for interrupt endpoints.
                                */
} cy_stc_usbdev_endpoint_descr_t;

/** \} group_usb_dev_structures_device_descr */


/*******************************************************************************
*          Macro for generation code usage
*******************************************************************************/

/**
* \addtogroup group_usb_dev_macros_device_descr
* \{
*/
#define CY_USB_DEV_USB_VERSION_2_0        (0x0200U)       /**< USB Specification Release Number 2.0 */
#define CY_USB_DEV_USB_VERSION_2_1        (0x0201U)       /**< USB Specification Release Number 2.1 */

/* USB v2.0 spec: Table 9-5. Descriptor Types */
#define CY_USB_DEV_DEVICE_DESCR           (1U)    /**< Device Descriptor type */
#define CY_USB_DEV_CONFIG_DESCR           (2U)    /**< Device Configuration Descriptor type */
#define CY_USB_DEV_STRING_DESCR           (3U)    /**< Device String Descriptor type */
#define CY_USB_DEV_INTERFACE_DESCR        (4U)    /**< Device Interface Descriptor type */
#define CY_USB_DEV_ENDPOINT_DESCR         (5U)    /**< Device Endpoint Descriptor type */
#define CY_USB_DEV_DEVICE_QUALIFIER_DESCR (6U)    /**< Device Qualifier Descriptor type */
#define CY_USB_DEV_OTHER_SPEED_CFG_DESCR  (7U)    /**< Device Other Speed Descriptor type */
#define CY_USB_DEV_INTERFACE_POWER_DESCR  (8U)    /**< Device Interface Power Descriptor type */
#define CY_USB_DEV_BOS_DESCR              (15U)   /**< Device BOS Descriptor type */

/* MS OS String Descriptors */
#define CY_USB_DEV_MS_OS_STRING_EXT_COMPAT_ID   (4U)    /**< Extended Compat ID OS Descriptor */
#define CY_USB_DEV_MS_OS_STRING_EXT_PROPERTEIS  (5U)    /**< Extended Properties OS Descriptor */

/* Standard descriptor lengths */
#define CY_USB_DEV_DEVICE_DESCR_LENGTH    (18U)   /**< Device Descriptor length */
#define CY_USB_DEV_CONFIG_DESCR_LENGTH    (9U)    /**< Device Configuration Descriptor length */
#define CY_USB_DEV_INTERFACE_DESCR_LENGTH (9U)    /**< Device Interface Descriptor length */
#define CY_USB_DEV_ENDPOINT_DESCR_LENGTH  (7U)    /**< Device Endpoint Descriptor length */
#define CY_USB_DEV_BOS_DESCR_LENGTH       (5U)    /**< Device BOS Descriptor length */

/* String Language ID length */
#define CY_USB_DEV_STRING_DESCR_LANG_ID_LENGTH   (4U) /**< Device String LANG ID Descriptor length */

/* bmAttributes in endpoint descriptor */
#define CY_USB_DEV_EP_CONTROL         (0x00U)     /**< Control Transfer type */
#define CY_USB_DEV_EP_ISOCHRONOUS     (0x01U)     /**< Isochronous Transfer type  */
#define CY_USB_DEV_EP_BULK            (0x02U)     /**< Bulk Transfer type  */
#define CY_USB_DEV_EP_INTERRUPT       (0x03U)     /**< Interrupt Transfer type  */
#define CY_USB_DEV_EP_TRANS_TYPE_MASK (0x03U)     /**< Transfer type mask */

/* For isochronous endpoints only */
#define CY_USB_DEV_EP_NO_SYNCHRONIZATION    (0x00U)   /**< No Synchronization of Isochronous endpoint */
#define CY_USB_DEV_EP_ASYNCHRONOUS          (0x04U)   /**< Asynchronous Isochronous endpoint */
#define CY_USB_DEV_EP_ADAPTIVE              (0x08U)   /**< Adaptive Isochronous endpoint */
#define CY_USB_DEV_EP_SYNCHRONOUS           (0x0CU)   /**< Synchronous Isochronous endpoint */
#define CY_USB_DEV_EP_DATA                  (0x00U)   /**< Data Isochronous endpoint */
#define CY_USB_DEV_EP_FEEDBACK              (0x10U)   /**< Feedback Isochronous endpoint */
#define CY_USB_DEV_EP_IMPLICIT_FEEDBACK     (0x20U)   /**< Implicit feedback Isochronous endpoint */

/** \} group_usb_dev_macros_device_descr */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */

#endif /* (CY_USB_DEV_DESCR_H) */


/* [] END OF FILE */
