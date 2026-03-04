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
 * @file usbh_ioreq.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "usbh_ioreq.h"

static USBH_Status USBH_SubmitSetupRequest(USBH_HOST *phost, uint8_t* buff, uint16_t length);

/**
*\*\name    USBH_CtrlReq.
*\*\fun     USBH_CtrlReq sends a control request and provide the status after completion of the request
*\*\param   USBx: selected device.
*\*\param   phost: host state set.
*\*\param   buff: data buffer address to store the response
*\*\param   length: length of the response
*\*\return  status.
*\*\
**/
USBH_Status USBH_CtrlReq(USB_CORE_MODULE *USBx, USBH_HOST *phost, uint8_t *buff, uint16_t length)
{
    USBH_Status status;
    status = USBH_BUSY;

    switch(phost->RequestState)
    {
        case CMD_SEND:
            /* Start a SETUP transfer */
            USBH_SubmitSetupRequest(phost, buff, length);
            phost->RequestState = CMD_WAIT;
            status = USBH_BUSY;
        break;

        case CMD_WAIT:
            if(phost->Control.state == CTRL_COMPLETE) 
            {
                /* Commands successfully sent and Response Received  */       
                phost->RequestState = CMD_SEND;
                phost->Control.state =CTRL_IDLE;  
                status = USBH_OK;      
            }
            else if(phost->Control.state == CTRL_ERROR)
            {
                /* Failure Mode */
                phost->RequestState = CMD_SEND;
                status = USBH_FAIL;
            }   
            else if(phost->Control.state == CTRL_STALLED)
            {
                /* Commands successfully sent and Response Received  */       
                phost->RequestState = CMD_SEND;
                status = USBH_NOT_SUPPORTED;
            }
        break;

        default:
        break; 
    }
    return status;
}

/**
*\*\name    USBH_CtrlSendSetup.
*\*\fun     Sends the Setup Packet to the Device.
*\*\param   USBx: selected device.
*\*\param   buff: data buffer address to store the response
*\*\param   hch_num: Host channel Number
*\*\return  status.
*\*\
**/
USBH_Status USBH_CtrlSendSetup(USB_CORE_MODULE *USBx, uint8_t *buff, uint8_t hch_num)
{
    USBx->host.hch[hch_num].ep_is_in = 0;
    USBx->host.hch[hch_num].data_pid = HCH_PID_SETUP;   
    USBx->host.hch[hch_num].xfer_buff = buff;
    USBx->host.hch[hch_num].xfer_len = USBH_SETUP_PKT_SIZE;   

    return (USBH_Status)HOST_SubmitRequest (USBx , hch_num);   
}

/**
*\*\name    USBH_CtrlSendSetup.
*\*\fun     Sends the Setup Packet to the Device.
*\*\param   USBx: selected device.
*\*\param   buff: data buffer address to store the response
*\*\param   length: Length of the data to be sent
*\*\param   hch_num: Host channel Number
*\*\return  status.
*\*\
**/
USBH_Status USBH_CtrlSendData(USB_CORE_MODULE *USBx, uint8_t *buff, uint16_t length, uint8_t hch_num)
{
    USBx->host.hch[hch_num].ep_is_in = 0;
    USBx->host.hch[hch_num].xfer_buff = buff;
    USBx->host.hch[hch_num].xfer_len = length;

    if(length == 0)
    {   /* For Status OUT stage, Length==0, Status Out PID = 1 */
        USBx->host.hch[hch_num].toggle_out = 1;   
    }

    /* Set the Data Toggle bit as per the Flag */
    if(USBx->host.hch[hch_num].toggle_out == 0)
    {   /* Put the PID 0 */
        USBx->host.hch[hch_num].data_pid = HCH_PID_DATA0;    
    }
    else
    {   /* Put the PID 1 */
        USBx->host.hch[hch_num].data_pid = HCH_PID_DATA1 ;
    }

    HOST_SubmitRequest (USBx , hch_num);   

    return USBH_OK;
}

