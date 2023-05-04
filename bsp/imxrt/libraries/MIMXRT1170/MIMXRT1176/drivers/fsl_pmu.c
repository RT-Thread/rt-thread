/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pmu.h"
#include "fsl_anatop_ai.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.pmu_1"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PMU_LDO_LPSR_DIG_TRG_SPX_REG_SETPOINT_COUNTS         4U
#define PMU_LDO_LPSR_DIG_TRG_SPX_VOLTAGE_SETPOINTX_BIT_WIDTH 8UL

#define PMU_POWER_DETECT_CTRL_REGISTER (ANADIG_PMU->PMU_POWER_DETECT_CTRL)

#define PMU_BIAS_CTRL_WB_CFG_1P8_WELL_SELECT_MASK (0x1U)

#define PMU_BIAS_CTRL_WB_CFG_1P8_VOLTAGE_THRESHOLD_MASK  (0x2U)
#define PMU_BIAS_CTRL_WB_CFG_1P8_VOLTAGE_THRESHOLD_SHIFT 1U
#define PMU_BIAS_CTRL_WB_CFG_1P8_VOLTAGE_THRESHOLD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << PMU_BIAS_CTRL_WB_CFG_1P8_VOLTAGE_THRESHOLD_SHIFT)) & \
     PMU_BIAS_CTRL_WB_CFG_1P8_VOLTAGE_THRESHOLD_MASK)

#define PMU_BIAS_CTRL_WB_CFG_1P8_DRIVE_STRENGTH_MASK  (0x1CU)
#define PMU_BIAS_CTRL_WB_CFG_1P8_DRIVE_STRENGTH_SHIFT 2U
#define PMU_BIAS_CTRL_WB_CFG_1P8_DRIVE_STRENGTH(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << PMU_BIAS_CTRL_WB_CFG_1P8_DRIVE_STRENGTH_SHIFT)) & \
     PMU_BIAS_CTRL_WB_CFG_1P8_DRIVE_STRENGTH_MASK)

#define PMU_BIAS_CTRL_WB_CFG_1P8_OSCILLATOR_FREQ_MASK  (0x1E0U)
#define PMU_BIAS_CTRL_WB_CFG_1P8_OSCILLATOR_FREQ_SHIFT 5U
#define PMU_BIAS_CTRL_WB_CFG_1P8_OSCILLATOR_FREQ(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << PMU_BIAS_CTRL_WB_CFG_1P8_OSCILLATOR_FREQ_SHIFT)) & \
     PMU_BIAS_CTRL_WB_CFG_1P8_OSCILLATOR_FREQ_MASK)

#define PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(member) \
    ((uint32_t)((ANADIG_PMU_BASE) + (uint32_t)offsetof(ANADIG_PMU_Type, member)))

#define PMU_LDO_ENABLE_SETPOINT_REGISTERS                                  \
    {                                                                      \
        PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_PLL_ENABLE_SP),              \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_ANA_ENABLE_SP),     \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_DIG_ENABLE_SP), 0UL \
    }

#define PMU_LDO_LP_MODE_EN_SETPOINT_REGISTERS                               \
    {                                                                       \
        0UL, PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_ANA_LP_MODE_SP),    \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_DIG_LP_MODE_SP), 0UL \
    }

#define PMU_LDO_TRACKING_EN_SETPOINT_REGISTERS                                  \
    {                                                                           \
        0UL, PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_ANA_TRACKING_EN_SP),    \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_DIG_TRACKING_EN_SP), 0UL \
    }

#define PMU_LDO_BYPASS_EN_SETPOINT_REGISTERS                                  \
    {                                                                         \
        0UL, PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_ANA_BYPASS_EN_SP),    \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_DIG_BYPASS_EN_SP), 0UL \
    }

#define PMU_LDO_STBY_EN_REGISTERS                                           \
    {                                                                       \
        PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(PLL_LDO_STBY_EN_SP),              \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_ANA_STBY_EN_SP),     \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_DIG_STBY_EN_SP), 0UL \
    }

#define PMU_LPSR_DIG_TRG_REGISTERS                                   \
    {                                                                \
        PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_DIG_TRG_SP0),     \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_DIG_TRG_SP1), \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_DIG_TRG_SP2), \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(LDO_LPSR_DIG_TRG_SP3)  \
    }

#if (defined(PMU_HAS_FBB) && PMU_HAS_FBB)
#define PMU_BODY_BIAS_ENABLE_REGISTERS                                                                             \
    {                                                                                                              \
        PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(FBB_M7_ENABLE_SP), PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_SOC_ENABLE_SP), \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_LPSR_ENABLE_SP)                                                  \
    }
#else
#define PMU_BODY_BIAS_ENABLE_REGISTERS                                                                              \
    {                                                                                                               \
        PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_SOC_ENABLE_SP), PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_LPSR_ENABLE_SP) \
    }
#endif /* PMU_HAS_FBB */

#if (defined(PMU_HAS_FBB) && PMU_HAS_FBB)
#define PMU_BODY_BIAS_STBY_EN_REGISTERS                                                                              \
    {                                                                                                                \
        PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(FBB_M7_STBY_EN_SP), PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_SOC_STBY_EN_SP), \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_LPSR_STBY_EN_SP)                                                   \
    }
#else
#define PMU_BODY_BIAS_STBY_EN_REGISTERS                                                                               \
    {                                                                                                                 \
        PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_SOC_STBY_EN_SP), PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_LPSR_STBY_EN_SP) \
    }
#endif /* PMU_HAS_FBB */

#if (defined(PMU_HAS_FBB) && PMU_HAS_FBB)
#define PMU_BODY_BIAS_CONFIGURE_REGISTERS                                                                          \
    {                                                                                                              \
        PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(FBB_M7_CONFIGURE), PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_SOC_CONFIGURE), \
            PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_LPSR_CONFIGURE)                                                  \
    }
