/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ctimer.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ctimer"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Gets the instance from the base address
 *
 * @param base Ctimer peripheral base address
 *
 * @return The Timer instance
 */
static uint32_t CTIMER_GetInstance(CTIMER_Type *base);

/*!
 * @brief CTIMER generic IRQ handle function.
 *
 * @param index FlexCAN peripheral instance index.
 */
static void CTIMER_GenericIRQHandler(uint32_t index);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to Timer bases for each instance. */
static CTIMER_Type *const s_ctimerBases[] = CTIMER_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to Timer clocks for each instance. */
static const clock_ip_name_t s_ctimerClocks[] = CTIMER_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_CTIMER_HAS_NO_RESET) && (FSL_FEATURE_CTIMER_HAS_NO_RESET))
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
#if defined(FSL_FEATURE_CTIMER_WRITE_ZERO_ASSERT_RESET) && FSL_FEATURE_CTIMER_WRITE_ZERO_ASSERT_RESET
/*! @brief Pointers to Timer resets for each instance, writing a zero asserts the reset */
static const reset_ip_name_t s_ctimerResets[] = CTIMER_RSTS_N;
#else
/*! @brief Pointers to Timer resets for each instance, writing a one asserts the reset */
static const reset_ip_name_t s_ctimerResets[] = CTIMER_RSTS;
#endif
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

/*! @brief Pointers real ISRs installed by drivers for each instance. */
static ctimer_callback_t *s_ctimerCallback[sizeof(s_ctimerBases) / sizeof(s_ctimerBases[0])] = {0};

/*! @brief Callback type installed by drivers for each instance. */
static ctimer_callback_type_t ctimerCallbackType[sizeof(s_ctimerBases) / sizeof(s_ctimerBases[0])] = {
    kCTIMER_SingleCallback};

/*! @brief Array to map timer instance to IRQ number. */
static const IRQn_Type s_ctimerIRQ[] = CTIMER_IRQS;

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t CTIMER_GetInstance(CTIMER_Type *base)
{
    uint32_t instance;
    uint32_t ctimerArrayCount = (sizeof(s_ctimerBases) / sizeof(s_ctimerBases[0]));

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ctimerArrayCount; instance++)
    {
        if (s_ctimerBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ctimerArrayCount);

    return instance;
}

/*!
 * brief Ungates the clock and configures the peripheral for basic operation.
 *
 * note This API should be called at the beginning of the application before using the driver.
 *
 * param base   Ctimer peripheral base address
 * param config Pointer to the user configuration structure.
 */
