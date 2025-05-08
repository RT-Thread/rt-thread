/*
 * Copyright 2021-2022, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_OPAMP_H_
#define FSL_OPAMP_H_

#include "fsl_common.h"

/*!
 * @addtogroup opamp
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief OPAMP driver version. */
#define FSL_OPAMP_DRIVER_VERSION (MAKE_VERSION(2, 2, 0))
/*! @} */

/*!
 * @brief The enumeration of OPAMP mode, including low noise mode and high speed mode.
 */
typedef enum _opamp_mode
{
    kOPAMP_LowNoiseMode = 0U, /*!< Set opamp mode as low noise mode. */
    kOPAMP_HighSpeedMode,     /*!< Set opamp mode as high speed mode. */
} opamp_mode_t;

/*!
 * @brief The enumeration of bias current trim option.
 */
typedef enum _opamp_bias_current_trim_option
{
    kOPAMP_TrimOptionDefault = 0U,           /*!< Default Bias current trim option. */
    kOPAMP_TrimOptionIncreaseCurrent,        /*!< Trim option selected as increase current. */
    kOPAMP_TrimOptionDecreaseCurrent,        /*!< Trim option selected as decrease current. */
    kOPAMP_TrimOptionFurtherDecreaseCurrent, /*!< Trim option selected as further decrease current. */
} opamp_bias_current_trim_option_t;

/*!
 * @brief The enumeration of internal reference voltage.
 */
typedef enum _opamp_internal_ref_voltage
{
    kOPAMP_IntRefVoltVddaDiv2 = 0U, /*!< Internal reference voltage selected as Vdda/2. */
    kOPAMP_IntRefVoltVdda3V,        /*!< Internal reference voltage selected as Vdda_3V. */
    kOPAMP_IntRefVoltVssa3V,        /*!< Internal reference voltage selected as Vssa_3V. */
    kOPAMP_IntRefVoltNotAllowed,    /*!< Internal reference voltage not allowed. */
} opamp_internal_ref_voltage_t;

/*!
 * @brief The enumeration of positive reference voltage（please refer to manual use）.
 */
typedef enum _opamp_positive_ref_voltage
{
    kOPAMP_PosRefVoltVrefh3 = 0U, /*!< Positive part reference voltage select Vrefh3, connected from DAC output. */
    kOPAMP_PosRefVoltVrefh0 = 1U, /*!< Positive part reference voltage select Vrefh0, connected from VDDA supply. */
    kOPAMP_PosRefVoltVrefh1 = 2U, /*!< Positive part reference voltage select Vrefh1,
                                        connected from Voltage reference output. */
    kOPAMP_PosRefVoltVrefh4 = 3U, /*!< Positive part reference voltage select 520mv or reserved.*/
} opamp_positive_ref_voltage_t;

/*!
 * @brief The enumeration of positive programmable gain (please refer to manual use).
 */
typedef enum _opamp_positive_gain
{
    kOPAMP_PosGainReserved     = 0U, /*!< Positive Gain reserved. */
    kOPAMP_PosGainNonInvert1X  = 1U, /*!< Positive non-inverting gain application 1X. */
    kOPAMP_PosGainNonInvert2X  = 2U, /*!< Positive non-inverting gain application 2X. */
    kOPAMP_PosGainNonInvert4X  = 3U, /*!< Positive non-inverting gain application 4X. */
    kOPAMP_PosGainNonInvert8X  = 4U, /*!< Positive non-inverting gain application 8X. */
    kOPAMP_PosGainNonInvert16X = 5U, /*!< Positive non-inverting gain application 16X. */
    kOPAMP_PosGainNonInvert33X = 6U, /*!< Positive non-inverting gain application 33X. */
    kOPAMP_PosGainNonInvert64X = 7U, /*!< Positive non-inverting gain application 64X. */
#if defined(FSL_FEATURE_OPAMP_HAS_SUPPORT_REFERENCE_BUFFER) && FSL_FEATURE_OPAMP_HAS_SUPPORT_REFERENCE_BUFFER
    /* The following gain selections are for basic OPAMP only, and signal inputs are
    supported on the non-inverting and inverting terminals.*/
    kOPAMP_PosGainNonInvertDisableBuffer2X  = 8U,  /*!< Positive non-inverting gain application 2X. */
    kOPAMP_PosGainNonInvertDisableBuffer3X  = 9U,  /*!< Positive non-inverting gain application 3X. */
    kOPAMP_PosGainNonInvertDisableBuffer5X  = 10U, /*!< Positive non-inverting gain application 5X. */
    kOPAMP_PosGainNonInvertDisableBuffer9X  = 11U, /*!< Positive non-inverting gain application 9X. */
    kOPAMP_PosGainNonInvertDisableBuffer17X = 12U, /*!< Positive non-inverting gain application 17X. */
    kOPAMP_PosGainNonInvertDisableBuffer34X = 13U, /*!< Positive non-inverting gain application 34X. */
    kOPAMP_PosGainNonInvertDisableBuffer65X = 14U, /*!< Positive non-inverting gain application 65X. */
#endif                                             /* FSL_FEATURE_OPAMP_HAS_SUPPORT_REFERENCE_BUFFER */
} opamp_positive_gain_t;

