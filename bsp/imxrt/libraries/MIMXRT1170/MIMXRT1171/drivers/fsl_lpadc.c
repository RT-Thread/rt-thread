/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lpadc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpadc"
#endif

#ifndef ADC_VERID_DIFFEN_MASK
#define ADC_VERID_DIFFEN_MASK (0x2U)
#endif /* ADC_VERID_DIFFEN_MASK */

#ifndef ADC_VERID_NUM_SEC_MASK
#define ADC_VERID_NUM_SEC_MASK (0x800U)
#endif /* ADC_VERID_NUM_SEC_MASK */

#define ADC_CMDL_CHANNEL_MODE_MASK  (0x60U)
#define ADC_CMDL_CHANNEL_MODE_SHIFT (5U)
#define ADC_CMDL_CHANNEL_MODE(x) \
    (((uint32_t)(((uint32_t)(x)) << ADC_CMDL_CHANNEL_MODE_SHIFT)) & ADC_CMDL_CHANNEL_MODE_MASK)

#define GET_ADC_CFG_TPRICTRL_VALUE(val) (((uint32_t)val) & 0x3U)

#if defined(FSL_FEATURE_LPADC_HAS_CFG_TRES) && FSL_FEATURE_LPADC_HAS_CFG_TRES
#define GET_ADC_CFG_TRES_VALUE(val) ((((uint32_t)val) & 0x4U) >> 2U)
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_TRES) && FSL_FEATURE_LPADC_HAS_CFG_TRES */

#if defined(FSL_FEATURE_LPADC_HAS_CFG_TCMDRES) && FSL_FEATURE_LPADC_HAS_CFG_TCMDRES
#define GET_ADC_CFG_TCMDRES_VALUE(val) ((((uint32_t)val) & 0x8U) >> 3U)
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_TCMDRES) && FSL_FEATURE_LPADC_HAS_CFG_TCMDRES */

#if defined(FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI) && FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI
#define GET_ADC_CFG_HPT_EXDI_VALUE(val) ((((uint32_t)val) & 0x10U) >> 4U)
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI) && FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI */

#if defined(LPADC_RSTS)
#define LPADC_RESETS_ARRAY LPADC_RSTS
#elif defined(ADC_RSTS)
#define LPADC_RESETS_ARRAY ADC_RSTS
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for LPADC module.
 *
 * @param base LPADC peripheral base address
 */
static uint32_t LPADC_GetInstance(ADC_Type *base);

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ
/*!
 * @brief Get gain conversion result .
 *
 * @param gainAdjustment gain adjustment value.
 */
static uint32_t LPADC_GetGainConvResult(float gainAdjustment);
#endif /* defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to LPADC bases for each instance. */
static ADC_Type *const s_lpadcBases[] = ADC_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to LPADC clocks for each instance. */
static const clock_ip_name_t s_lpadcClocks[] = LPADC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if defined(LPADC_RESETS_ARRAY)
/* Reset array */
static const reset_ip_name_t s_lpadcResets[] = LPADC_RESETS_ARRAY;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t LPADC_GetInstance(ADC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    /*
     * $Branch Coverage Justification$
     * (instance >= ARRAY_SIZE(s_lpadcBases)) not covered. The peripheral base
     * address is always valid and checked by assert.
     */
    for (instance = 0; instance < ARRAY_SIZE(s_lpadcBases); instance++)
    {
        /*
         * $Branch Coverage Justification$
         * (s_lpadcBases[instance] != base) not covered. The peripheral base
         * address is always valid and checked by assert.
         */
        if (MSDK_REG_SECURE_ADDR(s_lpadcBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lpadcBases));

    return instance;
}

#if (defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ)
/*!
 * brief  Get gain conversion Result .
 *
 * param gainAdjustment gain adjustment value.
 */
static uint32_t LPADC_GetGainConvResult(float gainAdjustment)
{
    uint16_t i        = 0U;
    uint32_t tmp32    = 0U;
    uint32_t GCRa[17] = {0};
    uint32_t GCALR    = 0U;

    for (i = 0x11U; i > 0U; i--)
    {
        tmp32          = (uint32_t)((gainAdjustment) / ((float)(1.0 / (double)(1U << (0x10U - (i - 1U))))));
        GCRa[i - 1U]   = tmp32;
        gainAdjustment = gainAdjustment - ((float)tmp32) * ((float)(1.0 / (double)(1U << (0x10U - (i - 1U)))));
    }
    /* Get GCALR value calculated */
    for (i = 0x11U; i > 0U; i--)
    {
        GCALR += GCRa[i - 1U] * ((uint32_t)(1UL << (uint32_t)(i - 1UL)));
    }

    /* to return GCALR value calculated */
    return GCALR;
}
#endif /* defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ */

/*!
 * brief Initializes the LPADC module.
 *
 * param base   LPADC peripheral base address.
 * param config Pointer to configuration structure. See "lpadc_config_t".
 */
void LPADC_Init(ADC_Type *base, const lpadc_config_t *config)
{
    /* Check if the pointer is available. */
    assert(config != NULL);

    uint32_t tmp32 = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock for LPADC instance. */
    (void)CLOCK_EnableClock(s_lpadcClocks[LPADC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(LPADC_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_lpadcResets[LPADC_GetInstance(base)]);
#endif

    /* Reset the module. */
    LPADC_DoResetConfig(base);
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
    LPADC_DoResetFIFO0(base);
    LPADC_DoResetFIFO1(base);
#else
    LPADC_DoResetFIFO(base);
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */

    /* Disable the module before setting configuration. */
    LPADC_Enable(base, false);

    /* Configure the module generally. */
    if (config->enableInDozeMode)
    {
        base->CTRL &= ~ADC_CTRL_DOZEN_MASK;
    }
    else
    {
        base->CTRL |= ADC_CTRL_DOZEN_MASK;
    }

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS
    /* Set calibration average mode. */
    base->CTRL |= ADC_CTRL_CAL_AVGS(config->conversionAverageMode);
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS */

/* ADCx_CFG. */
#if defined(FSL_FEATURE_LPADC_HAS_CFG_ADCKEN) && FSL_FEATURE_LPADC_HAS_CFG_ADCKEN
    if (config->enableInternalClock)
    {
        tmp32 |= ADC_CFG_ADCKEN_MASK;
    }
#endif /* FSL_FEATURE_LPADC_HAS_CFG_ADCKEN */
#if defined(FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG) && FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG
    if (config->enableVref1LowVoltage)
    {
        tmp32 |= ADC_CFG_VREF1RNG_MASK;
    }
#endif /* FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG */
    if (config->enableAnalogPreliminary)
    {
        tmp32 |= ADC_CFG_PWREN_MASK;
    }
    tmp32 |= (ADC_CFG_PUDLY(config->powerUpDelay)              /* Power up delay. */
              | ADC_CFG_REFSEL(config->referenceVoltageSource) /* Reference voltage. */
#if defined(FSL_FEATURE_LPADC_HAS_CFG_PWRSEL) && (FSL_FEATURE_LPADC_HAS_CFG_PWRSEL == 1U)
              | ADC_CFG_PWRSEL(config->powerLevelMode)         /* Power configuration. */
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_PWRSEL) && (FSL_FEATURE_LPADC_HAS_CFG_PWRSEL == 1U) */
    );

    tmp32 |= ADC_CFG_TPRICTRL(GET_ADC_CFG_TPRICTRL_VALUE(config->triggerPriorityPolicy));

#if (defined(FSL_FEATURE_LPADC_HAS_CFG_TRES) && FSL_FEATURE_LPADC_HAS_CFG_TRES)
    tmp32 |= ADC_CFG_TRES(GET_ADC_CFG_TRES_VALUE(config->triggerPriorityPolicy));
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_TRES) && FSL_FEATURE_LPADC_HAS_CFG_TRES */

#if (defined(FSL_FEATURE_LPADC_HAS_CFG_TCMDRES) && FSL_FEATURE_LPADC_HAS_CFG_TCMDRES)
    tmp32 |= ADC_CFG_TCMDRES(GET_ADC_CFG_TCMDRES_VALUE(config->triggerPriorityPolicy));
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_TCMDRES) && FSL_FEATURE_LPADC_HAS_CFG_TCMDRES */

#if (defined(FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI) && FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI)
    tmp32 |= ADC_CFG_HPT_EXDI(GET_ADC_CFG_HPT_EXDI_VALUE(config->triggerPriorityPolicy));
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI) && FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI */

    base->CFG = tmp32;

    /* ADCx_PAUSE. */
    if (config->enableConvPause)
    {
        base->PAUSE = ADC_PAUSE_PAUSEEN_MASK | ADC_PAUSE_PAUSEDLY(config->convPauseDelay);
    }
    else
    {
        base->PAUSE = 0U;
    }

