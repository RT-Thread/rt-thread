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
#include "ble_conn_state.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "ble.h"
#include "nrf_atflags.h"
#include "app_error.h"
#include "nrf_sdh_ble.h"
#include "app_util_platform.h"



#define DEFAULT_FLAG_COLLECTION_COUNT 5                                /**< The number of flags kept for each connection, excluding user flags. */
#define TOTAL_FLAG_COLLECTION_COUNT (DEFAULT_FLAG_COLLECTION_COUNT \
                                   + BLE_CONN_STATE_USER_FLAG_COUNT)   /**< The number of flags kept for each connection, including user flags. */

/**@brief Structure containing all the flag collections maintained by the Connection State module.
 */
typedef struct
{
    nrf_atflags_t valid_flags;                                 /**< Flags indicating which connection handles are valid. */
    nrf_atflags_t connected_flags;                             /**< Flags indicating which connections are connected, since disconnected connection handles will not immediately be invalidated. */
    nrf_atflags_t central_flags;                               /**< Flags indicating in which connections the local device is the central. */
    nrf_atflags_t encrypted_flags;                             /**< Flags indicating which connections are encrypted. */
    nrf_atflags_t mitm_protected_flags;                        /**< Flags indicating which connections have encryption with protection from man-in-the-middle attacks. */
    nrf_atflags_t user_flags[BLE_CONN_STATE_USER_FLAG_COUNT];  /**< Flags that can be reserved by the user. The flags will be cleared when a connection is invalidated, otherwise, the user is wholly responsible for the flag states. */
} ble_conn_state_flag_collections_t;


ANON_UNIONS_ENABLE;

/**@brief Structure containing the internal state of the Connection State module.
 */
typedef struct
{
    nrf_atflags_t acquired_flags; /**< Bitmap for keeping track of which user flags have been acquired. */
    union
    {
        ble_conn_state_flag_collections_t flags;                                   /**< Flag collections kept by the Connection State module. */
        nrf_atflags_t                     flag_array[TOTAL_FLAG_COLLECTION_COUNT]; /**< Flag collections as array to allow iterating over all flag collections. */
    };
} ble_conn_state_t;

ANON_UNIONS_DISABLE;


static ble_conn_state_t m_bcs = {0}; /**< Instantiation of the internal state. */


/**@brief Function for resetting all internal memory to the values it had at initialization.
 */
void bcs_internal_state_reset(void)
{
    memset( &m_bcs, 0, sizeof(ble_conn_state_t) );
}


ble_conn_state_conn_handle_list_t conn_handle_list_get(nrf_atflags_t flags)
{
    ble_conn_state_conn_handle_list_t conn_handle_list;
    conn_handle_list.len = 0;

    if (flags != 0)
    {
        for (uint32_t i = 0; i < BLE_CONN_STATE_MAX_CONNECTIONS; i++)
        {
            if (nrf_atflags_get(&flags, i))
            {
                conn_handle_list.conn_handles[conn_handle_list.len++] = i;
            }
        }
    }

    return conn_handle_list;
}


uint32_t active_flag_count(nrf_atflags_t flags)
{
    uint32_t set_flag_count = 0;

    for (uint32_t i = 0; i < BLE_CONN_STATE_MAX_CONNECTIONS; i++)
    {
        if (nrf_atflags_get(&flags, i))
        {
            set_flag_count += 1;
        }
    }
    return set_flag_count;
}


/**@brief Function for activating a connection record.
 *
 * @param p_record     The record to activate.
 * @param conn_handle  The connection handle to copy into the record.
 * @param role         The role of the connection.
 *
 * @return whether the record was activated successfully.
 */
static bool record_activate(uint16_t conn_handle)
{
    if (conn_handle >= BLE_CONN_STATE_MAX_CONNECTIONS)
    {
        return false;
    }
    nrf_atflags_set(&m_bcs.flags.connected_flags, conn_handle);
    nrf_atflags_set(&m_bcs.flags.valid_flags, conn_handle);
    return true;
}


/**@brief Function for marking a connection record as invalid and resetting the values.
 *
 * @param p_record  The record to invalidate.
 */
static void record_invalidate(uint16_t conn_handle)
{
    for (uint32_t i = 0; i < TOTAL_FLAG_COLLECTION_COUNT; i++)
    {
        nrf_atflags_clear(&m_bcs.flag_array[i], conn_handle);
    }
}


/**@brief Function for marking a connection as disconnected. See @ref BLE_CONN_STATUS_DISCONNECTED.
 *
 * @param p_record   The record of the connection to set as disconnected.
 */
static void record_set_disconnected(uint16_t conn_handle)
{
    nrf_atflags_clear(&m_bcs.flags.connected_flags, conn_handle);
}


