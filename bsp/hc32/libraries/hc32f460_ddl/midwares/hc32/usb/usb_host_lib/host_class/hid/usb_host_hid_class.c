/**
 *******************************************************************************
 * @file  usb_host_hid_class.c
 * @brief The HID Layer Handlers for USB Host HID class.
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
#include "usb_host_hid_class.h"
#include "usb_host_hid_mouseapp.h"
#include "usb_host_hid_keyboardapp.h"
#include "usb_host_driver.h"
#include "usb_host_cfgch.h"
#include "usb_host_ctrltrans.h"
#include "usb_host_stdreq.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CLASS LL USB Host Class
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_HID USB Host HID
 * @{
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
HOST_STATUS usb_host_hid_itfinit(usb_core_instance *pdev, void *phost);
void usb_host_hid_itfdeinit(usb_core_instance *pdev);
void usb_host_parse_hiddesc(USB_HOST_HIDDesc_TypeDef *desc, uint8_t *buf);
HOST_STATUS usb_host_hid_process(usb_core_instance *pdev, void *phost);
HOST_STATUS usb_host_hid_classreq(usb_core_instance *pdev, void *phost);
HOST_STATUS usb_host_get_hidreportdesc(usb_core_instance *pdev, USBH_HOST *phost, uint16_t length);
HOST_STATUS usb_host_get_hiddesc(usb_core_instance *pdev, USBH_HOST *phost, uint16_t length);
HOST_STATUS usb_host_set_hididle(usb_core_instance *pdev,
                                 USBH_HOST *phost,
                                 uint8_t duration,
                                 uint8_t reportId);
HOST_STATUS usb_host_set_hidprotocol(usb_core_instance *pdev, USBH_HOST *phost, uint8_t protocol);

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
usb_host_class_callback_func  USBH_HID_cb = {
    usb_host_hid_itfinit,
    usb_host_hid_itfdeinit,
    usb_host_hid_classreq,
    usb_host_hid_process
};

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

#ifdef USB_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN static HID_Machine_TypeDef        HID_Machine;

#ifdef USB_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN static USB_HOST_HIDDesc_TypeDef   HID_Desc;

__IO static uint8_t start_toggle = 0U;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  initialize the hid class
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @retval status defination by HOST_STATUS
 */
HOST_STATUS usb_host_hid_itfinit(usb_core_instance *pdev, void *phost)
{
    uint8_t maxEP;
    USBH_HOST *pphost = phost;

    uint8_t epnum;
    HOST_STATUS status = HSTATUS_BUSY ;
    HID_Machine.state = HID_ERROR;

    if (pphost->device_prop.devitfdesc[0].bInterfaceSubClass  == HID_BOOT_CODE) {
        switch (pphost->device_prop.devitfdesc[0].bInterfaceProtocol) {
            case HID_MOUSE_BOOT_CODE:
                HID_Machine.cb = &HID_MOUSE_cb;
                break;
            case HID_KEYBRD_BOOT_CODE:
                HID_Machine.cb = &HID_KEYBRD_cb;
                break;
            default:
                break;
        }
        HID_Machine.state     = HID_IDLE;
        HID_Machine.ctl_state = HID_REQ_IDLE;
        HID_Machine.ep_addr   = pphost->device_prop.devepdesc[0][0].bEndpointAddress;
        HID_Machine.length    = pphost->device_prop.devepdesc[0][0].wMaxPacketSize;
        HID_Machine.poll      = pphost->device_prop.devepdesc[0][0].bInterval ;

        if (HID_Machine.poll  < HID_MIN_POLL) {
            HID_Machine.poll = HID_MIN_POLL;
        }

        /* Check fo available number of endpoints */
        /* Find the number of EPs in the Interface Descriptor */
        /* Choose the lower number in order not to overrun the buffer allocated */
        maxEP = ((pphost->device_prop.devitfdesc[0].bNumEndpoints <= USBH_MAX_NUM_ENDPOINTS) ?
                 pphost->device_prop.devitfdesc[0].bNumEndpoints :
                 USBH_MAX_NUM_ENDPOINTS);

        /* Decode endpoint IN and OUT address from interface descriptor */
        for (epnum = 0U; epnum < maxEP; epnum++) {
            if (0U != (pphost->device_prop.devepdesc[0][epnum].bEndpointAddress & 0x80U)) {
                HID_Machine.HIDIntInEp = (pphost->device_prop.devepdesc[0][epnum].bEndpointAddress);
                HID_Machine.hc_num_in  = usb_host_distrch(pdev,
                                         pphost->device_prop.devepdesc[0][epnum].bEndpointAddress);
                usb_host_chopen(pdev,
                                HID_Machine.hc_num_in,
                                pphost->device_prop.devaddr,
                                pphost->device_prop.devspeed,
                                EP_TYPE_INTR,
                                HID_Machine.length);
            } else {
                HID_Machine.HIDIntOutEp = (pphost->device_prop.devepdesc[0][epnum].bEndpointAddress);
                HID_Machine.hc_num_out  = usb_host_distrch(pdev,
                                          pphost->device_prop.devepdesc[0][epnum].bEndpointAddress);
                usb_host_chopen(pdev,
                                HID_Machine.hc_num_out,
                                pphost->device_prop.devaddr,
                                pphost->device_prop.devspeed,
                                EP_TYPE_INTR,
                                HID_Machine.length);
            }
        }
        start_toggle = 0U;
        status = HSTATUS_OK;
    } else {
        pphost->user_callbk->huser_devunsupported();
    }
    return status;
}

