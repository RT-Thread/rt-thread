/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_GLIKEY_H_
#define _FSL_GLIKEY_H_

#include "fsl_common.h"

/*!
 * @addtogroup GLIKEY
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Defines GLIKEY driver version 2.0.0.
 *
 * Change log:
 * - Version 2.0.0
 *   - Initial version
 */
#define FSL_GLIKEY_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))

enum
{
    kStatus_GLIKEY_LockedError =
        MAKE_STATUS(kStatusGroup_GLIKEY, 0x1u), /*!< GLIKEY status for locked SFR registers (unexpected) . */
    kStatus_GLIKEY_NotLocked = MAKE_STATUS(kStatusGroup_GLIKEY, 0x2u), /*!< GLIKEY status for unlocked SFR registers. */
    kStatus_GLIKEY_Locked    = MAKE_STATUS(kStatusGroup_GLIKEY, 0x3u), /*!< GLIKEY status for locked SFR registers. */
    kStatus_GLIKEY_DisabledError = MAKE_STATUS(kStatusGroup_GLIKEY, 0x4u), /*!< GLIKEY status for disabled error. */
};

/* [Design]
    Value: XX YZ UU VW
    - XX: F0: write to WR_EN1, 0F: do not write to WR_EN1
    - UU: F0: write to WR_EN0, 0F: do not write to WR_EN0
    - Y:  equal to <step> ^ W
    - Z:  value to write to WR_EN1 or equal to ~W
    - V:  equal to <step> ^ Z
    - W:  value to write to WR_EN0 or equal to ~Z
    Invariant: XXYZ ^ UUVW == 0xFFFF
*/
#define GLIKEY_CODEWORD_STEP1   ((uint32_t)0xF0C10F3EU) /*< Codeword for transition from STEP1 --> STEP2 */
#define GLIKEY_CODEWORD_STEP2   ((uint32_t)0x0F1DF0E2U) /*< Codeword for transition from STEP2 --> STEP3 */
#define GLIKEY_CODEWORD_STEP3   ((uint32_t)0xF0B00F4FU) /*< Codeword for transition from STEP3 --> STEP4 */
#define GLIKEY_CODEWORD_STEP4   ((uint32_t)0x0F4EF0B1U) /*< Codeword for transition from STEP4 --> STEP5 */
#define GLIKEY_CODEWORD_STEP5   ((uint32_t)0xF0810F7EU) /*< Codeword for transition from STEP5 --> STEP6 */
#define GLIKEY_CODEWORD_STEP6   ((uint32_t)0x0F5DF0A2U) /*< Codeword for transition from STEP6 --> STEP7 */
#define GLIKEY_CODEWORD_STEP7   ((uint32_t)0xF0700F8FU) /*< Codeword for transition from STEP7 --> STEP8 */
#define GLIKEY_CODEWORD_STEP_EN ((uint32_t)0x0FFFF000U) /*< Codeword for transition from STEP 4/8 --> WR_EN */

#define GLIKEY_FSM_WR_DIS    0x0Bu
#define GLIKEY_FSM_INIT      0x16u
#define GLIKEY_FSM_STEP1     0x2Cu
#define GLIKEY_FSM_STEP2     0x58u
#define GLIKEY_FSM_STEP3     0xB0u
#define GLIKEY_FSM_STEP4     0x160u
#define GLIKEY_FSM_LOCKED    0xC01u
#define GLIKEY_FSM_WR_EN     0x1802u
#define GLIKEY_FSM_SSR_RESET 0x1005u

