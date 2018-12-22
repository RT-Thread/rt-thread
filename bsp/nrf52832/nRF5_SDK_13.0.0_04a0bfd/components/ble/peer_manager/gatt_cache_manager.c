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
#include "gatt_cache_manager.h"

#include "ble_gap.h"
#include "ble_conn_state.h"
#include "peer_manager_types.h"
#include "peer_manager_internal.h"
#include "id_manager.h"
#include "security_dispatcher.h"
#include "gatts_cache_manager.h"


// The number of registered event handlers.
#define GCM_EVENT_HANDLERS_CNT      (sizeof(m_evt_handlers) / sizeof(m_evt_handlers[0]))

// GATT Cache Manager event handler in Peer Manager.
extern void pm_gcm_evt_handler(gcm_evt_t const * p_gcm_evt);

// GATT Cache Manager events' handlers.
// The number of elements in this array is GCM_EVENT_HANDLERS_CNT.
static gcm_evt_handler_t m_evt_handlers[] =
{
    pm_gcm_evt_handler
};

static bool                           m_module_initialized;
static ble_conn_state_user_flag_id_t  m_flag_local_db_update_pending; /**< Flag ID for flag collection to keep track of which connections need a local DB update procedure. */
static ble_conn_state_user_flag_id_t  m_flag_local_db_apply_pending;  /**< Flag ID for flag collection to keep track of which connections need a local DB apply procedure. */
static ble_conn_state_user_flag_id_t  m_flag_service_changed_pending; /**< Flag ID for flag collection to keep track of which connections need to be sent a service changed indication. */
static ble_conn_state_user_flag_id_t  m_flag_service_changed_sent;    /**< Flag ID for flag collection to keep track of which connections have been sent a service changed indication and are waiting for a handle value confirmation. */


static void service_changed_pending_flags_check(void);


/**@brief Function for resetting the module variable(s) of the GSCM module.
 *
 * @param[out]  The instance to reset.
 */
static void internal_state_reset()
{
    m_module_initialized = false;
}


static void evt_send(gcm_evt_t const * p_gcm_evt)
{
    for (uint32_t i = 0; i < GCM_EVENT_HANDLERS_CNT; i++)
    {
        m_evt_handlers[i](p_gcm_evt);
    }
}


/**@brief Function for checking a write event for whether a CCCD was written during the write
 *        operation.
 *
 * @param[in]  p_write_evt  The parameters of the write event.
 *
 * @return  Whether the write was on a CCCD.
 */
static bool cccd_written(ble_gatts_evt_write_t * p_write_evt)
{
    return (    (p_write_evt->op        == BLE_GATTS_OP_WRITE_REQ)
             && (p_write_evt->uuid.type == BLE_UUID_TYPE_BLE)
             && (p_write_evt->uuid.uuid == BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG)
           );
}


/**@brief Function for performing the local DB update procedure in an event context, where no return
 *        code can be given.
 *
 * @details This function will do the procedure, and check the result, set a flag if needed, and
 *          send an event if needed.
 *
 * @param[in]  conn_handle  The connection to perform the procedure on.
 */
static void local_db_apply_in_evt(uint16_t conn_handle)
{
    bool set_procedure_as_pending = false;
    ret_code_t err_code;
    gcm_evt_t event;

    if (conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return;
    }

    err_code = gscm_local_db_cache_apply(conn_handle);

    switch (err_code)
    {
        case NRF_SUCCESS:
            event.evt_id                                    = GCM_EVT_LOCAL_DB_CACHE_APPLIED;
            event.peer_id                                   = im_peer_id_get_by_conn_handle(conn_handle);
            event.params.local_db_cache_applied.conn_handle = conn_handle;

            evt_send(&event);
            break;

        case NRF_ERROR_BUSY:
            set_procedure_as_pending = true;
            break;

        case NRF_ERROR_INVALID_DATA:
            event.evt_id                                        = GCM_EVT_ERROR_LOCAL_DB_CACHE_APPLY;
            event.peer_id                                       = im_peer_id_get_by_conn_handle(conn_handle);
            event.params.error_local_db_cache_apply.conn_handle = conn_handle;

            evt_send(&event);
            break;

        case BLE_ERROR_INVALID_CONN_HANDLE:
            /* Do nothing */
            break;

        default:
            event.evt_id                              = GCM_EVT_ERROR_UNEXPECTED;
            event.peer_id                             = im_peer_id_get_by_conn_handle(conn_handle);
            event.params.error_unexpected.conn_handle = conn_handle;
            event.params.error_unexpected.error       = err_code;

            evt_send(&event);
            break;
    }

    ble_conn_state_user_flag_set(conn_handle, m_flag_local_db_apply_pending, set_procedure_as_pending);
}


