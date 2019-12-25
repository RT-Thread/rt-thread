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
#include "gatts_cache_manager.h"

#include <string.h>
#include "ble_gap.h"
#include "ble_err.h"
#include "peer_manager_types.h"
#include "peer_manager_internal.h"
#include "peer_database.h"
#include "peer_data_storage.h"
#include "id_manager.h"

#define NRF_LOG_MODULE_NAME peer_manager_gscm
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


#if !defined(PM_SERVICE_CHANGED_ENABLED) || (PM_SERVICE_CHANGED_ENABLED == 1)
// The number of registered event handlers.
#define GSCM_EVENT_HANDLERS_CNT      (sizeof(m_evt_handlers) / sizeof(m_evt_handlers[0]))

// GATTS Cache Manager event handler in Peer Manager.
extern void pm_gscm_evt_handler(pm_evt_t * p_gcm_evt);

// GATTS Cache Manager events' handlers.
// The number of elements in this array is GSCM_EVENT_HANDLERS_CNT.
static pm_evt_handler_internal_t m_evt_handlers[] =
{
    pm_gscm_evt_handler
};
#endif

// Syntactic sugar, two spoons.
#define SYS_ATTR_SYS                    (BLE_GATTS_SYS_ATTR_FLAG_SYS_SRVCS)
#define SYS_ATTR_USR                    (BLE_GATTS_SYS_ATTR_FLAG_USR_SRVCS)
#define SYS_ATTR_BOTH                   (SYS_ATTR_SYS | SYS_ATTR_USR)

static bool               m_module_initialized;
static pm_peer_id_t       m_current_sc_store_peer_id;


/**@brief Function for resetting the module variable(s) of the GSCM module.
 */
static void internal_state_reset()
{
    m_module_initialized       = false;
    m_current_sc_store_peer_id = PM_PEER_ID_INVALID;

    // If PM_SERVICE_CHANGED_ENABLED is 0, this variable is unused.
    UNUSED_VARIABLE(m_current_sc_store_peer_id);
}


#if !defined(PM_SERVICE_CHANGED_ENABLED) || (PM_SERVICE_CHANGED_ENABLED == 1)
static void evt_send(pm_evt_t * p_gscm_evt)
{
    p_gscm_evt->conn_handle = im_conn_handle_get(p_gscm_evt->peer_id);

    for (uint32_t i = 0; i < GSCM_EVENT_HANDLERS_CNT; i++)
    {
        m_evt_handlers[i](p_gscm_evt);
    }
}


//lint -save -e550
/**@brief Function for storing service_changed_pending = true to flash for all peers, in sequence.
 *
 * This function aborts if it gets @ref NRF_ERROR_BUSY when trying to store. A subsequent call will
 * continue where the last call was aborted.
 */
static void service_changed_pending_set(void)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    ret_code_t err_code;
    // Use a uint32_t to enforce 4-byte alignment.
    static const uint32_t service_changed_pending = true;

    //lint -save -e65 -e64
    pm_peer_data_const_t peer_data =
    {
        .data_id                   = PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING,
        .length_words              = PM_SC_STATE_N_WORDS(),
        .p_service_changed_pending = (bool*)&service_changed_pending,
    };
    //lint -restore

    while (m_current_sc_store_peer_id != PM_PEER_ID_INVALID)
    {
        err_code = pds_peer_data_store(m_current_sc_store_peer_id, &peer_data, NULL);
        if (err_code != NRF_SUCCESS)
        {
            pm_evt_t evt = {.peer_id = m_current_sc_store_peer_id};
            if (err_code == NRF_ERROR_BUSY)
            {
                // Do nothing.
            }
            else if (err_code == NRF_ERROR_STORAGE_FULL)
            {
                evt.evt_id = PM_EVT_STORAGE_FULL;
                evt_send(&evt);
            }
            else
            {
                NRF_LOG_ERROR("pds_peer_data_store() returned %s while storing service changed"\
                              "state for peer id %d.",
                              nrf_strerror_get(err_code),
                              m_current_sc_store_peer_id);
                evt.evt_id = PM_EVT_ERROR_UNEXPECTED;
                evt.params.error_unexpected.error = err_code;
                evt_send(&evt);
            }
            break;
        }

        m_current_sc_store_peer_id = pds_next_peer_id_get(m_current_sc_store_peer_id);
    }
}
//lint -restore



