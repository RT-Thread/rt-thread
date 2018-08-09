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

/*!
 * @brief ChaCha20 is a stream cipher developed by Daniel J. Bernstein based on the 20-round cipher Salsa20/20.
 */
/**@file
 * A 256-bit key is expanded into 2^64 randomly accessible streams, each
 * containing 2^64 randomly accessible 64-byte (512 bits) blocks.
 *
 * The changes from Salsa20/20 to ChaCha20 are designed to improve diffusion per
 * round, conjecturally increasing resistance to cryptanalysis, while
 * preserving - and often improving - time per round.
 *
 * @see [RFC 7539 - ChaCha20 and Poly1305 for IETF Protocols](http://tools.ietf.org/html/rfc7539)
 * @see [The ChaCha family of stream ciphers](http://cr.yp.to/chacha.html)
 */

#ifndef OCC_CHACHA20_H
#define OCC_CHACHA20_H

#include <stdint.h>
#include <stddef.h>


/**
 * Length of the encryption key.
 */
#define occ_chacha20_KEY_BYTES (32)

/**
 * Maximum length of the nonce.
 */
#define occ_chacha20_NONCE_BYTES_MAX (12)


/**
 * ChaCha20 cipher stream generator.
 * 
 * The encryption key @p k, the nonce @p n and the initial block counter
 * @p count are used to generate a pseudo random cipher stream.
 *
 * Possible applications include key generation and random number generation.
 *
 * **Example**
 * @include occ_chacha20_stream.c
 * 
 * @param[out] c     Generated cipher stream.
 * @param      c_len Length of @p c.
 * @param      n     Nonce.
 * @param      n_len Nonce length. 0 <= @p n_len <= @c occ_chacha20_NONCE_BYTES_MAX.
 * @param      k     Encryption key.
 * @param      count Initial block counter.
 *
 * @remark When reusing an encryption key @p k, a different nonce @p n or
 *         initial block counter @p count must be used.
 *
 * @remark This function is equivalent to @c chacha20_stream_xor with a
 *         message @p m consisting of @p c_len zeroes.
 */
void occ_chacha20_stream(uint8_t *c, size_t c_len,
                         const uint8_t *n, size_t n_len,
                         const uint8_t k[occ_chacha20_KEY_BYTES],
                         uint32_t count);

/**
 * ChaCha20 cipher stream encoder.
 *
 * The message @p m is encrypted by applying the XOR operation with a pseudo
 * random cipher stream derived from the encryption key @p k, the nonce @p n and
 * the initial block counter @p count.
 *
 * Calling the function a second time with the generated ciphertext as input
 * message @p m decrypts it back to the original message.
 *
 * **Example**
 * @include occ_chacha20_stream_xor.c
 *
 * @param[out] c     Generated ciphertext. Same length as input message.
 * @param      m     Input message.
 * @param      m_len Length of @p c and @p m.
 * @param      n     Nonce.
 * @param      n_len Nonce length. 0 <= @p n_len <= @c occ_chacha20_NONCE_BYTES_MAX.
 * @param      k     Encryption key.
 * @param      count Initial block counter.
 * 
 * @remark @p c and @p m can point to the same address.
 *
 * @remark When reusing an encryption key @p k for a different message @p m, a
 *         different nonce @p n or initial block counter @p count must be used.
 */
void occ_chacha20_stream_xor(uint8_t *c,
                             const uint8_t *m, size_t m_len,
                             const uint8_t *n, size_t n_len,
                             const uint8_t k[occ_chacha20_KEY_BYTES],
                             uint32_t count);

#endif
