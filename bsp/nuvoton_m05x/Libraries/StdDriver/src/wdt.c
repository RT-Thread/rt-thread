/**************************************************************************//**
 * @file     wdt.c
 * @version  V3.00
 * $Revision: 2 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series WDT driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M051Series.h"


/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_WDT_Driver WDT Driver
  @{
*/

/** @addtogroup M051_WDT_EXPORTED_FUNCTIONS WDT Exported Functions
  @{
*/

/**
  * @brief      Initialize WDT counter and start counting
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
  * @param[in]  u32ResetDelay       Configure reset delay period while WDT time-out happened. Valid values are:
  *                                 - \ref WDT_RESET_DELAY_1026CLK
  *                                 - \ref WDT_RESET_DELAY_130CLK
  *                                 - \ref WDT_RESET_DELAY_18CLK
  *                                 - \ref WDT_RESET_DELAY_3
  * @param[in]  u32EnableReset      Enable WDT rest system function. Valid values are TRUE and FALSE.
  * @param[in]  u32EnableWakeup     Enable WDT wake-up system function. Valid values are TRUE and FALSE.
  *
  * @return     None
  *
  * @details    This function make WDT module start counting with different time-out interval and reset delay period.
  */
void WDT_Open(uint32_t u32TimeoutInterval,
              uint32_t u32ResetDelay,
              uint32_t u32EnableReset,
              uint32_t u32EnableWakeup)
{
    WDT->WTCRALT = u32ResetDelay;

    WDT->WTCR = u32TimeoutInterval | WDT_WTCR_WTE_Msk |
                (u32EnableReset << WDT_WTCR_WTRE_Pos) |
                (u32EnableWakeup << WDT_WTCR_WTWKE_Pos);
    return;
}

/*@}*/ /* end of group M051_WDT_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_WDT_Driver */

/*@}*/ /* end of group M051_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
