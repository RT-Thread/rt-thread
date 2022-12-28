/*!
 * @file        apm32f0xx_comp.c
 *
 * @brief       This file contains all the functions for the COMP peripheral
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
#include "apm32f0xx_comp.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup COMP_Driver
  @{
*/

/** @defgroup COMP_Macros Macros
  @{
*/

/**@} end of group COMP_Macros */

/** @defgroup COMP_Enumerations Enumerations
  @{
*/

/**@} end of group COMP_Enumerations */

/** @defgroup COMP_Structures Structures
  @{
*/

/**@} end of group COMP_Structures */

/** @defgroup COMP_Variables Variables
  @{
*/

/**@} end of group COMP_Variables */

/** @defgroup COMP_Functions Functions
  @{
*/

/*!
 * @brief    Reset COMP peripheral registers to their default values.
 *
 * @param    None
 *
 * @retval   None
 *
 * @note     Deinitialization can't be performed if the COMP configuration is locked.
 *           To unlock the configuration, perform a system reset.
 */
void COMP_Reset(void)
{
    COMP->CSTS = ((uint32_t)0x00000000);
}

/*!
 * @brief    Configs the COMP peripheral according to the specified parameters
 *           in COMP_InitStruct
 *
 * @param    compSelect: the selected comparator.
 *            This parameter can be one of the following values:
 *              @arg COMP_SELECT_COMP1: COMP1 selected
 *              @arg COMP_SELECT_COMP2: COMP2 selected
 *
 * @param    compConfig: pointer to an COMP_Config_T structure that contains
 *           the configuration information for the specified COMP peripheral.
 *
 * @retval   None
 *
 * @note     If the selected comparator is locked, initialization can't be performed.
 *           To unlock the configuration, perform a system reset.
 *
 * @note     By default, PA1 is selected as COMP1 non inverting input.
 *           To use PA4 as COMP1 non inverting input call COMP_EnableSwitch() after COMP_Config()
 *
 */
void COMP_Config(COMP_SELECT_T compSelect, COMP_Config_T* compConfig)
{
    if (compSelect == COMP_SELECT_COMP1)
    {
        COMP->CSTS_B.INVINSEL1 = compConfig->invertingInput;
        COMP->CSTS_B.OUTSEL1 = compConfig->output;
        COMP->CSTS_B.OPINV1 = compConfig->outputPol;
        COMP->CSTS_B.HYSCFG1    = compConfig->hysterrsis;
        COMP->CSTS_B.MOD1   = compConfig->mode;
    }
    else
    {
        COMP->CSTS_B.INVINSEL2 = compConfig->invertingInput;
        COMP->CSTS_B.OUTSEL2  = compConfig->output;
        COMP->CSTS_B.OPINV2  = compConfig->outputPol;
        COMP->CSTS_B.HYSCFG2 = compConfig->hysterrsis;
        COMP->CSTS_B.MOD2 = compConfig->mode;
    }
}

/*!
 * @brief    Fills each compConfig member with initial value value.
 *
 * @param    compConfig: pointer to an COMP_InitTypeDef structure which will
 *           be initialized.
 *
 * @retval   None
 */
void COMP_ConfigStructInit(COMP_Config_T* compConfig)
{
    compConfig->invertingInput  = COMP_INVERTING_INPUT_1_4VREFINT;
    compConfig->output          = COMP_OUTPUT_NONE;
    compConfig->outputPol       = COMP_OUTPUTPOL_NONINVERTED;
    compConfig->hysterrsis      = COMP_HYSTERRSIS_NO;
    compConfig->mode            = COMP_MODE_HIGHSPEED;
}

/*!
 * @brief    Enable the COMP peripheral.
 *
 * @param    compSelect: the selected comparator.
 *            This parameter can be one of the following values:
 *              @arg COMP_SELECT_COMP1: COMP1 selected
 *              @arg COMP_SELECT_COMP2: COMP2 selected
 *
 * @retval   None
 *
 * @note     If the selected comparator is locked, enable can't be performed.
 *           To unlock the configuration, perform a system reset.
 */
