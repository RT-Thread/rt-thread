/**************************************************************************//**
 * @file     wwdt.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 15/08/11 10:26a $
 * @brief    M451 series WWDT driver source file
 *
 * @note
 * Copyright (C) 2013~2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M451Series.h"


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
  * @note       This WWDT_CTL register can be write only one time after chip is powered on or reset.
  */
void WWDT_Open(uint32_t u32PreScale,
               uint32_t u32CmpValue,
               uint32_t u32EnableInt)
{
    WWDT->CTL = u32PreScale |
                (u32CmpValue << WWDT_CTL_CMPDAT_Pos) |
                ((u32EnableInt == TRUE) ? WWDT_CTL_INTEN_Msk : 0) |
                WWDT_CTL_WWDTEN_Msk;
    return;
}

/*@}*/ /* end of group WWDT_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group WWDT_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2013~2015 Nuvoton Technology Corp. ***/
