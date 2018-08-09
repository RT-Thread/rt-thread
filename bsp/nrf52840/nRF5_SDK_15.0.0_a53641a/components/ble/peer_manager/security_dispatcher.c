/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#include "ble_err.h"
#include "ble_conn_state.h"
#include "peer_manager_types.h"
#include "peer_database.h"
#include "id_manager.h"

#ifndef PM_CENTRAL_ENABLED
    #define PM_CENTRAL_ENABLED 1
#endif

// The number of registered event handlers.
#define SMD_EVENT_HANDLERS_CNT      (sizeof(m_evt_handlers) / sizeof(m_evt_handlers[0]))

STATIC_ASSERT((NRF_SDH_BLE_CENTRAL_LINK_COUNT == 0) || PM_CENTRAL_ENABLED,
               "Peer Manager Central operation must be enabled when using central links.");

// Security Dispacher event handlers in Security Manager and GATT Cache Manager.
extern void sm_smd_evt_handler(pm_evt_t * p_event);

// Security Dispatcher events' handlers.
// The number of elements in this array is SMD_EVENT_HANDLERS_CNT.
static pm_evt_handler_internal_t const m_evt_handlers[] =
{
    sm_smd_evt_handler
};

static bool                          m_module_initialized;

static ble_conn_state_user_flag_id_t m_flag_sec_proc          = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t m_flag_sec_proc_pairing  = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t m_flag_sec_proc_bonding  = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t m_flag_sec_proc_new_peer = BLE_CONN_STATE_USER_FLAG_INVALID;
static ble_conn_state_user_flag_id_t m_flag_allow_repairing   = BLE_CONN_STATE_USER_FLAG_INVALID;

static ble_gap_lesc_p256_pk_t        m_peer_pk;


static __INLINE bool sec_procedure(uint16_t conn_handle)
{
    return ble_conn_state_user_flag_get(conn_handle, m_flag_sec_proc);
}

static __INLINE bool pairing(uint16_t conn_handle)
{
    return ble_conn_state_user_flag_get(conn_handle, m_flag_sec_proc_pairing);
}

static __INLINE bool bonding(uint16_t conn_handle)
{
    return ble_conn_state_user_flag_get(conn_handle, m_flag_sec_proc_bonding);
}

static __INLINE bool peer_created(uint16_t conn_handle)
{
    return ble_conn_state_user_flag_get(conn_handle, m_flag_sec_proc_new_peer);
}

static __INLINE bool allow_repairing(uint16_t conn_handle)
{
    return ble_conn_state_user_flag_get(conn_handle, m_flag_allow_repairing);
}


/**@brief Function for sending an SMD event to all event handlers.
 *
 * @param[in]  p_event  The event to pass to all event handlers.
 */
static void evt_send(pm_evt_t * p_event)
{
    p_event->peer_id = im_peer_id_get_by_conn_handle(p_event->conn_handle);

    for (uint32_t i = 0; i < SMD_EVENT_HANDLERS_CNT; i++)
    {
        m_evt_handlers[i](p_event);
    }
}


/**@brief Function for sending a PM_EVT_CONN_SEC_START event.
 *
 * @param[in]  conn_handle  The connection handle the event pertains to.
 * @param[in]  procedure    The procedure that has started on the connection.
 */
static void sec_start_send(uint16_t                conn_handle,
                           pm_conn_sec_procedure_t procedure)
{
    pm_evt_t evt =
    {
        .evt_id      = PM_EVT_CONN_SEC_START,
        .conn_handle = conn_handle,
        .params      = {.conn_sec_start = {.procedure = procedure}}
    };
    evt_send(&evt);
}


/**@brief Function for sending a PM_EVT_ERROR_UNEXPECTED event.
 *
 * @param[in]  conn_handle  The connection handle the event pertains to.
 * @param[in]  err_code     The unexpected error that occurred.
 */
static void send_unexpected_error(uint16_t conn_handle, ret_code_t err_code)
{
    pm_evt_t error_evt =
    {
        .evt_id = PM_EVT_ERROR_UNEXPECTED,
        .conn_handle = conn_handle,
        .params =
        {
            .error_unexpected =
            {
                .error = err_code,
            }
        }
    };
    evt_send(&error_evt);
}


