/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_tsi_v6.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.tsi_v6"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of TSI clock name. */
const clock_ip_name_t s_tsiClock[] = TSI_CLOCKS;
/* Array of TSI peripheral base address. */
TSI_Type *const s_tsiBases[] = TSI_BASE_PTRS;
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Get the TSI instance from peripheral base address.
 *
 * param base TSI peripheral base address.
 * return TSI instance.
 */
uint32_t TSI_GetInstance(TSI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_tsiBases); instance++)
    {
        if (s_tsiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_tsiBases));

    return instance;
}

/*!
 * brief Initialize hardware to Self-cap mode.
 *
 * details Initialize the peripheral to the targeted state specified by parameter config,
 *          such as sets sensitivity adjustment, current settings.
 * param  base    TSI peripheral base address.
 * param  config  Pointer to TSI self-cap configuration structure.
 * return none
 */
void TSI_InitSelfCapMode(TSI_Type *base, const tsi_selfCap_config_t *config)
{
    uint32_t temp = 0U;
    assert(config != NULL);

    bool is_module_enabled = false;
    bool is_int_enabled    = false;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = TSI_GetInstance(base);

    /* Enable tsi clock */
    (void)CLOCK_EnableClock(s_tsiClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    if ((bool)(base->GENCS & TSI_GENCS_TSIEN_MASK))
    {
        is_module_enabled = true;
        TSI_EnableModule(base, false);
    }

    /* common settings */
    temp = (base->CONFIG) & ~(TSI_CONFIG_MUTUAL_MODE_MASK | TSI_CONFIG_S_SEN_MASK);
    base->CONFIG =
        temp | (TSI_CONFIG_MUTUAL_MODE(config->commonConfig.mode) | TSI_CONFIG_S_SEN(config->enableSensitivity));

    temp        = (base->GENCS) & ~(TSI_GENCS_SETCLK_MASK);
    base->GENCS = temp | (TSI_GENCS_SETCLK(config->commonConfig.mainClock));

    temp         = (base->SHIELD) & ~(TSI_SHIELD_SHIELD_ENABLE_MASK);
    base->SHIELD = temp | (TSI_SHIELD_SHIELD_ENABLE(config->enableShield));

    base->DATA  = base->DATA & ~(ALL_FLAGS_MASK);
    base->GENCS = (base->GENCS & (~(TSI_GENCS_DVOLT_MASK))) | TSI_GENCS_DVOLT(config->commonConfig.dvolt);
    temp        = (base->SINC) & ~(TSI_SINC_CUTOFF_MASK | TSI_SINC_ORDER_MASK | TSI_SINC_DECIMATION_MASK);
    base->SINC  = temp | (TSI_SINC_CUTOFF(config->commonConfig.cutoff) | TSI_SINC_ORDER(config->commonConfig.order) |
                         TSI_SINC_DECIMATION(config->commonConfig.decimation));

    temp = (base->SSC0) & ~(TSI_SSC0_CHARGE_NUM_MASK | TSI_SSC0_BASE_NOCHARGE_NUM_MASK | TSI_SSC0_PRBS_OUTSEL_MASK |
                            TSI_SSC0_SSC_PRESCALE_NUM_MASK | TSI_SSC0_SSC_MODE_MASK);
    base->SSC0 =
        temp | (TSI_SSC0_PRBS_OUTSEL(config->commonConfig.prbsOutsel) |
                TSI_SSC0_SSC_MODE(config->commonConfig.ssc_mode) | TSI_SSC0_CHARGE_NUM(config->commonConfig.chargeNum) |
                TSI_SSC0_BASE_NOCHARGE_NUM(config->commonConfig.noChargeNum) |
                TSI_SSC0_SSC_PRESCALE_NUM(config->commonConfig.ssc_prescaler));

    /* Self-cap mode specific settings */
    temp = (base->CONFIG) &
           ~(TSI_CONFIG_S_XDN_MASK | TSI_CONFIG_S_CTRIM_MASK | TSI_CONFIG_S_XIN_MASK | TSI_CONFIG_S_XCH_MASK);
    base->CONFIG = temp | (TSI_CONFIG_S_XDN(config->xdn) | TSI_CONFIG_S_CTRIM(config->ctrim) |
                           TSI_CONFIG_S_XIN(config->inputCurrent) | TSI_CONFIG_S_XCH(config->chargeCurrent));

    if (is_module_enabled)
    {
        TSI_EnableModule(base, true);
    }
    if (is_int_enabled)
    {
        TSI_EnableInterrupts(base, (uint32_t)kTSI_GlobalInterruptEnable);
    }
}

/*!
 * brief Initialize hardware to Mutual-cap mode.
 *
 * details Initialize the peripheral to the targeted state specified by parameter config,
 *          such as sets Vref generator setting, sensitivity boost settings, Pmos/Nmos settings.
 * param  base    TSI peripheral base address.
 * param  config  Pointer to TSI mutual-cap configuration structure.
 * return none
 */
void TSI_InitMutualCapMode(TSI_Type *base, const tsi_mutualCap_config_t *config)
{
    uint32_t temp = 0U;
    assert(config != NULL);

    bool is_module_enabled = false;
    bool is_int_enabled    = false;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = TSI_GetInstance(base);

    /* Enable tsi clock */
    (void)CLOCK_EnableClock(s_tsiClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    if ((bool)(base->GENCS & TSI_GENCS_TSIEN_MASK))
    {
        is_module_enabled = true;
        TSI_EnableModule(base, false);
    }

    temp                = (base->CONFIG_MUTUAL) & ~(TSI_CONFIG_MUTUAL_MODE_MASK);
    base->CONFIG_MUTUAL = temp | (TSI_CONFIG_MUTUAL_MODE(config->commonConfig.mode));

    temp        = (base->GENCS) & ~(TSI_GENCS_SETCLK_MASK);
    base->GENCS = temp | (TSI_GENCS_SETCLK(config->commonConfig.mainClock));

    base->DATA  = base->DATA & ~(ALL_FLAGS_MASK);
    base->GENCS = (base->GENCS & (~(TSI_GENCS_DVOLT_MASK))) | TSI_GENCS_DVOLT(config->commonConfig.dvolt);

    temp       = (base->SINC) & ~(TSI_SINC_CUTOFF_MASK | TSI_SINC_ORDER_MASK | TSI_SINC_DECIMATION_MASK);
    base->SINC = temp | (TSI_SINC_CUTOFF(config->commonConfig.cutoff) | TSI_SINC_ORDER(config->commonConfig.order) |
                         TSI_SINC_DECIMATION(config->commonConfig.decimation));

    temp = (base->SSC0) & ~(TSI_SSC0_CHARGE_NUM_MASK | TSI_SSC0_BASE_NOCHARGE_NUM_MASK | TSI_SSC0_PRBS_OUTSEL_MASK |
                            TSI_SSC0_SSC_PRESCALE_NUM_MASK | TSI_SSC0_SSC_MODE_MASK);
    base->SSC0 =
        temp | (TSI_SSC0_PRBS_OUTSEL(config->commonConfig.prbsOutsel) |
                TSI_SSC0_SSC_MODE(config->commonConfig.ssc_mode) | TSI_SSC0_CHARGE_NUM(config->commonConfig.chargeNum) |
                TSI_SSC0_BASE_NOCHARGE_NUM(config->commonConfig.noChargeNum) |
                TSI_SSC0_SSC_PRESCALE_NUM(config->commonConfig.ssc_prescaler));

    temp = (base->CONFIG_MUTUAL) & ~(TSI_CONFIG_MUTUAL_M_PRE_RES_MASK | TSI_CONFIG_MUTUAL_M_PRE_CURRENT_MASK |
                                     TSI_CONFIG_MUTUAL_M_SEN_BOOST_MASK | TSI_CONFIG_MUTUAL_M_PMIRRORL_MASK |
                                     TSI_CONFIG_MUTUAL_M_PMIRRORR_MASK | TSI_CONFIG_MUTUAL_M_NMIRROR_MASK);
    base->CONFIG_MUTUAL =
        temp |
        (TSI_CONFIG_MUTUAL_M_PRE_RES(config->preResistor) | TSI_CONFIG_MUTUAL_M_PRE_CURRENT(config->preCurrent) |
         TSI_CONFIG_MUTUAL_M_SEN_BOOST(config->boostCurrent) | TSI_CONFIG_MUTUAL_M_PMIRRORL(config->pmosLeftCurrent) |
         TSI_CONFIG_MUTUAL_M_PMIRRORR(config->pmosRightCurrent) | TSI_CONFIG_MUTUAL_M_NMIRROR(config->nmosCurrent));

    temp         = (base->SHIELD) & ~(TSI_SHIELD_M_SEN_RES_MASK);
    base->SHIELD = temp | (TSI_SHIELD_M_SEN_RES(config->senseResistor));

    temp      = (base->MUL) & ~(TSI_MUL_M_MODE_MASK);
    base->MUL = temp | (TSI_MUL_M_MODE(config->txDriveMode));

    if (is_module_enabled)
    {
        TSI_EnableModule(base, true);
    }
    if (is_int_enabled)
    {
        TSI_EnableInterrupts(base, (uint32_t)kTSI_EndOfScanInterruptEnable);
    }
}

/*!
 * brief De-initialize hardware.
 *
 * details De-initialize the peripheral to default state.
 *
 * param  base  TSI peripheral base address.
 * return none
 */
void TSI_Deinit(TSI_Type *base)
{
    base->GENCS = 0U;
    base->DATA  = 0U;
    base->TSHD  = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = TSI_GetInstance(base);

    /* Disable tsi clock */
    (void)CLOCK_DisableClock(s_tsiClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Get TSI self-cap mode user configure structure.
 * This interface sets userConfig structure to a default value. The configuration structure only
 * includes the settings for the whole TSI.
 * The user configure is set to a value:
 * code
    userConfig->commonConfig.mainClock     = kTSI_MainClockSlection_0;
    userConfig->commonConfig.mode          = kTSI_SensingModeSlection_Self;
    userConfig->commonConfig.dvolt         = kTSI_DvoltOption_2;
    userConfig->commonConfig.cutoff        = kTSI_SincCutoffDiv_1;
    userConfig->commonConfig.order         = kTSI_SincFilterOrder_1;
    userConfig->commonConfig.decimation    = kTSI_SincDecimationValue_8;
    userConfig->commonConfig.chargeNum     = kTSI_SscChargeNumValue_3;
    userConfig->commonConfig.prbsOutsel    = kTSI_SscPrbsOutsel_2;
    userConfig->commonConfig.noChargeNum   = kTSI_SscNoChargeNumValue_2;
    userConfig->commonConfig.ssc_mode      = kTSI_ssc_prbs_method;
    userConfig->commonConfig.ssc_prescaler = kTSI_ssc_div_by_1;
    userConfig->enableSensitivity          = true;
    userConfig->enableShield               = false;
    userConfig->xdn                        = kTSI_SensitivityXdnOption_1;
    userConfig->ctrim                      = kTSI_SensitivityCtrimOption_7;
    userConfig->inputCurrent               = kTSI_CurrentMultipleInputValue_0;
    userConfig->chargeCurrent              = kTSI_CurrentMultipleChargeValue_1;
   endcode
 *
 * param userConfig Pointer to TSI user configure structure.
 */
void TSI_GetSelfCapModeDefaultConfig(tsi_selfCap_config_t *userConfig)
{
    /* Initializes the configure structure to zero. */
    (void)memset(userConfig, 0, sizeof(*userConfig));

    userConfig->commonConfig.mainClock     = kTSI_MainClockSlection_0;
    userConfig->commonConfig.mode          = kTSI_SensingModeSlection_Self;
    userConfig->commonConfig.dvolt         = kTSI_DvoltOption_2;
    userConfig->commonConfig.cutoff        = kTSI_SincCutoffDiv_1;
    userConfig->commonConfig.order         = kTSI_SincFilterOrder_1;
    userConfig->commonConfig.decimation    = kTSI_SincDecimationValue_8;
    userConfig->commonConfig.chargeNum     = kTSI_SscChargeNumValue_3;
    userConfig->commonConfig.prbsOutsel    = kTSI_SscPrbsOutsel_2;
    userConfig->commonConfig.noChargeNum   = kTSI_SscNoChargeNumValue_2;
    userConfig->commonConfig.ssc_mode      = kTSI_ssc_prbs_method;
    userConfig->commonConfig.ssc_prescaler = kTSI_ssc_div_by_1;
    userConfig->enableSensitivity          = true;
    userConfig->enableShield               = kTSI_shieldAllOff;
    userConfig->xdn                        = kTSI_SensitivityXdnOption_1;
    userConfig->ctrim                      = kTSI_SensitivityCtrimOption_7;
    userConfig->inputCurrent               = kTSI_CurrentMultipleInputValue_0;
    userConfig->chargeCurrent              = kTSI_CurrentMultipleChargeValue_1;
}

/*!
 * brief Get TSI mutual-cap mode default user configure structure.
 * This interface sets userConfig structure to a default value. The configuration structure only
 * includes the settings for the whole TSI.
 * The user configure is set to a value:
 * code
    userConfig->commonConfig.mainClock     = kTSI_MainClockSlection_1;
    userConfig->commonConfig.mode          = kTSI_SensingModeSlection_Mutual;
    userConfig->commonConfig.dvolt         = kTSI_DvoltOption_0;
    userConfig->commonConfig.cutoff        = kTSI_SincCutoffDiv_1;
    userConfig->commonConfig.order         = kTSI_SincFilterOrder_1;
    userConfig->commonConfig.decimation    = kTSI_SincDecimationValue_8;
    userConfig->commonConfig.chargeNum     = kTSI_SscChargeNumValue_4;
    userConfig->commonConfig.prbsOutsel    = kTSI_SscPrbsOutsel_2;
    userConfig->commonConfig.noChargeNum   = kTSI_SscNoChargeNumValue_5;
    userConfig->commonConfig.ssc_mode      = kTSI_ssc_prbs_method;
    userConfig->commonConfig.ssc_prescaler = kTSI_ssc_div_by_1;
    userConfig->preCurrent                 = kTSI_MutualPreCurrent_4uA;
    userConfig->preResistor                = kTSI_MutualPreResistor_4k;
    userConfig->senseResistor              = kTSI_MutualSenseResistor_10k;
    userConfig->boostCurrent               = kTSI_MutualSenseBoostCurrent_0uA;
    userConfig->txDriveMode                = kTSI_MutualTxDriveModeOption_0;
    userConfig->pmosLeftCurrent            = kTSI_MutualPmosCurrentMirrorLeft_32;
    userConfig->pmosRightCurrent           = kTSI_MutualPmosCurrentMirrorRight_1;
    userConfig->enableNmosMirror           = true;
    userConfig->nmosCurrent                = kTSI_MutualNmosCurrentMirror_1;
   endcode
 *
 * param userConfig Pointer to TSI user configure structure.
 */
void TSI_GetMutualCapModeDefaultConfig(tsi_mutualCap_config_t *userConfig)
{
    /* Initializes the configure structure to zero. */
    (void)memset(userConfig, 0, sizeof(*userConfig));

    userConfig->commonConfig.mainClock     = kTSI_MainClockSlection_1;
    userConfig->commonConfig.mode          = kTSI_SensingModeSlection_Mutual;
    userConfig->commonConfig.dvolt         = kTSI_DvoltOption_0;
    userConfig->commonConfig.cutoff        = kTSI_SincCutoffDiv_1;
    userConfig->commonConfig.order         = kTSI_SincFilterOrder_1;
    userConfig->commonConfig.decimation    = kTSI_SincDecimationValue_8;
    userConfig->commonConfig.chargeNum     = kTSI_SscChargeNumValue_4;
    userConfig->commonConfig.prbsOutsel    = kTSI_SscPrbsOutsel_2;
    userConfig->commonConfig.noChargeNum   = kTSI_SscNoChargeNumValue_5;
    userConfig->commonConfig.ssc_mode      = kTSI_ssc_prbs_method;
    userConfig->commonConfig.ssc_prescaler = kTSI_ssc_div_by_1;
    userConfig->preCurrent                 = kTSI_MutualPreCurrent_4uA;
    userConfig->preResistor                = kTSI_MutualPreResistor_4k;
    userConfig->senseResistor              = kTSI_MutualSenseResistor_10k;
    userConfig->boostCurrent               = kTSI_MutualSenseBoostCurrent_0uA;
    userConfig->txDriveMode                = kTSI_MutualTxDriveModeOption_0;
    userConfig->pmosLeftCurrent            = kTSI_MutualPmosCurrentMirrorLeft_32;
    userConfig->pmosRightCurrent           = kTSI_MutualPmosCurrentMirrorRight_1;
    userConfig->enableNmosMirror           = true;
    userConfig->nmosCurrent                = kTSI_MutualNmosCurrentMirror_1;
}

/*!
 * brief Hardware base counter value for calibration.
 *
 * details Calibrate the peripheral to fetch the initial counter value of
 *          the enabled channels.
 *          This API is mostly used at initial application setup, it shall be called
 *          after the \ref TSI_Init API, then user can use the calibrated
 *          counter values to setup applications(such as to determine
 *          under which counter value we can confirm a touch event occurs).
 *
 * param   base    TSI peripheral base address.
 * param   calBuff Data buffer that store the calibrated counter value.
 * return  none
 * note    This API is mainly used for self-cap mode;
 * note    The calibration work in mutual-cap mode shall be done in applications due to different board layout.
 *
 */
void TSI_SelfCapCalibrate(TSI_Type *base, tsi_calibration_data_t *calBuff)
{
    assert(calBuff != NULL);

    uint8_t i           = 0U;
    bool is_int_enabled = false;
    /* Enable software trigger scan */
    TSI_EnableHardwareTriggerScan(base, false);

    if ((bool)(base->GENCS & TSI_GENCS_ESOR_MASK))
    {
        is_int_enabled = true;
        TSI_DisableInterrupts(base, (uint32_t)kTSI_EndOfScanInterruptEnable);
    }
    for (i = 0U; i < (uint8_t)FSL_FEATURE_TSI_CHANNEL_COUNT; i++)
    {
        TSI_SetSelfCapMeasuredChannel(base, i);
        TSI_StartSoftwareTrigger(base);
        while (!(bool)((TSI_GetStatusFlags(base) & (uint32_t)kTSI_EndOfScanFlag)))
        {
        }
        calBuff->calibratedData[i] = TSI_GetCounter(base);
        TSI_ClearStatusFlags(base, (uint32_t)kTSI_EndOfScanFlag);
    }
    if (is_int_enabled)
    {
        TSI_EnableInterrupts(base, (uint32_t)kTSI_EndOfScanInterruptEnable);
    }
}

/*!
 * brief Enables TSI interrupt requests.
 * param base TSI peripheral base address.
 * param mask interrupt source
 *     The parameter can be combination of the following source if defined:
 *     arg kTSI_GlobalInterruptEnable
 *     arg kTSI_EndOfScanInterruptEnable
 *     arg kTSI_OutOfRangeInterruptEnable
 */
void TSI_EnableInterrupts(TSI_Type *base, uint32_t mask)
{
    uint32_t regValue = base->GENCS;

    if ((bool)(mask & (uint32_t)kTSI_OutOfRangeInterruptEnable))
    {
        regValue |= TSI_GENCS_OUTRG_EN_MASK;
    }
    if ((bool)(mask & (uint32_t)kTSI_EndOfScanInterruptEnable))
    {
        regValue |= TSI_GENCS_ESOR_MASK;
    }
    base->DATA &= ~(ALL_FLAGS_MASK);
    base->GENCS = regValue; /* write value to register */
}

/*!
 * brief Disables TSI interrupt requests.
 * param base TSI peripheral base address.
 * param mask interrupt source
 *     The parameter can be combination of the following source if defined:
 *     arg kTSI_GlobalInterruptEnable
 *     arg kTSI_EndOfScanInterruptEnable
 *     arg kTSI_OutOfRangeInterruptEnable
 */
void TSI_DisableInterrupts(TSI_Type *base, uint32_t mask)
{
    uint32_t regValue = base->GENCS;

    base->DATA &= ~(ALL_FLAGS_MASK);
    if ((bool)(mask & (uint32_t)kTSI_OutOfRangeInterruptEnable))
    {
        regValue &= (~TSI_GENCS_OUTRG_EN_MASK);
    }
    if ((bool)(mask & (uint32_t)kTSI_EndOfScanInterruptEnable))
    {
        regValue &= (~TSI_GENCS_ESOR_MASK);
    }

    base->GENCS = regValue; /* write value to register */
}

/*!
 * brief Clear interrupt flag.
 *
 * This function clear tsi interrupt flag,
 * automatically cleared flags can not be cleared by this function.
 *
 * param base TSI peripheral base address.
 * param mask The status flags to clear.
 */
void TSI_ClearStatusFlags(TSI_Type *base, uint32_t mask)
{
    uint32_t regValue = base->DATA & (~ALL_FLAGS_MASK);

    if ((bool)(mask & (uint32_t)kTSI_EndOfScanFlag))
    {
        regValue |= TSI_DATA_EOSF_MASK;
    }
    if ((bool)(mask & (uint32_t)kTSI_OutOfRangeFlag))
    {
        regValue |= TSI_DATA_OUTRGF_MASK;
    }
    base->DATA = regValue; /* write value to register */
}
