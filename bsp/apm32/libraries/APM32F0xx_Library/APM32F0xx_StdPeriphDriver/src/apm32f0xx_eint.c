/*!
 * @file        apm32f0xx_eint.c
 *
 * @brief       This file contains all the functions for the EINT peripheral
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
#include "apm32f0xx_eint.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
  */

/** @addtogroup EINT_Driver
  @{
  */

/** @defgroup EINT_Macros Macros
  @{
  */

/**@} end of group EINT_Macros */

/** @defgroup EINT_Enumerates Enumerates
  @{
  */

/**@} end of group EINT_Enumerates */

/** @defgroup EINT_Structures Structures
  @{
  */

/**@} end of group EINT_Structures */

/** @defgroup EINT_Variables Variables
  @{
  */

/**@} end of group EINT_Variables */

/** @defgroup EINT_Functions Functions
  @{
  */

/*!
 * @brief     Set the EINT peripheral registers to their default reset values
 *
 * @param     None
 *
 * @retval    None
 */
void EINT_Reset(void)
{
    EINT->IMASK = EINT_INTMASK_RESET_VALUE;
    EINT->EMASK = EINT_EVTMASK_RESET_VALUE;
    EINT->RTEN  = EINT_RTSEL_RESET_VALUE;
    EINT->FTEN  = EINT_FTSEL_RESET_VALUE;
    EINT->IPEND = EINT_PEND_RESET_VALUE;
}

/*!
 * @brief       Configure the EINT
 *
 * @param       eintConfig: Pointer to EINT_Config_T structure
 *
 * @retval      None
 */
void EINT_Config(EINT_Config_T* eintConfig)
{
    if (eintConfig->lineCmd  == DISABLE)
    {
        if (eintConfig->mode == EINT_MODE_INTERRUPT)
        {
            EINT->IMASK &= ~eintConfig->line;
        }
        else if (eintConfig->mode == EINT_MODE_EVENT)
        {
            EINT->EMASK &= ~eintConfig->line;
        }
    }
    else
    {
        if (eintConfig->mode == EINT_MODE_INTERRUPT)
        {
            EINT->IMASK |= eintConfig->line;
        }
        else if (eintConfig->mode == EINT_MODE_EVENT)
        {
            EINT->EMASK |= eintConfig->line;
        }

        if (eintConfig->trigger == EINT_TRIGGER_RISING)
        {
            EINT->RTEN |= eintConfig->line;
        }
        else if (eintConfig->trigger == EINT_TRIGGER_FALLING)
        {
            EINT->FTEN |= eintConfig->line;
        }
        else
        {
            EINT->RTEN |= eintConfig->line;
            EINT->FTEN |= eintConfig->line;
        }

    }
}

/*!
 * @brief       Fills each EINT_Config_T member with its default value
 *
 * @param       eintConfig: Pointer to a EINT_Config_T structure which will be initialized
 *
 * @retval      None
 */
void EINT_ConfigStructInit(EINT_Config_T* eintConfig)
{
    eintConfig->line    = EINT_LINENONE;
    eintConfig->mode    = EINT_MODE_INTERRUPT;
    eintConfig->trigger = EINT_TRIGGER_FALLING;
    eintConfig->lineCmd = DISABLE;
}

/*!
 * @brief     Select software interrupt on EINT line
 *
 * @param     line: specifies the EINT line on which the software interrupt
 *
 * @retval    None
 */
void EINT_SelectSWInterrupt(uint32_t line)
{
    EINT->SWINTE |= (uint32_t)line;
}

/*!
 * @brief    Read the specified EINT line flag
 *
 * @param    line: Select the EINT line
 *
 * @retval   status: The new state of flag (SET or RESET)
 */
uint8_t EINT_ReadStatusFlag(uint32_t line)
{
    uint8_t status = RESET;

    if ((EINT->IPEND & line) != (uint32_t)RESET)
    {
        status = SET;
    }
    else
    {
        status = RESET;
    }

    return status;
}

/*!
 * @brief    Clears the EINT line pending bits
 *
 * @param    line: Select the EINT line
 *
 * @retval   None
 */
void EINT_ClearStatusFlag(uint32_t line)
{
    EINT->IPEND = line;
}

/*!
 * @brief    Read the specified EINT line interrupt flag
 *
 * @param    line: Select the EINT line
 *
 * @retval   None
 */
uint8_t EINT_ReadIntFlag(uint32_t line)
{
    uint8_t status = RESET;
    uint32_t enablestatus = 0;

    enablestatus = EINT->IMASK & line;

    if ((EINT->IPEND & line) != ((uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
    {
        status = SET;
    }
    else
    {
        status = RESET;
    }

    return status;
}

/*!
 * @brief    Clears the EINT line pending bits
 *
 * @param    line: Select the EINT line
 *
 * @retval   None
 */
void EINT_ClearIntFlag(uint32_t line)
{
    EINT->IPEND = line;
}

/**@} end of group EINT_Functions */
/**@} end of group EINT_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
