/**
 *******************************************************************************
 * @file  usb_host_msc_class.c
 * @brief The MSC class driver functions
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
#include "usb_host_msc_class.h"
#include "usb_host_msc_scsi.h"
#include "usb_host_msc_bot.h"
#include "usb_host_core.h"
#include "usb_host_driver.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_MSC
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define USBH_MSC_ERROR_RETRY_LIMIT  (10U)

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
HOST_STATUS usb_host_msc_itfinit(usb_core_instance *pdev, void *phost);
void usb_host_msc_itfdeinit(usb_core_instance *pdev);
HOST_STATUS usb_host_msc_process(usb_core_instance *pdev, void *phost);
HOST_STATUS usb_host_msc_classreq(usb_core_instance *pdev, void *phost);

HOST_STATUS usb_host_msc_bot_reset(usb_core_instance *pdev, USBH_HOST *phost);
HOST_STATUS usb_host_msc_maxlun_get(usb_core_instance *pdev, USBH_HOST *phost);
void usb_host_msc_error_process(USB_HOST_MSC_STATUS status);

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
#ifdef USB_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN MSC_Machine_TypeDef         MSC_Machine;

#ifdef USB_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
uint8_t MSCErrorCount = 0U;

usb_host_class_callback_func  USBH_MSC_cb = {
    &usb_host_msc_itfinit,
    &usb_host_msc_itfdeinit,
    &usb_host_msc_classreq,
    &usb_host_msc_process,
};

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  This request is used to issue a request to reset the msc device and
 *         its related interface. This class-specific request shall prepare the
 *         device for the next CBW from the host.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @retval status define by HOST_STATUS
 */
HOST_STATUS usb_host_msc_bot_reset(usb_core_instance *pdev, USBH_HOST *phost)
{
    phost->ctrlparam.setup.b.bmRequestType = USB_H2D | USB_REQ_TYPE_CLASS | \
            USB_REQ_RECIPIENT_INTERFACE;
    phost->ctrlparam.setup.b.bRequest = USB_REQ_BOT_RESET;
    phost->ctrlparam.setup.b.wValue.w = 0U;
    phost->ctrlparam.setup.b.wIndex.w = 0U;
    phost->ctrlparam.setup.b.wLength.w = 0U;
    return usb_host_ctrlreq(pdev, phost, NULL, 0U);
}

/**
 * @brief  this request is used to issue a request to get the max logic unit of
 *         the msc device.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @retval status defined by HOST_STATUS
 */
HOST_STATUS usb_host_msc_maxlun_get(usb_core_instance *pdev, USBH_HOST *phost)
{
    phost->ctrlparam.setup.b.bmRequestType = USB_D2H | USB_REQ_TYPE_CLASS | \
            USB_REQ_RECIPIENT_INTERFACE;

    phost->ctrlparam.setup.b.bRequest = USB_REQ_GET_MAX_LUN;
    phost->ctrlparam.setup.b.wValue.w = 0U;
    phost->ctrlparam.setup.b.wIndex.w = 0U;
    phost->ctrlparam.setup.b.wLength.w = 1U;
    return usb_host_ctrlreq(pdev, phost, MSC_Machine.buff, 1U);
}

/**
 * @brief  The function is used for handling errors during processing the MSC
 *         state machine
 * @param  [in] status
 * @retval None
 */
void usb_host_msc_error_process(USB_HOST_MSC_STATUS status)
{
    switch (status) {
        case USB_HOST_MSC_FAIL:
            MSCErrorCount++;
            if (MSCErrorCount < USBH_MSC_ERROR_RETRY_LIMIT) {
                /* Try MSC level error recovery, Issue the request Sense to get
                driver error reason  */
                USBH_MSC_BOTXferParam.MSCState = HOST_MSC_REQUEST_SENSE;
                USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
            } else {
                /* Error trials exceeded the limit, go to unrecovered state */
                USBH_MSC_BOTXferParam.MSCState = HOST_MSC_UNRECOVERED_STATE;
            }
            break;
        case USB_HOST_MSC_PHASE_ERROR:
            /* Phase error, Go to Unrecoovered state */
            USBH_MSC_BOTXferParam.MSCState = HOST_MSC_UNRECOVERED_STATE;
            break;
        default:
            break;
    }
}

/**
 * @brief  Interface initialization for msc class application, the channels for
 *         the IN and OUT EP will be distributed.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @retval status defined by HOST_STATUS
 */
