/**************************************************************************//**
 * @file     emac.c
 * @version  V1.00
 * @brief    M480 EMAC driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EMAC_Driver EMAC Driver
  @{
*/


/* Below are structure, definitions, static variables used locally by EMAC driver and does not want to parse by doxygen unless HIDDEN_SYMBOLS is defined */
/** @cond HIDDEN_SYMBOLS */

/** @addtogroup EMAC_EXPORTED_CONSTANTS EMAC Exported Constants
  @{
*/

/* PHY Register Description */
#define PHY_CNTL_REG    0x00UL        /*!<  PHY control register address */
#define PHY_STATUS_REG  0x01UL        /*!<  PHY status register address */
#define PHY_ID1_REG     0x02UL        /*!<  PHY ID1 register */
#define PHY_ID2_REG     0x03UL        /*!<  PHY ID2 register */
#define PHY_ANA_REG     0x04UL        /*!<  PHY auto-negotiation advertisement register */
#define PHY_ANLPA_REG   0x05UL        /*!<  PHY auto-negotiation link partner availability register */
#define PHY_ANE_REG     0x06UL        /*!<  PHY auto-negotiation expansion register */

/* PHY Control Register */
#define PHY_CNTL_RESET_PHY      (1UL << 15UL)
#define PHY_CNTL_DR_100MB       (1UL << 13UL)
#define PHY_CNTL_ENABLE_AN      (1UL << 12UL)
#define PHY_CNTL_POWER_DOWN     (1UL << 11UL)
#define PHY_CNTL_RESTART_AN     (1UL << 9UL)
#define PHY_CNTL_FULLDUPLEX     (1UL << 8UL)

/* PHY Status Register */
#define PHY_STATUS_AN_COMPLETE   (1UL << 5UL)
#define PHY_STATUS_LINK_VALID    (1UL << 2UL)

/* PHY Auto-negotiation Advertisement Register */
#define PHY_ANA_DR100_TX_FULL   (1UL << 8UL)
#define PHY_ANA_DR100_TX_HALF   (1UL << 7UL)
#define PHY_ANA_DR10_TX_FULL    (1UL << 6UL)
#define PHY_ANA_DR10_TX_HALF    (1UL << 5UL)
#define PHY_ANA_IEEE_802_3_CSMA_CD   (1UL << 0UL)

/* PHY Auto-negotiation Link Partner Advertisement Register */
#define PHY_ANLPA_DR100_TX_FULL   (1UL << 8UL)
#define PHY_ANLPA_DR100_TX_HALF   (1UL << 7UL)
#define PHY_ANLPA_DR10_TX_FULL    (1UL << 6UL)
#define PHY_ANLPA_DR10_TX_HALF    (1UL << 5UL)

/* EMAC Tx/Rx descriptor's owner bit */
#define EMAC_DESC_OWN_EMAC 0x80000000UL  /*!<  Set owner to EMAC */
#define EMAC_DESC_OWN_CPU  0x00000000UL  /*!<  Set owner to CPU */

/* Rx Frame Descriptor Status */
#define EMAC_RXFD_RTSAS   0x0080UL  /*!<  Time Stamp Available */
#define EMAC_RXFD_RP      0x0040UL  /*!<  Runt Packet */
#define EMAC_RXFD_ALIE    0x0020UL  /*!<  Alignment Error */
#define EMAC_RXFD_RXGD    0x0010UL  /*!<  Receiving Good packet received */
#define EMAC_RXFD_PTLE    0x0008UL  /*!<  Packet Too Long Error */
#define EMAC_RXFD_CRCE    0x0002UL  /*!<  CRC Error */
#define EMAC_RXFD_RXINTR  0x0001UL  /*!<  Interrupt on receive */

/* Tx Frame Descriptor's Control bits */
#define EMAC_TXFD_TTSEN     0x08UL      /*!<  Tx time stamp enable */
#define EMAC_TXFD_INTEN     0x04UL      /*!<  Tx interrupt enable */
#define EMAC_TXFD_CRCAPP    0x02UL      /*!<  Append CRC */
#define EMAC_TXFD_PADEN     0x01UL      /*!<  Padding mode enable */

/* Tx Frame Descriptor Status */
#define EMAC_TXFD_TXINTR 0x0001UL  /*!<  Interrupt on Transmit */
#define EMAC_TXFD_DEF    0x0002UL  /*!<  Transmit deferred  */
#define EMAC_TXFD_TXCP   0x0008UL  /*!<  Transmission Completion  */
#define EMAC_TXFD_EXDEF  0x0010UL  /*!<  Exceed Deferral */
#define EMAC_TXFD_NCS    0x0020UL  /*!<  No Carrier Sense Error */
#define EMAC_TXFD_TXABT  0x0040UL  /*!<  Transmission Abort  */
#define EMAC_TXFD_LC     0x0080UL  /*!<  Late Collision  */
#define EMAC_TXFD_TXHA   0x0100UL  /*!<  Transmission halted */
#define EMAC_TXFD_PAU    0x0200UL  /*!<  Paused */
#define EMAC_TXFD_SQE    0x0400UL  /*!<  SQE error  */
#define EMAC_TXFD_TTSAS  0x0800UL  /*!<  Time Stamp available */

/*@}*/ /* end of group EMAC_EXPORTED_CONSTANTS */

/** @addtogroup EMAC_EXPORTED_TYPEDEF EMAC Exported Type Defines
  @{
*/

/*@}*/ /* end of group EMAC_EXPORTED_TYPEDEF */

/* local variables */
static uint32_t s_u32EnableTs = 0UL;

static void EMAC_MdioWrite(EMAC_T *EMAC, uint32_t u32Reg, uint32_t u32Addr, uint32_t u32Data);
static uint32_t EMAC_MdioRead(EMAC_T *EMAC, uint32_t u32Reg, uint32_t u32Addr);

static uint32_t EMAC_Subsec2Nsec(uint32_t subsec);
static uint32_t EMAC_Nsec2Subsec(uint32_t nsec);
static void EMAC_TxDescInit(EMAC_MEMMGR_T *psMemMgr);
static void EMAC_RxDescInit(EMAC_MEMMGR_T *psMemMgr);

