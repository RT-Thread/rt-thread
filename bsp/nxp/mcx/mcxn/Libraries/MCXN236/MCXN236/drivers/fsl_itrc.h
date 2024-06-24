/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_ITRC_H_
#define FSL_ITRC_H_

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
/*! @brief Defines ITRC driver version 2.3.0.
 *
 * Change log:
 * - Version 2.3.0
 *   - Update names of kITRC_SwEvent1/2 to kITRC_SwEvent0/1 to align with RM
 * - Version 2.2.0
 *   - Update driver to new version and input events
 * - Version 2.1.0
 *   - Make SYSCON glitch platform dependent
 * - Version 2.0.0
 *   - initial version
 */
#define FSL_ITRC_DRIVER_VERSION (MAKE_VERSION(2, 3, 0))
/*@}*/

typedef enum _itrc_input_signals
{
    kITRC_Glitch   = 0U,
    kITRC_Tamper   = 1U,
    kITRC_Cdog     = 2U,
    kITRC_BodVbat  = 3u,
    kITRC_BodVdd   = 4u,
    kITRC_Watchdog = 5u,
    kITRC_FlashEcc = 6u,
    kITRC_Ahb      = 7u,
    kITRC_ElsErr   = 8u,
#if defined(FSL_FEATURE_ITRC_HAS_SYSCON_GLITCH) && (FSL_FEATURE_ITRC_HAS_SYSCON_GLITCH > 0)
    kITRC_SysconGlitch = 9u,
#endif
    kITRC_Pkc = 10u,
#if defined(ITRC_OUTX_SEL_OUTX_SELY_OUT_SEL_IN11_SELn_MASK)
    kITRC_Cdog1 = 11u,
#endif /* ITRC_OUTX_SEL_OUTX_SELY_OUT_SEL_IN11_SELn_MASK */
#if defined(ITRC_OUTX_SEL_OUTX_SELY_OUT_SEL_IN12_SELn_MASK)
    kITRC_Watchdog1 = 12u,
#endif /* ITRC_OUTX_SEL_OUTX_SELY_OUT_SEL_IN12_SELn_MASK*/
#if defined(ITRC_OUTX_SEL_OUTX_SELY_OUT_SEL_IN13_SELn_MASK)
    kITRC_Freqme = 13u,
#endif /* ITRC_OUTX_SEL_OUTX_SELY_OUT_SEL_IN13_SELn_MASK */
    kITRC_SwEvent0 = 14u,
    kITRC_SwEvent1 = 15u,
#if defined(ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN16_SELn_MASK)
    kITRC_VddSysLow = 16u,
#endif /* ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN16_SELn_MASK */
#if defined(ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN17_SELn_MASK)
    kITRC_VddIoLow = 17u,
#endif /* ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN17_SELn_MASK */
#if defined(ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN19_SELn_MASK)
    kITRC_VddTemp = 19u,
#endif /* ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN19_SELn_MASK */
#if defined(ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN20_SELn_MASK)
    kITRC_VddClock = 20u,
#endif /* ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN20_SELn_MASK */
#if defined(ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN21_SELn_MASK)
    kITRC_INTM0 = 21u,
#endif /* ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN21_SELn_MASK */
#if defined(ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN22_SELn_MASK)
    kITRC_INTM1 = 22u,
#endif /* ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN22_SELn_MASK */
#if defined(ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN23_SELn_MASK)
    kITRC_INTM2 = 23u,
#endif /* ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN23_SELn_MASK */
#if defined(ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN24_SELn_MASK)
    kITRC_INTM3 = 24u,
#endif /* ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN24_SELn_MASK */
#if defined(ITRC_OUTX_SEL_1_OUTX_SELY_OUT_SEL_1_IN25_SELn_MASK) && \
    defined(ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN32_SELn_MASK)
    kITRC_SoCTrim0 = 25u,
    kITRC_SoCTrim1 = 26u,
    kITRC_SoCTrim2 = 27u,
    kITRC_SoCTrim3 = 28u,
    kITRC_SoCTrim4 = 29u,
    kITRC_SoCTrim5 = 30u,
    kITRC_SoCTrim6 = 31u,
    kITRC_SoCTrim7 = 32u,
#endif /* ITRC_OUTX_SEL_x_OUTX_SELY_OUT_SEL_INxx_SELn_MASK */
#if defined(ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN33_SELn_MASK)
    kITRC_GdetSfr = 33u,
#endif /* ITRC_OUTX_SEL_x_OUTX_SELY_OUT_SEL_INxx_SELn_MASK */
#if defined(ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN34_SELn_MASK)
    kITRC_VddCore = 34u,
#endif /* ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN34_SELn_MASK */
#if defined(ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN35_SELn_MASK)
    kITRC_VddSys = 35u,
#endif /* ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN35_SELn_MASK */
#if defined(ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN36_SELn_MASK)
    kITRC_VddIo = 36u,
#endif /* ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN36_SELn_MASK */
#if defined(ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN37_SELn_MASK)
    kITRC_FlexspiGcm = 37u,
#endif /* ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN37_SELn_MASK */
#if defined(ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN46_SELn_MASK)
    kITRC_Sm3Err = 46u,
#endif /* ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN46_SELn_MASK */
#if defined(ITRC_OUTX_SEL_2_OUTX_SELY_OUT_SEL_2_IN47_SELn_MASK)
    kITRC_TrngErr = 47u,
#endif /*  */
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
    kITRC_Irq        = 0U,
    kITRC_ElsReset   = 1U,
    kITRC_PufZeroize = 2U,
    kITRC_RamZeroize = 3u,
    kITRC_ChipReset  = 4u,
    kITRC_TamperOut  = 5u,
    kITRC_TamperOut1 = 6u,
} itrc_out_signals_t;

