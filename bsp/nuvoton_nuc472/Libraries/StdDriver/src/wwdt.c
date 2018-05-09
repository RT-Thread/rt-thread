/**************************************************************************//**
 * @file     wwdt.c
 * @version  V1.00
 * $Revision: 6 $
 * $Date: 14/10/02 7:19p $
 * @brief    NUC472/NUC442 WWDT driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC472_442.h"

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_WWDT_Driver WWDT Driver
  @{
*/


/** @addtogroup NUC472_442_WWDT_EXPORTED_FUNCTIONS WWDT Exported Functions
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
void WWDT_Open(uint32_t u32PreScale, uint32_t u32CmpValue, uint32_t u32EnableInt)
{
    WWDT->CTL = u32PreScale |
                (u32CmpValue << WWDT_CTL_CMPDAT_Pos)|
                WWDT_CTL_WWDTEN_Msk |
                (u32EnableInt ? WWDT_CTL_INTEN_Msk : 0);
    return;
}




/*@}*/ /* end of group NUC472_442_WWDT_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_WWDT_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
