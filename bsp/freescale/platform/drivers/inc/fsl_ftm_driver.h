/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
#ifndef __FSL_FTM_DRIVER_H__
#define __FSL_FTM_DRIVER_H__

#include "fsl_ftm_hal.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_FTM_COUNT

/*!
 * @addtogroup ftm_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Table of base addresses for FTM instances. */
extern FTM_Type * const g_ftmBase[FTM_INSTANCE_COUNT];

/*! @brief Table to save FTM IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_ftmIrqId[FTM_INSTANCE_COUNT];

/*! @brief Configuration structure that the user needs to set
 */
typedef struct FtmUserConfig {
    uint8_t tofFrequency; /*!< Select ratio between number of overflows to times TOF is set @internal gui name="Overflow frequency" id="OvFrequency" */
    ftm_bdm_mode_t BDMMode; /*!< Select FTM behavior in BDM mode @internal gui name="BDM mode" id="BdmMode" */
    bool isWriteProtection; /*!< true: enable write protection, false: write protection is disabled @internal gui name="Write protection" id="WriteProtection" */
    uint32_t syncMethod; /*!< Register synch options available in the ftm_sync_method_t enumeration @internal gui name="Triggers" id="Triggers" */
} ftm_user_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the FTM driver.
 *
 * @param instance The FTM peripheral instance number.
 * @param info The FTM user configuration structure, see #ftm_user_config_t.
 * @return kStatusFtmSuccess means success. Otherwise means failure.
 */
ftm_status_t FTM_DRV_Init(uint32_t instance, const ftm_user_config_t *info);

/*!
 * @brief Shuts down the FTM driver.
 *
 * @param instance The FTM peripheral instance number.
 */
void FTM_DRV_Deinit(uint32_t instance);

/*!
 * @brief Stops the channel PWM.
 *
 * @param instance The FTM peripheral instance number.
 * @param param FTM driver PWM parameter to configure PWM options
 * @param channel The channel number. In combined mode, the code  finds the channel
 *                pair associated with the channel number passed in.
 */
void FTM_DRV_PwmStop(uint32_t instance, ftm_pwm_param_t *param, uint8_t channel);

/*!
 * @brief Configures the duty cycle and frequency and starts outputting the PWM on a specified channel .
 *
 * @param instance The FTM peripheral instance number.
 * @param param FTM driver PWM parameter to configure PWM options
 * @param channel The channel number. In combined mode, the code  finds the channel
 *                pair associated with the channel number passed in.
 * @return kStatusFtmSuccess if the PWM setup was successful,
 *         kStatusFtmError on failure as the PWM counter is disabled
 */
ftm_status_t FTM_DRV_PwmStart(uint32_t instance, ftm_pwm_param_t *param, uint8_t channel);

/*!
 * @brief Configures the parameters and activates the quadrature decode mode.
 *
 * @param instance     Instance number of the FTM module.
 * @param phaseAParams Phase A configuration parameters
 * @param phaseBParams Phase B configuration parameters
 * @param quadMode     Selects encoding mode used in quadrature decoder mode
 */
void FTM_DRV_QuadDecodeStart(uint32_t instance, ftm_phase_params_t *phaseAParams,
                                      ftm_phase_params_t *phaseBParams, ftm_quad_decode_mode_t quadMode);

/*!
 * @brief Deactivates the quadrature decode mode.
 *
 * @param instance  Instance number of the FTM module.
 */
void FTM_DRV_QuadDecodeStop(uint32_t instance);

/*!
 * @brief Starts the FTM counter.
 *
 * This function provides access to the FTM counter. The counter can be run in
 * up-counting and up-down counting modes. To run the counter in free running mode,
 * choose the up-counting option and provide 0x0 for the countStartVal and 0xFFFF for
 * countFinalVal.
 *
 * @param instance The FTM peripheral instance number.
 * @param countMode The FTM counter mode defined by ftm_counting_mode_t.
 * @param countStartVal The starting value that is stored in the CNTIN register.
 * @param countFinalVal The final value that is stored in the MOD register.
 * @param enableOverflowInt true: enable timer overflow interrupt; false: disable
 */
void FTM_DRV_CounterStart(uint32_t instance, ftm_counting_mode_t countMode, uint32_t countStartVal,
                                 uint32_t countFinalVal, bool enableOverflowInt);

/*!
 * @brief Stops the FTM counter.
 *
 * @param instance The FTM peripheral instance number.
 */
