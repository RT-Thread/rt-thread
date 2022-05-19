/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_rdc_sema42.h"

/******************************************************************************
 * Definitions
 *****************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.rdc_sema42"
#endif

/* The first number write to RSTGDP when reset RDC_SEMA42 gate. */
#define RDC_SEMA42_GATE_RESET_PATTERN_1 (0xE2U)
/* The second number write to RSTGDP when reset RDC_SEMA42 gate. */
#define RDC_SEMA42_GATE_RESET_PATTERN_2 (0x1DU)

#if !defined(RDC_SEMAPHORE_GATE_COUNT)
/* Compatible remap. */
#define RDC_SEMAPHORE_GATE_LDOM(x)    RDC_SEMAPHORE_GATE0_LDOM(x)
#define RDC_SEMAPHORE_GATE_GTFSM(x)   RDC_SEMAPHORE_GATE0_GTFSM(x)
#define RDC_SEMAPHORE_GATE_LDOM_MASK  RDC_SEMAPHORE_GATE0_LDOM_MASK
#define RDC_SEMAPHORE_GATE_LDOM_SHIFT RDC_SEMAPHORE_GATE0_LDOM_SHIFT
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for RDC_SEMA42 module.
 *
 * @param base RDC_SEMA42 peripheral base address.
 */
uint32_t RDC_SEMA42_GetInstance(RDC_SEMAPHORE_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to sema42 bases for each instance. */
static RDC_SEMAPHORE_Type *const s_sema42Bases[] = RDC_SEMAPHORE_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if defined(RDC_SEMA42_CLOCKS)
/*! @brief Pointers to sema42 clocks for each instance. */
static const clock_ip_name_t s_sema42Clocks[] = RDC_SEMA42_CLOCKS;
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/******************************************************************************
 * CODE
 *****************************************************************************/

uint32_t RDC_SEMA42_GetInstance(RDC_SEMAPHORE_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_sema42Bases); instance++)
    {
        if (s_sema42Bases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_sema42Bases));

    return instance;
}

/*!
 * brief Initializes the RDC_SEMA42 module.
 *
 * This function initializes the RDC_SEMA42 module. It only enables the clock but does
 * not reset the gates because the module might be used by other processors
 * at the same time. To reset the gates, call either RDC_SEMA42_ResetGate or
 * RDC_SEMA42_ResetAllGates function.
 *
 * param base RDC_SEMA42 peripheral base address.
 */
