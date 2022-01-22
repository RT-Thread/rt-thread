/**************************************************************************//**
 * @file     wwdt.c
 * @version  V3.00
 * @brief    Window Watchdog Timer(WWDT) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup WWDT_Driver WWDT Driver
  @{
*/

/** @addtogroup WWDT_EXPORTED_FUNCTIONS WWDT Exported Functions
  @{
*/

/**
  * @brief      Open WWDT and start counting
  *
  * @param[in]  u32PreScale     Pre-scale setting of WWDT counter. Valid values are:
  *                             - \ref WWDT_PRESCALER_1
  *                             - \ref WWDT_PRESCALER_2
  *                             - \ref WWDT_PRESCALER_4
  *                             - \ref WWDT_PRESCALER_8
  *                             - \ref WWDT_PRESCALER_16
  *                             - \ref WWDT_PRESCALER_32
  *                             - \ref WWDT_PRESCALER_64
  *                             - \ref WWDT_PRESCALER_128
  *                             - \ref WWDT_PRESCALER_192
  *                             - \ref WWDT_PRESCALER_256
  *                             - \ref WWDT_PRESCALER_384
  *                             - \ref WWDT_PRESCALER_512
  *                             - \ref WWDT_PRESCALER_768
  *                             - \ref WWDT_PRESCALER_1024
  *                             - \ref WWDT_PRESCALER_1536
  *                             - \ref WWDT_PRESCALER_2048
  * @param[in]  u32CmpValue     Setting the window compared value. Valid values are between 0x0 to 0x3F.
  * @param[in]  u32EnableInt    Enable WWDT time-out interrupt function. Valid values are TRUE and FALSE.
  *
  * @return     None
  *
  * @details    This function makes WWDT module start counting with different counter period by pre-scale setting and compared window value.
  * @note       Application can call this function only once after boot up.
  */
void WWDT_Open(uint32_t u32PreScale,
               uint32_t u32CmpValue,
               uint32_t u32EnableInt)
{
    WWDT->CTL = u32PreScale |
                (u32CmpValue << WWDT_CTL_CMPDAT_Pos) |
                ((u32EnableInt == (uint32_t)TRUE) ? WWDT_CTL_INTEN_Msk : 0UL) |
                WWDT_CTL_WWDTEN_Msk;
}

/**@}*/ /* end of group WWDT_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group WWDT_Driver */

/**@}*/ /* end of group Standard_Driver */

