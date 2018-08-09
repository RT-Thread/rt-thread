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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NFC_BLE_PAIR_LIB)

#include "nfc_ble_pair_lib.h"
#include "sdk_macros.h"
#include "app_error.h"
#include "nrf_drv_rng.h"
#include "nfc_t2t_lib.h"
#include "nfc_ble_pair_msg.h"
#include "ecc.h"
#include "nrf_sdh_ble.h"

#define NRF_LOG_MODULE_NAME nfc_ble_pair
#if NFC_BLE_PAIR_LIB_LOG_ENABLED
#define NRF_LOG_LEVEL       NFC_BLE_PAIR_LIB_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NFC_BLE_PAIR_LIB_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR NFC_BLE_PAIR_LIB_DEBUG_COLOR
#else // NFC_BLE_PAIR_LIB_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // NFC_BLE_PAIR_LIB_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

// Verify bonding and keys distribution settings.
#if ((BLE_NFC_SEC_PARAM_BOND)           &&  \
    !(BLE_NFC_SEC_PARAM_KDIST_OWN_ENC)  &&  \
    !(BLE_NFC_SEC_PARAM_KDIST_OWN_ID)   &&  \
    !(BLE_NFC_SEC_PARAM_KDIST_PEER_ENC) &&  \
    !(BLE_NFC_SEC_PARAM_KDIST_PEER_ID))
    #error "At least one of the BLE_NFC_SEC_PARAM_KDIST flags must be set to 1 when bonding is enabled."
#endif

// Macro for verifying if the pairing mode argument is valid
#define VERIFY_PAIRING_MODE(arg)         \
    if ((arg) >= NFC_PAIRING_MODE_CNT)    \
    {                                    \
        return NRF_ERROR_INVALID_PARAM;  \
    }

#define BLE_GAP_LESC_P256_SK_LEN        32                              /**< GAP LE Secure Connections Elliptic Curve Diffie-Hellman P-256 Secret Key Length. */
#define TK_MAX_NUM                      1                               /**< Maximal number of TK locations in NDEF message buffer. */
#define NDEF_MSG_BUFF_SIZE              256                             /**< Size of buffer for the NDEF pairing message. */

#define BLE_NFC_SEC_PARAM_KEYPRESS      0                               /**< Keypress notifications not enabled. */
#define BLE_NFC_SEC_PARAM_IO_CAPS       BLE_GAP_IO_CAPS_NONE            /**< No I/O capabilities. */

typedef struct
{
    uint8_t sk[BLE_GAP_LESC_P256_SK_LEN];                               /**< LE Secure Connections Elliptic Curve Diffie-Hellman P-256 Secret Key. */
} ble_gap_lesc_p256_sk_t;

static ble_advertising_t *       m_p_advertising = NULL;                /**< Pointer to the advertising module instance. */

static uint8_t                   m_ndef_msg_buf[NDEF_MSG_BUFF_SIZE];    /**< NFC tag NDEF message buffer. */
static ble_advdata_tk_value_t    m_oob_auth_key;                        /**< Temporary Key buffer used in OOB legacy pairing mode. */
static uint8_t *                 m_tk_group[TK_MAX_NUM];                /**< Locations of TK in NDEF message. */
static nfc_pairing_mode_t        m_pairing_mode;                        /**< Current pairing mode. */
static ble_gap_lesc_oob_data_t   m_ble_lesc_oob_data;                   /**< LESC OOB data used in LESC OOB pairing mode. */
static ble_gap_sec_params_t      m_sec_param;                           /**< Current Peer Manager secure parameters configuration. */

static uint8_t                   m_connections = 0;                     /**< Number of active connections. */

__ALIGN(4) static ble_gap_lesc_p256_pk_t m_lesc_pk;                     /**< LESC ECC Public Key. */
__ALIGN(4) static ble_gap_lesc_p256_sk_t m_lesc_sk;                     /**< LESC ECC Secret Key. */
__ALIGN(4) static ble_gap_lesc_dhkey_t   m_lesc_dhkey;                  /**< LESC ECC DH Key. */
__ALIGN(4) static ble_gap_lesc_p256_pk_t m_lesc_peer_pk;                /**< LESC Peer ECC Public Key. */


static void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context);

