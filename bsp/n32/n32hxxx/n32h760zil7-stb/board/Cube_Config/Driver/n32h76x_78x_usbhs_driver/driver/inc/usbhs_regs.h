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
 * @file usbhs_regs.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __USBHS_REGS_H__
#define __USBHS_REGS_H__

#include "n32h76x_78x.h"
#include "usbhs_conf.h"


#define USBHS1_BASE_ADDR                  (0x40100000)
#define USBHS1_WARP_BASE_ADDR             (0x40140000)
#define USBHS2_BASE_ADDR                  (0x40060000)
#define USBHS2_WARP_BASE_ADDR             (0x400A0000)

#define USB_GLOBAL_REGS_OFFSET            (0x000)
#define USB_DEV_GLOBAL_REG_OFFSET         (0x800)
#define USB_DEV_IN_EP_REG_OFFSET          (0x900)
#define USB_EP_REG_OFFSET                 (0x20)
#define USB_DEV_OUT_EP_REG_OFFSET         (0xB00)
#define USB_HOST_GLOBAL_REG_OFFSET        (0x400)
#define USB_HOST_PORT_REGS_OFFSET         (0x440)
#define USB_HOST_CHANNEL_REGS_OFFSET      (0x500)
#define USB_CHANNEL_REGS_OFFSET           (0x20)
#define USB_PWRCTRL_OFFSET                (0xE00)
#define USB_PWRCTRL1_OFFSET               (0xE04)
#define USB_DATA_FIFO_OFFSET              (0x1000)
#define USB_DATA_FIFO_SIZE                (0x1000)

#define USB_MAX_TX_FIFOS                  (16U)
#define USB_MAX_CH_NUM                    (USB_MAX_TX_FIFOS)
#define USB_MAX_EP_NUM                    (16U)
#define USB_MAX_EP0_SIZE                  (64U)

#define USB_HS_MAX_PACKET_SIZE            (1024U)
#define USB_FS_MAX_PACKET_SIZE            (64U)
#define USB_MAX_CHANNEL_NUM               (16U)           /* USBHS host channel count */
#define USB_MAX_FIFO_WORDLEN              (1280U)         /* USBHS max fifo size in words */


typedef struct 
{
    USB_Global_Registers   *GCSR;
    USB_Device_Registers   *DCSR;
    USB_Host_Registers     *HCSR;
    USB_INEP_Registers     *INEPCSR[USB_MAX_EP_NUM];
    USB_OUTEP_Registers    *OUTEPCSR[USB_MAX_EP_NUM];
    USB_HostCH_Registers   *HCHCSR[USB_MAX_CH_NUM];
    __IO uint32_t          *HPCS;
    __IO uint32_t          *DFIFO[USB_MAX_TX_FIFOS];
    __IO uint32_t          *PWRCTRL;
    __IO uint32_t          *PWRCTRL1;
    
    USB_Wrapper_Registers  *WRAPCSR;
}USB_Register;

#endif /* __USBHS_REGS_H__ */