/* Inputs 0 to 15 events mask */
#if defined(FSL_FEATURE_ITRC_HAS_SYSCON_GLITCH) && (FSL_FEATURE_ITRC_HAS_SYSCON_GLITCH > 0)
#define IN_0_15_EVENTS_MASK                                                                      \
    (ITRC_STATUS_IN0_STATUS_MASK | ITRC_STATUS_IN1_STATUS_MASK | ITRC_STATUS_IN2_STATUS_MASK |   \
     ITRC_STATUS_IN3_STATUS_MASK | ITRC_STATUS_IN4_STATUS_MASK | ITRC_STATUS_IN5_STATUS_MASK |   \
     ITRC_STATUS_IN6_STATUS_MASK | ITRC_STATUS_IN7_STATUS_MASK | ITRC_STATUS_IN8_STATUS_MASK |   \
     ITRC_STATUS_IN9_STATUS_MASK | ITRC_STATUS_IN10_STATUS_MASK | ITRC_STATUS_IN14_STATUS_MASK | \
     ITRC_STATUS_IN15_STATUS_MASK)
#else
#define IN_0_15_EVENTS_MASK                                                                    \
    (ITRC_STATUS_IN0_STATUS_MASK | ITRC_STATUS_IN1_STATUS_MASK | ITRC_STATUS_IN2_STATUS_MASK | \
     ITRC_STATUS_IN3_STATUS_MASK | ITRC_STATUS_IN4_STATUS_MASK | ITRC_STATUS_IN5_STATUS_MASK | \
     ITRC_STATUS_IN6_STATUS_MASK | ITRC_STATUS_IN7_STATUS_MASK | ITRC_STATUS_IN8_STATUS_MASK | \
     ITRC_STATUS_IN10_STATUS_MASK | ITRC_STATUS_IN14_STATUS_MASK | ITRC_STATUS_IN15_STATUS_MASK)
#endif /* FSL_FEATURE_ITRC_HAS_SYSCON_GLITCH */

/* Inputs 15 to 47 events mask */
#if defined(ITRC_STATUS1_IN16_STATUS_MASK) && defined(ITRC_STATUS1_IN47_STATUS)
#define IN_16_47_EVENTS_MASK                                                                               \
    (ITRC_STATUS1_IN16_STATUS_MASK | ITRC_STATUS1_IN17_STATUS_MASK | ITRC_STATUS1_IN18_STATUS_MASK |       \
     ITRC_STATUS1_IN19_STATUS_MASK | ITRC_STATUS1_IN20_STATUS_MASK | ITRC_STATUS1_IN24_21_STATUS_MASK |    \
     ITRC_STATUS1_IN24_21_STATUS_MASK | ITRC_STATUS1_IN32_25_STATUS_MASK | ITRC_STATUS1_IN33_STATUS_MASK | \
     ITRC_STATUS1_IN34_STATUS_MASK | ITRC_STATUS1_IN35_STATUS_MASK | ITRC_STATUS1_IN36_STATUS_MASK |       \
     ITRC_STATUS1_IN37_STATUS_MASK | ITRC_STATUS1_IN46_STATUS_MASK | ITRC_STATUS1_IN47_STATUS_MASK)
#endif /* ITRC_STATUS1_IN16_STATUS_MASK && ITRC_STATUS1_IN47_STATUS */

/* Output actions mask */
#if defined(ITRC_STATUS_OUT6_STATUS)
#define OUT_ACTIONS_MASK                                                                          \
    (ITRC_STATUS_OUT0_STATUS_MASK | ITRC_STATUS_OUT1_STATUS_MASK | ITRC_STATUS_OUT2_STATUS_MASK | \
     ITRC_STATUS_OUT3_STATUS_MASK | ITRC_STATUS_OUT4_STATUS_MASK | ITRC_STATUS_OUT5_STATUS_MASK | \
     ITRC_STATUS_OUT6_STATUS_MASK)
#else
#define OUT_ACTIONS_MASK                                                                          \
    (ITRC_STATUS_OUT0_STATUS_MASK | ITRC_STATUS_OUT1_STATUS_MASK | ITRC_STATUS_OUT2_STATUS_MASK | \
     ITRC_STATUS_OUT3_STATUS_MASK | ITRC_STATUS_OUT4_STATUS_MASK | ITRC_STATUS_OUT5_STATUS_MASK)
#endif /* ITRC_STATUS_OUT6_STATUS */

#define ITRC_OUT_COUNT (7u)
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
uint32_t ITRC_GetStatus(ITRC_Type *base);

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

#if defined(ITRC_STATUS1_IN16_STATUS_MASK)
/*!
 * @brief Get ITRC Status 1
 *
 * This function returns ITRC STATUS1 register value.
 *
 * @param base ITRC peripheral base address
 * @return Value of ITRC STATUS1 register
 */
uint32_t ITRC_GetStatus1(ITRC_Type *base);

/*!
 * brief Clear ITRC status 1
 *
 * This function clears corresponding ITRC event or action in STATUS1 register.
 *
 * param base ITRC peripheral base address
 * param word 32bit word represent corresponding event/action in STATUS1 register to be cleared (see
 * ITRC_STATUS_INx/OUTx_STATUS)
 * return kStatus_Success if success, kStatus_InvalidArgument otherwise
 */
status_t ITRC_ClearStatus1(ITRC_Type *base, uint32_t word);
#endif /* defined(ITRC_STATUS1_IN16_STATUS_MASK) */

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

#endif /* FSL_ITRC_H_ */
