/*
 * Copyright 2017-2021, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_DCDC_H__
#define __FSL_DCDC_H__

#include "fsl_common.h"

/*!
 * @addtogroup dcdc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief DCDC driver version. */
#define FSL_DCDC_DRIVER_VERSION (MAKE_VERSION(2, 3, 0)) /*!< Version 2.3.0. */

/*!
 * @brief DCDC status flags.
 */
enum _dcdc_status_flags_t
{
    kDCDC_LockedOKStatus = (1U << 0U), /*!< Indicate DCDC status. 1'b1: DCDC already settled 1'b0: DCDC is settling. */
};

/*!
 * @brief The current bias of low power comparator.
 */
typedef enum _dcdc_comparator_current_bias
{
    kDCDC_ComparatorCurrentBias50nA  = 0U, /*!< The current bias of low power comparator is 50nA. */
    kDCDC_ComparatorCurrentBias100nA = 1U, /*!< The current bias of low power comparator is 100nA. */
    kDCDC_ComparatorCurrentBias200nA = 2U, /*!< The current bias of low power comparator is 200nA. */
    kDCDC_ComparatorCurrentBias400nA = 3U, /*!< The current bias of low power comparator is 400nA. */
} dcdc_comparator_current_bias_t;

/*!
 * @brief The threshold of over current detection.
 */
typedef enum _dcdc_over_current_threshold
{
    kDCDC_OverCurrentThresholdAlt0 = 0U, /*!< 1A in the run mode, 0.25A in the power save mode. */
    kDCDC_OverCurrentThresholdAlt1 = 1U, /*!< 2A in the run mode, 0.25A in the power save mode. */
    kDCDC_OverCurrentThresholdAlt2 = 2U, /*!< 1A in the run mode, 0.2A in the power save mode. */
    kDCDC_OverCurrentThresholdAlt3 = 3U, /*!< 2A in the run mode, 0.2A in the power save mode. */
} dcdc_over_current_threshold_t;

/*!
 * @brief The threshold if peak current detection.
 */
typedef enum _dcdc_peak_current_threshold
{
    kDCDC_PeakCurrentThresholdAlt0 = 0U, /*!< 150mA peak current threshold. */
    kDCDC_PeakCurrentThresholdAlt1 = 1U, /*!< 250mA peak current threshold. */
    kDCDC_PeakCurrentThresholdAlt2 = 2U, /*!< 350mA peak current threshold. */
    kDCDC_PeakCurrentThresholdAlt3 = 3U, /*!< 450mA peak current threshold. */
    kDCDC_PeakCurrentThresholdAlt4 = 4U, /*!< 550mA peak current threshold. */
    kDCDC_PeakCurrentThresholdAlt5 = 5U, /*!< 650mA peak current threshold. */
} dcdc_peak_current_threshold_t;

/*!
 * @brief The period of counting the charging times in power save mode.
 */
typedef enum _dcdc_count_charging_time_period
{
    kDCDC_CountChargingTimePeriod8Cycle  = 0U, /*!< Eight 32k cycle. */
    kDCDC_CountChargingTimePeriod16Cycle = 1U, /*!< Sixteen 32k cycle. */
} dcdc_count_charging_time_period_t;

/*!
 * @brief The threshold of the counting number of charging times
 */
typedef enum _dcdc_count_charging_time_threshold
{
    kDCDC_CountChargingTimeThreshold32 = 0U, /*!< 0x0: 32. */
    kDCDC_CountChargingTimeThreshold64 = 1U, /*!< 0x1: 64. */
    kDCDC_CountChargingTimeThreshold16 = 2U, /*!< 0x2: 16. */
    kDCDC_CountChargingTimeThreshold8  = 3U, /*!< 0x3: 8. */
} dcdc_count_charging_time_threshold_t;

/*!
 * @brief Oscillator clock option.
 */
typedef enum _dcdc_clock_source
{
    kDCDC_ClockAutoSwitch  = 0U, /*!< Automatic clock switch from internal oscillator to external clock. */
    kDCDC_ClockInternalOsc = 1U, /*!< Use internal oscillator. */
    kDCDC_ClockExternalOsc = 2U, /*!< Use external 24M crystal oscillator. */
} dcdc_clock_source_t;

