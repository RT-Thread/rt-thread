/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#include "peer_data_storage.h"
#include "peer_database.h"
#include "nrf_mtx.h"

#define NRF_LOG_MODULE_NAME peer_manager_gcm
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
static nrf_mtx_t                      m_db_update_in_progress_mutex;  /**< Mutex indicating whether a local DB write operation is ongoing. */
static ble_conn_state_user_flag_id_t  m_flag_local_db_update_pending; /**< Flag ID for flag collection to keep track of which connections need a local DB update procedure. */
static ble_conn_state_user_flag_id_t  m_flag_local_db_apply_pending;  /**< Flag ID for flag collection to keep track of which connections need a local DB apply procedure. */
static ble_conn_state_user_flag_id_t  m_flag_service_changed_pending; /**< Flag ID for flag collection to keep track of which connections need to be sent a service changed indication. */
static ble_conn_state_user_flag_id_t  m_flag_service_changed_sent;    /**< Flag ID for flag collection to keep track of which connections have been sent a service changed indication and are waiting for a handle value confirmation. */
static ble_conn_state_user_flag_id_t  m_flag_car_update_pending;      /**< Flag ID for flag collection to keep track of which connections need to have their Central Address Resolution value stored. */
static ble_conn_state_user_flag_id_t  m_flag_car_handle_queried;      /**< Flag ID for flag collection to keep track of which connections are pending Central Address Resolution handle reply. */
static ble_conn_state_user_flag_id_t  m_flag_car_value_queried;       /**< Flag ID for flag collection to keep track of which connections are pending Central Address Resolution value reply. */

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
                .error     = err_code,
                .fds_error = false
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

            NRF_LOG_WARNING("The local database has changed, so some subscriptions to notifications "\
                            "and indications could not be restored for conn_handle %d",
                            conn_handle);
            evt_send(&event);
            break;

        case BLE_ERROR_INVALID_CONN_HANDLE:
            /* Do nothing */
            break;

        default:
            NRF_LOG_ERROR("gscm_local_db_cache_apply() returned %s which should not happen. "\
                          "conn_handle: %d",
                          nrf_strerror_get(err_code),
                          conn_handle);
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

            NRF_LOG_WARNING("Flash full. Could not store data for conn_handle: %d", conn_handle);
            evt_send(&event);
            break;
        }

        default:
            NRF_LOG_ERROR("gscm_local_db_cache_update() returned %s for conn_handle: %d",
                          nrf_strerror_get(err_code),
                          conn_handle);
            send_unexpected_error(conn_handle, err_code);
            break;
    }

    local_db_update(conn_handle, set_procedure_as_pending);

    return success;
}

#if PM_SERVICE_CHANGED_ENABLED

/**@brief Function for getting the value of the CCCD for the service changed characteristic.
 *
 * @details This function will search all system handles consecutively.
 *
 * @param[in]  conn_handle  The connection to check.
 * @param[out] p_cccd       The CCCD value of the service changed characteristic for this link.
 *
 * @return Any error from @ref sd_ble_gatts_value_get.
 */
