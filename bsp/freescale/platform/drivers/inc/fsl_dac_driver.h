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

#ifndef __FSL_DAC_DRIVER_H__
#define __FSL_DAC_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_dac_hal.h"

#if FSL_FEATURE_SOC_DAC_COUNT

/*!
 * @addtogroup dac_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Defines the type of event flags.
 */
typedef enum _dac_flag_t
{
#if FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    kDacBuffIndexWatermarkFlag = 0U, /*!< Event for the buffer index reaching the watermark. */
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
    kDacBuffIndexStartFlag = 1U, /*!< Event for the buffer index reaching  start (0). */
    kDacBuffIndexUpperFlag = 2U /*!< Event for the buffer index reaching the upper section. */
} dac_flag_t;

/*! @brief Table of base addresses for DAC instances. */
extern DAC_Type * const g_dacBase[];

/*! @brief Table to save DAC IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_dacIrqId[DAC_INSTANCE_COUNT];

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Populates the initial user configuration for the DAC module without interrupt and buffer features. 
 *
 * This function  populates the initial user configuration 
 * without interrupt and buffer features. Calling the initialization
 * function with the populated parameter configures the DAC module to operate as
 * a simple converter. The settings are:\n
 *
 * \li.dacRefVoltSrc = kDacRefVoltSrcOfVref2; // Vdda
 * \li.lowPowerEnable = false;
 *
 * @param userConfigPtr Pointer to the user configuration structure. See the "dac_user_config_t".
 * @return Execution status.
 */
dac_status_t DAC_DRV_StructInitUserConfigNormal(dac_converter_config_t *userConfigPtr);

/*!
 * @brief Initializes the converter. 
 *
 * This function initializes the converter. 
 *
 * @param instance DAC instance ID.
 * @param userConfigPtr Pointer to the initialization structure. See the "dac_user_config_t".
 * @return Execution status.
 */
dac_status_t DAC_DRV_Init(uint32_t instance, const dac_converter_config_t *userConfigPtr);

/*!
 * @brief De-initializes the DAC module converter.
 *
 * This function de-initializes the converter. It disables the
 * DAC module and shuts down the clock to reduce the power consumption. 
 *
 * @param instance DAC instance ID.
 * @return Execution status.
 */
dac_status_t DAC_DRV_Deinit(uint32_t instance);

/*!
 * @brief Drives the converter to output the DAC value.
 *
 * This function drives the converter to output the DAC value. It forces
 * the buffer index to be the first one and load the setting value to this item. 
 * Then, the converter outputs the voltage indicated by the indicated value
 * immediately. 
 *
 * @param instance DAC instance ID.
 * @param value Setting value for DAC.
 */
void DAC_DRV_Output(uint32_t instance, uint16_t value);

/*!
 * @brief Configures the internal buffer.
 *
 * This function configures the feature of the internal buffer for the DAC module.
 * By default, the buffer feature  is disabled. Calling this API enables
 * the buffer and configures it.
 *
 * @param instance DAC instance ID.
 * @param configPtr Pointer to the configuration structure. See the "dac_buff_config_t".
 * @return Execution status.
 */
dac_status_t DAC_DRV_ConfigBuffer(uint32_t instance, const dac_buffer_config_t *configPtr);

/*!
 * @brief Sets values into the DAC internal buffer.
 *
 * This function  sets values into the DAC internal buffer. Note that the buffer
 * size is defined by the  "FSL_FEATURE_DAC_BUFFER_SIZE" macro and the available
 * value is 12 bits.
 *
 * @param instance DAC instance ID.
 * @param start Start index of setting values.
 * @param offset Length of setting values' array.
 * @param arr Setting values' array.
 * @return Execution status.
 */
dac_status_t DAC_DRV_SetBuffValue(uint32_t instance, uint8_t start, uint8_t offset, uint16_t arr[]);

/*!
 * @brief Triggers the buffer by software and returns the current value.
 *
 * This function triggers the buffer by software and returns the current
 * value. After it is triggered, the buffer index  updates according to work mode.
 * Then, the value kept inside the pointed item  is immediately output.
 *
 * @param instance DAC instance ID.
 */
void DAC_DRV_SoftTriggerBuffCmd(uint32_t instance);

/*!
 * @brief Clears the flag for an indicated event causing an interrupt.
 *
 * This function clears the flag for an indicated event causing an interrupt.
 *
 * @param instance DAC instance ID.
 * @param flag Indicated flag. See "dac_flag_t".
 */
void DAC_DRV_ClearBuffFlag(uint32_t instance, dac_flag_t flag);

/*!
 * @brief Gets the flag for an indicated event causing an interrupt.
 *
 * This function gets the flag for an indicated event causing an interrupt.
 * If the event occurs, the return value is asserted.
 *
 * @param instance DAC instance ID.
 * @param flag Indicated flag. See "dac_flag_t".
 * @return Assertion of indicated event.
 */
bool DAC_DRV_GetBuffFlag(uint32_t instance, dac_flag_t flag);

/*!
 * @brief Sets the current read pointer in DAC buffer.
 *
 * This function sets the current read pointer in DAC buffer.
 *
 * @param instance DAC instance ID.
 * @param idx Index for read pointer in buffer.
 */
void DAC_DRV_SetBuffCurIdx(uint32_t instance, uint8_t idx);

/*!
 * @brief Gets the current read pointer in the DAC buffer.
 *
 * This function gets the current read pointer in DAC buffer.
 *
 * @param instance DAC instance ID.
 * @return Index for current read pointer in buffer.
 */
uint8_t DAC_DRV_GetBuffCurIdx(uint32_t instance);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* __FSL_DAC_DRIVER_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/

#endif
