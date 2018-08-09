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
#include "gatt_cache_manager.h"

#include "ble_gap.h"
#include "ble_err.h"
#include "ble_conn_state.h"
#include "peer_manager_types.h"
#include "peer_manager_internal.h"
#include "id_manager.h"
#include "gatts_cache_manager.h"
#include "peer_database.h"
#include "pm_mutex.h"


// The number of registered event handlers.
#define GCM_EVENT_HANDLERS_CNT      (sizeof(m_evt_handlers) / sizeof(m_evt_handlers[0]))

// GATT Cache Manager event handler in Peer Manager.
extern void pm_gcm_evt_handler(pm_evt_t * p_gcm_evt);

// GATT Cache Manager events' handlers.
// The number of elements in this array is GCM_EVENT_HANDLERS_CNT.
static pm_evt_handler_internal_t m_evt_handlers[] =
{
    pm_gcm_evt_handler
};

static bool                           m_module_initialized;
static uint8_t                        m_db_update_in_progress_mutex;  /**< Mutex indicating whether a local DB write operation is ongoing. */
static ble_conn_state_user_flag_id_t  m_flag_local_db_update_pending; /**< Flag ID for flag collection to keep track of which connections need a local DB update procedure. */
static ble_conn_state_user_flag_id_t  m_flag_local_db_apply_pending;  /**< Flag ID for flag collection to keep track of which connections need a local DB apply procedure. */
static ble_conn_state_user_flag_id_t  m_flag_service_changed_pending; /**< Flag ID for flag collection to keep track of which connections need to be sent a service changed indication. */
static ble_conn_state_user_flag_id_t  m_flag_service_changed_sent;    /**< Flag ID for flag collection to keep track of which connections have been sent a service changed indication and are waiting for a handle value confirmation. */

#ifdef PM_SERVICE_CHANGED_ENABLED
    STATIC_ASSERT(PM_SERVICE_CHANGED_ENABLED || !NRF_SDH_BLE_SERVICE_CHANGED,
                 "PM_SERVICE_CHANGED_ENABLED should be enabled if NRF_SDH_BLE_SERVICE_CHANGED is enabled.");
#else
    #define PM_SERVICE_CHANGED_ENABLED 1
#endif

/**@brief Function for resetting the module variable(s) of the GSCM module.
 *
 * @param[out]  The instance to reset.
 */
static void internal_state_reset()
{
    m_module_initialized = false;
}


static void evt_send(pm_evt_t * p_gcm_evt)
{
    p_gcm_evt->peer_id = im_peer_id_get_by_conn_handle(p_gcm_evt->conn_handle);

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
static bool cccd_written(ble_gatts_evt_write_t const * p_write_evt)
{
    return (    (p_write_evt->op        == BLE_GATTS_OP_WRITE_REQ)
             && (p_write_evt->uuid.type == BLE_UUID_TYPE_BLE)
             && (p_write_evt->uuid.uuid == BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG)
           );
}


/**@brief Function for sending an PM_EVT_ERROR_UNEXPECTED event.
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
    pm_evt_t event =
    {
        .conn_handle = conn_handle,
    };

    if (conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return;
    }

    err_code = gscm_local_db_cache_apply(conn_handle);

    switch (err_code)
    {
        case NRF_SUCCESS:
            event.evt_id = PM_EVT_LOCAL_DB_CACHE_APPLIED;

            evt_send(&event);
            break;

        case NRF_ERROR_BUSY:
            set_procedure_as_pending = true;
            break;

        case NRF_ERROR_INVALID_DATA:
            event.evt_id = PM_EVT_LOCAL_DB_CACHE_APPLY_FAILED;

            evt_send(&event);
            break;

        case BLE_ERROR_INVALID_CONN_HANDLE:
            /* Do nothing */
            break;

        default:
            send_unexpected_error(conn_handle, err_code);
            break;
    }

    ble_conn_state_user_flag_set(conn_handle, m_flag_local_db_apply_pending, set_procedure_as_pending);
}


/**@brief Function for asynchronously starting a DB update procedure.
 *
 * @note This procedure can only be started asynchronously.
 *
 * @param[in]  conn_handle  The connection to perform the procedure on.
 * @param[in]  update       Whether to perform the procedure.
 */
static __INLINE void local_db_update(uint16_t conn_handle, bool update)
{
    ble_conn_state_user_flag_set(conn_handle, m_flag_local_db_update_pending, update);
}