#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
    /* ADCx_FCTRL0. */
    base->FCTRL[0] = ADC_FCTRL_FWMARK(config->FIFO0Watermark);
    /* ADCx_FCTRL1. */
    base->FCTRL[1] = ADC_FCTRL_FWMARK(config->FIFO1Watermark);
#else
    /* ADCx_FCTRL. */
    base->FCTRL           = ADC_FCTRL_FWMARK(config->FIFOWatermark);
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */

    /* Enable the module after setting configuration. */
    LPADC_Enable(base, true);
}

/*!
 * brief Gets an available pre-defined settings for initial configuration.
 *
 * This function initializes the converter configuration structure with an available settings. The default values are:
 * code
 *   config->enableInDozeMode        = true;
 *   config->conversionAverageMode   = kLPADC_ConversionAverage1;
 *   config->enableAnalogPreliminary = false;
 *   config->powerUpDelay            = 0x80;
 *   config->referenceVoltageSource  = kLPADC_ReferenceVoltageAlt1;
 *   config->powerLevelMode          = kLPADC_PowerLevelAlt1;
 *   config->triggerPriorityPolicy   = kLPADC_TriggerPriorityPreemptImmediately;
 *   config->enableConvPause         = false;
 *   config->convPauseDelay          = 0U;
 *   config->FIFO0Watermark          = 0U;
 *   config->FIFO1Watermark          = 0U;
 *   config->FIFOWatermark           = 0U;
 * endcode
 * param config Pointer to configuration structure.
 */
void LPADC_GetDefaultConfig(lpadc_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

#if defined(FSL_FEATURE_LPADC_HAS_CFG_ADCKEN) && FSL_FEATURE_LPADC_HAS_CFG_ADCKEN
    config->enableInternalClock = false;
#endif /* FSL_FEATURE_LPADC_HAS_CFG_ADCKEN */
#if defined(FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG) && FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG
    config->enableVref1LowVoltage = false;
#endif /* FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG */
    config->enableInDozeMode = true;
#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS
    /* Set calibration average mode. */
    config->conversionAverageMode = kLPADC_ConversionAverage1;
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS */
    config->enableAnalogPreliminary = false;
    config->powerUpDelay            = 0x80;
    config->referenceVoltageSource  = kLPADC_ReferenceVoltageAlt1;
#if defined(FSL_FEATURE_LPADC_HAS_CFG_PWRSEL) && (FSL_FEATURE_LPADC_HAS_CFG_PWRSEL == 1U)
    config->powerLevelMode = kLPADC_PowerLevelAlt1;
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_PWRSEL) && (FSL_FEATURE_LPADC_HAS_CFG_PWRSEL == 1U) */
    config->triggerPriorityPolicy = kLPADC_TriggerPriorityPreemptImmediately;
    config->enableConvPause       = false;
    config->convPauseDelay        = 0U;
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
    config->FIFO0Watermark = 0U;
    config->FIFO1Watermark = 0U;
#else
    config->FIFOWatermark = 0U;
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
}

/*!
 * brief De-initializes the LPADC module.
 *
 * param base LPADC peripheral base address.
 */
