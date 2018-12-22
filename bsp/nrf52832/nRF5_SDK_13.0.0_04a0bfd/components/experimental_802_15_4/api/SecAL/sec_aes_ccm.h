/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
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
#ifndef SEC_AES_CCM_H_INCLUDED
#define SEC_AES_CCM_H_INCLUDED

#include <stdint.h>

/** @file
 * This file contains declarations of the AES CCM encryption/decryption routines and necessary types.
 * It also contains the declaration of the Security Abstract library initialization routine.
 *
 * @defgroup sec_aes_ccm Security AES CCM declarations
 * @ingroup sec_15_4
 * @{
 * @brief Module to declare Security AES CCM API
 */

/**
 * @brief   AES CCM Status enumeration.
 */
typedef enum
{
    AES_CCM_OK,             /**< AES CCM operation succeeded. */
    AES_ENGINE_FAIL,        /**< AES engine failed. */
    AES_CCM_FAIL,           /**< CCM algorithm failed. */
    AES_CCM_AUTH_FAIL       /**< CCM authentication failed. */
} sec_aes_ccm_status_t;

/**
 * @brief AES CCM request.
 *
 * @details The AES CCM request primitive is issued by the AES user.
 * There are two use cases for the request:
 * The first one is to encrypt the user text with some given key.
 * The second one is to decrypt the cipher text against the key.
 * The encrypted or decrypted data is stored in text_data.
 */
typedef struct
{
    /** Counted authentication tag. */
    uint8_t               * mic;
    /** Security level identifier. */
    uint8_t                 level;
    /** A 128-bit-long string to be used as a key. Each entity must have evidence that access
     *  to this key is restricted to the entity itself and its intended key sharing group member(s). */
    uint8_t               * key;
    /** A nonce N of 15 - L octets. Within the scope of any encryption key, the nonce value must be unique. */
    uint8_t               * nonce;
    /** An octet string representing plain text data in case of encryption and cipher text data
     *  in case of decryption. */
    uint8_t               * text_data;
    /** Text data length. */
    uint8_t                 text_data_len;
    /** Octet string representing input data to perform authentication. */
    uint8_t               * auth_data;
    /** Auth data length. */
    uint8_t                 auth_data_len;
} sec_aes_ccm_req_t;


/**
 * @brief Function for initializing the security abstraction layer.
 */
void sec_init(void);

/**
 * @brief AES CCM encryption transformation.
 *
 * @details Performs synchronous encryption of data.
 *
 * @param req Encryption request structure.
 * @return AES_CCM_OK on success, otherwise an implementation defined error.
 */
sec_aes_ccm_status_t sec_aes_ccm_enc(sec_aes_ccm_req_t * req);


/**
 * @brief AES CCM decryption transformation.
 *
 * @details Performs synchronous decryption of a cipher.
 *
 * @param req Decryption request structure.
 * @return AES_CCM_OK on success, otherwise an implementation defined error.
 */
sec_aes_ccm_status_t sec_aes_ccm_dec(sec_aes_ccm_req_t * req);

/** @} */

#endif /* SEC_AES_CCM_H_INCLUDED */