/**@brief Function for performing the local DB update procedure in an event context, where no return
 *        code can be given.
 *
 * @details This function will do the procedure, and check the result, set a flag if needed, and
 *          send an event if needed.
 *
 * @param[in]  conn_handle  The connection to perform the procedure on.
 */
static bool local_db_update_in_evt(uint16_t conn_handle)
{
    bool set_procedure_as_pending = false;
    bool success = false;
    ret_code_t err_code = gscm_local_db_cache_update(conn_handle);

    switch (err_code)
    {
        case NRF_SUCCESS:
            success = true;
            break;

        case BLE_ERROR_INVALID_CONN_HANDLE:
            /* Do nothing */
            break;

        case NRF_ERROR_BUSY:
            set_procedure_as_pending = true;
            break;

        case NRF_ERROR_STORAGE_FULL:
        {
            pm_evt_t event =
            {
                .evt_id      = PM_EVT_STORAGE_FULL,
                .conn_handle = conn_handle,
            };

            evt_send(&event);
            break;
        }

        default:
            send_unexpected_error(conn_handle, err_code);
            break;
    }

    local_db_update(conn_handle, set_procedure_as_pending);

    return success;
}

#if PM_SERVICE_CHANGED_ENABLED
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
    bool sc_pending_state = true;
    bool sc_sent_state = false;
    ret_code_t err_code = gscm_service_changed_ind_send(conn_handle);

    switch (err_code)
    {
        case NRF_SUCCESS:
        {
            pm_evt_t event =
            {
                .evt_id      = PM_EVT_SERVICE_CHANGED_IND_SENT,
                .conn_handle = conn_handle,
            };

            sc_sent_state = true;

            evt_send(&event);
            break;
        }

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
            send_unexpected_error(conn_handle, err_code);
            break;
    }

    ble_conn_state_user_flag_set(conn_handle, m_flag_service_changed_pending, sc_pending_state);
    ble_conn_state_user_flag_set(conn_handle, m_flag_service_changed_sent, sc_sent_state);
}
#endif

static void apply_pending_handle(uint16_t conn_handle, void * p_context)
{
    UNUSED_PARAMETER(p_context);
    local_db_apply_in_evt(conn_handle);
}


static __INLINE void apply_pending_flags_check(void)
{
    UNUSED_RETURN_VALUE(ble_conn_state_for_each_set_user_flag(m_flag_local_db_apply_pending,
                                                              apply_pending_handle,
                                                              NULL));
}


static void db_update_pending_handle(uint16_t conn_handle, void * p_context)
{
    UNUSED_PARAMETER(p_context);
    if (pm_mutex_lock(&m_db_update_in_progress_mutex, 0))
    {
        if (local_db_update_in_evt(conn_handle))
        {
            // Successfully started writing to flash.
            return;
        }
        else
        {
            pm_mutex_unlock(&m_db_update_in_progress_mutex, 0);
        }
    }
}


static __INLINE void update_pending_flags_check(void)
{
    UNUSED_RETURN_VALUE(ble_conn_state_for_each_set_user_flag(m_flag_local_db_update_pending,
                                                              db_update_pending_handle,
                                                              NULL));
}


#if PM_SERVICE_CHANGED_ENABLED
static void sc_send_pending_handle(uint16_t conn_handle, void * p_context)
{
    UNUSED_PARAMETER(p_context);
    if (!ble_conn_state_user_flag_get(conn_handle, m_flag_service_changed_sent))
    {
        service_changed_send_in_evt(conn_handle);
    }
}


static __INLINE void service_changed_pending_flags_check(void)
{
    UNUSED_RETURN_VALUE(ble_conn_state_for_each_set_user_flag(m_flag_service_changed_pending,
                                                              sc_send_pending_handle,
                                                              NULL));
}
#endif


/**@brief Callback function for events from the ID Manager module.
 *        This function is registered in the ID Manager module.
 *
 * @param[in]  p_event  The event from the ID Manager module.
 */
void gcm_im_evt_handler(pm_evt_t * p_event)
{
    switch (p_event->evt_id)
    {
        case PM_EVT_BONDED_PEER_CONNECTED:
            local_db_apply_in_evt(p_event->conn_handle);
#if (PM_SERVICE_CHANGED_ENABLED == 1)
            if (gscm_service_changed_ind_needed(p_event->conn_handle))
            {
                ble_conn_state_user_flag_set(p_event->conn_handle, m_flag_service_changed_pending, true);
            }
#endif
            break;
        default:
            break;
    }
}


/**@brief Callback function for events from the Peer Database module.
 *        This handler is extern in Peer Database.
 *
 * @param[in]  p_event  The event from the Security Dispatcher module.
 */
