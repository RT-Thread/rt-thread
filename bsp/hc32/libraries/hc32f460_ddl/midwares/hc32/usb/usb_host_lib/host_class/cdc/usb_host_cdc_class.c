/**
 *******************************************************************************
 * @file  usb_host_cdc_class.c
 * @brief cdc class related functions
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
#include "usb_host_cdc_class.h"
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
 * @addtogroup LL_USB_HOST_CDC USB Host CDC
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
CDC_Requests CDC_ReqState;
CDC_Usercb_TypeDef UserCb;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
#ifdef USB_INTERNAL_DMA_ENABLED
#if defined(__ICCARM__) /*!< IAR Compiler */
#pragma data_alignment = 4
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN static CDC_Machine_TypeDef CDC_Machine;

static CDC_Xfer_TypeDef CDC_TxParam;
static CDC_Xfer_TypeDef CDC_RxParam;

#ifdef USB_INTERNAL_DMA_ENABLED
#if defined(__ICCARM__) /*!< IAR Compiler */
#pragma data_alignment = 4
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN static uint8_t TxBuf[CDC_BUFFER_SIZE];

#ifdef USB_INTERNAL_DMA_ENABLED
#if defined(__ICCARM__) /*!< IAR Compiler */
#pragma data_alignment = 4
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN static uint8_t RxBuf[CDC_BUFFER_SIZE];

static uint8_t RX_Enabled = 0;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void usb_host_cdc_txrxparam_init(void);

static void usb_host_cdc_receivedata(CDC_Xfer_TypeDef *cdc_Data);

static void usb_host_cdc_senddata_process(usb_core_instance *pdev, USBH_HOST *phost);

static void usb_host_cdc_receivedata_process(usb_core_instance *pdev, USBH_HOST *phost);

static HOST_STATUS usb_host_cdc_interface_init(usb_core_instance *pdev, void *phost);

void usb_host_cdc_interface_deinit(usb_core_instance *pdev);

static HOST_STATUS usb_host_cdc_class_process(usb_core_instance *pdev, void *phost);

static HOST_STATUS usb_host_cdc_class_request(usb_core_instance *pdev, void *phost);

usb_host_class_callback_func CDC_cb = {
    usb_host_cdc_interface_init,
    usb_host_cdc_interface_deinit,
    usb_host_cdc_class_request,
    usb_host_cdc_class_process
};

/**
 * @brief  init the vendor interface
 * @param  [in] pdev   device instance
 * @param  [in] phost  host state set
 * @retval status defined by HOST_STATUS
 */
