/**
 *******************************************************************************
 * @file  usb_dev_core.c
 * @brief USBD core functions.
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
#include "usb_dev_core.h"
#include "usb_dev_stdreq.h"
#include "usb_dev_ctrleptrans.h"
#include "usb_dev_driver.h"
#include "usb_dev_int.h"
#include "usb_bsp.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CORE LL USB Device Core
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
void usb_setup_process(usb_core_instance *pdev);
void usb_dataout_process(usb_core_instance *pdev, uint8_t epnum);
void usb_datain_process(usb_core_instance *pdev, uint8_t epnum);
void usb_sof_process(usb_core_instance *pdev);
void usb_dev_rst(usb_core_instance *pdev);
void usb_dev_susp(usb_core_instance *pdev);
void usb_dev_resume(usb_core_instance *pdev);
void usb_ctrlconn(usb_core_instance *pdev, uint8_t conn);
void usb_isoinincomplt_process(usb_core_instance *pdev);
void usb_isooutincomplt_process(usb_core_instance *pdev);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
__IO uint32_t SET_TEST_MODE;
static usb_dev_int_cbk_typedef dev_int_cbk = {
    &usb_dev_rst,
    &usb_ctrlconn,
    &usb_dev_susp,
    &usb_dev_resume,
    &usb_sof_process,
    &usb_setup_process,
    &usb_dataout_process,
    &usb_datain_process,
    &usb_isoinincomplt_process,
    &usb_isooutincomplt_process
};

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
usb_dev_int_cbk_typedef  *dev_int_cbkpr = &dev_int_cbk;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Initailizes the device stack and load the class driver
 * @param  [in] pdev            device instance
 * @param  [in] pdesc           Device Descriptor
 * @param  [in] class_cb        Class callback structure address
 * @param  [in] usr_cb          User callback structure address
 * @retval None
 */
void usb_dev_init(usb_core_instance *pdev,
                  usb_dev_desc_func *pdesc,
                  usb_dev_class_func *class_cb,
                  usb_dev_user_func *usr_cb)
{
    usb_bsp_init(pdev);
    pdev->dev.class_callback = class_cb;
    pdev->dev.user_callback  = usr_cb;
    pdev->dev.desc_callback  = pdesc;
    usb_initdev(pdev);
    pdev->dev.user_callback->user_init();
    pdev->dev.device_state   = USB_EP0_IDLE;
    usb_bsp_nvicconfig();
}

/**
 * @brief  De-initailizes the device stack and load the class driver
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_dev_deinit(usb_core_instance *pdev)
{
    (void)(pdev);
}

/**
 * @brief  Handle Reset event
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_dev_rst(usb_core_instance *pdev)
{
    usb_opendevep(pdev, 0x00U, USB_MAX_EP0_SIZE, EP_TYPE_CTRL);
    usb_opendevep(pdev, 0x80U, USB_MAX_EP0_SIZE, EP_TYPE_CTRL);
    pdev->dev.device_cur_status = USB_DEV_DEFAULT;
    pdev->dev.user_callback->user_devrst();
}

/**
 * @brief  Handle device connection and disconnection event
 * @param  [in] pdev        device instance
 * @param  [in] conn        1 or 0
 * @retval None
 */
void usb_ctrlconn(usb_core_instance *pdev, uint8_t conn)
{
    __IO uint8_t tmp_1;
    tmp_1 = conn;
    if (tmp_1 != 0U) {
        pdev->dev.user_callback->user_devconn();
        pdev->dev.connection_status = 1U;
    } else {
        pdev->dev.user_callback->user_devdisconn();
        pdev->dev.class_callback->class_deinit(pdev);
        pdev->dev.connection_status = 0U;
    }
}

