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
#include "security_dispatcher.h"

#include <string.h>
#include "ble.h"
#include "ble_gap.h"
#include "ble_conn_state.h"
#include "peer_manager_types.h"
#include "peer_database.h"
#include "id_manager.h"


// The number of registered event handlers.
#define SMD_EVENT_HANDLERS_CNT      (sizeof(m_evt_handlers) / sizeof(m_evt_handlers[0]))


// Security Dispacher event handlers in Security Manager and GATT Cache Manager.
extern void sm_smd_evt_handler(smd_evt_t const * p_event);
extern void gcm_smd_evt_handler(smd_evt_t const * p_event);

// Security Dispatcher events' handlers.
// The number of elements in this array is SMD_EVENT_HANDLERS_CNT.
static smd_evt_handler_t const m_evt_handlers[] =
{
    sm_smd_evt_handler,
    gcm_smd_evt_handler
};

static bool                          m_module_initialized;

static ble_conn_state_user_flag_id_t m_flag_sec_proc          = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t m_flag_sec_proc_pairing  = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t m_flag_sec_proc_new_peer = BLE_CONN_STATE_USER_FLAG_INVALID;

static ble_gap_lesc_p256_pk_t        m_peer_pk;


static void evt_send(smd_evt_t * p_event)
{
    for (uint32_t i = 0; i < SMD_EVENT_HANDLERS_CNT; i++)
    {
        m_evt_handlers[i](p_event);
    }
}


static void sec_start_send(uint16_t conn_handle, pm_conn_sec_procedure_t procedure)
{
    smd_evt_t evt =
    {
        .evt_id      = SMD_EVT_SEC_PROCEDURE_START,
        .conn_handle = conn_handle,
        .params      = {.sec_procedure_start = {.procedure = procedure}}
    };
    evt_send(&evt);
}


/**@brief Event handler for events from the Peer Database module.
 *        This handler is extern in Peer Database.
 *
 * @param[in]  p_event   The event that has happened.
 */
void smd_pdb_evt_handler(pdb_evt_t const * p_event)
{
    if ((p_event->evt_id == PDB_EVT_WRITE_BUF_STORED) && (p_event->data_id == PM_PEER_DATA_ID_BONDING))
    {
        smd_evt_t evt =
        {
            .evt_id      = SMD_EVT_BONDING_INFO_STORED,
            .conn_handle = im_conn_handle_get(p_event->peer_id),
            .params      = {.bonding_info_stored = {.peer_id = p_event->peer_id}}
        };
        evt_send(&evt);
    }
}


/**@brief Function for processing the @ref BLE_GAP_EVT_SEC_PARAMS_REQUEST event from the SoftDevice.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void sec_params_request_process(ble_gap_evt_t * p_gap_evt)
{
    smd_evt_t evt =
    {
        .evt_id      = SMD_EVT_PARAMS_REQ,
        .conn_handle = p_gap_evt->conn_handle
    };
    evt_send(&evt);
    return;
}


/**@brief Function for administrative actions to be taken when a security process has been attempted.
 *
 * @param[in]  conn_handle       The connection the security process was attempted on.
 * @param[in]  peer_id           The peer ID given to the connected peer.
 * @param[in]  success           Whether the process was started successfully.
 * @param[in]  pairing           Whether the process was a pairing process.
 * @param[in]  new_peer_created  Whether a new peer was created during the process attempt.
 */
static void sec_proc_start(uint16_t     conn_handle,
                           pm_peer_id_t peer_id,
                           bool         success,
                           bool         pairing,
                           bool         new_peer_created)
{
    ble_conn_state_user_flag_set(conn_handle, m_flag_sec_proc, success);

    if (success)
    {
        ble_conn_state_user_flag_set(conn_handle, m_flag_sec_proc_pairing, pairing);
        ble_conn_state_user_flag_set(conn_handle, m_flag_sec_proc_new_peer, new_peer_created);

        if (new_peer_created)
        {
            im_new_peer_id(conn_handle, peer_id);
        }
    }
    else
    {
        if (new_peer_created)
        {
            ret_code_t err_code = im_peer_free(peer_id); // Attempt to free allocated peer.
            UNUSED_VARIABLE(err_code);
        }
    }
}



