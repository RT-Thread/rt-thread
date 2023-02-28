/**************************************************************************//**
 * @file     kpi.c
 * @brief    KPI driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include <stdio.h>
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup KPI_Driver KPI Driver
  @{
*/

/** @addtogroup KPI_EXPORTED_FUNCTIONS KPI Exported Functions
  @{
*/


/// @cond HIDDEN_SYMBOLS
#define KPICONF_VALUE   0x00288059
/// @endcond HIDDEN_SYMBOLS


/**
  * @brief   Open KPI function.
  *
  * @return   TRUE:  Success  \n
  *           FALSE:  KPI function already open
  *
  */
void KPI_Open(KPI_T *kpi, uint32_t u32Row, uint32_t u32Col)
{
    uint32_t u32Reg;

    kpi->KPICONF = 0x0;
    kpi->KPI3KCONF = 0x0;
    kpi->KPIRSTC = 0x0;

    if (u32Row < 2)
        u32Row = 1;
    else if (u32Row > 6)
        u32Row = 6;
    else
        u32Row = u32Row - 1;

    if (u32Col < 2)
        u32Col = 1;
    else if (u32Col > 8)
        u32Col = 8;
    else
        u32Col = u32Col - 1;

    u32Reg = (KPICONF_VALUE | (u32Row << 28) | (u32Col << 24));
    kpi->KPICONF = u32Reg;
}

/**
  * @brief   Close KPI function.
  *
  * @return   Successful:  Success   \n
  *           kpiNotOpen:  KPI function not open
  */
void KPI_Close(KPI_T *kpi)
{
    kpi->KPICONF &= ~KPI_KPICONF_ENKP_Msk;
}


/**
  * @brief   Config KPI scan key timing.
  *
  * @param[in]    u32PreScale: Row Scan Cycle Pre-scale Value. The divided number is from 1 to 256
  * @param[in]    u32Debounce:  De-bounce Sampling Cycle. The value is from 3 to 13
  * @param[in]    u32ScanDelay: Setting delay cycle when row change:
  *               \ref KPI_ROW_SCAN_DELAY4CLK
  *               \ref KPI_ROW_SCAN_DELAY8CLK
  *               \ref KPI_ROW_SCAN_DELAY16CLK
  *               \ref KPI_ROW_SCAN_DELAY32CLK
  *
  * @return   None
  *
  */
void KPI_ConfigKeyScanTiming(KPI_T *kpi, uint32_t u32PreScale, uint32_t u32Debounce, uint32_t u32ScanDelay)
{
    if (u32Debounce < 3)  u32Debounce = 3;
    if (u32Debounce > 13) u32Debounce = 13;

    kpi->KPICONF &= ~(KPI_KPICONF_PRESCALE_Msk | KPI_KPICONF_DBCLKSEL_Msk | KPI_KPICONF_SCANROWD_Msk);
    kpi->KPICONF |= (u32PreScale << KPI_KPICONF_PRESCALE_Pos) | (u32Debounce << KPI_KPICONF_DBCLKSEL_Pos) |
                    (u32ScanDelay << KPI_KPICONF_SCANROWD_Pos);
}

/**
  * @brief   Read KPI Release key Status.
  *
  * @param[in]    u32Key1: \ref KPI_KEY00 ~ \ref KPI_KEY58
  * @param[in]    u32Key2: \ref KPI_KEY00 ~ \ref KPI_KEY58
  * @param[in]    u32Key3: \ref KPI_KEY00 ~ \ref KPI_KEY58
  * @param[in]    u32RSTC: Reset Period Count. The value is from 0 ~ 255.
  *
  * @return   None
  */
void KPI_Set3KeyReset(KPI_T *kpi, uint32_t u32Key1, uint32_t u32Key2, uint32_t u32Key3, uint32_t u32RstCnt)
{
    kpi->KPI3KCONF &= ~(KPI_KPI3KCONF_K30C_Msk | KPI_KPI3KCONF_K30R_Msk |
                        KPI_KPI3KCONF_K31C_Msk | KPI_KPI3KCONF_K31R_Msk |
                        KPI_KPI3KCONF_K32C_Msk | KPI_KPI3KCONF_K32R_Msk);

    // Set Key
    kpi->KPI3KCONF |= ((u32Key1 / 8) << 3) | (u32Key1 % 8);
    kpi->KPI3KCONF |= ((((u32Key1 / 8) << 3) | (u32Key1 % 8)) << 8);
    kpi->KPI3KCONF |= ((((u32Key1 / 8) << 3) | (u32Key1 % 16)) << 8);

    // Set Reset Period Count
    kpi->KPIRSTC = u32RstCnt;

    // Enable 3Key Reset
    kpi->KPI3KCONF |= KPI_KPI3KCONF_EN3KYRST_Msk;
}

/*@}*/ /* end of group KPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group KPI_Driver */

/*@}*/ /* end of group Standard_Driver */




