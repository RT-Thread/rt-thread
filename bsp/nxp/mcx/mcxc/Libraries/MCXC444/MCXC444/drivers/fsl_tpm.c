/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_tpm.h"

/*
 * $Coverage Justification Reference$
 *
 * $Justification tpm_c_ref_1$
 * Hardware limitations make this code impossible to implement.
 *
 * $Justification tpm_c_ref_2$
 * Because the incoming base is invalid, the second judgment is not continued after the first condition
 * is established.
 *
 * $Justification tpm_c_ref_3$
 * Hardware limitations, the 32-bit counter register makes counterMax = 0xffffffffu,
 * and the mod vlue can't be greater than or equal to counterMax after the operation.
 *
 * $Justification tpm_c_ref_4$
 * If the incoming base can not make (1U == (uint8_t)FSL_FEATURE_TPM_POL_HAS_EFFECTn(base) true,
 * the subsequent register operation is incorrect.
 *
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.tpm"
#endif

#define TPM_COMBINE_SHIFT (8U)

#if defined(TPM_RSTS)
#define TPM_RESETS_ARRAY TPM_RSTS
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to TPM bases for each instance. */
static TPM_Type *const s_tpmBases[] = TPM_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to TPM clocks for each instance. */
static const clock_ip_name_t s_tpmClocks[] = TPM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/* Array of TPM callback function pointer. */
static tpm_callback_t s_tpmCallback[ARRAY_SIZE(s_tpmBases)];

/* Array to map TPM instance to IRQ number. */
static const IRQn_Type s_tpmIRQ[] = TPM_IRQS;

#if defined(TPM_RESETS_ARRAY)
/* Reset array */
static const reset_ip_name_t s_tpmResets[] = TPM_RESETS_ARRAY;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Gets the instance from the base address
 *
 * param base TPM peripheral base address
 * return The TPM instance
 */