/**@brief Function for processing the @ref BLE_GAP_EVT_SEC_INFO_REQUEST event from the SoftDevice.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void sec_info_request_process(ble_gap_evt_t * p_gap_evt)
{
    ret_code_t                 err_code;
    ble_gap_enc_info_t const * p_enc_info = NULL;
    pm_peer_data_flash_t       peer_data;
    pm_peer_id_t               peer_id = im_peer_id_get_by_master_id(&p_gap_evt->params.sec_info_request.master_id);
    smd_evt_t evt;

    evt.conn_handle = p_gap_evt->conn_handle;

    if (peer_id == PM_PEER_ID_INVALID)
    {
        peer_id = im_peer_id_get_by_conn_handle(p_gap_evt->conn_handle);
    }

    if (peer_id != PM_PEER_ID_INVALID)
    {
        err_code = pdb_peer_data_ptr_get(peer_id, PM_PEER_DATA_ID_BONDING, &peer_data);

        if (err_code == NRF_SUCCESS)
        {
            // There is stored bonding data for this peer.
            ble_gap_enc_key_t const * p_existing_key = &peer_data.p_bonding_data->own_ltk;

            if (   p_existing_key->enc_info.lesc
                || (im_master_ids_compare(&p_existing_key->master_id,
                                          &p_gap_evt->params.sec_info_request.master_id)))
            {
                p_enc_info = &p_existing_key->enc_info;
            }
        }
    }

    // All return values from the following can be safely ignored.
    err_code = sd_ble_gap_sec_info_reply(p_gap_evt->conn_handle, p_enc_info, NULL, NULL);

    if (err_code != NRF_SUCCESS)
    {
        evt.evt_id                        = SMD_EVT_ERROR_UNEXPECTED;
        evt.params.error_unexpected.error = err_code;

        evt_send(&evt);
    }
    else if (p_enc_info == NULL)
    {
        evt.evt_id                                  = SMD_EVT_LINK_ENCRYPTION_FAILED;
        evt.params.link_encryption_failed.error     = PM_CONN_SEC_ERROR_PIN_OR_KEY_MISSING;
        evt.params.link_encryption_failed.error_src = BLE_GAP_SEC_STATUS_SOURCE_LOCAL;

        evt_send(&evt);

        sec_proc_start(p_gap_evt->conn_handle, peer_id, false, false, false);
    }
    else
    {
        sec_start_send(p_gap_evt->conn_handle, PM_LINK_SECURED_PROCEDURE_ENCRYPTION);

        sec_proc_start(p_gap_evt->conn_handle, peer_id, err_code == NRF_SUCCESS, false, false);
    }


    return;
}


/**@brief Function for processing the @ref BLE_GAP_EVT_SEC_REQUEST event from the SoftDevice.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void sec_request_process(ble_gap_evt_t * p_gap_evt)
{
    smd_evt_t evt =
    {
        .evt_id = SMD_EVT_SLAVE_SECURITY_REQ,
        .conn_handle = p_gap_evt->conn_handle,
        .params =
        {
            .slave_security_req =
            {
                .bond = p_gap_evt->params.sec_request.bond,
                .mitm = p_gap_evt->params.sec_request.mitm,
            }
        }
    };
    evt_send(&evt);
    return;
}


/**@brief Function for processing the @ref BLE_GAP_EVT_AUTH_STATUS event from the SoftDevice, when
 *        the auth_status is success.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void auth_status_success_process(ble_gap_evt_t * p_gap_evt)
{
    ret_code_t           err_code   = NRF_SUCCESS;
    uint8_t              role       = ble_conn_state_role(p_gap_evt->conn_handle);
    pm_peer_id_t         peer_id    = im_peer_id_get_by_conn_handle(p_gap_evt->conn_handle);
    ble_gap_sec_kdist_t  kdist_own  = p_gap_evt->params.auth_status.kdist_own;
    ble_gap_sec_kdist_t  kdist_peer = p_gap_evt->params.auth_status.kdist_peer;

    ble_conn_state_user_flag_set(p_gap_evt->conn_handle, m_flag_sec_proc, false);

    if (role == BLE_GAP_ROLE_INVALID)
    {
        /* Unlikely, but maybe possible? */
        return;
    }

    if (p_gap_evt->params.auth_status.bonded)
    {

        err_code = pdb_write_buf_store(peer_id, PM_PEER_DATA_ID_BONDING);
        if (err_code != NRF_SUCCESS)
        {
            /* Unexpected */
            smd_evt_t error_evt;

            error_evt.evt_id                            = SMD_EVT_ERROR_BONDING_INFO;
            error_evt.conn_handle                       = p_gap_evt->conn_handle;
            error_evt.params.error_bonding_info.peer_id = peer_id;
            error_evt.params.error_bonding_info.error   = err_code;

            evt_send(&error_evt);
        }

    }
    else if (ble_conn_state_user_flag_get(p_gap_evt->conn_handle, m_flag_sec_proc_new_peer))
    {
        ret_code_t err_code_free = im_peer_free(peer_id);
        UNUSED_VARIABLE(err_code_free); // Errors can be safely ignored.
    }

    smd_evt_t pairing_success_evt;

    pairing_success_evt.evt_id                            = SMD_EVT_PAIRING_SUCCESS;
    pairing_success_evt.conn_handle                       = p_gap_evt->conn_handle;
    pairing_success_evt.params.pairing_success.bonded     = p_gap_evt->params.auth_status.bonded;
    pairing_success_evt.params.pairing_success.mitm       = p_gap_evt->params.auth_status.sm1_levels.lv3;
    pairing_success_evt.params.pairing_success.kdist_own  = kdist_own;
    pairing_success_evt.params.pairing_success.kdist_peer = kdist_peer;

    evt_send(&pairing_success_evt);
    return;
}


