/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_BLE_LESC)

#include "nrf_ble_lesc.h"
#include "nrf_crypto.h"

#define NRF_LOG_MODULE_NAME nrf_ble_lesc
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief Descriptor of the peer public key. */
typedef struct
{
    nrf_crypto_ecc_public_key_t value;        /**< Peer public key. */
    bool                        is_requested; /**< Flag indicating that the public key has been requested to compute DH key. */
    bool                        is_valid;     /**< Flag indicating that the public key is valid. */
} nrf_ble_lesc_peer_pub_key_t;

/**@brief   The maximum number of peripheral and central connections combined.
 *          This value is based on what is configured in the SoftDevice handler sdk_config.
 */
#define NRF_BLE_LESC_LINK_COUNT (NRF_SDH_BLE_PERIPHERAL_LINK_COUNT + NRF_SDH_BLE_CENTRAL_LINK_COUNT)

__ALIGN(4) static ble_gap_lesc_p256_pk_t m_lesc_public_key;                             /**< LESC ECC Public Key. */
__ALIGN(4) static ble_gap_lesc_dhkey_t   m_lesc_dh_key;                                 /**< LESC ECC DH Key. */

static nrf_crypto_ecdh_context_t                  m_ecdh_context;                       /**< Context to do the LESC ECDH calculation */

static bool                                       m_ble_lesc_internal_error;            /**< Flag indicating that the module encountered an internal error. */
static bool                                       m_keypair_generated;                  /**< Flag indicating that the local ECDH key pair was generated. */
static nrf_crypto_ecc_key_pair_generate_context_t m_keygen_context;                     /**< Context to generate private/public key pair. */
static nrf_crypto_ecc_private_key_t               m_private_key;                        /**< Allocated private key type to use for LESC DH generation. */
static nrf_crypto_ecc_public_key_t                m_public_key;                         /**< Allocated public key type to use for LESC DH generation. */
static nrf_ble_lesc_peer_pub_key_t                m_peer_keys[NRF_BLE_LESC_LINK_COUNT]; /**< Array of pointers to peer public keys, used for LESC DH generation. */

static bool                                       m_lesc_oobd_own_generated;
static ble_gap_lesc_oob_data_t                    m_ble_lesc_oobd_own;                  /**< LESC OOB data used in LESC OOB pairing mode. */
static nrf_ble_lesc_peer_oob_data_handler         m_lesc_oobd_peer_handler;

ret_code_t nrf_ble_lesc_init(void)
{
    ret_code_t err_code;

    memset((void *) m_peer_keys, 0, sizeof(m_peer_keys));

#if NRF_CRYPTO_ALLOCATOR == NRF_CRYPTO_ALLOCATOR_NRF_MALLOC
    // Initialize mem_manager if used by nrf_crypto.
    err_code = nrf_mem_init();
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("nrf_mem_init() returned error 0x%x.", err_code);
        return err_code;
    }
#endif

    // Ensure that nrf_crypto has been initialized.
    err_code = nrf_crypto_init();
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("nrf_crypto_init() returned error 0x%x.", err_code);
        return err_code;
    }
    NRF_LOG_DEBUG("Initialized nrf_crypto.");

#if defined(NRF_CRYPTO_RNG_AUTO_INIT_ENABLED) && (NRF_CRYPTO_RNG_AUTO_INIT_ENABLED == 1)
    // Do nothing. RNG is initialized with nrf_crypto_init call.
#elif defined(NRF_CRYPTO_RNG_AUTO_INIT_ENABLED) && (NRF_CRYPTO_RNG_AUTO_INIT_ENABLED == 0)
    // Initialize the RNG.
    err_code = nrf_crypto_rng_init(NULL, NULL);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("nrf_crypto_rng_init() returned error 0x%x.", err_code);
        return err_code;
    }
#else
    #error Invalid sdk_config.h (does not contain NRF_CRYPTO_RNG_AUTO_INIT_ENABLED)
