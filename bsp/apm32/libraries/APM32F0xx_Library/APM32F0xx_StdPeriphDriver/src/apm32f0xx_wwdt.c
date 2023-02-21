/*!
 * @file        apm32f0xx_wwdt.c
 *
 * @brief       This file contains all the functions for the WWDG peripheral
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

#include "apm32f0xx_wwdt.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup WWDT_Driver  WWDT Driver
  @{
*/

/** @defgroup WWDT_Macros Macros
  @{
*/

/**@} end of group WWDT_Macros */

/** @defgroup WWDT_Enumerations Enumerations
  @{
*/

/**@} end of group WWDT_Enumerations */

/** @defgroup WWDT_Structures Structures
  @{
*/

/**@} end of group WWDT_Structures */

/** @defgroup WWDT_Variables Variables
  @{
*/

/**@} end of group WWDT_Variables */

/** @defgroup  WWDT_Functions Functions
  @{
*/

/*!
 * @brief       Set the WWDT peripheral registers to their default reset values
 *
 * @param       None

 * @retval       None
 */
void WWDT_Reset(void)
{
    RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_WWDT);
    RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_WWDT);
}

/*!
 * @brief       Set the WWDT Timebase
 *
 * @param       timebase:   WWDT Prescaler
 *                          The parameter can be one of following values:
 *                          @arg WWDT_DIV_1:  WWDT counter clock = (PCLK1/4096)/1
 *                          @arg WWDT_DIV_2:  WWDT counter clock = (PCLK1/4096)/2
 *                          @arg WWDT_DIV_4:  WWDT counter clock = (PCLK1/4096)/4
 *                          @arg WWDT_DIV_8:  WWDT counter clock = (PCLK1/4096)/8
 *
 * @retval      None
 */
void WWDT_SetTimebase(uint32_t div)
{
    WWDT->CFG_B.TBPSC = 0;
    WWDT->CFG_B.TBPSC = div;
}

/*!
 * @brief       Set the Window data
 *
 * @param       data:   Specifies the window data to be set
 *
 * @retval      None
 */
void WWDT_ConfigWindowValue(uint16_t windowValue)
{
    uint32_t reg;

    reg = (windowValue | BIT6) & 0x7f;

    WWDT->CFG_B.WIN = reg;
}

/*!
 * @brief       Enable the WWDT Early Wakeup interrupt
 *
 * @param       None
 *
 * @retval      None
 */
void WWDT_EnableEWI(void)
{
    WWDT->CFG_B.EWIEN = SET;
}

/*!
 * @brief       Set counter
 *
 * @param       couter: Specifies the counter to be set
 *
 * @retval      None
 */
void WWDT_ConfigCounter(uint8_t couter)
{
    WWDT->CTRL = (uint32_t)(couter & 0x7f);
}

/*!
 * @brief       Enable WWDT and set the counter value
 *
 * @param       count: the window watchdog counter value
 *
 * @retval      None
 */
void WWDT_Enable(uint8_t count)
{
    WWDT->CTRL_B.CNT = count;
    WWDT->CTRL_B.WWDTEN = SET;
}

/*!
 * @brief       Read the Early Wakeup interrupt flag
 *
 * @param       None
 *
 * @retval      the state of the Early Wakeup interrupt flag
 */
uint8_t WWDT_ReadStatusFlag(void)
{
    return (uint8_t)(WWDT->STS);
}

/*!
 * @brief       Clear the Early Wakeup interrupt flag
 *
 * @param       None
 *
 * @retval      None
 */
void WWDT_ClearStatusFlag(void)
{
    WWDT->STS_B.EWIFLG = RESET;
}

/**@} end of group WWDT_Functions*/
/**@} end of group WWDT_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver*/