/**@brief Function for cleaning up after a failed pairing procedure.
 *
 * @param[in]  conn_handle  The handle of the connection the pairing procedure happens on.
 * @param[in]  peer_id      The peer id used in the pairing procedure.
 * @param[in]  error        The error the procedure failed with.
 * @param[in]  error_src    The party that raised the error. See @ref BLE_GAP_SEC_STATUS_SOURCES.
 */
static void pairing_failure(uint16_t            conn_handle,
                            pm_peer_id_t        peer_id,
                            pm_sec_error_code_t error,
                            uint8_t             error_src)
{
    ret_code_t err_code = NRF_SUCCESS;

    smd_evt_t evt =
    {
        .evt_id      = SMD_EVT_PAIRING_FAIL,
        .conn_handle = conn_handle,
        .params =
        {
            .pairing_failed =
            {
                .error     = error,
                .error_src = error_src,
            }
        }
    };

    if (ble_conn_state_user_flag_get(conn_handle, m_flag_sec_proc_new_peer))
    {
        // The peer_id was created during the procedure, and should be freed, because no data is
        // stored under it.
        err_code = im_peer_free(peer_id);  // Attempt to free allocated peer.
        UNUSED_VARIABLE(err_code);
    }
    else
    {
        err_code = pdb_write_buf_release(peer_id, PM_PEER_DATA_ID_BONDING);
        if ((err_code != NRF_SUCCESS) && (err_code == NRF_ERROR_NOT_FOUND /* No buffer was allocated */))
        {
            smd_evt_t error_evt;
            error_evt.evt_id = SMD_EVT_ERROR_UNEXPECTED;
            error_evt.conn_handle = conn_handle;
            error_evt.params.error_unexpected.error = err_code;
            evt_send(&error_evt);
        }
    }

    ble_conn_state_user_flag_set(conn_handle, m_flag_sec_proc, false);

    evt_send(&evt);
    return;
}


/**@brief Function for cleaning up after a failed encryption procedure.
 *
 * @param[in]  conn_handle  The handle of the connection the encryption procedure happens on.
 * @param[in]  error        The error the procedure failed with.
 * @param[in]  error_src    The party that raised the error. See @ref BLE_GAP_SEC_STATUS_SOURCES.
 */
static void encryption_failure(uint16_t            conn_handle,
                               pm_sec_error_code_t error,
                               uint8_t             error_src)
{
    smd_evt_t evt =
    {
        .evt_id = SMD_EVT_LINK_ENCRYPTION_FAILED,
        .conn_handle = conn_handle,
        .params =
        {
            .link_encryption_failed =
            {
                .error     = error,
                .error_src = error_src,
            }
        }
    };

    ble_conn_state_user_flag_set(conn_handle, m_flag_sec_proc, false);

    evt_send(&evt);
    return;
}