#endif // defined(NRF_CRYPTO_RNG_AUTO_INIT_ENABLED) && (NRF_CRYPTO_RNG_AUTO_INIT_ENABLED == 1)
    NRF_LOG_DEBUG("Initialized nrf_ble_lesc.");

    // Reset module state.
    m_ble_lesc_internal_error = false;
    m_keypair_generated       = false;

    // Generate ECC key pair. Only one key pair is automatically generated by this module.
    err_code = nrf_ble_lesc_keypair_generate();
    return err_code;
}


ret_code_t nrf_ble_lesc_keypair_generate(void)
{
    ret_code_t err_code;
    size_t     public_len = NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE;

    // Check if any DH computation is pending
    for (uint32_t i = 0; i < ARRAY_SIZE(m_peer_keys); i++)
    {
        if (m_peer_keys[i].is_valid)
        {
            return NRF_ERROR_BUSY;
        }
    }

    // Update flag to indicate that there is no valid private key.
    m_keypair_generated       = false;
    m_lesc_oobd_own_generated = false;

    NRF_LOG_DEBUG("Generating ECC key pair");
    err_code = nrf_crypto_ecc_key_pair_generate(&m_keygen_context,
                                                &g_nrf_crypto_ecc_secp256r1_curve_info,
                                                &m_private_key,
                                                &m_public_key);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("nrf_crypto_ecc_key_pair_generate() returned error 0x%x.", err_code);
        return err_code;
    }

    // Convert to a raw type.
    err_code = nrf_crypto_ecc_public_key_to_raw(&m_public_key,
                                                m_lesc_public_key.pk,
                                                &public_len);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("nrf_crypto_ecc_public_key_to_raw() returned error 0x%x.", err_code);
        return err_code;
    }

    // Invert the raw type to little-endian (required for BLE).
    err_code = nrf_crypto_ecc_byte_order_invert(&g_nrf_crypto_ecc_secp256r1_curve_info,
                                                m_lesc_public_key.pk,
                                                m_lesc_public_key.pk,
                                                NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("nrf_crypto_ecc_byte_order_invert() returned error 0x%x.", err_code);
    }
    else
    {
        // Set the flag to indicate that there is a valid ECDH key pair generated.
        m_keypair_generated = true;
    }

    return err_code;
}


ret_code_t nrf_ble_lesc_own_oob_data_generate(void)
{
    ret_code_t err_code = NRF_ERROR_INVALID_STATE;

    m_lesc_oobd_own_generated = false;

    if (m_keypair_generated)
    {
        err_code = sd_ble_gap_lesc_oob_data_get(BLE_CONN_HANDLE_INVALID,
                                                &m_lesc_public_key,
                                                &m_ble_lesc_oobd_own);
        if (err_code == NRF_SUCCESS)
        {
            m_lesc_oobd_own_generated = true;
        }
    }

    return err_code;
}


ble_gap_lesc_p256_pk_t * nrf_ble_lesc_public_key_get(void)
{
    ble_gap_lesc_p256_pk_t * p_lesc_pk = NULL;

    if (m_keypair_generated)
    {
        p_lesc_pk = &m_lesc_public_key;
    }
    else
    {
        NRF_LOG_ERROR("Trying to access LESC public key that has not been generated yet.");
    }

    return p_lesc_pk;
}


ble_gap_lesc_oob_data_t * nrf_ble_lesc_own_oob_data_get(void)
{
    ble_gap_lesc_oob_data_t * p_lesc_oobd_own = NULL;

    if (m_lesc_oobd_own_generated)
    {
        p_lesc_oobd_own = &m_ble_lesc_oobd_own;
    }
    else
    {
        NRF_LOG_ERROR("Trying to access LESC OOB data that have not been generated yet.");
    }

    return p_lesc_oobd_own;
}


