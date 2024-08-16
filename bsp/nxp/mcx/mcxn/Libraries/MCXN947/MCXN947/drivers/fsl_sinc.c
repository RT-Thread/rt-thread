/*
 * Copyright 2022-2023 NXP
 *
 * All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sinc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sinc"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
static uint8_t SINC_GetInstance(SINC_Type *base);
#endif /*FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL*/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! brief Pointer to SINC clocks for each instance. */
static clock_ip_name_t const s_sincClocks[] = SINC_CLOCKS;

/*! brief Pointers to SINC bases for each instance. */
static SINC_Type *const s_sincBases[] = SINC_BASE_PTRS;

#endif /*FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL*/

/*******************************************************************************
 * Code
 ******************************************************************************/

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
static uint8_t SINC_GetInstance(SINC_Type *base)
{
    uint8_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_sincBases); instance++)
    {
        if (s_sincBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_sincBases));

    return instance;
}
#endif /*FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL*/

/*!
 * brief Initialize selected SINC instance, including clock options and channel options.
 *
 * param base SINC peripheral base address.
 * param config The pointer to sinc_config_t structure.
 */
void SINC_Init(SINC_Type *base, const sinc_config_t *config)
{
    assert(config != NULL);
    uint8_t i = 0U;

    /* Enable SINC clock root. */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(s_sincClocks[SINC_GetInstance(base)]);
#endif /*FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL*/

    SINC_EnableMaster(base, false);
    /* Reset all function blocks except for the clock. */
    SINC_DoSoftwareReset(base);

    /* Set clock configuration. */
    SINC_SetClkPrescale(base, config->clockPreDivider);
    SINC_SetModulatorClockDivider(base, config->modClkDivider);
    SINC_DisableModulatorClockOutput(base, (uint32_t)kSINC_ModClk0, config->disableModClk0Output);
    SINC_DisableModulatorClockOutput(base, (uint32_t)kSINC_ModClk1, config->disableModClk1Output);
    SINC_DisableModulatorClockOutput(base, (uint32_t)kSINC_ModClk2, config->disableModClk2Output);

    SINC_DisableDozeMode(base, config->disableDozeMode);

    for (i = 0U; i < (uint8_t)SINC_CHANNEL_COUNT; i++)
    {
        if (config->channelsConfigArray[i] != NULL)
        {
            SINC_SetChannelConfig(base, (sinc_channel_id_t)i, config->channelsConfigArray[i]);
        }
    }

    SINC_EnableMaster(base, config->enableMaster);
    if ((config->disableModClk0Output == false) && (config->enableMaster == true))
    {
        while (!SINC_CheckModulatorClockReady(base, (uint32_t)kSINC_ModClk0))
        {
            /* Loop until Modulator clock 0 is ready. */
            ;
        }
    }
    else if ((config->disableModClk1Output == false) && (config->enableMaster == true))
    {
        while (!SINC_CheckModulatorClockReady(base, (uint32_t)kSINC_ModClk1))
        {
            /* Loop until Modulator clock 0 is ready. */
            ;
        }
    }
    else if ((config->disableModClk2Output == false) && (config->enableMaster == true))
    {
        while (!SINC_CheckModulatorClockReady(base, (uint32_t)kSINC_ModClk2))
        {
            /* Loop until Modulator clock 0 is ready. */
            ;
        }
    }
    else
    {
        /* Added comments to avoid violations of MISRA C-2012 rules. */
    }
}

/*!
 * brief De-initialize selected SINC instance.
 *
 * param base SINC peripheral base address.
 */