/**@brief Function for cleaning up after a failed security procedure.
 *
 * @param[in]  conn_handle  The handle of the connection the security procedure happens on.
 * @param[in]  procedure    The procedure that failed.
 * @param[in]  error        The error the procedure failed with.
 * @param[in]  error_src    The party that raised the error. See @ref BLE_GAP_SEC_STATUS_SOURCES.
 */
static void conn_sec_failure(uint16_t                conn_handle,
                             pm_conn_sec_procedure_t procedure,
                             pm_sec_error_code_t     error,
                             uint8_t                 error_src)
{
    pm_evt_t evt =
    {
        .evt_id      = PM_EVT_CONN_SEC_FAILED,
        .conn_handle = conn_handle,
        .params      =
        {
            .conn_sec_failed =
            {
                .procedure = procedure,
                .error     = error,
                .error_src = error_src,
            }
        }
    };

    ble_conn_state_user_flag_set(conn_handle, m_flag_sec_proc, false);

    evt_send(&evt);
    return;
}


/**@brief Function for cleaning up after a failed pairing procedure.
 *
 * @param[in]  conn_handle  The handle of the connection the pairing procedure happens on.
 * @param[in]  error        The error the procedure failed with.
 * @param[in]  error_src    The source of the error (local or remote). See @ref
 *                          BLE_GAP_SEC_STATUS_SOURCES.
 */
static void pairing_failure(uint16_t            conn_handle,
                            pm_sec_error_code_t error,
                            uint8_t             error_src)
{
    ret_code_t              err_code  = NRF_SUCCESS;
    pm_peer_id_t            peer_id   = im_peer_id_get_by_conn_handle(conn_handle);
    pm_conn_sec_procedure_t procedure = bonding(conn_handle) ? PM_CONN_SEC_PROCEDURE_BONDING
                                                             : PM_CONN_SEC_PROCEDURE_PAIRING;

    if (peer_created(conn_handle))
    {
        // The peer_id was created during the procedure, and should be freed, because no data is
        // stored under it.
        err_code = im_peer_free(peer_id);  // Attempt to free allocated peer.
        UNUSED_VARIABLE(err_code);
    }
    else if(peer_id != PM_PEER_ID_INVALID)
    {
        err_code = pdb_write_buf_release(peer_id, PM_PEER_DATA_ID_BONDING);
        if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_NOT_FOUND /* No buffer was allocated */))
        {
            send_unexpected_error(conn_handle, err_code);
        }
    }

    conn_sec_failure(conn_handle, procedure, error, error_src);

    return;
}


/**@brief Function for cleaning up after a failed encryption procedure.
 *
 * @param[in]  conn_handle  The handle of the connection the encryption procedure happens on.
 * @param[in]  error        The error the procedure failed with.
 * @param[in]  error_src    The party that raised the error. See @ref BLE_GAP_SEC_STATUS_SOURCES.
 */
static __INLINE void encryption_failure(uint16_t            conn_handle,
                                        pm_sec_error_code_t error,
                                        uint8_t             error_src)
{
    conn_sec_failure(conn_handle, PM_CONN_SEC_PROCEDURE_ENCRYPTION, error, error_src);

    return;
}


/**@brief Function for possibly cleaning up after a failed pairing or encryption procedure.
 *
 * @param[in]  conn_handle  The handle of the connection the pairing procedure happens on.
 * @param[in]  error        The error the procedure failed with.
 * @param[in]  error_src    The party that raised the error. See @ref BLE_GAP_SEC_STATUS_SOURCES.
 */
static void link_secure_failure(uint16_t            conn_handle,
                                pm_sec_error_code_t error,
                                uint8_t             error_src)
{
    if (sec_procedure(conn_handle))
    {
        if (pairing(conn_handle))
        {
            pairing_failure(conn_handle, error, error_src);
        }
        else
        {
            encryption_failure(conn_handle, error, error_src);
        }
    }
}


/**@brief Function for administrative actions to be taken when a security process has started.
 *
 * @param[in]  conn_handle  The connection the security process was attempted on.
 * @param[in]  success      Whether the procedure was started successfully.
 * @param[in]  procedure    The procedure that was started.
 */
