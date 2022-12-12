/**
 *******************************************************************************
 * @file  usb_dev_hid_cdc_wrapper.c
 * @brief HID CDC composite functions.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_dev_custom_hid_class.h"
#include "usb_dev_cdc_class.h"
#include "usb_dev_hid_cdc_wrapper.h"
#include "usb_dev_desc.h"
#include "usb_dev_stdreq.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_HID_CDC_COMPOSITE USB Device HID CDC Composite
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define USB_COMPOSITE_CFGDESC_SIZE  (USB_CUSTOM_HID_CONFIG_DESC_SIZ - 9U + USB_CDC_CONFIG_DESC_SIZ  + 8U)

#define HID_INTERFACE       (0x0U)
#define CDC_COM_INTERFACE   (0x1U)


/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
void    usb_dev_composite_init(void *pdev);
void    usb_dev_composite_deinit(void *pdev);
uint8_t usb_dev_composite_setup(void *pdev, USB_SETUP_REQ *req);
void    usb_dev_composite_rxready(void *pdev);
void    usb_dev_composite_datain(void *pdev, uint8_t epnum);
void    usb_dev_composite_dataout(void *pdev, uint8_t epnum);
uint8_t usb_dev_composite_sof(void *pdev);
uint8_t *usb_dev_composite_getcfgdesc(uint16_t *length);


/*******************************************************************************
 * Global variable definitions
 ******************************************************************************/
