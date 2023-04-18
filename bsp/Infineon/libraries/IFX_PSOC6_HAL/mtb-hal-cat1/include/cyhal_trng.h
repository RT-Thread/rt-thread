/***************************************************************************//**
* \file cyhal_trng.h
*
* \brief
* Provides a high level interface for interacting with the Infineon True Random
* Number Generator. This interface abstracts out the chip specific details. If
* any chip specific functionality is necessary, or performance is critical the
* low level functions can be used directly.
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
* \addtogroup group_hal_trng TRNG (True Random Number Generator)
* \ingroup group_hal
* \{
* High level interface to the True Random Number Generator (TRNG).
*
* This block uses dedicated hardware to efficiently generate true random numbers.
*
* \section subsection_trng_features Features
* * Number generated is statistically random
* * Based on physical processes exhibiting random variation
* * Generated sequences of numbers cannot be duplicated by running the process again
* * Uses polynomial generators with fixed and programmable polynomials
*
* \note This driver is not intended to be used as a security library. If a full security library
* is needed something like Mbed TLS should be used instead.
*
* \section subsection_trng_quickstart Quick Start
*
* \ref cyhal_trng_init initializes the TRNG and passes a pointer to the **TRNG** block through the **obj** object of  type \ref cyhal_trng_t.
*
* See \ref subsection_trng_use_case_1.
*
* \subsection subsection_trng_use_case_1 Simple TRNG number generation example
* The following snippet initializes a TRNG and generates a true random number.
*
* \snippet hal_trng.c snippet_cyhal_trng_simple_init
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_trng TRNG HAL Results
 *  TRNG specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** An invalid argument was passed to a function. */
#define CYHAL_TRNG_RSLT_ERR_BAD_ARGUMENT                \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TRNG, 0))
/** Hardware error in the crypto block. This will only occur if the Ring oscillators in the TRNG generator are explicitly
 *  disabled during TRNG generation.
 */
#define CYHAL_TRNG_RSLT_ERR_HW                          \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TRNG, 1))

/**
 * \}
 */

/** Initialize the random number generator.
 *
 * @param[out] obj  Pointer to a random number generator object. The caller must
 *  allocate the memory for this object but the init function will initialize its contents.
 * @return The status of the init request
 *
 * Returns \ref CY_RSLT_SUCCESS if the operation was successful
 */
cy_rslt_t cyhal_trng_init(cyhal_trng_t *obj);

/** Release the random number generator.
 *
 * @param[in,out] obj The random number generator object
 */
void cyhal_trng_free(cyhal_trng_t *obj);

/** Generate a random number.
 *
 * @param[in]  obj   The random number generator object
 * @return The random number generated
 *
 * See \ref subsection_trng_use_case_1
 */
uint32_t cyhal_trng_generate(const cyhal_trng_t *obj);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_TRNG_IMPL_HEADER
#include CYHAL_TRNG_IMPL_HEADER
#endif /* CYHAL_TRNG_IMPL_HEADER */

/** \} group_hal_trng */