#if (defined(FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT) && (FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT == 2))
/*!
 * @brief Voltage output option.
 */
typedef enum _dcdc_voltage_output_sel
{
    kDCDC_VoltageOutput1P8 = 0U, /*!< 1.8V output. */
    kDCDC_VoltageOutput1P0 = 1U, /*!< 1.0V output. */
} dcdc_voltage_output_sel_t;
#endif /* FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT */

#if defined(FSL_FEATURE_DCDC_HAS_CTRL_REG) && FSL_FEATURE_DCDC_HAS_CTRL_REG
/*!
 * @brief DCDC low power modes.
 */
typedef enum _dcdc_low_power_mode
{
    kDCDC_StandbyMode            = 0U, /*!< Standby mode. */
    kDCDC_LowPowerMode           = 1U, /*!< Low power mode. */
    kDCDC_GpcStandbyLowPowerMode = 2U, /*!< low power mode for GPC standby request. */
} dcdc_low_power_mode_t;

/*!
 * @brief DCDC control mode.
 */
typedef enum _dcdc_control_mode
{
    kDCDC_StaticControl   = 0U, /*!< Static control. */
    kDCDC_SetPointControl = 1U, /*!< Controlled by GPC set points. */
} dcdc_control_mode_t;

/*!
 * @brief DCDC trim input mode.
 */
typedef enum _dcdc_trim_input_mode
{
    kDCDC_SampleTrimInput = 0U, /*!< Sample trim input. */
    kDCDC_HoldTrimInput   = 1U, /*!< Hold trim input. */
} dcdc_trim_input_mode_t;

#if defined(DCDC_REG4_ENABLE_SP_MASK) && DCDC_REG4_ENABLE_SP_MASK
/*!
 * @brief System setpoints enumeration.
 */
enum _dcdc_setpoint_map
{
    kDCDC_SetPoint0  = 1UL << 0UL,  /*!< Set point 0. */
    kDCDC_SetPoint1  = 1UL << 1UL,  /*!< Set point 1. */
    kDCDC_SetPoint2  = 1UL << 2UL,  /*!< Set point 2. */
    kDCDC_SetPoint3  = 1UL << 3UL,  /*!< Set point 3. */
    kDCDC_SetPoint4  = 1UL << 4UL,  /*!< Set point 4. */
    kDCDC_SetPoint5  = 1UL << 5UL,  /*!< Set point 5. */
    kDCDC_SetPoint6  = 1UL << 6UL,  /*!< Set point 6. */
    kDCDC_SetPoint7  = 1UL << 7UL,  /*!< Set point 7. */
    kDCDC_SetPoint8  = 1UL << 8UL,  /*!< Set point 8. */
    kDCDC_SetPoint9  = 1UL << 9UL,  /*!< Set point 9. */
    kDCDC_SetPoint10 = 1UL << 10UL, /*!< Set point 10. */
    kDCDC_SetPoint11 = 1UL << 11UL, /*!< Set point 11. */
    kDCDC_SetPoint12 = 1UL << 12UL, /*!< Set point 12. */
    kDCDC_SetPoint13 = 1UL << 13UL, /*!< Set point 13. */
    kDCDC_SetPoint14 = 1UL << 14UL, /*!< Set point 14. */
    kDCDC_SetPoint15 = 1UL << 15UL  /*!< Set point 15. */
};
#endif /* DCDC_REG4_ENABLE_SP_MASK */

/*!
 * @brief Configuration for DCDC.
 */
typedef struct _dcdc_config
{
    dcdc_control_mode_t controlMode;      /*!< DCDC control mode. */
    dcdc_trim_input_mode_t trimInputMode; /*!< Hold trim input. */
    bool enableDcdcTimeout;               /*!< Enable internal count for DCDC_OK timeout. */
    bool enableSwitchingConverterOutput;  /*!< Enable the VDDIO switching converter output.*/
} dcdc_config_t;
#endif /* FSL_FEATURE_DCDC_HAS_CTRL_REGp */

/*!
 * @brief Configuration for DCDC detection.
 */