/**@brief Function for performing the local DB apply procedure in an event context, where no return
 *        code can be given.
 *
 * @details This function will do the procedure, and check the result, set a flag if needed, and
 *          send an event if needed.
 *
 * @param[in]  conn_handle  The connection to perform the procedure on.
 */
static void local_db_update_in_evt(uint16_t conn_handle)
{
    gcm_evt_t event;
    bool set_procedure_as_pending = false;
    ret_code_t err_code = gscm_local_db_cache_update(conn_handle);

    switch (err_code)
    {
        case NRF_SUCCESS:
            event.evt_id                                    = GCM_EVT_LOCAL_DB_CACHE_UPDATED;
            event.params.local_db_cache_applied.conn_handle = conn_handle;
            event.peer_id                                   = im_peer_id_get_by_conn_handle(conn_handle);

            evt_send(&event);
            break;

        case BLE_ERROR_INVALID_CONN_HANDLE:
            /* Do nothing */
            break;

        case NRF_ERROR_BUSY:
            set_procedure_as_pending = true;
            break;

        case NRF_ERROR_DATA_SIZE:
            event.evt_id = GCM_EVT_ERROR_DATA_SIZE;
            event.params.error_data_size.conn_handle = conn_handle;
            event.peer_id = im_peer_id_get_by_conn_handle(conn_handle);

            evt_send(&event);
            break;

        case NRF_ERROR_STORAGE_FULL:
            event.evt_id = GCM_EVT_ERROR_STORAGE_FULL;
            event.params.error_no_mem.conn_handle = conn_handle;
            event.peer_id = im_peer_id_get_by_conn_handle(conn_handle);

            evt_send(&event);
            break;

        default:
            event.evt_id                              = GCM_EVT_ERROR_UNEXPECTED;
            event.peer_id                             = im_peer_id_get_by_conn_handle(conn_handle);
            event.params.error_unexpected.conn_handle = conn_handle;
            event.params.error_unexpected.error       = err_code;

            evt_send(&event);
            break;
    }

    ble_conn_state_user_flag_set(conn_handle, m_flag_local_db_update_pending, set_procedure_as_pending);
}


/**@brief Function for sending a service changed indication in an event context, where no return
 *        code can be given.
 *
 * @details This function will do the procedure, and check the result, set a flag if needed, and
 *          send an event if needed.
 *
 * @param[in]  conn_handle  The connection to perform the procedure on.
 */
static void service_changed_send_in_evt(uint16_t conn_handle)
{
    gcm_evt_t event;
    bool sc_pending_state = true;
    bool sc_sent_state = false;
    ret_code_t err_code = gscm_service_changed_ind_send(conn_handle);

    switch (err_code)
    {
        case NRF_SUCCESS:
            sc_sent_state = true;

            event.evt_id = GCM_EVT_SERVICE_CHANGED_IND_SENT;
            event.peer_id = im_peer_id_get_by_conn_handle(conn_handle);
            event.params.service_changed_ind_sent.conn_handle = conn_handle;

            evt_send(&event);
            break;

        case NRF_ERROR_BUSY:
            // Do nothing.
            break;

        case NRF_ERROR_INVALID_STATE:
            // CCCDs not enabled. Drop indication.
            // Fallthrough.

        case NRF_ERROR_NOT_SUPPORTED:
            // Service changed not supported. Drop indication.
            sc_pending_state = false;
            gscm_db_change_notification_done(im_peer_id_get_by_conn_handle(conn_handle));
            break;

        case BLE_ERROR_GATTS_SYS_ATTR_MISSING:
            local_db_apply_in_evt(conn_handle);
            break;

        case BLE_ERROR_INVALID_CONN_HANDLE:
            // Do nothing.
            break;

        default:
            event.evt_id = GCM_EVT_ERROR_UNEXPECTED;
            event.params.error_unexpected.conn_handle = conn_handle;
            event.params.error_unexpected.error = err_code;
            event.peer_id = im_peer_id_get_by_conn_handle(conn_handle);

            evt_send(&event);
            break;
    }

    ble_conn_state_user_flag_set(conn_handle, m_flag_service_changed_pending, sc_pending_state);
    ble_conn_state_user_flag_set(conn_handle, m_flag_service_changed_sent, sc_sent_state);
}


