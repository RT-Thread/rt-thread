/*!
 * @file        apm32f0xx_pmu.c
 *
 * @brief       This file contains all the functions for the PMU peripheral
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

#include "apm32f0xx_pmu.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup PMU_Driver  PMU Driver
  @{
*/

/** @defgroup PMU_Macros Macros
  @{
*/

/**@} end of group PMU_Macros*/

/** @defgroup PMU_Enumerations Enumerations
  @{
*/

/**@} end of group PMU_Enumerations*/

/** @defgroup PMU_Structures Structures
  @{
*/

/**@} end of group PMU_Structures*/

/** @defgroup PMU_Variables Variables
  @{
*/

/**@} end of group PMU_Variables*/

/** @defgroup  PMU_Functions Functions
  @{
*/

/*!
 * @brief   Resets the PWR peripheral registers to their default reset values
 *
 * @param   None
 *
 * @retval  None
 */
void PMU_Reset(void)
{
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);
    RCM_DisableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);
}

/*!
 * @brief   Enables access to the Backup domain registers
 *
 * @param   None
 *
 * @retval  None
 */
void PMU_EnableBackupAccess(void)
{
    PMU->CTRL_B.BPWEN = BIT_SET;
}

/*!
 * @brief   Disables access to the Backup domain registers
 *
 * @param   None
 *
 * @retval  None
 */
void PMU_DisableBackupAccess(void)
{
    PMU->CTRL_B.BPWEN = BIT_RESET;
}

/*!
 * @brief   Configures the PMU PVD Level
 *
 * @param   level: specifies the PVD Level
 *                 This parameter can be one of the following values
 *                 @arg PMU_PVDLEVEL_0
 *                 @arg PMU_PVDLEVEL_1
 *                 @arg PMU_PVDLEVEL_2
 *                 @arg PMU_PVDLEVEL_3
 *                 @arg PMU_PVDLEVEL_4
 *                 @arg PMU_PVDLEVEL_5
 *                 @arg PMU_PVDLEVEL_6
 *                 @arg PMU_PVDLEVEL_7
 *
 * @retval  None
 *
 * @note    It's not for APM32F030 devices
 */
void PMU_ConfigPVDLevel(PMU_PVDLEVEL_T level)
{
    PMU->CTRL_B.PLSEL = level;
}

/*!
 * @brief   Enables Power voltage detector
 *
 * @param   None
 *
 * @retval  None
 *
 * @note    It's not for APM32F030 devices
 */
void PMU_EnablePVD(void)
{
    PMU->CTRL_B.PVDEN = BIT_SET;
}
/*!
 * @brief   Disables Power voltage detector
 *
 * @param   None
 *
 * @retval  None
 *
 * @note    It's not for APM32F030 devices
 */
void PMU_DisablePVD(void)
{
    PMU->CTRL_B.PVDEN = BIT_RESET;
}

/*!
 * @brief   Enables the WakeUp Pin functionality
 *
 * @param   pin: specifies the WakeUpPin
 *               This parameter can be one of the following values
 *               @arg PMU_WAKEUPPIN_1
 *               @arg PMU_WAKEUPPIN_2
 *               @arg PMU_WAKEUPPIN_3 It's Only for APM32F072/091 devices
 *               @arg PMU_WAKEUPPIN_4 It's Only for APM32F072/091 devices
 *               @arg PMU_WAKEUPPIN_5 It's Only for APM32F072/091 devices
 *               @arg PMU_WAKEUPPIN_6 It's Only for APM32F072/091 devices
 *               @arg PMU_WAKEUPPIN_7 It's Only for APM32F072/091 devices
 *               @arg PMU_WAKEUPPIN_8 It's Only for APM32F072/091 devices
 *
 * @retval  None
 */
void PMU_EnableWakeUpPin(PMU_WAKEUPPIN_T pin)
{
    PMU->CSTS |= pin;
}

/*!
 * @brief   DIsable the WakeUp Pin functionality
 *
 * @param   pin: specifies the WakeUpPin
 *               This parameter can be one of the following values
 *               @arg PMU_WAKEUPPIN_1
 *               @arg PMU_WAKEUPPIN_2
 *               @arg PMU_WAKEUPPIN_3 It's Only for APM32F072/091 devices
 *               @arg PMU_WAKEUPPIN_4 It's Only for APM32F072/091 devices
 *               @arg PMU_WAKEUPPIN_5 It's Only for APM32F072/091 devices
 *               @arg PMU_WAKEUPPIN_6 It's Only for APM32F072/091 devices
 *               @arg PMU_WAKEUPPIN_7 It's Only for APM32F072/091 devices
 *               @arg PMU_WAKEUPPIN_8 It's Only for APM32F072/091 devices
 *
 * @retval  None
 */
