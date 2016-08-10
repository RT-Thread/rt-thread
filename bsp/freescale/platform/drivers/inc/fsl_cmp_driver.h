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

#ifndef __FSL_CMP_DRIVER_H__
#define __FSL_CMP_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_cmp_hal.h"
#if FSL_FEATURE_SOC_CMP_COUNT

/*!
 * @addtogroup cmp_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Defines type of flags for the CMP event.
 */
typedef enum _cmp_flag
{
    kCmpFlagOfCoutRising  = 0U, /*!< Identifier to indicate if the COUT change from logic zero to one. */
    kCmpFlagOfCoutFalling = 1U  /*!< Identifier to indicate if the COUT change from logic one to zero. */
} cmp_flag_t;

/*!
 * @brief Internal driver state information.
 *
 * The contents of this structure are internal to the driver and should not be
 *  modified by users. Also, contents of the structure are subject to change in
 *  future releases.
 */
typedef struct CmpState
{
    bool isInUsed; /* If the CMP instance is in use. All the CMP instances share
        * the same clock gate and are aligned to use clock.*/
} cmp_state_t;

/*! @brief Table of base addresses for CMP instances. */
extern CMP_Type * const g_cmpBase[];

/*! @brief Table to save CMP IRQ enumeration numbers defined in CMSIS header file. */
extern const IRQn_Type g_cmpIrqId[CMP_INSTANCE_COUNT];

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * APIs
 ******************************************************************************/
/*!
 * @brief Populates the initial user configuration with default settings. 
 *
 * This function populates the initial user configuration with default settings. 
 * The default settings enable the CMP module to operate as  a comparator.
 * The settings are :\n
 *     \li.hystersisMode = kCmpHystersisOfLevel0
 *     \li.pinoutEnable = true
 *     \li.pinoutUnfilteredEnable = true
 *     \li.invertEnable = false
 *     \li.highSpeedEnable = false
 *     \li.dmaEnable = false
 *     \li.risingIntEnable = false
 *     \li.fallingIntEnable = false
 *     \li.triggerEnable = false
 * However, it is still recommended to fill some fields of structure such as
 * channel mux according to the application requirements. Note that this function does not set the
 * configuration to hardware.
 *
 * @param userConfigPtr Pointer to structure of configuration. See "cmp_user_config_t".
 * @param plusInput Plus Input mux selection. See  "cmp_chn_mux_mode_t".
 * @param minusInput Minus Input mux selection. See  "cmp_chn_mux_mode_t".
 * @return Execution status.
 */
cmp_status_t CMP_DRV_StructInitUserConfigDefault(cmp_comparator_config_t *userConfigPtr,
    cmp_chn_mux_mode_t plusInput, cmp_chn_mux_mode_t minusInput);

/*!
 * @brief Initializes the CMP module. 
 *
 * This function initializes the CMP module, enables the clock, and
 * sets the interrupt switcher. The CMP module is
 * configured as a basic comparator.
 *
 * @param instance CMP instance ID.
 * @param userStatePtr Pointer to structure of context. See  "cmp_state_t".
 * @param userConfigPtr Pointer to structure of configuration. See  "cmp_user_config_t".
 * @return Execution status.
 */
cmp_status_t CMP_DRV_Init(uint32_t instance, cmp_state_t *userStatePtr,
    const cmp_comparator_config_t *userConfigPtr);

/*!
 * @brief De-initializes the CMP module. 
 *
 * This function de-initializes the CMP module. It  shuts down the CMP
 * clock and disables the interrupt. This API should be called when CMP is no
 * longer used in the application. It also reduces power consumption.
 *
 * @param instance CMP instance ID.
 * @return Execution status.
 */
cmp_status_t CMP_DRV_Deinit(uint32_t instance);

/*!
 * @brief Starts the CMP module. 
 *
 * This function starts the CMP module. The configuration does not take
 * effect until the module is started.
 *
 * @param instance CMP instance ID.
 */
void CMP_DRV_Start(uint32_t instance);

/*!
 * @brief Stops the CMP module. 
 *
 * This function stops the CMP module. Note that this function does not shut down
 * the module, but only pauses the features.
 *
 * @param instance CMP instance ID.
 */
void CMP_DRV_Stop(uint32_t instance);

/*!
 * @brief Enables the internal DAC in the CMP module. 
 *
 * This function enables the internal DAC in the CMP module. It takes
 * effect only when the internal DAC has been chosen as an input
 * channel for the comparator. Then, the DAC channel can be programmed to provide
 * a reference voltage level.
 *
 * @param instance CMP instance ID.
 * @param dacConfigPtr Pointer to structure of configuration. See "cmp_dac_config_t".
 * @return Execution status.
 */
cmp_status_t CMP_DRV_ConfigDacChn(uint32_t instance, const cmp_dac_config_t *dacConfigPtr);

/*!
 * @brief Configures the Sample\Filter feature in the CMP module. 
 *
 * This function configures the CMP working in Sample\Filter modes. These
 * modes are advanced features in addition to the basic comparator such as 
 * Window Mode, Filter Mode, etc. See  
 * "cmp_sample_filter_config_t"for detailed description.
 *
 * @param instance CMP instance ID.
 * @param configPtr Pointer to a structure of configurations.
 *        See "cmp_sample_filter_config_t".
 * @return Execution status.
 */
cmp_status_t CMP_DRV_ConfigSampleFilter(uint32_t instance, const cmp_sample_filter_config_t *configPtr);

/*!
 * @brief Gets the output of the CMP module. 
 *
 * This function gets the output of the CMP module.
 * The output source depends on the configuration when initializing the comparator.
 * When the cmp_user_config_t.pinoutUnfilteredEnable is false, the output is
 * processed by the filter. Otherwise, the output is that the signal did not pass
 * the filter.
 *
 * @param instance CMP instance ID.
 * @return Output logic's assertion. When not inverted, plus side > minus side, it is true.
 */
bool CMP_DRV_GetOutputLogic(uint32_t instance);

/*!
 * @brief Gets the state of the CMP module. 
 *
 * This function  gets the state of the CMP module. It returns if the indicated
 * event has been detected.
 *
 * @param instance CMP instance ID.
 * @param flag Represent events or states. See "cmp_flag_t".
 * @return Assertion if indicated event occurs.
 */
bool CMP_DRV_GetFlag(uint32_t instance, cmp_flag_t flag);

/*!
 * @brief Clears the event record of the CMP module. 
 *
 * This function clears the event record of the CMP module. 
 *
 * @param instance CMP instance ID.
 * @param flag Represent events or states. See "cmp_flag_t".
 */
void CMP_DRV_ClearFlag(uint32_t instance, cmp_flag_t flag);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif
#endif /* __FSL_CMP_DRIVER_H__ */
/******************************************************************************
 * EOF
 *****************************************************************************/
 