/** @addtogroup EMAC_EXPORTED_FUNCTIONS EMAC Exported Functions
  @{
*/


/**
  * @brief  Write PHY register
  * @param[in]  u32Reg PHY register number
  * @param[in]  u32Addr PHY address, this address is board dependent
  * @param[in] u32Data data to write to PHY register
  * @return None
  */
static void EMAC_MdioWrite(EMAC_T *EMAC, uint32_t u32Reg, uint32_t u32Addr, uint32_t u32Data)
{
    /* Set data register */
    EMAC->MIIMDAT = u32Data ;
    /* Set PHY address, PHY register address, busy bit and write bit */
    EMAC->MIIMCTL = u32Reg | (u32Addr << 8) | EMAC_MIIMCTL_BUSY_Msk | EMAC_MIIMCTL_WRITE_Msk | EMAC_MIIMCTL_MDCON_Msk;

    /* Wait write complete by polling busy bit. */
    while (EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk)
    {
        ;
    }

}

/**
  * @brief  Read PHY register
  * @param[in]  u32Reg PHY register number
  * @param[in]  u32Addr PHY address, this address is board dependent
  * @return Value read from PHY register
  */
static uint32_t EMAC_MdioRead(EMAC_T *EMAC, uint32_t u32Reg, uint32_t u32Addr)
{
    /* Set PHY address, PHY register address, busy bit */
    EMAC->MIIMCTL = u32Reg | (u32Addr << EMAC_MIIMCTL_PHYADDR_Pos) | EMAC_MIIMCTL_BUSY_Msk | EMAC_MIIMCTL_MDCON_Msk;

    /* Wait read complete by polling busy bit */
    while (EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk)
    {
        ;
    }

    /* Get return data */
    return EMAC->MIIMDAT;
}

void EMAC_Reset(EMAC_T *EMAC)
{
    /* Reset MAC */
    EMAC->CTL = 0x1000000;
}

/**
  * @brief  Initialize PHY chip, check for the auto-negotiation result.
  * @param  None
  * @return None
  */
void EMAC_PhyInit(EMAC_T *EMAC)
{
    uint32_t reg;
    uint32_t i = 0UL;

    /* Reset Phy Chip */
    EMAC_MdioWrite(EMAC, PHY_CNTL_REG, EMAC_PHY_ADDR, PHY_CNTL_RESET_PHY);

    /* Wait until reset complete */
    while (1)
    {
        reg = EMAC_MdioRead(EMAC, PHY_CNTL_REG, EMAC_PHY_ADDR) ;

        if ((reg & PHY_CNTL_RESET_PHY) == 0UL)
        {
            break;
        }
    }

    while (!(EMAC_MdioRead(EMAC, PHY_STATUS_REG, EMAC_PHY_ADDR) & PHY_STATUS_LINK_VALID))
    {
        if (i++ > 2000000UL)      /* Cable not connected */
        {
            EMAC->CTL &= ~EMAC_CTL_OPMODE_Msk;
            EMAC->CTL &= ~EMAC_CTL_FUDUP_Msk;
            break;
        }
    }

    if (i <= 2000000UL)
    {
        /* Configure auto negotiation capability */
        EMAC_MdioWrite(EMAC, PHY_ANA_REG, EMAC_PHY_ADDR, PHY_ANA_DR100_TX_FULL |
                       PHY_ANA_DR100_TX_HALF |
                       PHY_ANA_DR10_TX_FULL |
                       PHY_ANA_DR10_TX_HALF |
                       PHY_ANA_IEEE_802_3_CSMA_CD);
        /* Restart auto negotiation */
        EMAC_MdioWrite(EMAC, PHY_CNTL_REG, EMAC_PHY_ADDR, EMAC_MdioRead(EMAC, PHY_CNTL_REG, EMAC_PHY_ADDR) | PHY_CNTL_RESTART_AN);

        /* Wait for auto-negotiation complete */
        while (!(EMAC_MdioRead(EMAC, PHY_STATUS_REG, EMAC_PHY_ADDR) & PHY_STATUS_AN_COMPLETE))
        {
            ;
        }

        /* Check link valid again. Some PHYs needs to check result after link valid bit set */
        while (!(EMAC_MdioRead(EMAC, PHY_STATUS_REG, EMAC_PHY_ADDR) & PHY_STATUS_LINK_VALID))
        {
            ;
        }

        /* Check link partner capability */
        reg = EMAC_MdioRead(EMAC, PHY_ANLPA_REG, EMAC_PHY_ADDR) ;

        if (reg & PHY_ANLPA_DR100_TX_FULL)
        {
            EMAC->CTL |= EMAC_CTL_OPMODE_Msk;
            EMAC->CTL |= EMAC_CTL_FUDUP_Msk;
        }
        else if (reg & PHY_ANLPA_DR100_TX_HALF)
        {
            EMAC->CTL |= EMAC_CTL_OPMODE_Msk;
            EMAC->CTL &= ~EMAC_CTL_FUDUP_Msk;
        }
        else if (reg & PHY_ANLPA_DR10_TX_FULL)
        {
            EMAC->CTL &= ~EMAC_CTL_OPMODE_Msk;
            EMAC->CTL |= EMAC_CTL_FUDUP_Msk;
        }
        else
        {
            EMAC->CTL &= ~EMAC_CTL_OPMODE_Msk;
            EMAC->CTL &= ~EMAC_CTL_FUDUP_Msk;
        }
    }
}

/**
  * @brief  Initial EMAC Tx descriptors and get Tx descriptor base address
  * @param  EMAC_MEMMGR_T pointer
  * @return None
  */
