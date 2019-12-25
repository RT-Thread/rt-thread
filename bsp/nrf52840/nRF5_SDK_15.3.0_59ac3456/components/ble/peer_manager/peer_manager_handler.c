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
#include "peer_manager_handler.h"
#include <stdint.h>
#include "sdk_errors.h"
#include "app_error.h"
#include "peer_manager.h"
#include "ble_gap.h"
#include "ble_gattc.h"
#include "ble_conn_state.h"
#include "fds.h"
#include "nrf_strerror.h"
#include "sdk_config.h"

#if PM_HANDLER_SEC_DELAY_MS > 0
#include "app_timer.h"
#endif

#define NRF_LOG_MODULE_NAME peer_manager_handler
#if PM_LOG_ENABLED
    #define NRF_LOG_LEVEL       PM_LOG_LEVEL
    #define NRF_LOG_INFO_COLOR  PM_LOG_INFO_COLOR
    #define NRF_LOG_DEBUG_COLOR PM_LOG_DEBUG_COLOR
#else
    #define NRF_LOG_LEVEL       0
#endif // PM_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
NRF_LOG_MODULE_REGISTER();
#include "nrf_strerror.h"

static const char * m_roles_str[] =
{
    "Invalid Role",
    "Peripheral",
    "Central",
};

static const char * m_sec_procedure_str[] =
{
    "Encryption",
    "Bonding",
    "Pairing",
};

#define PM_EVT_STR(_name) [_name] = STRINGIFY(_name)

static const char * m_event_str[] =
{
    PM_EVT_STR(PM_EVT_BONDED_PEER_CONNECTED),
    PM_EVT_STR(PM_EVT_CONN_SEC_START),
    PM_EVT_STR(PM_EVT_CONN_SEC_SUCCEEDED),
    PM_EVT_STR(PM_EVT_CONN_SEC_FAILED),
    PM_EVT_STR(PM_EVT_CONN_SEC_CONFIG_REQ),
    PM_EVT_STR(PM_EVT_CONN_SEC_PARAMS_REQ),
    PM_EVT_STR(PM_EVT_STORAGE_FULL),
    PM_EVT_STR(PM_EVT_ERROR_UNEXPECTED),
    PM_EVT_STR(PM_EVT_PEER_DATA_UPDATE_SUCCEEDED),
    PM_EVT_STR(PM_EVT_PEER_DATA_UPDATE_FAILED),
    PM_EVT_STR(PM_EVT_PEER_DELETE_SUCCEEDED),
    PM_EVT_STR(PM_EVT_PEER_DELETE_FAILED),
    PM_EVT_STR(PM_EVT_PEERS_DELETE_SUCCEEDED),
    PM_EVT_STR(PM_EVT_PEERS_DELETE_FAILED),
    PM_EVT_STR(PM_EVT_LOCAL_DB_CACHE_APPLIED),
    PM_EVT_STR(PM_EVT_LOCAL_DB_CACHE_APPLY_FAILED),
    PM_EVT_STR(PM_EVT_SERVICE_CHANGED_IND_SENT),
    PM_EVT_STR(PM_EVT_SERVICE_CHANGED_IND_CONFIRMED),
    PM_EVT_STR(PM_EVT_SLAVE_SECURITY_REQ),
    PM_EVT_STR(PM_EVT_FLASH_GARBAGE_COLLECTED),
    PM_EVT_STR(PM_EVT_FLASH_GARBAGE_COLLECTION_FAILED),
};

static const char * m_data_id_str[] =
{
    "Outdated (0)",
    "Service changed pending flag",
    "Outdated (2)",
    "Outdated (3)",
    "Application data",
    "Remote database",
    "Peer rank",
    "Bonding data",
    "Local database",
    "Central address resolution",
};

static const char * m_data_action_str[] =
{
    "Update",
    "Delete"
};