NRF_SDH_BLE_OBSERVER(m_ble_evt_observer, NFC_BLE_PAIR_LIB_BLE_OBSERVER_PRIO, ble_evt_handler, NULL);

/**
 * @brief Generates random values to a given buffer
 *
 * @param[out] p_buff Buffer for random values
 * @param[in]  size   Number of bytes to generate
 *
 * @returns    Number of generated bytes
 */
static uint8_t random_vector_generate(uint8_t * p_buff, uint8_t size)
{
    uint8_t    available;
    ret_code_t err_code = NRF_SUCCESS;

    nrf_drv_rng_bytes_available(&available);

    uint8_t length = (size < available) ? size : available;
    err_code = nrf_drv_rng_rand(p_buff, length);
    APP_ERROR_CHECK(err_code);
    return length;
}

/**
 * @brief Prints generated key to the log console
 *
 * @param[in] lenght TK value length
 */
static void random_vector_log(uint8_t length)
{
    NRF_LOG_INFO("TK Random Value:");
    for (uint32_t i = 0; i < length; i++)
    {
        NRF_LOG_RAW_INFO(" %02X",(int)m_oob_auth_key.tk[i]);
    }
    NRF_LOG_RAW_INFO("\r\n");
}

/**
 * @brief Function for handling NFC events.
 *
 * @details Starts advertising and generates new OOB keys on the NFC_T2T_EVENT_FIELD_ON event.
 *
 * @param[in] p_context    Context for callback execution, not used in this callback implementation.
 * @param[in] event        Event generated by hal NFC lib.
 * @param[in] p_data       Received/transmitted data or NULL, not used in this callback implementation.
 * @param[in] data_length  Size of the received/transmitted packet, not used in this callback implementation.
 */
static void nfc_callback(void            * p_context,
                         nfc_t2t_event_t   event,
                         uint8_t const   * p_data,
                         size_t            data_length)
{
    UNUSED_PARAMETER(p_context);
    UNUSED_PARAMETER(p_data);
    UNUSED_PARAMETER(data_length);

    ret_code_t         err_code = NRF_SUCCESS;
    nfc_pairing_mode_t pairing_mode;

    switch (event)
    {
        case NFC_T2T_EVENT_FIELD_ON:
            NRF_LOG_DEBUG("NFC_EVENT_FIELD_ON");

            pairing_mode = nfc_ble_pair_mode_get();

            if ((pairing_mode == NFC_PAIRING_MODE_OOB) ||
                (pairing_mode == NFC_PAIRING_MODE_GENERIC_OOB))
            {
                // Generate Authentication OOB Key and update NDEF message content.
                uint8_t length = random_vector_generate(m_oob_auth_key.tk, BLE_GAP_SEC_KEY_LEN);
                random_vector_log(length);
                err_code = nfc_tk_group_modifier_update(&m_oob_auth_key);
                APP_ERROR_CHECK(err_code);
            }

            // Start advertising when NFC field is sensed and there is a place for another connection.
            if (m_connections < NRF_SDH_BLE_PERIPHERAL_LINK_COUNT)
            {
                err_code = ble_advertising_start(m_p_advertising, BLE_ADV_MODE_FAST);
                if (err_code != NRF_ERROR_INVALID_STATE)
                {
                    APP_ERROR_CHECK(err_code);
                }
            }

            break;

        case NFC_T2T_EVENT_FIELD_OFF:
            NRF_LOG_DEBUG("NFC_EVENT_FIELD_OFF");
            break;

        default:
            break;
    }
}

/**
 * @brief Function for setting the Peer Manager secure mode used in device pairing.
 *
 * @param[in] mode                  NFC pairing mode, this is the value of @ref nfc_pairing_mode_t enum
 *
 * @retval NRF_SUCCESS              If new secure mode has been set correctly.
 * @retval NRF_ERROR_INVALID_PARAM  If pairing mode is invalid.
 * @retval Other                    Other error codes might be returned depending on used modules.
 */