/*!
 * @brief The enumeration of negative programmable gain.
 */
typedef enum _opamp_negative_gain
{
    kOPAMP_NegGainBufferMode = 0U, /*!< Negative Buffer Mode. */
    kOPAMP_NegGainInvert1X,        /*!< Negative inverting gain application -1X. */
    kOPAMP_NegGainInvert2X,        /*!< Negative inverting gain application -2X. */
    kOPAMP_NegGainInvert4X,        /*!< Negative inverting gain application -4X. */
    kOPAMP_NegGainInvert8X,        /*!< Negative inverting gain application -8X. */
    kOPAMP_NegGainInvert16X,       /*!< Negative inverting gain application -16X. */
    kOPAMP_NegGainInvert33X,       /*!< Negative inverting gain application -33X. */
    kOPAMP_NegGainInvert64X,       /*!< Negative inverting gain application -64X. */
} opamp_negative_gain_t;

#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_INPSEL) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_INPSEL
/*!
 * @brief The enumeration of positive input channel selection.
 */
typedef enum _opamp_positive_input_channel_selection
{
    kOPAMP_PosInputChannel0 = 0U, /*!< When OPAMP not in trigger mode, select positive input 0 (INP0).*/
    kOPAMP_PosInputChannel1 = 1U, /*!< When OPAMP not in trigger mode, select positive input 1 (INP1).*/
} opamp_positive_input_channel_selection_t;
#endif
/*!
 * @brief OPAMP configuraion, including mode, internal reference voltage, positive gain, negative gain and so on.
 */
typedef struct _opamp_config
{
    bool enable;       /*!< Enable/disable OPAMP.  */
    opamp_mode_t mode; /*!< Opamp mode, available values are @ref kOPAMP_LowNoiseMode and @ref kOPAMP_HighSpeedMode. */
    opamp_bias_current_trim_option_t trimOption; /*!< Bias current trim option, please refer to
                                                      @ref opamp_bias_current_trim_option_t.  */
    opamp_internal_ref_voltage_t intRefVoltage;  /*!< Internal reference voltage, please refer to
                                                     @ref opamp_internal_ref_voltage_t. */
    opamp_positive_ref_voltage_t posRefVoltage;  /*!< Positive part reference voltage, please refer
                                                     to @ref opamp_positive_ref_voltage_t. */
    /* Positive part configuration. */
    opamp_positive_gain_t posGain; /*!< Positive part programmable gain, please refer
                                       to @ref opamp_positive_gain_t. */
    /* Negative part configuration. */
    opamp_negative_gain_t negGain; /*!< Negative part programmable gain, please refer
                                       to @ref opamp_negative_gain_t. */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_OUTSW) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_OUTSW
    bool enableOutputSwitch;       /*!< OPAMP out to negative gain resistor ladder switch.*/
#endif                             /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_OUTSW */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW1) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW1
    bool enablePosADCSw1;          /*!< Positive part reference voltage switch to ADC channel or not.
                                      - \b true Positive part reference voltage switch to ADC channel.
                                      - \b false Positive part reference voltage do not switch to ADC channel. */
#else
    bool enablePosADCSw; /*!< Positive part reference voltage switch to ADC channel or not.
                             - \b true Positive part reference voltage switch to ADC channel.
                             - \b false Positive part reference voltage do not switch to ADC channel. */
#endif                             /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW1 */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW2) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW2
    bool enablePosADCSw2;          /*!< Positive part reference voltage switch to ADC channel or not.
                                      - \b true Positive part reference voltage switch to ADC channel.
                                      - \b false Positive part reference voltage do not switch to ADC channel. */
