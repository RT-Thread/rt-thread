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
#ifndef __FSL_COP_DRIVER_H__
#define __FSL_COP_DRIVER_H__

#include "fsl_cop_hal.h"
#include "fsl_device_registers.h"
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

/*! 
 * @addtogroup cop_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief Table of base addresses for COP instances. */
extern SIM_Type * const g_copBase[];

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
 * @name COP Driver
 * @{
 */


/*!
 * @brief Initializes the COP.
 *
 * This function initializes the COP. After it is called, the COP 
 * starts running according to the configuration.
 * Because all COP control registers are write-once only, the cop_init function
 * and the cop_shutdown function can be called only once. A second call has no effect.
 *
 * @param instance The COP peripheral instance number.
 * @param initPtr COP Initialize data structure.
 * @return The initialization status.
 *
 */
cop_status_t COP_DRV_Init(uint32_t instance, const cop_config_t* initPtr);

/*!
 * @brief Disables the COP Watchdog.
 *
 * This function disables the COP Watchdog.
 * Note: The COP configuration register is write-once after reset.
 * To disable the COP Watchdog, call this function first.
 *
 * @param instance The COP peripheral instance number.
 */
void COP_DRV_Disable(uint32_t instance);

/*!
 * @brief Resets the COP timeout counter.
 *
 *  This function feeds the COP. It sets the COP timer count to zero and
 *  should be called before the COP timer expires. Otherwise, a RESET is asserted.
 *
 * @param instance The COP peripheral instance number.
 */
void COP_DRV_Refresh(uint32_t instance);

/*!
 * @brief Gets the COP running status.
 *
 * This function gets the COP running status.
 * 
 * @param instance The COP peripheral instance number.
 * @return COP running status; 0 means not running; 1 means running
 */
bool COP_DRV_IsRunning(uint32_t instance);

/*!
 * @brief Resets the system.
 *
 * This function resets the device.
 *
 * @param instance The COP peripheral instance number.
 */
void COP_DRV_ResetSystem(uint32_t instance);

/*@}*/
#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_COP_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

