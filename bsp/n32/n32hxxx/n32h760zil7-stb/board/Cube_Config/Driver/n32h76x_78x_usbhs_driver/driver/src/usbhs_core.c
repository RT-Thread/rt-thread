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
 * @file usbhs_core.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbhs_core.h"
#include "usbhs_bsp.h"
#include "n32h76x_78x_rcc.h"
#include "usbhs_dcd.h"
#include "usbhs_defines.h"

/**
*\*\name    USB_EnableCommonInt.
*\*\fun     Initializes the commmon interrupts, used in both device and modes.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
static void USB_EnableCommonInt(USB_CORE_MODULE *USBx)
{
    /* Clear any pending interrupts */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, 0xFFFFFFFFU);
    /* Enable the interrupts in the INTEN */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTEN, (USBHS_GINTEN_WKUPIEN | USBHS_GINTEN_USBSUSPIEN));
}

/**
*\*\name    USB_CoreReset.
*\*\fun     Soft reset of the core.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
static USB_STS USB_CoreReset(USB_CORE_MODULE *USBx)
{
    USB_STS status = USB_OK;
    uint32_t u32grstctrl;
    uint32_t count = 0;

    /* Wait for AHB master IDLE state. */
    do
    {
        USB_BSP_uDelay(3);
        u32grstctrl = USB_READ_REG32(&USBx->regs.GCSR->GRSTCTRL);
        if (++count > 200000UL)
        {
            return USB_OK;
        }
    }while((u32grstctrl & USBHS_GRSTCTRL_AHBIDLE) == 0);
    
    if(status == USB_OK)
    {
    /* Core Soft Reset */
        count = 0;
        u32grstctrl |= USBHS_GRSTCTRL_CSRST;
        USB_WRITE_REG32(&USBx->regs.GCSR->GRSTCTRL, u32grstctrl);
        do
        {
            u32grstctrl = USB_READ_REG32(&USBx->regs.GCSR->GRSTCTRL);
            if (++count > 200000UL)
            {
                break;
            }
        } while ((u32grstctrl & USBHS_GRSTCTRL_SRSTDNE) == 0);
        /* clear CSRST bit*/
        u32grstctrl &= (~USBHS_GRSTCTRL_CSRST);
        USB_WRITE_REG32(&USBx->regs.GCSR->GRSTCTRL, u32grstctrl);
        
        USB_BSP_uDelay(3);
    }
    return status;
}


/**
*\*\name    USB_WritePacket.
*\*\fun     Writes a packet into the Tx FIFO associated with the EP.
*\*\param   USBx: selected device.
*\*\param   src : source pointer.
*\*\param   ch_ep_num : end point number.
*\*\param   len : length of bytes.
*\*\return  status.
*\*\
**/
USB_STS USB_WritePacket(USB_CORE_MODULE *USBx, uint8_t *src,uint8_t ch_ep_num, uint16_t len)
{
    USB_STS status = USB_OK;
    uint32_t u32Count32b = 0, i = 0;
    __IO uint32_t *fifo;

    if(USBx->cfg.dma_enable == 0)
    {
        u32Count32b =  (len + 3) / 4;
        fifo = USBx->regs.DFIFO[ch_ep_num];
        for (i=0; i<u32Count32b; i++)
        {
            *fifo = *((__IO uint32_t *)src);
            src+=4;
        }
    }
    return status;
}


/**
*\*\name    USB_ReadPacket.
*\*\fun     Reads a packet from the Rx FIFO.
*\*\param   USBx: selected device.
*\*\param   dest : Destination Pointer.
*\*\param   len : length of bytes.
*\*\return  none.
*\*\
**/
void *USB_ReadPacket(USB_CORE_MODULE *USBx, uint8_t *dest, uint16_t len)
{
    uint32_t i=0;
    uint32_t u32Count32b = 0;

    __IO uint32_t *fifo = USBx->regs.DFIFO[0];
    u32Count32b = (len + 3) / 4;

    for(i=0; i<u32Count32b; i++)
    {
        *(__IO uint32_t *)dest = *fifo;
        dest += 4 ;
    }
    return ((void *)dest);
}

static uint32_t USBHS_PHYCLKSel(void)
{
    uint32_t temp;
    
    if(HSE_VALUE == 10000000)
    {
        temp = USBHS_WRPCFG_PHYCLKSEL_10M;
    }
    else if(HSE_VALUE == 12000000)
    {
        temp = USBHS_WRPCFG_PHYCLKSEL_12M;
    }
    else if(HSE_VALUE == 25000000)
    {
        temp = USBHS_WRPCFG_PHYCLKSEL_25M;
    }
    else if(HSE_VALUE == 30000000)
    {
        temp = USBHS_WRPCFG_PHYCLKSEL_30M;
    }
    else if(HSE_VALUE == 19200000)
    {
        temp = USBHS_WRPCFG_PHYCLKSEL_19_2M;
    }
    else if(HSE_VALUE == 24000000)
    {
        temp = USBHS_WRPCFG_PHYCLKSEL_24M;
    }
    else if(HSE_VALUE == 27000000)
    {
        temp = USBHS_WRPCFG_PHYCLKSEL_27M;
    }
    else if(HSE_VALUE == 40000000)
    {
        temp = USBHS_WRPCFG_PHYCLKSEL_40M;
    }
    else
    {
        temp = USBHS_WRPCFG_PHYCLKSEL_25M;
    }
    return temp;
}


/**
*\*\name    USB_BasicInit.
*\*\fun     Initialize core registers address and configuration.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS USB_BasicInit(USB_CORE_MODULE *USBx, USB_CORE_ID_TypeDef coreID)
{
    uint32_t i ,baseAddress, wrapperAddress;
    uint32_t temp;
    
    USB_STS status = USB_OK;

    if(coreID == USBHS1_CORE_ID)
    {
        baseAddress = USBHS1_BASE_ADDR;
        wrapperAddress = USBHS1_WARP_BASE_ADDR;
    }
    else if(coreID == USBHS2_CORE_ID)
    {
        baseAddress = USBHS2_BASE_ADDR;
        wrapperAddress = USBHS2_WARP_BASE_ADDR;
    }
    
    /* configure USB default transfer mode as dma disable */
    USBx->cfg.dma_enable       = 0;

    /* Configure startup the core is in FS mode */
    USBx->cfg.speed            = USB_SPEED_FULL;
    USBx->cfg.mps              = USB_FS_MAX_PACKET_SIZE;
    /* initialize device cfg following its address */
    USBx->cfg.dev_endpoints_num = USB_MAX_EP_NUM;
    USBx->cfg.host_channels_num = USB_MAX_CHANNEL_NUM;
    USBx->cfg.TotalFifoSize     = USB_MAX_FIFO_WORDLEN;

#ifdef USB_INTERNAL_DMA_ENABLED
    USBx->cfg.dma_enable = 1;
#endif

    USBx->regs.GCSR     = (USB_Global_Registers *)(baseAddress + USB_GLOBAL_REGS_OFFSET);
    USBx->regs.DCSR     = (USB_Device_Registers *)(baseAddress + USB_DEV_GLOBAL_REG_OFFSET);
    USBx->regs.HCSR     = (USB_Host_Registers *)(baseAddress + USB_HOST_GLOBAL_REG_OFFSET);
    USBx->regs.HPCS     = (uint32_t *)(baseAddress + USB_HOST_PORT_REGS_OFFSET);
    USBx->regs.PWRCTRL  = (uint32_t *)(baseAddress + USB_PWRCTRL_OFFSET);
    USBx->regs.PWRCTRL1 = (uint32_t *)(baseAddress + USB_PWRCTRL1_OFFSET);
    
    USBx->regs.WRAPCSR  = (USB_Wrapper_Registers *)(wrapperAddress);

    for (i = 0; i < USBx->cfg.dev_endpoints_num; i++)
    {
        USBx->regs.INEPCSR[i]  = (USB_INEP_Registers *) (baseAddress + USB_DEV_IN_EP_REG_OFFSET + (i * USB_EP_REG_OFFSET));
        USBx->regs.OUTEPCSR[i] = (USB_OUTEP_Registers *)(baseAddress + USB_DEV_OUT_EP_REG_OFFSET + (i * USB_EP_REG_OFFSET));
    }
    for (i = 0; i < USBx->cfg.host_channels_num; i++)
    {
        USBx->regs.HCHCSR[i] = (USB_HostCH_Registers *)(baseAddress + USB_HOST_CHANNEL_REGS_OFFSET + (i * USB_CHANNEL_REGS_OFFSET));
    }
    for (i = 0; i < USBx->cfg.host_channels_num; i++)
    {
        USBx->regs.DFIFO[i] = (uint32_t *)(baseAddress + USB_DATA_FIFO_OFFSET + (i * USB_DATA_FIFO_SIZE));
    }
    
    temp = USBx->regs.WRAPCSR->WRPCFG;
    /* Select PHY clock source */
    temp &= ~USBHS_WRPCFG_PHYCLKSEL;
    temp |= USBHS_PHYCLKSel();
    /* Enable PHY PLL */
    temp |= USBHS_WRPCFG_PLLEN;
    
#ifdef USE_HOST_MODE
    /* Set ID internal signal */
    temp &= ~USBHS_WRPCFG_IDSIG;
#endif
    
    USBx->regs.WRAPCSR->WRPCFG = temp;
    
    temp = USBx->regs.WRAPCSR->WRPCTRL;
    temp |= USBHS_WRPCTRL_PINDETEN;
    USBx->regs.WRAPCSR->WRPCTRL = temp;
    
    return status;
}

