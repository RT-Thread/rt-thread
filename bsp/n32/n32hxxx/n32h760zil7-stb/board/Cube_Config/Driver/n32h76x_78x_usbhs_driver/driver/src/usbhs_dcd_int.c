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
 * @file usbhs_dcd_int.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbhs_dcd_int.h"
#include "usbhs_regs.h"
#include "n32h76x_78x_rcc.h"
#include "n32h76x_78x_pwr.h"

/* static functions */
static uint32_t USBDEV_ReadDevInEP(USB_CORE_MODULE *USBx, uint8_t epnum);

/* Interrupt Handlers */
static uint32_t USBDEV_HandleInEP_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBDEV_HandleOutEP_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBDEV_HandleSof_ISTR(USB_CORE_MODULE *USBx);

static uint32_t USBDEV_HandleRxStatusQueueLevel_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBDEV_WriteEmptyTxFifo(USB_CORE_MODULE *USBx , uint32_t epnum);

static uint32_t USBDEV_HandleUsbReset_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBDEV_HandleEnumDone_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBDEV_HandleResume_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBDEV_HandleUSBSuspend_ISTR(USB_CORE_MODULE *USBx);

static uint32_t USBDEV_IsoINIncomplete_ISTR(USB_CORE_MODULE *USBx);
static uint32_t USBDEV_IsoOUTIncomplete_ISTR(USB_CORE_MODULE *USBx);

/**
*\*\name    USBD_ISTR_Handler.
*\*\fun     Handles all USB Interrupts.
*\*\param   USBx: device instance.
*\*\return  status.
**/
uint32_t USBD_ISTR_Handler(USB_CORE_MODULE *USBx)
{
    uint32_t retval = 0;
    uint32_t gintsts = 0;

    if(USB_IsDeviceMode(USBx)) /* ensure that we are in device mode */
    {
        gintsts = USB_ReadCoreItr(USBx);
        if(gintsts == 0U) /* avoid spurious interrupt */
        {
            return 0;
        }
        if(gintsts & USBHS_GINTSTS_OUTEPIF)
        {
            retval |= USBDEV_HandleOutEP_ISTR(USBx);
        }
        if(gintsts & USBHS_GINTSTS_INEPIF)
        {
            retval |= USBDEV_HandleInEP_ISTR(USBx);
        }
        if(gintsts & USBHS_GINTSTS_MODMISIF)
        {
            USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, USBHS_GINTSTS_MODMISIF);
        }
        if(gintsts & USBHS_GINTSTS_WKUPIF)
        {
            retval |= USBDEV_HandleResume_ISTR(USBx);
        }
        if(gintsts & USBHS_GINTSTS_USBSUSPIF)
        {
            retval |= USBDEV_HandleUSBSuspend_ISTR(USBx);
        }
        if(gintsts & USBHS_GINTSTS_SOFIF)
        {
            retval |= USBDEV_HandleSof_ISTR(USBx);
        }
        if(gintsts & USBHS_GINTSTS_RXFNEIF)
        {
            retval |= USBDEV_HandleRxStatusQueueLevel_ISTR(USBx);
        }
        if(gintsts & USBHS_GINTSTS_USBRSTIF)
        {
            retval |= USBDEV_HandleUsbReset_ISTR(USBx);
        }
        if(gintsts & USBHS_GINTSTS_ENUMDIF)
        {
            retval |= USBDEV_HandleEnumDone_ISTR(USBx);
        }
        if(gintsts & USBHS_GINTSTS_ISOINCIF)
        {
            retval |= USBDEV_IsoINIncomplete_ISTR(USBx);
        }
        if(gintsts & USBHS_GINTSTS_PTNCIF_ISOUTNCIF)
        {
            retval |= USBDEV_IsoOUTIncomplete_ISTR(USBx);
        }
    }
    return retval;
}

/**
*\*\name    USBDEV_HandleResume_ISTR.
*\*\fun     Indicates that the USBHS controller has detected a resume or remote Wake-up sequence.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_HandleResume_ISTR(USB_CORE_MODULE *USBx)
{
    uint32_t pwrctrl;

    if(USBx->cfg.low_power)
    {
        /* un-gate USB Core clock */
        pwrctrl = USB_READ_REG32(USBx->regs.PWRCTRL);
        pwrctrl &= (~USBHS_PWRCTRL_PHYSTP);
        USB_WRITE_REG32(USBx->regs.PWRCTRL, pwrctrl);
    }

    /* Clear the Remote Wake-up Signaling */
    USB_MODIFY_REG32(&USBx->regs.DCSR->DCTRL, USBHS_DCTRL_RMWKUP, 0);

    /* Inform upper layer by the Resume Event */
    USBD_DEV_INT_fops->Resume(USBx);

    /* Clear interrupt */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, USBHS_GINTSTS_WKUPIF);
    return 1;
}

