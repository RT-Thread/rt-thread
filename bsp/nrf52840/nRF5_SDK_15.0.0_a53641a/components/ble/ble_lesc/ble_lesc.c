/**
 * Copyright (c) 2018 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(BLE_LESC)

#include "sdk_common.h"
#include "ble_gap.h"
#include "ble_lesc.h"
#include "nrf_crypto.h"
#include "nrf_crypto_mem.h"
#include "peer_manager.h"
#include "nrf_sdh_ble.h"
#include "ble_conn_state.h"
#define NRF_LOG_MODULE_NAME ble_lesc
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief Structure holding a ECDH public key, connection handle and valid state */
typedef struct
{
    nrf_crypto_ecc_public_key_t     public_key;     /**< Public key used in either central or peripheral link. */
    volatile uint16_t               conn_handle;    /**< Connection handle for connection that received the public key. */
    volatile bool                   is_valid;       /**< Flag indicating that the public key was valid. */
} ble_lesc_public_key_t;

/**@brief Context to generate an ECC private/public key pair
 */
static nrf_crypto_ecc_key_pair_generate_context_t   m_ecc_keygen_context;


/**@brief Context to do the LESC ECDH calculation.
 */
static nrf_crypto_ecdh_context_t                    m_ecdh_context;


/**@brief Private key to use for LESC ECDH calculations
 */
static nrf_crypto_ecc_private_key_t                 m_local_private_key;


/**@brief Public key to use for LESC ECDH calculation
 */
static ble_lesc_public_key_t                        m_local_public_key;


/**@brief Structure holding peer central LESC ECC public key and valid state
 */
static ble_lesc_public_key_t                        m_peer_public_key_central =
{
    .conn_handle = BLE_CONN_HANDLE_INVALID,
    .is_valid = false
};


/**@brief Structure holding peer peripheral LESC ECC public key and valid state
 */
static ble_lesc_public_key_t                        m_peer_public_key_peripheral =
{
    .conn_handle = BLE_CONN_HANDLE_INVALID,
    .is_valid = false
};

/**@brief LESC ECC public key in a format usable by SoftDevice APIs. 
 * 
 * @note The BLE specification requires this key to be in little-endian format.
 */
static ble_gap_lesc_p256_pk_t                       m_lesc_public_key;


/**@brief LESC ECDH key in a format usable by SoftDevice APIs.
 *
 * @note The BLE specification requires this key to be in little-endian format.
 */
static ble_gap_lesc_dhkey_t                         m_lesc_ecdh_key;


static bool m_ble_lesc_invalid_state = false;
static bool m_keypair_generated = false;  /**< Flag indicating that the local ECDH key pair was generated. */


static void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context);
NRF_SDH_BLE_OBSERVER(m_ble_evt_observer, BLE_LESC_OBSERVER_PRIO, ble_evt_handler, NULL);


/**@brief Function to calculate LESC ECDH and set it using SoftDevice API
 *
 * @details This function calculates a LESC ECDH key (also know as a shared secret) 
  *         sets it using a call to @ref sd_ble_gap_lesc_dhkey_reply.
 *
 * @note This function will only work if there is a generated local ECC key pair (private and
 *       public key pair) and a valid ECC public key received from the peer on either a peripheral
 *       or central link. If the ECC public key from the peer is invalid, a random shared secret 
 *       is generated and set using the @ref sd_ble_gap_lesc_dhkey_reply call.
 *
 * @warning     This function must be run in a low interrupt priority, like the main
 *              application context. Running this in a high priority interrupt level
 *              may disrupt time critical operations like radio communications.
 *
 * @retval
 */