typedef struct _dcdc_detection_config
{
    bool enableXtalokDetection; /*!< Enable xtalok detection circuit. */
#if (defined(FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT) && (FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT == 2))
    bool powerDownOverVoltageVdd1P8Detection; /*!< Power down over-voltage detection comparator for VDD1P8. */
    bool powerDownOverVoltageVdd1P0Detection; /*!< Power down over-voltage detection comparator for VDD1P0. */
#else
    bool powerDownOverVoltageDetection; /*!< Power down over-voltage detection comparator. */
#endif                                  /* FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT */
    bool powerDownLowVlotageDetection;  /*!< Power down low-voltage detection comparator. */
    bool powerDownOverCurrentDetection; /*!< Power down over-current detection. */
    bool powerDownPeakCurrentDetection; /*!< Power down peak-current detection. */
    bool powerDownZeroCrossDetection;   /*!< Power down the zero cross detection function for discontinuous conductor
                                           mode. */
    dcdc_over_current_threshold_t OverCurrentThreshold; /*!< The threshold of over current detection. */
    dcdc_peak_current_threshold_t PeakCurrentThreshold; /*!< The threshold of peak current detection. */
} dcdc_detection_config_t;

/*!
 * @brief Configuration for the loop control.
 */
typedef struct _dcdc_loop_control_config
{
    bool enableCommonHysteresis;         /*!< Enable hysteresis in switching converter common mode analog comparators.
                                              This feature will improve transient supply ripple and efficiency. */
    bool enableCommonThresholdDetection; /*!< Increase the threshold detection for common mode analog comparator. */
#if defined(FSL_FEATURE_DCDC_HAS_SWITCHING_CONVERTER_DIFFERENTIAL_MODE) && \
    FSL_FEATURE_DCDC_HAS_SWITCHING_CONVERTER_DIFFERENTIAL_MODE
    bool enableDifferentialHysteresis;         /*!< Enable hysteresis in switching converter differential mode analog
                                                    comparators. This feature will improve transient supply ripple and
                                                    efficiency. */
    bool enableDifferentialThresholdDetection; /*!< Increase the threshold detection for differential mode analog
                                                    comparators. */
#endif                                         /* FSL_FEATURE_DCDC_HAS_SWITCHING_CONVERTER_DIFFERENTIAL_MODE */
    bool enableInvertHysteresisSign;           /*!< Invert the sign of the hysteresis in DC-DC analog comparators. */
    bool enableRCThresholdDetection;           /*!< Increase the threshold detection for RC scale circuit. */
    uint32_t enableRCScaleCircuit;      /*!< Available range is 0~7. Enable analog circuit of DC-DC converter to respond
                                             faster under transient load conditions. */
    uint32_t complementFeedForwardStep; /*!< Available range is 0~7. Two's complement feed forward step in duty cycle in
                                           the switching DC-DC converter. Each time this field makes a transition from
                                           0x0, the loop filter of the DC-DC converter is stepped once by a value
                                           proportional to the change. This can be used to force a certain control loop
                                           behavior, such as improving response under known heavy load transients. */
} dcdc_loop_control_config_t;
/*!
 * @brief Configuration for DCDC low power.
 */
typedef struct _dcdc_low_power_config
{
#if !(defined(FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS) && FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS)
    bool enableOverloadDetection; /*!< Enable the overload detection in power save mode, if current is larger than the
                                     overloading threshold (typical value is 50 mA), DCDC will switch to the run mode
                                     automatically. */
#endif                            /* FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS */
    bool enableAdjustHystereticValue; /*!< Adjust hysteretic value in low power from 12.5mV to 25mV. */
    dcdc_count_charging_time_period_t
        countChargingTimePeriod; /*!< The period of counting the charging times in power save mode. */
    dcdc_count_charging_time_threshold_t
        countChargingTimeThreshold; /*!< the threshold of the counting number of charging times during
                                         the period that lp_overload_freq_sel sets in power save mode. */
} dcdc_low_power_config_t;

/*!
 * @brief Configuration for DCDC internal regulator.
 */
typedef struct _dcdc_internal_regulator_config
{
    bool enableLoadResistor; /*!< control the load resistor of the internal regulator of DCDC, the load resistor is
                                connected as default "true", and need set to "false" to disconnect the load
                                resistor. */
    uint32_t feedbackPoint;  /*!< Available range is 0~3. Select the feedback point of the internal regulator. */
} dcdc_internal_regulator_config_t;

/*!
 * @brief Configuration for min power setting.
 */
