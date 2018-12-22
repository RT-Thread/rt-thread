/*
 * File      : rthw.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include "synopsys_emac.h"

/* Global pointers on Tx and Rx descriptor used to track transmit and receive descriptors */
extern EMAC_DMADESCTypeDef  *DMATxDescToSet;
extern EMAC_DMADESCTypeDef  *DMARxDescToGet;

/**
  * Initializes the ETHERNET peripheral according to the specified
  */
rt_uint32_t EMAC_init(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t SystemCoreClock)
{
    rt_uint32_t  value = 0;

    /*-------------------------------- MAC Config ------------------------------*/
    /*---------------------- ETHERNET MACMIIAR Configuration -------------------*/
    /* Get the ETHERNET MACMIIAR value */
    value = ETHERNET_MAC->GAR;
    /* Clear CSR Clock Range CR[2:0] bits */
    value &= MACMIIAR_CR_MASK;

    /* Get hclk frequency value */
    /* Set CR bits depending on hclk value */
    if((SystemCoreClock >= 20000000)&&(SystemCoreClock < 35000000))
    {
        /* CSR Clock Range between 20-35 MHz */
        value |= (rt_uint32_t)EMAC_MACMIIAR_CR_Div16;
    }
    else if((SystemCoreClock >= 35000000)&&(SystemCoreClock < 60000000))
    {
        /* CSR Clock Range between 35-60 MHz */
        value |= (rt_uint32_t)EMAC_MACMIIAR_CR_Div26;
    }
    else if((SystemCoreClock >= 60000000)&&(SystemCoreClock <= 100000000))
    {
        /* CSR Clock Range between 60-100 MHz */
        value |= (rt_uint32_t)EMAC_MACMIIAR_CR_Div42;
    }
    else if((SystemCoreClock >= 100000000)&&(SystemCoreClock <= 150000000))
    {
        /* CSR Clock Range between 100-150 MHz */
        value |= (rt_uint32_t)EMAC_MACMIIAR_CR_Div62;
    }
    else if((SystemCoreClock >= 150000000)&&(SystemCoreClock <= 250000000))
    {
        /* CSR Clock Range between 150-250 MHz */
        value |= (rt_uint32_t)EMAC_MACMIIAR_CR_Div102;
    }
    else /* if((SystemCoreClock >= 250000000)&&(SystemCoreClock <= 300000000)) */
    {
        /* CSR Clock Range between 250-300 MHz */
        value |= (rt_uint32_t)EMAC_MACMIIAR_CR_Div122;
    }
    /* Write to ETHERNET MAC MIIAR: Configure the ETHERNET CSR Clock Range */
    ETHERNET_MAC->GAR = (rt_uint32_t)value;

    /*------------------------ ETHERNET MACCR Configuration --------------------*/
    /* Get the ETHERNET MACCR value */
    value = ETHERNET_MAC->MCR;
    /* Clear WD, PCE, PS, TE and RE bits */
    value &= MACCR_CLEAR_MASK;

    value |= (rt_uint32_t)(EMAC_Watchdog_Enable |
                        EMAC_Jabber_Enable |
                        EMAC_InterFrameGap_96Bit |
                        EMAC_CarrierSense_Enable |
                        EMAC_Speed_100M |
                        EMAC_ReceiveOwn_Enable |
                        EMAC_LoopbackMode_Disable |
                        EMAC_Mode_FullDuplex |
                        EMAC_ChecksumOffload_Enable |
                        EMAC_RetryTransmission_Disable |
                        EMAC_AutomaticPadCRCStrip_Disable |
                        EMAC_BackOffLimit_10 |
                        EMAC_DeferralCheck_Disable);

    /* Write to ETHERNET MACCR */
    value |= (1<<15);
    value &= ~(1<<25);
    value &= ~(1<<24);
    ETHERNET_MAC->MCR = (rt_uint32_t)value;

    /*----------------------- ETHERNET MACFFR Configuration --------------------*/
    /* Write to ETHERNET MACFFR */
    ETHERNET_MAC->MFFR = (rt_uint32_t)(EMAC_ReceiveAll_Enable |
                                        EMAC_SourceAddrFilter_Disable |
                                        EMAC_PassControlFrames_BlockAll |
                                        EMAC_BroadcastFramesReception_Disable |
                                        EMAC_DestinationAddrFilter_Normal |
                                        EMAC_PromiscuousMode_Disable |
                                        EMAC_MulticastFramesFilter_Perfect |
                                        EMAC_UnicastFramesFilter_Perfect);

    /*--------------- ETHERNET MACHTHR and MACHTLR Configuration ---------------*/
    /* Write to ETHERNET MACHTHR */
    ETHERNET_MAC->MHTRH = 0;
    /* Write to ETHERNET MACHTLR */
    ETHERNET_MAC->MHTRL = 0;
    /*----------------------- ETHERNET MACFCR Configuration --------------------*/
    /* Get the ETHERNET MACFCR value */
    value = ETHERNET_MAC->FCR;
    /* Clear xx bits */
    value &= MACFCR_CLEAR_MASK;

    value |= (rt_uint32_t)((0 << 16) |
                        EMAC_ZeroQuantaPause_Disable |
                        EMAC_PauseLowThreshold_Minus4 |
                        EMAC_UnicastPauseFrameDetect_Disable |
                        EMAC_ReceiveFlowControl_Disable |
                        EMAC_TransmitFlowControl_Disable);

    /* Write to ETHERNET MACFCR */
    ETHERNET_MAC->FCR = (rt_uint32_t)value;
    /*----------------------- ETHERNET MACVLANTR Configuration -----------------*/
    ETHERNET_MAC->VTR = (rt_uint32_t)(EMAC_VLANTagComparison_16Bit |
                                       0);

    /*-------------------------------- DMA Config ------------------------------*/
    /*----------------------- ETHERNET DMAOMR Configuration --------------------*/
    /* Get the ETHERNET DMAOMR value */
    value = ETHERNET_MAC->OMR;
    /* Clear xx bits */
    value &= DMAOMR_CLEAR_MASK;

    value |= (rt_uint32_t)(EMAC_DropTCPIPChecksumErrorFrame_Disable |
                        EMAC_ReceiveStoreForward_Enable |
                        EMAC_FlushReceivedFrame_Enable |
                        EMAC_TransmitStoreForward_Enable |
                        EMAC_TransmitThresholdControl_64Bytes |
                        EMAC_ForwardErrorFrames_Disable |
                        EMAC_ForwardUndersizedGoodFrames_Disable |
                        EMAC_ReceiveThresholdControl_64Bytes |
                        EMAC_SecondFrameOperate_Disable);

    /* Write to ETHERNET DMAOMR */
    ETHERNET_MAC->OMR = (rt_uint32_t)value;

    /*----------------------- ETHERNET DMABMR Configuration --------------------*/
    ETHERNET_MAC->BMR = (rt_uint32_t)(EMAC_AddressAlignedBeats_Enable |
                                       EMAC_FixedBurst_Enable |
                                       EMAC_RxDMABurstLength_32Beat | /* !! if 4xPBL is selected for Tx or Rx it is applied for the other */
                                       EMAC_TxDMABurstLength_32Beat |
                                       (0 << 2) |
                                       EMAC_DMAArbitration_RoundRobin_RxTx_2_1 |
                                       EMAC_DMABMR_USP); /* Enable use of separate PBL for Rx and Tx */

    /* Return Ethernet configuration success */
    return EMAC_SUCCESS;
}