/**@brief Event handler for events from the Peer Database module.
 *        This function is extern in Peer Database.
 *
 * @param[in]  p_event The event that has happened with peer id and flags.
 */
void gscm_pdb_evt_handler(pm_evt_t * p_event)
{
    if (m_current_sc_store_peer_id != PM_PEER_ID_INVALID)
    {
        service_changed_pending_set();
    }
}
#endif


ret_code_t gscm_init()
{
    NRF_PM_DEBUG_CHECK(!m_module_initialized);

    internal_state_reset();
    m_module_initialized = true;

    return NRF_SUCCESS;
}


ret_code_t gscm_local_db_cache_update(uint16_t conn_handle)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    pm_peer_id_t peer_id = im_peer_id_get_by_conn_handle(conn_handle);
    ret_code_t   err_code;

    if (peer_id == PM_PEER_ID_INVALID)
    {
        return BLE_ERROR_INVALID_CONN_HANDLE;
    }
    else
    {
        pm_peer_data_t peer_data;
        uint16_t       n_bufs = 1;
        bool           retry_with_bigger_buffer = false;

        do
        {
            retry_with_bigger_buffer = false;

            err_code = pdb_write_buf_get(peer_id, PM_PEER_DATA_ID_GATT_LOCAL, n_bufs++, &peer_data);
            if (err_code == NRF_SUCCESS)
            {
                pm_peer_data_local_gatt_db_t * p_local_gatt_db = peer_data.p_local_gatt_db;

                p_local_gatt_db->flags = SYS_ATTR_BOTH;

                err_code = sd_ble_gatts_sys_attr_get(conn_handle, &p_local_gatt_db->data[0], &p_local_gatt_db->len, p_local_gatt_db->flags);

                if (err_code == NRF_SUCCESS)
                {
                    err_code = pdb_write_buf_store(peer_id, PM_PEER_DATA_ID_GATT_LOCAL, peer_id);
                }
                else
                {
                    if (err_code == NRF_ERROR_DATA_SIZE)
                    {
                        // The sys attributes are bigger than the requested write buffer.
                        retry_with_bigger_buffer = true;
                    }
                    else if (err_code == NRF_ERROR_NOT_FOUND)
                    {
                        // There are no sys attributes in the GATT db, so nothing needs to be stored.
                        err_code = NRF_SUCCESS;
                    }

                    ret_code_t err_code_release = pdb_write_buf_release(peer_id, PM_PEER_DATA_ID_GATT_LOCAL);
                    if (err_code_release != NRF_SUCCESS)
                    {
                        NRF_LOG_ERROR("Did another thread manipulate PM_PEER_DATA_ID_GATT_LOCAL for "\
                                      "peer_id %d at the same time? pdb_write_buf_release() returned %s.",
                                      peer_id,
                                      nrf_strerror_get(err_code_release));
                        err_code = NRF_ERROR_INTERNAL;
                    }
                }
            }
            else if (err_code == NRF_ERROR_INVALID_PARAM)
            {
                // The sys attributes are bigger than the entire write buffer.
                err_code = NRF_ERROR_DATA_SIZE;
            }
        } while (retry_with_bigger_buffer);
    }

    return err_code;
}