typedef struct _dcdc_min_power_config
{
    bool enableUseHalfFreqForContinuous; /*!< Set DCDC clock to half frequency for the continuous mode. */
} dcdc_min_power_config_t;

#if defined(DCDC_REG4_ENABLE_SP_MASK) && DCDC_REG4_ENABLE_SP_MASK
/*!
 * @brief DCDC configuration in set point mode.
 */
typedef struct _dcdc_setpoint_config
{
    uint32_t enableDCDCMap;     /*!< The setpoint map that enable the DCDC module. Should be the OR'ed value of @ref
                                   _dcdc_setpoint_map. */
    uint32_t enableDigLogicMap; /*!< The setpoint map that enable the DCDC dig logic. Should be the OR'ed value of @ref
                                   _dcdc_setpoint_map. */
    uint32_t lowpowerMap; /*!< The setpoint map that enable the DCDC Low powermode. Should be the OR'ed value of @ref
                              _dcdc_setpoint_map. */
    uint32_t standbyMap;  /*!< The setpoint map that enable the DCDC standby mode. Should be the OR'ed value of @ref
                              _dcdc_setpoint_map. */
    uint32_t standbyLowpowerMap; /*!< The setpoint map that enable the DCDC low power mode, when the related setpoint is
                                    in standby mode.
                                     @ref _dcdc_setpoint_map. */
    uint8_t *buckVDD1P8TargetVoltage;    /*!< Point to the array that store the target voltage level of VDD1P8 in buck
                                            mode.    Note that the pointed array must have 16 elements. */
    uint8_t *buckVDD1P0TargetVoltage;    /*!< Point to the array that store the target voltage level of VDD1P0 in buck
                                            mode.    Note that the pointed array must have 16 elements. */
    uint8_t *standbyVDD1P8TargetVoltage; /*!< Point to the array that store the target voltage level of VDD1P8 in
                                            standby mode. Note that the pointed array must have 16 elements. */
    uint8_t *standbyVDD1P0TargetVoltage; /*!< Point to the array that store the target voltage level of VDD1P0 in
                                            standby mode. Note that the pointed array must have 16 elements. */
} dcdc_setpoint_config_t;

#endif /* DCDC_REG4_ENABLE_SP_MASK */

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @name Initialization and deinitialization
 * @{
 */

#if defined(FSL_FEATURE_DCDC_HAS_CTRL_REG) && FSL_FEATURE_DCDC_HAS_CTRL_REG
/*!
 * @brief Enable the access to DCDC registers.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to the configuration structure.
 */
void DCDC_Init(DCDC_Type *base, dcdc_config_t *config);
#else
/*!
 * @brief Enable the access to DCDC registers.
 *
 * @param base DCDC peripheral base address.
 */
void DCDC_Init(DCDC_Type *base);
#endif /* FSL_FEATURE_DCDC_HAS_CTRL_REG */

/*!
 * @brief Disable the access to DCDC registers.
 *
 * @param base DCDC peripheral base address.
 */
void DCDC_Deinit(DCDC_Type *base);

#if defined(FSL_FEATURE_DCDC_HAS_CTRL_REG) && FSL_FEATURE_DCDC_HAS_CTRL_REG
/*!
 * brief Get the default setting for DCDC user configuration structure.
 *
 * This function initializes the user configuration structure to a default value. The default values are:
 * code
 *   config->controlMode                    = kDCDC_StaticControl;
 *   config->trimInputMode                  = kDCDC_SampleTrimInput;
 *   config->enableDcdcTimeout              = false;
 *   config->enableSwitchingConverterOutput = false;
 * endcode
 *
 * param config Pointer to configuration structure. See to "dcdc_config_t"
 */
void DCDC_GetDefaultConfig(DCDC_Type *base, dcdc_config_t *config);
#endif /* FSL_FEATURE_DCDC_HAS_CTRL_REGp */

/* @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Get DCDC status flags.
 *
 * @param base peripheral base address.
 * @return Mask of asserted status flags. See to "_dcdc_status_flags_t".
 */
uint32_t DCDC_GetstatusFlags(DCDC_Type *base);

/* @} */

/*!
 * @name Misc control
 * @{
 */

#if defined(FSL_FEATURE_DCDC_HAS_CTRL_REG) && FSL_FEATURE_DCDC_HAS_CTRL_REG
/*!
 * @brief Make DCDC enter into low power modes.
 *
 * @param base DCDC peripheral base address.
 * @param mode DCDC low power mode selection. See to "_dcdc_low_power_mode"
 */
void DCDC_EnterLowPowerMode(DCDC_Type *base, dcdc_low_power_mode_t mode);
#endif /* FSL_FEATURE_DCDC_HAS_CTRL_REG */

/*!
 * @brief Enable the output range comparator.
 *
 * The output range comparator is disabled by default.
 *
 * @param base DCDC peripheral base address.
 * @param enable Enable the feature or not.
 */
static inline void DCDC_EnableOutputRangeComparator(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->REG0 &= ~DCDC_REG0_PWD_CMP_OFFSET_MASK;
    }
    else
    {
        base->REG0 |= DCDC_REG0_PWD_CMP_OFFSET_MASK;
    }
}