/**@brief Function for invalidating records with a @ref BLE_CONN_STATUS_DISCONNECTED
 *        connection status
 */
static void record_purge_disconnected()
{
    nrf_atflags_t                     disconnected_flags = ~m_bcs.flags.connected_flags;
    ble_conn_state_conn_handle_list_t disconnected_list;

    UNUSED_RETURN_VALUE(nrf_atomic_u32_and(&disconnected_flags, m_bcs.flags.valid_flags));
    disconnected_list  =  conn_handle_list_get(disconnected_flags);

    for (uint32_t i = 0; i < disconnected_list.len; i++)
    {
        record_invalidate(disconnected_list.conn_handles[i]);
    }
}


/**@brief Function for checking if a user flag has been acquired.
 *
 * @param[in]  flag_id  Which flag to check.
 *
 * @return  Whether the flag has been acquired.
 */
static bool user_flag_is_acquired(ble_conn_state_user_flag_id_t flag_id)
{
    return nrf_atflags_get(&m_bcs.acquired_flags, flag_id);
}


void ble_conn_state_init(void)
{
    bcs_internal_state_reset();
}

/**
 * @brief Function for handling BLE events.
 *
 * @param[in]   p_ble_evt       Event received from the BLE stack.
 * @param[in]   p_context       Context.
 */
static void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context)
{
    uint16_t conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            record_purge_disconnected();

            if ( !record_activate(conn_handle) )
            {
                // No more records available. Should not happen.
                APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
            }
            else if ((p_ble_evt->evt.gap_evt.params.connected.role != BLE_GAP_ROLE_PERIPH))
            {
                // Central
                nrf_atflags_set(&m_bcs.flags.central_flags, conn_handle);
            }

            break;

        case BLE_GAP_EVT_DISCONNECTED:
            record_set_disconnected(conn_handle);
            break;

        case BLE_GAP_EVT_CONN_SEC_UPDATE:
        {
            bool encrypted = (p_ble_evt->evt.gap_evt.params.conn_sec_update.conn_sec.sec_mode.lv > 1);
            bool mitm      = (p_ble_evt->evt.gap_evt.params.conn_sec_update.conn_sec.sec_mode.lv > 2);

            if (encrypted)
            {
                nrf_atflags_set(&m_bcs.flags.encrypted_flags, conn_handle);
                if (mitm)
                {
                    nrf_atflags_set(&m_bcs.flags.mitm_protected_flags, conn_handle);
                }
                else
                {
                    nrf_atflags_clear(&m_bcs.flags.mitm_protected_flags, conn_handle);
                }
            }
            else
            {
                nrf_atflags_clear(&m_bcs.flags.encrypted_flags, conn_handle);
                nrf_atflags_clear(&m_bcs.flags.mitm_protected_flags, conn_handle);
            }
            break;
        }
    }
}

NRF_SDH_BLE_OBSERVER(m_ble_evt_observer, BLE_CONN_STATE_BLE_OBSERVER_PRIO, ble_evt_handler, NULL);


bool ble_conn_state_valid(uint16_t conn_handle)
{
    if (conn_handle >= BLE_CONN_STATE_MAX_CONNECTIONS)
    {
        return false;
    }
    return nrf_atflags_get(&m_bcs.flags.valid_flags, conn_handle);
}


uint8_t ble_conn_state_role(uint16_t conn_handle)
{
    uint8_t role = BLE_GAP_ROLE_INVALID;

    if (ble_conn_state_valid(conn_handle))
    {
#if !defined (S112)
        bool central = nrf_atflags_get(&m_bcs.flags.central_flags, conn_handle);
        role = central ? BLE_GAP_ROLE_CENTRAL : BLE_GAP_ROLE_PERIPH;
#else
        role = BLE_GAP_ROLE_PERIPH;
#endif // !defined (S112)
    }

    return role;
}


ble_conn_state_status_t ble_conn_state_status(uint16_t conn_handle)
{
    ble_conn_state_status_t conn_status = BLE_CONN_STATUS_INVALID;

    if (ble_conn_state_valid(conn_handle))
    {
        bool connected = nrf_atflags_get(&m_bcs.flags.connected_flags, conn_handle);
        conn_status = connected ? BLE_CONN_STATUS_CONNECTED : BLE_CONN_STATUS_DISCONNECTED;
    }

    return conn_status;
}


bool ble_conn_state_encrypted(uint16_t conn_handle)
{
    if (ble_conn_state_valid(conn_handle))
    {
        return nrf_atflags_get(&m_bcs.flags.encrypted_flags, conn_handle);
    }
    return false;
}


bool ble_conn_state_mitm_protected(uint16_t conn_handle)
{
    if (ble_conn_state_valid(conn_handle))
    {
        return nrf_atflags_get(&m_bcs.flags.mitm_protected_flags, conn_handle);
    }
    return false;
}


