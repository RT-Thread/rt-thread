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
 * @file n32g45x_dbg.c
 * @author Nations Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_dbg.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup DBG
 * @brief DBG driver modules
 * @{
 */

/** @addtogroup DBGMCU_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup DBGMCU_Private_Defines
 * @{
 */

#define IDCODE_DEVID_MASK ((uint32_t)0x00000FFF)
/**
 * @}
 */

/** @addtogroup DBGMCU_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup DBGMCU_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup DBGMCU_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup DBGMCU_Private_Functions
 * @{
 */

/**
 * @brief  Returns the device revision number.
 * @return Device revision identifier
 */
uint32_t DBG_GetRevNum(void)
{
    return (DBG->ID & 0x00FF);
}

/**
 * @brief  Returns the device identifier.
 * @return Device identifier
 */
uint32_t DBG_GetDevNum(void)
{
    uint32_t id = DBG->ID;
    return ((id & 0x00F00000) >> 20) | ((id & 0xFF00) >> 4);
}

/**
 * @brief  Configures the specified peripheral and low power mode behavior
 *   when the MCU under Debug mode.
 * @param DBG_Periph specifies the peripheral and low power mode.
 *   This parameter can be any combination of the following values:
 *     @arg DBG_SLP Keep debugger connection during SLEEP mode
 *     @arg DBG_STOP Keep debugger connection during STOP mode
 *     @arg DBG_STDBY Keep debugger connection during STANDBY mode
 *     @arg DBG_IWDG_STOP Debug IWDG stopped when Core is halted
 *     @arg DBG_WWDG_STOP Debug WWDG stopped when Core is halted
 *     @arg DBG_TIM1_STOP TIM1 counter stopped when Core is halted
 *     @arg DBG_TIM2_STOP TIM2 counter stopped when Core is halted
 *     @arg DBG_TIM3_STOP TIM3 counter stopped when Core is halted
 *     @arg DBG_TIM4_STOP TIM4 counter stopped when Core is halted
 *     @arg DBG_CAN1_STOP Debug CAN2 stopped when Core is halted
 *     @arg DBG_I2C1SMBUS_TIMEOUT I2C1 SMBUS timeout mode stopped when Core is halted
 *     @arg DBG_I2C2SMBUS_TIMEOUT I2C2 SMBUS timeout mode stopped when Core is halted
 *     @arg DBG_TIM5_STOP TIM5 counter stopped when Core is halted
 *     @arg DBG_TIM6_STOP TIM6 counter stopped when Core is halted
 *     @arg DBG_TIM7_STOP TIM7 counter stopped when Core is halted
 *     @arg DBG_TIM8_STOP TIM8 counter stopped when Core is halted
 *     @arg DBG_CAN2_STOP Debug CAN2 stopped when Core is halted
 *     @arg DBGMCU_TIM15_STOP TIM15 counter stopped when Core is halted
 *     @arg DBGMCU_TIM16_STOP TIM16 counter stopped when Core is halted
 *     @arg DBGMCU_TIM17_STOP TIM17 counter stopped when Core is halted
 *     @arg DBGMCU_TIM9_STOP TIM9 counter stopped when Core is halted
 *     @arg DBGMCU_TIM10_STOP TIM10 counter stopped when Core is halted
 *     @arg DBGMCU_TIM11_STOP TIM11 counter stopped when Core is halted
 *     @arg DBGMCU_TIM12_STOP TIM12 counter stopped when Core is halted
 *     @arg DBGMCU_TIM13_STOP TIM13 counter stopped when Core is halted
 *     @arg DBGMCU_TIM14_STOP TIM14 counter stopped when Core is halted
 * @param Cmd new state of the specified peripheral in Debug mode.
 *   This parameter can be: ENABLE or DISABLE.
 */
void DBG_ConfigPeriph(uint32_t DBG_Periph, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_DBGMCU_PERIPH(DBG_Periph));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        DBG->CTRL |= DBG_Periph;
    }
    else
    {
        DBG->CTRL &= ~DBG_Periph;
    }
}

/**
 * @brief Get FLASH size of this chip.
 *
 * @return FLASH size in bytes.
 */
uint32_t DBG_GetFlashSize(void)
{
    return (DBG->ID & 0x000F0000);
}

/**
 * @brief Get SRAM size of this chip.
 *
 * @return SRAM size in bytes.
 */
uint32_t DBG_GetSramSize(void)
{
    return (((DBG->ID & 0xF0000000) >> 28) + 1) << 14;
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
