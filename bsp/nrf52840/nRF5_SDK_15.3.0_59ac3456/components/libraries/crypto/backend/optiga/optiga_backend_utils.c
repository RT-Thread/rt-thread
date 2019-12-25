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


#include <string.h>
#include "optiga_backend_utils.h"
#include "nrf_crypto_error.h"

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
                            size_t        * p_rs_len)
{

    uint8_t const * p_cur = p_asn1;
    uint8_t const * p_end = p_asn1 + asn1_len; // Points to first invalid mem-location
    uint8_t         r_len;
    uint8_t         s_len;

    if (p_asn1 == NULL || p_rs == NULL || p_rs_len == NULL)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    if (asn1_len == 0 || *p_rs_len == 0)
    {
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    if (*p_cur != DER_TAG_INTEGER)
    {
        // Wrong tag type
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    if ((p_cur + 2) >= p_end)
    {
        // Prevented out-of-bounds read
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    // Move to length value
    p_cur++;
    r_len = *p_cur;

    if (r_len > DER_INTEGER_MAX_LEN)
    {
        // Unsupported length
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    // Move to first data value
    p_cur++;

    // Check for stuffing bits
    if (*p_cur == 0x00)
    {
        p_cur++;
        r_len--;
    }

    // Check for out-of-bounds read
    if ((p_cur + r_len) >= p_end)
    {
        // prevented out-of-bounds read
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    // Check for out-of-bounds write
    if ((p_rs + r_len) > (p_rs + *p_rs_len))
    {
        // prevented out-of-bounds write
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    // Copy R component to output
    memcpy(p_rs, p_cur, r_len);

    // Move to next tag
    p_cur += r_len;

    if (*p_cur != DER_TAG_INTEGER)
    {
        // Wrong tag type
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    if ((p_cur + 2) >= p_end)
    {
        // Prevented out-of-bounds read
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    p_cur++;
    s_len = *p_cur;

    if (s_len > DER_INTEGER_MAX_LEN)
    {
        // Unsupported length
        return NRF_ERROR_CRYPTO_INTERNAL;
    }
    p_cur++;

    if (*p_cur == 0x00)
    {
        p_cur++;
        s_len--;
    }

    // Check for out-of-bounds read
    if ((p_cur + s_len) > p_end)
    {
        // prevented out-of-bounds read
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    // Check for out-of-bounds write
    if ((p_rs + r_len + s_len) > (p_rs + *p_rs_len))
    {
        // Prevented out-of-bounds write
        return NRF_ERROR_CRYPTO_INTERNAL;
    }

    memcpy(p_rs + r_len, p_cur, s_len);

    *p_rs_len = r_len + s_len;

    return NRF_SUCCESS;
}


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
                      size_t        * p_asn_sig_len)
{
    size_t index = 0;
    // NULL checks
    if (p_r == NULL || p_s == NULL || p_asn_sig_len == NULL)
    {
        return false;
    }

    if (r_len == 0 || r_len > DER_INTEGER_MAX_LEN || s_len == 0 || s_len > DER_INTEGER_MAX_LEN)
    {
        return false;
    }

    if (*p_asn_sig_len < (r_len + s_len + DER_OVERHEAD))
    {
    	// Not enough space in output buffer
    	return false;
    }

    // R component
    // DER TAG INTEGER
    p_asn_sig[index] = DER_TAG_INTEGER;
    index++;

    // Set length
    p_asn_sig[index] = r_len;

    // check if extra byte needed
    if (p_r[0] & 0x80)
    {
        // Update length value
        p_asn_sig[index] += 1;
        index++;
        // Insert zero byte for padding
        p_asn_sig[index] =  0;
    }

    index++;

    memcpy(&p_asn_sig[index], p_r, r_len);
    index += r_len;

    // S component
    // DER TAG INTEGER
    p_asn_sig[index] = DER_TAG_INTEGER;
    index++;
    // Set length
    p_asn_sig[index] = s_len;

    if (p_s[0] & 0x80)
    {
        // Update length value
        p_asn_sig[index] += 1;
        index++;
        // Insert zero byte for padding
        p_asn_sig[index] =  0;
    }

    index++;

    memcpy(&p_asn_sig[index], p_s, s_len);
    index += s_len;

    // Return total length of ASN.1-encoded data structure
    *p_asn_sig_len = index;
    return true;
}
