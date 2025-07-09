/*
 * Copyright 2017-2020, 2022, 2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SEMA4_H_
#define FSL_SEMA4_H_

#include "fsl_common.h"

/*!
 * @addtogroup sema4
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief SEMA4 driver version */
#define FSL_SEMA4_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*! @} */

/*! @brief The number to reset all SEMA4 gates. */
#define SEMA4_GATE_NUM_RESET_ALL (64U)

#if defined(SEMA4_GATE_COUNT)

/*!
 * @brief SEMA4 gate n register address.
 */
#define SEMA4_GATEn(base, n) ((base)->GATE[(n)])

#ifndef FSL_FEATURE_SEMA4_GATE_COUNT
#define FSL_FEATURE_SEMA4_GATE_COUNT SEMA4_GATE_COUNT
#endif

#else

/*!
 * @brief SEMA4 gate n register address.
 */
#define SEMA4_GATEn(base, n) (((volatile uint8_t *)(&((base)->Gate00)))[(n)])

#endif

/*!
 * @brief Maximum polling iterations for SEMA4 waiting loops
 *
 * This parameter defines the maximum number of iterations for any polling loop
 * in the SEMA4 driver code before timing out and returning an error.
 *
 * It applies to all waiting loops in SEMA4 driver, such as waiting for a gate
 * to be unlocked, waiting for a reset to complete, or waiting for a resource
 * to become available.
 *
 * This is a count of loop iterations, not a time-based value.
 *
 * If defined as 0, polling loops will continue indefinitely until their exit condition
 * is met, which could potentially cause the system to hang if hardware doesn't respond
 * or if a resource is never released.
 */
#ifndef SEMA4_BUSY_POLL_COUNT
    #ifdef CONFIG_SEMA4_BUSY_POLL_COUNT
        #define SEMA4_BUSY_POLL_COUNT CONFIG_SEMA4_BUSY_POLL_COUNT
    #else
        #define SEMA4_BUSY_POLL_COUNT 0U
    #endif
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the SEMA4 module.
 *
 * This function initializes the SEMA4 module. It only enables the clock but does
 * not reset the gates because the module might be used by other processors
 * at the same time. To reset the gates, call either SEMA4_ResetGate or
 * SEMA4_ResetAllGates function.
 *
 * @param base SEMA4 peripheral base address.
 */
void SEMA4_Init(SEMA4_Type *base);

/*!
 * @brief De-initializes the SEMA4 module.
 *
 * This function de-initializes the SEMA4 module. It only disables the clock.
 *
 * @param base SEMA4 peripheral base address.
 */
void SEMA4_Deinit(SEMA4_Type *base);

/*!
 * @brief Tries to lock the SEMA4 gate.
 *
 * This function tries to lock the specific SEMA4 gate. If the gate has been
 * locked by another processor, this function returns an error code.
 *
 * @param base SEMA4 peripheral base address.
 * @param gateNum  Gate number to lock.
 * @param procNum  Current processor number.
 *
 * @retval kStatus_Success     Lock the sema4 gate successfully.
 * @retval kStatus_Fail Sema4 gate has been locked by another processor.
 */
status_t SEMA4_TryLock(SEMA4_Type *base, uint8_t gateNum, uint8_t procNum);

/*!
 * @brief Locks the SEMA4 gate.
 *
 * This function locks the specific SEMA4 gate. If the gate has been
 * locked by other processors, this function waits until it is unlocked and then
 * lock it.
 *
 * If SEMA4_BUSY_POLL_COUNT is defined and non-zero, the function will timeout
 * after the specified number of polling iterations and return kStatus_Timeout.
 *
 * @param base SEMA4 peripheral base address.
 * @param gateNum  Gate number to lock.
 * @param procNum  Current processor number.
 *
 * @return status_t
 * @retval kStatus_Success The gate was successfully locked.
 * @retval kStatus_Timeout Timeout occurred while waiting for the gate to be unlocked.
 */
status_t SEMA4_Lock(SEMA4_Type *base, uint8_t gateNum, uint8_t procNum);

/*!
 * @brief Unlocks the SEMA4 gate.
 *
 * This function unlocks the specific SEMA4 gate. It only writes unlock value
 * to the SEMA4 gate register. However, it does not check whether the SEMA4 gate is locked
 * by the current processor or not. As a result, if the SEMA4 gate is not locked by the current
 * processor, this function has no effect.
 *
 * @param base SEMA4 peripheral base address.
 * @param gateNum  Gate number to unlock.
 */
static inline void SEMA4_Unlock(SEMA4_Type *base, uint8_t gateNum)
{
    assert(gateNum < (uint8_t)FSL_FEATURE_SEMA4_GATE_COUNT);

    SEMA4_GATEn(base, gateNum) = 0U;
}