usb_dev_class_func  class_composite_cbk = {
    &usb_dev_composite_init,
    &usb_dev_composite_deinit,
    &usb_dev_composite_setup,
    NULL,
    &usb_dev_composite_rxready,
    &usb_dev_composite_getcfgdesc,
    &usb_dev_composite_sof,
    &usb_dev_composite_datain,
    &usb_dev_composite_dataout,
    NULL,
    NULL,
};

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
__USB_ALIGN_BEGIN static uint8_t usb_dev_composite_cfgdesc[USB_COMPOSITE_CFGDESC_SIZE] = {
    0x09,                              /* bLength: Configuration Descriptor size */
    USB_CFG_DESCRIPTOR_TYPE,           /* bDescriptorType: Configuration */
    USB_COMPOSITE_CFGDESC_SIZE,        /* wTotalLength: Bytes returned */
    0x00,
    0x03,                              /* bNumInterfaces: 3 interfaces (2 for CDC, 1 for HID) */
    0x01,                              /* bConfigurationValue: Configuration value */
    0x00,                              /* iConfiguration: Index of string descriptor describing the configuration */
    0xE0,                              /* bmAttributes: bus powered and Support Remote Wake-up */
    0x32,                              /* MaxPower 100 mA: this current is used for detecting Vbus */
    /* 09 */
    /************** Descriptor of HID interface ****************/
    0x09,                              /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,     /* bDescriptorType: Interface descriptor type */
    HID_INTERFACE,                     /* bInterfaceNumber: Number of Interface */
    0x00,                              /* bAlternateSetting: Alternate setting */
    0x02,                              /* bNumEndpoints */
    0x03,                              /* bInterfaceClass: HID */
    0x01,                              /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x02,                              /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0x00,                              /* iInterface: Index of string descriptor */
    /* 18 */
    /******************** Descriptor of HID ********************/
    0x09,                              /* bLength: HID Descriptor size */
    CUSTOM_HID_DESCRIPTOR_TYPE,        /* bDescriptorType: HID*/
    0x11,                              /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,                              /* bCountryCode: Hardware target country */
    0x01,                              /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,                              /* bDescriptorType */
    CUSTOM_HID_REPORT_DESC_SIZE,       /* wItemLength: Total length of Report descriptor */
    0x00,
    /* 27 */
    /******************** Descriptor of HID endpoint ********************/
    0x07,                              /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType: */
    HID_IN_EP,                         /* bEndpointAddress: Endpoint Address (IN) */
    0x03,                              /* bmAttributes: Interrupt endpoint */
    HID_IN_PACKET,                     /* wMaxPacketSize: 64 Byte max */
    0x00,
    0x0A,                              /* bInterval: Polling Interval (10 ms) */
    /* 34 */
    0x07,                              /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType: */
    HID_OUT_EP,                        /* bEndpointAddress: Endpoint Address (IN) */
    0x03,                              /* bmAttributes: Interrupt endpoint */
    HID_OUT_PACKET,                    /* wMaxPacketSize: 64 Byte max */
    0x00,
    0x0A,                              /* bInterval: Polling Interval (10 ms) */
    /* 41 */
    /******** IAD should be positioned just before the CDC interfaces *******/
    0x08,                              /* bLength */
    0x0B,                              /* bDescriptorType */
    0x01,                              /* bFirstInterface */
    0x02,                              /* bInterfaceCount */
    0x02,                              /* bFunctionClass */
    0x02,                              /* bFunctionSubClass */
    0x01,                              /* bFunctionProtocol */
    0x00,                              /* iFunction (Index of string descriptor describing this function) */
    /*49*/
    /*Interface Descriptor */
    0x09,                              /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,     /* bDescriptorType: Interface */
    CDC_COM_INTERFACE,                 /* bInterfaceNumber: Number of Interface */
    0x00,                              /* bAlternateSetting: Alternate setting */
    0x01,                              /* bNumEndpoints: One endpoints used */
    0x02,                              /* bInterfaceClass: Communication Interface Class */
    0x02,                              /* bInterfaceSubClass: Abstract Control Model */
    0x01,                              /* bInterfaceProtocol: Common AT commands */
    0x01,                              /* iInterface: */
    /*58*/
    /*Header Functional Descriptor*/
    0x05,                              /* bLength: Endpoint Descriptor size */
    0x24,                              /* bDescriptorType: CS_INTERFACE */
    0x00,                              /* bDescriptorSubtype: Header Func Desc */
    0x10,                              /* bcdCDC: spec release number */
    0x01,
    /*63*/
    /*Call Management Functional Descriptor*/
    0x05,                              /* bFunctionLength */
    0x24,                              /* bDescriptorType: CS_INTERFACE */
    0x01,                              /* bDescriptorSubtype: Call Management Func Desc */
    0x00,                              /* bmCapabilities: D0+D1 */
    0x02,                              /* bDataInterface: 2 */
    /*68*/
    /*ACM Functional Descriptor*/
    0x04,                              /* bFunctionLength */
    0x24,                              /* bDescriptorType: CS_INTERFACE */
    0x02,                              /* bDescriptorSubtype: Abstract Control Management desc */
    0x02,                              /* bmCapabilities */
    /*72*/
    /*Union Functional Descriptor*/
    0x05,                              /* bFunctionLength */
    0x24,                              /* bDescriptorType: CS_INTERFACE */
    0x06,                              /* bDescriptorSubtype: Union func desc */
    0x01,                              /* bMasterInterface: Communication class interface */
    0x02,                              /* bSlaveInterface0: Data Class Interface */
    /*77*/
    /*Endpoint 2 Descriptor*/
    0x07,                              /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType: Endpoint */
    CDC_CMD_EP,                        /* bEndpointAddress */
    0x03,                              /* bmAttributes: Interrupt */
    LOBYTE(CDC_CMD_PACKET_SIZE),       /* wMaxPacketSize: */
    HIBYTE(CDC_CMD_PACKET_SIZE),
    0xFF,                              /* bInterval: */
    /*84*/
    /*---------------------------------------------------------------------------*/

    /*Data class interface descriptor*/
    0x09,                              /* bLength: Endpoint Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,     /* bDescriptorType: */
    0x02,                              /* bInterfaceNumber: Number of Interface */
    0x00,                              /* bAlternateSetting: Alternate setting */
    0x02,                              /* bNumEndpoints: Two endpoints used */
    0x0A,                              /* bInterfaceClass: CDC */
    0x00,                              /* bInterfaceSubClass: */
    0x00,                              /* bInterfaceProtocol: */
    0x00,                              /* iInterface: */
    /*93*/
    /*Endpoint OUT Descriptor*/
    0x07,                              /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType: Endpoint */
    CDC_OUT_EP,                        /* bEndpointAddress */
    0x02,                              /* bmAttributes: Bulk */
    LOBYTE(MAX_CDC_PACKET_SIZE),       /* wMaxPacketSize: */
    HIBYTE(MAX_CDC_PACKET_SIZE),
    0x00,                              /* bInterval: ignore for Bulk transfer */
    /*100*/
    /*Endpoint IN Descriptor*/
    0x07,                              /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType: Endpoint */
    CDC_IN_EP,                         /* bEndpointAddress */
    0x02,                              /* bmAttributes: Bulk */
    LOBYTE(MAX_CDC_PACKET_SIZE),       /* wMaxPacketSize: */
    HIBYTE(MAX_CDC_PACKET_SIZE),
    0x00,                              /* bInterval */
    /*107*/
} ;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Initialize the composite app
 * @param  [in] pdev        Device instance
 * @retval None
 */
