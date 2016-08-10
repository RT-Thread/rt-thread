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

#ifndef __FSL_LTC_DRIVER_H__
#define __FSL_LTC_DRIVER_H__

#include "fsl_ltc_hal.h"
#if FSL_FEATURE_LTC_HAS_DES
#include "fsl_ltc_driver_des.h"
#endif
#include "fsl_ltc_driver_aes.h"
#include "fsl_ltc_driver_hash.h"
#if FSL_FEATURE_LTC_HAS_PKHA
#include "fsl_ltc_driver_pkha.h"
#include "fsl_ltc_driver_rsa.h"
#endif
#include "fsl_clock_manager.h"
#include "fsl_os_abstraction.h"

/*!
 * @addtogroup ltc_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/
/*! @brief Enables/disables multithread support in the LTC driver. 
 *
 *  Enables/disables multithread support in the LTC driver, which is achieved by locking critical sections with a mutex and enabled by default for RTOS. */
#ifndef LTC_DRV_RTOS_MULTI_THREAD
#define LTC_DRV_RTOS_MULTI_THREAD  (USE_RTOS)
#endif

/*! @brief Enables/disables putting the calling task to "sleep" during the LTC blocking operation. 
 *
 *  Enables/disables putting the calling task to "sleep" during the LTC blocking operation. If enabled, it requires using of LTC IRQ handler. 
 *  It is enabled by default for RTOS. */
#ifndef LTC_DRV_RTOS_SLEEP
#define LTC_DRV_RTOS_SLEEP         (USE_RTOS)
#endif

/*! @brief Table of base addresses for LTC instances. */
extern LTC_Type * const g_ltcBase[];

/*! @brief Table to save LTC IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_ltcIrqId[];

/*******************************************************************************
 * API
 ******************************************************************************/
 
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the LTC driver.
 * This function initializes the LTC driver.
 * @param instance LTC instance ID.
 */
ltc_status_t LTC_DRV_Init(uint32_t instance);

/*!
 * @brief Deinitializes the LTC driver.
 * This function deinitializes the LTC driver.
 * @param instance LTC instance ID.
 */
void LTC_DRV_Deinit(uint32_t instance);

/*!
 * @brief LTC interrupt handler.
 *
 * This function handles the LTC interrupt.
 *
 * @param instance LTC instance ID.
 */
void LTC_DRV_IRQHandler(uint32_t instance);


#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* __FSL_LTC_DRIVER_H__ */