static void sec_proc_start(uint16_t                conn_handle,
                           bool                    success,
                           pm_conn_sec_procedure_t procedure)
{
    ble_conn_state_user_flag_set(conn_handle, m_flag_sec_proc, success);
    if (success)
    {
        ble_conn_state_user_flag_set(conn_handle,
                                     m_flag_sec_proc_pairing,
                                     (procedure != PM_CONN_SEC_PROCEDURE_ENCRYPTION));
        ble_conn_state_user_flag_set(conn_handle,
                                     m_flag_sec_proc_bonding,
                                     (procedure == PM_CONN_SEC_PROCEDURE_BONDING));
        ble_conn_state_user_flag_set(conn_handle, m_flag_sec_proc_new_peer, false);
        sec_start_send(conn_handle, procedure);
    }
}



/**@brief Function for administrative actions to be taken during the course of a security process.
 *
 * @param[in]  conn_handle       The connection the security process was attempted on.
 * @param[in]  peer_id           The peer ID given to the connected peer.
 * @param[in]  success           Whether the process was started successfully.
 * @param[in]  new_peer_created  Whether a new peer was created during the process attempt.
 */
static void sec_proc_housekeeping(uint16_t     conn_handle,
                                  pm_peer_id_t peer_id,
                                  bool         success,
                                  bool         new_peer_created)
{
    if (success)
    {
        if (new_peer_created)
        {
            ble_conn_state_user_flag_set(conn_handle, m_flag_sec_proc_new_peer, true);
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
static void sec_info_request_process(ble_gap_evt_t const * p_gap_evt)
{
    ret_code_t                 err_code;
    ble_gap_enc_info_t const * p_enc_info = NULL;
    pm_peer_data_flash_t       peer_data;
    pm_peer_id_t               peer_id = im_peer_id_get_by_master_id(
                                                    &p_gap_evt->params.sec_info_request.master_id);

    if (peer_id == PM_PEER_ID_INVALID)
    {
        peer_id = im_peer_id_get_by_conn_handle(p_gap_evt->conn_handle);
    }
    else
    {
        // The peer might have been unrecognized until now (since connecting). E.g. if using a
        // random non-resolvable advertising address. Report the discovered peer ID just in case.
        im_new_peer_id(p_gap_evt->conn_handle, peer_id);
    }

    sec_proc_start(p_gap_evt->conn_handle, true, PM_CONN_SEC_PROCEDURE_ENCRYPTION);

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

    err_code = sd_ble_gap_sec_info_reply(p_gap_evt->conn_handle, p_enc_info, NULL, NULL);

    if (err_code != NRF_SUCCESS)
    {
        sec_proc_housekeeping(p_gap_evt->conn_handle, peer_id, false, false);
        send_unexpected_error(p_gap_evt->conn_handle, err_code);
    }
    else if (p_enc_info == NULL)
    {
        sec_proc_housekeeping(p_gap_evt->conn_handle, peer_id, false, false);
        encryption_failure(p_gap_evt->conn_handle,
                           PM_CONN_SEC_ERROR_PIN_OR_KEY_MISSING,
                           BLE_GAP_SEC_STATUS_SOURCE_LOCAL);
    }

    return;
}


/**@brief Function for sending a CONFIG_REQ event.
 *
 * @param[in]  conn_handle  The connection the sec parameters are needed for.
 */
static void send_config_req(uint16_t conn_handle)
{
    pm_evt_t evt;
    memset(&evt, 0, sizeof(evt));

    evt.evt_id      = PM_EVT_CONN_SEC_CONFIG_REQ;
    evt.conn_handle = conn_handle;

    evt_send(&evt);
}


void smd_conn_sec_config_reply(uint16_t conn_handle, pm_conn_sec_config_t * p_conn_sec_config)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_conn_sec_config != NULL);

    ble_conn_state_user_flag_set(conn_handle,
                                 m_flag_allow_repairing,
                                 p_conn_sec_config->allow_repairing);
}


/**@brief Function for processing the @ref BLE_GAP_EVT_DISCONNECT event from the SoftDevice.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void disconnect_process(ble_gap_evt_t const * p_gap_evt)
{
    pm_sec_error_code_t error = (p_gap_evt->params.disconnected.reason
                                        == BLE_HCI_CONN_TERMINATED_DUE_TO_MIC_FAILURE)
                                ? PM_CONN_SEC_ERROR_MIC_FAILURE : PM_CONN_SEC_ERROR_DISCONNECT;

    link_secure_failure(p_gap_evt->conn_handle, error, BLE_GAP_SEC_STATUS_SOURCE_LOCAL);
}


/**@brief Function for sending a PARAMS_REQ event.
 *
 * @param[in]  conn_handle    The connection the security parameters are needed for.
 * @param[in]  p_peer_params  The security parameters from the peer. Can be NULL if the peer's parameters
 *                            are not yet available.
 */
static void send_params_req(uint16_t conn_handle, ble_gap_sec_params_t const * p_peer_params)
{
    pm_evt_t evt =
    {
        .evt_id      = PM_EVT_CONN_SEC_PARAMS_REQ,
        .conn_handle = conn_handle,
        .params      =
        {
            .conn_sec_params_req =
            {
                .p_peer_params = p_peer_params
            },
        },
    };

    evt_send(&evt);
}


/**@brief Function for processing the @ref BLE_GAP_EVT_SEC_PARAMS_REQUEST event from the SoftDevice.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void sec_params_request_process(ble_gap_evt_t const * p_gap_evt)
{
    if (ble_conn_state_role(p_gap_evt->conn_handle) == BLE_GAP_ROLE_PERIPH)
    {
        sec_proc_start(p_gap_evt->conn_handle,
                       true,
                       p_gap_evt->params.sec_params_request.peer_params.bond
                                               ? PM_CONN_SEC_PROCEDURE_BONDING
                                               : PM_CONN_SEC_PROCEDURE_PAIRING);
    }

    send_params_req(p_gap_evt->conn_handle, &p_gap_evt->params.sec_params_request.peer_params);
    return;
}


/**@brief Function for processing the @ref BLE_GAP_EVT_AUTH_STATUS event from the SoftDevice, when
 *        the auth_status is success.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void auth_status_success_process(ble_gap_evt_t const * p_gap_evt)
{
    ret_code_t           err_code    = NRF_SUCCESS;
    uint16_t             conn_handle = p_gap_evt->conn_handle;
    pm_peer_id_t         peer_id     = im_peer_id_get_by_conn_handle(conn_handle);
    pm_peer_id_t         new_peer_id = peer_id;
    pm_peer_data_t       peer_data;
    bool                 data_stored = false;

    ble_conn_state_user_flag_set(conn_handle, m_flag_sec_proc, false);

    if (p_gap_evt->params.auth_status.bonded)
    {
        pm_peer_id_t duplicate_peer_id = PM_PEER_ID_INVALID;
        data_stored = true;

        err_code = pdb_write_buf_get(peer_id, PM_PEER_DATA_ID_BONDING, 1, &peer_data);
        if (err_code != NRF_SUCCESS)
        {
            send_unexpected_error(conn_handle, err_code);
            data_stored = false;
        }
        else
        {
            duplicate_peer_id = im_find_duplicate_bonding_data(peer_data.p_bonding_data,
                                                               PM_PEER_ID_INVALID);
        }

        if (duplicate_peer_id != PM_PEER_ID_INVALID)
        {
            // The peer has been identified as someone we have already bonded with.
            new_peer_id = duplicate_peer_id;
            im_new_peer_id(conn_handle, new_peer_id);

            // If the flag is true, the configuration has been requested before.
            if (!allow_repairing(conn_handle))
            {
                send_config_req(conn_handle);
                if (!allow_repairing(conn_handle))
                {
                    data_stored = false;
                }
            }
        }

        if (data_stored)
        {
            err_code = pdb_write_buf_store(peer_id, PM_PEER_DATA_ID_BONDING, new_peer_id);
            if (err_code != NRF_SUCCESS)
            {
                /* Unexpected */
                send_unexpected_error(conn_handle, err_code);
                data_stored = false;
            }
        }

        if ((duplicate_peer_id != PM_PEER_ID_INVALID) && peer_created(conn_handle))
        {
            // We already have a bond with the peer. Now that the data has been stored for the
            // existing peer, the peer created for this bonding procedure can be freed.
            ret_code_t err_code_free = im_peer_free(peer_id);
            UNUSED_VARIABLE(err_code_free); // Errors can be safely ignored.
        }
    }
    else if (peer_created(conn_handle))
    {
        ret_code_t err_code_free = im_peer_free(peer_id);
        UNUSED_VARIABLE(err_code_free); // Errors can be safely ignored.
    }
    else
    {
        // No action.
    }

    pm_evt_t pairing_success_evt;

    pairing_success_evt.evt_id                                = PM_EVT_CONN_SEC_SUCCEEDED;
    pairing_success_evt.conn_handle                           = conn_handle;
    pairing_success_evt.params.conn_sec_succeeded.procedure   = p_gap_evt->params.auth_status.bonded
                                                              ? PM_CONN_SEC_PROCEDURE_BONDING
                                                              : PM_CONN_SEC_PROCEDURE_PAIRING;
    pairing_success_evt.params.conn_sec_succeeded.data_stored = data_stored;

    evt_send(&pairing_success_evt);

    return;
}