uint32_t TPM_GetInstance(TPM_Type *base)
{
    uint32_t instance;
    uint32_t tpmArrayCount = (sizeof(s_tpmBases) / sizeof(s_tpmBases[0]));

    /* Find the instance index from base address mappings. */
    /*
     * $Branch Coverage Justification$
     * (instance >= tpmArrayCount) not covered.
     * The peripheral base address is always valid.
     */
    for (instance = 0; instance < tpmArrayCount; instance++)
    {
        if (s_tpmBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < tpmArrayCount);

    return instance;
}

/*!
 * brief Ungates the TPM clock and configures the peripheral for basic operation.
 *
 * note This API should be called at the beginning of the application using the TPM driver.
 *
 * param base   TPM peripheral base address
 * param config Pointer to user's TPM config structure.
 */
void TPM_Init(TPM_Type *base, const tpm_config_t *config)
{
    assert(NULL != config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the module clock */
    (void)CLOCK_EnableClock(s_tpmClocks[TPM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(TPM_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_tpmResets[TPM_GetInstance(base)]);
#endif

#if defined(FSL_FEATURE_TPM_HAS_GLOBAL) && FSL_FEATURE_TPM_HAS_GLOBAL
    /* TPM reset is available on certain SoC's */
    TPM_Reset(base);
#endif

    /* Set the clock prescale factor */
    base->SC = TPM_SC_PS(config->prescale);
#if !(defined(FSL_FEATURE_TPM_HAS_NO_CONF) && FSL_FEATURE_TPM_HAS_NO_CONF)
    /* Setup the counter operation */
    base->CONF = TPM_CONF_DOZEEN(config->enableDoze) |
#if defined(FSL_FEATURE_TPM_HAS_GLOBAL_TIME_BASE_EN) && FSL_FEATURE_TPM_HAS_GLOBAL_TIME_BASE_EN
                 TPM_CONF_GTBEEN(config->useGlobalTimeBase) |
#endif
#if defined(FSL_FEATURE_TPM_HAS_GLOBAL_TIME_BASE_SYNC) && FSL_FEATURE_TPM_HAS_GLOBAL_TIME_BASE_SYNC
                 TPM_CONF_GTBSYNC(config->syncGlobalTimeBase) |
#endif
                 TPM_CONF_CROT(config->enableReloadOnTrigger) |
                 TPM_CONF_CSOT(config->enableStartOnTrigger) | TPM_CONF_CSOO(config->enableStopOnOverflow) |
#if defined(FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER) && FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER
                 TPM_CONF_CPOT(config->enablePauseOnTrigger) |
#endif
#if defined(FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION) && FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION
                 TPM_CONF_TRGSRC(config->triggerSource) | TPM_CONF_TRGPOL(config->extTriggerPolarity) |
#endif
                 TPM_CONF_TRGSEL(config->triggerSelect);
    if (true == config->enableDebugMode)
    {
        base->CONF |= TPM_CONF_DBGMODE_MASK;
    }
    else
    {
        base->CONF &= ~TPM_CONF_DBGMODE_MASK;
    }
#endif
#if defined(FSL_FEATURE_TPM_HAS_POL) && FSL_FEATURE_TPM_HAS_POL
    base->POL = config->chnlPolarity;
#endif
}

/*!
 * brief Stops the counter and gates the TPM clock
 *
 * param base TPM peripheral base address
 */
void TPM_Deinit(TPM_Type *base)
{
#if defined(FSL_FEATURE_TPM_HAS_SC_CLKS) && FSL_FEATURE_TPM_HAS_SC_CLKS
    /* Stop the counter */
    base->SC &= ~TPM_SC_CLKS_MASK;
#else
    /* Stop the counter */
    base->SC &= ~TPM_SC_CMOD_MASK;
#endif
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the TPM clock */
    (void)CLOCK_DisableClock(s_tpmClocks[TPM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief  Fill in the TPM config struct with the default settings
 *
 * The default values are:
 * code
 *     config->prescale = kTPM_Prescale_Divide_1;
 *     config->useGlobalTimeBase = false;
 *     config->syncGlobalTimeBase = false;
 *     config->dozeEnable = false;
 *     config->dbgMode = false;
 *     config->enableReloadOnTrigger = false;
 *     config->enableStopOnOverflow = false;
 *     config->enableStartOnTrigger = false;
 *#if FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER
 *     config->enablePauseOnTrigger = false;
 *#endif
 *     config->triggerSelect = kTPM_Trigger_Select_0;
 *#if FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION
 *     config->triggerSource = kTPM_TriggerSource_External;
 *     config->extTriggerPolarity = kTPM_ExtTrigger_Active_High;
 *#endif
 *#if defined(FSL_FEATURE_TPM_HAS_POL) && FSL_FEATURE_TPM_HAS_POL
 *     config->chnlPolarity = 0U;
 *#endif
 * endcode
 * param config Pointer to user's TPM config structure.
 */
void TPM_GetDefaultConfig(tpm_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* TPM clock divide by 1 */
    config->prescale = kTPM_Prescale_Divide_1;
#if !(defined(FSL_FEATURE_TPM_HAS_NO_CONF) && FSL_FEATURE_TPM_HAS_NO_CONF)
    /* Use internal TPM counter as timebase */
    config->useGlobalTimeBase = false;
    /* Disable internal TPM counter sync with global timebase */
    config->syncGlobalTimeBase = false;
    /* TPM counter continues in doze mode */
    config->enableDoze = false;
    /* TPM counter pauses when in debug mode */
    config->enableDebugMode = false;
    /* TPM counter will not be reloaded on input trigger */
    config->enableReloadOnTrigger = false;
    /* TPM counter continues running after overflow */
    config->enableStopOnOverflow = false;
    /* TPM counter starts immediately once it is enabled */
    config->enableStartOnTrigger = false;
#if defined(FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER) && FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER
    config->enablePauseOnTrigger = false;
#endif
    /* Choose trigger select 0 as input trigger for controlling counter operation */
    config->triggerSelect = kTPM_Trigger_Select_0;
#if defined(FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION) && FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION
    /* Choose external trigger source (high active) to control counter operation */
    config->triggerSource      = kTPM_TriggerSource_External;
    config->extTriggerPolarity = kTPM_ExtTrigger_Active_High;
#endif
#if defined(FSL_FEATURE_TPM_HAS_POL) && FSL_FEATURE_TPM_HAS_POL
    /* Default channel polarity is active high */
    config->chnlPolarity = 0U;
#endif
#endif
}

/*!
 * brief Calculates the counter clock prescaler.
 *
 * This function calculates the values for SC[PS].
 *
 * param base                TPM peripheral base address
 * param counterPeriod_Hz    The desired frequency in Hz which corresponding to the time when the counter reaches the
 * mod value param srcClock_Hz   TPM counter clock in Hz
 *
 * return Calculated clock prescaler value.
 */
tpm_clock_prescale_t TPM_CalculateCounterClkDiv(TPM_Type *base, uint32_t counterPeriod_Hz, uint32_t srcClock_Hz)
{
    uint32_t counterMax = TPM_MAX_COUNTER_VALUE(base);
    uint32_t i;
    assert(((srcClock_Hz / 2U) > counterPeriod_Hz) && ((srcClock_Hz / 128U / counterMax) <= counterPeriod_Hz));

    for (i = 0U; i < (uint32_t)kTPM_Prescale_Divide_128; i++)
    {
        if ((srcClock_Hz / (1UL << i) / counterMax) < counterPeriod_Hz)
        {
            break;
        }
    }
    return (tpm_clock_prescale_t)i;
}

/*!
 * brief Set parameters for PWM duty cycle and edges for a single tpm channel
 *
 * User calls this function to configure the mode, duty cycle and edge of a single PWM signal.
 *
 * param base        TPM peripheral base address
 * param mod         PWM period
 * param mode        PWM operation mode, options available in enumeration ::tpm_pwm_mode_t
 * param chnlParams  A structure for configuring PWM channel parameters, used to configure the channel.
 *
 * return kStatus_Success if the PWM setup was successful,
 *         kStatus_Error on failure
 */
static status_t TPM_SetupSinglePwmChannel(TPM_Type *base,
                                          uint32_t mod,
                                          tpm_pwm_mode_t mode,
                                          tpm_chnl_pwm_signal_param_t chnlParams)
{
    uint32_t cnv;
    uint32_t counterMax = TPM_MAX_COUNTER_VALUE(base);
    uint8_t controlBits;
    uint8_t chnlId;

    /* MSnB:MSnA field value always be 10, ELSnB:ELSnA field value should config according to the channel params */
#if defined(FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT) && FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT
    controlBits =
        (uint8_t)((uint32_t)kTPM_ChnlMSBMask | TPM_CnSC_ELSB(chnlParams.pauseLevel) | TPM_CnSC_ELSA(chnlParams.level));
#else
    controlBits = ((uint8_t)kTPM_ChnlMSBMask | ((uint8_t)chnlParams.level << TPM_CnSC_ELSA_SHIFT));
#endif
    chnlId = (uint8_t)chnlParams.chnlNumber;
    /* Return error if requested dutycycle/chnlNumber is greater than the max allowed */
    /*
     * $Branch Coverage Justification$
     * (-1 == (int8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)) not covered.
     * This function is called inside the TPM_SetupPwm() function.
     * If you enter an invalid base, the function will not work properly.
     */
    if ((chnlId >= (uint8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)) ||
        /*
         * $Branch Coverage Justification$
         * (chnlId >= (uint8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)) not covered.  $ref tpm_c_ref_2$.
         */
        (-1 == (int8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)))
    {
        return kStatus_InvalidArgument;
    }
    /* Return error if requested dutycycle is greater than the max allowed or MOD equal to 0xFFFF when it want get a
     * 100% duty cycle PWM signal*/
    /*
     * $Branch Coverage Justification$
     * (mod == counterMax) not covered. $ref tpm_c_ref_3$.
     */
    if (((chnlParams.dutyCyclePercent == 100U) && (mod == counterMax)) || (chnlParams.dutyCyclePercent > 100U))
    {
        return kStatus_OutOfRange;
    }

#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
    if (mode == kTPM_CombinedPwm)
    {
        /* Check added for combined mode */
        /*
         * $Branch Coverage Justification$
         * (chnlId >= ((uint8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base) / 2U)) not covered. $ref tpm_c_ref_2$.
         */
        if ((chnlId >= ((uint8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base) / 2U)) ||
            (1U != (uint8_t)FSL_FEATURE_TPM_COMBINE_HAS_EFFECTn(base)))
        {
            /* The instance should support combine mode and the channel number should be the pair number */
            return kStatus_InvalidArgument;
        }
        if (((chnlParams.firstEdgeDelayPercent + chnlParams.dutyCyclePercent) > 100U) ||
            ((chnlParams.firstEdgeDelayPercent > 0U) && (chnlParams.dutyCyclePercent == 0U)) ||
            ((chnlParams.firstEdgeDelayPercent == 0U) && (chnlParams.deadTimeValue[0] != 0U)))
        {
            /* Return error if the following situation occurs :
             * firstEdgeDelayPercent + dutyCyclePercent > 100
             * firstEdgeDelayPercent > 0 and dutyCyclePercent == 0
             * firstEdgeDelayPercent == 0 and deadTimeValue[0] != 0
             */
            return kStatus_OutOfRange;
        }
        /* Configure delay of the first edge */
        uint32_t cnvFirstEdge;
        /* Configure dutycycle */
        if (chnlParams.dutyCyclePercent == 0U)
        {
            cnvFirstEdge = mod + 1U;
            cnv          = 0;
        }
        else if (chnlParams.dutyCyclePercent == 100U)
        {
            cnvFirstEdge = 0U;
            cnv          = mod + 1U;
        }
        else
        {
            cnvFirstEdge = (mod * chnlParams.firstEdgeDelayPercent) / 100U;
            cnv          = (mod * chnlParams.dutyCyclePercent) / 100U;
        }

        /* Set the combine bit for the channel pair */
        base->COMBINE |= 1UL << (TPM_COMBINE_SHIFT * chnlId);

        chnlId *= 2U;
        /* Set deadtime insertion for the channel pair using channel filter register */
        uint32_t filterVal = base->FILTER;
        /* Clear the channel pair's filter values */
        filterVal &=
            ~(((uint32_t)TPM_FILTER_CH0FVAL_MASK | TPM_FILTER_CH1FVAL_MASK) << (chnlId * TPM_FILTER_CH1FVAL_SHIFT));
        /* Shift the deadtime insertion value to the right place in the register */
        filterVal |= (TPM_FILTER_CH0FVAL(chnlParams.deadTimeValue[0]) | TPM_FILTER_CH1FVAL(chnlParams.deadTimeValue[1]))
                     << (chnlId * TPM_FILTER_CH1FVAL_SHIFT);
        base->FILTER = filterVal;

        /* When switching mode, disable channel n first */
        TPM_DisableChannel(base, (tpm_chnl_t)chnlId);
        /* Set the requested PWM mode for channel n, under combine PWM mode, the active level is opposite of
         * edge-aligned mode */
        TPM_EnableChannel(base, (tpm_chnl_t)chnlId, controlBits ^ TPM_CnSC_ELSA_MASK);
        /* Set the channel n value */
        do
        {
            base->CONTROLS[chnlId].CnV = cnvFirstEdge;
            /*
             * $Branch Coverage Justification$
             * (cnvFirstEdge != base->CONTROLS[chnlId].CnV) not covered. $ref tpm_c_ref_1$.
             */
        } while (cnvFirstEdge != base->CONTROLS[chnlId].CnV);

        chnlId += 1U;
        /* When switching mode, disable channel n + 1 */
        TPM_DisableChannel(base, (tpm_chnl_t)chnlId);
#if defined(FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT) && FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT
        /* Select the pause level for second channel */
        controlBits = (uint8_t)((uint32_t)kTPM_ChnlMSBMask | TPM_CnSC_ELSB(chnlParams.secPauseLevel) |
                                TPM_CnSC_ELSA(chnlParams.level));
#endif
        /* Set the requested PWM mode for channel n + 1 */
        if (chnlParams.enableComplementary)
        {
            /* Change the polarity on the second channel get complementary PWM signals */
            TPM_EnableChannel(base, (tpm_chnl_t)chnlId, controlBits);
        }
        else
        {
            /* Second channel use same control bits as first channel */
            TPM_EnableChannel(base, (tpm_chnl_t)chnlId, controlBits ^ TPM_CnSC_ELSA_MASK);
        }

        /* Set the channel n+1 value */
        do
        {
            base->CONTROLS[chnlId].CnV = cnvFirstEdge + cnv;
            /*
             * $Branch Coverage Justification$
             * ((cnvFirstEdge + cnv) != base->CONTROLS[chnlId].CnV) not covered. $ref tpm_c_ref_1$.
             */
        } while ((cnvFirstEdge + cnv) != base->CONTROLS[chnlId].CnV);
    }
    else
    {
#endif
        /* Configure dutycycle */
        if (chnlParams.dutyCyclePercent == 100U)
        {
            cnv = mod + 1U;
        }
        else
        {
            cnv = (mod * chnlParams.dutyCyclePercent) / 100U;
        }
        /* Fix ERROR050050 When TPM is configured in EPWM mode as PS = 0, the compare event is missed on
        the first reload/overflow after writing 1 to the CnV register and causes an incorrect duty output.*/
#if (defined(FSL_FEATURE_TPM_HAS_ERRATA_050050) && FSL_FEATURE_TPM_HAS_ERRATA_050050)
        assert(!(mode == kTPM_EdgeAlignedPwm && cnv == 1U && (base->SC & TPM_SC_PS_MASK) == kTPM_Prescale_Divide_1));
#endif
        /* When switching mode, disable channel first */
        TPM_DisableChannel(base, (tpm_chnl_t)chnlId);
        /* Set the requested PWM mode, output mode MSnB:MSnA field value set to 10 */
        TPM_EnableChannel(base, (tpm_chnl_t)chnlId, controlBits);
        do
        {
            base->CONTROLS[chnlId].CnV = cnv;
            /*
             * $Branch Coverage Justification$
             * (cnv != base->CONTROLS[chnlId].CnV) not covered. $ref tpm_c_ref_1$.
             */
        } while (cnv != base->CONTROLS[chnlId].CnV);

#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
    }
#endif
    return kStatus_Success;
}

/*!
 * brief Configures the PWM signal parameters
 *
 * User calls this function to configure the PWM signals period, mode, dutycycle and edge. Use this
 * function to configure all the TPM channels that will be used to output a PWM signal
 *
 * param base        TPM peripheral base address
 * param chnlParams  Array of PWM channel parameters to configure the channel(s)
 * param numOfChnls  Number of channels to configure, this should be the size of the array passed in
 * param mode        PWM operation mode, options available in enumeration ::tpm_pwm_mode_t
 * param pwmFreq_Hz  PWM signal frequency in Hz
 * param srcClock_Hz TPM counter clock in Hz
 *
 * return kStatus_Success if the PWM setup was successful,
 *         kStatus_Error on failure
 */
status_t TPM_SetupPwm(TPM_Type *base,
                      const tpm_chnl_pwm_signal_param_t *chnlParams,
                      uint8_t numOfChnls,
                      tpm_pwm_mode_t mode,
                      uint32_t pwmFreq_Hz,
                      uint32_t srcClock_Hz)
{
    assert(NULL != chnlParams);

    uint32_t mod        = 0U;
    uint32_t counterMax = TPM_MAX_COUNTER_VALUE(base);
    uint32_t tpmClock   = (srcClock_Hz / (1UL << (base->SC & TPM_SC_PS_MASK)));
    status_t status     = kStatus_Success;

    if ((0U == pwmFreq_Hz) || (0U == srcClock_Hz) || (0U == numOfChnls) || (tpmClock < pwmFreq_Hz))
    {
        return kStatus_InvalidArgument;
    }

    switch (mode)
    {
#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
        case kTPM_CombinedPwm:
#endif
        case kTPM_EdgeAlignedPwm:
            base->SC &= ~TPM_SC_CPWMS_MASK;
            mod = (tpmClock / pwmFreq_Hz) - 1U;

            /*
             * $Branch Coverage Justification$
             * (mod > counterMax) not covered. $ref tpm_c_tpm_3$.
             */
            if ((mod > counterMax) || (mod == 0U))
            {
                /*  The MOD greater than the maximum allowed (some instanse only support 16-bit counter) or smaller than
                1, probably would require changing clock source to get the desired frequency. */
                status = kStatus_OutOfRange;
            }
            break;
        case kTPM_CenterAlignedPwm:
            base->SC |= TPM_SC_CPWMS_MASK;
            mod = tpmClock / (pwmFreq_Hz * 2u);
            /*
             * $Branch Coverage Justification$
             * (mod > counterMax >> 1U) not covered. $ref tpm_c_tpm_3$.
             */
            if ((mod > (counterMax >> 1U)) || (mod == 0U))
            {
                /* MOD values have additional requirements under center-aligned MODE, it must be kept in the range
                 * of 0x1 ~ 0x7FFF (under 16-bit counter). */
                status = kStatus_OutOfRange;
            }
            break;
        default:
            /* All the cease have been listed above, the default case should not be reached. */
            status = kStatus_InvalidArgument;
            break;
    }
    if (kStatus_Success != status)
    {
        return status;
    }
    /* Set the PWM period */
    base->MOD = mod;

    /* Setup each TPM channel */
    for (uint8_t i = 0; i < numOfChnls; i++)
    {
        /* Setup a single PWM channel */
        status = TPM_SetupSinglePwmChannel(base, mod, mode, *chnlParams);
        if (status != kStatus_Success)
        {
            return status;
        }
        chnlParams++;
    }

#if defined(FSL_FEATURE_TPM_HAS_QDCTRL) && FSL_FEATURE_TPM_HAS_QDCTRL
    /* The TPM's QDCTRL register required to be effective */
    if (1U == (uint8_t)FSL_FEATURE_TPM_QDCTRL_HAS_EFFECTn(base))
    {
        /* Clear quadrature Decoder mode because in quadrature Decoder mode PWM doesn't operate*/
        base->QDCTRL &= ~TPM_QDCTRL_QUADEN_MASK;
    }
#endif

    return kStatus_Success;
}

/*!
 * brief Update the duty cycle of an active PWM signal
 *
 * param base              TPM peripheral base address
 * param chnlNumber        The channel number. In combined mode, this represents
 *                          the channel pair number
 * param currentPwmMode    The current PWM mode set during PWM setup
 * param dutyCyclePercent  New PWM pulse width, value should be between 0 to 100
 *                          0=inactive signal(0% duty cycle)...
 *                          100=active signal (100% duty cycle)
 * return kStatus_Success if the PWM setup was successful,
 *        kStatus_Error on failure
 */
status_t TPM_UpdatePwmDutycycle(TPM_Type *base,
                                tpm_chnl_t chnlNumber,
                                tpm_pwm_mode_t currentPwmMode,
                                uint8_t dutyCyclePercent)
{
    uint32_t cnv, mod;
    uint32_t counterMax = TPM_MAX_COUNTER_VALUE(base);
    uint8_t chnlId      = (uint8_t)chnlNumber;

    /* Return error if requested chnlNumber is greater than the max allowed */
    /* Return error if requested dutycycle/chnlNumber is greater than the max allowed */
    if ((chnlId >= (uint8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)) ||
        (-1 == (int8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)))
    {
        return kStatus_InvalidArgument;
    }
    /* Get the PWM period */
    mod = base->MOD & counterMax;
    /* Return error if requested dutycycle is greater than the max allowed */
    if (((dutyCyclePercent == 100U) && (mod == counterMax)) || (dutyCyclePercent > 100U))
    {
        /* MOD can't equal to 0xFFFF otherwise it can't get a 100% duty cycle PWM signal. */
        return kStatus_OutOfRange;
    }

#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
    if (currentPwmMode == kTPM_CombinedPwm)
    {
        /* Check added for combined mode */
        /*
         * $Branch Coverage Justification$
         * (chnlId >= ((uint8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base) / 2U)) not covered. $ref tpm_c_ref_2$.
         */
        if ((chnlId >= ((uint8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base) / 2U)) ||
            (1U != (uint8_t)FSL_FEATURE_TPM_COMBINE_HAS_EFFECTn(base)))
        {
            /* The instance should support combine mode and the channel number should be the pair number */
            return kStatus_InvalidArgument;
        }
        uint32_t cnvFirstEdge;
        cnv = (mod * dutyCyclePercent) / 100U;
        if ((base->CONTROLS[chnlId * 2U].CnV & counterMax) > mod)
        {
            cnvFirstEdge = 0U;
        }
        else
        {
            cnvFirstEdge = base->CONTROLS[chnlId * 2U].CnV & counterMax;
        }

        if (((cnvFirstEdge + cnv) > mod) || ((cnv == 0U) && (cnvFirstEdge > 0U)))
        {
            /* Return error if the following situation occurs :
             * firstEdgeDelayPercent + dutyCyclePercent > 100
             * firstEdgeDelayPercent > 0 and dutyCyclePercent == 0
             */
            return kStatus_OutOfRange;
        }
        if (cnv == mod)
        {
            /* 100% duty cycle */
            cnv = mod + 1U;
        }
        else if (cnv == 0U)
        {
            /* 0% duty cycle */
            cnvFirstEdge = mod + 1U;
        }
        else
        {
            ; /* Intentional empty */
        }

        do
        {
            base->CONTROLS[chnlId * 2U].CnV = cnvFirstEdge;
            /*
             * $Branch Coverage Justification$
             * (cnvFirstEdge != base->CONTROLS[chnlId * 2U].CnV) not covered. $ref tpm_c_ref_1$.
             */
        } while (cnvFirstEdge != base->CONTROLS[chnlId * 2U].CnV);
        do
        {
            base->CONTROLS[(chnlId * 2U) + 1U].CnV = cnvFirstEdge + cnv;
        } while ((cnvFirstEdge + cnv) != base->CONTROLS[(chnlId * 2U) + 1U].CnV);
    }
    else
    {
#endif
        if (dutyCyclePercent == 100U)
        {
            cnv = mod + 1U;
        }
        else
        {
            cnv = (mod * dutyCyclePercent) / 100U;
        }
        /* Fix ERROR050050 */
#if (defined(FSL_FEATURE_TPM_HAS_ERRATA_050050) && FSL_FEATURE_TPM_HAS_ERRATA_050050)
        assert(!(currentPwmMode == kTPM_EdgeAlignedPwm && cnv == 1U &&
                 (base->SC & TPM_SC_PS_MASK) == kTPM_Prescale_Divide_1));
#endif

        do
        {
            base->CONTROLS[chnlId].CnV = cnv;
            /*
             * $Branch Coverage Justification$
             * (cnv != base->CONTROLS[chnlId].CnV) not covered. $ref tpm_c_ref_1$.
             */
        } while (cnv != base->CONTROLS[chnlId].CnV);

#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
    }
#endif
    return kStatus_Success;
}

/*!
 * brief Update the edge level selection for a channel
 *
 * note When the TPM has PWM pause level select feature (FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT = 1), the PWM output
 *      cannot be turned off by selecting the output level. In this case, must use TPM_DisableChannel API to close
 * the PWM output.
 *
 * param base       TPM peripheral base address
 * param chnlNumber The channel number
 * param level      The level to be set to the ELSnB:ELSnA field; valid values are 00, 01, 10, 11.
 *                   See the appropriate SoC reference manual for details about this field.
 */
void TPM_UpdateChnlEdgeLevelSelect(TPM_Type *base, tpm_chnl_t chnlNumber, uint8_t level)
{
    assert(((uint8_t)chnlNumber < (uint8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)) &&
           (-1 != (int8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)));

    uint8_t control = TPM_GetChannelContorlBits(base, chnlNumber);

    /* When switching mode, disable channel first */
    TPM_DisableChannel(base, chnlNumber);

    /* Clear the field and write the new level value */
    control &= ~(uint8_t)(TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK);
    control |= ((uint8_t)level << TPM_CnSC_ELSA_SHIFT) & (TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK);

    /* Enable channle with new level value */
    TPM_EnableChannel(base, chnlNumber, control);
}

/*!
 * brief Enables capturing an input signal on the channel using the function parameters.
 *
 * When the edge specified in the captureMode argument occurs on the channel, the TPM counter is captured into
 * the CnV register. The user has to read the CnV register separately to get this value.
 *
 * param base        TPM peripheral base address
 * param chnlNumber  The channel number
 * param captureMode Specifies which edge to capture
 */
void TPM_SetupInputCapture(TPM_Type *base, tpm_chnl_t chnlNumber, tpm_input_capture_edge_t captureMode)
{
    assert(((uint8_t)chnlNumber < (uint8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)) &&
           (-1 != (int8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)));

#if defined(FSL_FEATURE_TPM_HAS_QDCTRL) && FSL_FEATURE_TPM_HAS_QDCTRL
    /* The TPM's QDCTRL register required to be effective */
    if (1U == (uint8_t)FSL_FEATURE_TPM_QDCTRL_HAS_EFFECTn(base))
    {
        /* Clear quadrature Decoder mode for channel 0 or 1*/
        if (((uint32_t)chnlNumber == 0u) || ((uint32_t)chnlNumber == 1u))
        {
            base->QDCTRL &= ~TPM_QDCTRL_QUADEN_MASK;
        }
    }
#endif

#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
    /* The TPM's COMBINE register required to be effective */
    if (1U == (uint8_t)FSL_FEATURE_TPM_COMBINE_HAS_EFFECTn(base))
    {
        /* Clear the combine bit for chnlNumber */
        base->COMBINE &= ~((uint32_t)1U << (((uint32_t)chnlNumber / 2U) * TPM_COMBINE_SHIFT));
    }
#endif
    /*Clear CPWMS bit when the input capture mode is selected */
    base->SC &= ~TPM_SC_CPWMS_MASK;
    /* When switching mode, disable channel first */
    TPM_DisableChannel(base, chnlNumber);
    /* Enable channel with new requested input capture mode */
    TPM_EnableChannel(base, chnlNumber, (uint8_t)captureMode);
}

/*!
 * brief Configures the TPM to generate timed pulses.
 *
 * When the TPM counter matches the value of compareVal argument (this is written into CnV reg), the channel
 * output is changed based on what is specified in the compareMode argument.
 *
 * param base         TPM peripheral base address
 * param chnlNumber   The channel number
 * param compareMode  Action to take on the channel output when the compare condition is met
 * param compareValue Value to be programmed in the CnV register.
 */
void TPM_SetupOutputCompare(TPM_Type *base,
                            tpm_chnl_t chnlNumber,
                            tpm_output_compare_mode_t compareMode,
                            uint32_t compareValue)
{
    assert(((uint8_t)chnlNumber < (uint8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)) &&
           (-1 != (int8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)));

#if defined(FSL_FEATURE_TPM_HAS_QDCTRL) && FSL_FEATURE_TPM_HAS_QDCTRL
    /* The TPM's QDCTRL register required to be effective */
    if (1U == (uint8_t)FSL_FEATURE_TPM_QDCTRL_HAS_EFFECTn(base))
    {
        /* Clear quadrature Decoder mode for channel 0 or 1 */
        if (((uint32_t)chnlNumber == 0U) || ((uint32_t)chnlNumber == 1U))
        {
            base->QDCTRL &= ~TPM_QDCTRL_QUADEN_MASK;
        }
    }
#endif

    /*Clear CPWMS bit when the output compare mode is selected */
    base->SC &= ~TPM_SC_CPWMS_MASK;
    /* When switching mode, disable channel first  */
    TPM_DisableChannel(base, chnlNumber);
    /* Enable channel with new requested compare mode */
    TPM_EnableChannel(base, chnlNumber, (uint8_t)compareMode);

    /* Setup the compare value */
    do
    {
        base->CONTROLS[chnlNumber].CnV = compareValue;
        /*
         * $Branch Coverage Justification$
         * (compareValue != base->CONTROLS[chnlNumber].CnV) not covered. $ref tpm_c_ref_1$.
         */
    } while (compareValue != base->CONTROLS[chnlNumber].CnV);
}

#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
/*!
 * brief Configures the dual edge capture mode of the TPM.
 *
 * This function allows to measure a pulse width of the signal on the input of channel of a
 * channel pair. The filter function is disabled if the filterVal argument passed is zero.
 *
 * param base           TPM peripheral base address
 * param chnlPairNumber The TPM channel pair number; options are 0, 1, 2, 3
 * param edgeParam      Sets up the dual edge capture function
 * param filterValue    Filter value, specify 0 to disable filter.
 */
void TPM_SetupDualEdgeCapture(TPM_Type *base,
                              tpm_chnl_t chnlPairNumber,
                              const tpm_dual_edge_capture_param_t *edgeParam,
                              uint32_t filterValue)
{
    assert(NULL != edgeParam);
    assert(((uint8_t)chnlPairNumber < (uint8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base) / 2U) &&
           (-1 != (int8_t)FSL_FEATURE_TPM_CHANNEL_COUNTn(base)));
    assert(1U == (uint8_t)FSL_FEATURE_TPM_COMBINE_HAS_EFFECTn(base));

    uint32_t reg;
    uint32_t u32flag;
    uint8_t chnlId = (uint8_t)chnlPairNumber * 2U;

#if defined(FSL_FEATURE_TPM_HAS_QDCTRL) && FSL_FEATURE_TPM_HAS_QDCTRL
    /* The TPM's QDCTRL register required to be effective */
    if (1U == (uint8_t)FSL_FEATURE_TPM_QDCTRL_HAS_EFFECTn(base))
    {
        /* Clear quadrature Decoder mode for channel 0 or 1*/
        if (chnlId == 0u)
        {
            base->QDCTRL &= ~TPM_QDCTRL_QUADEN_MASK;
        }
    }
#endif

    /* When switching mode, disable channel first */
    TPM_DisableChannel(base, (tpm_chnl_t)chnlId);
    chnlId++;
    TPM_DisableChannel(base, (tpm_chnl_t)chnlId);
    chnlId--;

    /* Now, the registers for input mode can be operated. */
    if (true == edgeParam->enableSwap)
    {
        u32flag = TPM_COMBINE_COMBINE0_MASK | TPM_COMBINE_COMSWAP0_MASK;
        /* Set the combine and swap bits for the channel pair */
        base->COMBINE |= u32flag << (TPM_COMBINE_SHIFT * (uint32_t)chnlPairNumber);

        /* Input filter setup for channel n+1 input */
        reg = base->FILTER;
        reg &= ~((uint32_t)TPM_FILTER_CH0FVAL_MASK << (TPM_FILTER_CH1FVAL_SHIFT * (chnlId + 1U)));
        reg |= (filterValue << (TPM_FILTER_CH1FVAL_SHIFT * (chnlId + 1U)));
        base->FILTER = reg;
    }
    else
    {
        reg = base->COMBINE;
        /* Clear the swap bit for the channel pair */
        reg &= ~((uint32_t)TPM_COMBINE_COMSWAP0_MASK << ((uint32_t)chnlPairNumber * TPM_COMBINE_COMSWAP0_SHIFT));
        u32flag = TPM_COMBINE_COMBINE0_MASK;

        /* Set the combine bit for the channel pair */
        reg |= u32flag << (TPM_COMBINE_SHIFT * (uint32_t)chnlPairNumber);
        base->COMBINE = reg;

        /* Input filter setup for channel n input */
        reg = base->FILTER;
        reg &= ~((uint32_t)TPM_FILTER_CH0FVAL_MASK << (TPM_FILTER_CH1FVAL_SHIFT * chnlId));
        reg |= (filterValue << (TPM_FILTER_CH1FVAL_SHIFT * chnlId));
        base->FILTER = reg;
    }

    /* Setup the edge detection from channel n and n+1*/
    TPM_EnableChannel(base, (tpm_chnl_t)chnlId, (uint8_t)edgeParam->currChanEdgeMode);
    chnlId++;
    TPM_EnableChannel(base, (tpm_chnl_t)chnlId, (uint8_t)edgeParam->nextChanEdgeMode);
}
#endif

#if defined(FSL_FEATURE_TPM_HAS_QDCTRL) && FSL_FEATURE_TPM_HAS_QDCTRL
/*!
 * brief Configures the parameters and activates the quadrature decode mode.
 *
 * param base         TPM peripheral base address
 * param phaseAParams Phase A configuration parameters
 * param phaseBParams Phase B configuration parameters
 * param quadMode     Selects encoding mode used in quadrature decoder mode
 */
void TPM_SetupQuadDecode(TPM_Type *base,
                         const tpm_phase_params_t *phaseAParams,
                         const tpm_phase_params_t *phaseBParams,
                         tpm_quad_decode_mode_t quadMode)
{
    assert(NULL != phaseAParams);
    assert(NULL != phaseBParams);
    assert(1U == (uint8_t)FSL_FEATURE_TPM_QDCTRL_HAS_EFFECTn(base));

    /* Disable channel 0 */
    TPM_DisableChannel(base, kTPM_Chnl_0);

    uint32_t reg;

    /* Set Phase A filter value */
    reg = base->FILTER;
    reg &= ~(TPM_FILTER_CH0FVAL_MASK);
    reg |= TPM_FILTER_CH0FVAL(phaseAParams->phaseFilterVal);
    base->FILTER = reg;

#if defined(FSL_FEATURE_TPM_HAS_POL) && FSL_FEATURE_TPM_HAS_POL
    /*
     * $Branch Coverage Justification$
     * (1U != FSL_FEATURE_TPM_QDCTRL_HAS_EFFECTn(base)) not covered. $ref tpm_c_ref_4$.
     */
    if (1U == (uint8_t)FSL_FEATURE_TPM_POL_HAS_EFFECTn(base))
    {
        /* Set Phase A polarity */
        if (kTPM_QuadPhaseInvert == phaseAParams->phasePolarity)
        {
            base->POL |= TPM_POL_POL0_MASK;
        }
        else
        {
            base->POL &= ~TPM_POL_POL0_MASK;
        }
    }
#endif

    /* Disable channel 1 */
    TPM_DisableChannel(base, kTPM_Chnl_0);

    /* Set Phase B filter value */
    reg = base->FILTER;
    reg &= ~(TPM_FILTER_CH1FVAL_MASK);
    reg |= TPM_FILTER_CH1FVAL(phaseBParams->phaseFilterVal);
    base->FILTER = reg;
#if defined(FSL_FEATURE_TPM_HAS_POL) && FSL_FEATURE_TPM_HAS_POL
    /*
     * $Branch Coverage Justification$
     * (1U != FSL_FEATURE_TPM_QDCTRL_HAS_EFFECTn(base)) not covered. $ref tpm_c_ref_4$.
     */
    if (1U == (uint8_t)FSL_FEATURE_TPM_POL_HAS_EFFECTn(base))
    {
        /* Set Phase B polarity */
        if (kTPM_QuadPhaseInvert == phaseBParams->phasePolarity)
        {
            base->POL |= TPM_POL_POL1_MASK;
        }
        else
        {
            base->POL &= ~TPM_POL_POL1_MASK;
        }
    }
#endif

    /* Set Quadrature mode */
    reg = base->QDCTRL;
    reg &= ~(TPM_QDCTRL_QUADMODE_MASK);
    reg |= TPM_QDCTRL_QUADMODE(quadMode);
    base->QDCTRL = reg;

    /* Enable Quad decode */
    base->QDCTRL |= TPM_QDCTRL_QUADEN_MASK;
}

#endif

/*!
 * brief Enables the selected TPM interrupts.
 *
 * param base TPM peripheral base address
 * param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::tpm_interrupt_enable_t
 */
void TPM_EnableInterrupts(TPM_Type *base, uint32_t mask)
{
    uint32_t chnlInterrupts = (mask & 0xFFU);
    uint8_t chnlNumber      = 0;

    /* Enable the timer overflow interrupt */
    if ((uint32_t)kTPM_TimeOverflowInterruptEnable == (mask & (uint32_t)kTPM_TimeOverflowInterruptEnable))
    {
        base->SC |= TPM_SC_TOIE_MASK;
    }

    /* Enable the channel interrupts */
    while (0U != chnlInterrupts)
    {
        if (0U != (chnlInterrupts & 0x1u))
        {
            base->CONTROLS[chnlNumber].CnSC |= TPM_CnSC_CHIE_MASK;
        }
        chnlNumber++;
        chnlInterrupts = chnlInterrupts >> 1U;
    }
}

/*!
 * brief Disables the selected TPM interrupts.
 *
 * param base TPM peripheral base address
 * param mask The interrupts to disable. This is a logical OR of members of the
 *             enumeration ::tpm_interrupt_enable_t
 */
void TPM_DisableInterrupts(TPM_Type *base, uint32_t mask)
{
    uint32_t chnlInterrupts = (mask & 0xFFU);
    uint8_t chnlNumber      = 0;

    /* Disable the timer overflow interrupt */
    if ((uint32_t)kTPM_TimeOverflowInterruptEnable == (mask & (uint32_t)kTPM_TimeOverflowInterruptEnable))
    {
        base->SC &= ~TPM_SC_TOIE_MASK;
    }

    /* Disable the channel interrupts */
    while (0U != chnlInterrupts)
    {
        if (0U != (chnlInterrupts & 0x1u))
        {
            base->CONTROLS[chnlNumber].CnSC &= ~TPM_CnSC_CHIE_MASK;
        }
        chnlNumber++;
        chnlInterrupts = chnlInterrupts >> 1U;
    }
}

/*!
 * brief Gets the enabled TPM interrupts.
 *
 * param base TPM peripheral base address
 *
 * return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::tpm_interrupt_enable_t
 */
uint32_t TPM_GetEnabledInterrupts(TPM_Type *base)
{
    uint32_t enabledInterrupts = 0;
    uint32_t u32flag           = 1;
    int8_t chnlCount           = FSL_FEATURE_TPM_CHANNEL_COUNTn(base);

    /* The CHANNEL_COUNT macro returns -1 if it cannot match the TPM instance */
    assert(chnlCount != -1);

    /* Check if timer overflow interrupt is enabled */
    if (0U != (base->SC & TPM_SC_TOIE_MASK))
    {
        enabledInterrupts |= (uint32_t)kTPM_TimeOverflowInterruptEnable;
    }

    /* Check if the channel interrupts are enabled */
    while (chnlCount > 0)
    {
        chnlCount--;
        if (0U != (base->CONTROLS[chnlCount].CnSC & TPM_CnSC_CHIE_MASK))
        {
            enabledInterrupts |= (u32flag << (uint8_t)chnlCount);
        }
    }

    return enabledInterrupts;
}

/*!
 * brief Register callback.
 *
 * If channel or overflow interrupt is enabled by the user, then a callback can be registered
 * which will be invoked when the interrupt is triggered.
 *
 * param base       TPM peripheral base address
 * param callback   Callback function
 */
void TPM_RegisterCallBack(TPM_Type *base, tpm_callback_t callback)
{
    uint32_t instance;

    instance = TPM_GetInstance(base);

    /* Create TPM callback instance. */
    s_tpmCallback[instance] = callback;

    /* Enable IRQ. */
    (void)EnableIRQ(s_tpmIRQ[instance]);
}

#if defined(TPM0)
void TPM0_DriverIRQHandler(void);
void TPM0_DriverIRQHandler(void)
{
    if (NULL != s_tpmCallback[0])
    {
        s_tpmCallback[0](TPM0);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(TPM1)
void TPM1_DriverIRQHandler(void);
void TPM1_DriverIRQHandler(void)
{
    if (NULL != s_tpmCallback[1])
    {
        s_tpmCallback[1](TPM1);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif
