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
 * @file usbhs_hcd_int.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbhs_core.h"
#include "usbhs_defines.h"
#include "usbhs_hcd_int.h"

#if defined   (__CC_ARM) /*!< ARM Compiler */
#pragma O0
#elif defined (__GNUC__) /*!< GNU Compiler */
#pragma GCC optimize ("O0")                        

#endif /* __CC_ARM */


static uint32_t USBHOST_handle_sof_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBHOST_handle_port_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBHOST_handle_hch_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBHOST_handle_hch_n_In_ISTR(USB_CORE_MODULE *USBx, uint32_t num);
static uint32_t USBHOST_handle_hch_n_Out_ISTR(USB_CORE_MODULE *USBx, uint32_t num);
static uint32_t USBHOST_handle_rx_qlvl_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBHOST_handle_nptxfempty_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBHOST_handle_ptxfempty_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBHOST_handle_Disconnect_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBHOST_handle_IncompletePeriodicXfer_ISTR(USB_CORE_MODULE *USBx);

/**
*\*\name    USBHOST_handle_Wakeup_ISTR.
*\*\fun     process the resume/remote wakeup detected interrupt.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
static void USBHOST_handle_Wakeup_ISTR(USB_CORE_MODULE *USBx)
{
    uint32_t hpcs;
    
    hpcs = USB_ReadHPCS(USBx);
    hpcs &= ~USBHS_HPCS_PRES;
    USB_WRITE_REG32(USBx->regs.HPCS, hpcs);
}

/**
*\*\name    USBHOST_ISTR_WKUP_handler.
*\*\fun     process the resume/remote wakeup detected interrupt.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USBHOST_ISTR_WKUP_handler(USB_CORE_MODULE *pdev)
{
    uint32_t gintsts;
    if (0U != USB_GetMode(pdev)) 
    {
        gintsts = USB_ReadCoreItr(pdev);
        if (gintsts == 0UL) 
        {
            return;
        }
        if (0UL != (gintsts & USBHS_GINTSTS_WKUPIF)) 
        {
            USBHOST_handle_Wakeup_ISTR(pdev);
        }
    }
}

/**
*\*\name    USBHOST_ISTR_Handler.
*\*\fun     This function handles all USB Host Interrupts.
*\*\param   USBx: selected device.
*\*\return  retval.
*\*\
**/
uint32_t USBHOST_ISTR_Handler(USB_CORE_MODULE *USBx)
{
    uint32_t retval = 0;
    uint32_t gintsts = 0;

    /* Check if HOST Mode */
    if(USB_IsHostMode(USBx))
    {
        gintsts = USB_ReadCoreItr(USBx);
        if(!gintsts)
        {
            return 0;
        }
        if(gintsts & USBHS_GINTSTS_SOFIF)
        {
            retval |= USBHOST_handle_sof_ISTR(USBx);
        }

        if(gintsts & USBHS_GINTSTS_RXFNEIF)
        {
            retval |= USBHOST_handle_rx_qlvl_ISTR(USBx);
        }

        if(gintsts & USBHS_GINTSTS_NPTXFEIF)
        {
            retval |= USBHOST_handle_nptxfempty_ISTR(USBx);
        }

        if(gintsts & USBHS_GINTSTS_PTXFEIF)
        {
            retval |= USBHOST_handle_ptxfempty_ISTR(USBx);
        }    

        if(gintsts & USBHS_GINTSTS_HCHIF)
        {
            retval |= USBHOST_handle_hch_ISTR(USBx);
        }

        if(gintsts & USBHS_GINTSTS_HPIF)
        {
            retval |= USBHOST_handle_port_ISTR(USBx);
        }
        if(gintsts & USBHS_GINTSTS_DISCIF)
        {
            retval |= USBHOST_handle_Disconnect_ISTR(USBx);  
        }
        if(gintsts & USBHS_GINTSTS_PTNCIF_ISOUTNCIF)
        {
            retval |= USBHOST_handle_IncompletePeriodicXfer_ISTR(USBx);
        }
    }
    return retval;
}


/**
*\*\name    USBHOST_handle_hch_ISTR.
*\*\fun     This function indicates that one or more host channels has a pending.
*\*\param   USBx: selected device.
*\*\return  retval.
*\*\
**/
static uint32_t USBHOST_handle_hch_ISTR(USB_CORE_MODULE *USBx)
{
    uint32_t i = 0;
    uint32_t retval = 0;
    uint32_t hachint = 0;
    uint32_t hchctrl = 0;

    /* Clear appropriate bits in HCHINTSTSn to clear the interrupt bit in GINTSTS */
    hachint = USB_ReadHostAllChannels_intr(USBx);

    for(i=0; i<USBx->cfg.host_channels_num; i++)
    {
        if(((hachint & USBHS_HACHINT) >> USBHS_HACHINT_POS) & (1 << i))
        {
            hchctrl = USB_READ_REG32(&USBx->regs.HCHCSR[i]->HCHCTRL);
            if(hchctrl & USBHS_HCHCTRL_EPDIR)
            {
                retval |= USBHOST_handle_hch_n_In_ISTR(USBx, i);
            }
            else
            {
                retval |=  USBHOST_handle_hch_n_Out_ISTR(USBx, i);
            }
        }
    }
    return retval;
}


/**
*\*\name    USBHOST_handle_sof_ISTR.
*\*\fun     Handles the start-of-frame interrupt in host mode.
*\*\param   USBx: selected device.
*\*\return  1.
*\*\
**/
static uint32_t USBHOST_handle_sof_ISTR(USB_CORE_MODULE *USBx)
{
    uint32_t gintsts = 0;

    USBHOST_INT_fops->SOF(USBx);

    /* Clear interrupt */
    gintsts |= USBHS_GINTSTS_SOFIF;
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, gintsts);

    return 1;
}


/**
*\*\name    USBHOST_handle_Disconnect_ISTR.
*\*\fun     Handles disconnect event.
*\*\param   USBx: selected device.
*\*\return  1.
*\*\
**/
static uint32_t USBHOST_handle_Disconnect_ISTR(USB_CORE_MODULE *USBx)
{
    USBHOST_INT_fops->DevDisconnected(USBx);
    /* Clear interrupt */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, USBHS_GINTSTS_DISCIF);
    return 1;
}
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */

/**
*\*\name    USBHOST_handle_nptxfempty_ISTR.
*\*\fun     Handles non periodic tx fifo empty.
*\*\param   USBx: selected device.
*\*\return  1.
*\*\
**/
static uint32_t USBHOST_handle_nptxfempty_ISTR(USB_CORE_MODULE *USBx)
{
    uint16_t len_words = 0, len = 0; 
    uint32_t ginten = 0;
    uint32_t gnptxfsts = 0;
    uint8_t chnum = 0;

    gnptxfsts = USB_READ_REG32(&USBx->regs.GCSR->GNPTXFSTS);

    chnum = (gnptxfsts & USBHS_GNPTXFSTS_NPTXRQTOP_CHNUM) >> USBHS_GNPTXFSTS_NPTXRQTOP_CHNUM_POS;
    len_words = (USBx->host.hch[chnum].xfer_len + 3) / 4;

    while(((gnptxfsts & USBHS_GNPTXFSTS_NPTXFSAV) > len_words) && (USBx->host.hch[chnum].xfer_len != 0))
    {
        len = (gnptxfsts & USBHS_GNPTXFSTS_NPTXFSAV) * 4;

        if(len > USBx->host.hch[chnum].xfer_len)
        {
            /* Last packet */
            len = USBx->host.hch[chnum].xfer_len;

            ginten |= USBHS_GINTEN_NPTXFEIEN;
            USB_MODIFY_REG32(&USBx->regs.GCSR->GINTEN, ginten, 0);       
        }

        len_words = (USBx->host.hch[chnum].xfer_len + 3) / 4;

        USB_WritePacket(USBx , USBx->host.hch[chnum].xfer_buff, chnum, len);

        USBx->host.hch[chnum].xfer_buff  += len;
        USBx->host.hch[chnum].xfer_len   -= len;
        USBx->host.hch[chnum].xfer_count  += len; 

        gnptxfsts = USB_READ_REG32(&USBx->regs.GCSR->GNPTXFSTS);
    }
    return 1;
}
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */

/**
*\*\name    USBHOST_handle_ptxfempty_ISTR.
*\*\fun     Handles periodic tx fifo empty.
*\*\param   USBx: selected device.
*\*\return  1.
*\*\
**/
static uint32_t USBHOST_handle_ptxfempty_ISTR(USB_CORE_MODULE *USBx)
{
    uint16_t len_words = 0, len = 0; 
    uint32_t ginten = 0;
    uint32_t hptxfqsts = 0;
    uint8_t chnum = 0;

    hptxfqsts = USB_READ_REG32(&USBx->regs.HCSR->HPTXFQSTS);
    chnum = (hptxfqsts & USBHS_HPTXFQSTS_PTXRQTOP_CHNUM) >> USBHS_HPTXFQSTS_PTXRQTOP_CHNUM_POS;
    len_words = (USBx->host.hch[chnum].xfer_len + 3) / 4;

    while (((hptxfqsts & USBHS_HPTXFQSTS_PTXFSAVL) > len_words)&& (USBx->host.hch[chnum].xfer_len != 0))    
    {
        len = (hptxfqsts & USBHS_HPTXFQSTS_PTXFSAVL) * 4;
        if(len > USBx->host.hch[chnum].xfer_len)
        {
            len = USBx->host.hch[chnum].xfer_len;
            /* Last packet */
            ginten |= USBHS_GINTEN_PTXFEIEN;
            USB_MODIFY_REG32(&USBx->regs.GCSR->GINTEN, ginten, 0); 
        }

        len_words = (USBx->host.hch[chnum].xfer_len + 3) / 4;

        USB_WritePacket(USBx , USBx->host.hch[chnum].xfer_buff, chnum, len);

        USBx->host.hch[chnum].xfer_buff  += len;
        USBx->host.hch[chnum].xfer_len   -= len;
        USBx->host.hch[chnum].xfer_count  += len; 

        hptxfqsts = USB_READ_REG32(&USBx->regs.HCSR->HPTXFQSTS);
    }
    return 1;
}

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */

/**
*\*\name    USBHOST_handle_port_ISTR.
*\*\fun     This function determines which interrupt conditions have occurred.
*\*\param   USBx: selected device.
*\*\return  retval.
*\*\
**/
static uint32_t USBHOST_handle_port_ISTR(USB_CORE_MODULE *USBx)
{
    uint32_t retval = 0;
    uint32_t ginten = 0;
    uint32_t hpcs = 0, hpcs_dup = 0;
    uint8_t portspeed = 0;

    hpcs = USB_READ_REG32(USBx->regs.HPCS);
    hpcs_dup = USB_READ_REG32(USBx->regs.HPCS);

    /* Clear the interrupt bits in GINTSTS */
    hpcs_dup &= ~(USBHS_HPCS_PEN | USBHS_HPCS_PCDET | USBHS_HPCS_PENC | USBHS_HPCS_POCC);

    /* Port Connect Detected */
    if(hpcs & USBHS_HPCS_PCDET)
    {
        hpcs_dup |= USBHS_HPCS_PCDET;
        USBHOST_INT_fops->DevConnected(USBx);
        retval |= 1;   
    }

    /* Port Enable Changed */
    if(hpcs & USBHS_HPCS_PENC)
    {
        hpcs_dup |= USBHS_HPCS_PENC;
        if(hpcs & USBHS_HPCS_PEN)
        {
            portspeed = (hpcs & USBHS_HPCS_PSPD) >> USBHS_HPCS_PSPD_POS;
            if((portspeed == HPCS_PRTSPD_LOW_SPEED) || (portspeed == HPCS_PRTSPD_FULL_SPEED))
            {
                USB_WRITE_REG32(&USBx->regs.HCSR->HFRI, 60000);
            }
            USBHOST_INT_fops->DevPortEnabled(USBx);  

            /* Enable disconnect interrupt */
            ginten |= USBHS_GINTEN_DISCIEN;
            USB_MODIFY_REG32(&USBx->regs.GCSR->GINTEN, ginten, ginten);
        }
        else
        {
            USBHOST_INT_fops->DevPortDisabled(USBx);
        }
    }

    /* Overcurrent Change Interrupt */
    if((hpcs & USBHS_HPCS_POCC) >> USBHS_HPCS_POCC_POS)
    {
        hpcs_dup |= USBHS_HPCS_POCC;
        retval |= 1;
    }
    /* Clear Port Interrupts */
    USB_WRITE_REG32(USBx->regs.HPCS, hpcs_dup);
    return retval;
}
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */

/**
*\*\name    USBHOST_handle_hch_n_Out_ISTR.
*\*\fun     Handles interrupt for a specific Host Channel.
*\*\param   USBx: selected device.
*\*\param   num: Channel number.
*\*\return  1.
*\*\
**/
uint32_t USBHOST_handle_hch_n_Out_ISTR(USB_CORE_MODULE *USBx , uint32_t num)
{
    USB_HostCH_Registers *hostchreg;

    uint32_t hchintsts = 0;
    uint32_t hchinten = 0;
    uint32_t hchctrl = 0;

    hostchreg = USBx->regs.HCHCSR[num];
    hchintsts = USB_READ_REG32(&hostchreg->HCHINTSTS);
    hchinten = USB_READ_REG32(&hostchreg->HCHINTEN);
    hchintsts &= hchinten;

    hchctrl = USB_READ_REG32(&USBx->regs.HCHCSR[num]->HCHCTRL);

    if(hchintsts & USBHS_HCHINTSTS_AHBERRIF)
    {
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_AHBERRIF);

        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
    } 
    else if(hchintsts & USBHS_HCHINTSTS_ACKIF)
    {
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_ACKIF);
    }
    else if(hchintsts & USBHS_HCHINTSTS_FOVRIF)
    {
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
        USB_HCH_Halt(USBx, num);
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_FOVRIF);
    }
    else if(hchintsts & USBHS_HCHINTSTS_TXCFIF)
    {
        USBx->host.ErrCnt[num] = 0;
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
        USB_HCH_Halt(USBx, num);
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_TXCFIF);
        USBx->host.HCH_Status[num] = HCH_XFRC;            
    }
    else if(hchintsts & USBHS_HCHINTSTS_STALLIF)
    {
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_STALLIF);
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
        USB_HCH_Halt(USBx, num);
        USBx->host.HCH_Status[num] = HCH_STALL;      
    }
    else if(hchintsts & USBHS_HCHINTSTS_NAKIF)
    {
        USBx->host.ErrCnt[num] = 0;
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
        if(USBx->cfg.dma_enable == 0)
        {
            USB_HCH_Halt(USBx, num);
        }
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_NAKIF);
        USBx->host.HCH_Status[num] = HCH_NAK;      
    }

    else if(hchintsts & USBHS_HCHINTSTS_TXERRIF)
    {
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
        USB_HCH_Halt(USBx, num);
        USBx->host.HCH_Status[num] = HCH_XACTERR;
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_TXERRIF);
    }
    else if(hchintsts & USBHS_HCHINTSTS_NYETIF)
    {
        USBx->host.ErrCnt[num] = 0;
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
        if(USBx->cfg.dma_enable == 0)
        {
            USB_HCH_Halt(USBx, num);
        }
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_NYETIF);
        USBx->host.HCH_Status[num] = HCH_NYET;    
    }
    else if(hchintsts & USBHS_HCHINTSTS_DTERRIF)
    {
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
        USB_HCH_Halt(USBx, num);
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_NAKIF);
        USBx->host.HCH_Status[num] = HCH_DATATGLERR;

        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_DTERRIF);
    }  
    else if(hchintsts & USBHS_HCHINTSTS_CHHTDIF)
    {
        USB_MODIFY_REG32(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN, 0);

        if(USBx->host.HCH_Status[num] == HCH_XFRC)
        {
            USBx->host.URB_State[num] = URB_DONE;  

            if((hchctrl & USBHS_HCHCTRL_EPTYPE) >> USBHS_HCHCTRL_EPTYPE_POS == EP_TYPE_BULK)
            {
                USBx->host.hch[num].toggle_out ^= 1; 
            }
        }
        else if(USBx->host.HCH_Status[num] == HCH_NAK)
        {
            USBx->host.URB_State[num] = URB_NOTREADY;      
        }    
        else if(USBx->host.HCH_Status[num] == HCH_NYET)
        {
            if(USBx->host.hch[num].do_ping == 1)
            {
                USB_HCH_DoPing(USBx, num);
            }
            USBx->host.URB_State[num] = URB_NOTREADY;      
        }      
        else if(USBx->host.HCH_Status[num] == HCH_STALL)
        {
            USBx->host.URB_State[num] = URB_STALL;      
        }  
        else if(USBx->host.HCH_Status[num] == HCH_XACTERR)
        {
            USBx->host.URB_State[num] = URB_ERROR;  
        }
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_CHHTDIF);
    }
    return 1;
}
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */

/**
*\*\name    USBHOST_handle_hch_n_In_ISTR.
*\*\fun     Handles interrupt for a specific Host Channel.
*\*\param   USBx: selected device.
*\*\param   num: Channel number.
*\*\return  1.
*\*\
**/
uint32_t USBHOST_handle_hch_n_In_ISTR(USB_CORE_MODULE *USBx, uint32_t num)
{
    USB_HostCH_Registers *hostchreg;

    uint32_t hchintsts = 0;
    uint32_t hchinten = 0;
    uint32_t hchctrl = 0;
    uint32_t hchtxsiz = 0;
    uint8_t eptype = 0;

    hostchreg = USBx->regs.HCHCSR[num];
    hchintsts = USB_READ_REG32(&hostchreg->HCHINTSTS);
    hchinten = USB_READ_REG32(&hostchreg->HCHINTEN);
    hchintsts &= hchinten;
    hchctrl = USB_READ_REG32(&USBx->regs.HCHCSR[num]->HCHCTRL);


    eptype = (hchctrl & USBHS_HCHCTRL_EPTYPE) >> USBHS_HCHCTRL_EPTYPE_POS;

    if(hchintsts & USBHS_HCHINTSTS_AHBERRIF)
    {
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_AHBERRIF);
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
    }
    else if(hchintsts & USBHS_HCHINTSTS_ACKIF)
    {
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_ACKIF);
    }
    else if(hchintsts & USBHS_HCHINTSTS_STALLIF)  
    {
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
        USBx->host.HCH_Status[num] = HCH_STALL; 
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_NAKIF);   /* Clear the NAK Condition */
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_STALLIF); /* Clear the STALL Condition */
        hchintsts &= (~USBHS_HCHINTSTS_NAKIF);          /* NOTE: When there is a 'stall', reset also nak, 
                                                          else, the USBx->host.HCH_Status = HCH_STALL
                                                          will be overwritten by 'nak' in code below */
        USB_HCH_Halt(USBx, num);    
    }
    else if(hchintsts & USBHS_HCHINTSTS_DTERRIF)
    {
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
        USB_HCH_Halt(USBx, num);
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_NAKIF);
        USBx->host.HCH_Status[num] = HCH_DATATGLERR; 
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_DTERRIF);
    }

    if(hchintsts & USBHS_HCHINTSTS_FOVRIF)
    {
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
        USB_HCH_Halt(USBx, num);
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_FOVRIF);
    }
    else if(hchintsts & USBHS_HCHINTSTS_TXCFIF)
    {
        if(USBx->cfg.dma_enable == 1)
        {
            hchtxsiz = USB_READ_REG32(&USBx->regs.HCHCSR[num]->HCHTXSIZ);
            USBx->host.XferCnt[num] =  USBx->host.hch[num].xfer_len - ((hchtxsiz & USBHS_HCHTXSIZ_TXSIZ) >> USBHS_HCHTXSIZ_TXSIZ_POS);
        }

        USBx->host.HCH_Status[num] = HCH_XFRC;     
        USBx->host.ErrCnt[num] = 0;
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_TXCFIF);

        if((eptype == EP_TYPE_CTRL) || (eptype == EP_TYPE_BULK))
        {
            USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
            USB_HCH_Halt(USBx, num);
            USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_NAKIF);
            USBx->host.hch[num].toggle_in ^= 1;
        }
        else if(eptype == EP_TYPE_INTR)
        {
            hchctrl |= USBHS_HCHCTRL_ODDFRM;
            USB_WRITE_REG32(&USBx->regs.HCHCSR[num]->HCHCTRL, hchctrl); 
            USBx->host.URB_State[num] = URB_DONE;  
        } 
    }
    else if(hchintsts & USBHS_HCHINTSTS_CHHTDIF)
    {
        USB_MODIFY_REG32(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN, 0);

        if(USBx->host.HCH_Status[num] == HCH_XFRC)
        {
            USBx->host.URB_State[num] = URB_DONE;      
        }
        else if(USBx->host.HCH_Status[num] == HCH_STALL) 
        {
            USBx->host.URB_State[num] = URB_STALL;
        }   

        else if((USBx->host.HCH_Status[num] == HCH_XACTERR) || (USBx->host.HCH_Status[num] == HCH_DATATGLERR))
        {
            USBx->host.ErrCnt[num] = 0;
            USBx->host.URB_State[num] = URB_ERROR;
        }
        else if(eptype == EP_TYPE_INTR)
        {
            USBx->host.hch[num].toggle_in ^= 1;
        }
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_CHHTDIF);  
    }    
    else if(hchintsts & USBHS_HCHINTSTS_TXERRIF)
    {
        USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
        USBx->host.HCH_Status[num] = HCH_XACTERR;
        USB_HCH_Halt(USBx, num);
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_TXERRIF);  
    }
    else if(hchintsts & USBHS_HCHINTSTS_NAKIF)  
    {  
        if(eptype == EP_TYPE_INTR)
        {
            USB_SET_REG32_BIT(&USBx->regs.HCHCSR[num]->HCHINTEN, USBHS_HCHINTEN_CHHTDIEN);
            if(USBx->cfg.dma_enable == 0)
            {
                USB_HCH_Halt(USBx, num);
            }
        }
        USBx->host.HCH_Status[num] = HCH_NAK;
        USB_WRITE_REG32(&hostchreg->HCHINTSTS, USBHS_HCHINTSTS_NAKIF);  
        if((eptype == EP_TYPE_CTRL)|| (eptype == EP_TYPE_BULK))
        {
            /* re-activate the channel  */
            hchctrl |= USBHS_HCHCTRL_CHEN;
            hchctrl &= (~USBHS_HCHCTRL_CHDIS);
            USB_WRITE_REG32(&USBx->regs.HCHCSR[num]->HCHCTRL, hchctrl); 
        }
    }
    return 1;
}


#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */

/**
*\*\name    USBHOST_handle_rx_qlvl_ISTR.
*\*\fun     Handles the Rx Status Queue Level Interrupt.
*\*\param   USBx: selected device.
*\*\return  1.
*\*\
**/
static uint32_t USBHOST_handle_rx_qlvl_ISTR(USB_CORE_MODULE *USBx)
{
    uint32_t grxstsp = 0;
    uint32_t ginten = 0;
    uint32_t hchctrl = 0;
    uint32_t hchtxsiz = 0;

    __IO uint8_t chnum =0;  
    uint32_t count = 0;
    uint32_t bcnt = 0;

    /* Disable the Rx Status Queue Level interrupt */
    ginten |= USBHS_GINTEN_RXFNEIEN;
    USB_MODIFY_REG32(&USBx->regs.GCSR->GINTEN, ginten, 0);

    grxstsp = USB_READ_REG32(&USBx->regs.GCSR->GRXSTSP);
    chnum = (grxstsp & USBHS_GRXSTS_CHEPNUM) >> USBHS_GRXSTS_CHEPNUM_POS;
    bcnt = (grxstsp & USBHS_GRXSTS_BCNT) >> USBHS_GRXSTS_BCNT_POS;
    hchctrl = USB_READ_REG32(&USBx->regs.HCHCSR[chnum]->HCHCTRL);

    switch((grxstsp & USBHS_GRXSTS_PKTSTS) >> USBHS_GRXSTS_PKTSTS_POS)
    {
        case GRXSTS_PKTSTS_IN:
            /* Read the data into the host buffer. */
            if(((bcnt > 0) && (USBx->host.hch[chnum].xfer_buff != (void *)0)))
            {
                USB_ReadPacket(USBx, USBx->host.hch[chnum].xfer_buff, bcnt);
                /*manage multiple Xfer */
                USBx->host.hch[chnum].xfer_buff += bcnt;           
                USBx->host.hch[chnum].xfer_count  += bcnt;

                count = USBx->host.hch[chnum].xfer_count;
                USBx->host.XferCnt[chnum] = count;

                hchtxsiz = USB_READ_REG32(&USBx->regs.HCHCSR[chnum]->HCHTXSIZ);
                if(((hchtxsiz & USBHS_HCHTXSIZ_PKCNT) >> USBHS_HCHTXSIZ_PKCNT_POS) > 0)
                {
                    /* re-activate the channel when more packets are expected */
                    hchctrl |= USBHS_HCHCTRL_CHEN;
                    hchctrl &= (~USBHS_HCHCTRL_CHDIS);
                    USB_WRITE_REG32(&USBx->regs.HCHCSR[chnum]->HCHCTRL, hchctrl);
                }
            }
        break;

        case GRXSTS_PKTSTS_IN_XFER_COMP:

        case GRXSTS_PKTSTS_DATA_TOGGLE_ERR:
        case GRXSTS_PKTSTS_CH_HALTED:
        default:
        break;
    }

    /* Enable the Rx Status Queue Level interrupt */
    ginten |= USBHS_GINTEN_RXFNEIEN;
    USB_MODIFY_REG32(&USBx->regs.GCSR->GINTEN, 0, ginten);
    return 1;
}


#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */

/**
*\*\name    USBHOST_handle_IncompletePeriodicXfer_ISTR.
*\*\fun     Handles the incomplete Periodic transfer Interrupt.
*\*\param   USBx: selected device.
*\*\return  1.
*\*\
**/
static uint32_t USBHOST_handle_IncompletePeriodicXfer_ISTR(USB_CORE_MODULE *USBx)
{
    uint32_t gintsts = 0;
    uint32_t hchctrl = 0;

    hchctrl = USB_READ_REG32(&USBx->regs.HCHCSR[0]->HCHCTRL);
    hchctrl |= USBHS_HCHCTRL_CHEN;
    hchctrl |= USBHS_HCHCTRL_CHDIS;
    USB_WRITE_REG32(&USBx->regs.HCHCSR[0]->HCHCTRL, hchctrl);  

    /* Clear interrupt */
    gintsts |= USBHS_GINTSTS_PTNCIF_ISOUTNCIF;
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, gintsts);

    return 1;
}
