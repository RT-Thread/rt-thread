/*!
 * @file        apm32s10x_wwdt.c
 *
 * @brief       This file contains all the functions for the WWDT peripheral
 *
 * @version     V1.0.1
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2022-2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "apm32s10x_wwdt.h"
#include "apm32s10x_rcm.h"

/** @addtogroup APM32S10x_StdPeriphDriver
  @{
*/

/** @addtogroup WWDT_Driver  WWDT Driver
  @{
*/

/** @defgroup  WWDT_Functions Functions
  @{
*/

/*!
 * @brief        Reset the WWDT peripheral registers
 *
 * @param        None
 *
 * @retval       None
 */
void WWDT_Reset(void)
{
    RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_WWDT);
    RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_WWDT);
}

/*!
 * @brief        Configure the WWDT Timebase
 *
 * @param        timebase: WWDT Prescaler
 *               The parameter can be one of following values:
 *               @arg WWDT_TIME_BASE_1: WWDT counter clock = (PCLK1/4096)/1
 *               @arg WWDT_TIME_BASE_2: WWDT counter clock = (PCLK1/4096)/2
 *               @arg WWDT_TIME_BASE_4: WWDT counter clock = (PCLK1/4096)/4
 *               @arg WWDT_TIME_BASE_8: WWDT counter clock = (PCLK1/4096)/8
 *
 * @retval       None
 */
void WWDT_ConfigTimebase(WWDT_TIME_BASE_T timeBase)
{
    __IO uint32_t reg;

    reg = WWDT->CFG & 0xFFFFFE7F;
    reg |= timeBase;
    WWDT->CFG = reg;
}

/*!
 * @brief        Configure the WWDT Window data
 *
 * @param        windowdata: window data which compare with the downcounter
 *
 * @retval       None
 *
 * @note         The windowdata must be lower than 0x80
 */
void WWDT_ConfigWindowData(uint8_t windowData)
{
    __IO uint32_t reg;

    reg = WWDT->CFG & 0xFFFFFF80;
    reg |= windowData & 0x7F;
    WWDT->CFG = reg;
}

/*!
 * @brief       Configure the WWDT counter value
 *
 * @param       counter: Specify the watchdog counter value
 *
 * @retval      None
 *
 * @note        The counter between 0x40 and 0x7F
 */
void WWDT_ConfigCounter(uint8_t counter)
{
    WWDT->CTRL = counter & 0x7F;
}

/*!
 * @brief        Enable the WWDT Early Wakeup interrupt
 *
 * @param        None
 *
 * @retval       None
 */
void WWDT_EnableEWI(void)
{
    WWDT->CFG_B.EWIEN = SET;
}

/*!
 * @brief        Enable WWDT and set the counter value
 *
 * @param        counter: the window watchdog counter value
 *
 * @retval       None
 *
 * @note         The counter between 0x40 and 0x7F
 */
void WWDT_Enable(uint8_t counter)
{
    WWDT->CTRL =  counter | 0x00000080;
}

/*!
 * @brief        Read the Early Wakeup interrupt flag
 *
 * @param        None
 *
 * @retval       the state of the Early Wakeup interrupt flag
 */
uint8_t WWDT_ReadFlag(void)
{
    return (uint8_t)WWDT->STS;
}

/*!
 * @brief        Clear the Early Wakeup interrupt flag
 *
 * @param        None
 *
 * @retval       None
 */
void WWDT_ClearFlag(void)
{
    WWDT->STS_B.EWIFLG = RESET;
}

/**@} end of group WWDT_Functions */
/**@} end of group WWDT_Driver */
/**@} end of group APM32S10x_StdPeriphDriver */
