/*!
 * @file        apm32f4xx_pmu.c
 *
 * @brief       This file provides all the PMU firmware functions.
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

#include "apm32f4xx_pmu.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup PMU_Driver
  * @brief PMU driver modules
  @{
*/

/** @defgroup PMU_Functions
  @{
*/

/*!
 * @brief     Reset the PMU peripheral register.
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_Reset(void)
{
    RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_PMU);
    RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_PMU);
}

/*!
 * @brief     Enables access to the RTC and backup registers.
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_EnableBackupAccess(void)
{
    PMU->CTRL_B.BPWEN = ENABLE;
}

/*!
 * @brief     Disables access to the RTC and backup registers.
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_DisableBackupAccess(void)
{
    PMU->CTRL_B.BPWEN = DISABLE;
}

/*!
 * @brief     Enables the Power Voltage Detector(PVD).
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_EnablePVD(void)
{
    PMU->CTRL_B.PVDEN = ENABLE;
}

/*!
 * @brief     Disables the Power Voltage Detector(PVD).
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_DisablePVD(void)
{
    PMU->CTRL_B.PVDEN = DISABLE;
}

/*!
 * @brief    Configures the voltage threshold detected by the Power Voltage Detector(PVD).
 *
 * @param    level: specifies the PVD detection level
 *           This parameter can be one of the following values:
 *              @arg PMU_PVD_LEVEL_2V0 : Config PVD detection level to 2.0V
 *              @arg PMU_PVD_LEVEL_2V1 : Config PVD detection level to 2.1V
 *              @arg PMU_PVD_LEVEL_2V3 : Config PVD detection level to 2.3V
 *              @arg PMU_PVD_LEVEL_2V5 : Config PVD detection level to 2.5V
 *              @arg PMU_PVD_LEVEL_2V6 : Config PVD detection level to 2.6V
 *              @arg PMU_PVD_LEVEL_2V7 : Config PVD detection level to 2.7V
 *              @arg PMU_PVD_LEVEL_2V8 : Config PVD detection level to 2.8V
 *              @arg PMU_PVD_LEVEL_2V9 : Config PVD detection level to 2.9V
 *
 * @retval   None
 */
void PMU_ConfigPVDLevel(PMU_PVD_LEVEL_T level)
{
    PMU->CTRL_B.PLSEL = 0;
    PMU->CTRL_B.PLSEL = level;
}

/*!
 * @brief     Enables the WakeUp Pin functionality.
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_EnableWakeUpPin(void)
{
    PMU->CSTS_B.WKUPCFG = ENABLE;
}

/*!
 * @brief     Diaables the WakeUp Pin functionality.
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_DisableWakeUpPin(void)
{
    PMU->CSTS_B.WKUPCFG = DISABLE;
}

/*!
 * @brief     Enables the Backup Regulator.
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_EnableBackupRegulator(void)
{
    PMU->CSTS_B.BKPREN = ENABLE;
}

/*!
 * @brief     Diaables the Backup Regulator.
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_DisableBackupRegulator(void)
{
    PMU->CSTS_B.BKPREN = DISABLE;
}

/*!
 * @brief     Configures the main internal regulator output voltage.
 *
 * @param     scale: This parameter can be one of the following values:
 *               @arg PMU_REGULATOR_VOLTAGE_SCALE1 : Select regulator voltage scale 1
 *               @arg PMU_REGULATOR_VOLTAGE_SCALE2 : Select regulator voltage scale 2
 *
 * @retval    None
 */
void PMU_ConfigMainRegulatorMode(PMU_REGULATOR_VOLTAGE_SCALE_T scale)
{
    PMU->CTRL_B.VOSSEL = 0;
    PMU->CTRL_B.VOSSEL = scale;
}