HOST_STATUS usb_host_msc_itfinit(usb_core_instance *pdev, void *phost)
{
    USBH_HOST *pphost = phost;

    if ((pphost->device_prop.devitfdesc[0].bInterfaceClass == MSC_CLASS) && \
            (pphost->device_prop.devitfdesc[0].bInterfaceProtocol == MSC_PROTOCOL)) {
        if ((pphost->device_prop.devepdesc[0][0].bEndpointAddress & 0x80U) == 0x80U) {
            MSC_Machine.MSC_BulkInEp = (pphost->device_prop.devepdesc[0][0].bEndpointAddress);
            MSC_Machine.MSC_BulkInEpSize  = pphost->device_prop.devepdesc[0][0].wMaxPacketSize;
        } else {
            MSC_Machine.MSC_BulkOutEp = (pphost->device_prop.devepdesc[0][0].bEndpointAddress);
            MSC_Machine.MSC_BulkOutEpSize  = pphost->device_prop.devepdesc[0] [0].wMaxPacketSize;
        }
        if ((pphost->device_prop.devepdesc[0][1].bEndpointAddress & 0x80U) == 0x80U) {
            MSC_Machine.MSC_BulkInEp = (pphost->device_prop.devepdesc[0][1].bEndpointAddress);
            MSC_Machine.MSC_BulkInEpSize  = pphost->device_prop.devepdesc[0][1].wMaxPacketSize;
        } else {
            MSC_Machine.MSC_BulkOutEp = (pphost->device_prop.devepdesc[0][1].bEndpointAddress);
            MSC_Machine.MSC_BulkOutEpSize  = pphost->device_prop.devepdesc[0][1].wMaxPacketSize;
        }
        /* distribute the channels for the EPs */
        MSC_Machine.hc_num_out = usb_host_distrch(pdev, MSC_Machine.MSC_BulkOutEp);
        MSC_Machine.hc_num_in = usb_host_distrch(pdev, MSC_Machine.MSC_BulkInEp);
        /* open the channels that have distributed */
        usb_host_chopen(pdev,
                        MSC_Machine.hc_num_out,
                        pphost->device_prop.devaddr,
                        pphost->device_prop.devspeed,
                        EP_TYPE_BULK,
                        MSC_Machine.MSC_BulkOutEpSize);
        usb_host_chopen(pdev,
                        MSC_Machine.hc_num_in,
                        pphost->device_prop.devaddr,
                        pphost->device_prop.devspeed,
                        EP_TYPE_BULK,
                        MSC_Machine.MSC_BulkInEpSize);
    } else {
        pphost->user_callbk->huser_devunsupported();
    }
    return HSTATUS_OK ;
}

/**
 * @brief  deinitialize interface of msc class by freeing host channels
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_host_msc_itfdeinit(usb_core_instance *pdev)
{
    if (MSC_Machine.hc_num_out != 0U) {
        usb_hchstop(&pdev->regs, MSC_Machine.hc_num_out);
        (void)usb_host_freech(pdev, MSC_Machine.hc_num_out);
        MSC_Machine.hc_num_out = 0U;
    }
    if (MSC_Machine.hc_num_in != 0U) {
        usb_hchstop(&pdev->regs, MSC_Machine.hc_num_in);
        (void)usb_host_freech(pdev, MSC_Machine.hc_num_in);
        MSC_Machine.hc_num_in = 0U;
    }
}

/**
 * @brief  initialize the msc state machine
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @retval status defined by HOST_STATUS
 */
HOST_STATUS usb_host_msc_classreq(usb_core_instance *pdev, void *phost)
{
    USBH_MSC_BOTXferParam.MSCState = HOST_MSC_BOT_INIT_STATE;
    return HSTATUS_OK;
}

/**
 * @brief  process the msc state machine
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @retval status defined by HOST_STATUS
 */