/*!
 * @brief Configure the DCDC clock source.
 *
 * @param base DCDC peripheral base address.
 * @param clockSource Clock source for DCDC. See to "dcdc_clock_source_t".
 */
void DCDC_SetClockSource(DCDC_Type *base, dcdc_clock_source_t clockSource);

/*!
 * @brief Get the default setting for detection configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * @code
 *   config->enableXtalokDetection = false;
 *   config->powerDownOverVoltageDetection = true;
 *   config->powerDownLowVlotageDetection = false;
 *   config->powerDownOverCurrentDetection = true;
 *   config->powerDownPeakCurrentDetection = true;
 *   config->powerDownZeroCrossDetection = true;
 *   config->OverCurrentThreshold = kDCDC_OverCurrentThresholdAlt0;
 *   config->PeakCurrentThreshold = kDCDC_PeakCurrentThresholdAlt0;
 * @endcode
 *
 * @param config Pointer to configuration structure. See to "dcdc_detection_config_t"
 */
void DCDC_GetDefaultDetectionConfig(dcdc_detection_config_t *config);

/*!
 * @brief Configure the DCDC detection.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to "dcdc_detection_config_t"
 */
void DCDC_SetDetectionConfig(DCDC_Type *base, const dcdc_detection_config_t *config);

/*!
 * @brief Get the default setting for low power configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * @code
 *   config->enableOverloadDetection = true;
 *   config->enableAdjustHystereticValue = false;
 *   config->countChargingTimePeriod = kDCDC_CountChargingTimePeriod8Cycle;
 *   config->countChargingTimeThreshold = kDCDC_CountChargingTimeThreshold32;
 * @endcode
 *
 * @param config Pointer to configuration structure. See to "dcdc_low_power_config_t"
 */
void DCDC_GetDefaultLowPowerConfig(dcdc_low_power_config_t *config);

/*!
 * @brief Configure the DCDC low power.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to "dcdc_low_power_config_t".
 */
void DCDC_SetLowPowerConfig(DCDC_Type *base, const dcdc_low_power_config_t *config);

/*!
 * @brief Reset current alert signal. Alert signal is generate by peak current detection.
 *
 * @param base DCDC peripheral base address.
 * @param enable Switcher to reset signal. True means reset signal. False means don't reset signal.
 */
void DCDC_ResetCurrentAlertSignal(DCDC_Type *base, bool enable);

/*!
 * @brief Set the bangap trim value to trim bandgap voltage.
 *
 * @param base DCDC peripheral base address.
 * @param trimValue The bangap trim value. Available range is 0U-31U.
 */
static inline void DCDC_SetBandgapVoltageTrimValue(DCDC_Type *base, uint32_t trimValue)
{
    base->REG1 &= ~DCDC_REG1_VBG_TRIM_MASK;
    base->REG1 |= DCDC_REG1_VBG_TRIM(trimValue);
}

/*!
 * @brief Get the default setting for loop control configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * @code
 *   config->enableCommonHysteresis = false;
 *   config->enableCommonThresholdDetection = false;
 *   config->enableInvertHysteresisSign = false;
 *   config->enableRCThresholdDetection = false;
 *   config->enableRCScaleCircuit = 0U;
 *   config->complementFeedForwardStep = 0U;
 * @endcode
 *
 * @param config Pointer to configuration structure. See to "dcdc_loop_control_config_t"
 */
