/***************************************************************************//**
* \file cyhal_hwmgr.h
*
* \brief
* Provides a high level interface for managing hardware resources. This is
* used to track what hardware blocks are already being used so they are not over
* allocated.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
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

/**
* \addtogroup group_hal_hwmgr HWMGR (Hardware Manager)
* \ingroup group_hal
* \{
* High level interface to the Hardware Manager.
*
* \section section_hwmgr_features Features
* * Allows HAL drivers or application firmware to mark specific hardware resources
*   as reserved. When this is done, other reservation requests for the same resource will be denied.
* * For resources which are interchangeable such as clock dividers, provides allocation
*   and reservation of an available instance.
*
* \section section_hwmgr_quickstart Quick Start
* * \ref cyhal_hwmgr_init is used to initialize the hardware manager to keep
* track of resources being used.
* * \ref cyhal_hwmgr_reserve reserves a specified resource if available.
* * \ref cyhal_hwmgr_free frees the specified resource.
* * \ref cyhal_hwmgr_allocate can be used to allocate a free block of specified
* resource, if available.
*
*
* \section section_hwmgr_snippets Code snippets
* \subsection subsection_hwmgr_snippet_1 Snippet 1: Freeing a block used by PDL or configurators
* The following snippet shows how a specific resource used directly in PDL or the
* configurators can be freed so that it can be used by HAL.<br>
*
* \snippet hal_hwmgr.c snippet_cyhal_hwmgr_reserve
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_hwmgr HWMGR HAL Results
 *  HWMGR specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** The requested resource type is invalid */
#define CYHAL_HWMGR_RSLT_ERR_INVALID                    \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_HWMGR, 0))
/** The requested resource is already in use */
#define CYHAL_HWMGR_RSLT_ERR_INUSE                      \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_HWMGR, 1))
/** No resources of the requested type are available */
#define CYHAL_HWMGR_RSLT_ERR_NONE_FREE                  \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_HWMGR, 2))
/** No hardware connection available */
#define CYHAL_HWMGR_RSLT_ERR_NO_CONNECTION                \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_HWMGR, 3))
/** Attempt to free a resource that was not used */
#define CYHAL_HWMGR_RSLT_WARN_UNUSED                    \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_WARNING, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_HWMGR, 50))

/**
 * \}
 */




/** Initializes the hardware manager to keep track of what resources are being used.
 *
 * @return The status of the init request
 *
 */
cy_rslt_t cyhal_hwmgr_init(void);

/** Reserve the specified resource. The exact block number and
 * channel number must be specified. If this is not know, use
 * \ref cyhal_hwmgr_allocate.
 *
 * \note This function is called by the init function of hardware blocks.
 * Calling this again for the same block will result in error since the hardware
 * block is already marked as consumed.
 *
 * @param[in] obj  The resource object that should be reserved
 * @return The status of the reserve request
 *
 * See \ref subsection_hwmgr_snippet_1
 */
cy_rslt_t cyhal_hwmgr_reserve(const cyhal_resource_inst_t* obj);

/** Free the specified resource to allow it to be reused.
 *
 * @param[in,out] obj The resource object to free
 *
 * See \ref subsection_hwmgr_snippet_1
 */
void cyhal_hwmgr_free(const cyhal_resource_inst_t* obj);

/** Allocates a free block of the specified type if available
 * This function is used when the exact block number and channel number of the
 * resource is not known. This function loops through all available resource
 * of the specified type and assigns the resource if available.
 * This function internally calls \ref cyhal_hwmgr_reserve function and hence,
 * it should not be called again.
 *
 * @param[in]  type The type of resource to allocate.
 * @param[out] obj  The resource object.
 * @return The status of the allocate request.
 *
 */
cy_rslt_t cyhal_hwmgr_allocate(cyhal_resource_t type, cyhal_resource_inst_t* obj);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_HWMGR_IMPL_HEADER
#include CYHAL_HWMGR_IMPL_HEADER
#endif /* CYHAL_HWMGR_IMPL_HEADER */

/** \} group_hal_hwmgr */
