/**
 *******************************************************************************
 * @file  usb_dev_cdc_msc_wrapper.c
 * @brief USB composite functions.
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
#include "usb_dev_cdc_class.h"
#include "usb_dev_msc_class.h"
#include "usb_dev_cdc_msc_wrapper.h"
#include "usb_dev_desc.h"
#include "usb_dev_stdreq.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CLASS LL USB Device Class
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CDC_MSC_COMPOSITE USB Device CDC MSC Composite
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
void usb_dev_msc_cdc_init(void *pdev);
void usb_dev_msc_cdc_deinit(void *pdev);
uint8_t usb_dev_msc_cdc_setup(void *pdev, USB_SETUP_REQ *req);
void usb_dev_msc_cdc_datain(void *pdev, uint8_t epnum);
void usb_dev_msc_cdc_dataout(void *pdev, uint8_t epnum);
uint8_t *usb_dev_msc_cdc_getcfgdesc(uint16_t *length);
uint8_t usb_dev_msc_cdc_sof(void *pdev);
void usb_dev_msc_cdc_ctrlep_rxready(void *pdev);

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
usb_dev_class_func usb_dev_composite_cbk = {
    &usb_dev_msc_cdc_init,
    &usb_dev_msc_cdc_deinit,
    &usb_dev_msc_cdc_setup,
    NULL,
    &usb_dev_msc_cdc_ctrlep_rxready,
    &usb_dev_msc_cdc_getcfgdesc,
    &usb_dev_msc_cdc_sof,
    &usb_dev_msc_cdc_datain,
    &usb_dev_msc_cdc_dataout,
    NULL,
    NULL,
};

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
__USB_ALIGN_BEGIN static uint8_t usb_dev_msc_cdc_cfgdesc[USB_MSC_CDC_CONFIG_DESC_SIZ] = {
    0x09,                          /* bLength: Configuration Descriptor size */
    USB_CFG_DESCRIPTOR_TYPE,       /* bDescriptorType: Configuration */
    USB_MSC_CDC_CONFIG_DESC_SIZ,   /* wTotalLength: Bytes returned */
    0x00,
    0x03,                          /* bNumInterfaces: 2 interface */
    0x01,                          /* bConfigurationValue: Configuration value */
    0x00,                          /* iConfiguration: Index of string descriptor describing the configuration */
    0xC0,                          /* bmAttributes: bus powered and Support Remote Wake-up */
    0x32,                          /* MaxPower 100 mA: this current is used for detecting Vbus */

    /* IAD for CDC configuration descriptor */
    0x08,                          /* bLength */
    0x0B,                          /* bDescriptorType */
    0x00,                          /* bFirstInterface */
    0x02,                          /* bInterfaceCount */
    0x02,                          /* bFunctionClass */
    0x02,                          /* bFunctionSubClass */
    0x01,                          /* bFunctionProtocol */
    0x00,                          /* iFunction (Index of string descriptor describing this function) */
    /* CDC configuration descriptor */
    /* interface descriptor */
    0x09,                          /* bLength: Interface Descriptor size */
    0x04,                          /* bDescriptorType: Interface */
    0x00,                          /* bInterfaceNumber: Number of Interface */
    0x00,                          /* bAlternateSetting: Alternate setting */
    0x01,                          /* bNumEndpoints: One endpoints used */
    0x02,                          /* bInterfaceClass: Communication Interface Class */
    0x02,                          /* bInterfaceSubClass: Abstract Control Model */
    0x01,                          /* bInterfaceProtocol: Common AT commands */
    0x00,                          /* iInterface: */
    /* Header Functional Descriptor */
    0x05,                          /* bLength: Endpoint Descriptor size */
    0x24,                          /* bDescriptorType: CS_INTERFACE */
    0x00,                          /* bDescriptorSubtype: Header Func Desc */
    0x10,                          /* bcdCDC: spec release number */
    0x01,
    /* Call Management Functional Descriptor */
    0x05,                          /* bFunctionLength */
    0x24,                          /* bDescriptorType: CS_INTERFACE */
    0x01,                          /* bDescriptorSubtype: Call Management Func Desc */
    0x00,                          /* bmCapabilities: D0+D1 */
    0x01,                          /* bDataInterface: 1 */
    /* ACM Functional Descriptor */
    0x04,                          /* bFunctionLength */
    0x24,                          /* bDescriptorType: CS_INTERFACE */
    0x02,                          /* bDescriptorSubtype: Abstract Control Management desc */
    0x02,                          /* bmCapabilities */
    /* Union Functional Descriptor */
    0x05,                          /* bFunctionLength */
    0x24,                          /* bDescriptorType: CS_INTERFACE */
    0x06,                          /* bDescriptorSubtype: Union func desc */
    0x00,                          /* bMasterInterface: Communication class interface */
    0x01,                          /* bSlaveInterface0: Data Class Interface */
    /* Endpoint 2 Descriptor */
    0x07,                           /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */
    CDC_CMD_EP,                     /* bEndpointAddress */
    0x03,                           /* bmAttributes: Interrupt */
    LOBYTE(CDC_CMD_PACKET_SIZE),     /* wMaxPacketSize: */
    HIBYTE(CDC_CMD_PACKET_SIZE),
    0xFF,                           /* bInterval: */
    /* Data class interface descriptor */
    0x09,                           /* bLength: Endpoint Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: */
    0x01,                           /* bInterfaceNumber: Number of Interface */
    0x00,                           /* bAlternateSetting: Alternate setting */
    0x02,                           /* bNumEndpoints: Two endpoints used */
    0x0A,                           /* bInterfaceClass: CDC */
    0x00,                           /* bInterfaceSubClass: */
    0x00,                           /* bInterfaceProtocol: */
    0x00,                           /* iInterface: */
    /* Endpoint OUT Descriptor */
    0x07,                           /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */
    CDC_OUT_EP,                     /* bEndpointAddress */
    0x02,                           /* bmAttributes: Bulk */
    LOBYTE(MAX_CDC_PACKET_SIZE),    /* wMaxPacketSize: */
    HIBYTE(MAX_CDC_PACKET_SIZE),
    0x00,                           /* bInterval: ignore for Bulk transfer */
    /* Endpoint IN Descriptor */
    0x07,                           /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */
    CDC_IN_EP,                      /* bEndpointAddress */
    0x02,                           /* bmAttributes: Bulk */
    LOBYTE(MAX_CDC_PACKET_SIZE),    /* wMaxPacketSize: */
    HIBYTE(MAX_CDC_PACKET_SIZE),
    0x00,

    /* Mass Storage interface ********************/
    0x09,                           /* bLength: Interface Descriptor size */
    0x04,                           /* bDescriptorType: */
    0x02,                           /* bInterfaceNumber: Number of Interface */
    0x00,                           /* bAlternateSetting: Alternate setting */
    0x02,                           /* bNumEndpoints*/
    0x08,                           /* bInterfaceClass: MSC Class */
    0x06,                           /* bInterfaceSubClass : SCSI transparent*/
    0x50,                           /* nInterfaceProtocol */
    0x05,                           /* iInterface: */
    /* Mass Storage Endpoints ********************/
    0x07,                           /* Endpoint descriptor length = 7 */
    0x05,                           /* Endpoint descriptor type */
    MSC_IN_EP,                      /* Endpoint address (IN, address 1) */
    0x02,                           /* Bulk endpoint type */
    LOBYTE(MSC_MAX_PACKET),
    HIBYTE(MSC_MAX_PACKET),
    0x00,                           /* Polling interval in milliseconds */

    0x07,                           /* Endpoint descriptor length = 7 */
    0x05,                           /* Endpoint descriptor type */
    MSC_OUT_EP,                     /* Endpoint address (OUT, address 1) */
    0x02,                           /* Bulk endpoint type */
    LOBYTE(MSC_MAX_PACKET),
    HIBYTE(MSC_MAX_PACKET),
    0x00                            /* Polling interval in milliseconds*/
} ;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Initialize the composite device of MSC-HID interface
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_dev_msc_cdc_init(void *pdev)
{
    usb_dev_cdc_init(pdev);
    usb_dev_msc_init(pdev);
}

