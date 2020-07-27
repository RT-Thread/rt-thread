/**************************************************************************//**
 * @file     crc.c
 * @version  V1.00
 * @brief     M480 CRC driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
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
  * @details    This macro gets the CRC checksum result by current CRC polynomial mode.
  */
uint32_t CRC_GetChecksum(void)
{
    uint32_t ret;

    switch(CRC->CTL & CRC_CTL_CRCMODE_Msk)
    {
    case CRC_CCITT:
    case CRC_16:
        ret = (CRC->CHECKSUM & 0xFFFFU);
        break;
    case CRC_32:
        ret = (CRC->CHECKSUM);
        break;
    case CRC_8:
        ret = (CRC->CHECKSUM & 0xFFU);
        break;
    default:
        ret = 0U;
        break;
    }

    return ret;
}

/*@}*/ /* end of group CRC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CRC_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