void DCDC_GetDefaultLoopControlConfig(dcdc_loop_control_config_t *config);

/*!
 * @brief Configure the DCDC loop control.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to "dcdc_loop_control_config_t".
 */
void DCDC_SetLoopControlConfig(DCDC_Type *base, const dcdc_loop_control_config_t *config);

/*!
 * @brief Configure for the min power.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to "dcdc_min_power_config_t".
 */
void DCDC_SetMinPowerConfig(DCDC_Type *base, const dcdc_min_power_config_t *config);

/*!
 * @brief Set the current bias of low power comparator.
 *
 * @param base DCDC peripheral base address.
 * @param biasVaule The current bias of low power comparator. Refer to "dcdc_comparator_current_bias_t".
 */
static inline void DCDC_SetLPComparatorBiasValue(DCDC_Type *base, dcdc_comparator_current_bias_t biasVaule)
{
    base->REG1 &= ~DCDC_REG1_LP_CMP_ISRC_SEL_MASK;
    base->REG1 |= DCDC_REG1_LP_CMP_ISRC_SEL(biasVaule);
}

#if (defined(FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT) && (FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT == 2))
/*!
 * @brief Lock VDD 1P0 target voltage.
 *
 * @param base DCDC peripheral base address.
 */
static inline void DCDC_LockVdd1p0TargetVoltage(DCDC_Type *base)
{
    base->REG3 |= DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;
}

/*!
 * @brief Lock VDD 1P8 target voltage.
 *
 * @param base DCDC peripheral base address.
 */
static inline void DCDC_LockVdd1p8TargetVoltage(DCDC_Type *base)
{
    base->REG3 |= DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_MASK;
}

/*!
 * @brief Adjust the target voltage of VDD_SOC in run mode and low power mode.
 * @deprecated Do not use this function. It has been superceded by @ref DCDC_AdjustRunTargetVoltage
 * and @ref DCDC_AdjustLowPowerTargetVoltage
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * @param base DCDC peripheral base address.
 * @param VDDRun Target value in run mode. 25 mV each step from 0x00 to 0x1F. 00 is for 0.8V, 0x1F is for 1.575V.
 * @param VDDStandby Target value in low power mode. 25 mV each step from 0x00 to 0x4. 00 is for 0.9V, 0x4 is for 1.0V.
 * @param sel sel DCDC target voltage output selection. See to "_dcdc_voltage_output_sel".
 */
void DCDC_AdjustTargetVoltage(DCDC_Type *base, uint32_t VDDRun, uint32_t VDDStandby, dcdc_voltage_output_sel_t sel);

/*!
 * @brief Adjust the target voltage of VDD_SOC in run mode.
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * @param base DCDC peripheral base address.
 * @param VDDRun Target value in run mode. 25 mV each step from 0x00 to 0x1F. 00 is for 0.8V, 0x1F is for 1.575V.
 * @param sel sel DCDC target voltage output selection. See to "_dcdc_voltage_output_sel".
 */
void DCDC_AdjustRunTargetVoltage(DCDC_Type *base, uint32_t VDDRun, dcdc_voltage_output_sel_t sel);

/*!
 * @brief Adjust the target voltage of VDD_SOC in low power mode.
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * @param base DCDC peripheral base address.
 * @param VDDStandby Target value in low power mode. 25 mV each step from 0x00 to 0x4. 00 is for 0.9V, 0x4 is for 1.0V.
 * @param sel sel DCDC target voltage output selection. See to "_dcdc_voltage_output_sel".
 */
void DCDC_AdjustLowPowerTargetVoltage(DCDC_Type *base, uint32_t VDDStandby, dcdc_voltage_output_sel_t sel);
#else

/*!
 * @brief Lock target voltage.
 *
 * @param base DCDC peripheral base address.
 */
static inline void DCDC_LockTargetVoltage(DCDC_Type *base)
{
    base->REG3 |= DCDC_REG3_DISABLE_STEP_MASK;
}

