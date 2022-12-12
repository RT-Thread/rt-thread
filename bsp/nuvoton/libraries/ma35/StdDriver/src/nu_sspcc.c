/**************************************************************************//**
 * @file     sspcc.c
 * @brief    SSPCC driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SSPCC_Driver SSPCC Driver
  @{
*/

/** @addtogroup SSPCC_EXPORTED_FUNCTIONS SSPCC Exported Functions
  @{
*/

/**
 * @brief       Set Peripheral Realm
 *
 * @param[in]   u32Perip    SSPCC Peripheral ID.
 * @param[in]   u32Realm    Security set(Realm).  It could be \n
 *                          SSPCC_SSET_TZS, SSPCC_SSET_TZNS, SSPCC_SSET_SUBM.
 *
 * @return      None
 *
 * @details     This function is used to set specified realm.
 */
void SSPCC_SetRealm(uint32_t u32Perip, uint32_t u32Realm)
{
    vu32 *pu32SSet = (vu32 *)(SSPCC_BASE + (u32Perip >> SSPCC_REG_Pos));
    uint32_t u32Pos = u32Perip & SSPCC_PS_Msk;

    *pu32SSet = (*pu32SSet & ~(SSPCC_SSET_Msk << u32Pos)) | (u32Realm << u32Pos);
}

/**
 * @brief       Get Peripheral Realm
 *
 * @param[in]   u32Perip    SSPCC Peripheral ID.
 * @param[out]  u32Realm    Security set(Realm).  It could be \n
 *                          SSPCC_SSET_TZS, SSPCC_SSET_TZNS, SSPCC_SSET_SUBM.
 *
 * @return      None
 *
 * @details     This function is used to get specified realm.
 */
uint32_t SSPCC_GetRealm(uint32_t u32Perip)
{
    vu32 *pu32SSet = (vu32 *)(SSPCC_BASE + (u32Perip >> SSPCC_REG_Pos));
    uint32_t u32Pos = u32Perip & SSPCC_PS_Msk;

    return (*pu32SSet & (SSPCC_SSET_Msk << u32Pos)) >> u32Pos;
}

/**
 * @brief       Set Pin Realm
 *
 * @param[in]   u32PortBA   GPIO port. It could be GPIOA_BASE, GPIOB_BASE, ..., GPIOM_BASE and GPION_BASE.
 * @param[in]   u32Pin      It could be 0 ~ 15 for PA, PB, ..., PM and PN GPIO ports.
 * @param[in]   u32Realm    realm.  It could be \n
 *                          SSPCC_SSET_TZS, SSPCC_SSET_TZNS, SSPCC_SSET_SUBM.
 *
 * @return      None
 *
 * @details     This function is used to set specified IO realm.
 */
void SSPCC_SetRealm_GPIO(uint32_t u32PortBA, uint32_t u32Pin, uint32_t u32Realm)
{
    uint32_t u32PortIdx = (u32PortBA - GPIO_BASE) / 0x40;
    vu32 *avu32IOSecuritySet = (vu32 *)&SSPCC->IOASSET;

    avu32IOSecuritySet[u32PortIdx] = (avu32IOSecuritySet[u32PortIdx] & ~(SSPCC_SSET_Msk << (u32Pin << 1))) | (u32Realm << (u32Pin << 1));
}

/**
 * @brief       Get Pin Realm
 *
 * @param[in]   u32PortBA   GPIO port. It could be GPIOA_BASE, GPIOB_BASE, ..., GPIOM_BASE and GPION_BASE.
 * @param[in]   u32Pin      It could be 0 ~ 15 for PA, PB, ..., PM and PN GPIO ports.
 *
 * @return      It could be \n
 *              SSPCC_SSET_TZS, SSPCC_SSET_TZNS, SSPCC_SSET_SUBM.
 *
 * @details     This function is used to set specified IO realm.
 */
uint32_t SSPCC_GetRealm_GPIO(uint32_t u32PortBA, uint32_t u32Pin)
{
    uint32_t u32PortIdx = (u32PortBA - GPIO_BASE) / 0x40;
    vu32 *avu32IOSecuritySet = (vu32 *)&SSPCC->IOASSET;
    uint32_t u32Ret = avu32IOSecuritySet[u32PortIdx] & (SSPCC_SSET_Msk << (u32Pin << 1));

    return u32Ret >> (u32Pin << 1);
}

/*@}*/ /* end of group SSPCC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SSPCC_Driver */

/*@}*/ /* end of group Standard_Driver */