static void EMAC_TxDescInit(EMAC_MEMMGR_T *psMemMgr)
{
    uint32_t i;

    /* Get Frame descriptor's base address. */
    psMemMgr->psNextTxDesc = psMemMgr->psCurrentTxDesc = (EMAC_DESCRIPTOR_T *)((uint32_t)&psMemMgr->psTXDescs[0] | BIT31);

    for (i = 0UL; i < psMemMgr->u32TxDescSize; i++)
    {

        if (s_u32EnableTs)
        {
            psMemMgr->psTXDescs[i].u32Status1 = EMAC_TXFD_PADEN | EMAC_TXFD_CRCAPP | EMAC_TXFD_INTEN;
        }
        else
        {
            psMemMgr->psTXDescs[i].u32Status1 = EMAC_TXFD_PADEN | EMAC_TXFD_CRCAPP | EMAC_TXFD_INTEN | EMAC_TXFD_TTSEN;
        }

        psMemMgr->psTXDescs[i].u32Data = (uint32_t)& psMemMgr->psTXFrames[i] | BIT31;
        psMemMgr->psTXDescs[i].u32Status2 = 0UL;
        psMemMgr->psTXDescs[i].u32Next = (uint32_t)(&psMemMgr->psTXDescs[(i + 1UL) % EMAC_TX_DESC_SIZE]) | BIT31;
        psMemMgr->psTXDescs[i].u32Backup1 = psMemMgr->psTXDescs[i].u32Data;
        psMemMgr->psTXDescs[i].u32Backup2 = psMemMgr->psTXDescs[i].u32Next;
    }
    psMemMgr->psEmac->TXDSA = (uint32_t)psMemMgr->psCurrentTxDesc;
}


/**
  * @brief  Initial EMAC Rx descriptors and get Rx descriptor base address
  * @param  EMAC_MEMMGR_T pointer
  * @return None
  */
static void EMAC_RxDescInit(EMAC_MEMMGR_T *psMemMgr)
{

    uint32_t i;

    /* Get Frame descriptor's base address. */
    psMemMgr->psCurrentRxDesc = (EMAC_DESCRIPTOR_T *)((uint32_t)&psMemMgr->psRXDescs[0] | BIT31);

    for (i = 0UL; i < psMemMgr->u32RxDescSize; i++)
    {
        psMemMgr->psRXDescs[i].u32Status1 = EMAC_DESC_OWN_EMAC;
        psMemMgr->psRXDescs[i].u32Data = (uint32_t)&psMemMgr->psRXFrames[i] | BIT31;
        psMemMgr->psRXDescs[i].u32Status2 = 0UL;
        psMemMgr->psRXDescs[i].u32Next = (uint32_t)(&psMemMgr->psRXDescs[(i + 1UL) % EMAC_RX_DESC_SIZE]) | BIT31;
        psMemMgr->psRXDescs[i].u32Backup1 = psMemMgr->psRXDescs[i].u32Data;
        psMemMgr->psRXDescs[i].u32Backup2 = psMemMgr->psRXDescs[i].u32Next;
    }
    psMemMgr->psEmac->RXDSA = (uint32_t)psMemMgr->psCurrentRxDesc;
}

/**
  * @brief  Convert subsecond value to nano second
  * @param[in]  subsec Subsecond value to be convert
  * @return Nano second
  */
static uint32_t EMAC_Subsec2Nsec(uint32_t subsec)
{
    /* 2^31 subsec == 10^9 ns */
    uint64_t i;
    i = 1000000000ull * (uint64_t)subsec;
    i >>= 31;
    return ((uint32_t)i);
}

/**
  * @brief  Convert nano second to subsecond value
  * @param[in]  nsec Nano second to be convert
  * @return Subsecond
  */
static uint32_t EMAC_Nsec2Subsec(uint32_t nsec)
{
    /* 10^9 ns =  2^31 subsec */
    uint64_t i;
    i = (1ull << 31) * nsec;
    i /= 1000000000ull;
    return ((uint32_t)i);
}


/*@}*/ /* end of group EMAC_EXPORTED_FUNCTIONS */



/** @endcond HIDDEN_SYMBOLS */


/** @addtogroup EMAC_EXPORTED_FUNCTIONS EMAC Exported Functions
  @{
*/


/**
  * @brief  Initialize EMAC interface, including descriptors, MAC address, and PHY.
  * @param[in]  pu8MacAddr  Pointer to uint8_t array holds MAC address
  * @return None
  * @note This API configures EMAC to receive all broadcast and multicast packets, but could configure to other settings with
  *       \ref EMAC_ENABLE_RECV_BCASTPKT, \ref EMAC_DISABLE_RECV_BCASTPKT, \ref EMAC_ENABLE_RECV_MCASTPKT, and \ref EMAC_DISABLE_RECV_MCASTPKT
  * @note Receive(RX) and transmit(TX) are not enabled yet, application must call \ref EMAC_ENABLE_RX and \ref EMAC_ENABLE_TX to
  *       enable receive and transmit function.
  */
void EMAC_Open(EMAC_MEMMGR_T *psMemMgr, uint8_t *pu8MacAddr)
{
    EMAC_T *EMAC = psMemMgr->psEmac;

    /* Enable transmit and receive descriptor */
    EMAC_TxDescInit(psMemMgr);
    EMAC_RxDescInit(psMemMgr);

    /* Set the CAM Control register and the MAC address value */
    EMAC_SetMacAddr(EMAC, pu8MacAddr);

    /* Configure the MAC interrupt enable register. */
    EMAC->INTEN = EMAC_INTEN_RXIEN_Msk |
                  EMAC_INTEN_TXIEN_Msk |
                  EMAC_INTEN_RXGDIEN_Msk |
                  EMAC_INTEN_TXCPIEN_Msk |
                  EMAC_INTEN_RXBEIEN_Msk |
                  EMAC_INTEN_TXBEIEN_Msk |
                  EMAC_INTEN_RDUIEN_Msk |
                  EMAC_INTEN_TSALMIEN_Msk |
                  EMAC_INTEN_WOLIEN_Msk;

    /* Configure the MAC control register. */
    EMAC->CTL = EMAC_CTL_STRIPCRC_Msk |
                EMAC_CTL_RMIIEN_Msk;

    /* Accept packets for us and all broadcast and multicast packets */
    EMAC->CAMCTL =  EMAC_CAMCTL_CMPEN_Msk |
                    EMAC_CAMCTL_AMP_Msk |
                    EMAC_CAMCTL_ABP_Msk;

    /* Limit the max receive frame length */
    EMAC->MRFL = EMAC_MAX_PKT_SIZE;
}

