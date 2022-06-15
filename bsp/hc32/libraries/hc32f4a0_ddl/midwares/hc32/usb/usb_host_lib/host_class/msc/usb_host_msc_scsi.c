/**
 *******************************************************************************
 * @file  usb_host_msc_scsi.c
 * @brief The SCSI commands。
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
#include "usb_host_ctrltrans.h"
#include "usb_host_def.h"
#include "usb_host_driver.h"
#include <stdio.h>

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

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
MSC_PARAMETER USB_HOST_MSC_Param;

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
#ifdef USB_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ )
#pragma data_alignment=4
#endif
#endif
__USB_ALIGN_BEGIN static uint8_t USB_HOST_DataInBuf[512];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Issues 'Test Unit Ready' command to the device. Once the response
 *         received, it updates the status to upper layer, the length of the
 *         command are 31bytes.
 * @param  [in] pdev        device instance
 * @retval status define by USB_HOST_MSC_STATUS
 */
USB_HOST_MSC_STATUS usb_host_msc_TestUnitReady(usb_core_instance *pdev)
{
    uint8_t index;
    USB_HOST_MSC_STATUS status = USB_HOST_MSC_BUSY;

    if (host_driver_ifdevconnected(pdev) != 0UL) {
        switch (USBH_MSC_BOTXferParam.CmdStateMachine) {
            case USB_HOST_MSC_CMD_SEND:
                USBH_MSC_CBWData.field.CBWTransferLength = 0UL;
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_OUT;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH_TEST_UNIT_READY;
                USBH_MSC_BOTXferParam.pRxTxBuff = USBH_MSC_CSWData.CSWArray;
                USBH_MSC_BOTXferParam.DataLength = HOST_MSC_CSW_MAX_LENGTH;
                USBH_MSC_BOTXferParam.MSCStateCurrent = HOST_MSC_TEST_UNIT_READY;
                for (index = 0U; index < CBW_CB_LENGTH; index++) {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00U;
                }
                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_TEST_UNIT_READY;
                USBH_MSC_BOTXferParam.BOTState = HOST_MSC_SEND_CBW;
                /* Start the transfer, then let the state machine magage the other transactions */
                USBH_MSC_BOTXferParam.MSCState = HOST_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = (uint8_t)USB_HOST_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_WAIT;

                status = USB_HOST_MSC_BUSY;
                break;

            case USB_HOST_MSC_CMD_WAIT:
                switch (USBH_MSC_BOTXferParam.BOTXferStatus) {
                    case USB_HOST_MSC_OK:
                        /* Commands successfully sent and Response Received  */
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_OK;
                        break;
                    case USB_HOST_MSC_FAIL:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_FAIL;
                        break;
                    case USB_HOST_MSC_PHASE_ERROR:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_PHASE_ERROR;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    return status;
}

/**
 * @brief  Issue the 'Read capacity10' command to the device. Once the response
 *         received, it updates the status to upper layer
 * @param  [in] pdev        device instance
 * @retval status define by USB_HOST_MSC_STATUS
 */
USB_HOST_MSC_STATUS usb_host_msc_ReadCapacity10(usb_core_instance *pdev)
{
    uint8_t index;
    USB_HOST_MSC_STATUS status = USB_HOST_MSC_BUSY;

    if (host_driver_ifdevconnected(pdev) != 0UL) {
        switch (USBH_MSC_BOTXferParam.CmdStateMachine) {
            case USB_HOST_MSC_CMD_SEND:
                /*Prepare the CBW and relevent field*/
                USBH_MSC_CBWData.field.CBWTransferLength = XFER_LEN_READ_CAPACITY10;
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_IN;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH;
                USBH_MSC_BOTXferParam.pRxTxBuff = USB_HOST_DataInBuf;
                USBH_MSC_BOTXferParam.MSCStateCurrent = HOST_MSC_READ_CAPACITY10;
                for (index = 0U; index < CBW_CB_LENGTH; index++) {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00U;
                }
                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_READ_CAPACITY10;
                USBH_MSC_BOTXferParam.BOTState = HOST_MSC_SEND_CBW;
                /* Start the transfer, then let the state machine manage the other
                                                            transactions */
                USBH_MSC_BOTXferParam.MSCState = HOST_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = (uint8_t)USB_HOST_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_WAIT;
                status = USB_HOST_MSC_BUSY;
                break;

            case USB_HOST_MSC_CMD_WAIT:
                switch (USBH_MSC_BOTXferParam.BOTXferStatus) {
                    case USB_HOST_MSC_OK:
                        /*assign the capacity*/
                        (((uint8_t *)&USB_HOST_MSC_Param.MSC_Capacity)[3]) = USB_HOST_DataInBuf[0];
                        (((uint8_t *)&USB_HOST_MSC_Param.MSC_Capacity)[2]) = USB_HOST_DataInBuf[1];
                        (((uint8_t *)&USB_HOST_MSC_Param.MSC_Capacity)[1]) = USB_HOST_DataInBuf[2];
                        (((uint8_t *)&USB_HOST_MSC_Param.MSC_Capacity)[0]) = USB_HOST_DataInBuf[3];
                        /*assign the page length*/
                        (((uint8_t *)&USB_HOST_MSC_Param.MSC_PageLength)[1]) = USB_HOST_DataInBuf[6];
                        (((uint8_t *)&USB_HOST_MSC_Param.MSC_PageLength)[0]) = USB_HOST_DataInBuf[7];
                        /* Commands successfully sent and Response Received  */
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_OK;
                        break;
                    case USB_HOST_MSC_FAIL:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_FAIL;
                        break;
                    case USB_HOST_MSC_PHASE_ERROR:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_PHASE_ERROR;
                        break;
                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
    return status;
}

/**
 * @brief  Issue the 'Mode Sense6' Command to the device. This function is used
 *         for reading the WriteProtect Status of the MSC device.
 * @param  [in] pdev        device instance
 * @retval status by USB_HOST_MSC_STATUS
 */
USB_HOST_MSC_STATUS usb_host_msc_ModeSense6(usb_core_instance *pdev)
{
    uint8_t index;
    USB_HOST_MSC_STATUS status = USB_HOST_MSC_BUSY;

    if (host_driver_ifdevconnected(pdev) != 0UL) {
        switch (USBH_MSC_BOTXferParam.CmdStateMachine) {
            case USB_HOST_MSC_CMD_SEND:
                /*Prepare the CBW and relevent field*/
                USBH_MSC_CBWData.field.CBWTransferLength = XFER_LEN_MODE_SENSE6;
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_IN;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH;

                USBH_MSC_BOTXferParam.pRxTxBuff = USB_HOST_DataInBuf;
                USBH_MSC_BOTXferParam.MSCStateCurrent = HOST_MSC_MODE_SENSE6;

                for (index = 0U; index < CBW_CB_LENGTH; index++) {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00U;
                }

                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_MODE_SENSE6;
                USBH_MSC_CBWData.field.CBWCB[2]  = MODE_SENSE_PAGE_CONTROL_FIELD | \
                                                   MODE_SENSE_PAGE_CODE;

                USBH_MSC_CBWData.field.CBWCB[4]  = XFER_LEN_MODE_SENSE6;

                USBH_MSC_BOTXferParam.BOTState = HOST_MSC_SEND_CBW;

                /* Start the transfer, then let the state machine manage the other
                                    transactions */
                USBH_MSC_BOTXferParam.MSCState = HOST_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = (uint8_t)USB_HOST_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_WAIT;

                status = USB_HOST_MSC_BUSY;
                break;

            case USB_HOST_MSC_CMD_WAIT:
                switch (USBH_MSC_BOTXferParam.BOTXferStatus) {
                    case USB_HOST_MSC_OK:
                        /* Assign the Write Protect status */
                        /* If WriteProtect = 0, Writing is allowed
                        If WriteProtect != 0, Disk is Write Protected */
                        if (0U != (USB_HOST_DataInBuf[2] & MASK_MODE_SENSE_WRITE_PROTECT)) {
                            USB_HOST_MSC_Param.MSC_WriteProtect    = DISK_WRITE_PROTECTED;
                        } else {
                            USB_HOST_MSC_Param.MSC_WriteProtect    = 0U;
                        }

                        /* Commands successfully sent and Response Received  */
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_OK;
                        break;
                    case USB_HOST_MSC_FAIL:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_FAIL;
                        break;
                    case USB_HOST_MSC_PHASE_ERROR:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_PHASE_ERROR;
                        break;
                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
    return status;
}

/**
 * @brief  usb_host_msc_RequestSense
 *         Issues the Request Sense command to the device. Once the response
 *         received, it updates the status to upper layer
 * @param  [in] pdev        device instance
 * @retval status defined by USB_HOST_MSC_STATUS
 */
USB_HOST_MSC_STATUS usb_host_msc_RequestSense(usb_core_instance *pdev)
{
    USB_HOST_MSC_STATUS status = USB_HOST_MSC_BUSY;
    uint8_t index;

    if (host_driver_ifdevconnected(pdev) != 0UL) {
        switch (USBH_MSC_BOTXferParam.CmdStateMachine) {
            case USB_HOST_MSC_CMD_SEND:
                /*Prepare the CBW and relevent field*/
                USBH_MSC_CBWData.field.CBWTransferLength = \
                        ALLOCATION_LENGTH_REQUEST_SENSE;
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_IN;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH;

                USBH_MSC_BOTXferParam.pRxTxBuff = USB_HOST_DataInBuf;
                USBH_MSC_BOTXferParam.MSCStateBkp = USBH_MSC_BOTXferParam.MSCStateCurrent;
                USBH_MSC_BOTXferParam.MSCStateCurrent = HOST_MSC_REQUEST_SENSE;

                for (index = 0U; index < CBW_CB_LENGTH; index++) {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00U;
                }

                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_REQUEST_SENSE;
                USBH_MSC_CBWData.field.CBWCB[1]  = DESC_REQUEST_SENSE;
                USBH_MSC_CBWData.field.CBWCB[4]  = ALLOCATION_LENGTH_REQUEST_SENSE;

                USBH_MSC_BOTXferParam.BOTState = HOST_MSC_SEND_CBW;
                /* Start the transfer, then let the state machine magage
                the other transactions */
                USBH_MSC_BOTXferParam.MSCState = HOST_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = (uint8_t)USB_HOST_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_WAIT;
                status = USB_HOST_MSC_BUSY;
                break;

            case USB_HOST_MSC_CMD_WAIT:
                switch (USBH_MSC_BOTXferParam.BOTXferStatus) {
                    case USB_HOST_MSC_OK:
                        /* Get Sense data*/
                        (((uint8_t *)&USB_HOST_MSC_Param.MSC_Sense)[3]) = USB_HOST_DataInBuf[0];
                        (((uint8_t *)&USB_HOST_MSC_Param.MSC_Sense)[2]) = USB_HOST_DataInBuf[1];
                        (((uint8_t *)&USB_HOST_MSC_Param.MSC_Sense)[1]) = USB_HOST_DataInBuf[2];
                        (((uint8_t *)&USB_HOST_MSC_Param.MSC_Sense)[0]) = USB_HOST_DataInBuf[3];

                        /* Commands successfully sent and Response Received  */
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_OK;
                        break;
                    case USB_HOST_MSC_FAIL:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_FAIL;
                        break;
                    case USB_HOST_MSC_PHASE_ERROR:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_PHASE_ERROR;
                        break;
                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
    return status;
}

/**
 * @brief  issue the 'Write10 ' command to the device. Once the response received,
 *         it updates the status to upper layer
 * @param  [in] pdev            device instance
 * @param  [in] dataBuffer      data buffer contains the data to write
 * @param  [in] address         address to which the data will be written
 * @param  [in] nbOfbytes       NbOfbytes to be written
 * @retval status define by USB_HOST_MSC_STATUS
 */
USB_HOST_MSC_STATUS usb_host_msc_Write10(usb_core_instance *pdev,
                                         uint8_t *dataBuffer,
                                         uint32_t address,
                                         uint32_t nbOfbytes)
{
    uint8_t index;
    USB_HOST_MSC_STATUS status = USB_HOST_MSC_BUSY;
    uint16_t nbOfPages;

    if (host_driver_ifdevconnected(pdev) != 0UL) {
        switch (USBH_MSC_BOTXferParam.CmdStateMachine) {
            case USB_HOST_MSC_CMD_SEND:
                USBH_MSC_CBWData.field.CBWTransferLength = nbOfbytes;
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_OUT;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH;
                USBH_MSC_BOTXferParam.pRxTxBuff = dataBuffer;

                for (index = 0U; index < CBW_CB_LENGTH; index++) {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00U;
                }

                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_WRITE10;
                /*logical block address*/
                USBH_MSC_CBWData.field.CBWCB[2]  = (((uint8_t *)&address)[3]) ;
                USBH_MSC_CBWData.field.CBWCB[3]  = (((uint8_t *)&address)[2]);
                USBH_MSC_CBWData.field.CBWCB[4]  = (((uint8_t *)&address)[1]);
                USBH_MSC_CBWData.field.CBWCB[5]  = (((uint8_t *)&address)[0]);

                /*HOST_MSC_PAGE_LENGTH = 512*/
                nbOfPages = (uint16_t)(nbOfbytes / HOST_MSC_PAGE_LENGTH);

                /*Tranfer length */
                USBH_MSC_CBWData.field.CBWCB[7]  = (((uint8_t *)&nbOfPages)[1]) ;
                USBH_MSC_CBWData.field.CBWCB[8]  = (((uint8_t *)&nbOfPages)[0]) ;

                USBH_MSC_BOTXferParam.BOTState = HOST_MSC_SEND_CBW;
                /* Start the transfer, then let the state machine
                magage the other transactions */
                USBH_MSC_BOTXferParam.MSCState = HOST_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = (uint8_t)USB_HOST_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_WAIT;

                status = USB_HOST_MSC_BUSY;
                break;

            case USB_HOST_MSC_CMD_WAIT:
                switch (USBH_MSC_BOTXferParam.BOTXferStatus) {
                    case USB_HOST_MSC_OK:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_OK;
                        break;
                    case USB_HOST_MSC_FAIL:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        break;
                    case USB_HOST_MSC_PHASE_ERROR:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_PHASE_ERROR;
                        break;
                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
    return status;
}

/**
 * @brief  issue the read command to the device. Once the response received,
 *         it updates the status to upper layer
 * @param  [in] pdev            device instance
 * @param  [in] dataBuffer      data buffer will contain the data to be read
 * @param  [in] address         Address from which the data will be read
 * @param  [in] nbOfbytes       number of bytes to be read
 * @retval status defined by USB_HOST_MSC_STATUS
 */
USB_HOST_MSC_STATUS usb_host_msc_Read10(usb_core_instance *pdev,
                                        uint8_t *dataBuffer,
                                        uint32_t address,
                                        uint32_t nbOfbytes)
{
    uint8_t index;
    static USB_HOST_MSC_STATUS status = USB_HOST_MSC_BUSY;
    uint16_t nbOfPages;
    status = USB_HOST_MSC_BUSY;

    if (host_driver_ifdevconnected(pdev) != 0UL) {
        switch (USBH_MSC_BOTXferParam.CmdStateMachine) {
            case USB_HOST_MSC_CMD_SEND:
                /*Prepare the CBW and relevent field*/
                USBH_MSC_CBWData.field.CBWTransferLength = nbOfbytes;
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_IN;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH;

                USBH_MSC_BOTXferParam.pRxTxBuff = dataBuffer;

                for (index = 0U; index < CBW_CB_LENGTH; index++) {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00U;
                }

                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_READ10;

                /*logical block address*/
                USBH_MSC_CBWData.field.CBWCB[2]  = (((uint8_t *)&address)[3]);
                USBH_MSC_CBWData.field.CBWCB[3]  = (((uint8_t *)&address)[2]);
                USBH_MSC_CBWData.field.CBWCB[4]  = (((uint8_t *)&address)[1]);
                USBH_MSC_CBWData.field.CBWCB[5]  = (((uint8_t *)&address)[0]);
                /*HOST_MSC_PAGE_LENGTH = 512*/
                nbOfPages = (uint16_t)(nbOfbytes / HOST_MSC_PAGE_LENGTH);
                /*Tranfer length */
                USBH_MSC_CBWData.field.CBWCB[7]  = (((uint8_t *)&nbOfPages)[1]) ;
                USBH_MSC_CBWData.field.CBWCB[8]  = (((uint8_t *)&nbOfPages)[0]) ;
                USBH_MSC_BOTXferParam.BOTState = HOST_MSC_SEND_CBW;
                /* Start the transfer, then let the state machine
                magage the other transactions */
                USBH_MSC_BOTXferParam.MSCState = HOST_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = (uint8_t)USB_HOST_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_WAIT;
                status = USB_HOST_MSC_BUSY;
                break;

            case USB_HOST_MSC_CMD_WAIT:
                switch (USBH_MSC_BOTXferParam.BOTXferStatus) {
                    case USB_HOST_MSC_OK:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_OK;
                        break;
                    case USB_HOST_MSC_FAIL:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        break;
                    case USB_HOST_MSC_PHASE_ERROR:
                        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
                        status = USB_HOST_MSC_PHASE_ERROR;
                        break;
                    default:
                        break;
                }
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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
