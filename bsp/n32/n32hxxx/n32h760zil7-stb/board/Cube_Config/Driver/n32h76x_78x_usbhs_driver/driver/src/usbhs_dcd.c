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
 * @file usbhs_dcd.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbhs_dcd.h"
#include "usbhs_bsp.h"


/**
*\*\name    USBDEV_CoreInit.
*\*\fun     Initialize the device core.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USBDEV_CoreInit(USB_CORE_MODULE *USBx, USB_CORE_ID_TypeDef coreID)
{
    uint32_t i;
    USB_EP *ep;

    USB_BasicInit(USBx, coreID);

    USBx->dev.device_status = USB_DEFAULT;
    USBx->dev.device_address = 0;

    /* Init ep structure */
    for(i=0; i<USBx->cfg.dev_endpoints_num; i++)
    {
        ep = &USBx->dev.in_ep[i];
        /* Init ep structure */
        ep->is_in = 1;
        ep->num = i;
        ep->tx_fifo_num = i;
        /* Control until ep is activated */
        ep->type = EP_TYPE_CTRL;
        ep->maxpacket =  USB_MAX_EP0_SIZE;
        ep->xfer_buff = 0;
        ep->xfer_len = 0;
    }
    for(i = 0; i<USBx->cfg.dev_endpoints_num; i++)
    {
        ep = &USBx->dev.out_ep[i];
        /* Init ep structure */
        ep->is_in = 0;
        ep->num = i;
        ep->tx_fifo_num = i;
        /* Control until ep is activated */
        ep->type = EP_TYPE_CTRL;
        ep->maxpacket = USB_MAX_EP0_SIZE;
        ep->xfer_buff = 0;
        ep->xfer_len = 0;
    }

    USB_EnableGlobalInt(USBx, DISABLE);

    /*Init the Core (common init.) */
    USB_CoreInit(USBx);

    /* Force Device Mode*/
    USB_SetCurrentMode(USBx, DEVICE_MODE);

    /* Init Device */
    USB_CoreInitDev(USBx);

    /* Enable USB Global interrupt */
    USB_EnableGlobalInt(USBx, ENABLE);
}

/**
*\*\name    USBDEV_EP_Open.
*\*\fun     Configure an EP.
*\*\param   USBx: selected device.
*\*\param   ep_addr : Endpoint address.
*\*\param   ep_mps: Endpoint max packet size.
*\*\param   ep_type: Endpoint type.
*\*\return  status.
*\*\
**/
uint32_t USBDEV_EP_Open(USB_CORE_MODULE *USBx , uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type)
{
    USB_EP *ep;
    __IO uint8_t tmp_1, tmp_2;
    
    tmp_1 = ep_addr>>7;       //EP type, it is IN(=1) or OUT(=0)
    tmp_2 = ep_addr & 0x7f;   //EP number

    if(tmp_1 == 1)
    {
        ep = &USBx->dev.in_ep[tmp_2];
    }
    else
    {
        ep = &USBx->dev.out_ep[tmp_2];
    }
    ep->num = tmp_2;

    ep->is_in = tmp_1;
    ep->maxpacket = ep_mps;
    ep->type = ep_type;
    if(ep->is_in)
    {
        /* Assign a Tx FIFO */
        ep->tx_fifo_num = tmp_2;
    }
    /* Set initial data PID. */
    if(ep_type == USB_EP_BULK )
    {
        ep->data_pid_start = 0;
    }
    USB_EPActivate(USBx , ep);
    return 0;
}

/**
*\*\name    USBDEV_EP_Close.
*\*\fun     Called when an EP is disabled.
*\*\param   USBx: selected device.
*\*\param   ep_addr : Endpoint address.
*\*\return  status.
*\*\
**/
uint32_t USBDEV_EP_Close(USB_CORE_MODULE *USBx , uint8_t  ep_addr)
{
    USB_EP *ep;

    if((ep_addr&0x80) == 0x80)
    {
        ep = &USBx->dev.in_ep[ep_addr & 0x7F];
    }
    else
    {
        ep = &USBx->dev.out_ep[ep_addr & 0x7F];
    }
    ep->num   = ep_addr & 0x7F;
    ep->is_in = (0x80 & ep_addr) != 0;
    USB_EPDeactivate(USBx , ep);
    return 0;
}

/**
*\*\name    USBDEV_EP_PrepareRx.
*\*\fun     Enable endpoint receive.
*\*\param   USBx: selected device.
*\*\param   ep_addr : Endpoint address.
*\*\param   pbuf: pointer to Rx buffer
*\*\param   buf_len: data length
*\*\return  status.
*\*\
**/
uint32_t USBDEV_EP_PrepareRx( USB_CORE_MODULE *USBx, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len)
{
    USB_EP *ep;
    __IO uint8_t tmp_1;
    
    tmp_1 = ep_addr & 0x7f;   //EP number   

    ep = &USBx->dev.out_ep[tmp_1];

    /*setup and start the Xfer */
    ep->xfer_buff = pbuf;  
    ep->xfer_len = buf_len;
    ep->xfer_count = 0;
    ep->is_in = 0;
    ep->num = tmp_1;

    if(USBx->cfg.dma_enable == 1)
    {
        ep->dma_addr = (uint32_t)pbuf;
    }
    if(tmp_1 == 0)
    {
        USB_EP0StartXfer(USBx , ep);
    }
    else
    {
        USB_EPStartXfer(USBx, ep);
    }
    return 0;
}