/**
  * @brief  This function stop all receive and transmit activity and disable MAC interface
  * @param None
  * @return None
  */

void EMAC_Close(EMAC_T *EMAC)
{
    EMAC->CTL |= EMAC_CTL_RST_Msk;

    while (EMAC->CTL & EMAC_CTL_RST_Msk) {}
}

/**
  * @brief  Set the device MAC address
  * @param[in]  pu8MacAddr  Pointer to uint8_t array holds MAC address
  * @return None
  */
void EMAC_SetMacAddr(EMAC_T *EMAC, uint8_t *pu8MacAddr)
{
    EMAC_EnableCamEntry(EMAC, 0UL, pu8MacAddr);
}

/**
  * @brief Fill a CAM entry for MAC address comparison.
  * @param[in] u32Entry MAC entry to fill. Entry 0 is used to store device MAC address, do not overwrite the setting in it.
  * @param[in] pu8MacAddr  Pointer to uint8_t array holds MAC address
  * @return None
  */
void EMAC_EnableCamEntry(EMAC_T *EMAC, uint32_t u32Entry, uint8_t pu8MacAddr[])
{
    uint32_t u32Lsw, u32Msw;
    uint32_t reg;
    u32Lsw = (uint32_t)(((uint32_t)pu8MacAddr[4] << 24) |
                        ((uint32_t)pu8MacAddr[5] << 16));
    u32Msw = (uint32_t)(((uint32_t)pu8MacAddr[0] << 24) |
                        ((uint32_t)pu8MacAddr[1] << 16) |
                        ((uint32_t)pu8MacAddr[2] << 8) |
                        (uint32_t)pu8MacAddr[3]);

    reg = (uint32_t)&EMAC->CAM0M + u32Entry * 2UL * 4UL;
    *(uint32_t volatile *)reg = u32Msw;
    reg = (uint32_t)&EMAC->CAM0L + u32Entry * 2UL * 4UL;
    *(uint32_t volatile *)reg = u32Lsw;

    EMAC->CAMEN |= (1UL << u32Entry);
}

/**
  * @brief  Disable a specified CAM entry
  * @param[in]  u32Entry CAM entry to be disabled
  * @return None
  */
void EMAC_DisableCamEntry(EMAC_T *EMAC, uint32_t u32Entry)
{
    EMAC->CAMEN &= ~(1UL << u32Entry);
}


/**
  * @brief Receive an Ethernet packet
  * @param[in] pu8Data Pointer to a buffer to store received packet (4 byte CRC removed)
  * @param[in] pu32Size Received packet size (without 4 byte CRC).
  * @return Packet receive success or not
  * @retval 0 No packet available for receive
  * @retval 1 A packet is received
  * @note Return 0 doesn't guarantee the packet will be sent and received successfully.
  */
uint32_t EMAC_RecvPkt(EMAC_MEMMGR_T *psMemMgr, uint8_t *pu8Data, uint32_t *pu32Size)
{
    uint32_t reg;
    uint32_t u32Count = 0UL;
    EMAC_T *EMAC = psMemMgr->psEmac;

    /* Clear Rx interrupt flags */
    reg = EMAC->INTSTS;
    EMAC->INTSTS = reg & 0xFFFFUL;  /* Clear all RX related interrupt status */

    if (reg & EMAC_INTSTS_RXBEIF_Msk)
    {
        /* Bus error occurred, this is usually a bad sign about software bug and will occur again... */
        while (1) {}
    }
    else
    {
        /* Get Rx Frame Descriptor */
        EMAC_DESCRIPTOR_T *desc = (EMAC_DESCRIPTOR_T *)psMemMgr->psCurrentRxDesc;

        /* If we reach last recv Rx descriptor, leave the loop */
        if ((desc->u32Status1 & EMAC_DESC_OWN_EMAC) != EMAC_DESC_OWN_EMAC)   /* ownership=CPU */
        {
            uint32_t status = desc->u32Status1 >> 16;

            /* If Rx frame is good, process received frame */
            if (status & EMAC_RXFD_RXGD)
            {
                /* lower 16 bit in descriptor status1 stores the Rx packet length */
                *pu32Size = desc->u32Status1 & 0xFFFFUL;
                memcpy(pu8Data, (uint8_t *)desc->u32Data, *pu32Size);
                u32Count = 1UL;
            }
            else
            {
                /* Save Error status if necessary */
                if (status & EMAC_RXFD_RP) {}

                if (status & EMAC_RXFD_ALIE) {}

                if (status & EMAC_RXFD_PTLE) {}

                if (status & EMAC_RXFD_CRCE) {}
            }
        }
    }

    return (u32Count);
}

/**
  * @brief Receive an Ethernet packet and the time stamp while it's received
  * @param[out] pu8Data Pointer to a buffer to store received packet (4 byte CRC removed)
  * @param[out] pu32Size Received packet size (without 4 byte CRC).
  * @param[out] pu32Sec Second value while packet received
  * @param[out] pu32Nsec Nano second value while packet received
  * @return Packet receive success or not
  * @retval 0 No packet available for receive
  * @retval 1 A packet is received
  * @note Return 0 doesn't guarantee the packet will be sent and received successfully.
  * @note Largest Ethernet packet is 1514 bytes after stripped CRC, application must give
  *       a buffer large enough to store such packet
  */