/**
*\*\name    USBDEV_HandleUSBSuspend_ISTR.
*\*\fun     Indicates that SUSPEND state has been detected on the USB.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_HandleUSBSuspend_ISTR(USB_CORE_MODULE *USBx)
{
    uint8_t prev_status;
    uint32_t dsts;

    prev_status = USBx->dev.device_status;
    USBD_DEV_INT_fops->Suspend(USBx);

    dsts = USB_READ_REG32(&USBx->regs.DCSR->DSTS);

    /* Clear interrupt */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, USBHS_GINTSTS_USBSUSPIF);

    if((USBx->cfg.low_power) && (dsts & USBHS_DSTS_SUSPF) && (prev_status  == USB_CONFIGURED))
    {
        /*  switch-off the clocks */
        USB_WRITE_REG32(USBx->regs.PWRCTRL, USBHS_PWRCTRL_PHYSTP);
        /* Request to enter SLEEP mode*/
        PWR_EnterSLEEPMode(PWR_SLEEP_NOW, PWR_SLEEPENTRY_WFI);
    }
    return 1;
}

/**
*\*\name    USBDEV_HandleInEP_ISTR.
*\*\fun     Indicates that an IN EP has a pending Interrupt.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_HandleInEP_ISTR(USB_CORE_MODULE *USBx)
{  
    uint32_t ep_intr;
    uint32_t epnum = 0;
    uint32_t fifoemptymsk;
    uint32_t dinepintsts;

    ep_intr = USB_ReadDevAllInEPItr(USBx);

    while(ep_intr)
    {
        if((ep_intr & 0x1) == 0x01) /* In ITR */
        {
            dinepintsts = USBDEV_ReadDevInEP(USBx, epnum); /* Get In ITR status */
            if(dinepintsts & USBHS_DINEPINTSTS_TXCIF)
            {
                fifoemptymsk = 0x1 << epnum;
                USB_MODIFY_REG32(&USBx->regs.DCSR->DINEPFEINTEN, fifoemptymsk, 0);
                USB_WRITE_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS, USBHS_DINEPINTSTS_TXCIF);
                /* TX COMPLETE */
                USBD_DEV_INT_fops->DataInStage(USBx , epnum);

                if (USBx->cfg.dma_enable == 1 && (epnum == 0))
                {
                    if(USBx->dev.out_ep[epnum].xfer_len == 0)
                    {
                        /* prepare to rx more setup packets */
                        USB_EP0_OutStart(USBx);
                    }
                }
            }
            if(dinepintsts & USBHS_DINEPINTSTS_EPDISIF)
            {
                USB_WRITE_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS, USBHS_DINEPINTSTS_EPDISIF);
            }       
            if(dinepintsts & USBHS_DINEPINTSTS_TOUTIF)
            {
                USB_WRITE_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS, USBHS_DINEPINTSTS_TOUTIF);
            }
            if(dinepintsts & USBHS_DINEPINTSTS_TXFERINTIF)
            {
                USB_WRITE_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS, USBHS_DINEPINTSTS_TXFERINTIF);
            }
            if(dinepintsts & USBHS_DINEPINTSTS_INEPNAKEIF)
            {
                USB_WRITE_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS, USBHS_DINEPINTSTS_INEPNAKEIF);
            }
            if(dinepintsts & USBHS_DINEPINTSTS_TXFEIF)
            {
                USBDEV_WriteEmptyTxFifo(USBx, epnum);
            }
        }
        epnum++;
        ep_intr >>= 1;
    }

    return 1;
}

