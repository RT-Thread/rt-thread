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


#ifndef __FSL_VREF_DRIVER_H__
#define __FSL_VREF_DRIVER_H__

#include "fsl_vref_hal.h"
#if FSL_FEATURE_SOC_VREF_COUNT

/*!
 * @addtogroup vref_driver
 * @{
 */

/*! @file */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Table of base addresses for VREF instances. */
extern VREF_Type * const g_vrefBase[];

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the VREF module.
 *
 * @param instance VREF instance.
 * @param userConfigPtr Pointer to the initialization structure. See the "vref_user_config_t".
 *
 * @return Execution status.
 */
vref_status_t VREF_DRV_Init(uint32_t instance, const vref_user_config_t *userConfigPtr);

/*!
 * @brief De-initializes the VREF module.
 *
 * @param instance VREF instance.
 * @return Execution status.
 */
vref_status_t VREF_DRV_Deinit(uint32_t instance);

#if FSL_FEATURE_VREF_HAS_CHOP_OSC
/*!
 * @brief Enables or disables the chop oscillator.
 *
 * When set, internal chopping operation is enabled and the internal analog offset is
 * be minimized.
 * This bit is set during factory trimming of the VREF voltage and should be written to 1
 * to achieve the performance stated in the data sheet.
 *
 * @param instance VREF instance.
 * @param enable   Enables or disables chop oscillator
 *        - true : Chop oscillator enable
 *        - false: Chop oscillator disable
 *
 * @return Execution status.
 */
static inline vref_status_t VREF_DRV_SetChopOsc(uint32_t instance, bool enable)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = g_vrefBase[instance];

    VREF_HAL_SetChopOscillatorCmd(base, enable);

    return kStatus_VREF_Success;
}
#endif

/*!
 * @brief Sets the TRIM bits value.
 *
 * These bits change the resulting VREF by approximately +/- 0.5 mV for each step.
 * For minimum and maximum voltage reference output values, see the Data Sheet for this chip.
 *
 * @param instance  VREF instance.
 * @param trimValue TRIM bits value.
 *
 * @return Execution status.
 */
vref_status_t VREF_DRV_SetTrimValue(uint32_t instance, uint8_t trimValue);

/*!
 * @brief Get TRIM bits value was set.
 *
 * @param instance VREF instance.
 *
 * @return Actual TRIM bits value.
 */
static inline uint8_t VREF_DRV_GetTrimValue(uint32_t instance)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = g_vrefBase[instance];

    return VREF_HAL_GetTrimVal(base);
}

/*!
 * @brief Enables or disables the regulator.
 *
 * This bit is used to enable the internal 1.75 V regulator to produce a constant internal voltage
 * supply to reduce the sensitivity to the external supply noise and variation.
 * To keep the regulator enabled in very low power modes, see
 * the Chip Configuration details for a description.
 * This bit is set during factory trimming of the VREF voltage and should be written to 1
 * to achieve the performance stated in the data sheet.
 *
 * @param instance VREF instance.
 * @param enable Enables or disables internal regulator
 *        - true : Internal regulator enable
 *        - false: Internal regulator disable
 *
 * @return Execution status.
 */
static inline vref_status_t VREF_DRV_SetRegulator(uint32_t instance, bool enable)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = g_vrefBase[instance];

    VREF_HAL_SetInternalRegulatorCmd(base, enable);

    return kStatus_VREF_Success;
}

#if FSL_FEATURE_VREF_HAS_COMPENSATION
/*!
 * @brief Enables or disables the second order curvature compensation.
 *
 * This bit is set during the factory trimming of the VREF voltage and should be written to 1
 * to achieve the performance stated in the data sheet.
 *
 * @param instance VREF instance.
 * @param enable Enables or disables second order curvature compensation.
 *        - true: Second order curvature compensation enabled
 *        - false: Second order curvature compensation disabled
 *
 * @return Execution status.
 */