static ret_code_t ble_lesc_dhkey_calculate_and_set(ble_lesc_public_key_t * const p_peer_public_key)
{
    ret_code_t  err_code            = NRF_ERROR_INVALID_STATE;
    size_t      shared_secret_size  = BLE_GAP_LESC_DHKEY_LEN;
    
    uint8_t *   p_shared_secret = m_lesc_ecdh_key.key;
    
    // Check if there is a valid generated and set local ECDH public key
    if (!m_keypair_generated)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    
    // Check if the public_key is valid
    if (p_peer_public_key->is_valid)
    {
        err_code = nrf_crypto_ecdh_compute(&m_ecdh_context,
                                           &m_local_private_key,
                                           &p_peer_public_key->public_key,
                                           p_shared_secret,
                                           &shared_secret_size);
    }

    if(err_code == NRF_SUCCESS)
    {
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

    NRF_LOG_DEBUG("Calling sd_ble_gap_lesc_dhkey_reply on conn_handle: %d", p_peer_public_key->conn_handle);
    err_code = sd_ble_gap_lesc_dhkey_reply(p_peer_public_key->conn_handle, &m_lesc_ecdh_key);

    return err_code;
}


/**@brief Function to set the peer ECC public key for a peripheral link
 *
 * @details This call should be made to 
 *
 * @param[in]   conn_handle     The connection handle to the peripheral connection.
 * @param[in]   p_public_key    Pointer to structure holding the public key received from the peer.
 *
 * @retval 
 */
static ret_code_t ble_lesc_peer_peripheral_public_key_set(
    uint16_t conn_handle, 
    ble_gap_lesc_p256_pk_t const * const p_public_key)
{
    ret_code_t  err_code;

    uint8_t     public_raw[BLE_GAP_LESC_P256_PK_LEN];
    size_t      public_raw_len  = BLE_GAP_LESC_P256_PK_LEN;
    
    VERIFY_TRUE(conn_handle != BLE_CONN_HANDLE_INVALID, NRF_ERROR_INVALID_PARAM);
    VERIFY_PARAM_NOT_NULL(p_public_key);
    
    memcpy(public_raw, p_public_key->pk, BLE_GAP_LESC_P256_PK_LEN);
    
    err_code = nrf_crypto_ecc_byte_order_invert(&g_nrf_crypto_ecc_secp256r1_curve_info,
                                                public_raw,
                                                public_raw,
                                                NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE);
    VERIFY_SUCCESS(err_code); 
    
    
    err_code = nrf_crypto_ecc_public_key_from_raw(&g_nrf_crypto_ecc_secp256r1_curve_info,
                                                  &m_peer_public_key_peripheral.public_key,
                                                  public_raw,
                                                  public_raw_len);

    if (err_code == NRF_SUCCESS)
    {
        m_peer_public_key_peripheral.is_valid = true;
    }
    else
    {
        m_peer_public_key_peripheral.is_valid = false;
    }

    m_peer_public_key_peripheral.conn_handle = conn_handle;

    return NRF_SUCCESS;
}

/**@brief Function to set peer ECC public key for a central link
 *
 * @details Setting the peer ECC public key will start a 
 *
 * @param[in]   conn_handle     The connection handle to the peripheral connection.
 * @param[in]   p_public_key    Pointer to structure holding the public key received from the peer.
 *
 * @retval 
 */
static ret_code_t ble_lesc_peer_central_public_key_set(
    uint16_t conn_handle, 
    ble_gap_lesc_p256_pk_t const * const p_public_key)
{
    ret_code_t err_code;

    uint8_t     public_raw[BLE_GAP_LESC_P256_PK_LEN];
    size_t      public_raw_len  = BLE_GAP_LESC_P256_PK_LEN;
    
    VERIFY_TRUE(conn_handle != BLE_CONN_HANDLE_INVALID, NRF_ERROR_INVALID_PARAM);
    VERIFY_PARAM_NOT_NULL(p_public_key);
    
    memcpy(public_raw, p_public_key->pk, BLE_GAP_LESC_P256_PK_LEN);
    
    err_code = nrf_crypto_ecc_byte_order_invert(&g_nrf_crypto_ecc_secp256r1_curve_info,
                                                public_raw,
                                                public_raw,
                                                NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE);
    VERIFY_SUCCESS(err_code); 
    
    err_code = nrf_crypto_ecc_public_key_from_raw(&g_nrf_crypto_ecc_secp256r1_curve_info,
                                                  &m_peer_public_key_central.public_key,
                                                  public_raw,
                                                  public_raw_len);

    if (err_code == NRF_SUCCESS)
    {
        m_peer_public_key_central.is_valid = true;
    }
    else
    {
        m_peer_public_key_central.is_valid = false;
    }

    m_peer_public_key_central.conn_handle = conn_handle;

    return NRF_SUCCESS;
}


/**@brief BLE event handler for LESC DHKEY requests
 */
static void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context)
{
    ret_code_t  err_code = NRF_SUCCESS;
    uint16_t    conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
    uint16_t    role        = ble_conn_state_role(conn_handle);
    
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_LESC_DHKEY_REQUEST:
        {
            NRF_LOG_DEBUG("Handling BLE_GAP_EVT_LESC_DHKEY_REQUEST");
        
            ble_gap_lesc_p256_pk_t const * p_pk_peer = 
                p_ble_evt->evt.gap_evt.params.lesc_dhkey_request.p_pk_peer;
        
            if (role == BLE_GAP_ROLE_CENTRAL)
            {        
                err_code = ble_lesc_peer_central_public_key_set(conn_handle, 
                                                                p_pk_peer);
            }
            else if (role == BLE_GAP_ROLE_PERIPH)
            {
                err_code = ble_lesc_peer_peripheral_public_key_set(conn_handle, 
                                                                   p_pk_peer);
            }
            
            if (err_code != NRF_SUCCESS)
            {
                // Set the state to invalid
                m_ble_lesc_invalid_state = true;
            }
            
            break;
        }
        
        default:
            break;
    }
}