/**
*\*\name    USB_CoreInit.
*\*\fun     Initializes the USBHS controller registers and prepares the core device mode or host mode operation.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS USB_CoreInit(USB_CORE_MODULE *USBx)
{
    USB_STS status = USB_OK;
    
    /* HS Interface */
    USB_MODIFY_REG32(&USBx->regs.GCSR->GCFG, USBHS_GCFG_PHYSEL, 0);

    /* set phy 8bit */
    USB_MODIFY_REG32(&USBx->regs.GCSR->GCFG, USBHS_GCFG_PHYIF, USBHS_GCFG_PHYIF);
    
    /* Reset after a PHY select and set Host mode */
    USB_CoreReset(USBx);

    USB_BSP_mDelay(20);
  
    /* case the HS core is working in FS mode */
    if(USBx->cfg.dma_enable == 1)
    {
        USB_MODIFY_REG32(&USBx->regs.GCSR->GAHBCFG, USBHS_GAHBCFG_BURSTTYP, 5 << USBHS_GAHBCFG_BURSTTYP_POS);
        USB_MODIFY_REG32(&USBx->regs.GCSR->GAHBCFG, 0, USBHS_GAHBCFG_DMAEN);
    }
    return status;
}

/**
*\*\name    USB_EnableGlobalInt.
*\*\fun     Enables or Disables the usb Global Int.
*\*\param   USBx: selected device.
*\*\param   Cmd : ENABLE or DISABLE
*\*\return  status.
*\*\
**/
USB_STS USB_EnableGlobalInt(USB_CORE_MODULE *USBx, FunctionalState Cmd)
{
    USB_STS status = USB_OK;
    if (Cmd != DISABLE)
    {
        /* Enable interrupts */
        USB_MODIFY_REG32(&USBx->regs.GCSR->GAHBCFG, 0, USBHS_GAHBCFG_GINTEN);
    }
    else
    {
        /* Disable interrupts */
        USB_MODIFY_REG32(&USBx->regs.GCSR->GAHBCFG, USBHS_GAHBCFG_GINTEN, 0);
    }
    return status;
}

/**
*\*\name    USB_FlushTxFifo.
*\*\fun     Flush a Tx FIFO.
*\*\param   USBx: selected device.
*\*\param   num : FIFO num.
*\*\return  status.
*\*\
**/
USB_STS USB_FlushTxFifo(USB_CORE_MODULE *USBx , uint32_t num)
{
    USB_STS status = USB_OK;
    uint32_t  grstctrl = 0;
    uint32_t count = 0;

    do
    {
        grstctrl = USB_READ_REG32(&USBx->regs.GCSR->GRSTCTRL);
        if (++count > 200000)
        {
            break;
        }
    }while ((grstctrl & USBHS_GRSTCTRL_AHBIDLE) == 0);
    
    count = 0;
    grstctrl = 0;
    grstctrl |= USBHS_GRSTCTRL_TXFFLSH;
    grstctrl |= ((num & 0x1FU) << USBHS_GRSTCTRL_TXFNUM_POS);
    USB_WRITE_REG32(&USBx->regs.GCSR->GRSTCTRL, grstctrl);
    do
    {
        grstctrl = USB_READ_REG32(&USBx->regs.GCSR->GRSTCTRL);
        if (++count > 200000)
        {
            break;
        }
    }while ((grstctrl & USBHS_GRSTCTRL_TXFFLSH) != 0);
    return status;
}

/**
*\*\name    USB_FlushRxFifo.
*\*\fun     Flush a Rx FIFO.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS USB_FlushRxFifo(USB_CORE_MODULE *USBx)
{
    USB_STS status = USB_OK;
    uint32_t  grstctrl = 0;
    uint32_t count = 0;

    do
    {
        grstctrl = USB_READ_REG32(&USBx->regs.GCSR->GRSTCTRL);
        if (++count > 200000)
        {
            break;
        }
    }while ((grstctrl & USBHS_GRSTCTRL_AHBIDLE) == 0);
    
    count = 0;

    USB_WRITE_REG32(&USBx->regs.GCSR->GRSTCTRL, USBHS_GRSTCTRL_RXFFLSH);

    do
    {
        grstctrl = USB_READ_REG32(&USBx->regs.GCSR->GRSTCTRL);
        if(++count > 200000)
        {
            break;
        }
    }while ((grstctrl & USBHS_GRSTCTRL_RXFFLSH) != 0);
    return status;
}


/**
*\*\name    USB_SetCurrentMode.
*\*\fun     Set ID line.
*\*\param   USBx: selected device.
*\*\param   mode: (Host/device).
*\*\return  status.
*\*\
**/
USB_STS USB_SetCurrentMode(USB_CORE_MODULE *USBx , uint8_t mode)
{
    USB_STS status = USB_OK;

    if(mode == HOST_MODE)
    {
        USB_MODIFY_REG32(&USBx->regs.GCSR->GCFG, USBHS_GCFG_FHMODE | USBHS_GCFG_FDMODE, USBHS_GCFG_FHMODE);
    }
    else
    {
        USB_MODIFY_REG32(&USBx->regs.GCSR->GCFG, USBHS_GCFG_FHMODE | USBHS_GCFG_FDMODE, USBHS_GCFG_FDMODE);
    }
    USB_BSP_mDelay(50);
    return status;
}


/**
*\*\name    USB_GetMode.
*\*\fun     Get current mode.
*\*\param   USBx: selected device.
*\*\return  current mode.
*\*\
**/
uint32_t USB_GetMode(USB_CORE_MODULE *USBx)
{
    return (USB_READ_REG32(&USBx->regs.GCSR->GINTSTS) & 0x1);
}

/**
*\*\name    USB_IsDeviceMode.
*\*\fun     Check if it is device mode.
*\*\param   USBx: selected device.
*\*\return  1 or 0.
*\*\
**/
uint8_t USB_IsDeviceMode(USB_CORE_MODULE *USBx)
{
    if(USB_GetMode(USBx) != HOST_MODE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
*\*\name    USB_IsHostMode.
*\*\fun     Check if it is host mode.
*\*\param   USBx: selected device.
*\*\return  1 or 0.
*\*\
**/
uint8_t USB_IsHostMode(USB_CORE_MODULE *USBx)
{
    if(USB_GetMode(USBx) != HOST_MODE)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
*\*\name    USB_ReadCoreItr.
*\*\fun     returns the Core Interrupt register.
*\*\param   USBx: selected device.
*\*\return  v.
*\*\
**/
uint32_t USB_ReadCoreItr(USB_CORE_MODULE *USBx)
{
    uint32_t v;
    v = USB_READ_REG32(&USBx->regs.GCSR->GINTSTS);
    v &= USB_READ_REG32(&USBx->regs.GCSR->GINTEN);
    return v;
}

#ifdef USE_HOST_MODE
/**
*\*\name    USB_CoreInitHost.
*\*\fun     Initializes USBHS controller for host mode.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS USB_CoreInitHost(USB_CORE_MODULE *USBx)
{
    USB_STS status = USB_OK;

    uint32_t i = 0;

    /* configure charge pump IO */
    USB_BSP_ConfigVBUS(USBx);

    /* Restart the Phy Clock */
    USB_WRITE_REG32(USBx->regs.PWRCTRL, 0);

    USB_ResetPort(USBx);

    USB_CLR_REG32_BIT(&USBx->regs.HCSR->HCFG, USBHS_HCFG_SPSEL);

    /* Configure data FIFO sizes */
    /* set Rx FIFO size */
    USB_WRITE_REG32(&USBx->regs.GCSR->GRXFSIZ, RX_FIFO_HS_SIZE);
    USB_WRITE_REG32(&USBx->regs.GCSR->GNPTXFSIZ_DINEP0TXFSIZ, ( RX_FIFO_HS_SIZE << USBHS_DINEP0TXSIZ_IEP0TXFRSADD_POS | TXH_NP_HS_FIFOSIZE << USBHS_DINEP0TXSIZ_NPTXFDEP_POS));

    USB_WRITE_REG32(&USBx->regs.GCSR->HPTXFSIZ, ((RX_FIFO_HS_SIZE + TXH_NP_HS_FIFOSIZE) << USBHS_HPTXFSIZ_HPTXFSADD_POS | TXH_P_HS_FIFOSIZE << USBHS_HPTXFSIZ_HPTXFDEP_POS));

    /* Make sure the FIFOs are flushed. */
    USB_FlushTxFifo(USBx, 0x10);         /* all Tx FIFOs */
    USB_FlushRxFifo(USBx);

    /* Clear all pending HC Interrupts */
    for (i = 0; i < USBx->cfg.host_channels_num; i++)
    {
        USB_WRITE_REG32(&USBx->regs.HCHCSR[i]->HCHINTSTS, 0xFFFFFFFF);
        USB_WRITE_REG32(&USBx->regs.HCHCSR[i]->HCHINTEN, 0);
    }

    USB_DriveVbus(USBx, 1);

    USB_EnableHostInt(USBx);
    return status;
}

/**
*\*\name    USB_IsEvenFrame.
*\*\fun     This function returns the frame number for sof packet.
*\*\param   USBx: selected device.
*\*\return  Frame number.
*\*\
**/
uint8_t USB_IsEvenFrame(USB_CORE_MODULE *USBx)
{
    return !(USB_READ_REG32(&USBx->regs.HCSR->HFNUM) & 0x1);
}

/**
*\*\name    USB_DriveVbus.
*\*\fun     set/reset vbus.
*\*\param   USBx: selected device.
*\*\param   state : VBUS state
*\*\return  none.
*\*\
**/
void USB_DriveVbus(USB_CORE_MODULE *USBx, uint8_t state)
{
    uint32_t hpcs = 0;

    /* enable disable the external charge pump */
    USB_BSP_DriveVBUS(USBx, state);

    /* Turn on the Host port power. */
    hpcs = USB_ReadHPCS(USBx);
    if(((hpcs & USBHS_HPCS_PPWR) == 0) && (state == 1))
    {
        hpcs |= USBHS_HPCS_PPWR;
        USB_WRITE_REG32(USBx->regs.HPCS, hpcs);
    }
    if(((hpcs & USBHS_HPCS_PPWR) != 0) && (state == 0))
    {
        hpcs &= (~USBHS_HPCS_PPWR);
        USB_WRITE_REG32(USBx->regs.HPCS, hpcs);
    }
    USB_BSP_mDelay(200);
}

/**
*\*\name    USB_EnableHostInt.
*\*\fun     Enables the Host mode interrupts.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS USB_EnableHostInt(USB_CORE_MODULE *USBx)
{
    USB_STS status = USB_OK;
    uint32_t ginten = 0;

    /* Disable all interrupts. */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTEN, 0);

    /* Clear any pending interrupts. */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, 0xFFFFFFFF);

    /* Enable the common interrupts */
    USB_EnableCommonInt(USBx);

    if(USBx->cfg.dma_enable == 0)
    {
        USB_SET_REG32_BIT(&USBx->regs.GCSR->GINTEN, USBHS_GINTEN_RXFNEIEN);
    }
    ginten |= (USBHS_GINTEN_PTNCIEN_ISOUTNCIEN
           | USBHS_GINTEN_HCHIEN 
           | USBHS_GINTEN_HPIEN
           | USBHS_GINTEN_DISCIEN
           | USBHS_GINTEN_SOFIEN);
    USB_SET_REG32_BIT(&USBx->regs.GCSR->GINTEN, ginten);

    return status;
}