static inline vref_status_t VREF_DRV_SetIcomp(uint32_t instance, bool enable)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = g_vrefBase[instance];

    VREF_HAL_SetSecondOrderCurvatureCompensationCmd(base, enable);

    return kStatus_VREF_Success;
}
#endif

/*!
 * @brief Sets the buffer mode.
 *
 * These bits select the buffer modes for the Voltage Reference module.
 * - Buffer mode = 0x00: The internal VREF bandgap is enabled to generate an accurate 1.2 V output
 * that can be trimmed with the TRM register TRIM[5:0] bit field.
 * The bandgap requires some time for startup and stabilization. SC[VREFST] can be monitored
 * to determine if the stabilization and startup is complete.
 * - Buffer mode = 0x01: The internal VREF bandgap is on. The high power buffer is enabled
 * to generate a buffered 1.2 V voltage to VREF_OUT.
 * - Buffer mode = 0x02: The internal VREF bandgap is on. The high power buffer is enabled
 * to generate a buffered 1.2 V voltage to VREF_OUT.

 * VREF_OUT generated by high and low buffer modes can also be used as a reference
 * to internal analog peripherals such as an ADC channel or analog comparator input.
 * If those modes is entered from the standby mode, there is a delay before
 * the buffer output is settled at the final value. A 100 nF capacitor is required to connect
 * between the VREF_OUT pin and VSSA.
 *
 * @param instance VREF instance.
 * @param bufferMode Buffer mode value.
 *
 * @return Execution status.
 */
static inline vref_status_t VREF_DRV_SetBufferMode(uint32_t instance, vref_buffer_mode_t bufferMode)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = g_vrefBase[instance];

    VREF_HAL_SetBufferMode(base, bufferMode);

    return kStatus_VREF_Success;
}

#if FSL_FEATURE_VREF_HAS_LOW_REFERENCE
/*!
 * @brief Selects the voltage reference between the internal and external 1.2 V reference.
 *
 * @param instance VREF instance.
 * @param ref Defines reference to be set.
 *        - kVrefReferenceInternal: Select internal reference
 *        - kVrefReferenceExternal: Select external reference
 *
 * @return Execution status.
 */

static inline vref_status_t VREF_DRV_SetVoltageReference(uint32_t instance, vref_voltage_reference_t ref)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = g_vrefBase[instance];

    VREF_HAL_SetVoltageReference(base, ref);

    return kStatus_VREF_Success;
}

/*!
 * @brief Enables or disables the VREFL (0.4 V) reference buffer.
 *
 * @param instance VREF instance.
 * @param enable Enables or disables VREFL (0.4 V) reference buffer
 *        - true : Enable VREFL (0.4 V) reference buffer
 *        - false: Disable VREFL (0.4 V) reference buffer
 *
 * @return Execution status.
 */
static inline vref_status_t VREF_DRV_SetLowReference(uint32_t instance, bool enable)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = g_vrefBase[instance];

    VREF_HAL_SetLowReference(base, enable);

    return kStatus_VREF_Success;
}

/*!
 * @brief Sets the trim value for low voltage reference.
 *
 * @param instance VREF instance.
 * @param trimValue Value of trim register to set output low reference voltage (max 0x07 (3-bit)).
 *
 * @return Execution status.
 */
vref_status_t VREF_DRV_SetLowReferenceTrimVal(uint32_t instance, uint8_t trimValue);

/*!
 * @brief Reads the value of trim meaning output voltage.
 *
 * @param instance VREF instance.
 * @return Three-bit value of trim setting.
 */
static inline uint8_t VREF_DRV_GetLowReferenceTrimVal(uint32_t instance)
{
    assert(instance < VREF_INSTANCE_COUNT);
    VREF_Type * base = g_vrefBase[instance];

    return VREF_HAL_GetLowReferenceTrimVal(base);
}
#endif /* FSL_FEATURE_VREF_HAS_LOW_REFERENCE */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif/* __FSL_VREF_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

