/*!
 * @file        apm32s10x_rtc.c
 *
 * @brief       This file provides all the RTC firmware functions
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
#include "apm32s10x_rtc.h"

/** @addtogroup APM32S10x_StdPeriphDriver
  @{
*/

/** @addtogroup RTC_Driver RTC Driver
  @{
*/

/** @defgroup RTC_Functions Functions
  @{
*/

/*!
 * @brief     Enter RTC configuration mode.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_EnableConfigMode(void)
{
    RTC->CSTS_B.CFGMFLG = BIT_SET;
}

/*!
 * @brief     Exit RTC configuration mode.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_DisableConfigMode(void)
{
    RTC->CSTS_B.CFGMFLG = BIT_RESET;
}

/*!
 * @brief     Read the RTC counter value.
 *
 * @param     None
 *
 * @retval    RTC counter value.
 */
uint32_t RTC_ReadCounter(void)
{
    uint32_t reg = 0;
    reg = (RTC->CNTH_B.CNTH) << 16;
    reg |= (RTC->CNTL_B.CNTL);
    return reg;
}

/*!
 * @brief     Configure the RTC counter value.
 *
 * @param     value: RTC counter new value.
 *
 * @retval    None
 */
void RTC_ConfigCounter(uint32_t value)
{
    RTC_EnableConfigMode();
    RTC->CNTH_B.CNTH = value >> 16;
    RTC->CNTL_B.CNTL = value & 0x0000FFFF;
    RTC_DisableConfigMode();
}

/*!
 * @brief     Configure the RTC prescaler value.
 *
 * @param     value: RTC prescaler new value.
 *
 * @retval    None
 */
void RTC_ConfigPrescaler(uint32_t value)
{
    RTC_EnableConfigMode();
    RTC->PSCRLDH_B.PSCRLDH = value >> 16;
    RTC->PSCRLDL_B.PSCRLDL = value & 0x0000FFFF;
    RTC_DisableConfigMode();
}

/*!
 * @brief     Configure the RTC alarm value.
 *
 * @param     value: RTC alarm new value.
 *
 * @retval    None
 */
void RTC_ConfigAlarm(uint32_t value)
{
    RTC_EnableConfigMode();
    RTC->ALRH_B.ALRH = value >> 16;
    RTC->ALRL_B.ALRL = value & 0x0000FFFF;
    RTC_DisableConfigMode();
}

/*!
 * @brief     Read the RTC divider value.
 *
 * @param     None
 *
 * @retval    RTC Divider value.
 */
uint32_t RTC_ReadDivider(void)
{
    uint32_t reg = 0;
    reg = (RTC->PSCH_B.PSCH & 0x000F) << 16;
    reg |= (RTC->PSCL_B.PSCL);
    return reg;
}

/*!
 * @brief     Wait until last write operation on RTC registers has finished.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_WaitForLastTask(void)
{
    while (RTC->CSTS_B.OCFLG == BIT_RESET)
    {
    }
}

/*!
 * @brief     Wait until the RTC registers
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_WaitForSynchro(void)
{
    RTC->CSTS_B.RSYNCFLG = BIT_RESET;
    while (RTC->CSTS_B.RSYNCFLG == BIT_RESET);
}

/*!
 * @brief     Enable RTC interrupts.
 *
 * @param     interrupt: specify the RTC interrupt sources to be enabled
 *              This parameter can be any combination of the following values:
 *              @arg RTC_INT_OVR : Overflow interrupt
 *              @arg RTC_INT_ALR : Alarm interrupt
 *              @arg RTC_INT_SEC : Second interrupt
 */
void RTC_EnableInterrupt(uint16_t interrupt)
{
    RTC->CTRL |= interrupt;
}

/*!
 * @brief     Disable RTC interrupts.
 *
 * @param     interrupt: specify the RTC interrupt sources to be disabled
 *              This parameter can be any combination of the following values:
 *              @arg RTC_INT_OVR : Overflow interrupt
 *              @arg RTC_INT_ALR : Alarm interrupt
 *              @arg RTC_INT_SEC : Second interrupt
 *
 * @retval    None
 */
void RTC_DisableInterrupt(uint16_t interrupt)
{
    RTC->CTRL &= (uint32_t)~interrupt;
}

/*!
 * @brief     Read flag bit
 *
 * @param     flag: specify the flag to check.
 *              This parameter can be one of the following values:
 *              @arg RTC_FLAG_OC    : RTC Operation Complete flag
 *              @arg RTC_FLAG_RSYNC : Registers Synchronized flag
 *              @arg RTC_FLAG_OVR   : Overflow flag
 *              @arg RTC_FLAG_ALR   : Alarm flag
 *              @arg RTC_FLAG_SEC   : Second flag
 *
 * @retval    SET or RESET
 */
uint8_t RTC_ReadStatusFlag(RTC_FLAG_T flag)
{
    return (RTC->CSTS & flag) ? SET : RESET;
}

/*!
 * @brief     Clear flag bit
 *
 * @param     flag: specify the flag to clear.
 *              This parameter can be any combination of the following values:
 *              @arg RTC_FLAG_OVR : Overflow flag
 *              @arg RTC_FLAG_ALR : Alarm flag
 *              @arg RTC_FLAG_SEC : Second flag
 *
 * @retval    None
 */
void RTC_ClearStatusFlag(uint16_t flag)
{
    RTC->CSTS &= (uint32_t)~flag;
}

/*!
 * @brief     Read interrupt flag bit is set
 *
 * @param     flag: specify the flag to check.
 *              This parameter can be any combination of the following values:
 *              @arg RTC_INT_OVR : Overflow interrupt
 *              @arg RTC_INT_ALR : Alarm interrupt
 *              @arg RTC_INT_SEC : Second interrupt
 *
 * @retval    None
 */
uint8_t RTC_ReadIntFlag(RTC_INT_T flag)
{
    return (RTC->CSTS & flag) ? SET : RESET;
}

/*!
 * @brief     Clear RTC interrupt flag bit
 *
 * @param     flag: specify the flag to clear.
 *              This parameter can be one of the following values:
 *              @arg RTC_INT_OVR : Overflow interrupt
 *              @arg RTC_INT_ALR : Alarm interrupt
 *              @arg RTC_INT_SEC : Second interrupt
 *
 * @retval    None
 */
void RTC_ClearIntFlag(uint16_t flag)
{
    RTC->CSTS &= (uint32_t)~flag;
}

/**@} end of group RTC_Functions */
/**@} end of group RTC_Driver */
/**@} end of group APM32S10x_StdPeriphDriver */