/**
*\*\name    USB_InitFSLSPClkSel.
*\*\fun     Initializes the FSLSPClkSel field of the HCFG register on the PHY type.
*\*\param   USBx: selected device.
*\*\param   freq : clock frequency.
*\*\return  none.
*\*\
**/
void USB_InitFSLSPClkSel(USB_CORE_MODULE *USBx , uint8_t freq)
{
    uint32_t hcfg = 0;

    hcfg = USB_READ_REG32(&USBx->regs.HCSR->HCFG);
    hcfg &= (~(uint32_t)0x03);
    hcfg |= freq;

    USB_WRITE_REG32(&USBx->regs.HCSR->HCFG, hcfg);
}

/**
*\*\name    USB_ReadHPCS.
*\*\fun     Reads HPCS to modify later.
*\*\param   USBx: selected device.
*\*\return  HPCS value.
*\*\
**/
uint32_t USB_ReadHPCS(USB_CORE_MODULE *USBx)
{
    uint32_t hpcs;
    hpcs = USB_READ_REG32(USBx->regs.HPCS);
    hpcs &= ~(USBHS_HPCS_PEN | USBHS_HPCS_PCDET | USBHS_HPCS_PENC | USBHS_HPCS_POCC);
    return hpcs;
}

/**
*\*\name    USB_ReadHostAllChannels_intr.
*\*\fun     Register PCD Callbacks.
*\*\param   USBx: selected device.
*\*\return  Status.
*\*\
**/
uint32_t USB_ReadHostAllChannels_intr(USB_CORE_MODULE *USBx)
{
    return (USB_READ_REG32(&USBx->regs.HCSR->HACHINT));
}

/**
*\*\name    USB_ResetPort.
*\*\fun     Reset Host Port.
*\*\param   USBx: selected device.
*\*\return  Status.
*\*\
**/
uint32_t USB_ResetPort(USB_CORE_MODULE *USBx)
{
    uint32_t  hpcs = 0;

    hpcs = USB_ReadHPCS(USBx);
    hpcs |= USBHS_HPCS_PRST;
    USB_WRITE_REG32(USBx->regs.HPCS, hpcs);
    USB_BSP_mDelay(100);
    hpcs &= (~USBHS_HPCS_PRST);
    USB_WRITE_REG32(USBx->regs.HPCS, hpcs);
    USB_BSP_mDelay(20);
    return 1;
}

/**
*\*\name    USB_HCH_Init.
*\*\fun     Prepares a host channel for transferring packets.
*\*\param   USBx: selected device.
*\*\param   hch_num: channel number.
*\*\return  status.
*\*\
**/
USB_STS USB_HCH_Init(USB_CORE_MODULE *USBx , uint8_t hch_num)
{
    USB_STS status = USB_OK;
    uint32_t intr_enable = 0;
    uint32_t hchinten = 0;
    uint32_t hchctrl = 0;

    /* Clear old interrupt conditions for this host channel. */
    USB_WRITE_REG32(&USBx->regs.HCHCSR[hch_num]->HCHINTSTS, 0xFFFFFFFF);

    /* Enable channel interrupts required for this transfer. */

    if (USBx->cfg.dma_enable == 1)
    {
        hchinten |= USBHS_HCHINTEN_AHBERRIEN; 
    }

    switch (USBx->host.hch[hch_num].ep_type)
    {
        case EP_TYPE_CTRL:
        case EP_TYPE_BULK:
        hchinten |= USBHS_HCHINTEN_TXCIEN;
        hchinten |= USBHS_HCHINTEN_STALLIEN;
        hchinten |= USBHS_HCHINTEN_TXERRIEN;
        hchinten |= USBHS_HCHINTEN_DTERRIEN;
        hchinten |= USBHS_HCHINTEN_NAKIEN;

        if (USBx->host.hch[hch_num].ep_is_in)
        {
            hchinten |= USBHS_HCHINTEN_BBERRIEN;
        }
        else
        {
            hchinten |= USBHS_HCHINTEN_NYETIEN;
            if (USBx->host.hch[hch_num].do_ping)
            {
                hchinten |= USBHS_HCHINTEN_ACKIEN;
            }
        }
        break;
        case EP_TYPE_INTR:
        hchinten |= USBHS_HCHINTEN_TXCIEN;
        hchinten |= USBHS_HCHINTEN_NAKIEN;
        hchinten |= USBHS_HCHINTEN_STALLIEN;
        hchinten |= USBHS_HCHINTEN_TXERRIEN;
        hchinten |= USBHS_HCHINTEN_DTERRIEN;
        hchinten |= USBHS_HCHINTEN_FOVRIEN;

        if (USBx->host.hch[hch_num].ep_is_in)
        {
            hchinten |= USBHS_HCHINTEN_BBERRIEN;
        }

        break;
        case EP_TYPE_ISOC:
        hchinten |= USBHS_HCHINTEN_TXCIEN;
        hchinten |= USBHS_HCHINTEN_FOVRIEN;
        hchinten |= USBHS_HCHINTEN_ACKIEN;

        if (USBx->host.hch[hch_num].ep_is_in)
        {
            hchinten |= USBHS_HCHINTEN_TXERRIEN;
            hchinten |= USBHS_HCHINTEN_BBERRIEN;
        }
        break;
    }
    USB_WRITE_REG32(&USBx->regs.HCHCSR[hch_num]->HCHINTEN, hchinten);

    /* Enable the top level host channel interrupt. */
    intr_enable = (1 << hch_num);
    USB_MODIFY_REG32(&USBx->regs.HCSR->HACHINTEN, 0, intr_enable);

    /* Make sure host channel interrupts are enabled. */
    USB_SET_REG32_BIT(&USBx->regs.GCSR->GINTEN, USBHS_GINTEN_HCHIEN);

    /* Program the HCHCTRL register */
    hchctrl |= ((uint32_t)(USBx->host.hch[hch_num].dev_addr)   << USBHS_HCHCTRL_DEVADDR_POS);
    hchctrl |= ((uint32_t)(USBx->host.hch[hch_num].ep_num)     << USBHS_HCHCTRL_EPNUM_POS);
    hchctrl |= ((uint32_t)(USBx->host.hch[hch_num].ep_is_in)   << USBHS_HCHCTRL_EPDIR_POS);
    hchctrl |= ((uint32_t)(USBx->host.hch[hch_num].ep_type)    << USBHS_HCHCTRL_EPTYPE_POS);
    hchctrl |= ((uint32_t)(USBx->host.hch[hch_num].max_packet) << USBHS_HCHCTRL_MPS_POS);
    if(USBx->host.hch[hch_num].speed == HPCS_PRTSPD_LOW_SPEED)
    {
        hchctrl |= USBHS_HCHCTRL_LSPDDEV;
    }
    if (USBx->host.hch[hch_num].ep_type == HCHCTRL_INTR)
    {
        hchctrl |= USBHS_HCHCTRL_ODDFRM;
    }
    USB_WRITE_REG32(&USBx->regs.HCHCSR[hch_num]->HCHCTRL, hchctrl);
    return status;
}