#endif                             /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_ADCSW2 */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_BUFEN) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_BUFEN
    bool enableRefBuffer;          /*!< Reference buffer enable.*/
#endif                             /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_BUFEN */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_INPSEL) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_INPSEL
    opamp_positive_input_channel_selection_t PosInputChannelSelection; /*!< Positive Input Channel Selection*/
#endif                                                                 /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_INPSEL */
#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD
    bool enableTriggerMode;                                            /*!< Trigger Mode Enable.*/
#endif                                                                 /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD */
} opamp_config_t;

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initialize OPAMP instance.
 *
 * @param base OPAMP peripheral base address.
 * @param config The pointer to @ref opamp_config_t.
 */
void OPAMP_Init(OPAMP_Type *base, const opamp_config_t *config);

/*!
 * @brief De-initialize OPAMP instance.
 *
 * @param base OPAMP peripheral base address.
 */
void OPAMP_Deinit(OPAMP_Type *base);

/*!
 * @brief Get default configuration of OPAMP.
 *
 * @code
 *     config->enable        = false;
 *     config->mode          = kOPAMP_LowNoiseMode;
 *     config->trimOption    = kOPAMP_TrimOptionDefault;
 *     config->intRefVoltage = kOPAMP_IntRefVoltVddaDiv2;
 *     config->enablePosADCSw = false;
 *     config->posRefVoltage = kOPAMP_PosRefVoltVrefh3;
 *     config->posGain       = kOPAMP_PosGainReserved;
 *     config->negGain       = kOPAMP_NegGainBufferMode;
 * @endcode
 *
 * @param config The pointer to @ref opamp_config_t.
 */
void OPAMP_GetDefaultConfig(opamp_config_t *config);

/*! @} */

/*!
 * @name Positive port gain and negative gain configuration.
 * @{
 */
/*!
 * @brief Configure OPAMP positive port gain.
 *
 * @param base OPAMP peripheral base address.
 * @param option OPAMP positive port gain.
 */
static inline void OPAMP_DoPosGainConfig(OPAMP_Type *base, opamp_positive_gain_t option)
{
    base->OPAMP_CTR = (((base->OPAMP_CTR) & (~OPAMP_OPAMP_CTR_PGAIN_MASK)) | OPAMP_OPAMP_CTR_PGAIN(option));
}

/*!
 * @brief Configure OPAMP negative port gain.
 *
 * @param base OPAMP peripheral base address.
 * @param option OPAMP negative port gain.
 */
static inline void OPAMP_DoNegGainConfig(OPAMP_Type *base, opamp_negative_gain_t option)
{
    base->OPAMP_CTR = (((base->OPAMP_CTR) & (~OPAMP_OPAMP_CTR_NGAIN_MASK)) | OPAMP_OPAMP_CTR_NGAIN(option));
}
/*! @} */

#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_BUFEN) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_BUFEN
/*!
 * @name Reference Buffer Control Interface
 * @{
 */

/*!
 * @brief Enable reference buffer.
 *
 * @param base OPAMP peripheral base address.
 * @param enable true to enable and false to disable.
 */
static inline void OPAMP_EnableRefBuffer(OPAMP_Type *base, bool enable)
{
    if (enable)
    {
        base->OPAMP_CTR |= OPAMP_OPAMP_CTR_BUFEN_MASK;
    }
    else
    {
        base->OPAMP_CTR &= ~(uint32_t)OPAMP_OPAMP_CTR_BUFEN_MASK;
    }
}
/*! @} */
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_BUFEN */

#if defined(FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD) && FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD
/*!
 * @name Trigger Mode Control Interface
 * @{
 */

/*!
 * @brief Enable OPAMP trigger mode.
 *
 * @param base OPAMP peripheral base address.
 * @param enable true to enable and false to disable.
 */
static inline void OPAMP_EnableTriggerMode(OPAMP_Type *base, bool enable)
{
    if (enable)
    {
        base->OPAMP_CTR |= OPAMP_OPAMP_CTR_TRIGMD_MASK;
    }
    else
    {
        base->OPAMP_CTR &= ~(uint32_t)OPAMP_OPAMP_CTR_TRIGMD_MASK;
    }
}
/*! @} */
#endif /* FSL_FEATURE_OPAMP_HAS_OPAMP_CTR_TRIGMD */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_OPAMP_H_ */
