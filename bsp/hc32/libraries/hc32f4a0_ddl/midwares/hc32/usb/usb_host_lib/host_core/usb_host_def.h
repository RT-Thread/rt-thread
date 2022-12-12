/**
 *******************************************************************************
 * @file  usb_host_def.h
 * @brief Definitions used in the USB host library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __USB_HOST_DEF_H__
#define __USB_HOST_DEF_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <stdint.h>
#include "usb_app_conf.h"
#include "usb_lib.h"
#include "hc32_ll.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CORE
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/*  This Union is copied from usb_core.h  */
typedef union {
    uint16_t w;
    struct BW {
        uint8_t msb;
        uint8_t lsb;
    }
    bw;
} uint16_t_uint8_t;
/* standard setup packet defination */
typedef union {
    uint8_t d8[8];
    struct _SetupPkt_Struc {
        uint8_t           bmRequestType;
        uint8_t           bRequest;
        uint16_t_uint8_t  wValue;
        uint16_t_uint8_t  wIndex;
        uint16_t_uint8_t  wLength;
    } b;
} usb_setup_typedef;

typedef  struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
} USB_HOST_DescHeader_TypeDef;

/* Standard Device Descriptor */
typedef struct {
    uint8_t   bLength;            /* Size of this descriptor in bytes */
    uint8_t   bDescriptorType;    /* Device descriptor type */
    uint16_t  bcdUSB;             /* USB Specification Release Numbrer in Binary-Coded Decimal(i.e.,2.10 is 210H) */
    uint8_t   bDeviceClass;       /* Class code(assigned by the USB-IF) */
    uint8_t   bDeviceSubClass;    /* Subclass code(assigned by the USB-IF) this code is qualified by the value of the \
                                     bDeviceClass field. */
    uint8_t   bDeviceProtocol;    /* Protocol code(assigned by the USB-IF), this code is qualified by the value of the \
                                     bDeviceClass and the bDeviceSubClass fields. */
    uint8_t   bMaxPacketSize0;    /* Maximum packet size for EP0 */
    uint16_t  idVendor;           /* Vendor ID (assigned by the USB-IF) */
    uint16_t  idProduct;          /* Product ID (assigned by manufacturer) */
    uint16_t  bcdDevice;          /* Device Release Number in binary-coded decimal */
    uint8_t   iManufacturer;      /* Index of string descriptor describing manufacturer */
    uint8_t   iProduct;           /* Index of string descriptor describing product */
    uint8_t   iSerialNumber;      /* Index of string descriptor describing the device's serial number */
    uint8_t   bNumConfigurations; /* Number of possible configurations */
} usb_host_devdesc_typedef;

/* Standard Configuration Descriptor */
typedef struct {
    uint8_t   bLength;             /* Size of this descriptor in bytes */
    uint8_t   bDescriptorType;     /* CONFIGURATION descriptor type */
    uint16_t  wTotalLength;        /* Total length of data returned for this configuration */
    uint8_t   bNumInterfaces;      /* Number of interfaces supported by this configuration */
    uint8_t   bConfigurationValue; /* Value to use as an argument to the SetConfiguration() request to select this configuration */
    uint8_t   iConfiguration;      /* Index of string descriptor describing this configuration */
    uint8_t   bmAttributes;        /* Configuration characteristics: D7:Reserved(set to one) D6:Self-powered D5:Remote Wakeup D4..0 Reserved(set to zero) */
    uint8_t   bMaxPower;           /* Maximum power consumption of the device from the bus in this specific configuration when the device is fully operational */
} usb_host_cfgdesc_typedef;

typedef struct {
    uint8_t   bLength;
    uint8_t   bDescriptorType;
    uint16_t  bcdHID;              /* indicates what endpoint this descriptor is describing */
    uint8_t   bCountryCode;        /* specifies the transfer type. */
    uint8_t   bNumDescriptors;     /* specifies the transfer type. */
    uint8_t   bReportDescriptorType;  /* Maximum Packet Size this endpoint is capable of sending or receiving */
    uint16_t  wItemLength;         /* is used to specify the polling interval of certain transfers. */
} USB_HOST_HIDDesc_TypeDef;

/* Standard Interface Descriptor */
typedef struct {
    uint8_t bLength;              /* Size of this descriptor in bytes */
    uint8_t bDescriptorType;      /* INTERFACE Descriptor Type */
    uint8_t bInterfaceNumber;     /* Number of this interface */
    uint8_t bAlternateSetting;    /* Value used to select this alternate setting for the interface identifiled in the \
                                     prior field */
    uint8_t bNumEndpoints;        /* Number of Endpoints used by this interface */
    uint8_t bInterfaceClass;      /* Class code (assigned by the USB-IF) */
    uint8_t bInterfaceSubClass;   /* Subclass code (assigned by the USB-IF) */
    uint8_t bInterfaceProtocol;   /* Protocol code (assigned by the USB) */
    uint8_t iInterface;           /* Index of string descriptor describing this interface */
} usb_host_itfdesc_typedef;