static ret_code_t pm_secure_mode_set(nfc_pairing_mode_t mode)
{
    ret_code_t           err_code = NRF_SUCCESS;

    // Check if pairing mode is valid.
    VERIFY_PAIRING_MODE(mode);

    memset(&m_sec_param, 0x00, sizeof(m_sec_param));

    // Pairing mode specific security parameters.
    switch (mode)
    {
        case NFC_PAIRING_MODE_JUST_WORKS:
            // Disable pairing with OOB data.
            m_sec_param.mitm = 0;
            m_sec_param.oob  = 0;
            m_sec_param.lesc = 0;
            break;

        case NFC_PAIRING_MODE_OOB:
            // Enable legacy pairing with OOB data - TK value.
            m_sec_param.mitm  = 1;
            m_sec_param.oob   = 1;
            m_sec_param.lesc  = 0;
            break;

        case NFC_PAIRING_MODE_LESC_OOB:
        case NFC_PAIRING_MODE_LESC_JUST_WORKS:
            // Enable LESC pairing - OOB and MITM flags are cleared because it is the central device
            // who decides if the connection will be authorized with LESC OOB data.
            m_sec_param.mitm  = 0;
            m_sec_param.oob   = 0;
            m_sec_param.lesc  = 1;
            break;

        case NFC_PAIRING_MODE_GENERIC_OOB:
            // MITM, OOB and LESC flags are changing dynamically depending on central device pairing flags.
            break;

        default:
            return NRF_ERROR_INVALID_PARAM;
    }

    // Common security parameters to be used for all security procedures.
    m_sec_param.min_key_size   = BLE_NFC_SEC_PARAM_MIN_KEY_SIZE;
    m_sec_param.max_key_size   = BLE_NFC_SEC_PARAM_MAX_KEY_SIZE;
    m_sec_param.keypress       = BLE_NFC_SEC_PARAM_KEYPRESS;
    m_sec_param.io_caps        = BLE_NFC_SEC_PARAM_IO_CAPS;
    m_sec_param.bond           = BLE_NFC_SEC_PARAM_BOND;

#if (BLE_NFC_SEC_PARAM_BOND)
    // If bonding is enabled, set key distribution flags.
    m_sec_param.kdist_own.enc  = BLE_NFC_SEC_PARAM_KDIST_OWN_ENC;
    m_sec_param.kdist_own.id   = BLE_NFC_SEC_PARAM_KDIST_OWN_ID;
    m_sec_param.kdist_peer.enc = BLE_NFC_SEC_PARAM_KDIST_PEER_ENC;
    m_sec_param.kdist_peer.id  = BLE_NFC_SEC_PARAM_KDIST_PEER_ID;
#else
    // If bonding is not enabled, no keys can be distributed.
    m_sec_param.kdist_own.enc  = 0;
    m_sec_param.kdist_own.id   = 0;
    m_sec_param.kdist_peer.enc = 0;
    m_sec_param.kdist_peer.id  = 0;
#endif

    // Update Peer Manager security parameter settings.
    err_code = pm_sec_params_set(&m_sec_param);

    return err_code;
}


 /**@brief Function for preparing the BLE pairing data for the NFC tag.
 *
 * @details This function does not stop and start the NFC tag data emulation.
 *
 * @param[in] mode Pairing mode for which the tag data will be prepared.
 *
 * @retval NRF_SUCCESS              If new tag pairing data has been set correctly.
 * @retval NRF_ERROR_INVALID_PARAM  If pairing mode is invalid.
 * @retval Other                    Other error codes might be returned depending on used modules.
 */
