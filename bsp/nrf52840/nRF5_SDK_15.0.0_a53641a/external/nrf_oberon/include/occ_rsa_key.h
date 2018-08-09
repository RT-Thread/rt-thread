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
 * These functions suport the setup of 1024 and 4069 RSA secret and public keys.
 */

#ifndef OCC_RSA_KEY_H
#define OCC_RSA_KEY_H

#include <stdint.h>

#include "nrf.h"
#if defined(NRF51)
#error "Oberon library currently doesn't support RSA for NRF51"
#endif

/**
 * The Public RSA Exponent.
 */
#define PUB_EXP 65537  // 2^16 + 1


/**@name 1024 Bit RSA Keys.
 * 
 * This group of keys is used for 1024 bit RSA.
 */
/**@{*/
/**
 * 1024 bit RSA public key
 */
typedef struct {
	uint32_t n[32];
	// e = 65537
} occ_rsa1024_pub_key;

/**
 * 1024 bit RSA secret key
 */
typedef struct {
	uint32_t n[32];
	uint32_t d[32];  // x^(e*d) mod n == x
} occ_rsa1024_key;

/**
 * 1024 bit RSA secret key with CRT coefficients
 */
typedef struct {
	uint32_t n[32];
	uint32_t p[16], q[16];   // primes, p*q = n
	uint32_t dp[16], dq[16]; // d mod (p-1), d mod (q-1)
	uint32_t qinv[16];       // 1/q mod p
} occ_rsa1024_crt_key;
/**@}*/


/**@name 2048 Bit RSA Keys.
 * 
 * This group of keys is used for 2048 bit RSA.
 */
/**@{*/
/**
 * 2048 bit RSA public key
 */
typedef struct {
	uint32_t n[64];
	// e = 65537
} occ_rsa2048_pub_key;

/**
 * 2048 bit RSA secret key
 */
typedef struct {
	uint32_t n[64];
	uint32_t d[64];  // x^(e*d) mod n == x
} occ_rsa2048_key;

/**
 * 2048 bit RSA secret key with CRT coefficients
 */
typedef struct {
	uint32_t n[64];
	uint32_t p[32], q[32];   // primes, p*q = n
	uint32_t dp[32], dq[32]; // d mod (p-1), d mod (q-1)
	uint32_t qinv[32];       // 1/q mod p
} occ_rsa2048_crt_key;
/**@}*/

/**@name 1024 Bit RSA key setup.
 * 
 * This group of functions is used for 1024 bit RSA key setup.
 */
/**@{*/
/**
 * 1024 bit RSA public key setup.
 *
 * @param[out] k       The initialzed public key.
 * @param      n,nlen  The RSA modulus. Must be exactly 1024 bits.
 *
 * @retruns -1 If the input length is not correct
 * @returns 0  Otherwise.

 * @remark The public exponent is fixed at 65537.
 */
int occ_rsa1024_init_pub_key (occ_rsa1024_pub_key *k,
						      const uint8_t *n, int nlen);

/**
 * 1024 bit RSA secret key setup.
 *
 * @param[out] k       The initialzed public key.
 * @param      n,nlen  The RSA modulus. Must be exactly 1024 bits.
 * @param      d,dlen  The secret exponent. Must be <= 1024 bits.
 *
 * @retruns -1 If the input length is not correct
 * @returns 0  Otherwise.
 */
int occ_rsa1024_init_key (occ_rsa1024_key *k,
					      const uint8_t *n, int nlen,
					      const uint8_t *d, int dlen);

/**
 * 1024 bit RSA secret key setup with CRT coefficients.
 *
 * @param[out] k          The initialzed secret key.
 * @param      p,plen     The 1. RSA prime. Must be exactly 512 bits.
 * @param      q,qlen     The 2. RSA prime. Must be exactly 512 bits.
 * @param      dp,dplen   The 1. CRT exponent. dp = d mod (p-1).
 * @param      dq,dqlen   The 2. CRT exponent. dq = d mod (q-1).
 * @param      qinv,qilen The CRT coefficient. qinv = 1/q mod p.
 *
 * @retruns -1 If the input length is not correct
 * @returns 0  Otherwise.
 */
int occ_rsa1024_init_crt_key (occ_rsa1024_crt_key *k,
						      const uint8_t *p,    int plen,
						      const uint8_t *q,    int qlen,
						      const uint8_t *dp,   int dplen,
						      const uint8_t *dq,   int dqlen,
						      const uint8_t *qinv, int qilen);
/**@}*/

/**@name 2048 Bit RSA key setup.
 * 
 * This group of functions is used for 2048 bit RSA key setup.
 */
/**@{*/
/**
 * 2048 bit RSA public key setup.
 *
 * @param[out] k       The initialzed public key.
 * @param      n,nlen  The RSA modulus. Must be exactly 2048 bits.
 *
 * @retruns -1 If the input length is not correct
 * @returns 0  Otherwise.

 * @remark The public exponent is fixed at 65537.
 */
int occ_rsa2048_init_pub_key (occ_rsa2048_pub_key *k,
						      const uint8_t *n, int nlen);

/**
 * 2048 bit RSA secret key setup.
 *
 * @param[out] k       The initialzed public key.
 * @param      n,nlen  The RSA modulus. Must be exactly 2048 bits.
 * @param      d,dlen  The secret exponent. Must be <= 2048 bits.
 *
 * @retruns -1 If the input length is not correct
 * @returns 0  Otherwise.
 */
int occ_rsa2048_init_key (occ_rsa2048_key *k,
					      const uint8_t *n, int nlen,
					      const uint8_t *d, int dlen);

/**
 * 2048 bit RSA secret key setup with CRT coefficients.
 *
 * @param[out] k          The initialzed secret key.
 * @param      p,plen     The 1. RSA prime. Must be exactly 1024 bits.
 * @param      q,qlen     The 2. RSA prime. Must be exactly 1024 bits.
 * @param      dp,dplen   The 1. CRT exponent. dp = d mod (p-1).
 * @param      dq,dqlen   The 2. CRT exponent. dq = d mod (q-1).
 * @param      qinv,qilen The CRT coefficient. qinv = 1/q mod p.
 *
 * @retruns -1 If the input length is not correct
 * @returns 0  Otherwise.
 */
int occ_rsa2048_init_crt_key (occ_rsa2048_crt_key *k,
						      const uint8_t *p,    int plen,
						      const uint8_t *q,    int qlen,
						      const uint8_t *dp,   int dplen,
						      const uint8_t *dq,   int dqlen,
						      const uint8_t *qinv, int qilen);
/**@}*/

#endif