void LPADC_Deinit(ADC_Type *base)
{
    /* Disable the module. */
    LPADC_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the clock. */
    (void)CLOCK_DisableClock(s_lpadcClocks[LPADC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
/*!
 * brief Get the result in conversion FIFOn.
 *
 * param base LPADC peripheral base address.
 * param result Pointer to structure variable that keeps the conversion result in conversion FIFOn.
 * param index Result FIFO index.
 *
 * return Status whether FIFOn entry is valid.
 */
bool LPADC_GetConvResult(ADC_Type *base, lpadc_conv_result_t *result, uint8_t index)
{
    assert(result != NULL); /* Check if the input pointer is available. */

    uint32_t tmp32 = 0U;

    tmp32 = base->RESFIFO[index];

    if (ADC_RESFIFO_VALID_MASK != (tmp32 & ADC_RESFIFO_VALID_MASK))
    {
        return false; /* FIFO is empty. Discard any read from RESFIFO. */
    }

    result->commandIdSource = (tmp32 & ADC_RESFIFO_CMDSRC_MASK) >> ADC_RESFIFO_CMDSRC_SHIFT;
    result->loopCountIndex  = (tmp32 & ADC_RESFIFO_LOOPCNT_MASK) >> ADC_RESFIFO_LOOPCNT_SHIFT;
    result->triggerIdSource = (tmp32 & ADC_RESFIFO_TSRC_MASK) >> ADC_RESFIFO_TSRC_SHIFT;
    result->convValue       = (uint16_t)(tmp32 & ADC_RESFIFO_D_MASK);

    return true;
}
/*!
 * brief Get the result in conversion FIFOn using blocking method.
 *
 * param base LPADC peripheral base address.
 * param result Pointer to structure variable that keeps the conversion result in conversion FIFOn.
 * param index Result FIFO index.
 */
void LPADC_GetConvResultBlocking(ADC_Type *base, lpadc_conv_result_t *result, uint8_t index)
{
    assert(result != NULL); /* Check if the input pointer is available. */

    uint32_t tmp32 = 0U;

    tmp32 = base->RESFIFO[index];

    while (ADC_RESFIFO_VALID_MASK != (tmp32 & ADC_RESFIFO_VALID_MASK))
    {
        tmp32 = base->RESFIFO[index];
    }

    result->commandIdSource = (tmp32 & ADC_RESFIFO_CMDSRC_MASK) >> ADC_RESFIFO_CMDSRC_SHIFT;
    result->loopCountIndex  = (tmp32 & ADC_RESFIFO_LOOPCNT_MASK) >> ADC_RESFIFO_LOOPCNT_SHIFT;
    result->triggerIdSource = (tmp32 & ADC_RESFIFO_TSRC_MASK) >> ADC_RESFIFO_TSRC_SHIFT;
    result->convValue       = (uint16_t)(tmp32 & ADC_RESFIFO_D_MASK);
}
#else
/*!
 * brief Get the result in conversion FIFO.
 *
 * param base LPADC peripheral base address.
 * param result Pointer to structure variable that keeps the conversion result in conversion FIFO.
 *
 * return Status whether FIFO entry is valid.
 */
bool LPADC_GetConvResult(ADC_Type *base, lpadc_conv_result_t *result)
{
    assert(result != NULL); /* Check if the input pointer is available. */

    uint32_t tmp32 = 0U;

    tmp32 = base->RESFIFO;

    if (ADC_RESFIFO_VALID_MASK != (tmp32 & ADC_RESFIFO_VALID_MASK))
    {
        return false; /* FIFO is empty. Discard any read from RESFIFO. */
    }

    result->commandIdSource = (tmp32 & ADC_RESFIFO_CMDSRC_MASK) >> ADC_RESFIFO_CMDSRC_SHIFT;
    result->loopCountIndex  = (tmp32 & ADC_RESFIFO_LOOPCNT_MASK) >> ADC_RESFIFO_LOOPCNT_SHIFT;
    result->triggerIdSource = (tmp32 & ADC_RESFIFO_TSRC_MASK) >> ADC_RESFIFO_TSRC_SHIFT;
    result->convValue       = (uint16_t)(tmp32 & ADC_RESFIFO_D_MASK);

    return true;
}
/*!
 * @brief Get the result in conversion FIFO using blocking method.
 *
 * @param base LPADC peripheral base address.
 * @param result Pointer to structure variable that keeps the conversion result in conversion FIFO.
 */
void LPADC_GetConvResultBlocking(ADC_Type *base, lpadc_conv_result_t *result)
{
    assert(result != NULL); /* Check if the input pointer is available. */

    uint32_t tmp32 = 0U;

    tmp32 = base->RESFIFO;

    while (ADC_RESFIFO_VALID_MASK != (tmp32 & ADC_RESFIFO_VALID_MASK))
    {
        tmp32 = base->RESFIFO;
    }

    result->commandIdSource = (tmp32 & ADC_RESFIFO_CMDSRC_MASK) >> ADC_RESFIFO_CMDSRC_SHIFT;
    result->loopCountIndex  = (tmp32 & ADC_RESFIFO_LOOPCNT_MASK) >> ADC_RESFIFO_LOOPCNT_SHIFT;
    result->triggerIdSource = (tmp32 & ADC_RESFIFO_TSRC_MASK) >> ADC_RESFIFO_TSRC_SHIFT;
    result->convValue       = (uint16_t)(tmp32 & ADC_RESFIFO_D_MASK);
}
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */

/*!
 * brief Configure the conversion trigger source.
 *
 * Each programmable trigger can launch the conversion command in command buffer.
 *
 * param base LPADC peripheral base address.
 * param triggerId ID for each trigger. Typically, the available value range is from 0 to 3.
 * param config Pointer to configuration structure. See to #lpadc_conv_trigger_config_t.
 */
void LPADC_SetConvTriggerConfig(ADC_Type *base, uint32_t triggerId, const lpadc_conv_trigger_config_t *config)
{
    assert(triggerId < ADC_TCTRL_COUNT); /* Check if the triggerId is available in this device. */
    assert(config != NULL);              /* Check if the input pointer is available. */

    uint32_t tmp32;

    tmp32 = ADC_TCTRL_TCMD(config->targetCommandId) /* Trigger command select. */
            | ADC_TCTRL_TDLY(config->delayPower)    /* Trigger delay select. */
            | ADC_TCTRL_TPRI(config->priority)      /* Trigger priority setting. */
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
            | ADC_TCTRL_FIFO_SEL_A(config->channelAFIFOSelect)
#if !(defined(FSL_FEATURE_LPADC_HAS_NO_TCTRL_FIFO_SEL_B) && FSL_FEATURE_LPADC_HAS_NO_TCTRL_FIFO_SEL_B)
            | ADC_TCTRL_FIFO_SEL_B(config->channelBFIFOSelect)
#endif /* FSL_FEATURE_LPADC_HAS_NO_TCTRL_FIFO_SEL_B  */
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
        ;
    if (config->enableHardwareTrigger)
    {
        tmp32 |= ADC_TCTRL_HTEN_MASK;
    }

    base->TCTRL[triggerId] = tmp32;
}

/*!
 * brief Gets an available pre-defined settings for trigger's configuration.
 *
 * This function initializes the trigger's configuration structure with an available settings. The default values are:
 * code
 *   config->targetCommandId        = 0U;
 *   config->delayPower             = 0U;
 *   config->priority               = 0U;
 *   config->channelAFIFOSelect     = 0U;
 *   config->channelBFIFOSelect     = 0U;
 *   config->enableHardwareTrigger  = false;
 * endcode
 * param config Pointer to configuration structure.
 */
void LPADC_GetDefaultConvTriggerConfig(lpadc_conv_trigger_config_t *config)
{
    assert(config != NULL); /* Check if the input pointer is available. */

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->targetCommandId = 0U;
    config->delayPower      = 0U;
    config->priority        = 0U;
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
    config->channelAFIFOSelect = 0U;
    config->channelBFIFOSelect = 0U;
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
    config->enableHardwareTrigger = false;
}

/*!
 * brief Configure conversion command.
 *
 * note The number of compare value register on different chips is different, that is mean in some chips, some
 * command buffers do not have the compare functionality.
 *
 * param base LPADC peripheral base address.
 * param commandId ID for command in command buffer. Typically, the available value range is 1 - 15.
 * param config Pointer to configuration structure. See to #lpadc_conv_command_config_t.
 */
void LPADC_SetConvCommandConfig(ADC_Type *base, uint32_t commandId, const lpadc_conv_command_config_t *config)
{
    assert(commandId < (ADC_CMDL_COUNT + 1U)); /* Check if the commandId is available on this device. */
    assert(config != NULL);                    /* Check if the input pointer is available. */

    uint32_t tmp32 = 0;

    commandId--; /* The available command number are 1-15, while the index of register group are 0-14. */

    /* ADCx_CMDL. */
    tmp32 = ADC_CMDL_ADCH(config->channelNumber);        /* Channel number. */
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_ALTB_ADCH) && FSL_FEATURE_LPADC_HAS_CMDL_ALTB_ADCH
    tmp32 |= ADC_CMDL_ALTB_ADCH(config->channelBNumber); /* Alternate channel B number. */
#endif
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_CSCALE) && FSL_FEATURE_LPADC_HAS_CMDL_CSCALE
    tmp32 |= ADC_CMDL_CSCALE(config->sampleScaleMode);        /* Full/Part scale input voltage. */
#endif                                                        /* FSL_FEATURE_LPADC_HAS_CMDL_CSCALE */
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE) && FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE
    tmp32 |= ADC_CMDL_ALTB_CSCALE(config->channelBScaleMode); /* Alternate channel B full/Part scale input voltage. */
#endif                                                        /* FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE */

#if (defined(FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS) && (FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS == 1U))
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_DIFF) && FSL_FEATURE_LPADC_HAS_CMDL_DIFF
    assert(((config->sampleChannelMode >= kLPADC_SampleChannelDiffBothSideAB) &&
            (((base->VERID) & ADC_VERID_DIFFEN_MASK) != 0U)) ||
           (config->sampleChannelMode < kLPADC_SampleChannelDiffBothSideAB));
