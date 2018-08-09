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
 * RSA is a number theoretic public-key encryption and signature algorithm.
 *
 * These functions support RSA encrytion and signatures with 1024 and 2048 bit
 * modulo and PKCS1 V1.5 padding.
 */

#ifndef OCC_RSA_H
#define OCC_RSA_H

#include <stdint.h>
#include "occ_rsa_key.h"


#include "nrf.h"
#if defined(NRF51)
#error "Oberon library currently doesn't support RSA for NRF51"
#endif

/**@name 1024 Bit RSA Functions.
 * 
 * This group of functions is used for 1024 bit RSA.
 */
/**@{*/
/**
 * 1024 bit RSA PKCS1 V1.5 encryption.
 *
 * The message @p m is encryted to a ciphertext returned in @p c.
 *
 * @param[out] c         The generated 128 byte cyphertext.
 * @param      m,mlen    The message to be encrypted. 0 <= mlen <= 117.
 * @param      seed,slen The random sedd to be used for the padding. slen >= 125 - mlen.
 * @param      pk        A valid 1024 bit RSA public key.
 *
 * @returns -1 If the message is too long (mlen > 117).
 * @returns -2 If the seed is too short (slen < 125 - mlen).
 * @returns 0  Otherwise.
 *
 * @remark The key @p pk should be initialized with @c occ_rsa1024_init_pub_key.
 * @remark The @p seed should consist of non-zero random bytes.
 * @remark @p c and @p m can point to the same address.
 */
int occ_rsa1024_pkcs1_v15_encrypt(uint8_t c[128], const uint8_t *m, int mlen, const uint8_t *seed, int slen, const occ_rsa1024_pub_key *pk);

/**
 * 1024 bit RSA PKCS1 V1.5 decryption.
 *
 * The ciphertext @p c is decryted to the message returned in @p m.
 *
 * @param[out] m,mlen  The decypted message. The buffer must be long enough to hold the meaasge.
 * @param      c       The 128 byte cyphertext to decrypt.
 * @param      k       A valid 1024 bit RSA secret key.

 * @returns -1 If decrytion failed.
 * @returns -2 If the output buffer is too short (mlen < length of message).
 * @returns  n If a message of length n was successfully decrypted. 
 *
 * @remark The key @p k should be initialized with @c occ_rsa1024_init_key.
 * @remark @p m and @p c can point to the same address.
 */
int occ_rsa1024_pkcs1_v15_decrypt(uint8_t *m, int mlen, const uint8_t c[128], const occ_rsa1024_key *k);

/**
 * 1024 bit RSA PKCS1 V1.5 decryption with CRT acceleration.
 *
 * The ciphertext @p c is decryted to the message returned in @p m.
 *
 * @param[out] m,mlen  The decypted message. The buffer must be long enough to hold the meaasge.
 * @param      c       The 128 byte cyphertext to decrypt.
 * @param      k       A valid 1024 bit RSA secret key with CRT coefficients.

 * @returns -1  If decrytion failed.
 * @returns -2  If the output buffer is too short (mlen < length of message).
 * @returns  n  If a message of length n was successfully decrypted. 
 *
 * @remark The key @p k should be initialized with @c occ_rsa1024_init_crt_key.
 * @remark @p m and @p c can point to the same address.
 */
int occ_rsa1024_pkcs1_v15_crt_decrypt(uint8_t *m, int mlen, const uint8_t c[128], const occ_rsa1024_crt_key *k);

/**
 * 1024 bit RSA PKCS1 V1.5 SHA-256 sign.
 *
 * The message @p m is signed and the signature returned in @p s.
 *
 * @param[out] s       The generated 128 byte signature.
 * @param      m,mlen  The message to be signed.
 * @param      k       A valid 1024 bit RSA secret key.

 * @returns 0
 *
 * @remark The key @p k should be initialized with @c occ_rsa1024_init_key.
 * @remark @p s and @p m can point to the same address.
 */
int occ_rsa1024_pkcs1_v15_sha256_sign(uint8_t s[128], const uint8_t *m, int mlen, const occ_rsa1024_key *k);

/**
 * 1024 bit RSA PKCS1 V1.5 SHA-256 sign with CRT acceleration.
 *
 * The message @p m is signed and the signature returned in @p s.
 *
 * @param[out] s       The generated 128 byte signature.
 * @param      m,mlen  The message to be signed.
 * @param      k       A valid 1024 bit RSA secret key with CRT coefficients.

 * @returns 0
 *
 * @remark The key @p k should be initialized with @c occ_rsa1024_init_crt_key.
 * @remark @p s and @p m can point to the same address.
 */
int occ_rsa1024_pkcs1_v15_sha256_crt_sign(uint8_t s[128], const uint8_t *m, int mlen, const occ_rsa1024_crt_key *k);

/**
 * 1024 bit RSA PKCS1 V1.5 SHA-256 signature verify.
 *
 * The signature @p s is verified for a correct signature of message @p m.
 *
 * @param s      The 128 byte signature.
 * @param m,mlen The signed message.
 * @param pk     A valid 1024 bit RSA public key.
 *
 * @returns 0  If the signature is successfully verified.
 * @returns -1 If verification failed.
 *
 * @remark The key @p pk should be initialized with @c occ_rsa1024_init_pub_key.
 */