uint32_t EMAC_RecvPktTS(EMAC_MEMMGR_T *psMemMgr, uint8_t *pu8Data, uint32_t *pu32Size, uint32_t *pu32Sec, uint32_t *pu32Nsec)
{
    EMAC_T *EMAC = psMemMgr->psEmac;
    uint32_t reg;
    uint32_t u32Count = 0UL;

    /* Clear Rx interrupt flags */
    reg = EMAC->INTSTS;
    EMAC->INTSTS = reg & 0xFFFFUL; /* Clear all Rx related interrupt status */

    if (reg & EMAC_INTSTS_RXBEIF_Msk)
    {
        /* Bus error occurred, this is usually a bad sign about software bug and will occur again... */
        while (1) {}
    }
    else
    {
        /* Get Rx Frame Descriptor */
        EMAC_DESCRIPTOR_T *desc = (EMAC_DESCRIPTOR_T *)psMemMgr->psCurrentRxDesc;

        /* If we reach last recv Rx descriptor, leave the loop */
        if (EMAC->CRXDSA != (uint32_t)desc)
        {
            if ((desc->u32Status1 | EMAC_DESC_OWN_EMAC) != EMAC_DESC_OWN_EMAC)   /* ownership=CPU */
            {

                uint32_t status = desc->u32Status1 >> 16;

                /* If Rx frame is good, process received frame */
                if (status & EMAC_RXFD_RXGD)
                {
                    /* lower 16 bit in descriptor status1 stores the Rx packet length */
                    *pu32Size = desc->u32Status1 & 0xFFFFUL;
                    memcpy(pu8Data, (uint8_t *)desc->u32Data, *pu32Size);

                    *pu32Sec = desc->u32Next; /* second stores in descriptor's NEXT field */
                    *pu32Nsec = EMAC_Subsec2Nsec(desc->u32Data); /* Sub nano second store in DATA field */

                    u32Count = 1UL;
                }
                else
                {
                    /* Save Error status if necessary */
                    if (status & EMAC_RXFD_RP) {}

                    if (status & EMAC_RXFD_ALIE) {}

                    if (status & EMAC_RXFD_PTLE) {}

                    if (status & EMAC_RXFD_CRCE) {}
                }
            }
        }
    }

    return (u32Count);
}

/**
  * @brief Clean up process after a packet is received
  * @param None
  * @return None
  * @details EMAC Rx interrupt service routine \b must call this API to release the resource use by receive process
  * @note Application can only call this function once every time \ref EMAC_RecvPkt or \ref EMAC_RecvPktTS returns 1
  */
void EMAC_RecvPktDone(EMAC_MEMMGR_T *psMemMgr)
{
    EMAC_T *EMAC = psMemMgr->psEmac;
    /* Get Rx Frame Descriptor */
    EMAC_DESCRIPTOR_T *desc = (EMAC_DESCRIPTOR_T *)psMemMgr->psCurrentRxDesc;

    /* Restore descriptor link list and data pointer they will be overwrite if time stamp enabled */
    desc->u32Data = desc->u32Backup1;
    desc->u32Next = desc->u32Backup2;

    /* Change ownership to DMA for next use */
    desc->u32Status1 |= EMAC_DESC_OWN_EMAC;

    /* Get Next Frame Descriptor pointer to process */
    desc = (EMAC_DESCRIPTOR_T *)desc->u32Next;

    /* Save last processed Rx descriptor */
    psMemMgr->psCurrentRxDesc = desc;

    EMAC_TRIGGER_RX(EMAC);
}


/**
  * @brief Send an Ethernet packet
  * @param[in] pu8Data Pointer to a buffer holds the packet to transmit
  * @param[in] u32Size Packet size (without 4 byte CRC).
  * @return Packet transmit success or not
  * @retval 0 Transmit failed due to descriptor unavailable.
  * @retval 1 Packet is copied to descriptor and triggered to transmit.
  * @note Return 1 doesn't guarantee the packet will be sent and received successfully.
  */
uint32_t EMAC_SendPkt(EMAC_MEMMGR_T *psMemMgr, uint8_t *pu8Data, uint32_t u32Size)
{
    EMAC_T *EMAC = psMemMgr->psEmac;

    /* Get Tx frame descriptor & data pointer */
    EMAC_DESCRIPTOR_T *desc = (EMAC_DESCRIPTOR_T *)psMemMgr->psNextTxDesc;
    uint32_t status = desc->u32Status1;
    uint32_t ret = 0UL;

    /* Check descriptor ownership */
    if ((status & EMAC_DESC_OWN_EMAC) != EMAC_DESC_OWN_EMAC)
    {
        memcpy((uint8_t *)desc->u32Data, pu8Data, u32Size);

        /* Set Tx descriptor transmit byte count */
        desc->u32Status2 = u32Size;

        /* Change descriptor ownership to EMAC */
        desc->u32Status1 |= EMAC_DESC_OWN_EMAC;

        /* Get next Tx descriptor */
        psMemMgr->psNextTxDesc = (EMAC_DESCRIPTOR_T *)(desc->u32Next);

        /* Trigger EMAC to send the packet */
        EMAC_TRIGGER_TX(EMAC);
        ret = 1UL;
    }

    return (ret);
}


/**
  * @brief Clean up process after packet(s) are sent
  * @param None
  * @return Number of packet sent between two function calls
  * @details EMAC Tx interrupt service routine \b must call this API or \ref EMAC_SendPktDoneTS to
  *          release the resource use by transmit process
  */