void CTIMER_Init(CTIMER_Type *base, const ctimer_config_t *config)
{
    assert(config != NULL);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the timer clock*/
    CLOCK_EnableClock(s_ctimerClocks[CTIMER_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
/* Reset the module. */
#if !(defined(FSL_FEATURE_CTIMER_HAS_NO_RESET) && (FSL_FEATURE_CTIMER_HAS_NO_RESET))
    RESET_PeripheralReset(s_ctimerResets[CTIMER_GetInstance(base)]);
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

/* Setup the cimer mode and count select */
#if !(defined(FSL_FEATURE_CTIMER_HAS_NO_INPUT_CAPTURE) && (FSL_FEATURE_CTIMER_HAS_NO_INPUT_CAPTURE))
    base->CTCR = CTIMER_CTCR_CTMODE(config->mode) | CTIMER_CTCR_CINSEL(config->input);
#endif
    /* Setup the timer prescale value */
    base->PR = CTIMER_PR_PRVAL(config->prescale);
}

/*!
 * brief Gates the timer clock.
 *
 * param base Ctimer peripheral base address
 */
void CTIMER_Deinit(CTIMER_Type *base)
{
    uint32_t index = CTIMER_GetInstance(base);
    /* Stop the timer */
    base->TCR &= ~CTIMER_TCR_CEN_MASK;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the timer clock*/
    CLOCK_DisableClock(s_ctimerClocks[index]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Disable IRQ at NVIC Level */
    (void)DisableIRQ(s_ctimerIRQ[index]);
}

/*!
 * brief  Fills in the timers configuration structure with the default settings.
 *
 * The default values are:
 * code
 *   config->mode = kCTIMER_TimerMode;
 *   config->input = kCTIMER_Capture_0;
 *   config->prescale = 0;
 * endcode
 * param config Pointer to the user configuration structure.
 */
void CTIMER_GetDefaultConfig(ctimer_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Run as a timer */
    config->mode = kCTIMER_TimerMode;
    /* This field is ignored when mode is timer */
    config->input = kCTIMER_Capture_0;
    /* Timer counter is incremented on every APB bus clock */
    config->prescale = 0;
}

/*!
 * brief Configures the PWM signal parameters.
 *
 * Enables PWM mode on the match channel passed in and will then setup the match value
 * and other match parameters to generate a PWM signal.
 * This function can manually assign the specified channel to set the PWM cycle.
 *
 * note When setting PWM output from multiple output pins, all should use the same PWM
 * frequency. Please use CTIMER_SetupPwmPeriod to set up the PWM with high resolution.
 *
 * param base             Ctimer peripheral base address
 * param pwmPeriodChannel Specify the channel to control the PWM period
 * param matchChannel     Match pin to be used to output the PWM signal
 * param dutyCyclePercent PWM pulse width; the value should be between 0 to 100
 * param pwmFreq_Hz       PWM signal frequency in Hz
 * param srcClock_Hz      Timer counter clock in Hz
 * param enableInt        Enable interrupt when the timer value reaches the match value of the PWM pulse,
 *                         if it is 0 then no interrupt will be generated.
 *
 * return kStatus_Success on success
 *         kStatus_Fail If matchChannel is equal to pwmPeriodChannel; this channel is reserved to set the PWM cycle
 */
status_t CTIMER_SetupPwm(CTIMER_Type *base,
                         const ctimer_match_t pwmPeriodChannel,
                         ctimer_match_t matchChannel,
                         uint8_t dutyCyclePercent,
                         uint32_t pwmFreq_Hz,
                         uint32_t srcClock_Hz,
                         bool enableInt)
{
    assert(pwmFreq_Hz > 0U);

    uint32_t reg;
    uint32_t period, pulsePeriod = 0;
    uint32_t timerClock = srcClock_Hz / (base->PR + 1U);
    uint32_t index      = CTIMER_GetInstance(base);

    if (matchChannel == pwmPeriodChannel)
    {
        return kStatus_Fail;
    }

    /* Enable PWM mode on the match channel */
    base->PWMC |= (1UL << (uint32_t)matchChannel);

    /* Clear the stop, reset and interrupt bits for this channel */
    reg = base->MCR;
    reg &=
        ~(((uint32_t)((uint32_t)CTIMER_MCR_MR0R_MASK | (uint32_t)CTIMER_MCR_MR0S_MASK | (uint32_t)CTIMER_MCR_MR0I_MASK))
          << ((uint32_t)matchChannel * 3U));

    /* If call back function is valid then enable match interrupt for the channel */
    if (enableInt)
    {
        reg |= (((uint32_t)CTIMER_MCR_MR0I_MASK) << (CTIMER_MCR_MR0I_SHIFT + ((uint32_t)matchChannel * 3U)));
    }

    /* Reset the counter when match on PWM period channel (pwmPeriodChannel)  */
    reg |= ((uint32_t)((uint32_t)CTIMER_MCR_MR0R_MASK) << ((uint32_t)pwmPeriodChannel * 3U));

    base->MCR = reg;

    /* Calculate PWM period match value */
    period = (timerClock / pwmFreq_Hz) - 1U;

    /* Calculate pulse width match value */
    if (dutyCyclePercent == 0U)
    {
        pulsePeriod = period + 1U;
    }
    else
    {
        pulsePeriod = (period * (100U - (uint32_t)dutyCyclePercent)) / 100U;
    }

    /* Specified channel pwmPeriodChannel will define the PWM period */
    base->MR[pwmPeriodChannel] = period;

    /* This will define the PWM pulse period */
    base->MR[matchChannel] = pulsePeriod;
    /* Clear status flags */
    CTIMER_ClearStatusFlags(base, ((uint32_t)CTIMER_IR_MR0INT_MASK) << (uint32_t)matchChannel);
    /* If call back function is valid then enable interrupt and update the call back function */
    if (enableInt)
    {
        (void)EnableIRQ(s_ctimerIRQ[index]);
    }

    return kStatus_Success;
}

/*!
 * brief Configures the PWM signal parameters.
 *
 * Enables PWM mode on the match channel passed in and will then setup the match value
 * and other match parameters to generate a PWM signal.
 * This function can manually assign the specified channel to set the PWM cycle.
 *
 * note When setting PWM output from multiple output pins, all should use the same PWM
 * period
 *
 * param base             Ctimer peripheral base address
 * param pwmPeriodChannel Specify the channel to control the PWM period
 * param matchChannel     Match pin to be used to output the PWM signal
 * param pwmPeriod        PWM period match value
 * param pulsePeriod      Pulse width match value
 * param enableInt        Enable interrupt when the timer value reaches the match value of the PWM pulse,
 *                         if it is 0 then no interrupt will be generated.
 *
 * return kStatus_Success on success
 *         kStatus_Fail If matchChannel is equal to pwmPeriodChannel; this channel is reserved to set the PWM period
 */
status_t CTIMER_SetupPwmPeriod(CTIMER_Type *base,
                               const ctimer_match_t pwmPeriodChannel,
                               ctimer_match_t matchChannel,
                               uint32_t pwmPeriod,
                               uint32_t pulsePeriod,
                               bool enableInt)
{
/* Some CTimers only have 16bits , so the value is limited*/
#if defined(FSL_FEATURE_SOC_CTIMER16B) && FSL_FEATURE_SOC_CTIMER16B
    assert(!((FSL_FEATURE_CTIMER_BIT_SIZEn(base) < 32) && (pulsePeriod > 0xFFFFU)));
#endif

    uint32_t reg;
    uint32_t index = CTIMER_GetInstance(base);

    if (matchChannel == pwmPeriodChannel)
    {
        return kStatus_Fail;
    }

    /* Enable PWM mode on PWM pulse channel */
    base->PWMC |= (1UL << (uint32_t)matchChannel);

    /* Clear the stop, reset and interrupt bits for PWM pulse channel */
    reg = base->MCR;
    reg &=
        ~((uint32_t)((uint32_t)CTIMER_MCR_MR0R_MASK | (uint32_t)CTIMER_MCR_MR0S_MASK | (uint32_t)CTIMER_MCR_MR0I_MASK)
          << ((uint32_t)matchChannel * 3U));

    /* If call back function is valid then enable match interrupt for PWM pulse channel */
    if (enableInt)
    {
        reg |= (((uint32_t)CTIMER_MCR_MR0I_MASK) << (CTIMER_MCR_MR0I_SHIFT + ((uint32_t)matchChannel * 3U)));
    }

    /* Reset the counter when match on PWM period channel (pwmPeriodChannel)  */
    reg |= ((uint32_t)((uint32_t)CTIMER_MCR_MR0R_MASK) << ((uint32_t)pwmPeriodChannel * 3U));

    base->MCR = reg;

    /* Specified channel pwmPeriodChannel will define the PWM period */
    base->MR[pwmPeriodChannel] = pwmPeriod;

    /* This will define the PWM pulse period */
    base->MR[matchChannel] = pulsePeriod;
    /* Clear status flags */
    CTIMER_ClearStatusFlags(base, ((uint32_t)CTIMER_IR_MR0INT_MASK) << (uint32_t)matchChannel);
    /* If call back function is valid then enable interrupt and update the call back function */
    if (enableInt)
    {
        (void)EnableIRQ(s_ctimerIRQ[index]);
    }

    return kStatus_Success;
}

/*!
 * brief Updates the duty cycle of an active PWM signal.
 *
 * note Please use CTIMER_SetupPwmPeriod to update the PWM with high resolution.
 * This function can manually assign the specified channel to set the PWM cycle.
 *
 * param base             Ctimer peripheral base address
 * param pwmPeriodChannel Specify the channel to control the PWM period
 * param matchChannel     Match pin to be used to output the PWM signal
 * param dutyCyclePercent New PWM pulse width; the value should be between 0 to 100
 */
void CTIMER_UpdatePwmDutycycle(CTIMER_Type *base,
                               const ctimer_match_t pwmPeriodChannel,
                               ctimer_match_t matchChannel,
                               uint8_t dutyCyclePercent)
{
    uint32_t pulsePeriod = 0, period;

    /* Specified channel pwmPeriodChannel  defines the PWM period */
    period = base->MR[pwmPeriodChannel];

    /* For 0% dutycyle, make pulse period greater than period so the event will never occur */
    if (dutyCyclePercent == 0U)
    {
        pulsePeriod = period + 1U;
    }
    else
    {
        pulsePeriod = (period * (100U - (uint32_t)dutyCyclePercent)) / 100U;
    }

    /* Update dutycycle */
    base->MR[matchChannel] = pulsePeriod;
}

/*!
 * brief Setup the match register.
 *
 * User configuration is used to setup the match value and action to be taken when a match occurs.
 *
 * param base         Ctimer peripheral base address
 * param matchChannel Match register to configure
 * param config       Pointer to the match configuration structure
 */
void CTIMER_SetupMatch(CTIMER_Type *base, ctimer_match_t matchChannel, const ctimer_match_config_t *config)
{
/* Some CTimers only have 16bits , so the value is limited*/
#if defined(FSL_FEATURE_SOC_CTIMER16B) && FSL_FEATURE_SOC_CTIMER16B
    assert(!(FSL_FEATURE_CTIMER_BIT_SIZEn(base) < 32 && config->matchValue > 0xFFFFU));
#endif
    uint32_t reg;
    uint32_t index = CTIMER_GetInstance(base);

    /* Set the counter operation when a match on this channel occurs */
    reg = base->MCR;
    reg &=
        ~((uint32_t)((uint32_t)CTIMER_MCR_MR0R_MASK | (uint32_t)CTIMER_MCR_MR0S_MASK | (uint32_t)CTIMER_MCR_MR0I_MASK)
          << ((uint32_t)matchChannel * 3U));
    reg |= ((uint32_t)(config->enableCounterReset) << (CTIMER_MCR_MR0R_SHIFT + ((uint32_t)matchChannel * 3U)));
    reg |= ((uint32_t)(config->enableCounterStop) << (CTIMER_MCR_MR0S_SHIFT + ((uint32_t)matchChannel * 3U)));
    reg |= ((uint32_t)(config->enableInterrupt) << (CTIMER_MCR_MR0I_SHIFT + ((uint32_t)matchChannel * 3U)));
    base->MCR = reg;

    reg = base->EMR;
    /* Set the match output operation when a match on this channel occurs */
    reg &= ~(((uint32_t)CTIMER_EMR_EMC0_MASK) << ((uint32_t)matchChannel * 2U));
    reg |= ((uint32_t)config->outControl) << (CTIMER_EMR_EMC0_SHIFT + ((uint32_t)matchChannel * 2U));

    /* Set the initial state of the EM bit/output */
    reg &= ~(((uint32_t)CTIMER_EMR_EM0_MASK) << (uint32_t)matchChannel);
    reg |= ((uint32_t)config->outPinInitState) << (uint32_t)matchChannel;
    base->EMR = reg;

    /* Set the match value */
    base->MR[matchChannel] = config->matchValue;
    /* Clear status flags */
    CTIMER_ClearStatusFlags(base, ((uint32_t)CTIMER_IR_MR0INT_MASK) << (uint32_t)matchChannel);
    /* If interrupt is enabled then enable interrupt and update the call back function */
    if (config->enableInterrupt)
    {
        (void)EnableIRQ(s_ctimerIRQ[index]);
    }
}

/*!
 * brief Get the status of output match.
 *
 * This function gets the status of output MAT, whether or not this output is connected to a pin.
 * This status is driven to the MAT pins if the match function is selected via IOCON. 0 = LOW. 1 = HIGH.
 *
 * param base         Ctimer peripheral base address
 * param matchChannel External match channel, user can obtain the status of multiple match channels
 *                    at the same time by using the logic of "|"
 *                    enumeration ::ctimer_external_match_t
 * return The mask of external match channel status flags. Users need to use the
 *        _ctimer_external_match type to decode the return variables.
 */
uint32_t CTIMER_GetOutputMatchStatus(CTIMER_Type *base, uint32_t matchChannel)
{
    return (base->EMR & matchChannel);
}

#if !(defined(FSL_FEATURE_CTIMER_HAS_NO_INPUT_CAPTURE) && (FSL_FEATURE_CTIMER_HAS_NO_INPUT_CAPTURE))
/*!
 * brief Setup the capture.
 *
 * param base      Ctimer peripheral base address
 * param capture   Capture channel to configure
 * param edge      Edge on the channel that will trigger a capture
 * param enableInt Flag to enable channel interrupts, if enabled then the registered call back
 *                  is called upon capture
 */
void CTIMER_SetupCapture(CTIMER_Type *base,
                         ctimer_capture_channel_t capture,
                         ctimer_capture_edge_t edge,
                         bool enableInt)
{
    uint32_t reg   = base->CCR;
    uint32_t index = CTIMER_GetInstance(base);

    /* Set the capture edge */
    reg &= ~((uint32_t)((uint32_t)CTIMER_CCR_CAP0RE_MASK | (uint32_t)CTIMER_CCR_CAP0FE_MASK |
                        (uint32_t)CTIMER_CCR_CAP0I_MASK)
             << ((uint32_t)capture * 3U));
    reg |= ((uint32_t)edge) << (CTIMER_CCR_CAP0RE_SHIFT + ((uint32_t)capture * 3U));
    /* Clear status flags */
    CTIMER_ClearStatusFlags(base, (((uint32_t)kCTIMER_Capture0Flag) << (uint32_t)capture));
    /* If call back function is valid then enable capture interrupt for the channel and update the call back function */
    if (enableInt)
    {
        reg |= ((uint32_t)CTIMER_CCR_CAP0I_MASK) << ((uint32_t)capture * 3U);
        (void)EnableIRQ(s_ctimerIRQ[index]);
    }
    base->CCR = reg;
}
#endif

/*!
 * brief Register callback.
 *
 * param base      Ctimer peripheral base address
 * param cb_func   callback function
 * param cb_type   callback function type, singular or multiple
 */
void CTIMER_RegisterCallBack(CTIMER_Type *base, ctimer_callback_t *cb_func, ctimer_callback_type_t cb_type)
{
    uint32_t index            = CTIMER_GetInstance(base);
    s_ctimerCallback[index]   = cb_func;
    ctimerCallbackType[index] = cb_type;
}

/*!
 * brief CTIMER generic IRQ handle function.
 *
 * param index FlexCAN peripheral instance index.
 */
static void CTIMER_GenericIRQHandler(uint32_t index)
{
    uint32_t int_stat, i, mask;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(s_ctimerBases[index]);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(s_ctimerBases[index], int_stat);
    if (ctimerCallbackType[index] == kCTIMER_SingleCallback)
    {
        if (s_ctimerCallback[index][0] != NULL)
        {
            s_ctimerCallback[index][0](int_stat);
        }
    }
    else
    {
#if defined(FSL_FEATURE_CTIMER_HAS_NO_INPUT_CAPTURE) && FSL_FEATURE_CTIMER_HAS_NO_INPUT_CAPTURE
        for (i = 0; i <= CTIMER_IR_MR3INT_SHIFT; i++)
#else
#if defined(FSL_FEATURE_CTIMER_HAS_IR_CR3INT) && FSL_FEATURE_CTIMER_HAS_IR_CR3INT
        for (i = 0; i <= CTIMER_IR_CR3INT_SHIFT; i++)
#else
#if !(defined(FSL_FEATURE_CTIMER_HAS_NO_IR_CR2INT) && FSL_FEATURE_CTIMER_HAS_NO_IR_CR2INT)
        for (i = 0; i <= CTIMER_IR_CR2INT_SHIFT; i++)
#else
        for (i = 0; i <= CTIMER_IR_CR1INT_SHIFT; i++)
#endif /* FSL_FEATURE_CTIMER_HAS_NO_IR_CR2INT */
#endif /* FSL_FEATURE_CTIMER_HAS_IR_CR3INT */
#endif
        {
            mask = 0x01UL << i;
            /* For each status flag bit that was set call the callback function if it is valid */
            if (((int_stat & mask) != 0U) && (s_ctimerCallback[index][i] != NULL))
            {
                s_ctimerCallback[index][i](int_stat);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

/* IRQ handler functions overloading weak symbols in the startup */
#if defined(CTIMER0)
void CTIMER0_DriverIRQHandler(void);
void CTIMER0_DriverIRQHandler(void)
{
    CTIMER_GenericIRQHandler(0);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(CTIMER1)
void CTIMER1_DriverIRQHandler(void);
void CTIMER1_DriverIRQHandler(void)
{
    CTIMER_GenericIRQHandler(1);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(CTIMER2)
void CTIMER2_DriverIRQHandler(void);
void CTIMER2_DriverIRQHandler(void)
{
    CTIMER_GenericIRQHandler(2);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(CTIMER3)
void CTIMER3_DriverIRQHandler(void);
void CTIMER3_DriverIRQHandler(void)
{
    CTIMER_GenericIRQHandler(3);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(CTIMER4)
void CTIMER4_DriverIRQHandler(void);
void CTIMER4_DriverIRQHandler(void)
{
    CTIMER_GenericIRQHandler(4);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(CTIMER5)
void CTIMER5_DriverIRQHandler(void);
void CTIMER5_DriverIRQHandler(void)
{
    CTIMER_GenericIRQHandler(5);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(CTIMER6)
void CTIMER6_DriverIRQHandler(void);
void CTIMER6_DriverIRQHandler(void)
{
    CTIMER_GenericIRQHandler(6);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(CTIMER7)
void CTIMER7_DriverIRQHandler(void);
void CTIMER7_DriverIRQHandler(void)
{
    CTIMER_GenericIRQHandler(7);
    SDK_ISR_EXIT_BARRIER;
}
#endif