void RDC_SEMA42_Init(RDC_SEMAPHORE_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if defined(RDC_SEMA42_CLOCKS)
    CLOCK_EnableClock(s_sema42Clocks[RDC_SEMA42_GetInstance(base)]);
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief De-initializes the RDC_SEMA42 module.
 *
 * This function de-initializes the RDC_SEMA42 module. It only disables the clock.
 *
 * param base RDC_SEMA42 peripheral base address.
 */
void RDC_SEMA42_Deinit(RDC_SEMAPHORE_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if defined(RDC_SEMA42_CLOCKS)
    CLOCK_DisableClock(s_sema42Clocks[RDC_SEMA42_GetInstance(base)]);
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Tries to lock the RDC_SEMA42 gate.
 *
 * This function tries to lock the specific RDC_SEMA42 gate. If the gate has been
 * locked by another processor, this function returns an error code.
 *
 * param base RDC_SEMA42 peripheral base address.
 * param gateNum  Gate number to lock.
 * param masterIndex  Current processor master index.
 * param domainId  Current processor domain ID.
 *
 * retval kStatus_Success   Lock the sema42 gate successfully.
 * retval kStatus_Failed    Sema42 gate has been locked by another processor.
 */
status_t RDC_SEMA42_TryLock(RDC_SEMAPHORE_Type *base, uint8_t gateNum, uint8_t masterIndex, uint8_t domainId)
{
    assert(gateNum < RDC_SEMA42_GATE_COUNT);

    status_t status = kStatus_Success;
    uint8_t regGate;

    ++masterIndex;

    regGate = (uint8_t)(RDC_SEMAPHORE_GATE_LDOM(domainId) | RDC_SEMAPHORE_GATE_GTFSM(masterIndex));

    /* Try to lock. */
    RDC_SEMA42_GATEn(base, gateNum) = masterIndex;

    /* Check locked or not. */
    if (regGate != RDC_SEMA42_GATEn(base, gateNum))
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Locks the RDC_SEMA42 gate.
 *
 * This function locks the specific RDC_SEMA42 gate. If the gate has been
 * locked by other processors, this function waits until it is unlocked and then
 * lock it.
 *
 * param base RDC_SEMA42 peripheral base address.
 * param gateNum  Gate number to lock.
 * param masterIndex  Current processor master index.
 * param domainId  Current processor domain ID.
 */
void RDC_SEMA42_Lock(RDC_SEMAPHORE_Type *base, uint8_t gateNum, uint8_t masterIndex, uint8_t domainId)
{
    assert(gateNum < RDC_SEMA42_GATE_COUNT);

    uint8_t regGate;

    ++masterIndex;

    regGate = (uint8_t)(RDC_SEMAPHORE_GATE_LDOM(domainId) | RDC_SEMAPHORE_GATE_GTFSM(masterIndex));

    while (regGate != RDC_SEMA42_GATEn(base, gateNum))
    {
        /* Wait for unlocked status. */
        while (0U != (RDC_SEMA42_GATEn(base, gateNum) & RDC_SEMAPHORE_GATE_GTFSM_MASK))
        {
        }

        /* Lock the gate. */
        RDC_SEMA42_GATEn(base, gateNum) = masterIndex;
    }
}

/*!
 * brief Gets which domain has currently locked the gate.
 *
 * param base RDC_SEMA42 peripheral base address.
 * param gateNum  Gate number.
 *
 * return Return -1 if the gate is not locked by any domain, otherwise return the
 * domain ID.
 */
int32_t RDC_SEMA42_GetLockDomainID(RDC_SEMAPHORE_Type *base, uint8_t gateNum)
{
    assert(gateNum < RDC_SEMA42_GATE_COUNT);

    int32_t ret;
    uint8_t regGate = RDC_SEMA42_GATEn(base, gateNum);

    /* Current gate is not locked. */
    if (0U == (regGate & RDC_SEMAPHORE_GATE_GTFSM_MASK))
    {
        ret = -1;
    }
    else
    {
        ret = (int32_t)((uint8_t)((regGate & RDC_SEMAPHORE_GATE_LDOM_MASK) >> RDC_SEMAPHORE_GATE_LDOM_SHIFT));
    }

    return ret;
}

/*!
 * brief Resets the RDC_SEMA42 gate to an unlocked status.
 *
 * This function resets a RDC_SEMA42 gate to an unlocked status.
 *
 * param base RDC_SEMA42 peripheral base address.
 * param gateNum  Gate number.
 *
 * retval kStatus_Success         RDC_SEMA42 gate is reset successfully.
 * retval kStatus_Failed Some other reset process is ongoing.
 */
status_t RDC_SEMA42_ResetGate(RDC_SEMAPHORE_Type *base, uint8_t gateNum)
{
    status_t status;

    /*
     * Reset all gates if gateNum >= RDC_SEMA42_GATE_NUM_RESET_ALL
     * Reset specific gate if gateNum < RDC_SEMA42_GATE_COUNT
     */

    /* Check whether some reset is ongoing. */
    if (0U != (base->RSTGT_R & RDC_SEMAPHORE_RSTGT_R_RSTGSM_MASK))
    {
        status = kStatus_Fail;
    }
    else
    {
        /* First step. */
        base->RSTGT_W = RDC_SEMAPHORE_RSTGT_W_RSTGDP(RDC_SEMA42_GATE_RESET_PATTERN_1);
        /* Second step. */
        base->RSTGT_W =
            RDC_SEMAPHORE_RSTGT_W_RSTGDP(RDC_SEMA42_GATE_RESET_PATTERN_2) | RDC_SEMAPHORE_RSTGT_W_RSTGTN(gateNum);

        status = kStatus_Success;
    }

    return status;
}