/**
*\*\name    USBDEV_HandleOutEP_ISTR.
*\*\fun     Indicates that an OUT EP has a pending Interrupt.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_HandleOutEP_ISTR(USB_CORE_MODULE *USBx)
{
    uint32_t ep_intr;
    uint32_t epnum = 0;
    uint32_t doutepintsts;
    uint32_t douteptxsiz;
    uint32_t doutepintsts_v;

    /* Read in the device interrupt bits */
    ep_intr = USB_ReadDevAllOutEp_itr(USBx);

    while(ep_intr)
    {
        if(ep_intr&0x1)
        {
            doutepintsts = USB_ReadDevOutEP_itr(USBx, epnum);
            doutepintsts_v = USB_READ_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS);
            /* Transfer complete */
            if(doutepintsts & USBHS_DOUTEPINTSTS_TXCIF)
            {
                /* Clear the bit in DOUTEPINTSTSn for this interrupt */
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_TXCIF);
                if(USBx->cfg.dma_enable == 1)
                {
                    /* Setup Phase Done (control EPs) */
                    if(doutepintsts_v & USBHS_DOUTEPINTSTS_STUPPDNEIF)
                    {
                        if(doutepintsts_v & USBHS_DOUTEPINTSTS_STUPPRXIF)
                        {
                            USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_STUPPRXIF);
                        }
                    }
                    else if(doutepintsts_v & USBHS_DOUTEPINTSTS_STSPRXIF)
                    {
                        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_STSPRXIF);
                    }
                    else if((doutepintsts_v & (USBHS_DOUTEPINTSTS_STUPPDNEIF | USBHS_DOUTEPINTSTS_STSPRXIF)) == 0)
                    {
                        if(doutepintsts_v & USBHS_DOUTEPINTSTS_STUPPRXIF)
                        {
                            USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_STUPPRXIF);
                        }
                    }
                    douteptxsiz = USB_READ_REG32((&USBx->regs.OUTEPCSR[epnum]->DOUTEPTXSIZ));
                    /*ToDo : handle more than one single MPS size packet */
                    USBx->dev.out_ep[epnum].xfer_count = USBx->dev.out_ep[epnum].maxpacket - (douteptxsiz & USBHS_DOUTEPTXSIZ_TLEN);
                    
                    /* Inform upper layer: data ready */
                    /* RX COMPLETE */
                    USBD_DEV_INT_fops->DataOutStage(USBx , epnum);
                    if((epnum == 0) && (USBx->dev.out_ep[epnum].xfer_len == 0))
                    {
                        /* prepare to rx more setup packets */
                        USB_EP0_OutStart(USBx);
                    }
                }
                else
                {
                    /* Inform upper layer: data ready */
                    /* RX COMPLETE */
                    USBD_DEV_INT_fops->DataOutStage(USBx , epnum);
                }
            }
            if(doutepintsts & USBHS_DOUTEPINTSTS_OUTTRXEPDISIF)
            {
                /* Clear the bit in DOUTEPINTSTSn for this interrupt */
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_OUTTRXEPDISIF);
            }
            /* Endpoint disable  */
            if(doutepintsts & USBHS_DOUTEPINTSTS_EPDISIF)
            {
                /* Clear the bit in DOUTEPINTSTSn for this interrupt */
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_EPDISIF);
                
            }
            /* Setup Phase Done (control EPs) */
            if(doutepintsts & USBHS_DOUTEPINTSTS_STUPPDNEIF)
            {
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_STUPPDNEIF);
                /* inform the upper layer that a setup packet is available */
                /* SETUP COMPLETE */
                USBD_DEV_INT_fops->SetupStage(USBx);

                if(doutepintsts_v & USBHS_DOUTEPINTSTS_STUPPRXIF)
                {
                    USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_STUPPRXIF);
                }
                if((epnum == 0) && (USBx->cfg.dma_enable == 1) && (USBx->dev.out_ep[epnum].xfer_len == 0))
                {
                    /* prepare to rx more setup packets */
                    USB_EP0_OutStart(USBx);
                }
            }
            
            if(doutepintsts & USBHS_DOUTEPINTSTS_OUTTRXEPDISIF)
            {
                /* Clear the bit in DOUTEPINTSTSn for this interrupt */
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_OUTTRXEPDISIF);
                
            }
            
            /* Endpoint disable  */
            if(doutepintsts & USBHS_DOUTEPINTSTS_EPDISIF)
            {
                /* Clear the bit in DOUTEPINTSTSn for this interrupt */
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_EPDISIF);
            }
        }
        epnum++;
        ep_intr >>= 1;
    }
    return 1;
}

/**
*\*\name    USBDEV_HandleSof_ISTR.
*\*\fun     Handles the SOF Interrupts.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_HandleSof_ISTR(USB_CORE_MODULE *USBx)
{
    USBD_DEV_INT_fops->SOF(USBx);
    /* Clear SOF interrupt */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, USBHS_GINTSTS_SOFIF);

    return 1;
}

