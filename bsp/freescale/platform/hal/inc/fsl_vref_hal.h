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
#ifndef __FSL_VREF_HAL_H__
#define __FSL_VREF_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_VREF_COUNT

/*! @addtogroup vref_hal*/
/*! @{*/

/*! @file*/

/*!*****************************************************************************
 * Definitions
 ******************************************************************************/
#if FSL_FEATURE_VREF_HAS_LOW_REFERENCE

/*!< Those macros below defined to support SoC family which have have VREFL (0.4V) reference */
#define VREF_BWR_TRM_CHOPEN     VREF_BWR_VREFH_TRM_CHOPEN
#define VREF_BWR_TRM_TRIM       VREF_BWR_VREFH_TRM_TRIM
#define VREF_BRD_TRM_TRIM       VREF_BRD_VREFH_TRM_TRIM
#define VREF_BWR_SC_VREFEN      VREF_BWR_VREFH_SC_VREFEN
#define VREF_BWR_SC_REGEN       VREF_BWR_VREFH_SC_REGEN
#define VREF_BRD_SC_VREFST      VREF_BRD_VREFH_SC_VREFST
#define VREF_BWR_SC_ICOMPEN     VREF_BWR_VREFH_SC_ICOMPEN
#define VREF_BWR_SC_MODE_LV     VREF_BWR_VREFH_SC_MODE_LV
#define VREF_BRD_SC_MODE_LV     VREF_BRD_VREFH_SC_MODE_LV

#endif

/*! @brief VREF status return codes */
typedef enum _vref_status
{
    kStatus_VREF_Success         = 0x0U, /*!< Success. */
    kStatus_VREF_InvalidArgument = 0x1U, /*!< Invalid argument existed. */
    kStatus_VREF_Failed          = 0x2U  /*!< Execution failed. */
} vref_status_t;

/*!
 * @brief VREF modes.
 */

#if FSL_FEATURE_VREF_MODE_LV_TYPE

typedef enum _vref_buffer_mode
{
    kVrefModeBandgapOnly     = 0x0U, /*!< Bandgap on only, for stabilization and startup */
    kVrefModeHighPowerBuffer = 0x1U, /*!< High power buffer mode enabled */
    kVrefModeLowPowerBuffer  = 0x2U  /*!< Low power buffer mode enabled */
} vref_buffer_mode_t;

#else

typedef enum _vref_buffer_mode
{
    kVrefModeBandgapOnly           = 0x0U, /*!< Bandgap on only. For stabilization and startup */
    kVrefModeTightRegulationBuffer = 0x2U  /*!< Tight regulation buffer enabled */
} vref_buffer_mode_t;

#endif /* FSL_FEATURE_VREF_MODE_LV_TYPE */

#if FSL_FEATURE_VREF_HAS_LOW_REFERENCE

typedef enum _vref_voltage_reference
{
    kVrefReferenceInternal = 0x0U, /*!< Internal voltage reference */
    kVrefReferenceExternal = 0x1U  /*!< External voltage reference */
} vref_voltage_reference_t;

#endif /* FSL_FEATURE_VREF_HAS_LOW_REFERENCE */

/*! @brief The description structure for the VREF module.
 *  @internal gui name="VREF configuration" id="vrefCfg"
 */
typedef struct VrefUserConfig
{
#if FSL_FEATURE_VREF_HAS_CHOP_OSC
    bool        chopOscEnable;      /*!< Chop oscillator enable @internal gui name="Chop oscillator" id="chopOscEnable" */
#endif
    uint8_t     trimValue;          /*!< Trim bits @internal gui name="Trim value" id="trimValue" range="0..63" */
    bool        regulatorEnable;    /*!< Enable regulator @internal gui name="Regulator" id="regulatorEnable" */
#if FSL_FEATURE_VREF_HAS_COMPENSATION
    bool        soccEnable;         /*!< Enable Second order curvature compensation @internal gui name="Second order curvature compensation" id="soccEnable" */
#endif
    vref_buffer_mode_t bufferMode;  /*!< Buffer mode selection @internal gui name="Buffer mode selection" id="bufferMode" */
} vref_user_config_t;

/*!*****************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name VREF related feature APIs*/

/*!
 * @brief Initialize VREF module to default state.
 *
 * @param base VREF module base number.
 */
void VREF_HAL_Init(VREF_Type * base);

/*!
 * @brief Configure VREF module to known state.
 *
 * @param base VREF module base number.
 * @param userConfigPtr Pointer to the initialization structure. See the "vref_user_config_t".
 */
void VREF_HAL_Configure(VREF_Type * base, const vref_user_config_t *userConfigPtr);

/*!
 * @brief Enable VREF module
 *
 * @param base VREF module base number.
 */
static inline void VREF_HAL_Enable(VREF_Type * base)
{
    VREF_BWR_SC_VREFEN(base, true);
}

/*!
 * @brief Disable VREF module
 *
 * @param base VREF module base number.
 */
static inline void VREF_HAL_Disable(VREF_Type * base)
{
    VREF_BWR_SC_VREFEN(base, false);
}

/*!
 * @brief Set VREF internal regulator to Enable.
 *
 * Cannot be enabled in very low-power modes!
 * @param base VREF module base number.
 * @param enable   Enables or disables internal regulator
 *        - true : Internal regulator enable
 *        - false: Internal regulator disable
 */
