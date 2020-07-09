/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(PEER_MANAGER)
#include "security_manager.h"

#include <string.h>
#include "security_dispatcher.h"
#include "peer_database.h"
#include "ble_conn_state.h"
#include "id_manager.h"


// The number of registered event handlers.
#define SM_EVENT_HANDLERS_CNT       (sizeof(m_evt_handlers) / sizeof(m_evt_handlers[0]))


// Security Manager event handler in Peer Manager.
extern void pm_sm_evt_handler(sm_evt_t const * p_sm_evt);

// Security Manager events' handlers.
// The number of elements in this array is SM_EVENT_HANDLERS_CNT.
static sm_evt_handler_t const m_evt_handlers[] =
{
    pm_sm_evt_handler
};

static bool                            m_module_initialized;

static ble_gap_sec_params_t            m_sec_params;
static bool                            m_sec_params_valid;

static ble_gap_lesc_p256_pk_t        * m_p_public_key;
static ble_conn_state_user_flag_id_t   m_flag_link_secure_pending_busy        = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t   m_flag_link_secure_pending_flash_full  = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t   m_flag_link_secure_force_repairing     = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t   m_flag_link_secure_null_params         = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t   m_flag_params_reply_pending_busy       = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t   m_flag_params_reply_pending_flash_full = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t   m_flag_reject_pairing                  = BLE_CONN_STATE_USER_FLAG_INVALID;


static void evt_send(sm_evt_t * p_event)
{
    for (uint32_t i = 0; i < SM_EVENT_HANDLERS_CNT; i++)
    {
        m_evt_handlers[i](p_event);
    }
}


static void flags_set_from_err_code(uint16_t conn_handle, ret_code_t err_code, bool params_reply)
{
    bool flag_value_flash_full = false;
    bool flag_value_busy       = false;

    if (    (err_code == NRF_ERROR_STORAGE_FULL)
         || (err_code == NRF_ERROR_BUSY)
         || (err_code == NRF_SUCCESS))
    {
        if ((err_code == NRF_ERROR_STORAGE_FULL))
        {
            flag_value_busy       = false;
            flag_value_flash_full = true;
        }
        else if (err_code == NRF_ERROR_BUSY)
        {
            flag_value_busy       = true;
            flag_value_flash_full = false;
        }
        else if (err_code == NRF_SUCCESS)
        {
            flag_value_busy       = false;
            flag_value_flash_full = false;
        }

        if (params_reply)
        {
            ble_conn_state_user_flag_set(conn_handle,
                                         m_flag_params_reply_pending_flash_full,
                                         flag_value_flash_full);
            ble_conn_state_user_flag_set(conn_handle,
                                         m_flag_params_reply_pending_busy,
                                         flag_value_busy);
            ble_conn_state_user_flag_set(conn_handle,
                                         m_flag_link_secure_pending_flash_full,
                                         false);
            ble_conn_state_user_flag_set(conn_handle,
                                         m_flag_link_secure_pending_busy,
                                         false);
        }
        else
        {
            ble_conn_state_user_flag_set(conn_handle,
                                         m_flag_link_secure_pending_flash_full,
                                         flag_value_flash_full);
            ble_conn_state_user_flag_set(conn_handle,
                                         m_flag_link_secure_pending_busy,
                                         flag_value_busy);
        }
    }
}


static void events_send_from_err_code(uint16_t conn_handle, ret_code_t err_code)
{
     if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_BUSY))
     {
        sm_evt_t evt =
        {
            .conn_handle = conn_handle,
            .params = {.error_unexpected = {
                .error = err_code
            }}
        };
        if (err_code == NRF_ERROR_TIMEOUT)
        {
            evt.evt_id = SM_EVT_ERROR_SMP_TIMEOUT;
        }
        else if (err_code == NRF_ERROR_STORAGE_FULL)
        {
            evt.evt_id = SM_EVT_ERROR_NO_MEM;
        }
        else
        {
            evt.evt_id = SM_EVT_ERROR_UNEXPECTED;
        }
        evt_send(&evt);
     }
}