/**
*\*\name    USBDEV_HandleRxStatusQueueLevel_ISTR.
*\*\fun     Handles the Rx Status Queue Level Interrupt.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_HandleRxStatusQueueLevel_ISTR(USB_CORE_MODULE *USBx)
{
    USB_EP *ep;
    uint32_t grxstsp;
    uint32_t bcnt;

    /* Disable the Rx Status Queue Level interrupt */
    USB_MODIFY_REG32(&USBx->regs.GCSR->GINTEN, USBHS_GINTEN_RXFNEIEN, 0);

    /* Get the Status from the top of the FIFO */
    grxstsp = USB_READ_REG32(&USBx->regs.GCSR->GRXSTSP);
    bcnt = (grxstsp & USBHS_GRXSTS_BCNT) >> USBHS_GRXSTS_BCNT_POS;

    ep = &USBx->dev.out_ep[(grxstsp & USBHS_GRXSTS_CHEPNUM) >> USBHS_GRXSTS_CHEPNUM_POS];

    switch ((grxstsp & USBHS_GRXSTS_PKTSTS) >> USBHS_GRXSTS_PKTSTS_POS)
    {
        case STS_GOUT_NAK:
        break;
        case STS_DATA_UPDT:
            if(bcnt)
            {
                USB_ReadPacket(USBx,ep->xfer_buff, bcnt);
                ep->xfer_buff += bcnt;
                ep->xfer_count += bcnt;
            }
        break;
        case STS_XFER_COMP:
        break;
        case STS_SETUP_COMP:
        break;
        case STS_SETUP_UPDT:
            /* Copy the setup packet received in FIFO into the setup buffer in RAM */
            USB_ReadPacket(USBx , USBx->dev.setup_packet, 8);
            ep->xfer_count += bcnt;
        break;
        default:
        break;
    }
    /* Enable the Rx Status Queue Level interrupt */
    USB_MODIFY_REG32(&USBx->regs.GCSR->GINTEN, 0, USBHS_GINTEN_RXFNEIEN);
    return 1;
}

/**
*\*\name    USBDEV_WriteEmptyTxFifo.
*\*\fun     Check FIFO for the next packet to be loaded.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_WriteEmptyTxFifo(USB_CORE_MODULE *USBx, uint32_t epnum)
{
    USB_EP *ep;
    uint32_t len;
    uint32_t len32;
    uint32_t fifoemptymsk;
    uint32_t dineptxfsts;

    ep = &USBx->dev.in_ep[epnum];

    len = ep->xfer_len - ep->xfer_count;

    if(len > ep->maxpacket)
    {
        len = ep->maxpacket;
    }

    len32 = (len + 3) / 4;
    dineptxfsts = USB_READ_REG32(&USBx->regs.INEPCSR[epnum]->DINEPTXFSTS);

    while(((dineptxfsts & USBHS_DINEPTXFSTS_TXFSPCAVL) >> USBHS_DINEPTXFSTS_TXFSPCAVL_POS) > len32 &&
          (ep->xfer_count < ep->xfer_len) && (ep->xfer_len != 0))
    {
        /* Write the FIFO */
        len = ep->xfer_len - ep->xfer_count;
        if(len > ep->maxpacket)
        {
            len = ep->maxpacket;
        }
        len32 = (len + 3) / 4;

        USB_WritePacket(USBx , ep->xfer_buff, epnum, len);

        ep->xfer_buff  += len;
        ep->xfer_count += len;

        dineptxfsts = USB_READ_REG32(&USBx->regs.INEPCSR[epnum]->DINEPTXFSTS);

        /* Mask the TxFIFOEmpty interrupt  */
        if(ep->xfer_len == ep->xfer_count)
        {
            fifoemptymsk = 0x1 << ep->num;  
            USB_MODIFY_REG32(&USBx->regs.DCSR->DINEPFEINTEN, fifoemptymsk, 0); 
        }
    }

    return 1;
}

/**
*\*\name    USBDEV_HandleUsbReset_ISTR.
*\*\fun     This interrupt occurs when a USB Reset is detected.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_HandleUsbReset_ISTR(USB_CORE_MODULE *USBx)
{
    uint32_t i;
    uint32_t depinten = 0;
    uint32_t doutepinten = 0;
    uint32_t dinepinten = 0;
    uint32_t dcfg;

    /* Clear the Remote Wake-up Signaling */
    USB_MODIFY_REG32(&USBx->regs.DCSR->DCTRL, USBHS_DCTRL_RMWKUP, 0);

    /* Flush the Tx FIFO */
    USB_FlushTxFifo(USBx , 0x10);

    for (i=0; i<USBx->cfg.dev_endpoints_num; i++)
    {
        USB_WRITE_REG32(&USBx->regs.INEPCSR[i]->DINEPINTSTS, 0xFFFFU);
        USB_MODIFY_REG32(&USBx->regs.INEPCSR[i]->DINEPCTRL, USBHS_DINEPCTRL_STALL, 0);
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[i]->DOUTEPINTSTS, 0xFFFFU);
        USB_MODIFY_REG32(&USBx->regs.OUTEPCSR[i]->DOUTEPCTRL, USBHS_DOUTEPCTRL_STALL, USBHS_DOUTEPCTRL_SNAK);
    }
