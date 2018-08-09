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
#include <stdbool.h>
#include <stdint.h>
#include "es_security.h"
#include "app_timer.h"
#include "es_flash.h"
#include "es_stopwatch.h"
#include "fds.h"
#include "modes.h"
#include "nrf_crypto.h"

#define TK_ROLLOVER 0x10000

#define NONCE_SIZE                  (6)
#define TAG_SIZE                    (2)
#define SALT_SIZE                   (2)
#define TLM_DATA_SIZE               (ES_TLM_LENGTH - 2)
#define EIK_SIZE                    (ESCS_AES_KEY_SIZE)
#define AES_ECB_CIPHERTEXT_LENGTH   (16)
#define AES_ECB_CLEARTEXT_LENGTH    (16)

/**@brief Timing structure. */
typedef struct
{
    uint32_t time_counter;
    uint8_t  k_scaler;
} es_security_timing_t;

/**@brief Security slot structure. */
typedef struct
{
    nrf_ecb_hal_data_t   aes_ecb_ik;
    nrf_ecb_hal_data_t   aes_ecb_tk;
    uint8_t              eid[ES_EID_ID_LENGTH];
    es_security_timing_t timing;
    bool                 is_occupied;
} es_security_slot_t;

/**@brief Key pair structure. */
typedef struct
{
    nrf_crypto_ecc_private_key_t private;
    nrf_crypto_ecc_public_key_t  public;
} ecdh_key_pair_t;

/**@brief ECDH structure. */
typedef struct
{
    ecdh_key_pair_t ecdh_key_pair;
} es_security_ecdh_t;

static nrf_ecb_hal_data_t                           m_aes_ecb_lk;
static es_security_slot_t                           m_security_slot[APP_MAX_EID_SLOTS];
static es_security_ecdh_t                           m_ecdh;
static es_security_msg_cb_t                         m_security_callback;
static es_stopwatch_id_t                            m_seconds_passed_sw_id;

// Use static context variables to avoid stack allocation.
static nrf_crypto_aes_context_t                     m_aes_context;
static nrf_crypto_hmac_context_t                    m_hmac_context;
static nrf_crypto_aead_context_t                    m_aead_context;
static nrf_crypto_ecc_key_pair_generate_context_t   ecc_key_pair_generate_context;
static nrf_crypto_ecdh_context_t                    ecdh_context;

/**@brief Generates a EID with the Temporary Key*/
static void eid_generate(uint8_t slot_no)
{
    ret_code_t  err_code;
    size_t      ciphertext_size = AES_ECB_CIPHERTEXT_LENGTH;

    memset(m_security_slot[slot_no].aes_ecb_tk.cleartext, 0, ESCS_AES_KEY_SIZE);
    m_security_slot[slot_no].aes_ecb_tk.cleartext[11] = m_security_slot[slot_no].timing.k_scaler;

    uint32_t k_bits_cleared_time =
        (m_security_slot[slot_no].timing.time_counter >> m_security_slot[slot_no].timing.k_scaler)
        << m_security_slot[slot_no].timing.k_scaler;

    m_security_slot[slot_no].aes_ecb_tk.cleartext[12] =
        (uint8_t)((k_bits_cleared_time >> 24) & 0xff);
    m_security_slot[slot_no].aes_ecb_tk.cleartext[13] =
        (uint8_t)((k_bits_cleared_time >> 16) & 0xff);
    m_security_slot[slot_no].aes_ecb_tk.cleartext[14] = (uint8_t)((k_bits_cleared_time >> 8) & 0xff);
    m_security_slot[slot_no].aes_ecb_tk.cleartext[15] = (uint8_t)((k_bits_cleared_time) & 0xff);

    err_code = nrf_crypto_aes_crypt(&m_aes_context,
                                    &g_nrf_crypto_aes_ecb_128_info,
                                    NRF_CRYPTO_ENCRYPT,                             // Operation
                                    m_security_slot[slot_no].aes_ecb_tk.key,        // Key
                                    NULL,                                           // IV
                                    m_security_slot[slot_no].aes_ecb_tk.cleartext,  // Data in
                                    AES_ECB_CLEARTEXT_LENGTH,                       // Data in size
                                    m_security_slot[slot_no].aes_ecb_tk.ciphertext, // Data out
                                    &ciphertext_size);                              // Data out size

    APP_ERROR_CHECK(err_code);

    memcpy(m_security_slot[slot_no].eid,
           m_security_slot[slot_no].aes_ecb_tk.ciphertext,
           ES_EID_ID_LENGTH);

    m_security_callback(slot_no, ES_SECURITY_MSG_EID);
}