/**
*\*\name    USB_HCH_StartXfer.
*\*\fun     Start transfer.
*\*\param   USBx: selected device.
*\*\param   hch_num: channel number.
*\*\return  status.
*\*\
**/
USB_STS USB_HCH_StartXfer(USB_CORE_MODULE *USBx , uint8_t hch_num)
{
    USB_STS status = USB_OK;

    uint16_t len_words = 0;
    uint16_t num_packets = 0;
    uint16_t max_hch_pkt_count = 0;

    uint32_t hchtxsiz = 0;
    uint32_t hchctrl = 0;
    uint32_t gnptxfsts = 0;
    uint32_t hptxfqsts = 0;

    max_hch_pkt_count = 256;


    /* Compute the expected number of packets associated to the transfer */
    if(USBx->host.hch[hch_num].xfer_len > 0)
    {
        num_packets = (USBx->host.hch[hch_num].xfer_len + USBx->host.hch[hch_num].max_packet - 1) / USBx->host.hch[hch_num].max_packet;

        if(num_packets > max_hch_pkt_count)
        {
            num_packets = max_hch_pkt_count;
            USBx->host.hch[hch_num].xfer_len = num_packets * USBx->host.hch[hch_num].max_packet;
        }
    }
    else
    {
        num_packets = 1;
    }
    if(USBx->host.hch[hch_num].ep_is_in)
    {
        USBx->host.hch[hch_num].xfer_len = num_packets * USBx->host.hch[hch_num].max_packet;
    }
    /* Initialize the HCHTXSIZn register */
    hchtxsiz |= ((uint32_t)(USBx->host.hch[hch_num].xfer_len) << USBHS_HCHTXSIZ_TXSIZ_POS);
    hchtxsiz |= ((uint32_t)(num_packets) << USBHS_HCHTXSIZ_PKCNT_POS);
    hchtxsiz |= ((uint32_t)(USBx->host.hch[hch_num].data_pid) << USBHS_HCHTXSIZ_PID_POS);
    USB_WRITE_REG32(&USBx->regs.HCHCSR[hch_num]->HCHTXSIZ, hchtxsiz);

    if(USBx->cfg.dma_enable == 1)
    {
        USB_WRITE_REG32(&USBx->regs.HCHCSR[hch_num]->HCHDMADD, (unsigned int)USBx->host.hch[hch_num].xfer_buff);
    }

    hchctrl = USB_READ_REG32(&USBx->regs.HCHCSR[hch_num]->HCHCTRL);
    hchctrl &= (~USBHS_HCHCTRL_ODDFRM);
    hchctrl |= (USB_IsEvenFrame(USBx) << USBHS_HCHCTRL_ODDFRM_POS);

    /* Set host channel enable */
    hchctrl |= USBHS_HCHCTRL_CHEN;
    hchctrl &= (~USBHS_HCHCTRL_CHDIS);

    USB_WRITE_REG32(&USBx->regs.HCHCSR[hch_num]->HCHCTRL, hchctrl);

    if (USBx->cfg.dma_enable == 0) /* Slave mode */
    {
        if((USBx->host.hch[hch_num].ep_is_in == 0) &&
           (USBx->host.hch[hch_num].xfer_len > 0))
        {
            switch(USBx->host.hch[hch_num].ep_type)
            {
                /* Non periodic transfer */
                case EP_TYPE_CTRL:
                case EP_TYPE_BULK:
                    gnptxfsts = USB_READ_REG32(&USBx->regs.GCSR->GNPTXFSTS);
                    len_words = (USBx->host.hch[hch_num].xfer_len + 3) / 4;

                    /* check if there is enough space in FIFO space */
                    if(len_words > (gnptxfsts & USBHS_GNPTXFSTS_NPTXFSAV) >> USBHS_GNPTXFSTS_NPTXFSAV_POS)
                    {
                        /* need to process data in nptxfempty interrupt */
                        USB_SET_REG32_BIT(&USBx->regs.GCSR->GINTEN, USBHS_GINTEN_NPTXFEIEN);
                    }
                break;
                /* Periodic transfer */
                case EP_TYPE_INTR:
                case EP_TYPE_ISOC:
                    hptxfqsts = USB_READ_REG32(&USBx->regs.HCSR->HPTXFQSTS);
                    len_words = (USBx->host.hch[hch_num].xfer_len + 3) / 4;
                    /* check if there is enough space in FIFO space */
                    if(len_words > (hptxfqsts & USBHS_HPTXFQSTS_PTXFSAVL) >> USBHS_HPTXFQSTS_PTXFSAVL_POS) /* split the transfer */
                    {
                        /* need to process data in ptxfempty interrupt */
                        USB_SET_REG32_BIT(&USBx->regs.GCSR->GINTEN, USBHS_GINTEN_PTXFEIEN);
                    }
                break;

                default:
                break;
            }
            /* Write packet into the Tx FIFO. */
            USB_WritePacket(USBx, USBx->host.hch[hch_num].xfer_buff, hch_num, USBx->host.hch[hch_num].xfer_len);
        }
    }
    return status;
}



/**
*\*\name    USB_HCH_Halt.
*\*\fun     Halt channel.
*\*\param   USBx: selected device.
*\*\param   hch_num: channel number.
*\*\return  status.
*\*\
**/
USB_STS USB_HCH_Halt(USB_CORE_MODULE *USBx , uint8_t hch_num)
{
    USB_STS status = USB_OK;

    uint32_t gnptxfsts = 0;
    uint32_t hptxfqsts = 0;
    uint32_t hchctrl = 0;

    hchctrl = USB_READ_REG32(&USBx->regs.HCHCSR[hch_num]->HCHCTRL);

    hchctrl |= USBHS_HCHCTRL_CHDIS;

    /* Check for space in the request queue to issue the halt. */
    if(((hchctrl & USBHS_HCHCTRL_EPTYPE) >> USBHS_HCHCTRL_EPTYPE_POS) == HCHCTRL_CTRL 
    || ((hchctrl & USBHS_HCHCTRL_EPTYPE) >> USBHS_HCHCTRL_EPTYPE_POS) == HCHCTRL_BULK)
    {
        gnptxfsts = USB_READ_REG32(&USBx->regs.GCSR->GNPTXFSTS);
        if(((gnptxfsts & USBHS_GNPTXFSTS_NPTXRQSAV) >> USBHS_GNPTXFSTS_NPTXRQSAV_POS) == 0)
        {
            hchctrl &= (~USBHS_HCHCTRL_CHEN);
            USB_WRITE_REG32(&USBx->regs.HCHCSR[hch_num]->HCHCTRL, hchctrl);
        }
    }
    else
    {
        hptxfqsts = USB_READ_REG32(&USBx->regs.HCSR->HPTXFQSTS);
        if(((hptxfqsts & USBHS_HPTXFQSTS_PTXRQSAV) >> USBHS_HPTXFQSTS_PTXRQSAV_POS) == 0)
        {
            hchctrl &= (~USBHS_HCHCTRL_CHEN);
            USB_WRITE_REG32(&USBx->regs.HCHCSR[hch_num]->HCHCTRL, hchctrl);
        }
    }
    hchctrl |= USBHS_HCHCTRL_CHEN;
    USB_WRITE_REG32(&USBx->regs.HCHCSR[hch_num]->HCHCTRL, hchctrl);
    return status;
}


/**
*\*\name    USB_HCH_DoPing.
*\*\fun     Issue a ping token.
*\*\param   USBx: selected device.
*\*\param   hch_num: channel number.
*\*\return  status.
*\*\
**/
USB_STS USB_HCH_DoPing(USB_CORE_MODULE *USBx , uint8_t hch_num)
{
    USB_STS status = USB_OK;
    uint32_t hchctrl = 0;
    uint32_t hchtxsiz = 0;

    hchtxsiz |= USBHS_HCHCTRL_DPING;
    hchtxsiz |= 1 << USBHS_HCHTXSIZ_PKCNT_POS;
    USB_WRITE_REG32(&USBx->regs.HCHCSR[hch_num]->HCHTXSIZ, hchtxsiz);

    hchctrl = USB_READ_REG32(&USBx->regs.HCHCSR[hch_num]->HCHCTRL);
    hchctrl |= USBHS_HCHCTRL_CHEN;
    hchctrl &= (~USBHS_HCHCTRL_CHDIS);
    USB_WRITE_REG32(&USBx->regs.HCHCSR[hch_num]->HCHCTRL, hchctrl);
    return status;
}

/**
*\*\name    USB_StopHost.
*\*\fun     Stop the device and clean up fifo's.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USB_StopHost(USB_CORE_MODULE *USBx)
{
    uint32_t i = 0;
    uint32_t hchctrl = 0;

    USB_WRITE_REG32(&USBx->regs.HCSR->HACHINTEN, 0);
    USB_WRITE_REG32(&USBx->regs.HCSR->HACHINT, 0xFFFFFFFF);
    /* Flush out any leftover queued requests. */
    for (i = 0; i < USBx->cfg.host_channels_num; i++)
    {
        hchctrl = USB_READ_REG32(&USBx->regs.HCHCSR[i]->HCHCTRL);
        hchctrl &= (~USBHS_HCHCTRL_CHEN);
        hchctrl |= USBHS_HCHCTRL_CHDIS;
        hchctrl &= (~USBHS_HCHCTRL_EPDIR);
        USB_WRITE_REG32(&USBx->regs.HCHCSR[i]->HCHCTRL, hchctrl);
    }
    /* Flush the FIFO */
    USB_FlushRxFifo(USBx);
    USB_FlushTxFifo(USBx, 0x10);
}
#endif
#ifdef USE_DEVICE_MODE

/**
*\*\name    USB_InitDevSpeed.
*\*\fun     Initializes the DevSpd field of DCFG register depending the PHY type and the enumeration speed of the device.
*\*\param   USBx: selected device.
*\*\param   speed: device speed.
*\*\return  none.
*\*\
**/
void USB_InitDevSpeed(USB_CORE_MODULE *USBx , uint8_t speed)
{
    uint32_t dcfg = 0;

    dcfg = USB_READ_REG32(&USBx->regs.DCSR->DCFG);
    dcfg &= (~USBHS_DCFG_DEVSPD);
    dcfg |= speed;
    USB_WRITE_REG32(&USBx->regs.DCSR->DCFG, dcfg);
}