#ifdef USB_DEDICATED_EP_ENABLED
    USB_WRITE_REG32(&USBx->regs.DCSR->DEEPINTSTS, 0xFFFFFFFF);
    depinten |= 1 << USBHS_DEEPINTSTS_INEPINT_POS;
    depinten |= 1 << USBHS_DEEPINTSTS_OUTEPINT_POS;
    USB_WRITE_REG32(&USBx->regs.DCSR->DEEPINTEN, depinten);
#else
    USB_WRITE_REG32(&USBx->regs.DCSR->DAEPINTSTS, 0xFFFFFFFF);
    depinten |= 1 << USBHS_DAEPINTEN_INEPIEN_POS;
    depinten |= 1 << USBHS_DAEPINTEN_OUTEPIEN_POS;
    USB_WRITE_REG32(&USBx->regs.DCSR->DAEPINTEN, depinten);
#endif /* USB_DEDICATED_EP_ENABLED */
    
    doutepinten |= USBHS_DOUTEPINTEN_STUPDNEIEN;
    doutepinten |= USBHS_DOUTEPINTEN_TXCIEN;
    doutepinten |= USBHS_DOUTEPINTEN_EPDIEN;
    
#ifdef USB_DEDICATED_EP_ENABLED
    for (i = 0UL; i < USBx->cfg.dev_endpoints_num ; i++)
    {
        if(i<=8)
        {
            USB_WRITE_REG32(&USBx->regs.DCSR->DOUTEPXINTEN[i], doutepinten);
        }
    }
#else

    USB_WRITE_REG32(&USBx->regs.DCSR->DOUTEPINTEN, doutepinten);
#endif /* USB_DEDICATED_EP_ENABLED */

    dinepinten |= USBHS_DINEPINTEN_TXCIEN;
    dinepinten |= USBHS_DINEPINTEN_TOIEN;
    dinepinten |= USBHS_DINEPINTEN_EPDIEN;
    
#ifdef USB_DEDICATED_EP_ENABLED
    for (i = 0UL; i < USBx->cfg.dev_endpoints_num ; i++)
    {
        if(i<=8)
        {
            USB_WRITE_REG32(&USBx->regs.DCSR->DINEPXINTEN[i], dinepinten);
        }
    }
#else
    USB_WRITE_REG32(&USBx->regs.DCSR->DINEPINTEN, dinepinten);
#endif /* USB_DEDICATED_EP_ENABLED */

    /* Reset Device Address */
    dcfg = USB_READ_REG32(&USBx->regs.DCSR->DCFG);
    dcfg &= (~USBHS_DCFG_DEVARR);
    USB_WRITE_REG32(&USBx->regs.DCSR->DCFG, dcfg);

    /* setup EP0 to receive SETUP packets */
    USB_EP0_OutStart(USBx);

    /* Clear interrupt */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, USBHS_GINTSTS_USBRSTIF);

    /*Reset internal state machine */
    USBD_DEV_INT_fops->Reset(USBx);
    return 1;
}

