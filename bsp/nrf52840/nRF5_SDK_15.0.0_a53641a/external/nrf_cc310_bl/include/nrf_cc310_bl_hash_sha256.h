/**************************************************************************************
* Copyright (c) 2016-2017, ARM Limited or its affiliates. All rights reserved         *
*                                                                                     *
* This file and the related binary are licensed under the following license:          *
*                                                                                     *
* ARM Object Code and Header Files License, v1.0 Redistribution.                      *
*                                                                                     *
* Redistribution and use of object code, header files, and documentation, without     *
* modification, are permitted provided that the following conditions are met:         *
*                                                                                     *
* 1) Redistributions must reproduce the above copyright notice and the                *
*    following disclaimer in the documentation and/or other materials                 *
*    provided with the distribution.                                                  *
*                                                                                     *
* 2) Unless to the extent explicitly permitted by law, no reverse                     *
*    engineering, decompilation, or disassembly of is permitted.                      *
*                                                                                     *
* 3) Redistribution and use is permitted solely for the purpose of                    *
*    developing or executing applications that are targeted for use                   *
*    on an ARM-based product.                                                         *
*                                                                                     *
* DISCLAIMER. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                  *
* CONTRIBUTORS "AS IS." ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT             *
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT,        *
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED            *
* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR              *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF              *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING                *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                  *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                        *
**************************************************************************************/
#ifndef NRF_CC310_BL_HASH_SHA256_H__
#define NRF_CC310_BL_HASH_SHA256_H__

/**@file
 *
 * @defgroup nrf_cc310_bl_hash_sha256 nrf_cc310_bl Hash SHA-256 API
 * @ingroup nrf_cc310_bl
 * @brief Type definitions and public APIs for nrf_cc310_bl HASH using SHA-256.
 * @{
 */

#include <stdint.h>
#include "nrf_cc310_bl_hash_common.h"
#include "crys_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Structure to hold SHA-256 context information.
 */
typedef struct
{
    uint32_t    init_val;
    uint8_t     context_buffer[NRF_CC310_BL_HASH_CONTEXT_BUFFER_SIZE_SHA256];
} nrf_cc310_bl_hash_context_sha256_t;


/**@brief Array to hold SHA-256 hash digest.
 */
typedef uint8_t nrf_cc310_bl_hash_digest_sha256_t[NRF_CC310_BL_SHA256_DIGEST_SIZE_IN_BYTES];


/**@brief Function for initializing the SHA-256 context.
 *
 * @note Memory pointed to in hash context must be allocated prior to this call.
 *
 * @param[in,out]   p_hash_context  Structure holding context information for
 *                                  the SHA-256 operation.
 *
 * @retval CRYS_OK If call was successful.
 * @retval  CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR    p_hash_context was NULL.
 */
CRYSError_t nrf_cc310_bl_hash_sha256_init(
    nrf_cc310_bl_hash_context_sha256_t * const p_hash_context);


/** @brief Function for running an update to the SHA-256 hash calculation.
 *
 * @param[in,out]   p_hash_context  Structure holding context information
 *                                  for the SHA-256 operation.
 *
 * @retval CRYS_OK If call was successful.
 * @retval CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR    p_hash_context was NULL.
 * @retval CRYS_HASH_USER_CONTEXT_CORRUPTED_ERROR          p_hash_context not initialized.
 * @retval CRYS_HASH_LAST_BLOCK_ALREADY_PROCESSED_ERROR    p_hash_context already finalized.
 */
CRYSError_t nrf_cc310_bl_hash_sha256_update(
    nrf_cc310_bl_hash_context_sha256_t  * const p_hash_context,
    uint8_t                             const * p_src,
    uint32_t                                    len);


/** @brief Function for finalizing the hash calculation.
 *
 *  @note Memory pointed to in hash digest must be allocated prior to this call.
 *
 * @param[in,out]   p_hash_context  Structure holding context information for
 *                                  the SHA-256 operation.
 * @param[in,out]   p_hash_digest   Pointer to the structure holding SHA-256
 *                                  hash digest. Data pointed to must be 32 bytes long.
 *
 * @retval  CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR    p_hash_context was NULL.
 * @retval  CRYS_HASH_USER_CONTEXT_CORRUPTED_ERROR          p_hash_context was corrupted.
 * @retval  CRYS_HASH_INVALID_RESULT_BUFFER_POINTER_ERROR   p_digest was NULL.
 */
CRYSError_t nrf_cc310_bl_hash_sha256_finalize(
    nrf_cc310_bl_hash_context_sha256_t    * const p_hash_context,
    nrf_cc310_bl_hash_digest_sha256_t     * const p_digest);

#ifdef __cplusplus
}
#endif

/** @} */

#endif // NRF_CC310_BL_HASH_SHA256_H__
