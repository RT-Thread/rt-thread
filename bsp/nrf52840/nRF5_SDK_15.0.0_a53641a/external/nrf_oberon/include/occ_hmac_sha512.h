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
 * HMAC-SHA512 is an algorithm for message authentication using the
 * cryptographic hash function SHA512 and a reusable secret key. Users in
 * possession of the key can verify the integrity and authenticity of the
 * message.
 *
 * @see [RFC 2104 - HMAC: Keyed-Hashing for Message Authentication](http://tools.ietf.org/html/rfc2104)
 */
 
#ifndef OCC_HMAC_SHA512_H
#define OCC_HMAC_SHA512_H

#include <stdint.h>
#include <stddef.h>
#include "include/occ_sha512.h"


/**
 * Maximum key length.
 */
#define occ_hmac_sha512_KEY_BYTES_MAX (128)

/**
 * Length of the authenticator.
 */
#define occ_hmac_sha512_BYTES (64)


/**@cond */
typedef struct
{
    occ_sha512_ctx hash_ctx;
    uint8_t        ikey[occ_hmac_sha512_KEY_BYTES_MAX];
    uint8_t        okey[occ_hmac_sha512_KEY_BYTES_MAX];
    uint8_t        key[occ_hmac_sha512_KEY_BYTES_MAX];
} occ_hmac_sha512_ctx;
/**@endcond */

/**@name Incremental HMAC-SHA512 generator.
 * 
 * This group of functions can be used to incrementally compute HMAC-SHA512
 * for a given message.
 */
/**@{*/


/**
 * HMAC-SHA512 initialization.
 *
 * The generator state @p ctx is initialized by this function.
 *
 * @param[out] ctx     Generator state.
 * @param      key     HMAC key.
 * @param      key_len Length of @p key.
 */
void occ_hmac_sha512_init(occ_hmac_sha512_ctx * ctx,
                          const uint8_t* key, size_t key_len);

/**
 * HMAC-SHA512 incremental data input.
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
 *         @c occ_hmac_sha512_init is required before this function can be called.
 */
void occ_hmac_sha512_update(occ_hmac_sha512_ctx * ctx,
                            const uint8_t* in, size_t in_len);

/**
 * HMAC-SHA512 output.
 *
 * The generator state @p ctx is updated to finalize the HMAC calculation.
 * The HMAC digest is put into @p r.
 *
 * @param[out]    r   Generated HMAC digest.
 * @param[in,out] ctx Generator state.
 *
 * @remark Initialization of the generator state @p ctx through
 *         @c occ_hmac_sha512_init is required before this function can be called.
 *
 * @remark After return, the generator state @p ctx must no longer be used with
 *         @c occ_hmac_sha512_update and @c occ_hmac_sha512_final unless it is
 *         reinitialized using @c occ_hmac_sha512_init.
 */
void occ_hmac_sha512_final(uint8_t r[occ_hmac_sha512_BYTES],
                           occ_hmac_sha512_ctx * ctx);
/**@}*/


/**
 * HMAC-SHA512 algorithm.
 *
 * The input message @p in is authenticated using the key @p k. The computed
 * authenticator is put into @p r. To verify the authenticator, the recipient
 * needs to recompute the HMAC authenticator and can then compare it with the
 * received authenticator.
 *
 * **Example**
 * @include occ_hmac_sha512.c
 *
 * @param[out] r       HMAC output.
 * @param      key     HMAC key.
 * @param      key_len Length of @p key. 0 <= @p key_len <= @c occ_hmac_sha512_KEY_BYTES_MAX.
 * @param      in      Input data.
 * @param      in_len  Length of @p in.
 */
void occ_hmac_sha512(uint8_t r[occ_hmac_sha512_BYTES],
                     const uint8_t* key, size_t key_len,
                     const uint8_t* in, size_t in_len);

#endif