void nrf_ble_lesc_peer_oob_data_handler_set(nrf_ble_lesc_peer_oob_data_handler handler)
{
    m_lesc_oobd_peer_handler = handler;
}


/**@brief Function for calculating a DH key and responding to the DH key request on a given
 *        connection handle.
 *
 * @param[in]  p_peer_public_key  ECC peer public key, used to compute shared secret.
 * @param[in]  conn_handle        Connection handle.
 *
 * @retval NRF_SUCCESS If the operation was successful.
 * @retval Other       Other error codes might be returned by the @ref nrf_crypto_ecdh_compute, @ref
 *                     nrf_crypto_ecc_byte_order_invert, and @ref sd_ble_gap_lesc_dhkey_reply functions.
 */
static ret_code_t compute_and_give_dhkey(nrf_ble_lesc_peer_pub_key_t * p_peer_public_key,
                                         uint16_t                      conn_handle)
{
    ret_code_t err_code           = NRF_ERROR_INTERNAL;
    size_t     shared_secret_size = BLE_GAP_LESC_DHKEY_LEN;
    uint8_t  * p_shared_secret    = m_lesc_dh_key.key;

    // Check if there is a valid generated and set a local ECDH public key.
    if (!m_keypair_generated)
    {
        return NRF_ERROR_INTERNAL;
    }

    // Check if the public_key is valid
    if (p_peer_public_key->is_valid)
    {
        err_code = nrf_crypto_ecdh_compute(&m_ecdh_context,
                                           &m_private_key,
                                           &p_peer_public_key->value,
                                           p_shared_secret,
                                           &shared_secret_size);
    }

    if (err_code == NRF_SUCCESS)
    {
        // Invert the shared secret for little endian format.
        err_code = nrf_crypto_ecc_byte_order_invert(&g_nrf_crypto_ecc_secp256r1_curve_info,
                                                    p_shared_secret,
                                                    p_shared_secret,
                                                    BLE_GAP_LESC_DHKEY_LEN);
        VERIFY_SUCCESS(err_code);
    }
    else
    {
        NRF_LOG_WARNING("Creating invalid shared secret to make LESC fail.");
        err_code = nrf_crypto_rng_vector_generate(p_shared_secret, BLE_GAP_LESC_DHKEY_LEN);
        VERIFY_SUCCESS(err_code);
    }

    NRF_LOG_INFO("Calling sd_ble_gap_lesc_dhkey_reply on conn_handle: %d", conn_handle);
    err_code = sd_ble_gap_lesc_dhkey_reply(conn_handle, &m_lesc_dh_key);

    return err_code;
}


ret_code_t nrf_ble_lesc_request_handler(void)
{
    ret_code_t err_code = NRF_SUCCESS;

    // If the LESC module is in an invalid state, a restart is required.
    if (m_ble_lesc_internal_error)
    {
        return NRF_ERROR_INTERNAL;
    }

    for (uint16_t i = 0; i < NRF_BLE_LESC_LINK_COUNT; i++)
    {
        if (m_peer_keys[i].is_requested)
        {
            err_code                    = compute_and_give_dhkey(&m_peer_keys[i], i);
            m_peer_keys[i].is_requested = false;
            m_peer_keys[i].is_valid     = false;
            VERIFY_SUCCESS(err_code);

        }
    }

    return err_code;
}


/**@brief Function for handling a DH key request event.
 *
 * @param[in]  conn_handle      Connection handle.
 * @param[in]  p_dhkey_request  DH key request descriptor.
 *
 * @retval NRF_SUCCESS      If the operation was successful.
 * @retval Other            Other error codes might be returned by the @ref nrf_crypto_ecc_byte_order_invert
 *                          and @ref nrf_crypto_ecc_public_key_from_raw functions.
 */