void COMP_Enable(COMP_SELECT_T compSelect)
{
    if (compSelect == COMP_SELECT_COMP1)
    {
        COMP->CSTS_B.EN1 = SET;
    }
    else
    {
        COMP->CSTS_B.EN2 = SET;
    }
}

/*!
 * @brief    Disable the COMP peripheral.
 *
 * @param    compSelect: the selected comparator.
 *            This parameter can be one of the following values:
 *              @arg COMP_SELECT_COMP1: COMP1 selected
 *              @arg COMP_SELECT_COMP2: COMP2 selected
 *
 * @retval   None
 *
 * @note     If the selected comparator is locked, disable can't be performed.
 *           To unlock the configuration, perform a system reset.
 */
void COMP_Disable(COMP_SELECT_T compSelect)
{
    if (compSelect == COMP_SELECT_COMP1)
    {
        COMP->CSTS_B.EN1 = RESET;
    }
    else
    {
        COMP->CSTS_B.EN2 = RESET;
    }
}

/*!
 * @brief    Close the SW1 switch.
 *
 * @param    None
 *
 * @retval   None
 *
 * @note     This switch is solely intended to redirect signals onto high
 *           impedance input, such as COMP1 non-inverting input (highly resistive switch)
 */
void COMP_EnableSwitch(void)
{
    COMP->CSTS_B.SW1 = SET;
}

/*!
 * @brief    Open the SW1 switch.
 *
 * @param    None
 *
 * @retval   None
 */
void COMP_DisableSwitch(void)
{
    COMP->CSTS_B.SW1 = RESET;
}

/*!
 * @brief    Return the output level (high or low) of the selected comparator.
 *
 * @param    compSelect: the selected comparator.
 *            This parameter can be one of the following values:
 *              @arg COMP_SELECT_COMP1: COMP1 selected
 *              @arg COMP_SELECT_COMP2: COMP2 selected
 *
 * @retval   Returns the selected comparator output level: low or high.
 */
uint32_t COMP_ReadOutPutLevel(COMP_SELECT_T compSelect)
{
    uint32_t compOUT = 0x00;
    if (compSelect == COMP_SELECT_COMP1)
    {
        if ((COMP->CSTS & COMP_CSTS_COMP1OUT)  != 0)
        {
            compOUT = COMP_OUTPUTLEVEL_HIGH;
        }
        else
            compOUT = COMP_OUTPUTLEVEL_LOW;
    }
    else
    {
        if ((COMP->CSTS & COMP_CSTS_COMP2OUT)  != 0)
        {
            compOUT = COMP_OUTPUTLEVEL_HIGH;
        }
        else
            compOUT = COMP_OUTPUTLEVEL_LOW;
    }
    return (uint32_t)(compOUT);
}

/*!
 * @brief    Enablesthe window mode.
 *
 * @param    None
 *
 * @retval   None
 */
void COMP_EnableWindow(void)
{
    COMP->CSTS_B.WMODEN = SET;
}

/*!
 * @brief    Disables the window mode.
 *
 * @param    None
 *
 * @retval   None
 */
void COMP_DisnableWindow(void)
{
    COMP->CSTS_B.WMODEN = RESET;
}

/*!
 * @brief    Lock the selected comparator configuration.
 *
 * @param    compSelect: selects the comparator to be locked
 *             This parameter can be one of  the following values:
 *               @arg COMP_SELECT_COMP1: COMP1 configuration is locked.
 *               @arg COMP_SELECT_COMP2: COMP2 configuration is locked.
 *
 * @retval   None
 */
void COMP_ConfigLOCK(COMP_SELECT_T compSelect)
{
    if (compSelect == COMP_SELECT_COMP1)
    {
        COMP->CSTS_B.LOCK1 = SET;
    }
    else
    {
        COMP->CSTS_B.LOCK2 = SET;
    }
}

/**@} end of group COMP_Functions */
/**@} end of group COMP_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