uint32_t EMAC_SendPktDone(EMAC_MEMMGR_T *psMemMgr)
{
    EMAC_T *EMAC = psMemMgr->psEmac;

    uint32_t status, reg;
    uint32_t last_tx_desc;
    uint32_t u32Count = 0UL;

    reg = EMAC->INTSTS;
    /* Clear Tx interrupt flags */
    EMAC->INTSTS = reg & (0xFFFF0000UL & ~EMAC_INTSTS_TSALMIF_Msk);


    if (reg & EMAC_INTSTS_TXBEIF_Msk)
    {
        /* Bus error occurred, this is usually a bad sign about software bug and will occur again... */
        while (1) {}
    }
    else
    {
        /* Get our first descriptor to process */
        EMAC_DESCRIPTOR_T *desc = (EMAC_DESCRIPTOR_T *)psMemMgr->psCurrentTxDesc;

        /* Process the descriptor(s). */
        last_tx_desc = EMAC->CTXDSA ;

        do
        {
            /* Descriptor ownership is still EMAC, so this packet haven't been send. */
            if (desc->u32Status1 & EMAC_DESC_OWN_EMAC)
            {
                break;
            }

            /* Get Tx status stored in descriptor */
            status = desc->u32Status2 >> 16UL;

            if (status & EMAC_TXFD_TXCP)
            {
                u32Count++;
            }
            else
            {
                /* Do nothing here on error. */
                if (status & EMAC_TXFD_TXABT) {}

                if (status & EMAC_TXFD_DEF) {}

                if (status & EMAC_TXFD_PAU) {}

                if (status & EMAC_TXFD_EXDEF) {}

                if (status & EMAC_TXFD_NCS) {}

                if (status & EMAC_TXFD_SQE) {}

                if (status & EMAC_TXFD_LC) {}

                if (status & EMAC_TXFD_TXHA) {}
            }

            /* restore descriptor link list and data pointer they will be overwrite if time stamp enabled */
            desc->u32Data = desc->u32Backup1;
            desc->u32Next = desc->u32Backup2;
            /* go to next descriptor in link */
            desc = (EMAC_DESCRIPTOR_T *)desc->u32Next;
        }
        while (last_tx_desc != (uint32_t)desc);      /* If we reach last sent Tx descriptor, leave the loop */

        /* Save last processed Tx descriptor */
        psMemMgr->psCurrentTxDesc = (EMAC_DESCRIPTOR_T *)desc;
    }

    return (u32Count);
}

/**
  * @brief Clean up process after a packet is sent, and get the time stamp while packet is sent
  * @param[in]  pu32Sec Second value while packet sent
  * @param[in]  pu32Nsec Nano second value while packet sent
  * @return If a packet sent successfully
  * @retval 0 No packet sent successfully, and the value in *pu32Sec and *pu32Nsec are meaningless
  * @retval 1 A packet sent successfully, and the value in *pu32Sec and *pu32Nsec is the time stamp while packet sent
  * @details EMAC Tx interrupt service routine \b must call this API or \ref EMAC_SendPktDone to
  *          release the resource use by transmit process
  */
uint32_t EMAC_SendPktDoneTS(EMAC_MEMMGR_T *psMemMgr, uint32_t *pu32Sec, uint32_t *pu32Nsec)
{
    EMAC_T *EMAC = psMemMgr->psEmac;
    uint32_t reg;
    uint32_t u32Count = 0UL;

    reg = EMAC->INTSTS;
    /* Clear Tx interrupt flags */
    EMAC->INTSTS = reg & (0xFFFF0000UL & ~EMAC_INTSTS_TSALMIF_Msk);


    if (reg & EMAC_INTSTS_TXBEIF_Msk)
    {
        /* Bus error occurred, this is usually a bad sign about software bug and will occur again... */
        while (1) {}
    }
    else
    {
        /* Process the descriptor.
           Get our first descriptor to process */
        EMAC_DESCRIPTOR_T *desc = (EMAC_DESCRIPTOR_T *)psMemMgr->psCurrentTxDesc;

        /* Descriptor ownership is still EMAC, so this packet haven't been send. */
        if ((desc->u32Status1 & EMAC_DESC_OWN_EMAC) != EMAC_DESC_OWN_EMAC)
        {
            /* Get Tx status stored in descriptor */
            uint32_t status = desc->u32Status2 >> 16UL;

            if (status & EMAC_TXFD_TXCP)
            {
                u32Count = 1UL;
                *pu32Sec = desc->u32Next; /* second stores in descriptor's NEXT field */
                *pu32Nsec = EMAC_Subsec2Nsec(desc->u32Data); /* Sub nano second store in DATA field */
            }
            else
            {
                /* Do nothing here on error. */
                if (status & EMAC_TXFD_TXABT) {}

                if (status & EMAC_TXFD_DEF) {}

                if (status & EMAC_TXFD_PAU) {}

                if (status & EMAC_TXFD_EXDEF) {}

                if (status & EMAC_TXFD_NCS) {}

                if (status & EMAC_TXFD_SQE) {}

                if (status & EMAC_TXFD_LC) {}

                if (status & EMAC_TXFD_TXHA) {}
            }

            /* restore descriptor link list and data pointer they will be overwrite if time stamp enabled */
            desc->u32Data = desc->u32Backup1;
            desc->u32Next = desc->u32Backup2;
            /* go to next descriptor in link */
            desc = (EMAC_DESCRIPTOR_T *)desc->u32Next;

            /* Save last processed Tx descriptor */
            psMemMgr->psCurrentTxDesc = desc;
        }
    }

    return (u32Count);
}

/**
  * @brief  Enable IEEE1588 time stamp function and set current time
  * @param[in]  u32Sec Second value
  * @param[in]  u32Nsec Nano second value
  * @return None
  */
void EMAC_EnableTS(EMAC_T *EMAC, uint32_t u32Sec, uint32_t u32Nsec)
{
#if 0
    double f;
    uint32_t reg;
    EMAC->TSCTL = EMAC_TSCTL_TSEN_Msk;
    EMAC->UPDSEC = u32Sec;   /* Assume current time is 0 sec + 0 nano sec */
    EMAC->UPDSUBSEC = EMAC_Nsec2Subsec(u32Nsec);

    /* PTP source clock is 160MHz (Real chip using PLL). Each tick is 6.25ns
       Assume we want to set each tick to 100ns.
       Increase register = (100 * 2^31) / (10^9) = 214.71 =~ 215 = 0xD7
       Addend register = 2^32 * tick_freq / (160MHz), where tick_freq = (2^31 / 215) MHz
       From above equation, addend register = 2^63 / (160M * 215) ~= 268121280 = 0xFFB34C0
       So:
        EMAC->TSIR = 0xD7;
        EMAC->TSAR = 0x1E70C600; */
    f = (100.0 * 2147483648.0) / (1000000000.0) + 0.5;
    EMAC->TSINC = (reg = (uint32_t)f);
    f = (double)9223372036854775808.0 / ((double)(CLK_GetHCLKFreq()) * (double)reg);
    EMAC->TSADDEND = (uint32_t)f;
    EMAC->TSCTL |= (EMAC_TSCTL_TSUPDATE_Msk | EMAC_TSCTL_TSIEN_Msk | EMAC_TSCTL_TSMODE_Msk); /* Fine update */
#endif
}