static ret_code_t service_changed_cccd(uint16_t conn_handle, uint16_t * p_cccd)
{
    bool       sc_found = false;
    uint16_t   end_handle;
    ret_code_t err_code = sd_ble_gatts_initial_user_handle_get(&end_handle);
    ASSERT(err_code == NRF_SUCCESS);

    for (uint16_t handle = 1; handle < end_handle; handle++)
    {
        uint16_t uuid;
        ble_gatts_value_t value = {.p_value = (uint8_t *)&uuid, .len = 2, .offset = 0};
        err_code = sd_ble_gatts_value_get(conn_handle, handle, &value);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
        else if (!sc_found && (uuid == BLE_UUID_GATT_CHARACTERISTIC_SERVICE_CHANGED))
        {
            sc_found = true;
        }
        else if (sc_found && (uuid == BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG))
        {
            value.p_value = (uint8_t *)p_cccd;
            return sd_ble_gatts_value_get(conn_handle, ++handle, &value);
        }
    }
    return NRF_ERROR_NOT_FOUND;
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
        {
            uint16_t cccd;
            err_code = service_changed_cccd(conn_handle, &cccd);
            if ((err_code == NRF_SUCCESS) && cccd)
            {
                // Possible ATT_MTU exchange ongoing.
                // Do nothing, treat as busy.
                break;
            }
            else
            {
                if (err_code != NRF_SUCCESS)
                {
                    NRF_LOG_DEBUG("Unexpected error when looking for service changed CCCD: %s",
                                  nrf_strerror_get(err_code));
                }
                // CCCDs not enabled or an error happened. Drop indication.
                // Fallthrough.
            }
        }
            // Sometimes fallthrough.
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
            NRF_LOG_ERROR("gscm_service_changed_ind_send() returned %s for conn_handle: %d",
                          nrf_strerror_get(err_code),
                          conn_handle);
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
    if (nrf_mtx_trylock(&m_db_update_in_progress_mutex))
    {
        if (local_db_update_in_evt(conn_handle))
        {
            // Successfully started writing to flash.
            return;
        }
        else
        {
            nrf_mtx_unlock(&m_db_update_in_progress_mutex);
        }
    }
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


static void service_changed_needed(uint16_t conn_handle)
{
    if (gscm_service_changed_ind_needed(conn_handle))
    {
        ble_conn_state_user_flag_set(conn_handle, m_flag_service_changed_pending, true);
    }
}
#endif


static void car_update_pending_handle(uint16_t conn_handle, void * p_context)
{
    UNUSED_PARAMETER(p_context);

    ble_uuid_t car_uuid;
    memset(&car_uuid, 0, sizeof(ble_uuid_t));
    car_uuid.uuid = BLE_UUID_GAP_CHARACTERISTIC_CAR;
    car_uuid.type = BLE_UUID_TYPE_BLE;

    ble_gattc_handle_range_t const car_handle_range = {1, 0xFFFF};

    ret_code_t err_code = sd_ble_gattc_char_value_by_uuid_read(conn_handle, &car_uuid, &car_handle_range);
    if (err_code == NRF_SUCCESS)
    {
        ble_conn_state_user_flag_set(conn_handle, m_flag_car_handle_queried, true);
    }
}


static void car_update_needed(uint16_t conn_handle)
{
    pm_peer_data_t peer_data;
    if (pds_peer_data_read(im_peer_id_get_by_conn_handle(conn_handle),
                           PM_PEER_DATA_ID_CENTRAL_ADDR_RES,
                           &peer_data,
                           NULL) == NRF_ERROR_NOT_FOUND)
    {
        ble_conn_state_user_flag_set(conn_handle, m_flag_car_update_pending, true);
    }
}


static __INLINE void update_pending_flags_check(void)
{
    uint32_t count = ble_conn_state_for_each_set_user_flag(m_flag_local_db_update_pending,
                                                           db_update_pending_handle,
                                                           NULL);
    if (count == 0)
    {
        count = ble_conn_state_for_each_set_user_flag(m_flag_car_update_pending,
                                                      car_update_pending_handle,
                                                      NULL);
        UNUSED_RETURN_VALUE(count);
    }
}


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
            service_changed_needed(p_event->conn_handle);
#endif
            car_update_needed(p_event->conn_handle);
            update_pending_flags_check();
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
                    car_update_needed(conn_handle);
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
                if (m_db_update_in_progress_mutex == NRF_MTX_LOCKED)
                {
                    nrf_mtx_unlock(&m_db_update_in_progress_mutex);
                }

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
    m_flag_car_update_pending      = ble_conn_state_user_flag_acquire();
    m_flag_car_handle_queried      = ble_conn_state_user_flag_acquire();
    m_flag_car_value_queried       = ble_conn_state_user_flag_acquire();

    if  ((m_flag_local_db_update_pending  == BLE_CONN_STATE_USER_FLAG_INVALID)
      || (m_flag_local_db_apply_pending   == BLE_CONN_STATE_USER_FLAG_INVALID)
      || (m_flag_service_changed_pending  == BLE_CONN_STATE_USER_FLAG_INVALID)
      || (m_flag_service_changed_sent     == BLE_CONN_STATE_USER_FLAG_INVALID)
      || (m_flag_car_update_pending       == BLE_CONN_STATE_USER_FLAG_INVALID)
      || (m_flag_car_handle_queried       == BLE_CONN_STATE_USER_FLAG_INVALID)
      || (m_flag_car_value_queried        == BLE_CONN_STATE_USER_FLAG_INVALID)
      )
    {
        NRF_LOG_ERROR("Could not acquire conn_state user flags. Increase "\
                      "BLE_CONN_STATE_USER_FLAG_COUNT in the ble_conn_state module.");
        return NRF_ERROR_INTERNAL;
    }

    nrf_mtx_init(&m_db_update_in_progress_mutex);

    m_module_initialized = true;

    return NRF_SUCCESS;
}