/**
*\*\name    USBDEV_HandleEnumDone_ISTR.
*\*\fun     Read the device status register and set the device speed.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_HandleEnumDone_ISTR(USB_CORE_MODULE *USBx)
{
    RCC_ClocksTypeDef RCC_Clocks;
    uint32_t hclk;
    uint32_t gcfg;

    USB_EP0Activate(USBx);

    /* Get HCLK frequency */
    RCC_GetClocksFreqValue(&RCC_Clocks);
    hclk = RCC_Clocks.AHB2ClkFreq;

    /* Clear default TRDT value and Set USB turn-around time based on device speed and PHY interface. */
    gcfg = USB_READ_REG32(&USBx->regs.GCSR->GCFG);
    gcfg &= (~USBHS_GCFG_TRDTIM);
    USB_WRITE_REG32(&USBx->regs.GCSR->GCFG, gcfg);

    /* Full or High speed */
    if(USB_GetDeviceSpeed(USBx) == USB_SPEED_HIGH)
    {
        USBx->cfg.speed = USB_SPEED_HIGH;
        USBx->cfg.mps   = USB_HS_MAX_PACKET_SIZE ;
        /*USBTRD min For HS device*/
        gcfg |= (9 << USBHS_GCFG_TRDTIM_POS);
    }
    else
    {
        USBx->cfg.speed = USB_SPEED_FULL;
        USBx->cfg.mps   = USB_FS_MAX_PACKET_SIZE ; 

        /* The USBTRD is configured according to the tables below, depending on AHB frequency 
        used by application. In the low AHB frequency range it is used to stretch enough the USB response 
        time to IN tokens, the USB turnaround time, so to compensate for the longer AHB read access 
        latency to the Data FIFO */

        if((hclk >= 15000000)&&(hclk < 16000000))
        {
            /* hclk Clock Range between 15-16 MHz */
            gcfg |= (0xE << USBHS_GCFG_TRDTIM_POS);
        }

        else if((hclk >= 16000000)&&(hclk < 17100000))
        {
            /* hclk Clock Range between 16-17.1 MHz */
            gcfg |= (0xD << USBHS_GCFG_TRDTIM_POS);
        }

        else if((hclk >= 17100000)&&(hclk < 18400000))
        {
          /* hclk Clock Range between 17-18.4 MHz */
          gcfg |= (0xC << USBHS_GCFG_TRDTIM_POS);
        }

        else if((hclk >= 18400000)&&(hclk < 20000000))
        {
            /* hclk Clock Range between 18.4-20 MHz */
            gcfg |= (0xB << USBHS_GCFG_TRDTIM_POS);
        }

        else if((hclk >= 20000000)&&(hclk < 21800000))
        {
            /* hclk Clock Range between 20-21.8 MHz */
            gcfg |= (0xA << USBHS_GCFG_TRDTIM_POS);
        }

        else if((hclk >= 21800000)&&(hclk < 24000000))
        {
            /* hclk Clock Range between 21.8-24 MHz */
            gcfg |= (0x9 << USBHS_GCFG_TRDTIM_POS);
        }

        else if((hclk >= 24000000)&&(hclk < 26600000))
        {
            /* hclk Clock Range between 24-26.6 MHz */
            gcfg |= (0x8 << USBHS_GCFG_TRDTIM_POS);
        }

        else if((hclk >= 26600000)&&(hclk < 30000000))
        {
            /* hclk Clock Range between 26.6-30 MHz */
            gcfg |= (0x7 << USBHS_GCFG_TRDTIM_POS);
        }

        else if((hclk >= 30000000)&&(hclk < 34300000))
        {
            /* hclk Clock Range between 30-34.3 MHz */
            gcfg |= (0x6 << USBHS_GCFG_TRDTIM_POS);
        } 

        else /* if(hclk >= 34300000) */
        {
            /* hclk Clock Range between 34.3-240 MHz */
            gcfg |= (0x5 << USBHS_GCFG_TRDTIM_POS);
        }
    }
    USB_MODIFY_REG32(&USBx->regs.GCSR->GCFG, 0, gcfg);

    /* Clear interrupt */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, USBHS_GINTSTS_ENUMDIF);
    return 1;
}

/**
*\*\name    USBDEV_IsoINIncomplete_ISTR.
*\*\fun     Handle the ISO IN incomplete interrupt.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_IsoINIncomplete_ISTR(USB_CORE_MODULE *USBx)
{
    USBD_DEV_INT_fops->IsoINIncomplete (USBx); 

    /* Clear interrupt */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, USBHS_GINTSTS_ISOINCIF);
    
    return 1;
}

/**
*\*\name    USBDEV_IsoOUTIncomplete_ISTR.
*\*\fun     Handle the ISO OUT incomplete interrupt.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_IsoOUTIncomplete_ISTR(USB_CORE_MODULE *USBx)
{
    USBD_DEV_INT_fops->IsoOUTIncomplete(USBx); 

    /* Clear interrupt */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, USBHS_GINTSTS_PTNCIF_ISOUTNCIF);
    return 1;
}

/**
*\*\name    USBDEV_ReadDevInEP.
*\*\fun     Reads IN ep flags.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_ReadDevInEP (USB_CORE_MODULE *USBx, uint8_t epnum)
{
    uint32_t v;
    uint32_t dinepinten;
    uint32_t dinepfeinten;

    dinepinten = USB_READ_REG32(&USBx->regs.DCSR->DINEPINTEN);
    dinepfeinten = USB_READ_REG32(&USBx->regs.DCSR->DINEPFEINTEN);
    dinepinten |= ((dinepfeinten >> epnum) & 0x1) << 7;
    v = USB_READ_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS) & dinepinten;
    return v;
}

/**
*\*\name    USBD_ISTR_WKUP_handler.
*\*\fun     Handle Wake up interrupt.
*\*\param   USBx: device instance.
*\*\return  none.
**/
void USBD_ISTR_WKUP_handler(USB_CORE_MODULE *USBx)
{
    uint32_t gintsts;
    if(USB_IsDeviceMode(USBx)) 
    {
        gintsts= USB_ReadCoreItr(USBx);
        if(gintsts & USBHS_GINTSTS_WKUPIF)
        {
            USBDEV_HandleResume_ISTR(USBx);
        }
    }
}

