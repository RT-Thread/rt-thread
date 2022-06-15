/**
 *******************************************************************************
 * @file  usb_host_ctrltrans.c
 * @brief This file handles the issuing of the USB transactions
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
#include "usb_host_ctrltrans.h"
#include "usb_host_driver.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CORE
 * @{
 */

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
void usb_host_submitsetupreq(USBH_HOST *phost, uint8_t *buff, uint16_t length);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Start a setup transfer by changing the state-machine and
 *         initializing  the required variables needed for the Control Transfer
 * @param  [in] phost       host state set
 * @param  [in] buff        data buffer used for setup request
 * @param  [in] length      data length in byte
 * @retval status
 */
void usb_host_submitsetupreq(USBH_HOST *phost, uint8_t *buff, uint16_t length)
{
    /* Save Global State */
    phost->host_state_backup    =   phost->host_state;
    /* Prepare the Transactions */
    phost->host_state           = HOST_CTRL_TRANSMIT;
    phost->ctrlparam.buff       = buff;
    phost->ctrlparam.length     = length;
    phost->ctrlparam.ctrl_state = CTRL_SETUP;
}

/**
 * @brief  send a control request and update the status after the request sent.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @param  [in] buff        data buffer whose data will be sent in the control pipe.
 * @param  [in] length      length of the data sent.
 * @retval status
 */
HOST_STATUS usb_host_ctrlreq(usb_core_instance *pdev,
                             USBH_HOST *phost,
                             uint8_t *buff,
                             uint16_t length)
{
    HOST_STATUS status;
    REQ_HANDLE_STATE tmp_req_state;
    (void)(pdev);
    status = HSTATUS_BUSY;
    tmp_req_state = phost->req_state;
    if (tmp_req_state == REQ_CMD_TX) {
        /* prepare a setup packet for transferring */
        usb_host_submitsetupreq(phost, buff, length);
        /* update the request state */
        phost->req_state = REQ_CMD_WAIT;
        /* The status would be returned in this function */
        status = HSTATUS_BUSY;
    } else if (tmp_req_state == REQ_CMD_WAIT) {
        switch (phost->ctrlparam.ctrl_state) {
            case CTRL_COMPLETE:
                /* Commands have been successfully sent and Responses have been Received */
                phost->req_state            = REQ_CMD_TX;
                /* update the control state */
                phost->ctrlparam.ctrl_state = CTRL_IDLE;
                status = HSTATUS_OK;
                break;
            case CTRL_ERROR:
                /* fail transfer */
                phost->req_state = REQ_CMD_TX;
                status           = HSTATUS_FAIL;
                break;
            case CTRL_STALLED:
                /* Commands have been successfully sent and Responses have been Received */
                phost->req_state = REQ_CMD_TX;
                status           = HSTATUS_UNSUPPORTED;
                break;
            default:
                break;
        }
    } else {
        ;
    }
    return status;
}

/**
 * @brief  sends a setup packet to the control EP of the USB device
 * @param  [in] pdev        device instance
 * @param  [in] buff        data buffer whose data will be sent in the control pipe to the control EP of the device.
 * @param  [in] hc_num      host channel index
 * @retval None
 */
void usb_host_sendctrlsetup(usb_core_instance *pdev, uint8_t *buff, uint8_t hc_num)
{
    pdev->host.hc[hc_num].is_epin   = 0U;
    pdev->host.hc[hc_num].pid_type  = PID_SETUP;
    pdev->host.hc[hc_num].xfer_buff = buff;
    pdev->host.hc[hc_num].xfer_len  = 8;
    (void)host_driver_submitrequest(pdev, hc_num);
}

/**
 * @brief  sends a data packet to the USB device
 * @param  [in] pdev        device instance
 * @param  [in] buff        data buffer whose data will be sent to the USB device
 * @param  [in] length      the data length in byte that would be sent
 * @param  [in] hc_num      host channel index
 * @retval None
 */
void usb_host_sendctrldata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num)
{
    pdev->host.hc[hc_num].is_epin   = 0;
    pdev->host.hc[hc_num].xfer_buff = buff;
    pdev->host.hc[hc_num].xfer_len  = length;
    if (length == 0U) {
        /* For Status OUT stage, Length==0, Status Out PID = 1 always */
        pdev->host.hc[hc_num].out_toggle = 1;
    }
    /* Set the Data Toggle bit */
    if (pdev->host.hc[hc_num].out_toggle == 0U) {
        pdev->host.hc[hc_num].pid_type = PID_DATA0;
    } else {
        pdev->host.hc[hc_num].pid_type = PID_DATA1 ;
    }
    (void)host_driver_submitrequest(pdev, hc_num);
}

/**
 * @brief  Receives the response data to the setup packet
 * @param  [in] pdev        device instance
 * @param  [in] buff        data buffer when received data.
 * @param  [in] length      the length data in byte have received.
 * @param  [in] hc_num      host channel index
 * @retval None
 */
void usb_host_recvctrldata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num)
{
    pdev->host.hc[hc_num].is_epin   = (uint8_t)1;
    pdev->host.hc[hc_num].pid_type  = PID_DATA1;
    pdev->host.hc[hc_num].xfer_buff = buff;
    pdev->host.hc[hc_num].xfer_len  = length;

    (void)host_driver_submitrequest(pdev, hc_num);
}

