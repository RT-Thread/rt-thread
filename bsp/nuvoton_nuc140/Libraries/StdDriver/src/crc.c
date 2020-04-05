/**************************************************************************//**
 * @file     crc.c
 * @version  V3.00
 * $Revision: 2 $
 * $Date: 15/05/04 3:27p $
 * @brief    CRC driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC100Series.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CRC_Driver CRC Driver
  @{
*/

/** @addtogroup CRC_EXPORTED_FUNCTIONS CRC Exported Functions
  @{
*/

/**
 * @brief       CRC Open
 *
 * @param[in]   u32Mode         CRC Polynomial Mode. CRC_CCITT, CRC_8, CRC_16, CRC_32
 * @param[in]   u32Attribute    Parameter attribute. CRC_CHECKSUM_COM, CRC_CHECKSUM_RVS, CRC_WDATA_COM, CRC_WDATA_RVS
 * @param[in]   u32Seed         Seed value.
 * @param[in]   u32DataLen      CPU Write Data Length. CRC_CPU_WDATA_8, CRC_CPU_WDATA_16, CRC_CPU_WDATA_32
 *
 * @return      None
 *
 * @details     This function enable the CRC channel by specify CRC mode, attribute, initial seed and write data length.
 */
void CRC_Open(uint32_t u32Mode, uint32_t u32Attribute, uint32_t u32Seed, uint32_t u32DataLen)
{
    /* Enable CRC channel clock */
    PDMA_GCR->GCRCSR |= PDMA_GCRCSR_CRC_CLK_EN_Msk;

    CRC->SEED = u32Seed;
    CRC->CTL = u32Mode | u32Attribute | u32DataLen | CRC_CTL_CRCCEN_Msk;

    /* Setting RST bit will reload the initial seed value (CRC_SEED register) */
    CRC->CTL |= CRC_CTL_CRC_RST_Msk;
}

/**
 * @brief       CRC Start DMA transfer
 *
 * @param[in]   u32SrcAddr      Source address
 * @param[in]   u32ByteCount    Calculate byte count
 *
 * @return      None
 *
 * @details     This function start CRC DMA transfer from specify source address and byte counts.
 */
void CRC_StartDMATransfer(uint32_t u32SrcAddr, uint32_t u32ByteCount)
{
    CRC->DMASAR = u32SrcAddr;
    CRC->DMABCR = u32ByteCount;
    CRC->CTL |= CRC_CTL_TRIG_EN_Msk;
}

/**
 * @brief       Get CRC Checksum
 *
 * @param[in]   None
 *
 * @return      Checksum
 *
 * @details     This macro get the CRC checksum result by current CRC polynomial mode.
 */
uint32_t CRC_GetChecksum(void)
{
    switch(CRC->CTL & CRC_CTL_CRC_MODE_Msk)
    {
    case CRC_CCITT:
    case CRC_16:
        return (CRC->CHECKSUM & 0xFFFF);

    case CRC_32:
        return (CRC->CHECKSUM);

    case CRC_8:
        return (CRC->CHECKSUM & 0xFF);

    default:
        return 0;
    }
}

/*@}*/ /* end of group CRC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CRC_Driver */

/*@}*/ /* end of group Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
