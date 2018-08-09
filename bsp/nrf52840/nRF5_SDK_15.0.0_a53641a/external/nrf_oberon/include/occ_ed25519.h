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
 * Ed25519 is a specific implementation of EdDSA, a digital signature scheme.
 * EdDSA is based on Twisted Edwards curves and is designed to be faster than
 * existing digital signature schemes without sacrificing security. It was
 * developed by Daniel J. Bernstein, et al. Ed25519 is intended to provide
 * attack resistance comparable to quality 128-bit symmetric ciphers.
 * 
 * @see [Ed25519: high-speed high-security signatures](https://ed25519.cr.yp.to)
 */

#ifndef OCC_ED25519_H
#define OCC_ED25519_H

#include <stdint.h>
#include <stddef.h>


/**
 * Length of a public key.
 */
#define occ_ed25519_PUBLIC_KEY_BYTES (32)

/**
 * Length of a secret key.
 */
#define occ_ed25519_SECRET_KEY_BYTES (32)

/**
 * Length of a signature.
 */
#define occ_ed25519_BYTES (64)


/**
 * Ed25519 signature key pair generation.
 *
 * Given a secret key `sk`, the corresponding public key is computed and put
 * into `pk`. The key pair can then be used to sign and verify message signatures.
 *
 * **Example**
 * @include occ_ed25519_public_key.c
 *
 * @param[out] pk Generated public key.
 * @param      sk Secret key. Must be prefilled with random data.
 */
void occ_ed25519_public_key(uint8_t pk[occ_ed25519_PUBLIC_KEY_BYTES],
                            const uint8_t sk[occ_ed25519_SECRET_KEY_BYTES]);

/**
 * Ed25519 signature generate.
 *
 * The message @p m is signed using the secret key @p sk and the corresponding
 * public key @p pk. The signature is put into @p sig.
 *
 * **Example**
 * @include occ_ed25519_sign.c
 *
 * @param[out] sig   Generated signature.
 * @param      m     Input message.
 * @param      m_len Length of @p m.
 * @param      sk    Secret key.
 * @param      pk    Public key.
 */
void occ_ed25519_sign(uint8_t sig[occ_ed25519_BYTES],
                      const uint8_t *m, size_t m_len,
                      const uint8_t sk[occ_ed25519_SECRET_KEY_BYTES],
                      const uint8_t pk[occ_ed25519_PUBLIC_KEY_BYTES]);

/**
 * Ed25519 signature verification.
 * 
 * The signature @p sig of the input message @p m is verified using the signer's
 * public key @p pk.
 *
 * **Example**
 * @include occ_ed25519_verify.c
 * 
 * @param sig   Input signature.
 * @param m     Input message.
 * @param m_len Length of @p m.
 * @param pk    Signer's public key.
 *
 * @returns 0 If signature OK.
 * @returns -1 Otherwise.
 */
int occ_ed25519_verify(const uint8_t sig[occ_ed25519_BYTES],
                       const uint8_t *m, size_t m_len,
                       const uint8_t pk[occ_ed25519_PUBLIC_KEY_BYTES]);

#endif
