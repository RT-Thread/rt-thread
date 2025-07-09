/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022, 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pwm.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.pwm"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the instance from the base address
 *
 * @param base PWM peripheral base address
 *
 * @return The PWM module instance
 */

#if defined(PWM_RESETS_ARRAY) || \
    !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
static uint32_t PWM_GetInstance(PWM_Type *base);
#endif

#if defined(PWM_RSTS)
#define PWM_RESETS_ARRAY PWM_RSTS
#elif defined(FLEXPWM_RSTS)
#define PWM_RESETS_ARRAY FLEXPWM_RSTS
#elif defined(FLEXPWM_RSTS_N)
#define PWM_RESETS_ARRAY FLEXPWM_RSTS_N
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to PWM bases for each instance. */
static PWM_Type *const s_pwmBases[] = PWM_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to PWM clocks for each PWM submodule. */
static const clock_ip_name_t s_pwmClocks[][FSL_FEATURE_PWM_SUBMODULE_COUNT] = PWM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(PWM_RESETS_ARRAY)
/* Reset array */
static const reset_ip_name_t s_pwmResets[] = PWM_RESETS_ARRAY;
#endif

/*! @brief Temporary PWM duty cycle. */
static uint8_t s_pwmGetPwmDutyCycle[FSL_FEATURE_PWM_SUBMODULE_COUNT][PWM_SUBMODULE_CHANNEL] = {{0}};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Complement the variable of type uint16_t as needed
 *
 * This function can complement the variable of type uint16_t as needed.For example,
 * need to ask for the opposite of a positive integer.
 *
 * param value    Parameters of type uint16_t
 */
static inline uint16_t PWM_GetComplementU16(uint16_t value)
{
    return (~value + 1U);
}

static inline uint16_t dutyCycleToReloadValue(uint8_t dutyCyclePercent)
{
    /* Rounding calculations to improve the accuracy of reloadValue */
    return ((65535U * dutyCyclePercent) + 50U) / 100U;
}

static uint32_t PWM_GetInstance(PWM_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_pwmBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_pwmBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_pwmBases));

    return instance;
}

/*!
 * brief Set register about period on one PWM submodule.
 *
 * param base        PWM peripheral base address
 * param subModule   PWM submodule to configure
 * param mode        PWM operation mode, options available in enumeration ::pwm_mode_t
 * param pulseCnt    PWM period, value should be between 0 to 65535
 */