static HOST_STATUS usb_host_cdc_vendor_interface_init(usb_core_instance *pdev, void *phost)
{
    USBH_HOST *pphost = phost;
    HOST_STATUS status = HSTATUS_UNSUPPORTED;
    uint8_t idxep;
    uint8_t bulk_inep_cnt, bulk_inep_idx = 0U;
    uint8_t bulk_outep_cnt, bulk_outep_idx = 0U;
    uint8_t intr_inep_cnt = 0U, intr_inep_idx = 0U;
    /* try to support vendor cdc device */
    if (pphost->device_prop.devitfdesc[0].bInterfaceClass == VENDOR_SPECIFIC) {
        if (pphost->device_prop.devitfdesc[0].bNumEndpoints < 2U) {
            return HSTATUS_UNSUPPORTED;
        }
        bulk_inep_cnt = 0;
        bulk_outep_cnt = 0;
        for (idxep = 0; idxep < pphost->device_prop.devitfdesc[0].bNumEndpoints; idxep++) {
            if ((pphost->device_prop.devepdesc[0][idxep].bmAttributes & EP_TYPE_MSK) == EP_TYPE_BULK) {
                if (0U != (pphost->device_prop.devepdesc[0][idxep].bEndpointAddress & 0x80U)) {
                    bulk_inep_cnt++;
                    bulk_inep_idx = idxep;
                } else {
                    bulk_outep_cnt++;
                    bulk_outep_idx = idxep;
                }
            } else if ((pphost->device_prop.devepdesc[0][idxep].bmAttributes & EP_TYPE_MSK) == EP_TYPE_INTR) {
                if (0U != (pphost->device_prop.devepdesc[0][idxep].bEndpointAddress & 0x80U)) {
                    intr_inep_cnt++;
                    intr_inep_idx = idxep;
                }
            } else {
                ;
            }
        }
        if ((bulk_inep_cnt != 1U) || (bulk_outep_cnt != 1U)) {
            return HSTATUS_UNSUPPORTED;
        }

        if (bulk_inep_cnt == 1U) {
            /* fill the communication endpoint address and length */
            CDC_Machine.CDC_CommItf.ep_addr = pphost->device_prop.devepdesc[0][intr_inep_idx].bEndpointAddress;
            CDC_Machine.CDC_CommItf.length = pphost->device_prop.devepdesc[0][intr_inep_idx].wMaxPacketSize;

            if (0U != (pphost->device_prop.devepdesc[0][intr_inep_idx].bEndpointAddress & 0x80U)) {
                CDC_Machine.CDC_CommItf.notificationEp =
                    (pphost->device_prop.devepdesc[0][intr_inep_idx].bEndpointAddress);
            }
            /* distribute a channel for communication endpoint */
            CDC_Machine.CDC_CommItf.hc_num_in = usb_host_distrch(pdev,
                                                CDC_Machine.CDC_CommItf.notificationEp);

            /* open channel for communication endpoint */
            usb_host_chopen(pdev,
                            CDC_Machine.CDC_CommItf.hc_num_in,
                            pphost->device_prop.devaddr,
                            pphost->device_prop.devspeed,
                            EP_TYPE_INTR,
                            CDC_Machine.CDC_CommItf.length);
        }

        /* fill cdc data endpoint address and length */
        CDC_Machine.CDC_DataItf.ep_addr = pphost->device_prop.devepdesc[0][bulk_inep_idx].bEndpointAddress;
        CDC_Machine.CDC_DataItf.length = pphost->device_prop.devepdesc[0][bulk_inep_idx].wMaxPacketSize;

        CDC_Machine.CDC_DataItf.cdcInEp = (pphost->device_prop.devepdesc[0][bulk_inep_idx].bEndpointAddress);
        CDC_Machine.CDC_DataItf.cdcOutEp = (pphost->device_prop.devepdesc[0][bulk_outep_idx].bEndpointAddress);

        /* distribute channels for cdc data endpoints */
        CDC_Machine.CDC_DataItf.hc_num_out = usb_host_distrch(pdev,
                                             CDC_Machine.CDC_DataItf.cdcOutEp);

        CDC_Machine.CDC_DataItf.hc_num_in = usb_host_distrch(pdev,
                                            CDC_Machine.CDC_DataItf.cdcInEp);

        /* open cdc data endpoints */
        usb_host_chopen(pdev,
                        CDC_Machine.CDC_DataItf.hc_num_out,
                        pphost->device_prop.devaddr,
                        pphost->device_prop.devspeed,
                        EP_TYPE_BULK,
                        CDC_Machine.CDC_DataItf.length);

        usb_host_chopen(pdev,
                        CDC_Machine.CDC_DataItf.hc_num_in,
                        pphost->device_prop.devaddr,
                        pphost->device_prop.devspeed,
                        EP_TYPE_BULK,
                        CDC_Machine.CDC_DataItf.length);

        /* txrx parms init */
        usb_host_cdc_txrxparam_init();

        /* host next state is HOST_CLASS_REQ, so set cdc request to GET_LINE_CODING */
        CDC_ReqState = CDC_GET_LINE_CODING_RQUEST;

        status = HSTATUS_OK;
    }
    return status;
}

/**
 * @brief  init the std cdc interface
 * @param  [in] pdev    device instance
 * @param  [in] phost   host state set
 * @retval status defined by HOST_STATUS
 */
static HOST_STATUS usb_host_cdc_interface_init(usb_core_instance *pdev, void *phost)
{
    USBH_HOST *pphost = phost;
    HOST_STATUS status = HSTATUS_OK;
    uint8_t unsupport_cnt = 0;

    /* Communication Interface */
    if ((pphost->device_prop.devitfdesc[0].bInterfaceClass == COMMUNICATION_DEVICE_CLASS_CODE) &&
            (pphost->device_prop.devitfdesc[0].bInterfaceSubClass == ABSTRACT_CONTROL_MODEL) &&
            (pphost->device_prop.devitfdesc[0].bInterfaceProtocol == COMMON_AT_COMMAND)) {
        /* fill the communication endpoint address and length */
        CDC_Machine.CDC_CommItf.ep_addr = pphost->device_prop.devepdesc[0][0].bEndpointAddress;
        CDC_Machine.CDC_CommItf.length = pphost->device_prop.devepdesc[0][0].wMaxPacketSize;

        if (0U != (pphost->device_prop.devepdesc[0][0].bEndpointAddress & 0x80U)) {
            CDC_Machine.CDC_CommItf.notificationEp =
                (pphost->device_prop.devepdesc[0][0].bEndpointAddress);
        }
        /* distribute a channel for communication endpoint */
        CDC_Machine.CDC_CommItf.hc_num_in = usb_host_distrch(pdev,
                                            CDC_Machine.CDC_CommItf.notificationEp);

        /* open channel for communication endpoint */
        usb_host_chopen(pdev,
                        CDC_Machine.CDC_CommItf.hc_num_in,
                        pphost->device_prop.devaddr,
                        pphost->device_prop.devspeed,
                        EP_TYPE_INTR,
                        CDC_Machine.CDC_CommItf.length);
    } else {
        pphost->user_callbk->huser_devunsupported();
        unsupport_cnt++;
    }

    /* Data Interface */
    if ((pphost->device_prop.devitfdesc[1].bInterfaceClass == DATA_INTERFACE_CLASS_CODE) &&
            (pphost->device_prop.devitfdesc[1].bInterfaceSubClass == RESERVED) &&
            (pphost->device_prop.devitfdesc[1].bInterfaceProtocol == NO_CLASS_SPECIFIC_PROTOCOL_CODE)) {
        /* fill cdc data endpoint address and length */
        CDC_Machine.CDC_DataItf.ep_addr = pphost->device_prop.devepdesc[1][0].bEndpointAddress;
        CDC_Machine.CDC_DataItf.length = pphost->device_prop.devepdesc[1][0].wMaxPacketSize;

        if (0U != (pphost->device_prop.devepdesc[1][0].bEndpointAddress & 0x80U)) {
            CDC_Machine.CDC_DataItf.cdcInEp = (pphost->device_prop.devepdesc[1][0].bEndpointAddress);
        } else {
            CDC_Machine.CDC_DataItf.cdcOutEp = (pphost->device_prop.devepdesc[1][0].bEndpointAddress);
        }

        if (0U != (pphost->device_prop.devepdesc[1][1].bEndpointAddress & 0x80U)) {
            CDC_Machine.CDC_DataItf.cdcInEp = (pphost->device_prop.devepdesc[1][1].bEndpointAddress);
        } else {
            CDC_Machine.CDC_DataItf.cdcOutEp = (pphost->device_prop.devepdesc[1][1].bEndpointAddress);
        }

        /* distribute channels for cdc data endpoints */
        CDC_Machine.CDC_DataItf.hc_num_out = usb_host_distrch(pdev,
                                             CDC_Machine.CDC_DataItf.cdcOutEp);

        CDC_Machine.CDC_DataItf.hc_num_in = usb_host_distrch(pdev,
                                            CDC_Machine.CDC_DataItf.cdcInEp);

        /* open cdc data endpoints */
        usb_host_chopen(pdev,
                        CDC_Machine.CDC_DataItf.hc_num_out,
                        pphost->device_prop.devaddr,
                        pphost->device_prop.devspeed,
                        EP_TYPE_BULK,
                        CDC_Machine.CDC_DataItf.length);

        usb_host_chopen(pdev,
                        CDC_Machine.CDC_DataItf.hc_num_in,
                        pphost->device_prop.devaddr,
                        pphost->device_prop.devspeed,
                        EP_TYPE_BULK,
                        CDC_Machine.CDC_DataItf.length);

        /* txrx parms init */
        usb_host_cdc_txrxparam_init();

        /* host next state is HOST_CLASS_REQ, so set cdc request to GET_LINE_CODING */
        CDC_ReqState = CDC_GET_LINE_CODING_RQUEST;
    } else {
        pphost->user_callbk->huser_devunsupported();
        unsupport_cnt++;
    }

    /* not a stand CDC ACM device */
    if (2U == unsupport_cnt) {
        if (HSTATUS_OK != usb_host_cdc_vendor_interface_init(pdev, phost)) {
            pphost->user_callbk->huser_devunsupported();
        }
    }

    return status;
}

/**
 * @brief  deinit the cdc interface
 * @param  [in] pdev    device instance
 * @retval None
 */
void usb_host_cdc_interface_deinit(usb_core_instance *pdev)
{
    /* halt and free all channels */
    if (0U != CDC_Machine.CDC_CommItf.hc_num_in) {
        usb_hchstop(&pdev->regs, CDC_Machine.CDC_CommItf.hc_num_in);
        (void)usb_host_freech(pdev, CDC_Machine.CDC_CommItf.hc_num_in);
        CDC_Machine.CDC_CommItf.hc_num_in = 0;
    }

    if (0U != CDC_Machine.CDC_DataItf.hc_num_out) {
        usb_hchstop(&pdev->regs, CDC_Machine.CDC_DataItf.hc_num_out);
        (void)usb_host_freech(pdev, CDC_Machine.CDC_DataItf.hc_num_out);
        CDC_Machine.CDC_DataItf.hc_num_out = 0;
    }

    if (0U != CDC_Machine.CDC_DataItf.hc_num_in) {
        usb_hchstop(&pdev->regs, CDC_Machine.CDC_DataItf.hc_num_in);
        (void)usb_host_freech(pdev, CDC_Machine.CDC_DataItf.hc_num_in);
        CDC_Machine.CDC_DataItf.hc_num_in = 0;
    }
}

/**
 * @brief  handing host class request state
 * @param  [in] pdev    device instance
 * @param  [in] phost   host state set
 * @retval status defined by HOST_STATUS
 */
static HOST_STATUS usb_host_cdc_class_request(usb_core_instance *pdev, void *phost)
{
    USBH_HOST *pphost = phost;

    HOST_STATUS status = HSTATUS_BUSY;
    HOST_STATUS ClassReqStatus;

    switch (CDC_ReqState) {

        case CDC_GET_LINE_CODING_RQUEST:

            ClassReqStatus = usb_host_cdc_getlinecoding(pdev, phost);
            if (ClassReqStatus == HSTATUS_OK) {
                CDC_ReqState = CDC_SET_CONTROL_LINE_STATE_REQUEST;
            }
            break;

        case CDC_SET_LINE_CODING_RQUEST:

            ClassReqStatus = usb_host_cdc_setlinecoding(pdev, phost);
            if (ClassReqStatus == HSTATUS_OK) {
                CDC_ReqState = CDC_GET_LINE_CODING_RQUEST;
            }
            if (ClassReqStatus == HSTATUS_UNSUPPORTED) {
                /* Clear Feature should be issued */
                CDC_ReqState = CDC_ERROR_STATE;
            }
            break;

        case CDC_SET_CONTROL_LINE_STATE_REQUEST:

            ClassReqStatus = usb_host_cdc_setcontrollinestate(pdev, phost);
            if (ClassReqStatus == HSTATUS_OK) {
                /* change state to itself */
                CDC_ReqState = CDC_SET_CONTROL_LINE_STATE_REQUEST;
                /* change rx state to CDC_IDLE */
                CDC_RxParam.CDCState = CDC_IDLE;

                status = HSTATUS_OK;
            }
            break;

        case CDC_ERROR_STATE:

            ClassReqStatus = usb_host_clrfeature(pdev,
                                                 phost,
                                                 0x00,
                                                 pphost->ctrlparam.hc_num_out);

            if (ClassReqStatus == HSTATUS_OK) {
                /* change state to GET_LINE_CODING */
                CDC_ReqState = CDC_GET_LINE_CODING_RQUEST;
            }
            break;
        default:
            break;
    }

    return status;
}