/**@brief Generates a temporary key with the Identity key. */
static void temp_key_generate(uint8_t slot_no)
{
    ret_code_t  err_code;
    size_t      ciphertext_size = AES_ECB_CIPHERTEXT_LENGTH;

    memset(m_security_slot[slot_no].aes_ecb_ik.cleartext, 0, ESCS_AES_KEY_SIZE);
    m_security_slot[slot_no].aes_ecb_ik.cleartext[11] = 0xFF;
    m_security_slot[slot_no].aes_ecb_ik.cleartext[14] =
        (uint8_t)((m_security_slot[slot_no].timing.time_counter >> 24) & 0xff);
    m_security_slot[slot_no].aes_ecb_ik.cleartext[15] =
        (uint8_t)((m_security_slot[slot_no].timing.time_counter >> 16) & 0xff);

    err_code = nrf_crypto_aes_crypt(&m_aes_context,
                                    &g_nrf_crypto_aes_ecb_128_info,
                                    NRF_CRYPTO_ENCRYPT,                             // Operation
                                    m_security_slot[slot_no].aes_ecb_ik.key,        // Key
                                    NULL,                                           // IV
                                    m_security_slot[slot_no].aes_ecb_ik.cleartext,  // Data in
                                    AES_ECB_CLEARTEXT_LENGTH,                       // Data in size
                                    m_security_slot[slot_no].aes_ecb_ik.ciphertext, // Data out
                                    &ciphertext_size);                              // Data out size

    APP_ERROR_CHECK(err_code);

    memcpy(m_security_slot[slot_no].aes_ecb_tk.key,
           m_security_slot[slot_no].aes_ecb_ik.ciphertext,
           ESCS_AES_KEY_SIZE);
}


static void check_rollovers_and_update_eid(uint8_t slot_no)
{
    if (m_security_slot[slot_no].timing.time_counter % TK_ROLLOVER == 0)
    {
        temp_key_generate(slot_no);
    }
    /*lint -save -e573 */
    if ((m_security_slot[slot_no].timing.time_counter %
         (2 << (m_security_slot[slot_no].timing.k_scaler - 1))) == 0)
    {
        eid_generate(slot_no);
    }
    /*lint -restore */
}


/**@brief Initialize lock code from flash. If it does not exist, copy from APP_CONFIG_LOCK_CODE.
 */
static void lock_code_init(uint8_t * p_lock_buff)
{
    ret_code_t err_code;

    err_code = es_flash_access_lock_key(p_lock_buff, ES_FLASH_ACCESS_READ);
    FLASH_ACCES_ERROR_CHECK_ALLOW_NOT_FOUND(err_code);

    // If no lock keys exist, then generate one and copy it to buffer.
    if (err_code == FDS_ERR_NOT_FOUND)
    {
        uint8_t lock_code[16] = APP_CONFIG_LOCK_CODE;

        memcpy(p_lock_buff, lock_code, sizeof(lock_code));

        err_code = es_flash_access_lock_key(p_lock_buff, ES_FLASH_ACCESS_WRITE);
        APP_ERROR_CHECK(err_code);
    }
}