/**
*\*\name    USBDEV_EP_Tx.
*\*\fun     Transmit data over USB.
*\*\param   USBx: selected device.
*\*\param   ep_addr : Endpoint address.
*\*\param   pbuf: pointer to Tx buffer
*\*\param   buf_len: data length
*\*\return  status.
*\*\
**/
uint32_t USBDEV_EP_Tx (USB_CORE_MODULE *USBx, uint8_t ep_addr, uint8_t *pbuf, uint32_t buf_len)
{
    USB_EP *ep;

    ep = &USBx->dev.in_ep[ep_addr & 0x7F];

    /* Setup and start the Transfer */
    ep->is_in = 1;
    ep->num = ep_addr & 0x7F;
    ep->xfer_buff = pbuf;
    ep->xfer_count = 0;
    ep->xfer_len  = buf_len;

    if(USBx->cfg.dma_enable == 1)
    {
        ep->dma_addr = (uint32_t)pbuf;
    }
    if(ep->num == 0)
    {
        USB_EP0StartXfer(USBx, ep);
    }
    else
    {
        USB_EPStartXfer(USBx, ep);
    }
    return 0;
}

/**
*\*\name    USBDEV_EP_Stall.
*\*\fun     Stall an endpoint.
*\*\param   USBx: selected device.
*\*\param   epnum: endpoint number
*\*\return  status.
*\*\
**/
uint32_t USBDEV_EP_Stall (USB_CORE_MODULE *USBx, uint8_t epnum)
{
    USB_EP *ep;
    if((0x80 & epnum) == 0x80)
    {
        ep = &USBx->dev.in_ep[epnum & 0x7F];
    }
    else
    {
        ep = &USBx->dev.out_ep[epnum];
    }

    ep->is_stall = 1;
    ep->num   = epnum & 0x7F;
    ep->is_in = ((epnum & 0x80) == 0x80);

    USB_EPSetStall(USBx , ep);
    return (0);
}

/**
*\*\name    USBDEV_EP_ClrStall.
*\*\fun     Clear stall condition on endpoints.
*\*\param   USBx: selected device.
*\*\param   epnum: endpoint number
*\*\return  status.
*\*\
**/
uint32_t USBDEV_EP_ClrStall(USB_CORE_MODULE *USBx, uint8_t epnum)
{
    USB_EP *ep;
    if((0x80 & epnum) == 0x80)
    {
        ep = &USBx->dev.in_ep[epnum & 0x7F];    
    }
    else
    {
        ep = &USBx->dev.out_ep[epnum];
    }

    ep->is_stall = 0;  
    ep->num   = epnum & 0x7F;
    ep->is_in = ((epnum & 0x80) == 0x80);

    USB_EPClearStall(USBx , ep);
    return (0);
}

/**
*\*\name    USBDEV_EP_Flush.
*\*\fun     This Function flushes the FIFOs.
*\*\param   USBx: selected device.
*\*\param   epnum: endpoint number
*\*\return  status.
*\*\
**/
uint32_t USBDEV_EP_Flush(USB_CORE_MODULE *USBx , uint8_t epnum)
{
    if((epnum & 0x80) == 0x80)
    {
        USB_FlushTxFifo(USBx, epnum & 0x7F);
    }
    else
    {
        USB_FlushRxFifo(USBx);
    }
    return (0);
}

/**
*\*\name    USBDEV_EP_SetAddress.
*\*\fun     This Function set USB device address.
*\*\param   USBx: selected device.
*\*\param   address: new device address
*\*\return  status.
*\*\
**/
void USBDEV_EP_SetAddress(USB_CORE_MODULE *USBx, uint8_t address)
{
    uint32_t dcfg = 0;
    dcfg |= (address << USBHS_DCFG_DEVARR_POS);
    USB_MODIFY_REG32(&USBx->regs.DCSR->DCFG, USBHS_DCFG_DEVARR, dcfg);
}

/**
*\*\name    USBDEV_DevConnect.
*\*\fun     Connect device (enable internal pull-up)
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USBDEV_DevConnect(USB_CORE_MODULE *USBx)
{
    USB_CLR_REG32_BIT(&USBx->regs.DCSR->DCTRL, USBHS_DCTRL_SFTDIS);
}

/**
*\*\name    USBDEV_DevDisconnect.
*\*\fun     Disconnect device (disable internal pull-up)
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USBDEV_DevDisconnect(USB_CORE_MODULE *USBx)
{
    /* Disconnect device for 3ms */
    USB_MODIFY_REG32(&USBx->regs.DCSR->DCTRL, 0, USBHS_DCTRL_SFTDIS);
    USB_BSP_mDelay(3);
}

/**
*\*\name    USBDEV_GetEPStatus.
*\*\fun     returns the EP Status.
*\*\param   USBx: selected device.
*\*\param   epnum : endpoint number
*\*\return  EP status.
*\*\
**/
uint32_t USBDEV_GetEPStatus(USB_CORE_MODULE *USBx ,uint8_t epnum)
{
    USB_EP *ep;
    uint32_t Status = 0;  

    if((0x80 & epnum) == 0x80)
    {
        ep = &USBx->dev.in_ep[epnum & 0x7F];    
    }
    else
    {
        ep = &USBx->dev.out_ep[epnum];
    }
    Status = USB_GetEPStatus(USBx ,ep);
    /* Return the current status */
    return Status;
}

/**
*\*\name    USBDEV_SetEPStatus.
*\*\fun     Set the EP Status.
*\*\param   USBx: selected device.
*\*\param   epnum : endpoint number.
*\*\param   Status : new Status.
*\*\return  none.
*\*\
**/
void USBDEV_SetEPStatus(USB_CORE_MODULE *USBx , uint8_t epnum , uint32_t Status)
{
    USB_EP *ep;

    if((0x80 & epnum) == 0x80)
    {
        ep = &USBx->dev.in_ep[epnum & 0x7F];
    }
    else
    {
        ep = &USBx->dev.out_ep[epnum];
    }
    USB_SetEPStatus(USBx , ep , Status);
}