static ret_code_t on_dhkey_request(uint16_t                                 conn_handle,
                                   ble_gap_evt_lesc_dhkey_request_t const * p_dhkey_request)
{
    ret_code_t err_code = NRF_SUCCESS;
    uint8_t    public_raw[BLE_GAP_LESC_P256_PK_LEN];
    uint8_t  * p_public_raw;
    size_t     public_raw_len;

    // Convert the received public key from big-endian to little endian.
    p_public_raw   = p_dhkey_request->p_pk_peer->pk;
    public_raw_len = BLE_GAP_LESC_P256_PK_LEN;
    err_code       = nrf_crypto_ecc_byte_order_invert(&g_nrf_crypto_ecc_secp256r1_curve_info,
                                                      p_public_raw,
                                                      public_raw,
                                                      public_raw_len);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("nrf_crypto_ecc_byte_order_invert() returned error 0x%x.", err_code);
        return err_code;
    }

    // Copy peer public key to the allocated context. The dhkey calculation will be performed in
    // @ref nrf_ble_lesc_request_handler, so it does not block normal operation.
    err_code = nrf_crypto_ecc_public_key_from_raw(&g_nrf_crypto_ecc_secp256r1_curve_info,
                                                  &m_peer_keys[conn_handle].value,
                                                  public_raw,
                                                  public_raw_len);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("nrf_crypto_ecc_public_key_from_raw() returned error 0x%x.", err_code);
        m_peer_keys[conn_handle].is_valid = false;
    }
    else
    {
        m_peer_keys[conn_handle].is_valid = true;
    }
    m_peer_keys[conn_handle].is_requested = true;

    return NRF_SUCCESS;
}


/**@brief Function for setting LESC OOB data.
 *
 * @param[in]  conn_handle      Connection handle.
 *
 * @retval NRF_SUCCESS      If the operation was successful.
 * @retval Other            Other error codes might be returned by the @ref sd_ble_gap_lesc_oob_data_set.
 */
static ret_code_t lesc_oob_data_set(uint16_t conn_handle)
{
    ret_code_t                err_code;
    ble_gap_lesc_oob_data_t * p_lesc_oobd_own;
    ble_gap_lesc_oob_data_t * p_lesc_oobd_peer;

    p_lesc_oobd_own  = (m_lesc_oobd_own_generated) ? &m_ble_lesc_oobd_own : NULL;
    p_lesc_oobd_peer = (m_lesc_oobd_peer_handler != NULL) ?
                        m_lesc_oobd_peer_handler(conn_handle) : NULL;

    err_code = sd_ble_gap_lesc_oob_data_set(conn_handle,
                                            p_lesc_oobd_own,
                                            p_lesc_oobd_peer);
    return err_code;
}


void nrf_ble_lesc_on_ble_evt(ble_evt_t const * p_ble_evt)
{
    ret_code_t err_code    = NRF_SUCCESS;
    uint16_t   conn_handle = p_ble_evt->evt.gap_evt.conn_handle;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_DISCONNECTED:
            m_peer_keys[conn_handle].is_valid     = false;
            m_peer_keys[conn_handle].is_requested = false;
            break;

        case BLE_GAP_EVT_LESC_DHKEY_REQUEST:
            NRF_LOG_DEBUG("BLE_GAP_EVT_LESC_DHKEY_REQUEST");

            if (p_ble_evt->evt.gap_evt.params.lesc_dhkey_request.oobd_req)
            {
                err_code = lesc_oob_data_set(conn_handle);
                if (err_code != NRF_SUCCESS)
                {
                    NRF_LOG_ERROR("sd_ble_gap_lesc_oob_data_set() returned error 0x%x.", err_code);
                    m_ble_lesc_internal_error = true;
                }
            }

            err_code = on_dhkey_request(conn_handle,
                                        &p_ble_evt->evt.gap_evt.params.lesc_dhkey_request);
            if (err_code != NRF_SUCCESS)
            {
                m_ble_lesc_internal_error = true;
            }
            break;

        default:
            break;
    }
}


#endif // NRF_BLE_LESC_ENABLED
