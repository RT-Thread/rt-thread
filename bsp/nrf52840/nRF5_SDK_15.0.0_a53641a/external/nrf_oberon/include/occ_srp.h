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
 * SRP is an augmented password-authenticated key agreement protocol,
 * specifically designed to work around existing patents. SRP allows the use of
 * user names and passwords over unencrypted channels and supplies a shared
 * secret at the end of the authentication sequence that can be used to generate
 * encryption keys.
 *
 * An eavesdropper or man in the middle cannot obtain enough information to be
 * able to brute force guess a password without further interactions with the
 * parties for each guess.
 *
 * The server does not store password-equivalent data. This means that an
 * attacker who steals the server data cannot masquerade as the client unless
 * they first perform a brute force search for the password.
 *
 * The specific variant implemented here is SRP-6 3072 bit SHA-512 as mandated
 * by Apple for use with HomeKit.
 *
 * @see [RFC 5054 - Using the Secure Remote Password (SRP) Protocol for TLS Authentication](https://tools.ietf.org/html/rfc5054)
 * @see [The Stanford SRP Homepage](http://srp.stanford.edu)
 *
 * **Basic protocol overview**
 *
 * *Setup*
 * 1. Server generates a username / password combination together with a salt.
 * 2. Server derives a password verifier (see #occ_srp_verifier).
 * 3. The username, salt and verifier are stored and required to open sessions.
 *    The original password is no longer needed.
 *
 * *Session opening*
 * 1. Client sends a username and the public key of an ephemeral key pair to the
 *    server.
 * 2. Server sends the salt and the public key of another ephemeral key pair to
 *    the client (see #occ_srp_public_key).
 * 3. Client and Server both compute the session key from this information (see
 *    #occ_srp_scrambling_parameter, #occ_srp_premaster_secret,
 *    #occ_srp_session_key).
 * 4. Client sends proof of the session key to the server.
 * 5. Server validates proof (see #occ_srp_proof_m1), then sends proof of the 
 *    session key to the client (see #occ_srp_proof_m2).
 * 6. Client validates proof. Both parties know that they share the same private
 *    session key.
 */

#ifndef OCC_SRP_H
#define OCC_SRP_H

#include <stdint.h>
#include <stddef.h>


/**
 * Salt length.
 */
#define occ_srp_SALT_BYTES (16)

/**
 * Password verifier length.
 */
#define occ_srp_VERIFIER_BYTES (384)

/**
 * Secret key length.
 */
#define occ_srp_SECRET_KEY_BYTES (32)

/**
 * Public key length.
 */
#define occ_srp_PUBLIC_KEY_BYTES (384)

/**
 * Scrambling parameter length.
 */
#define occ_srp_SCRAMBLING_PARAMETER_BYTES (64)

/**
 * Premaster secret length.
 */
#define occ_srp_PREMASTER_SECRET_BYTES (384)

/**
 * Session key length.
 */
#define occ_srp_SESSION_KEY_BYTES (64)

/**
 * Proof length.
 */
#define occ_srp_PROOF_BYTES (64)


/**@name SRP-6 Password verifier generation.
 *
 * A password verifier is generated from a user name and a password. The
 * password @p pass may be discarded, as only the verifier is used during later
 * computations.
 *
 * **Example**
 * @include occ_srp_verifier.c
 */
/**@{*/
/**
 * SRP-6 Password Verifier.
 *
 * The verifier is generated for a given user name @p user, a password @p pass
 * and salt @p salt.
 *
 * @param[out] v        Generated password verifier, must be 32 bit aligned.
 * @param      salt     Salt.
 * @param      user     User name.
 * @param      user_len Length of @p user.
 * @param      pass     Password.
 * @param      pass_len Length of @p pass.
 */
void occ_srp_verifier(uint8_t v[occ_srp_VERIFIER_BYTES],
                      const uint8_t salt[occ_srp_SALT_BYTES],
                      const uint8_t *user, size_t user_len,
                      const uint8_t *pass, size_t pass_len);
/**@}*/

/**@name SRP-6 Public key generation.
 *
 * An ephemeral keypair can be generated based on the password verifier to be
 * used when opening a new session.
 *
 * **Example**
 * @include occ_srp_public_key.c
 */
/**@{*/
/**
 * SRP-6 Public Key.
 *
 * The public key for a given private key @p priv_b is generated using the
 * password verifier @p v and put into @p pub_b.
 *
 * @param[out] pub_b  Generated public key, must be 32 bit aligned.
 * @param      priv_b Private key.
 * @param      v      Password verifier.
 */
void occ_srp_public_key(uint8_t pub_b[occ_srp_PUBLIC_KEY_BYTES],
                        const uint8_t priv_b[occ_srp_SECRET_KEY_BYTES],
                        const uint8_t v[occ_srp_VERIFIER_BYTES]);
/**@}*/

/**@name SRP-6 Session key generation.
 * 
 * A premaster secret can be derived from both the client's and server's public
 * keys, the server's private key and the password verifier. A shared session
 * key can be generated from this premaster secret.
 *
 * **Example**
 * @include occ_srp_session_key.c
 */
/**@{*/
/**
 * SRP-6 Scrambling Parameter.
 *
 * The scrambling parameter is computed from both the client's public key
 * @p pub_a and the server's public key @p pub_b. The scrambling parameter
 * is required to compute the premaster secret.
 *
 * @param[out] u     Generated scrambling parameter.
 * @param      pub_a Client public key.
 * @param      pub_b Server public key.
 */
void occ_srp_scrambling_parameter(uint8_t u[occ_srp_SCRAMBLING_PARAMETER_BYTES],
                                  const uint8_t pub_a[occ_srp_PUBLIC_KEY_BYTES],
                                  const uint8_t pub_b[occ_srp_PUBLIC_KEY_BYTES]);

/**
 * SRP-6 Premaster Secret.
 *
 * The premaster secret between the client and the server is computed using the
 * client public key @p pub_a, the server private key @p priv_b, the scrambling
 * parameter @p u and the password verifier @p v. If the client public key
 * @p pub_a is valid, the premaster secret is then put into @p s. The premaster
 * secret can be used to generate encryption keys.
 *
 * @param[out] s      Generated premaster secret, must be 32 bit aligned.
 * @param      pub_a  Client public key.
 * @param      priv_b Server private key.
 * @param      u      Scrambling parameter; generated with @c srp_scrambling_parameter.
 * @param      v      Password verifier.
 *
 * @returns 0 If @p pub_a is a legal public key.
 * @returns 1 Otherwise.
 */
int occ_srp_premaster_secret(uint8_t s[occ_srp_PREMASTER_SECRET_BYTES],
                             const uint8_t pub_a[occ_srp_PUBLIC_KEY_BYTES],
                             const uint8_t priv_b[occ_srp_SECRET_KEY_BYTES],
                             const uint8_t u[occ_srp_SCRAMBLING_PARAMETER_BYTES],
                             const uint8_t v[occ_srp_VERIFIER_BYTES]);

/**
 * SRP-6 SRP Session Key.
 *
 * Generates the shared SRP session key from the premaster secret @p s and puts
 * it into @p k.
 *
 * @param[out] k Generated SRP session key.
 * @param      s Premaster secret.
 */
void occ_srp_session_key(uint8_t k[occ_srp_SESSION_KEY_BYTES],
                         const uint8_t s[occ_srp_PREMASTER_SECRET_BYTES]);
/**@}*/

/**@name SRP-6 Proof exchange.
 * 
 * Proofs are exchanged from client to server and vice versa to ensure that both
 * parties computed the same shared session key. The proofs only match if the
 * correct password is used by the client.
 *
 * **Example**
 * @include occ_srp_proof.c
 */
/**@{*/
/**
 * SRP-6 Proof M1 (client to server).
 *
 * A proof is generated by the client and sent to the server to assert that the
 * client is in possession of the shared session key @p k. The server also
 * generates the proof. Only if the proofs match, the process can continue.
 * The proof is based on the salt @p salt, the client public key @p pub_a,
 * the server public key @p pub_b and the shared session key @p k.
 *
 * @param[out] m1       Generated proof.
 * @param      user     User name.
 * @param      user_len Length of @p user.
 * @param      salt     Salt.
 * @param      pub_a    Client public key.
 * @param      pub_b    Server public key.
 * @param      k        Session key.
 */
void occ_srp_proof_m1(uint8_t m1[occ_srp_PROOF_BYTES],
                      const uint8_t *user, size_t user_len,
                      const uint8_t salt[occ_srp_SALT_BYTES],
                      const uint8_t pub_a[occ_srp_PUBLIC_KEY_BYTES],
                      const uint8_t pub_b[occ_srp_PUBLIC_KEY_BYTES],
                      const uint8_t k[occ_srp_SESSION_KEY_BYTES]);

/**
 * SRP-6 Proof M2 (server to client).
 *
 * A second proof is generated by the server and sent back to the client to
 * assert that the server is in possession of the shared session key @p k. The
 * client also generates the proof. If the proofs match, both parties can assume
 * that they share the same session key @p k. The second proof is based on the
 * client public key @p pub_a, the first proof @p m1 and the session key @p k.
 *
 * @param[out] m2    Generated proof.
 * @param      pub_a Client public key.
 * @param      m1    First proof; generated with @c srp_proof_m1.
 * @param      k     Session key.
 */
void occ_srp_proof_m2(uint8_t m2[occ_srp_PROOF_BYTES],
                      const uint8_t pub_a[occ_srp_PUBLIC_KEY_BYTES],
                      const uint8_t m1[occ_srp_PROOF_BYTES],
                      const uint8_t k[occ_srp_SESSION_KEY_BYTES]);
/**@}*/

#endif