#endif /* FSL_FEATURE_LPADC_HAS_CMDL_DIFF */

#if defined(FSL_FEATURE_LPADC_HAS_CMDL_CTYPE) && FSL_FEATURE_LPADC_HAS_CMDL_CTYPE
    assert(((config->sampleChannelMode == kLPADC_SampleChannelDiffBothSide) &&
            (((base->VERID) & ADC_VERID_DIFFEN_MASK) != 0U)) ||
           ((config->sampleChannelMode == kLPADC_SampleChannelDualSingleEndBothSide) &&
            (((base->VERID) & ADC_VERID_NUM_SEC_MASK) != 0U)) ||
           (config->sampleChannelMode < kLPADC_SampleChannelDualSingleEndBothSide));
#endif /* FSL_FEATURE_LPADC_HAS_CMDL_CTYPE */
#endif /* FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS */

    tmp32 |= ADC_CMDL_CHANNEL_MODE(config->sampleChannelMode);

#if defined(FSL_FEATURE_LPADC_HAS_CMDL_MODE) && FSL_FEATURE_LPADC_HAS_CMDL_MODE
    tmp32 |= ADC_CMDL_MODE(config->conversionResolutionMode);
#endif /* FSL_FEATURE_LPADC_HAS_CMDL_MODE */

#if defined(FSL_FEATURE_LPADC_HAS_CMDL_ALTBEN) && FSL_FEATURE_LPADC_HAS_CMDL_ALTBEN
    /* Enable alternate channel B.*/
    if (config->enableChannelB)
    {
        tmp32 |= ADC_CMDL_ALTBEN_MASK;
    }