static void _conn_secure(uint16_t conn_handle, bool force)
{
    ret_code_t err_code;

    if (!force)
    {
        pm_conn_sec_status_t status;
        err_code = pm_conn_sec_status_get(conn_handle, &status);
        if (err_code != BLE_ERROR_INVALID_CONN_HANDLE)
        {
            APP_ERROR_CHECK(err_code);
        }

        // If the link is already secured, don't initiate security procedure.
        if (status.encrypted)
        {
            NRF_LOG_DEBUG("Already encrypted, skipping security.");
            return;
        }
    }

    err_code = pm_conn_secure(conn_handle, false);

    if ((err_code == NRF_SUCCESS) || (err_code == NRF_ERROR_BUSY))
    {
        // Success.
    }
    else if (err_code == NRF_ERROR_TIMEOUT)
    {
        NRF_LOG_WARNING("pm_conn_secure() failed because an SMP timeout is preventing security on "\
                        "the link. Disconnecting conn_handle %d.",
                        conn_handle);

        err_code = sd_ble_gap_disconnect(conn_handle, BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_WARNING("sd_ble_gap_disconnect() returned %s on conn_handle %d.",
                            nrf_strerror_get(err_code),
                            conn_handle);
        }
    }
    else if (err_code == NRF_ERROR_INVALID_DATA)
    {
        NRF_LOG_WARNING("pm_conn_secure() failed because the stored data for conn_handle %d does "\
                        "not have a valid key.",
                        conn_handle);
    }
    else if (err_code == BLE_ERROR_INVALID_CONN_HANDLE)
    {
        NRF_LOG_WARNING("pm_conn_secure() failed because conn_handle %d is not a valid connection.",
                        conn_handle);
    }
    else
    {
        NRF_LOG_ERROR("Asserting. pm_conn_secure() returned %s on conn_handle %d.",
                      nrf_strerror_get(err_code),
                      conn_handle);
        APP_ERROR_CHECK(err_code);
    }
}

#if PM_HANDLER_SEC_DELAY_MS > 0
APP_TIMER_DEF(secure_delay_timer);

typedef union
{
    struct
    {
        uint16_t conn_handle;
        bool     force;
    } values;
    void * p_void;
} conn_secure_context_t;

STATIC_ASSERT(sizeof(conn_secure_context_t) <= sizeof(void *), "conn_secure_context_t is too large.");

static void _conn_secure(uint16_t conn_handle, bool force);

static void delayed_conn_secure(void * context)
{
    conn_secure_context_t sec_context = {.p_void = context};
    _conn_secure(sec_context.values.conn_handle, sec_context.values.force);
}

static void conn_secure(uint16_t conn_handle, bool force)
{
    ret_code_t err_code;
    static bool created = false;
    if (!created)
    {
        err_code = app_timer_create(&secure_delay_timer,
                                    APP_TIMER_MODE_SINGLE_SHOT,
                                    delayed_conn_secure);
        APP_ERROR_CHECK(err_code);
        created = true;
    }

    conn_secure_context_t sec_context = {0};
    sec_context.values.conn_handle    = conn_handle;
    sec_context.values.force          = force;

    err_code = app_timer_start(secure_delay_timer,
                               APP_TIMER_TICKS(PM_HANDLER_SEC_DELAY_MS),
                               sec_context.p_void);
    APP_ERROR_CHECK(err_code);
}


#else
static void conn_secure(uint16_t conn_handle, bool force)
{
    _conn_secure(conn_handle, force);
}
#endif


void pm_handler_on_pm_evt(pm_evt_t const * p_pm_evt)
{
    pm_handler_pm_evt_log(p_pm_evt);

    if (p_pm_evt->evt_id == PM_EVT_BONDED_PEER_CONNECTED)
    {
        conn_secure(p_pm_evt->conn_handle, false);
    }
    else if (p_pm_evt->evt_id == PM_EVT_ERROR_UNEXPECTED)
    {
        NRF_LOG_ERROR("Asserting.");
        APP_ERROR_CHECK(p_pm_evt->params.error_unexpected.error);
    }
}