/*!
 * @brief     Enables the Flash Power Down in STOP mode.
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_EnableFlashPowerDown(void)
{
    PMU->CTRL_B.FPDSM = ENABLE ;
}

/*!
 * @brief     Diaables the Flash Power Down in STOP mode.
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_DisableFlashPowerDown(void)
{
    PMU->CTRL_B.FPDSM = DISABLE ;
}

/*!
 * @brief     Enters STOP mode.
 *
 * @param     regulator: specifies the regulator state in STOP mode.
 *            This parameter can be one of the following values:
 *              @arg PMU_REGULATOR_ON        : STOP mode with regulator ON
 *              @arg PMU_REGULATOR_LOWPOWER  : STOP mode with regulator in low power mode
 *
 * @param     entry: specifies if STOP mode in entered with WFI or WFE instruction.
 *            This parameter can be one of the following values:
 *              @arg PMU_STOP_ENTRY_WFI: Enter STOP mode with WFI instruction
 *              @arg PMU_STOP_ENTRY_WFE: Enter STOP mode with WFE instruction
 *
 * @retval    None
 */
void PMU_EnterSTOPMode(PMU_REGULATOR_T regulator, PMU_STOP_ENTRY_T entry)
{
    /* Clear PDDSCFG and LPDSCFG bits */
    PMU->CTRL_B.PDDSCFG = 0x00;
    PMU->CTRL_B.LPDSCFG = 0x00;
    /* Set LPDSCFG bit according to regulator value */
    PMU->CTRL_B.LPDSCFG = regulator;
    /* Set Cortex System Control Register */
    SCB->SCR |= (uint32_t)0x04;
    /* Select STOP mode entry*/
    if (entry == PMU_STOP_ENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __WFE();
    }

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)0x04);
}

/*!
 * @brief     Enters STANDBY mode.
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_EnterSTANDBYMode(void)
{
    /* Select STANDBY mode */
    PMU->CTRL_B.PDDSCFG = BIT_SET;
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= (uint32_t)0x04;
#if defined ( __CC_ARM   )
    __force_stores();
#endif
    /* Request Wait For Interrupt */
    __WFI();

}

/*!
 * @brief     Read the specified PMU flag is set or not.
 *
 * @param     flag: Reads the status of specifies the flag.
 *                  This parameter can be one of the following values:
 *                    @arg PMU_FLAG_WUE : Wake Up flag.
 *                    @arg PMU_FLAG_SB  : StandBy flag.
 *                    @arg PMU_FLAG_PVDO: PVD Output.
 *                    @arg PMU_FLAG_BKPR: Backup regulator ready flag.
 *                    @arg PMU_FLAG_VOSR: This flag indicates that the Regulator voltage
 *                         scaling output selection is ready.
 *
 * @retval    The new state of PMU_FLAG (SET or RESET).
 */
uint8_t PMU_ReadStatusFlag(PMU_FLAG_T flag)
{
    uint8_t BitStatus = BIT_RESET;

    if (flag == PMU_FLAG_WUE)
    {
        BitStatus = PMU->CSTS_B.WUEFLG;
    }
    else if (flag == PMU_FLAG_SB)
    {
        BitStatus = PMU->CSTS_B.SBFLG;
    }
    else if (flag == PMU_FLAG_PVDO)
    {
        BitStatus = PMU->CSTS_B.PVDOFLG;
    }
    else if (flag == PMU_FLAG_BKPR)
    {
        BitStatus = PMU->CSTS_B.BKPRFLG;
    }
    else if (flag == PMU_FLAG_VOSR)
    {
        BitStatus = PMU->CSTS_B.VOSRFLG;
    }

    return BitStatus;
}

/*!
 * @brief     Clears the PMU's pending flags.
 *
 * @param     flag: specifies the flag to clear.
 *            This parameter can be one of the following values:
 *              @arg PMU_FLAG_WUE : Wake Up flag.
 *              @arg PMU_FLAG_SB  : StandBy flag.
 *
 * @retval    None
 */
void PMU_ClearStatusFlag(PMU_FLAG_T flag)
{
    if (flag == PMU_FLAG_WUE)
    {
        PMU->CTRL_B.WUFLGCLR = BIT_SET;
    }
    else if (flag == PMU_FLAG_SB)
    {
        PMU->CTRL_B.SBFLGCLR = BIT_SET;
    }
}

/**@} end of group PMU_Functions */
/**@} end of group PMU_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