/*!
 * @brief Gets the status of the SEMA4 gate.
 *
 * This function checks the lock status of a specific SEMA4 gate.
 *
 * @param base SEMA4 peripheral base address.
 * @param gateNum  Gate number.
 *
 * @return Return -1 if the gate is unlocked, otherwise return the
 * processor number which has locked the gate.
 */
static inline int32_t SEMA4_GetLockProc(SEMA4_Type *base, uint8_t gateNum)
{
    assert(gateNum < (uint8_t)FSL_FEATURE_SEMA4_GATE_COUNT);

    return (int32_t)(SEMA4_GATEn(base, gateNum)) - 1;
}

/*!
 * @brief Resets the SEMA4 gate to an unlocked status.
 *
 * This function resets a SEMA4 gate to an unlocked status.
 *
 * @param base SEMA4 peripheral base address.
 * @param gateNum  Gate number.
 *
 * @retval kStatus_Success         SEMA4 gate is reset successfully.
 * @retval kStatus_Fail Some other reset process is ongoing.
 */
status_t SEMA4_ResetGate(SEMA4_Type *base, uint8_t gateNum);

/*!
 * @brief Resets all SEMA4 gates to an unlocked status.
 *
 * This function resets all SEMA4 gate to an unlocked status.
 *
 * @param base SEMA4 peripheral base address.
 *
 * @retval kStatus_Success         SEMA4 is reset successfully.
 * @retval kStatus_Fail Some other reset process is ongoing.
 */
static inline status_t SEMA4_ResetAllGates(SEMA4_Type *base)
{
    return SEMA4_ResetGate(base, SEMA4_GATE_NUM_RESET_ALL);
}

/*!
 * @brief Enable the gate notification interrupt.
 *
 * Gate notification provides such feature, when core tried to lock the gate
 * and failed, it could get notification when the gate is idle.
 *
 * @param base SEMA4 peripheral base address.
 * @param procNum  Current processor number.
 * @param mask OR'ed value of the gate index, for example: (1<<0) | (1<<1) means
 * gate 0 and gate 1.
 */
static inline void SEMA4_EnableGateNotifyInterrupt(SEMA4_Type *base, uint8_t procNum, uint16_t mask)
{
    mask = __REV(__RBIT(mask));
    base->CPINE[procNum].CPINE |= mask;
}

/*!
 * @brief Disable the gate notification interrupt.
 *
 * Gate notification provides such feature, when core tried to lock the gate
 * and failed, it could get notification when the gate is idle.
 *
 * @param base SEMA4 peripheral base address.
 * @param procNum  Current processor number.
 * @param mask OR'ed value of the gate index, for example: (1<<0) | (1<<1) means
 * gate 0 and gate 1.
 */
static inline void SEMA4_DisableGateNotifyInterrupt(SEMA4_Type *base, uint8_t procNum, uint16_t mask)
{
    mask = __REV(__RBIT(mask));
    base->CPINE[procNum].CPINE &= (~mask);
}

/*!
 * @brief Get the gate notification flags.
 *
 * Gate notification provides such feature, when core tried to lock the gate
 * and failed, it could get notification when the gate is idle. The status flags
 * are cleared automatically when the gate is locked by current core or locked
 * again before the other core.
 *
 * @param base SEMA4 peripheral base address.
 * @param procNum  Current processor number.
 * @return OR'ed value of the gate index, for example: (1<<0) | (1<<1) means
 * gate 0 and gate 1 flags are pending.
 */
static inline uint32_t SEMA4_GetGateNotifyStatus(SEMA4_Type *base, uint8_t procNum)
{
    return __REV(__RBIT(base->CPNTF[procNum].CPNTF));
}

/*!
 * @brief Resets the SEMA4 gate IRQ notification.
 *
 * This function resets a SEMA4 gate IRQ notification.
 *
 * @param base SEMA4 peripheral base address.
 * @param gateNum  Gate number.
 *
 * @retval kStatus_Success Reset successfully.
 * @retval kStatus_Fail    Some other reset process is ongoing.
 */
status_t SEMA4_ResetGateNotify(SEMA4_Type *base, uint8_t gateNum);

/*!
 * @brief Resets all SEMA4 gates IRQ notification.
 *
 * This function resets all SEMA4 gate IRQ notifications.
 *
 * @param base SEMA4 peripheral base address.
 *
 * @retval kStatus_Success  Reset successfully.
 * @retval kStatus_Fail     Some other reset process is ongoing.
 */
static inline status_t SEMA4_ResetAllGateNotify(SEMA4_Type *base)
{
    return SEMA4_ResetGateNotify(base, SEMA4_GATE_NUM_RESET_ALL);
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* FSL_SEMA4_H_ */