ret_code_t nfc_ble_pair_data_set(nfc_pairing_mode_t mode)
{
    ret_code_t err_code = NRF_SUCCESS;

    // Check if pairing mode is valid
    VERIFY_PAIRING_MODE(mode);

    // Provide information about available buffer size to encoding function.
    uint32_t ndef_msg_len = sizeof(m_ndef_msg_buf);

    switch (mode)
    {
        case NFC_PAIRING_MODE_OOB:
            // Encode NDEF message with Secure Simple Pairing OOB optional data - TK value.
            err_code = nfc_ble_pair_msg_updatable_tk_encode(NFC_BLE_PAIR_MSG_BLUETOOTH_LE_SHORT,
                                                            &m_oob_auth_key,
                                                            NULL,
                                                            m_ndef_msg_buf,
                                                            &ndef_msg_len,
                                                            m_tk_group,
                                                            TK_MAX_NUM);
            break;

        case NFC_PAIRING_MODE_JUST_WORKS:
            // Encode NDEF message with Secure Simple Pairing OOB data.
            err_code = nfc_ble_pair_default_msg_encode(NFC_BLE_PAIR_MSG_BLUETOOTH_LE_SHORT,
                                                       NULL,
                                                       NULL,
                                                       m_ndef_msg_buf,
                                                       &ndef_msg_len);
            break;

        case NFC_PAIRING_MODE_LESC_OOB:
            // Generate LESC OOB data
            err_code = sd_ble_gap_lesc_oob_data_get(BLE_CONN_HANDLE_INVALID,
                                                    &m_lesc_pk,
                                                    &m_ble_lesc_oob_data);
            VERIFY_SUCCESS(err_code);

            // Encode NDEF message with BLE LESC OOB pairing data -  LESC random and confirmation values.
            err_code = nfc_ble_pair_default_msg_encode(NFC_BLE_PAIR_MSG_BLUETOOTH_LE_SHORT,
                                                       NULL,
                                                       &m_ble_lesc_oob_data,
                                                       m_ndef_msg_buf,
                                                       &ndef_msg_len);
            break;

        case NFC_PAIRING_MODE_LESC_JUST_WORKS:
            err_code = nfc_ble_pair_default_msg_encode(NFC_BLE_PAIR_MSG_BLUETOOTH_LE_SHORT,
                                                       NULL,
                                                       NULL,
                                                       m_ndef_msg_buf,
                                                       &ndef_msg_len);
            break;

        case NFC_PAIRING_MODE_GENERIC_OOB:
            // Generate LESC OOB data
            err_code = sd_ble_gap_lesc_oob_data_get(BLE_CONN_HANDLE_INVALID,
                                                    &m_lesc_pk,
                                                    &m_ble_lesc_oob_data);
            VERIFY_SUCCESS(err_code);

            // Encode NDEF message with Secure Simple Pairing OOB data - TK value and LESC Random and Confirmation Keys.
            err_code = nfc_ble_pair_msg_updatable_tk_encode(NFC_BLE_PAIR_MSG_BLUETOOTH_LE_SHORT,
                                                            &m_oob_auth_key,
                                                            &m_ble_lesc_oob_data,
                                                            m_ndef_msg_buf,
                                                            &ndef_msg_len,
                                                            m_tk_group,
                                                            TK_MAX_NUM);
            break;

        default:
            return NRF_ERROR_INVALID_PARAM;
    }

    VERIFY_SUCCESS(err_code);

    // Update NFC tag data
    err_code = nfc_t2t_payload_set(m_ndef_msg_buf, ndef_msg_len);

    return err_code;
}

ret_code_t nfc_ble_pair_init(ble_advertising_t * const p_advertising, nfc_pairing_mode_t mode)
{
    ret_code_t err_code = NRF_SUCCESS;

    // Check if pairing mode is valid
    VERIFY_PAIRING_MODE(mode);

    // Check if pointer to the advertising module instance is not NULL
    VERIFY_PARAM_NOT_NULL(p_advertising);
    
    m_p_advertising = p_advertising;
    m_pairing_mode = mode;

    // Initialize RNG peripheral for authentication OOB data generation
    err_code = nrf_drv_rng_init(NULL);
    if (err_code != NRF_ERROR_INVALID_STATE)
    {
        VERIFY_SUCCESS(err_code);
    }

    // Initialize encryption module with random number generator use
    ecc_init(true);

    // Start NFC
    err_code = nfc_t2t_setup(nfc_callback, NULL);
    VERIFY_SUCCESS(err_code);

    // Set Peer Manager pairing mode
    err_code = pm_secure_mode_set(mode);
    VERIFY_SUCCESS(err_code);

    if ((mode == NFC_PAIRING_MODE_LESC_OOB) ||
        (mode == NFC_PAIRING_MODE_LESC_JUST_WORKS) ||
        (mode == NFC_PAIRING_MODE_GENERIC_OOB))
    {
        // Generate new LESC keys
        err_code = ecc_p256_keypair_gen(m_lesc_sk.sk, m_lesc_pk.pk);
        VERIFY_SUCCESS(err_code);

        // Update Peer Manager with new LESC Public Key
        err_code = pm_lesc_public_key_set(&m_lesc_pk);
        VERIFY_SUCCESS(err_code);
    }

    // Set proper NFC data according to the pairing mode
    err_code = nfc_ble_pair_data_set(mode);
    VERIFY_SUCCESS(err_code);

    // Turn on tag emulation
    err_code = nfc_t2t_emulation_start();

    return err_code;
}

