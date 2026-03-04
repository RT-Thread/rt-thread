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
 * @file usbd_ioreq.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbd_ioreq.h"

/**
*\*\name   USBD_CtrlSendData.
*\*\fun    send data on the ctrl pipe
*\*\param  USBx : USB device
*\*\param  pbuf: pointer to data buffer
*\*\param  len: length of data to be sent
*\*\return USBD_OK
**/
USBD_Status USBD_CtrlSendData (USB_CORE_MODULE *USBx, uint8_t *pbuf, uint16_t len)
{
    USBD_Status ret = USBD_OK;

    USBx->dev.in_ep[0].total_data_len = len;
    USBx->dev.in_ep[0].rem_data_len   = len;
    USBx->dev.device_state = USB_EP0_DATA_IN;

    USBDEV_EP_Tx (USBx, 0, pbuf, len);

    return ret;
}

/**
*\*\name   USBD_CtrlContinueSendData.
*\*\fun    continue sending data on the ctrl pipe
*\*\param  USBx : USB device
*\*\param  pbuf: pointer to data buffer
*\*\param  len: length of data to be sent
*\*\return USBD_OK
**/
USBD_Status USBD_CtrlContinueSendData (USB_CORE_MODULE *USBx, uint8_t *pbuf, uint16_t len)
{
    USBD_Status ret = USBD_OK;

    USBDEV_EP_Tx (USBx, 0, pbuf, len);

    return ret;
}

/**
*\*\name   USBD_CtrlPrepareRx.
*\*\fun    receive data on the ctrl pipe
*\*\param  USBx : USB device
*\*\param  pbuf: pointer to data buffer
*\*\param  len: length of data to be sent
*\*\return USBD_OK
**/
USBD_Status USBD_CtrlPrepareRx (USB_CORE_MODULE *USBx, uint8_t *pbuf, uint16_t len)
{
    USBD_Status ret = USBD_OK;

    USBx->dev.out_ep[0].total_data_len = len;
    USBx->dev.out_ep[0].rem_data_len   = len;
    USBx->dev.device_state = USB_EP0_DATA_OUT;

    USBDEV_EP_PrepareRx (USBx, 0, pbuf, len);

    return ret;
}

/**
*\*\name   USBD_CtrlContinueRx.
*\*\fun    continue receive data on the ctrl pipe
*\*\param  USBx : USB device
*\*\param  pbuf: pointer to data buffer
*\*\param  len: length of data to be sent
*\*\return USBD_OK
**/
USBD_Status USBD_CtrlContinueRx (USB_CORE_MODULE *USBx, uint8_t *pbuf, uint16_t len)
{
    USBD_Status ret = USBD_OK;

    USBDEV_EP_PrepareRx (USBx, 0, pbuf, len);
    return ret;
}

/**
*\*\name   USBD_CtrlSendStatus.
*\*\fun    send zero length packet on the ctrl pipe
*\*\param  USBx : USB device
*\*\return USBD_OK
**/
USBD_Status USBD_CtrlSendStatus (USB_CORE_MODULE *USBx)
{
    USBD_Status ret = USBD_OK;
    USBx->dev.device_state = USB_EP0_STATUS_IN;
    USBDEV_EP_Tx (USBx, 0, USBx->dev.out_ep[0].xfer_buff, 0); 

    USB_EP0_OutStart(USBx);

    return ret;
}

/**
*\*\name   USBD_CtrlReceiveStatus.
*\*\fun    receive zero length packet on the ctrl pipe
*\*\param  USBx : USB device
*\*\return USBD_OK
**/
USBD_Status USBD_CtrlReceiveStatus (USB_CORE_MODULE *USBx)
{
    USBD_Status ret = USBD_OK;
    USBx->dev.device_state = USB_EP0_STATUS_OUT;
    USBDEV_EP_PrepareRx ( USBx, 0, USBx->dev.setup_packet, 0);

    USB_EP0_OutStart(USBx);

    return ret;
}

/**
*\*\name   USBD_GetRxCount.
*\*\fun    returns the received data length
*\*\param  USBx : USB device
*\*\param  epnum: endpoint index
*\*\return USBD_OK
**/
uint16_t  USBD_GetRxCount (USB_CORE_MODULE *USBx , uint8_t epnum)
{
    return USBx->dev.out_ep[epnum].xfer_count;
}
