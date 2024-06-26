/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_syspm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.syspm"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)) && defined(SYSPM_CLOCKS)
/*!
 * @brief Get instance number for ESYSPM.
 *
 * @param base ESYSPM peripheral base address.
 */
static uint32_t SYSPM_GetInstance(SYSPM_Type *base);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)) && defined(SYSPM_CLOCKS)
/*! @brief Array to map SYSPM instance number to base pointer. */
static SYSPM_Type *const s_syspmBases[] = SYSPM_BASE_PTRS;

/*! @brief Array to map SYSPM instance number to clock name. */
static const clock_ip_name_t s_syspmClockName[] = SYSPM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)) && defined(SYSPM_CLOCKS)
static uint32_t SYSPM_GetInstance(SYSPM_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_syspmBases); instance++)
    {
        if (s_syspmBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_syspmBases));

    return instance;
}
#endif

/*
 * brief Initializes the SYSPM
 *
 * This function enables the SYSPM clock.
 *
 * param base  SYSPM peripheral base address.
 */
void SYSPM_Init(SYSPM_Type *base)
{
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)) && defined(SYSPM_CLOCKS)
    CLOCK_EnableClock(s_syspmClockName[SYSPM_GetInstance(base)]);
#endif
}

/*
 * brief Deinitializes the SYSPM
 *
 * This function disables the SYSPM clock.
 *
 * param base  SYSPM peripheral base address.
 */
void SYSPM_Deinit(SYSPM_Type *base)
{
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)) && defined(SYSPM_CLOCKS)
    CLOCK_DisableClock(s_syspmClockName[SYSPM_GetInstance(base)]);
#endif
}

/*!
 * @brief Select event counters
 *
 * @param base               SYSPM peripheral base address.
 * @param monitor            syspm control monitor, see to #syspm_monitor_t.
 * @param event              syspm select event, see to #syspm_event_t.
 * @param eventCode          select which event to be counted in PMECTRx., see to table Events.
 */
void SYSPM_SelectEvent(SYSPM_Type *base, syspm_monitor_t monitor, syspm_event_t event, uint8_t eventCode)
{
    uint32_t pmcr;
    uint8_t shift;

    shift = 7U * (uint8_t)event;

    pmcr = base->PMCR[(uint8_t)monitor].PMCR;
    pmcr &= ~(SYSPM_PMCR_SELEVT1_MASK << shift);
    pmcr |= SYSPM_PMCR_SELEVT1(eventCode) << shift;

    base->PMCR[(uint8_t)monitor].PMCR = pmcr;
}

/*!
 * @brief Reset event counters
 *
 * @param base        SYSPM peripheral base address.
 * @param monitor     syspm control monitor, see to #syspm_monitor_t.
 */
void SYSPM_ResetEvent(SYSPM_Type *base, syspm_monitor_t monitor, syspm_event_t event)
{
    base->PMCR[(uint8_t)monitor].PMCR |= ((uint32_t)SYSPM_PMCR_RECTR1_MASK << (uint8_t)event);
}

#if !((defined(FSL_FEATURE_SYSPM_HAS_PMCR_RICTR) && (FSL_FEATURE_SYSPM_HAS_PMCR_RICTR == 0U)))
/*!
 * @brief Reset Instruction Counter
 *
 * @param base        SYSPM peripheral base address.
 * @param monitor     syspm control monitor, see to #syspm_monitor_t.
 */
void SYSPM_ResetInstructionEvent(SYSPM_Type *base, syspm_monitor_t monitor)
{
    base->PMCR[(uint8_t)monitor].PMCR |= SYSPM_PMCR_RICTR_MASK;
}
#endif /* FSL_FEATURE_SYSPM_HAS_PMCR_RICTR */

/*!
 * @brief Set count mode
 *
 * @param base               SYSPM peripheral base address.
 * @param monitor            syspm control monitor, see to #syspm_monitor_t.
 * @param mode               syspm select counter mode, see to #syspm_mode_t.
 */
void SYSPM_SetCountMode(SYSPM_Type *base, syspm_monitor_t monitor, syspm_mode_t mode)
{
    base->PMCR[(uint8_t)monitor].PMCR =
        (base->PMCR[(uint8_t)monitor].PMCR & ~SYSPM_PMCR_CMODE_MASK) | SYSPM_PMCR_CMODE(mode);
}

/*!
 * @brief  Set Start/Stop Control
 *
 * @param base              SYSPM peripheral base address.
 * @param monitor           syspm control monitor, see to #syspm_monitor_t.
 * @param ssc               This 3-bit field provides a three-phase mechanism to start/stop the counters. It includes a
 *                          prioritized scheme with local start > local stop > global start > global stop > conditional
 * TSTART > TSTOP. The global and conditional start/stop affect all configured PM/PSAM module concurrently so counters
 * are "coherent". see to #syspm_startstop_control_t
 */
void SYSPM_SetStartStopControl(SYSPM_Type *base, syspm_monitor_t monitor, syspm_startstop_control_t ssc)
{
    base->PMCR[(uint8_t)monitor].PMCR =
        (base->PMCR[(uint8_t)monitor].PMCR & ~SYSPM_PMCR_SSC_MASK) | SYSPM_PMCR_SSC(ssc);
}

#if !((defined(FSL_FEATURE_SYSPM_HAS_PMCR_DCIFSH)) && (FSL_FEATURE_SYSPM_HAS_PMCR_DCIFSH == 0U))
/*!
 * @brief Disable Counters if Stopped or Halted
 *
 * @param base              SYSPM peripheral base address.
 * @param monitor           syspm control monitor, see to #syspm_monitor_t.
 */
void SYSPM_DisableCounter(SYSPM_Type *base, syspm_monitor_t monitor)
{
    base->PMCR[(uint8_t)monitor].PMCR |= SYSPM_PMCR_DCIFSH_MASK;
}
#endif /* FSL_FEATURE_SYSPM_HAS_PMCR_DCIFSH */

/*!
 * @brief This is the the 40-bits of eventx counter.
         The value in this register increments each time the event
         selected in PMCRx[SELEVTx] occurs.
 *
 * @param base              SYSPM peripheral base address.
 * @param monitor           syspm control monitor, see to #syspm_monitor_t.
 * @param event             syspm select event, see to #syspm_event_t.
 * @return                  get the the 40 bits of eventx counter.
 */
uint64_t SYSPM_GetEventCounter(SYSPM_Type *base, syspm_monitor_t monitor, syspm_event_t event)
{
    uint32_t highOld;
    uint32_t high;
    uint32_t low;

    highOld = base->PMCR[(uint8_t)monitor].PMECTR[(uint8_t)event].HI;
    while (true)
    {
        low  = base->PMCR[(uint8_t)monitor].PMECTR[(uint8_t)event].LO;
        high = base->PMCR[(uint8_t)monitor].PMECTR[(uint8_t)event].HI;
        if (high == highOld)
        {
            break;
        }
        else
        {
            highOld = high;
        }
    }

    return ((uint64_t)high << 32U) + low;
}
