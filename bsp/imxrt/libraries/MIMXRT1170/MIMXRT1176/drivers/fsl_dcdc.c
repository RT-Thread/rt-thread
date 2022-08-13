/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dcdc.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dcdc_soc"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * brief Gets instance number for DCDC module.
 *
 * param base DCDC peripheral base address
 */
static uint32_t DCDC_GetInstance(DCDC_Type *base);

/*!
 * brief Converts the byte array to word.
 *
 * param ptrArray Pointer to the byte array.
 * return The converted result.
 */
static uint32_t DCDC_ConvertByteArrayToWord(uint8_t *ptrArray);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! brief Pointers to DCDC bases for each instance. */
static DCDC_Type *const s_dcdcBases[] = DCDC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! brief Pointers to DCDC clocks for each instance. */
static const clock_ip_name_t s_dcdcClocks[] = DCDC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * CodDCDC_GetstatusFlagse
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

static uint32_t DCDC_ConvertByteArrayToWord(uint8_t *ptrArray)
{
    assert(ptrArray != NULL);

    uint32_t temp32 = 0UL;
    uint32_t index;

    for (index = 0U; index < 4U; index++)
    {
        temp32 |= (uint32_t)ptrArray[index] << ((index % 4UL) * 8UL);
    }

    return temp32;
}

/*!
 * brief Initializes the basic resource of DCDC module, such as control mode, etc.
 *
 * param base DCDC peripheral base address.
 * param config Pointer to the configuration structure.
 */
void DCDC_Init(DCDC_Type *base, const dcdc_config_t *config)
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
    tmp32 |= DCDC_CTRL0_ENABLE_MASK;
    base->CTRL0 = tmp32;
}

/*!
 * brief De-initializes the DCDC module.
 *
 * param base DCDC peripheral base address.
 */