/*!
 * @brief Adjust the target voltage of VDD_SOC in run mode and low power mode.
 * @deprecated Do not use this function. It has been superceded by @ref DCDC_AdjustRunTargetVoltage
 * and @ref DCDC_AdjustLowPowerTargetVoltage
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * @param base DCDC peripheral base address.
 * @param VDDRun Target value in run mode. 25 mV each step from 0x00 to 0x1F. 00 is for 0.8V, 0x1F is for 1.575V.
 * @param VDDStandby Target value in low power mode. 25 mV each step from 0x00 to 0x4. 00 is for 0.9V, 0x4 is for 1.0V.
 */
void DCDC_AdjustTargetVoltage(DCDC_Type *base, uint32_t VDDRun, uint32_t VDDStandby);

/*!
 * @brief Adjust the target voltage of VDD_SOC in run mode.
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * @param base DCDC peripheral base address.
 * @param VDDRun Target value in run mode. 25 mV each step from 0x00 to 0x1F. 00 is for 0.8V, 0x1F is for 1.575V.
 */
void DCDC_AdjustRunTargetVoltage(DCDC_Type *base, uint32_t VDDRun);

/*!
 * @brief Adjust the target voltage of VDD_SOC in low power mode.
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * @param base DCDC peripheral base address.
 * @param VDDStandby Target value in low power mode. 25 mV each step from 0x00 to 0x4. 00 is for 0.9V, 0x4 is for 1.0V.
 */
void DCDC_AdjustLowPowerTargetVoltage(DCDC_Type *base, uint32_t VDDStandby);
#endif /* FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT */

/*!
 * @brief Configure the DCDC internal regulator.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to "dcdc_internal_regulator_config_t".
 */
void DCDC_SetInternalRegulatorConfig(DCDC_Type *base, const dcdc_internal_regulator_config_t *config);

/*!
 * @brief Enable/Disable to improve the transition from heavy load to light load. It is valid while zero
 *        cross detection is enabled. If ouput exceeds the threshold, DCDC would return CCM from DCM.
 *
 * @param base DCDC peripheral base address.
 * @param enable Enable the feature or not.
 */
static inline void DCDC_EnableImproveTransition(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->REG2 |= DCDC_REG2_DCM_SET_CTRL_MASK;
    }
    else
    {
        base->REG2 &= ~DCDC_REG2_DCM_SET_CTRL_MASK;
    }
}

/* @} */

#if defined(DCDC_REG4_ENABLE_SP_MASK) && DCDC_REG4_ENABLE_SP_MASK
/*!
 * @name Setpoint mode APIs
 */

/*!
 * @brief Init DCDC module when the control mode selected as setpoint mode.
 *
 * @note The function should be invoked in the initial step to config the
 *       DCDC via setpoint control mode.
 *
 * @param base DCDC peripheral base address.
 * @param config The pointer to the structure @ref dcdc_setpoint_config_t.
 */
void DCDC_SetPointInit(DCDC_Type *base, const dcdc_setpoint_config_t *config);

/*!
 * @brief Disable DCDC module when the control mode selected as setpoint mode.
 *
 * @param base DCDC peripheral base address.
 * @param setpointMap. The map of the setpoint to disable the DCDC module.
 *                      Should be the OR'ed value of _dcdc_setpoint_map.
 */
static inline void DCDC_SetPointDeinit(DCDC_Type *base, uint32_t setpointMap)
{
    base->REG4 &= ~setpointMap;
}

/* @} */
#endif /* DCDC_REG4_ENABLE_SP_MASK */

/*!
 * @name Application guideline
 * @{
 */

/*!
 * @brief Boot DCDC into DCM(discontinous conduction mode).
 *
 *  pwd_zcd=0x0;
 *  pwd_cmp_offset=0x0;
 *  dcdc_loopctrl_en_rcscale= 0x5;
 *  DCM_set_ctrl=1'b1;
 *
 * @param base DCDC peripheral base address.
 */
void DCDC_BootIntoDCM(DCDC_Type *base);

/*!
 * @brief Boot DCDC into CCM(continous conduction mode).
 *
 *  pwd_zcd=0x1;
 *  pwd_cmp_offset=0x0;
 *  dcdc_loopctrl_en_rcscale=0x3;
 *
 * @param base DCDC peripheral base address.
 */
void DCDC_BootIntoCCM(DCDC_Type *base);

/* @} */

#if defined(__cplusplus)
}
#endif

/* @} */

#endif /* __FSL_DCDC_H__ */
