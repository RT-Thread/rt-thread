/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sctimer.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sctimer"
#endif
#if defined(SCT_RSTS_N) || defined(SCT_RSTS)
#define FSL_FEATURE_SCT_HAS_RESET
#endif


/*! @brief Typedef for interrupt handler. */
typedef void (*sctimer_isr_t)(SCT_Type *base);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Gets the instance from the base address
 *
 * @param base SCTimer peripheral base address
 *
 * @return The SCTimer instance
 */
static uint32_t SCTIMER_GetInstance(SCT_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to SCT bases for each instance. */
static SCT_Type *const s_sctBases[] = SCT_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to SCT clocks for each instance. */
static const clock_ip_name_t s_sctClocks[] = SCT_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(FSL_FEATURE_SCT_HAS_RESET)
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
#if defined(FSL_FEATURE_SCT_WRITE_ZERO_ASSERT_RESET) && FSL_FEATURE_SCT_WRITE_ZERO_ASSERT_RESET
/*! @brief Pointers to SCT resets for each instance, writing a zero asserts the reset */
static const reset_ip_name_t s_sctResets[] = SCT_RSTS_N;
#else
/*! @brief Pointers to SCT resets for each instance, writing a one asserts the reset */
static const reset_ip_name_t s_sctResets[] = SCT_RSTS;
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
#endif /* FSL_FEATURE_SCT_HAS_RESET */

/*!< @brief SCTimer event Callback function. */
static sctimer_event_callback_t s_eventCallback[FSL_FEATURE_SCT_NUMBER_OF_EVENTS];

/*!< @brief Keep track of SCTimer event number */
static uint32_t s_currentEvent;

/*!< @brief Keep track of SCTimer state number */
static uint32_t s_currentState;

/*!< @brief Keep track of SCTimer unify 32-bit or low 16-bit match/capture register number. */
static uint32_t s_currentMatch;
/*!< @brief Keep track of SCTimer high 16-bit match/capture register number. */
static uint32_t s_currentMatchhigh;

/*! @brief Pointer to SCTimer IRQ handler */
static sctimer_isr_t s_sctimerIsr;

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t SCTIMER_GetInstance(SCT_Type *base)
{
    uint32_t instance;
    uint32_t sctArrayCount = (sizeof(s_sctBases) / sizeof(s_sctBases[0]));

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < sctArrayCount; instance++)
    {
        if (s_sctBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < sctArrayCount);

    return instance;
}

/*!
 * brief Ungates the SCTimer clock and configures the peripheral for basic operation.
 *
 * note This API should be called at the beginning of the application using the SCTimer driver.
 *
 * param base   SCTimer peripheral base address
 * param config Pointer to the user configuration structure.
 *
 * return kStatus_Success indicates success; Else indicates failure.
 */
status_t SCTIMER_Init(SCT_Type *base, const sctimer_config_t *config)
{
    assert(NULL != config);

    uint32_t i;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the SCTimer clock*/
    CLOCK_EnableClock(s_sctClocks[SCTIMER_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(FSL_FEATURE_SCT_HAS_RESET)
#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(s_sctResets[SCTIMER_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */
#endif /* FSL_FEATURE_SCT_HAS_RESET */

    /* Setup the counter operation. For Current Driver interface SCTIMER_Init don't know detail
     * frequency of input clock, but User know it. So the INSYNC have to set by user level. */
    base->CONFIG = SCT_CONFIG_CKSEL(config->clockSelect) | SCT_CONFIG_CLKMODE(config->clockMode) |
                   SCT_CONFIG_UNIFY(config->enableCounterUnify) | SCT_CONFIG_INSYNC(config->inputsync);

    /* Write to the control register, keep the counters halted. */
    base->CTRL =
        SCT_CTRL_BIDIR_L(config->enableBidirection_l) | SCT_CTRL_PRE_L(config->prescale_l) | SCT_CTRL_HALT_L_MASK;
    /* Clear the counter after changing the PRE value. */
    base->CTRL |= SCT_CTRL_CLRCTR_L_MASK;

    if (!(config->enableCounterUnify))
    {
        base->CTRL |=
            SCT_CTRL_BIDIR_H(config->enableBidirection_h) | SCT_CTRL_PRE_H(config->prescale_h) | SCT_CTRL_HALT_H_MASK;
        base->CTRL |= SCT_CTRL_CLRCTR_H_MASK;
    }

    /* Initial state of channel output */
    base->OUTPUT = config->outInitState;

    /* Clear the global variables */
    s_currentEvent     = 0U;
    s_currentState     = 0U;
    s_currentMatch     = 0U;
    s_currentMatchhigh = 0U;

    /* Clear the callback array */
    for (i = 0; i < (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_EVENTS; i++)
    {
        s_eventCallback[i] = NULL;
    }

    /* Save interrupt handler */
    s_sctimerIsr = SCTIMER_EventHandleIRQ;

    return kStatus_Success;
}

/*!
 * brief Gates the SCTimer clock.
 *
 * param base SCTimer peripheral base address
 */
void SCTIMER_Deinit(SCT_Type *base)
{
    /* Halt the counters */
    base->CTRL |= (SCT_CTRL_HALT_L_MASK | SCT_CTRL_HALT_H_MASK);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the SCTimer clock*/
    CLOCK_DisableClock(s_sctClocks[SCTIMER_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief  Fills in the SCTimer configuration structure with the default settings.
 *
 * The default values are:
 * code
 *  config->enableCounterUnify = true;
 *  config->clockMode = kSCTIMER_System_ClockMode;
 *  config->clockSelect = kSCTIMER_Clock_On_Rise_Input_0;
 *  config->enableBidirection_l = false;
 *  config->enableBidirection_h = false;
 *  config->prescale_l = 0U;
 *  config->prescale_h = 0U;
 *  config->outInitState = 0U;
 *  config->inputsync  = 0xFU;
 * endcode
 * param config Pointer to the user configuration structure.
 */
void SCTIMER_GetDefaultConfig(sctimer_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* SCT operates as a unified 32-bit counter */
    config->enableCounterUnify = true;
    /* System clock clocks the entire SCT module */
    config->clockMode = kSCTIMER_System_ClockMode;
    /* This is used only by certain clock modes */
    config->clockSelect = kSCTIMER_Clock_On_Rise_Input_0;
    /* Up count mode only for the unified counter */
    config->enableBidirection_l = false;
    /* Up count mode only for Counte_H */
    config->enableBidirection_h = false;
    /* Prescale factor of 1 */
    config->prescale_l = 0U;
    /* Prescale factor of 1 for Counter_H*/
    config->prescale_h = 0U;
    /* Clear outputs */
    config->outInitState = 0U;
    /* Default value is 0xFU, it can be clear as 0 when speical conditions met.
     * Condition can be clear as 0: (for all Clock Modes):
     * (1) The corresponding input is already synchronous to the SCTimer/PWM clock.
     * (2) The SCTimer/PWM clock frequency does not exceed 100 MHz.
     * Note: The SCTimer/PWM clock is the bus/system clock for CKMODE 0-2 or asynchronous input
     * clock for CKMODE3.
     * Another condition can be clear as 0: (for CKMODE2 only)
     * (1) The corresponding input is synchronous to the designated CKMODE2 input clock.
     * (2) The CKMODE2 input clock frequency is less than one-third the frequency of the bus/system clock.
     * Default value set as 0U, input0~input3 are set as bypasses. */
    config->inputsync = 0xFU;
}

/*!
 * brief Configures the PWM signal parameters.
 *
 * Call this function to configure the PWM signal period, mode, duty cycle, and edge. This
 * function will create 2 events; one of the events will trigger on match with the pulse value
 * and the other will trigger when the counter matches the PWM period. The PWM period event is
 * also used as a limit event to reset the counter or change direction. Both events are enabled
 * for the same state. The state number can be retrieved by calling the function
 * SCTIMER_GetCurrentStateNumber().
 * The counter is set to operate as one 32-bit counter (unify bit is set to 1).
 * The counter operates in bi-directional mode when generating a center-aligned PWM.
 *
 * note When setting PWM output from multiple output pins, they all should use the same PWM mode
 * i.e all PWM's should be either edge-aligned or center-aligned.
 * When using this API, the PWM signal frequency of all the initialized channels must be the same.
 * Otherwise all the initialized channels' PWM signal frequency is equal to the last call to the
 * API's pwmFreq_Hz.
 *
 * param base        SCTimer peripheral base address
 * param pwmParams   PWM parameters to configure the output
 * param mode        PWM operation mode, options available in enumeration ::sctimer_pwm_mode_t
 * param pwmFreq_Hz  PWM signal frequency in Hz
 * param srcClock_Hz SCTimer counter clock in Hz
 * param event       Pointer to a variable where the PWM period event number is stored
 *
 * return kStatus_Success on success
 *         kStatus_Fail If we have hit the limit in terms of number of events created or if
 *                      an incorrect PWM dutycylce is passed in.
 */
status_t SCTIMER_SetupPwm(SCT_Type *base,
                          const sctimer_pwm_signal_param_t *pwmParams,
                          sctimer_pwm_mode_t mode,
                          uint32_t pwmFreq_Hz,
                          uint32_t srcClock_Hz,
                          uint32_t *event)
{
    assert(NULL != pwmParams);
    assert(0U != srcClock_Hz);
    assert(0U != pwmFreq_Hz);
    assert((uint32_t)pwmParams->output < (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_OUTPUTS);
    assert(1U == (base->CONFIG & SCT_CONFIG_UNIFY_MASK));

    /* If we do not have enough events available (this function will create two events),
     * the function will return fail.
     */
    status_t status = kStatus_Fail;
    status_t status2;
    uint32_t period, pulsePeriod = 0;
    uint32_t sctClock    = srcClock_Hz / (((base->CTRL & SCT_CTRL_PRE_L_MASK) >> SCT_CTRL_PRE_L_SHIFT) + 1U);
    uint32_t periodEvent = 0, pulseEvent = 0;
    uint32_t reg;

    if ((s_currentEvent + 2U) <= (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_EVENTS)
    {
        /* Use bi-directional mode for center-aligned PWM */
        if (mode == kSCTIMER_CenterAlignedPwm)
        {
            base->CTRL |= SCT_CTRL_BIDIR_L_MASK;
        }

        /* Calculate PWM period match value */
        if (mode == kSCTIMER_EdgeAlignedPwm)
        {
            period = (sctClock / pwmFreq_Hz) - 1U;
        }
        else
        {
            period = sctClock / (pwmFreq_Hz * 2U);
        }

        /* For 100% dutycyle, make pulse period greater than period so the event will never occur */
        if (pwmParams->dutyCyclePercent >= 100U)
        {
            pulsePeriod = period + 2U;
        }
        else
        {
            pulsePeriod = (uint32_t)(((uint64_t)period * pwmParams->dutyCyclePercent) / 100U);
        }

        /* Schedule an event when we reach the PWM period */
        status =
            SCTIMER_CreateAndScheduleEvent(base, kSCTIMER_MatchEventOnly, period, 0, kSCTIMER_Counter_U, &periodEvent);

        /* Schedule an event when we reach the pulse width */
        status2 = SCTIMER_CreateAndScheduleEvent(base, kSCTIMER_MatchEventOnly, pulsePeriod, 0, kSCTIMER_Counter_U,
                                                 &pulseEvent);

        if ((kStatus_Success == status) && (kStatus_Success == status2))
        {
            /* Reset the counter when we reach the PWM period */
            SCTIMER_SetupCounterLimitAction(base, kSCTIMER_Counter_U, periodEvent);

            /* Return the period event to the user */
            *event = periodEvent;

            /* For high-true level */
            if ((uint32_t)pwmParams->level == (uint32_t)kSCTIMER_HighTrue)
            {
                if (mode == kSCTIMER_EdgeAlignedPwm)
                {
                    /* Set the initial output level to low which is the inactive state */
                    base->OUTPUT &= ~(1UL << (uint32_t)pwmParams->output);
                    /* Set the output when we reach the PWM period */
                    SCTIMER_SetupOutputSetAction(base, (uint32_t)pwmParams->output, periodEvent);
                    /* Clear the output when we reach the PWM pulse value */
                    SCTIMER_SetupOutputClearAction(base, (uint32_t)pwmParams->output, pulseEvent);
                }
                else
                {
                    /* Set the initial output level to high which is the active state */
                    base->OUTPUT |= (1UL << (uint32_t)pwmParams->output);
                    /* Clear the output when we reach the PWM pulse event */
                    SCTIMER_SetupOutputClearAction(base, (uint32_t)pwmParams->output, pulseEvent);
                    /* Reverse output when down counting */
                    reg = base->OUTPUTDIRCTRL;
                    reg &= ~((uint32_t)SCT_OUTPUTDIRCTRL_SETCLR0_MASK << (2U * (uint32_t)pwmParams->output));
                    reg |= (1UL << (2U * (uint32_t)pwmParams->output));
                    base->OUTPUTDIRCTRL = reg;
                }
            }
            /* For low-true level */
            else
            {
                if (mode == kSCTIMER_EdgeAlignedPwm)
                {
                    /* Set the initial output level to high which is the inactive state */
                    base->OUTPUT |= (1UL << (uint32_t)pwmParams->output);
                    /* Clear the output when we reach the PWM period */
                    SCTIMER_SetupOutputClearAction(base, (uint32_t)pwmParams->output, periodEvent);
                    /* Set the output when we reach the PWM pulse value */
                    SCTIMER_SetupOutputSetAction(base, (uint32_t)pwmParams->output, pulseEvent);
                }
                else
                {
                    /* Set the initial output level to low which is the active state */
                    base->OUTPUT &= ~(1UL << (uint32_t)pwmParams->output);
                    /* Set the output when we reach the PWM pulse event */
                    SCTIMER_SetupOutputSetAction(base, (uint32_t)pwmParams->output, pulseEvent);
                    /* Reverse output when down counting */
                    reg = base->OUTPUTDIRCTRL;
                    reg &= ~((uint32_t)SCT_OUTPUTDIRCTRL_SETCLR0_MASK << (2U * (uint32_t)pwmParams->output));
                    reg |= (1UL << (2U * (uint32_t)pwmParams->output));
                    base->OUTPUTDIRCTRL = reg;
                }
            }
        }
        else
        {
            status = kStatus_Fail;
        }
    }

    return status;
}

/*!
 * brief Updates the duty cycle of an active PWM signal.
 *
 * Before calling  this function, the counter is set to operate as one 32-bit counter (unify bit is set to 1).
 *
 * param base              SCTimer peripheral base address
 * param output            The output to configure
 * param dutyCyclePercent  New PWM pulse width; the value should be between 0 to 100
 * param event             Event number associated with this PWM signal. This was returned to the user by the
 *                          function SCTIMER_SetupPwm().
 */
void SCTIMER_UpdatePwmDutycycle(SCT_Type *base, sctimer_out_t output, uint8_t dutyCyclePercent, uint32_t event)

{
    assert(dutyCyclePercent <= 100U);
    assert((uint32_t)output < (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_OUTPUTS);
    assert(1U == (base->CONFIG & SCT_CONFIG_UNIFY_MASK));

    uint32_t periodMatchReg, pulseMatchReg;
    uint32_t pulsePeriod = 0, period;
    bool isHighTrue      = (0U != (base->OUT[output].CLR & (1UL << (event + 1U))));

    /* Retrieve the match register number for the PWM period */
    periodMatchReg = base->EV[event].CTRL & SCT_EV_CTRL_MATCHSEL_MASK;

    /* Retrieve the match register number for the PWM pulse period */
    pulseMatchReg = base->EV[event + 1U].CTRL & SCT_EV_CTRL_MATCHSEL_MASK;

    period = base->MATCH[periodMatchReg];

    /* Stop the counter before updating match register */
    SCTIMER_StopTimer(base, (uint32_t)kSCTIMER_Counter_U);

    /* For 100% dutycyle, make pulse period greater than period so the event will never occur */
    if (dutyCyclePercent >= 100U)
    {
        pulsePeriod = period + 2U;

        /* Set the initial output level base on output mode */
        if (isHighTrue)
        {
            base->OUTPUT |= (1UL << (uint32_t)output);
        }
        else
        {
            base->OUTPUT &= ~(1UL << (uint32_t)output);
        }
    }
    else
    {
        pulsePeriod = (uint32_t)(((uint64_t)period * dutyCyclePercent) / 100U);
    }

    /* Update dutycycle */
    base->MATCH[pulseMatchReg]    = pulsePeriod;
    base->MATCHREL[pulseMatchReg] = pulsePeriod;

    /* Restart the counter */
    SCTIMER_StartTimer(base, (uint32_t)kSCTIMER_Counter_U);
}

/*!
 * brief Create an event that is triggered on a match or IO and schedule in current state.
 *
 * This function will configure an event using the options provided by the user. If the event type uses
 * the counter match, then the function will set the user provided match value into a match register
 * and put this match register number into the event control register.
 * The event is enabled for the current state and the event number is increased by one at the end.
 * The function returns the event number; this event number can be used to configure actions to be
 * done when this event is triggered.
 *
 * param base         SCTimer peripheral base address
 * param howToMonitor Event type; options are available in the enumeration ::sctimer_event_t
 * param matchValue   The match value that will be programmed to a match register
 * param whichIO      The input or output that will be involved in event triggering. This field
 *                     is ignored if the event type is "match only"
 * param whichCounter SCTimer counter to use. In 16-bit mode, we can select Counter_L and Counter_H,
 *                     In 32-bit mode, we can select Counter_U.
 * param event        Pointer to a variable where the new event number is stored
 *
 * return kStatus_Success on success
 *         kStatus_Error if we have hit the limit in terms of number of events created or
                         if we have reached the limit in terms of number of match registers
 */
status_t SCTIMER_CreateAndScheduleEvent(SCT_Type *base,
                                        sctimer_event_t howToMonitor,
                                        uint32_t matchValue,
                                        uint32_t whichIO,
                                        sctimer_counter_t whichCounter,
                                        uint32_t *event)
{
    uint32_t combMode       = (((uint32_t)howToMonitor & SCT_EV_CTRL_COMBMODE_MASK) >> SCT_EV_CTRL_COMBMODE_SHIFT);
    uint32_t currentCtrlVal = (uint32_t)howToMonitor;
    status_t status         = kStatus_Success;
    uint32_t temp           = 0;

    if (s_currentEvent < (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_EVENTS)
    {
        if (2U == combMode)
        {
            base->EV[s_currentEvent].CTRL = currentCtrlVal | SCT_EV_CTRL_IOSEL(whichIO);
        }
        else
        {
            if ((0U == combMode) || (3U == combMode))
            {
                currentCtrlVal |= SCT_EV_CTRL_IOSEL(whichIO);
            }

            if ((kSCTIMER_Counter_L == whichCounter) && (0U == (base->CONFIG & SCT_CONFIG_UNIFY_MASK)))
            {
                if (s_currentMatch < (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_MATCH_CAPTURE)
                {
                    currentCtrlVal |= SCT_EV_CTRL_MATCHSEL(s_currentMatch);

                    /* Use Counter_L bits if user wants to setup the Low counter */
                    base->MATCH_ACCESS16BIT[s_currentMatch].MATCHL       = (uint16_t)matchValue;
                    base->MATCHREL_ACCESS16BIT[s_currentMatch].MATCHRELL = (uint16_t)matchValue;
                    base->EV[s_currentEvent].CTRL                        = currentCtrlVal;

                    /* Increment the match register number */
                    s_currentMatch++;
                }
                else
                {
                    /* An error would occur if we have hit the limit in terms of number of match registers */
                    status = kStatus_Fail;
                }
            }
            else if ((kSCTIMER_Counter_H == whichCounter) && (0U == (base->CONFIG & SCT_CONFIG_UNIFY_MASK)))
            {
                if (s_currentMatchhigh < (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_MATCH_CAPTURE)
                {
                    currentCtrlVal |= SCT_EV_CTRL_MATCHSEL(s_currentMatchhigh);

                    /* Use Counter_H bits if user wants to setup the High counter */
                    currentCtrlVal |= SCT_EV_CTRL_HEVENT(1U);
                    temp                               = base->MATCH_ACCESS16BIT[s_currentMatchhigh].MATCHL;
                    base->MATCH[s_currentMatchhigh]    = temp | (matchValue << 16U);
                    temp                               = base->MATCHREL_ACCESS16BIT[s_currentMatchhigh].MATCHRELL;
                    base->MATCHREL[s_currentMatchhigh] = temp | (matchValue << 16U);

                    base->EV[s_currentEvent].CTRL = currentCtrlVal;
                    /* Increment the match register number */
                    s_currentMatchhigh++;
                }
                else
                {
                    /* An error would occur if we have hit the limit in terms of number of match registers */
                    status = kStatus_Fail;
                }
            }
            else if ((kSCTIMER_Counter_U == whichCounter) && (0U != (base->CONFIG & SCT_CONFIG_UNIFY_MASK)))
            {
                if (s_currentMatch < (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_MATCH_CAPTURE)
                {
                    /* Use Counter_L bits if counter is operating in 32-bit mode */
                    currentCtrlVal |= SCT_EV_CTRL_MATCHSEL(s_currentMatch);

                    base->MATCH[s_currentMatch]    = matchValue;
                    base->MATCHREL[s_currentMatch] = matchValue;
                    base->EV[s_currentEvent].CTRL  = currentCtrlVal;

                    /* Increment the match register number */
                    s_currentMatch++;
                }
                else
                {
                    /* An error would occur if we have hit the limit in terms of number of match registers */
                    status = kStatus_Fail;
                }
            }
            else
            {
                /* The used counter must match the CONFIG[UNIFY] bit selection */
                status = kStatus_Fail;
            }
        }

        if (kStatus_Success == status)
        {
            /* Enable the event in the current state */
            base->EV[s_currentEvent].STATE = (1UL << s_currentState);

            /* Return the event number */
            *event = s_currentEvent;

            /* Increment the event number */
            s_currentEvent++;
        }
    }
    else
    {
        /* An error would occur if we have hit the limit in terms of number of events created */
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Enable an event in the current state.
 *
 * This function will allow the event passed in to trigger in the current state. The event must
 * be created earlier by either calling the function SCTIMER_SetupPwm() or function
 * SCTIMER_CreateAndScheduleEvent() .
 *
 * param base  SCTimer peripheral base address
 * param event Event number to enable in the current state
 *
 */
void SCTIMER_ScheduleEvent(SCT_Type *base, uint32_t event)
{
    /* Enable event in the current state */
    base->EV[event].STATE |= (1UL << s_currentState);
}

/*!
 * brief Increase the state by 1
 *
 * All future events created by calling the function SCTIMER_ScheduleEvent() will be enabled in this new
 * state.
 *
 * param base  SCTimer peripheral base address
 *
 * return kStatus_Success on success
 *         kStatus_Error if we have hit the limit in terms of states used

 */
status_t SCTIMER_IncreaseState(SCT_Type *base)
{
    status_t status = kStatus_Success;

    /* Return an error if we have hit the limit in terms of states used */
    if (s_currentState >= (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_STATES)
    {
        status = kStatus_Fail;
    }
    else
    {
        s_currentState++;
    }

    return status;
}

/*!
 * brief Provides the current state
 *
 * User can use this to set the next state by calling the function SCTIMER_SetupNextStateAction().
 *
 * param base SCTimer peripheral base address
 *
 * return The current state
 */
uint32_t SCTIMER_GetCurrentState(SCT_Type *base)
{
    return s_currentState;
}

/*!
 * brief Toggle the output level.
 *
 * This change in the output level is triggered by the event number that is passed in by the user.
 *
 * param base    SCTimer peripheral base address
 * param whichIO The output to toggle
 * param event   Event number that will trigger the output change
 */
void SCTIMER_SetupOutputToggleAction(SCT_Type *base, uint32_t whichIO, uint32_t event)
{
    assert(whichIO < (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_OUTPUTS);

    uint32_t reg;

    /* Set the same event to set and clear the output */
    base->OUT[whichIO].CLR |= (1UL << event);
    base->OUT[whichIO].SET |= (1UL << event);

    /* Set the conflict resolution to toggle output */
    reg = base->RES;
    reg &= ~(((uint32_t)SCT_RES_O0RES_MASK) << (2U * whichIO));
    reg |= ((uint32_t)(kSCTIMER_ResolveToggle)) << (2U * whichIO);
    base->RES = reg;
}

/*!
 * brief Setup capture of the counter value on trigger of a selected event
 *
 * param base            SCTimer peripheral base address
 * param whichCounter    SCTimer counter to use. In 16-bit mode, we can select Counter_L and Counter_H,
 *                        In 32-bit mode, we can select Counter_U.
 * param captureRegister Pointer to a variable where the capture register number will be returned. User
 *                        can read the captured value from this register when the specified event is triggered.
 * param event           Event number that will trigger the capture
 *
 * return kStatus_Success on success
 *         kStatus_Error if we have hit the limit in terms of number of match/capture registers available
 */
status_t SCTIMER_SetupCaptureAction(SCT_Type *base,
                                    sctimer_counter_t whichCounter,
                                    uint32_t *captureRegister,
                                    uint32_t event)
{
    status_t status;
    uint32_t temp = 0;

    if ((kSCTIMER_Counter_L == whichCounter) || (kSCTIMER_Counter_U == whichCounter))
    {
        if (s_currentMatch < (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_MATCH_CAPTURE)
        {
            /* Set the bit to enable event */
            base->CAPCTRL_ACCESS16BIT[s_currentMatch].CAPCTRLL |= SCT_CAPCTRLL_CAPCTRLL(1UL << event);

            /* Set this resource to be a capture rather than match */
            base->REGMODE_ACCESS16BIT.REGMODEL |= SCT_REGMODEL_REGMODEL(1UL << s_currentMatch);

            /* Return the match register number */
            *captureRegister = s_currentMatch;

            /* Increase the match register number */
            s_currentMatch++;

            status = kStatus_Success;
        }
        else
        {
            /* Return an error if we have hit the limit in terms of number of capture/match registers used */
            status = kStatus_Fail;
        }
    }
    else
    {
        if (s_currentMatchhigh < (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_MATCH_CAPTURE)
        {
            /* Set bit to enable event */
            temp                              = base->CAPCTRL_ACCESS16BIT[s_currentMatchhigh].CAPCTRLL;
            base->CAPCTRL[s_currentMatchhigh] = temp | ((uint32_t)((uint32_t)(1UL << event) << 16U) & 0xFFFF0000U);
            /* Set this resource to be a capture rather than match */
            temp          = base->REGMODE_ACCESS16BIT.REGMODEL;
            base->REGMODE = temp | ((uint32_t)((uint32_t)(1UL << s_currentMatchhigh) << 16U) & 0xFFFF0000U);

            /* Return the match register number */
            *captureRegister = s_currentMatchhigh;

            /* Increase the match register number */
            s_currentMatchhigh++;

            status = kStatus_Success;
        }
        else
        {
            /* Return an error if we have hit the limit in terms of number of capture/match registers used */
            status = kStatus_Fail;
        }
    }

    return status;
}

/*!
 * brief Receive noticification when the event trigger an interrupt.
 *
 * If the interrupt for the event is enabled by the user, then a callback can be registered
 * which will be invoked when the event is triggered
 *
 * param base     SCTimer peripheral base address
 * param event    Event number that will trigger the interrupt
 * param callback Function to invoke when the event is triggered
 */

void SCTIMER_SetCallback(SCT_Type *base, sctimer_event_callback_t callback, uint32_t event)
{
    s_eventCallback[event] = callback;
}

/*!
 * brief SCTimer interrupt handler.
 *
 * param base SCTimer peripheral base address.
 */
void SCTIMER_EventHandleIRQ(SCT_Type *base)
{
    uint32_t eventFlag = base->EVFLAG;
    /* Only clear the flags whose interrupt field is enabled */
    uint32_t clearFlag = (eventFlag & base->EVEN);
    uint32_t mask      = eventFlag;
    uint32_t i;

    /* Invoke the callback for certain events */
    for (i = 0; i < (uint32_t)FSL_FEATURE_SCT_NUMBER_OF_EVENTS; i++)
    {
        if ((mask & 0x1U) != 0U)
        {
            if (s_eventCallback[i] != NULL)
            {
                s_eventCallback[i]();
            }
        }
        mask >>= 1UL;

        if (0U == mask)
        {
            /* All events have been handled. */
            break;
        }
    }

    /* Clear event interrupt flag */
    base->EVFLAG = clearFlag;
}

#if defined(SCT0)
void SCT0_DriverIRQHandler(void);
void SCT0_DriverIRQHandler(void)
{
    s_sctimerIsr(SCT0);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(SCT)
void SCT_DriverIRQHandler(void);
void SCT_DriverIRQHandler(void)
{
    s_sctimerIsr(SCT);
    SDK_ISR_EXIT_BARRIER;
}
#endif