void DCDC_Deinit(DCDC_Type *base)
{
    /* Disables DCDC. */
    base->CTRL0 &= ~DCDC_CTRL0_ENABLE_MASK;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_dcdcClocks[DCDC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets the default setting for DCDC, such as control mode, etc.
 *
 * This function initializes the user configuration structure to a default value. The default values are:
 * code
 *   config->controlMode                    = kDCDC_StaticControl;
 *   config->trimInputMode                  = kDCDC_SampleTrimInput;
 *   config->enableDcdcTimeout              = false;
 *   config->enableSwitchingConverterOutput = false;
 * endcode
 *
 * param config Pointer to configuration structure. See to dcdc_config_t.
 */
void DCDC_GetDefaultConfig(dcdc_config_t *config)
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
 * brief Gets the default setting for detection configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * code
 *   config->enableXtalokDetection = false;
 *   config->powerDownOverVoltageVdd1P8Detection = true;
 *   config->powerDownOverVoltageVdd1P0Detection = true;
 *   config->powerDownLowVoltageDetection  = false;
 *   config->powerDownOverCurrentDetection = true;
 *   config->powerDownPeakCurrentDetection = true;
 *   config->powerDownZeroCrossDetection   = true;
 *   config->PeakCurrentThreshold          = kDCDC_PeakCurrentRunMode250mALPMode1P5A;
 * endcode
 *
 * param config Pointer to configuration structure. See to "dcdc_detection_config_t"
 */
void DCDC_GetDefaultDetectionConfig(dcdc_detection_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableXtalokDetection               = false;
    config->powerDownOverVoltageVdd1P8Detection = true;
    config->powerDownOverVoltageVdd1P0Detection = true;
    config->powerDownLowVoltageDetection        = false;
    config->powerDownOverCurrentDetection       = true;
    config->powerDownPeakCurrentDetection       = true;
    config->powerDownZeroCrossDetection         = true;
    config->PeakCurrentThreshold                = kDCDC_PeakCurrentRunMode250mALPMode1P5A;
}

/*!
 * breif Configures the DCDC detection.
 *
 * param base DCDC peripheral base address.
 * param config Pointer to configuration structure. See to "dcdc_detection_config_t"
 */
void DCDC_SetDetectionConfig(DCDC_Type *base, const dcdc_detection_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;
    /* Configure the DCDC_REG0 register. */
    tmp32 = base->REG0 &
            ~(DCDC_REG0_XTALOK_DISABLE_MASK | DCDC_REG0_PWD_HIGH_VDD1P8_DET_MASK | DCDC_REG0_PWD_HIGH_VDD1P0_DET_MASK |
              DCDC_REG0_PWD_CMP_DCDC_IN_DET_MASK | DCDC_REG0_PWD_OVERCUR_DET_MASK | DCDC_REG0_PWD_CUR_SNS_CMP_MASK |
              DCDC_REG0_PWD_ZCD_MASK | DCDC_REG0_CUR_SNS_THRSH_MASK);

    tmp32 |= DCDC_REG0_CUR_SNS_THRSH(config->PeakCurrentThreshold);
    if (false == config->enableXtalokDetection)
    {
        tmp32 |= DCDC_REG0_XTALOK_DISABLE_MASK;
    }
    if (config->powerDownOverVoltageVdd1P8Detection)
    {
        tmp32 |= DCDC_REG0_PWD_HIGH_VDD1P8_DET_MASK;
    }
    if (config->powerDownOverVoltageVdd1P0Detection)
    {
        tmp32 |= DCDC_REG0_PWD_HIGH_VDD1P0_DET_MASK;
    }
    if (config->powerDownLowVoltageDetection)
    {
        tmp32 |= DCDC_REG0_PWD_CMP_DCDC_IN_DET_MASK;
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
 * brief Configures the DCDC clock source.
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
 * brief Gets the default setting for low power configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * code
 *   config->enableAdjustHystereticValue = false;
 * endcode
 *
 * param config Pointer to configuration structure. See to "dcdc_low_power_config_t"
 */
void DCDC_GetDefaultLowPowerConfig(dcdc_low_power_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));
    config->enableAdjustHystereticValue = false;
}

/*!
 * brief Configures the DCDC low power.
 *
 * param base DCDC peripheral base address.
 * param config Pointer to configuration structure. See to "dcdc_low_power_config_t".
 */
void DCDC_SetLowPowerConfig(DCDC_Type *base, const dcdc_low_power_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;
    /* Configure the DCDC_REG0 register. */
    tmp32 = base->REG0 & ~(DCDC_REG0_LP_HIGH_HYS_MASK);

    if (config->enableAdjustHystereticValue)
    {
        tmp32 |= DCDC_REG0_LP_HIGH_HYS_MASK;
    }
    base->REG0 = tmp32;
}

/*!
 * brief Gets the default setting for loop control configuration.
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
 *   config->controlParameterMagnitude = 2U;
 *   config->integralProportionalRatio = 2U;
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
    config->controlParameterMagnitude      = 2U;
    config->integralProportionalRatio      = 2U;
}

/*!
 * brief Configures the DCDC loop control.
 *
 * param base DCDC peripheral base address.
 * param config Pointer to configuration structure. See to "dcdc_loop_control_config_t".
 */
void DCDC_SetLoopControlConfig(DCDC_Type *base, const dcdc_loop_control_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;

    /* Configure the DCDC_REG1 register. */
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

    base->REG1 = tmp32;

    /* configure the DCDC_REG2 register. */
    tmp32 = base->REG2 & ~(DCDC_REG2_LOOPCTRL_HYST_SIGN_MASK | DCDC_REG2_LOOPCTRL_RCSCALE_THRSH_MASK |
                           DCDC_REG2_LOOPCTRL_EN_RCSCALE_MASK | DCDC_REG2_LOOPCTRL_DC_FF_MASK |
                           DCDC_REG2_LOOPCTRL_DC_R_MASK | DCDC_REG2_LOOPCTRL_DC_C_MASK);
    tmp32 |= DCDC_REG2_LOOPCTRL_DC_FF(config->complementFeedForwardStep) |
             DCDC_REG2_LOOPCTRL_DC_R(config->controlParameterMagnitude) |
             DCDC_REG2_LOOPCTRL_DC_C(config->integralProportionalRatio) |
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
 * brief Configures for the min power.
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

/*!
 * brief Configures the DCDC internal regulator.
 *
 * param base DCDC peripheral base address.
 * param config Pointer to configuration structure. See to "dcdc_internal_regulator_config_t".
 */
void DCDC_SetInternalRegulatorConfig(DCDC_Type *base, const dcdc_internal_regulator_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;

    tmp32 = base->REG3 & ~DCDC_REG3_REG_FBK_SEL_MASK;
    tmp32 |= DCDC_REG3_REG_FBK_SEL(config->feedbackPoint);
    base->REG3 = tmp32;
}

/*!
 * brief Initializes DCDC module when the control mode selected as setpoint mode.
 *
 * note The function should be invoked in the initial step to config the
 *      DCDC via setpoint control mode.
 *
 * param base DCDC peripheral base address.
 * param config The pointer to the structure dcdc_setpoint_config_t.
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
    base->REG8  = DCDC_ConvertByteArrayToWord((uint8_t *)config->buckVDD1P8TargetVoltage);
    base->REG9  = DCDC_ConvertByteArrayToWord((uint8_t *)config->buckVDD1P8TargetVoltage + 4U);
    base->REG10 = DCDC_ConvertByteArrayToWord((uint8_t *)config->buckVDD1P8TargetVoltage + 8U);
    base->REG11 = DCDC_ConvertByteArrayToWord((uint8_t *)config->buckVDD1P8TargetVoltage + 12U);

    /* Set target voltage of VDD1P0 in buck mode. */
    base->REG12 = DCDC_ConvertByteArrayToWord((uint8_t *)config->buckVDD1P0TargetVoltage);
    base->REG13 = DCDC_ConvertByteArrayToWord((uint8_t *)config->buckVDD1P0TargetVoltage + 4U);
    base->REG14 = DCDC_ConvertByteArrayToWord((uint8_t *)config->buckVDD1P0TargetVoltage + 8U);
    base->REG15 = DCDC_ConvertByteArrayToWord((uint8_t *)config->buckVDD1P0TargetVoltage + 12U);

    /* Set target voltage of VDD1P8 in low power mode. */
    base->REG16 = DCDC_ConvertByteArrayToWord((uint8_t *)config->standbyVDD1P8TargetVoltage);
    base->REG17 = DCDC_ConvertByteArrayToWord((uint8_t *)config->standbyVDD1P8TargetVoltage + 4U);
    base->REG18 = DCDC_ConvertByteArrayToWord((uint8_t *)config->standbyVDD1P8TargetVoltage + 8U);
    base->REG19 = DCDC_ConvertByteArrayToWord((uint8_t *)config->standbyVDD1P8TargetVoltage + 12U);

    /* Set target voltage of VDD1P0 in low power mode. */
    base->REG20 = DCDC_ConvertByteArrayToWord((uint8_t *)config->standbyVDD1P0TargetVoltage);
    base->REG21 = DCDC_ConvertByteArrayToWord((uint8_t *)config->standbyVDD1P0TargetVoltage + 4U);
    base->REG22 = DCDC_ConvertByteArrayToWord((uint8_t *)config->standbyVDD1P0TargetVoltage + 8U);
    base->REG23 = DCDC_ConvertByteArrayToWord((uint8_t *)config->standbyVDD1P0TargetVoltage + 12U);

    /* Enable DCDC module. */
    base->REG4 = config->enableDCDCMap;
}

/*!
 * brief Boots DCDC into DCM(discontinous conduction mode).
 *
 *  pwd_zcd=0x0;
 *  DM_CTRL = 1'b1;
 *  pwd_cmp_offset=0x0;
 *  dcdc_loopctrl_en_rcscale=0x3 or 0x5;
 *  DCM_set_ctrl=1'b1;
 *
 * param base DCDC peripheral base address.
 */
void DCDC_BootIntoDCM(DCDC_Type *base)
{
    base->REG0 &= ~(DCDC_REG0_PWD_ZCD_MASK | DCDC_REG0_PWD_CMP_OFFSET_MASK);
    base->REG1 &= ~DCDC_REG1_RLOAD_REG_EN_LPSR_MASK;
    base->REG1 |= DCDC_REG1_DM_CTRL_MASK;
    base->REG2 = (~DCDC_REG2_LOOPCTRL_EN_RCSCALE_MASK & base->REG2) | DCDC_REG2_LOOPCTRL_EN_RCSCALE(0x5U);
    base->REG3 &= ~(DCDC_REG3_DISABLE_IDLE_SKIP_MASK | DCDC_REG3_DISABLE_PULSE_SKIP_MASK);
    base->REG3 |= DCDC_REG3_ENABLE_FF_MASK;
}

/*!
 * brief Boots DCDC into CCM(continous conduction mode).
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