/* Standard Endpoint Descriptor */
typedef struct {
    uint8_t   bLength;           /* Size of this descriptor in bytes */
    uint8_t   bDescriptorType;   /* ENDPOINT descriptor type */
    uint8_t   bEndpointAddress;  /* The address of the endpoint on the device described by this descriptor */
    uint8_t   bmAttributes;      /* refer to the related standard of USB 2.0 */
    uint16_t  wMaxPacketSize;    /* Maximum Packet Size this endpoint is capable of sending or receiving when this \
                                    configuration is selected */
    uint8_t   bInterval;         /* Interval for servicing the endpoint for data transfers */
} USB_HOST_EPDesc_TypeDef;

/* USBH_CORE_Exported_Types */
/* Host status */
typedef enum {
    HSTATUS_OK = 0,
    HSTATUS_BUSY,
    HSTATUS_FAIL,
    HSTATUS_UNSUPPORTED,
    HSTATUS_UNRECOVERED_ERROR,
    HSTATUS_SPEED_UNKNOWN,
    HSTATUS_APP_DEINIT
} HOST_STATUS;

/* states about the handle stages on the host side */
typedef enum {
    HOST_IDLE = 0,
    HOST_DEV_CONNECTED,
    HOST_DEV_DISCONNECTED,
    HOST_GET_DEVSPEED,
    HOST_ENUM,
    HOST_CLASS_REQ,
    HOST_CLASS_PROCESS,
    HOST_CTRL_TRANSMIT,
    HOST_USER_INPUT,
    HOST_SUSPENDED,
    HOST_ERROR_STATE
} HOST_HANDLE_STATE;


/* states of the enumeration stage on the host side */
typedef enum {
    ENUM_IDLE = 0,
    ENUM_GET_FULL_DEVDESC,
    ENUM_SET_DEVADDR,
    ENUM_GET_CFGDESC,
    ENUM_GET_FULL_CFGDESC,
    ENUM_GET_MFCSTRINGDESC,
    ENUM_GET_PRODUCT_STRINGDESC,
    ENUM_GET_SERIALNUM_STRINGDESC,
    ENUM_SET_CFG,
    ENUM_DEV_CFG_OVER
} ENUM_HANDLE_STATE;

/* states of the control stages on the host side */
typedef enum {
    CTRL_IDLE = 0,
    CTRL_SETUP,
    CTRL_SETUP_WAIT,
    CTRL_DATA_IN,
    CTRL_DATA_IN_WAIT,
    CTRL_DATA_OUT,
    CTRL_DATA_OUT_WAIT,
    CTRL_STATUS_IN,
    CTRL_STATUS_IN_WAIT,
    CTRL_STATUS_OUT,
    CTRL_STATUS_OUT_WAIT,
    CTRL_ERROR,
    CTRL_STALLED,
    CTRL_COMPLETE
} CTRL_HANDLE_STATE;

/* Following states are state machine for the request transferring */
typedef enum {
    REQ_CMD_IDLE = 0,
    REQ_CMD_TX,
    REQ_CMD_WAIT
} REQ_HANDLE_STATE;

typedef enum {
    USER_HAVE_RESP = 0,
    USER_NONE_RESP
} HOST_USER_STATUS;

typedef struct {
    uint8_t               hc_num_in;         /* channel number for the IN EP */
    uint8_t               hc_num_out;        /* channel number for the OUT EP */
    uint8_t               ctrlmaxsize;       /* the max size of EP0 parsed from the device descriptor */
    uint8_t               err_cnt;           /* the error counter */
    uint16_t              sof_num;           /* the frame number for sof packet */
    uint16_t              length;            /* length of data in byte */
    uint8_t               *buff;             /* data buffer */
    CTRL_HANDLE_STATUS    ctrl_status;       /* status of control pipe */
    CTRL_HANDLE_STATE     ctrl_state;        /* running state of the control transfer */
    usb_setup_typedef     setup;             /* setup packet */
} usb_host_ctrl_param;

/* Device information parsed from the related descriptors requested from the connected device
   the following data are all parsed from the data sent by the connnected device */
