/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_waketimer.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.waketimer"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * brief Gets the instance from the base address
 *
 * param base WAKETIMER peripheral base address
 *
 * return The WAKETIMER instance
 */
static uint32_t WAKETIMER_GetInstance(WAKETIMER_Type *base);

/*!
 * brief WAKETIMER generic IRQ handle function.
 *
 * param index WAKETIMER peripheral instance index.
 */
static void WAKETIMER_GenericIRQHandler(WAKETIMER_Type *base, waketimer_callback_t callback);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of WAKETIMER peripheral base address. */
static WAKETIMER_Type *const s_waketimerBases[] = WAKETIMER_BASE_PTRS;
/* Array of WAKETIMER ISR. */
static waketimer_callback_t s_waketimerCallback[sizeof(s_waketimerBases) / sizeof(s_waketimerBases[0])];
/* Array of WAKETIMER IRQ number. */
static const IRQn_Type s_waketimerIRQ[] = WAKETIMER_IRQS;

/*******************************************************************************
 * Code
 ******************************************************************************/

/* brief Function for getting the instance number of Waketimer. */
static uint32_t WAKETIMER_GetInstance(WAKETIMER_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_waketimerBases); instance++)
    {
        if (s_waketimerBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_waketimerBases));

    return instance;
}

/*!
 * brief Initializes an WAKETIMER.
 * param base WAKETIMER peripheral base address.
 */
void WAKETIMER_Init(WAKETIMER_Type *base, const waketimer_config_t *config)
{
    assert(NULL != base);

    uint32_t index = WAKETIMER_GetInstance(base);

    /* Halt timer */
    base->WAKE_TIMER_CTRL |= WAKETIMER_WAKE_TIMER_CTRL_CLR_WAKE_TIMER_MASK;

    /* Set OSC divide */
    if (config->enableOSCDivide)
    {
        base->WAKE_TIMER_CTRL |= WAKETIMER_WAKE_TIMER_CTRL_OSC_DIV_ENA_MASK;
    }
    else
    {
        base->WAKE_TIMER_CTRL &= ~WAKETIMER_WAKE_TIMER_CTRL_OSC_DIV_ENA_MASK;
    }

    /* Set callback */
    s_waketimerCallback[index] = config->callback;

    /* Set interrupt */
    if (config->enableInterrupt)
    {
        base->WAKE_TIMER_CTRL |= WAKETIMER_WAKE_TIMER_CTRL_INTR_EN_MASK;
        (void)EnableIRQ(s_waketimerIRQ[index]);
    }
    else
    {
        base->WAKE_TIMER_CTRL &= ~WAKETIMER_WAKE_TIMER_CTRL_INTR_EN_MASK;
        (void)DisableIRQ(s_waketimerIRQ[index]);
    }
}

/*!
 * brief Deinitializes a WAKETIMER instance.
 *
 * This function deinitializes the WAKETIMER.
 *
 * param base WAKETIMER peripheral base address.
 */
void WAKETIMER_Deinit(WAKETIMER_Type *base)
{
    assert(NULL != base);

    uint32_t index = WAKETIMER_GetInstance(base);

    /* Disable IRQ at NVIC Level */
    (void)DisableIRQ(s_waketimerIRQ[index]);
}

/*!
 * brief  Fills in the WAKETIMER configuration structure with the default settings.
 *
 * The default values are:
 * code
 *  config->enableInterrupt = true;
 *  config->enableOSCDivide = true;
 *  config->callback        = NULL;
 * endcode
 * param config Pointer to the user configuration structure.
 */
void WAKETIMER_GetDefaultConfig(waketimer_config_t *config)
{
    config->enableInterrupt = true;
    config->enableOSCDivide = true;
    config->callback        = NULL;
}

/*!
 * brief Enables the selected WAKETIMER interrupts.
 *
 * param base WAKETIMER peripheral base address
 * param mask Mask value for interrupt events. See to #_waketimer_interrupt_enable
 */
void WAKETIMER_EnableInterrupts(WAKETIMER_Type *base, uint32_t mask)
{
    assert(NULL != base);

    if (0U != (mask & (uint32_t)kWAKETIMER_WakeInterruptEnable))
    {
        base->WAKE_TIMER_CTRL |= WAKETIMER_WAKE_TIMER_CTRL_INTR_EN_MASK;
    }
}

/*!
 * brief Disable the selected WAKETIMER interrupts.
 *
 * param base WAKETIMER peripheral base address
 * param mask Mask value for interrupt events. See to #_waketimer_interrupt_enable
 */
void WAKETIMER_DisableInterrupts(WAKETIMER_Type *base, uint32_t mask)
{
    assert(NULL != base);

    if (0U != (mask & (uint32_t)kWAKETIMER_WakeInterruptEnable))
    {
        base->WAKE_TIMER_CTRL &= ~WAKETIMER_WAKE_TIMER_CTRL_INTR_EN_MASK;
    }
}

/*!
 * brief Clear Status Interrupt Flag.
 *
 * This clears intrrupt status flag.
 * Currently, only match interrupt flag can be cleared.
 *
 * param base WAKETIMER peripheral base address.
 * param mask Mask value for flags to be cleared. See to #_waketimer_status_flags.
 * return none
 */
void WAKETIMER_ClearStatusFlags(WAKETIMER_Type *base, uint32_t mask)
{
    if (0U != (mask & (uint32_t)kWAKETIMER_WakeFlag))
    {
        base->WAKE_TIMER_CTRL |= WAKETIMER_WAKE_TIMER_CTRL_WAKE_FLAG_MASK;
    }
}

/*!
 * brief Receive noticification when waketime countdown.
 *
 * If the interrupt for the waketime countdown is enabled, then a callback can be registered
 * which will be invoked when the event is triggered
 *
 * param base     WAKETIMER peripheral base address
 * param callback Function to invoke when the event is triggered
 */
void WAKETIMER_SetCallback(WAKETIMER_Type *base, waketimer_callback_t callback)
{
    assert(NULL != base);

    uint32_t index             = WAKETIMER_GetInstance(base);
    s_waketimerCallback[index] = callback;
}

/*!
 * brief Get current timer count value from WAKETIMER.
 *
 * This function will get a decimal timer count value.
 * The RAW value of timer count is gray code format, will be translated to decimal data internally.
 *
 * param base   WAKETIMER peripheral base address.
 * return Value of WAKETIMER which will formated to decimal value.
 */
uint32_t WAKETIMER_GetCurrentTimerValue(WAKETIMER_Type *base)
{
    uint32_t value1 = 0;
    uint32_t value2 = 0;

    do
    {
        value1 = base->WAKE_TIMER_CNT;
        value2 = base->WAKE_TIMER_CNT;
    } while (value1 != value2);

    return value1;
}

static void WAKETIMER_GenericIRQHandler(WAKETIMER_Type *base, waketimer_callback_t callback)
{
    /* Clear interrupt flag. */
    WAKETIMER_ClearStatusFlags(base, (uint32_t)kWAKETIMER_WakeFlag);

    if (callback != NULL)
    {
        callback();
    }
}

#if defined(WAKETIMER0)
void WAKETIMER0_DriverIRQHandler(void);
void WAKETIMER0_DriverIRQHandler(void)
{
    WAKETIMER_GenericIRQHandler(WAKETIMER0, s_waketimerCallback[0]);
    SDK_ISR_EXIT_BARRIER;
}
#endif