uint32_t ble_conn_state_conn_count(void)
{
    return active_flag_count(m_bcs.flags.connected_flags);
}


uint32_t ble_conn_state_central_conn_count(void)
{
    nrf_atflags_t central_conn_flags = m_bcs.flags.central_flags;
    UNUSED_RETURN_VALUE(nrf_atomic_u32_and(&central_conn_flags, m_bcs.flags.connected_flags));

    return active_flag_count(central_conn_flags);
}


uint32_t ble_conn_state_peripheral_conn_count(void)
{
    nrf_atflags_t peripheral_conn_flags = ~m_bcs.flags.central_flags;
    UNUSED_RETURN_VALUE(nrf_atomic_u32_and(&peripheral_conn_flags, m_bcs.flags.connected_flags));

    return active_flag_count(peripheral_conn_flags);
}


ble_conn_state_conn_handle_list_t ble_conn_state_conn_handles(void)
{
    return conn_handle_list_get(m_bcs.flags.valid_flags);
}


ble_conn_state_conn_handle_list_t ble_conn_state_central_handles(void)
{
    nrf_atflags_t central_conn_flags = m_bcs.flags.central_flags;
    UNUSED_RETURN_VALUE(nrf_atomic_u32_and(&central_conn_flags, m_bcs.flags.connected_flags));

    return conn_handle_list_get(central_conn_flags);
}


ble_conn_state_conn_handle_list_t ble_conn_state_periph_handles(void)
{
    nrf_atflags_t peripheral_conn_flags = ~m_bcs.flags.central_flags;
    UNUSED_RETURN_VALUE(nrf_atomic_u32_and(&peripheral_conn_flags, m_bcs.flags.connected_flags));

    return conn_handle_list_get(peripheral_conn_flags);
}


uint16_t ble_conn_state_conn_idx(uint16_t conn_handle)
{
    if (ble_conn_state_valid(conn_handle))
    {
        return conn_handle;
    }
    else
    {
        return BLE_CONN_STATE_MAX_CONNECTIONS;
    }
}


ble_conn_state_user_flag_id_t ble_conn_state_user_flag_acquire(void)
{
    uint32_t acquired_flag = nrf_atflags_find_and_set_flag(&m_bcs.acquired_flags,
                                                            BLE_CONN_STATE_USER_FLAG_COUNT);

    if (acquired_flag == BLE_CONN_STATE_USER_FLAG_COUNT)
    {
        return BLE_CONN_STATE_USER_FLAG_INVALID;
    }
    return (ble_conn_state_user_flag_id_t)acquired_flag;
}


bool ble_conn_state_user_flag_get(uint16_t conn_handle, ble_conn_state_user_flag_id_t flag_id)
{
    if (user_flag_is_acquired(flag_id) && ble_conn_state_valid(conn_handle))
    {
        return nrf_atflags_get(&m_bcs.flags.user_flags[flag_id], conn_handle);
    }
    else
    {
        return false;
    }
}


void ble_conn_state_user_flag_set(uint16_t                      conn_handle,
                                  ble_conn_state_user_flag_id_t flag_id,
                                  bool                          value)
{
    if (user_flag_is_acquired(flag_id) && ble_conn_state_valid(conn_handle))
    {
        if (value)
        {
            nrf_atflags_set(&m_bcs.flags.user_flags[flag_id], conn_handle);
        }
        else
        {
            nrf_atflags_clear(&m_bcs.flags.user_flags[flag_id], conn_handle);
        }
    }
}


static uint32_t for_each_set_flag(nrf_atflags_t                  flags,
                                  ble_conn_state_user_function_t user_function,
                                  void                         * p_context)
{
    if (user_function == NULL)
    {
        return 0;
    }

    uint32_t call_count = 0;

    if (flags != 0)
    {
        for (uint32_t i = 0; i < BLE_CONN_STATE_MAX_CONNECTIONS; i++)
        {
            if (nrf_atflags_get(&flags, i))
            {
                user_function(i, p_context);
                call_count += 1;
            }
        }
    }
    return call_count;
}


uint32_t ble_conn_state_for_each_connected(ble_conn_state_user_function_t user_function,
                                           void                         * p_context)
{
    return for_each_set_flag(m_bcs.flags.connected_flags, user_function, p_context);
}


uint32_t ble_conn_state_for_each_set_user_flag(ble_conn_state_user_flag_id_t  flag_id,
                                               ble_conn_state_user_function_t user_function,
                                               void                         * p_context)
{
    if (!user_flag_is_acquired(flag_id))
    {
        return 0;
    }

    return for_each_set_flag(m_bcs.flags.user_flags[flag_id], user_function, p_context);
}