/**
*\*\name    USB_DevHSFifoConfig.
*\*\fun     Initializes device fifo.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
static void USB_DevHSFifoConfig(USB_CORE_MODULE *USBx)
{
    uint32_t StardAddr = RX_FIFO_HS_SIZE;
    /* set Rx FIFO size */
    USB_WRITE_REG32(&USBx->regs.GCSR->GRXFSIZ, RX_FIFO_HS_SIZE);

    /* EP0 TX*/
    USB_WRITE_REG32(&USBx->regs.GCSR->GNPTXFSIZ_DINEP0TXFSIZ, 
                  (RX_FIFO_HS_SIZE << USBHS_DINEP0TXSIZ_IEP0TXFRSADD_POS) | (TX0_FIFO_HS_SIZE << USBHS_DINEP0TXSIZ_NPTXFDEP_POS));

    /* EP1 TX*/
    StardAddr += TX0_FIFO_HS_SIZE;
    USB_WRITE_REG32(&USBx->regs.GCSR->DINEPPTXFSIZ[0],
                  (StardAddr << USBHS_DINEP0TXSIZ_IEP0TXFRSADD_POS) | (TX1_FIFO_HS_SIZE << USBHS_DINEP0TXSIZ_NPTXFDEP_POS));

    /* EP2 TX*/
    StardAddr += TX1_FIFO_HS_SIZE;
    USB_WRITE_REG32(&USBx->regs.GCSR->DINEPPTXFSIZ[1],
                  (StardAddr << USBHS_DINEP0TXSIZ_IEP0TXFRSADD_POS) | (TX2_FIFO_HS_SIZE << USBHS_DINEP0TXSIZ_NPTXFDEP_POS));

    /* EP3 TX*/
    StardAddr += TX2_FIFO_HS_SIZE;
    USB_WRITE_REG32(&USBx->regs.GCSR->DINEPPTXFSIZ[2],
                  (StardAddr << USBHS_DINEP0TXSIZ_IEP0TXFRSADD_POS) | (TX3_FIFO_HS_SIZE << USBHS_DINEP0TXSIZ_NPTXFDEP_POS));

    /* EP4 TX*/
    StardAddr += TX3_FIFO_HS_SIZE;
    USB_WRITE_REG32(&USBx->regs.GCSR->DINEPPTXFSIZ[3],
                  (StardAddr << USBHS_DINEP0TXSIZ_IEP0TXFRSADD_POS) | (TX4_FIFO_HS_SIZE << USBHS_DINEP0TXSIZ_NPTXFDEP_POS));

    /* EP5 TX*/
    StardAddr += TX4_FIFO_HS_SIZE;
    USB_WRITE_REG32(&USBx->regs.GCSR->DINEPPTXFSIZ[4],
                  (StardAddr << USBHS_DINEP0TXSIZ_IEP0TXFRSADD_POS) | (TX5_FIFO_HS_SIZE << USBHS_DINEP0TXSIZ_NPTXFDEP_POS));

    /* EP6 TX*/
    StardAddr += TX5_FIFO_HS_SIZE;
    USB_WRITE_REG32(&USBx->regs.GCSR->DINEPPTXFSIZ[5],
                  (StardAddr << USBHS_DINEP0TXSIZ_IEP0TXFRSADD_POS) | (TX6_FIFO_HS_SIZE << USBHS_DINEP0TXSIZ_NPTXFDEP_POS));

    /* EP7 TX*/
    StardAddr += TX6_FIFO_HS_SIZE;
    USB_WRITE_REG32(&USBx->regs.GCSR->DINEPPTXFSIZ[6],
                  (StardAddr << USBHS_DINEP0TXSIZ_IEP0TXFRSADD_POS) | (TX7_FIFO_HS_SIZE << USBHS_DINEP0TXSIZ_NPTXFDEP_POS));

    /* EP8 TX*/
    StardAddr += TX7_FIFO_HS_SIZE;
    USB_WRITE_REG32(&USBx->regs.GCSR->DINEPPTXFSIZ[7],
                  (StardAddr << USBHS_DINEP0TXSIZ_IEP0TXFRSADD_POS) | (TX8_FIFO_HS_SIZE << USBHS_DINEP0TXSIZ_NPTXFDEP_POS));
}


/**
*\*\name    USB_CoreInitDev.
*\*\fun     Initializes the USBHS controller registers for device mode.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS USB_CoreInitDev (USB_CORE_MODULE *USBx)
{
    USB_STS status = USB_OK;
    uint32_t i=0;
    uint32_t dinepctrl;
    uint32_t doutepctrl;
    uint32_t dinepinten;
    uint32_t dthrctrl;

    /* Restart the Phy Clock */
    USB_WRITE_REG32(USBx->regs.PWRCTRL, 0);
    /* Device configuration register */
    USB_MODIFY_REG32(&USBx->regs.DCSR->DCFG, USBHS_DCFG_PFRITVL, DCFG_FRAME_INTERVAL_80 << USBHS_DCFG_PFRITVL_POS);
    
#ifdef USE_USB_HS_IN_HS
    /* Set High speed phy */
    USB_InitDevSpeed(USBx , USB_SPEED_PARAM_HIGH);
#else
    /* set High speed phy in Full speed mode */
    USB_InitDevSpeed(USBx , USB_SPEED_PARAM_HIGH_IN_FULL);
#endif

    USB_DevHSFifoConfig(USBx);

    /* Flush the FIFOs */
    USB_FlushTxFifo(USBx , 0x10); /* all Tx FIFOs */
    USB_FlushRxFifo(USBx);
    /* Clear all pending Device Interrupts */
    USB_WRITE_REG32(&USBx->regs.DCSR->DINEPINTEN, 0U);
    USB_WRITE_REG32(&USBx->regs.DCSR->DOUTEPINTEN, 0U);
    USB_WRITE_REG32(&USBx->regs.DCSR->DAEPINTSTS, 0xFFFFFFFFU);
    USB_WRITE_REG32(&USBx->regs.DCSR->DAEPINTEN, 0U);

    for(i=0; i<USBx->cfg.dev_endpoints_num; i++)
    {
        dinepctrl = USB_READ_REG32_BIT(&USBx->regs.INEPCSR[i]->DINEPCTRL, USBHS_DINEPCTRL_EPEN);
        if(dinepctrl)
        {
            dinepctrl = 0;
            dinepctrl |= (USBHS_DINEPCTRL_EPDIS | USBHS_DINEPCTRL_SNAK);
        }
        else
        {
            dinepctrl= 0;
        }
        USB_WRITE_REG32(&USBx->regs.INEPCSR[i]->DINEPCTRL, dinepctrl);
        USB_WRITE_REG32(&USBx->regs.INEPCSR[i]->DINEPTXSIZ, 0U);
        USB_WRITE_REG32(&USBx->regs.INEPCSR[i]->DINEPINTSTS, 0xFFU);
    }
    for(i=0; i<USBx->cfg.dev_endpoints_num; i++)
    {
        doutepctrl = USB_READ_REG32_BIT(&USBx->regs.OUTEPCSR[i]->DOUTEPCTRL, USBHS_DOUTEPCTRL_EPEN);
        if(doutepctrl)
        {
            doutepctrl = 0;
            doutepctrl |= (USBHS_DOUTEPCTRL_EPDIS | USBHS_DOUTEPCTRL_SNAK);
        }
        else
        {
            doutepctrl = 0;
        }
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[i]->DOUTEPCTRL, doutepctrl);
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[i]->DOUTEPTXSIZ, 0U);
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[i]->DOUTEPINTSTS, 0xFFU);
    }
    dinepinten = 0;
    dinepinten |= USBHS_DINEPINTEN_TXFUDIEN;
    USB_MODIFY_REG32(&USBx->regs.DCSR->DINEPINTEN, dinepinten, dinepinten);

    if (USBx->cfg.dma_enable == 1)
    {
        dthrctrl = 0;
        dthrctrl |= USBHS_DTHRCTRL_NISOINEPTHREN;
        dthrctrl |= USBHS_DTHRCTRL_ISOINEPTHREN;
        dthrctrl |= 64 << USBHS_DTHRCTRL_TXTHRLEN_POS;
        dthrctrl |= USBHS_DTHRCTRL_RXTHREN;
        dthrctrl |= 64 << USBHS_DTHRCTRL_RXTHRLEN_POS;
        USB_WRITE_REG32(&USBx->regs.DCSR->DTHRCTRL, dthrctrl);
    }
    USBDEV_DevConnect(USBx);
    USB_EnableDevInt(USBx);
    return status;
}

/**
*\*\name    USB_EnableDevInt.
*\*\fun     Enables the Device mode interrupts.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS USB_EnableDevInt(USB_CORE_MODULE *USBx)
{
    USB_STS status = USB_OK;
    uint32_t ginten = 0;

    /* Disable all interrupts. */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTEN, 0U);
    /* Clear any pending interrupts */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, 0xBFFFFFFFU);
    /* Enable the common interrupts */
    USB_EnableCommonInt(USBx);

    if (USBx->cfg.dma_enable == 0)
    {
        ginten |= USBHS_GINTEN_RXFNEIEN;
    }
#ifdef USB_DEDICATED_EP_ENABLED
    /* Enable interrupts matching to the Device mode ONLY */
    ginten |= USBHS_GINTEN_USBSUSPIEN | USBHS_GINTEN_USBRSTIEN | USBHS_GINTEN_ENUMDIEN
           | USBHS_GINTEN_SOFIEN
           | USBHS_GINTEN_ISOINCIEN | USBHS_GINTEN_PTNCIEN_ISOUTNCIEN;
#else
    /* Enable interrupts matching to the Device mode ONLY */
    ginten |= USBHS_GINTEN_USBSUSPIEN | USBHS_GINTEN_USBRSTIEN | USBHS_GINTEN_ENUMDIEN
           | USBHS_GINTEN_INEPIEN | USBHS_GINTEN_OUTEPIEN | USBHS_GINTEN_SOFIEN
           | USBHS_GINTEN_ISOINCIEN | USBHS_GINTEN_PTNCIEN_ISOUTNCIEN;
#endif
    
    USB_MODIFY_REG32(&USBx->regs.GCSR->GINTEN, ginten, ginten);
    return status;
}



/**
*\*\name    USB_GetDeviceSpeed.
*\*\fun     Get the device speed from the device status register.
*\*\param   USBx: selected device.
*\*\return  speed.
*\*\
**/
enum USB_SPEED USB_GetDeviceSpeed (USB_CORE_MODULE *USBx)
{
    enum USB_SPEED speed = USB_SPEED_UNKNOWN;
    uint32_t dsts = 0;

    dsts = USB_READ_REG32(&USBx->regs.DCSR->DSTS);

    switch ((dsts & USBHS_DSTS_ENUMSPD) >> USBHS_DSTS_ENUMSPD_POS)
    {
        case DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ:
            speed = USB_SPEED_HIGH;
        break;
        case DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ:
            speed = USB_SPEED_FULL;
        break;
        case DSTS_ENUMSPD_LS_PHY_6MHZ:
            speed = USB_SPEED_LOW;
        break;

        default:
            speed = USB_SPEED_FULL;
        break;
    }
    return speed;
}

/**
*\*\name    USB_EP0Activate.
*\*\fun     enables EP0 OUT to receive SETUP packets and configures EP0 for transmitting packets.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS  USB_EP0Activate(USB_CORE_MODULE *USBx)
{
    USB_STS status = USB_OK;
    uint32_t dsts;
    uint32_t dinepctrl;

    /* Read the Device Status and Endpoint 0 Control registers */
    dsts = USB_READ_REG32(&USBx->regs.DCSR->DSTS);
    dinepctrl = USB_READ_REG32(&USBx->regs.INEPCSR[0]->DINEPCTRL);
    dinepctrl &= (~USBHS_DINEP0CTRL_MPLEN);
    /* Set the MPS of the IN EP based on the enumeration speed */
    switch ((dsts & USBHS_DSTS_ENUMSPD) >> USBHS_DSTS_ENUMSPD_POS)
    {
        case DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ:
        case DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ:
            dinepctrl |= (DEP0CTRL_MPS_64 << USBHS_DINEP0CTRL_MPLEN_POS);
        break;
        case DSTS_ENUMSPD_LS_PHY_6MHZ:
            dinepctrl |= (DEP0CTRL_MPS_8 << USBHS_DINEP0CTRL_MPLEN_POS);
        break;

        default:
            dinepctrl |= (DEP0CTRL_MPS_64 << USBHS_DINEP0CTRL_MPLEN_POS);
        break;
    }
    USB_WRITE_REG32(&USBx->regs.INEPCSR[0]->DINEPCTRL, dinepctrl);
    USB_MODIFY_REG32(&USBx->regs.DCSR->DCTRL, USBHS_DCTRL_CGNPINAK, USBHS_DCTRL_CGNPINAK);
    return status;
}