/**@brief Function for processing the @ref BLE_GAP_EVT_AUTH_STATUS event from the SoftDevice, when
 *        the auth_status is failure.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void auth_status_failure_process(ble_gap_evt_t const * p_gap_evt)
{
    link_secure_failure(p_gap_evt->conn_handle,
                        p_gap_evt->params.auth_status.auth_status,
                        p_gap_evt->params.auth_status.error_src);
}


/**@brief Function for processing the @ref BLE_GAP_EVT_AUTH_STATUS event from the SoftDevice.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void auth_status_process(ble_gap_evt_t const * p_gap_evt)
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
static void conn_sec_update_process(ble_gap_evt_t const * p_gap_evt)
{
    if (!pairing(p_gap_evt->conn_handle))
    {
        // This is an encryption procedure (not pairing), so this event marks the end of the procedure.

        if (!ble_conn_state_encrypted(p_gap_evt->conn_handle))
        {
            encryption_failure(p_gap_evt->conn_handle,
                               PM_CONN_SEC_ERROR_PIN_OR_KEY_MISSING,
                               BLE_GAP_SEC_STATUS_SOURCE_REMOTE);
        }
        else
        {
            ble_conn_state_user_flag_set(p_gap_evt->conn_handle, m_flag_sec_proc, false);

            pm_evt_t evt;

            evt.evt_id                                = PM_EVT_CONN_SEC_SUCCEEDED;
            evt.conn_handle                           = p_gap_evt->conn_handle;
            evt.params.conn_sec_succeeded.procedure   = PM_CONN_SEC_PROCEDURE_ENCRYPTION;
            evt.params.conn_sec_succeeded.data_stored = false;

            evt_send(&evt);
        }
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
    flag_id_init(&m_flag_sec_proc_bonding);
    flag_id_init(&m_flag_sec_proc_new_peer);
    flag_id_init(&m_flag_allow_repairing);

    if ((m_flag_sec_proc          == BLE_CONN_STATE_USER_FLAG_INVALID) ||
        (m_flag_sec_proc_pairing  == BLE_CONN_STATE_USER_FLAG_INVALID) ||
        (m_flag_sec_proc_bonding  == BLE_CONN_STATE_USER_FLAG_INVALID) ||
        (m_flag_sec_proc_new_peer == BLE_CONN_STATE_USER_FLAG_INVALID) ||
        (m_flag_allow_repairing   == BLE_CONN_STATE_USER_FLAG_INVALID))
    {
        return NRF_ERROR_INTERNAL;
    }

    m_module_initialized = true;

    return NRF_SUCCESS;
}


/**@brief Function for putting retrieving a buffer and putting pointers into a @ref ble_gap_sec_keyset_t.
 *
 * @param[in]  conn_handle   The connection the security procedure is happening on.
 * @param[in]  peer_id       The peer the security procedure is happening with.
 * @param[in]  role          Our role in the connection.
 * @param[in]  p_public_key  Pointer to a buffer holding the public key, or NULL.
 * @param[out] p_sec_keyset  Pointer to the keyset to be filled.
 *
 * @retval NRF_SUCCESS              Success.
 * @retval NRF_ERROR_STORAGE_FULL   Not enough room in persistent storage.
 * @retval NRF_ERROR_BUSY           Could not process request at this time. Reattempt later.
 * @retval NRF_ERROR_INVALID_PARAM  Data ID or Peer ID was invalid or unallocated.
 * @retval NRF_ERROR_INTERNAL       Fatal error.
 */
