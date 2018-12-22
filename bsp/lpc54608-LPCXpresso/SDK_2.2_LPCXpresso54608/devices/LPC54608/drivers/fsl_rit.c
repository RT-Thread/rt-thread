/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_rit.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Gets the instance from the base address to be used to gate or ungate the module clock
 *
 * @param base RIT peripheral base address
 *
 * @return The RIT instance
 */
static uint32_t RIT_GetInstance(RIT_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to RIT bases for each instance. */
static RIT_Type *const s_ritBases[] = RIT_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to PIT clocks for each instance. */
static const clock_ip_name_t s_ritClocks[] = RIT_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t RIT_GetInstance(RIT_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_ritBases); instance++)
    {
        if (s_ritBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_ritBases));

    return instance;
}

void RIT_GetDefaultConfig(rit_config_t *config)
{
    assert(config);
    /* Timer operation are no effect in Debug mode */
    config->enableRunInDebug = false;
}

void RIT_Init(RIT_Type *base, const rit_config_t *config)
{
    assert(config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate the RIT clock*/
    CLOCK_EnableClock(s_ritClocks[RIT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Enable RIT timers */
    base->CTRL &= ~RIT_CTRL_RITEN_MASK;

    /* Config timer operation is no effect in debug mode */
    if (!config->enableRunInDebug)
    {
        base->CTRL &= ~RIT_CTRL_RITENBR_MASK;
    }
    else
    {
        base->CTRL |= RIT_CTRL_RITENBR_MASK;
    }
}

void RIT_Deinit(RIT_Type *base)
{
    /* Disable RIT timers */
    base->CTRL |= ~RIT_CTRL_RITEN_MASK;
#ifdef FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
    /* Gate the RIT clock*/
    CLOCK_DisableClock(s_ritClocks[RIT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void RIT_SetTimerCompare(RIT_Type *base, uint64_t count)
{
    /* Disable RIT timers */
    base->CTRL &= ~RIT_CTRL_RITEN_MASK;
    base->COMPVAL = (uint32_t)count;
    base->COMPVAL_H = (uint16_t)(count >> 32U);
}

void RIT_SetMaskBit(RIT_Type *base, uint64_t count)
{
    base->MASK = (uint32_t)count;
    base->MASK_H = (uint16_t)(count >> 32U);
}

uint64_t RIT_GetCompareTimerCount(RIT_Type *base)
{
    uint16_t valueH = 0U;
    uint32_t valueL = 0U;

    /* COMPVAL_H should be read before COMPVAL */
    valueH = base->COMPVAL_H;
    valueL = base->COMPVAL;

    return (((uint64_t)valueH << 32U) + (uint64_t)(valueL));
}

uint64_t RIT_GetCounterTimerCount(RIT_Type *base)
{
    uint16_t valueH = 0U;
    uint32_t valueL = 0U;

    /* COUNTER_H should be read before COUNTER */
    valueH = base->COUNTER_H;
    valueL = base->COUNTER;

    return (((uint64_t)valueH << 32U) + (uint64_t)(valueL));
}

uint64_t RIT_GetMaskTimerCount(RIT_Type *base)
{
    uint16_t valueH = 0U;
    uint32_t valueL = 0U;

    /* MASK_H should be read before MASK */
    valueH = base->MASK_H;
    valueL = base->MASK;

    return (((uint64_t)valueH << 32U) + (uint64_t)(valueL));
}