/**
  * Enables or disables the specified ETHERNET DMA interrupts.
  */
void EMAC_INT_config(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t EMAC_DMA_IT, rt_bool_t NewState)
{
    if (NewState)
    {
        /* Enable the selected ETHERNET DMA interrupts */
        ETHERNET_MAC->IER |= EMAC_DMA_IT;
    }
    else
    {
        /* Disable the selected ETHERNET DMA interrupts */
        ETHERNET_MAC->IER &=(~(rt_uint32_t)EMAC_DMA_IT);
    }
}

/**
  * Configures the selected MAC address.
  */
void EMAC_MAC_Addr_config(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t MacAddr, rt_uint8_t *Addr)
{
    rt_uint32_t value;

    /* Calculate the selectecd MAC address high register */
    value = ((rt_uint32_t)Addr[5] << 8) | (rt_uint32_t)Addr[4];
    /* Load the selectecd MAC address high register */
    //(*(volatile rt_uint32_t *) (EMAC_MAC_ADDR_HBASE + MacAddr)) = value;
    ETHERNET_MAC->MARs[MacAddr].MARH = value;
    /* Calculate the selectecd MAC address low register */
    value = ((rt_uint32_t)Addr[3] << 24) | ((rt_uint32_t)Addr[2] << 16) | ((rt_uint32_t)Addr[1] << 8) | Addr[0];

    /* Load the selectecd MAC address low register */
    //(*(volatile rt_uint32_t *) (EMAC_MAC_ADDR_LBASE + MacAddr)) = value;
    ETHERNET_MAC->MARs[MacAddr].MARL = value;
}