/**
*\*\name    USB_EPActivate.
*\*\fun     Activates an EP.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS USB_EPActivate(USB_CORE_MODULE *USBx, USB_EP *ep)
{
    USB_STS status = USB_OK;
    __IO uint32_t *addr;

    uint32_t depctrl;
    uint32_t depinten;

    /* Read DEPCTRLn register */
    if (ep->is_in == 1)
    {
        addr = &USBx->regs.INEPCSR[ep->num]->DINEPCTRL;
        depinten = (1 << ep->num) << USBHS_DEEPINTEN_INEPIEN_POS;
    }
    else
    {
        addr = &USBx->regs.OUTEPCSR[ep->num]->DOUTEPCTRL;
        depinten = (1 << ep->num) << USBHS_DEEPINTEN_OUTEPIEN_POS;
    }
    /* If the EP is already active don't change the EP Control
    * register. */
    depctrl = USB_READ_REG32(addr);
    if (!(depctrl & USBHS_DINEPCTRL_EPACT))
    {
        depctrl |= ep->maxpacket << USBHS_DINEPCTRL_MPLEN_POS;
        depctrl |= ep->type << USBHS_DINEPCTRL_EPTYPE_POS;
        depctrl |= ep->tx_fifo_num << USBHS_DINEPCTRL_TXFNUM_POS;
        depctrl |= USBHS_DINEPCTRL_SD0PID_SEVNFRM;
        depctrl |= USBHS_DINEPCTRL_EPACT;

        USB_WRITE_REG32(addr, depctrl);
    }
#ifdef USB_DEDICATED_EP_ENABLED
    USB_SET_REG32_BIT(&USBx->regs.DCSR->DEEPINTEN, depinten);
#else
    /* Enable the Interrupt for this EP */
    USB_SET_REG32_BIT(&USBx->regs.DCSR->DAEPINTEN, depinten);
#endif
    return status;
}


/**
*\*\name    USB_EPDeactivate.
*\*\fun     Deactivates an EP.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS USB_EPDeactivate(USB_CORE_MODULE *USBx , USB_EP *ep)
{
    USB_STS status = USB_OK;
    uint32_t depctrl = 0;

    /* Read DEPCTRLn register and Disable the IN endpoint*/
    if(ep->is_in == 1)
    {
        depctrl = USB_READ_REG32(&USBx->regs.INEPCSR[ep->num]->DINEPCTRL);
        if(depctrl & USBHS_DINEPCTRL_EPEN)
        {
            depctrl = 0;
            depctrl |= USBHS_DINEPCTRL_EPDIS;
            depctrl |= USBHS_DINEPCTRL_SNAK;
        }
        else
        {
            depctrl = 0;
        }
        USB_WRITE_REG32(&USBx->regs.INEPCSR[ep->num]->DINEPCTRL, depctrl);
    }
    else  /* Disable the OUT endpoint */
    {
        depctrl = USB_READ_REG32(&USBx->regs.OUTEPCSR[ep->num]->DOUTEPCTRL);
        if(depctrl & USBHS_DOUTEPCTRL_EPEN)
        {
            depctrl = 0;
            depctrl |= USBHS_DOUTEPCTRL_EPDIS;
            depctrl |= USBHS_DOUTEPCTRL_SNAK;
        }
        else
        {
            depctrl = 0;
        }
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[ep->num]->DOUTEPCTRL, depctrl);
    }
    return status;
}


/**
*\*\name    USB_EPStartXfer.
*\*\fun     Handle the setup for data xfer for an EP and starts the xfer.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS USB_EPStartXfer(USB_CORE_MODULE *USBx, USB_EP *ep)
{
    USB_STS status = USB_OK;
    uint32_t fifoemptymsk = 0;
    uint32_t dinepctrl, doutepctrl;
    uint32_t dineptxsiz, douteptxsiz;
    uint32_t dsts = 0;

    /* IN endpoint */
    if(ep->is_in == 1)
    {
        dinepctrl = USB_READ_REG32(&USBx->regs.INEPCSR[ep->num]->DINEPCTRL);
        dineptxsiz = USB_READ_REG32(&USBx->regs.INEPCSR[ep->num]->DINEPTXSIZ);
        /* Zero Length Packet */
        if (ep->xfer_len == 0)
        {
            dineptxsiz = 1 << USBHS_DINEPTXSIZ_PKTCNT_POS;
            dineptxsiz |= 1 << USBHS_DINEPTXSIZ_MCNT_POS;
        }
        else
        {
            /* Program the transfer size and packet count
            * as follows: xfersize = N * maxpacket +
            * short_packet pktcnt = N + (short_packet
            * exist ? 1 : 0)
            */
            dineptxsiz &= (~USBHS_DINEPTXSIZ_TLEN) ;
            dineptxsiz |= ep->xfer_len << USBHS_DINEPTXSIZ_TLEN_POS;
            dineptxsiz &= (~USBHS_DINEPTXSIZ_PKTCNT) ;
            dineptxsiz |= ((ep->xfer_len - 1 + ep->maxpacket) / ep->maxpacket) << USBHS_DINEPTXSIZ_PKTCNT_POS;
            if (ep->type == EP_TYPE_ISOC)
            {
                dineptxsiz &= (~USBHS_DINEPTXSIZ_MCNT) ;
                dineptxsiz |= 1 << USBHS_DINEPTXSIZ_MCNT_POS;
            }
            else if (ep->type == EP_TYPE_INTR)
            {
                dineptxsiz &= (~USBHS_DINEPTXSIZ_MCNT) ;
                if(((ep->xfer_len - 1 + ep->maxpacket) / ep->maxpacket) <=3)
                {
                    dineptxsiz |= ((ep->xfer_len - 1 + ep->maxpacket) / ep->maxpacket) << USBHS_DINEPTXSIZ_MCNT_POS;
                }
            }
        }
        USB_WRITE_REG32(&USBx->regs.INEPCSR[ep->num]->DINEPTXSIZ, dineptxsiz);

        if (USBx->cfg.dma_enable == 1)
        {
            USB_WRITE_REG32(&USBx->regs.INEPCSR[ep->num]->DINEPDMADD, ep->dma_addr);
        }
        else
        {
            if (ep->type != EP_TYPE_ISOC)
            {
                /* Enable the Tx FIFO Empty Interrupt for this EP */
                if (ep->xfer_len > 0)
                {
                    fifoemptymsk = 1 << ep->num;
                    USB_SET_REG32_BIT(&USBx->regs.DCSR->DINEPFEINTEN, fifoemptymsk);
                }
            }
        }
        if (ep->type == EP_TYPE_ISOC)
        {
            dsts = USB_READ_REG32(&USBx->regs.DCSR->DSTS);
            if ((((dsts & USBHS_DSTS_SOFFN)>>USBHS_DSTS_SOFFN_POS) & 0x1) == 0)
            {
                dinepctrl |= USBHS_DINEPCTRL_SD1PID_SODDFRM;
            }
            else
            {
                dinepctrl |= USBHS_DINEPCTRL_SD0PID_SEVNFRM;
            }
        }

        /* EP enable, IN data in FIFO */
        dinepctrl |= USBHS_DINEPCTRL_CNAK;
        dinepctrl |= USBHS_DINEPCTRL_EPEN;

        USB_WRITE_REG32(&USBx->regs.INEPCSR[ep->num]->DINEPCTRL, dinepctrl);

        if (ep->type == EP_TYPE_ISOC)
        {
            USB_WritePacket(USBx, ep->xfer_buff, ep->num, ep->xfer_len);
        }
    }
    else
    {
        /* OUT endpoint */
        doutepctrl  = USB_READ_REG32((&USBx->regs.OUTEPCSR[ep->num]->DOUTEPCTRL));
        douteptxsiz = USB_READ_REG32((&USBx->regs.OUTEPCSR[ep->num]->DOUTEPTXSIZ));
        /* Program the transfer size and packet count as follows:
        * pktcnt = N
        * xfersize = N * maxpacket
        */
        if (ep->xfer_len == 0)
        {
            douteptxsiz &= (~USBHS_DOUTEPTXSIZ_TLEN);
            douteptxsiz |= ep->maxpacket << USBHS_DOUTEPTXSIZ_TLEN_POS;
            douteptxsiz &= (~USBHS_DOUTEPTXSIZ_PKTCNT);
            douteptxsiz |= 1 << USBHS_DOUTEPTXSIZ_PKTCNT_POS;
        }
        else
        {
            douteptxsiz &= (~USBHS_DOUTEPTXSIZ_PKTCNT);
            douteptxsiz |= ((ep->xfer_len + (ep->maxpacket - 1)) / ep->maxpacket) << USBHS_DOUTEPTXSIZ_PKTCNT_POS;
            douteptxsiz &= (~USBHS_DOUTEPTXSIZ_TLEN);
            douteptxsiz |= (((douteptxsiz & USBHS_DOUTEPTXSIZ_PKTCNT) >> USBHS_DOUTEPTXSIZ_PKTCNT_POS) * ep->maxpacket);
            ep->xfer_len = (((douteptxsiz & USBHS_DOUTEPTXSIZ_PKTCNT) >> USBHS_DOUTEPTXSIZ_PKTCNT_POS) * ep->maxpacket);
        }
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[ep->num]->DOUTEPTXSIZ, douteptxsiz);

        if (USBx->cfg.dma_enable == 1)
        {
            USB_WRITE_REG32(&USBx->regs.OUTEPCSR[ep->num]->DOUTEPDMADD, ep->dma_addr);
        }

        if (ep->type == EP_TYPE_ISOC)
        {
            if (ep->even_odd_frame)
            {
                doutepctrl |= USBHS_DOUTEPCTRL_SD1PID_SODDFRM;
            }
            else
            {
                doutepctrl |= USBHS_DOUTEPCTRL_SD0PID_SEVNFRM;
            }
        }
        /* EP enable */
        doutepctrl |= (USBHS_DOUTEPCTRL_CNAK | USBHS_DOUTEPCTRL_EPEN);
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[ep->num]->DOUTEPCTRL, doutepctrl);
    }
    return status;
}