#else
#define PMU_BODY_BIAS_CONFIGURE_REGISTERS                                                                           \
    {                                                                                                               \
        PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_SOC_CONFIGURE), PMU_GET_ANADIG_PMU_MEMBER_ADDRESS(RBB_LPSR_CONFIGURE) \
    }
#endif /* PMU_HAS_FBB */
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Selects the control mode of the PLL LDO.
 *
 * param base PMU peripheral base address.
 * param mode The control mode of the PLL LDO. Please refer to pmu_control_mode_t.
 */
void PMU_SetPllLdoControlMode(ANADIG_PMU_Type *base, pmu_control_mode_t mode)
{
    if (mode == kPMU_StaticMode)
    {
        base->PMU_LDO_PLL &= ~ANADIG_PMU_PMU_LDO_PLL_LDO_PLL_CONTROL_MODE_MASK;
    }
    else
    {
        base->PMU_LDO_PLL |= ANADIG_PMU_PMU_LDO_PLL_LDO_PLL_CONTROL_MODE_MASK;
    }
}

/*!
 * brief Switches the PLL LDO from Static/Software Mode to GPC/Hardware Mode.
 *
 * param base PMU peripheral base address.
 */
void PMU_SwitchPllLdoToGPCMode(ANADIG_PMU_Type *base)
{
    if ((base->LDO_PLL_ENABLE_SP & ANADIG_PMU_LDO_PLL_ENABLE_SP_ON_OFF_SETPOINT0_MASK) != 0UL)
    {
        base->PMU_LDO_PLL |= ANADIG_PMU_PMU_LDO_PLL_LDO_PLL_ENABLE_MASK;
    }
    else
    {
        base->PMU_LDO_PLL &= ~ANADIG_PMU_PMU_LDO_PLL_LDO_PLL_ENABLE_MASK;
    }
}

/*!
 * brief Enables PLL LDO via AI interface in Static/Software mode.
 *
 * param base PMU peripheral base address.
 */