/**
*\*\name    USBH_CtrlReceiveData.
*\*\fun     Receives the Device Response to the Setup Packet.
*\*\param   USBx: selected device.
*\*\param   buff: data buffer address to store the response
*\*\param   length: Length of the data to be sent
*\*\param   hch_num: Host channel Number
*\*\return  status.
*\*\
**/
USBH_Status USBH_CtrlReceiveData(USB_CORE_MODULE *USBx, uint8_t* buff, uint16_t length, uint8_t hch_num)
{
    USBx->host.hch[hch_num].ep_is_in = 1;
    USBx->host.hch[hch_num].data_pid = HCH_PID_DATA1;
    USBx->host.hch[hch_num].xfer_buff = buff;
    USBx->host.hch[hch_num].xfer_len = length;  

    HOST_SubmitRequest (USBx , hch_num);

    return USBH_OK;
}

/**
*\*\name    USBH_BulkSendData.
*\*\fun     Sends the Bulk Packet to the device.
*\*\param   USBx: selected device.
*\*\param   buff: Buffer pointer from which the Data will be sent to Device
*\*\param   length: Length of the data to be sent
*\*\param   hch_num: Host channel Number
*\*\return  status.
*\*\
**/
USBH_Status USBH_BulkSendData(USB_CORE_MODULE *USBx, uint8_t *buff, uint16_t length, uint8_t hch_num)
{ 
    USBx->host.hch[hch_num].ep_is_in = 0;
    USBx->host.hch[hch_num].xfer_buff = buff;
    USBx->host.hch[hch_num].xfer_len = length;  

    /* Set the Data Toggle bit as per the Flag */
    if(USBx->host.hch[hch_num].toggle_out == 0)
    {   /* Put the PID 0 */
        USBx->host.hch[hch_num].data_pid = HCH_PID_DATA0;    
    }
    else
    {   /* Put the PID 1 */
        USBx->host.hch[hch_num].data_pid = HCH_PID_DATA1 ;
    }

    HOST_SubmitRequest (USBx , hch_num);   
    return USBH_OK;
}

/**
*\*\name    USBH_BulkReceiveData.
*\*\fun     Receives IN bulk packet from device.
*\*\param   USBx: selected device.
*\*\param   buff: Buffer pointer from which the received data packet to be copied.
*\*\param   length: Length of the data to be received.
*\*\param   hch_num: Host channel Number
*\*\return  status.
*\*\
**/
USBH_Status USBH_BulkReceiveData(USB_CORE_MODULE *USBx, uint8_t *buff, uint16_t length, uint8_t hch_num)
{
    USBx->host.hch[hch_num].ep_is_in = 1;   
    USBx->host.hch[hch_num].xfer_buff = buff;
    USBx->host.hch[hch_num].xfer_len = length;

    if( USBx->host.hch[hch_num].toggle_in == 0)
    {
        USBx->host.hch[hch_num].data_pid = HCH_PID_DATA0;
    }
    else
    {
        USBx->host.hch[hch_num].data_pid = HCH_PID_DATA1;
    }

    HOST_SubmitRequest (USBx , hch_num);  
    return USBH_OK;
}

/**
*\*\name    USBH_InterruptReceiveData.
*\*\fun     Receives the Device Response to the Interrupt IN token.
*\*\param   USBx: selected device.
*\*\param   buff: Buffer pointer from which the received data packet to be copied.
*\*\param   length: Length of the data to be received.
*\*\param   hch_num: Host channel Number
*\*\return  status.
*\*\
**/
USBH_Status USBH_InterruptReceiveData(USB_CORE_MODULE *USBx, uint8_t *buff, uint8_t length, uint8_t hch_num)
{
    USBx->host.hch[hch_num].ep_is_in = 1;  
    USBx->host.hch[hch_num].xfer_buff = buff;
    USBx->host.hch[hch_num].xfer_len = length;

    if(USBx->host.hch[hch_num].toggle_in == 0)
    {
        USBx->host.hch[hch_num].data_pid = HCH_PID_DATA0;
    }
    else
    {
        USBx->host.hch[hch_num].data_pid = HCH_PID_DATA1;
    }

    /* toggle DATA PID */
    USBx->host.hch[hch_num].toggle_in ^= 1;  

    HOST_SubmitRequest (USBx , hch_num);  

    return USBH_OK;
}