static ret_code_t link_secure(uint16_t conn_handle, bool null_params, bool force_repairing, bool send_events)
{
    ret_code_t err_code;

    if (!null_params && !m_sec_params_valid)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    if (null_params)
    {
        err_code = smd_link_secure(conn_handle, NULL, force_repairing);
    }
    else
    {
        err_code = smd_link_secure(conn_handle, &m_sec_params, force_repairing);
    }

    flags_set_from_err_code(conn_handle, err_code, false);

    if (send_events)
    {
        events_send_from_err_code(conn_handle, err_code);
    }

    switch (err_code)
    {
        case NRF_ERROR_BUSY:
            ble_conn_state_user_flag_set(conn_handle, m_flag_link_secure_null_params, null_params);
            ble_conn_state_user_flag_set(conn_handle, m_flag_link_secure_force_repairing, force_repairing);
            err_code = NRF_SUCCESS;
            break;
        case NRF_ERROR_STORAGE_FULL:
            ble_conn_state_user_flag_set(conn_handle, m_flag_link_secure_null_params, null_params);
            ble_conn_state_user_flag_set(conn_handle, m_flag_link_secure_force_repairing, force_repairing);
            break;
        case NRF_SUCCESS:
        case NRF_ERROR_TIMEOUT:
        case BLE_ERROR_INVALID_CONN_HANDLE:
        case NRF_ERROR_INVALID_STATE:
            /* No action */
            break;
        default:
            err_code = NRF_ERROR_INTERNAL;
            break;
    }

    return err_code;
}


static void send_config_req(uint16_t conn_handle)
{
    sm_evt_t sm_evt;
    memset(&sm_evt, 0, sizeof(sm_evt));

    sm_evt.evt_id      = SM_EVT_CONN_SEC_CONFIG_REQ;
    sm_evt.conn_handle = conn_handle;

    evt_send(&sm_evt);
}


static void smd_params_reply_perform(uint16_t conn_handle)
{
    ret_code_t err_code;

    if (  (ble_conn_state_role(conn_handle) == BLE_GAP_ROLE_PERIPH)
        && im_peer_id_get_by_conn_handle(conn_handle) != PM_PEER_ID_INVALID)
    {
        // Bond already exists. Reject the pairing request if the user doesn't intervene.
        ble_conn_state_user_flag_set(conn_handle, m_flag_reject_pairing, true);
        send_config_req(conn_handle);
    }
    else
    {
        ble_conn_state_user_flag_set(conn_handle, m_flag_reject_pairing, false);
    }

    if (   m_sec_params_valid
        && !ble_conn_state_user_flag_get(conn_handle, m_flag_reject_pairing))
    {
        err_code = smd_params_reply(conn_handle, &m_sec_params, m_p_public_key);
    }
    else
    {
        err_code = smd_params_reply(conn_handle, NULL, NULL);
    }

    flags_set_from_err_code(conn_handle, err_code, true);
    events_send_from_err_code(conn_handle, err_code);
}


/**@brief Event handler for events from the Security Dispatcher module.
 *        This handler is extern in Security Dispatcher.
 *
 * @param[in]  p_event   The event that has happened.
 */
void sm_smd_evt_handler(smd_evt_t const * p_event)
{
    switch (p_event->evt_id)
    {
        case SMD_EVT_PARAMS_REQ:
            smd_params_reply_perform(p_event->conn_handle);
            break;
        case SMD_EVT_SLAVE_SECURITY_REQ:
        {
            bool null_params = false;
            if (!m_sec_params_valid)
            {
                null_params = true;
            }
            else if ((bool)m_sec_params.bond < (bool)p_event->params.slave_security_req.bond)
            {
                null_params = true;
            }
            else if ((bool)m_sec_params.mitm < (bool)p_event->params.slave_security_req.mitm)
            {
                null_params = true;
            }
            ret_code_t err_code = link_secure(p_event->conn_handle, null_params, false, true);
            UNUSED_VARIABLE(err_code); // It is acceptable to ignore the return code because it is
                                       // acceptable to ignore a security request.
        }
        /* fallthrough */
        case SMD_EVT_PAIRING_SUCCESS:
        case SMD_EVT_PAIRING_FAIL:
        case SMD_EVT_LINK_ENCRYPTION_UPDATE:
        case SMD_EVT_LINK_ENCRYPTION_FAILED:
        case SMD_EVT_BONDING_INFO_STORED:
        case SMD_EVT_ERROR_BONDING_INFO:
        case SMD_EVT_ERROR_UNEXPECTED:
        case SMD_EVT_SEC_PROCEDURE_START:
        {
            sm_evt_t evt;
            evt.evt_id = (sm_evt_id_t)p_event->evt_id;
            evt.conn_handle = p_event->conn_handle;
            evt.params = p_event->params;

            evt_send(&evt);
        }
            break;
    }
}


