/**************************************************************************//**
 * @file     crc.c
 * @version  V3.00
 * @brief    Cyclic Redundancy Check(CRC) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


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
  * @brief      CRC Open
  *
  * @param[in]  u32Mode         CRC operation polynomial mode. Valid values are:
  *                             - \ref CRC_CCITT
  *                             - \ref CRC_8
  *                             - \ref CRC_16
  *                             - \ref CRC_32
  * @param[in]  u32Attribute    CRC operation data attribute. Valid values are combined with:
  *                             - \ref CRC_CHECKSUM_COM
  *                             - \ref CRC_CHECKSUM_RVS
  *                             - \ref CRC_WDATA_COM
  *                             - \ref CRC_WDATA_RVS
  * @param[in]  u32Seed         Seed value.
  * @param[in]  u32DataLen      CPU Write Data Length. Valid values are:
  *                             - \ref CRC_CPU_WDATA_8
  *                             - \ref CRC_CPU_WDATA_16
  *                             - \ref CRC_CPU_WDATA_32
  *
  * @return     None
  *
  * @details    This function will enable the CRC controller by specify CRC operation mode, attribute, initial seed and write data length. \n
  *             After that, user can start to perform CRC calculate by calling CRC_WRITE_DATA macro or CRC_DAT register directly.
  */
void CRC_Open(uint32_t u32Mode, uint32_t u32Attribute, uint32_t u32Seed, uint32_t u32DataLen)
{
    CRC->SEED = u32Seed;

    switch (u32Mode)
    {
    case CRC_CCITT:
        u32Mode = CRC_16;
        CRC->POLYNOMIAL = 0x1021;
        break;
    case CRC_8:
        CRC->POLYNOMIAL = 0x7;
        break;
    case CRC_16:
        CRC->POLYNOMIAL = 0x8005;
        break;
    case CRC_32:
        CRC->POLYNOMIAL = 0x04C11DB7;
        break;
    default:
        CRC->POLYNOMIAL = 0x0ul;
        break;
    }

    CRC->CTL = u32Mode | u32Attribute | u32DataLen | CRC_CTL_CRCEN_Msk;

    /* Setting CHKSINIT bit will reload the initial seed value(CRC_SEED register) to CRC controller */
    CRC->CTL |= CRC_CTL_CHKSINIT_Msk;
}

/**
  * @brief      Get CRC Checksum
  *
  * @param[in]  None
  *
  * @return     Checksum Result
  *
  * @details    This function gets the CRC checksum result by current CRC polynomial mode.
  */
uint32_t CRC_GetChecksum(void)
{
    uint32_t u32Checksum = 0UL;

    switch (CRC->CTL & CRC_CTL_CRCMODE_Msk)
    {
    case CRC_CCITT:
    case CRC_16:
        u32Checksum = (CRC->CHECKSUM & 0xFFFFUL);
        break;

    case CRC_32:
        u32Checksum = CRC->CHECKSUM;
        break;

    case CRC_8:
        u32Checksum = (CRC->CHECKSUM & 0xFFUL);
        break;

    default:
        break;
    }

    return u32Checksum;
}

/**@}*/ /* end of group CRC_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group CRC_Driver */

/**@}*/ /* end of group Standard_Driver */
