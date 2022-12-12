/**
 *******************************************************************************
 * @file  usb_dev_custom_hid_class.c
 * @brief CUSTOM HID core functions.
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
#include "usb_dev_desc.h"
#include "usb_dev_stdreq.h"
#include "usb_dev_driver.h"
#include "usb_bsp.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CUSTOM_HID USB Device Custom HID
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
void usb_dev_hid_init(void *pdev);
void usb_dev_hid_deinit(void *pdev);
uint8_t usb_dev_hid_setup(void *pdev, USB_SETUP_REQ *req);
uint8_t *usb_dev_hid_getcfgdesc(uint16_t *length);
void usb_dev_hid_datain(void *pdev, uint8_t epnum);
void usb_dev_hid_dataout(void *pdev, uint8_t epnum);
void usb_dev_hid_ctrlep_rxready(void *pdev);

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
uint8_t Report_buf[64];
uint8_t Send_Buf[64];
static __IO uint32_t IsReportAvailable = 0UL;

usb_dev_class_func  class_customhid_cbk = {
    &usb_dev_hid_init,
    &usb_dev_hid_deinit,
    &usb_dev_hid_setup,
    NULL,
    &usb_dev_hid_ctrlep_rxready,
    &usb_dev_hid_getcfgdesc,
    NULL,
    &usb_dev_hid_datain,
    &usb_dev_hid_dataout,
    NULL,
    NULL,
};

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
__USB_ALIGN_BEGIN static uint32_t  USB_DEV_HID_AltSet = 0UL;

__USB_ALIGN_BEGIN static uint32_t  USB_DEV_HID_Protocol = 0UL;

__USB_ALIGN_BEGIN static uint32_t  USB_DEV_HID_IdleState = 0UL;

__USB_ALIGN_BEGIN static uint8_t usb_dev_hid_cfgdesc[USB_CUSTOM_HID_CONFIG_DESC_SIZ] = {
    0x09,
    USB_CFG_DESCRIPTOR_TYPE,
    USB_CUSTOM_HID_CONFIG_DESC_SIZ,
    0x00,
    0x01,
    0x01,
    0x00,
    0xC0,
    0x32,

    0x09,
    USB_INTERFACE_DESCRIPTOR_TYPE,
    0x00,
    0x00,
    0x02,
    0x03,
    0x00,
    0x00,
    0x00,

    0x09,
    CUSTOM_HID_DESCRIPTOR_TYPE,
    0x10,
    0x01,
    0x21,
    0x01,
    0x22,
    CUSTOM_HID_REPORT_DESC_SIZE,
    0x00,

    0x07,
    USB_ENDPOINT_DESCRIPTOR_TYPE,
    HID_IN_EP,
    0x03,
    HID_IN_PACKET,
    0x00,
    0x0A,

    0x07,
    USB_ENDPOINT_DESCRIPTOR_TYPE,

    HID_OUT_EP,
    0x03,
    HID_OUT_PACKET,
    0x00,
    0x0A,
} ;


__USB_ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc[CUSTOM_HID_REPORT_DESC_SIZE] = {
    0x05, 0x8C, 0x09, 0x06, 0xA1, 0x01, 0x09, 0x06, 0x15, 0x00, 0x26, 0x00,
    0xFF, 0x75, 0x08, 0x95, 0x40, 0x91, 0x82, 0x09, 0x06, 0x15, 0x00, 0x26,
    0x00, 0xFF, 0x75, 0x08, 0x95, 0X40, 0x81, 0x82, 0xC0
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Initialize the HID application
 * @param  [in] pdev        Device instance
 * @retval None
 */
void usb_dev_hid_init(void *pdev)
{
    usb_opendevep(pdev, HID_IN_EP, HID_IN_PACKET, EP_TYPE_INTR);
    usb_opendevep(pdev, HID_OUT_EP, HID_OUT_PACKET, EP_TYPE_INTR);
    usb_readytorx(pdev, HID_OUT_EP, Report_buf, HID_OUT_PACKET);
    usb_devepstatusset(pdev, HID_OUT_EP, USB_EP_RX_VALID);
}

/**
 * @brief  Deinitialize  the HID application
 * @param  [in] pdev        Device instance
 * @retval None
 */
void usb_dev_hid_deinit(void *pdev)
{
    usb_shutdevep(pdev, HID_IN_EP);
    usb_shutdevep(pdev, HID_OUT_EP);
}

/**
 * @brief  Handle the setup requests
 * @param  [in] pdev        Device instance
 * @param  [in] req         usb requests
 * @retval status
 */