void es_security_update_time(void)
{
    static uint32_t timer_persist;
    uint32_t        second_since_last_invocation = es_stopwatch_check(m_seconds_passed_sw_id);

    if (second_since_last_invocation > 0)
    {
        for (uint32_t i = 0; i < APP_MAX_EID_SLOTS; ++i)
        {
            if (m_security_slot[i].is_occupied)
            {
                m_security_slot[i].timing.time_counter += second_since_last_invocation;
                check_rollovers_and_update_eid(i);
            }
        }

        // Every 24 hr, write the new EID timer to flash.
        timer_persist += second_since_last_invocation;
        const uint32_t TWENTY_FOUR_HOURS = 60 * 60 * 24;
        if (timer_persist >= TWENTY_FOUR_HOURS)
        {
            for (uint32_t i = 0; i < APP_MAX_EID_SLOTS; ++i)
            {
                if (m_security_slot[i].is_occupied)
                {
                    m_security_callback(i, ES_SECURITY_MSG_STORE_TIME);
                }
            }
            timer_persist = 0;
        }
    }
}


void es_security_eid_slots_restore(uint8_t         slot_no,
                                   uint8_t         k_scaler,
                                   uint32_t        time_counter,
                                   const uint8_t * p_ik)
{
    m_security_slot[slot_no].timing.k_scaler     = k_scaler;
    m_security_slot[slot_no].timing.time_counter = time_counter;
    memcpy(m_security_slot[slot_no].aes_ecb_ik.key, p_ik, ESCS_AES_KEY_SIZE);
    m_security_slot[slot_no].is_occupied = true;
    m_security_callback(slot_no, ES_SECURITY_MSG_IK);
    temp_key_generate(slot_no);
    eid_generate(slot_no);
}


ret_code_t es_security_lock_code_update(uint8_t * p_ecrypted_key)
{
    ret_code_t  err_code;
    uint8_t     temp_buff[ESCS_AES_KEY_SIZE] = {0};
    size_t      temp_buff_size = sizeof(temp_buff);

    err_code = nrf_crypto_aes_crypt(&m_aes_context,
                                    &g_nrf_crypto_aes_ecb_128_info,
                                    NRF_CRYPTO_DECRYPT,             // Operation
                                    m_aes_ecb_lk.key,               // Key
                                    NULL,                           // IV
                                    p_ecrypted_key,                 // Data in
                                    16,                             // Data in size
                                    temp_buff,                      // Data out
                                    &temp_buff_size);               // Data out size

    VERIFY_SUCCESS(err_code);

    memcpy(m_aes_ecb_lk.key, temp_buff, ESCS_AES_KEY_SIZE);
    return es_flash_access_lock_key(m_aes_ecb_lk.key, ES_FLASH_ACCESS_WRITE);
}


void es_security_unlock_prepare(uint8_t * p_challenge)
{
    ret_code_t  err_code;
    size_t      ciphertext_size = AES_ECB_CIPHERTEXT_LENGTH;

    memcpy(m_aes_ecb_lk.cleartext, p_challenge, ESCS_AES_KEY_SIZE);

    err_code = nrf_crypto_aes_crypt(&m_aes_context,
                                    &g_nrf_crypto_aes_ecb_128_info,
                                    NRF_CRYPTO_ENCRYPT,             // Operation
                                    m_aes_ecb_lk.key,               // Key
                                    NULL,                           // IV
                                    m_aes_ecb_lk.cleartext,         // Data in
                                    AES_ECB_CLEARTEXT_LENGTH,       // Data in size
                                    m_aes_ecb_lk.ciphertext,        // Data out
                                    &ciphertext_size);              // Data out size

    APP_ERROR_CHECK(err_code);
}


void es_security_unlock_verify(uint8_t * p_unlock_token)
{
    if (memcmp(p_unlock_token, m_aes_ecb_lk.ciphertext, ESCS_AES_KEY_SIZE) == 0)
    {
        m_security_callback(0, ES_SECURITY_MSG_UNLOCKED);
    }
}


ret_code_t es_security_random_challenge_generate(uint8_t * p_rand_chlg_buff)
{
    return nrf_crypto_rng_vector_generate(p_rand_chlg_buff, ESCS_AES_KEY_SIZE);
}


