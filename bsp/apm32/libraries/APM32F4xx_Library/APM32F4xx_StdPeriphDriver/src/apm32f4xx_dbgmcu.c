/*!
 * @file        apm32f4xx_dbgmcu.c
 *
 * @brief       This file provides all the DEBUG firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
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

#include "apm32f4xx_dbgmcu.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup DBGMCU_Driver
  * @brief DBGMCU driver modules
  @{
*/

/** @defgroup DBGMCU_Functions
  @{
*/

/*!
 * @brief     Returns the device identifier.
 *
 * @param     None
 *
 * @retval    Device identifier
 */
uint32_t DBGMCU_ReadDEVID(void)
{
    return(DBGMCU->IDCODE_B.EQR);
}

/*!
 * @brief     Returns the device revision identifier.
 *
 * @param     None
 *
 * @retval    Device revision identifier
 */
uint32_t DBGMCU_ReadREVID(void)
{
    return(DBGMCU->IDCODE_B.WVR);
}

/*!
 * @brief     Enable the specified peripheral and low power mode behavior
 *            when the MCU under Debug mode
 *
 * @param     periph: Specifies the peripheral and low power mode
 *                    This parameter can be any combination of the following values:
 *                    @arg DBGMCU_SLEEP     : Keep debugger connection during SLEEP mode
 *                    @arg DBGMCU_STOP      : Keep debugger connection during STOP mode
 *                    @arg DBGMCU_STANDBY   : Keep debugger connection during STANDBY mode
 *
 * @retval    None
 */
void DBGMCU_Enable(uint32_t periph)
{
    DBGMCU->CFG |= periph;
}

/*!
 * @brief     DBGMCU_Disable the specified peripheral and low power mode behavior
 *            when the MCU under Debug mode
 *
 * @param     periph: Specifies the peripheral and low power mode
 *                    This parameter can be any combination of the following values:
 *                    @arg DBGMCU_SLEEP     : Keep debugger connection during SLEEP mode
 *                    @arg DBGMCU_STOP      : Keep debugger connection during STOP mode
 *                    @arg DBGMCU_STANDBY   : Keep debugger connection during STANDBY mode
 *
 * @retval    None
 */
void DBGMCU_Disable(uint32_t periph)
{
    DBGMCU->CFG &= ~periph;
}

/*!
 * @brief     Enable APB1 peripheral behavior when the MCU is in Debug mode.
 *
 * @param     periph: specifies the APB1 peripheral.
 *                    This parameter can be any combination of the following values:
 *                    @arg DBGMCU_TMR2_STOP          : TMR2 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR3_STOP          : TMR3 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR4_STOP          : TMR4 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR5_STOP          : TMR5 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR6_STOP          : TMR6 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR7_STOP          : TMR7 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR12_STOP         : TMR12 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR13_STOP         : TMR13 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR14_STOP         : TMR14 counter stopped when Core is halted
 *                    @arg DBGMCU_RTC_STOP           : RTC Calendar and Wakeup counter stopped when Core is halted.
 *                    @arg DBGMCU_WWDT_STOP          : Debug WWDG stopped when Core is halted
 *                    @arg DBGMCU_IWDT_STOP          : Debug IWDG stopped when Core is halted
 *                    @arg DBGMCU_I2C1_SMBUS_TIMEOUT : I2C1 SMBUS timeout mode stopped when Core is halted
 *                    @arg DBGMCU_I2C2_SMBUS_TIMEOUT : I2C2 SMBUS timeout mode stopped when Core is halted
 *                    @arg DBGMCU_I2C3_SMBUS_TIMEOUT : I2C3 SMBUS timeout mode stopped when Core is halted
 *                    @arg DBGMCU_CAN1_STOP          : Debug CAN1 stopped when Core is halted
 *                    @arg DBGMCU_CAN2_STOP          : Debug CAN2 stopped when Core is halted
 *
 * @retval    None
 */
void DBGMCU_EnableAPB1Periph(uint32_t periph)
{
    DBGMCU->APB1F |= periph;
}

/*!
 * @brief     Disable APB1 peripheral behavior when the MCU is in Debug mode.
 *
 * @param     periph: specifies the APB1 peripheral.
 *                    This parameter can be any combination of the following values:
 *                    @arg DBGMCU_TMR2_STOP          : TMR2 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR3_STOP          : TMR3 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR4_STOP          : TMR4 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR5_STOP          : TMR5 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR6_STOP          : TMR6 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR7_STOP          : TMR7 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR12_STOP         : TMR12 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR13_STOP         : TMR13 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR14_STOP         : TMR14 counter stopped when Core is halted
 *                    @arg DBGMCU_RTC_STOP           : RTC Calendar and Wakeup counter stopped when Core is halted.
 *                    @arg DBGMCU_WWDT_STOP          : Debug WWDG stopped when Core is halted
 *                    @arg DBGMCU_IWDT_STOP          : Debug IWDG stopped when Core is halted
 *                    @arg DBGMCU_I2C1_SMBUS_TIMEOUT : I2C1 SMBUS timeout mode stopped when Core is halted
 *                    @arg DBGMCU_I2C2_SMBUS_TIMEOUT : I2C2 SMBUS timeout mode stopped when Core is halted
 *                    @arg DBGMCU_I2C3_SMBUS_TIMEOUT : I2C3 SMBUS timeout mode stopped when Core is halted
 *                    @arg DBGMCU_CAN1_STOP          : Debug CAN1 stopped when Core is halted
 *                    @arg DBGMCU_CAN1_STOP          : Debug CAN2 stopped when Core is halted
 *
 * @retval    None
 */
void DBGMCU_DisableAPB1Periph(uint32_t periph)
{
    DBGMCU->APB1F &= ~periph;
}

/*!
 * @brief     Enable APB2 peripheral behavior when the MCU is in Debug mode.
 *
 * @param     periph: specifies the APB2 peripheral.
 *                    This parameter can be any combination of the following values:
 *                    @arg DBGMCU_TMR1_STOP  : TMR1 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR8_STOP  : TMR8 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR9_STOP  : TMR9 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR10_STOP : TMR10 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR11_STOP : TMR11 counter stopped when Core is halted
 *
 * @retval    None
 */
void DBGMCU_EnableAPB2Periph(uint32_t periph)
{
    DBGMCU->APB2F |= periph;
}

/*!
 * @brief     Disable APB2 peripheral behavior when the MCU is in Debug mode.
 *
 * @param     periph: specifies the APB2 peripheral.
 *                    This parameter can be any combination of the following values:
 *                    @arg DBGMCU_TMR1_STOP  : TMR1 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR8_STOP  : TMR8 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR9_STOP  : TMR9 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR10_STOP : TMR10 counter stopped when Core is halted
 *                    @arg DBGMCU_TMR11_STOP : TMR11 counter stopped when Core is halted
 *
 * @retval    None
 */
void DBGMCU_DisableAPB2Periph(uint32_t periph)
{
    DBGMCU->APB2F &= ~periph;
}

/**@} end of group DBGMCU_Functions */
/**@} end of group DBGMCU_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