/**@brief Function for possibly cleaning up after a failed pairing or encryption procedure.
 *
 * @param[in]  conn_handle  The handle of the connection the pairing procedure happens on.
 * @param[in]  peer_id      The peer id used in the pairing procedure.
 * @param[in]  error        The error the procedure failed with.
 * @param[in]  error_src    The party that raised the error. See @ref BLE_GAP_SEC_STATUS_SOURCES.
 */
static void link_secure_failure(uint16_t            conn_handle,
                                pm_sec_error_code_t error,
                                uint8_t             error_src)
{
    if (ble_conn_state_user_flag_get(conn_handle, m_flag_sec_proc))
    {
        pm_peer_id_t  peer_id = im_peer_id_get_by_conn_handle(conn_handle);

        if (peer_id != PM_PEER_ID_INVALID)
        {
            if (ble_conn_state_user_flag_get(conn_handle, m_flag_sec_proc_pairing))
            {
                pairing_failure(conn_handle, peer_id, error, error_src);
            }
            else
            {
                encryption_failure(conn_handle, error, error_src);
            }
        }
    }
}


/**@brief Function for processing the @ref BLE_GAP_EVT_DISCONNECT event from the SoftDevice.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void disconnect_process(ble_gap_evt_t * p_gap_evt)
{
    pm_sec_error_code_t error = (p_gap_evt->params.disconnected.reason
                                        == BLE_HCI_CONN_TERMINATED_DUE_TO_MIC_FAILURE)
                                ? PM_CONN_SEC_ERROR_MIC_FAILURE : PM_CONN_SEC_ERROR_DISCONNECT;

    link_secure_failure(p_gap_evt->conn_handle, error, BLE_GAP_SEC_STATUS_SOURCE_LOCAL);
}


/**@brief Function for processing the @ref BLE_GAP_EVT_AUTH_STATUS event from the SoftDevice, when
 *        the auth_status is failure.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void auth_status_failure_process(ble_gap_evt_t * p_gap_evt)
{
    link_secure_failure(p_gap_evt->conn_handle,
                        p_gap_evt->params.auth_status.auth_status,
                        p_gap_evt->params.auth_status.error_src);
}


/**@brief Function for processing the @ref BLE_GAP_EVT_AUTH_STATUS event from the SoftDevice.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void auth_status_process(ble_gap_evt_t * p_gap_evt)
{
    switch (p_gap_evt->params.auth_status.auth_status)
    {
        case BLE_GAP_SEC_STATUS_SUCCESS:
            auth_status_success_process(p_gap_evt);
            break;

        default:
            auth_status_failure_process(p_gap_evt);
            break;
    }
}


/**@brief Function for processing the @ref BLE_GAP_EVT_CONN_SEC_UPDATE event from the SoftDevice.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void conn_sec_update_process(ble_gap_evt_t * p_gap_evt)
{
    if (ble_conn_state_encrypted(p_gap_evt->conn_handle))
    {
        if (!ble_conn_state_user_flag_get(p_gap_evt->conn_handle, m_flag_sec_proc_pairing))
        {
            ble_conn_state_user_flag_set(p_gap_evt->conn_handle, m_flag_sec_proc, false);
        }

        smd_evt_t evt;

        evt.conn_handle = p_gap_evt->conn_handle;
        evt.evt_id = SMD_EVT_LINK_ENCRYPTION_UPDATE;
        evt.params.link_encryption_update.mitm_protected
                                = ble_conn_state_mitm_protected(p_gap_evt->conn_handle);
        evt_send(&evt);
    }
    else
    {
        encryption_failure(p_gap_evt->conn_handle,
                           PM_CONN_SEC_ERROR_PIN_OR_KEY_MISSING,
                           BLE_GAP_SEC_STATUS_SOURCE_REMOTE);
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


ret_code_t smd_init(void)
{
    NRF_PM_DEBUG_CHECK(!m_module_initialized);

    flag_id_init(&m_flag_sec_proc);
    flag_id_init(&m_flag_sec_proc_pairing);
    flag_id_init(&m_flag_sec_proc_new_peer);

    if ((m_flag_sec_proc          == BLE_CONN_STATE_USER_FLAG_INVALID) ||
        (m_flag_sec_proc_pairing  == BLE_CONN_STATE_USER_FLAG_INVALID) ||
        (m_flag_sec_proc_new_peer == BLE_CONN_STATE_USER_FLAG_INVALID))
    {
        return NRF_ERROR_INTERNAL;
    }

    m_module_initialized = true;

    return NRF_SUCCESS;
}


ret_code_t smd_params_reply(uint16_t                 conn_handle,
                            ble_gap_sec_params_t   * p_sec_params,
                            ble_gap_lesc_p256_pk_t * p_public_key)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    uint8_t              role = ble_conn_state_role(conn_handle);
    pm_peer_id_t         peer_id = PM_PEER_ID_INVALID;
    ret_code_t           err_code = NRF_SUCCESS;
    uint8_t              sec_status = BLE_GAP_SEC_STATUS_SUCCESS;
    ble_gap_sec_keyset_t sec_keyset;
    bool                 new_peer_created = false;

    memset(&sec_keyset, 0, sizeof(ble_gap_sec_keyset_t));

    if (role == BLE_GAP_ROLE_INVALID)
    {
        return BLE_ERROR_INVALID_CONN_HANDLE;
    }

    if (p_sec_params == NULL)
    {
        // NULL params means reject pairing.
        sec_status = BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP;
    }
    else if (p_sec_params->bond)
    {
        // Bonding is to be performed, prepare to receive bonding data.
        pm_peer_data_t       peer_data;

        peer_id = im_peer_id_get_by_conn_handle(conn_handle);

        if (peer_id == PM_PEER_ID_INVALID)
        {
            // Peer is unknown to us, allocate a new peer ID for it.
            peer_id = pdb_peer_allocate();
            if (peer_id != PM_PEER_ID_INVALID)
            {
                new_peer_created = true;
            }
            else
            {
                err_code = NRF_ERROR_INTERNAL;
            }
        }

        if (err_code == NRF_SUCCESS)
        {
            // Peer ID is ready, acquire a memory buffer to receive bonding data into.
            err_code = pdb_write_buf_get(peer_id, PM_PEER_DATA_ID_BONDING, 1, &peer_data);
            if (err_code == NRF_SUCCESS)
            {
                memset(peer_data.p_bonding_data, 0, sizeof(pm_peer_data_bonding_t));

                peer_data.p_bonding_data->own_role = role;

                sec_keyset.keys_own.p_enc_key  = &peer_data.p_bonding_data->own_ltk;
                sec_keyset.keys_own.p_pk       = p_public_key;
                sec_keyset.keys_peer.p_enc_key = &peer_data.p_bonding_data->peer_ltk;
                sec_keyset.keys_peer.p_id_key  = &peer_data.p_bonding_data->peer_ble_id;
                sec_keyset.keys_peer.p_pk      = &m_peer_pk;

                // Retrieve the address the peer used during connection establishment.
                // This address will be overwritten if ID is shared. Should not fail.
                ret_code_t err_code_addr = im_ble_addr_get(conn_handle,
                    &peer_data.p_bonding_data->peer_ble_id.id_addr_info);
                UNUSED_VARIABLE(err_code_addr);

                // Buffer is OK, reserve room in flash for the data.
                err_code = pdb_write_buf_store_prepare(peer_id, PM_PEER_DATA_ID_BONDING);
            }
        }
    }
    else
    {
        // Pairing, no bonding.

        sec_keyset.keys_own.p_pk  = p_public_key;
        sec_keyset.keys_peer.p_pk = &m_peer_pk;
    }

    if (err_code == NRF_SUCCESS)
    {
        // Everything OK, reply to SoftDevice. If an error happened, the user is given an
        // opportunity to change the parameters and retry the call.
        if (role == BLE_GAP_ROLE_CENTRAL)
        {
            err_code = sd_ble_gap_sec_params_reply(conn_handle, sec_status, NULL, &sec_keyset);
        }
        else
        {
            err_code = sd_ble_gap_sec_params_reply(conn_handle, sec_status, p_sec_params, &sec_keyset);

            if ((p_sec_params != NULL) && (err_code == NRF_SUCCESS))
            {
                pm_conn_sec_procedure_t procedure = p_sec_params->bond
                                               ? PM_LINK_SECURED_PROCEDURE_BONDING
                                               : PM_LINK_SECURED_PROCEDURE_PAIRING;
                sec_start_send(conn_handle, procedure);
            }
        }
    }

    sec_proc_start(conn_handle,
                   peer_id,
                   (err_code == NRF_SUCCESS) && (sec_status != BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP),
                   true,
                   new_peer_created);

    return err_code;
}


static ret_code_t link_secure_central_existing_peer(uint16_t                  conn_handle,
                                                    ble_gap_sec_params_t    * p_sec_params,
                                                    bool                      force_repairing,
                                                    pm_peer_id_t              peer_id,
                                                    pm_conn_sec_procedure_t * procedure)
{
    pm_peer_data_flash_t      peer_data;
    pm_peer_data_t            dummy_peer_data;
    ret_code_t                err_code;
    ble_gap_enc_key_t const * p_existing_key = NULL;
    bool                      lesc = false;

    err_code = pdb_peer_data_ptr_get(peer_id, PM_PEER_DATA_ID_BONDING, &peer_data);

    if (err_code == NRF_SUCCESS)
    {
        // Use peer's key since they are peripheral.
        p_existing_key = &(peer_data.p_bonding_data->peer_ltk);

        lesc = peer_data.p_bonding_data->own_ltk.enc_info.lesc;
        if  (lesc) // LESC was used during bonding.
        {
            // For LESC, always use own key.
            p_existing_key = &(peer_data.p_bonding_data->own_ltk);
        }
    }

    if     (!force_repairing
         && (err_code == NRF_SUCCESS)
         && (p_existing_key != NULL)
         && (lesc || im_master_id_is_valid(&(p_existing_key->master_id)))) /* There is a valid LTK stored. */
         //&& (p_existing_key->enc_info.auth >= p_sec_params->mitm)          /* The requested MITM security is at or below the existing level. */
         //&& (!p_sec_params->mitm || (lesc >= p_sec_params->lesc)))         /* The requested LESC security is at or below the existing level. We only care about LESC if MITM is required. */
    {
        err_code = sd_ble_gap_encrypt(conn_handle, &(p_existing_key->master_id), &(p_existing_key->enc_info));

        *procedure = PM_LINK_SECURED_PROCEDURE_ENCRYPTION;
    }
    else if ((err_code == NRF_SUCCESS) || (err_code == NRF_ERROR_NOT_FOUND))
    {
        /* Re-pairing is needed, because there is no LTK available or the existing key is not
           secure enough */
        err_code = NRF_SUCCESS;

        if (p_sec_params->bond)
        {
            err_code = pdb_write_buf_get(peer_id, PM_PEER_DATA_ID_BONDING, 1, &dummy_peer_data);
            if (err_code == NRF_SUCCESS)
            {
                err_code = pdb_write_buf_store_prepare(peer_id, PM_PEER_DATA_ID_BONDING);
            }
        }

        if (err_code == NRF_SUCCESS)
        {
            err_code = sd_ble_gap_authenticate(conn_handle, p_sec_params);
        }

        if (err_code != NRF_SUCCESS)
        {
            ret_code_t err_code_release = pdb_write_buf_release(peer_id, PM_PEER_DATA_ID_BONDING);
            if ((err_code_release != NRF_SUCCESS) && (err_code_release != NRF_ERROR_NOT_FOUND))
            {
                err_code = NRF_ERROR_INTERNAL;
            }
        }
    }

    sec_proc_start(conn_handle,
                   peer_id,
                   err_code == NRF_SUCCESS,
                   *procedure != PM_LINK_SECURED_PROCEDURE_ENCRYPTION,
                   false);

    return err_code;
}