void SINC_Deinit(SINC_Type *base)
{
    SINC_DoSoftwareReset(base);
    /* Disable master */
    SINC_EnableMaster(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(s_sincClocks[SINC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Get default configuration.
 *
 * code {.c}
 *     config->clockPreDivider = kSINC_ClkPrescale1;
 *     config->modClkDivider   = 2UL;
 *     config->disableModClk0Output = false;
 *     config->disableModClk1Output = false;
 *     config->disableModClk2Output = false;
 *
 *     config->channelsConfigArray[SINC_CHANNEL_COUNT] = {NULL, NULL, NULL, NULL};
 *
 *     config->disableDozeMode      = false;
 *     config->enableMaster         = false;
 * endcode
 *
 *
 * param config The pointer to sinc_config_t structure, must not be NULL.
 */
void SINC_GetDefaultConfig(sinc_config_t *config)
{
    assert(config != NULL);

    config->clockPreDivider      = kSINC_ClkPrescale1;
    config->modClkDivider        = 2UL;
    config->disableModClk0Output = false;
    config->disableModClk1Output = false;
    config->disableModClk2Output = false;

    for (uint8_t i = 0U; i < (uint8_t)SINC_CHANNEL_COUNT; i++)
    {
        config->channelsConfigArray[i] = NULL;
    }

    config->disableDozeMode = false;
    config->enableMaster    = false;
}

/*!
 * brief Set channel configurations, including input options, conversion options and protection options.
 *
 * param base SINC peripheral base address.
 * param chId Selected channel id, please refer to sinc_channel_id_t.
 * param chConfig Pointer to sinc_channel_config_t structure, must not be NULL.
 */
void SINC_SetChannelConfig(SINC_Type *base, sinc_channel_id_t chId, sinc_channel_config_t *chConfig)
{
    assert(chConfig != NULL);

    SINC_EnableChannel(base, chId, false);

    /* Set channel input options, including input clock and input source. */
    SINC_SetChannelInputOption(base, chId, chConfig->chInputOption);

    /* Set channel conversion options, including trigger source and primary filter. */
    SINC_SetChannelConversionOption(base, chId, chConfig->chConvOption);

    /* Set channel protection options, including SCD, limit check, CAD, zero crossing. */
    SINC_SetChannelProtectionOption(base, chId, chConfig->chProtectionOption);

    SINC_EnableChannelFIFO(base, chId, chConfig->bEnableFifo);
    SINC_SetChannelFifoWatermark(base, chId, chConfig->u8FifoWaterMark);

    SINC_EnableChannelPrimaryDma(base, chId, chConfig->bEnablePrimaryDma);

#if (defined(FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) && FSL_FEATURE_SINC_CACFR_HAS_ADMASEL)
    SINC_SetChannelAltDmaSource(base, chId, chConfig->altDmaSource);
#endif /* (defined(FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) && FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) */

    SINC_SetChannelResultDataFormat(base, chId, chConfig->dataFormat);

    SINC_EnableChannel(base, chId, chConfig->bEnableChannel);
}
/*!
 * brief Set channel input options, including input bit format, input bit source, input bit delay, input clock source,
 * input clock edge.
 *
 * param base SINC peripheral base address.
 * param chId Selected channel id, please refer to sinc_channel_id_t.
 * param chInputOption Pointer to sinc_channel_input_option_t structure, must not be NULL.
 */
void SINC_SetChannelInputOption(SINC_Type *base, sinc_channel_id_t chId, sinc_channel_input_option_t *chInputOption)
{
    assert(chInputOption != NULL);

    uint32_t u32Tmp;

    u32Tmp = ((base->CHANNEL[(uint8_t)chId].CCFR) &
              ~(SINC_CCFR_IBFMT_MASK | SINC_CCFR_ICSEL_MASK | SINC_CCFR_ICESEL_MASK | SINC_CCFR_IBSEL_MASK));
    u32Tmp |= SINC_CCFR_ICSEL(chInputOption->inputClkSource) | SINC_CCFR_IBFMT(chInputOption->inputBitFormat) |
              SINC_CCFR_ICESEL(chInputOption->inputClkEdge) | SINC_CCFR_IBSEL(chInputOption->inputBitSource);
    base->CHANNEL[(uint8_t)chId].CCFR = u32Tmp;

    u32Tmp = ((base->CHANNEL[(uint8_t)chId].CACFR) & ~SINC_CACFR_IBDLY_MASK);
    u32Tmp |= SINC_CACFR_IBDLY(chInputOption->inputBitDelay);
    base->CHANNEL[(uint8_t)chId].CACFR = u32Tmp;
}

/*!
 * brief Set channel conversion options, including conversion mode, trigger source, and primary filter settings.
 *
 * param base SINC peripheral base address.
 * param chId Selected channel id, please refer to sinc_channel_id_t.
 * param chConvOption Pointer to sinc_channel_conv_option_t structure, must not be NULL.
 */
void SINC_SetChannelConversionOption(SINC_Type *base, sinc_channel_id_t chId, sinc_channel_conv_option_t *chConvOption)
{
    assert(chConvOption != NULL);

    /* Set  trigger source. */
    SINC_SetChannelTriggerSource(base, chId, chConvOption->convTriggerSource);

    /* Set PF CIC options. */
    SINC_SetChannelConversionMode(base, chId, chConvOption->convMode);
    SINC_SetChannelPfOrder(base, chId, chConvOption->pfOrder);
    SINC_SetChannelPfOsr(base, chId, chConvOption->u16pfOverSampleRatio);

    /* Set HPF alpha coefficient. */
    SINC_SetChannelPfHpfAlphaCoeff(base, chId, chConvOption->pfHpfAlphaCoeff);

    /* Set shift options */
    SINC_SetChannelPfShiftConfig(base, chId, chConvOption->pfShiftDirection, chConvOption->u8pfShiftBitsNum);

    /* Set bias options. */
    SINC_SetChannelPfBiasConfig(base, chId, chConvOption->pfBiasSign, chConvOption->u32pfBiasValue);

    /* Enable channel's primary filter. */
    SINC_EnableChannelPrimaryFilter(base, chId, chConvOption->enableChPrimaryFilter);
}

/*!
 * brief Set channel protection options, including limit check, short-circuit detector, clock-absence detector, and
 * zero-crossing detector.
 *
 * param base SINC peripheral base address.
 * param chId Selected channel id, please refer to sinc_channel_id_t.
 * param chProtection Pointer to sinc_channel_protection_option_t, must not be NULL.
 */
void SINC_SetChannelProtectionOption(SINC_Type *base,
                                     sinc_channel_id_t chId,
                                     sinc_channel_protection_option_t *chProtection)
{
    assert(chProtection != NULL);

    /* limit check */
    if (chProtection->limitDetectorMode == kSINC_Lmt_Disabled)
    {
        base->CHANNEL[(uint8_t)chId].CCR &= ~SINC_CCR_LMTEN_MASK;
    }
    else
    {
        SINC_SetChannelLowLimitThreshold(base, chId, chProtection->u32LowLimitThreshold);
        SINC_SetChannelHighLimitThreshold(base, chId, chProtection->u32HighLimitThreshold);
        base->CHANNEL[(uint8_t)chId].CPROT = (base->CHANNEL[(uint8_t)chId].CPROT & ~SINC_CPROT_LMTOP_MASK) |
                                             SINC_CPROT_LMTOP((uint32_t)chProtection->limitDetectorMode & 0x3UL);
        if (chProtection->bEnableLmtBreakSignal)
        {
            base->CHANNEL[(uint8_t)chId].CPROT |=
                (((((uint32_t)(chProtection->limitDetectorMode)) & 0x1CUL) >> 2UL) << SINC_CPROT_LLMTBK_SHIFT);
        }
        else
        {
            base->CHANNEL[(uint8_t)chId].CPROT &=
                ~(((((uint32_t)(chProtection->limitDetectorMode)) & 0x1CUL) >> 2UL) << SINC_CPROT_LLMTBK_SHIFT);
        }
        base->CHANNEL[(uint8_t)chId].CCR |= SINC_CCR_LMTEN_MASK;
    }

    /* Short-circuit detector. */
    if (chProtection->scdOperateMode == kSINC_Scd_OperateDisabled)
    {
        SINC_SetChannelScdOperateMode(base, chId, kSINC_Scd_OperateDisabled);
    }
    else
    {
        SINC_SetChannelScdLimitThreshold(base, chId, chProtection->u8ScdLimitThreshold);
        SINC_SetChannelScdOption(base, chId, chProtection->scdOption);
        SINC_EnableChannelScdBreakSignal(base, chId, chProtection->bEnableScdBreakSignal);
        SINC_SetChannelScdOperateMode(base, chId, chProtection->scdOperateMode);
    }

    /* Clock-absence detector. */
    SINC_EnableChannelCadBreakSignal(base, chId, chProtection->bEnableCadBreakSignal);
    SINC_SetChannelCadLimitThreshold(base, chId, chProtection->cadLimitThreshold);

    /* zero-crossing detector. */
    SINC_SetChannelZcdOperateMode(base, chId, chProtection->zcdOperateMode);
}

/*!
 * brief Get selected channel's number of conversions.
 *
 * param base SINC peripheral base address.
 * param chId Selected channel id, refer to sinc_channel_id_t for details.
 * return uint8_t Selected channel's number of conversions.
 */
uint8_t SINC_GetChannelConversionCount(SINC_Type *base, sinc_channel_id_t chId)
{
    uint8_t u8Count;

    u8Count = (uint8_t)((base->CHANNEL[(uint8_t)chId].CSR & SINC_CSR_CNUM_MASK) >> SINC_CSR_CNUM_SHIFT);
    if ((base->CHANNEL[(uint8_t)chId].CSR & SINC_CSR_CNUM_OV_MASK) != 0UL)
    {
        u8Count += 128U;
    }

    return u8Count;
}