static ret_code_t sec_keyset_fill(uint16_t                 conn_handle,
                                  pm_peer_id_t             peer_id,
                                  uint8_t                  role,
                                  ble_gap_lesc_p256_pk_t * p_public_key,
                                  ble_gap_sec_keyset_t   * p_sec_keyset)
{
    ret_code_t     err_code;
    pm_peer_data_t peer_data;

    if (p_sec_keyset == NULL)
    {
        return NRF_ERROR_INTERNAL;
    }

    // Acquire a memory buffer to receive bonding data into.
    err_code = pdb_write_buf_get(peer_id, PM_PEER_DATA_ID_BONDING, 1, &peer_data);

    if (err_code == NRF_ERROR_BUSY)
    {
        // No action.
    }
    else if (err_code != NRF_SUCCESS)
    {
        err_code = NRF_ERROR_INTERNAL;
    }
    else /* if (err_code == NRF_SUCCESS) */
    {
        memset(peer_data.p_bonding_data, 0, sizeof(pm_peer_data_bonding_t));

        peer_data.p_bonding_data->own_role = role;

        p_sec_keyset->keys_own.p_enc_key  = &peer_data.p_bonding_data->own_ltk;
        p_sec_keyset->keys_own.p_pk       = p_public_key;
        p_sec_keyset->keys_peer.p_enc_key = &peer_data.p_bonding_data->peer_ltk;
        p_sec_keyset->keys_peer.p_id_key  = &peer_data.p_bonding_data->peer_ble_id;
        p_sec_keyset->keys_peer.p_pk      = &m_peer_pk;

        // Retrieve the address the peer used during connection establishment.
        // This address will be overwritten if ID is shared. Should not fail.
        err_code = im_ble_addr_get(conn_handle, &peer_data.p_bonding_data->peer_ble_id.id_addr_info);
        if (err_code != NRF_SUCCESS)
        {
            return NRF_ERROR_INTERNAL;
        }

        // Buffer is OK, reserve room in flash for the data.
        err_code = pdb_write_buf_store_prepare(peer_id, PM_PEER_DATA_ID_BONDING);
        if (err_code == NRF_ERROR_NOT_FOUND)
        {
            return NRF_ERROR_INTERNAL;
        }
    }

    return err_code;
}