ret_code_t gscm_local_db_cache_apply(uint16_t conn_handle)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    pm_peer_id_t         peer_id = im_peer_id_get_by_conn_handle(conn_handle);
    ret_code_t           err_code;
    pm_peer_data_flash_t peer_data;
    uint8_t      const * p_sys_attr_data = NULL;
    uint16_t             sys_attr_len    = 0;
    uint32_t             sys_attr_flags  = (SYS_ATTR_BOTH);
    bool                 all_attributes_applied = true;

    if (peer_id != PM_PEER_ID_INVALID)
    {
        err_code = pdb_peer_data_ptr_get(peer_id, PM_PEER_DATA_ID_GATT_LOCAL, &peer_data);
        if (err_code == NRF_SUCCESS)
        {
            pm_peer_data_local_gatt_db_t const * p_local_gatt_db;

            p_local_gatt_db = peer_data.p_local_gatt_db;
            p_sys_attr_data = p_local_gatt_db->data;
            sys_attr_len    = p_local_gatt_db->len;
            sys_attr_flags  = p_local_gatt_db->flags;
        }
    }

    do
    {
        err_code = sd_ble_gatts_sys_attr_set(conn_handle, p_sys_attr_data, sys_attr_len, sys_attr_flags);

        if (err_code == NRF_ERROR_NO_MEM)
        {
            err_code = NRF_ERROR_BUSY;
        }
        else if (err_code == NRF_ERROR_INVALID_STATE)
        {
            err_code = NRF_SUCCESS;
        }
        else if (err_code == NRF_ERROR_INVALID_DATA)
        {
            all_attributes_applied = false;

            if (sys_attr_flags & SYS_ATTR_USR)
            {
                // Try setting only system attributes.
                sys_attr_flags = SYS_ATTR_SYS;
            }
            else if (p_sys_attr_data || sys_attr_len)
            {
                // Try reporting that none exist.
                p_sys_attr_data = NULL;
                sys_attr_len    = 0;
                sys_attr_flags  = SYS_ATTR_BOTH;
            }
            else
            {
                NRF_LOG_ERROR("sd_ble_gatts_sys_attr_set() returned NRF_ERROR_INVALID_DATA for NULL "\
                              "pointer which should never happen. conn_handle: %d",
                              conn_handle);
                err_code = NRF_ERROR_INTERNAL;
            }
        }
    } while (err_code == NRF_ERROR_INVALID_DATA);

    if (!all_attributes_applied)
    {
        err_code = NRF_ERROR_INVALID_DATA;
    }

    return err_code;
}

#if !defined(PM_SERVICE_CHANGED_ENABLED) || (PM_SERVICE_CHANGED_ENABLED == 1)
void gscm_local_database_has_changed(void)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    m_current_sc_store_peer_id = pds_next_peer_id_get(PM_PEER_ID_INVALID);
    service_changed_pending_set();
}


bool gscm_service_changed_ind_needed(uint16_t conn_handle)
{
    ret_code_t           err_code;
    bool                 service_changed_state;
    pm_peer_data_flash_t peer_data;

    peer_data.p_service_changed_pending = &service_changed_state;
    pm_peer_id_t peer_id = im_peer_id_get_by_conn_handle(conn_handle);

    err_code = pdb_peer_data_ptr_get(peer_id, PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING, &peer_data);

    if (err_code != NRF_SUCCESS)
    {
        return false;
    }

    return *peer_data.p_service_changed_pending;
}


ret_code_t gscm_service_changed_ind_send(uint16_t conn_handle)
{
    static uint16_t start_handle;
    const  uint16_t end_handle = 0xFFFF;
    ret_code_t err_code;

    err_code = sd_ble_gatts_initial_user_handle_get(&start_handle);

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("sd_ble_gatts_initial_user_handle_get() returned %s which should not happen.",
                      nrf_strerror_get(err_code));
        return NRF_ERROR_INTERNAL;
    }

    do
    {
        err_code = sd_ble_gatts_service_changed(conn_handle, start_handle, end_handle);
        if (err_code == BLE_ERROR_INVALID_ATTR_HANDLE)
        {
            start_handle += 1;
        }
    } while (err_code == BLE_ERROR_INVALID_ATTR_HANDLE);

    return err_code;
}


void gscm_db_change_notification_done(pm_peer_id_t peer_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    // Use a uint32_t to enforce 4-byte alignment.
    static const uint32_t service_changed_pending = false;

    //lint -save -e65 -e64
    pm_peer_data_const_t peer_data =
    {
        .data_id                   = PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING,
        .length_words              = PM_SC_STATE_N_WORDS(),
        .p_service_changed_pending = (bool*)&service_changed_pending,
    };
    //lint -restore

    // Don't need to check return code, because all error conditions can be ignored.
    //lint -save -e550
    (void) pds_peer_data_store(peer_id, &peer_data, NULL);
    //lint -restore
}
#endif
#endif // NRF_MODULE_ENABLED(PEER_MANAGER)
