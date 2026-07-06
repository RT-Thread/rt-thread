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
 * @file n32g45x_wwdg.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_wwdg.h"
#include "n32g45x_rcc.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup WWDG
 * @brief WWDG driver modules
 * @{
 */

/** @addtogroup WWDG_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup WWDG_Private_Defines
 * @{
 */

/* ----------- WWDG registers bit address in the alias region ----------- */
#define WWDG_OFFADDR (WWDG_BASE - PERIPH_BASE)

/* Alias word address of EWI bit */
#define CFG_OFFADDR  (WWDG_OFFADDR + 0x04)
#define EWINT_BIT    0x09
#define CFG_EWINT_BB (PERIPH_BB_BASE + (CFG_OFFADDR * 32) + (EWINT_BIT * 4))

/* --------------------- WWDG registers bit mask ------------------------ */

/* CTRL register bit mask */
#define CTRL_ACTB_SET ((uint32_t)0x00000080)

/* CFG register bit mask */
#define CFG_TIMERB_MASK ((uint32_t)0xFFFFFE7F)
#define CFG_W_MASK      ((uint32_t)0xFFFFFF80)
#define BIT_MASK        ((uint8_t)0x7F)

/**
 * @}
 */

/** @addtogroup WWDG_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup WWDG_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup WWDG_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup WWDG_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the WWDG peripheral registers to their default reset values.
 */
void WWDG_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_WWDG, ENABLE);
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_WWDG, DISABLE);
}

/**
 * @brief  Sets the WWDG Prescaler.
 * @param WWDG_Prescaler specifies the WWDG Prescaler.
 *   This parameter can be one of the following values:
 *     @arg WWDG_PRESCALER_DIV1 WWDG counter clock = (PCLK1/4096)/1
 *     @arg WWDG_PRESCALER_DIV2 WWDG counter clock = (PCLK1/4096)/2
 *     @arg WWDG_PRESCALER_DIV4 WWDG counter clock = (PCLK1/4096)/4
 *     @arg WWDG_PRESCALER_DIV8 WWDG counter clock = (PCLK1/4096)/8
 */
void WWDG_SetPrescalerDiv(uint32_t WWDG_Prescaler)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_WWDG_PRESCALER_DIV(WWDG_Prescaler));
    /* Clear WDGTB[1:0] bits */
    tmpregister = WWDG->CFG & CFG_TIMERB_MASK;
    /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
    tmpregister |= WWDG_Prescaler;
    /* Store the new value */
    WWDG->CFG = tmpregister;
}

/**
 * @brief  Sets the WWDG window value.
 * @param WindowValue specifies the window value to be compared to the downcounter.
 *   This parameter value must be lower than 0x80.
 */
void WWDG_SetWValue(uint8_t WindowValue)
{
    __IO uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_WWDG_WVALUE(WindowValue));
    /* Clear W[6:0] bits */

    tmpregister = WWDG->CFG & CFG_W_MASK;

    /* Set W[6:0] bits according to WindowValue value */
    tmpregister |= WindowValue & (uint32_t)BIT_MASK;

    /* Store the new value */
    WWDG->CFG = tmpregister;
}

/**
 * @brief  Enables the WWDG Early Wakeup interrupt(EWI).
 */
void WWDG_EnableInt(void)
{
    *(__IO uint32_t*)CFG_EWINT_BB = (uint32_t)ENABLE;
}

/**
 * @brief  Sets the WWDG counter value.
 * @param Counter specifies the watchdog counter value.
 *   This parameter must be a number between 0x40 and 0x7F.
 */
void WWDG_SetCnt(uint8_t Counter)
{
    /* Check the parameters */
    assert_param(IS_WWDG_CNT(Counter));
    /* Write to T[6:0] bits to configure the counter value, no need to do
       a read-modify-write; writing a 0 to WDGA bit does nothing */
    WWDG->CTRL = Counter & BIT_MASK;
}

/**
 * @brief  Enables WWDG and load the counter value.
 * @param Counter specifies the watchdog counter value.
 *   This parameter must be a number between 0x40 and 0x7F.
 */
void WWDG_Enable(uint8_t Counter)
{
    /* Check the parameters */
    assert_param(IS_WWDG_CNT(Counter));
    WWDG->CTRL = CTRL_ACTB_SET | Counter;
}

/**
 * @brief  Checks whether the Early Wakeup interrupt flag is set or not.
 * @return The new state of the Early Wakeup interrupt flag (SET or RESET)
 */
FlagStatus WWDG_GetEWINTF(void)
{
    return (FlagStatus)(WWDG->STS);
}

/**
 * @brief  Clears Early Wakeup interrupt flag.
 */
void WWDG_ClrEWINTF(void)
{
    WWDG->STS = (uint32_t)RESET;
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