ret_code_t smd_params_reply(uint16_t                 conn_handle,
                            ble_gap_sec_params_t   * p_sec_params,
                            ble_gap_lesc_p256_pk_t * p_public_key)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    uint8_t              role             = ble_conn_state_role(conn_handle);
    pm_peer_id_t         peer_id          = PM_PEER_ID_INVALID;
    ret_code_t           err_code         = NRF_SUCCESS;
    uint8_t              sec_status       = BLE_GAP_SEC_STATUS_SUCCESS;
    bool                 new_peer_created = peer_created(conn_handle);
    ble_gap_sec_keyset_t sec_keyset;

    memset(&sec_keyset, 0, sizeof(ble_gap_sec_keyset_t));
    if (role == BLE_GAP_ROLE_PERIPH)
    {
        // Set the default value for allowing repairing at the start of the sec proc. (for peripheral)
        ble_conn_state_user_flag_set(conn_handle, m_flag_allow_repairing, false);
    }

    if (role == BLE_GAP_ROLE_INVALID)
    {
        return BLE_ERROR_INVALID_CONN_HANDLE;
    }

    if (p_sec_params == NULL)
    {
        // NULL params means reject pairing.
        sec_status = BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP;
    }
    else if (!p_sec_params->bond)
    {
        // Pairing, no bonding.

        sec_keyset.keys_own.p_pk  = p_public_key;
        sec_keyset.keys_peer.p_pk = &m_peer_pk;
    }
    else
    {
        // Bonding is to be performed, prepare to receive bonding data.

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
        else if (role == BLE_GAP_ROLE_PERIPH && !allow_repairing(conn_handle))
        {
            // Bond already exists. Reject the pairing request if the user doesn't intervene.
            // send_config_req(conn_handle, peer_id);
            send_config_req(conn_handle);
            if (!allow_repairing(conn_handle))
            {
                // Reject pairing.
                sec_status = BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP;
            }
        }

        if ((sec_status != BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP) && (err_code == NRF_SUCCESS))
        {
            err_code = sec_keyset_fill(conn_handle, peer_id, role, p_public_key, &sec_keyset);
        }
    }

    if (err_code == NRF_SUCCESS)
    {
        // Everything OK, reply to SoftDevice. If an error happened, the user is given an
        // opportunity to change the parameters and retry the call.
        if (role == BLE_GAP_ROLE_PERIPH)
        {
            err_code = sd_ble_gap_sec_params_reply(conn_handle, sec_status, p_sec_params, &sec_keyset);
        }
        else
        {
            err_code = sd_ble_gap_sec_params_reply(conn_handle, sec_status, NULL, &sec_keyset);
        }
    }

    sec_proc_housekeeping(conn_handle,
                          peer_id,
                          (err_code == NRF_SUCCESS) && (sec_status == BLE_GAP_SEC_STATUS_SUCCESS),
                          new_peer_created);

    return err_code;
}


