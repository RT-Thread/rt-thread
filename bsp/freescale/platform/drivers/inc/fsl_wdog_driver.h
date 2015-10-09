/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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
#ifndef __FSL_WDOG_DRIVER_H__
#define __FSL_WDOG_DRIVER_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_wdog_hal.h"
#if FSL_FEATURE_SOC_WDOG_COUNT

/*! 
 * @addtogroup wdog_driver
 * @{
 */
/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Table of base addresses for WDOG instances. */
extern WDOG_Type * const g_wdogBase[];

/* Table to save WDOG IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_wdogIrqId[WDOG_INSTANCE_COUNT];

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! 
 * @brief Data structure for Watchdog initialization
 *
 * This structure is used when initializing the WDOG during the wdog_init function call.
 * It contains all WDOG configurations.
 * @internal gui name="Common configuration" id="wdogCfg"
 */

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
 * @name Watchdog Driver
 * @{
 */
 

/*!
 * @brief Initializes the Watchdog.
 *
 * This function  initializes the WDOG. When called, the WDOG 
 * runs according to the requirements of the configuration.
 * 
 * @param userConfigPtr Watchdog user configure data structure, see #wdog_user_config_t.
 * @return kStatus_WDOG_Success means success. Otherwise, means failure.
 *
 */
wdog_status_t WDOG_DRV_Init(const wdog_config_t* userConfigPtr);

/*!
 * @brief Shuts down the Watchdog.
 *
 * This function shuts down the WDOG. 
 *
 * @return kStatus_WDOG_Success means success. Otherwise, means failure.
 */
wdog_status_t WDOG_DRV_Deinit(void);

/*!
 * @brief Refreshes the Watchdog.
 *
 *  This function feeds the WDOG. It sets the WDOG timer count to zero and 
 *  should be called before the Watchdog timer times out. Otherwise, a reset is asserted.
 *  Enough time should be allowed for the
 *  refresh sequence to be detected by the Watchdog timer on the Watchdog clock.
 *
 */
void WDOG_DRV_Refresh(void);

/*!
 * @brief Gets the Watchdog running status.
 *
 * This function gets the WDOG running status.
 *
 * @return Watchdog running status, false means not running, true means running
 */
bool WDOG_DRV_IsRunning(void);

/*!
 * @brief Resets the MCU by using the Watchdog.
 *
 * This function resets the MCU by using the WDOG. 
 *
 */
void WDOG_DRV_ResetSystem(void);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_WDOG_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

