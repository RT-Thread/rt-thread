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
 * SHA-512 is part of the SHA-2 family that is a set of cryptographic hash
 * functions designed by the NSA. It is the successor of the SHA-1 algorithm.
 *
 * A fixed-sized message digest is computed from variable length input data.
 * The function is practically impossible to revert, and small changes in the
 * input message lead to major changes in the message digest.
 */

#ifndef OCC_SHA512_H
#define OCC_SHA512_H

#include <stdint.h>
#include <stddef.h>

/**
 * Length of SHA-512 hash.
 */
#define occ_sha512_BYTES (64)


/**@cond */
typedef struct {
    uint64_t h[8];
    uint8_t  padded[128];
    uint32_t length;
    size_t   bytes;
} occ_sha512_ctx;
/**@endcond */


/**@name Incremental SHA-512 generator.
 * 
 * This group of functions can be used to incrementally compute the SHA-512
 * hash for a given message.
 *
 * **Example**
 * @include occ_sha512_incremental.c
 */
/**@{*/
/**
 * SHA-512 initialization.
 *
 * The generator state @p ctx is initialized by this function.
 *
 * @param[out] ctx Generator state.
 */
void occ_sha512_init(occ_sha512_ctx *ctx);

/**
 * SHA-512 incremental data input.
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
 *         @c occ_sha512_init is required before this function can be called.
 */
void occ_sha512_update(occ_sha512_ctx *ctx,
                       const uint8_t *in, size_t in_len);

/**
 * SHA-512 output.
 *
 * The generator state @p ctx is updated to finalize the hash for the previously
 * processed message chunks. The hash is put into @p r.
 *
 * @param[out]    r   Generated hash value.
 * @param[in,out] ctx Generator state.
 *
 * @remark Initialization of the generator state @p ctx through
 *         @c occ_sha512_init is required before this function can be called.
 *
 * @remark After return, the generator state @p ctx must no longer be used with
 *         @c occ_sha512_update and @c occ_sha512_final unless it is
 *         reinitialized using @c occ_sha512_init.
 */
void occ_sha512_final(uint8_t r[occ_sha512_BYTES], occ_sha512_ctx *ctx);
/**@}*/

/**
 * SHA-512 hash.
 *
 * The SHA-512 hash of a given input message @p in is computed and put into @p r.
 *
 * **Example**
 * @include occ_sha512.c
 *
 * @param[out] r      Generated hash.
 * @param      in     Input data.
 * @param      in_len Length of @p in.
 */
void occ_sha512(uint8_t r[occ_sha512_BYTES],
                const uint8_t *in, size_t in_len);

#endif