static inline void VREF_HAL_SetInternalRegulatorCmd(VREF_Type * base, bool enable)
{
    VREF_BWR_SC_REGEN(base, enable);
}

/*!
 * @brief Set trim value for voltage reference.
 *
 * @param base  VREF module base number.
 * @param trimValue Value of trim register to set output reference voltage (max 0x3F (6-bit)).
 */
static inline void VREF_HAL_SetTrimVal(VREF_Type * base, uint8_t trimValue)
{
    assert(trimValue <= 0x3F);
    VREF_BWR_TRM_TRIM(base, trimValue);
}

/*!
 * @brief Read value of trim meaning output voltage.
 *
 * @param base VREF module base number.
 *
 * @return Six-bit value of trim setting.
 */
static inline uint8_t VREF_HAL_GetTrimVal(VREF_Type * base)
{
    return VREF_BRD_TRM_TRIM(base);
}

/*!
 * @brief Wait to internal voltage stable.
 *
 * @param base VREF module base number.
 */

static inline void VREF_HAL_WaitVoltageStable(VREF_Type * base)
{
    while ((bool)VREF_BRD_SC_VREFST(base) != true) {}
}

/*!
 * @brief Set buffer mode
 *
 * @param base VREF module base number.
 * @param mode     Defines mode to be set.
 *        - kVrefModeBandgapOnly          : Set Bandgap on only
 *        - kVrefModeHighPowerBuffer      : Set High power buffer mode
 *        - kVrefModeLowPowerBuffer       : Set Low power buffer mode
 *        - kVrefModeTightRegulationBuffer: Set Tight regulation buffer mode
 */
static inline void VREF_HAL_SetBufferMode(VREF_Type * base, vref_buffer_mode_t mode)
{
#if FSL_FEATURE_VREF_MODE_LV_TYPE
    assert(mode <= kVrefModeLowPowerBuffer);
#else
    assert(mode <= kVrefModeTightRegulationBuffer);
#endif
    VREF_BWR_SC_MODE_LV(base, mode);
}

#if FSL_FEATURE_VREF_HAS_COMPENSATION
/*!
 * @brief Second order curvature compensation enable.
 *
 * @param base VREF module base number.
 * @param enable   Enables or disables second order curvature compensation.
 *        - true : Second order curvature compensation enabled
 *        - false: Second order curvature compensation disabled
 */
static inline void VREF_HAL_SetSecondOrderCurvatureCompensationCmd(VREF_Type * base, bool enable)
{
    VREF_BWR_SC_ICOMPEN(base, enable);
}
#endif /* FSL_FEATURE_VREF_HAS_COMPENSATION */

#if FSL_FEATURE_VREF_HAS_CHOP_OSC
/*!
 * @brief Chop oscillator enable.
 *
 * @param base VREF module base number.
 * @param enable   Enables or disables chop oscillator
 *        - true : Chop oscillator enable
 *        - false: Chop oscillator disable
 */
static inline void VREF_HAL_SetChopOscillatorCmd(VREF_Type * base, bool enable)
{
    VREF_BWR_TRM_CHOPEN(base, enable);
}
#endif /* FSL_FEATURE_VREF_HAS_CHOP_OSC */

#if FSL_FEATURE_VREF_HAS_LOW_REFERENCE
/*!
 * @brief Select voltage reference
 *
 * @param base VREF module base number.
 * @param ref Defines reference to be set.
 *      - kVrefReferenceInternal: Select internal reference
 *      - kVrefReferenceExternal: Select external reference
 */

static inline void VREF_HAL_SetVoltageReference(VREF_Type * base, vref_voltage_reference_t ref)
{
    VREF_BWR_VREFL_TRM_VREFL_SEL(base, ref);
}

/*!
 * @brief Set VREFL (0.4 V) reference buffer.
 *
 * @param base VREF module base number.
 * @param enable   Enables or disables VREFL (0.4 V) reference buffer
 *        - true : Enable VREFL (0.4 V) reference buffer
 *        - false: Disable VREFL (0.4 V) reference buffer
 */
static inline void VREF_HAL_SetLowReference(VREF_Type * base, bool enable)
{
    VREF_BWR_VREFL_TRM_VREFL_EN(base, enable);
}

/*!
 * @brief Set trim value for low voltage reference.
 *
 * @param base VREF module base number.
 * @param trimValue Value of trim register to set output low reference voltage (max 0x07 (3-bit) ).
 */
static inline void VREF_HAL_SetLowReferenceTrimVal(VREF_Type * base, uint8_t trimValue)
{
    assert(trimValue <= 0x07);
    VREF_BWR_VREFL_TRM_VREFL_TRIM(base, trimValue);
}

/*!
 * @brief Read value of trim meaning output voltage.
 *
 * @param base VREF module base number.
 *
 * @return Three-bit value of trim setting.
 */
static inline uint8_t VREF_HAL_GetLowReferenceTrimVal(VREF_Type * base)
{
    return VREF_BRD_VREFL_TRM_VREFL_TRIM(base);
}
#endif /* FSL_FEATURE_VREF_HAS_LOW_REFERENCE */

/*@}*/

 #if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_VREF_HAL_H__*/
/*******************************************************************************
* EOF
*******************************************************************************/

