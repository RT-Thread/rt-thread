/***************************************************************************//**
* \file cyhal_crc.h
*
* \brief
* Provides a high level interface for interacting with the CRC hardware accelerator.
* This interface abstracts out the chip specific details. If any chip specific
* functionality is necessary, or performance is critical the low level functions
* can be used directly.
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
* \addtogroup group_hal_crc CRC (Cyclic Redundancy Check)
* \ingroup group_hal
* \{
* High level interface for interacting with the CRC, which provides hardware
* accelerated CRC computations.
* The CRC APIs are structured to enable usage in situations where the entire input data
* set is not available in memory at the same time. Therefore, each conversion consists of three steps:
* * A single call to \ref cyhal_crc_start, to initialize data structures used to compute CRC
* * One or more calls to \ref cyhal_crc_compute, to provide chunks of data
* * A single call to \ref cyhal_crc_finish, to finalize the computation and retrieve the result
*
* The table below provides CRC parameters for some common CRC algorithms.
* \note The Expected CRC column shows the computed CRC when the value "123456789" is passed to \ref cyhal_crc_compute.
*
* | CRC algorithm Name  | Len | Polynomial |Initial seed| Data REV | Data XOR | Rem REV | Remainder XOR | Expected CRC |
* | ------------------- | --- | ---------- |----------- | -------- | -------- | ------- | ------------- | ------------ |
* | CRC-6  / CDMA2000-A |  6  |    0x27    |    0x3F    |   false  |     0    |  false  |      0x00     |     0x0D     |
* | CRC-6  / CDMA2000-B |  6  |    0x07    |    0x3F    |   false  |     0    |  false  |      0x00     |     0x3B     |
* | CRC-6  / DARC       |  6  |    0x19    |    0x00    |   true   |     0    |  true   |      0x00     |     0x26     |
* | CRC-6  / ITU        |  6  |    0x03    |    0x00    |   true   |     0    |  true   |      0x00     |     0x06     |
* | CRC-8  / ITU        |  8  |    0x07    |    0x00    |   false  |     0    |  false  |      0x55     |     0xA1     |
* | CRC-8  / MAXIM      |  8  |    0x31    |    0x00    |   true   |     0    |  true   |      0x00     |     0xA1     |
* | CRC-8  / ROHC       |  8  |    0x07    |    0xFF    |   true   |     0    |  true   |      0x00     |     0xD0     |
* | CRC-8  / WCDMA      |  8  |    0x9B    |    0x00    |   true   |     0    |  true   |      0x00     |     0x25     |
* | CRC-16 / CCITT-0    | 16  |   0x1021   |   0xFFFF   |   false  |     0    |  false  |     0x0000    |    0x29B1    |
* | CRC-16 / CDMA2000   | 16  |   0xC867   |   0xFFFF   |   false  |     0    |  false  |     0x0000    |    0x4C06    |
* | CRC-32              | 32  | 0x04C11DB7 | 0xFFFFFFFF |   true   |     0    |  true   |   0xFFFFFFFF  |  0xCBF43926  |
* | CRC-32 / BZIP2      | 32  | 0x04C11DB7 | 0xFFFFFFFF |   false  |     0    |  false  |   0xFFFFFFFF  |  0xFC891918  |
*
* \note Algorithms that have less than 8 bits, like CRC-6, populate the lower bits and leave the high order bits 0.
*
* \note Many of the algorithm parameters can be customized.
*
* See \ref crc_algorithm_t and \ref subsection_crc_snippet_1 for more details.
*
* \section subsection_crc_quickstart Quick Start
*
* \ref cyhal_crc_init initializes the CRC generator and passes the pointer to the CRC block through the **obj** object of type \ref cyhal_crc_t.
*
* \subsection subsection_crc_snippet_1 Snippet1: CRC Generation
* The following snippet initializes a CRC generator and computes the CRC for a sample message.
*
* \snippet hal_crc.c snippet_cyhal_crc_simple_init
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_crc CRC HAL Results
 *  CRC specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Invalid argument */
#define CYHAL_CRC_RSLT_ERR_BAD_ARGUMENT                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_CRC, 0))

/**
 * \}
 */

/** @brief CRC algorithm parameters */
typedef struct
{
    uint32_t width; //!< Bit width of the CRC
    uint32_t polynomial; //!< The polynomial to use
    uint32_t lfsrInitState; //!< Initial state of the LFSR
    uint32_t dataXor; //!< Byte mask to xor with the data
    uint32_t remXor; //!< Mask to xor with the remainder.
    /**
     * The order in which data should be processed.
     * If 0, data is processed MSB first.
     * If 1, data is processed LSB first.
     */
    bool dataReverse;
    bool remReverse; //!< If 1, the remainder is reversed. If 0, it is not.
} crc_algorithm_t;

/** Initialize the CRC generator. This function reserves the CRYPTO block for CRC calculations.
 *
 * @param[out] obj  Pointer to a CRC generator object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @return          The status of the init request.
 *
 * Returns \ref CY_RSLT_SUCCESS if the operation was successful. Refer \ref subsection_crc_snippet_1 for more information.
 */
cy_rslt_t cyhal_crc_init(cyhal_crc_t *obj);

/** Release the CRC generator.
 *
 * @param[in,out] obj The CRC generator object
 */
void cyhal_crc_free(cyhal_crc_t *obj);

/** The CRC block is setup to perform CRC computation
 *
 * @param[in,out] obj       The CRC generator object
 * @param[in] algorithm     The CRC algorithm to use for computations Refer \ref crc_algorithm_t.
 * @return The status of the compute request
 *
 * \note The state of the CRC Block will be reset to the state provided by in the argument algorithm.
 *
 * Returns \ref CY_RSLT_SUCCESS if the operation was successful.
 */
cy_rslt_t cyhal_crc_start(cyhal_crc_t *obj, const crc_algorithm_t *algorithm);

/** Computes the CRC for the given data and accumulates the CRC with the CRC generated from previous calls.
 * This function can be called multiple times to provide additional data.
 * \note Input data must be 4-byte aligned. Refer \ref subsection_crc_snippet_1 for more details.
 * @param[in] obj    The CRC generator object
 * @param[in] data   The input data
 * @param[in] length The number of bytes in the data
 * @return The status of the compute request
 *
 * Returns \ref CY_RSLT_SUCCESS if the operation was successful.
 */
cy_rslt_t cyhal_crc_compute(const cyhal_crc_t *obj, const uint8_t *data, size_t length);

/** Finalizes the CRC computation and returns the CRC for the complete set of data passed through a
 * single call or multiple calls to \ref cyhal_crc_compute.
 * \note The computed CRC pointer provided must be 4 byte aligned. Refer to
 * \ref subsection_crc_snippet_1 for more details.
 *
 * \note If the length of the CRC is less than a full word, the result will be in the lower bits
 * allowing the result to be downcast if desired.
 *
 * @param[in]  obj The CRC generator object
 * @param[out] crc The computed CRC
 * @return The status of the compute request
 *
 * Returns \ref CY_RSLT_SUCCESS if the operation was successful.
 */
cy_rslt_t cyhal_crc_finish(const cyhal_crc_t *obj, uint32_t *crc);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_CRC_IMPL_HEADER
#include CYHAL_CRC_IMPL_HEADER
#endif /* CYHAL_CRC_IMPL_HEADER */

/** \} group_hal_crc */
