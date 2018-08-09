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

#include <string.h>
#include "nrf_ble_es.h"
#include "app_error.h"
#include "fds.h"
#include "es_adv.h"
#include "es_battery_voltage.h"
#include "es_flash.h"
#include "es_gatts.h"
#include "es_security.h"
#include "es_slot.h"
#include "es_stopwatch.h"
#include "escs_defs.h"
#include "nrf_sdh_ble.h"

static uint16_t                       m_conn_handle = BLE_CONN_HANDLE_INVALID;  //!< Connection handle.
static nrf_ble_escs_t                 m_ble_ecs;                                //!< Struct identifying the Eddystone Config Service.
static nrf_ble_es_evt_handler_t       m_evt_handler;                            //!< Event handler.

uint8_t m_adv_handle = BLE_GAP_ADV_SET_HANDLE_NOT_SET;                          //!< Advertising handle used to identify an advertising set.

/**@brief Function for invoking registered callback.
 *
 * @param[in] evt Event to issue to callback.
 */
static void handle_evt(nrf_ble_es_evt_t evt)
{
    if (m_evt_handler != NULL)
    {
        m_evt_handler(evt);
    }
}


/**@brief Function resetting MAC address. Will resume advertisement. */
static void new_address_set(void)
{

    ret_code_t     err_code;
    uint8_t        bytes_available;
    ble_gap_addr_t new_address;

    new_address.addr_type = BLE_GAP_ADDR_TYPE_PUBLIC;

    // Randomize the MAC address on every EID generation
    (void)sd_rand_application_bytes_available_get(&bytes_available);

    while (bytes_available < BLE_GAP_ADDR_LEN)
    {
        // wait for SD to acquire enough RNs
        (void)sd_rand_application_bytes_available_get(&bytes_available);
    }

    (void)sd_rand_application_vector_get(new_address.addr, BLE_GAP_ADDR_LEN);

    // Stop advertising to ensure that it is possible to change the address.
    (void)sd_ble_gap_adv_stop(m_adv_handle);

    do
    {
        err_code = sd_ble_gap_addr_set(&new_address);
    } while (err_code == NRF_ERROR_INVALID_STATE);

    APP_ERROR_CHECK(err_code);

    if (es_adv_remain_connectable_get())
    {
        es_adv_start_connectable_adv();
    }
    else
    {
        es_adv_start_non_connctable_adv();
    }
}


/**@brief Function updating MAC address if required.
 *
 * @param[in] demand_new_mac If 'true', mac address will be updated on next invocation when not connected.
 *                           If 'false', simply check if we have an outstanding demand for new MAC and update if not connected.
 */
static void check_and_update_mac_address(bool demand_new_mac)
{
    static bool reset_mac_address = false;

    if (demand_new_mac)
    {
        reset_mac_address = true;
    }

    // Not possible to update MAC address while in a connection
    if (m_conn_handle != BLE_CONN_HANDLE_INVALID)
    {
        return;
    }

    else if (reset_mac_address)
    {
        reset_mac_address = false;

        new_address_set();
    }
}


/**@brief Function to lock the beacon (change lock state characteristic to LOCKED)
 */
static void lock_beacon(void)
{
    *(m_ble_ecs.p_lock_state) = NRF_BLE_ESCS_LOCK_STATE_LOCKED;
}


/**@brief Function for handling BLE event from the SoftDevice.
 *
 * @param[in] p_ble_evt Pointer to BLE event.
 */
static void on_ble_evt(ble_evt_t const * p_ble_evt)
{
    ret_code_t            err_code;
    es_flash_flags_t      flash_flag = {{0}};
    const es_slot_reg_t * p_reg      = es_slot_get_registry();

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            m_conn_handle = p_ble_evt->evt.common_evt.conn_handle;
            *(m_ble_ecs.p_active_slot) = 0;
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            m_conn_handle = BLE_CONN_HANDLE_INVALID;

            for (uint32_t i = 0; i < APP_MAX_ADV_SLOTS; ++i)
            {
                err_code = es_slot_write_to_flash(i);
                APP_ERROR_CHECK(err_code);

                flash_flag.slot_is_empty[i] = !p_reg->slots[i].configured;
            }

            err_code = es_flash_access_flags(&flash_flag, ES_FLASH_ACCESS_WRITE);
            APP_ERROR_CHECK(err_code);

            es_flash_beacon_config_t beacon_config;
            beacon_config.adv_interval       = es_adv_interval_get();
            beacon_config.remain_connectable = es_adv_remain_connectable_get();

            err_code = es_flash_access_beacon_config(&beacon_config, ES_FLASH_ACCESS_WRITE);
            APP_ERROR_CHECK(err_code);

            if (*m_ble_ecs.p_lock_state == NRF_BLE_ESCS_LOCK_STATE_UNLOCKED)
            {
                lock_beacon();
            }

            check_and_update_mac_address(false);

            break;

        default:
            // No implementation needed.
            break;
    }
}