/**
*\*\name    USBH_InterruptSendData.
*\*\fun     Sends the data on Interrupt OUT Endpoint.
*\*\param   USBx: selected device.
*\*\param   buff: Buffer pointer from where the data needs to be copied.
*\*\param   length: Length of the data to be sent.
*\*\param   hch_num: Host channel Number
*\*\return  status.
*\*\
**/
USBH_Status USBH_InterruptSendData( USB_CORE_MODULE *USBx, uint8_t *buff, uint8_t length, uint8_t hch_num)
{
    USBx->host.hch[hch_num].ep_is_in = 0;  
    USBx->host.hch[hch_num].xfer_buff = buff;
    USBx->host.hch[hch_num].xfer_len = length;

    if(USBx->host.hch[hch_num].toggle_in == 0)
    {
        USBx->host.hch[hch_num].data_pid = HCH_PID_DATA0;
    }
    else
    {
        USBx->host.hch[hch_num].data_pid = HCH_PID_DATA1;
    }

    USBx->host.hch[hch_num].toggle_in ^= 1;  

    HOST_SubmitRequest (USBx , hch_num);  

    return USBH_OK;
}

/**
*\*\name    USBH_SubmitSetupRequest.
*\*\fun     Start a setup transfer by changing the state-machine and initializing  the required variables needed for the Control Transfer.
*\*\param   USBx: selected device.
*\*\param   buff: Buffer used for setup request.
*\*\param   length: Length of the data.
*\*\return  status.
*\*\
**/
static USBH_Status USBH_SubmitSetupRequest(USBH_HOST *phost, uint8_t* buff, uint16_t length)
{
    /* Save Global State */
    phost->gStateBkp =   phost->gState; 

    /* Prepare the Transactions */
    phost->gState = HOST_CTRL_XFER;
    phost->Control.buff = buff; 
    phost->Control.length = length;
    phost->Control.state = CTRL_SETUP;  

    return USBH_OK;  
}

/**
*\*\name    USBH_IsocReceiveData.
*\*\fun     Receives the Device Response to the Isochronous IN token.
*\*\param   USBx: selected device.
*\*\param   buff: Buffer pointer in which the response needs to be copied.
*\*\param   length: Length of the data to be received.
*\*\param   hch_num: Host channel Number
*\*\return  status.
*\*\
**/
USBH_Status USBH_IsocReceiveData( USB_CORE_MODULE *USBx, uint8_t *buff, uint32_t length, uint8_t hch_num)
{
    USBx->host.hch[hch_num].ep_is_in = 1;  
    USBx->host.hch[hch_num].xfer_buff = buff;
    USBx->host.hch[hch_num].xfer_len = length;
    USBx->host.hch[hch_num].data_pid = HCH_PID_DATA0;

    HOST_SubmitRequest (USBx , hch_num);  

    return USBH_OK;
}

/**
*\*\name    USBH_IsocSendData.
*\*\fun     Sends the data on Isochronous OUT Endpoint.
*\*\param   USBx: selected device.
*\*\param   buff: Buffer pointer from where the data needs to be copied.
*\*\param   length: Length of the data to be sent.
*\*\param   hch_num: Host channel Number
*\*\return  status.
*\*\
**/
USBH_Status USBH_IsocSendData( USB_CORE_MODULE *USBx, uint8_t *buff, uint32_t length, uint8_t hch_num)
{
    USBx->host.hch[hch_num].ep_is_in = 0;  
    USBx->host.hch[hch_num].xfer_buff = buff;
    USBx->host.hch[hch_num].xfer_len = length;
    USBx->host.hch[hch_num].data_pid = HCH_PID_DATA0;

    HOST_SubmitRequest (USBx , hch_num);  

    return USBH_OK;
}
