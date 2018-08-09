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
#ifndef NRF_CC310_BL_ECDSA_VERIFY_SECP256R1_H__
#define NRF_CC310_BL_ECDSA_VERIFY_SECP256R1_H__

/**@file
 *
 * @defgroup nrf_cc310_bl_ecdsa_verify_secp256r1 nrf_cc310_bl ECDSA verify secp256r1 types
 * @ingroup nrf_cc310_bl
 * @brief  Type definitions and APIs for nrf_cc310_bl ECDSA verify using curve secp256r1.
 * @{
 */

#include <stdint.h>
#include "crys_error.h"
#include "nrf_cc310_bl_ecdsa_verify_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Structure holding the secp256r1 public key represented by X,Y coordinates.
*/
typedef struct
{
    uint8_t x[32]; //!< Public key X coordinate in big-endian format.
    uint8_t y[32]; //!< Public key Y coordinate in big-endian format.
} nrf_cc310_bl_ecc_public_key_secp256r1_t;


/**@brief Structure holding the secp256r1 signature represented by R,S values.
*/
typedef struct
{
    uint8_t r[32]; //!< Signature R part in big-endian format.
    uint8_t s[32]; //!< Signature S part in big-endian format.
} nrf_cc310_bl_ecc_signature_secp256r1_t;


/**@brief Structure holding memory required for allocation of CC310 ECDSA verify context
 *        using curve secp256r1.
 */
typedef struct
{
    uint32_t    init_val;
    uint8_t     context_buffer[NRF_CC310_BL_ECDSA_VERIFY_CONTEXT_SIZE_SECP256R1];
}  nrf_cc310_bl_ecdsa_verify_context_secp256r1_t;


/**@brief Function for initializing the context information for an ECDSA verify operation.
 *
 * @note    The memory that holds the context object must be allocated prior to this call.
 *
 * @param[in,out]   p_context       Pointer to the structure holding context information
 *                                  for the ECDSA verify operation.
 * @param[in]       p_public_key    Pointer to the structure holding the public key for
 *                                  the ECDSA verify operation.
 *
 * @retval CRYS_ECDSA_VERIFY_INVALID_USER_CONTEXT_PTR_ERROR        p_context was NULL.
 * @retval CRYS_ECDSA_VERIFY_SIGNER_PUBL_KEY_VALIDATION_TAG_ERROR  p_public_key was NULL.
 */
CRYSError_t nrf_cc310_bl_ecdsa_verify_init_secp256r1(
    nrf_cc310_bl_ecdsa_verify_context_secp256r1_t  * const p_context,
    nrf_cc310_bl_ecc_public_key_secp256r1_t  const * const p_public_key);


/**@brief Function for executing an ECDSA verify operation using secp256r1 with hash input.
 *
 * @note    The ECDSA verify context structure must be initialized prior to this call using
 *          @ref nrf_cc310_bl_ecdsa_verify_init_secp256r1.
 *
 * @param[in,out]   p_context   Pointer to the structure holding context information
 *                              for the ECDSA verify operation.
 * @param[in]       p_signature Pointer to the structure holding the signature to use for
 *                              the ECDSA verify operation.
 * @param[in]       p_hash      Pointer to the hash to use in the ECDSA verify operation.
 * @param[in]       hash_len    Length of the hash to verify.
 *
 * @retval CRYS_OK Signature was successfully verified.
 * @retval CRYS_ECDSA_VERIFY_INVALID_USER_CONTEXT_PTR_ERROR     p_context was NULL.
 * @retval CRYS_ECDSA_VERIFY_USER_CONTEXT_VALIDATION_TAG_ERROR  p_context was not initialized.
 * @retval CRYS_ECDSA_VERIFY_INVALID_SIGNATURE_IN_PTR_ERROR     p_signature was NULL.
 * @retval CRYS_ECDSA_VERIFY_INVALID_MESSAGE_DATA_IN_PTR_ERROR  p_hash was NULL.
 * @retval CRYS_ECDSA_VERIFY_INVALID_MESSAGE_DATA_IN_SIZE_ERROR hash_len was invalid.
 * @retval CRYS_ECDSA_VERIFY_INCONSISTENT_VERIFY_ERROR          Signature verification failed.
 */
CRYSError_t nrf_cc310_bl_ecdsa_verify_hash_secp256r1(
    nrf_cc310_bl_ecdsa_verify_context_secp256r1_t * const p_context,
    nrf_cc310_bl_ecc_signature_secp256r1_t  const * const p_signature,
    uint8_t                                 const * const p_hash,
    uint32_t                                              hash_len);

/**@brief Function for executing an ECDSA verify operation using secp256r1 with
 *                                  hash input in integrated form.
 *
 * @note This will run initialization of ECDSA context and run ECDSA verify in a single step.
 *
 * @param[in,out]   p_context       Pointer to the structure holding context information for
 *                                  the ECDSA verify operation.
 * @param[in]       p_public_key    Pointer to the structure holding the public key for
 *                                  the ECDSA verify operation.
 * @param[in]       p_signature     Pointer to the structure holding the signature to use
 *                                  for the ECDSA verify operation.
 * @param[in]       p_hash          Pointer to the hash to use in the ECDSA verify operation.
 * @param[in]       hash_len        Length of the hash to verify.
 *
 * @retval CRYS_OK Signature was successfully verified.
 * @retval CRYS_ECDSA_VERIFY_INVALID_USER_CONTEXT_PTR_ERROR     p_context was NULL.
 * @retval CRYS_ECDSA_VERIFY_USER_CONTEXT_VALIDATION_TAG_ERROR  p_context was not initialized.
 * @retval CRYS_ECDSA_VERIFY_SIGNER_PUBL_KEY_VALIDATION_TAG_ERROR
 *         p_public_key was NULL.
 * @retval CRYS_ECDSA_VERIFY_INVALID_SIGNATURE_IN_PTR_ERROR     p_signature was NULL.
 * @retval CRYS_ECDSA_VERIFY_INVALID_MESSAGE_DATA_IN_PTR_ERROR  p_hash was NULL.
 * @retval CRYS_ECDSA_VERIFY_INVALID_MESSAGE_DATA_IN_SIZE_ERROR hash_len was invalid.
 * @retval CRYS_ECDSA_VERIFY_INCONSISTENT_VERIFY_ERROR          Signature verification failed.
 */
CRYSError_t nrf_cc310_bl_ecdsa_verify_secp256r1(
    nrf_cc310_bl_ecdsa_verify_context_secp256r1_t   * const p_context,
    nrf_cc310_bl_ecc_public_key_secp256r1_t   const * const p_public_key,
    nrf_cc310_bl_ecc_signature_secp256r1_t    const * const p_signature,
    uint8_t                                   const * const p_hash,
    uint32_t                                                hash_len);

#ifdef __cplusplus
}
#endif

/** @} */

#endif // NRF_CC310_BL_ECDSA_VERIFY_SECP256R1_H__
