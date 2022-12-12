/**
 *******************************************************************************
 * @file  usb_host_cdc_ctrl.c
 * @brief The CDC ctrl functions
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
#include "usb_host_cdc_ctrl.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CDC
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

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern CDC_Requests               CDC_ReqState;
CDC_LineCodingTypeDef             CDC_SetLineCode;

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static CDC_InterfaceDesc_Typedef         CDC_Desc;
static CDC_LineCodingTypeDef             CDC_GetLineCode;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  host send ctrl request to get line coding
 * @param  [in] pdev    device instance
 * @param  [in] phost   host state set
 * @retval status define by HOST_STATUS
 */
HOST_STATUS usb_host_cdc_getlinecoding(usb_core_instance *pdev, USBH_HOST *phost)
{
    phost->ctrlparam.setup.b.bmRequestType = USB_D2H | USB_REQ_TYPE_CLASS | \
            USB_REQ_RECIPIENT_INTERFACE;

    phost->ctrlparam.setup.b.bRequest = CDC_GET_LINE_CODING;
    phost->ctrlparam.setup.b.wValue.w = 0;
    phost->ctrlparam.setup.b.wIndex.w = CDC_Desc.CDC_UnionFuncDesc.bControlInterface;
    phost->ctrlparam.setup.b.wLength.w = LINE_CODING_STRUCTURE_SIZE;


    return usb_host_ctrlreq(pdev, phost, CDC_GetLineCode.Array, LINE_CODING_STRUCTURE_SIZE);
}

/**
 * @brief  host send ctrl request to set line coding
 *         to config Baud rate/Stop bits/Parity/Data bits
 * @param  [in] pdev    device instance
 * @param  [in] phost   host state set
 * @retval status define by HOST_STATUS
 */
HOST_STATUS usb_host_cdc_setlinecoding(usb_core_instance *pdev, USBH_HOST *phost)
{

    phost->ctrlparam.setup.b.bmRequestType = USB_H2D | USB_REQ_TYPE_CLASS | \
            USB_REQ_RECIPIENT_INTERFACE;

    phost->ctrlparam.setup.b.bRequest = CDC_SET_LINE_CODING;
    phost->ctrlparam.setup.b.wValue.w = 0;

    phost->ctrlparam.setup.b.wIndex.w = CDC_Desc.CDC_UnionFuncDesc.bControlInterface;

    phost->ctrlparam.setup.b.wLength.w = LINE_CODING_STRUCTURE_SIZE;

    return usb_host_ctrlreq(pdev, phost, CDC_SetLineCode.Array, LINE_CODING_STRUCTURE_SIZE);
}

/**
 * @brief  host send ctrl request to set control line state
 * @param  [in] pdev    device instance
 * @param  [in] phost   host state set
 * @retval status define by HOST_STATUS
 */
HOST_STATUS usb_host_cdc_setcontrollinestate(usb_core_instance *pdev, USBH_HOST *phost)
{
    phost->ctrlparam.setup.b.bmRequestType = USB_H2D | USB_REQ_TYPE_CLASS | \
            USB_REQ_RECIPIENT_INTERFACE;

    phost->ctrlparam.setup.b.bRequest = CDC_SET_CONTROL_LINE_STATE;

    phost->ctrlparam.setup.b.wValue.w = CDC_DEACTIVATE_CARRIER_SIGNAL_RTS | \
                                        CDC_DEACTIVATE_SIGNAL_DTR;

    phost->ctrlparam.setup.b.wIndex.w = CDC_Desc.CDC_UnionFuncDesc.bControlInterface;

    phost->ctrlparam.setup.b.wLength.w = 0;

    return usb_host_ctrlreq(pdev, phost, NULL, 0U);
}

/**
 * @brief  user call this function to issue set line coding request
 *         before call this funtion user need fill CDC_SetLineCode with config params
 * @param  [in] pdev    device instance
 * @param  [in] phost   host state set
 * @retval None
 */
void usb_host_cdc_issue_setlinecoding(usb_core_instance *pdev, USBH_HOST *phost)
{
    phost->host_state_backup = phost->host_state  ;
    phost->host_state = HOST_CLASS_REQ;
    CDC_ReqState = CDC_SET_LINE_CODING_RQUEST;
}

/**
 * @brief  user call this function to issue get line coding request
 * @param  [in] pdev    device instance
 * @param  [in] phost   host state set
 * @retval None
 */
void usb_host_cdc_issue_getlinecoding(usb_core_instance *pdev, USBH_HOST *phost)
{
    phost->host_state_backup =  phost->host_state ;
    phost->host_state = HOST_CLASS_REQ;
    CDC_ReqState = CDC_GET_LINE_CODING_RQUEST;
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
