/**
 *******************************************************************************
 * @file  usb_host_msc_bot.c
 * @brief mass storage related functions
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
#include "usb_host_int.h"
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
 * @addtogroup LL_USB_HOST_MSC USB Host MSC
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
#ifdef USB_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN HOST_CSW_PACKET_TypeDef USBH_MSC_CSWData;

USB_HOST_BOTXFER_TypeDef USBH_MSC_BOTXferParam;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
#ifdef USB_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN HostCBWPkt_TypeDef USBH_MSC_CBWData;

static uint32_t BOTStallErrorCount;   /* Keeps count of STALL Error Cases*/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  initializes original state of the mass storage parameters
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_host_msc_init(usb_core_instance *pdev)
{
    if (host_driver_ifdevconnected(pdev) != 0UL) {
        USBH_MSC_CBWData.field.CBWSignature = HOST_MSC_BOT_CBW_SIGNATURE;
        USBH_MSC_CBWData.field.CBWTag = HOST_MSC_BOT_CBW_TAG;
        USBH_MSC_CBWData.field.CBWLUN = 0U;
        USBH_MSC_BOTXferParam.CmdStateMachine = USB_HOST_MSC_CMD_SEND;
    }
    BOTStallErrorCount = 0UL;
    MSCErrorCount = 0U;
}

/**
 * @brief  manages the different states of BOT transfer and updates the
 *         status for the upper layer.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @retval None
 */
