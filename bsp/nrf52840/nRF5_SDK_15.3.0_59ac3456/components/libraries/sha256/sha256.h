/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup sha256 SHA-256 hash library
 * @{
 * @ingroup app_common
 *
 * @brief  This module calculates SHA-256 (SHA-2, FIPS-180) hashes.
 *
 * @details To use this module, first call @ref sha256_init on a @ref sha256_context_t instance. Then call @ref
 *          sha256_update with the data to be hashed. This step can optionally be done with multiple
 *          calls to @ref sha256_update, each with a section of the data (in the correct order).
 *          After all data has been passed to @ref sha256_update, call @ref sha256_final to finalize
 *          and extract the hash value.
 *
 *          This code is adapted from code by Brad Conte, retrieved from
 *          https://github.com/B-Con/crypto-algorithms.
 *
 */

#ifndef SHA256_H
#define SHA256_H


#include <stdint.h>
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Current state of a hash operation.
 */
typedef struct {
    uint8_t data[64];
    uint32_t datalen;
    uint64_t bitlen;
    uint32_t state[8];
} sha256_context_t;


/**@brief Function for initializing a @ref sha256_context_t instance.
 *
 * @param[out] ctx  Context instance to be initialized.
 *
 * @retval NRF_SUCCESS     If the instance was successfully initialized.
 * @retval NRF_ERROR_NULL  If the parameter was NULL.
 */
ret_code_t sha256_init(sha256_context_t *ctx);

/**@brief Function for calculating the hash of an array of uint8_t data.
 *
 * @details This function can be called multiple times in sequence. This is equivalent to calling
 *          the function once on a concatenation of the data from the different calls.
 *
 * @param[in,out] ctx   Hash instance.
 * @param[in]     data  Data to be hashed.
 * @param[in]     len   Length of the data to be hashed.
 *
 * @retval NRF_SUCCESS     If the data was successfully hashed.
 * @retval NRF_ERROR_NULL  If the ctx parameter was NULL or the data parameter was NULL,  while the len parameter was not zero.
 */
ret_code_t sha256_update(sha256_context_t *ctx, const uint8_t * data, const size_t len);

/**@brief Function for extracting the hash value from a hash instance.
 *
 * @details This function should be called after all data to be hashed has been passed to the hash
 *          instance (by one or more calls to @ref sha256_update).
 *
 * Do not call @ref sha256_update again after @ref sha256_final has been called.
 *
 * @param[in,out] ctx   Hash instance.
 * @param[out]    hash  Array to hold the extracted hash value (assumed to be 32 bytes long).
 * @param[in]     le   Store the hash in little-endian.
 *
 * @retval NRF_SUCCESS     If the has value was successfully extracted.
 * @retval NRF_ERROR_NULL  If a parameter was NULL.
 */
ret_code_t sha256_final(sha256_context_t *ctx, uint8_t * hash, uint8_t le);


#ifdef __cplusplus
}
#endif

#endif   // SHA256_H

/** @} */