/**
*\*\name    USB_EP0StartXfer.
*\*\fun     Handle the setup for a data xfer for EP0 and starts the xfer.
*\*\param   USBx: selected device.
*\*\return  status.
*\*\
**/
USB_STS USB_EP0StartXfer(USB_CORE_MODULE *USBx , USB_EP *ep)
{
    USB_STS status = USB_OK;
    USB_INEP_Registers *in_regs;
    uint32_t fifoemptymsk = 0;
    uint32_t dinepctrl = 0, doutepctrl = 0;
    uint32_t dineptxsiz = 0, douteptxsiz = 0;

    /* IN endpoint */
    if(ep->is_in == 1)
    {
        in_regs = USBx->regs.INEPCSR[0];
        dinepctrl  = USB_READ_REG32(&in_regs->DINEPCTRL);
        dineptxsiz = USB_READ_REG32(&in_regs->DINEPTXSIZ);
        /* Zero Length Packet */
        if(ep->xfer_len == 0)
        {
            dineptxsiz &= (~USBHS_DINEP0TXSIZ_TLEN);
            dineptxsiz &= (~USBHS_DINEP0TXSIZ_PKTCNT);
            dineptxsiz |= 1 << USBHS_DINEP0TXSIZ_PKTCNT_POS;
        }
        else
        {
            if(ep->xfer_len > ep->maxpacket)
            {
                ep->xfer_len = ep->maxpacket;
                dineptxsiz &= (~USBHS_DINEP0TXSIZ_TLEN);
                dineptxsiz |= ep->maxpacket << USBHS_DINEP0TXSIZ_TLEN_POS;
            }
            else
            {
                dineptxsiz &= (~USBHS_DINEP0TXSIZ_TLEN);
                dineptxsiz |= ep->xfer_len << USBHS_DINEP0TXSIZ_TLEN_POS;
            }
            dineptxsiz &= (~USBHS_DINEP0TXSIZ_PKTCNT);
            dineptxsiz |= 1 << USBHS_DINEP0TXSIZ_PKTCNT_POS;
        }
        USB_WRITE_REG32(&in_regs->DINEPTXSIZ, dineptxsiz);

        if(USBx->cfg.dma_enable == 1)
        {
            USB_WRITE_REG32(&USBx->regs.INEPCSR[ep->num]->DINEPDMADD, ep->dma_addr);
        }

        /* EP enable, IN data in FIFO */
        dinepctrl |= ( USBHS_DINEP0CTRL_CNAK | USBHS_DINEP0CTRL_EPEN);
        USB_WRITE_REG32(&in_regs->DINEPCTRL, dinepctrl);

        if(USBx->cfg.dma_enable == 0)
        {
            /* Enable the Tx FIFO Empty Interrupt for this EP */
            if (ep->xfer_len > 0)
            {
                {
                    fifoemptymsk |= 1 << ep->num;
                    USB_MODIFY_REG32(&USBx->regs.DCSR->DINEPFEINTEN, 0, fifoemptymsk);
                }
            }
        }
    }
    else
    {
        /* OUT endpoint */
        doutepctrl  = USB_READ_REG32(&USBx->regs.OUTEPCSR[ep->num]->DOUTEPCTRL);
        douteptxsiz = USB_READ_REG32(&USBx->regs.OUTEPCSR[ep->num]->DOUTEPTXSIZ);
        /* Program the transfer size and packet count as follows:
        * xfersize = N * (maxpacket + 4 - (maxpacket % 4))
        * pktcnt = N           */
        if(ep->xfer_len == 0)
        {
            douteptxsiz &= (~USBHS_DOUTEP0TXSIZ_TLEN);
            douteptxsiz |= ep->maxpacket << USBHS_DOUTEP0TXSIZ_TLEN_POS;
            douteptxsiz &= (~USBHS_DOUTEP0TXSIZ_PKTCNT);
            douteptxsiz |= 1 << USBHS_DOUTEP0TXSIZ_PKTCNT_POS;
        }
        else
        {
            ep->xfer_len = ep->maxpacket;
            douteptxsiz &= (~USBHS_DOUTEP0TXSIZ_TLEN);
            douteptxsiz |= ep->maxpacket << USBHS_DOUTEP0TXSIZ_TLEN_POS;
            douteptxsiz &= (~USBHS_DOUTEP0TXSIZ_PKTCNT);
            douteptxsiz |= 1 << USBHS_DOUTEP0TXSIZ_PKTCNT_POS;
        }
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[ep->num]->DOUTEPTXSIZ, douteptxsiz);
        if(USBx->cfg.dma_enable == 1)
        {
            USB_WRITE_REG32(&USBx->regs.OUTEPCSR[ep->num]->DOUTEPDMADD, ep->dma_addr);
        }
        /* EP enable */
        doutepctrl |= (USBHS_DOUTEP0CTRL_CNAK | USBHS_DOUTEP0CTRL_EPEN);
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[ep->num]->DOUTEPCTRL, doutepctrl);
    }
    return status;
}



/**
*\*\name    USB_EPSetStall.
*\*\fun     Set the EP STALL.
*\*\param   USBx: selected device.
*\*\param   ep: endpoint instance
*\*\return  status.
*\*\
**/
USB_STS USB_EPSetStall(USB_CORE_MODULE *USBx , USB_EP *ep)
{
    USB_STS status = USB_OK;
    __IO uint32_t *depctrl_addr;
    uint32_t depctrl;

    if(ep->is_in == 1)
    {
        depctrl_addr = &(USBx->regs.INEPCSR[ep->num]->DINEPCTRL);
        depctrl = USB_READ_REG32(depctrl_addr);
        /* set the disable and stall bits */
        if (depctrl & USBHS_DINEPCTRL_EPEN)
        {
            depctrl |= USBHS_DINEPCTRL_EPDIS;
        }
        depctrl |= USBHS_DINEPCTRL_STALL;
        USB_WRITE_REG32(depctrl_addr, depctrl);
    }
    else
    {
        depctrl_addr = &(USBx->regs.OUTEPCSR[ep->num]->DOUTEPCTRL);
        depctrl = USB_READ_REG32(depctrl_addr);
        /* set the stall bit */
        depctrl |= USBHS_DOUTEPCTRL_STALL;
        USB_WRITE_REG32(depctrl_addr, depctrl);
    }
    return status;
}


/**
*\*\name    USB_EPClearStall.
*\*\fun     Clear the EP STALL.
*\*\param   USBx: selected device.
*\*\param   ep: endpoint instance
*\*\return  status.
*\*\
**/
USB_STS USB_EPClearStall(USB_CORE_MODULE *USBx , USB_EP *ep)
{
    USB_STS status = USB_OK;
    __IO uint32_t *depctrl_addr;
    uint32_t depctrl;


    if (ep->is_in == 1)
    {
        depctrl_addr = &(USBx->regs.INEPCSR[ep->num]->DINEPCTRL);
    }
    else
    {
        depctrl_addr = &(USBx->regs.OUTEPCSR[ep->num]->DOUTEPCTRL);
    }
    depctrl = USB_READ_REG32(depctrl_addr);
    /* clear the stall bits */
    depctrl &= (~USBHS_DINEPCTRL_STALL);
    if (ep->type == EP_TYPE_INTR || ep->type == EP_TYPE_BULK)
    {
        depctrl |= USBHS_DINEPCTRL_SD0PID_SEVNFRM;  /* DATA0 */
    }
    USB_WRITE_REG32(depctrl_addr, depctrl);
    return status;
}

/**
*\*\name    USB_ReadDevAllOutEp_itr.
*\*\fun     returns OUT endpoint interrupt bits.
*\*\param   USBx: selected device.
*\*\return  OUT endpoint interrupt bits.
*\*\
**/
uint32_t USB_ReadDevAllOutEp_itr(USB_CORE_MODULE *USBx)
{
    uint32_t v;
    v  = USB_READ_REG32(&USBx->regs.DCSR->DAEPINTSTS);
    v &= USB_READ_REG32(&USBx->regs.DCSR->DAEPINTEN);
    return ((v & 0xffff0000) >> 16);
}

/**
*\*\name    USB_ReadDevOutEP_itr.
*\*\fun     returns Device OUT EP Interrupt register.
*\*\param   USBx: selected device.
*\*\param   ep : end point number
*\*\return  Device OUT EP Interrupt register.
*\*\
**/
uint32_t USB_ReadDevOutEP_itr(USB_CORE_MODULE *USBx , uint8_t epnum)
{
    uint32_t v;
    v  = USB_READ_REG32(&USBx->regs.OUTEPCSR[epnum]->DOUTEPINTSTS);
    v &= USB_READ_REG32(&USBx->regs.DCSR->DOUTEPINTEN);
    return v;
}

/**
*\*\name    USB_ReadDevAllInEPItr.
*\*\fun     Get int status register.
*\*\param   USBx: selected device.
*\*\return  int status register.
*\*\
**/
uint32_t USB_ReadDevAllInEPItr(USB_CORE_MODULE *USBx)
{
    uint32_t v;
    v = USB_READ_REG32(&USBx->regs.DCSR->DAEPINTSTS);
    v &= USB_READ_REG32(&USBx->regs.DCSR->DAEPINTEN);
    return (v & 0xffff);
}