/**@brief Callback function to receive messages from the security module
 *
 * @details Need to be passed in during es_security_init(). The security
 *          module will callback anytime a particular security process is completed
 *
 * @params[in]  slot_no     Index of the slot
 * @params[in]  msg_type    Message type corersponding to different security components
 */
static void nrf_ble_escs_security_cb(uint8_t slot_no, es_security_msg_t msg_type)
{
    nrf_ble_escs_eid_id_key_t      encrypted_id_key;
    nrf_ble_escs_public_ecdh_key_t pub_ecdh_key;

    ret_code_t               err_code;
    static ble_gatts_value_t value;

    switch (msg_type)
    {
        case ES_SECURITY_MSG_UNLOCKED:
            *(m_ble_ecs.p_lock_state) = NRF_BLE_ESCS_LOCK_STATE_UNLOCKED;
            break;

        case ES_SECURITY_MSG_EID:
            es_slot_eid_ready(slot_no);
#ifdef MAC_RANDOMIZED
            check_and_update_mac_address(true);
#endif // MAC_RANDOMIZED
            break;

        case ES_SECURITY_MSG_IK:
            es_security_encrypted_eid_id_key_get(slot_no, (uint8_t *)encrypted_id_key.key);
            // Set the EID ID key in the slot so it can be exposed in the characteristic
            es_slot_encrypted_eid_id_key_set(slot_no, &encrypted_id_key);
            break;

        case ES_SECURITY_MSG_ECDH:
            es_security_pub_ecdh_get(slot_no, (uint8_t *)pub_ecdh_key.key);

            // Set the characteristic to the ECDH key value
            value.len     = sizeof(nrf_ble_escs_public_ecdh_key_t);
            value.offset  = 0;
            value.p_value = (uint8_t *)pub_ecdh_key.key;

            if (m_conn_handle != BLE_CONN_HANDLE_INVALID)
            {
                err_code = sd_ble_gatts_value_set(m_ble_ecs.conn_handle,
                                                  m_ble_ecs.pub_ecdh_key_handles.value_handle,
                                                  &value);
                if (err_code != NRF_SUCCESS)
                {
                    APP_ERROR_CHECK(err_code);
                }
            }
            break;

        case ES_SECURITY_MSG_STORE_TIME:
            // Every 24 hours any EID slots time is stored to flash to allow for power lock_state_handles
            // recovery. Only time needs to be stored, but just store the entire slot anyway for API simplicity.
            err_code = es_slot_write_to_flash(slot_no);
            APP_ERROR_CHECK(err_code);

            break;

        default:
            APP_ERROR_CHECK(NRF_ERROR_INVALID_PARAM); // Should never happen
            break;
    }
}


/**@brief Function for handling advertisement events from 'es_adv'.
 *
 * @param[in] evt Advertisement event to handle.
 */
static void adv_evt_handler(es_adv_evt_t evt)
{
    switch (evt)
    {
        case ES_ADV_EVT_NON_CONN_ADV:
            handle_evt(NRF_BLE_ES_EVT_ADVERTISEMENT_SENT);
            es_security_update_time();
            break;

        case ES_ADV_EVT_CONNECTABLE_ADV_STARTED:
            handle_evt(NRF_BLE_ES_EVT_CONNECTABLE_ADV_STARTED);
            break;

        case ES_ADV_EVT_CONNECTABLE_ADV_STOPPED:
            handle_evt(NRF_BLE_ES_EVT_CONNECTABLE_ADV_STOPPED);
            break;

        default:
            break;
    }
}