static void link_secure_pending_process(ble_conn_state_user_flag_id_t flag_id)
{
    sdk_mapped_flags_t flag_collection = ble_conn_state_user_flag_collection(flag_id);
    if (sdk_mapped_flags_any_set(flag_collection))
    {
        sdk_mapped_flags_key_list_t conn_handle_list = ble_conn_state_conn_handles();

        for (uint32_t i = 0; i < conn_handle_list.len; i++)
        {
            bool pending = ble_conn_state_user_flag_get(conn_handle_list.flag_keys[i], flag_id);
            if (pending)
            {
                bool force_repairing = ble_conn_state_user_flag_get(conn_handle_list.flag_keys[i], m_flag_link_secure_force_repairing);
                bool null_params     = ble_conn_state_user_flag_get(conn_handle_list.flag_keys[i], m_flag_link_secure_null_params);

                ret_code_t err_code = link_secure(conn_handle_list.flag_keys[i], null_params, force_repairing, true); // If this fails, it will be automatically retried.
                UNUSED_VARIABLE(err_code);
            }
        }
    }
}


static void params_reply_pending_process(ble_conn_state_user_flag_id_t flag_id)
{
    sdk_mapped_flags_t flag_collection = ble_conn_state_user_flag_collection(flag_id);
    if (sdk_mapped_flags_any_set(flag_collection))
    {
        sdk_mapped_flags_key_list_t conn_handle_list = ble_conn_state_conn_handles();

        for (uint32_t i = 0; i < conn_handle_list.len; i++)
        {
            bool pending = ble_conn_state_user_flag_get(conn_handle_list.flag_keys[i], flag_id);
            if (pending)
            {
                smd_params_reply_perform(conn_handle_list.flag_keys[i]);
            }
        }
    }
}


/**@brief Event handler for events from the Peer Database module.
 *        This handler is extern in Peer Database.
 *
 * @param[in]  p_event   The event that has happened.
 */
void sm_pdb_evt_handler(pdb_evt_t const * p_event)
{
    switch (p_event->evt_id)
    {
        case PDB_EVT_COMPRESSED:
            params_reply_pending_process(m_flag_params_reply_pending_flash_full);
            link_secure_pending_process(m_flag_link_secure_pending_flash_full);
            /* fallthrough */
        case PDB_EVT_WRITE_BUF_STORED:
        case PDB_EVT_RAW_STORED:
        case PDB_EVT_RAW_STORE_FAILED:
        case PDB_EVT_CLEARED:
        case PDB_EVT_CLEAR_FAILED:
        case PDB_EVT_PEER_FREED:
        case PDB_EVT_PEER_FREE_FAILED:
            params_reply_pending_process(m_flag_params_reply_pending_busy);
            link_secure_pending_process(m_flag_link_secure_pending_busy);
            break;
        case PDB_EVT_ERROR_NO_MEM:
        case PDB_EVT_ERROR_UNEXPECTED:
            break;
    }
}


/**@brief Funtion for initializing a BLE Connection State user flag.
 *
 * @param[out] flag_id  The flag to initialize.
 */
static void flag_id_init(ble_conn_state_user_flag_id_t * p_flag_id)
{
    if (*p_flag_id == BLE_CONN_STATE_USER_FLAG_INVALID)
    {
        *p_flag_id = ble_conn_state_user_flag_acquire();
    }
}