#if PM_CENTRAL_ENABLED
/**@brief Function for initiating encryption as a central. See @ref smd_link_secure for more info.
 */
static ret_code_t link_secure_central_encryption(uint16_t     conn_handle,
                                                 pm_peer_id_t peer_id)
{
    pm_peer_data_flash_t      peer_data;
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

    if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_NOT_FOUND))
    {
        if (err_code != NRF_ERROR_BUSY)
        {
            // Unexpected error code.
            err_code = NRF_ERROR_INTERNAL;
        }
    }
    else if (p_existing_key == NULL)  /* There is no bonding data stored. This means that a bonding
                                         procedure is in ongoing, or that the records in flash are
                                         in a bad state. */
    {
        err_code = NRF_ERROR_BUSY;
    }
    else if (!lesc && !im_master_id_is_valid(&(p_existing_key->master_id))) /* There is no valid LTK stored. */
    {
        // No LTK to encrypt with.
        err_code = NRF_ERROR_INVALID_DATA;
    }
    else
    {
        // Encrypt with existing LTK.
        err_code = sd_ble_gap_encrypt(conn_handle,
                                    &(p_existing_key->master_id),
                                    &(p_existing_key->enc_info));
    }

    sec_proc_start(conn_handle, err_code == NRF_SUCCESS, PM_CONN_SEC_PROCEDURE_ENCRYPTION);
    sec_proc_housekeeping(conn_handle, peer_id, (err_code == NRF_SUCCESS), false);

    return err_code;
}


/**@brief Function for intiating pairing as a central. See @ref smd_link_secure for more info.
 */
