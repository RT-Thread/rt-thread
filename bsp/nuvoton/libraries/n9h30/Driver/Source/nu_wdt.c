/**************************************************************************//**
 * @file     wdt.c
 * @brief    NUC980 series WDT driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "nu_wdt.h"

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
void WDT_Open(UINT32 u32TimeoutInterval,
              UINT32 u32ResetDelay,
              UINT32 u32EnableReset,
              UINT32 u32EnableWakeup)
{

    outpw(REG_WDT_ALTCTL, u32ResetDelay);
    outpw(REG_WDT_CTL, u32TimeoutInterval | 0x80 |
          (u32EnableReset << 1) |
          (u32EnableWakeup << 4));
    return;
}

/*@}*/ /* end of group WDT_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group WDT_Driver */

/*@}*/ /* end of group Standard_Driver */