static ret_code_t link_secure_central_new_peer(uint16_t               conn_handle,
                                               ble_gap_sec_params_t * p_sec_params)
{
    pm_peer_id_t    peer_id = pdb_peer_allocate();
    pm_peer_data_t  dummy_peer_data;
    ret_code_t      err_code;

    if (peer_id != PM_PEER_ID_INVALID)
    {
        err_code = pdb_write_buf_get(peer_id, PM_PEER_DATA_ID_BONDING, 1, &dummy_peer_data);
        if (err_code == NRF_SUCCESS)
        {
            err_code = pdb_write_buf_store_prepare(peer_id, PM_PEER_DATA_ID_BONDING);
        }

        if (err_code == NRF_SUCCESS)
        {
            err_code = sd_ble_gap_authenticate(conn_handle, p_sec_params);
        }

        if (err_code != NRF_SUCCESS)
        {
            ret_code_t err_code_free = pdb_write_buf_release(peer_id, PM_PEER_DATA_ID_BONDING);
            if ((err_code_free != NRF_SUCCESS) && (err_code_free != NRF_ERROR_NOT_FOUND))
            {
                err_code = NRF_ERROR_INTERNAL;
            }
        }
    }
    else
    {
        err_code = NRF_ERROR_INTERNAL;
    }

    sec_proc_start(conn_handle,
                   peer_id,
                   err_code == NRF_SUCCESS,
                   true,
                   peer_id != PM_PEER_ID_INVALID);

    return err_code;
}