void pm_handler_flash_clean_on_return(void)
{
    // Trigger the mechanism to make more room in flash.
    pm_evt_t storage_full_evt = {.evt_id = PM_EVT_STORAGE_FULL};
    pm_handler_flash_clean(&storage_full_evt);
}


static void rank_highest(pm_peer_id_t peer_id)
{
    // Trigger a pm_peer_rank_highest() with internal bookkeeping.
    pm_evt_t connected_evt = {.evt_id = PM_EVT_BONDED_PEER_CONNECTED, .peer_id = peer_id};
    pm_handler_flash_clean(&connected_evt);
}


void pm_handler_flash_clean(pm_evt_t const * p_pm_evt)
{
    ret_code_t  err_code;
    static bool flash_cleaning       = false;     // Indicates whether garbage collection is currently being run.
    static bool flash_write_after_gc = false;     // Indicates whether a successful write happened after the last garbage
                                                  // collection. If this is false when flash is full, it means just a
                                                  // garbage collection won't work, so some data should be deleted.
    #define RANK_QUEUE_SIZE 8                     // Size of rank_queue.
    #define RANK_QUEUE_INIT() PM_PEER_ID_INVALID, // Initial value of rank_queue.

    //lint -save -e40 -e26 -esym(628,MACRO_REPEAT_8)
    static pm_peer_id_t rank_queue[8]  = {MACRO_REPEAT(RANK_QUEUE_SIZE, RANK_QUEUE_INIT)}; // Queue of rank_highest calls that
                                                                                           // failed because of full flash.
    //lint -restore
    static int          rank_queue_wr = 0;        // Write pointer for rank_queue.

    switch (p_pm_evt->evt_id)
    {
        case PM_EVT_BONDED_PEER_CONNECTED:
            err_code = pm_peer_rank_highest(p_pm_evt->peer_id);
            if ((err_code == NRF_ERROR_STORAGE_FULL) ||
                (err_code == NRF_ERROR_BUSY))
            {
                // Queue pm_peer_rank_highest() call and attempt to clean flash.
                rank_queue[rank_queue_wr] = p_pm_evt->peer_id;
                rank_queue_wr = (rank_queue_wr + 1) % RANK_QUEUE_SIZE;
                pm_handler_flash_clean_on_return();
            }
            else if ((err_code != NRF_ERROR_NOT_SUPPORTED) &&
                     (err_code != NRF_ERROR_INVALID_PARAM) &&
                     (err_code != NRF_ERROR_RESOURCES))
            {
                APP_ERROR_CHECK(err_code);
            }
            else
            {
                NRF_LOG_DEBUG("pm_peer_rank_highest() returned %s for peer id %d",
                              nrf_strerror_get(err_code),
                              p_pm_evt->peer_id);
            }
            break;

        case PM_EVT_CONN_SEC_START:
            break;

        case PM_EVT_CONN_SEC_SUCCEEDED:
            if (   (p_pm_evt->params.conn_sec_succeeded.procedure == PM_CONN_SEC_PROCEDURE_BONDING)
                || (p_pm_evt->params.conn_sec_succeeded.procedure == PM_CONN_SEC_PROCEDURE_ENCRYPTION))
                // PM_CONN_SEC_PROCEDURE_ENCRYPTION in case peer was not recognized at connection time.
            {
                rank_highest(p_pm_evt->peer_id);
            }
            break;

        case PM_EVT_CONN_SEC_FAILED:
        case PM_EVT_CONN_SEC_CONFIG_REQ:
        case PM_EVT_CONN_SEC_PARAMS_REQ:
            break;

        case PM_EVT_STORAGE_FULL:
            if (!flash_cleaning)
            {
                err_code = NRF_SUCCESS;
                NRF_LOG_INFO("Attempting to clean flash.");
                if (!flash_write_after_gc)
                {
                    pm_peer_id_t peer_id_to_delete;
                    err_code = pm_peer_ranks_get(NULL, NULL, &peer_id_to_delete, NULL);
                    if (err_code == NRF_SUCCESS)
                    {
                        NRF_LOG_INFO("Deleting lowest ranked peer (peer_id: %d)", peer_id_to_delete);
                        err_code = pm_peer_delete(peer_id_to_delete);
                        APP_ERROR_CHECK(err_code);
                        flash_write_after_gc = true;
                    }
                    if (err_code == NRF_ERROR_NOT_FOUND)
                    {
                        NRF_LOG_ERROR("There are no peers to delete.");
                    }
                    else if (err_code == NRF_ERROR_NOT_SUPPORTED)
                    {
                        NRF_LOG_WARNING("Peer ranks functionality is disabled, so no peers are deleted.");
                    }
                    else
                    {
                        APP_ERROR_CHECK(err_code);
                    }
                }
                if (err_code == NRF_SUCCESS)
                {
                    err_code = fds_gc();
                    if (err_code == NRF_SUCCESS)
                    {
                        NRF_LOG_DEBUG("Running flash garbage collection.");
                        flash_cleaning = true;
                    }
                    else if (err_code != FDS_ERR_NO_SPACE_IN_QUEUES)
                    {
                        APP_ERROR_CHECK(err_code);
                    }
                }
            }
            break;

        case PM_EVT_ERROR_UNEXPECTED:
            break;

        case PM_EVT_PEER_DATA_UPDATE_SUCCEEDED:
            flash_write_after_gc = true;
            break;

        case PM_EVT_PEER_DATA_UPDATE_FAILED:
            break;

        case PM_EVT_PEER_DELETE_SUCCEEDED:
            flash_write_after_gc = true;
            break;

        case PM_EVT_PEER_DELETE_FAILED:
        case PM_EVT_PEERS_DELETE_SUCCEEDED:
        case PM_EVT_PEERS_DELETE_FAILED:
        case PM_EVT_LOCAL_DB_CACHE_APPLIED:
        case PM_EVT_LOCAL_DB_CACHE_APPLY_FAILED:
        case PM_EVT_SERVICE_CHANGED_IND_SENT:
        case PM_EVT_SERVICE_CHANGED_IND_CONFIRMED:
        case PM_EVT_SLAVE_SECURITY_REQ:
            break;

        case PM_EVT_FLASH_GARBAGE_COLLECTED:
            flash_cleaning       = false;
            flash_write_after_gc = false;
            {
                // Reattempt queued pm_peer_rank_highest() calls.
                int rank_queue_rd = rank_queue_wr;
                for (int i = 0; i < RANK_QUEUE_SIZE; i++)
                {
                    pm_peer_id_t peer_id = rank_queue[(i + rank_queue_rd) % RANK_QUEUE_SIZE];
                    if (peer_id != PM_PEER_ID_INVALID)
                    {
                        rank_queue[(i + rank_queue_rd) % RANK_QUEUE_SIZE] = PM_PEER_ID_INVALID;
                        rank_highest(peer_id);
                    }
                }
            }
            break;

        case PM_EVT_FLASH_GARBAGE_COLLECTION_FAILED:
            flash_cleaning = false;

            if (p_pm_evt->params.garbage_collection_failed.fds_error
              &&   (p_pm_evt->params.garbage_collection_failed.error == FDS_ERR_BUSY
                 || p_pm_evt->params.garbage_collection_failed.error == FDS_ERR_OPERATION_TIMEOUT))
            {
                // Retry immediately if error is transient.
                pm_handler_flash_clean_on_return();
            }
            break;

        default:
            break;
    }
}


