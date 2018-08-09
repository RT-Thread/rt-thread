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

#ifndef OCC_ECDSA_P256_H
#define OCC_ECDSA_P256_H

#include <stdint.h>


// ecdsa P-256 signature key pair generation
// pk[64]: the generated public key
// sk[32]: the private key
// returns 0 if sk is a legal secret key
int occ_ecdsa_p256_public_key(uint8_t pk[64], const uint8_t sk[32]);

// ecdsa P-256 signature generate
// sig[64]: the generated signature
// m[mlen]: the input message
// sk[32]:  the secret key
// ek[32]:  the session key
// returns 0 if ek is a valid session key
int occ_ecdsa_p256_sign(uint8_t sig[64], const uint8_t *m, uint32_t mlen, const uint8_t sk[32], const uint8_t ek[32]);

// ecdsa P-256 signature generate
// sig[64]: the generated signature
// hash[32]: SHA-256 hash of the input message
// sk[32]:  the secret key
// ek[32]:  the session key
// returns 0 if ek is a valid session key
int occ_ecdsa_p256_sign_hash(uint8_t sig[64], const uint8_t hash[32], const uint8_t sk[32], const uint8_t ek[32]);


// ecdsa P-256 signature verification
// sig[64]: the input signature
// m[mlen]: the input message
// pk[64]:  the public key
// returns 0 if signature is valid, -1 otherwise
int occ_ecdsa_p256_verify(const uint8_t sig[64], const uint8_t *m, uint32_t mlen, const uint8_t pk[64]);

// ecdsa P-256 signature verification
// sig[64]: the input signature
// hash[32]: SHA-256 hash of the input message
// pk[64]:  the public key
// returns 0 if signature is valid, -1 otherwise
int occ_ecdsa_p256_verify_hash(const uint8_t sig[64], const uint8_t hash[32], const uint8_t pk[64]);


#endif
