/*!
 * @file        apm32f4xx_rng.c
 *
 * @brief       This file provides all the RNG firmware functions
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

#include "apm32f4xx_rng.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup RNG_Driver
  * @brief RNG driver modules
  @{
*/

/** @defgroup RNG_Functions
  @{
*/

/*!
 * @brief     Reset RNG peripheral registers to their default reset values.
 *
 * @param     None
 *
 * @retval    None
 */
void RNG_Reset(void)
{
    RCM_EnableAHB2PeriphReset(RCM_AHB2_PERIPH_RNG);
    RCM_DisableAHB2PeriphReset(RCM_AHB2_PERIPH_RNG);
}

/*!
 * @brief     Enable the RNG peripheral.
 *
 * @param     None
 *
 * @retval    None
 */
void RNG_Enable(void)
{
    RNG->CTRL_B.RNGEN = BIT_SET;
}

/*!
 * @brief     Disable the RNG peripheral.
 *
 * @param     None
 *
 * @retval    None
 */
void RNG_Disable(void)
{
    RNG->CTRL_B.RNGEN = BIT_RESET;
}

/*!
 * @brief     Read the 32-bit random number.
 *
 * @param     None
 *
 * @retval    a 32-bit random number.
 */
uint32_t RNG_ReadRandomNumber(void)
{
    return RNG->DATA;
}

/*!
 * @brief     Enable the RNG interrupt.
 *
 * @param     None
 *
 * @retval    None
 */
void EnableInterrupt(void)
{
    RNG->CTRL_B.INTEN = BIT_SET;
}

/*!
 * @brief     Disable the RNG interrupt.
 *
 * @param     None
 *
 * @retval    None
 */
void DisableInterrupt(void)
{
    RNG->CTRL_B.INTEN = BIT_RESET;
}

/*!
 * @brief     Read the specified RNG flag.
 *
 * @param     flag: specifies the RNG flag to check.
 *                  This parameter can be one of the following values:
 *                  @arg RNG_FLAG_DATARDY  : Data Ready flag.
 *                  @arg RNG_FLAG_CLKERCSTS: RNG clock error flag.
 *                  @arg RNG_FLAG_FSCSTS   : Faulty sequence flag.
 *
 * @retval    SET or RESET
 */
uint8_t RNG_ReadStatusFlag(RNG_FLAG_T flag)
{
    if ((RNG->STS & flag) != RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief     Clears the RNG flags.
 *
 * @param     flag: specifies the flag to clear.
 *                  This parameter can be any combination of the following values:
 *                  @arg RNG_FLAG_CLKERCSTS: RNG clock error flag.
 *                  @arg RNG_FLAG_FSCSTS   : Faulty sequence flag.
 *
 * @note      RNG_FLAG_DATARDY can not be cleared only by reading the Random data
 *            (using RNG_ReadRandomNumber() function).
 *
 * @retval    None
 */
void RNG_ClearStatusFlag(uint8_t flag)
{
    RNG->STS = ~(uint32_t)(((uint32_t)flag) << 4);
}

/*!
 * @brief     Read the specified RNG interrupt flag.
 *
 * @param     flag: check status of specifies the RNG interrupt source.
 *                  This parameter can be one of the following values:
 *                  @arg RNG_INT_FLAG_CLKERINT: RNGCLK Error Interrupt.
 *                  @arg RNG_INT_FLAG_FSINT   : Faulty Sequence Interrupt.
 *
 * @retval    SET or RESET
 */
uint8_t RNG_ReadIntFlag(RNG_INT_FLAG_T flag)
{
    if ((RNG->STS & flag) != RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief     Clears the RNG interrupt flags.
 *
 * @param     flag: clear flag specifies the RNG interrupt flag.
 *                  This parameter can be any combination of the following values:
 *                  @arg RNG_INT_FLAG_CLKERINT: RNGCLK Error Interrupt flag.
 *                  @arg RNG_INT_FLAG_FSINT   : Faulty Sequence Interrupt flag.
 *
 * @retval    None
 */
void RNG_ClearIntFlag(uint8_t flag)
{
    RNG->STS = (uint8_t)~flag;
}

/**@} end of group RNG_Functions */
/**@} end of group RNG_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
