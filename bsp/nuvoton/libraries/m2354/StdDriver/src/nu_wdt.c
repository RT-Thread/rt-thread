/**************************************************************************//**
 * @file     wdt.c
 * @version  V3.00
 * @brief    Watchdog Timer(WDT) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup WDT_Driver WDT Driver
  @{
*/

/** @addtogroup WDT_EXPORTED_FUNCTIONS WDT Exported Functions
  @{
*/

/**
  * @brief      Initialize WDT and start counting
  *
  * @param[in]  u32TimeoutInterval  Time-out interval period of WDT module. Valid values are:
  *                                 - \ref WDT_TIMEOUT_2POW4
  *                                 - \ref WDT_TIMEOUT_2POW6
  *                                 - \ref WDT_TIMEOUT_2POW8
  *                                 - \ref WDT_TIMEOUT_2POW10
  *                                 - \ref WDT_TIMEOUT_2POW12
  *                                 - \ref WDT_TIMEOUT_2POW14
  *                                 - \ref WDT_TIMEOUT_2POW16
  *                                 - \ref WDT_TIMEOUT_2POW18
  *                                 - \ref WDT_TIMEOUT_2POW20
  * @param[in]  u32ResetDelay       Configure WDT time-out reset delay period. Valid values are:
  *                                 - \ref WDT_RESET_DELAY_1026CLK
  *                                 - \ref WDT_RESET_DELAY_130CLK
  *                                 - \ref WDT_RESET_DELAY_18CLK
  *                                 - \ref WDT_RESET_DELAY_3CLK
  * @param[in]  u32EnableReset      Enable WDT time-out reset system function. Valid values are TRUE and FALSE.
  * @param[in]  u32EnableWakeup     Enable WDT time-out wake-up system function. Valid values are TRUE and FALSE.
  *
  * @return     None
  *
  * @details    This function makes WDT module start counting with different time-out interval, reset delay period and choose to \n
  *             enable or disable WDT time-out reset system or wake-up system.
  * @note       Please make sure that Register Write-Protection Function has been disabled before using this function.
  */
void WDT_Open(uint32_t u32TimeoutInterval,
              uint32_t u32ResetDelay,
              uint32_t u32EnableReset,
              uint32_t u32EnableWakeup)
{
    WDT->ALTCTL = u32ResetDelay;

    WDT->CTL = u32TimeoutInterval | WDT_CTL_WDTEN_Msk |
               (u32EnableReset << WDT_CTL_RSTEN_Pos) |
               (u32EnableWakeup << WDT_CTL_WKEN_Pos);

    while((WDT->CTL & WDT_CTL_SYNC_Msk) == WDT_CTL_SYNC_Msk) {} /* Wait enable WDTEN bit completed, it needs 2 * WDT_CLK. */
}

/**@}*/ /* end of group WDT_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group WDT_Driver */

/**@}*/ /* end of group Standard_Driver */

