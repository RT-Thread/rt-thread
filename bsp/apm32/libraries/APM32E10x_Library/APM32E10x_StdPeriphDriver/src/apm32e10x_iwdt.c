/*!
 * @file        apm32e10x_iwdt.c
 *
 * @brief       This file provides all the IWDT firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32e10x_iwdt.h"

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup IWDT_Driver
  * @brief IWDT driver modules
  @{
*/

/** @defgroup IWDT_Functions Functions
  @{
*/

/*!
 * @brief        Enable IWDT
 *
 * @param        None
 *
 * @retval       None
 */
void IWDT_Enable(void)
{
    IWDT->KEY = IWDT_KEYWORD_ENABLE;
}

/*!
 * @brief        Reload the IWDT counter with value
 *
 * @param        None
 *
 * @retval       None
 */
void IWDT_Refresh(void)
{
    IWDT->KEY = IWDT_KEYWORD_RELOAD;
}

/*!
 * @brief        Set IWDT count reload values
 *
 * @param        reload: IWDT count reload values
 *
 * @retval       None
 */
void IWDT_ConfigReload(uint16_t reload)
{
    IWDT->CNTRLD = reload;
}

/*!
 * @brief        Enable the IWDT write access
 *
 * @param        None
 *
 * @retval       None
 */
void IWDT_EnableWriteAccess(void)
{
    IWDT->KEY_B.KEY = IWDT_WRITEACCESS_ENABLE;
}

/*!
 * @brief        Disable the IWDT write access
 *
 * @param        None
 *
 * @retval       None
 */
void IWDT_DisableWriteAccess(void)
{
    IWDT->KEY_B.KEY = IWDT_WRITEACCESS_DISABLE;
}

/*!
 * @brief        Set IWDT frequency divider values
 *
 * @param        div: IWDT frequency divider values
 *                    This parameter can be one of the following values:
 *                    @arg IWDT_DIVIDER_4  : prescaler divider equal to 4
 *                    @arg IWDT_DIVIDER_8  : prescaler divider equal to 8
 *                    @arg IWDT_DIVIDER_16 : prescaler divider equal to 16
 *                    @arg IWDT_DIVIDER_32 : prescaler divider equal to 32
 *                    @arg IWDT_DIVIDER_64 : prescaler divider equal to 64
 *                    @arg IWDT_DIVIDER_128: prescaler divider equal to 128
 *                    @arg IWDT_DIVIDER_256: prescaler divider equal to 256
 *
 * @retval       None
 */
void IWDT_ConfigDivider(uint8_t div)
{
    IWDT->PSC = div;
}

/*!
 * @brief        Read the specified IWDT flag
 *
 * @param        flag: specifies the flag to read
 *                     This parameter can be one of the following values:
 *                     @arg IWDT_FLAG_PSCU : Watchdog Prescaler Factor Update flag
 *                     @arg IWDT_FLAG_CNTU : Watchdog Counter Reload Value Update flag
 *
 * @retval       status of IWDT_FLAG (SET or RESET)
 *
 * @note
 */
uint8_t IWDT_ReadStatusFlag(uint16_t flag)
{
    uint8_t bitStatus = RESET;

    if((IWDT->STS & flag) != (uint32_t)RESET)
    {
        bitStatus = SET;
    }
    else
    {
        bitStatus = RESET;
    }
    return bitStatus;
}

/**@} end of group IWDT_Functions */
/**@} end of group IWDT_Driver */
/**@} end of group APM32E10x_StdPeriphDriver */
