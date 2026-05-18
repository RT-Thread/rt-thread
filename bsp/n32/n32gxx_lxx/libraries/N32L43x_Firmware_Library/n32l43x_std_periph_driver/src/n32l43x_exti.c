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
 * @file n32l43x_exti.c
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l43x_exti.h"

/** @addtogroup n32l43x_StdPeriph_Driver
 * @{
 */

/** @addtogroup EXTI
 * @brief EXTI driver modules
 * @{
 */

/** @addtogroup EXTI_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup EXTI_Private_Defines
 * @{
 */

#define EXTI_LINENONE ((uint32_t)0x00000) /* No interrupt selected */

/**
 * @}
 */

/** @addtogroup EXTI_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup EXTI_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup EXTI_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup EXTI_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
 */
void EXTI_DeInit(void)
{
    EXTI->IMASK  = 0x00000000;
    EXTI->EMASK  = 0x00000000;
    EXTI->RT_CFG = 0x00000000;
    EXTI->FT_CFG = 0x00000000;
    EXTI->PEND   = 0x0FFFFFFF;
}

/**
 * @brief  Initializes the EXTI peripheral according to the specified
 *         parameters in the EXTI_InitStruct.
 * @param EXTI_InitStruct pointer to a EXTI_InitType structure
 *         that contains the configuration information for the EXTI peripheral.
 */
void EXTI_InitPeripheral(EXTI_InitType* EXTI_InitStruct)
{
    uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
    assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
    assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));
    assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));

    tmp = (uint32_t)EXTI_BASE;

    if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
    {
        /* Clear EXTI line configuration */
        EXTI->IMASK &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->EMASK &= ~EXTI_InitStruct->EXTI_Line;

        tmp += EXTI_InitStruct->EXTI_Mode;

        *(__IO uint32_t*)tmp |= EXTI_InitStruct->EXTI_Line;

        /* Clear Rising Falling edge configuration */
        EXTI->RT_CFG &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->FT_CFG &= ~EXTI_InitStruct->EXTI_Line;

        /* Select the trigger for the selected external interrupts */
        if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
        {
            /* Rising Falling edge */
            EXTI->RT_CFG |= EXTI_InitStruct->EXTI_Line;
            EXTI->FT_CFG |= EXTI_InitStruct->EXTI_Line;
        }
        else
        {
            tmp = (uint32_t)EXTI_BASE;
            tmp += EXTI_InitStruct->EXTI_Trigger;

            *(__IO uint32_t*)tmp |= EXTI_InitStruct->EXTI_Line;
        }
    }
    else
    {
        tmp += EXTI_InitStruct->EXTI_Mode;

        /* Disable the selected external lines */
        *(__IO uint32_t*)tmp &= ~EXTI_InitStruct->EXTI_Line;
    }
}

/**
 * @brief  Fills each EXTI_InitStruct member with its reset value.
 * @param EXTI_InitStruct pointer to a EXTI_InitType structure which will
 *         be initialized.
 */
void EXTI_InitStruct(EXTI_InitType* EXTI_InitStruct)
{
    EXTI_InitStruct->EXTI_Line    = EXTI_LINENONE;
    EXTI_InitStruct->EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
 * @brief  Generates a Software interrupt.
 * @param EXTI_Line specifies the EXTI lines to be enabled or disabled.
 *   This parameter can be any combination of EXTI_Linex where x can be (0..27).
 */
void EXTI_TriggerSWInt(uint32_t EXTI_Line)
{
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));

    EXTI->SWIE |= EXTI_Line;
}

/**
 * @brief  Checks whether the specified EXTI line flag is set or not.
 * @param EXTI_Line specifies the EXTI line flag to check.
 *   This parameter can be:
 *     @arg EXTI_Linex External interrupt line x where x(0..27)
 * @return The new state of EXTI_Line (SET or RESET).
 */
FlagStatus EXTI_GetStatusFlag(uint32_t EXTI_Line)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_GET_EXTI_LINE(EXTI_Line));

    if ((EXTI->PEND & EXTI_Line) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Clears the EXTI's line pending flags.
 * @param EXTI_Line specifies the EXTI lines flags to clear.
 *   This parameter can be any combination of EXTI_Linex where x can be (0..27).
 */
void EXTI_ClrStatusFlag(uint32_t EXTI_Line)
{
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));

    EXTI->PEND = EXTI_Line;
}

/**
 * @brief  Checks whether the specified EXTI line is asserted or not.
 * @param EXTI_Line specifies the EXTI line to check.
 *   This parameter can be:
 *     @arg EXTI_Linex External interrupt line x where x(0..27)
 * @return The new state of EXTI_Line (SET or RESET).
 */
INTStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
    INTStatus bitstatus   = RESET;
    uint32_t enablestatus = 0;
    /* Check the parameters */
    assert_param(IS_GET_EXTI_LINE(EXTI_Line));

    enablestatus = EXTI->IMASK & EXTI_Line;
    if (((EXTI->PEND & EXTI_Line) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Clears the EXTI's line pending bits.
 * @param EXTI_Line specifies the EXTI lines to clear.
 *   This parameter can be any combination of EXTI_Linex where x can be (0..27).
 */
void EXTI_ClrITPendBit(uint32_t EXTI_Line)
{
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));

    EXTI->PEND = EXTI_Line;
}

/**
 * @brief  Select one of EXTI inputs to the RTC TimeStamp event.
 * @param EXTI_TSSEL_Line specifies the EXTI lines to select.
 *   This parameter can be any combination of EXTI_TSSEL_Line where x can be (0..15).
 */
void EXTI_RTCTimeStampSel(uint32_t EXTI_TSSEL_Line)
{
    /* Check the parameters */
    assert_param(IS_EXTI_TSSEL_LINE(EXTI_TSSEL_Line));

    EXTI->TS_SEL &= EXTI_TSSEL_LINE_MASK;
    EXTI->TS_SEL |= EXTI_TSSEL_Line;
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