void PMU_DisableWakeUpPin(PMU_WAKEUPPIN_T pin)
{
    PMU->CSTS &= ~pin;
}

/*!
 * @brief   Enters Sleep mode
 *
 * @param   entry :specifies if SLEEP mode in entered with WFI or WFE instruction
 *                 This parameter can be one of the following values:
 *                 @arg PMU_SLEEPENTRY_WFI: enter SLEEP mode with WFI instruction
 *                 @arg PMU_SLEEPENTRY_WFE: enter SLEEP mode with WFE instruction
 *
 * @retval  None
 */
void PMU_EnterSleepMode(PMU_SLEEPENTRY_T entry)
{
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    if (entry == PMU_SLEEPENTRY_WFI)
    {
        __WFI();
    }
    else
    {
        __SEV();
        __WFE();
        __WFE();
    }
}

/*!
 * @brief   Enters STOP mode
 *
 * @param   regulator: specifies the regulator state in STOP mode
 *                     This parameter can be one of the following values:
 *                     @arg PMU_REGULATOR_ON: STOP mode with regulator ON
 *                     @arg PMU_REGULATOR_LowPower: STOP mode with regulator in low power mode
 *
 * @param   entry:     specifies if STOP mode in entered with WFI or WFE instruction
 *                     This parameter can be one of the following values:
 *                     @arg PMU_STOPENTRY_WFI: enter STOP mode with WFI instruction
 *                     @arg PMU_STOPENTRY_WFE: enter STOP mode with WFE instruction
 *                     @arg PMU_STOPENTRY_SLEEPONEXIT: enter STOP mode with SLEEPONEXIT instruction
 *
 * @retval  None
 */
void PMU_EnterSTOPMode(PMU_REGULATOR_T regulator, PMU_STOPENTRY_T entry)
{
    PMU->CTRL_B.PDDSCFG = BIT_RESET;

    PMU->CTRL_B.LPDSCFG = regulator;

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    switch (entry)
    {
        case PMU_STOPENTRY_WFI:

            __WFI();
            SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
            break;

        case  PMU_STOPENTRY_WFE:
            __WFE();
            SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
            break;

        case PMU_STOPENTRY_SLEEPONEXIT:
            SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
            break;

        default:
            break;
    }
}

/*!
 * @brief   Enters STANDBY mode
 *
 * @param   None
 *
 * @retval  None
 */
void PMU_EnterSTANDBYMode(void)
{
    PMU->CTRL_B.PDDSCFG = BIT_SET;

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    __WFI();
}

/*!
 * @brief   Checks whether the specified PMU flag is set or not
 *
 * @param   flag: specifies the flag to check
 *                This parameter can be one of the following values:
 *                @arg PMU_FLAG_WUPF: Wake Up flag
 *                @arg PMU_FLAG_STDBYF: StandBy flag
 *                @arg PMU_FLAG_PVDOF: PVD output flag (Not for APM32F030)
 *                @arg PMU_FLAG_VREFINTF: VREFINT flag
 *
 * @retval  The new state of PMU_FLAG (SET or RESET)
 */
uint8_t PMU_ReadStatusFlag(PMU_FLAG_T flag)
{
    uint8_t bit;

    if ((PMU->CSTS & flag) != (uint32_t)RESET)
    {
        bit = SET;
    }
    else
    {
        bit = RESET;
    }

    /** Return the flag status */
    return bit;
}

/*!
 * @brief   Clears the PWR's pending flags
 *
 * @param   flag: specifies the flag to clear
 *                This parameter can be one of the following values:
 *                @arg PMU_FLAG_WUPF: Wake Up flag
 *                @arg PMU_FLAG_STDBYF: StandBy flag
 *
 * @retval  None
 */
void PMU_ClearStatusFlag(uint8_t flag)
{
    if (flag == PMU_FLAG_WUPF)
    {
        PMU->CTRL_B.WUFLGCLR = BIT_SET;
    }
    else if (flag == PMU_FLAG_STDBYF)
    {
        PMU->CTRL_B.SBFLGCLR = BIT_SET;
    }
}

/**@} end of group PMU_Functions*/
/**@} end of group PMU_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver*/