ret_code_t nfc_ble_pair_mode_set(nfc_pairing_mode_t mode)
{
    ret_code_t err_code = NRF_SUCCESS;

    // Check if pairing mode is valid
    VERIFY_PAIRING_MODE(mode);

    if (mode != m_pairing_mode)
    {
        m_pairing_mode = mode;

        if ((mode == NFC_PAIRING_MODE_LESC_OOB) ||
            (mode == NFC_PAIRING_MODE_LESC_JUST_WORKS) ||
            (mode == NFC_PAIRING_MODE_GENERIC_OOB))
        {
            // Generate new LESC keys
            err_code = ecc_p256_keypair_gen(m_lesc_sk.sk, m_lesc_pk.pk);
            VERIFY_SUCCESS(err_code);

            // Update Peer Manager with new LESC Public Key
            err_code = pm_lesc_public_key_set(&m_lesc_pk);
            VERIFY_SUCCESS(err_code);
        }

        // Update Peer Manager settings according to the new pairing mode
        err_code = pm_secure_mode_set(mode);
        VERIFY_SUCCESS(err_code);

        // NFC tag emulation must be turned off during changes in payload
        err_code = nfc_t2t_emulation_stop();
        VERIFY_SUCCESS(err_code);

        // Update NFC tag data
        err_code = nfc_ble_pair_data_set(mode);
        VERIFY_SUCCESS(err_code);

        // Turn on tag emulation after changes
        err_code = nfc_t2t_emulation_start();
        VERIFY_SUCCESS(err_code);
    }

    return NRF_SUCCESS;
}

nfc_pairing_mode_t nfc_ble_pair_mode_get(void)
{
    return m_pairing_mode;
}

/**
 * @brief   Generates new key pair for LESC pairing.
 *
 * @details If device is in the @ref NFC_PAIRING_MODE_LESC_OOB mode or in
 *          the @ref NFC_PAIRING_MODE_GENERIC_OOB mode, NFC Connection Handover
 *          message is also updated with newly generated LESC OOB data.
 *
 * @retval  NRF_SUCCESS If new tag pairing data has been set correctly.
 * @retval  Other       Other error codes might be returned depending on used modules.
 */
static ret_code_t generate_lesc_keys(void)
{
    ret_code_t err_code = NRF_SUCCESS;

    // Generate new LESC keys
    err_code = ecc_p256_keypair_gen(m_lesc_sk.sk, m_lesc_pk.pk);
    VERIFY_SUCCESS(err_code);

    // Update Peer Manager with new LESC Public Key
    err_code = pm_lesc_public_key_set(&m_lesc_pk);
    VERIFY_SUCCESS(err_code);

    if ((m_pairing_mode == NFC_PAIRING_MODE_LESC_OOB) ||
        (m_pairing_mode == NFC_PAIRING_MODE_GENERIC_OOB))
    {
        // Generate LESC OOB data.
        err_code = sd_ble_gap_lesc_oob_data_get(BLE_CONN_HANDLE_INVALID,
                                                &m_lesc_pk,
                                                &m_ble_lesc_oob_data);
        VERIFY_SUCCESS(err_code);

        // Update NDEF message with new LESC OOB data.
        err_code = nfc_lesc_data_update(&m_ble_lesc_oob_data);
        VERIFY_SUCCESS(err_code);
    }

    return NRF_SUCCESS;
}

/**
 * @brief Function for handling BLE events.
 *
 * @param[in]   p_ble_evt       Event received from the BLE stack.
 * @param[in]   p_context       Context.
 */