/**
  * Enables or disables the MAC transmission.
  */
void EMAC_MACTransmissionCmd(struct rt_synopsys_eth * ETHERNET_MAC, rt_bool_t NewState)
{
    if (NewState)
    {
        /* Enable the MAC transmission */
        ETHERNET_MAC->MCR |= EMAC_MACCR_TE;
    }
    else
    {
        /* Disable the MAC transmission */
        ETHERNET_MAC->MCR &= ~EMAC_MACCR_TE;
    }
}

/**
  * Clears the ETHERNET transmit FIFO.
  */
void EMAC_FlushTransmitFIFO(struct rt_synopsys_eth * ETHERNET_MAC)
{
    /* Set the Flush Transmit FIFO bit */
    ETHERNET_MAC->OMR |= EMAC_DMAOMR_FTF;
}

/**
  * Enables or disables the MAC reception.
  */
void EMAC_MACReceptionCmd(struct rt_synopsys_eth * ETHERNET_MAC, rt_bool_t NewState)
{
    if (NewState)
    {
        /* Enable the MAC reception */
        ETHERNET_MAC->MCR |= EMAC_MACCR_RE;
    }
    else
    {
        /* Disable the MAC reception */
        ETHERNET_MAC->MCR &= ~EMAC_MACCR_RE;
    }
}

/**
  * Enables or disables the DMA transmission.
  */
void EMAC_DMATransmissionCmd(struct rt_synopsys_eth * ETHERNET_MAC, rt_bool_t NewState)
{
    if (NewState)
    {
        /* Enable the DMA transmission */
        ETHERNET_MAC->OMR |= EMAC_DMAOMR_ST;
    }
    else
    {
        /* Disable the DMA transmission */
        ETHERNET_MAC->OMR &= ~EMAC_DMAOMR_ST;
    }
}

/**
  * Enables or disables the DMA reception.
  */
void EMAC_DMAReceptionCmd(struct rt_synopsys_eth * ETHERNET_MAC, rt_bool_t NewState)
{
    if (NewState)
    {
        /* Enable the DMA reception */
        ETHERNET_MAC->OMR |= EMAC_DMAOMR_SR;
    }
    else
    {
        /* Disable the DMA reception */
        ETHERNET_MAC->OMR &= ~EMAC_DMAOMR_SR;
    }
}

/**
  * Enables ENET MAC and DMA reception/transmission
  */
void EMAC_start(struct rt_synopsys_eth * ETHERNET_MAC)
{
    /* Enable transmit state machine of the MAC for transmission on the MII */
    EMAC_MACTransmissionCmd(ETHERNET_MAC, RT_TRUE);
    /* Flush Transmit FIFO */
    EMAC_FlushTransmitFIFO(ETHERNET_MAC);
    /* Enable receive state machine of the MAC for reception from the MII */
    EMAC_MACReceptionCmd(ETHERNET_MAC, RT_TRUE);

    /* Start DMA transmission */
    EMAC_DMATransmissionCmd(ETHERNET_MAC, RT_TRUE);
    /* Start DMA reception */
    EMAC_DMAReceptionCmd(ETHERNET_MAC, RT_TRUE);
}