/**
 * @brief  deinitialize the channels for the hid class
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_host_hid_itfdeinit(usb_core_instance *pdev)
{
    if (HID_Machine.hc_num_in != 0x00U) {
        usb_hchstop(&pdev->regs, HID_Machine.hc_num_in);
        (void)usb_host_freech(pdev, HID_Machine.hc_num_in);
        HID_Machine.hc_num_in = 0U;
    }

    if (HID_Machine.hc_num_out != 0x00U) {
        usb_hchstop(&pdev->regs, HID_Machine.hc_num_out);
        (void)usb_host_freech(pdev, HID_Machine.hc_num_out);
        HID_Machine.hc_num_out = 0U;
    }
    start_toggle = 0U;
}

/**
 * @brief  This function is responsible for handling requests about HID class.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @retval status defined by HOST_STATUS
 */
HOST_STATUS usb_host_hid_classreq(usb_core_instance *pdev, void *phost)
{
    HOST_STATUS status;
    HOST_STATUS classReqStatus;
    USBH_HOST *pphost = phost;
    status            = HSTATUS_BUSY;
    switch (HID_Machine.ctl_state) {
        case HID_IDLE:
        case HID_REQ_GET_HID_DESC:
            if (usb_host_get_hiddesc(pdev, pphost, USB_HID_DESC_SIZE) == HSTATUS_OK) {
                usb_host_parse_hiddesc(&HID_Desc, pdev->host.Rx_Buffer);
                HID_Machine.ctl_state = HID_REQ_GET_REPORT_DESC;
            }
            break;
        case HID_REQ_GET_REPORT_DESC:
            if (usb_host_get_hidreportdesc(pdev, pphost, HID_Desc.wItemLength) == HSTATUS_OK) {
                HID_Machine.ctl_state = HID_REQ_SET_IDLE;
            }
            break;
        case HID_REQ_SET_IDLE:
            classReqStatus = usb_host_set_hididle(pdev, pphost, 0U, 0U);
            if (classReqStatus == HSTATUS_OK) {
                HID_Machine.ctl_state = HID_REQ_SET_PROTOCOL;
            } else if (classReqStatus == HSTATUS_UNSUPPORTED) {
                HID_Machine.ctl_state = HID_REQ_SET_PROTOCOL;
            } else {
                /*reserved*/
            }
            break;
        case HID_REQ_SET_PROTOCOL:
            if (usb_host_set_hidprotocol(pdev, pphost, 0U) == HSTATUS_OK) {
                HID_Machine.ctl_state = HID_REQ_IDLE;
                status = HSTATUS_OK;
            }
            break;
        default:
            break;
    }
    return status;
}

/**
 * @brief  This function is to process the state machine for HID data transmitting
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @retval status defined by HOST_STATUS
 */
HOST_STATUS usb_host_hid_process(usb_core_instance *pdev, void *phost)
{
    HOST_STATUS status;
    USBH_HOST *pphost = phost;
    status = HSTATUS_OK;
    switch (HID_Machine.state) {
        case HID_IDLE:
            HID_Machine.cb->Init();
            HID_Machine.state = HID_SYNC;
        case HID_SYNC:
            if (usb_ifevenframe(&pdev->regs) == TRUE) {
                HID_Machine.state = HID_GET_DATA;
            }
            break;
        case HID_GET_DATA:
            usb_host_recvintdata(pdev,
                                 HID_Machine.buff,
                                 HID_Machine.length,
                                 HID_Machine.hc_num_in);
            start_toggle = 1U;
            HID_Machine.state = HID_POLL;
            HID_Machine.timer = (uint16_t)host_driver_getcurrentfrm(pdev);
            break;
        case HID_POLL:
            if ((host_driver_getcurrentfrm(pdev) - HID_Machine.timer) >= HID_Machine.poll) {
                HID_Machine.state = HID_GET_DATA;
            } else if (host_driver_getxferstate(pdev, HID_Machine.hc_num_in) == HOST_CH_XFER_DONE) {
                if (start_toggle == 1U) {
                    start_toggle = 0U;
                    HID_Machine.cb->Decode(HID_Machine.buff);
                }
            } else if (host_driver_getxferstate(pdev, HID_Machine.hc_num_in) == HOST_CH_XFER_STALL) {
                /* Issue Clear Feature on interrupt IN endpoint */
                if ((usb_host_clrfeature(pdev,
                                         pphost,
                                         HID_Machine.ep_addr,
                                         HID_Machine.hc_num_in)) == HSTATUS_OK) {
                    HID_Machine.state = HID_GET_DATA;
                }
            } else {
                /*reserved*/
            }
            break;
        default:
            break;
    }
    return status;
}

