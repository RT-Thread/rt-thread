/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
#ifndef __FSL_TPM_DRIVER_H__
#define __FSL_TPM_DRIVER_H__

#include "fsl_tpm_hal.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_TPM_COUNT

/*!
 * @addtogroup tpm_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Table of base addresses for TPM instances. */
extern TPM_Type * const g_tpmBase[TPM_INSTANCE_COUNT];

/*! @brief Table to save TPM IRQ numbers for TPM instances. */
extern const IRQn_Type g_tpmIrqId[TPM_INSTANCE_COUNT];

/*! @brief Internal driver state information grouped by names. User  needs to set the relevant ones.
 * @internal gui name="Basic configuration" id="tpmCfg"
 */
typedef struct TpmGeneralConfig {
    bool isDBGMode;          /*!< DBGMode behavioral, false to pause, true to continue run in DBG mode @internal gui name="Debug mode" id="DebugMode" */
    bool isGlobalTimeBase;   /*!< If Global time base enabled, true to enable, false to disable @internal gui name="Global time base" id="GlobalTimeBase" */
    bool isTriggerMode;      /*!< If Trigger mode enabled, true to enable, false to disable @internal gui name="Trigger mode" id="TriggerMode" */
    bool isStopCountOnOveflow; /*!< True to stop counter after overflow, false to continue running @internal gui name="Stop count on overflow" id="StopOnOvf" */
    bool isCountReloadOnTrig;  /*!< True to reload counter on trigger, false means counter is not reloaded @internal gui name="Reload counter on trigger" id="ReloadOnTrigger" */
    tpm_trigger_source_t triggerSource; /*!< Trigger source if trigger mode enabled @internal gui name="Trigger source" id="TriggerSource" */
}tpm_general_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the TPM driver.
 *
 * @param instance The TPM peripheral instance number.
 * @param info Pointer to the TPM user configuration structure, see #tpm_general_config_t.
 * @return kStatusTpmSuccess means success; Otherwise means failure.
 */
tpm_status_t TPM_DRV_Init(uint32_t instance, const tpm_general_config_t * info);

/*!
 * @brief Stops the channel PWM.
 *
 * @param instance The TPM peripheral instance number.
 * @param param PWM parameter to configure PWM options
 * @param channel The channel number.
 */
void TPM_DRV_PwmStop(uint32_t instance, tpm_pwm_param_t *param, uint8_t channel);

/*!
 * @brief Configures the duty cycle and frequency and starts outputting PWM on a specified channel.
 *
 * @param instance The TPM peripheral instance number.
 * @param param PWM parameter to configure PWM options, see #tpm_pwm_param_t.
 * @param channel The channel number.
 *
 * @return kStatusTpmSuccess means success; Otherwise means failure.
 */
tpm_status_t TPM_DRV_PwmStart(uint32_t instance, tpm_pwm_param_t *param, uint8_t channel);

/*!
 * @brief Enables or disables the timer overflow interrupt.
 *
 * @param instance The TPM peripheral instance number.
 * @param overflowEnable true: enable the timer overflow interrupt, false: disable
 */
void TPM_DRV_SetTimeOverflowIntCmd(uint32_t instance, bool overflowEnable);

/*!
 * @brief Enables or disables the channel interrupt.
 *
 * @param instance The TPM peripheral instance number.
 * @param channelNum The channel number.
 * @param enable true: enable the channel interrupt, false: disable
 */
void TPM_DRV_SetChnIntCmd(uint32_t instance, uint8_t channelNum, bool enable);

/*!
 * @brief Sets the TPM clock source.
 *
 * @param instance The TPM peripheral instance number.
 * @param clock The TPM peripheral clock selection, see #tpm_clock_mode_t.
 * @param clockPs The TPM peripheral clock prescale factor, see #tpm_clock_ps_t.
 */
void TPM_DRV_SetClock(uint32_t instance, tpm_clock_mode_t clock, tpm_clock_ps_t clockPs);

/*!
 * @brief Gets the TPM clock frequency.
 *
 * @param instance The TPM peripheral instance number.
 * @return The function returns the frequency of the TPM clock.
 */
uint32_t TPM_DRV_GetClock(uint32_t instance);

/*!
 * @brief Starts the TPM counter.
 *
 * This function provides access to the TPM counter. The counter can run in
 * up-counting and up-down counting modes.
 *
 * @param instance The TPM peripheral instance number.
 * @param countMode The TPM counter mode defined by tpm_counting_mode_t.
 * @param countFinalVal The final value that is stored in the MOD register.
 * @param enableOverflowInt true: enable timer overflow interrupt; false: disable
 */
void TPM_DRV_CounterStart(uint32_t instance, tpm_counting_mode_t countMode, uint32_t countFinalVal,
                                 bool enableOverflowInt);

/*!
 * @brief Stops the TPM counter.
 *
 * @param instance The TPM peripheral instance number.
 */
void TPM_DRV_CounterStop(uint32_t instance);

/*!
 * @brief Reads back the current value of the TPM counter.
 *
 * @param instance The TPM peripheral instance number.
 * @return The current value of the TPM counter.
 */
uint32_t TPM_DRV_CounterRead(uint32_t instance);

/*!
 * @brief TPM input capture mode setup.
 *
 * @param instance The TPM peripheral instance number.
 * @param channel The channel number.
 * @param mode The TPM input mode defined by #tpm_input_capture_mode_t.
 * @param countFinalVal The final value that is stored in the MOD register.
 * @param intEnable true: enable channel interrupt; false: disable
 */
void TPM_DRV_InputCaptureEnable(uint32_t instance, uint8_t channel, tpm_input_capture_mode_t mode,
                                         uint32_t countFinalVal, bool intEnable);

/*!
 * @brief Reads back the current value of the TPM channel value.
 *
 * @param instance The TPM peripheral instance number.
 * @param channel The channel number.
 * @return The current value of the TPM channel value.
 */
uint32_t TPM_DRV_GetChnVal(uint32_t instance, uint8_t channel);

/*!
 * @brief TPM output compare mode setup.
 *
 * @param instance The TPM peripheral instance number.
 * @param channel The channel number.
 * @param mode The TPM output mode defined by #tpm_output_compare_mode_t.
 * @param countFinalVal The final value that is stored in the MOD register.
 * @param matchVal The channel compare value stored in the CnV register
 * @param intEnable true: enable channel interrupt; false: disable
 */
void TPM_DRV_OutputCompareEnable(uint32_t instance, uint8_t channel, tpm_output_compare_mode_t mode,
                                            uint32_t countFinalVal, uint32_t matchVal, bool intEnable);

/*!
 * @brief Shuts down the TPM driver.
 *
 * @param instance The TPM peripheral instance number.
 */
void TPM_DRV_Deinit(uint32_t instance);

/*!
 * @brief Action to take when an TPM interrupt is triggered.
 *
 * The timer overflow flag is checked and cleared if set.
 *
 * @param instance   Instance number of the TPM module.
 */
void TPM_DRV_IRQHandler(uint32_t instance);

/*Other API functions are for input capture, output compare, dual edge capture, and quadrature. */
#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_TPM_COUNT */

#endif /* __FSL_TPM_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

