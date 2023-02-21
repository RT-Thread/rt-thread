/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_tim_basic.h"

bool TIM_BASIC_Init(TIM_BASIC_Type * TIMx, TIM_BASIC_Init_Type * init)
{
    TIMx->CR1 = (TIMx->CR1 & ~(TIM_BASIC_CR1_OPM_MASK | TIM_BASIC_CR1_APRE_MASK) )
              | TIM_BASIC_CR1_OPM(init->PeriodMode)
              | ((init->EnablePreloadPeriod) ? TIM_BASIC_CR1_APRE_MASK: 0u)
              ;

    /* Check StepFreqHz validity. */
    if ( (init->StepFreqHz == 0u) || (init->StepFreqHz > init->ClockFreqHz) )
    {
        return false;
    }
    /* Calculate prescaler of the timer.*/
    TIMx->PSC = init->ClockFreqHz / init->StepFreqHz - 1u;
    /* Set the period length. */
    TIMx->ARR = init->Period;
    return true;
}

void TIM_BASIC_Start(TIM_BASIC_Type * TIMx)
{
    TIMx->CR1 |= TIM_BASIC_CR1_CEN_MASK;
}

void TIM_BASIC_Stop(TIM_BASIC_Type * TIMx)
{
    TIMx->CR1 &= ~TIM_BASIC_CR1_CEN_MASK;
}

uint32_t TIM_BASIC_GetCounterValue(TIM_BASIC_Type * TIMx)
{
    return TIMx->CNT;
}

void TIM_BASIC_EnableInterrupts(TIM_BASIC_Type *TIMx, uint32_t interrupts, bool enable)
{
    if (enable)
    {
        TIMx->DIER |= interrupts;
    }
    else
    {
        TIMx->DIER &= ~interrupts;
    }
}

void TIM_BASIC_EnableDMA(TIM_BASIC_Type *TIMx, uint32_t dmas, bool enable)
{
    if (enable)
    {
        TIMx->DIER |= dmas;
    }
    else
    {
        TIMx->DIER &= ~dmas;
    }
}

void TIM_BASIC_DoSwTrigger(TIM_BASIC_Type *TIMx, uint32_t swtrgs)
{
    TIMx->EGR = swtrgs;
}

uint32_t TIM_BASIC_GetInterruptStatus(TIM_BASIC_Type * TIMx)
{
    return TIMx->SR;
}

void TIM_BASIC_ClearInterruptStatus(TIM_BASIC_Type *TIMx, uint32_t status)
{
    TIMx->SR &= ~status;
}

/* EOF. */

