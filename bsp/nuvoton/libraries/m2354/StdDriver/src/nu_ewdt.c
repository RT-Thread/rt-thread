/**************************************************************************//**
 * @file     ewdt.c
 * @version  V3.00
 * @brief    Extra Watchdog Timer(EWDT) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EWDT_Driver EWDT Driver
  @{
*/

/** @addtogroup EWDT_EXPORTED_FUNCTIONS EWDT Exported Functions
  @{
*/

/**
  * @brief      Initialize EWDT and start counting
  *
  * @param[in]  u32TimeoutInterval  Time-out interval period of EWDT module. Valid values are:
  *                                 - \ref EWDT_TIMEOUT_2POW4
  *                                 - \ref EWDT_TIMEOUT_2POW6
  *                                 - \ref EWDT_TIMEOUT_2POW8
  *                                 - \ref EWDT_TIMEOUT_2POW10
  *                                 - \ref EWDT_TIMEOUT_2POW12
  *                                 - \ref EWDT_TIMEOUT_2POW14
  *                                 - \ref EWDT_TIMEOUT_2POW16
  *                                 - \ref EWDT_TIMEOUT_2POW18
  *                                 - \ref EWDT_TIMEOUT_2POW20
  * @param[in]  u32ResetDelay       Configure EWDT time-out reset delay period. Valid values are:
  *                                 - \ref EWDT_RESET_DELAY_1026CLK
  *                                 - \ref EWDT_RESET_DELAY_130CLK
  *                                 - \ref EWDT_RESET_DELAY_18CLK
  *                                 - \ref EWDT_RESET_DELAY_3CLK
  * @param[in]  u32EnableReset      Enable EWDT time-out reset system function. Valid values are TRUE and FALSE.
  * @param[in]  u32EnableWakeup     Enable EWDT time-out wake-up system function. Valid values are TRUE and FALSE.
  *
  * @return     None
  *
  * @details    This function makes EWDT module start counting with different time-out interval, reset delay period and choose to \n
  *             enable or disable EWDT time-out reset system or wake-up system.
  * @note       Please make sure that Register Write-Protection Function has been disabled before using this function.
  */
void EWDT_Open(uint32_t u32TimeoutInterval,
               uint32_t u32ResetDelay,
               uint32_t u32EnableReset,
               uint32_t u32EnableWakeup)
{
    EWDT->ALTCTL = u32ResetDelay;

    EWDT->CTL = u32TimeoutInterval | EWDT_CTL_WDTEN_Msk |
                (u32EnableReset << EWDT_CTL_RSTEN_Pos) |
                (u32EnableWakeup << EWDT_CTL_WKEN_Pos);

    while((EWDT->CTL & EWDT_CTL_SYNC_Msk) == EWDT_CTL_SYNC_Msk) {} /* Wait enable WDTEN bit completed, it needs 2 * EWDT_CLK. */
}

/**@}*/ /* end of group EWDT_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group EWDT_Driver */

/**@}*/ /* end of group Standard_Driver */
