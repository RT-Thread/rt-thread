/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#include "aes.h"
#include "app_timer.h"
#include "cifra_eax_aes.h"
#include "es_flash.h"
#include "es_stopwatch.h"
#include "fds.h"
#include "modes.h"
#include "occ_curve25519.h"
#include "occ_hmac_sha256.h"

#define TK_ROLLOVER 0x10000

#define NONCE_SIZE (6)
#define TAG_SIZE (2)
#define SALT_SIZE (2)
#define TLM_DATA_SIZE (ES_TLM_LENGTH - 2)
#define EIK_SIZE (ESCS_AES_KEY_SIZE)

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
    uint8_t private[ESCS_ECDH_KEY_SIZE];
    uint8_t public[ESCS_ECDH_KEY_SIZE];
} ecdh_key_pair_t;

/**@brief ECDH structure. */
typedef struct
{
    ecdh_key_pair_t ecdh_key_pair;
} es_security_ecdh_t;

static nrf_ecb_hal_data_t   m_aes_ecb_lk;
static es_security_slot_t   m_security_slot[APP_MAX_EID_SLOTS];
static es_security_ecdh_t   m_ecdh;
static es_security_msg_cb_t m_security_callback;
static es_stopwatch_id_t    m_seconds_passed_sw_id;

/**@brief Generates a EID with the Temporary Key*/
static void eid_generate(uint8_t slot_no)
{
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

    AES128_ECB_encrypt(m_security_slot[slot_no].aes_ecb_tk.cleartext,
                       m_security_slot[slot_no].aes_ecb_tk.key,
                       m_security_slot[slot_no].aes_ecb_tk.ciphertext);

    memcpy(m_security_slot[slot_no].eid,
           m_security_slot[slot_no].aes_ecb_tk.ciphertext,
           ES_EID_ID_LENGTH);

    m_security_callback(slot_no, ES_SECURITY_MSG_EID);
}


