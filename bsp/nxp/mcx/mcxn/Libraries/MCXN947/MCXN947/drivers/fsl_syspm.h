/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SYSPM_H_
#define FSL_SYSPM_H_

#include "fsl_common.h"

/*! @addtogroup syspm */
/*! @{ */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief SYSPM driver version */
#define FSL_SYSPM_DRIVER_VERSION (MAKE_VERSION(2, 2, 0))

/*! @} */
/*! @brief syspm select control monitor */
typedef enum _syspm_monitor
{
    kSYSPM_Monitor0 = 0U, /*!< Monitor 0 */
#if (SYSPM_PMCR_COUNT > 1U)
    kSYSPM_Monitor1 = 1U, /*!< Monitor 1 */
#endif
} syspm_monitor_t;

/*! @brief syspm select event */
typedef enum _syspm_event
{
    kSYSPM_Event1 = 0U, /*!< Event 1 */
    kSYSPM_Event2 = 1U, /*!< Event 2 */
    kSYSPM_Event3 = 2U, /*!< Event 3 */
} syspm_event_t;

/*! @brief syspm set count mode */
typedef enum _syspm_mode
{
    kSYSPM_BothMode       = 0x00, /*!< count in both modes */
    kSYSPM_UserMode       = 0x02, /*!< count only in user mode */
    kSYSPM_PrivilegedMode = 0x03, /*!< count only in privileged mode */
} syspm_mode_t;

/*! @brief syspm start/stop control */
typedef enum _syspm_startstop_control
{
    kSYSPM_Idle               = 0x00, /*!< idle >*/
    kSYSPM_LocalStop          = 0x01, /*!< local stop */
    kSYSPM_LocalStart         = 0x02, /*!< local start */
    KSYSPM_EnableTraceControl = 0x04, /*!< enable global TSTART/TSTOP */
    kSYSPM_GlobalStart        = 0x05, /*!< global stop */
    kSYSPM_GlobalStop         = 0x06, /*!< global start */
} syspm_startstop_control_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*_cplusplus. */

/*!
 * @brief Initializes the SYSPM
 *
 * This function enables the SYSPM clock.
 *
 * @param base  SYSPM peripheral base address.
 */
void SYSPM_Init(SYSPM_Type *base);

/*!
 * @brief Deinitializes the SYSPM
 *
 * This function disables the SYSPM clock.
 *
 * @param base  SYSPM peripheral base address.
 */
void SYSPM_Deinit(SYSPM_Type *base);

/*!
 * @brief Select event counters
 *
 * @param base               SYSPM peripheral base address.
 * @param event              syspm select event, see to #syspm_event_t.
 * @param eventCode          select which event to be counted in PMECTRx., see to table Events.
 */
void SYSPM_SelectEvent(SYSPM_Type *base, syspm_monitor_t monitor, syspm_event_t event, uint8_t eventCode);

/*!
 * @brief Reset event counters
 *
 * @param base        SYSPM peripheral base address.
 * @param monitor     syspm control monitor, see to #syspm_monitor_t.
 */
void SYSPM_ResetEvent(SYSPM_Type *base, syspm_monitor_t monitor, syspm_event_t event);

#if !((defined(FSL_FEATURE_SYSPM_HAS_PMCR_RICTR) && (FSL_FEATURE_SYSPM_HAS_PMCR_RICTR == 0U)))
/*!
 * @brief Reset Instruction Counter
 *
 * @param base        SYSPM peripheral base address.
 * @param monitor     syspm control monitor, see to #syspm_monitor_t.
 */
void SYSPM_ResetInstructionEvent(SYSPM_Type *base, syspm_monitor_t monitor);
#endif

/*!
 * @brief Set count mode
 *
 * @param base               SYSPM peripheral base address.
 * @param monitor            syspm control monitor, see to #syspm_monitor_t.
 * @param mode               syspm select counter mode, see to #syspm_mode_t.
 */
void SYSPM_SetCountMode(SYSPM_Type *base, syspm_monitor_t monitor, syspm_mode_t mode);

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
void SYSPM_SetStartStopControl(SYSPM_Type *base, syspm_monitor_t monitor, syspm_startstop_control_t ssc);

#if !((defined(FSL_FEATURE_SYSPM_HAS_PMCR_DCIFSH)) && (FSL_FEATURE_SYSPM_HAS_PMCR_DCIFSH == 0U))
/*!
 * @brief Disable Counters if Stopped or Halted
 *
 * @param base              SYSPM peripheral base address.
 * @param monitor           syspm control monitor, see to #syspm_monitor_t.
 */
void SYSPM_DisableCounter(SYSPM_Type *base, syspm_monitor_t monitor);
#endif

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
uint64_t SYSPM_GetEventCounter(SYSPM_Type *base, syspm_monitor_t monitor, syspm_event_t event);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* FSL_SYSPM_H_*/