void pm_handler_pm_evt_log(pm_evt_t const * p_pm_evt)
{
    NRF_LOG_DEBUG("Event %s", m_event_str[p_pm_evt->evt_id]);

    switch (p_pm_evt->evt_id)
    {
        case PM_EVT_BONDED_PEER_CONNECTED:
            NRF_LOG_DEBUG("Previously bonded peer connected: role: %s, conn_handle: %d, peer_id: %d",
                          m_roles_str[ble_conn_state_role(p_pm_evt->conn_handle)],
                          p_pm_evt->conn_handle,
                          p_pm_evt->peer_id);
            break;

        case PM_EVT_CONN_SEC_START:
            NRF_LOG_DEBUG("Connection security procedure started: role: %s, conn_handle: %d, procedure: %s",
                          m_roles_str[ble_conn_state_role(p_pm_evt->conn_handle)],
                          p_pm_evt->conn_handle,
                          m_sec_procedure_str[p_pm_evt->params.conn_sec_start.procedure]);
            break;

        case PM_EVT_CONN_SEC_SUCCEEDED:
            NRF_LOG_INFO("Connection secured: role: %s, conn_handle: %d, procedure: %s",
                         m_roles_str[ble_conn_state_role(p_pm_evt->conn_handle)],
                         p_pm_evt->conn_handle,
                         m_sec_procedure_str[p_pm_evt->params.conn_sec_start.procedure]);
            break;

        case PM_EVT_CONN_SEC_FAILED:
            NRF_LOG_INFO("Connection security failed: role: %s, conn_handle: 0x%x, procedure: %s, error: %d",
                         m_roles_str[ble_conn_state_role(p_pm_evt->conn_handle)],
                         p_pm_evt->conn_handle,
                         m_sec_procedure_str[p_pm_evt->params.conn_sec_start.procedure],
                         p_pm_evt->params.conn_sec_failed.error);
            break;

        case PM_EVT_CONN_SEC_CONFIG_REQ:
            NRF_LOG_DEBUG("Security configuration request");
            break;

        case PM_EVT_CONN_SEC_PARAMS_REQ:
            NRF_LOG_DEBUG("Security parameter request");
            break;

        case PM_EVT_STORAGE_FULL:
            NRF_LOG_WARNING("Flash storage is full");
            break;

        case PM_EVT_ERROR_UNEXPECTED:
            NRF_LOG_ERROR("Unexpected fatal error occurred: error: %s",
                          nrf_strerror_get(p_pm_evt->params.error_unexpected.error));
            break;

        case PM_EVT_PEER_DATA_UPDATE_SUCCEEDED:
            NRF_LOG_DEBUG("Peer data updated in flash: peer_id: %d, data_id: %s, action: %s",
                          p_pm_evt->peer_id,
                          m_data_id_str[p_pm_evt->params.peer_data_update_succeeded.data_id],
                          m_data_action_str[p_pm_evt->params.peer_data_update_succeeded.action]);
            break;

        case PM_EVT_PEER_DATA_UPDATE_FAILED:
            // This can happen if the SoftDevice is too busy with BLE operations.
            NRF_LOG_WARNING("Peer data updated failed: peer_id: %d, data_id: %s, action: %s, error: %s",
                            p_pm_evt->peer_id,
                            m_data_id_str[p_pm_evt->params.peer_data_update_failed.data_id],
                            m_data_action_str[p_pm_evt->params.peer_data_update_succeeded.action],
                            nrf_strerror_get(p_pm_evt->params.peer_data_update_failed.error));
            break;

        case PM_EVT_PEER_DELETE_SUCCEEDED:
            NRF_LOG_ERROR("Peer deleted successfully: peer_id: %d", p_pm_evt->peer_id);
            break;

        case PM_EVT_PEER_DELETE_FAILED:
            NRF_LOG_ERROR("Peer deletion failed: peer_id: %d, error: %s",
                          p_pm_evt->peer_id,
                          nrf_strerror_get(p_pm_evt->params.peer_delete_failed.error));
            break;

        case PM_EVT_PEERS_DELETE_SUCCEEDED:
            NRF_LOG_INFO("All peers deleted.");
            break;

        case PM_EVT_PEERS_DELETE_FAILED:
            NRF_LOG_ERROR("All peer deletion failed: error: %s",
                          nrf_strerror_get(p_pm_evt->params.peers_delete_failed_evt.error));
            break;

        case PM_EVT_LOCAL_DB_CACHE_APPLIED:
            NRF_LOG_DEBUG("Previously stored local DB applied: conn_handle: %d, peer_id: %d",
                          p_pm_evt->conn_handle,
                          p_pm_evt->peer_id);
            break;

        case PM_EVT_LOCAL_DB_CACHE_APPLY_FAILED:
            // This can happen when the local DB has changed.
            NRF_LOG_WARNING("Local DB could not be applied: conn_handle: %d, peer_id: %d",
                            p_pm_evt->conn_handle,
                            p_pm_evt->peer_id);
            break;

        case PM_EVT_SERVICE_CHANGED_IND_SENT:
            NRF_LOG_DEBUG("Sending Service Changed indication.");
            break;

        case PM_EVT_SERVICE_CHANGED_IND_CONFIRMED:
            NRF_LOG_DEBUG("Service Changed indication confirmed.");
            break;

        case PM_EVT_SLAVE_SECURITY_REQ:
            NRF_LOG_DEBUG("Security Request received from peer.");
            break;

        case PM_EVT_FLASH_GARBAGE_COLLECTED:
            NRF_LOG_DEBUG("Flash garbage collection complete.");
            break;

        case PM_EVT_FLASH_GARBAGE_COLLECTION_FAILED:
            NRF_LOG_WARNING("Flash garbage collection failed with error %s.",
                            nrf_strerror_get(p_pm_evt->params.garbage_collection_failed.error));
            break;

        default:
            NRF_LOG_WARNING("Unexpected PM event ID: 0x%x.", p_pm_evt->evt_id);
            break;
    }
}