static ret_code_t link_secure_central(uint16_t               conn_handle,
                                      ble_gap_sec_params_t * p_sec_params,
                                      bool                   force_repairing)
{
    ret_code_t           err_code;
    pm_peer_id_t         peer_id;

    if (p_sec_params == NULL)
    {
        return sd_ble_gap_authenticate(conn_handle, NULL);
    }

    pm_conn_sec_procedure_t procedure = p_sec_params->bond ? PM_LINK_SECURED_PROCEDURE_BONDING
                                                           : PM_LINK_SECURED_PROCEDURE_PAIRING;

    peer_id = im_peer_id_get_by_conn_handle(conn_handle);

    if (peer_id != PM_PEER_ID_INVALID)
    {
        // There is already data in flash for this peer.
        err_code = link_secure_central_existing_peer(conn_handle,
                                                     p_sec_params,
                                                     force_repairing,
                                                     peer_id,
                                                     &procedure);
    }
    else if (p_sec_params->bond)
    {
        // New peer is required.
        err_code = link_secure_central_new_peer(conn_handle, p_sec_params);
    }
    else
    {
        // No bonding, only pairing.
        err_code = sd_ble_gap_authenticate(conn_handle, p_sec_params);

        sec_proc_start(conn_handle, peer_id, err_code == NRF_SUCCESS, true, false);
    }

    if (err_code == NRF_SUCCESS)
    {
        sec_start_send(conn_handle, procedure);
    }

    return err_code;
}