void es_security_shared_ik_receive(uint8_t slot_no, uint8_t * p_encrypted_ik, uint8_t scaler_k)
{
    ret_code_t  err_code;
    size_t      cleartext_size = AES_ECB_CLEARTEXT_LENGTH;

    m_security_slot[slot_no].is_occupied         = true;
    m_security_slot[slot_no].timing.k_scaler     = scaler_k;
    m_security_slot[slot_no].timing.time_counter = APP_CONFIG_TIMING_INIT_VALUE;

    err_code = nrf_crypto_aes_crypt(&m_aes_context,
                                    &g_nrf_crypto_aes_ecb_128_info,
                                    NRF_CRYPTO_DECRYPT,                         // Operation
                                    m_aes_ecb_lk.key,                           // Key
                                    NULL,                                       // IV
                                    p_encrypted_ik,                             // Data in
                                    16,                                         // Data in size
                                    m_security_slot[slot_no].aes_ecb_ik.key,    // Data out
                                    &cleartext_size);                           // Data out size

    APP_ERROR_CHECK(err_code);

    temp_key_generate(slot_no);
    eid_generate(slot_no);

    m_security_callback(slot_no, ES_SECURITY_MSG_IK);
}


void es_security_client_pub_ecdh_receive(uint8_t slot_no, uint8_t * p_pub_ecdh, uint8_t scaler_k)
{
    ret_code_t                  err_code;
    nrf_crypto_ecc_public_key_t phone_public;                       // Phone public ECDH key
    uint8_t                     beacon_public[ESCS_ECDH_KEY_SIZE];  // Beacon public ECDH key
    uint8_t                     shared[ESCS_ECDH_KEY_SIZE];         // Shared secret ECDH key
    uint8_t                     public_keys[64];                    // Buffer for concatenated public keys
    uint8_t                     key_material[64];                   // Buffer for holding key material
    uint8_t                     empty_check[ESCS_ECDH_KEY_SIZE]     = {0};
    size_t                      beacon_public_size                  = sizeof(beacon_public);
    size_t                      shared_size                         = sizeof(shared);
    size_t                      key_material_size                   = sizeof(key_material);

    m_security_slot[slot_no].is_occupied         = true;
    m_security_slot[slot_no].timing.k_scaler     = scaler_k;
    m_security_slot[slot_no].timing.time_counter = APP_CONFIG_TIMING_INIT_VALUE;

    // Get public 32-byte service ECDH key from phone.
    err_code = nrf_crypto_ecc_public_key_from_raw(&g_nrf_crypto_ecc_curve25519_curve_info,
                                                  &phone_public,
                                                  p_pub_ecdh,
                                                  ESCS_ECDH_KEY_SIZE);

    APP_ERROR_CHECK(err_code);

    // Generate key pair.
    err_code = nrf_crypto_ecc_key_pair_generate(&ecc_key_pair_generate_context,
                                                &g_nrf_crypto_ecc_curve25519_curve_info,
                                                &m_ecdh.ecdh_key_pair.private,
                                                &m_ecdh.ecdh_key_pair.public);

    APP_ERROR_CHECK(err_code);

    // Generate shared 32-byte ECDH secret from beacon private service ECDH key and phone public ECDH key.
    err_code = nrf_crypto_ecdh_compute(&ecdh_context,
                                       &m_ecdh.ecdh_key_pair.private,
                                       &phone_public,
                                       shared,
                                       &shared_size);

    APP_ERROR_CHECK(err_code);

    // Verify that the shared secret is not zero at this point, and report an error/reset if it is.
    if (memcmp(empty_check, shared, ESCS_ECDH_KEY_SIZE) == 0)
    {
        APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
    }

    // Concatenate the resolver's public key and beacon's public key
    err_code = nrf_crypto_ecc_public_key_to_raw(&m_ecdh.ecdh_key_pair.public,
                                                beacon_public,
                                                &beacon_public_size);

    APP_ERROR_CHECK(err_code);

    memcpy(public_keys, p_pub_ecdh, 32);
    memcpy(public_keys + 32, beacon_public, 32);

    // Convert the shared secret to key material using HKDF-SHA256. HKDF is used with the salt set
    // to a concatenation of the resolver's public key and beacon's public key
    err_code = nrf_crypto_hkdf_calculate(&m_hmac_context,
                                         &g_nrf_crypto_hmac_sha256_info,
                                         key_material,                          // Output key
                                         &key_material_size,                    // Output key size
                                         shared,                                // Input key
                                         sizeof(shared),                        // Input key size
                                         public_keys,                           // Salt
                                         sizeof(public_keys),                   // Salt size
                                         NULL,                                  // Additional info
                                         0,                                     // Additional info size
                                         NRF_CRYPTO_HKDF_EXTRACT_AND_EXPAND);   // Mode

    APP_ERROR_CHECK(err_code);

    // Truncate the key material to 128 bits to convert it to an AES-128 secret key (Identity key).
    memcpy(m_security_slot[slot_no].aes_ecb_ik.key, key_material, ESCS_AES_KEY_SIZE);

    temp_key_generate(slot_no);
    eid_generate(slot_no);

    m_security_callback(slot_no, ES_SECURITY_MSG_ECDH);
    m_security_callback(slot_no, ES_SECURITY_MSG_IK);
}


