/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_iwdg.h"

void IWDG_Init(IWDG_Type * IWDGx, IWDG_Init_Type * init)
{
    if ( NULL != init )
    {
        IWDGx->KR = IWDG_KEY_UNLOCK;
        IWDGx->PR = init->Prescaler;

        IWDGx->KR = IWDG_KEY_UNLOCK;
        IWDGx->RLR = init->Relaod;

        IWDG_DoReload(IWDGx);
    }
}

void IWDG_Start(IWDG_Type * IWDGx)
{
    IWDGx->KR = IWDG_KEY_ENABLE;
}

uint32_t IWDG_GetStatus(IWDG_Type * IWDGx)
{
    return IWDGx->SR;
}

void IWDG_DoReload(IWDG_Type * IWDGx)
{
    IWDGx->KR = IWDG_KEY_RELOAD;
}

void IWDG_EnableInterrupts(IWDG_Type * IWDGx, uint32_t interrupts, bool enable)
{
    if( (true == enable ) && (IWDG_INT_ALMOST_TIMEOUT == interrupts) )
    {
        IWDGx->CR |= IWDG_CR_IRQSEL_MASK;
    }
    else
    {
        /* if IWDG_EnableInterrupts interrupt was enabled, only MCU reset can close it. */
    }
}

void IWDG_ClearStatus(IWDG_Type * IWDGx, uint32_t status)
{
    if( 0u != ( status & IWDG_CR_IRQCLR_MASK ) )
    {
        IWDGx->CR |=  IWDG_CR_IRQCLR_MASK;
    }
}

/* EOF. */