typedef struct {
    uint8_t                  devaddr;      /* the address of the connected device */
    uint8_t                  devspeed;     /* the core speed of the connected device */
    usb_host_devdesc_typedef devdesc;      /* the device descriptor parsed from the data sent by device */
    usb_host_cfgdesc_typedef devcfgdesc;   /* the device configuration descriptor parsed from the data sent by device */
    usb_host_itfdesc_typedef devitfdesc[USBH_MAX_NUM_INTERFACES];  /* the interface descritpor */
    USB_HOST_EPDesc_TypeDef  devepdesc[USBH_MAX_NUM_INTERFACES][USBH_MAX_NUM_ENDPOINTS];  /* the endpoint descriptor */
    USB_HOST_HIDDesc_TypeDef hiddesc;      /* the hid descriptor */
} usb_host_devinformation;

typedef struct {
    HOST_STATUS(*host_class_init)(usb_core_instance *pdev, void *phost);
    void (*host_class_deinit)(usb_core_instance *pdev);
    HOST_STATUS(*host_class_request)(usb_core_instance *pdev, void *phost);
    HOST_STATUS(*host_class_process)(usb_core_instance *pdev, void *phost);
} usb_host_class_callback_func;

typedef struct {
    void (*huser_init)(void);
    void (*huser_deinit)(void);
    void (*huser_devattached)(void);
    void (*huser_devreset)(void);
    void (*huser_devdisconn)(void);
    void (*huser_overcurrent)(void);
    void (*huser_devspddetected)(uint8_t DeviceSpeed);
    void (*huser_devdescavailable)(void *);
    void (*huser_devaddrdistributed)(void);
    void (*huser_cfgdescavailable)(usb_host_cfgdesc_typedef *,
                                   usb_host_itfdesc_typedef *,
                                   USB_HOST_EPDesc_TypeDef *);
    /* Configuration Descriptor available */
    void (*huser_mfcstring)(void *);
    void (*huser_productstring)(void *);
    void (*huser_serialnum)(void *);
    void (*huser_enumcompl)(void);
    HOST_USER_STATUS(*huser_userinput)(void);
    int (*huser_application)(void);
    void (*huser_devunsupported)(void);
    void (*huser_unrecoverederror)(void);
} usb_host_user_callback_func;

typedef struct {
    /* states for the host, enumeration, request */
    REQ_HANDLE_STATE                       req_state;          /* value of state machine about the request */
    ENUM_HANDLE_STATE                      enum_state;         /* state machine while enumerating */
    HOST_HANDLE_STATE                      host_state_backup;  /* backup value of state machine about the host */
    HOST_HANDLE_STATE                      host_state;         /* value of state machine about the host */
    /* control informations */
    usb_host_ctrl_param                    ctrlparam;          /* values about the control parameters */
    /* device information parsed from the descriptors from the device */
    usb_host_devinformation                device_prop;
    /* functions: call back functions for the class and user */
    usb_host_class_callback_func           *class_callbk;
    usb_host_user_callback_func            *user_callbk;
} USBH_HOST;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

#ifndef FALSE
#define FALSE 0U
#endif

#ifndef TRUE
#define TRUE 1U
#endif

/* Get a 16bits data from buffer in little end mode. */
#define  SMALL_END(addr)   (((uint16_t)(*((uint8_t *)(addr)))) + (((uint16_t)(*(((uint8_t *)(addr)) + 1U))) << 8U))

#define  USB_LEN_CFG_DESC                               (0x09U)

/* bmRequestType
D7: Data transfer direction
    0 = Host-to-device
    1 = Device-to-host
*/
#define  USB_REQ_DIR_MASK                               (0x80U)
#define  USB_H2D                                        (0x00U)
#define  USB_D2H                                        (0x80U)

/* bmRequestType
D6...5: Type
        0 = Standard
        1 = Class
        2 = Vendor
        3 = Reserved
*/
#define  USB_REQ_TYPE_STANDARD                          (0x00U)
#define  USB_REQ_TYPE_CLASS                             (0x20U)
#define  USB_REQ_TYPE_VENDOR                            (0x40U)
#define  USB_REQ_TYPE_RESERVED                          (0x60U)

/* bmRequestType
D4...0:  Recipient
         0 = Device
         1 = Interface
         2 = Endpoint
         3 = Other
         4...31 = Reserved
*/
#define  USB_REQ_RECIPIENT_DEVICE                       (0x00U)
#define  USB_REQ_RECIPIENT_INTERFACE                    (0x01U)
#define  USB_REQ_RECIPIENT_ENDPOINT                     (0x02U)
#define  USB_REQ_RECIPIENT_OTHER                        (0x03U)

