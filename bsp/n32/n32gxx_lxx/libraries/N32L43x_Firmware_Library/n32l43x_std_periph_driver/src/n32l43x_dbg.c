/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
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
 * @file n32l43x_dbg.c
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l43x_dbg.h"

/** @addtogroup n32l43x_StdPeriph_Driver
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


void GetUCID(uint8_t *UCIDbuf)
{
    uint8_t num = 0;
    uint32_t* ucid_addr = (void*)0;
    uint32_t temp = 0;

    ucid_addr = (uint32_t*)UCID_BASE;

    for (num = 0; num < UCID_LENGTH;)
    {
        temp = *(__IO uint32_t*)(ucid_addr++);
        UCIDbuf[num++] = (temp & 0xFF);
        UCIDbuf[num++] = (temp & 0xFF00) >> 8;
        UCIDbuf[num++] = (temp & 0xFF0000) >> 16;
        UCIDbuf[num++] = (temp & 0xFF000000) >> 24;
    }
}

/**
 * @brief  Returns the UID.
 * @return UID
 */

void GetUID(uint8_t *UIDbuf)
{
    uint8_t num = 0;
    uint32_t* uid_addr = (void*)0;
    uint32_t temp = 0;

    uid_addr = (uint32_t*)UID_BASE;

    for (num = 0; num < UID_LENGTH;)
    {
        temp = *(__IO uint32_t*)(uid_addr++);
        UIDbuf[num++] = (temp & 0xFF);
        UIDbuf[num++] = (temp & 0xFF00) >> 8;
        UIDbuf[num++] = (temp & 0xFF0000) >> 16;
        UIDbuf[num++] = (temp & 0xFF000000) >> 24;
    }
}

/**
 * @brief  Returns the DBGMCU_ID.
 * @return DBGMCU_ID
 */

void GetDBGMCU_ID(uint8_t *DBGMCU_IDbuf)
{
    uint8_t num = 0;
    uint32_t* dbgid_addr = (void*)0;
    uint32_t temp = 0;

    dbgid_addr = (uint32_t*)DBGMCU_ID_BASE;
    for (num = 0; num < DBGMCU_ID_LENGTH;)
    {
        temp = *(__IO uint32_t*)(dbgid_addr++);
        DBGMCU_IDbuf[num++] = (temp & 0xFF);
        DBGMCU_IDbuf[num++] = (temp & 0xFF00) >> 8;
        DBGMCU_IDbuf[num++] = (temp & 0xFF0000) >> 16;
        DBGMCU_IDbuf[num++] = (temp & 0xFF000000) >> 24;
    }
}

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
 *     @arg DBG_SLEEP Keep debugger connection during SLEEP mode
 *     @arg DBG_STOP Keep debugger connection during STOP mode
 *     @arg DBG_STDBY Keep debugger connection during STANDBY mode
 *     @arg DBG_IWDG_STOP Debug IWDG stopped when Core is halted
 *     @arg DBG_WWDG_STOP Debug WWDG stopped when Core is halted
 *     @arg DBG_TIM1_STOP TIM1 counter stopped when Core is halted
 *     @arg DBG_TIM2_STOP TIM2 counter stopped when Core is halted
 *     @arg DBG_TIM3_STOP TIM3 counter stopped when Core is halted
 *     @arg DBG_TIM4_STOP TIM4 counter stopped when Core is halted
 *     @arg DBG_CAN_STOP Debug CAN stopped when Core is halted
 *     @arg DBG_I2C1SMBUS_TIMEOUT I2C1 SMBUS timeout mode stopped when Core is halted
 *     @arg DBG_I2C2SMBUS_TIMEOUT I2C2 SMBUS timeout mode stopped when Core is halted
 *     @arg DBG_TIM8_STOP TIM8 counter stopped when Core is halted
 *     @arg DBG_TIM5_STOP TIM5 counter stopped when Core is halted
 *     @arg DBG_TIM6_STOP TIM6 counter stopped when Core is halted
 *     @arg DBG_TIM7_STOP TIM7 counter stopped when Core is halted
 *     @arg DBG_TIM9_STOP TIM9 counter stopped when Core is halted

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
