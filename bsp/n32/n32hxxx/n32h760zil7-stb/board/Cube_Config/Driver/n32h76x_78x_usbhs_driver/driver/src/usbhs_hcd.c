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
 * @file usbhs_hcd.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbhs_core.h"
#include "usbhs_hcd.h"
#include "usbhs_conf.h"
#include "usbhs_bsp.h"

/**
*\*\name    USBHOST_CoreInit.
*\*\fun     Initialize the HOST portion of the driver.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USBHOST_CoreInit(USB_CORE_MODULE *USBx, USB_CORE_ID_TypeDef coreID)
{
    uint8_t i = 0;
    USBx->host.ConnSts = 0;

    for (i= 0; i< USB_MAX_TX_FIFOS; i++)
    {
        USBx->host.ErrCnt[i] = 0;
        USBx->host.XferCnt[i] = 0;
        USBx->host.HCH_Status[i] = HCH_IDLE;
    }
    USBx->host.hch[0].max_packet = 8;

    USB_BasicInit(USBx, coreID);

    USB_EnableGlobalInt(USBx, DISABLE);
    USB_CoreInit(USBx);

    /* Force Host Mode*/
    USB_SetCurrentMode(USBx, HOST_MODE);
    /* Init Host */
    USB_CoreInitHost(USBx);
    /* Enable USB Global interrupt */
    USB_EnableGlobalInt(USBx, ENABLE);
}

/**
*\*\name    HOST_GetCurrentSpeed.
*\*\fun     Get Current device Speed.
*\*\param   USBx: selected device.
*\*\return  speed.
*\*\
**/
uint32_t HOST_GetCurrentSpeed(USB_CORE_MODULE *USBx)
{
    uint32_t hpcs = 0;
    hpcs = USB_READ_REG32(USBx->regs.HPCS);
    return (hpcs & USBHS_HPCS_PSPD) >> USBHS_HPCS_PSPD_POS;
}

/**
*\*\name    HOST_ResetPort.
*\*\fun     Issues the reset command to device.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
uint32_t HOST_ResetPort(USB_CORE_MODULE *USBx)
{
    USB_ResetPort(USBx);
    return 0;    
}

/**
*\*\name    HOST_IsDeviceConnected.
*\*\fun     Check if the device is connected.
*\*\param   USBx: selected device.
*\*\return  Device connection status. 1 -> connected and 0 -> disconnected.
*\*\
**/
uint32_t HOST_IsDeviceConnected(USB_CORE_MODULE *USBx)
{
    return (USBx->host.ConnSts);
}

/**
*\*\name    HOST_IsPortEnabled.
*\*\fun     This function checks if port is enabled.
*\*\param   USBx: selected device.
*\*\return  port enable or disable.
*\*\
**/
uint32_t HOST_IsPortEnabled(USB_CORE_MODULE *USBx)
{
    return (USBx->host.PortEnabled);
}

/**
*\*\name    HOST_GetCurrentFrame.
*\*\fun     This function returns the frame number for sof packet.
*\*\param   USBx: selected device.
*\*\return  Frame number.
*\*\
**/
uint32_t HOST_GetCurrentFrame(USB_CORE_MODULE *USBx) 
{
    return (USB_READ_REG32(&USBx->regs.HCSR->HFNUM) & 0xFFFF) ;
}

/**
*\*\name    HOST_GetCurrentFrame.
*\*\fun     This function returns the last URBstate.
*\*\param   USBx: selected device.
*\*\param   ch_num: channel number.
*\*\return  URB_STATE.
*\*\
**/
URB_STATE HOST_GetURB_State(USB_CORE_MODULE *USBx, uint8_t ch_num) 
{
    return USBx->host.URB_State[ch_num] ;
}

/**
*\*\name    HOST_GetXferCnt.
*\*\fun     This function returns the last URBstate.
*\*\param   USBx: selected device.
*\*\param   ch_num: channel number.
*\*\return  Number of data bytes transferred.
*\*\
**/
uint32_t HOST_GetXferCnt(USB_CORE_MODULE *USBx, uint8_t ch_num) 
{
    return USBx->host.XferCnt[ch_num] ;
}

/**
*\*\name    HOST_GetHCState.
*\*\fun     This function returns the HC Status.
*\*\param   USBx: selected device.
*\*\param   ch_num: channel number.
*\*\return  HCH_STATUS.
*\*\
**/
HCH_STATUS HOST_GetHCState(USB_CORE_MODULE *USBx,  uint8_t ch_num) 
{
    return USBx->host.HCH_Status[ch_num] ;
}

/**
*\*\name    HOST_HC_Init.
*\*\fun     This function prepare a HC and start a transfer.
*\*\param   USBx: selected device.
*\*\param   ch_num: channel number.
*\*\return  status.
*\*\
**/
uint32_t HOST_HC_Init(USB_CORE_MODULE *USBx, uint8_t ch_num) 
{
    return USB_HCH_Init(USBx, ch_num);  
}

/**
*\*\name    HOST_SubmitRequest.
*\*\fun     This function prepare a HC and start a transfer.
*\*\param   USBx: selected device.
*\*\param   ch_num: channel number.
*\*\return  status.
*\*\
**/
uint32_t HOST_SubmitRequest(USB_CORE_MODULE *USBx, uint8_t ch_num) 
{
    USBx->host.URB_State[ch_num] = URB_IDLE;  
    USBx->host.hch[ch_num].xfer_count = 0 ;
    return USB_HCH_StartXfer(USBx, ch_num);
}
