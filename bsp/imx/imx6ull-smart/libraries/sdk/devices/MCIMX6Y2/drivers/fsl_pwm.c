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

#include "fsl_pwm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the instance from the base address
 *
 * @param base PWM peripheral base address
 *
 * @return The PWM module instance
 */
static uint32_t pwm_get_instance(PWM_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to PWM bases for each instance. */
static PWM_Type *const s_pwmBases[] = PWM_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of PWM clock name. */
static const clock_ip_name_t s_pwmClock[] = PWM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t pwm_get_instance(PWM_Type *base)
{
    uint32_t instance;
    uint32_t pwmArrayCount = (sizeof(s_pwmBases) / sizeof(s_pwmBases[0]));

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < pwmArrayCount; instance++)
    {
        if (s_pwmBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < pwmArrayCount);

    return instance;
}

status_t pwm_init(PWM_Type *base, const pwm_config_t *config)
{
    assert(config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate PWM clock */
    CLOCK_EnableClock(s_pwmClock[pwm_get_instance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Setup the PWM operation */
    base->PWMCR = (PWM_PWMCR_REPEAT(config->sampleRepeat) | PWM_PWMCR_PRESCALER(config->prescale) |
                    PWM_PWMCR_CLKSRC(config->clockSource) | PWM_PWMCR_POUTC(config->outputConfig) |
                    PWM_PWMCR_HCTR(config->halfWordSwap) | PWM_PWMCR_BCTR(config->byteSwap) |
                    PWM_PWMCR_STOPEN(config->enableStopMode) | PWM_PWMCR_DBGEN(config->enableDebugMode) |
                    PWM_PWMCR_WAITEN(config->enableWaitMode) | PWM_PWMCR_DOZEN(config->enableDozeMode) |
                    PWM_PWMCR_FWM(config->fifoWater));

    return kStatus_Success;
}

void pwm_deinit(PWM_Type *base)
{
    /* Set clock source to none to disable counter */
    base->PWMCR &= ~(PWM_PWMCR_CLKSRC_MASK);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the PWM clock */
    CLOCK_DisableClock(s_pwmClock[pwm_get_instance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void pwm_get_default_config(pwm_config_t *config)
{
    assert(config);

    /* Stop mode disabled */
    config->enableStopMode = false;
    /* Doze mode disabled */
    config->enableDozeMode = false;
    /* Wait mode disabled */
    config->enableWaitMode = false;
    /* Debug mode disabled */
    config->enableDebugMode = false;
    /* Choose low frequency clock to control counter operation */
    config->clockSource = KPWM_LOW_FREQUENCY_CLOCK;
    /* PWM clock devide by (config->prescale + 1) */
    config->prescale = 0U;
    /* Output pin is set at rollover and cleared at comparison */
    config->outputConfig = KPWM_SET_AT_ROLLOVER_AND_CLEAR_AT_COMPARISON;
    /* FIFO empty flag is set when there are more than or equal to 2 empty slots in FIFO */
    config->fifoWater = KPWM_FIFO_WATERMARK_2;
    /* Use each sample once */
    config->sampleRepeat = KPMW_EACH_SAMPLE_ONCE;
    /* byte ordering remains the same */
    config->byteSwap = KPWM_BYTE_NO_SWAP;
    /* Half word swapping does not take place */
    config->halfWordSwap = KPWM_HALF_WORD_NO_SWAP;
}