void store_car_value(uint16_t conn_handle, bool car_value)
{
    // Use a uint32_t to enforce 4-byte alignment.
    static const uint32_t car_value_true  = true;
    static const uint32_t car_value_false = false;

    pm_peer_data_const_t peer_data =
    {
        .data_id      = PM_PEER_DATA_ID_CENTRAL_ADDR_RES,
        .length_words = 1,
    };

    ble_conn_state_user_flag_set(conn_handle, m_flag_car_update_pending, false);
    peer_data.p_central_addr_res = car_value ? &car_value_true : &car_value_false;
    ret_code_t err_code = pds_peer_data_store(im_peer_id_get_by_conn_handle(conn_handle), &peer_data, NULL);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_WARNING("CAR char value couldn't be stored (error: %s). Reattempt will happen on the next connection.", nrf_strerror_get(err_code));
    }
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

        case BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP:
        {
            bool handle_found = false;
            conn_handle = p_ble_evt->evt.gattc_evt.conn_handle;
            const ble_gattc_evt_char_val_by_uuid_read_rsp_t * p_val = &p_ble_evt->evt.gattc_evt.params.char_val_by_uuid_read_rsp;

            if (!ble_conn_state_user_flag_get(conn_handle, m_flag_car_handle_queried))
            {
                break;
            }

            ble_conn_state_user_flag_set(conn_handle, m_flag_car_handle_queried, false);

            if (p_ble_evt->evt.gattc_evt.gatt_status == BLE_GATT_STATUS_ATTERR_ATTRIBUTE_NOT_FOUND)
            {
                // Store 0.
            }
            else if (p_ble_evt->evt.gattc_evt.gatt_status != BLE_GATT_STATUS_SUCCESS)
            {
                NRF_LOG_WARNING("Unexpected GATT status while getting CAR char value: 0x%x",
                                p_ble_evt->evt.gattc_evt.gatt_status);
                // Store 0.
            }
            else
            {
                if (p_val->count != 1)
                {
                    NRF_LOG_WARNING("Multiple (%d) CAR characteristics found, using the first.",
                                    p_val->count);
                }

                if (p_val->value_len != 1)
                {
                    NRF_LOG_WARNING("Unexpected CAR characteristic value length (%d), store 0.",
                                    p_val->value_len);
                    // Store 0.
                }
                else
                {
                    ret_code_t err_code = sd_ble_gattc_read(conn_handle, *(uint16_t*)p_val->handle_value, 0);
                    if (err_code == NRF_SUCCESS)
                    {
                        handle_found = true;
                        ble_conn_state_user_flag_set(conn_handle, m_flag_car_value_queried, true);
                    }
                }
            }

            if (!handle_found)
            {
                store_car_value(conn_handle, false);
            }
            break;
        }

        case BLE_GATTC_EVT_READ_RSP:
        {
            bool car_value = false;
            conn_handle = p_ble_evt->evt.gattc_evt.conn_handle;
            const ble_gattc_evt_read_rsp_t * p_val = &p_ble_evt->evt.gattc_evt.params.read_rsp;

            if (!ble_conn_state_user_flag_get(conn_handle, m_flag_car_value_queried))
            {
                break;
            }

            ble_conn_state_user_flag_set(conn_handle, m_flag_car_value_queried, false);

            if (p_ble_evt->evt.gattc_evt.gatt_status != BLE_GATT_STATUS_SUCCESS)
            {
                NRF_LOG_WARNING("Unexpected GATT status while getting CAR char value: 0x%x",
                                p_ble_evt->evt.gattc_evt.gatt_status);
                // Store 0.
            }
            else
            {
                if (p_val->len != 1)
                {
                    NRF_LOG_WARNING("Unexpected CAR characteristic value length (%d), store 0.",
                                    p_val->len);
                    // Store 0.
                }
                else
                {
                    car_value = *p_val->data;
                }
            }

            store_car_value(conn_handle, car_value);
        }
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
