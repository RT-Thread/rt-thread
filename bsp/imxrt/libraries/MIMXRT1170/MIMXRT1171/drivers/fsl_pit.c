/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pit.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.pit"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Gets the instance from the base address to be used to gate or ungate the module clock
 *
 * @param base PIT peripheral base address
 *
 * @return The PIT instance
 */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
static uint32_t PIT_GetInstance(PIT_Type *base);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to PIT bases for each instance. */
static PIT_Type *const s_pitBases[] = PIT_BASE_PTRS;

/*! @brief Pointers to PIT clocks for each instance. */
static const clock_ip_name_t s_pitClocks[] = PIT_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
static uint32_t PIT_GetInstance(PIT_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_pitBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_pitBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_pitBases));

    return instance;
}
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*!
 * brief Ungates the PIT clock, enables the PIT module, and configures the peripheral for basic operations.
 *
 * note This API should be called at the beginning of the application using the PIT driver.
 *
 * param base   PIT peripheral base address
 * param config Pointer to the user's PIT config structure
 */
void PIT_Init(PIT_Type *base, const pit_config_t *config)
{
    assert(NULL != config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate the PIT clock*/
    CLOCK_EnableClock(s_pitClocks[PIT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(FSL_FEATURE_PIT_HAS_MDIS) && FSL_FEATURE_PIT_HAS_MDIS
#if defined(FSL_FEATURE_PIT_HAS_ERRATA_7914) && FSL_FEATURE_PIT_HAS_ERRATA_7914
    /*
     * If a write to the MCR[MDIS] bit occurs within two bus clock cycles of enabling the PIT clock 
     * in the SIM_CG register, the write will be ignored and the PIT will fail to enable.
     * Insert a read of the MCR register before writing to the MCR register. This guarantees a minimum
     * delay of two bus clocks to guarantee the write is not ignored.
     */
    (void)base->MCR;
#endif
    /* Enable PIT timers */
    base->MCR &= ~PIT_MCR_MDIS_MASK;
#endif

#if defined(FSL_FEATURE_PIT_TIMER_COUNT) && (FSL_FEATURE_PIT_TIMER_COUNT)
    /* Clear all status bits for all channels to make sure the status of all TCTRL registers is clean. */
    for (uint8_t i = 0U; i < (uint32_t)FSL_FEATURE_PIT_TIMER_COUNT; i++)
    {
        base->CHANNEL[i].TCTRL &= ~(PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK | PIT_TCTRL_CHN_MASK);
    }
#endif /* FSL_FEATURE_PIT_TIMER_COUNT */

    /* Config timer operation when in debug mode */
    if (true == config->enableRunInDebug)
    {
        base->MCR &= ~PIT_MCR_FRZ_MASK;
    }
    else
    {
        base->MCR |= PIT_MCR_FRZ_MASK;
    }
}

/*!
 * brief Gates the PIT clock and disables the PIT module.
 *
 * param base PIT peripheral base address
 */
void PIT_Deinit(PIT_Type *base)
{
#if defined(FSL_FEATURE_PIT_HAS_MDIS) && FSL_FEATURE_PIT_HAS_MDIS
    /* Disable PIT timers */
    base->MCR |= PIT_MCR_MDIS_MASK;
#endif

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the PIT clock*/
    CLOCK_DisableClock(s_pitClocks[PIT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

#if defined(FSL_FEATURE_PIT_HAS_RTI) && (FSL_FEATURE_PIT_HAS_RTI)
/*!
 * brief Enables the PIT RTI module, and configures the peripheral for basic operations.
 *
 * note The RTI might take several RTI clock cycles to get enabled or updated. Hence, you must wait for at least four
 *      RTI clock cycles after RTI configuration.
 *
 * param base   PIT peripheral base address
 * param config Pointer to the user's PIT config structure
 */
void PIT_RTI_Init(PIT_Type *base, const pit_config_t *config)
{
    assert(NULL != config);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate the PIT clock*/
    CLOCK_EnableClock(s_pitClocks[PIT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Enable PIT RTI timer */
    base->MCR &= ~(PIT_MCR_MDIS_RTI_MASK | PIT_MCR_MDIS_MASK);
    /* Clear all status bits for RTI to make sure the status of TCTRL registers is clean. */
    base->RTI_TCTRL &= ~(PIT_RTI_TCTRL_TEN_MASK | PIT_RTI_TCTRL_TIE_MASK);

    /* Config timer operation when in debug mode */
    if (true == config->enableRunInDebug)
    {
        base->MCR &= ~PIT_MCR_FRZ_MASK;
    }
    else
    {
        base->MCR |= PIT_MCR_FRZ_MASK;
    }
}

#endif /* FSL_FEATURE_PIT_HAS_RTI */

#if defined(FSL_FEATURE_PIT_HAS_LIFETIME_TIMER) && FSL_FEATURE_PIT_HAS_LIFETIME_TIMER

/*!
 * brief Reads the current lifetime counter value.
 *
 * The lifetime timer is a 64-bit timer which chains timer 0 and timer 1 together.
 * Timer 0 and 1 are chained by calling the PIT_SetTimerChainMode before using this timer.
 * The period of lifetime timer is equal to the "period of timer 0 * period of timer 1".
 * For the 64-bit value, the higher 32-bit has the value of timer 1, and the lower 32-bit
 * has the value of timer 0.
 *
 * param base PIT peripheral base address
 *
 * return Current lifetime timer value
 */
uint64_t PIT_GetLifetimeTimerCount(PIT_Type *base)
{
    uint32_t valueH = 0U;
    uint32_t valueL = 0U;

    /* LTMR64H should be read before LTMR64L */
    valueH = base->LTMR64H;
    valueL = base->LTMR64L;

    return (((uint64_t)valueH << 32U) + (uint64_t)(valueL));
}

#endif /* FSL_FEATURE_PIT_HAS_LIFETIME_TIMER */
