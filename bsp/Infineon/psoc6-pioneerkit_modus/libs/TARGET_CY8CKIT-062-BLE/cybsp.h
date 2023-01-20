/***************************************************************************//**
* \file cybsp.h
*
* \brief
* Basic API for setting up boards containing a Cypress MCU.
*
********************************************************************************
* \copyright
* Copyright 2018-2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#pragma once

#include "cy_result.h"
#include "cybsp_types.h"
#include "cycfg.h"
#if defined(CYBSP_WIFI_CAPABLE) && defined(CY_USING_HAL)
#include "cyhal_sdio.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_bsp_macros Macros
* \{
*/

/** Failed to configure sysclk power management callback */
#define CYBSP_RSLT_ERR_SYSCLK_PM_CALLBACK  (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_BSP, 0))

/** \} group_bsp_macros */

/**
* \addtogroup group_bsp_functions Functions
* \{
*/

/**
 * \brief Initialize all hardware on the board
 * \returns CY_RSLT_SUCCESS if the board is sucessfully initialized, if there is
 *          a problem initializing any hardware it returns an error code specific
 *          to the hardware module that had a problem.
 */
cy_rslt_t cybsp_init(void);

#if defined(CYBSP_WIFI_CAPABLE) && defined(CY_USING_HAL)
/**
 * \brief Get the initialized sdio object used for communicating with the WiFi Chip.
 * \note This function should only be called after cybsp_init();
 * \returns The initialized sdio object.
 */
cyhal_sdio_t* cybsp_get_wifi_sdio_obj(void);
#endif /* defined(CYBSP_WIFI_CAPABLE) */

/** \} group_bsp_functions */

#ifdef __cplusplus
}
#endif /* __cplusplus */