void es_security_pub_ecdh_get(uint8_t slot_no, uint8_t * p_edch_buffer)
{
    ret_code_t  err_code;
    size_t      buffer_size = ESCS_ECDH_KEY_SIZE;

    err_code = nrf_crypto_ecc_public_key_to_raw(&m_ecdh.ecdh_key_pair.public,
                                                p_edch_buffer,
                                                &buffer_size);

    APP_ERROR_CHECK(err_code);
}


uint32_t es_security_clock_get(uint8_t slot_no)
{
    return m_security_slot[slot_no].timing.time_counter;
}


void es_security_eid_slot_destroy(uint8_t slot_no)
{
    memset(&m_security_slot[slot_no], 0, sizeof(es_security_slot_t));
}


uint8_t es_security_scaler_get(uint8_t slot_no)
{
    return m_security_slot[slot_no].timing.k_scaler;
}


void es_security_eid_get(uint8_t slot_no, uint8_t * p_eid_buffer)
{
    memcpy(p_eid_buffer, m_security_slot[slot_no].eid, ES_EID_ID_LENGTH);
}


void es_security_encrypted_eid_id_key_get(uint8_t slot_no, uint8_t * p_key_buffer)
{
    ret_code_t  err_code;
    size_t      ciphertext_size = AES_ECB_CIPHERTEXT_LENGTH;

    memcpy(m_aes_ecb_lk.cleartext, m_security_slot[slot_no].aes_ecb_ik.key, ESCS_AES_KEY_SIZE);

    err_code = nrf_crypto_aes_crypt(&m_aes_context,
                                    &g_nrf_crypto_aes_ecb_128_info,
                                    NRF_CRYPTO_ENCRYPT,             // Operation
                                    m_aes_ecb_lk.key,               // Key
                                    NULL,                           // IV
                                    m_aes_ecb_lk.cleartext,         // Data in
                                    AES_ECB_CLEARTEXT_LENGTH,       // Data in size
                                    m_aes_ecb_lk.ciphertext,        // Data out
                                    &ciphertext_size);              // Data out size

    APP_ERROR_CHECK(err_code);

    memcpy(p_key_buffer, m_aes_ecb_lk.ciphertext, ESCS_AES_KEY_SIZE);
}


void es_security_plain_eid_id_key_get(uint8_t slot_no, uint8_t * p_key_buffer)
{
    memcpy(p_key_buffer, m_security_slot[slot_no].aes_ecb_ik.key, ESCS_AES_KEY_SIZE);
}


