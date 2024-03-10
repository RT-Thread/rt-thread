/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_ITRC_H_
#define _FSL_ITRC_H_

#include "fsl_common.h"

/*!
 * @addtogroup ITRC
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Defines ITRC driver version 2.1.0.
 *
 * Change log:
 * - Version 2.1.0
 *   - Make SYSCON glitch platform dependent
 * - Version 2.0.0
 *   - initial version
 */
#define FSL_ITRC_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*@}*/

typedef enum _itrc_input_signals
{
    kITRC_CssGlitch = 0U,
    kITRC_RtcTamper = 1U,
    kITRC_Cdog      = 2U,
    kITRC_BodVbat   = 3u,
    kITRC_BodVdd    = 4u,
    kITRC_Watchdog  = 5u,
    kITRC_FlashEcc  = 6u,
    kITRC_Ahb       = 7u,
    kITRC_CssErr    = 8u,
#if defined(FSL_FEATURE_ITRC_HAS_SYSCON_GLITCH) && (FSL_FEATURE_ITRC_HAS_SYSCON_GLITCH > 0)
    kITRC_SysconGlitch = 9u,
#endif
    kITRC_Pkc      = 10u,
    kITRC_SwEvent1 = 14u,
    kITRC_SwEvent2 = 15u
} itrc_input_signals_t;

typedef enum _itrc_lock
{
    kITRC_Unlock = 0U,
    kITRC_Lock   = 1U,
} itrc_lock_t;

typedef enum _itrc_enable
{
    kITRC_Enable  = 0U,
    kITRC_Disable = 1U,
} itrc_enable_t;

typedef enum _itrc_out_signals
{
    kITRC_Irq        = 16U,
    kITRC_CssReset   = 17U,
    kITRC_PufZeroize = 18U,
    kITRC_RamZeroize = 19u,
    kITRC_ChipReset  = 20u,
    kITRC_TamperOut  = 21u,
} itrc_out_signals_t;

#if defined(FSL_FEATURE_ITRC_HAS_SYSCON_GLITCH) && (FSL_FEATURE_ITRC_HAS_SYSCON_GLITCH > 0)
#define IN_EVENTS_MASK                                                                           \
    (ITRC_STATUS_IN0_STATUS_MASK | ITRC_STATUS_IN1_STATUS_MASK | ITRC_STATUS_IN2_STATUS_MASK |   \
     ITRC_STATUS_IN3_STATUS_MASK | ITRC_STATUS_IN4_STATUS_MASK | ITRC_STATUS_IN5_STATUS_MASK |   \
     ITRC_STATUS_IN6_STATUS_MASK | ITRC_STATUS_IN7_STATUS_MASK | ITRC_STATUS_IN8_STATUS_MASK |   \
     ITRC_STATUS_IN9_STATUS_MASK | ITRC_STATUS_IN10_STATUS_MASK | ITRC_STATUS_IN14_STATUS_MASK | \
     ITRC_STATUS_IN15_STATUS_MASK)
#else
#define IN_EVENTS_MASK                                                                         \
    (ITRC_STATUS_IN0_STATUS_MASK | ITRC_STATUS_IN1_STATUS_MASK | ITRC_STATUS_IN2_STATUS_MASK | \
     ITRC_STATUS_IN3_STATUS_MASK | ITRC_STATUS_IN4_STATUS_MASK | ITRC_STATUS_IN5_STATUS_MASK | \
     ITRC_STATUS_IN6_STATUS_MASK | ITRC_STATUS_IN7_STATUS_MASK | ITRC_STATUS_IN8_STATUS_MASK | \
     ITRC_STATUS_IN10_STATUS_MASK | ITRC_STATUS_IN14_STATUS_MASK | ITRC_STATUS_IN15_STATUS_MASK)
#endif /* FSL_FEATURE_ITRC_HAS_SYSCON_GLITCH */

#define OUT_ACTIONS_MASK                                                                          \
    (ITRC_STATUS_OUT0_STATUS_MASK | ITRC_STATUS_OUT1_STATUS_MASK | ITRC_STATUS_OUT2_STATUS_MASK | \
     ITRC_STATUS_OUT3_STATUS_MASK | ITRC_STATUS_OUT4_STATUS_MASK | ITRC_STATUS_OUT5_STATUS_MASK)

#ifndef ITRC
#define ITRC ITRC0
#endif

/*******************************************************************************
 * API
 *******************************************************************************/

extern void ITRC0_DriverIRQHandler(void);

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name ITRC Functional Operation
 * @{
 */

/*!
 * @brief Set ITRC Action to Event
 *
 * This function sets input Event signal to corresponding output Action response signal.
 *
 * @param base ITRC peripheral base address
 * @param out ITRC OUT signal action
 * @param in ITRC IN signal event
 * @param lock if set locks INx_SEL configuration. This can be cleared only by PMC Core reset.
 * @param enable if set input Event will be selected for output Action, otherwise disable (if not already locked).
 * @return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_SetActionToEvent(
    ITRC_Type *base, itrc_out_signals_t out, itrc_input_signals_t in, itrc_lock_t lock, itrc_enable_t enable);

/*!
 * @brief Trigger ITRC SW Event 0
 *
 * This funciton set SW_EVENT0 register with value !=0 which triggers ITRC SW Event 0.
 *
 * @param base ITRC peripheral base address
 */
void ITRC_SetSWEvent0(ITRC_Type *base);

/*!
 * @brief Trigger ITRC SW Event 1
 *
 * This funciton set SW_EVENT1 register with value !=0 which triggers ITRC SW Event 1.
 *
 * @param base ITRC peripheral base address
 */
void ITRC_SetSWEvent1(ITRC_Type *base);

/*!
 * @brief Get ITRC Status
 *
 * This function returns ITRC register status.
 *
 * @param base ITRC peripheral base address
 * @return Value of ITRC STATUS register
 */
status_t ITRC_GetStatus(ITRC_Type *base);

/*!
 * @brief Clear ITRC status
 *
 * This function clears corresponding ITRC event or action in STATUS register.
 *
 * @param base ITRC peripheral base address
 * @param word 32bit word represent corresponding event/action in STATUS register to be cleared (see
 * ITRC_STATUS_INx/OUTx_STATUS)
 * @return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_ClearStatus(ITRC_Type *base, uint32_t word);

/*!
 * @brief Clear All ITRC status
 *
 * This function clears all event and action status.
 *
 * @param base ITRC peripheral base address
 * @return kStatus_Success if success
 */
status_t ITRC_ClearAllStatus(ITRC_Type *base);

/*!
 * @brief Initialize ITRC
 *
 * This function initializes ITRC by enabling IRQ.
 *
 * @param base ITRC peripheral base address
 * @param conf ITRC configuration structure
 * @return Status of the init operation
 */
status_t ITRC_Init(ITRC_Type *base);

/*!
 * @brief Deinitialize ITRC
 *
 * This function deinitializes ITRC by disabling IRQ.
 *
 * @param base ITRC peripheral base address
 */
void ITRC_Deinit(ITRC_Type *base);

/*! @}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/ /* end of group itrc */

#endif /* _FSL_ITRC_H_ */