int occ_rsa1024_pkcs1_v15_sha256_verify(const uint8_t s[128], const uint8_t *m, int mlen, const occ_rsa1024_pub_key *pk);
/**@}*/


/**@name 2048 Bit RSA Functions.
 * 
 * This group of functions is used for 2048 bit RSA.
 */
/**@{*/
/**
 * 2048 bit RSA PKCS1 V1.5 encryption.
 *
 * The message @p m is encryted to a ciphertext returned in @p c.
 *
 * @param[out] c         The generated 256 byte cyphertext.
 * @param      m,mlen    The message to be encrypted. 0 <= mlen <= 245.
 * @param      seed,slen The random sedd to be used for the padding. slen >= 253 - mlen.
 * @param      pk        A valid 2048 bit RSA public key.
 *
 * @returns -1 If the message is too long (mlen > 245).
 * @returns -2 If the seed is too short (slen < 253 - mlen).
 * @returns 0  Otherwise.
 *
 * @remark The key @p pk should be initialized with @c occ_rsa2048_init_pub_key.
 * @remark The @p seed should consist of non-zero random bytes.
 * @remark @p c and @p m can point to the same address.
 */
int occ_rsa2048_pkcs1_v15_encrypt(uint8_t c[256], const uint8_t *m, int mlen, const uint8_t *seed, int slen, const occ_rsa2048_pub_key *pk);

/**
 * 2048 bit RSA PKCS1 V1.5 decryption.
 *
 * The ciphertext @p c is decryted to the message returned in @p m.
 *
 * @param[out] m,mlen  The decypted message. The buffer must be long enough to hold the meaasge.
 * @param      c       The 256 byte cyphertext to decrypt.
 * @param      k       A valid 2048 bit RSA secret key.

 * @returns -1 If decrytion failed.
 * @returns -2 If the output buffer is too short (mlen < length of message).
 * @returns n  If a message of length n was successfully decrypted. 
 *
 * @remark The key @p k should be initialized with @c occ_rsa2048_init_key.
 * @remark @p m and @p c can point to the same address.
 */
int occ_rsa2048_pkcs1_v15_decrypt(uint8_t *m, int mlen, const uint8_t c[256], const occ_rsa2048_key *k);

/**
 * 2048 bit RSA PKCS1 V1.5 decryption with CRT acceleration.
 *
 * The ciphertext @p c is decryted to the message returned in @p m.
 *
 * @param[out] m,mlen  The decypted message. The buffer must be long enough to hold the meaasge.
 * @param      c       The 256 byte cyphertext to decrypt.
 * @param      k       A valid 2048 bit RSA secret key with CRT coefficients.

 * @returns -1  If decrytion failed.
 * @returns -2  If the output buffer is too short (mlen < length of message).
 * @returns  n  If a message of length n was successfully decrypted. 
 *
 * @remark The key @p k should be initialized with @c occ_rsa2048_init_crt_key.
 * @remark @p m and @p c can point to the same address.
 */
int occ_rsa2048_pkcs1_v15_crt_decrypt(uint8_t *m, int mlen, const uint8_t c[256], const occ_rsa2048_crt_key *k);

/**
 * 2048 bit RSA PKCS1 V1.5 SHA-256 sign.
 *
 * The message @p m is signed and the signature returned in @p s.
 *
 * @param[out] s       The generated 256 byte signature.
 * @param      m,mlen  The message to be signed.
 * @param      k       A valid 2048 bit RSA secret key.

 * @returns 0
 *
 * @remark The key @p k should be initialized with @c occ_rsa2048_init_key.
 * @remark @p s and @p m can point to the same address.
 */
int occ_rsa2048_pkcs1_v15_sha256_sign(uint8_t s[256], const uint8_t *m, int mlen, const occ_rsa2048_key *k);

/**
 * 2048 bit RSA PKCS1 V1.5 SHA-256 sign with CRT acceleration.
 *
 * The message @p m is signed and the signature returned in @p s.
 *
 * @param[out] s       The generated 256 byte signature.
 * @param      m,mlen  The message to be signed.
 * @param      k       A valid 2048 bit RSA secret key with CRT coefficients.

 * @returns 0
 *
 * @remark The key @p k should be initialized with @c occ_rsa2048_init_crt_key.
 * @remark @p s and @p m can point to the same address.
 */
int occ_rsa2048_pkcs1_v15_sha256_crt_sign(uint8_t s[256], const uint8_t *m, int mlen, const occ_rsa2048_crt_key *k);

/**
 * 2048 bit RSA PKCS1 V1.5 SHA-256 signature verify.
 *
 * The signature @p s is verified for a correct signature of message @p m.
 *
 * @param s      The 256 byte signature.
 * @param m,mlen The signed message.
 * @param pk     A valid 2048 bit RSA public key.
 *
 * @returns 0  If the signature is successfully verified.
 * @returns -1 If verification failed.
 *
 * @remark The key @p pk should be initialized with @c occ_rsa2048_init_pub_key.
 */
int occ_rsa2048_pkcs1_v15_sha256_verify(const uint8_t s[256], const uint8_t *m, int mlen, const occ_rsa2048_pub_key *pk);
/**@}*/


#endif