/**@brief Callback function for events from the GATT Cache Server Manager module.
 *        This handler is extern in GATTS Cache Manager module.
 *
 * @param[in]  p_event  The event from the GATT Cache Server Manager module.
 */
void gcm_gscm_evt_handler(gscm_evt_t const * p_event)
{
    gcm_evt_t event;
    event.peer_id = p_event->peer_id;

    switch (p_event->evt_id)
    {
        case GSCM_EVT_LOCAL_DB_CACHE_STORED:
            event.evt_id = GCM_EVT_LOCAL_DB_CACHE_STORED;

            evt_send(&event);
            local_db_apply_in_evt(im_conn_handle_get(p_event->peer_id));
            break;

        case GSCM_EVT_LOCAL_DB_CACHE_UPDATED:
            event.evt_id = GCM_EVT_LOCAL_DB_CACHE_UPDATED;
            event.params.local_db_cache_updated.conn_handle = p_event->params.local_db_cache_updated.conn_handle;

            evt_send(&event);
            break;

        case GSCM_EVT_SC_STATE_STORED:
            if (p_event->params.sc_state_stored.state)
            {
                uint16_t conn_handle = im_conn_handle_get(p_event->peer_id);
                if (conn_handle != BLE_CONN_HANDLE_INVALID)
                {
                    ble_conn_state_user_flag_set(conn_handle, m_flag_service_changed_pending, true);
                    service_changed_pending_flags_check();
                }
            }
            break;
    }
}


/**@brief Callback function for events from the ID Manager module.
 *        This function is registered in the ID Manager module.
 *
 * @param[in]  p_event  The event from the ID Manager module.
 */
void gcm_im_evt_handler(im_evt_t const * p_event)
{
    switch (p_event->evt_id)
    {
        case IM_EVT_BONDED_PEER_CONNECTED:
            local_db_apply_in_evt(p_event->conn_handle);
            if (gscm_service_changed_ind_needed(p_event->conn_handle))
            {
                ble_conn_state_user_flag_set(p_event->conn_handle, m_flag_service_changed_pending, true);
            }
            break;
        default:
            break;
    }
}


/**@brief Callback function for events from the Security Dispatcher module.
 *        This handler is extern in Security Dispatcher.
 *
 * @param[in]  p_event  The event from the Security Dispatcher module.
 */
void gcm_smd_evt_handler(smd_evt_t const * p_event)
{
    switch (p_event->evt_id)
    {
        case SMD_EVT_BONDING_INFO_STORED:
            local_db_update_in_evt(p_event->conn_handle);
            break;
        default:
            break;
    }
}


ret_code_t gcm_init()
{
    NRF_PM_DEBUG_CHECK(!m_module_initialized);

    internal_state_reset();

    m_flag_local_db_update_pending = ble_conn_state_user_flag_acquire();
    m_flag_local_db_apply_pending  = ble_conn_state_user_flag_acquire();
    m_flag_service_changed_pending = ble_conn_state_user_flag_acquire();
    m_flag_service_changed_sent    = ble_conn_state_user_flag_acquire();

    if  ((m_flag_local_db_update_pending  == BLE_CONN_STATE_USER_FLAG_INVALID)
      || (m_flag_local_db_apply_pending   == BLE_CONN_STATE_USER_FLAG_INVALID)
      || (m_flag_service_changed_pending  == BLE_CONN_STATE_USER_FLAG_INVALID)
      || (m_flag_service_changed_sent     == BLE_CONN_STATE_USER_FLAG_INVALID))
    {
        return NRF_ERROR_INTERNAL;
    }

    m_module_initialized = true;

    return NRF_SUCCESS;
}


// @todo emdi: apply_pending_flags_check() and update_pending_flags_check() should really be
// refactored into one function..

/**@brief Function for performing the Local DB apply procedure if it is pending on any connections.
 */
static void apply_pending_flags_check(void)
{
    sdk_mapped_flags_t apply_pending_flags;

    apply_pending_flags = ble_conn_state_user_flag_collection(m_flag_local_db_apply_pending);
    if (sdk_mapped_flags_any_set(apply_pending_flags))
    {
        sdk_mapped_flags_key_list_t conn_handle_list;
        conn_handle_list = ble_conn_state_conn_handles();

        for (uint32_t i = 0; i < conn_handle_list.len; i++)
        {
            if (ble_conn_state_user_flag_get(conn_handle_list.flag_keys[i], m_flag_local_db_apply_pending))
            {
                local_db_apply_in_evt(conn_handle_list.flag_keys[i]);
            }
        }
    }
}


