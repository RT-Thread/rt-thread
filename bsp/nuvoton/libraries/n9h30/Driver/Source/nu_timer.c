/**************************************************************************//**
 * @file     timer.c
 * @brief    N9H30 series TIMER driver source file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "N9H30.h"
#include "nu_sys.h"
#include "nu_timer.h"

void TIMER_SET_CMP_VALUE(uint32_t timer, uint32_t u32Cmpr)
{
    uint32_t u32TmrCMPROffset;

    u32TmrCMPROffset = REG_TMR0_CMPR + timer * 0x10;

    outpw(u32TmrCMPROffset, u32Cmpr);
}

void TIMER_SET_OPMODE(uint32_t timer, uint32_t u32OpMode)
{
    uint32_t u32TmrCSROffset;

    u32TmrCSROffset = REG_TMR0_CSR + timer * 0x10;

    outpw(u32TmrCSROffset, (inpw(u32TmrCSROffset) & ~(0x3UL << 27)) | u32OpMode);
}

void TIMER_SET_PRESCALE_VALUE(uint32_t timer, uint32_t u32PreScale)
{
    uint32_t u32TmrCSROffset;

    u32TmrCSROffset = REG_TMR0_CSR + timer * 0x10;

    outpw(u32TmrCSROffset, (inpw(u32TmrCSROffset) & ~(0xFFUL)) | u32PreScale);
}

uint32_t TIMER_GetModuleClock(uint32_t timer)
{
    return 12000000;
}

void TIMER_Start(uint32_t timer)
{
    uint32_t u32TmrCSROffset;

    u32TmrCSROffset = REG_TMR0_CSR + timer * 0x10;

    outpw(u32TmrCSROffset, inpw(u32TmrCSROffset) | TIMER_COUNTER_ENABLE);
}

void TIMER_Stop(uint32_t timer)
{
    uint32_t u32TmrCSROffset;

    u32TmrCSROffset = REG_TMR0_CSR + timer * 0x10;

    outpw(u32TmrCSROffset, inpw(u32TmrCSROffset) & ~TIMER_COUNTER_ENABLE);
}

void TIMER_ClearCounter(uint32_t timer)
{
    uint32_t u32TmrCSROffset;

    u32TmrCSROffset = REG_TMR0_CSR + timer * 0x10;

    outpw(u32TmrCSROffset, inpw(u32TmrCSROffset) | TIMER_COUNTER_RESET);
}

uint32_t TIMER_GetCounter(uint32_t timer)
{
    uint32_t u32TmrDROffset;

    u32TmrDROffset = REG_TMR0_DR + timer * 0x10;

    return inpw(u32TmrDROffset);
}

uint32_t TIMER_GetCompareData(uint32_t timer)
{
    uint32_t u32TmrCMPROffset;

    u32TmrCMPROffset = REG_TMR0_CMPR + timer * 0x10;

    return inpw(u32TmrCMPROffset);
}

void TIMER_EnableInt(uint32_t timer)
{
    uint32_t u32TmrCSROffset;

    u32TmrCSROffset = REG_TMR0_CSR + timer * 0x10;

    outpw(u32TmrCSROffset,  inpw(u32TmrCSROffset) | TIMER_INTERRUPT_ENABLE);
}

void TIMER_DisableInt(uint32_t timer)
{
    uint32_t u32TmrCSROffset;

    u32TmrCSROffset = REG_TMR0_CSR + timer * 0x10;

    outpw(u32TmrCSROffset,  inpw(u32TmrCSROffset) & ~TIMER_INTERRUPT_ENABLE);
}

void TIMER_Close(uint32_t timer)
{
    uint32_t u32TmrCSROffset;

    u32TmrCSROffset = REG_TMR0_CSR + timer * 0x10;

    outpw(u32TmrCSROffset, 0);
}

uint32_t TIMER_Open(uint32_t timer, uint32_t u32Mode, uint32_t u32Freq)
{
    uint32_t u32Clk = TIMER_GetModuleClock(timer);
    uint32_t u32Cmpr = 0, u32Prescale = 0;
    uint32_t u32TmrOffset = 0;

    // Fastest possible timer working freq is u32Clk / 2. While cmpr = 2, pre-scale = 0
    if (u32Freq > (u32Clk / 2))
    {
        u32Cmpr = 2;
    }
    else
    {
        /* Clock source is only XIN. */
        u32Cmpr = u32Clk / u32Freq;
    }

    u32TmrOffset = timer * 0x10;

    TIMER_Close(timer);            /* disable timer */
    TIMER_DisableInt(timer);       /* clear for safety */

    outpw(REG_TMR0_CMPR + u32TmrOffset,  u32Cmpr);
    outpw(REG_TMR0_CSR + u32TmrOffset,   u32Mode | u32Prescale);

    return (u32Clk / (u32Cmpr * (u32Prescale + 1)));
}

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/