/* Table 9-4. Standard Request Codes [USB Specification] */
/*      bRequest                                Value    */
#define  USB_REQ_GET_STATUS                             (0x00U)
#define  USB_REQ_CLEAR_FEATURE                          (0x01U)
#define  USB_REQ_SET_FEATURE                            (0x03U)
#define  USB_REQ_SET_ADDRESS                            (0x05U)
#define  USB_REQ_GET_DESCRIPTOR                         (0x06U)
#define  USB_REQ_SET_DESCRIPTOR                         (0x07U)
#define  USB_REQ_GET_CONFIGURATION                      (0x08U)
#define  USB_REQ_SET_CONFIGURATION                      (0x09U)
#define  USB_REQ_GET_INTERFACE                          (0x0AU)
#define  USB_REQ_SET_INTERFACE                          (0x0BU)
#define  USB_REQ_SYNCH_FRAME                            (0x0Cu)

/* Table 9-5. Descriptor Types  [USB Specification]  */
/*   Descriptor Types                               Value    */
#define  USB_DESC_TYPE_DEVICE                            (1U)
#define  USB_DESC_TYPE_CONFIGURATION                     (2U)
#define  USB_DESC_TYPE_STRING                            (3U)
#define  USB_DESC_TYPE_INTERFACE                         (4U)
#define  USB_DESC_TYPE_ENDPOINT                          (5U)
#define  USB_DESC_TYPE_DEVICE_QUALIFIER                  (6U)
#define  USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION         (7U)
#define  USB_DESC_TYPE_INTERFACE_POWER                   (8U)
#define  USB_DESC_TYPE_HID                               (0x21U)
#define  USB_DESC_TYPE_HID_REPORT                        (0x22U)

#define USB_DEVICE_DESC_SIZE                             (18U)
#define USB_CONFIGURATION_DESC_SIZE                      (9U)
#define USB_HID_DESC_SIZE                                (9U)
#define USB_INTERFACE_DESC_SIZE                          (9U)
#define USB_ENDPOINT_DESC_SIZE                           (7U)

/* Descriptor Type and Descriptor Index  */
/* Use the following values when calling the function usb_host_getdesc  */
#define  USB_DESC_DEVICE                    (((uint16_t)USB_DESC_TYPE_DEVICE << 8U) & 0xFF00U)
#define  USB_DESC_CONFIGURATION             (((uint16_t)USB_DESC_TYPE_CONFIGURATION << 8U) & 0xFF00U)
#define  USB_DESC_STRING                    (((uint16_t)USB_DESC_TYPE_STRING << 8U) & 0xFF00U)
#define  USB_DESC_INTERFACE                 (((uint16_t)USB_DESC_TYPE_INTERFACE << 8U) & 0xFF00U)
#define  USB_DESC_ENDPOINT                  (((uint16_t)USB_DESC_TYPE_INTERFACE << 8U) & 0xFF00U)
#define  USB_DESC_DEVICE_QUALIFIER          (((uint16_t)USB_DESC_TYPE_DEVICE_QUALIFIER << 8U) & 0xFF00U)
#define  USB_DESC_OTHER_SPEED_CONFIGURATION (((uint16_t)USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION << 8U) & 0xFF00U)
#define  USB_DESC_INTERFACE_POWER           (((uint16_t)USB_DESC_TYPE_INTERFACE_POWER << 8U) & 0xFF00U)
#define  USB_DESC_HID_REPORT                (((uint16_t)USB_DESC_TYPE_HID_REPORT << 8U) & 0xFF00U)
#define  USB_DESC_HID                       (((uint16_t)USB_DESC_TYPE_HID << 8U) & 0xFF00U)

#define  USB_EP_DIR_OUT                                 (0x00U)
#define  USB_EP_DIR_IN                                  (0x80U)
#define  USB_EP_DIR_MSK                                 (0x80U)

/* supported classes */
#define USB_MSC_CLASS                                   (0x08U)
#define USB_HID_CLASS                                   (0x03U)

/* Interface Descriptor field values for HID Boot Protocol */
#define HID_BOOT_CODE                                  (0x01U)
#define HID_KEYBRD_BOOT_CODE                           (0x01U)
#define HID_MOUSE_BOOT_CODE                            (0x02U)

/* As per USB specs 9.2.6.4 :Standard request with data request timeout: 5sec
   Standard request with no data stage timeout : 50ms */
#define DATA_STAGE_TIMEOUT                              (5000U)
#define NODATA_STAGE_TIMEOUT                            (50U)

/* Macro definations for host mode */
#define PID_DATA0                                       (0U)
#define PID_DATA2                                       (1U)
#define PID_DATA1                                       (2U)
#define PID_SETUP                                       (3U)
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_HOST_DEF_H__ */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