static void PWM_SetPeriodRegister(PWM_Type *base, pwm_submodule_t subModule, pwm_mode_t mode, uint16_t pulseCnt)
{
    uint16_t modulo = 0;

    switch (mode)
    {
        case kPWM_SignedCenterAligned:
            /* Setup the PWM period for a signed center aligned signal */
            modulo = (pulseCnt >> 1U);
            /* Indicates the start of the PWM period */
            base->SM[subModule].INIT = PWM_GetComplementU16(modulo);
            /* Indicates the center value */
            base->SM[subModule].VAL0 = 0;
            /* Indicates the end of the PWM period */
            /* The change during the end to start of the PWM period requires a count time */
            base->SM[subModule].VAL1 = modulo - 1U;
            break;
        case kPWM_CenterAligned:
            /* Setup the PWM period for an unsigned center aligned signal */
            /* Indicates the start of the PWM period */
            base->SM[subModule].INIT = 0;
            /* Indicates the center value */
            base->SM[subModule].VAL0 = pulseCnt / 2U;
            /* Indicates the end of the PWM period */
            /* The change during the end to start of the PWM period requires a count time */
            base->SM[subModule].VAL1 = pulseCnt - 1U;
            break;
        case kPWM_SignedEdgeAligned:
            /* Setup the PWM period for a signed edge aligned signal */
            modulo = (pulseCnt >> 1U);
            /* Indicates the start of the PWM period */
            base->SM[subModule].INIT = PWM_GetComplementU16(modulo);
            /* Indicates the center value */
            base->SM[subModule].VAL0 = 0;
            /* Indicates the end of the PWM period */
            /* The change during the end to start of the PWM period requires a count time */
            base->SM[subModule].VAL1 = modulo - 1U;
            break;
        case kPWM_EdgeAligned:
            /* Setup the PWM period for a unsigned edge aligned signal */
            /* Indicates the start of the PWM period */
            base->SM[subModule].INIT = 0;
            /* Indicates the center value */
            base->SM[subModule].VAL0 = pulseCnt / 2U;
            /* Indicates the end of the PWM period */
            /* The change during the end to start of the PWM period requires a count time */
            base->SM[subModule].VAL1 = pulseCnt - 1U;
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Set register about dutycycle on one PWM submodule.
 *
 * param base        PWM peripheral base address
 * param subModule   PWM submodule to configure
 * param pwmSignal   Signal (PWM A, PWM B, PWM X) to update
 * param mode        PWM operation mode, options available in enumeration ::pwm_mode_t
 * param pulseCnt    PWM period, value should be between 0 to 65535
 * param dutyCycle   New PWM pulse width, value should be between 0 to 65535
 */
static void PWM_SetDutycycleRegister(PWM_Type *base,
                                     pwm_submodule_t subModule,
                                     pwm_channels_t pwmSignal,
                                     pwm_mode_t mode,
                                     uint16_t pulseCnt,
                                     uint16_t pwmHighPulse)
{
    uint16_t modulo = 0;

    switch (mode)
    {
        case kPWM_SignedCenterAligned:
            /* Setup the PWM dutycycle for a signed center aligned signal */
            if (pwmSignal == kPWM_PwmA)
            {
                base->SM[subModule].VAL2 = PWM_GetComplementU16(pwmHighPulse / 2U);
                base->SM[subModule].VAL3 = pwmHighPulse / 2U;
            }
            else if (pwmSignal == kPWM_PwmB)
            {
                base->SM[subModule].VAL4 = PWM_GetComplementU16(pwmHighPulse / 2U);
                base->SM[subModule].VAL5 = pwmHighPulse / 2U;
            }
            else
            {
                ; /* Intentional empty */
            }
            break;
        case kPWM_CenterAligned:
            /* Setup the PWM dutycycle for an unsigned center aligned signal */
            if (pwmSignal == kPWM_PwmA)
            {
                base->SM[subModule].VAL2 = (pulseCnt - pwmHighPulse) / 2U;
                base->SM[subModule].VAL3 = (pulseCnt + pwmHighPulse) / 2U;
            }
            else if (pwmSignal == kPWM_PwmB)
            {
                base->SM[subModule].VAL4 = (pulseCnt - pwmHighPulse) / 2U;
                base->SM[subModule].VAL5 = (pulseCnt + pwmHighPulse) / 2U;
            }
            else
            {
                ; /* Intentional empty */
            }
            break;
        case kPWM_SignedEdgeAligned:
            modulo = (pulseCnt >> 1U);
            /* Setup the PWM dutycycle for a signed edge aligned signal */
            if (pwmSignal == kPWM_PwmA)
            {
                base->SM[subModule].VAL2 = PWM_GetComplementU16(modulo);
                base->SM[subModule].VAL3 = PWM_GetComplementU16(modulo) + pwmHighPulse;
            }
            else if (pwmSignal == kPWM_PwmB)
            {
                base->SM[subModule].VAL4 = PWM_GetComplementU16(modulo);
                base->SM[subModule].VAL5 = PWM_GetComplementU16(modulo) + pwmHighPulse;
            }
            else
            {
                base->SM[subModule].VAL0 = PWM_GetComplementU16(modulo) + pwmHighPulse;
            }
            break;
        case kPWM_EdgeAligned:
            /* Setup the PWM dutycycle for a unsigned edge aligned signal */
            if (pwmSignal == kPWM_PwmA)
            {
                base->SM[subModule].VAL2 = 0;
                base->SM[subModule].VAL3 = pwmHighPulse;
            }
            else if (pwmSignal == kPWM_PwmB)
            {
                base->SM[subModule].VAL4 = 0;
                base->SM[subModule].VAL5 = pwmHighPulse;
            }
            else
            {
                base->SM[subModule].VAL0 = pwmHighPulse;
            }
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Ungates the PWM submodule clock and configures the peripheral for basic operation.
 *
 * This API should be called at the beginning of the application using the PWM driver.
 * When user select PWMX, user must choose edge aligned output, becasue there are some limitation on center
 * aligned PWMX output.
 * When output PWMX in center aligned mode, VAL1 register controls both PWM period and PWMX duty cycle, PWMA
 * and PWMB output will be corrupted. But edge aligned PWMX output do not have such limit.
 * In master reload counter initialization mode, PWM period is depended by period of set LDOK in submodule 0
 * because this operation will reload register.
 * Submodule 0 counter initialization cannot be master sync or master reload.
 * 
 * param base      PWM peripheral base address
 * param subModule PWM submodule to configure
 * param config    Pointer to user's PWM config structure.
 *
 * return kStatus_Success means success; else failed.
 */
status_t PWM_Init(PWM_Type *base, pwm_submodule_t subModule, const pwm_config_t *config)
{
    assert(config);

    uint16_t reg;

    /* Source clock for submodule 0 cannot be itself */
    if ((config->clockSource == kPWM_Submodule0Clock) && (subModule == kPWM_Module_0))
    {
        return kStatus_Fail;
    }

    /* Reload source select clock for submodule 0 cannot be master reload */
    if ((config->reloadSelect == kPWM_MasterReload) && (subModule == kPWM_Module_0))
    {
        return kStatus_Fail;
    }

    /* Counter initialize for submodule 0 cannot be master reload or master sync. */
    if ((config->initializationControl == kPWM_Initialize_MasterReload ||
         config->initializationControl == kPWM_Initialize_MasterSync) &&
        (subModule == kPWM_Module_0))
    {
        return kStatus_Fail;
    }

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate the PWM submodule clock*/
    CLOCK_EnableClock(s_pwmClocks[PWM_GetInstance(base)][subModule]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(PWM_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_pwmResets[PWM_GetInstance(base)]);
#endif

    /* Clear the fault status flags */
    base->FSTS |= PWM_FSTS_FFLAG_MASK;

    reg = base->SM[subModule].CTRL2;

    /* Setup the submodule clock-source, control source of the INIT signal,
     * source of the force output signal, operation in debug & wait modes and reload source select
     */
    reg &=
        ~(uint16_t)(PWM_CTRL2_CLK_SEL_MASK | PWM_CTRL2_FORCE_SEL_MASK | PWM_CTRL2_INIT_SEL_MASK | PWM_CTRL2_INDEP_MASK |
#if !defined(FSL_FEATURE_PWM_HAS_NO_WAITEN) || (!FSL_FEATURE_PWM_HAS_NO_WAITEN)
                    PWM_CTRL2_WAITEN_MASK |
#endif /* FSL_FEATURE_PWM_HAS_NO_WAITEN */
                    PWM_CTRL2_DBGEN_MASK | PWM_CTRL2_RELOAD_SEL_MASK);
    reg |= (PWM_CTRL2_CLK_SEL(config->clockSource) | PWM_CTRL2_FORCE_SEL(config->forceTrigger) |
            PWM_CTRL2_INIT_SEL(config->initializationControl) | PWM_CTRL2_DBGEN(config->enableDebugMode) |
#if !defined(FSL_FEATURE_PWM_HAS_NO_WAITEN) || (!FSL_FEATURE_PWM_HAS_NO_WAITEN)
            PWM_CTRL2_WAITEN(config->enableWait) |
#endif /* FSL_FEATURE_PWM_HAS_NO_WAITEN */
            PWM_CTRL2_RELOAD_SEL(config->reloadSelect));

    /* Setup PWM A & B to be independent or a complementary-pair */
    switch (config->pairOperation)
    {
        case kPWM_Independent:
            reg |= PWM_CTRL2_INDEP_MASK;
            break;
        case kPWM_ComplementaryPwmA:
            base->MCTRL &= ~((uint16_t)1U << (PWM_MCTRL_IPOL_SHIFT + (uint16_t)subModule));
            break;
        case kPWM_ComplementaryPwmB:
            base->MCTRL |= ((uint16_t)1U << (PWM_MCTRL_IPOL_SHIFT + (uint16_t)subModule));
            break;
        default:
            assert(false);
            break;
    }
    base->SM[subModule].CTRL2 = reg;

    reg = base->SM[subModule].CTRL;

    /* Setup the clock prescale, load mode and frequency */
    reg &= ~(uint16_t)(PWM_CTRL_PRSC_MASK | PWM_CTRL_LDFQ_MASK | PWM_CTRL_LDMOD_MASK);
    reg |= (PWM_CTRL_PRSC(config->prescale) | PWM_CTRL_LDFQ(config->reloadFrequency));

    /* Setup register reload logic */
    switch (config->reloadLogic)
    {
        case kPWM_ReloadImmediate:
            reg |= PWM_CTRL_LDMOD_MASK;
            break;
        case kPWM_ReloadPwmHalfCycle:
            reg |= PWM_CTRL_HALF_MASK;
            reg &= (uint16_t)(~PWM_CTRL_FULL_MASK);
            break;
        case kPWM_ReloadPwmFullCycle:
            reg &= (uint16_t)(~PWM_CTRL_HALF_MASK);
            reg |= PWM_CTRL_FULL_MASK;
            break;
        case kPWM_ReloadPwmHalfAndFullCycle:
            reg |= PWM_CTRL_HALF_MASK;
            reg |= PWM_CTRL_FULL_MASK;
            break;
        default:
            assert(false);
            break;
    }
    base->SM[subModule].CTRL = reg;

    /* Set PWM output normal */
#if defined(PWM_MASK_UPDATE_MASK)
    base->MASK &= (uint16_t)(~(uint16_t)(PWM_MASK_MASKX_MASK | PWM_MASK_MASKA_MASK | PWM_MASK_MASKB_MASK |
                                         PWM_MASK_UPDATE_MASK_MASK));
#else
    base->MASK &= ~(uint16_t)(PWM_MASK_MASKX_MASK | PWM_MASK_MASKA_MASK | PWM_MASK_MASKB_MASK);
#endif

    base->DTSRCSEL = 0U;

    /* Issue a Force trigger event when configured to trigger locally */
    if (config->forceTrigger == kPWM_Force_Local)
    {
        base->SM[subModule].CTRL2 |= PWM_CTRL2_FORCE(1U);
    }

    return kStatus_Success;
}

/*!
 * brief Gate the PWM submodule clock
 *
 * param base      PWM peripheral base address
 * param subModule PWM submodule to deinitialize
 */
void PWM_Deinit(PWM_Type *base, pwm_submodule_t subModule)
{
    /* Stop the submodule */
    base->MCTRL &= ~((uint16_t)1U << (PWM_MCTRL_RUN_SHIFT + (uint16_t)subModule));

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the PWM submodule clock*/
    CLOCK_DisableClock(s_pwmClocks[PWM_GetInstance(base)][subModule]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief  Fill in the PWM config struct with the default settings
 *
 * The default values are:
 * code
 *   config->enableDebugMode = false;
 *   config->enableWait = false;
 *   config->reloadSelect = kPWM_LocalReload;
 *   config->clockSource = kPWM_BusClock;
 *   config->prescale = kPWM_Prescale_Divide_1;
 *   config->initializationControl = kPWM_Initialize_LocalSync;
 *   config->forceTrigger = kPWM_Force_Local;
 *   config->reloadFrequency = kPWM_LoadEveryOportunity;
 *   config->reloadLogic = kPWM_ReloadImmediate;
 *   config->pairOperation = kPWM_Independent;
 * endcode
 * param config Pointer to user's PWM config structure.
 */
void PWM_GetDefaultConfig(pwm_config_t *config)
{
    assert(config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* PWM is paused in debug mode */
    config->enableDebugMode = false;
    /* PWM is paused in wait mode */
#if !defined(FSL_FEATURE_PWM_HAS_NO_WAITEN) || (!FSL_FEATURE_PWM_HAS_NO_WAITEN)
    config->enableWait = false;
#endif /* FSL_FEATURE_PWM_HAS_NO_WAITEN */
    /* PWM module uses the local reload signal to reload registers */
    config->reloadSelect = kPWM_LocalReload;
    /* Use the IP Bus clock as source clock for the PWM submodule */
    config->clockSource = kPWM_BusClock;
    /* Clock source prescale is set to divide by 1*/
    config->prescale = kPWM_Prescale_Divide_1;
    /* Local sync causes initialization */
    config->initializationControl = kPWM_Initialize_LocalSync;
    /* The local force signal, CTRL2[FORCE], from the submodule is used to force updates */
    config->forceTrigger = kPWM_Force_Local;
    /* PWM reload frequency, reload opportunity is PWM half cycle or full cycle.
     * This field is not used in Immediate reload mode
     */
    config->reloadFrequency = kPWM_LoadEveryOportunity;
    /* Buffered-registers get loaded with new values as soon as LDOK bit is set */
    config->reloadLogic = kPWM_ReloadImmediate;
    /* PWM A & PWM B operate as 2 independent channels */
    config->pairOperation = kPWM_Independent;
}

/*!
 * brief Sets up the PWM signals for a PWM submodule.
 *
 * The function initializes the submodule according to the parameters passed in by the user. The function
 * also sets up the value compare registers to match the PWM signal requirements.
 * If the dead time insertion logic is enabled, the pulse period is reduced by the dead time period specified
 * by the user.
 * Recommend to invoke this API after PWM and fault configuration. But invoke this API before configure MCTRL
 * register is okay, such as set LDOK or start timer.
 * When user select PWMX, user must choose edge aligned output, becasue there are some limitation on center
 * aligned PWMX output.
 * Due to edge aligned PWMX is negative true signal, need to configure PWMX active low true level to get
 * correct duty cycle. The half cycle point will not be exactly in the middle of the PWM cycle when PWMX enabled.
 *
 * param base        PWM peripheral base address
 * param subModule   PWM submodule to configure
 * param chnlParams  Array of PWM channel parameters to configure the channel(s).
 * param numOfChnls  Number of channels to configure, this should be the size of the array passed in.
 *                   Array size should not be more than 3 as each submodule has 3 pins to output PWM.
 * param mode        PWM operation mode, options available in enumeration ::pwm_mode_t
 * param pwmFreq_Hz  PWM signal frequency in Hz
 * param srcClock_Hz PWM source clock of correspond submodule in Hz. If source clock of submodule1,2,3 is from
 *                   submodule0 AUX_CLK, its source clock is submodule0 source clock divided with submodule0
 *                   prescaler value instead of submodule0 source clock.
 *
 * return Returns kStatus_Fail if there was error setting up the signal; kStatus_Success otherwise
 */
status_t PWM_SetupPwm(PWM_Type *base,
                      pwm_submodule_t subModule,
                      const pwm_signal_param_t *chnlParams,
                      uint8_t numOfChnls,
                      pwm_mode_t mode,
                      uint32_t pwmFreq_Hz,
                      uint32_t srcClock_Hz)
{
    assert(chnlParams);
    assert(pwmFreq_Hz);
    assert(numOfChnls);
    assert(srcClock_Hz);

    uint32_t pwmClock;
    uint16_t pulseCnt = 0, pwmHighPulse = 0;
    uint8_t i, polarityShift = 0, outputEnableShift = 0;

    for (i = 0; i < numOfChnls; i++)
    {
        if (chnlParams[i].pwmChannel == kPWM_PwmX && (mode == kPWM_SignedCenterAligned || mode == kPWM_CenterAligned))
        {
            /* Center aligned PWMX configuration is not supported yet. */
            return kStatus_Fail;
        }
    }

    /* Divide the clock by the prescale value */
    pwmClock = (srcClock_Hz / (1UL << ((base->SM[subModule].CTRL & PWM_CTRL_PRSC_MASK) >> PWM_CTRL_PRSC_SHIFT)));
    pulseCnt = (uint16_t)(pwmClock / pwmFreq_Hz);

    /* Update register about period */
    PWM_SetPeriodRegister(base, subModule, mode, pulseCnt);

    /* Setup each PWM channel */
    for (i = 0; i < numOfChnls; i++)
    {
        /* Calculate pulse width */
        pwmHighPulse = (pulseCnt * chnlParams->dutyCyclePercent) / 100U;

        /* Update register about dutycycle */
        PWM_SetDutycycleRegister(base, subModule, chnlParams->pwmChannel, mode, pulseCnt, pwmHighPulse);

        /* Setup register shift values based on the channel being configured.
         * Also setup the deadtime value
         */
        if (chnlParams->pwmChannel == kPWM_PwmA)
        {
            polarityShift              = PWM_OCTRL_POLA_SHIFT;
            outputEnableShift          = PWM_OUTEN_PWMA_EN_SHIFT;
            base->SM[subModule].DTCNT0 = PWM_DTCNT0_DTCNT0(chnlParams->deadtimeValue);
        }
        else if (chnlParams->pwmChannel == kPWM_PwmB)
        {
            polarityShift              = PWM_OCTRL_POLB_SHIFT;
            outputEnableShift          = PWM_OUTEN_PWMB_EN_SHIFT;
            base->SM[subModule].DTCNT1 = PWM_DTCNT1_DTCNT1(chnlParams->deadtimeValue);
        }
        else
        {
            polarityShift     = PWM_OCTRL_POLX_SHIFT;
            outputEnableShift = PWM_OUTEN_PWMX_EN_SHIFT;
        }

        /* Set PWM output fault status */
        switch (chnlParams->pwmChannel)
        {
            case kPWM_PwmA:
                base->SM[subModule].OCTRL &= ~((uint16_t)PWM_OCTRL_PWMAFS_MASK);
                base->SM[subModule].OCTRL |= (((uint16_t)(chnlParams->faultState) << (uint16_t)PWM_OCTRL_PWMAFS_SHIFT) &
                                              (uint16_t)PWM_OCTRL_PWMAFS_MASK);
                break;
            case kPWM_PwmB:
                base->SM[subModule].OCTRL &= ~((uint16_t)PWM_OCTRL_PWMBFS_MASK);
                base->SM[subModule].OCTRL |= (((uint16_t)(chnlParams->faultState) << (uint16_t)PWM_OCTRL_PWMBFS_SHIFT) &
                                              (uint16_t)PWM_OCTRL_PWMBFS_MASK);
                break;
            case kPWM_PwmX:
                base->SM[subModule].OCTRL &= ~((uint16_t)PWM_OCTRL_PWMXFS_MASK);
                base->SM[subModule].OCTRL |= (((uint16_t)(chnlParams->faultState) << (uint16_t)PWM_OCTRL_PWMXFS_SHIFT) &
                                              (uint16_t)PWM_OCTRL_PWMXFS_MASK);
                break;
            default:
                assert(false);
                break;
        }

        /* Setup signal active level */
        if ((bool)chnlParams->level == kPWM_HighTrue)
        {
            base->SM[subModule].OCTRL &= ~((uint16_t)1U << (uint16_t)polarityShift);
        }
        else
        {
            base->SM[subModule].OCTRL |= ((uint16_t)1U << (uint16_t)polarityShift);
        }
        if (chnlParams->pwmchannelenable)
        {
            /* Enable PWM output */
            base->OUTEN |= ((uint16_t)1U << ((uint16_t)outputEnableShift + (uint16_t)subModule));
        }

        /* Get the pwm duty cycle */
        s_pwmGetPwmDutyCycle[subModule][chnlParams->pwmChannel] = chnlParams->dutyCyclePercent;

        /* Get the next channel parameters */
        chnlParams++;
    }

    return kStatus_Success;
}

/*!
 * brief Set PWM phase shift for PWM channel running on channel PWM_A, PWM_B which with 50% duty cycle.
 *
 * param base        PWM peripheral base address
 * param subModule   PWM submodule to configure
 * param pwmChannel  PWM channel to configure
 * param pwmFreq_Hz  PWM signal frequency in Hz
 * param srcClock_Hz PWM main counter clock in Hz.
 * param shiftvalue  Phase shift value, range in 0 ~ 50
 * param doSync      true: Set LDOK bit for the submodule list;
 *                   false: LDOK bit don't set, need to call PWM_SetPwmLdok to sync update.
 *
 * return Returns kStatus_Fail if there was error setting up the signal; kStatus_Success otherwise
 */
status_t PWM_SetupPwmPhaseShift(PWM_Type *base,
                                pwm_submodule_t subModule,
                                pwm_channels_t pwmChannel,
                                uint32_t pwmFreq_Hz,
                                uint32_t srcClock_Hz,
                                uint8_t shiftvalue,
                                bool doSync)
{
    assert(pwmFreq_Hz != 0U);
    assert(srcClock_Hz != 0U);
    assert(shiftvalue <= 50U);

    uint32_t pwmClock;
    uint16_t pulseCnt = 0, pwmHighPulse = 0;
    uint16_t modulo = 0;
    uint16_t shift  = 0;

    if (pwmChannel != kPWM_PwmX)
    {
        /* Divide the clock by the prescale value */
        pwmClock = (srcClock_Hz / (1UL << ((base->SM[subModule].CTRL & PWM_CTRL_PRSC_MASK) >> PWM_CTRL_PRSC_SHIFT)));
        pulseCnt = (uint16_t)(pwmClock / pwmFreq_Hz);

        /* Clear LDOK bit if it is set */
        if (0U != (base->MCTRL & PWM_MCTRL_LDOK(1UL << (uint8_t)subModule)))
        {
            base->MCTRL |= PWM_MCTRL_CLDOK(1UL << (uint8_t)subModule);
        }

        modulo = (pulseCnt >> 1U);
        /* Indicates the start of the PWM period */
        base->SM[subModule].INIT = PWM_GetComplementU16(modulo);
        /* Indicates the center value */
        base->SM[subModule].VAL0 = 0;
        /* Indicates the end of the PWM period */
        /* The change during the end to start of the PWM period requires a count time */
        base->SM[subModule].VAL1 = modulo - 1U;

        /* Immediately upon when MCTRL[LDOK] being set */
        base->SM[subModule].CTRL |= PWM_CTRL_LDMOD_MASK;

        /* phase shift value */
        shift = (pulseCnt * shiftvalue) / 100U;

        /* duty cycle 50% */
        pwmHighPulse = pulseCnt / 2U;

        if (pwmChannel == kPWM_PwmA)
        {
            base->SM[subModule].VAL2 = PWM_GetComplementU16(modulo) + shift;
            base->SM[subModule].VAL3 = PWM_GetComplementU16(modulo) + pwmHighPulse + shift - 1U;
        }
        else if (pwmChannel == kPWM_PwmB)
        {
            base->SM[subModule].VAL4 = PWM_GetComplementU16(modulo) + shift;
            base->SM[subModule].VAL5 = PWM_GetComplementU16(modulo) + pwmHighPulse + shift - 1U;
        }
        else
        {
            return kStatus_Fail;
        }

        if (doSync)
        {
            /* Set LDOK bit to load VALx bit */
            base->MCTRL |= PWM_MCTRL_LDOK(1UL << (uint8_t)subModule);
        }
    }
    else
    {
        return kStatus_Fail;
    }

    return kStatus_Success;
}

/*!
 * brief Updates the PWM signal's dutycycle.
 *
 * The function updates the PWM dutycyle to the new value that is passed in.
 * If the dead time insertion logic is enabled then the pulse period is reduced by the
 * dead time period specified by the user.
 *
 * param base              PWM peripheral base address
 * param subModule         PWM submodule to configure
 * param pwmSignal         Signal (PWM A, PWM B, PWM X) to update
 * param currPwmMode       The current PWM mode set during PWM setup
 * param dutyCyclePercent  New PWM pulse width, value should be between 0 to 100
 *                          0=inactive signal(0% duty cycle)...
 *                          100=active signal (100% duty cycle)
 */
void PWM_UpdatePwmDutycycle(PWM_Type *base,
                            pwm_submodule_t subModule,
                            pwm_channels_t pwmSignal,
                            pwm_mode_t currPwmMode,
                            uint8_t dutyCyclePercent)
{
    assert(dutyCyclePercent <= 100U);
    uint16_t reloadValue = dutyCycleToReloadValue(dutyCyclePercent);

    PWM_UpdatePwmDutycycleHighAccuracy(base, subModule, pwmSignal, currPwmMode, reloadValue);
}

/*!
 * brief Updates the PWM signal's dutycycle with 16-bit accuracy.
 *
 * The function updates the PWM dutycyle to the new value that is passed in.
 * If the dead time insertion logic is enabled then the pulse period is reduced by the
 * dead time period specified by the user.
 *
 * param base              PWM peripheral base address
 * param subModule         PWM submodule to configure
 * param pwmSignal         Signal (PWM A, PWM B, PWM X) to update
 * param currPwmMode       The current PWM mode set during PWM setup
 * param dutyCycle         New PWM pulse width, value should be between 0 to 65535
 *                          0=inactive signal(0% duty cycle)...
 *                          65535=active signal (100% duty cycle)
 */
void PWM_UpdatePwmDutycycleHighAccuracy(
    PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwmSignal, pwm_mode_t currPwmMode, uint16_t dutyCycle)
{
    uint16_t pulseCnt = 0, pwmHighPulse = 0;
    uint16_t pulseEndCnt;
    uint8_t subModuleSync;

    /* If submodule initialization control is Master Sync, PWM period is submodule 0 PWM period. */
    if (((base->SM[subModule].CTRL2 & PWM_CTRL2_INIT_SEL_MASK) >> PWM_CTRL2_INIT_SEL_SHIFT) ==
        kPWM_Initialize_MasterSync)
    {
        subModuleSync = kPWM_Module_0;
    }
    else
    {
        subModuleSync = subModule;
    }

    /* Get pwm period and pulse width. */
    pulseEndCnt = base->SM[subModuleSync].VAL1;
    pulseCnt = pulseEndCnt - base->SM[subModuleSync].INIT + 1U;
    pwmHighPulse = (pulseCnt * dutyCycle) / 65535U;

    /* Update register about dutycycle */
    PWM_SetDutycycleRegister(base, subModule, pwmSignal, currPwmMode, pulseCnt, pwmHighPulse);

    /* Get the pwm duty cycle */
    s_pwmGetPwmDutyCycle[subModule][pwmSignal] = (uint8_t)(dutyCycle * 100U / 65535U);
}

/*!
 * brief Update the PWM signal's period and dutycycle for a PWM submodule.
 *
 * The function updates PWM signal period generated by a specific submodule according to the parameters
 * passed in by the user. This function can also set dutycycle weather you want to keep original dutycycle
 * or update new dutycycle. Call this function in local sync control mode because PWM period is depended by
 * INIT and VAL1 register of each submodule. In master sync initialization control mode, call this function
 * to update INIT and VAL1 register of all submodule because PWM period is depended by INIT and VAL1 register
 * in submodule0. If the dead time insertion logic is enabled, the pulse period is reduced by the dead time
 * period specified by the user. PWM signal will not be generated if its period is less than dead time duration.
 *
 * param base        PWM peripheral base address
 * param subModule   PWM submodule to configure
 * param pwmSignal   Signal (PWM A or PWM B) to update
 * param currPwmMode The current PWM mode set during PWM setup, options available in enumeration ::pwm_mode_t
 * param pulseCnt    New PWM period, value should be between 0 to 65535
 *                    0=minimum PWM period...
 *                    65535=maximum PWM period
 * param dutyCycle   New PWM pulse width of channel, value should be between 0 to 65535
 *                    0=inactive signal(0% duty cycle)...
 *                    65535=active signal (100% duty cycle)
 *                    You can keep original dutycycle or update new dutycycle
 */
void PWM_UpdatePwmPeriodAndDutycycle(PWM_Type *base,
                                     pwm_submodule_t subModule,
                                     pwm_channels_t pwmSignal,
                                     pwm_mode_t currPwmMode,
                                     uint16_t pulseCnt,
                                     uint16_t dutyCycle)
{
    uint16_t pwmHighPulse = 0;

    assert(pwmSignal != kPWM_PwmX);

    /* Calculate pulse width */
    pwmHighPulse = (pulseCnt * dutyCycle) / 65535U;

    /* Update register about period */
    PWM_SetPeriodRegister(base, subModule, currPwmMode, pulseCnt);

    /* Update register about dutycycle */
    PWM_SetDutycycleRegister(base, subModule, pwmSignal, currPwmMode, pulseCnt, pwmHighPulse);

    /* Get the pwm duty cycle */
    s_pwmGetPwmDutyCycle[subModule][pwmSignal] = (uint8_t)((dutyCycle * 100U) / 65535U);
}

/*!
 * brief Sets up the PWM input capture
 *
 * Each PWM submodule has 3 pins that can be configured for use as input capture pins. This function
 * sets up the capture parameters for each pin and enables the pin for input capture operation.
 *
 * param base               PWM peripheral base address
 * param subModule          PWM submodule to configure
 * param pwmChannel         Channel in the submodule to setup
 * param inputCaptureParams Parameters passed in to set up the input pin
 */
void PWM_SetupInputCapture(PWM_Type *base,
                           pwm_submodule_t subModule,
                           pwm_channels_t pwmChannel,
                           const pwm_input_capture_param_t *inputCaptureParams)
{
    uint16_t reg = 0;
    switch (pwmChannel)
    {
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA
        case kPWM_PwmA:
            /* Setup the capture paramters for PWM A pin */
            reg = (PWM_CAPTCTRLA_INP_SELA(inputCaptureParams->captureInputSel) |
                   PWM_CAPTCTRLA_EDGA0(inputCaptureParams->edge0) | PWM_CAPTCTRLA_EDGA1(inputCaptureParams->edge1) |
                   PWM_CAPTCTRLA_ONESHOTA(inputCaptureParams->enableOneShotCapture) |
                   PWM_CAPTCTRLA_CFAWM(inputCaptureParams->fifoWatermark));
            /* Enable the edge counter if using the output edge counter */
            if (inputCaptureParams->captureInputSel)
            {
                reg |= PWM_CAPTCTRLA_EDGCNTA_EN_MASK;
            }
            /* Enable input capture operation */
            reg |= PWM_CAPTCTRLA_ARMA_MASK;

            base->SM[subModule].CAPTCTRLA = reg;

            /* Setup the compare value when using the edge counter as source */
            base->SM[subModule].CAPTCOMPA = PWM_CAPTCOMPA_EDGCMPA(inputCaptureParams->edgeCompareValue);
            /* Setup PWM A pin for input capture */
            base->OUTEN &= ~((uint16_t)1U << (PWM_OUTEN_PWMA_EN_SHIFT + (uint16_t)subModule));
            break;
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB
        case kPWM_PwmB:
            /* Setup the capture paramters for PWM B pin */
            reg = (PWM_CAPTCTRLB_INP_SELB(inputCaptureParams->captureInputSel) |
                   PWM_CAPTCTRLB_EDGB0(inputCaptureParams->edge0) | PWM_CAPTCTRLB_EDGB1(inputCaptureParams->edge1) |
                   PWM_CAPTCTRLB_ONESHOTB(inputCaptureParams->enableOneShotCapture) |
                   PWM_CAPTCTRLB_CFBWM(inputCaptureParams->fifoWatermark));
            /* Enable the edge counter if using the output edge counter */
            if (inputCaptureParams->captureInputSel)
            {
                reg |= PWM_CAPTCTRLB_EDGCNTB_EN_MASK;
            }
            /* Enable input capture operation */
            reg |= PWM_CAPTCTRLB_ARMB_MASK;

            base->SM[subModule].CAPTCTRLB = reg;

            /* Setup the compare value when using the edge counter as source */
            base->SM[subModule].CAPTCOMPB = PWM_CAPTCOMPB_EDGCMPB(inputCaptureParams->edgeCompareValue);
            /* Setup PWM B pin for input capture */
            base->OUTEN &= ~((uint16_t)1U << (PWM_OUTEN_PWMB_EN_SHIFT + (uint16_t)subModule));
            break;
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX
        case kPWM_PwmX:
            reg = (PWM_CAPTCTRLX_INP_SELX(inputCaptureParams->captureInputSel) |
                   PWM_CAPTCTRLX_EDGX0(inputCaptureParams->edge0) | PWM_CAPTCTRLX_EDGX1(inputCaptureParams->edge1) |
                   PWM_CAPTCTRLX_ONESHOTX(inputCaptureParams->enableOneShotCapture) |
                   PWM_CAPTCTRLX_CFXWM(inputCaptureParams->fifoWatermark));
            /* Enable the edge counter if using the output edge counter */
            if (inputCaptureParams->captureInputSel)
            {
                reg |= PWM_CAPTCTRLX_EDGCNTX_EN_MASK;
            }
            /* Enable input capture operation */
            reg |= PWM_CAPTCTRLX_ARMX_MASK;

            base->SM[subModule].CAPTCTRLX = reg;

            /* Setup the compare value when using the edge counter as source */
            base->SM[subModule].CAPTCOMPX = PWM_CAPTCOMPX_EDGCMPX(inputCaptureParams->edgeCompareValue);
            /* Setup PWM X pin for input capture */
            base->OUTEN &= ~((uint16_t)1U << (PWM_OUTEN_PWMX_EN_SHIFT + (uint16_t)subModule));
            break;
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX */
        default:
            assert(false);
            break;
    }
}

/*!
 * @brief Sets up the PWM fault input filter.
 *
 * @param base                   PWM peripheral base address
 * @param faultInputFilterParams Parameters passed in to set up the fault input filter.
 */
void PWM_SetupFaultInputFilter(PWM_Type *base, const pwm_fault_input_filter_param_t *faultInputFilterParams)
{
    assert(NULL != faultInputFilterParams);

    /* When changing values for fault period from a non-zero value, first write a value of 0 to clear the filter. */
    if (0U != (base->FFILT & PWM_FFILT_FILT_PER_MASK))
    {
        base->FFILT &= ~(uint16_t)(PWM_FFILT_FILT_PER_MASK);
    }

    base->FFILT = (uint16_t)(PWM_FFILT_FILT_PER(faultInputFilterParams->faultFilterPeriod) |
                             PWM_FFILT_FILT_CNT(faultInputFilterParams->faultFilterCount) |
                             PWM_FFILT_GSTR(faultInputFilterParams->faultGlitchStretch ? 1U : 0U));
}

/*!
 * brief Sets up the PWM fault protection.
 *
 * PWM has 4 fault inputs.
 *
 * param base        PWM peripheral base address
 * param faultNum    PWM fault to configure.
 * param faultParams Pointer to the PWM fault config structure
 */
void PWM_SetupFaults(PWM_Type *base, pwm_fault_input_t faultNum, const pwm_fault_param_t *faultParams)
{
    assert(faultParams);
    uint16_t reg;

    reg = base->FCTRL;
    /* Set the faults level-settting */
    if (faultParams->faultLevel)
    {
        reg |= ((uint16_t)1U << (PWM_FCTRL_FLVL_SHIFT + (uint16_t)faultNum));
    }
    else
    {
        reg &= ~((uint16_t)1U << (PWM_FCTRL_FLVL_SHIFT + (uint16_t)faultNum));
    }
    /* Set the fault clearing mode */
    if ((uint16_t)faultParams->faultClearingMode != 0U)
    {
        /* Use manual fault clearing */
        reg &= ~((uint16_t)1U << (PWM_FCTRL_FAUTO_SHIFT + (uint16_t)faultNum));
        if (faultParams->faultClearingMode == kPWM_ManualSafety)
        {
            /* Use manual fault clearing with safety mode enabled */
            reg |= ((uint16_t)1U << (PWM_FCTRL_FSAFE_SHIFT + (uint16_t)faultNum));
        }
        else
        {
            /* Use manual fault clearing with safety mode disabled */
            reg &= ~((uint16_t)1U << (PWM_FCTRL_FSAFE_SHIFT + (uint16_t)faultNum));
        }
    }
    else
    {
        /* Use automatic fault clearing */
        reg |= ((uint16_t)1U << (PWM_FCTRL_FAUTO_SHIFT + (uint16_t)faultNum));
    }
    base->FCTRL = reg;

    /* Set the combinational path option */
    if (faultParams->enableCombinationalPath)
    {
        /* Combinational path from the fault input to the PWM output is available */
        base->FCTRL2 &= ~((uint16_t)1U << (uint16_t)faultNum);
    }
    else
    {
        /* No combinational path available, only fault filter & latch signal can disable PWM output */
        base->FCTRL2 |= ((uint16_t)1U << (uint16_t)faultNum);
    }

    /* Initially clear both recovery modes */
    reg = base->FSTS;
    reg &= ~(((uint16_t)1U << (PWM_FSTS_FFULL_SHIFT + (uint16_t)faultNum)) |
             ((uint16_t)1U << (PWM_FSTS_FHALF_SHIFT + (uint16_t)faultNum)));
    /* Setup fault recovery */
    switch (faultParams->recoverMode)
    {
        case kPWM_NoRecovery:
            break;
        case kPWM_RecoverHalfCycle:
            reg |= ((uint16_t)1U << (PWM_FSTS_FHALF_SHIFT + (uint16_t)faultNum));
            break;
        case kPWM_RecoverFullCycle:
            reg |= ((uint16_t)1U << (PWM_FSTS_FFULL_SHIFT + (uint16_t)faultNum));
            break;
        case kPWM_RecoverHalfAndFullCycle:
            reg |= ((uint16_t)1U << (PWM_FSTS_FHALF_SHIFT + (uint16_t)faultNum));
            reg |= ((uint16_t)1U << (PWM_FSTS_FFULL_SHIFT + (uint16_t)faultNum));
            break;
        default:
            assert(false);
            break;
    }
    base->FSTS = reg;
}

/*!
 * brief  Fill in the PWM fault config struct with the default settings
 *
 * The default values are:
 * code
 *   config->faultClearingMode = kPWM_Automatic;
 *   config->faultLevel = false;
 *   config->enableCombinationalPath = true;
 *   config->recoverMode = kPWM_NoRecovery;
 * endcode
 * param config Pointer to user's PWM fault config structure.
 */
void PWM_FaultDefaultConfig(pwm_fault_param_t *config)
{
    assert(config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* PWM uses automatic fault clear mode */
    config->faultClearingMode = kPWM_Automatic;
    /* PWM fault level is set to logic 0 */
    config->faultLevel = false;
    /* Combinational Path from fault input is enabled */
    config->enableCombinationalPath = true;
    /* PWM output will stay inactive when recovering from a fault */
    config->recoverMode = kPWM_NoRecovery;
}

/*!
 * brief Selects the signal to output on a PWM pin when a FORCE_OUT signal is asserted.
 *
 * The user specifies which channel to configure by supplying the submodule number and whether
 * to modify PWM A or PWM B within that submodule.
 *
 * param base       PWM peripheral base address
 * param subModule  PWM submodule to configure
 * param pwmChannel Channel to configure
 * param mode       Signal to output when a FORCE_OUT is triggered
 */
void PWM_SetupForceSignal(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwmChannel, pwm_force_signal_t mode)

{
    uint16_t shift;
    uint16_t reg;

    /* DTSRCSEL register has 4 bits per submodule; 2 bits for PWM A and 2 bits for PWM B */
    shift = ((uint16_t)subModule * 4U) + ((uint16_t)pwmChannel * 2U);

    /* Setup the signal to be passed upon occurrence of a FORCE_OUT signal */
    reg = base->DTSRCSEL;
    reg &= ~((uint16_t)0x3U << shift);
    reg |= (uint16_t)((uint16_t)mode << shift);
    base->DTSRCSEL = reg;
}

/*!
 * brief Set PWM output in idle status (high or low).
 *
 * note This API should call after PWM_SetupPwm() APIs, and PWMX submodule is not supported.
 *
 * param base               PWM peripheral base address
 * param pwmChannel         PWM channel to configure
 * param subModule          PWM submodule to configure
 * param idleStatus         True: PWM output is high in idle status; false: PWM output is low in idle status.
 *
 * return kStatus_Fail if there was error setting up the signal; kStatus_Success if set output idle success
 */
status_t PWM_SetOutputToIdle(PWM_Type *base, pwm_channels_t pwmChannel, pwm_submodule_t subModule, bool idleStatus)
{
    uint16_t valOn = 0, valOff = 0;
    uint16_t ldmod;

    /* Clear LDOK bit if it is set */
    if (0U != (base->MCTRL & PWM_MCTRL_LDOK(1UL << (uint8_t)subModule)))
    {
        base->MCTRL |= PWM_MCTRL_CLDOK(1UL << (uint8_t)subModule);
    }

    valOff = base->SM[subModule].INIT;
    valOn  = base->SM[subModule].VAL1 + 0x1U;

    if ((valOff + 1U) == valOn)
    {
        return kStatus_Fail;
    }

    /* Should not PWM_X channel */
    if (kPWM_PwmA == pwmChannel)
    {
        if (0U != (base->SM[subModule].OCTRL & PWM_OCTRL_POLA_MASK))
        {
            if (!idleStatus)
            {
                valOn  = base->SM[subModule].INIT;
                valOff = base->SM[subModule].VAL1 + 0x1U;
            }
        }
        else
        {
            if (idleStatus)
            {
                valOn  = base->SM[subModule].INIT;
                valOff = base->SM[subModule].VAL1 + 0x1U;
            }
        }
        base->SM[subModule].VAL2 = valOn;
        base->SM[subModule].VAL3 = valOff;
    }
    else if (kPWM_PwmB == pwmChannel)
    {
        if (0U != (base->SM[subModule].OCTRL & PWM_OCTRL_POLB_MASK))
        {
            if (!idleStatus)
            {
                valOn  = base->SM[subModule].INIT;
                valOff = base->SM[subModule].VAL1 + 0x1U;
            }
        }
        else
        {
            if (idleStatus)
            {
                valOn  = base->SM[subModule].INIT;
                valOff = base->SM[subModule].VAL1 + 0x1U;
            }
        }
        base->SM[subModule].VAL4 = valOn;
        base->SM[subModule].VAL5 = valOff;
    }
    else
    {
        return kStatus_Fail;
    }

    /* Record Load mode */
    ldmod = base->SM[subModule].CTRL;
    /* Set Load mode to make Buffered registers take effect immediately when LDOK bit set */
    base->SM[subModule].CTRL |= PWM_CTRL_LDMOD_MASK;
    /* Set LDOK bit to load buffer registers */
    base->MCTRL |= PWM_MCTRL_LDOK(1UL << (uint8_t)subModule);
    /* Restore Load mode */
    base->SM[subModule].CTRL = ldmod;

    /* Get pwm duty cycle */
    s_pwmGetPwmDutyCycle[subModule][pwmChannel] = 0x0U;

    return kStatus_Success;
}

/*!
 * brief Get the dutycycle value.
 *
 * param base        PWM peripheral base address
 * param subModule   PWM submodule to configure
 * param pwmChannel  PWM channel to configure
 *
 * return Current channel dutycycle value.
 */
uint8_t PWM_GetPwmChannelState(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwmChannel)
{
    return s_pwmGetPwmDutyCycle[subModule][pwmChannel];
}

/*!
 * brief Set the pwm submodule prescaler.
 *
 * param base               PWM peripheral base address
 * param subModule          PWM submodule to configure
 * param prescaler          Set prescaler value
 */
void PWM_SetClockMode(PWM_Type *base, pwm_submodule_t subModule, pwm_clock_prescale_t prescaler)
{
    uint16_t reg = base->SM[subModule].CTRL;

    /* Clear LDOK bit if it is set */
    if (0U != (base->MCTRL & PWM_MCTRL_LDOK(1UL << (uint8_t)subModule)))
    {
        base->MCTRL |= PWM_MCTRL_CLDOK(1UL << (uint8_t)subModule);
    }
    /* Set submodule prescaler. */
    reg &= ~(uint16_t)PWM_CTRL_PRSC_MASK;
    reg |= PWM_CTRL_PRSC(prescaler);
    base->SM[subModule].CTRL = reg;
    /* Set Load mode to make Buffered registers take effect immediately when LDOK bit set */
    base->SM[subModule].CTRL |= PWM_CTRL_LDMOD_MASK;
    /* Set LDOK bit to load buffer registers */
    base->MCTRL |= PWM_MCTRL_LDOK(1UL << (uint8_t)subModule);
    /* Restore Load mode */
    base->SM[subModule].CTRL = reg;
}

/*!
 * brief This function enables-disables the forcing of the output of a given eFlexPwm channel to logic 0.
 *
 * param base               PWM peripheral base address
 * param pwmChannel         PWM channel to configure
 * param subModule          PWM submodule to configure
 * param forcetozero        True: Enable the pwm force output to zero; False: Disable the pwm output resumes normal
 *                          function.
 */
void PWM_SetPwmForceOutputToZero(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwmChannel, bool forcetozero)
{
#if !defined(PWM_MASK_UPDATE_MASK)
    uint16_t reg = base->SM[subModule].CTRL2;
#endif
    uint16_t mask;

    if (kPWM_PwmA == pwmChannel)
    {
        mask = PWM_MASK_MASKA(0x01UL << (uint8_t)subModule);
    }
    else if (kPWM_PwmB == pwmChannel)
    {
        mask = PWM_MASK_MASKB(0x01UL << (uint8_t)subModule);
    }
    else
    {
        mask = PWM_MASK_MASKX(0x01UL << (uint8_t)subModule);
    }

    if (forcetozero)
    {
        /* Disables the channel output, forcing output level to 0 */
        base->MASK |= mask;
    }
    else
    {
        /* Enables the channel output */
        base->MASK &= ~mask;
    }

#if defined(PWM_MASK_UPDATE_MASK)
    /* Update output mask bits immediately with UPDATE_MASK bit */
    base->MASK |= PWM_MASK_UPDATE_MASK(0x01UL << (uint8_t)subModule);
#else
    /* Select local force signal */
    base->SM[subModule].CTRL2 &= ~(uint16_t)PWM_CTRL2_FORCE_SEL_MASK;
    /* Issue a local Force trigger event */
    base->SM[subModule].CTRL2 |= PWM_CTRL2_FORCE_MASK;
    /* Restore the source of FORCE OUTPUT signal */
    base->SM[subModule].CTRL2 = reg;
#endif
}

/*!
 * brief This function set the output state of the PWM pin as requested for the current cycle.
 *
 * param base               PWM peripheral base address
 * param subModule          PWM submodule to configure
 * param pwmChannel         PWM channel to configure
 * param outputstate        Set pwm output state, see @ref pwm_output_state_t.
 */
void PWM_SetChannelOutput(PWM_Type *base,
                          pwm_submodule_t subModule,
                          pwm_channels_t pwmChannel,
                          pwm_output_state_t outputstate)
{
    uint16_t mask, swcout, sourceShift;
    uint16_t reg = base->SM[subModule].CTRL2;

    if (kPWM_PwmA == pwmChannel)
    {
        mask        = PWM_MASK_MASKA(0x01UL << (uint8_t)subModule);
        swcout      = (uint16_t)PWM_SWCOUT_SM0OUT23_MASK << ((uint8_t)subModule * 2U);
        sourceShift = PWM_DTSRCSEL_SM0SEL23_SHIFT + ((uint16_t)subModule * 4U);
    }
    else if (kPWM_PwmB == pwmChannel)
    {
        mask        = PWM_MASK_MASKB(0x01UL << (uint8_t)subModule);
        swcout      = (uint16_t)PWM_SWCOUT_SM0OUT45_MASK << ((uint8_t)subModule * 2U);
        sourceShift = PWM_DTSRCSEL_SM0SEL45_SHIFT + ((uint16_t)subModule * 4U);
    }
    else
    {
        mask        = PWM_MASK_MASKX(0x01UL << (uint8_t)subModule);
        swcout      = 0U;
        sourceShift = 0U;
    }

    if (kPWM_MaskState == outputstate)
    {
        /* Disables the channel output, forcing output level to 0 */
        base->MASK |= mask;
    }
    else
    {
        /* Enables the channel output first */
        base->MASK &= ~mask;
        /* PwmX only support MASK mode */
        if (kPWM_PwmX != pwmChannel)
        {
            if (kPWM_HighState == outputstate)
            {
                base->SWCOUT |= swcout;
                base->DTSRCSEL =
                    (base->DTSRCSEL & ~(uint16_t)(0x3UL << sourceShift)) | (uint16_t)(0x2UL << sourceShift);
            }
            else if (kPWM_LowState == outputstate)
            {
                base->SWCOUT &= ~swcout;
                base->DTSRCSEL =
                    (base->DTSRCSEL & ~(uint16_t)(0x3UL << sourceShift)) | (uint16_t)(0x2UL << sourceShift);
            }
            else if (kPWM_NormalState == outputstate)
            {
                base->DTSRCSEL &= ~(uint16_t)(0x3UL << sourceShift);
            }
            else
            {
                base->DTSRCSEL =
                    (base->DTSRCSEL & ~(uint16_t)(0x3UL << sourceShift)) | (uint16_t)(0x1UL << sourceShift);
            }
        }
    }

    /* Select local force signal */
    base->SM[subModule].CTRL2 &= ~(uint16_t)PWM_CTRL2_FORCE_SEL_MASK;
    /* Issue a local Force trigger event */
    base->SM[subModule].CTRL2 |= PWM_CTRL2_FORCE_MASK;
    /* Restore the source of FORCE OUTPUT signal */
    base->SM[subModule].CTRL2 = reg;
}

#if defined(FSL_FEATURE_PWM_HAS_PHASE_DELAY) && FSL_FEATURE_PWM_HAS_PHASE_DELAY
/*!
 * brief This function set the phase delay from the master sync signal of submodule 0.
 *
 * param base               PWM peripheral base address
 * param subModule          PWM submodule to configure
 * param pwmChannel         PWM channel to configure
 * param delayCycles        Number of cycles delayed from submodule 0.
 *
 * return kStatus_Fail if the number of delay cycles is set larger than the period defined in submodule 0;
 *        kStatus_Success if set phase delay success
 */
status_t PWM_SetPhaseDelay(PWM_Type *base, pwm_channels_t pwmChannel, pwm_submodule_t subModule, uint16_t delayCycles)
{
    assert(subModule != kPWM_Module_0);
    uint16_t reg = base->SM[subModule].CTRL2;

    /* Clear LDOK bit if it is set */
    if (0U != (base->MCTRL & PWM_MCTRL_LDOK(1UL << (uint8_t)subModule)))
    {
        base->MCTRL |= PWM_MCTRL_CLDOK(1UL << (uint8_t)subModule);
    }

    if (base->SM[kPWM_Module_0].VAL1 < delayCycles)
    {
        return kStatus_Fail;
    }
    else
    {
        /*
         * ERR051989: When the value of the phase delay register SMxPHASEDLY is reduced from a
         * non-zero value to 0 and submodule x reload source is from submodule0, the submodule
         * x may output an unexpected wide PWM pulse. The workaround is set SMxPHASEDLY=1,
         * SMxINIT=SM0INIT-1, SMxVALy=SM0VALy-1 (x=1,2,3, y=0,1,2,3,4,5).
         */
#if defined(FSL_FEATURE_PWM_HAS_ERRATA_51989) && FSL_FEATURE_PWM_HAS_ERRATA_51989
        if (delayCycles == 0 &&
            ((base->SM[subModule].CTRL2 & PWM_CTRL2_RELOAD_SEL_MASK) >> PWM_CTRL2_RELOAD_SEL_SHIFT) == 1U)
        {
            base->SM[subModule].PHASEDLY = 1U;
            base->SM[subModule].INIT     = base->SM[0].INIT - 1U;
            base->SM[subModule].VAL0     = base->SM[0].VAL0 - 1U;
            base->SM[subModule].VAL1     = base->SM[0].VAL1 - 1U;
            base->SM[subModule].VAL2     = base->SM[0].VAL2 - 1U;
            base->SM[subModule].VAL3     = base->SM[0].VAL3 - 1U;
            base->SM[subModule].VAL4     = base->SM[0].VAL4 - 1U;
            base->SM[subModule].VAL5     = base->SM[0].VAL5 - 1U;
        }
        else
        {
            base->SM[subModule].PHASEDLY = delayCycles;
        }
#else
        base->SM[subModule].PHASEDLY = delayCycles;
#endif
    }

    /* Select the master sync signal as the source for initialization */
    reg = (reg & ~(uint16_t)PWM_CTRL2_INIT_SEL_MASK) | PWM_CTRL2_INIT_SEL(2);
    /* Set Load mode to make Buffered registers take effect immediately when LDOK bit set */
    base->SM[subModule].CTRL |= PWM_CTRL_LDMOD_MASK;
    /* Set LDOK bit to load buffer registers */
    base->MCTRL |= PWM_MCTRL_LDOK(1UL << (uint8_t)subModule);
    /* Restore the source of phase delay register intialization */
    base->SM[subModule].CTRL2 = reg;
    return kStatus_Success;
}
#endif /* FSL_FEATURE_PWM_HAS_PHASE_DELAY */