#ifdef USB_DEDICATED_EP_ENABLED

/**
*\*\name    USBDEV_HandleEachInEP_ISTR.
*\*\fun     Indicates that Each IN EP has a pending Interrupt.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_HandleEachInEP_ISTR(USB_CORE_MODULE *USBx)
{  
    uint32_t ep_intr;
    uint32_t epnum = 0;
    uint32_t fifoemptymsk;
    uint32_t dinepintsts, dinepinten;

    ep_intr = USB_ReadDevEachInEPItr(USBx);

    while(ep_intr)
    {
        if((ep_intr & 0x1) == 0x01) /* In ITR */
        {
            dinepinten  = USB_READ_REG32(&USBx->regs.DCSR->DINEPXINTEN[epnum]); /* Get In ITR status */
            dinepinten |= (((USB_READ_REG32(&USBx->regs.DCSR->DINEPFEINTEN) >> epnum) & 0x1UL) << 7U);
            dinepintsts = (USB_READ_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS) & dinepinten); 
            if(dinepintsts & USBHS_DINEPINTSTS_TXCIF)
            {
                fifoemptymsk = 0x1 << epnum;
                USB_MODIFY_REG32(&USBx->regs.DCSR->DINEPFEINTEN, fifoemptymsk, 0);
                USB_WRITE_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS, USBHS_DINEPINTSTS_TXCIF);
                /* TX COMPLETE */
                USBD_DEV_INT_fops->DataInStage(USBx , epnum);

                if (USBx->cfg.dma_enable == 1 && (epnum == 0))
                {
                    if(USBx->dev.out_ep[epnum].xfer_len == 0)
                    {
                        /* prepare to rx more setup packets */
                        USB_EP0_OutStart(USBx);
                    }
                }
            }
            if(dinepintsts & USBHS_DINEPINTSTS_EPDISIF)
            {
                USB_WRITE_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS, USBHS_DINEPINTSTS_EPDISIF);
            }       
            if(dinepintsts & USBHS_DINEPINTSTS_TOUTIF)
            {
                USB_WRITE_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS, USBHS_DINEPINTSTS_TOUTIF);
            }
            if(dinepintsts & USBHS_DINEPINTSTS_TXFERINTIF)
            {
                USB_WRITE_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS, USBHS_DINEPINTSTS_TXFERINTIF);
            }
            if(dinepintsts & USBHS_DINEPINTSTS_INEPNAKEIF)
            {
                USB_WRITE_REG32(&USBx->regs.INEPCSR[epnum]->DINEPINTSTS, USBHS_DINEPINTSTS_INEPNAKEIF);
            }
            if(dinepintsts & USBHS_DINEPINTSTS_TXFEIF)
            {
                USBDEV_WriteEmptyTxFifo(USBx, epnum);
            }
        }
        epnum++;
        ep_intr >>= 1;
    }

    return 1;
}

