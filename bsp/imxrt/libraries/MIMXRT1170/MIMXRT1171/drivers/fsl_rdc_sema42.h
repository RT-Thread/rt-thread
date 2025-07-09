/*
 * Copyright 2017-2020, 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_RDC_SEMA42_H_
#define FSL_RDC_SEMA42_H_

#include "fsl_common.h"

/*!
 * @addtogroup rdc_sema42
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief RDC_SEMA42 driver version */
#define FSL_RDC_SEMA42_DRIVER_VERSION (MAKE_VERSION(2, 0, 4))
/*! @} */

/*! @brief The number to reset all RDC_SEMA42 gates. */
#define RDC_SEMA42_GATE_NUM_RESET_ALL (64U)

#if defined(RDC_SEMAPHORE_GATE_COUNT)

/*! @brief RDC_SEMA42 gate n register address. */
#define RDC_SEMA42_GATEn(base, n) ((base)->GATE[(n)])

/*! @brief RDC_SEMA42 gate count. */
#define RDC_SEMA42_GATE_COUNT (RDC_SEMAPHORE_GATE_COUNT)

#else /* RDC_SEMAPHORE_GATE_COUNT */

/*! @brief RDC_SEMA42 gate n register address. */
#define RDC_SEMA42_GATEn(base, n)     (((volatile uint8_t *)(&((base)->GATE0)))[(n)])

/*! @brief RDC_SEMA42 gate count. */
#define RDC_SEMA42_GATE_COUNT         (64U)

/* Compatible remap. */
#define RDC_SEMAPHORE_GATE_GTFSM_MASK RDC_SEMAPHORE_GATE0_GTFSM_MASK

#endif /* RDC_SEMAPHORE_GATE_COUNT */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the RDC_SEMA42 module.
 *
 * This function initializes the RDC_SEMA42 module. It only enables the clock but does
 * not reset the gates because the module might be used by other processors
 * at the same time. To reset the gates, call either RDC_SEMA42_ResetGate or
 * RDC_SEMA42_ResetAllGates function.
 *
 * @param base RDC_SEMA42 peripheral base address.
 */
void RDC_SEMA42_Init(RDC_SEMAPHORE_Type *base);

/*!
 * @brief De-initializes the RDC_SEMA42 module.
 *
 * This function de-initializes the RDC_SEMA42 module. It only disables the clock.
 *
 * @param base RDC_SEMA42 peripheral base address.
 */
void RDC_SEMA42_Deinit(RDC_SEMAPHORE_Type *base);

/*!
 * @brief Tries to lock the RDC_SEMA42 gate.
 *
 * This function tries to lock the specific RDC_SEMA42 gate. If the gate has been
 * locked by another processor, this function returns an error code.
 *
 * @param base RDC_SEMA42 peripheral base address.
 * @param gateNum  Gate number to lock.
 * @param masterIndex  Current processor master index.
 * @param domainId  Current processor domain ID.
 *
 * @retval kStatus_Success   Lock the sema42 gate successfully.
 * @retval kStatus_Failed    Sema42 gate has been locked by another processor.
 */
status_t RDC_SEMA42_TryLock(RDC_SEMAPHORE_Type *base, uint8_t gateNum, uint8_t masterIndex, uint8_t domainId);

/*!
 * @brief Locks the RDC_SEMA42 gate.
 *
 * This function locks the specific RDC_SEMA42 gate. If the gate has been
 * locked by other processors, this function waits until it is unlocked and then
 * lock it.
 *
 * @param base RDC_SEMA42 peripheral base address.
 * @param gateNum  Gate number to lock.
 * @param masterIndex  Current processor master index.
 * @param domainId  Current processor domain ID.
 */
void RDC_SEMA42_Lock(RDC_SEMAPHORE_Type *base, uint8_t gateNum, uint8_t masterIndex, uint8_t domainId);

/*!
 * @brief Unlocks the RDC_SEMA42 gate.
 *
 * This function unlocks the specific RDC_SEMA42 gate. It only writes unlock value
 * to the RDC_SEMA42 gate register. However, it does not check whether the RDC_SEMA42 gate is locked
 * by the current processor or not. As a result, if the RDC_SEMA42 gate is not locked by the current
 * processor, this function has no effect.
 *
 * @param base RDC_SEMA42 peripheral base address.
 * @param gateNum  Gate number to unlock.
 */
static inline void RDC_SEMA42_Unlock(RDC_SEMAPHORE_Type *base, uint8_t gateNum)
{
    assert(gateNum < RDC_SEMA42_GATE_COUNT);

    RDC_SEMA42_GATEn(base, gateNum) = 0U;
}

/*!
 * @brief Gets which master has currently locked the gate.
 *
 * @param base RDC_SEMA42 peripheral base address.
 * @param gateNum  Gate number.
 *
 * @return Return -1 if the gate is not locked by any master, otherwise return the
 * master index.
 */
static inline int32_t RDC_SEMA42_GetLockMasterIndex(RDC_SEMAPHORE_Type *base, uint8_t gateNum)
{
    assert(gateNum < RDC_SEMA42_GATE_COUNT);

    uint8_t regGate = RDC_SEMA42_GATEn(base, gateNum);

    return (int32_t)((uint8_t)(regGate & RDC_SEMAPHORE_GATE_GTFSM_MASK)) - 1;
}

/*!
 * @brief Gets which domain has currently locked the gate.
 *
 * @param base RDC_SEMA42 peripheral base address.
 * @param gateNum  Gate number.
 *
 * @return Return -1 if the gate is not locked by any domain, otherwise return the
 * domain ID.
 */
int32_t RDC_SEMA42_GetLockDomainID(RDC_SEMAPHORE_Type *base, uint8_t gateNum);

/*!
 * @brief Resets the RDC_SEMA42 gate to an unlocked status.
 *
 * This function resets a RDC_SEMA42 gate to an unlocked status.
 *
 * @param base RDC_SEMA42 peripheral base address.
 * @param gateNum  Gate number.
 *
 * @retval kStatus_Success         RDC_SEMA42 gate is reset successfully.
 * @retval kStatus_Failed Some other reset process is ongoing.
 */
status_t RDC_SEMA42_ResetGate(RDC_SEMAPHORE_Type *base, uint8_t gateNum);

/*!
 * @brief Resets all RDC_SEMA42 gates to an unlocked status.
 *
 * This function resets all RDC_SEMA42 gate to an unlocked status.
 *
 * @param base RDC_SEMA42 peripheral base address.
 *
 * @retval kStatus_Success         RDC_SEMA42 is reset successfully.
 * @retval kStatus_RDC_SEMA42_Reseting Some other reset process is ongoing.
 */
static inline status_t RDC_SEMA42_ResetAllGates(RDC_SEMAPHORE_Type *base)
{
    return RDC_SEMA42_ResetGate(base, RDC_SEMA42_GATE_NUM_RESET_ALL);
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* FSL_RDC_SEMA42_H_ */
