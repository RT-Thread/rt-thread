/**************************************************************************//**
 * @file     ewwdt.c
 * @version  V3.00
 * @brief    Extra Window Watchdog Timer(EWWDT) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EWWDT_Driver EWWDT Driver
  @{
*/

/** @addtogroup EWWDT_EXPORTED_FUNCTIONS EWWDT Exported Functions
  @{
*/

/**
  * @brief      Open EWWDT and start counting
  *
  * @param[in]  u32PreScale     Pre-scale setting of EWWDT counter. Valid values are:
  *                             - \ref EWWDT_PRESCALER_1
  *                             - \ref EWWDT_PRESCALER_2
  *                             - \ref EWWDT_PRESCALER_4
  *                             - \ref EWWDT_PRESCALER_8
  *                             - \ref EWWDT_PRESCALER_16
  *                             - \ref EWWDT_PRESCALER_32
  *                             - \ref EWWDT_PRESCALER_64
  *                             - \ref EWWDT_PRESCALER_128
  *                             - \ref EWWDT_PRESCALER_192
  *                             - \ref EWWDT_PRESCALER_256
  *                             - \ref EWWDT_PRESCALER_384
  *                             - \ref EWWDT_PRESCALER_512
  *                             - \ref EWWDT_PRESCALER_768
  *                             - \ref EWWDT_PRESCALER_1024
  *                             - \ref EWWDT_PRESCALER_1536
  *                             - \ref EWWDT_PRESCALER_2048
  * @param[in]  u32CmpValue     Setting the window compared value. Valid values are between 0x0 to 0x3F.
  * @param[in]  u32EnableInt    Enable WWDT time-out interrupt function. Valid values are TRUE and FALSE.
  *
  * @return     None
  *
  * @details    This function makes EWWDT module start counting with different counter period by pre-scale setting and compared window value.
  * @note       Application can call this function only once after boot up.
  */
void EWWDT_Open(uint32_t u32PreScale,
                uint32_t u32CmpValue,
                uint32_t u32EnableInt)
{
    EWWDT->CTL = u32PreScale |
                 (u32CmpValue << EWWDT_CTL_CMPDAT_Pos) |
                 ((u32EnableInt == (uint32_t)TRUE) ? EWWDT_CTL_INTEN_Msk : 0UL) |
                 EWWDT_CTL_WWDTEN_Msk;
}

/**@}*/ /* end of group EWWDT_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group EWWDT_Driver */

/**@}*/ /* end of group Standard_Driver */