/**
*\*\name    USBDEV_HandleEachOutEP_ISTR.
*\*\fun     Indicates that Each OUT EP has a pending Interrupt.
*\*\param   USBx: device instance.
*\*\return  status.
**/
static uint32_t USBDEV_HandleEachOutEP_ISTR(USB_CORE_MODULE *USBx)
{
    uint32_t ep_intr;
    uint32_t epnum = 0;
    uint32_t doutepintsts;
    uint32_t douteptxsiz;
    uint32_t doutepintsts_v;

    /* Read in the device interrupt bits */
    ep_intr = USB_ReadDevEachOutEPItr(USBx);

    while(ep_intr)
    {
        if(ep_intr&0x1)
        {
            doutepintsts = USB_READ_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS);
            doutepintsts &= USB_READ_REG32(&USBx->regs.DCSR->DOUTEPXINTEN[epnum]);
            doutepintsts_v = USB_READ_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS);
            /* Transfer complete */
            if(doutepintsts & USBHS_DOUTEPINTSTS_TXCIF)
            {
                /* Clear the bit in DOUTEPINTSTSn for this interrupt */
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_TXCIF);
                if(USBx->cfg.dma_enable == 1)
                {
                    /* Setup Phase Done (control EPs) */
                    if(doutepintsts_v & USBHS_DOUTEPINTSTS_STUPPDNEIF)
                    {
                        if(doutepintsts_v & USBHS_DOUTEPINTSTS_STUPPRXIF)
                        {
                            USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_STUPPRXIF);
                        }
                    }
                    else if(doutepintsts_v & USBHS_DOUTEPINTSTS_STSPRXIF)
                    {
                        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_STSPRXIF);
                    }
                    else if((doutepintsts_v & (USBHS_DOUTEPINTSTS_STUPPDNEIF | USBHS_DOUTEPINTSTS_STSPRXIF)) == 0)
                    {
                        if(doutepintsts_v & USBHS_DOUTEPINTSTS_STUPPRXIF)
                        {
                            USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_STUPPRXIF);
                        }
                    }
                    douteptxsiz = USB_READ_REG32((&USBx->regs.OUTEPCSR[epnum]->DOUTEPTXSIZ));
                    /*ToDo : handle more than one single MPS size packet */
                    USBx->dev.out_ep[epnum].xfer_count = USBx->dev.out_ep[epnum].maxpacket - (douteptxsiz & USBHS_DOUTEPTXSIZ_TLEN);
                    
                    /* Inform upper layer: data ready */
                    /* RX COMPLETE */
                    USBD_DEV_INT_fops->DataOutStage(USBx , epnum);
                    if((epnum == 0) && (USBx->dev.out_ep[epnum].xfer_len == 0))
                    {
                        /* prepare to rx more setup packets */
                        USB_EP0_OutStart(USBx);
                    }
                }
                else
                {
                    /* Inform upper layer: data ready */
                    /* RX COMPLETE */
                    USBD_DEV_INT_fops->DataOutStage(USBx , epnum);
                }
            }
            if(doutepintsts & USBHS_DOUTEPINTSTS_OUTTRXEPDISIF)
            {
                /* Clear the bit in DOUTEPINTSTSn for this interrupt */
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_OUTTRXEPDISIF);
            }
            /* Endpoint disable  */
            if(doutepintsts & USBHS_DOUTEPINTSTS_EPDISIF)
            {
                /* Clear the bit in DOUTEPINTSTSn for this interrupt */
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_EPDISIF);
                
            }
            /* Setup Phase Done (control EPs) */
            if(doutepintsts & USBHS_DOUTEPINTSTS_STUPPDNEIF)
            {
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_STUPPDNEIF);
                /* inform the upper layer that a setup packet is available */
                /* SETUP COMPLETE */
                USBD_DEV_INT_fops->SetupStage(USBx);

                if(doutepintsts_v & USBHS_DOUTEPINTSTS_STUPPRXIF)
                {
                    USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_STUPPRXIF);
                }
                if((epnum == 0) && (USBx->cfg.dma_enable == 1) && (USBx->dev.out_ep[epnum].xfer_len == 0))
                {
                    /* prepare to rx more setup packets */
                    USB_EP0_OutStart(USBx);
                }
            }
            
            if(doutepintsts & USBHS_DOUTEPINTSTS_OUTTRXEPDISIF)
            {
                /* Clear the bit in DOUTEPINTSTSn for this interrupt */
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_OUTTRXEPDISIF);
            }
            
            /* Endpoint disable  */
            if(doutepintsts & USBHS_DOUTEPINTSTS_EPDISIF)
            {
                /* Clear the bit in DOUTEPINTSTSn for this interrupt */
                USB_WRITE_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS, USBHS_DOUTEPINTSTS_EPDISIF);
            }
        }
        epnum++;
        ep_intr >>= 1;
    }
    return 1;
}

/**
*\*\name    USBD_EP_IN_ISTR_Handler.
*\*\fun     Handle IN EP interrupt.
*\*\param   USBx: device instance.
*\*\return  none.
**/
void USBD_EP_IN_ISTR_Handler(USB_CORE_MODULE *USBx)
{
    uint32_t ep_intr;
    if (USB_IsDeviceMode(USBx)) 
    {
        ep_intr = USB_ReadDevEachInEPItr(USBx);
        
        if (ep_intr == 0UL) 
        {
            return;
        }
        USBDEV_HandleEachInEP_ISTR(USBx);
    }
}

/**
*\*\name    USBD_EP_OUT_ISTR_Handler.
*\*\fun     Handle OUT EP interrupt.
*\*\param   USBx: device instance.
*\*\return  none.
**/
void USBD_EP_OUT_ISTR_Handler(USB_CORE_MODULE *USBx)
{
    uint32_t ep_intr;
    if (USB_IsDeviceMode(USBx)) 
    {
        ep_intr = USB_ReadDevEachOutEPItr(USBx);
        if (ep_intr == 0UL) 
        {
            return;
        }
        USBDEV_HandleEachOutEP_ISTR(USBx);
    }
}

#endif /* USB_DEDICATED_EP_ENABLED */