HOST_STATUS usb_host_msc_process(usb_core_instance *pdev, void *phost)
{
    USBH_HOST *pphost   = phost;
    HOST_STATUS status  = HSTATUS_BUSY;
    USB_HOST_MSC_STATUS mscStatus;
    uint8_t appliStatus;
    static uint8_t maxLunExceed = FALSE;

    if (host_driver_ifdevconnected(pdev) != 0UL) {
        switch (USBH_MSC_BOTXferParam.MSCState) {
            case HOST_MSC_BOT_INIT_STATE:
                usb_host_msc_init(pdev);
                USBH_MSC_BOTXferParam.MSCState = HOST_MSC_BOT_RESET;
                break;
            case HOST_MSC_BOT_RESET:
                /* issue a request to reset the bot. */
                status = usb_host_msc_bot_reset(pdev, phost);
                if (status == HSTATUS_OK) {
                    USBH_MSC_BOTXferParam.MSCState = HOST_MSC_GET_MAX_LUN;
                }
                if (status == HSTATUS_UNSUPPORTED) {
                    /* if the request fails, it needs to move to next state and should save the next state as backup */
                    USBH_MSC_BOTXferParam.MSCStateBkp = HOST_MSC_GET_MAX_LUN;
                    /* a clear feature should be issued if the request fails. */
                    USBH_MSC_BOTXferParam.MSCState = HOST_MSC_CTRL_ERROR_STATE;
                }
                break;
            case HOST_MSC_GET_MAX_LUN:
                /* issue a request to get the max logical unit(MAXLUN). */
                status = usb_host_msc_maxlun_get(pdev, phost);
                if (status == HSTATUS_OK) {
                    MSC_Machine.maxLun = *(MSC_Machine.buff) ;
                    if ((MSC_Machine.maxLun > 0U) && (maxLunExceed == FALSE)) {
                        maxLunExceed = TRUE;
                        pphost->user_callbk->huser_devunsupported();
                        break;
                    }
                    USBH_MSC_BOTXferParam.MSCState = HOST_MSC_TEST_UNIT_READY;
                }

                if (status == HSTATUS_UNSUPPORTED) {
                    /* if the request fails, it needs to move to next state and should save the next state as backup */
                    USBH_MSC_BOTXferParam.MSCStateBkp = HOST_MSC_TEST_UNIT_READY;
                    /* a clear feature should be issued if the request fails. */
                    USBH_MSC_BOTXferParam.MSCState = HOST_MSC_CTRL_ERROR_STATE;
                }
                break;
            case HOST_MSC_CTRL_ERROR_STATE:
                /* issue a request to clear feature */
                status = usb_host_clrfeature(pdev,
                                             phost,
                                             0x00U,
                                             pphost->ctrlparam.hc_num_out);
                if (status == HSTATUS_OK) {
                    /* If GetMaxLun Request not support, assume Single LUN configuration */
                    MSC_Machine.maxLun = 0U;
                    USBH_MSC_BOTXferParam.MSCState = USBH_MSC_BOTXferParam.MSCStateBkp;
                }
                break;
            case HOST_MSC_TEST_UNIT_READY:
                /* issue the request Test Unit Ready[0] of SCSI command */
                mscStatus = usb_host_msc_TestUnitReady(pdev);

                if (mscStatus == USB_HOST_MSC_OK) {
                    USBH_MSC_BOTXferParam.MSCState = HOST_MSC_READ_CAPACITY10;
                    MSCErrorCount = 0U;
                    status = HSTATUS_OK;
                } else {
                    usb_host_msc_error_process(mscStatus);
                }
                break;

            case HOST_MSC_READ_CAPACITY10:
                /* issue the request Read Capacity[0] of SCSI command. */
                mscStatus = usb_host_msc_ReadCapacity10(pdev);
                if (mscStatus == USB_HOST_MSC_OK) {
                    USBH_MSC_BOTXferParam.MSCState = HOST_MSC_MODE_SENSE6;
                    MSCErrorCount = 0U;
                    status = HSTATUS_OK;
                } else {
                    usb_host_msc_error_process(mscStatus);
                }
                break;
            case HOST_MSC_MODE_SENSE6:
                /* issue the request ModeSense6 of SCSI command for detecting whelth the deviec is write-protected. */
                mscStatus = usb_host_msc_ModeSense6(pdev);
                if (mscStatus == USB_HOST_MSC_OK) {
                    USBH_MSC_BOTXferParam.MSCState = HOST_MSC_DEFAULT_APPLI_STATE;
                    MSCErrorCount = 0U;
                    status = HSTATUS_OK;
                } else {
                    usb_host_msc_error_process(mscStatus);
                }
                break;
            case HOST_MSC_REQUEST_SENSE:
                /* issue the request RequestSense of SCSI command for retreiving error code. */
                mscStatus = usb_host_msc_RequestSense(pdev);
                if (mscStatus == USB_HOST_MSC_OK) {
                    USBH_MSC_BOTXferParam.MSCState = USBH_MSC_BOTXferParam.MSCStateBkp;
                    status = HSTATUS_OK;
                } else {
                    usb_host_msc_error_process(mscStatus);
                }
                break;
            case HOST_MSC_BOT_USB_TRANSFERS:
                /* handle the BOT state machine. */
                usb_host_msc_botxferprocess(pdev, phost);
                break;
            case HOST_MSC_DEFAULT_APPLI_STATE:
                /* handle the user callback for the msc application. */
                appliStatus = pphost->user_callbk->huser_application();
                if (appliStatus == 0U) {
                    USBH_MSC_BOTXferParam.MSCState = HOST_MSC_DEFAULT_APPLI_STATE;
                } else if (appliStatus == 1U) {
                    /* deinit requested from the application layer. */
                    status = HSTATUS_APP_DEINIT;
                } else {
                    ;
                }
                break;
            case HOST_MSC_UNRECOVERED_STATE:
                status = HSTATUS_UNRECOVERED_ERROR;
                break;
            default:
                break;
        }
    }
    return status;
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