/**@brief Function for performing the Local DB update procedure if it is pending on any connections.
 */
static void update_pending_flags_check(void)
{
    sdk_mapped_flags_t update_pending_flags;

    update_pending_flags = ble_conn_state_user_flag_collection(m_flag_local_db_update_pending);
    if (sdk_mapped_flags_any_set(update_pending_flags))
    {
        sdk_mapped_flags_key_list_t conn_handle_list;
        conn_handle_list = ble_conn_state_conn_handles();

        for (uint32_t i = 0; i < conn_handle_list.len; i++)
        {
            if (ble_conn_state_user_flag_get(conn_handle_list.flag_keys[i], m_flag_local_db_update_pending))
            {
                local_db_update_in_evt(conn_handle_list.flag_keys[i]);
            }
        }
    }
}


/**@brief Function for sending service changed indications if it is pending on any connections.
 */
static void service_changed_pending_flags_check(void)
{
    sdk_mapped_flags_t service_changed_pending_flags;

    service_changed_pending_flags = ble_conn_state_user_flag_collection(m_flag_service_changed_pending);
    if (sdk_mapped_flags_any_set(service_changed_pending_flags))
    {
        sdk_mapped_flags_key_list_t conn_handle_list;
        conn_handle_list = ble_conn_state_conn_handles();

        for (uint32_t i = 0; i < conn_handle_list.len; i++)
        {
            if (    ble_conn_state_user_flag_get(conn_handle_list.flag_keys[i],
                                                 m_flag_service_changed_pending)
                && !ble_conn_state_user_flag_get(conn_handle_list.flag_keys[i],
                                                 m_flag_service_changed_sent))
            {
                service_changed_send_in_evt(conn_handle_list.flag_keys[i]);
            }
        }
    }
}


/**@brief Callback function for BLE events from the SoftDevice.
 *
 * @param[in]  p_ble_evt  The BLE event from the SoftDevice.
 */
void gcm_ble_evt_handler(ble_evt_t * p_ble_evt)
{
    gcm_evt_t event;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTS_EVT_SYS_ATTR_MISSING:
            local_db_apply_in_evt(p_ble_evt->evt.gatts_evt.conn_handle);
            break;

        case BLE_GATTS_EVT_SC_CONFIRM:
            event.evt_id = GCM_EVT_SERVICE_CHANGED_IND_CONFIRMED;
            event.peer_id = im_peer_id_get_by_conn_handle(p_ble_evt->evt.gatts_evt.conn_handle);
            event.params.service_changed_ind_sent.conn_handle = p_ble_evt->evt.gatts_evt.conn_handle;

            gscm_db_change_notification_done(event.peer_id);
            ble_conn_state_user_flag_set(p_ble_evt->evt.gatts_evt.conn_handle, m_flag_service_changed_pending, false);

            evt_send(&event);
            break;

        case BLE_GATTS_EVT_WRITE:
            if (cccd_written(&p_ble_evt->evt.gatts_evt.params.write))
            {
                local_db_update_in_evt(p_ble_evt->evt.gatts_evt.conn_handle);
            }
            break;
    }

    apply_pending_flags_check();
    update_pending_flags_check();
    service_changed_pending_flags_check();
}


ret_code_t gcm_local_db_cache_update(uint16_t conn_handle)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    ret_code_t err_code = gscm_local_db_cache_update(conn_handle);
    bool set_procedure_as_pending = false;

    if (err_code == NRF_ERROR_BUSY)
    {
        set_procedure_as_pending = true;
        err_code = NRF_SUCCESS;
    }

    ble_conn_state_user_flag_set(conn_handle, m_flag_local_db_update_pending, set_procedure_as_pending);

    return err_code;
}


ret_code_t gcm_local_db_cache_set(pm_peer_id_t peer_id, pm_peer_data_local_gatt_db_t * p_local_db)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    return gscm_local_db_cache_set(peer_id, p_local_db);
}


void gcm_local_database_has_changed(void)
{
    gscm_local_database_has_changed();

    sdk_mapped_flags_key_list_t conn_handles = ble_conn_state_conn_handles();

    for (uint16_t i = 0; i < conn_handles.len; i++)
    {
        if (im_peer_id_get_by_conn_handle(conn_handles.flag_keys[i]) == PM_PEER_ID_INVALID)
        {
            ble_conn_state_user_flag_set(conn_handles.flag_keys[i], m_flag_service_changed_pending, true);
        }
    }

    service_changed_pending_flags_check();
}
#endif // NRF_MODULE_ENABLED(PEER_MANAGER)