ret_code_t ble_lesc_init(void)
{
    ret_code_t err_code;
    
#if NRF_CRYPTO_ALLOCATOR == NRF_CRYPTO_ALLOCATOR_NRF_MALLOC

    // Initialize mem_manager if used by nrf_crypto
    err_code = nrf_mem_init();
    VERIFY_SUCCESS(err_code);
    
#endif
    
    // Ensure that nrf_crypto has been initialized
    err_code = nrf_crypto_init();
    VERIFY_SUCCESS(err_code);

#if defined(NRF_CRYPTO_RNG_AUTO_INIT_ENABLED) && (NRF_CRYPTO_RNG_AUTO_INIT_ENABLED == 1)

    // Do nothing. RNG is initialized with nrf_crypto_init call.

#elif defined((NRF_CRYPTO_RNG_AUTO_INIT_ENABLED) && (NRF_CRYPTO_RNG_AUTO_INIT_ENABLED == 0)

    // Initialize the RNG
    err_code = nrf_crypto_rng_init(NULL, NULL);
    VERIFY_SUCCESS(err_code);

#else

    #error Invalid sdk_config.h (does not contain NRF_CRYPTO_RNG_AUTO_INIT_ENABLED)
        
#endif // defined(NRF_CRYPTO_RNG_AUTO_INIT_ENABLED) && (NRF_CRYPTO_RNG_AUTO_INIT_ENABLED == 1)
    
    return err_code;
}


ret_code_t ble_lesc_ecc_keypair_generate_and_set(void)
{
    ret_code_t  err_code;
    
    size_t      public_len = BLE_GAP_LESC_P256_PK_LEN;
    
    // Update flag to indicate that there is no valid private key
    m_keypair_generated = false;

    err_code = nrf_crypto_ecc_key_pair_generate(&m_ecc_keygen_context,
                                                &g_nrf_crypto_ecc_secp256r1_curve_info,
                                                &m_local_private_key,
                                                &m_local_public_key.public_key);
    VERIFY_SUCCESS(err_code);
    
    // Converting public key to raw format.
    err_code = nrf_crypto_ecc_public_key_to_raw(&m_local_public_key.public_key, 
                                                (uint8_t *)m_lesc_public_key.pk, 
                                                &public_len);
    VERIFY_SUCCESS(err_code);
    
    // Convert the raw public key to little-endian (required for BLE)
    err_code = nrf_crypto_ecc_byte_order_invert(&g_nrf_crypto_ecc_secp256r1_curve_info, 
                                                m_lesc_public_key.pk, 
                                                m_lesc_public_key.pk, 
                                                NRF_CRYPTO_ECC_SECP256R1_RAW_PUBLIC_KEY_SIZE);
    VERIFY_SUCCESS(err_code);
    
    // Set the local public key used for all LESC pairing procedures.
    err_code = pm_lesc_public_key_set(&m_lesc_public_key);
    
    if(err_code == NRF_SUCCESS)
    {
        // Set the flag to indicate that there is a valid ECDH key pair generated
        m_keypair_generated = true;
    }
    
    return err_code;
}


ret_code_t ble_lesc_ecc_local_public_key_get(ble_gap_lesc_p256_pk_t const ** pp_lesc_public_key)
{
    VERIFY_PARAM_NOT_NULL(pp_lesc_public_key);
    VERIFY_TRUE(m_keypair_generated, NRF_ERROR_INVALID_STATE);
    
    (*pp_lesc_public_key) = &m_lesc_public_key;
    return NRF_SUCCESS;
}


ret_code_t ble_lesc_service_request_handler(void)
{
    ret_code_t err_code = NRF_SUCCESS;
    
    // If the LESC module is in an invalid state restart is required
    if (m_ble_lesc_invalid_state)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    
    if (m_peer_public_key_central.conn_handle != BLE_CONN_HANDLE_INVALID)
    {
        // The central link has received a DHKEY_REQUEST.
        err_code = ble_lesc_dhkey_calculate_and_set(&m_peer_public_key_central);
        
        m_peer_public_key_central.conn_handle = BLE_CONN_HANDLE_INVALID;
    }
    else if (m_peer_public_key_peripheral.conn_handle != BLE_CONN_HANDLE_INVALID)
    {
        // The peripheral link has received a DHKEY_REQUEST.
        err_code = ble_lesc_dhkey_calculate_and_set(&m_peer_public_key_peripheral);
        
        m_peer_public_key_peripheral.conn_handle = BLE_CONN_HANDLE_INVALID;
    }
    else
    {
        // Do nothing
    }
    
    return err_code;
}

#endif // NRF_MODULE_ENABLED(BLE_LESC)