/**@brief Generates a temporary key with the Identity key. */
static void temp_key_generate(uint8_t slot_no)
{
    memset(m_security_slot[slot_no].aes_ecb_ik.cleartext, 0, ESCS_AES_KEY_SIZE);
    m_security_slot[slot_no].aes_ecb_ik.cleartext[11] = 0xFF;
    m_security_slot[slot_no].aes_ecb_ik.cleartext[14] =
        (uint8_t)((m_security_slot[slot_no].timing.time_counter >> 24) & 0xff);
    m_security_slot[slot_no].aes_ecb_ik.cleartext[15] =
        (uint8_t)((m_security_slot[slot_no].timing.time_counter >> 16) & 0xff);

    AES128_ECB_encrypt(m_security_slot[slot_no].aes_ecb_ik.cleartext,
                       m_security_slot[slot_no].aes_ecb_ik.key,
                       m_security_slot[slot_no].aes_ecb_ik.ciphertext);

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


/**@brief Generates a the private/public ECDH key pair.
 *
 * @param[out]  p_priv_buffer   buffer of size 32 bytes to hold the private key.
 * @param[out]  p_pub_buffer    buffer of size 32 bytes to hold the public key.
 */
static void es_beacon_ecdh_pair_generate(uint8_t * p_priv_buffer, uint8_t * p_pub_buffer)
{
    // Generate random beacon private key.
    uint8_t pool_size;
    uint8_t bytes_available;

    (void)sd_rand_application_pool_capacity_get(&pool_size);
    (void)sd_rand_application_bytes_available_get(&bytes_available);

    while (bytes_available < pool_size)
    {
        // wait for SD to acquire enough RNs.
        (void)sd_rand_application_bytes_available_get(&bytes_available);
    }

    (void)sd_rand_application_vector_get(p_priv_buffer, pool_size);

    if (pool_size < ESCS_ECDH_KEY_SIZE)
    {
        (void)sd_rand_application_bytes_available_get(&bytes_available);

        while (bytes_available < (ESCS_ECDH_KEY_SIZE - pool_size))
        {
            // Wait for SD to acquire enough RNs.
            (void)sd_rand_application_bytes_available_get(&bytes_available);
        }
        (void)sd_rand_application_vector_get(p_priv_buffer + pool_size,
                                             ESCS_ECDH_KEY_SIZE - pool_size);
    }

    // Create beacon public 32-byte ECDH key from private 32-byte ECDH key.
    occ_curve25519_scalarmult_base(p_pub_buffer, p_priv_buffer);
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
    uint8_t temp_buff[ESCS_AES_KEY_SIZE] = {0};

    AES128_ECB_decrypt(p_ecrypted_key, m_aes_ecb_lk.key, temp_buff);

    memcpy(m_aes_ecb_lk.key, temp_buff, ESCS_AES_KEY_SIZE);
    return es_flash_access_lock_key(m_aes_ecb_lk.key, ES_FLASH_ACCESS_WRITE);
}


void es_security_unlock_prepare(uint8_t * p_challenge)
{
    memcpy(m_aes_ecb_lk.cleartext, p_challenge, ESCS_AES_KEY_SIZE);
    AES128_ECB_encrypt(m_aes_ecb_lk.cleartext, m_aes_ecb_lk.key, m_aes_ecb_lk.ciphertext);
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
    return sd_rand_application_vector_get(p_rand_chlg_buff, ESCS_AES_KEY_SIZE);
}


void es_security_shared_ik_receive(uint8_t slot_no, uint8_t * p_encrypted_ik, uint8_t scaler_k)
{
    m_security_slot[slot_no].is_occupied         = true;
    m_security_slot[slot_no].timing.k_scaler     = scaler_k;
    m_security_slot[slot_no].timing.time_counter = APP_CONFIG_TIMING_INIT_VALUE;

    AES128_ECB_decrypt(p_encrypted_ik, m_aes_ecb_lk.key, m_security_slot[slot_no].aes_ecb_ik.key);

    temp_key_generate(slot_no);
    eid_generate(slot_no);

    m_security_callback(slot_no, ES_SECURITY_MSG_IK);
}


void es_security_client_pub_ecdh_receive(uint8_t slot_no, uint8_t * p_pub_ecdh, uint8_t scaler_k)
{
    static uint8_t attempt_counter = 0;

    m_security_slot[slot_no].is_occupied         = true;
    m_security_slot[slot_no].timing.k_scaler     = scaler_k;
    m_security_slot[slot_no].timing.time_counter = APP_CONFIG_TIMING_INIT_VALUE;

    uint8_t       beacon_private[ESCS_ECDH_KEY_SIZE]; // Beacon private ECDH key
    uint8_t       beacon_public[ESCS_ECDH_KEY_SIZE];  // Beacon public ECDH key
    uint8_t       phone_public[ESCS_ECDH_KEY_SIZE];   // Phone public ECDH key
    uint8_t       shared[ESCS_ECDH_KEY_SIZE];         // Shared secret ECDH key
    const uint8_t salt[1] = {0x01};                   // Salt
    uint8_t       identity_key[ESCS_AES_KEY_SIZE];    // Identity Key

    // Get public 32-byte service ECDH key from phone.
    memcpy(phone_public, p_pub_ecdh, ESCS_ECDH_KEY_SIZE);

    // Generate new set of keys for use with this EID slot.
    es_beacon_ecdh_pair_generate(beacon_private, beacon_public);
    memcpy(m_ecdh.ecdh_key_pair.private, beacon_private, ESCS_ECDH_KEY_SIZE);
    memcpy(m_ecdh.ecdh_key_pair.public, beacon_public, ESCS_ECDH_KEY_SIZE);

    // Generate shared 32-byte ECDH secret from beacon private service ECDH key and phone public ECDH key.
    occ_curve25519_scalarmult(shared, beacon_private, phone_public);

    // Generate key material using shared ECDH secret as salt and public_keys as key material. RFC 2104 HMAC-SHA256.
    uint8_t digest[64];
    uint8_t public_keys[64];
    memcpy(public_keys, phone_public, 32);
    memcpy(public_keys + 32, beacon_public, 32);

    occ_hmac_sha256(digest, public_keys, 64, shared, 32);

    // Zero check of the shared secret becoming zero, try generating a new key pair if so. Max attempt limit twice.
    uint8_t empty_check[32] = {0};

    if (memcmp(empty_check, shared, 32) == 0)
    {
        if (attempt_counter < 2)
        {
            attempt_counter++;
            es_beacon_ecdh_pair_generate(beacon_private, beacon_public);
        }
    }
    else
    {
        attempt_counter = 0;
    }

    // Generate 16-byte Identity Key from shared ECDH secret using RFC 2104 HMAC-SHA256 and salt.
    uint8_t digest_salted[64];
    occ_hmac_sha256(digest_salted, digest, 32, salt, 1);

    memcpy(identity_key, digest_salted, ESCS_AES_KEY_SIZE);

    memcpy(m_security_slot[slot_no].aes_ecb_ik.key, identity_key, ESCS_AES_KEY_SIZE);

    temp_key_generate(slot_no);
    eid_generate(slot_no);

    m_security_callback(slot_no, ES_SECURITY_MSG_ECDH);
    m_security_callback(slot_no, ES_SECURITY_MSG_IK);
}


void es_security_pub_ecdh_get(uint8_t slot_no, uint8_t * p_edch_buffer)
{
    memcpy(p_edch_buffer, m_ecdh.ecdh_key_pair.public, ESCS_ECDH_KEY_SIZE);
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
    memcpy(m_aes_ecb_lk.cleartext, m_security_slot[slot_no].aes_ecb_ik.key, ESCS_AES_KEY_SIZE);
    AES128_ECB_encrypt(m_aes_ecb_lk.cleartext, m_aes_ecb_lk.key, m_aes_ecb_lk.ciphertext);
    memcpy(p_key_buffer, m_aes_ecb_lk.ciphertext, ESCS_AES_KEY_SIZE);
}


void es_security_plain_eid_id_key_get(uint8_t slot_no, uint8_t * p_key_buffer)
{
    memcpy(p_key_buffer, m_security_slot[slot_no].aes_ecb_ik.key, ESCS_AES_KEY_SIZE);
}


void es_security_tlm_to_etlm(uint8_t ik_slot_no, es_tlm_frame_t * p_tlm, es_etlm_frame_t * p_etlm)
{
    cf_prp prp; // Describe the block cipher to use.

    uint8_t plain[TLM_DATA_SIZE] = {0}; // Plaintext tlm, without the frame byte and version.
    size_t  nplain               = TLM_DATA_SIZE; // Length of message plaintext.

    /*lint -save -e420 */
    memcpy(plain, &p_tlm->vbatt[0], sizeof(plain));

    const uint8_t header  = 0; // Additionally authenticated data (AAD).
    size_t        nheader = 0; // Length of header (AAD). May be zero.

    uint8_t key[EIK_SIZE] = {0};      // Encryption/decryption key: EIK.
    size_t  nkey          = EIK_SIZE; // Length of encryption/decryption key.

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
    (void)sd_rand_application_vector_get(salt, SALT_SIZE);
    memcpy(&nonce[4], salt, SALT_SIZE);

    uint8_t cipher[ES_ETLM_ECRYPTED_LENGTH]; // Ciphertext output. nplain bytes are written.
    uint8_t tag[TAG_SIZE] = {0};             // Authentication tag. ntag bytes are written.
    size_t  ntag          = TAG_SIZE;        // Length of authentication tag.

    // Encryption
    // --------------------------------------------------------------------------
    cf_aes_context ctx;
    cf_aes_init(&ctx, key, nkey);

    prp.encrypt = (cf_prp_block)cf_aes_encrypt; // Encryption context
    prp.decrypt = (cf_prp_block)cf_aes_decrypt; // Decryption context
    prp.blocksz = ESCS_AES_KEY_SIZE;

    cf_eax_encrypt(&prp,
                   &ctx,
                   plain,   // Plaintext input, aka TLM
                   nplain,  // Length of TLM
                   &header, // Empty
                   nheader, // Empty
                   nonce,   // Nonce input
                   nnonce,  // Length of nonce
                   cipher,  // Encrypted output
                   tag,     // Authentication tag output
                   ntag     // Length of authentication tag
                   );

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

    return NRF_SUCCESS;
}
