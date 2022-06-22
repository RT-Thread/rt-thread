/**************************************************************************//**
 * @file     wwdt.c
 * @brief    NUC980 WWDT driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "nu_wwdt.h"

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
 * @brief This function make WWDT module start counting with different counter period and compared window value
 * @param[in] u32PreScale  Prescale period for the WWDT counter period. Valid values are:
 *              - \ref WWDT_PRESCALER_1
 *              - \ref WWDT_PRESCALER_2
 *              - \ref WWDT_PRESCALER_4
 *              - \ref WWDT_PRESCALER_8
 *              - \ref WWDT_PRESCALER_16
 *              - \ref WWDT_PRESCALER_32
 *              - \ref WWDT_PRESCALER_64
 *              - \ref WWDT_PRESCALER_128
 *              - \ref WWDT_PRESCALER_192
 *              - \ref WWDT_PRESCALER_256
 *              - \ref WWDT_PRESCALER_384
 *              - \ref WWDT_PRESCALER_512
 *              - \ref WWDT_PRESCALER_768
 *              - \ref WWDT_PRESCALER_1024
 *              - \ref WWDT_PRESCALER_1536
 *              - \ref WWDT_PRESCALER_2048
 * @param[in] u32CmpValue Window compared value. Valid values are between 0x0 to 0x3F
 * @param[in] u32EnableInt Enable WWDT interrupt or not. Valid values are \ref TRUE and \ref FALSE
 * @return None
 * @note Application can call this function can only once after boot up
 */
void WWDT_Open(UINT u32PreScale, UINT u32CmpValue, UINT u32EnableInt)
{
    UINT reg;
    reg = u32PreScale |
          (u32CmpValue << 16) |
          0x1 | // enable
          (u32EnableInt ? 0x2 : 0);
    outpw(REG_WWDT_CTL, reg);

    return;
}



/*@}*/ /* end of group WWDT_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group WWDT_Driver */

/*@}*/ /* end of group Standard_Driver */