ret_code_t sm_init(void)
{
    NRF_PM_DEBUG_CHECK(!m_module_initialized);

    flag_id_init(&m_flag_link_secure_pending_busy);
    flag_id_init(&m_flag_link_secure_pending_flash_full);
    flag_id_init(&m_flag_link_secure_force_repairing);
    flag_id_init(&m_flag_link_secure_null_params);
    flag_id_init(&m_flag_params_reply_pending_busy);
    flag_id_init(&m_flag_params_reply_pending_flash_full);
    flag_id_init(&m_flag_reject_pairing);

    if (m_flag_reject_pairing == BLE_CONN_STATE_USER_FLAG_INVALID)
    {
        return NRF_ERROR_INTERNAL;
    }

    m_module_initialized = true;

    return NRF_SUCCESS;
}


void sm_ble_evt_handler(ble_evt_t * p_ble_evt)
{
    NRF_PM_DEBUG_CHECK(p_ble_evt != NULL);

    smd_ble_evt_handler(p_ble_evt);
    link_secure_pending_process(m_flag_link_secure_pending_busy);
}


static bool sec_params_verify(ble_gap_sec_params_t * p_sec_params)
{
    // NULL check.
    if (p_sec_params == NULL)
    {
        return false;
    }

    // OOB not allowed unless MITM.
    if (!p_sec_params->mitm && p_sec_params->oob)
    {
        return false;
    }

    // IO Capabilities must be one of the valid values from @ref BLE_GAP_IO_CAPS.
    if (p_sec_params->io_caps > BLE_GAP_IO_CAPS_KEYBOARD_DISPLAY)
    {
        return false;
    }

    // Must have either IO capabilities or OOB if MITM.
    if (p_sec_params->mitm && (p_sec_params->io_caps == BLE_GAP_IO_CAPS_NONE) && !p_sec_params->oob)
    {
        return false;
    }

    // Minimum key size cannot be larger than maximum key size.
    if (p_sec_params->min_key_size > p_sec_params->max_key_size)
    {
        return false;
    }

    // Key size cannot be below 7 bytes.
    if (p_sec_params->min_key_size < 7)
    {
        return false;
    }

    // Key size cannot be above 16 bytes.
    if (p_sec_params->max_key_size > 16)
    {
        return false;
    }

    // Signing is not supported.
    if (p_sec_params->kdist_own.sign || p_sec_params->kdist_peer.sign)
    {
        return false;
    }

    // link bit must be 0.
    if (p_sec_params->kdist_own.link || p_sec_params->kdist_peer.link)
    {
        return false;
    }

    // If bonding is not enabled, no keys can be distributed.
    if (!p_sec_params->bond && (   p_sec_params->kdist_own.enc
                                || p_sec_params->kdist_own.id
                                || p_sec_params->kdist_peer.enc
                                || p_sec_params->kdist_peer.id))
    {
        return false;
    }

    // If bonding is enabled, one or more keys must be distributed.
    if (    p_sec_params->bond
        && !p_sec_params->kdist_own.enc
        && !p_sec_params->kdist_own.id
        && !p_sec_params->kdist_peer.enc
        && !p_sec_params->kdist_peer.id)
    {
        return false;
    }

    return true;
}


ret_code_t sm_sec_params_set(ble_gap_sec_params_t * p_sec_params)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    if (p_sec_params == NULL)
    {
        m_sec_params_valid = false;
        return NRF_SUCCESS;
    }
    else if (sec_params_verify(p_sec_params))
    {
        m_sec_params       = *p_sec_params;
        m_sec_params_valid = true;
        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM;
    }
}


void sm_conn_sec_config_reply(uint16_t conn_handle, pm_conn_sec_config_t * p_conn_sec_config)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_conn_sec_config != NULL);

    ble_conn_state_user_flag_set(conn_handle, m_flag_reject_pairing, !p_conn_sec_config->allow_repairing);
}


ret_code_t sm_lesc_public_key_set(ble_gap_lesc_p256_pk_t * p_public_key)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    m_p_public_key = p_public_key;

    return NRF_SUCCESS;
}


ret_code_t sm_sec_params_reply(uint16_t conn_handle, ble_gap_sec_params_t * p_sec_params)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return NRF_SUCCESS;
}


ret_code_t sm_link_secure(uint16_t conn_handle, bool force_repairing)
{
    ret_code_t ret;

    NRF_PM_DEBUG_CHECK(m_module_initialized);

    ret = link_secure(conn_handle, false, force_repairing, false);
    return ret;
}
#endif // NRF_MODULE_ENABLED(PEER_MANAGER)