#endif /* FSL_FEATURE_LPADC_HAS_CMDL_ALTBEN */

    base->CMD[commandId].CMDL = tmp32;

    /* ADCx_CMDH. */
    tmp32 = ADC_CMDH_NEXT(config->chainedNextCommandNumber) /* Next Command Select. */
            | ADC_CMDH_LOOP(config->loopCount)              /* Loop Count Select. */
            | ADC_CMDH_AVGS(config->hardwareAverageMode)    /* Hardware Average Select. */
            | ADC_CMDH_STS(config->sampleTimeMode)          /* Sample Time Select. */
            | ADC_CMDH_CMPEN(config->hardwareCompareMode);  /* Hardware compare enable. */
#if (defined(FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG) && FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG)
    if (config->enableWaitTrigger)
    {
        tmp32 |= ADC_CMDH_WAIT_TRIG_MASK; /* Wait trigger enable. */
    }
#endif                                    /* FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG */

    if (config->enableAutoChannelIncrement)
    {
        tmp32 |= ADC_CMDH_LWI_MASK;
    }
    base->CMD[commandId].CMDH = tmp32;

    /* Hardware compare settings.
     * Not all Command Buffers have an associated Compare Value register. The compare function is only available on
     * Command Buffers that have a corresponding Compare Value register. Therefore, assertion judgment needs to be
     * made before setting the CV register.
     */

    if ((kLPADC_HardwareCompareDisabled != config->hardwareCompareMode) && (commandId < ADC_CV_COUNT))
    {
        /* Set CV register. */
        base->CV[commandId] = (ADC_CV_CVH(config->hardwareCompareValueHigh)    /* Compare value high. */
                               | ADC_CV_CVL(config->hardwareCompareValueLow)); /* Compare value low. */
    }
}

/*!
 * brief Gets an available pre-defined settings for conversion command's configuration.
 *
 * This function initializes the conversion command's configuration structure with an available settings. The default
 * values are:
 * code
 *   config->sampleScaleMode            = kLPADC_SampleFullScale;
 *   config->channelBScaleMode          = kLPADC_SampleFullScale;
 *   config->sampleChannelMode          = kLPADC_SampleChannelSingleEndSideA;
 *   config->channelNumber              = 0U;
 *   config->channelBNumber             = 0U;
 *   config->chainedNextCommandNumber   = 0U;
 *   config->enableAutoChannelIncrement = false;
 *   config->loopCount                  = 0U;
 *   config->hardwareAverageMode        = kLPADC_HardwareAverageCount1;
 *   config->sampleTimeMode             = kLPADC_SampleTimeADCK3;
 *   config->hardwareCompareMode        = kLPADC_HardwareCompareDisabled;
 *   config->hardwareCompareValueHigh   = 0U;
 *   config->hardwareCompareValueLow    = 0U;
 *   config->conversionResolutionMode   = kLPADC_ConversionResolutionStandard;
 *   config->enableWaitTrigger          = false;
 *   config->enableChannelB             = false;
 * endcode
 * param config Pointer to configuration structure.
 */
void LPADC_GetDefaultConvCommandConfig(lpadc_conv_command_config_t *config)
{
    assert(config != NULL); /* Check if the input pointer is available. */

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

#if defined(FSL_FEATURE_LPADC_HAS_CMDL_CSCALE) && FSL_FEATURE_LPADC_HAS_CMDL_CSCALE
    config->sampleScaleMode = kLPADC_SampleFullScale;
#endif /* FSL_FEATURE_LPADC_HAS_CMDL_CSCALE */
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE) && FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE
    config->channelBScaleMode = kLPADC_SampleFullScale;
#endif /* FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE */
    config->sampleChannelMode = kLPADC_SampleChannelSingleEndSideA;
    config->channelNumber     = 0U;
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_ALTB_ADCH) && FSL_FEATURE_LPADC_HAS_CMDL_ALTB_ADCH
    config->channelBNumber = 0U;
#endif                                       /* FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE */
    config->chainedNextCommandNumber   = 0U; /* No next command defined. */
    config->enableAutoChannelIncrement = false;
    config->loopCount                  = 0U;
    config->hardwareAverageMode        = kLPADC_HardwareAverageCount1;
    config->sampleTimeMode             = kLPADC_SampleTimeADCK3;
    config->hardwareCompareMode        = kLPADC_HardwareCompareDisabled;
    config->hardwareCompareValueHigh   = 0U; /* No used. */
    config->hardwareCompareValueLow    = 0U; /* No used. */
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_MODE) && FSL_FEATURE_LPADC_HAS_CMDL_MODE
    config->conversionResolutionMode = kLPADC_ConversionResolutionStandard;
#endif /* FSL_FEATURE_LPADC_HAS_CMDL_MODE */
#if defined(FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG) && FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG
    config->enableWaitTrigger = false;
#endif                              /* FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG */
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_ALTBEN) && FSL_FEATURE_LPADC_HAS_CMDL_ALTBEN
    config->enableChannelB = false; /* Enable alternate channel B.*/
#endif                              /* FSL_FEATURE_LPADC_HAS_CMDL_ALTBEN */
}

#if defined(FSL_FEATURE_LPADC_HAS_CFG_CALOFS) && FSL_FEATURE_LPADC_HAS_CFG_CALOFS
/*!
 * brief Enable the calibration function.
 *
 * When CALOFS is set, the ADC is configured to perform a calibration function anytime the ADC executes
 * a conversion. Any channel selected is ignored and the value returned in the RESFIFO is a signed value
 * between -31 and 31. -32 is not a valid and is never a returned value. Software should copy the lower 6-
 * bits of the conversion result stored in the RESFIFO after a completed calibration conversion to the
 * OFSTRIM field. The OFSTRIM field is used in normal operation for offset correction.
 *
 * param base LPADC peripheral base address.
 * param enable switcher to the calibration function.
 */
