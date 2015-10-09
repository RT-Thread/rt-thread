/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_TRNG_DRIVER_H__
#define __FSL_TRNG_DRIVER_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_trng_hal.h"
#include "fsl_os_abstraction.h"
#if FSL_FEATURE_SOC_TRNG_COUNT
/*! 
 * @addtogroup trng_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/
/*! @brief Enables/disables multi-thread support in TRNG driver. It is achieved by mutex locking of critical sections.
 *   and is enabled by default for RTOS. It is optional and may be disabled if TRNG is used only by one RTOS task. */
#ifndef TRNG_DRV_RTOS_MULTI_THREAD
#define TRNG_DRV_RTOS_MULTI_THREAD  (USE_RTOS)
#endif

/*! @brief Enables/disables putting the calling task to "sleep" during the TRNG blocking entropy generation. If enabled, it requires using of TRNG IRQ handler. 
 *   and is enabled by default for RTOS. It is optional and may be disabled. */
#ifndef TRNG_DRV_RTOS_SLEEP
#define TRNG_DRV_RTOS_SLEEP         (USE_RTOS)
#endif

/*! @brief Table of base addresses for TRNG instances. */
extern TRNG_Type * const g_trngBase[];

/*! @brief Table to save TRNG IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_trngIrqId[];

/*! 
 * @brief Data structure for the TRNG initialization
 *
 * This structure initializes the TRNG by calling the the TRNG_DRV_Init() function.
 * It contains all TRNG configurations.
 * @internal gui name="Basic configuration" id="trngCfg"
 */
typedef struct _trng_user_config
{
    bool                            lock;                   /*!< @brief Disable programmability of TRNG registers. Default is 0. */
    trng_clock_mode_t               clockMode;              /*!< @brief Clock mode used to operate TRNG. Default is kTRNGClockModeRingOscillator.*/
    trng_ring_osc_div_t             ringOscDiv;             /*!< @brief Ring oscillator divide used by TRNG. Default is kTRNGRingOscDiv0.*/
    trng_sample_mode_t              sampleMode;             /*!< @brief Sample mode of the TRNG ring oscillator. Default is kTRNGSampleModeRaw.*/
    /* Seed Control*/
    uint16_t                        entropyDelay;           /*!< @brief Entropy Delay. Defines the length (in system clocks) of each Entropy sample taken. Default is 3200.*/
    uint16_t                        sampleSize;             /*!< @brief Sample Size. Defines the total number of Entropy samples that will be taken during Entropy generation. Default is 2500.*/
    uint16_t                        sparseBitLimit;         /*!< @brief Sparse Bit Limit which defines the maximum number of
                                                            * consecutive samples that may be discarded before an error is generated.
                                                            * This limit is used only for During Von Neumann sampling (enabled by TRNG_HAL_SetSampleMode()).
                                                            * Samples are discarded if two consecutive raw samples are both 0 or both 1. If
                                                            * this discarding occurs for a long period of time, it indicates that there is
                                                            * insufficient Entropy. Default is 63.*/
    /* Statistical Check Parameters.*/
    uint8_t                         retryCount;             /*!< @brief Retry count. It defines the number of times a statistical check may fails 
                                                            * during the TRNG Entropy Generation before generating an error. Default is 1.*/
    uint8_t                         longRunMaxLimit;        /*!< @brief Largest allowable number of consecutive samples of all 1, or all 0,
                                                            * that is allowed during the Entropy generation. Default is 34.*/
    trng_statistical_check_limit_t  monobitLimit;           /*!< @brief Maximum and minimum limits for statistical check of number of ones/zero detected during entropy generation. */
    trng_statistical_check_limit_t  runBit1Limit;           /*!< @brief Maximum and minimum limits for statistical check of number of runs of length 1 detected during entropy generation. */
    trng_statistical_check_limit_t  runBit2Limit;           /*!< @brief Maximum and minimum limits for statistical check of number of runs of length 2 detected during entropy generation. */
    trng_statistical_check_limit_t  runBit3Limit;           /*!< @brief Maximum and minimum limits for statistical check of number of runs of length 3 detected during entropy generation. */
    trng_statistical_check_limit_t  runBit4Limit;           /*!< @brief Maximum and minimum limits for statistical check of number of runs of length 4 detected during entropy generation. */
    trng_statistical_check_limit_t  runBit5Limit;           /*!< @brief Maximum and minimum limits for statistical check of number of runs of length 5 detected during entropy generation. */
    trng_statistical_check_limit_t  runBit6PlusLimit;       /*!< @brief Maximum and minimum limits for statistical check of number of runs of length 6 or more detected during entropy generation. */
    trng_statistical_check_limit_t  pokerLimit;             /*!< @brief Maximum and minimum limits for statistical check of "Poker Test". */
    trng_statistical_check_limit_t  frequencyCountLimit;    /*!< @brief Maximum and minimum limits for statistical check of entropy sample frequency count. */
} trng_user_config_t;

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the TRNG.
 *
 * This function initializes the TRNG. When called, the TRNG
 * runs immediately according to the specifications in the configuration.
 *
 * @param instance  TRNG instance ID.
 * @param user_config    Pointer to initialize configuration structure. 
 * @return If successful, returns the kStatus_TRNG_Success. Otherwise, it returns an error.
 */
trng_status_t TRNG_DRV_Init(uint32_t instance, const trng_user_config_t *user_config);

/*!
 * @brief Shuts down the TRNG.
 *
 * This function shuts down the TRNG.
 *
 * @param instance  TRNG instance ID
 * @return If successful, returns the kStatus_TRNG_Success. Otherwise, it returns an error.
 */
trng_status_t TRNG_DRV_Deinit(uint32_t instance);

/*!
 * @brief Initializes the user configuration structure to default values.
 *
 * This function fills the user configuration structure with default TRNG settings. 
 *
 * @param user_config   User configuration  structure.
 * @return If successful, returns the kStatus_TRNG_Success. Otherwise, it returns an error.
 */
trng_status_t  TRNG_DRV_InitUserConfigDefault(trng_user_config_t *user_config);


/*!
 * @brief Gets random data.
 *
 * This function gets random data from the TRNG.
 *
 * @param instance  TRNG instance ID
 * @param data  Pointer address used to store random data
 * @param data_size  Size of the buffer pointed by the data parameter
 * @return random data
 */
trng_status_t TRNG_DRV_GetRandomData(uint32_t instance, void *data, uint32_t data_size);


/*!
 * @brief TRNG interrupt handler.
 *
 * This function handles the TRNG interrupt.
 *
 * @param instance  TRNG instance ID
 */
void TRNG_DRV_IRQHandler(uint32_t instance);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_TRNG_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