static ret_code_t link_secure_peripheral(uint16_t conn_handle, ble_gap_sec_params_t * p_sec_params)
{
    // This should never happen for a peripheral.
    NRF_PM_DEBUG_CHECK(p_sec_params != NULL);

    // VERIFY_PARAM_NOT_NULL(p_sec_params);

    ret_code_t err_code = sd_ble_gap_authenticate(conn_handle, p_sec_params);

    return err_code;
}


ret_code_t smd_link_secure(uint16_t               conn_handle,
                           ble_gap_sec_params_t * p_sec_params,
                           bool                   force_repairing)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    uint8_t role = ble_conn_state_role(conn_handle);

    switch (role)
    {
        case BLE_GAP_ROLE_CENTRAL:
            return link_secure_central(conn_handle, p_sec_params, force_repairing);

        case BLE_GAP_ROLE_PERIPH:
            return link_secure_peripheral(conn_handle, p_sec_params);

        default:
            return BLE_ERROR_INVALID_CONN_HANDLE;
    }
}


void smd_ble_evt_handler(ble_evt_t * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_DISCONNECTED:
            disconnect_process(&(p_ble_evt->evt.gap_evt));
            break;

        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
            sec_params_request_process(&(p_ble_evt->evt.gap_evt));
            break;

        case BLE_GAP_EVT_SEC_INFO_REQUEST:
            sec_info_request_process(&(p_ble_evt->evt.gap_evt));
            break;

        case BLE_GAP_EVT_SEC_REQUEST:
            sec_request_process(&(p_ble_evt->evt.gap_evt));
            break;

        case BLE_GAP_EVT_AUTH_STATUS:
            auth_status_process(&(p_ble_evt->evt.gap_evt));
            break;

        case BLE_GAP_EVT_CONN_SEC_UPDATE:
            conn_sec_update_process(&(p_ble_evt->evt.gap_evt));
            break;
    };
}
#endif //NRF_MODULE_ENABLED(PEER_MANAGER)