/**
*\*\name    USB_ReadDevEachInEPItr.
*\*\fun     Get int status register.
*\*\param   USBx: selected device.
*\*\return  int status register.
**/
uint32_t USB_ReadDevEachInEPItr(USB_CORE_MODULE *USBx)
{
    uint32_t v;
    v = USB_READ_REG32(&USBx->regs.DCSR->DEEPINTSTS);
    v = USB_READ_REG32(&USBx->regs.DCSR->DEEPINTEN);
    return (v & 0xFFFF);
}

/**
*\*\name    USB_ReadDevEachOutEPItr.
*\*\fun     Get int status register.
*\*\param   USBx: selected device.
*\*\return  int status register.
**/
uint32_t USB_ReadDevEachOutEPItr(USB_CORE_MODULE *USBx)
{
    uint32_t v;
    v = USB_READ_REG32(&USBx->regs.DCSR->DEEPINTSTS);
    v = USB_READ_REG32(&USBx->regs.DCSR->DEEPINTEN);
    return (v & 0xFFFF0000) >> 16;
}

/**
*\*\name    USB_EP0_OutStart.
*\*\fun     configures EP0 to receive SETUP packets.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USB_EP0_OutStart(USB_CORE_MODULE *USBx)
{
    uint32_t douteptxsiz = 0;
    uint32_t doutepctrl;

    douteptxsiz |= 3 << USBHS_DOUTEP0TXSIZ_STUPPCNT_POS;
    douteptxsiz |= 1 << USBHS_DOUTEP0TXSIZ_PKTCNT_POS;
    douteptxsiz |= 64 << USBHS_DOUTEP0TXSIZ_TLEN_POS;

    USB_WRITE_REG32(&USBx->regs.OUTEPCSR[0]->DOUTEPTXSIZ, douteptxsiz);

    if(USBx->cfg.dma_enable == 1)
    {
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[0]->DOUTEPDMADD, (uint32_t)&USBx->dev.setup_packet);

        /* EP enable */
        doutepctrl = (USBHS_DOUTEP0CTRL_EPEN | USBHS_DOUTEP0CTRL_EPACT);
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[0]->DOUTEPCTRL, doutepctrl);
    }
}


/**
*\*\name    USB_ActiveRemoteWakeup.
*\*\fun     active remote wakeup signalling.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USB_ActiveRemoteWakeup(USB_CORE_MODULE *USBx)
{
    uint32_t dsts;
    uint32_t pwrctrl;

    if(USBx->dev.DevRemoteWakeup)
    {
        dsts = USB_READ_REG32(&USBx->regs.DCSR->DSTS);
        if(dsts & USBHS_DSTS_SUSPF)
        {
            if(USBx->cfg.low_power)
            {
                /* un-gate USB Core clock */
                pwrctrl = USB_READ_REG32(USBx->regs.PWRCTRL);
                pwrctrl &= (~USBHS_PWRCTRL_GATEHCLK);
                pwrctrl &= (~USBHS_PWRCTRL_PHYSTP);
                USB_WRITE_REG32(USBx->regs.PWRCTRL, pwrctrl);
            }
            /* active Remote wakeup signaling */
            USB_SET_REG32_BIT(&USBx->regs.DCSR->DCTRL, USBHS_DCTRL_RMWKUP);
            USB_BSP_mDelay(5);
            USB_MODIFY_REG32(&USBx->regs.DCSR->DCTRL, USBHS_DCTRL_RMWKUP, 0);
        }
    }
}


/**
*\*\name    USB_UngateClock.
*\*\fun     active USB Core clock.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USB_UngateClock(USB_CORE_MODULE *USBx)
{
    uint32_t dsts;
    uint32_t pwrctrl;
    if(USBx->cfg.low_power)
    {
        dsts = USB_READ_REG32(&USBx->regs.DCSR->DSTS);

        if(dsts & USBHS_DSTS_SUSPF)
        {
            /* un-gate USB Core clock */
            pwrctrl = USB_READ_REG32(USBx->regs.PWRCTRL);
            pwrctrl &= (~USBHS_PWRCTRL_GATEHCLK);
            pwrctrl &= (~USBHS_PWRCTRL_PHYSTP);
            USB_WRITE_REG32(USBx->regs.PWRCTRL, pwrctrl);
        }
    }
}


/**
*\*\name    USB_StopDevice.
*\*\fun     Stop the device and clean up fifo's.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USB_StopDevice(USB_CORE_MODULE *USBx)
{
    uint32_t i;

    USBx->dev.device_status = 1;

    for (i = 0; i < USBx->cfg.dev_endpoints_num ; i++)
    {
        USB_WRITE_REG32(&USBx->regs.INEPCSR[i]->DINEPINTSTS, 0xFF);
        USB_WRITE_REG32(&USBx->regs.OUTEPCSR[i]->DOUTEPINTSTS, 0xFF);
    }

    USB_WRITE_REG32(&USBx->regs.DCSR->DINEPINTEN, 0);
    USB_WRITE_REG32(&USBx->regs.DCSR->DOUTEPINTEN, 0);
    USB_WRITE_REG32(&USBx->regs.DCSR->DAEPINTEN, 0);
    USB_WRITE_REG32(&USBx->regs.DCSR->DAEPINTSTS, 0xFFFFFFFF );

    /* Flush the FIFO */
    USB_FlushRxFifo(USBx);
    USB_FlushTxFifo(USBx, 0x10);
}


/**
*\*\name    USB_GetEPStatus.
*\*\fun     returns the EP Status.
*\*\param   USBx: selected device.
*\*\param   ep: endpoint instance.
*\*\return  EP status.
*\*\
**/
uint32_t USB_GetEPStatus(USB_CORE_MODULE *USBx, USB_EP *ep)
{
    __IO uint32_t *depctrl_addr;
    uint32_t Status = 0;
    uint32_t depctrl = 0;

    if(ep->is_in == 1)
    {
        depctrl_addr = &(USBx->regs.INEPCSR[ep->num]->DINEPCTRL);
        depctrl = USB_READ_REG32(depctrl_addr);

        if((depctrl & USBHS_DINEPCTRL_STALL) >> USBHS_DINEPCTRL_STALL_POS)
        {
            Status = USB_EP_TX_STALL;
        }
        else if((depctrl & USBHS_DINEPCTRL_NAKSTS) >> USBHS_DINEPCTRL_NAKSTS_POS)
        {
            Status = USB_EP_TX_NAK;
        }
        else
        {
            Status = USB_EP_TX_VALID;
        }
    }
    else
    {
        depctrl_addr = &(USBx->regs.OUTEPCSR[ep->num]->DOUTEPCTRL);
        depctrl = USB_READ_REG32(depctrl_addr);
        if((depctrl & USBHS_DOUTEPCTRL_STALL) >> USBHS_DOUTEPCTRL_STALL_POS)
        {
            Status = USB_EP_RX_STALL;
        }
        else if((depctrl & USBHS_DOUTEPCTRL_NAKSTS) >> USBHS_DOUTEPCTRL_NAKSTS_POS)
        {
            Status = USB_EP_RX_NAK;
        }
        else
        {
            Status = USB_EP_RX_VALID;
        }
    }
    /* Return the current status */
    return Status;
}


/**
*\*\name    USB_SetEPStatus.
*\*\fun     Set the EP Status.
*\*\param   USBx: selected device.
*\*\param   ep: endpoint instance.
*\*\param   Status : new Status
*\*\return  none.
*\*\
**/
void USB_SetEPStatus(USB_CORE_MODULE *USBx, USB_EP *ep, uint32_t Status)
{
    __IO uint32_t *depctrl_addr;
    uint32_t depctrl = 0;

    /* Process for IN endpoint */
    if(ep->is_in == 1)
    {
        depctrl_addr = &(USBx->regs.INEPCSR[ep->num]->DINEPCTRL);
        depctrl = USB_READ_REG32(depctrl_addr);

        if(Status == USB_EP_TX_STALL)
        {
            USB_EPSetStall(USBx, ep);
            return;
        }
        else if(Status == USB_EP_TX_NAK)
        {
            depctrl |= USBHS_DINEPCTRL_SNAK;
        }
        else if(Status == USB_EP_TX_VALID)
        {
            if ((depctrl & USBHS_DINEPCTRL_STALL) >> USBHS_DINEPCTRL_STALL_POS)
            {
                ep->even_odd_frame = 0;
                USB_EPClearStall(USBx, ep);
                return;
            }
            depctrl |= USBHS_DINEPCTRL_CNAK;
            depctrl |= USBHS_DINEPCTRL_EPACT;
            depctrl |= USBHS_DINEPCTRL_EPEN;
        }
        else if (Status == USB_EP_TX_DIS)
        {
            depctrl &= (~USBHS_DINEPCTRL_EPACT);
        }
        else
        {
            /* Do Nothing */
        }
    }
    else /* Process for OUT endpoint */
    {
        depctrl_addr = &(USBx->regs.OUTEPCSR[ep->num]->DOUTEPCTRL);
        depctrl = USB_READ_REG32(depctrl_addr);

        if(Status == USB_EP_RX_STALL)
        {
            depctrl |= USBHS_DOUTEPCTRL_STALL;
        }
        else if (Status == USB_EP_RX_NAK)
        {
            depctrl |= USBHS_DOUTEPCTRL_SNAK;
        }
        else if(Status == USB_EP_RX_VALID)
        {
            if((depctrl & USBHS_DOUTEPCTRL_STALL) >> USBHS_DOUTEPCTRL_STALL_POS)
            {
                ep->even_odd_frame = 0;
                USB_EPClearStall(USBx, ep);
                return;
            }
            depctrl |= USBHS_DOUTEPCTRL_CNAK;
            depctrl |= USBHS_DOUTEPCTRL_EPACT;
            depctrl |= USBHS_DOUTEPCTRL_EPEN;
        }
        else if (Status == USB_EP_RX_DIS)
        {
            depctrl &= (~USBHS_DOUTEPCTRL_EPACT);
        }
        else
        {
            /* Do Nothing */
        }
    }
    USB_WRITE_REG32(depctrl_addr, depctrl);
}

#endif
