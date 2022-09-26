/*
 * Copyright 2017-2019, 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sema4.h"

/******************************************************************************
 * Definitions
 *****************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sema4"
#endif

/* The first number write to RSTGDP when reset SEMA4 gate. */
#define SEMA4_GATE_RESET_PATTERN_1 (0xE2U)
/* The second number write to RSTGDP when reset SEMA4 gate. */
#define SEMA4_GATE_RESET_PATTERN_2 (0x1DU)

/* The first number write to RSTGDP when reset SEMA4 gate IRQ notification. */
#define SEMA4_GATE_IRQ_RESET_PATTERN_1 (0x47U)
/* The second number write to RSTGDP when reset SEMA4 gate IRQ notification. */
#define SEMA4_GATE_IRQ_RESET_PATTERN_2 (0xB8U)

#define SEMA4_RSTGT_RSTNSM_MASK (0x30U)

#define SEMA4_RSTNTF_RSTNSM_MASK (0x30U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#if defined(SEMA4_CLOCKS)
/*!
 * @brief Get instance number for SEMA4 module.
 *
 * @param base SEMA4 peripheral base address.
 */
uint32_t SEMA4_GetInstance(SEMA4_Type *base);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if defined(SEMA4_CLOCKS)
/*! @brief Pointers to sema4 bases for each instance. */
static SEMA4_Type *const s_sema4Bases[] = SEMA4_BASE_PTRS;
#endif

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if defined(SEMA4_CLOCKS)
/*! @brief Pointers to sema4 clocks for each instance. */
static const clock_ip_name_t s_sema4Clocks[] = SEMA4_CLOCKS;
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/******************************************************************************
 * CODE
 *****************************************************************************/

#if defined(SEMA4_CLOCKS)
uint32_t SEMA4_GetInstance(SEMA4_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_sema4Bases); instance++)
    {
        if (s_sema4Bases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_sema4Bases));

    return instance;
}
#endif

/*!
 * brief Initializes the SEMA4 module.
 *
 * This function initializes the SEMA4 module. It only enables the clock but does
 * not reset the gates because the module might be used by other processors
 * at the same time. To reset the gates, call either SEMA4_ResetGate or
 * SEMA4_ResetAllGates function.
 *
 * param base SEMA4 peripheral base address.
 */
void SEMA4_Init(SEMA4_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if defined(SEMA4_CLOCKS)
    CLOCK_EnableClock(s_sema4Clocks[SEMA4_GetInstance(base)]);
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief De-initializes the SEMA4 module.
 *
 * This function de-initializes the SEMA4 module. It only disables the clock.
 *
 * param base SEMA4 peripheral base address.
 */
void SEMA4_Deinit(SEMA4_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if defined(SEMA4_CLOCKS)
    CLOCK_DisableClock(s_sema4Clocks[SEMA4_GetInstance(base)]);
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Tries to lock the SEMA4 gate.
 *
 * This function tries to lock the specific SEMA4 gate. If the gate has been
 * locked by another processor, this function returns an error code.
 *
 * param base SEMA4 peripheral base address.
 * param gateNum  Gate number to lock.
 * param procNum  Current processor number.
 *
 * retval kStatus_Success     Lock the sema4 gate successfully.
 * retval kStatus_Fail Sema4 gate has been locked by another processor.
 */
status_t SEMA4_TryLock(SEMA4_Type *base, uint8_t gateNum, uint8_t procNum)
{
    status_t status;

    assert(gateNum < (uint8_t)FSL_FEATURE_SEMA4_GATE_COUNT);

    ++procNum;

    /* Try to lock. */
    SEMA4_GATEn(base, gateNum) = procNum;

    /* Check locked or not. */
    if (procNum != SEMA4_GATEn(base, gateNum))
    {
        status = kStatus_Fail;
    }
    else
    {
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Locks the SEMA4 gate.
 *
 * This function locks the specific SEMA4 gate. If the gate has been
 * locked by other processors, this function waits until it is unlocked and then
 * lock it.
 *
 * param base SEMA4 peripheral base address.
 * param gateNum  Gate number to lock.
 * param procNum  Current processor number.
 */
void SEMA4_Lock(SEMA4_Type *base, uint8_t gateNum, uint8_t procNum)
{
    while (kStatus_Success != SEMA4_TryLock(base, gateNum, procNum))
    {
    }
}

/*!
 * brief Resets the SEMA4 gate to an unlocked status.
 *
 * This function resets a SEMA4 gate to an unlocked status.
 *
 * param base SEMA4 peripheral base address.
 * param gateNum  Gate number.
 *
 * retval kStatus_Success         SEMA4 gate is reset successfully.
 * retval kStatus_Fail Some other reset process is ongoing.
 */
status_t SEMA4_ResetGate(SEMA4_Type *base, uint8_t gateNum)
{
    status_t status;

    /*
     * Reset all gates if gateNum >= SEMA4_GATE_NUM_RESET_ALL
     * Reset specific gate if gateNum < FSL_FEATURE_SEMA4_GATE_COUNT
     */
    assert(!((gateNum < SEMA4_GATE_NUM_RESET_ALL) && (gateNum >= (uint8_t)FSL_FEATURE_SEMA4_GATE_COUNT)));

    /* Check whether some reset is ongoing. */
    if (0U != (base->RSTGT & SEMA4_RSTGT_RSTNSM_MASK))
    {
        status = kStatus_Fail;
    }
    else
    {
        /* First step. */
        base->RSTGT = SEMA4_RSTGT_RSTGSM_RSTGMS_RSTGDP(SEMA4_GATE_RESET_PATTERN_1);
        /* Second step. */
        base->RSTGT = SEMA4_RSTGT_RSTGSM_RSTGMS_RSTGDP(SEMA4_GATE_RESET_PATTERN_2) | SEMA4_RSTGT_RSTGTN(gateNum);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Resets the SEMA4 gate IRQ notification.
 *
 * This function resets a SEMA4 gate IRQ notification.
 *
 * param base SEMA4 peripheral base address.
 * param gateNum  Gate number.
 *
 * retval kStatus_Success Reset successfully.
 * retval kStatus_Fail    Some other reset process is ongoing.
 */
status_t SEMA4_ResetGateNotify(SEMA4_Type *base, uint8_t gateNum)
{
    status_t status;

    /*
     * Reset all gates if gateNum >= SEMA4_GATE_NUM_RESET_ALL
     * Reset specific gate if gateNum < FSL_FEATURE_SEMA4_GATE_COUNT
     */
    assert(!((gateNum < (uint8_t)SEMA4_GATE_NUM_RESET_ALL) && (gateNum >= (uint8_t)FSL_FEATURE_SEMA4_GATE_COUNT)));

    /* Check whether some reset is ongoing. */
    if (0U != (base->RSTNTF & SEMA4_RSTNTF_RSTNSM_MASK))
    {
        status = kStatus_Fail;
    }
    else
    {
        /* First step. */
        base->RSTNTF = SEMA4_RSTNTF_RSTNSM_RSTNMS_RSTNDP(SEMA4_GATE_IRQ_RESET_PATTERN_1);
        /* Second step. */
        base->RSTNTF = SEMA4_RSTNTF_RSTNSM_RSTNMS_RSTNDP(SEMA4_GATE_IRQ_RESET_PATTERN_2) | SEMA4_RSTNTF_RSTNTN(gateNum);

        status = kStatus_Success;
    }

    return status;
}
