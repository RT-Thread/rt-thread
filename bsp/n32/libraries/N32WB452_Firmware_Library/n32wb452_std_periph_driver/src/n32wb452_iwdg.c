/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32wb452_iwdg.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32wb452_iwdg.h"

/** @addtogroup N32WB452_StdPeriph_Driver
 * @{
 */

/** @addtogroup IWDG
 * @brief IWDG driver modules
 * @{
 */

/** @addtogroup IWDG_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup IWDG_Private_Defines
 * @{
 */

/* ---------------------- IWDG registers bit mask ----------------------------*/

/* KEY register bit mask */
#define KEY_ReloadKey ((uint16_t)0xAAAA)
#define KEY_EnableKey ((uint16_t)0xCCCC)

/**
 * @}
 */

/** @addtogroup IWDG_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup IWDG_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup IWDG_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup IWDG_Private_Functions
 * @{
 */

/**
 * @brief  Enables or disables write access to IWDG_PR and IWDG_RLR registers.
 * @param IWDG_WriteAccess new state of write access to IWDG_PR and IWDG_RLR registers.
 *   This parameter can be one of the following values:
 *     @arg IWDG_WRITE_ENABLE Enable write access to IWDG_PR and IWDG_RLR registers
 *     @arg IWDG_WRITE_DISABLE Disable write access to IWDG_PR and IWDG_RLR registers
 */
void IWDG_WriteConfig(uint16_t IWDG_WriteAccess)
{
    /* Check the parameters */
    assert_param(IS_IWDG_WRITE(IWDG_WriteAccess));
    IWDG->KEY = IWDG_WriteAccess;
}

/**
 * @brief  Sets IWDG Prescaler value.
 * @param IWDG_Prescaler specifies the IWDG Prescaler value.
 *   This parameter can be one of the following values:
 *     @arg IWDG_PRESCALER_DIV4 IWDG prescaler set to 4
 *     @arg IWDG_PRESCALER_DIV8 IWDG prescaler set to 8
 *     @arg IWDG_PRESCALER_DIV16 IWDG prescaler set to 16
 *     @arg IWDG_PRESCALER_DIV32 IWDG prescaler set to 32
 *     @arg IWDG_PRESCALER_DIV64 IWDG prescaler set to 64
 *     @arg IWDG_PRESCALER_DIV128 IWDG prescaler set to 128
 *     @arg IWDG_PRESCALER_DIV256 IWDG prescaler set to 256
 */
void IWDG_SetPrescalerDiv(uint8_t IWDG_Prescaler)
{
    /* Check the parameters */
    assert_param(IS_IWDG_PRESCALER_DIV(IWDG_Prescaler));
    IWDG->PREDIV = IWDG_Prescaler;
}

/**
 * @brief  Sets IWDG Reload value.
 * @param Reload specifies the IWDG Reload value.
 *   This parameter must be a number between 0 and 0x0FFF.
 */
void IWDG_CntReload(uint16_t Reload)
{
    /* Check the parameters */
    assert_param(IS_IWDG_RELOAD(Reload));
    IWDG->RELV = Reload;
}

/**
 * @brief  Reloads IWDG counter with value defined in the reload register
 *   (write access to IWDG_PR and IWDG_RLR registers disabled).
 */
void IWDG_ReloadKey(void)
{
    IWDG->KEY = KEY_ReloadKey;
}

/**
 * @brief  Enables IWDG (write access to IWDG_PR and IWDG_RLR registers disabled).
 */
void IWDG_Enable(void)
{
    IWDG->KEY = KEY_EnableKey;
}

/**
 * @brief  Checks whether the specified IWDG flag is set or not.
 * @param IWDG_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg IWDG_PVU_FLAG Prescaler Value Update on going
 *     @arg IWDG_CRVU_FLAG Reload Value Update on going
 * @return The new state of IWDG_FLAG (SET or RESET).
 */
FlagStatus IWDG_GetStatus(uint16_t IWDG_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_IWDG_FLAG(IWDG_FLAG));
    if ((IWDG->STS & IWDG_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
