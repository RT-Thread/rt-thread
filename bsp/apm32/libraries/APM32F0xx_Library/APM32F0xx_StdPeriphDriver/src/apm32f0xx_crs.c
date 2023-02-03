/*!
 * @file        apm32f0xx_crs.c
 *
 * @brief       This file contains all the functions for the CRS peripheral
 *
 * @note        It's only for APM32F072 and APM32F091 devices
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

/* Includes */
#include "apm32f0xx_crs.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup CRS_Driver
  @{
*/

/** @defgroup CRS_Macros Macros
  @{
*/

/**@} end of group CRS_Macros */

/** @defgroup CRS_Enumerations Enumerations
  @{
*/

/**@} end of group CRS_Enumerations */

/** @defgroup CRS_Structures Structures
  @{
*/

/**@} end of group CRS_Structures */

/** @defgroup CRS_Variables Variables
  @{
*/

/**@} end of group CRS_Variables */

/** @defgroup CRS_Functions Functions
  @{
*/

/*!
 * @brief    Resets the CRS peripheral registers to their default reset values.
 *
 * @param    None
 *
 * @retval   None
 */
void CRS_Reset(void)
{
    RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_CRS);
    RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_CRS);
}

/*!
 * @brief    Adjusts the Internal High Speed 48 oscillator (HSI 48) calibration value.
 *
 * @param    calibrationVal: HSI48 oscillator smooth trimming value. It can be 0x0 to 0xF.
 *
 * @retval   None
 */
void CRS_AdjustHSI48CalibrationValue(uint8_t calibrationVal)
{
    CRS->CTRL_B.HSI48TRM = calibrationVal;
}

/*!
 * @brief    Enables the oscillator clock for frequency error counter.
 *
 * @param    None
 *
 * @retval   None
 */
void CRS_EnableFrequencyErrorCounter(void)
{
    CRS->CTRL_B.CNTEN = SET;
}

/*!
 * @brief    Disables the oscillator clock for frequency error counter.
 *
 * @param    None
 *
 * @retval   None
 */
void CRS_DisableFrequencyErrorCounter(void)
{
    CRS->CTRL_B.CNTEN = RESET;
}

/*!
 * @brief  Enables the automatic hardware adjustement of HSI48TRM bits.
 *
 * @param  None
 *
 * @retval None
 */
void CRS_EnableAutomaticCalibration(void)
{
    CRS->CTRL_B.AUTOTRMEN = SET;
}

/*!
 * @brief    Disables the automatic hardware adjustement of HSI48TRM bits.
 *
 * @param    None
 *
 * @retval   None
 */
void CRS_DisableAutomaticCalibration(void)
{
    CRS->CTRL_B.AUTOTRMEN = RESET;
}

/*!
 * @brief  Generate the software synchronization event.
 *
 * @param  None
 *
 * @retval None
 */
void CRS_GenerateSoftwareSynchronization(void)
{
    CRS->CTRL_B.SWSGNR = SET;
}

/*!
 * @brief  Adjusts the Internal High Speed 48 oscillator (HSI 48) calibration value.
 *
 * @param  reloadVal: specifies the HSI calibration trimming value.
 *                    This parameter must be a number between 0 and 0xFFFF.
 *
 * @retval None
 */
void CRS_FrequencyErrorCounterReloadValue(uint16_t reloadVal)
{
    CRS->CFG_B.RLDVAL = reloadVal;
}

/**
 * @brief   Configs the frequency error limit value.
 *
 * @param    errLimitVal: specifies the HSI calibration trimming value.
 *
 * @retval   None
 */
void CRS_ConfigFrequencyErrorLimit(uint8_t errLimitVal)
{
    CRS->CFG_B.FELMT = errLimitVal;
}

/*!
 * @brief    Configs SYNC divider.
 *
 * @param    div: defines the SYNC divider.
 *                This parameter can be one of the following values:
 *                  @arg CRS_SYNC_DIV1
 *                  @arg CRS_SYNC_DIV2
 *                  @arg CRS_SYNC_DIV4
 *                  @arg CRS_SYNC_DIV8
 *                  @arg CRS_SYNC_DIV16
 *                  @arg CRS_SYNC_DIV32
 *                  @arg CRS_SYNC_DIV64
 *                  @arg CRS_SYNC_DIV128
 *
 * @retval   None
 */