void usb_host_msc_botxferprocess(usb_core_instance *pdev, USBH_HOST *phost)
{
    uint8_t xferDirection, index;
    static uint32_t remainingDataLength;
    static uint8_t *datapointer, *datapointer_prev;
    static uint8_t error_direction;
    HOST_STATUS status;

    HOST_CH_XFER_STATE URB_Status;

    if (host_driver_ifdevconnected(pdev) != 0UL) {

        switch (USBH_MSC_BOTXferParam.BOTState) {
            case HOST_MSC_SEND_CBW:
                /* send a CBW */
                usb_host_sendbulkdata(pdev,
                                      &USBH_MSC_CBWData.CBWArray[0],
                                      HOST_MSC_BOT_CBW_PACKET_LENGTH,
                                      MSC_Machine.hc_num_out);
                USBH_MSC_BOTXferParam.BOTStateBkp = HOST_MSC_SEND_CBW;
                USBH_MSC_BOTXferParam.BOTState    = HOST_MSC_SENT_CBW;
                break;
            case HOST_MSC_SENT_CBW:
                URB_Status = host_driver_getxferstate(pdev, MSC_Machine.hc_num_out);
                switch (URB_Status) {
                    case HOST_CH_XFER_DONE:
                        BOTStallErrorCount = 0U;
                        USBH_MSC_BOTXferParam.BOTStateBkp = HOST_MSC_SENT_CBW;
                        /* If the CBW packet is sent successful, then update the state */
                        xferDirection = (USBH_MSC_CBWData.field.CBWFlags & USB_REQ_DIR_MASK);
                        if (USBH_MSC_CBWData.field.CBWTransferLength != 0UL) {
                            remainingDataLength = USBH_MSC_CBWData.field.CBWTransferLength ;
                            datapointer         = USBH_MSC_BOTXferParam.pRxTxBuff;
                            datapointer_prev    = datapointer;
                            /* If there has data transfer stage, update the direction whether it is D2H or H2D */
                            if (xferDirection == USB_D2H) {
                                USBH_MSC_BOTXferParam.BOTState = HOST_MSC_BOT_DATAIN_STATE;
                            } else {
                                USBH_MSC_BOTXferParam.BOTState = HOST_MSC_BOT_DATAOUT_STATE;
                            }
                        } else {
                            /* If there has not data transfer stage also update the state */
                            USBH_MSC_BOTXferParam.BOTState = HOST_MSC_RECEIVE_CSW_STATE;
                        }
                        break;
                    case HOST_CH_XFER_UNREADY:
                        USBH_MSC_BOTXferParam.BOTState  = USBH_MSC_BOTXferParam.BOTStateBkp;
                        break;
                    case HOST_CH_XFER_STALL:
                        error_direction                 = HOST_MSC_DIR_OUT;
                        USBH_MSC_BOTXferParam.BOTState  = HOST_MSC_BOT_ERROR_OUT;
                        break;
                    default:
                        break;
                }
                break;

            case HOST_MSC_BOT_DATAIN_STATE:
                URB_Status = host_driver_getxferstate(pdev, MSC_Machine.hc_num_in);
                if ((URB_Status == HOST_CH_XFER_DONE) \
                        || (USBH_MSC_BOTXferParam.BOTStateBkp != HOST_MSC_BOT_DATAIN_STATE)) {
                    BOTStallErrorCount = 0U;
                    USBH_MSC_BOTXferParam.BOTStateBkp = HOST_MSC_BOT_DATAIN_STATE;

                    if (remainingDataLength > MSC_Machine.MSC_BulkInEpSize) {
                        usb_host_recvbulkdata(pdev,
                                              datapointer,
                                              MSC_Machine.MSC_BulkInEpSize,
                                              MSC_Machine.hc_num_in);
                        remainingDataLength -= MSC_Machine.MSC_BulkInEpSize;
                        datapointer          = datapointer + MSC_Machine.MSC_BulkInEpSize;
                    } else if (remainingDataLength == 0UL) {
                        /* If value was 0, and successful transfer, then change the state */
                        USBH_MSC_BOTXferParam.BOTState = HOST_MSC_RECEIVE_CSW_STATE;
                    } else {
                        usb_host_recvbulkdata(pdev,
                                              datapointer,
                                              (uint16_t)remainingDataLength,
                                              MSC_Machine.hc_num_in);
                        remainingDataLength = 0UL;
                    }
                } else if (URB_Status == HOST_CH_XFER_STALL) {
                    error_direction                 = HOST_MSC_DIR_IN;
                    USBH_MSC_BOTXferParam.BOTState  = HOST_MSC_BOT_ERROR_IN;
                    USBH_MSC_BOTXferParam.BOTStateBkp = HOST_MSC_RECEIVE_CSW_STATE;
                } else {
                    ;
                }
                break;
            case HOST_MSC_BOT_DATAOUT_STATE:
                URB_Status = host_driver_getxferstate(pdev, MSC_Machine.hc_num_out);
                if (URB_Status == HOST_CH_XFER_DONE) {
                    BOTStallErrorCount = 0UL;
                    USBH_MSC_BOTXferParam.BOTStateBkp = HOST_MSC_BOT_DATAOUT_STATE;
                    if (remainingDataLength > MSC_Machine.MSC_BulkOutEpSize) {
                        usb_host_sendbulkdata(pdev,
                                              datapointer,
                                              MSC_Machine.MSC_BulkOutEpSize,
                                              MSC_Machine.hc_num_out);
                        datapointer_prev = datapointer;
                        datapointer = datapointer + MSC_Machine.MSC_BulkOutEpSize;

                        remainingDataLength = remainingDataLength - MSC_Machine.MSC_BulkOutEpSize;
                    } else if (remainingDataLength == 0UL) {
                        USBH_MSC_BOTXferParam.BOTState = HOST_MSC_RECEIVE_CSW_STATE;
                    } else {
                        usb_host_sendbulkdata(pdev,
                                              datapointer,
                                              (uint16_t)remainingDataLength,
                                              MSC_Machine.hc_num_out);
                        remainingDataLength = 0UL;
                    }
                } else if (URB_Status == HOST_CH_XFER_UNREADY) {
                    if (datapointer != datapointer_prev) {
                        usb_host_sendbulkdata(pdev,
                                              (datapointer - MSC_Machine.MSC_BulkOutEpSize),
                                              MSC_Machine.MSC_BulkOutEpSize,
                                              MSC_Machine.hc_num_out);
                    } else {
                        usb_host_sendbulkdata(pdev,
                                              datapointer,
                                              MSC_Machine.MSC_BulkOutEpSize,
                                              MSC_Machine.hc_num_out);
                    }
                } else if (URB_Status == HOST_CH_XFER_STALL) {
                    error_direction = HOST_MSC_DIR_OUT;
                    USBH_MSC_BOTXferParam.BOTState  = HOST_MSC_BOT_ERROR_OUT;
                    USBH_MSC_BOTXferParam.BOTStateBkp = HOST_MSC_RECEIVE_CSW_STATE;
                } else {
                    ;
                }
                break;

            case HOST_MSC_RECEIVE_CSW_STATE:
                USBH_MSC_BOTXferParam.BOTStateBkp = HOST_MSC_RECEIVE_CSW_STATE;
                USBH_MSC_BOTXferParam.pRxTxBuff = USBH_MSC_CSWData.CSWArray;
                USBH_MSC_BOTXferParam.DataLength = HOST_MSC_CSW_MAX_LENGTH;
                for (index = 0U; index < HOST_MSC_CSW_LENGTH; index++) {
                    USBH_MSC_CSWData.CSWArray[index] = 0U;
                }

                USBH_MSC_CSWData.CSWArray[0] = 0U;
                usb_host_recvbulkdata(pdev,
                                      USBH_MSC_BOTXferParam.pRxTxBuff,
                                      HOST_MSC_CSW_MAX_LENGTH,
                                      MSC_Machine.hc_num_in);
                USBH_MSC_BOTXferParam.BOTState = HOST_MSC_DECODE_CSW;

                break;

            case HOST_MSC_DECODE_CSW:
                URB_Status = host_driver_getxferstate(pdev, MSC_Machine.hc_num_in);
                if (URB_Status == HOST_CH_XFER_DONE) {
                    BOTStallErrorCount                  = 0UL;
                    USBH_MSC_BOTXferParam.BOTStateBkp   = HOST_MSC_RECEIVE_CSW_STATE;
                    USBH_MSC_BOTXferParam.MSCState      = USBH_MSC_BOTXferParam.MSCStateCurrent ;
                    USBH_MSC_BOTXferParam.BOTXferStatus = usb_host_msc_cswdecode(pdev, phost);
                } else if (URB_Status == HOST_CH_XFER_STALL) {
                    error_direction                 = HOST_MSC_DIR_IN;
                    USBH_MSC_BOTXferParam.BOTState  = HOST_MSC_BOT_ERROR_IN;
                } else {
                    ;
                }
                break;

            case HOST_MSC_BOT_ERROR_IN:
                status = usb_host_msc_botabort(pdev, phost, HOST_MSC_DIR_IN);
                if (status == HSTATUS_OK) {
                    if (error_direction == HOST_MSC_BOTH_DIR) {
                        USBH_MSC_BOTXferParam.BOTState = HOST_MSC_BOT_ERROR_OUT;
                    } else {
                        /* switch back to the original state */
                        USBH_MSC_BOTXferParam.BOTState = USBH_MSC_BOTXferParam.BOTStateBkp;
                    }
                } else if (status == HSTATUS_UNRECOVERED_ERROR) {
                    /* This means that there is a STALL Error limit, Do Reset Recovery */
                    USBH_MSC_BOTXferParam.BOTXferStatus = (uint8_t)USB_HOST_MSC_PHASE_ERROR;
                } else {
                    ;
                }
                break;
            case HOST_MSC_BOT_ERROR_OUT:
                status = usb_host_msc_botabort(pdev, phost, HOST_MSC_DIR_OUT);
                if (status == HSTATUS_OK) {
                    /* switch back to the original state */
                    USBH_MSC_BOTXferParam.BOTState = USBH_MSC_BOTXferParam.BOTStateBkp;
                } else if (status == HSTATUS_UNRECOVERED_ERROR) {
                    /* This means that there is a STALL Error limit, Do Reset Recovery */
                    USBH_MSC_BOTXferParam.BOTXferStatus = (uint8_t)USB_HOST_MSC_PHASE_ERROR;
                } else {
                    ;
                }
                break;

            default:
                break;
        }
    }
}