void es_security_tlm_to_etlm(uint8_t ik_slot_no, es_tlm_frame_t * p_tlm, es_etlm_frame_t * p_etlm)
{
    ret_code_t  err_code;
    uint8_t     plain[TLM_DATA_SIZE] = {0};             // Plaintext tlm, without the frame byte and version.
    size_t      nplain               = TLM_DATA_SIZE;   // Length of message plaintext.

    /*lint -save -e420 */
    memcpy(plain, &p_tlm->vbatt[0], sizeof(plain));

    uint8_t key[EIK_SIZE] = {0};      // Encryption/decryption key: EIK.

    memcpy(key, &m_security_slot[ik_slot_no].aes_ecb_ik.key[0], EIK_SIZE);
    /*lint -restore */

    uint8_t nonce[NONCE_SIZE] = {0};        // Nonce. This must not repeat for a given key.
    size_t  nnonce            = NONCE_SIZE; // Length of nonce.First 4 bytes are beacon time base with k-bits cleared.
                                            // Last two bits are randomly generated

    // Take the current timestamp and clear the lowest K bits, use it as nonce.
    uint32_t k_bits_cleared_time = (m_security_slot[ik_slot_no].timing.time_counter
                                    >> m_security_slot[ik_slot_no].timing.k_scaler)
                                   << m_security_slot[ik_slot_no].timing.k_scaler;

    nonce[0] = (uint8_t)((k_bits_cleared_time >> 24) & 0xff);
    nonce[1] = (uint8_t)((k_bits_cleared_time >> 16) & 0xff);
    nonce[2] = (uint8_t)((k_bits_cleared_time >> 8) & 0xff);
    nonce[3] = (uint8_t)((k_bits_cleared_time) & 0xff);

    // Generate random salt.
    uint8_t salt[SALT_SIZE] = {0};
    err_code = nrf_crypto_rng_vector_generate(salt, SALT_SIZE);
    APP_ERROR_CHECK(err_code);
    memcpy(&nonce[4], salt, SALT_SIZE);

    uint8_t cipher[ES_ETLM_ECRYPTED_LENGTH]; // Ciphertext output. nplain bytes are written.
    uint8_t tag[TAG_SIZE] = {0};             // Authentication tag. ntag bytes are written.
    size_t  ntag          = TAG_SIZE;        // Length of authentication tag.

    // Encryption
    // --------------------------------------------------------------------------
    err_code = nrf_crypto_aead_init(&m_aead_context, &g_nrf_crypto_aes_eax_128_info, key);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_crypto_aead_crypt(&m_aead_context,
                                     NRF_CRYPTO_ENCRYPT, // Operation
                                     nonce,              // Nonce
                                     nnonce,             // Nonce size
                                     NULL,               // Additional authenticated data (adata)
                                     0,                  // Additional authenticated data size
                                     plain,              // Input data
                                     nplain,             // Input data size
                                     cipher,             // Output data
                                     tag,                // MAC result output
                                     ntag);              // MAC size

    APP_ERROR_CHECK(err_code);

    err_code = nrf_crypto_aead_uninit(&m_aead_context);
    APP_ERROR_CHECK(err_code);

    // Construct the eTLM.
    // --------------------------------------------------------------------------
    p_etlm->frame_type = p_tlm->frame_type;
    p_etlm->version    = ES_TLM_VERSION_ETLM;
    memcpy(p_etlm->encrypted_tlm, cipher, ES_ETLM_ECRYPTED_LENGTH);
    memcpy((uint8_t *)&p_etlm->random_salt, salt, SALT_SIZE);
    memcpy((uint8_t *)&p_etlm->msg_integrity_check, tag, TAG_SIZE);
}


ret_code_t es_security_init(es_security_msg_cb_t security_callback)
{
    ret_code_t err_code;

    if (security_callback == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    // Get lock code from 'es_app_config.h', or fetch it from flash if exists.
    lock_code_init(m_aes_ecb_lk.key);

    m_security_callback = security_callback;

    memset(&m_ecdh, 0, sizeof(es_security_ecdh_t));

    for (uint32_t i = 0; i < APP_MAX_EID_SLOTS; ++i)
    {
        m_security_slot[i].timing.time_counter = APP_CONFIG_TIMING_INIT_VALUE;
    }
    err_code = es_stopwatch_create(&m_seconds_passed_sw_id, APP_TIMER_TICKS(1000));
    APP_ERROR_CHECK(err_code);

    err_code = nrf_crypto_init();
    APP_ERROR_CHECK(err_code);

    return NRF_SUCCESS;
}
