/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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

/**@file
 * HMAC-SHA256 is an algorithm for message authentication using the
 * cryptographic hash function SHA256 and a reusable secret key. Users in
 * possession of the key can verify the integrity and authenticity of the
 * message.
 *
 * @see [RFC 2104 - HMAC: Keyed-Hashing for Message Authentication](http://tools.ietf.org/html/rfc2104)
 */
 
// REPLACEMENT

#ifndef OCC_HMAC_SHA256_H
#define OCC_HMAC_SHA256_H

#include <stdint.h>
#include <stddef.h>
#include "include/occ_sha256.h"


/**
 * Maximum key length.
 */
#define occ_hmac_sha256_KEY_BYTES_MAX (64)

/**
 * Length of the authenticator.
 */
#define occ_hmac_sha256_BYTES (32)


/**@cond */
typedef struct
{
    occ_sha256_ctx hash_ctx;
    uint8_t        ikey[occ_hmac_sha256_KEY_BYTES_MAX];
    uint8_t        okey[occ_hmac_sha256_KEY_BYTES_MAX];
    uint8_t        key[occ_hmac_sha256_KEY_BYTES_MAX];
} occ_hmac_sha256_ctx;
/**@endcond */


/**@name Incremental HMAC-SHA256 generator.
 * 
 * This group of functions can be used to incrementally compute HMAC-SHA256
 * for a given message.
 */
/**@{*/


/**
 * HMAC-SHA256 initialization.
 *
 * The generator state @p ctx is initialized by this function.
 *
 * @param[out] ctx     Generator state.
 * @param      key     HMAC key.
 * @param      key_len Length of @p key.
 */
void occ_hmac_sha256_init(occ_hmac_sha256_ctx * ctx,
                          const uint8_t* key, size_t key_len);

/**
 * HMAC-SHA256 incremental data input.
 *
 * The generator state @p ctx is updated to hash a message chunk @p in.
 *
 * This function can be called repeatedly until the whole message is processed.
 *
 * @param[in,out] ctx    Generator state.
 * @param         in     Input data.
 * @param         in_len Length of @p in.
 *
 * @remark Initialization of the generator state @p ctx through
 *         @c occ_hmac_sha256_init is required before this function can be called.
 */
void occ_hmac_sha256_update(occ_hmac_sha256_ctx * ctx,
                            const uint8_t* in, size_t in_len);

/**
 * HMAC-SHA256 output.
 *
 * The generator state @p ctx is updated to finalize the HMAC calculation.
 * The HMAC digest is put into @p r.
 *
 * @param[out]    r   Generated HMAC digest.
 * @param[in,out] ctx Generator state.
 *
 * @remark Initialization of the generator state @p ctx through
 *         @c occ_hmac_sha256_init is required before this function can be called.
 *
 * @remark After return, the generator state @p ctx must no longer be used with
 *         @c occ_hmac_sha256_update and @c occ_hmac_sha256_final unless it is
 *         reinitialized using @c occ_hmac_sha256_init.
 */
void occ_hmac_sha256_final(uint8_t r[occ_hmac_sha256_BYTES],
                           occ_hmac_sha256_ctx * ctx);
/**@}*/


/**
 * HMAC-SHA256 algorithm.
 *
 * The input message @p in is authenticated using the key @p k. The computed
 * authenticator is put into @p r. To verify the authenticator, the recipient
 * needs to recompute the HMAC authenticator and can then compare it with the
 * received authenticator.
 *
 * **Example**
 * @include occ_hmac_sha256.c
 *
 * @param[out] r       HMAC output.
 * @param      key     HMAC key.
 * @param      key_len Length of @p key. 0 <= @p key_len <= @c occ_hmac_sha256_KEY_BYTES_MAX.
 * @param      in      Input data.
 * @param      in_len  Length of @p in.
 */
void occ_hmac_sha256(uint8_t r[occ_hmac_sha256_BYTES],
                     const uint8_t* key, size_t key_len,
                     const uint8_t* in, size_t in_len);

#endif