/**
 * @brief  process the cdc data send/receive state machine and user application
 * @param  [in] pdev   device instance
 * @param  [in] phost  host state set
 * @retval status defined by HOST_STATUS
 */
static HOST_STATUS usb_host_cdc_class_process(usb_core_instance *pdev, void *phost)
{
    HOST_STATUS status = HSTATUS_OK;
    USBH_HOST *pphost = phost;

    /* application process */
    pphost->user_callbk->huser_application();

    /* send data process */
    usb_host_cdc_senddata_process(pdev, pphost);

    /* receive data process */
    usb_host_cdc_receivedata_process(pdev, pphost);

    return status;
}

/**
 * @brief  process the cdc data send state machine
 * @param  [in] pdev    device instance
 * @param  [in] phost   host state set
 * @retval None
 */
void usb_host_cdc_senddata_process(usb_core_instance *pdev, USBH_HOST *phost)
{
    static uint16_t len;
    HOST_CH_XFER_STATE URB_StatusTx;

    URB_StatusTx = host_driver_getxferstate(pdev, CDC_Machine.CDC_DataItf.hc_num_out);

    switch (CDC_TxParam.CDCState) {
        case CDC_IDLE:
            break;

        case CDC_SEND_DATA:

            if ((URB_StatusTx == HOST_CH_XFER_DONE) || (URB_StatusTx == HOST_CH_XFER_IDLE)) {
                /* check if send data len exceed CDC_DataItf.length */
                if (CDC_TxParam.DataLength > CDC_Machine.CDC_DataItf.length) {

                    len = CDC_Machine.CDC_DataItf.length;
                    /* send data */
                    usb_host_sendbulkdata(pdev,
                                          CDC_TxParam.pRxTxBuff,
                                          len,
                                          CDC_Machine.CDC_DataItf.hc_num_out);
                } else {
                    len = CDC_TxParam.DataLength;
                    /* send all the remaining data */
                    usb_host_sendbulkdata(pdev,
                                          CDC_TxParam.pRxTxBuff,
                                          len,
                                          CDC_Machine.CDC_DataItf.hc_num_out);
                }
                CDC_TxParam.CDCState = CDC_DATA_SENT;
            }

            break;

        case CDC_DATA_SENT:
            /* check send complete */
            if (URB_StatusTx == HOST_CH_XFER_DONE) {
                /* move txbuffer point */
                CDC_TxParam.pRxTxBuff += len;

                /* ecrease data length */
                CDC_TxParam.DataLength -= len;

                if (CDC_TxParam.DataLength == 0U) {
                    CDC_TxParam.CDCState = CDC_IDLE;
                } else {
                    CDC_TxParam.CDCState = CDC_SEND_DATA;
                }
            } else if (URB_StatusTx == HOST_CH_XFER_UNREADY) {
                /* send again */
                usb_host_sendbulkdata(pdev,
                                      (CDC_TxParam.pRxTxBuff),
                                      len,
                                      CDC_Machine.CDC_DataItf.hc_num_out);
            } else {
                ;
            }

            break;

        case CDC_READ_DATA:
            break;

        case CDC_BUSY:
            break;

        case CDC_GET_DATA:
            break;

        case CDC_POLL:
            break;

        case CDC_CTRL_STATE:
            break;
        default:
            break;
    }
}

/**
 * @brief  process the cdc data receive state machine
 * @param  [in] pdev     device instance
 * @param  [in] phost    host state set
 * @retval None
 */