void pm_handler_disconnect_on_sec_failure(pm_evt_t const * p_pm_evt)
{
    ret_code_t err_code;

    if (p_pm_evt->evt_id == PM_EVT_CONN_SEC_FAILED)
    {
        NRF_LOG_WARNING("Disconnecting conn_handle %d.", p_pm_evt->conn_handle);
        err_code = sd_ble_gap_disconnect(p_pm_evt->conn_handle,
                                         BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
        if ((err_code != NRF_ERROR_INVALID_STATE) && (err_code != BLE_ERROR_INVALID_CONN_HANDLE))
        {
            APP_ERROR_CHECK(err_code);
        }
    }
}


void pm_handler_secure_on_connection(ble_evt_t const * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            NRF_LOG_DEBUG("Connected, securing connection. conn_handle: %d", p_ble_evt->evt.gap_evt.conn_handle);
            conn_secure(p_ble_evt->evt.gap_evt.conn_handle, false);
            break;

#if PM_HANDLER_SEC_DELAY_MS > 0
        case BLE_GAP_EVT_DISCONNECTED:
        {
            ret_code_t err_code = app_timer_stop(secure_delay_timer);
            APP_ERROR_CHECK(err_code);
        } break;
#endif

        default:
            break;
    }
}


void pm_handler_secure_on_error(ble_evt_t const * p_ble_evt)
{
    if ((p_ble_evt->header.evt_id >= BLE_GATTC_EVT_BASE) && (p_ble_evt->header.evt_id <= BLE_GATTC_EVT_LAST))
    {
        if ((p_ble_evt->evt.gattc_evt.gatt_status == BLE_GATT_STATUS_ATTERR_INSUF_ENCRYPTION) ||
            (p_ble_evt->evt.gattc_evt.gatt_status == BLE_GATT_STATUS_ATTERR_INSUF_AUTHENTICATION))
        {
            NRF_LOG_INFO("GATTC procedure (evt id 0x%x) failed because it needs encryption. Bonding: conn_handle=%d",
                         p_ble_evt->header.evt_id,
                         p_ble_evt->evt.gattc_evt.conn_handle);
            conn_secure(p_ble_evt->evt.gattc_evt.conn_handle, true);
        }
    }
}
