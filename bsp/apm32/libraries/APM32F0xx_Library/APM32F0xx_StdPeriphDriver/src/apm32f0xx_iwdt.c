/*!
 * @file        apm32f0xx_iwdt.c
 *
 * @brief       This file contains all the functions for the IWDT peripheral
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
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

#include "apm32f0xx_iwdt.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup IWDT_Driver
  @{
*/

/** @defgroup IWDT_Macros Macros
  @{
*/

/**@} end of group IWDT_Macros*/

/** @defgroup IWDT_Enumerations Enumerations
  @{
*/

/**@} end of group IWDT_Enumerations*/

/** @defgroup IWDT_Structures Structures
  @{
*/

/**@} end of group IWDT_Structures*/

/** @defgroup IWDT_Variables Variables
  @{
*/

/**@} end of group IWDT_Variables*/

/** @defgroup IWDT_Functions Functions
  @{
*/

/*!
 * @brief       Enable IWDT
 *
 * @param       None
 *
 * @retval      None
 */
void IWDT_Enable(void)
{
    IWDT->KEY = IWDT_KEY_ENABLE;
}

/*!
 * @brief       Enable write access to Divider and Counter Reload registers
 *
 * @param       None
 *
 * @retval      None
 */
void IWDT_EnableWriteAccess(void)
{
    IWDT->KEY = IWDT_KEY_ACCESS;
}

/*!
 * @brief       Disable write access to Divider and Counter Reload registers
 *
 * @param       None
 *
 * @retval      None
 */
void IWDT_DisableWriteAccess(void)
{
    IWDT->KEY = 0;
}

/*!
 * @brief       Refresh IWDT
 *
 * @param       None
 *
 * @retval      None
 */
void IWDT_Refresh(void)
{
    IWDT->KEY = IWDT_KEY_REFRESH;
}

/*!
 * @brief       Divider configuration
 *
 * @param       div: Specifies the divider
 *                   The parameter can be one of following values:
 *                      @arg IWDT_DIV_4:    Prescaler divider 4
 *                      @arg IWDT_DIV_8:    Prescaler divider 8
 *                      @arg IWDT_DIV_16:   Prescaler divider 16
 *                      @arg IWDT_DIV_32:   Prescaler divider 32
 *                      @arg IWDT_DIV_64:   Prescaler divider 64
 *                      @arg IWDT_DIV_128:  Prescaler divider 128
 *                      @arg IWDT_DIV_256:  Prescaler divider 256
 *
 * @retval      None
 */
void IWDT_ConfigDivider(IWDT_DIV_T div)
{
    IWDT->PSC = (uint32_t)div;
}

/*!
 * @brief       Set counter reload value
 *
 * @param       reload: Specifies the reload value
 *
 * @retval      None
 */
void IWDT_ConfigReload(uint16_t reload)
{
    IWDT->CNTRLD = (uint32_t)reload;
}

/*!
 * @brief       Set counter reload value
 *
 * @param       reload: Specifies the reload value
 *
 * @retval      None
 */
void IWDT_ConfigWindowValue(uint16_t windowValue)
{
    IWDT->WIN = (uint32_t)windowValue;
}
/*!
 * @brief       Read the specified IWDT flag
 *
 * @param       flag: Specifies the flag to read
 *              The parameter can be one of following values:
 *                 @arg IWDT_FLAG_DIVU:  Watchdog prescaler value update
 *                 @arg IWDT_FLAG_CNTU:  Watchdog counter reload value update
 *                 @arg IWDT_FLAG_WINU:  Watchdog counter window value update
 *
 * @retval      status of IWDT_FLAG (SET or RESET)
 */
uint8_t IWDT_ReadStatusFlag(uint8_t flag)
{
    uint8_t bitStatus = RESET;

    if ((IWDT->STS & flag) != (uint32_t)RESET)
    {
        bitStatus = SET;
    }
    else
    {
        bitStatus = RESET;
    }

    return bitStatus;
}

/**@} end of group IWDT_Functions*/
/**@} end of group IWDT_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver*/
