/**
 *******************************************************************************
 * @file  usb_dev_msc_class.c
 * @brief USB MSC device class
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
#include "usb_dev_msc_mem.h"
#include "usb_dev_msc_class.h"
#include "usb_dev_msc_bot.h"
#include "usb_dev_stdreq.h"
#include "usb_dev_driver.h"
#include "usb_dev_ctrleptrans.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_MSC
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
uint8_t *usb_dev_msc_getcfgdesc(uint16_t *length);

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
usb_dev_class_func usb_dev_msc_cbk = {
    &usb_dev_msc_init,
    &usb_dev_msc_deinit,
    &usb_dev_msc_setup,
    NULL,
    NULL,
    &usb_dev_msc_getcfgdesc,
    NULL,
    &usb_dev_msc_datain,
    &usb_dev_msc_dataout,
    NULL,
    NULL,
};

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t dev_msc_maxlun = 0U;
static uint8_t dev_msc_altset = 0U;

__USB_ALIGN_BEGIN static uint8_t usb_dev_msc_cfgdesc[USB_MSC_CONFIG_DESC_SIZ] = {
    0x09,                        /* bLength: Configuation Descriptor size */
    USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
    USB_MSC_CONFIG_DESC_SIZ,
    0x00,
    0x01,                        /* bNumInterfaces: 1 interface */
    0x01,                        /* bConfigurationValue: */
    0x04,                        /* iConfiguration: */
    0xC0,                        /* bmAttributes: */
    0x32,                        /* MaxPower 100 mA */
    /********************  Mass Storage interface descriptor**********/
    0x09,                        /* bLength: Interface Descriptor size */
    0x04,                        /* bDescriptorType: */
    0x00,                        /* bInterfaceNumber: Number of Interface */
    0x00,                        /* bAlternateSetting: Alternate setting */
    0x02,                        /* bNumEndpoints*/
    0x08,                        /* bInterfaceClass: MSC Class */
    0x06,                        /* bInterfaceSubClass : SCSI transparent*/
    0x50,                        /* nInterfaceProtocol */
    0x05,                        /* iInterface: */
    /********************  Mass Storage Endpoints descriptor**********/
    0x07,                        /* Endpoint descriptor length = 7 */
    0x05,                        /* Endpoint descriptor type  */
    MSC_IN_EP,                   /* Endpoint address (IN, address 1)  */
    0x02,                        /* Bulk endpoint type */
    LOBYTE(MSC_MAX_PACKET),
    HIBYTE(MSC_MAX_PACKET),
    0x00,                        /* Polling interval in milliseconds */

    0x07,                        /* Endpoint descriptor length = 7 */
    0x05,                        /* Endpoint descriptor type */
    MSC_OUT_EP,                  /* Endpoint address (OUT, address 1) */
    0x02,                        /* Bulk endpoint type */
    LOBYTE(MSC_MAX_PACKET),
    HIBYTE(MSC_MAX_PACKET),
    0x00                         /* Polling interval in milliseconds */
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Initialize the mass storage interface configuration
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_dev_msc_init(void *pdev)
{
    usb_dev_msc_deinit(pdev);
    usb_opendevep(pdev, MSC_IN_EP, MSC_EPIN_SIZE, EP_TYPE_BULK);
    usb_opendevep(pdev, MSC_OUT_EP, MSC_EPOUT_SIZE, EP_TYPE_BULK);
    msc_bot_init(pdev);
}

/**
 * @brief  deinitilaize  the mass storage interface configuration
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_dev_msc_deinit(void *pdev)
{
    usb_shutdevep(pdev, MSC_IN_EP);
    usb_shutdevep(pdev, MSC_OUT_EP);
    msc_bot_deinit(pdev);
}

/**
 * @brief  process the msc setup requests
 * @param  [in] pdev        device instance
 * @param  [in] req         setup request
 * @retval status
 */
uint8_t usb_dev_msc_setup(void *pdev, USB_SETUP_REQ *req)
{
    uint8_t u8Res = USB_DEV_OK;
    switch (req->bmRequest & USB_REQ_TYPE_MASK) {
        case USB_REQ_TYPE_CLASS:
            switch (req->bRequest) {
                case BOT_GET_MAX_LUN:
                    if ((req->wValue == (uint16_t)0) &&
                            (req->wLength == (uint16_t)1) &&
                            ((req->bmRequest & 0x80U) == (uint8_t)0x80)) {
                        dev_msc_maxlun = msc_fops->GetMaxLun();
                        if (dev_msc_maxlun > 0U) {
                            usb_ctrldatatx(pdev, &dev_msc_maxlun, 1U);
                        } else {
                            usb_ctrlerr(pdev);
                            u8Res = USB_DEV_FAIL;
                        }
                    } else {
                        usb_ctrlerr(pdev);
                        u8Res = USB_DEV_FAIL;
                    }
                    break;
                case BOT_RESET:
                    if ((req->wValue == (uint16_t)0) &&
                            (req->wLength == (uint16_t)0) &&
                            ((req->bmRequest & 0x80U) != (uint8_t)0x80)) {
                        msc_bot_rst(pdev);
                    } else {
                        usb_ctrlerr(pdev);
                        u8Res = USB_DEV_FAIL;
                    }
                    break;
                default:
                    usb_ctrlerr(pdev);
                    u8Res = USB_DEV_FAIL;
                    break;
            }
            break;
        case USB_REQ_TYPE_STANDARD:
            switch (req->bRequest) {
                case USB_REQ_GET_INTERFACE:
                    usb_ctrldatatx(pdev, &dev_msc_altset, 1U);
                    break;
                case USB_REQ_SET_INTERFACE:
                    dev_msc_altset = (uint8_t)(req->wValue);
                    break;
                case USB_REQ_CLEAR_FEATURE:
                    usb_flsdevep(pdev, (uint8_t)req->wIndex);
                    usb_shutdevep(pdev, (uint8_t)req->wIndex);
                    if ((((uint8_t)req->wIndex) & (uint16_t)0x80U) == (uint16_t)0x80) {
                        usb_opendevep(pdev, ((uint8_t)req->wIndex), MSC_EPIN_SIZE, EP_TYPE_BULK);
                    } else {
                        usb_opendevep(pdev, ((uint8_t)req->wIndex), MSC_EPOUT_SIZE, EP_TYPE_BULK);
                    }
                    msc_bot_complete_clearfeature(pdev, (uint8_t)req->wIndex);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return u8Res;
}

/**
 * @brief  process data IN DATA
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_dev_msc_datain(void *pdev, uint8_t epnum)
{
    msc_bot_datain(pdev, epnum);
}

/**
 * @brief  process data OUT DATA
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_dev_msc_dataout(void *pdev, uint8_t epnum)
{
    msc_bot_dataout(pdev, epnum);
}

/**
 * @brief  get the configuration descriptor
 * @param  [in] length      length of data butter in bytes
 * @retval buffer pointer
 */
uint8_t *usb_dev_msc_getcfgdesc(uint16_t *length)
{
    *length = (uint16_t)sizeof(usb_dev_msc_cfgdesc);
    return usb_dev_msc_cfgdesc;
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