/**
 * @brief  Issue hid report descriptor command to the device, parse the report
 *         descriptor and update the status once the response received.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @param  [in] length      the length of the hid descriptor in bytes
 * @retval status defined by HOST_STATUS
 */
HOST_STATUS usb_host_get_hidreportdesc(usb_core_instance *pdev, USBH_HOST *phost, uint16_t length)
{
    HOST_STATUS status;
    status = usb_host_getdesc(pdev,
                              phost,
                              USB_REQ_RECIPIENT_INTERFACE | USB_REQ_TYPE_STANDARD,
                              USB_DESC_HID_REPORT,
                              pdev->host.Rx_Buffer,
                              length);
    return status;
}

/**
 * @brief  Issue HID descriptor command to the device, parse the descriptor
 *         and update the status once the response received.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @param  [in] length      length of HID descriptor in bytes
 * @retval status defined by HOST_STATUS
 */
HOST_STATUS usb_host_get_hiddesc(usb_core_instance *pdev, USBH_HOST *phost, uint16_t length)
{
    HOST_STATUS status;
    status = usb_host_getdesc(pdev,
                              phost,
                              USB_REQ_RECIPIENT_INTERFACE
                              | USB_REQ_TYPE_STANDARD,
                              USB_DESC_HID,
                              pdev->host.Rx_Buffer,
                              length);
    return status;
}

/**
 * @brief  Set hid application to be idle status.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @param  [in] duration    Duration for HID Idle request
 * @param  [in] reportId    Targetted report ID for Set Idle request
 * @retval status defined by HOST_STATUS
 */
HOST_STATUS usb_host_set_hididle(usb_core_instance *pdev,
                                 USBH_HOST *phost,
                                 uint8_t duration,
                                 uint8_t reportId)
{
    phost->ctrlparam.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE | USB_REQ_TYPE_CLASS;

    phost->ctrlparam.setup.b.bRequest = USB_HID_SET_IDLE;
    phost->ctrlparam.setup.b.wValue.w = ((uint16_t)duration << 8) | (uint16_t)reportId;

    phost->ctrlparam.setup.b.wIndex.w = 0U;
    phost->ctrlparam.setup.b.wLength.w = 0U;

    return usb_host_ctrlreq(pdev, phost, NULL, 0U);
}

/**
 * @brief  Issues a command to set report
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @param  [in] reportType  the report type to be sent
 * @param  [in] reportId    target report ID for set report request
 * @param  [in] reportLen   length of data of report to be sent in bytes
 * @param  [in] reportBuff  report buffer
 * @retval status defined by HOST_STATUS
 */
HOST_STATUS usb_host_set_hidreport(usb_core_instance *pdev,
                                   USBH_HOST *phost,
                                   uint8_t reportType,
                                   uint8_t reportId,
                                   uint8_t reportLen,
                                   uint8_t *reportBuff)
{
    phost->ctrlparam.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE | USB_REQ_TYPE_CLASS;
    phost->ctrlparam.setup.b.bRequest = USB_HID_SET_REPORT;
    phost->ctrlparam.setup.b.wValue.w = ((uint16_t)reportType << 8) | (uint16_t)reportId;
    phost->ctrlparam.setup.b.wIndex.w = 0U;
    phost->ctrlparam.setup.b.wLength.w = reportLen;
    return usb_host_ctrlreq(pdev, phost, reportBuff, reportLen);
}

/**
 * @brief  Set protocol state of the hid application.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @param  [in] protocol    protocol for HID application
 * @retval status defined by HOST_STATUS
 */
HOST_STATUS usb_host_set_hidprotocol(usb_core_instance *pdev, USBH_HOST *phost, uint8_t protocol)
{
    phost->ctrlparam.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE | USB_REQ_TYPE_CLASS;
    phost->ctrlparam.setup.b.bRequest = USB_HID_SET_PROTOCOL;
    if (protocol != 0U) {
        /* Boot Protocol */
        phost->ctrlparam.setup.b.wValue.w = 0U;
    } else {
        /* Report Protocol */
        phost->ctrlparam.setup.b.wValue.w = 1U;
    }
    phost->ctrlparam.setup.b.wIndex.w = 0U;
    phost->ctrlparam.setup.b.wLength.w = 0U;
    return usb_host_ctrlreq(pdev, phost, NULL, 0U);
}

/**
 * @brief  parse the HID descriptor
 * @param  [in] desc        used to get the fields parsed from the data buffer
 * @param  [in] buf         Buffer where the source descriptor is available
 * @retval None
 */
void usb_host_parse_hiddesc(USB_HOST_HIDDesc_TypeDef *desc, uint8_t *buf)
{
    desc->bLength                  = *(uint8_t *)(buf + 0);
    desc->bDescriptorType          = *(uint8_t *)(buf + 1);
    desc->bcdHID                   =  SMALL_END(buf + 2);
    desc->bCountryCode             = *(uint8_t *)(buf + 4);
    desc->bNumDescriptors          = *(uint8_t *)(buf + 5);
    desc->bReportDescriptorType    = *(uint8_t *)(buf + 6);
    desc->wItemLength              =  SMALL_END(buf + 7);
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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
