/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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

#ifndef OPTIGA_BACKEND_UTILS_H__
#define OPTIGA_BACKEND_UTILS_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "sdk_config.h"
#include "nordic_common.h"
#include "sdk_errors.h"

/** @brief Define for a integer tag in DER encoding. */
#define DER_TAG_INTEGER 0x02


/** @brief Max size of integer in DER encoding.
 *
 * @note This limit is for this implementation only, ASN.1 DER supports more
 */
#define DER_INTEGER_MAX_LEN 0x7F


/** @brief Define for overhead to encode a DER of two integers
 *
 * @details TAG + LENGTH needs 2 bytes if the highest bit of the integer is set
 *          we need an extra byte
 */
#define  DER_OVERHEAD ((2 + 1) * 2)


/**
 * @brief Decodes two ASN.1 integers to the R and S components of a ECC signature.
 *
 * @param[in]     p_asn1    Pointer to buffer containing the ASN.1 encoded R and S values.
 * @param[in]     asn1_len  Length of the asn1 buffer.
 * @param[out]    p_rs      Pointer to buffer where to write the R and S values
 * @param[in,out] p_rs_len  pointer to variable containing length of the rs buffer,
 *                          updated to actual length after the call.
 *
 * @returns NRF_SUCCESS on success, otherwise NRF_ERROR_CRYPTO_INTERNAL.
 */

ret_code_t asn1_to_ecdsa_rs(uint8_t const * p_asn1,
                            size_t          asn1_len,
                            uint8_t       * p_rs,
                            size_t        * p_rs_len);



/**
 * @brief Encodes the ECDSA signature components (r, s) in ASN.1 format.
 *
 * @param[in]   p_r             Pointer to buffer containing component r of the ECDSA signature.
 * @param[in]   r_len           Length of the r component of the ECDSA signature.
 * @param[in]   p_s             Pointer to buffer containing component s of the ECDSA signature.
 * @param[in]   s_len           Length of the s component of the ECDSA signature.
 * @param[out]  p_asn_sig       Pointer to buffer to hold the resulting ASN.1-encoded ECDSA signature.
 * @param[out]  p_asn_sig_len   Pointer to variable holding the length of the buffer for ASN.1-encoded
 *                              ECDSA signature. This will be updated to the actual size when the
 *                              function is called.
 *
 * @returns     True on success, otherwise false.
 */
bool ecdsa_rs_to_asn1(uint8_t const * p_r,
                      size_t          r_len,
                      uint8_t const * p_s,
                      size_t          s_len,
                      uint8_t       * p_asn_sig,
                      size_t        * p_asn_sig_len);


#endif // OPTIGA_BACKEND_UTILS_H__