void CRS_ConfigSynchronizationPrescaler(CRS_SYNC_DIV_T div)
{
    CRS->CFG_B.SYNCPSC = div;
}

/*!
 * @brief    Configs the SYNC signal source.
 *
 * @param    source: specifies the SYNC signal source.
 *                   This parameter can be one of the following values:
 *                     @arg CRS_SYNC_SOURCE_GPIO
 *                     @arg CRS_SYNC_SOURCE_LSE
 *                     @arg CRS_SYNC_SOURCE_USB
 *
 * @retval   None
 */
void CRS_ConfigSynchronizationSource(CRS_SYNC_SOURCE_T source)
{
    CRS->CFG_B.SYNCSRCSEL = source;
}

/*!
 * @brief    Configs the SYNC polarity.
 *
 * @param    polarity: specifies SYNC polarity.
 *                     This parameter can be one of the following values:
 *                       @arg CRS_SYNC_POL_RISING
 *                       @arg CRS_SYNC_POL_FALLING
 *
 * @retval   None
 */
void CRS_ConfigSynchronizationPolarity(CRS_SYNC_POL_T polarity)
{
    CRS->CFG_B.SYNCPOLSEL = polarity;
}

/*!
 * @brief    Returns the Relaod value.
 *
 * @param    None
 *
 * @retval   The reload value
 */
uint32_t CRS_ReadReloadValue(void)
{
    return (uint32_t)CRS->CFG_B.RLDVAL;
}

/*!
 * @brief    Returns the HSI48 Calibration value.
 *
 * @param    None
 *
 * @retval   The reload value
 */
uint32_t CRS_ReadHSI48CalibrationValue(void)
{
    return (uint32_t)CRS->CTRL_B.HSI48TRM;
}

/*!
 * @brief    Returns the frequency error capture.
 *
 * @param    None
 *
 * @retval   The frequency error capture value
 */
uint32_t CRS_ReadFrequencyErrorValue(void)
{
    return (uint32_t)CRS->INTSTS_B.FECPT;
}

/*!
 * @brief    Returns the frequency error direction.
 *
 * @param    None
 *
 * @retval   The frequency error direction.
 *           The returned value can be one of the following values:
 *              0: Up counting
 *              1: Down counting
 */
uint32_t CRS_ReadFrequencyErrorDirection(void)
{
    return (uint32_t)CRS->INTSTS_B.CNTDRCT;
}

/*!
 * @brief    Enables the specified CRS interrupts.
 *
 * @param    interrupt: specifies the RCC interrupt sources to be enabled or disabled.
 *                      This parameter can be any combination of the following values:
 *                          @arg CRS_INT_SYNCOK  : SYNC event OK interrupt
 *                          @arg CRS_INT_SYNCWARN: SYNC warning interrupt
 *                          @arg CRS_INT_ERR     : Synchronization or trimming error interrupt
 *                          @arg CRS_INT_ESYNC   : Expected SYNC interrupt
 *
 * @retval   None
 */
void CRS_EnableInterrupt(CRS_INT_T interrupt)
{
    CRS->CTRL |= interrupt;
}

/*!
 * @brief    Disables the specified CRS interrupts.
 *
 * @param    interrupt: specifies the RCC interrupt sources to be enabled or disabled.
 *                      This parameter can be any combination of the following values:
 *                          @arg CRS_INT_SYNCOK  : SYNC event OK interrupt
 *                          @arg CRS_INT_SYNCWARN: SYNC warning interrupt
 *                          @arg CRS_INT_ERR     : Synchronization or trimming error interrupt
 *                          @arg CRS_INT_ESYNC   : Expected SYNC interrupt
 *
 * @retval   None
 */
void CRS_DisableInterrupt(CRS_INT_T interrupt)
{
    CRS->CTRL &= ~interrupt;
}