void PMU_StaticEnablePllLdo(ANADIG_PMU_Type *base)
{
    uint32_t temp32;

    temp32 = ANATOP_AI_Read(kAI_Itf_Ldo, kAI_PHY_LDO_CTRL0);

    if (temp32 !=
        (AI_PHY_LDO_CTRL0_OUTPUT_TRG(0x10) | AI_PHY_LDO_CTRL0_LINREG_EN_MASK | AI_PHY_LDO_CTRL0_LIMIT_EN_MASK))
    {
        ANATOP_AI_Write(
            kAI_Itf_Ldo, kAI_PHY_LDO_CTRL0,
            (AI_PHY_LDO_CTRL0_OUTPUT_TRG(0x10) | AI_PHY_LDO_CTRL0_LINREG_EN_MASK | AI_PHY_LDO_CTRL0_LIMIT_EN_MASK));
        SDK_DelayAtLeastUs(1, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        /* Enable Voltage Reference for PLLs before those PLLs were enabled. */
        base->PMU_REF_CTRL |= ANADIG_PMU_PMU_REF_CTRL_EN_PLL_VOL_REF_BUFFER_MASK;
    }
}

/*!
 * brief Disables PLL LDO via AI interface in Static/Software mode.
 */
void PMU_StaticDisablePllLdo(void)
{
    ANATOP_AI_Write(kAI_Itf_Ldo, kAI_PHY_LDO_CTRL0, 0UL);
}

/*!
 * brief Selects the control mode of the LPSR ANA LDO.
 *
 * param base PMU peripheral base address.
 * param mode The control mode of the LPSR ANA LDO. Please refer to pmu_control_mode_t.
 */
void PMU_SetLpsrAnaLdoControlMode(ANADIG_LDO_SNVS_Type *base, pmu_control_mode_t mode)
{
    if (mode == kPMU_StaticMode)
    {
        base->PMU_LDO_LPSR_ANA &= ~ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_LPSR_ANA_CONTROL_MODE_MASK;
    }
    else
    {
        base->PMU_LDO_LPSR_ANA |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_LPSR_ANA_CONTROL_MODE_MASK;
    }
}

/*!
 * brief Sets the Bypass mode of the LPSR ANA LDO.
 *
 * param base ANADIG_LDO_SNVS peripheral base address.
 * param enable Enable/Disable bypass mode.
 *          - \b true Enable LPSR ANA Bypass mode.
 *          - \b false Disable LPSR ANA Bypass mode.
 */
void PMU_StaticEnableLpsrAnaLdoBypassMode(ANADIG_LDO_SNVS_Type *base, bool enable)
{
    if (enable == false)
    {
        /* Enable LPSR ANA LDO and HP mode. */
        base->PMU_LDO_LPSR_ANA &=
            ~(ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_REG_LP_EN_MASK | ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_REG_DISABLE_MASK);
        SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        /* Clear Bypass. */
        base->PMU_LDO_LPSR_ANA &= ~(ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_BYPASS_MODE_EN_MASK);
        SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        /* Disable Tracking mode. */
        base->PMU_LDO_LPSR_ANA &= ~ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_TRACK_MODE_EN_MASK;
    }
    else
    {
        /* Enable HP mode. */
        base->PMU_LDO_LPSR_ANA &= ~ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_REG_LP_EN_MASK;
        SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        /* Enable Tracking mode. */
        base->PMU_LDO_LPSR_ANA |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_TRACK_MODE_EN_MASK;
        SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        /* Enabled Bypass. */
        base->PMU_LDO_LPSR_ANA |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_BYPASS_MODE_EN_MASK;
        SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        /* Disable LPSR ANA LDO. */
        base->PMU_LDO_LPSR_ANA |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_REG_DISABLE_MASK;
    }
}

/*!
 * brief Fill the LPSR ANA LDO configuration structure with default settings.
 *
 * The default values are:
 * code
 *      config->mode                   = kPMU_HighPowerMode;
        config->enable2mALoad          = true;
        config->enable20uALoad         = false;
        config->enable4mALoad          = true;
        config->enableStandbyMode      = false;
        config->driverStrength         = kPMU_LpsrAnaLdoDriverStrength0;
        config->brownOutDetectorConfig = kPMU_LpsrAnaLdoBrownOutDetectorDisable;
        config->chargePumpCurrent      = kPMU_LpsrAnaChargePump300nA;
        config->outputRange            = kPMU_LpsrAnaLdoOutputFrom1P77To1P83;
 * endcode
 *
 * param config Pointer to the structure pmu_static_lpsr_ana_ldo_config_t. Please refer to @ref
 * pmu_static_lpsr_ana_ldo_config_t.
 */
void PMU_StaticGetLpsrAnaLdoDefaultConfig(pmu_static_lpsr_ana_ldo_config_t *config)
{
    assert(config != NULL);

    (void)memset(config, 0, sizeof(*config));

    config->mode              = kPMU_HighPowerMode;
    config->enable2mALoad     = true;
    config->enable20uALoad    = false;
    config->enable4mALoad     = true;
    config->enableStandbyMode = false;
}

/*!
 * brief Initialize the LPSR ANA LDO in Static/Sofware Mode.
 *
 * param base ANADIG_LDO_SNVS peripheral base address.
 * param config Pointer to the structure pmu_static_lpsr_ana_ldo_config_t. Please refer to @ref
 * pmu_static_lpsr_ana_ldo_config_t.
 */
void PMU_StaticLpsrAnaLdoInit(ANADIG_LDO_SNVS_Type *base, const pmu_static_lpsr_ana_ldo_config_t *config)
{
    assert(config != NULL);

    uint32_t regValue = base->PMU_LDO_LPSR_ANA;

    regValue &=
        ~(ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_REG_LP_EN_MASK | ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_PULL_DOWN_2MA_EN_MASK |
          ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_ALWAYS_4MA_PULLDOWN_EN_MASK |
          ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_PULL_DOWN_20UA_EN_MASK | ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_STANDBY_EN_MASK);

    if ((config->mode) == kPMU_LowPowerMode)
    {
        regValue |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_REG_LP_EN_MASK;
    }
    regValue |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_PULL_DOWN_2MA_EN(config->enable2mALoad);
    regValue |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_ALWAYS_4MA_PULLDOWN_EN(config->enable4mALoad);
    regValue |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_PULL_DOWN_20UA_EN(config->enable20uALoad);
    regValue |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_STANDBY_EN(config->enableStandbyMode);

    base->PMU_LDO_LPSR_ANA = regValue;

    /* Enable LPSR ANA DIG. */
    base->PMU_LDO_LPSR_ANA &= ~ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_REG_DISABLE_MASK;
}

/*!
 * brief Disable the output of LPSR ANA LDO.
 *
 * param base ANADIG_LDO_SNVS peripheral base address.
 */
void PMU_StaticLpsrAnaLdoDeinit(ANADIG_LDO_SNVS_Type *base)
{
    /* Disable LPSR ANA LDO. */
    base->PMU_LDO_LPSR_ANA |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_ANA_REG_DISABLE_MASK;
}

/*!
 * brief Selects the control mode of the LPSR DIG LDO.
 *
 * param base ANADIG_LDO_SNVS peripheral base address.
 * param mode The control mode of the LPSR DIG LDO. Please refer to pmu_control_mode_t.
 */
void PMU_SetLpsrDigLdoControlMode(ANADIG_LDO_SNVS_Type *base, pmu_control_mode_t mode)
{
    if (mode == kPMU_StaticMode)
    {
        base->PMU_LDO_LPSR_DIG &= ~ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_LPSR_DIG_CONTROL_MODE_MASK;
    }
    else
    {
        base->PMU_LDO_LPSR_DIG |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_LPSR_DIG_CONTROL_MODE_MASK;
    }
}

/*!
 * brief Turn on/off Bypass mode of the LPSR DIG LDO in Static/Software mode.
 *
 * param base ANADIG_LDO_SNVS peripheral base address.
 * param enable
 *              true    -   Turn on Bypass mode of the LPSR DIG LDO.
 *              false   -   Turn off Bypass mode of the LPSR DIG LDO.
 */
void PMU_StaticEnableLpsrDigLdoBypassMode(ANADIG_LDO_SNVS_Type *base, bool enable)
{
    if (enable)
    {
        /* tracking */
        base->PMU_LDO_LPSR_DIG |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_TRACKING_MODE_MASK;
        SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        /* set BYPASS */
        base->PMU_LDO_LPSR_DIG |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_BYPASS_MODE_MASK;
        SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        /* Disable LPSR DIG LDO */
        base->PMU_LDO_LPSR_DIG &= ~ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_REG_EN_MASK;
    }
    else
    {
        /* Enable LPSR DIG LDO and HP mode */
        base->PMU_LDO_LPSR_DIG |= (ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_REG_EN_MASK);
        SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        /* Clear BYPASS */
        base->PMU_LDO_LPSR_DIG &= ~ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_BYPASS_MODE_MASK;
        SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

        /* Disable tracking */
        base->PMU_LDO_LPSR_DIG &= ~ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_TRACKING_MODE_MASK;
    }
}

/*!
 * @brief Gets the default configuration of LPSR DIG LDO.
 *
 * @param config Pointer to the structure pmu_static_lpsr_dig_config_t. Please refer to @ref
 * pmu_static_lpsr_dig_config_t.
 */
void PMU_StaticGetLpsrDigLdoDefaultConfig(pmu_static_lpsr_dig_config_t *config)
{
    assert(config != NULL);

    (void)memset(config, 0, sizeof(*config));

    config->voltageStepTime = kPMU_LpsrDigVoltageStepInc50us;
    config->targetVoltage   = kPMU_LpsrDigTargetStableVoltage1P0V;
}

/*!
 * @brief Initialize the LPSR DIG LDO in static mode.
 *
 * @param base ANADIG_LDO_SNVS peripheral base address.
 * @param config Pointer to the structure pmu_static_lpsr_dig_config_t. Please refer to @ref
 * pmu_static_lpsr_dig_config_t.
 */
void PMU_StaticLpsrDigLdoInit(ANADIG_LDO_SNVS_Type *base, const pmu_static_lpsr_dig_config_t *config)
{
    assert(config != NULL);

    uint32_t temp32 = base->PMU_LDO_LPSR_DIG;

    temp32 &= ~ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_VOLTAGE_SELECT_MASK;
    temp32 |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_VOLTAGE_SELECT(config->targetVoltage);
    base->PMU_LDO_LPSR_DIG = temp32;

    temp32 = base->PMU_LDO_LPSR_DIG_2;
    temp32 &= ~ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_2_VOLTAGE_STEP_INC_MASK;
    temp32 |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_2_VOLTAGE_STEP_INC(config->voltageStepTime);
    base->PMU_LDO_LPSR_DIG_2 = temp32;

    /* Enable LPSR DIG LDO. */
    base->PMU_LDO_LPSR_DIG |= ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_REG_EN_MASK;
    SDK_DelayAtLeastUs(125U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    PMU_POWER_DETECT_CTRL_REGISTER |= ANADIG_PMU_PMU_POWER_DETECT_CTRL_CKGB_LPSR1P0_MASK;
}

/*!
 * @brief Disable the LPSR DIG LDO.
 *
 * @param base ANADIG_LDO_SNVS peripheral base address.
 */
void PMU_StaticLpsrDigLdoDeinit(ANADIG_LDO_SNVS_Type *base)
{
    PMU_POWER_DETECT_CTRL_REGISTER &= ~ANADIG_PMU_PMU_POWER_DETECT_CTRL_CKGB_LPSR1P0_MASK;
    base->PMU_LDO_LPSR_DIG &= ~ANADIG_LDO_SNVS_PMU_LDO_LPSR_DIG_REG_EN_MASK;
}

/*!
 * brief Sets the voltage step of LPSR DIG LDO in the certain setpoint during GPC mode.
 *
 * note The function provides the feature to set the voltage step to the different setpoints.
 *
 * param setpointMap The map of setpoints should be the OR'ed Value of _pmu_setpoint_map.
 * param voltageStep The voltage step to be set.
 */
void PMU_GPCSetLpsrDigLdoTargetVoltage(uint32_t setpointMap, pmu_lpsr_dig_target_output_voltage_t voltageValue)
{
    uint32_t regValue                   = 0UL;
    const uint32_t lpsrDigTrgRegArray[] = PMU_LPSR_DIG_TRG_REGISTERS;
    uint8_t regIndex;
    uint8_t temp8;
    uint32_t i;

    for (regIndex = 0U; regIndex < ARRAY_SIZE(lpsrDigTrgRegArray); regIndex++)
    {
        temp8 = (((uint8_t)(setpointMap >> (PMU_LDO_LPSR_DIG_TRG_SPX_REG_SETPOINT_COUNTS * regIndex))) & 0xFU);
        if (temp8 != 0UL)
        {
            regValue = (*(volatile uint32_t *)lpsrDigTrgRegArray[regIndex]);
            for (i = 0U; i < PMU_LDO_LPSR_DIG_TRG_SPX_REG_SETPOINT_COUNTS; i++)
            {
                if (((temp8 >> (1U * i)) & 0x1U) != 0U)
                {
                    regValue &= ~(0xFFUL << (PMU_LDO_LPSR_DIG_TRG_SPX_VOLTAGE_SETPOINTX_BIT_WIDTH * i));
                    regValue |= (uint32_t)voltageValue << (PMU_LDO_LPSR_DIG_TRG_SPX_VOLTAGE_SETPOINTX_BIT_WIDTH * i);
                }
            }
            (*(volatile uint32_t *)lpsrDigTrgRegArray[regIndex]) = regValue;
        }
    }
}

/*!
 * brief Gets the default config of the SNVS DIG LDO.
 *
 * The default values are:
 *  code
 *      config->mode                   = kPMU_LowPowerMode;
 *      config->chargePumpCurrent      = kPMU_SnvsDigChargePump12P5nA;
 *      config->dischargeResistorValue = kPMU_SnvsDigDischargeResistor15K;
 *      config->trimValue              = 0U;
 *      config->enablePullDown         = true;
 *      config->enableLdoStable        = false;
 *  endcode
 *
 * param config Pointer to the structure pmu_snvs_dig_config_t. Please refer to pmu_snvs_dig_config_t.
 */
void PMU_GetSnvsDigLdoDefaultConfig(pmu_snvs_dig_config_t *config)
{
    assert(config != NULL);

    (void)memset(config, 0, sizeof(*config));

    config->mode                   = kPMU_LowPowerMode;
    config->chargePumpCurrent      = kPMU_SnvsDigChargePump12P5nA;
    config->dischargeResistorValue = kPMU_SnvsDigDischargeResistor15K;
    config->trimValue              = 0U;
    config->enablePullDown         = true;
    config->enableLdoStable        = false;
}

/*!
 * brief Initialize the SNVS DIG LDO.
 *
 * param base LDO SNVS DIG peripheral base address.
 * param mode Used to control LDO power mode, please refer to pmu_ldo_operate_mode_t.
 */
void PMU_SnvsDigLdoInit(ANADIG_LDO_SNVS_DIG_Type *base, pmu_ldo_operate_mode_t mode)
{
    uint32_t temp32 = base->PMU_LDO_SNVS_DIG;

    temp32 &= ~(ANADIG_LDO_SNVS_DIG_PMU_LDO_SNVS_DIG_REG_LP_EN_MASK);

    temp32 |= (ANADIG_LDO_SNVS_DIG_PMU_LDO_SNVS_DIG_REG_LP_EN(mode) | ANADIG_LDO_SNVS_DIG_PMU_LDO_SNVS_DIG_REG_EN_MASK);

    base->PMU_LDO_SNVS_DIG = temp32;
}

/*!
 * brief  Controls the ON/OFF of the selected LDO in the certain setpoints with GPC mode.
 *
 * param name The name of the selected ldo. Please see the enumeration pmu_ldo_name_t for details.
 * param setpointMap The map of setpoints should be the OR'ed Value of @ref _pmu_setpoint_map, 1b'1
 * means enable specific ldo in that setpoint.
 * For example, the code PMU_GPCEnableLdo(kPMU_PllLdo, 0x1U) means enable PLL LDO in setpoint 0, disable
 * PLL LDO in other setpoint.
 */
void PMU_GPCEnableLdo(pmu_ldo_name_t name, uint32_t setpointMap)
{
    assert(name != kPMU_SnvsDigLdo);

    uint32_t ldoEnableRegArray[] = PMU_LDO_ENABLE_SETPOINT_REGISTERS;

    (*(volatile uint32_t *)ldoEnableRegArray[(uint8_t)name]) = ~setpointMap;
}

/*!
 * brief Sets the operating mode of the selected LDO in the certain setpoints with GPC mode.
 *
 * param name The name of the selected ldo. Please see the enumeration pmu_ldo_name_t for details.
 * param setpointMap The map of setpoints should be the OR'ed Value of _pmu_setpoint_map.
 * param mode The operating mode of the selected ldo. Please refer to the enumeration pmu_ldo_operate_mode_t for
 * details.
 */
void PMU_GPCSetLdoOperateMode(pmu_ldo_name_t name, uint32_t setpointMap, pmu_ldo_operate_mode_t mode)
{
    assert(name > kPMU_PllLdo);
    assert(name < kPMU_SnvsDigLdo);

    uint32_t ldoLpModeRegArray[] = PMU_LDO_LP_MODE_EN_SETPOINT_REGISTERS;

    if (mode == kPMU_LowPowerMode)
    {
        (*(volatile uint32_t *)ldoLpModeRegArray[(uint8_t)name]) &= ~setpointMap;
    }
    else
    {
        (*(volatile uint32_t *)ldoLpModeRegArray[(uint8_t)name]) |= setpointMap;
    }
}

/*!
 * brief Controls the ON/OFF of the selected LDOs' Tracking mode in the certain setpoints with GPC mode.
 *
 * param name The name of the selected ldo. Please see the enumeration pmu_ldo_name_t for details.
 * param setpointMap The map of setpoints that the LDO tracking mode will be enabled in those setpoints, this value
 * should be the OR'ed Value of @ref _pmu_setpoint_map.
 */
void PMU_GPCEnableLdoTrackingMode(pmu_ldo_name_t name, uint32_t setpointMap)
{
    assert(name > kPMU_PllLdo);
    assert(name < kPMU_SnvsDigLdo);

    uint32_t ldoTrackingEnableRegArray[] = PMU_LDO_TRACKING_EN_SETPOINT_REGISTERS;

    (*(volatile uint32_t *)ldoTrackingEnableRegArray[(uint8_t)name]) = setpointMap;
}

/*!
 * brief Controls the ON/OFF of the selected LDOs' Bypass mode in the certain setpoints with GPC mode.
 *
 * param name The name of the selected ldo. Please see the enumeration pmu_ldo_name_t for details.
 * param setpointMap The map of setpoints that the LDO bypass mode will be enabled in those setpoints, this value
 * should be the OR'ed Value of @ref _pmu_setpoint_map.
 */
void PMU_GPCEnableLdoBypassMode(pmu_ldo_name_t name, uint32_t setpointMap)
{
    assert(name > kPMU_PllLdo);
    assert(name < kPMU_SnvsDigLdo);

    uint32_t ldoBypassEnableRegArray[] = PMU_LDO_BYPASS_EN_SETPOINT_REGISTERS;

    (*(volatile uint32_t *)ldoBypassEnableRegArray[(uint8_t)name]) = setpointMap;
}

/*!
 * brief When STBY assert, enable/disable the selected LDO enter it's Low power mode.
 *
 * param name The name of the selected ldo. Please see the enumeration pmu_ldo_name_t for details.
 * param setpointMap The map of setpoints that the LDO low power mode will be enabled in those setpoints if STBY
 * assert, this value should be the OR'ed Value of @ref _pmu_setpoint_map.
 */
void PMU_GPCEnableLdoStandbyMode(pmu_ldo_name_t name, uint32_t setpointMap)
{
    assert(name != kPMU_SnvsDigLdo);

    uint32_t ldoStandbyEnableRegArray[] = PMU_LDO_STBY_EN_REGISTERS;

    (*(volatile uint32_t *)ldoStandbyEnableRegArray[(uint8_t)name]) = setpointMap;
}

/*!
 * brief Selects the control mode of the Bandgap Reference.
 *
 * param base PMU peripheral base address.
 * param mode The control mode of the Bandgap Reference. Please refer to pmu_control_mode_t.
 */
void PMU_SetBandgapControlMode(ANADIG_PMU_Type *base, pmu_control_mode_t mode)
{
    if (mode == kPMU_StaticMode)
    {
        base->PMU_REF_CTRL &= ~ANADIG_PMU_PMU_REF_CTRL_REF_CONTROL_MODE_MASK;
    }
    else
    {
        base->PMU_REF_CTRL |= ANADIG_PMU_PMU_REF_CTRL_REF_CONTROL_MODE_MASK;
    }
}

/*!
 * brief Switches the Bandgap from Static/Software Mode to GPC/Hardware Mode.
 *
 * param base PMU peripheral base address.
 */
void PMU_SwitchBandgapToGPCMode(ANADIG_PMU_Type *base)
{
    if ((base->BANDGAP_ENABLE_SP & ANADIG_PMU_BANDGAP_ENABLE_SP_ON_OFF_SETPOINT0_MASK) == 0UL)
    {
        base->PMU_REF_CTRL &= ~ANADIG_PMU_PMU_REF_CTRL_REF_ENABLE_MASK;
    }
    else
    {
        base->PMU_REF_CTRL |= ANADIG_PMU_PMU_REF_CTRL_REF_ENABLE_MASK;
    }
}

/*!
 * brief Disables Bandgap self bias for best noise performance.
 *
 * This function waits for the bandgap to be stable and disables the bandgap self bias.
 * After being powered up, it needs to wait for the bandgap stable to be stable and then disable Bandgap
 * Self bias for best noise performance.
 */
void PMU_DisableBandgapSelfBiasAfterPowerUp(void)
{
    uint32_t temp32;
    uint32_t regValue;

    /* Wait Bandgap stable. */
    do
    {
        regValue = ANATOP_AI_Read(kAI_Itf_Bandgap, kAI_BANDGAP_STAT0);
    } while ((regValue & AI_BANDGAP_STAT0_REFTOP_VBGUP_MASK) == 0UL);

    /* Disable Bandgap self bias for best noise performance. */
    temp32 = ANATOP_AI_Read(kAI_Itf_Bandgap, kAI_BANDGAP_CTRL0);
    temp32 |= AI_BANDGAP_CTRL0_REFTOP_SELFBIASOFF_MASK;
    ANATOP_AI_Write(kAI_Itf_Bandgap, kAI_BANDGAP_CTRL0, temp32);
}

/*!
 * brief Enables Bandgap self bias before power down.
 *
 * This function will enable Bandgap self bias feature before powering down or there
 * will be risk of Bandgap not starting properly.
 */
void PMU_EnableBandgapSelfBiasBeforePowerDown(void)
{
    uint32_t temp32;

    temp32 = ANATOP_AI_Read(kAI_Itf_Bandgap, kAI_BANDGAP_CTRL0);
    temp32 &= ~AI_BANDGAP_CTRL0_REFTOP_SELFBIASOFF_MASK;
    ANATOP_AI_Write(kAI_Itf_Bandgap, kAI_BANDGAP_CTRL0, temp32);
}

/*!
 * brief Init Bandgap.
 *
 * param config. Pointer to the structure pmu_static_bandgap_config_t. Please refer to pmu_static_bandgap_config_t.
 */
void PMU_StaticBandgapInit(const pmu_static_bandgap_config_t *config)
{
    assert(config != NULL);

    uint32_t temp32;

    temp32 = ANATOP_AI_Read(kAI_Itf_Bandgap, kAI_BANDGAP_CTRL0);
    temp32 &= ~(AI_BANDGAP_CTRL0_REFTOP_PWD_MASK | AI_BANDGAP_CTRL0_REFTOP_LINREGREF_PWD_MASK |
                AI_BANDGAP_CTRL0_REFTOP_PWDVBGUP_MASK | AI_BANDGAP_CTRL0_REFTOP_LOWPOWER_MASK |
                AI_BANDGAP_CTRL0_REFTOP_VBGADJ_MASK | AI_BANDGAP_CTRL0_REFTOP_IBZTCADJ_MASK);
    temp32 |= ((uint32_t)(config->powerDownOption) &
               (AI_BANDGAP_CTRL0_REFTOP_PWD_MASK | AI_BANDGAP_CTRL0_REFTOP_LINREGREF_PWD_MASK |
                AI_BANDGAP_CTRL0_REFTOP_PWDVBGUP_MASK));
    temp32 |= AI_BANDGAP_CTRL0_REFTOP_LOWPOWER(config->enableLowPowerMode);
    temp32 |= AI_BANDGAP_CTRL0_REFTOP_VBGADJ(config->outputVoltage);
    temp32 |= AI_BANDGAP_CTRL0_REFTOP_IBZTCADJ(config->outputCurrent);

    ANATOP_AI_Write(kAI_Itf_Bandgap, kAI_BANDGAP_CTRL0, temp32);
}

/*!
 * brief Configures Well bias, such as power source, clock source and so on.
 *
 * param base PMU peripheral base address.
 * param config Pointer to the pmu_well_bias_config_t structure.
 */
void PMU_WellBiasInit(ANADIG_PMU_Type *base, const pmu_well_bias_config_t *config)
{
    assert(config != NULL);

    uint32_t tmp32;

    tmp32 = base->PMU_BIAS_CTRL;
    tmp32 &= ~(ANADIG_PMU_PMU_BIAS_CTRL_WB_CFG_1P8_MASK | ANADIG_PMU_PMU_BIAS_CTRL_WB_VDD_SEL_1P8_MASK);
    tmp32 |= ((uint32_t)config->wellBiasOption.wellBiasData &
              (ANADIG_PMU_PMU_BIAS_CTRL_WB_CFG_1P8_MASK | ANADIG_PMU_PMU_BIAS_CTRL_WB_VDD_SEL_1P8_MASK));
    base->PMU_BIAS_CTRL = tmp32;

    tmp32 = base->PMU_BIAS_CTRL2;
    tmp32 &= ~ANADIG_PMU_PMU_BIAS_CTRL2_WB_ADJ_1P8_MASK;
    tmp32 |= ANADIG_PMU_PMU_BIAS_CTRL2_WB_ADJ_1P8(config->adjustment);
    base->PMU_BIAS_CTRL2 = tmp32;
}

/*!
 * brief Enables/disables the selected body bias.
 *
 * param base PMU peripheral base address.
 * param name The name of the body bias to be turned on/off, please refer to pmu_body_bias_name_t.
 * param enable Used to turn on/off the specific body bias.
 *              - \b true Enable the selected body bias.
 *              - \b false Disable the selected body bias.
 */
void PMU_GetWellBiasDefaultConfig(pmu_well_bias_config_t *config)
{
    assert(config != NULL);

    (void)memset(config, 0, sizeof(*config));

    config->wellBiasOption.wellBiasData = 0U;
    config->adjustment                  = kPMU_Cref0fFCspl0fFDeltaC0fF;
}

/*!
 * brief Selects the control mode of the Body Bias.
 *
 * param base PMU peripheral base address.
 * param name The name of the body bias. Please refer to pmu_body_bias_name_t.
 * param mode The control mode of the Body Bias. Please refer to pmu_control_mode_t.
 */
void PMU_SetBodyBiasControlMode(ANADIG_PMU_Type *base, pmu_body_bias_name_t name, pmu_control_mode_t mode)
{
    uint32_t temp32;

    switch (name)
    {
#if (defined(PMU_HAS_FBB) && PMU_HAS_FBB)
        case kPMU_FBB_CM7:
        {
            temp32 = base->PMU_BIAS_CTRL2;
            temp32 &= ~ANADIG_PMU_PMU_BIAS_CTRL2_FBB_M7_CONTROL_MODE_MASK;
            temp32 |= ANADIG_PMU_PMU_BIAS_CTRL2_FBB_M7_CONTROL_MODE(mode);
            base->PMU_BIAS_CTRL2 = temp32;
            break;
        }
#endif /* PMU_HAS_FBB */
        case kPMU_RBB_SOC:
        {
            temp32 = base->PMU_BIAS_CTRL2;
            temp32 &= ~ANADIG_PMU_PMU_BIAS_CTRL2_RBB_SOC_CONTROL_MODE_MASK;
            temp32 |= ANADIG_PMU_PMU_BIAS_CTRL2_RBB_SOC_CONTROL_MODE(mode);
            base->PMU_BIAS_CTRL2 = temp32;
            break;
        }
        case kPMU_RBB_LPSR:
        {
            temp32 = base->PMU_BIAS_CTRL2;
            temp32 &= ~ANADIG_PMU_PMU_BIAS_CTRL2_RBB_LPSR_CONTROL_MODE_MASK;
            temp32 |= ANADIG_PMU_PMU_BIAS_CTRL2_RBB_LPSR_CONTROL_MODE(mode);
            base->PMU_BIAS_CTRL2 = temp32;
            break;
        }
        default:
            /* This branch should never be hit. */
            break;
    }
}

/*!
 * brief Enables/disables the selected body bias.
 *
 * param base PMU peripheral base address.
 * param name The name of the body bias to be turned on/off, please refer to pmu_body_bias_name_t.
 * param enable Used to turn on/off the specific body bias.
 *              - \b true Enable the selected body bias.
 *              - \b false Disable the selected body bias.
 */
void PMU_EnableBodyBias(ANADIG_PMU_Type *base, pmu_body_bias_name_t name, bool enable)
{
    uint32_t tmp32;

    if (enable)
    {
        switch (name)
        {
#if (defined(PMU_HAS_FBB) && PMU_HAS_FBB)
            case kPMU_FBB_CM7:
            {
                tmp32 = base->PMU_BIAS_CTRL;
                tmp32 &= ~PMU_BIAS_CTRL_WB_CFG_1P8_WELL_SELECT_MASK;
                tmp32 |= PMU_BIAS_CTRL_WB_CFG_1P8_VOLTAGE_THRESHOLD_MASK;
                base->PMU_BIAS_CTRL = tmp32;

                tmp32 = base->PMU_BIAS_CTRL2;
                tmp32 &= ~(ANADIG_PMU_PMU_BIAS_CTRL2_WB_PWR_SW_EN_1P8_MASK);
                tmp32 |= ANADIG_PMU_PMU_BIAS_CTRL2_WB_PWR_SW_EN_1P8(1U) | ANADIG_PMU_PMU_BIAS_CTRL2_WB_EN_MASK;
                base->PMU_BIAS_CTRL2 = tmp32;

                while ((base->PMU_BIAS_CTRL2 & ANADIG_PMU_PMU_BIAS_CTRL2_WB_OK_MASK) !=
                       ANADIG_PMU_PMU_BIAS_CTRL2_WB_OK_MASK)
                {
                }
                break;
            }
#endif /* PMU_HAS_FBB */
            case kPMU_RBB_SOC:
            {
                tmp32 = base->PMU_BIAS_CTRL;
                tmp32 &= ~(PMU_BIAS_CTRL_WB_CFG_1P8_WELL_SELECT_MASK | PMU_BIAS_CTRL_WB_CFG_1P8_VOLTAGE_THRESHOLD_MASK);
                base->PMU_BIAS_CTRL = tmp32;

                tmp32 = base->PMU_BIAS_CTRL2;
                tmp32 &= ~(ANADIG_PMU_PMU_BIAS_CTRL2_WB_PWR_SW_EN_1P8_MASK);
                tmp32 |= ANADIG_PMU_PMU_BIAS_CTRL2_WB_PWR_SW_EN_1P8(2U) | ANADIG_PMU_PMU_BIAS_CTRL2_WB_EN_MASK;
                base->PMU_BIAS_CTRL2 = tmp32;
                while ((base->PMU_BIAS_CTRL2 & ANADIG_PMU_PMU_BIAS_CTRL2_WB_OK_MASK) !=
                       ANADIG_PMU_PMU_BIAS_CTRL2_WB_OK_MASK)
                {
                }
                break;
            }
            case kPMU_RBB_LPSR:
            {
                tmp32 = base->PMU_BIAS_CTRL;
                tmp32 &= ~(PMU_BIAS_CTRL_WB_CFG_1P8_WELL_SELECT_MASK | PMU_BIAS_CTRL_WB_CFG_1P8_VOLTAGE_THRESHOLD_MASK);
                base->PMU_BIAS_CTRL = tmp32;

                tmp32 = base->PMU_BIAS_CTRL2;
                tmp32 &= ~(ANADIG_PMU_PMU_BIAS_CTRL2_WB_PWR_SW_EN_1P8_MASK);
                tmp32 |= ANADIG_PMU_PMU_BIAS_CTRL2_WB_PWR_SW_EN_1P8(4U) | ANADIG_PMU_PMU_BIAS_CTRL2_WB_EN_MASK;
                base->PMU_BIAS_CTRL2 = tmp32;
                while ((base->PMU_BIAS_CTRL2 & ANADIG_PMU_PMU_BIAS_CTRL2_WB_OK_MASK) !=
                       ANADIG_PMU_PMU_BIAS_CTRL2_WB_OK_MASK)
                {
                }
                break;
            }
            default:
                /* This branch should never be hit. */
                break;
        }
    }
    else
    {
        base->PMU_BIAS_CTRL2 &=
            ~(ANADIG_PMU_PMU_BIAS_CTRL2_WB_PWR_SW_EN_1P8_MASK | ANADIG_PMU_PMU_BIAS_CTRL2_WB_EN_MASK);
    }
}

/*!
 * brief  Controls the ON/OFF of the selected body bias in the certain setpoints with GPC mode.
 *
 * param name The name of the selected body bias. Please see the enumeration pmu_body_bias_name_t for details.
 * param setpointMap The map of setpoints that the specific body bias will be enabled in those setpoints, this value
 * should be the OR'ed Value of _pmu_setpoint_map.
 */
void PMU_GPCEnableBodyBias(pmu_body_bias_name_t name, uint32_t setpointMap)
{
    uint32_t bodyBiasEnableRegArray[] = PMU_BODY_BIAS_ENABLE_REGISTERS;

    (*(volatile uint32_t *)bodyBiasEnableRegArray[(uint8_t)name]) = ~setpointMap;
}

/*!
 * brief Controls the ON/OFF of the selected Body Bias' Wbias power switch in certain setpoints with GPC mode.
 *
 * param name The name of the selected body bias. Please see the enumeration pmu_body_bias_name_t for details.
 * param setpointMap The map of setpoints that the specific body bias's wbias power switch will be turn on in those
 * setpoints, this value should be the OR'ed Value of _pmu_setpoint_map.
 */
void PMU_GPCEnableBodyBiasStandbyMode(pmu_body_bias_name_t name, uint32_t setpointMap)
{
    uint32_t BBStandbyEnableRegArray[] = PMU_BODY_BIAS_STBY_EN_REGISTERS;

    (*(volatile uint32_t *)BBStandbyEnableRegArray[(uint8_t)name]) = setpointMap;
}

/*!
 * brief Gets the default config of body bias in GPC mode.
 *
 * param config Pointer to the structure pmu_gpc_body_bias_config_t.
 */
void PMU_GPCGetBodyBiasDefaultConfig(pmu_gpc_body_bias_config_t *config)
{
    assert(config != NULL);

    config->PWELLRegulatorSize = 1U;
    config->NWELLRegulatorSize = 1U;
    config->oscillatorSize     = 7U;
    config->regulatorStrength  = 5U;
}

/*!
 * brief Sets the config of the selected Body Bias in GPC mode.
 *
 * param name The name of the selected body bias. Please see the enumeration pmu_body_bias_name_t for details.
 * param config Pointer to the structure pmu_gpc_body_bias_config_t.
 */
void PMU_GPCSetBodyBiasConfig(pmu_body_bias_name_t name, const pmu_gpc_body_bias_config_t *config)
{
    assert(config != NULL);

    uint32_t bodyBiasConfigRegArray[] = PMU_BODY_BIAS_CONFIGURE_REGISTERS;
    uint32_t temp32;

    temp32 = (*(volatile uint32_t *)bodyBiasConfigRegArray[(uint8_t)name]);
    temp32 &=
        (ANADIG_PMU_RBB_SOC_CONFIGURE_WB_CFG_PW_MASK | ANADIG_PMU_RBB_SOC_CONFIGURE_WB_CFG_NW_MASK |
         ANADIG_PMU_RBB_SOC_CONFIGURE_OSCILLATOR_BITS_MASK | ANADIG_PMU_RBB_SOC_CONFIGURE_REGULATOR_STRENGTH_MASK);
    temp32 |= ANADIG_PMU_RBB_SOC_CONFIGURE_WB_CFG_PW(config->PWELLRegulatorSize) |
              ANADIG_PMU_RBB_SOC_CONFIGURE_WB_CFG_NW(config->NWELLRegulatorSize) |
              ANADIG_PMU_RBB_SOC_CONFIGURE_OSCILLATOR_BITS(config->oscillatorSize) |
              ANADIG_PMU_RBB_SOC_CONFIGURE_REGULATOR_STRENGTH(config->regulatorStrength);
    (*(volatile uint32_t *)bodyBiasConfigRegArray[(uint8_t)name]) = temp32;
}