/**
  * @brief  Disable IEEE1588 time stamp function
  * @param None
  * @return None
  */
void EMAC_DisableTS(EMAC_T *EMAC)
{
#if 0
    EMAC->TSCTL = 0UL;
#endif
}

/**
  * @brief  Get current time stamp
  * @param[out]  pu32Sec Current second value
  * @param[out]  pu32Nsec Current nano second value
  * @return None
  */
void EMAC_GetTime(EMAC_T *EMAC, uint32_t *pu32Sec, uint32_t *pu32Nsec)
{
    /* Must read TSLSR firstly. Hardware will preserve TSMSR value at the time TSLSR read. */
    *pu32Nsec = EMAC_Subsec2Nsec(EMAC->TSSUBSEC);
    *pu32Sec = EMAC->TSSEC;
}

/**
  * @brief  Set current time stamp
  * @param[in]  u32Sec Second value
  * @param[in]  u32Nsec Nano second value
  * @return None
  */
void EMAC_SetTime(EMAC_T *EMAC, uint32_t u32Sec, uint32_t u32Nsec)
{
    /* Disable time stamp counter before update time value (clear EMAC_TSCTL_TSIEN_Msk) */
    EMAC->TSCTL = EMAC_TSCTL_TSEN_Msk;
    EMAC->UPDSEC = u32Sec;
    EMAC->UPDSUBSEC = EMAC_Nsec2Subsec(u32Nsec);
    EMAC->TSCTL |= (EMAC_TSCTL_TSIEN_Msk | EMAC_TSCTL_TSMODE_Msk);

}

/**
  * @brief  Enable alarm function and set alarm time
  * @param[in]  u32Sec Second value to trigger alarm
  * @param[in]  u32Nsec Nano second value to trigger alarm
  * @return None
  */
void EMAC_EnableAlarm(EMAC_T *EMAC, uint32_t u32Sec, uint32_t u32Nsec)
{

    EMAC->ALMSEC = u32Sec;
    EMAC->ALMSUBSEC = EMAC_Nsec2Subsec(u32Nsec);
    EMAC->TSCTL |= EMAC_TSCTL_TSALMEN_Msk;

}

/**
  * @brief  Disable alarm function
  * @param  None
  * @return None
  */
void EMAC_DisableAlarm(EMAC_T *EMAC)
{

    EMAC->TSCTL &= ~EMAC_TSCTL_TSALMEN_Msk;

}

/**
  * @brief  Add a offset to current time
  * @param[in]  u32Neg Offset is negative value (u32Neg == 1) or positive value (u32Neg == 0).
  * @param[in]  u32Sec Second value to add to current time
  * @param[in]  u32Nsec Nano second value to add to current time
  * @return None
  */
void EMAC_UpdateTime(EMAC_T *EMAC, uint32_t u32Neg, uint32_t u32Sec, uint32_t u32Nsec)
{
    EMAC->UPDSEC = u32Sec;
    EMAC->UPDSUBSEC = EMAC_Nsec2Subsec(u32Nsec);

    if (u32Neg)
    {
        EMAC->UPDSUBSEC |= BIT31;   /* Set bit 31 indicates this is a negative value */
    }

    EMAC->TSCTL |= EMAC_TSCTL_TSUPDATE_Msk;

}

/**
  * @brief  Check Ethernet link status
  * @param  None
  * @return Current link status, could be one of following value.
  * - \ref EMAC_LINK_DOWN
  * - \ref EMAC_LINK_100F
  * - \ref EMAC_LINK_100H
  * - \ref EMAC_LINK_10F
  * - \ref EMAC_LINK_10H
  * @note   This API should be called regularly to sync EMAC setting with real connection status
  */
uint32_t EMAC_CheckLinkStatus(EMAC_T *EMAC)
{
    uint32_t reg, ret = EMAC_LINK_DOWN;

    /* Check link valid again */
    if (EMAC_MdioRead(EMAC, PHY_STATUS_REG, EMAC_PHY_ADDR) & PHY_STATUS_LINK_VALID)
    {
        /* Check link partner capability */
        reg = EMAC_MdioRead(EMAC, PHY_ANLPA_REG, EMAC_PHY_ADDR) ;

        if (reg & PHY_ANLPA_DR100_TX_FULL)
        {
            EMAC->CTL |= EMAC_CTL_OPMODE_Msk;
            EMAC->CTL |= EMAC_CTL_FUDUP_Msk;
            ret = EMAC_LINK_100F;
        }
        else if (reg & PHY_ANLPA_DR100_TX_HALF)
        {
            EMAC->CTL |= EMAC_CTL_OPMODE_Msk;
            EMAC->CTL &= ~EMAC_CTL_FUDUP_Msk;
            ret = EMAC_LINK_100H;
        }
        else if (reg & PHY_ANLPA_DR10_TX_FULL)
        {
            EMAC->CTL &= ~EMAC_CTL_OPMODE_Msk;
            EMAC->CTL |= EMAC_CTL_FUDUP_Msk;
            ret = EMAC_LINK_10F;
        }
        else
        {
            EMAC->CTL &= ~EMAC_CTL_OPMODE_Msk;
            EMAC->CTL &= ~EMAC_CTL_FUDUP_Msk;
            ret = EMAC_LINK_10H;
        }
    }

    return ret;
}

/**
  * @brief  Fill a MAC address to list and enable.
  * @param  A MAC address
  * @return The CAM index
  * @retval -1 Failed to fill the MAC address.
  * @retval 0~(EMAC_CAMENTRY_NB-1) The index number of entry location.
  */