/**
 * @brief  sent the bulk packet to the device
 * @param  [in] pdev        device instance
 * @param  [in] buff        data buffer whose data will be sent
 * @param  [in] length      data length in byte
 * @param  [in] hc_num      host channel index
 * @retval None
 */
void usb_host_sendbulkdata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num)
{
    pdev->host.hc[hc_num].is_epin   = 0;
    pdev->host.hc[hc_num].xfer_buff = buff;
    pdev->host.hc[hc_num].xfer_len  = length;
    /* Set the Data Toggle bit */
    if (pdev->host.hc[hc_num].out_toggle == 0U) {
        pdev->host.hc[hc_num].pid_type = PID_DATA0;
    } else {
        pdev->host.hc[hc_num].pid_type = PID_DATA1 ;
    }

    (void)host_driver_submitrequest(pdev, hc_num);
}

/**
 * @brief  receives bulk packet from device
 * @param  [in] pdev        device instance
 * @param  [in] buff        buffer to save the data received from the device
 * @param  [in] length      data length in byte
 * @param  [in] hc_num      host channel index
 * @retval status
 */
void usb_host_recvbulkdata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num)
{
    pdev->host.hc[hc_num].is_epin   = (uint8_t)1;
    pdev->host.hc[hc_num].xfer_buff = buff;
    pdev->host.hc[hc_num].xfer_len  = length;


    if (pdev->host.hc[hc_num].in_toggle == (uint8_t)0) {
        pdev->host.hc[hc_num].pid_type = PID_DATA0;
    } else {
        pdev->host.hc[hc_num].pid_type = PID_DATA1;
    }

    (void)host_driver_submitrequest(pdev, hc_num);
}

/**
 * @brief  receives the device response to the Interrupt IN token
 * @param  [in] pdev        device instance
 * @param  [in] buff        buffer to save the data received from the device
 * @param  [in] length      data length in byte
 * @param  [in] hc_num      host channel index
 * @retval None
 */
void usb_host_recvintdata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num)
{
    pdev->host.hc[hc_num].is_epin   = (uint8_t)1;
    pdev->host.hc[hc_num].xfer_buff = buff;
    pdev->host.hc[hc_num].xfer_len  = length;
    if (pdev->host.hc[hc_num].in_toggle == (uint8_t)0) {
        pdev->host.hc[hc_num].pid_type = PID_DATA0;
    } else {
        pdev->host.hc[hc_num].pid_type = PID_DATA1;
    }
    /* toggle the DATA PID */
    pdev->host.hc[hc_num].in_toggle ^= (uint8_t)1;
    (void)host_driver_submitrequest(pdev, hc_num);
}

/**
 * @brief  send the data on Interrupt OUT Endpoint
 * @param  [in] pdev        device instance
 * @param  [in] buff        data buffer whose data will be sent
 * @param  [in] length      data length in byte
 * @param  [in] hc_num      host channel index
 * @retval None
 */
void usb_host_sentintdata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num)
{
    pdev->host.hc[hc_num].is_epin   = (uint8_t)0;
    pdev->host.hc[hc_num].xfer_buff = buff;
    pdev->host.hc[hc_num].xfer_len  = length;

    if (pdev->host.hc[hc_num].in_toggle == (uint8_t)0) {
        pdev->host.hc[hc_num].pid_type = PID_DATA0;
    } else {
        pdev->host.hc[hc_num].pid_type = PID_DATA1;
    }

    pdev->host.hc[hc_num].in_toggle ^= (uint8_t)1;
    (void)host_driver_submitrequest(pdev, hc_num);
}

/**
 * @brief  receives the Device Response to the Isochronous IN token
 * @param  [in] pdev        device instance
 * @param  [in] buff        buffer to save the data received from the device
 * @param  [in] length      data length in byte
 * @param  [in] hc_num      host channel index
 * @retval None
 */
void usb_host_recvisocdata(usb_core_instance *pdev, uint8_t *buff, uint32_t length, uint8_t hc_num)
{
    pdev->host.hc[hc_num].is_epin   = (uint8_t)1;
    pdev->host.hc[hc_num].xfer_buff = buff;
    pdev->host.hc[hc_num].xfer_len  = length;
    pdev->host.hc[hc_num].pid_type  = PID_DATA0;

    (void)host_driver_submitrequest(pdev, hc_num);
}

/**
 * @brief  Sends the data through Isochronous OUT Endpoint
 * @param  [in] pdev        device instance
 * @param  [in] buff        data buffer whose data will be sent
 * @param  [in] length      data length in byte
 * @param  [in] hc_num      host channel index
 * @retval None
 */
void usb_host_sendisocdata(usb_core_instance *pdev, uint8_t *buff, uint32_t length, uint8_t hc_num)
{
    pdev->host.hc[hc_num].is_epin   = (uint8_t)0;
    pdev->host.hc[hc_num].xfer_buff = buff;
    pdev->host.hc[hc_num].xfer_len  = length;
    pdev->host.hc[hc_num].pid_type  = PID_DATA0;
    (void)host_driver_submitrequest(pdev, hc_num);
}

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
