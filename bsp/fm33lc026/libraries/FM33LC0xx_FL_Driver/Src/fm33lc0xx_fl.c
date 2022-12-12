/**
  ****************************************************************************************************
  * @file    fm33lc0xx_fl.c
  * @author  FMSH Application Team
  * @brief   Source file of FL Driver Library
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  ****************************************************************************************************
  */


/* Includes ----------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl.h"

/** @addtogroup FL_EF_DELAY
  * @{
  */

/**
  * @brief  Initialize the timer(default is Systick) used as delay timer.
  * @note   The function is declared as __WEAK to be overwritten in case of other
  *         implementation in user file.
  * @param  None
  * @retval None
  */
__WEAK void FL_DelayInit(void)
{
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief  Provide block delay in microseconds.
  * @note   The function is declared as __WEAK to be overwritten in case of other
  *         implementation in user file.
  * @param  count   specifies the delay count in microseconds.
  * @retval None
  */
__WEAK void FL_DelayUs(uint32_t count)
{
    count = FL_DELAY_US * count;
    count = count > 16777216 ? 16777216 : count;
    SysTick->LOAD = count - 1;
    SysTick->VAL = 0;
    while(!((SysTick->CTRL >> 16) & 0x1));
}

/**
  * @brief  Provide blocking delay in milliseconds.
  * @note   The function is declared as __WEAK to be overwritten in case of other
  *         implementation in user file.
  * @param  count   specifies the delay count in milliseconds.
  * @retval None
  */
__WEAK void FL_DelayMs(uint32_t count)
{
    while(count--)
    {
        FL_DelayUs(1000);
    }
}

/**
  * @brief  Provide no-blocking delay initialization in microseconds.
  * @note   Should be follow By while(!FL_DelayEnd()){ ** user code ** } immediately.
  *         The function is declared as __WEAK to be overwritten in case of other
  *         implementation in user file.
  * @param  count   specifies the delay count in microseconds.
  * @retval None
  */
__WEAK void FL_DelayUsStart(uint32_t count)
{
    count = FL_DELAY_US * count;
    count = count > 16777216 ? 16777216 : count;
    SysTick->LOAD = count - 1;
    SysTick->VAL = 0;
}

/**
  * @brief  Provide no-blocking delay initialization in milliseconds.
  * @note   Should be followed By while(!FL_DelayEnd()){ ** user code ** }.
  *         The function is declared as __WEAK to be overwritten in case of other
  *         implementation in user file.
  * @param  count   specifies the delay count in milliseconds.
  * @retval None
  */
__WEAK void FL_DelayMsStart(uint32_t count)
{
    FL_DelayUsStart(1000 * count);
}

/**
  * @brief  Showing if the no-blocking delay has ended.
  * @note   Should be used with FL_DelayMs/UsStart() function.
  *         The function is declared as __WEAK to be overwritten in case of other
  *         implementation in user file.
  * @param  count   specifies the delay count in milliseconds.
  * @retval true  - delay has ended
  *         false - delay is in progress
  */
__WEAK bool FL_DelayEnd(void)
{
    return (((SysTick->CTRL >> 16) & 0x1) == 0x1);
}

/**
  * @}
  */

/** @addtogroup FL_EF_DELAY
  * @{
  */

void FL_Init(void)
{
    /* Init delay support function */
    FL_DelayInit();
}

/**
  * @}
  */

/** @addtogroup FL_EF_NVIC
  * @{
  */

/**
  * @brief  Configure NVIC for specified Interrupt.
  * @param  configStruct    NVIC configuration.
  * @param  irq             Interrupt number.
  * @retval None
  */
void FL_NVIC_Init(FL_NVIC_ConfigTypeDef *configStruct, IRQn_Type irq)
{
    /* Check parameter */
    if(configStruct->preemptPriority > 3)
    {
        configStruct->preemptPriority = 3;
    }
    NVIC_DisableIRQ(irq);
    NVIC_SetPriority(irq, configStruct->preemptPriority);
    NVIC_EnableIRQ(irq);
}

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/