static ret_code_t link_secure_central_pairing(uint16_t               conn_handle,
                                              pm_peer_id_t           peer_id,
                                              ble_gap_sec_params_t * p_sec_params)
{
    pm_conn_sec_procedure_t procedure        = PM_CONN_SEC_PROCEDURE_PAIRING;
    bool                    new_peer_created = false;
    ret_code_t              err_code         = NRF_SUCCESS;
    pm_peer_data_t          dummy_peer_data;

    if (p_sec_params == NULL)
    {
        err_code  = sd_ble_gap_authenticate(conn_handle, NULL);
    }
    else
    {
        if (p_sec_params->bond)
        {
            procedure = PM_CONN_SEC_PROCEDURE_BONDING;

            if (peer_id == PM_PEER_ID_INVALID)
            {
                // New peer is required.
                peer_id = pdb_peer_allocate();
                new_peer_created = true;
            }

            if (peer_id == PM_PEER_ID_INVALID)
            {
                err_code = NRF_ERROR_INTERNAL;
            }
            else
            {
                err_code = pdb_write_buf_get(peer_id, PM_PEER_DATA_ID_BONDING, 1, &dummy_peer_data);
                if (err_code == NRF_SUCCESS)
                {
                    err_code = pdb_write_buf_store_prepare(peer_id, PM_PEER_DATA_ID_BONDING);
                }
            }
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

    if (err_code == NRF_ERROR_NO_MEM)
    {
        // sd_ble_gap_authenticate() returned NRF_ERROR_NO_MEM. Too many other sec procedures running.
        err_code = NRF_ERROR_BUSY;
    }

    sec_proc_start(conn_handle, err_code == NRF_SUCCESS, procedure);
    sec_proc_housekeeping(conn_handle, peer_id, (err_code == NRF_SUCCESS), new_peer_created);

    return err_code;
}



/**@brief Function for intiating security as a central. See @ref smd_link_secure for more info.
 */
static ret_code_t link_secure_central(uint16_t conn_handle,
                                      ble_gap_sec_params_t * p_sec_params,
                                      bool     force_repairing)
{
    ret_code_t   err_code;
    pm_peer_id_t peer_id;

    if (p_sec_params == NULL)
    {
        return sd_ble_gap_authenticate(conn_handle, NULL);
    }

    // Set the default value for allowing repairing at the start of the sec proc. (for central)
    ble_conn_state_user_flag_set(conn_handle, m_flag_allow_repairing, force_repairing);

    peer_id = im_peer_id_get_by_conn_handle(conn_handle);

    if ((peer_id != PM_PEER_ID_INVALID) && !force_repairing)
    {
        // There is already data in flash for this peer, and repairing has not been requested, so
        // link will be encrypted with the existing keys.
        err_code  = link_secure_central_encryption(conn_handle, peer_id);
    }
    else
    {
        // There are no existing keys, or repairing has been explicitly requested, so pairing
        // (possibly including bonding) will be performed to encrypt the link.
        err_code = link_secure_central_pairing(conn_handle, peer_id, p_sec_params);
    }

    return err_code;
}

/**@brief Function for processing the @ref BLE_GAP_EVT_SEC_REQUEST event from the SoftDevice.
 *
 * @param[in]  p_gap_evt  The event from the SoftDevice.
 */
static void sec_request_process(ble_gap_evt_t const * p_gap_evt)
{
    pm_evt_t evt =
    {
        .evt_id = PM_EVT_SLAVE_SECURITY_REQ,
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
#endif // PM_CENTRAL_ENABLED


/**@brief Function for asking the central to secure the link. See @ref smd_link_secure for more info.
 */
static ret_code_t link_secure_peripheral(uint16_t conn_handle, ble_gap_sec_params_t * p_sec_params)
{
    ret_code_t err_code = NRF_SUCCESS;

    if (p_sec_params != NULL)
    {
        err_code = sd_ble_gap_authenticate(conn_handle, p_sec_params);
    }

    return err_code;
}


ret_code_t smd_link_secure(uint16_t conn_handle,
                           ble_gap_sec_params_t * p_sec_params,
                           bool     force_repairing)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    uint8_t role = ble_conn_state_role(conn_handle);

    switch (role)
    {
#if PM_CENTRAL_ENABLED
        case BLE_GAP_ROLE_CENTRAL:
            return link_secure_central(conn_handle, p_sec_params, force_repairing);
#endif

        case BLE_GAP_ROLE_PERIPH:
            return link_secure_peripheral(conn_handle, p_sec_params);

        default:
            return BLE_ERROR_INVALID_CONN_HANDLE;
    }
}


void smd_ble_evt_handler(ble_evt_t const * p_ble_evt)
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

#if PM_CENTRAL_ENABLED
        case BLE_GAP_EVT_SEC_REQUEST:
            sec_request_process(&(p_ble_evt->evt.gap_evt));
            break;
#endif

        case BLE_GAP_EVT_AUTH_STATUS:
            auth_status_process(&(p_ble_evt->evt.gap_evt));
            break;

        case BLE_GAP_EVT_CONN_SEC_UPDATE:
            conn_sec_update_process(&(p_ble_evt->evt.gap_evt));
            break;
    };
}
#endif //NRF_MODULE_ENABLED(PEER_MANAGER)
