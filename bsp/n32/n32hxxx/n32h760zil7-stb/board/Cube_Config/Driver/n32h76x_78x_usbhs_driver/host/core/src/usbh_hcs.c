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
 * @file usbh_hcs.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbh_hcs.h"
#include "usbhs_core.h"

static uint16_t USBH_GetFreeChannel(USB_CORE_MODULE *USBx);

/**
*\*\name    USBH_Open_Channel.
*\*\fun     Open a  pipe.
*\*\param   USBx: selected device.
*\*\param   hch_num: Host channel Number
*\*\param   dev_address: USB Device address allocated to attached device
*\*\param   speed : USB device speed (Full/Low)
*\*\param   ep_type: end point type (Bulk/int/ctl)
*\*\param   mps: max pkt size
*\*\return  HC_OK.
*\*\
**/
uint8_t USBH_Open_Channel(USB_CORE_MODULE *USBx, uint8_t hch_num, uint8_t dev_address, uint8_t speed, uint8_t ep_type, uint16_t mps)
{
    USBx->host.hch[hch_num].ep_num = USBx->host.channel[hch_num]& 0x7F;
    USBx->host.hch[hch_num].ep_is_in = (USBx->host.channel[hch_num] & 0x80) == 0x80;  
    USBx->host.hch[hch_num].dev_addr = dev_address;  
    USBx->host.hch[hch_num].ep_type = ep_type;  
    USBx->host.hch[hch_num].max_packet = mps; 
    USBx->host.hch[hch_num].speed = speed; 
    USBx->host.hch[hch_num].toggle_in = 0; 
    USBx->host.hch[hch_num].toggle_out = 0;
    if(speed == HPCS_PRTSPD_HIGH_SPEED)
    {
        USBx->host.hch[hch_num].do_ping = 1;
    }
  
    USB_HCH_Init(USBx, hch_num) ;

    return HC_OK; 
}

/**
*\*\name    USBH_Modify_Channel.
*\*\fun     Modify a pipe.
*\*\param   USBx: selected device.
*\*\param   hch_num: Host channel Number
*\*\param   dev_address: USB Device address allocated to attached device
*\*\param   speed : USB device speed (Full/Low)
*\*\param   ep_type: end point type (Bulk/int/ctl)
*\*\param   mps: max pkt size
*\*\return  HC_OK.
*\*\
**/
uint8_t USBH_Modify_Channel(USB_CORE_MODULE *USBx, uint8_t hch_num, uint8_t dev_address, uint8_t speed, uint8_t ep_type, uint16_t mps)
{
    if(dev_address != 0)
    {
        USBx->host.hch[hch_num].dev_addr = dev_address;  
    }

    if((USBx->host.hch[hch_num].max_packet != mps) && (mps != 0))
    {
        USBx->host.hch[hch_num].max_packet = mps; 
    }

    if((USBx->host.hch[hch_num].speed != speed ) && (speed != 0 )) 
    {
        USBx->host.hch[hch_num].speed = speed; 
    }

    USB_HCH_Init(USBx, hch_num);
    return HC_OK; 

}

/**
*\*\name    USBH_Alloc_Channel.
*\*\fun     Allocate a new channel for the pipe.
*\*\param   USBx: selected device.
*\*\param   ep_addr: End point for which the channel to be allocated
*\*\return  hch_num: Host channel number.
*\*\
**/
uint8_t USBH_Alloc_Channel(USB_CORE_MODULE *USBx, uint8_t ep_addr)
{
    uint16_t hch_num;

    hch_num =  USBH_GetFreeChannel(USBx);

    if (hch_num != HC_ERROR)
    {
        USBx->host.channel[hch_num & (USB_MAX_TX_FIFOS - 1U)] = HC_USED | ep_addr;
    }
    return hch_num;
}

/**
*\*\name    USBH_Free_Channel.
*\*\fun     Free the USB host channel.
*\*\param   USBx: selected device.
*\*\param   idx: Channel number to be freed.
*\*\return  USBH_OK.
*\*\
**/
uint8_t USBH_Free_Channel(USB_CORE_MODULE *USBx, uint8_t idx)
{
    if(idx < HC_MAX)
    {
        USBx->host.channel[idx & (USB_MAX_TX_FIFOS - 1U)] = 0;
    }
    return USBH_OK;
}

/**
*\*\name    USBH_DeAllocate_AllChannel.
*\*\fun     Free all USB host channel.
*\*\param   USBx: selected device.
*\*\return  USBH_OK.
*\*\
**/
uint8_t USBH_DeAllocate_AllChannel(USB_CORE_MODULE *USBx)
{
    uint8_t idx;

    for (idx = 2; idx < HC_MAX ; idx ++)
    {
        USBx->host.channel[idx] = 0;
    }
    return USBH_OK;
}

/**
*\*\name    USBH_GetFreeChannel.
*\*\fun     Get a free channel number for allocation to a device endpoint.
*\*\param   USBx: selected device.
*\*\return  idx: Free Channel number.
*\*\
**/
static uint16_t USBH_GetFreeChannel(USB_CORE_MODULE *USBx)
{
    uint8_t idx = 0;

    for (idx = 0 ; idx < HC_MAX ; idx++)
    {
        if ((USBx->host.channel[idx] & HC_USED) == 0)
        {
            return idx;
        } 
    }
    return HC_ERROR;
}