void gcm_pdb_evt_handler(pm_evt_t * p_event)
{
    if (   p_event->evt_id == PM_EVT_PEER_DATA_UPDATE_SUCCEEDED
        && p_event->params.peer_data_update_succeeded.action == PM_PEER_DATA_OP_UPDATE)
    {
        switch (p_event->params.peer_data_update_succeeded.data_id)
        {
            case PM_PEER_DATA_ID_BONDING:
            {
                uint16_t conn_handle = im_conn_handle_get(p_event->peer_id);

                if (conn_handle != BLE_CONN_HANDLE_INVALID)
                {
                    local_db_update(conn_handle, true);
                }
                break;
            }

#if PM_SERVICE_CHANGED_ENABLED
            case PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING:
            {
                ret_code_t           err_code;
                pm_peer_data_flash_t peer_data;

                err_code = pdb_peer_data_ptr_get(p_event->peer_id,
                                                 PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING,
                                                 &peer_data);

                if (err_code == NRF_SUCCESS)
                {
                    if (*peer_data.p_service_changed_pending)
                    {
                        uint16_t conn_handle = im_conn_handle_get(p_event->peer_id);
                        if (conn_handle != BLE_CONN_HANDLE_INVALID)
                        {
                            ble_conn_state_user_flag_set(conn_handle, m_flag_service_changed_pending, true);
                            service_changed_pending_flags_check();
                        }
                    }
                }
                break;
            }
#endif

            case PM_PEER_DATA_ID_GATT_LOCAL:
                pm_mutex_unlock(&m_db_update_in_progress_mutex, 0);
                // Expecting a call to update_pending_flags_check() immediately.
                break;

            default:
                /* No action */
                break;
        }
    }

    update_pending_flags_check();
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
      || (m_flag_service_changed_sent     == BLE_CONN_STATE_USER_FLAG_INVALID)
      )
    {
        return NRF_ERROR_INTERNAL;
    }

    pm_mutex_init(&m_db_update_in_progress_mutex, 1);

    m_module_initialized = true;

    return NRF_SUCCESS;
}


/**@brief Callback function for BLE events from the SoftDevice.
 *
 * @param[in]  p_ble_evt  The BLE event from the SoftDevice.
 */
void gcm_ble_evt_handler(ble_evt_t const * p_ble_evt)
{
    uint16_t conn_handle = p_ble_evt->evt.gatts_evt.conn_handle;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTS_EVT_SYS_ATTR_MISSING:
            local_db_apply_in_evt(conn_handle);
            break;

#if PM_SERVICE_CHANGED_ENABLED
        case BLE_GATTS_EVT_SC_CONFIRM:
        {
            pm_evt_t event =
            {
                .evt_id      = PM_EVT_SERVICE_CHANGED_IND_CONFIRMED,
                .peer_id     = im_peer_id_get_by_conn_handle(conn_handle),
                .conn_handle = conn_handle,
            };

            gscm_db_change_notification_done(event.peer_id);

            ble_conn_state_user_flag_set(conn_handle, m_flag_service_changed_sent, false);
            ble_conn_state_user_flag_set(conn_handle, m_flag_service_changed_pending, false);
            evt_send(&event);
            break;
        }
#endif

        case BLE_GATTS_EVT_WRITE:
            if (cccd_written(&p_ble_evt->evt.gatts_evt.params.write))
            {
                local_db_update(conn_handle, true);
                update_pending_flags_check();
            }
            break;
    }

    apply_pending_flags_check();
#if PM_SERVICE_CHANGED_ENABLED
    service_changed_pending_flags_check();
#endif
}


ret_code_t gcm_local_db_cache_update(uint16_t conn_handle)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    local_db_update(conn_handle, true);
    update_pending_flags_check();

    return NRF_SUCCESS;
}


#if PM_SERVICE_CHANGED_ENABLED
void gcm_local_database_has_changed(void)
{
    gscm_local_database_has_changed();

    ble_conn_state_conn_handle_list_t conn_handles = ble_conn_state_conn_handles();

    for (uint16_t i = 0; i < conn_handles.len; i++)
    {
        if (im_peer_id_get_by_conn_handle(conn_handles.conn_handles[i]) == PM_PEER_ID_INVALID)
        {
            ble_conn_state_user_flag_set(conn_handles.conn_handles[i], m_flag_service_changed_pending, true);
        }
    }

    service_changed_pending_flags_check();
}
#endif
#endif // NRF_MODULE_ENABLED(PEER_MANAGER)