void LPADC_EnableCalibration(ADC_Type *base, bool enable)
{
    LPADC_Enable(base, false);
    if (enable)
    {
        base->CFG |= ADC_CFG_CALOFS_MASK;
    }
    else
    {
        base->CFG &= ~ADC_CFG_CALOFS_MASK;
    }
    LPADC_Enable(base, true);
}

#if defined(FSL_FEATURE_LPADC_HAS_OFSTRIM) && FSL_FEATURE_LPADC_HAS_OFSTRIM
/*!
 * brief Do auto calibration.
 *
 * Calibration function should be executed before using converter in application. It used the software trigger and a
 * dummy conversion, get the offset and write them into the OFSTRIM register. It called some of functional API
 * including: -LPADC_EnableCalibration(...) -LPADC_LPADC_SetOffsetValue(...) -LPADC_SetConvCommandConfig(...)
 *   -LPADC_SetConvTriggerConfig(...)
 *
 * param base  LPADC peripheral base address.
 *
 * retval kStatus_Success Successfully configured.
 * retval kStatus_Timeout Timeout occurs while waiting completion.
 */
status_t LPADC_DoAutoCalibration(ADC_Type *base)
{
    assert(0u == LPADC_GetConvResultCount(base));

#if LPADC_CONVERSION_COMPLETE_TIMEOUT
    uint32_t timeout = LPADC_CONVERSION_COMPLETE_TIMEOUT;
#endif

    uint32_t mLpadcCMDL;
    uint32_t mLpadcCMDH;
    uint32_t mLpadcTrigger;
    lpadc_conv_trigger_config_t mLpadcTriggerConfigStruct;
    lpadc_conv_command_config_t mLpadcCommandConfigStruct;
    lpadc_conv_result_t mLpadcResultConfigStruct;

    /* Enable the calibration function. */
    LPADC_EnableCalibration(base, true);

    /* Keep the CMD and TRG state here and restore it later if the calibration completes.*/
    mLpadcCMDL    = base->CMD[0].CMDL; /* CMD1L. */
    mLpadcCMDH    = base->CMD[0].CMDH; /* CMD1H. */
    mLpadcTrigger = base->TCTRL[0];    /* Trigger0. */

    /* Set trigger0 configuration - for software trigger. */
    LPADC_GetDefaultConvTriggerConfig(&mLpadcTriggerConfigStruct);
    mLpadcTriggerConfigStruct.targetCommandId = 1U;                   /* CMD1 is executed. */
    LPADC_SetConvTriggerConfig(base, 0U, &mLpadcTriggerConfigStruct); /* Configurate the trigger0. */

    /* Set conversion CMD configuration. */
    LPADC_GetDefaultConvCommandConfig(&mLpadcCommandConfigStruct);
    mLpadcCommandConfigStruct.hardwareAverageMode = kLPADC_HardwareAverageCount128;
    LPADC_SetConvCommandConfig(base, 1U, &mLpadcCommandConfigStruct); /* Set CMD1 configuration. */

    /* Do calibration. */
    LPADC_DoSoftwareTrigger(base, 1U); /* 1U is trigger0 mask. */

    while (!LPADC_GetConvResult(base, &mLpadcResultConfigStruct))
    {
#if LPADC_CONVERSION_COMPLETE_TIMEOUT
        if ((--timeout) == 0U)
        {
            return kStatus_Timeout;
        }
#endif
    }

    /* The valid bits of data are bits 14:3 in the RESFIFO register. */
    LPADC_SetOffsetValue(base, (uint32_t)(mLpadcResultConfigStruct.convValue) >> 3UL);
    /* Disable the calibration function. */
    LPADC_EnableCalibration(base, false);

    /* restore CMD and TRG registers. */
    base->CMD[0].CMDL = mLpadcCMDL;    /* CMD1L. */
    base->CMD[0].CMDH = mLpadcCMDH;    /* CMD1H. */
    base->TCTRL[0]    = mLpadcTrigger; /* Trigger0. */

    return kStatus_Success;
}
#endif                                 /* FSL_FEATURE_LPADC_HAS_OFSTRIM */
#endif                                 /* FSL_FEATURE_LPADC_HAS_CFG_CALOFS */

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFS) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFS
/*!
 * brief Do offset calibration.
 *
 * param base LPADC peripheral base address.
 *
 * retval kStatus_Success Successfully configured.
 * retval kStatus_Timeout Timeout occurs while waiting completion.
 */
status_t LPADC_DoOffsetCalibration(ADC_Type *base)
{
#if LPADC_CALIBRATION_READY_TIMEOUT
    uint32_t timeout = LPADC_CALIBRATION_READY_TIMEOUT;
#endif

    LPADC_EnableOffsetCalibration(base, true);

    while (ADC_STAT_CAL_RDY_MASK != (base->STAT & ADC_STAT_CAL_RDY_MASK))
    {
#if LPADC_CALIBRATION_READY_TIMEOUT
        if ((--timeout) == 0U)
        {
            return kStatus_Timeout;
        }
#endif
    }

    return kStatus_Success;
}

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ
/*!
 * brief Do auto calibration.
 *
 * param base  LPADC peripheral base address.
 */
void LPADC_DoAutoCalibration(ADC_Type *base)
{
    LPADC_PrepareAutoCalibration(base);
#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE
    LPADC_FinishAutoCalibration(base);
#else
    LPADC_FinishAutoCalibration(base);
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE */
}

/*!
 * brief Prepare auto calibration, LPADC_FinishAutoCalibration has to be called before using the LPADC.
 * LPADC_DoAutoCalibration has been split in two API to avoid to be stuck too long in the function.
 *
 * param base  LPADC peripheral base address.
 */