/**
 * @brief  Handle Suspend event
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_dev_susp(usb_core_instance *pdev)
{
    pdev->dev.device_old_status  = pdev->dev.device_cur_status;
    pdev->dev.device_cur_status  = USB_DEV_SUSPENDED;
    pdev->dev.user_callback->user_devsusp();
}

/**
 * @brief  Handle Resume event
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_dev_resume(usb_core_instance *pdev)
{
    pdev->dev.user_callback->user_devresume();
    pdev->dev.device_cur_status = pdev->dev.device_old_status;
    pdev->dev.device_cur_status = USB_DEV_CONFIGURED;
}

/**
 * @brief  Handle SOF event
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_sof_process(usb_core_instance *pdev)
{
    if (0U != pdev->dev.class_callback->class_sof) {
        pdev->dev.class_callback->class_sof(pdev);
    }
}

/**
 * @brief  Handle the setup stage
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_setup_process(usb_core_instance *pdev)
{
    USB_SETUP_REQ req;

    usb_parsesetupreq(pdev, &req);

    switch (req.bmRequest & 0x1FU) {
        case USB_REQ_RECIPIENT_DEVICE:
            usb_standarddevreq(pdev, &req);
            break;

        case USB_REQ_RECIPIENT_INTERFACE:
            usb_standarditfreq(pdev, &req);
            break;

        case USB_REQ_RECIPIENT_ENDPOINT:
            usb_standardepreq(pdev, &req);
            break;

        default:
            usb_stalldevep(pdev, req.bmRequest & 0x80U);
            break;
    }
}

/**
 * @brief  Handle data out stage
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_dataout_process(usb_core_instance *pdev, uint8_t epnum)
{
    USB_DEV_EP *ep;

    if (epnum == 0U) {
        ep = &pdev->dev.out_ep[0];
        if (pdev->dev.device_state == USB_EP0_DATA_OUT) {
            if (ep->rem_data_len > ep->maxpacket) {
                ep->rem_data_len  -=  ep->maxpacket;

                if (pdev->basic_cfgs.dmaen == 1U) {
                    /* in slave mode this, is handled by the RxSTSQLvl ISR */
                    ep->xfer_buff += ep->maxpacket;
                }
                usb_readytorx(pdev, 0U, ep->xfer_buff, (uint16_t)LL_MIN(ep->rem_data_len, ep->maxpacket));
            } else {
                if (ep->xfer_count > ep->rem_data_len) {

                }
                ep->rem_data_len = 0UL;
                if ((pdev->dev.class_callback->ep0_dataout != NULL) &&
                        (pdev->dev.device_cur_status == USB_DEV_CONFIGURED)) {
                    pdev->dev.class_callback->ep0_dataout(pdev);
                }
                usb_ctrlstatustx(pdev);
            }
        }
    } else if ((pdev->dev.class_callback->class_dataout != NULL) && (pdev->dev.device_cur_status == USB_DEV_CONFIGURED)) {
        pdev->dev.class_callback->class_dataout(pdev, epnum);
    } else {
        ;
    }
}

/**
 * @brief  Handle data in stage
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_datain_process(usb_core_instance *pdev, uint8_t epnum)
{
    USB_DEV_EP *ep;

    if (epnum == 0U) {
        ep = &pdev->dev.in_ep[0];
        if (pdev->dev.device_state == USB_EP0_DATA_IN) {
            if (ep->rem_data_len > ep->maxpacket) {
                ep->rem_data_len  -=  ep->maxpacket;
                if (pdev->basic_cfgs.dmaen == 1U) {
                    /* in slave mode this, is handled by the TxFifoEmpty ISR */
                    ep->xfer_buff += ep->maxpacket;
                }
                usb_deveptx(pdev, 0U, ep->xfer_buff, ep->rem_data_len);
            } else {
                /* last packet is MPS multiple, so send ZLP packet */
                if ((ep->total_data_len % ep->maxpacket == 0U) &&
                        (ep->total_data_len >= ep->maxpacket) &&
                        (ep->total_data_len < ep->ctl_data_len)) {
                    usb_deveptx(pdev, 0U, NULL, 0UL);
                    ep->ctl_data_len = 0UL;
                } else {
                    if ((pdev->dev.class_callback->ep0_datain != NULL) &&
                            (pdev->dev.device_cur_status == USB_DEV_CONFIGURED)) {
                        pdev->dev.class_callback->ep0_datain(pdev);
                    }
                    usb_ctrlstatusrx(pdev);
                }
            }
        }
        if (pdev->dev.test_mode == 1U) {
            usb_runtestmode(&pdev->regs, SET_TEST_MODE);
            pdev->dev.test_mode = 0U;
        } else {
        }
    } else if ((pdev->dev.class_callback->class_datain != NULL) && (pdev->dev.device_cur_status == USB_DEV_CONFIGURED)) {
        pdev->dev.class_callback->class_datain(pdev, epnum);
    } else {
        ;
    }
}

/**
 * @brief  Handle iso in incomplete event
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_isoinincomplt_process(usb_core_instance *pdev)
{
    pdev->dev.class_callback->class_syn_in_incomplt(pdev);
}

/**
 * @brief  Handle iso out incomplete event
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_isooutincomplt_process(usb_core_instance *pdev)
{
    pdev->dev.class_callback->class_syn_out_incomplt(pdev);
}

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