static void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context)
{
    ret_code_t err_code = NRF_SUCCESS;

    switch (p_ble_evt->header.evt_id)
    {
        // Upon authorization key request, reply with Temporary Key that was read from the NFC tag
        case BLE_GAP_EVT_AUTH_KEY_REQUEST:
            NRF_LOG_DEBUG("BLE_GAP_EVT_AUTH_KEY_REQUEST");

            err_code = sd_ble_gap_auth_key_reply(p_ble_evt->evt.gap_evt.conn_handle,
                                                 BLE_GAP_AUTH_KEY_TYPE_OOB,
                                                 m_oob_auth_key.tk);
            APP_ERROR_CHECK(err_code);
            break;

        // Upon LESC Diffie_Hellman key request, reply with key computed from device secret key and peer public key
        case BLE_GAP_EVT_LESC_DHKEY_REQUEST:
            NRF_LOG_DEBUG("BLE_GAP_EVT_LESC_DHKEY_REQUEST");

            // If LESC OOB pairing is on, perform authentication with OOB data
            if (p_ble_evt->evt.gap_evt.params.lesc_dhkey_request.oobd_req)
            {
                err_code = sd_ble_gap_lesc_oob_data_set(p_ble_evt->evt.gap_evt.conn_handle,
                                                        &m_ble_lesc_oob_data,
                                                        NULL);
                APP_ERROR_CHECK(err_code);
            }

            // Buffer peer Public Key because ECC module arguments must be word aligned
            memcpy(&m_lesc_peer_pk.pk[0],
                   &p_ble_evt->evt.gap_evt.params.lesc_dhkey_request.p_pk_peer->pk[0],
                   BLE_GAP_LESC_P256_PK_LEN);

            // Compute D-H key
            err_code = ecc_p256_shared_secret_compute(&m_lesc_sk.sk[0],
                                                      &m_lesc_peer_pk.pk[0],
                                                      &m_lesc_dhkey.key[0]);
            APP_ERROR_CHECK(err_code);

            // Reply with obtained result
            err_code = sd_ble_gap_lesc_dhkey_reply(p_ble_evt->evt.gap_evt.conn_handle,
                                                   &m_lesc_dhkey);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_GAP_EVT_CONNECTED:
            m_connections++;
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            m_connections--;
            // Intentional fallthrough.

        case BLE_GAP_EVT_AUTH_STATUS:
            // Generate new LESC key pair and OOB data
            if ((m_pairing_mode == NFC_PAIRING_MODE_LESC_OOB) ||
                (m_pairing_mode == NFC_PAIRING_MODE_LESC_JUST_WORKS) ||
                (m_pairing_mode == NFC_PAIRING_MODE_GENERIC_OOB))
            {
                err_code = generate_lesc_keys();
                APP_ERROR_CHECK(err_code);
            }
            break;

        default:
            break;
    }
}

ret_code_t nfc_ble_pair_on_pm_params_req(pm_evt_t const * p_evt)
{
    ret_code_t err_code = NRF_SUCCESS;

    NRF_LOG_DEBUG("PM_EVT_CONN_SEC_PARAMS_REQ");

    // Dynamic security parameters changes are needed only
    // by NFC_PAIRING_MODE_GENERIC_OOB pairing mode.
    if (m_pairing_mode == NFC_PAIRING_MODE_GENERIC_OOB)
    {
        // Check if pointer to the Peer Manager event is not NULL.
        VERIFY_PARAM_NOT_NULL(p_evt);

        // Set up proper MITM, OOB and LESC flags depending on peer LESC flag
        // to support either Legacy OOB or LESC OOB pairing mode.
        if (p_evt->params.conn_sec_params_req.p_peer_params->lesc)
        {
            NRF_LOG_DEBUG("LESC OOB mode flags set.");

            m_sec_param.mitm  = 0;
            m_sec_param.oob   = 0;
            m_sec_param.lesc  = 1;
        }
        else
        {
            NRF_LOG_DEBUG("Legacy OOB mode flags set.");

            m_sec_param.mitm  = 1;
            m_sec_param.oob   = 1;
            m_sec_param.lesc  = 0;
        }

        // Reply with new security parameters to the Peer Manager.
        err_code = pm_conn_sec_params_reply(p_evt->conn_handle,
                                            &m_sec_param,
                                            p_evt->params.conn_sec_params_req.p_context);
    }

    return err_code;
}

#endif // NRF_MODULE_ENABLED(NFC_BLE_PAIR_LIB)