void LPADC_PrepareAutoCalibration(ADC_Type *base)
{
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
    assert((0U == LPADC_GetConvResultCount(base, 0)) && (0U == LPADC_GetConvResultCount(base, 1)));
#else  /* FSL_FEATURE_LPADC_FIFO_COUNT */
    assert(LPADC_GetConvResultCount(base) == 0U);
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */

    /* Request gain calibration. */
    base->CTRL |= ADC_CTRL_CAL_REQ_MASK;
}

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE
/*!
 * brief Finish auto calibration start with LPADC_PrepareAutoCalibration.
 * note This feature is used for LPADC with CTRL[CALOFSMODE].
 *
 * param base  LPADC peripheral base address.
 *
 * retval kStatus_Success Successfully configured.
 * retval kStatus_Timeout Timeout occurs while waiting completion.
 */
status_t LPADC_FinishAutoCalibration(ADC_Type *base)
{
    int32_t GCCa;
    int32_t GCCb;
    float GCRa;
    float GCRb;

#if LPADC_GAIN_CAL_READY_TIMEOUT
    uint32_t timeoutGainCal = LPADC_GAIN_CAL_READY_TIMEOUT;
#endif

#if LPADC_CALIBRATION_READY_TIMEOUT
    uint32_t timeoutCal = LPADC_CALIBRATION_READY_TIMEOUT;
#endif

    while ((ADC_GCC_RDY_MASK != (base->GCC[0] & ADC_GCC_RDY_MASK))
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
           || (ADC_GCC_RDY_MASK != (base->GCC[1] & ADC_GCC_RDY_MASK))
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
    )
    {
#if LPADC_GAIN_CAL_READY_TIMEOUT
        if ((--timeoutGainCal) == 0U)
        {
            return kStatus_Timeout;
        }
#endif
    }

    /* Calculate gain offset. */
    GCCa = (int32_t)(base->GCC[0] & ADC_GCC_GAIN_CAL_MASK);
    GCCb = (int32_t)(base->GCC[1] & ADC_GCC_GAIN_CAL_MASK);
    if (0U != ((base->GCC[0]) & 0x8000U))
    {
        GCCa         = GCCa - 0x10000;
        GCRa         = (float)((131072.0) /
                       (131072.0 - (double)GCCa)); /* Gain_CalA = (131072.0 / (131072-(ADC_GCC_GAIN_CAL(ADC->GCC[0])) */
        base->GCR[0] = LPADC_GetGainConvResult(GCRa); /* write A side GCALR. */
    }

    if (0U != ((base->GCC[1]) & 0x8000U))
    {
        GCCb         = GCCb - 0x10000;
        GCRb         = (float)((131072.0) /
                       (131072.0 - (double)GCCb)); /* Gain_CalB = (131072.0 / (131072-(ADC_GCC_GAIN_CAL(ADC->GCC[1])) */
        base->GCR[1] = LPADC_GetGainConvResult(GCRb); /* write B side GCALR. */
    }

    /* Indicate the values are valid. */
    base->GCR[0] |= ADC_GCR_RDY_MASK;
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    base->GCR[1] |= ADC_GCR_RDY_MASK;
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */

    while (ADC_STAT_CAL_RDY_MASK != (base->STAT & ADC_STAT_CAL_RDY_MASK))
    {
#if LPADC_CALIBRATION_READY_TIMEOUT
        if ((--timeoutCal) == 0U)
        {
            return kStatus_Timeout;
        }
#endif
    }

    return kStatus_Success;
}
#else
/*!
 * brief Finish auto calibration start with LPADC_PrepareAutoCalibration.
 * note This feature is used for LPADC without CTRL[CALOFSMODE].
 *
 * param base  LPADC peripheral base address.
 *
 * retval kStatus_Success Successfully configured.
 * retval kStatus_Timeout Timeout occurs while waiting completion.
 */
status_t LPADC_FinishAutoCalibration(ADC_Type *base)
{
#if LPADC_GAIN_CAL_READY_TIMEOUT
    uint32_t timeoutGainCal = LPADC_GAIN_CAL_READY_TIMEOUT;
#endif

#if LPADC_CALIBRATION_READY_TIMEOUT
    uint32_t timeoutCal = LPADC_CALIBRATION_READY_TIMEOUT;
#endif

#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    uint32_t GCCa;
    uint32_t GCCb;
    float GCRb;
#else
    int32_t GCCa;
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
    float GCRa;

    while ((ADC_GCC_RDY_MASK != (base->GCC[0] & ADC_GCC_RDY_MASK))
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
           || (ADC_GCC_RDY_MASK != (base->GCC[1] & ADC_GCC_RDY_MASK))
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
    )
    {
#if LPADC_GAIN_CAL_READY_TIMEOUT
        if ((--timeoutGainCal) == 0U)
        {
            return kStatus_Timeout;
        }
#endif
    }

    /* Calculate gain offset. */
    GCCa         = ((base->GCC[0] & ADC_GCC_GAIN_CAL_MASK) >> ADC_GCC_GAIN_CAL_SHIFT);
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    GCCb         = ((base->GCC[1] & ADC_GCC_GAIN_CAL_MASK) >> ADC_GCC_GAIN_CAL_SHIFT);
    GCRb         = (float)((131072.0) /
                   (131072.0 - (double)GCCb)); /* Gain_CalB = (131072.0 / (131072-(ADC_GCC_GAIN_CAL(ADC->GCC[1])) */
    base->GCR[1] = LPADC_GetGainConvResult(GCRb);      /* write B side GCALR. */
#else
    if ((GCCa & (((ADC_GCC_GAIN_CAL_MASK >> ADC_GCC_GAIN_CAL_SHIFT) + 1U) >> 1U)) != 0U)
    {
        GCCa |= (~(ADC_GCC_GAIN_CAL_MASK >> ADC_GCC_GAIN_CAL_SHIFT));
    }
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
    GCRa         = (float)((131072.0) /
                   (131072.0 - (double)GCCa)); /* Gain_CalA = (131072.0 / (131072-(ADC_GCC_GAIN_CAL(ADC->GCC[0])) */
    base->GCR[0] = LPADC_GetGainConvResult(GCRa);      /* write A side GCALR. */

    /* Indicate the values are valid. */
    base->GCR[0] |= ADC_GCR_RDY_MASK;
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    base->GCR[1] |= ADC_GCR_RDY_MASK;
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */

    while (ADC_STAT_CAL_RDY_MASK != (base->STAT & ADC_STAT_CAL_RDY_MASK))
    {
#if LPADC_CALIBRATION_READY_TIMEOUT
        if ((--timeoutCal) == 0U)
        {
            return kStatus_Timeout;
        }
#endif
    }

    return kStatus_Success;
}
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE */
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ */

/*!
 * brief Get calibration value into the memory which is defined by invoker.
 *
 * note Please note the ADC will be disabled temporary.
 * note This function should be used after finish calibration.
 *
 * param base LPADC peripheral base address.
 * param ptrCalibrationValue Pointer to lpadc_calibration_value_t structure, this memory block should be always powered
 * on even in low power modes.
 */
void LPADC_GetCalibrationValue(ADC_Type *base, lpadc_calibration_value_t *ptrCalibrationValue)
{
    assert(ptrCalibrationValue != NULL);

    bool adcEnabled = false;

    /* Check if ADC is enabled. */
    if ((base->CTRL & ADC_CTRL_ADCEN_MASK) != 0UL)
    {
        LPADC_Enable(base, false);
        adcEnabled = true;
    }

#if (defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ)
    uint32_t i;
    for (i = 0UL; i < 33UL; i++)
    {
#if defined(ADC_CAL_GAR0_CAL_GAR_VAL_MASK)
        ptrCalibrationValue->generalCalibrationValueA[i] =
            (uint16_t)((*(((volatile uint32_t *)(&(base->CAL_GAR0))) + i)) & 0xFFFFU);
#if (defined(FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS) && (FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS == 1U))
        ptrCalibrationValue->generalCalibrationValueB[i] =
            (uint16_t)((*(((volatile uint32_t *)(&(base->CAL_GBR0))) + i)) & 0xFFFFU);
#endif /* FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS */
#else
        ptrCalibrationValue->generalCalibrationValueA[i] =
            (uint16_t)((*(((volatile uint32_t *)(&(base->CAL_GAR[0]))) + i)) & 0xFFFFU);
#if (defined(FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS) && (FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS == 1U))
        ptrCalibrationValue->generalCalibrationValueB[i] =
            (uint16_t)((*(((volatile uint32_t *)(&(base->CAL_GBR[0]))) + i)) & 0xFFFFU);
#endif /* FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS */

#endif /* defined(ADC_CAL_GAR0_CAL_GAR_VAL_MASK) */
    }
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ */

    ptrCalibrationValue->gainCalibrationResultA = (uint16_t)(base->GCR[0] & ADC_GCR_GCALR_MASK);
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    ptrCalibrationValue->gainCalibrationResultB = (uint16_t)(base->GCR[1] & ADC_GCR_GCALR_MASK);
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */

    if (adcEnabled)
    {
        LPADC_Enable(base, true);
    }
}

/*!
 * brief Set calibration value into ADC calibration registers.
 *
 * note Please note the ADC will be disabled temporary.
 *
 * param base LPADC peripheral base address.
 * param ptrCalibrationValue Pointer to lpadc_calibration_value_t structure which contains ADC's calibration value.
 * 
 * retval kStatus_Success Successfully configured.
 * retval kStatus_Timeout Timeout occurs while waiting completion.
 */
status_t LPADC_SetCalibrationValue(ADC_Type *base, const lpadc_calibration_value_t *ptrCalibrationValue)
{
    assert(ptrCalibrationValue != NULL);

#if LPADC_CALIBRATION_READY_TIMEOUT
    uint32_t timeout = LPADC_CALIBRATION_READY_TIMEOUT;
#endif

    bool adcEnabled = false;

    /* Check if ADC is enabled. */
    if ((base->CTRL & ADC_CTRL_ADCEN_MASK) != 0UL)
    {
        LPADC_Enable(base, false);
        adcEnabled = true;
    }

#if (defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ)
    for (uint32_t i = 0UL; i < 33UL; i++)
    {
#if defined(ADC_CAL_GAR0_CAL_GAR_VAL_MASK)
        *(((volatile uint32_t *)(&(base->CAL_GAR0))) + i) = ptrCalibrationValue->generalCalibrationValueA[i];
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
        *(((volatile uint32_t *)(&(base->CAL_GBR0))) + i) = ptrCalibrationValue->generalCalibrationValueB[i];
#endif /* (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U)) */
#else
        *(((volatile uint32_t *)(&(base->CAL_GAR[0]))) + i) = ptrCalibrationValue->generalCalibrationValueA[i];
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
        *(((volatile uint32_t *)(&(base->CAL_GBR[0]))) + i) = ptrCalibrationValue->generalCalibrationValueB[i];
#endif /* (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U)) */
#endif /* defined(ADC_CAL_GAR0_CAL_GAR_VAL_MASK) */
    }
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ */

    base->GCR[0] = ADC_GCR_GCALR(ptrCalibrationValue->gainCalibrationResultA) | ADC_GCR_RDY_MASK;
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    base->GCR[1] = ADC_GCR_GCALR(ptrCalibrationValue->gainCalibrationResultB) | ADC_GCR_RDY_MASK;
#endif /* (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U)) */
    /*
     * $Branch Coverage Justification$
     * while ((base->STAT & ADC_STAT_CAL_RDY_MASK) == ADC_STAT_CAL_RDY_MASK) not covered. Test unfeasible,
     * the calibration ready state is too short not to catch.
     */
    while (ADC_STAT_CAL_RDY_MASK != (base->STAT & ADC_STAT_CAL_RDY_MASK))
    {
#if LPADC_CALIBRATION_READY_TIMEOUT
        if ((--timeout) == 0U)
        {
            return kStatus_Timeout;
        }
#endif
    }

    if (adcEnabled)
    {
        LPADC_Enable(base, true);
    }

    return kStatus_Success;
}

#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CALOFS */