/**
 * @brief  de-initialize the composite device of MSC-HID interface
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_dev_msc_cdc_deinit(void *pdev)
{
    usb_dev_cdc_deinit(pdev);
    usb_dev_msc_deinit(pdev);
}

/**
 * @brief  process the setup requests
 * @param  [in] pdev        device instance
 * @param  [in] req         setup request
 * @retval status
 */
uint8_t usb_dev_msc_cdc_setup(void *pdev, USB_SETUP_REQ *req)
{
    uint8_t u8Res = USB_DEV_OK;
    switch (req->bmRequest & USB_REQ_RECIPIENT_MASK) {
        case USB_REQ_RECIPIENT_INTERFACE:
            if (req->wIndex == 0x02U) {
                u8Res = usb_dev_msc_setup(pdev, req);
            } else {
                u8Res = usb_dev_cdc_setup(pdev, req);
            }
            break;

        case USB_REQ_RECIPIENT_ENDPOINT:
            if (req->wIndex == CDC_IN_EP) {
                u8Res = usb_dev_cdc_setup(pdev, req);
            } else {
                u8Res = usb_dev_msc_setup(pdev, req);
            }
            break;
        default:
            break;
    }
    return u8Res;
}

/**
 * @brief  Data received on control endpoint
 * @param  [in] pdev        device device instance
 * @retval None
 */
void usb_dev_msc_cdc_ctrlep_rxready(void *pdev)
{
    usb_dev_cdc_ctrlep_rxready(pdev);
}

/**
 * @brief  process the sof
 * @param  [in] pdev        device instance
 * @retval status
 */
uint8_t usb_dev_msc_cdc_sof(void *pdev)
{
    return usb_dev_cdc_sof(pdev);
}

/**
 * @brief  process data IN DATA
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_dev_msc_cdc_datain(void *pdev, uint8_t epnum)
{
    if (epnum == (uint8_t)(MSC_IN_EP & ((uint8_t)~0x80U))) {
        usb_dev_msc_datain(pdev, epnum);
    } else {
        usb_dev_cdc_datain(pdev, epnum);
    }
}

/**
 * @brief  process data OUT DATA
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_dev_msc_cdc_dataout(void *pdev, uint8_t epnum)
{
    if (epnum == (uint8_t)(MSC_OUT_EP & ((uint8_t)~0x80U))) {
        usb_dev_msc_dataout(pdev, epnum);
    } else {
        usb_dev_cdc_dataout(pdev, epnum);
    }
}

/**
 * @brief  get the configuration descriptor
 * @param  [in] length      length of data butter in bytes
 * @retval buffer pointer
 */
uint8_t *usb_dev_msc_cdc_getcfgdesc(uint16_t *length)
{
    *length = (uint16_t)sizeof(usb_dev_msc_cdc_cfgdesc);
    return usb_dev_msc_cdc_cfgdesc;
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