/*!
 * @brief    Checks whether the specified CRS flag is set or not.
 *
 * @param    flag: specifies the flag to check.
 *                 This parameter can be one of the following values:
 *                     @arg CRS_FLAG_SYNCOK  : SYNC event OK flag
 *                     @arg CRS_FLAG_SYNCWARN: SYNC warning flag
 *                     @arg CRS_FLAG_ERR     : Synchronization or trimming error flag
 *                     @arg CRS_FLAG_ESYNC   : Expected SYNC flag
 *                     @arg CRS_FLAG_SYNCERR : SYNC error flag
 *                     @arg CRS_FLAG_SYNCMISS: SYNC missed flag
 *                     @arg CRS_FLAG_TRIMOVF : Trimming overflow or underflow falg
 *
 * @retval   The new state of CRS_FLAG (SET or RESET).
 */
uint8_t CRS_ReadStatusFlag(CRS_FLAG_T flag)
{
    uint32_t status;
    status = (uint32_t)(CRS->INTSTS & flag);

    if (status == flag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief    Clears the CRS specified flag.
 *
 * @param    flag: specifies the flag to check.
 *                 This parameter can be one of the following values:
 *                     @arg CRS_FLAG_SYNCOK  : SYNC event OK flag
 *                     @arg CRS_FLAG_SYNCWARN: SYNC warning flag
 *                     @arg CRS_FLAG_ERR     : Synchronization or trimming error flag
 *                     @arg CRS_FLAG_ESYNC   : Expected SYNC flag
 *                     @arg CRS_FLAG_SYNCERR : SYNC error flag
 *                     @arg CRS_FLAG_SYNCMISS: SYNC missed flag
 *                     @arg CRS_FLAG_TRIMOVF : Trimming overflow or underflow falg
 *
 * @retval   None
 */
void CRS_ClearStatusFlag(CRS_FLAG_T flag)
{
    if ((flag & 0x00000700) != 0)
    {
        CRS->INTCLR_B.ECLR = BIT_SET;
    }

    CRS->INTCLR |= (uint32_t)flag;
}

/*!
 * @brief    Checks CRS interrupt flag.
 *
 * @param    flag: specifies the IT pending bit to check.
 *                   This parameter can be one of the following values:
 *                       @arg CRS_INT_SYNCOK  : SYNC event OK interrupt
 *                       @arg CRS_INT_SYNCWARN: SYNC warning interrupt
 *                       @arg CRS_INT_ERR     : Synchronization or trimming error interrupt
 *                       @arg CRS_INT_ESYNC   : Expected SYNC interrupt
 *                       @arg CRS_INT_SYNCERR : SYNC error
 *                       @arg CRS_INT_SYNCMISS: SYNC missed
 *                       @arg CRS_INT_TRIMOVF : Trimming overflow or underflow
 *
 * @retval   The new state of CRS_IT (SET or RESET).
 */
uint8_t CRS_ReadIntFlag(CRS_INT_T flag)
{
    if ((CRS->INTSTS & flag))
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief    Clears the CRS specified interrupt flag.
 *
 * @param    intFlag: specifies the IT pending bi to clear.
 *                     This parameter can be one of the following values:
 *                       @arg CRS_INT_SYNCOK  : SYNC event OK interrupt
 *                       @arg CRS_INT_SYNCWARN: SYNC warning interrupt
 *                       @arg CRS_INT_ERR     : Synchronization or trimming error interrupt
 *                       @arg CRS_INT_ESYNC   : Expected SYNC interrupt
 *                       @arg CRS_INT_SYNCERR : SYNC error
 *                       @arg CRS_INT_SYNCMISS: SYNC missed
 *                       @arg CRS_INT_TRIMOVF : Trimming overflow or underflow
 *
 * @retval   None
 */
void CRS_ClearIntFlag(CRS_INT_T intFlag)
{
    if ((intFlag & (uint32_t)0x700) != 0)
    {
        CRS->INTCLR |= CRS_INT_ERR;
    }
    else
    {
        CRS->INTCLR |= intFlag;
    }
}

/**@} end of group CRS_Functions */
/**@} end of group CRS_Driver*/
/**@} end of group APM32F0xx_StdPeriphDriver */