/**
 * @brief  manages the different Error handling for STALL
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @param  [in] direction   IN / OUT
 * @retval None
 */
HOST_STATUS usb_host_msc_botabort(usb_core_instance *pdev, USBH_HOST *phost, uint8_t direction)
{
    HOST_STATUS status;

    status = HSTATUS_BUSY;

    switch (direction) {
        case HOST_MSC_DIR_IN:
            /* send ClrFeture on Bulk IN endpoint */
            status = usb_host_clrfeature(pdev,
                                         phost,
                                         MSC_Machine.MSC_BulkInEp,
                                         MSC_Machine.hc_num_in);
            break;
        case HOST_MSC_DIR_OUT:
            /* send ClrFeature on Bulk OUT endpoint */
            status = usb_host_clrfeature(pdev,
                                         phost,
                                         MSC_Machine.MSC_BulkOutEp,
                                         MSC_Machine.hc_num_out);
            break;
        default:
            break;
    }
    BOTStallErrorCount++;
    if (BOTStallErrorCount > 4UL) {
        status = HSTATUS_UNRECOVERED_ERROR;
    }
    return status;
}

/**
 * @brief  Decodes the CSW received by the device and updates the same to upper layer
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @retval On success USB_HOST_MSC_OK, on failure USB_HOST_MSC_FAIL
 */