int32_t EMAC_FillCamEntry(EMAC_T *EMAC, uint8_t pu8MacAddr[])
{
    uint32_t *EMAC_CAMxM;
    uint32_t *EMAC_CAMxL;
    int32_t index;
    uint8_t mac[6];

    for (index = 0; index < EMAC_CAMENTRY_NB; index ++)
    {
        EMAC_CAMxM = (uint32_t *)((uint32_t)&EMAC->CAM0M + (index * 8));
        EMAC_CAMxL = (uint32_t *)((uint32_t)&EMAC->CAM0L + (index * 8));

        mac[0] = (*EMAC_CAMxM >> 24) & 0xff;
        mac[1] = (*EMAC_CAMxM >> 16) & 0xff;
        mac[2] = (*EMAC_CAMxM >> 8) & 0xff;
        mac[3] = (*EMAC_CAMxM) & 0xff;
        mac[4] = (*EMAC_CAMxL >> 24) & 0xff;
        mac[5] = (*EMAC_CAMxL >> 16) & 0xff;

        if (memcmp(mac, pu8MacAddr, sizeof(mac)) == 0)
        {
            goto exit_emac_fillcamentry;
        }

        if (*EMAC_CAMxM == 0 && *EMAC_CAMxL == 0)
        {
            break;
        }
    }

    if (index < EMAC_CAMENTRY_NB)
    {
        EMAC_EnableCamEntry(EMAC, index, pu8MacAddr);
        goto exit_emac_fillcamentry;
    }

    return -1;

exit_emac_fillcamentry:

    return index;
}

/**
  * @brief Send an Ethernet packet
  * @param[in] u32Size Packet size (without 4 byte CRC).
  * @return Packet transmit success or not
  * @retval 0 Transmit failed due to descriptor unavailable.
  * @retval 1 Triggered to transmit.
  * @note Return 1 doesn't guarantee the packet will be sent and received successfully.
  */
uint32_t EMAC_SendPktWoCopy(EMAC_MEMMGR_T *psMemMgr, uint32_t u32Size)
{
    EMAC_T *EMAC = psMemMgr->psEmac;

    /* Get Tx frame descriptor & data pointer */
    EMAC_DESCRIPTOR_T *desc = (EMAC_DESCRIPTOR_T *)psMemMgr->psNextTxDesc;
    uint32_t status = desc->u32Status1;
    uint32_t ret = 0UL;

    /* Check descriptor ownership */
    if ((status & EMAC_DESC_OWN_EMAC) != EMAC_DESC_OWN_EMAC)
    {
        /* Set Tx descriptor transmit byte count */
        desc->u32Status2 = u32Size;

        /* Change descriptor ownership to EMAC */
        desc->u32Status1 |= EMAC_DESC_OWN_EMAC;

        /* Get next Tx descriptor */
        psMemMgr->psNextTxDesc = (EMAC_DESCRIPTOR_T *)(desc->u32Next);

        /* Trigger EMAC to send the packet */
        EMAC_TRIGGER_TX(EMAC);
        ret = 1UL;
    }

    return (ret);
}

/**
  * @brief  Get avaiable TX buffer address
  * @param  None
  * @return An avaiable TX buffer.
  * @note   This API should be called before EMAC_SendPkt_WoCopy calling. Caller will do data-copy.
  */
uint8_t *EMAC_ClaimFreeTXBuf(EMAC_MEMMGR_T *psMemMgr)
{
    EMAC_DESCRIPTOR_T *desc = (EMAC_DESCRIPTOR_T *)psMemMgr->psNextTxDesc;

    if (desc->u32Status1 & EMAC_DESC_OWN_EMAC)
    {
        return (NULL);
    }
    else
    {
        return (uint8_t *)desc->u32Data;
    }
}

/**
  * @brief  Get data length of avaiable RX buffer.
  * @param  None
  * @return An data length of avaiable RX buffer.
  * @note   This API should be called before EMAC_RecvPktDone_WoTrigger calling. Caller will do data-copy.
  */
uint32_t EMAC_GetAvailRXBufSize(EMAC_MEMMGR_T *psMemMgr, uint8_t **ppuDataBuf)
{
    EMAC_DESCRIPTOR_T *desc = (EMAC_DESCRIPTOR_T *)psMemMgr->psCurrentRxDesc;

    if ((desc->u32Status1 & EMAC_DESC_OWN_EMAC) != EMAC_DESC_OWN_EMAC)   /* ownership=CPU */
    {
        uint32_t status = desc->u32Status1 >> 16;

        /* It is good and no CRC error. */
        if ((status & EMAC_RXFD_RXGD) && !(status & EMAC_RXFD_CRCE))
        {
            *ppuDataBuf = (uint8_t *)desc->u32Data;
            return desc->u32Status1 & 0xFFFFUL;
        }
        else
        {
            // Drop it
            EMAC_RecvPktDone(psMemMgr);
        }
    }

    return 0;
}


/**
  * @brief Clean up process after a packet is received.
  * @param None
  * @return None
  * @details Caller must call the function to release the resource.
  * @note Application can only call this function once every time \ref EMAC_RecvPkt or \ref EMAC_RecvPktTS returns 1
  * @note This function is without doing EMAC_TRIGGER_RX.
  */
void EMAC_RecvPktDoneWoRxTrigger(EMAC_MEMMGR_T *psMemMgr)
{
    /* Get Rx Frame Descriptor */
    EMAC_DESCRIPTOR_T *desc = (EMAC_DESCRIPTOR_T *)psMemMgr->psCurrentRxDesc;

    /* Restore descriptor link list and data pointer they will be overwrite if time stamp enabled */
    desc->u32Data = desc->u32Backup1;
    desc->u32Next = desc->u32Backup2;

    /* Change ownership to DMA for next use */
    desc->u32Status1 |= EMAC_DESC_OWN_EMAC;

    /* Get Next Frame Descriptor pointer to process */
    desc = (EMAC_DESCRIPTOR_T *)desc->u32Next;

    /* Save last processed Rx descriptor */
    psMemMgr->psCurrentRxDesc = desc;
}


/*@}*/ /* end of group EMAC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group EMAC_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