/**
  * Clears the ETHERNET's DMA interrupt pending bit.
  */
void EMAC_clear_pending(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t pending)
{
    /* Clear the selected ETHERNET DMA IT */
    ETHERNET_MAC->SR = (rt_uint32_t) pending;
}

/**
  * Resumes the DMA Transmission by writing to the DmaRxPollDemand register
  *   (the data written could be anything). This forces the DMA to resume reception.
  */
void EMAC_resume_reception(struct rt_synopsys_eth * ETHERNET_MAC)
{
    ETHERNET_MAC->RPDR = 0;
}

/**
  * Resumes the DMA Transmission by writing to the DmaTxPollDemand register
  *   (the data written could be anything). This forces  the DMA to resume transmission.
  */
void EMAC_resume_transmission(struct rt_synopsys_eth * ETHERNET_MAC)
{
    ETHERNET_MAC->TPDR = 0;
}

/**
  * Read a PHY register
  */
rt_uint16_t EMAC_PHY_read(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint16_t PHYAddress, rt_uint16_t PHYReg)
{
    rt_uint32_t value = 0;
    volatile rt_uint32_t timeout = 0;

    /* Get the ETHERNET MACMIIAR value */
    value = ETHERNET_MAC->GAR;
    /* Keep only the CSR Clock Range CR[2:0] bits value */
    value &= ~MACMIIAR_CR_MASK;
    /* Prepare the MII address register value */
    value |=(((rt_uint32_t)PHYAddress<<11) & EMAC_MACMIIAR_PA); /* Set the PHY device address */
    value |=(((rt_uint32_t)PHYReg<<6) & EMAC_MACMIIAR_MR);      /* Set the PHY register address */
    value &= ~EMAC_MACMIIAR_MW;                              /* Set the read mode */
    value |= EMAC_MACMIIAR_MB;                               /* Set the MII Busy bit */
    /* Write the result value into the MII Address register */
    ETHERNET_MAC->GAR = value;
    /* Check for the Busy flag */
    do
    {
        timeout++;
        value = ETHERNET_MAC->GAR;
    }
    while ((value & EMAC_MACMIIAR_MB) && (timeout < (rt_uint32_t)PHY_READ_TO));
    /* Return ERROR in case of timeout */
    if(timeout == PHY_READ_TO)
    {
        return (rt_uint16_t)EMAC_ERROR;
    }

    /* Return data register value */
    return (rt_uint16_t)(ETHERNET_MAC->GDR);
}

/**
  * Write to a PHY register
  */
rt_uint32_t EMAC_PHY_write(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint16_t PHYAddress, rt_uint16_t PHYReg, rt_uint16_t PHYValue)
{
    rt_uint32_t value = 0;
    volatile rt_uint32_t timeout = 0;

    /* Get the ETHERNET MACMIIAR value */
    value = ETHERNET_MAC->GAR;
    /* Keep only the CSR Clock Range CR[2:0] bits value */
    value &= ~MACMIIAR_CR_MASK;
    /* Prepare the MII register address value */
    value |=(((rt_uint32_t)PHYAddress<<11) & EMAC_MACMIIAR_PA); /* Set the PHY device address */
    value |=(((rt_uint32_t)PHYReg<<6) & EMAC_MACMIIAR_MR);      /* Set the PHY register address */
    value |= EMAC_MACMIIAR_MW;                               /* Set the write mode */
    value |= EMAC_MACMIIAR_MB;                               /* Set the MII Busy bit */
    /* Give the value to the MII data register */
    ETHERNET_MAC->GDR = PHYValue;
    /* Write the result value into the MII Address register */
    ETHERNET_MAC->GAR = value;
    /* Check for the Busy flag */
    do
    {
        timeout++;
        value = ETHERNET_MAC->GAR;
    }
    while ((value & EMAC_MACMIIAR_MB) && (timeout < (rt_uint32_t)PHY_WRITE_TO));
    /* Return ERROR in case of timeout */
    if(timeout == PHY_WRITE_TO)
    {
        return EMAC_ERROR;
    }

    /* Return SUCCESS */
    return EMAC_SUCCESS;
}
