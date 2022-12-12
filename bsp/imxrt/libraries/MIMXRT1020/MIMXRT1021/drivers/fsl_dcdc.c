/*
 * Copyright 2017-2021, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dcdc.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dcdc_1"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for DCDC module.
 *
 * @param base DCDC peripheral base address
 */
static uint32_t DCDC_GetInstance(DCDC_Type *base);

#if (defined(DCDC_REG4_ENABLE_SP_MASK) && DCDC_REG4_ENABLE_SP_MASK)
/*!
 * @brief Convert the byte array to word.
 *
 * @param ptrArray Pointer to the byte array.
 * @return The converted result.
 */
static uint32_t DCDC_ConvertByteArrayToWord(uint8_t *ptrArray);
#endif /* DCDC_REG4_ENABLE_SP_MASK */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to DCDC bases for each instance. */
static DCDC_Type *const s_dcdcBases[] = DCDC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to DCDC clocks for each instance. */
static const clock_ip_name_t s_dcdcClocks[] = DCDC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t DCDC_GetInstance(DCDC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_dcdcBases); instance++)
    {
        if (s_dcdcBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_dcdcBases));

    return instance;
}

#if (defined(DCDC_REG4_ENABLE_SP_MASK) && DCDC_REG4_ENABLE_SP_MASK)
static uint32_t DCDC_ConvertByteArrayToWord(uint8_t *ptrArray)
{
    assert(ptrArray != NULL);

    uint32_t temp32 = 0UL;
    uint8_t index;

    for (index = 0U; index < 4U; index++)
    {
        temp32 |= ptrArray[index] << ((index % 4U) * 8U);
    }

    return temp32;
}
#endif /* DCDC_REG4_ENABLE_SP_MASK */

#if defined(FSL_FEATURE_DCDC_HAS_CTRL_REG) && FSL_FEATURE_DCDC_HAS_CTRL_REG
/*!
 * brief Enable the access to DCDC registers.
 *
 * param base DCDC peripheral base address.
 * param config Pointer to the configuration structure.
 */
void DCDC_Init(DCDC_Type *base, dcdc_config_t *config)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_dcdcClocks[DCDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    uint32_t tmp32 = base->CTRL0;

    tmp32 |= DCDC_CTRL0_CONTROL_MODE(config->controlMode) | DCDC_CTRL0_TRIM_HOLD(config->trimInputMode);

    if (config->enableDcdcTimeout)
    {
        tmp32 |= DCDC_CTRL0_ENABLE_DCDC_CNT_MASK;
    }
    if (config->enableSwitchingConverterOutput)
    {
        tmp32 |= DCDC_CTRL0_DIG_EN_MASK;
    }
    base->CTRL0 |= DCDC_CTRL0_ENABLE_MASK;
    base->CTRL0 = tmp32;
}
#else
/*!
 * brief Enable the access to DCDC registers.
 *
 * param base DCDC peripheral base address.
 */