uint8_t usb_host_msc_cswdecode(usb_core_instance *pdev, USBH_HOST *phost)
{
    USB_HOST_MSC_STATUS status;
    uint32_t dataXferCount;
    status = USB_HOST_MSC_FAIL;

    if (host_driver_ifdevconnected(pdev) != 0UL) {
        dataXferCount = host_driver_getxfercnt(pdev, MSC_Machine.hc_num_in);
        if (dataXferCount != HOST_MSC_CSW_LENGTH) {
            /*(4) Hi > Dn (Host expects to receive data from the device,
            Device intends to transfer no data)
            (5) Hi > Di (Host expects to receive data from the device,
            Device intends to send data to the host)
            (9) Ho > Dn (Host expects to send data to the device,
            Device intends to transfer no data)
            (11) Ho > Do  (Host expects to send data to the device,
            Device intends to receive data from the host)*/
            status = USB_HOST_MSC_PHASE_ERROR;
        } else {
            /* CSW length is Correct */

            /* Check validity of the CSW Signature and CSWStatus */
            if (USBH_MSC_CSWData.field.dCSWSignature == HOST_MSC_BOT_CSW_SIGNATURE) {
                /* Check Condition 1. dCSWSignature is equal to 53425355h */
                if (USBH_MSC_CSWData.field.dCSWTag == USBH_MSC_CBWData.field.CBWTag) {
                    /* Check Condition 3. dCSWTag matches the dCBWTag from the
                    corresponding CBW */
                    if (USBH_MSC_CSWData.field.dCSWStatus == (uint8_t)USB_HOST_MSC_OK) {
                        /* Refer to USB Mass-Storage Class : BOT (www.usb.org)

                        Hn Host expects no data transfers
                        Hi Host expects to receive data from the device
                        Ho Host expects to send data to the device

                        Dn Device intends to transfer no data
                        Di Device intends to send data to the host
                        Do Device intends to receive data from the host

                        Section 6.7
                        (1) Hn = Dn (Host expects no data transfers,
                        Device intends to transfer no data)
                        (6) Hi = Di (Host expects to receive data from the device,
                        Device intends to send data to the host)
                        (12) Ho = Do (Host expects to send data to the device,
                        Device intends to receive data from the host)
                        */
                        status = USB_HOST_MSC_OK;
                    } else if (USBH_MSC_CSWData.field.dCSWStatus == (uint8_t)USB_HOST_MSC_FAIL) {
                        status = USB_HOST_MSC_FAIL;
                    } else if (USBH_MSC_CSWData.field.dCSWStatus == (uint8_t)USB_HOST_MSC_PHASE_ERROR) {
                        /* Refer to USB Mass-Storage Class : BOT (www.usb.org)
                        Section 6.7
                        (2) Hn < Di ( Host expects no data transfers,
                        Device intends to send data to the host)
                        (3) Hn < Do ( Host expects no data transfers,
                        Device intends to receive data from the host)
                        (7) Hi < Di ( Host expects to receive data from the device,
                        Device intends to send data to the host)
                        (8) Hi <> Do ( Host expects to receive data from the device,
                        Device intends to receive data from the host)
                        (10) Ho <> Di (Host expects to send data to the device,
                        Di Device intends to send data to the host)
                        (13) Ho < Do (Host expects to send data to the device,
                        Device intends to receive data from the host)
                        */
                        status = USB_HOST_MSC_PHASE_ERROR;
                    } else {
                        ;
                    }
                }
            } else {
                status = USB_HOST_MSC_PHASE_ERROR;
            }
        }
    }

    USBH_MSC_BOTXferParam.BOTXferStatus  = (uint8_t)status;
    return (uint8_t)status;
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
