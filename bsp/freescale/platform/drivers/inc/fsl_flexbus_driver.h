/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#ifndef __FSL_FLEXBUS_DRIVER_H__
#define __FSL_FLEXBUS_DRIVER_H__

#include "fsl_flexbus_hal.h"
#if FSL_FEATURE_SOC_FB_COUNT

/*!
 * @addtogroup flexbus_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Table of base addresses for FlexBus instances. */
extern FB_Type * const g_fbBase[];

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the FlexBus driver.
 *
 * @param instance The FlexBus peripheral instance number.
 * @param fb_config FlexBus input user configuration
 * @return Execution status.
 */
flexbus_status_t FLEXBUS_DRV_Init(uint32_t instance, const flexbus_user_config_t *fb_config);

/*!
 * @brief Shuts down the FlexBus driver.
 *
 * @param instance The FlexBus peripheral instance number.
 * @return Execution status.
 */
flexbus_status_t FLEXBUS_DRV_Deinit(uint32_t instance);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_FLEXBUS_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