void DCDC_Init(DCDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_dcdcClocks[DCDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
#endif /* FSL_FEATURE_DCDC_HAS_CTRL_REG */

/*!
 * brief Disable the access to DCDC registers.
 *
 * param base DCDC peripheral base address.
 */
void DCDC_Deinit(DCDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_dcdcClocks[DCDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

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
void DCDC_GetDefaultConfig(DCDC_Type *base, dcdc_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->controlMode                    = kDCDC_StaticControl;
    config->trimInputMode                  = kDCDC_SampleTrimInput;
    config->enableDcdcTimeout              = false;
    config->enableSwitchingConverterOutput = false;
}

/*!
 * @brief Make DCDC enter into low power modes.
 *
 * @param base DCDC peripheral base address.
 * @param mode DCDC low power mode selection. See to "_dcdc_low_power_mode"
 */
void DCDC_EnterLowPowerMode(DCDC_Type *base, dcdc_low_power_mode_t mode)
{
    switch (mode)
    {
        case kDCDC_StandbyMode:
            base->CTRL0 |= DCDC_CTRL0_STBY_EN_MASK;
            break;
        case kDCDC_LowPowerMode:
            base->CTRL0 |= DCDC_CTRL0_LP_MODE_EN_MASK;
            break;
        case kDCDC_GpcStandbyLowPowerMode:
            base->CTRL0 |= DCDC_CTRL0_STBY_LP_MODE_EN_MASK;
            break;
        default:
            assert(false);
            break;
    }
}
#endif /* FSL_FEATURE_DCDC_HAS_CTRL_REG */

/*!
 * brief Configure the DCDC clock source.
 *
 * param base DCDC peripheral base address.
 * param clockSource Clock source for DCDC. See to "dcdc_clock_source_t".
 */
void DCDC_SetClockSource(DCDC_Type *base, dcdc_clock_source_t clockSource)
{
    uint32_t tmp32;

    /* Configure the DCDC_REG0 register. */
    tmp32 = base->REG0 & ~(DCDC_REG0_XTAL_24M_OK_MASK | DCDC_REG0_DISABLE_AUTO_CLK_SWITCH_MASK |
                           DCDC_REG0_SEL_CLK_MASK | DCDC_REG0_PWD_OSC_INT_MASK);
    switch (clockSource)
    {
        case kDCDC_ClockInternalOsc:
            tmp32 |= DCDC_REG0_DISABLE_AUTO_CLK_SWITCH_MASK;
            break;
        case kDCDC_ClockExternalOsc:
            /* Choose the external clock and disable the internal clock. */
            tmp32 |= DCDC_REG0_DISABLE_AUTO_CLK_SWITCH_MASK | DCDC_REG0_SEL_CLK_MASK | DCDC_REG0_PWD_OSC_INT_MASK;
            break;
        case kDCDC_ClockAutoSwitch:
            /* Set to switch from internal ring osc to xtal 24M if auto mode is enabled. */
            tmp32 |= DCDC_REG0_XTAL_24M_OK_MASK;
            break;
        default:
            assert(false);
            break;
    }
    base->REG0 = tmp32;
}

/*!
 * brief Get the default setting for detection configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * code
 *   config->enableXtalokDetection = false;
 *   config->powerDownOverVoltageDetection = true;
 *   config->powerDownLowVlotageDetection = false;
 *   config->powerDownOverCurrentDetection = true;
 *   config->powerDownPeakCurrentDetection = true;
 *   config->powerDownZeroCrossDetection = true;
 *   config->OverCurrentThreshold = kDCDC_OverCurrentThresholdAlt0;
 *   config->PeakCurrentThreshold = kDCDC_PeakCurrentThresholdAlt0;
 * endcode
 *
 * param config Pointer to configuration structure. See to "dcdc_detection_config_t"
 */
void DCDC_GetDefaultDetectionConfig(dcdc_detection_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableXtalokDetection = false;
#if (defined(FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT) && (FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT == 2))
    config->powerDownOverVoltageVdd1P8Detection = true;
    config->powerDownOverVoltageVdd1P0Detection = true;
#else
    config->powerDownOverVoltageDetection = true;
#endif /* FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT */
    config->powerDownLowVlotageDetection  = false;
    config->powerDownOverCurrentDetection = true;
    config->powerDownPeakCurrentDetection = true;
    config->powerDownZeroCrossDetection   = true;
    config->OverCurrentThreshold          = kDCDC_OverCurrentThresholdAlt0;
    config->PeakCurrentThreshold          = kDCDC_PeakCurrentThresholdAlt0;
}

/*!
 * breif Configure the DCDC detection.
 *
 * param base DCDC peripheral base address.
 * param config Pointer to configuration structure. See to "dcdc_detection_config_t"
 */
void DCDC_SetDetectionConfig(DCDC_Type *base, const dcdc_detection_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;
    /* Configure the DCDC_REG0 register. */
    tmp32 = base->REG0 & ~(DCDC_REG0_XTALOK_DISABLE_MASK
#if (defined(FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT) && (FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT == 2))
                           | DCDC_REG0_PWD_HIGH_VDD1P8_DET_MASK | DCDC_REG0_PWD_HIGH_VDD1P0_DET_MASK
#else
                           | DCDC_REG0_PWD_HIGH_VOLT_DET_MASK
#endif /* FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT */
#if defined(FSL_FEATURE_DCDC_HAS_REG0_DCDC_IN_DET) && FSL_FEATURE_DCDC_HAS_REG0_DCDC_IN_DET
                           | DCDC_REG0_PWD_CMP_DCDC_IN_DET_MASK
#else
                           | DCDC_REG0_PWD_CMP_BATT_DET_MASK
#endif /* FSL_FEATURE_DCDC_HAS_REG0_DCDC_IN_DET */
                           | DCDC_REG0_PWD_OVERCUR_DET_MASK | DCDC_REG0_PWD_CUR_SNS_CMP_MASK | DCDC_REG0_PWD_ZCD_MASK |
                           DCDC_REG0_CUR_SNS_THRSH_MASK | DCDC_REG0_OVERCUR_TRIG_ADJ_MASK);

    tmp32 |= DCDC_REG0_CUR_SNS_THRSH(config->PeakCurrentThreshold) |
             DCDC_REG0_OVERCUR_TRIG_ADJ(config->OverCurrentThreshold);
    if (false == config->enableXtalokDetection)
    {
        tmp32 |= DCDC_REG0_XTALOK_DISABLE_MASK;
    }
#if (defined(FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT) && (FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT == 2))
    if (config->powerDownOverVoltageVdd1P8Detection)
    {
        tmp32 |= DCDC_REG0_PWD_HIGH_VDD1P8_DET_MASK;
    }
    if (config->powerDownOverVoltageVdd1P0Detection)
    {
        tmp32 |= DCDC_REG0_PWD_HIGH_VDD1P0_DET_MASK;
    }
#else
    if (config->powerDownOverVoltageDetection)
    {
        tmp32 |= DCDC_REG0_PWD_HIGH_VOLT_DET_MASK;
    }
#endif /* FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT */
    if (config->powerDownLowVlotageDetection)
    {
#if defined(FSL_FEATURE_DCDC_HAS_REG0_DCDC_IN_DET) && FSL_FEATURE_DCDC_HAS_REG0_DCDC_IN_DET
        tmp32 |= DCDC_REG0_PWD_CMP_DCDC_IN_DET_MASK;
#else
        tmp32 |= DCDC_REG0_PWD_CMP_BATT_DET_MASK;
#endif /* FSL_FEATURE_DCDC_HAS_REG0_DCDC_IN_DET */
    }
    if (config->powerDownOverCurrentDetection)
    {
        tmp32 |= DCDC_REG0_PWD_OVERCUR_DET_MASK;
    }
    if (config->powerDownPeakCurrentDetection)
    {
        tmp32 |= DCDC_REG0_PWD_CUR_SNS_CMP_MASK;
    }
    if (config->powerDownZeroCrossDetection)
    {
        tmp32 |= DCDC_REG0_PWD_ZCD_MASK;
    }
    base->REG0 = tmp32;
}

/*!
 * brief Get the default setting for low power configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * code
 *   config->enableOverloadDetection = true;
 *   config->enableAdjustHystereticValue = false;
 *   config->countChargingTimePeriod = kDCDC_CountChargingTimePeriod8Cycle;
 *   config->countChargingTimeThreshold = kDCDC_CountChargingTimeThreshold32;
 * endcode
 *
 * param config Pointer to configuration structure. See to "dcdc_low_power_config_t"
 */
void DCDC_GetDefaultLowPowerConfig(dcdc_low_power_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));
#if !(defined(FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS) && FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS)
    config->enableOverloadDetection = true;
#endif /* FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS */
    config->enableAdjustHystereticValue = false;
    config->countChargingTimePeriod     = kDCDC_CountChargingTimePeriod8Cycle;
    config->countChargingTimeThreshold  = kDCDC_CountChargingTimeThreshold32;
}

/*!
 * brief Configure the DCDC low power.
 *
 * param base DCDC peripheral base address.
 * param config Pointer to configuration structure. See to "dcdc_low_power_config_t".
 */
void DCDC_SetLowPowerConfig(DCDC_Type *base, const dcdc_low_power_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;
    /* Configure the DCDC_REG0 register. */
    tmp32 = base->REG0 &
            ~(DCDC_REG0_LP_HIGH_HYS_MASK | DCDC_REG0_LP_OVERLOAD_FREQ_SEL_MASK | DCDC_REG0_LP_OVERLOAD_THRSH_MASK
#if !(defined(FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS) && FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS)
              | DCDC_REG0_EN_LP_OVERLOAD_SNS_MASK
#endif /* FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS */
            );
    tmp32 |= DCDC_REG0_LP_OVERLOAD_FREQ_SEL(config->countChargingTimePeriod) |
             DCDC_REG0_LP_OVERLOAD_THRSH(config->countChargingTimeThreshold);
#if !(defined(FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS) && FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS)
    if (config->enableOverloadDetection)
    {
        tmp32 |= DCDC_REG0_EN_LP_OVERLOAD_SNS_MASK;
    }
#endif /* FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS */
    if (config->enableAdjustHystereticValue)
    {
        tmp32 |= DCDC_REG0_LP_HIGH_HYS_MASK;
    }
    base->REG0 = tmp32;
}

/*!
 * brief Get DCDC status flags.
 *
 * param base peripheral base address.
 * return Mask of asserted status flags. See to "_dcdc_status_flags_t".
 */
uint32_t DCDC_GetstatusFlags(DCDC_Type *base)
{
    uint32_t tmp32 = 0U;

    if (DCDC_REG0_STS_DC_OK_MASK == (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
        tmp32 |= (uint32_t)kDCDC_LockedOKStatus;
    }

    return tmp32;
}

#if !(defined(FSL_FEATURE_DCDC_HAS_NO_CURRENT_ALERT_FUNC) && FSL_FEATURE_DCDC_HAS_NO_CURRENT_ALERT_FUNC)
/*!
 * brief Reset current alert signal. Alert signal is generate by peak current detection.
 *
 * param base DCDC peripheral base address.
 * param enable Switcher to reset signal. True means reset signal. False means don't reset signal.
 */
void DCDC_ResetCurrentAlertSignal(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->REG0 |= DCDC_REG0_CURRENT_ALERT_RESET_MASK;
    }
    else
    {
        base->REG0 &= ~DCDC_REG0_CURRENT_ALERT_RESET_MASK;
    }
}
#endif /* FSL_FEATURE_DCDC_HAS_NO_CURRENT_ALERT_FUNC */

/*!
 * brief Get the default setting for loop control configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * code
 *   config->enableCommonHysteresis = false;
 *   config->enableCommonThresholdDetection = false;
 *   config->enableInvertHysteresisSign = false;
 *   config->enableRCThresholdDetection = false;
 *   config->enableRCScaleCircuit = 0U;
 *   config->complementFeedForwardStep = 0U;
 * endcode
 *
 * param config Pointer to configuration structure. See to "dcdc_loop_control_config_t"
 */
void DCDC_GetDefaultLoopControlConfig(dcdc_loop_control_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableCommonHysteresis         = false;
    config->enableCommonThresholdDetection = false;
    config->enableInvertHysteresisSign     = false;
    config->enableRCThresholdDetection     = false;
    config->enableRCScaleCircuit           = 0U;
    config->complementFeedForwardStep      = 0U;
}

/*!
 * brief Configure the DCDC loop control.
 *
 * param base DCDC peripheral base address.
 * param config Pointer to configuration structure. See to "dcdc_loop_control_config_t".
 */
void DCDC_SetLoopControlConfig(DCDC_Type *base, const dcdc_loop_control_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;

    /* Configure the DCDC_REG1 register. */
#if defined(FSL_FEATURE_DCDC_HAS_SWITCHING_CONVERTER_DIFFERENTIAL_MODE) && \
    FSL_FEATURE_DCDC_HAS_SWITCHING_CONVERTER_DIFFERENTIAL_MODE
    tmp32 = base->REG1 & ~(DCDC_REG1_LOOPCTRL_EN_DF_HYST_MASK | DCDC_REG1_LOOPCTRL_EN_CM_HYST_MASK |
                           DCDC_REG1_LOOPCTRL_DF_HST_THRESH_MASK | DCDC_REG1_LOOPCTRL_CM_HST_THRESH_MASK);
    if (config->enableCommonHysteresis)
    {
        tmp32 |= DCDC_REG1_LOOPCTRL_EN_CM_HYST_MASK;
    }
    if (config->enableCommonThresholdDetection)
    {
        tmp32 |= DCDC_REG1_LOOPCTRL_CM_HST_THRESH_MASK;
    }
    if (config->enableDifferentialHysteresis)
    {
        tmp32 |= DCDC_REG1_LOOPCTRL_EN_DF_HYST_MASK;
    }
    if (config->enableDifferentialThresholdDetection)
    {
        tmp32 |= DCDC_REG1_LOOPCTRL_DF_HST_THRESH_MASK;
    }
#else
    tmp32 = base->REG1 & ~(DCDC_REG1_LOOPCTRL_EN_HYST_MASK | DCDC_REG1_LOOPCTRL_HST_THRESH_MASK);
    if (config->enableCommonHysteresis)
    {
        tmp32 |= DCDC_REG1_LOOPCTRL_EN_HYST_MASK;
    }
    if (config->enableCommonThresholdDetection)
    {
        tmp32 |= DCDC_REG1_LOOPCTRL_HST_THRESH_MASK;
    }
#endif /* FSL_FEATURE_DCDC_HAS_SWITCHING_CONVERTER_DIFFERENTIAL_MODE */
    base->REG1 = tmp32;

    /* configure the DCDC_REG2 register. */
    tmp32 = base->REG2 & ~(DCDC_REG2_LOOPCTRL_HYST_SIGN_MASK | DCDC_REG2_LOOPCTRL_RCSCALE_THRSH_MASK |
                           DCDC_REG2_LOOPCTRL_EN_RCSCALE_MASK | DCDC_REG2_LOOPCTRL_DC_FF_MASK);
    tmp32 |= DCDC_REG2_LOOPCTRL_DC_FF(config->complementFeedForwardStep) |
             DCDC_REG2_LOOPCTRL_EN_RCSCALE(config->enableRCScaleCircuit);
    if (config->enableInvertHysteresisSign)
    {
        tmp32 |= DCDC_REG2_LOOPCTRL_HYST_SIGN_MASK;
    }
    if (config->enableRCThresholdDetection)
    {
        tmp32 |= DCDC_REG2_LOOPCTRL_RCSCALE_THRSH_MASK;
    }
    base->REG2 = tmp32;
}

/*!
 * brief Configure for the min power.
 *
 * param base DCDC peripheral base address.
 * param config Pointer to configuration structure. See to "dcdc_min_power_config_t".
 */
void DCDC_SetMinPowerConfig(DCDC_Type *base, const dcdc_min_power_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;

    tmp32 = base->REG3 & ~DCDC_REG3_MINPWR_DC_HALFCLK_MASK;
    if (config->enableUseHalfFreqForContinuous)
    {
        tmp32 |= DCDC_REG3_MINPWR_DC_HALFCLK_MASK;
    }
    base->REG3 = tmp32;
}

#if (defined(FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT) && (FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT == 2))
/*!
 * brief Adjust the target voltage of VDD_SOC in run mode and low power mode.
 * Do not use this function. It has been superceded by DCDC_AdjustRunTargetVoltage
 * and DCDC_AdjustLowPowerTargetVoltage.
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * param base DCDC peripheral base address.
 * param VDDRun Target value in run mode. 25 mV each step from 0x00 to 0x1F. 00 is for 0.8V, 0x1F is for 1.575V.
 * param VDDStandby Target value in low power mode. 25 mV each step from 0x00 to 0x4. 00 is for 0.9V, 0x4 is for 1.0V.
 * param sel sel DCDC target voltage output selection. See to "_dcdc_voltage_output_sel".
 */
void DCDC_AdjustTargetVoltage(DCDC_Type *base, uint32_t VDDRun, uint32_t VDDStandby, dcdc_voltage_output_sel_t sel)
{
    uint32_t tmp32;

    if (sel == kDCDC_VoltageOutput1P8)
    {
        /* Unlock the step for the VDD 1P8. */
        base->REG3 &= ~DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_MASK;

        /* Configure the DCDC_CTRL1 register. */
        tmp32 = base->CTRL1 & ~(DCDC_CTRL1_VDD1P8CTRL_STBY_TRG_MASK | DCDC_CTRL1_VDD1P8CTRL_TRG_MASK);

        tmp32 |= DCDC_CTRL1_VDD1P8CTRL_STBY_TRG(VDDStandby) | DCDC_CTRL1_VDD1P8CTRL_TRG(VDDRun);
        base->CTRL1 = tmp32;
    }
    else if (sel == kDCDC_VoltageOutput1P0)
    {
        /* Unlock the step for the VDD 1P0. */
        base->REG3 &= ~DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;

        /* Configure the DCDC_CTRL1 register. */
        tmp32 = base->CTRL1 & ~(DCDC_CTRL1_VDD1P0CTRL_STBY_TRG_MASK | DCDC_CTRL1_VDD1P0CTRL_TRG_MASK);

        tmp32 |= DCDC_CTRL1_VDD1P0CTRL_STBY_TRG(VDDStandby) | DCDC_CTRL1_VDD1P0CTRL_TRG(VDDRun);
        base->CTRL1 = tmp32;
    }
    else
    {
        ; /* Intentional empty */
    }

    /* DCDC_STS_DC_OK bit will be de-asserted after target register changes. After output voltage is set to new
     * target value, DCDC_STS_DC_OK will be asserted. */
    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}

/*!
 * brief Adjust the target voltage of VDD_SOC in run mode.
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * param base DCDC peripheral base address.
 * param VDDRun Target value in run mode. 25 mV each step from 0x00 to 0x1F. 00 is for 0.8V, 0x1F is for 1.575V.
 * param sel sel DCDC target voltage output selection. See to "_dcdc_voltage_output_sel".
 */
void DCDC_AdjustRunTargetVoltage(DCDC_Type *base, uint32_t VDDRun, dcdc_voltage_output_sel_t sel)
{
    uint32_t tmp32;

    if (sel == kDCDC_VoltageOutput1P8)
    {
        /* Unlock the step for the VDD 1P8. */
        base->REG3 &= ~DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_MASK;

        /* Configure the DCDC_CTRL1 register. */
        tmp32 = base->CTRL1 & ~DCDC_CTRL1_VDD1P8CTRL_TRG_MASK;

        tmp32 |= DCDC_CTRL1_VDD1P8CTRL_TRG(VDDRun);
        base->CTRL1 = tmp32;
    }
    else if (sel == kDCDC_VoltageOutput1P0)
    {
        /* Unlock the step for the VDD 1P0. */
        base->REG3 &= ~DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;

        /* Configure the DCDC_CTRL1 register. */
        tmp32 = base->CTRL1 & ~DCDC_CTRL1_VDD1P0CTRL_TRG_MASK;

        tmp32 |= DCDC_CTRL1_VDD1P0CTRL_TRG(VDDRun);
        base->CTRL1 = tmp32;
    }
    else
    {
        ; /* Intentional empty */
    }

    /* DCDC_STS_DC_OK bit will be de-asserted after target register changes. After output voltage is set to new
     * target value, DCDC_STS_DC_OK will be asserted. */
    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}

/*!
 * brief Adjust the target voltage of VDD_SOC in low power mode.
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * param base DCDC peripheral base address.
 * param VDDStandby Target value in low power mode. 25 mV each step from 0x00 to 0x4. 00 is for 0.9V, 0x4 is for 1.0V.
 * param sel sel DCDC target voltage output selection. See to "_dcdc_voltage_output_sel".
 */
void DCDC_AdjustLowPowerTargetVoltage(DCDC_Type *base, uint32_t VDDStandby, dcdc_voltage_output_sel_t sel)
{
    uint32_t tmp32;

    if (sel == kDCDC_VoltageOutput1P8)
    {
        /* Unlock the step for the VDD 1P8. */
        base->REG3 &= ~DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_MASK;

        /* Configure the DCDC_CTRL1 register. */
        tmp32 = base->CTRL1 & ~(DCDC_CTRL1_VDD1P8CTRL_STBY_TRG_MASK);

        tmp32 |= DCDC_CTRL1_VDD1P8CTRL_STBY_TRG(VDDStandby);
        base->CTRL1 = tmp32;
    }
    else if (sel == kDCDC_VoltageOutput1P0)
    {
        /* Unlock the step for the VDD 1P0. */
        base->REG3 &= ~DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;

        /* Configure the DCDC_CTRL1 register. */
        tmp32 = base->CTRL1 & ~(DCDC_CTRL1_VDD1P0CTRL_STBY_TRG_MASK);

        tmp32 |= DCDC_CTRL1_VDD1P0CTRL_STBY_TRG(VDDStandby);
        base->CTRL1 = tmp32;
    }
    else
    {
        ; /* Intentional empty */
    }

    /* DCDC_STS_DC_OK bit will be de-asserted after target register changes. After output voltage is set to new
     * target value, DCDC_STS_DC_OK will be asserted. */
    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}
#else

/*!
 * brief Adjust the target voltage of VDD_SOC in run mode and low power mode.
 * Do not use this function. It has been superceded by DCDC_AdjustRunTargetVoltage
 * and DCDC_AdjustLowPowerTargetVoltage
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * param base DCDC peripheral base address.
 * param VDDRun Target value in run mode. 25 mV each step from 0x00 to 0x1F. 00 is for 0.8V, 0x1F is for 1.575V.
 * param VDDStandby Target value in low power mode. 25 mV each step from 0x00 to 0x4. 00 is for 0.9V, 0x4 is for 1.0V.
 */
void DCDC_AdjustTargetVoltage(DCDC_Type *base, uint32_t VDDRun, uint32_t VDDStandby)
{
    uint32_t tmp32;

    /* Unlock the step for the output. */
    base->REG3 &= ~DCDC_REG3_DISABLE_STEP_MASK;

    /* Configure the DCDC_REG3 register. */
    tmp32 = base->REG3 & ~(DCDC_REG3_TARGET_LP_MASK | DCDC_REG3_TRG_MASK);

    tmp32 |= DCDC_REG3_TARGET_LP(VDDStandby) | DCDC_REG3_TRG(VDDRun);
    base->REG3 = tmp32;

    /* DCDC_STS_DC_OK bit will be de-asserted after target register changes. After output voltage is set to new
     * target value, DCDC_STS_DC_OK will be asserted. */
    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}

/*!
 * brief Adjust the target voltage of VDD_SOC in run mode.
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * param base DCDC peripheral base address.
 * param VDDRun Target value in run mode. 25 mV each step from 0x00 to 0x1F. 00 is for 0.8V, 0x1F is for 1.575V.
 */
void DCDC_AdjustRunTargetVoltage(DCDC_Type *base, uint32_t VDDRun)
{
    uint32_t tmp32;

    /* Unlock the step for the output. */
    base->REG3 &= ~DCDC_REG3_DISABLE_STEP_MASK;

    /* Configure the DCDC_REG3 register. */
    tmp32 = base->REG3 & ~DCDC_REG3_TRG_MASK;

    tmp32 |= DCDC_REG3_TRG(VDDRun);
    base->REG3 = tmp32;

    /* DCDC_STS_DC_OK bit will be de-asserted after target register changes. After output voltage is set to new
     * target value, DCDC_STS_DC_OK will be asserted. */
    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}

/*!
 * brief Adjust the target voltage of VDD_SOC in low power mode.
 *
 * This function is to adjust the target voltage of DCDC output. Change them and finally wait until the output is
 * stabled.
 * Set the target value of run mode the same as low power mode before entering power save mode, because DCDC will switch
 * back to run mode if it detects the current loading is larger than about 50 mA(typical value).
 *
 * param base DCDC peripheral base address.
 * param VDDStandby Target value in low power mode. 25 mV each step from 0x00 to 0x4. 00 is for 0.9V, 0x4 is for 1.0V.
 */
void DCDC_AdjustLowPowerTargetVoltage(DCDC_Type *base, uint32_t VDDStandby)
{
    uint32_t tmp32;

    /* Unlock the step for the output. */
    base->REG3 &= ~DCDC_REG3_DISABLE_STEP_MASK;

    /* Configure the DCDC_REG3 register. */
    tmp32 = base->REG3 & ~DCDC_REG3_TARGET_LP_MASK;

    tmp32 |= DCDC_REG3_TARGET_LP(VDDStandby);
    base->REG3 = tmp32;

    /* DCDC_STS_DC_OK bit will be de-asserted after target register changes. After output voltage is set to new
     * target value, DCDC_STS_DC_OK will be asserted. */
    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}
#endif /* FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT == 2 */

/*!
 * brief Configure the DCDC internal regulator.
 *
 * param base DCDC peripheral base address.
 * param config Pointer to configuration structure. See to "dcdc_internal_regulator_config_t".
 */
void DCDC_SetInternalRegulatorConfig(DCDC_Type *base, const dcdc_internal_regulator_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;

#if (defined(FSL_FEATURE_DCDC_HAS_REG3_FBK_SEL) && FSL_FEATURE_DCDC_HAS_REG3_FBK_SEL)
    tmp32 = base->REG3 & ~DCDC_REG3_REG_FBK_SEL_MASK;
    tmp32 |= DCDC_REG3_REG_FBK_SEL(config->feedbackPoint);
    base->REG3 = tmp32;

    tmp32 = base->REG1 & ~DCDC_REG1_REG_RLOAD_SW_MASK;
#else
    /* Configure the DCDC_REG1 register. */
    tmp32 = base->REG1 & ~(DCDC_REG1_REG_FBK_SEL_MASK | DCDC_REG1_REG_RLOAD_SW_MASK);
    tmp32 |= DCDC_REG1_REG_FBK_SEL(config->feedbackPoint);
#endif /* FSL_FEATURE_DCDC_HAS_REG3_FBK_SEL */

    if (config->enableLoadResistor)
    {
        tmp32 |= DCDC_REG1_REG_RLOAD_SW_MASK;
    }
    base->REG1 = tmp32;
}

#if (defined(DCDC_REG4_ENABLE_SP_MASK) && DCDC_REG4_ENABLE_SP_MASK)
/*!
 * brief Init DCDC module when the control mode selected as setpoint mode.
 *
 * note The function should be invoked in the initial step to config the
 *      DCDC via setpoint control mode.
 *
 * param base DCDC peripheral base address.
 * param config The pointer to the structure @ref dcdc_setpoint_config_t.
 */
void DCDC_SetPointInit(DCDC_Type *base, const dcdc_setpoint_config_t *config)
{
    assert(config != NULL);

    /* Enable DCDC Dig Logic. */
    base->REG5 = config->enableDigLogicMap;

    /* Set DCDC power mode. */
    base->REG6  = config->lowpowerMap;
    base->REG7  = config->standbyMap;
    base->REG7P = config->standbyLowpowerMap;

    /* Set target voltage of VDD1P8 in buck mode. */
    base->REG8  = DCDC_ConvertByteArrayToWord(config->buckVDD1P8TargetVoltage);
    base->REG9  = DCDC_ConvertByteArrayToWord(config->buckVDD1P8TargetVoltage + 4U);
    base->REG10 = DCDC_ConvertByteArrayToWord(config->buckVDD1P8TargetVoltage + 8U);
    base->REG11 = DCDC_ConvertByteArrayToWord(config->buckVDD1P8TargetVoltage + 12U);

    /* Set target voltage of VDD1P0 in buck mode. */
    base->REG12 = DCDC_ConvertByteArrayToWord(config->buckVDD1P0TargetVoltage);
    base->REG13 = DCDC_ConvertByteArrayToWord(config->buckVDD1P0TargetVoltage + 4U);
    base->REG14 = DCDC_ConvertByteArrayToWord(config->buckVDD1P0TargetVoltage + 8U);
    base->REG15 = DCDC_ConvertByteArrayToWord(config->buckVDD1P0TargetVoltage + 12U);

    /* Set target voltage of VDD1P8 in low power mode. */
    base->REG16 = DCDC_ConvertByteArrayToWord(config->standbyVDD1P8TargetVoltage);
    base->REG17 = DCDC_ConvertByteArrayToWord(config->standbyVDD1P8TargetVoltage + 4U);
    base->REG18 = DCDC_ConvertByteArrayToWord(config->standbyVDD1P8TargetVoltage + 8U);
    base->REG19 = DCDC_ConvertByteArrayToWord(config->standbyVDD1P8TargetVoltage + 12U);

    /* Set target voltage of VDD1P0 in low power mode. */
    base->REG20 = DCDC_ConvertByteArrayToWord(config->standbyVDD1P0TargetVoltage);
    base->REG21 = DCDC_ConvertByteArrayToWord(config->standbyVDD1P0TargetVoltage + 4U);
    base->REG22 = DCDC_ConvertByteArrayToWord(config->standbyVDD1P0TargetVoltage + 8U);
    base->REG23 = DCDC_ConvertByteArrayToWord(config->standbyVDD1P0TargetVoltage + 12U);

    /* Enable DCDC module. */
    base->REG4 = config->enableDCDCMap;
}
#endif /* DCDC_REG4_ENABLE_SP_MASK */

/*!
 * brief Boot DCDC into DCM(discontinous conduction mode).
 *
 *  pwd_zcd=0x0;
 *  pwd_cmp_offset=0x0;
 *  dcdc_loopctrl_en_rcscale= 0x5;
 *  DCM_set_ctrl=1'b1;
 *
 * param base DCDC peripheral base address.
 */
void DCDC_BootIntoDCM(DCDC_Type *base)
{
    base->REG0 &= ~(DCDC_REG0_PWD_ZCD_MASK | DCDC_REG0_PWD_CMP_OFFSET_MASK);
    base->REG2 = (~DCDC_REG2_LOOPCTRL_EN_RCSCALE_MASK & base->REG2) | DCDC_REG2_LOOPCTRL_EN_RCSCALE(0x5U) |
                 DCDC_REG2_DCM_SET_CTRL_MASK;
}

/*!
 * brief Boot DCDC into CCM(continous conduction mode).
 *
 *  pwd_zcd=0x1;
 *  pwd_cmp_offset=0x0;
 *  dcdc_loopctrl_en_rcscale=0x3;
 *
 * param base DCDC peripheral base address.
 */
void DCDC_BootIntoCCM(DCDC_Type *base)
{
    base->REG0 = (~DCDC_REG0_PWD_CMP_OFFSET_MASK & base->REG0) | DCDC_REG0_PWD_ZCD_MASK;
    base->REG2 = (~DCDC_REG2_LOOPCTRL_EN_RCSCALE_MASK & base->REG2) | DCDC_REG2_LOOPCTRL_EN_RCSCALE(0x3U);
}