void FTM_DRV_CounterStop(uint32_t instance);

/*!
 * @brief Reads back the current value of the FTM counter.
 *
 * @param instance The FTM peripheral instance number.
 * @return The counter value.
 */
uint32_t FTM_DRV_CounterRead(uint32_t instance);

/*!
 * @brief Sets the FTM clock source.
 *
 * This function saves the user's clock source selection in the driver
 * to set the clock source  and use features provided
 * by the driver-like counter, PWM generation, and so on. This function also sets the clock divider.
 *
 * @param instance The FTM peripheral instance number.
 * @param clock The clock source to use, cannot pick None.
 * @param clockPs The clock divider value.
 */
void FTM_DRV_SetClock(uint8_t instance, ftm_clock_source_t clock, ftm_clock_ps_t clockPs);

/*!
 * @brief Retrieves the frequency of the clock source feeding the FTM counter.
 *
 * This function returns zero if no clock source is selected and the FTM counter is disabled.
 *
 * @param instance The FTM peripheral instance number.
 * @return The frequency of the clock source running the FTM counter, returns 0 if counter is disabled
 */
uint32_t FTM_DRV_GetClock(uint8_t instance);

/*!
 * @brief Enables or disables the timer overflow interrupt.
 *
 * @param instance The FTM peripheral instance number.
 * @param overflowEnable true: enable the timer overflow interrupt, false: disable
 */
void FTM_DRV_SetTimeOverflowIntCmd(uint32_t instance, bool overflowEnable);

/*!
 * @brief Enables or disables the fault interrupt.
 *
 * @param instance The FTM peripheral instance number.
 * @param faultEnable true: enable the fault interrupt, false: disable
 */
void FTM_DRV_SetFaultIntCmd(uint32_t instance, bool faultEnable);

/*!
 * @brief Enables capturing an input signal on the channel using the function parameters.
 *
 * When the edge specified in the captureMode argument occurs on the channel, the FTM counter is captured into
 * the CnV register. The user has to read the CnV register separately to get this value. The filter
 * function is disabled if the filterVal argument passed in is 0. The filter function is available only for
 *  0, 1, 2, 3 channels.
 *
 * @param instance    The FTM peripheral instance number
 * @param captureMode Specifies which edge to capture
 * @param channel     The channel number
 * @param filterVal   Filter value to be used, specify 0 to disable filter. Available only for channels 0-3
 */
void FTM_DRV_SetupChnInputCapture(uint32_t instance, ftm_input_capture_edge_mode_t captureMode,
                                            uint8_t channel, uint8_t filterVal);

/*!
 * @brief Configures the FTM to generate timed pulses.
 *
 * When the FTM counter matches the value of compareVal argument (this is written into CnV reg), the channel
 * output is changed based on what is specified in the compareMode argument.
 *
 * @param instance    The FTM peripheral instance number.
 * @param compareMode Action to take on the channel output when the compare condition is met
 * @param channel     The channel number
 * @param compareVal  Value to be programmed in the CnV register.
 */
void FTM_DRV_SetupChnOutputCompare(uint32_t instance, ftm_output_compare_edge_mode_t compareMode,
                                               uint8_t channel, uint32_t compareVal);

/*!
 * @brief Configures the dual edge capture mode of the FTM.
 *
 * This function sets up the dual edge capture mode on a channel pair. The capture edge for the channel
 * pair and the capture mode (one-shot or continuous) is specified in the parameter argument. The filter function
 * is disabled if the filterVal argument passed is zero. The filter function is available only on
 * channels 0 and 2. The user has to read the channel CnV registers separately to get the capture values.
 *
 * @param instance    The FTM peripheral instance number.
 * @param param       Controls the dual edge capture function
 * @param channel     The channel number, the code finds the channel pair associated with the channel
 *                    number passed in.
 * @param filterVal   Filter value to be used, specify 0 to disable filter. Available only for channels 0, 2
 */
void FTM_DRV_SetupChnDualEdgeCapture(uint32_t instance, ftm_dual_edge_capture_param_t *param,
                                                 uint8_t channel, uint8_t filterVal);

/*!
 * @brief Action to take when an FTM interrupt is triggered.
 *
 * The timer overflow flag is checked and cleared if set.
 *
 * @param instance   Instance number of the FTM module.
 */
void FTM_DRV_IRQHandler(uint32_t instance);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_FTM_COUNT */

#endif /* __FSL_FTM_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