uint8_t usb_dev_hid_setup(void *pdev, USB_SETUP_REQ *req)
{
    uint8_t hid_report_length;
    uint16_t len = 0U;
    uint8_t *pbuf = NULL;
    uint8_t u8Ret = USB_DEV_OK;

    switch (req->bmRequest & USB_REQ_TYPE_MASK) {
        case USB_REQ_TYPE_CLASS :
            switch (req->bRequest) {
                case CUSTOM_HID_REQ_SET_PROTOCOL:
                    USB_DEV_HID_Protocol = (uint8_t)(req->wValue);
                    break;
                case CUSTOM_HID_REQ_GET_PROTOCOL:
                    usb_ctrldatatx(pdev, (uint8_t *)&USB_DEV_HID_Protocol, 1U);
                    break;
                case CUSTOM_HID_REQ_SET_IDLE:
                    USB_DEV_HID_IdleState = (uint8_t)(req->wValue >> 8);
                    break;
                case CUSTOM_HID_REQ_GET_IDLE:
                    usb_ctrldatatx(pdev, (uint8_t *)&USB_DEV_HID_IdleState, 1U);
                    break;
                case CUSTOM_HID_REQ_SET_REPORT:
                    IsReportAvailable = 1UL;
                    hid_report_length = (uint8_t)(req->wLength);
                    usb_ctrldatarx(pdev, Report_buf, (uint16_t)hid_report_length);
                    break;
                default:
                    usb_ctrlerr(pdev);
                    u8Ret = USB_DEV_FAIL;
                    break;
            }
            break;
        case USB_REQ_TYPE_STANDARD:
            switch (req->bRequest) {
                case USB_REQ_GET_DESCRIPTOR:
                    if (req->wValue >> 8U == CUSTOM_HID_REPORT_DESC) {
                        len = LL_MIN((uint16_t)CUSTOM_HID_REPORT_DESC_SIZE, req->wLength);
                        pbuf = (uint8_t *)CUSTOM_HID_ReportDesc;
                    } else if (req->wValue >> 8U == CUSTOM_HID_DESCRIPTOR_TYPE) {
                        pbuf = (uint8_t *)usb_dev_hid_cfgdesc + 0x12U;
                        len = LL_MIN(USB_CUSTOM_HID_DESC_SIZ, req->wLength);
                    } else {
                        ;
                    }

                    usb_ctrldatatx(pdev, pbuf, len);
                    break;
                case USB_REQ_GET_INTERFACE :
                    usb_ctrldatatx(pdev, (uint8_t *)&USB_DEV_HID_AltSet, 1U);
                    break;
                case USB_REQ_SET_INTERFACE :
                    USB_DEV_HID_AltSet = (uint8_t)(req->wValue);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return u8Ret;
}

/**
 * @brief  Send HID Report
 * @param  [in] pdev        Device instance
 * @param  [in] report      pointer to report
 * @param  [in] len         the length in bytes would be sent
 * @retval status
 */
uint8_t usb_dev_hid_txreport(usb_core_instance *pdev, uint8_t *report, uint16_t len)
{
    if (pdev->dev.device_cur_status == USB_DEV_CONFIGURED) {
        usb_deveptx(pdev, HID_IN_EP, report, (uint32_t)len);
    }
    return USB_DEV_OK;
}

/**
 * @brief  return configuration descriptor
 * @param  [in] length      length of configuration descriptor in bytes
 * @retval pointer to configuration descriptor buffer
 */
uint8_t *usb_dev_hid_getcfgdesc(uint16_t *length)
{
    *length = (uint8_t)sizeof(usb_dev_hid_cfgdesc);
    return usb_dev_hid_cfgdesc;
}

/**
 * @brief  processing for data in
  * @param  [in] pdev       Device instance
  * @param  [in] epnum      endpoint index
  * @retval None
 */
void usb_dev_hid_datain(void *pdev, uint8_t epnum)
{
    usb_flsdevep(pdev, HID_IN_EP);

    if (epnum == (HID_IN_EP & (uint8_t)~0x80U)) {
        PrevXferDone = 1U;
    }
}

/**
 * @brief  processing for data out
  * @param  [in] pdev       Device instance
  * @param  [in] epnum      endpoint index
  * @retval None
 */
void usb_dev_hid_dataout(void *pdev, uint8_t epnum)
{
    if (epnum == HID_OUT_EP) {
        switch (Report_buf[0]) {
            case 1: /* Led 1 */
                if (Report_buf[1U] == 0U) {
                    /* RED LED on */
                    BSP_LED_Off(LED_RED);
                } else {
                    /* RED LED off */
                    BSP_LED_On(LED_RED);
                }
                break;

            case 2: /* Led 2 */
                if (Report_buf[1U] == 0U) {
                    /* BLUE LED on */
                    BSP_LED_Off(LED_BLUE);
                } else {
                    /* BLUE LED off */
                    BSP_LED_On(LED_BLUE);
                }
                break;
            default:
                BSP_LED_Off(LED_RED);
                BSP_LED_Off(LED_BLUE);
                break;
        }
    }

    usb_readytorx(pdev, HID_OUT_EP, Report_buf, 2U);
    usb_devepstatusset(pdev, HID_OUT_EP, USB_EP_RX_VALID);
    usb_deveptx(pdev, HID_IN_EP, Report_buf, 2);
}

/**
 * @brief  processing for request data in control endpoint
 * @param  [in] pdev        Device instance
 * @retval None
 */
void usb_dev_hid_ctrlep_rxready(void *pdev)
{
    if (IsReportAvailable == 1UL) {
        IsReportAvailable = 0UL;
        switch (Report_buf[0]) {
            case 1: /* Led 1 */
                if (Report_buf[1] == 0U) {
                    /* RED LED on */
                    BSP_LED_Off(LED_RED);
                } else {
                    /* RED LED off */
                    BSP_LED_On(LED_RED);
                }
                break;

            case 2: /* Led 2 */
                if (Report_buf[1] == 0U) {
                    /* BLUE LED on */
                    BSP_LED_Off(LED_BLUE);
                } else {
                    /* BLUE LED off */
                    BSP_LED_On(LED_BLUE);
                }
                break;
            default:
                BSP_LED_Off(LED_RED);
                BSP_LED_Off(LED_BLUE);
                break;
        }
    }
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