/**@brief Initialize the ECS with initial values for the characteristics and other necessary modules */
static void ble_escs_init(void)
{
    ret_code_t                 err_code;
    nrf_ble_escs_init_t        ecs_init;
    nrf_ble_escs_init_params_t init_params;
    int8_t                     tx_powers[ESCS_NUM_OF_SUPPORTED_TX_POWER] = ESCS_SUPPORTED_TX_POWER;

    /*Init the broadcast capabilities characteristic*/
    memset(&init_params.broadcast_cap, 0, sizeof(init_params.broadcast_cap));
    init_params.broadcast_cap.vers_byte            = ES_SPEC_VERSION_BYTE;
    init_params.broadcast_cap.max_supp_total_slots = APP_MAX_ADV_SLOTS;
    init_params.broadcast_cap.max_supp_eid_slots   = APP_MAX_EID_SLOTS;
    init_params.broadcast_cap.cap_bitfield         = ( (APP_IS_VARIABLE_ADV_SUPPORTED << ESCS_BROADCAST_VAR_ADV_SUPPORTED_Pos)
                                                   | (APP_IS_VARIABLE_TX_POWER_SUPPORTED << ESCS_BROADCAST_VAR_TX_POWER_SUPPORTED_Pos))
                                                   & (ESCS_BROADCAST_VAR_RFU_MASK);
    init_params.broadcast_cap.supp_frame_types     = ( (APP_IS_URL_SUPPORTED << ESCS_FRAME_TYPE_URL_SUPPORTED_Pos)
                                                   | (APP_IS_UID_SUPPORTED << ESCS_FRAME_TYPE_UID_SUPPORTED_Pos)
                                                   | (APP_IS_TLM_SUPPORTED << ESCS_FRAME_TYPE_TLM_SUPPORTED_Pos)
                                                   | (APP_IS_EID_SUPPORTED << ESCS_FRAME_TYPE_EID_SUPPORTED_Pos))
                                                   & (ESCS_FRAME_TYPE_RFU_MASK);
    memcpy(init_params.broadcast_cap.supp_radio_tx_power, tx_powers, ESCS_NUM_OF_SUPPORTED_TX_POWER);

    init_params.adv_interval    = APP_CFG_NON_CONN_ADV_INTERVAL_MS;
    init_params.adv_tx_pwr      = APP_CFG_DEFAULT_RADIO_TX_POWER;
    init_params.radio_tx_pwr    = 0x00;
    init_params.factory_reset   = 0;
    init_params.remain_connectable.r_is_non_connectable_supported = APP_IS_REMAIN_CONNECTABLE_SUPPORTED;

    // Initialize evt handlers and the service
    memset(&ecs_init, 0, sizeof(ecs_init));
    ecs_init.write_evt_handler = es_gatts_handle_write;
    ecs_init.read_evt_handler  = es_gatts_handle_read;
    ecs_init.p_init_vals       = &(init_params);

    err_code = nrf_ble_escs_init(&m_ble_ecs, &ecs_init);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for initializing 'es_adv' module. */
static void adv_init(void)
{
    ret_code_t               err_code;
    es_flash_beacon_config_t beacon_config;

    err_code = es_flash_access_beacon_config(&beacon_config, ES_FLASH_ACCESS_READ);

    if (err_code == FDS_ERR_NOT_FOUND)
    {
        beacon_config.adv_interval       = APP_CFG_NON_CONN_ADV_INTERVAL_MS;
        beacon_config.remain_connectable = false;
    }

    else
    {
        APP_ERROR_CHECK(err_code);
    }

    es_adv_init(m_ble_ecs.uuid_type,
                adv_evt_handler,
                beacon_config.adv_interval,
                beacon_config.remain_connectable,
                &m_adv_handle);
}


/**@brief Function for initializing es_slots module. */
static void adv_slots_init(void)
{
    uint8_t default_frame_data[DEFAULT_FRAME_LENGTH] = DEFAULT_FRAME_DATA;

    es_slot_t default_adv_slot = {.slot_no             = 0,
                                  .radio_tx_pwr        = 0,
                                  .adv_frame.type      = DEFAULT_FRAME_TYPE,
                                  .adv_frame.length    = DEFAULT_FRAME_LENGTH,
                                  .adv_custom_tx_power = false,
                                  .configured          = true};

    memcpy(&default_adv_slot.adv_frame.frame, default_frame_data, DEFAULT_FRAME_LENGTH);

    es_slots_init(&default_adv_slot);
}


void nrf_ble_es_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    ret_code_t err_code;

    es_adv_on_ble_evt(p_ble_evt);
    err_code = nrf_ble_escs_on_ble_evt(&m_ble_ecs, p_ble_evt);
    APP_ERROR_CHECK(err_code);
    on_ble_evt(p_ble_evt);
    es_flash_on_ble_evt(p_ble_evt);
}

NRF_SDH_BLE_OBSERVER(m_es_observer, NRF_BLE_ES_BLE_OBSERVER_PRIO, nrf_ble_es_on_ble_evt, NULL);


void nrf_ble_es_on_start_connectable_advertising(void)
{
    es_adv_start_connectable_adv();
}


void nrf_ble_es_init(nrf_ble_es_evt_handler_t evt_handler)
{
    ret_code_t err_code;

    m_evt_handler = evt_handler;
    m_conn_handle = BLE_CONN_HANDLE_INVALID;

    es_stopwatch_init();

    err_code = es_gatts_init(&m_ble_ecs);
    APP_ERROR_CHECK(err_code);

    err_code = es_flash_init();
    APP_ERROR_CHECK(err_code);

    while (es_flash_num_pending_ops() > 0)
    {
        ; // Busy wait while initialization of FDS module completes
    }

    err_code = es_security_init(nrf_ble_escs_security_cb);
    APP_ERROR_CHECK(err_code);

    es_adv_timers_init();
    ble_escs_init();
    adv_slots_init();
    es_battery_voltage_init();
    adv_init();
    es_adv_start_non_connctable_adv();
}
