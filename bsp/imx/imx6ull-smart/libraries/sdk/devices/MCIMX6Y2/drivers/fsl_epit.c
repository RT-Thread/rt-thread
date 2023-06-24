/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
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

#include "fsl_epit.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Gets the instance from the base address to be used to gate or ungate the module clock
 *
 * @param base EPIT peripheral base address
 *
 * @return The EPIT instance
 */
static uint32_t EPIT_GetInstance(EPIT_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to EPIT bases for each instance. */
static EPIT_Type *const s_epitBases[] = EPIT_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to EPIT clocks for each instance. */
static const clock_ip_name_t s_epitClocks[] = EPIT_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t EPIT_GetInstance(EPIT_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_epitBases); instance++)
    {
        if (s_epitBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_epitBases));

    return instance;
}

void EPIT_Init(EPIT_Type *base, const epit_config_t *config)
{
    assert(config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate the EPIT clock*/
    CLOCK_EnableClock(s_epitClocks[EPIT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    base->CR = 0U;

    EPIT_SoftwareReset(base);

    base->CR =
        (config->enableRunInStop ? EPIT_CR_STOPEN_MASK : 0U) | (config->enableRunInWait ? EPIT_CR_WAITEN_MASK : 0U) |
        (config->enableRunInDbg ? EPIT_CR_DBGEN_MASK : 0U) | (config->enableCounterOverwrite ? EPIT_CR_IOVW_MASK : 0U) |
        (config->enableFreeRun ? 0U : EPIT_CR_RLD_MASK) | (config->enableResetMode ? EPIT_CR_ENMOD_MASK : 0U);

    EPIT_SetClockSource(base, config->clockSource);
    EPIT_SetClockDivider(base, config->divider);
}

void EPIT_Deinit(EPIT_Type *base)
{
    /* Disable EPIT timers */
    base->CR = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the EPIT clock*/
    CLOCK_DisableClock(s_epitClocks[EPIT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void EPIT_GetDefaultConfig(epit_config_t *config)
{
    assert(config);

    config->clockSource = kEPIT_ClockSource_Periph;
    config->divider = 1U;
    config->enableRunInStop = true;
    config->enableRunInWait = true;
    config->enableRunInDbg = false;
    config->enableCounterOverwrite = false;
    config->enableFreeRun = false;
    config->enableResetMode = true;
}
