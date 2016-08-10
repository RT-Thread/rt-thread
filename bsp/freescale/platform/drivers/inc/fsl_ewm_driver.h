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
#ifndef __FSL_EWM_DRIVER_H__
#define __FSL_EWM_DRIVER_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_ewm_hal.h"
#if FSL_FEATURE_SOC_EWM_COUNT

/*! 
 * @addtogroup ewm_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief Table of base addresses for EWM instances. */
extern EWM_Type * const g_ewmBase[];

/*! @brief Table to save EWM IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_ewmIrqId[EWM_INSTANCE_COUNT];

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name EWM Driver
 * @{
 */


/*!
 * @brief Initializes the EWM.
 *
 * This function initializes the EWM. When called, the EWM 
 * runs according to the configuration.
 *
 * @param instance EWM instance ID
 * @param ConfigPtr EWM user configure data structure, see #EWM_user_config_t
 * @return Execution status.
 */
ewm_status_t EWM_DRV_Init(uint32_t instance, const ewm_config_t* ConfigPtr);

/*!
 * @brief Closes the clock for EWM.
 *
 * This function sets the run time array to zero and closes the clock.
 *
 * @param instance EWM instance ID
 */
void EWM_DRV_Deinit(uint32_t instance);

/*!
 * @brief Refreshes the EWM.
 *
 * This function feeds the EWM. It sets the EWM timer count to zero and 
 * should be called before the EWM timer times out.
 *
 * @param instance EWM instance ID
 */
void EWM_DRV_Refresh(uint32_t instance);

/*!
 * @brief Gets the EWM running status.
 *
 * This function gets the EWM running status.
 *
 * @param instance EWM instance ID
 * @return EWM running status. False means not running. True means running
 */
bool EWM_DRV_IsRunning(uint32_t instance);

/*!
 * @brief Enables/disables the EWM interrupt.
 *
 * @param instance EWM instance ID.
 * @param enable EWM interrupt enable/disable.
 */
void EWM_DRV_SetIntCmd(uint32_t instance, bool enable);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_EWM_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