static void usb_host_cdc_receivedata_process(usb_core_instance *pdev, USBH_HOST *phost)
{

    if (RX_Enabled == 1U) {
        HOST_CH_XFER_STATE URB_StatusRx = host_driver_getxferstate(pdev, CDC_Machine.CDC_DataItf.hc_num_in);

        switch (CDC_RxParam.CDCState) {

            case CDC_IDLE:

                /* check if free rxbuf exceed CDC_DataItf.length */
                if (CDC_RxParam.DataLength < (CDC_RxParam.BufferLen - CDC_Machine.CDC_DataItf.length)) {
                    /* receive data */
                    usb_host_recvbulkdata(pdev,
                                          CDC_RxParam.pFillBuff,
                                          CDC_Machine.CDC_DataItf.length,
                                          CDC_Machine.CDC_DataItf.hc_num_in);

                    /* change sate to wait receive complete */
                    CDC_RxParam.CDCState = CDC_GET_DATA;
                }
                break;

            case CDC_GET_DATA:
                /* check XFER_DONE */
                if (URB_StatusRx == HOST_CH_XFER_DONE) {
                    /* increase rx data len */
                    CDC_RxParam.DataLength += (uint16_t)pdev->host.hc[CDC_Machine.CDC_DataItf.hc_num_in].xfer_count;
                    /* move rxbuff poinit */
                    CDC_RxParam.pFillBuff += pdev->host.hc[CDC_Machine.CDC_DataItf.hc_num_in].xfer_count;

                    /* process the received data */
                    usb_host_cdc_receivedata(&CDC_RxParam);

                    /* chage state back to CDC_IDLE */
                    CDC_RxParam.CDCState = CDC_IDLE;
                }
                break;

            case CDC_READ_DATA:

                break;

            case CDC_BUSY:

                break;

            case CDC_SEND_DATA:

                break;

            case CDC_DATA_SENT:

                break;

            case CDC_POLL:

                break;

            case CDC_CTRL_STATE:

                break;
            default:
                break;
        }
    }
}

/**
 * @brief  init tx rx buffer for cdc
 * @param  None
 * @retval None
 */
static void usb_host_cdc_txrxparam_init(void)
{
    /* init tx buffer */
    CDC_TxParam.CDCState = CDC_IDLE;
    CDC_TxParam.DataLength = 0;
    CDC_TxParam.pRxTxBuff = TxBuf;

    /* init rx buffer */
    CDC_RxParam.CDCState = CDC_IDLE;
    CDC_RxParam.DataLength = 0;
    CDC_RxParam.pFillBuff = RxBuf;
    CDC_RxParam.pEmptyBuff = RxBuf;
    CDC_RxParam.BufferLen = sizeof(RxBuf);
}

/**
 * @brief  call user callback fucntion to process the received data
 * @param  [in] cdc_Data    type of CDC_Xfer_TypeDef
 * @retval None
 */
static void usb_host_cdc_receivedata(CDC_Xfer_TypeDef *cdc_Data)
{
    uint8_t *ptr;

    if (cdc_Data->pEmptyBuff < cdc_Data->pFillBuff) {
        ptr = cdc_Data->pFillBuff;
        *ptr = 0x00;

        /* callback user function to process received data */
        UserCb.Receive(cdc_Data->pEmptyBuff, cdc_Data->DataLength);

        cdc_Data->pFillBuff = cdc_Data->pEmptyBuff;
        cdc_Data->DataLength = 0;
    }
}

/**
 * @brief  user call this function to send data to cdc device
 * @param  [in] data     send data buffer
 * @param  [in] length   send length
 * @retval None
 */
void usb_host_cdc_senddata(uint8_t *data, uint16_t length)
{

    if (CDC_TxParam.CDCState == CDC_IDLE) {
        CDC_TxParam.pRxTxBuff = data;
        CDC_TxParam.DataLength = length;
        CDC_TxParam.CDCState = CDC_SEND_DATA;
    }
}

/**
 * @brief  user call this function to enable receive data from device
 * @param  [in] pdev    device instance
 * @retval None
 */
void usb_host_cdc_enable_receive(usb_core_instance *pdev)
{
    RX_Enabled = 1;
}

/**
 * @brief  user call this function to disable receive data from device
 * @param  [in] pdev    device instance
 * @retval None
 */
void usb_host_cdc_disable_receive(usb_core_instance *pdev)
{
    RX_Enabled = 0;
    usb_hchstop(&pdev->regs, CDC_Machine.CDC_DataItf.hc_num_in);
    (void)usb_host_freech(pdev, CDC_Machine.CDC_DataItf.hc_num_in);
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
