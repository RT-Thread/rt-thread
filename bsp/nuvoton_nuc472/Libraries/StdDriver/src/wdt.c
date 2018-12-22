/**************************************************************************//**
 * @file     wdt.c
 * @version  V1.00
 * $Revision: 9 $
 * $Date: 15/11/12 9:49a $
 * @brief    NUC472/NUC442 WDT driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC472_442.h"

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_WDT_Driver WDT Driver
  @{
*/


/** @addtogroup NUC472_442_WDT_EXPORTED_FUNCTIONS WDT Exported Functions
  @{
*/

/**
 * @brief This function make WDT module start counting with different time-out interval
 * @param[in] u32TimeoutInterval  Time-out interval period of WDT module. Valid values are:
 *                - \ref WDT_TIMEOUT_2POW4
 *                - \ref WDT_TIMEOUT_2POW6
 *                - \ref WDT_TIMEOUT_2POW8
 *                - \ref WDT_TIMEOUT_2POW10
 *                - \ref WDT_TIMEOUT_2POW12
 *                - \ref WDT_TIMEOUT_2POW14
 *                - \ref WDT_TIMEOUT_2POW16
 *                - \ref WDT_TIMEOUT_2POW18
 * @param[in] u32ResetDelay Reset delay period while WDT time-out happened. Valid values are:
 *                - \ref WDT_RESET_DELAY_3CLK
 *                - \ref WDT_RESET_DELAY_18CLK
 *                - \ref WDT_RESET_DELAY_130CLK
 *                - \ref WDT_RESET_DELAY_1026CLK
 * @param[in] u32EnableReset Enable WDT rest system function. Valid values are \ref TRUE and \ref FALSE
 * @param[in] u32EnableWakeup Enable WDT wake-up system function. Valid values are \ref TRUE and \ref FALSE
 * @return None
 */
void  WDT_Open(uint32_t u32TimeoutInterval,
               uint32_t u32ResetDelay,
               uint32_t u32EnableReset,
               uint32_t u32EnableWakeup)
{

    WDT->CTL = u32TimeoutInterval | WDT_CTL_WDTEN_Msk |
               (u32EnableReset << WDT_CTL_RSTEN_Pos) |
               (u32EnableWakeup << WDT_CTL_WKEN_Pos);
    WDT->ALTCTL = u32ResetDelay;
    return;
}


/*@}*/ /* end of group NUC472_442_WDT_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_WDT_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
