/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "synopsys_emac.h"
#include "gd32f4xx_enet.h"

/* The state of enet  initialization */
volatile uint32_t enet_init_state = 0;

/* Global pointers on Tx and Rx descriptor used to track transmit and receive descriptors */
extern EMAC_DMADESCTypeDef  *DMATxDescToSet;
extern EMAC_DMADESCTypeDef  *DMARxDescToGet;

/**
  * Initializes the ETHERNET peripheral according to the specified
  */
rt_uint32_t EMAC_init(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t SystemCoreClock)
{
    /*-------------------------------- Reset ethernet -------------------------------*/
    enet_deinit();
    enet_software_reset();

    /* configure the parameters which are usually less cared for enet initialization */
    enet_initpara_config(HALFDUPLEX_OPTION, ENET_CARRIERSENSE_DISABLE|ENET_RECEIVEOWN_ENABLE|ENET_RETRYTRANSMISSION_DISABLE|ENET_BACKOFFLIMIT_10|ENET_DEFERRALCHECK_DISABLE);

    /*-------------------------------- Initialize ENET ------------------------------*/
    enet_init_state = enet_init(ENET_AUTO_NEGOTIATION, ENET_AUTOCHECKSUM_DROP_FAILFRAMES, ENET_BROADCAST_FRAMES_PASS);

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
    enet_txfifo_flush();
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
