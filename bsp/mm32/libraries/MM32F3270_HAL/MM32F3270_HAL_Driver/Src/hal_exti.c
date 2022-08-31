/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_exti.h"

void EXTI_EnableLineInterrupt(EXTI_Type * EXTIx, uint32_t lines, bool enable)
{
    if (enable)
    {
        EXTIx->IMR |= lines;
    }
    else
    {
        EXTIx->IMR &= ~ lines;
    }
}

void EXTI_EnableLineEvent(EXTI_Type * EXTIx, uint32_t lines, bool enable)
{
    if (enable)
    {
        EXTIx->EMR |= lines;
    }
    else
    {
        EXTIx->EMR &= ~ lines;
    }
}

void EXTI_SetTriggerIn(EXTI_Type * EXTIx, uint32_t lines, EXTI_TriggerIn_Type trgin)
{
    switch (trgin)
    {
        case EXTI_TriggerIn_Disable:
            EXTIx->RTSR &= ~ lines;
            EXTIx->FTSR &= ~ lines;
            break;
        case EXTI_TriggerIn_RisingEdge:
            EXTI->RTSR |= lines;
            EXTIx->FTSR &= ~ lines;
            break;
        case EXTI_TriggerIn_FallingEdge:
            EXTI->RTSR &= ~ lines;
            EXTI->FTSR |= lines;
            break;
        case EXTI_TriggerIn_BothEdges:
            EXTI->RTSR |= lines;
            EXTI->FTSR |= lines;
            break;
        default:
            break;
    }
}

void EXTI_DoSwTrigger(EXTI_Type * EXTIx, uint32_t lines)
{
    EXTIx->SWIER = lines;
}

uint32_t EXTI_GetLineStatus(EXTI_Type * EXTIx)
{
    return EXTIx->PR;
}

void EXTI_ClearLineStatus(EXTI_Type * EXTIx, uint32_t lines)
{
    EXTIx->PR |= lines;
}

/* EOF. */

