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

#if !defined(__FSL_MMAU_DRIVER_H__)
#define __FSL_MMAU_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_mmau_hal.h"
#include "fsl_os_abstraction.h"

/*!
 * @addtogroup mmau_driver MMAU Driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Table of base addresses for MMAU instances. */
extern const uint32_t g_mmauBaseAddr[];

/*! @brief Table to save MMAU IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_mmauIrqId[];

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif
  
/*!
 * @brief Initializes the MMAU module.
 *
 * This function initializes the MMAU module according to the userConfig structure.
 *
 * @param userConfigPtr Pointer to structure of "mmau_config_t".
 * @return Execution status.
 */  
mmau_status_t MMAU_DRV_Init(mmau_user_config_t * userConfigPtr);

/*!
 * @brief Deinitializes the MMAU module.
 *
 * This function deinitializes the MMAU module.
 * 
 * @return Execution status.
 */
mmau_status_t MMAU_DRV_Deinit(void);

/*!
 * @brief Driver-defined ISR in the MMAU module.
 *
 * This function is the driver-defined ISR in the MMAU module.
 * It includes the process for interrupt mode defined by the driver. Currently, it
 * is called inside the system-defined ISR.
 *
 */
void MMAU_DRV_IRQHandler(void);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_MMAU_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