void usb_dev_composite_init(void *pdev)
{
    usb_dev_hid_init(pdev);
    usb_dev_cdc_init(pdev);
}

/**
 * @brief  Deinitialize the composite app
 * @param  [in] pdev        Device instance
 * @retval None
 */
void usb_dev_composite_deinit(void *pdev)
{
    usb_dev_hid_deinit(pdev);
    usb_dev_cdc_deinit(pdev);
}

/**
 * @brief  Handle the setup requests
 * @param  [in] pdev        Device instance
 * @param  [in] req         usb requests
 * @retval status
 */
uint8_t usb_dev_composite_setup(void *pdev, USB_SETUP_REQ *req)
{
    uint8_t u8Res = USB_DEV_OK;
    switch (req->bmRequest & USB_REQ_RECIPIENT_MASK) {
        case USB_REQ_RECIPIENT_INTERFACE:
            if (req->wIndex == HID_INTERFACE) {
                u8Res = usb_dev_hid_setup(pdev, req);
            } else {
                u8Res = usb_dev_cdc_setup(pdev, req);
            }
            break;

        case USB_REQ_RECIPIENT_ENDPOINT:
            if (req->wIndex == HID_IN_EP) {
                u8Res = usb_dev_hid_setup(pdev, req);
            } else {
                u8Res = usb_dev_cdc_setup(pdev, req);
            }
            break;
        default:
            break;
    }
    return u8Res;
}

/**
 * @brief  get the configuration descriptor and return the its pointer
 * @param  [in] length      length of configuration descriptor
 * @retval the pointer of configuration descriptor buffer
 */
uint8_t *usb_dev_composite_getcfgdesc(uint16_t *length)
{
    *length = (uint16_t)sizeof(usb_dev_composite_cfgdesc);
    return usb_dev_composite_cfgdesc;
}

/**
 * @brief  processing for data in
 * @param  [in] pdev        Device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_dev_composite_datain(void *pdev, uint8_t epnum)
{
    if (epnum == ((uint8_t)CDC_IN_EP & ((uint8_t)~0x80U))) {
        usb_dev_cdc_datain(pdev, epnum);
    } else {
        usb_dev_hid_datain(pdev, epnum);
    }
}

/**
 * @brief  processing for data out
 * @param  [in] pdev        Device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_dev_composite_dataout(void *pdev, uint8_t epnum)
{
    if (epnum == ((uint8_t)CDC_OUT_EP & (uint8_t)~0x80U)) {
        usb_dev_cdc_dataout(pdev, epnum);
    } else {
        usb_dev_hid_dataout(pdev, epnum);
    }
}

/**
 * @brief  processing for sof
 * @param  [in] pdev        Device instance
 * @retval status
 */
uint8_t usb_dev_composite_sof(void *pdev)

{
    return (usb_dev_cdc_sof(pdev));
}

/**
 * @brief  processing for rxready of control endpoint
 * @param  [in] pdev        Device instance
 * @retval None
 */
void usb_dev_composite_rxready(void *pdev)
{
    usb_dev_cdc_ctrlep_rxready(pdev);
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
