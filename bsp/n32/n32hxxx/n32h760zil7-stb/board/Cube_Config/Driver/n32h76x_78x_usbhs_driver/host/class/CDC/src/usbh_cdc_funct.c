/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file usbh_cdc_funct.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbh_cdc_funct.h"

CDC_InterfaceDesc_Typedef         CDC_Desc;
CDC_LineCodingTypeDef             CDC_GetLineCode;
CDC_LineCodingTypeDef             CDC_SetLineCode;

extern CDC_Requests               CDC_ReqState;

/**
*\*\name    CDC_GETLineCoding.
*\*\fun     This request allows the host to find out the currently configured line coding.
*\*\param   pdev: Selected device
*\*\param   phost: Selected device property
*\*\return  status.
**/
USBH_Status CDC_GETLineCoding(USB_CORE_MODULE *pdev , USBH_HOST *phost)
{
    phost->Control.setup.b.bmRequestType = USB_D2H | USB_REQ_TYPE_CLASS | USB_REQ_RECIPIENT_INTERFACE;

    phost->Control.setup.b.bRequest = CDC_GET_LINE_CODING;
    phost->Control.setup.b.wValue.w = 0;
    phost->Control.setup.b.wIndex.w = CDC_Desc.CDC_UnionFuncDesc.bMasterInterface; /*At to be checked*/
    phost->Control.setup.b.wLength.w = LINE_CODING_STRUCTURE_SIZE;           

    return USBH_CtrlReq(pdev, phost, CDC_GetLineCode.Array, LINE_CODING_STRUCTURE_SIZE);
}

/**
*\*\name    CDC_SETLineCoding.
*\*\fun     This request allows the host to specify typical asynchronous line-character formatting properties.
*\*\param   pdev: Selected device
*\*\param   phost: Selected device property
*\*\return  status.
**/
USBH_Status CDC_SETLineCoding(USB_CORE_MODULE *pdev, USBH_HOST *phost)
{
    phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_TYPE_CLASS | USB_REQ_RECIPIENT_INTERFACE;

    phost->Control.setup.b.bRequest = CDC_SET_LINE_CODING;
    phost->Control.setup.b.wValue.w = 0;

    phost->Control.setup.b.wIndex.w = CDC_Desc.CDC_UnionFuncDesc.bMasterInterface;

    phost->Control.setup.b.wLength.w = LINE_CODING_STRUCTURE_SIZE;           

    return USBH_CtrlReq(pdev, phost, CDC_SetLineCode.Array , LINE_CODING_STRUCTURE_SIZE );  
}

/**
*\*\name    CDC_SETControlLineState.
*\*\fun     This request generates RS-232/V.24 style control signals.
*\*\param   pdev: Selected device
*\*\param   phost: Selected device property
*\*\return  status.
**/
USBH_Status CDC_SETControlLineState(USB_CORE_MODULE *pdev, USBH_HOST *phost)
{  
    phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_TYPE_CLASS | USB_REQ_RECIPIENT_INTERFACE;

    phost->Control.setup.b.bRequest = CDC_SET_CONTROL_LINE_STATE;
    /*Control Signal Bitmap Values for SetControlLineState*/
    phost->Control.setup.b.wValue.w = CDC_DEACTIVATE_CARRIER_SIGNAL_RTS | CDC_DEACTIVATE_SIGNAL_DTR;

    phost->Control.setup.b.wIndex.w = CDC_Desc.CDC_UnionFuncDesc.bMasterInterface;

    /*Length feild is zero*/
    phost->Control.setup.b.wLength.w = 0;

    return USBH_CtrlReq(pdev, phost, 0 , 0 );
}

/**
*\*\name    CDC_ChangeStateToIssueSetConfig.
*\*\fun     This function prepares the state before issuing the class specific commands.
*\*\param   pdev: Selected device
*\*\param   phost: Selected device property
*\*\return  none.
**/
void CDC_ChangeStateToIssueSetConfig(USB_CORE_MODULE *pdev, USBH_HOST *phost)
{
    phost->gStateBkp = phost->gState  ;
    phost->gState = HOST_CLASS_REQUEST;
    CDC_ReqState = CDC_SET_LINE_CODING_RQUEST;
}

/**
*\*\name    CDC_ChangeStateToIssueSetConfig.
*\*\fun     This function prepares the state before issuing the class specific commands.
*\*\param   pdev: Selected device
*\*\param   phost: Selected device property
*\*\return  none.
**/
void CDC_IssueGetConfig(USB_CORE_MODULE *pdev, USBH_HOST *phost)
{
    phost->gStateBkp =  phost->gState ;
    phost->gState = HOST_CLASS_REQUEST;
    CDC_ReqState = CDC_GET_LINE_CODING_RQUEST;
}