/*@}*/

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name GLIKEY Functional Operation
 * @{
 */

/*!
 * @brief Retreives the current status of Glikey.
 *
 * @param[in]   base    The base address of the Glikey instance
 *
 * @return Glikey status information
 */
uint32_t GLIKEY_GetStatus(GLIKEY_Type *base);

/*!
 * @brief Get if Glikey is locked
 *
 * This operation returns the locking status of Glikey.
 *
 * @return Status
 * @retval kStatus_GLIKEY_Locked if locked
 * @retval kStatus_GLIKEY_NotLocked if unlocked
 */
status_t GLIKEY_IsLocked(GLIKEY_Type *base);

/*!
 * @brief Check if Glikey is locked
 *
 * This operation returns the locking status of Glikey.
 *
 * @return Status kStatus_Success if success
 * @retval kStatus_GLIKEY_LockedError if locked
 * @retval kStatus_GLIKEY_NotLocked if unlocked
 */
status_t GLIKEY_CheckLock(GLIKEY_Type *base);

/*!
 * @brief Retreives the version and configuration of Glikey.
 *
 *
 * @param[in]   base    The base address of the Glikey instance
 * @param[out]  result  Pointer which will be filled with the Glikey hardware version
 *
 * @return Status kStatus_Success if success
 */
status_t GLIKEY_GetVersion(GLIKEY_Type *base, uint32_t *result);

/*!
 * @brief Perform a synchronous reset of Glikey.
 *
 * This function performs a synchrounous reset of the Glikey. This results in:
 * - Glikey will return to the INIT state, unless it is in the LOCK state
 *
 * @param[in]   base    The base address of the Glikey instance
 *
 * @return Status kStatus_Success if success
 * Possible errors: kStatus_GLIKEY_LockedError
 */
status_t GLIKEY_SyncReset(GLIKEY_Type *base);

/*!
 * @brief Set interrupt enable flag of Glikey.
 *
 * @param[in]   base    The base address of the Glikey instance
 * @param[in]   value   Value to set the interrupt enable flag to, see #[TODO: add reference to constants]
 *
 * @return Status kStatus_Success if success
 * Possible errors: kStatus_GLIKEY_LockedError
 */
status_t GLIKEY_SetIntEnable(GLIKEY_Type *base, uint32_t value);

/*!
 * @brief Get interrupt enable flag of Glikey.
 *
 * @param[in]   base    The base address of the Glikey instance
 * @param[out]  value   Pointer which will be filled with the interrupt enable status, see #[TODO: add reference to
 * constants]
 *
 * @return Status kStatus_Success if success
 */
status_t GLIKEY_GetIntEnable(GLIKEY_Type *base, uint32_t *value);

/*!
 * @brief Clear the interrupt status flag of Glikey.
 *
 * @param[in]   base    The base address of the Glikey instance
 *
 * @return Status kStatus_Success if success
 * Possible errors: kStatus_GLIKEY_LockedError
 */
status_t GLIKEY_ClearIntStatus(GLIKEY_Type *base);

/*!
 * @brief Set the interrupt status flag of Glikey.
 *
 * @param[in]   base    The base address of the Glikey instance
 *
 * @return Status kStatus_Success if success
 * Possible errors: kStatus_GLIKEY_LockedError
 */
status_t GLIKEY_SetIntStatus(GLIKEY_Type *base);

/*!
 * @brief Lock Glikey SFR (Special Function Registers) interface
 *
 * This operation locks the Glikey SFR interface if it is not locked yet.
 *
 * @param[in]   base    The base address of the Glikey instance
 *
 * @return Status kStatus_Success if success
 */
status_t GLIKEY_Lock(GLIKEY_Type *base);

/*!
 * @brief Lock Glikey index
 *
 * This operation is used to lock a Glikey index. It can only be executed from the WR_EN state,
 * executing it from any other state will result in Glikey entering WR_DIS state. When this happens
 * Glikey requires a reset (synchrous or asynchronous) to go back to INIT state.
 * If the Glikey SFR lock is active this operation will return an error.
 *
 * @param[in]   base    The base address of the Glikey instance
 *
 * @return Status kStatus_Success if success
 * Possible errors: kStatus_GLIKEY_LockedError, kStatus_GLIKEY_DisabledError
 */
status_t GLIKEY_LockIndex(GLIKEY_Type *base);

/*!
 * @brief Check if Glikey index is locked
 *
 * This operation returns the locking status of Glikey index.
 *
 * @param[in]   base    The base address of the Glikey instance
 * @param[in]   index   The index of the Glikey instance
 *
 * @return kStatus_GLIKEY_Locked if locked, kStatus_GLIKEY_NotLocked if unlocked
 * Possible errors: kStatus_Fail
 */
status_t GLIKEY_IsIndexLocked(GLIKEY_Type *base, uint32_t index);

/**
 * @brief Start Glikey enable
 *
 * This operation is used to set a new index and start a the sequence to enable it. It needs to be
 * started from the INIT state. If the new index is already locked Glikey will go to LOCKED state,
 * otherwise it will go to STEP1 state.
 * If this operation is used when Glikey is in any state other than INIT Glikey will go to WR_DIS
 * state. It can only recover from this state through a reset (synchrounous or asyncrhonous).
 * If the Glikey SFR lock is active this operation will return an error.
 *
 * @param[in]   base    The base address of the Glikey instance
 * @param[in]   index   The index of the Glikey instance
 *
 * @return Status kStatus_Success if success
 * Possible errors: kStatus_GLIKEY_LockedError, kStatus_Fail
 */
status_t GLIKEY_StartEnable(GLIKEY_Type *base, uint32_t index);

/**
 * @brief Continue Glikey enable
 *
 * This operation is used to progress through the different states of the state machine, starting
 * from STEP1 until the state WR_EN is reached. Each next state of the state machine can only be
 * reached by providing the right codeword to this function. If anything goes wrong the state machine
 * will go to WR_DIS state and can only recover from it through a reset (synchrous or asynchronous).
 * If the Glikey SFR lock is active this operation will return an error.
 *
 * @param[in]   base    The base address of the Glikey instance
 * @param[in]   codeword   Encoded word for progressing to next FSM state (see GLIKEY_CODEWORD_STEPx/EN)
 *
 * @return Status kStatus_Success if success
 * Possible errors: kStatus_GLIKEY_LockedError, kStatus_Fail, kStatus_GLIKEY_DisabledError
 */
/* [Design]
    - Check if Glikey is locked
        if ( GLIKEY_LOCKED == GLIKEY_GET_SFR_LOCK(base) ) return NXPCLGLIKEY_STATUS_LOCKED_ERROR
    - Decode the codeword and write to Glikey CTRL[]
        Write GLIKEY_CTRL(base, EnableSelect, EnableValue)
    - Check if an error occured
        - the only possible error here is FSM error which results in a transition to WR_DIS state
        - alternatively this can be confirmed by checking FSM state value
    - Only now we will check if the codeword itself is valid
        - this is done in this order to assure that the state machine reaches WR_DIS state when needed
        - check if XXYZ^UUVW == 0xFFFF and return kStatus_Fail when it fails
    - Return kStatus_Success
*/
status_t GLIKEY_ContinueEnable(GLIKEY_Type *base, uint32_t codeword);

/**
 * @brief End Glikey operation
 *
 * This operation is used to end a Glikey operation. It can only be executed from the WR_EN, LOCKED
 * and RESET states. Executing it from any other state will result in Glikey entering WR_DIS state.
 * When this happens Glikey requires a reset (synchrous or asynchronous) to go back to INIT state.
 * After this operation Glikey will go to INIT state or stay in LOCKED state when the index was locked.
 * If the Glikey SFR lock is active this operation will return an error.
 *
 * @return A code-flow protected error code (see @ref nxpCsslFlowProtection)
 *
 * @param[in]   base    The base address of the Glikey instance
 *
 * @return Status kStatus_Success if success, kStatus_GLIKEY_Locked if index is still locked
 * Possible errors: kStatus_GLIKEY_LockedError, kStatus_GLIKEY_DisabledError
 */
status_t GLIKEY_EndOperation(GLIKEY_Type *base);

/**
 * @brief Reset Glikey index
 *
 * This operation is used to reset a Glikey index. It can only be executed from the INIT state,
 * executing it from any other state will result in Glikey entering WR_DIS state. When this happens
 * Glikey requires a reset (synchrous or asynchronous) to go back to INIT state.
 * If the Glikey SFR lock is active or the index is locked this operation will return an error.
 *
 * @return A code-flow protected error code (see @ref nxpCsslFlowProtection)
 *
 * @return Status kStatus_Success if success, kStatus_GLIKEY_Locked if index is still locked
 * Possible errors: kStatus_GLIKEY_LockedError, kStatus_GLIKEY_DisabledError
 */
status_t GLIKEY_ResetIndex(GLIKEY_Type *base, uint32_t index);

/*! @}*/

#if defined(__cplusplus)
}
#endif   /* __cplusplus */

/*! @}*/ /* end of group glikey */

#endif   /* _FSL_GLIKEY_H_ */
