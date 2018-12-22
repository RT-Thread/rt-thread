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
#include "ble_conn_state.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "ble.h"
#include "sdk_mapped_flags.h"
#include "app_error.h"


#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#endif


#define BLE_CONN_STATE_N_DEFAULT_FLAGS 5                                                       /**< The number of flags kept for each connection, excluding user flags. */
#define BLE_CONN_STATE_N_FLAGS (BLE_CONN_STATE_N_DEFAULT_FLAGS + BLE_CONN_STATE_N_USER_FLAGS)  /**< The number of flags kept for each connection, including user flags. */


/**@brief Structure containing all the flag collections maintained by the Connection State module.
 */
typedef struct
{
    sdk_mapped_flags_t valid_flags;                                 /**< Flags indicating which connection handles are valid. */
    sdk_mapped_flags_t connected_flags;                             /**< Flags indicating which connections are connected, since disconnected connection handles will not immediately be invalidated. */
    sdk_mapped_flags_t central_flags;                               /**< Flags indicating in which connections the local device is the central. */
    sdk_mapped_flags_t encrypted_flags;                             /**< Flags indicating which connections are encrypted. */
    sdk_mapped_flags_t mitm_protected_flags;                        /**< Flags indicating which connections have encryption with protection from man-in-the-middle attacks. */
    sdk_mapped_flags_t user_flags[BLE_CONN_STATE_N_USER_FLAGS];     /**< Flags that can be reserved by the user. The flags will be cleared when a connection is invalidated, otherwise, the user is wholly responsible for the flag states. */
} ble_conn_state_flag_collections_t;


/**@brief Structure containing the internal state of the Connection State module.
 */
typedef struct
{
    uint32_t           acquired_flags;                              /**< Bitmap for keeping track of which user flags have been acquired. */
    uint16_t           valid_conn_handles[SDK_MAPPED_FLAGS_N_KEYS]; /**< List of connection handles used as keys for the sdk_mapped_flags module. */
    union
    {
        ble_conn_state_flag_collections_t flags;                              /**< Flag collections kept by the Connection State module. */
        sdk_mapped_flags_t                flag_array[BLE_CONN_STATE_N_FLAGS]; /**< Flag collections as array to allow use of @ref sdk_mapped_flags_bulk_update_by_key() when setting all flags. */
    };
} ble_conn_state_t;


#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#endif


static ble_conn_state_t m_bcs = {0}; /**< Instantiation of the internal state. */


/**@brief Function for resetting all internal memory to the values it had at initialization.
 */
void bcs_internal_state_reset(void)
{
    memset( &m_bcs, 0, sizeof(ble_conn_state_t) );
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
    uint16_t available_index = sdk_mapped_flags_first_key_index_get(~m_bcs.flags.valid_flags);

    if (available_index != SDK_MAPPED_FLAGS_INVALID_INDEX)
    {
        m_bcs.valid_conn_handles[available_index] = conn_handle;
        sdk_mapped_flags_update_by_key(m_bcs.valid_conn_handles,
                                      &m_bcs.flags.connected_flags,
                                       conn_handle,
                                       1);
        sdk_mapped_flags_update_by_key(m_bcs.valid_conn_handles,
                                      &m_bcs.flags.valid_flags,
                                       conn_handle,
                                       1);

        return true;
    }

    return false;
}


/**@brief Function for marking a connection record as invalid and resetting the values.
 *
 * @param p_record  The record to invalidate.
 */
static void record_invalidate(uint16_t conn_handle)
{
    sdk_mapped_flags_bulk_update_by_key(m_bcs.valid_conn_handles,
                                        m_bcs.flag_array,
                                        BLE_CONN_STATE_N_FLAGS,
                                        conn_handle,
                                        0);
}


/**@brief Function for marking a connection as disconnected. See @ref BLE_CONN_STATUS_DISCONNECTED.
 *
 * @param p_record   The record of the connection to set as disconnected.
 */
static void record_set_disconnected(uint16_t conn_handle)
{
    sdk_mapped_flags_update_by_key(m_bcs.valid_conn_handles,
                                  &m_bcs.flags.connected_flags,
                                   conn_handle,
                                   0);
}


/**@brief Function for invalidating records with a @ref BLE_CONN_STATUS_DISCONNECTED
 *        connection status
 */
static void record_purge_disconnected()
{
    sdk_mapped_flags_key_list_t disconnected_list;

    disconnected_list = sdk_mapped_flags_key_list_get(
                                   m_bcs.valid_conn_handles,
                                 (~m_bcs.flags.connected_flags) & (m_bcs.flags.valid_flags));

    for (uint32_t i = 0; i < disconnected_list.len; i++)
    {
        record_invalidate(disconnected_list.flag_keys[i]);
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
    return ((m_bcs.acquired_flags & (1 << flag_id)) != 0);
}


/**@brief Function for marking a user flag as acquired.
 *
 * @param[in]  flag_id  Which flag to mark.
 */
static void user_flag_acquire(ble_conn_state_user_flag_id_t flag_id)
{
    m_bcs.acquired_flags |= (1 << flag_id);
}


void ble_conn_state_init(void)
{
    bcs_internal_state_reset();
}


void ble_conn_state_on_ble_evt(ble_evt_t * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            record_purge_disconnected();

            if ( !record_activate(p_ble_evt->evt.gap_evt.conn_handle) )
            {
                // No more records available. Should not happen.
                APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
            }
            else
            {
                bool is_central =
                        (p_ble_evt->evt.gap_evt.params.connected.role == BLE_GAP_ROLE_CENTRAL);

                sdk_mapped_flags_update_by_key(m_bcs.valid_conn_handles,
                                              &m_bcs.flags.central_flags,
                                               p_ble_evt->evt.gap_evt.conn_handle,
                                               is_central);
            }

            break;

        case BLE_GAP_EVT_DISCONNECTED:
            record_set_disconnected(p_ble_evt->evt.gap_evt.conn_handle);
            break;

        case BLE_GAP_EVT_CONN_SEC_UPDATE:
            sdk_mapped_flags_update_by_key(
                          m_bcs.valid_conn_handles,
                         &m_bcs.flags.encrypted_flags,
                          p_ble_evt->evt.gap_evt.conn_handle,
                         (p_ble_evt->evt.gap_evt.params.conn_sec_update.conn_sec.sec_mode.lv > 1));
            sdk_mapped_flags_update_by_key(
                          m_bcs.valid_conn_handles,
                         &m_bcs.flags.mitm_protected_flags,
                          p_ble_evt->evt.gap_evt.conn_handle,
                         (p_ble_evt->evt.gap_evt.params.conn_sec_update.conn_sec.sec_mode.lv > 2));
            break;
    }
}


bool ble_conn_state_valid(uint16_t conn_handle)
{
    return sdk_mapped_flags_get_by_key(m_bcs.valid_conn_handles,
                                       m_bcs.flags.valid_flags,
                                       conn_handle);
}


uint8_t ble_conn_state_role(uint16_t conn_handle)
{
    uint8_t role = BLE_GAP_ROLE_INVALID;

    if ( sdk_mapped_flags_get_by_key(m_bcs.valid_conn_handles, m_bcs.flags.valid_flags, conn_handle) )
    {
        bool central = sdk_mapped_flags_get_by_key(m_bcs.valid_conn_handles,
                                                   m_bcs.flags.central_flags,
                                                   conn_handle);

        role = central ? BLE_GAP_ROLE_CENTRAL : BLE_GAP_ROLE_PERIPH;
    }

    return role;
}


ble_conn_state_status_t ble_conn_state_status(uint16_t conn_handle)
{
    ble_conn_state_status_t conn_status = BLE_CONN_STATUS_INVALID;
    bool valid = sdk_mapped_flags_get_by_key(m_bcs.valid_conn_handles,
                                             m_bcs.flags.valid_flags,
                                             conn_handle);

    if (valid)
    {
        bool connected = sdk_mapped_flags_get_by_key(m_bcs.valid_conn_handles,
                                                     m_bcs.flags.connected_flags,
                                                     conn_handle);

        conn_status = connected ? BLE_CONN_STATUS_CONNECTED : BLE_CONN_STATUS_DISCONNECTED;
    }

    return conn_status;
}


bool ble_conn_state_encrypted(uint16_t conn_handle)
{
    return sdk_mapped_flags_get_by_key(m_bcs.valid_conn_handles,
                                       m_bcs.flags.encrypted_flags,
                                       conn_handle);
}


bool ble_conn_state_mitm_protected(uint16_t conn_handle)
{
    return sdk_mapped_flags_get_by_key(m_bcs.valid_conn_handles,
                                       m_bcs.flags.mitm_protected_flags,
                                       conn_handle);
}


uint32_t ble_conn_state_n_connections(void)
{
    return sdk_mapped_flags_n_flags_set(m_bcs.flags.connected_flags);
}


uint32_t ble_conn_state_n_centrals(void)
{
    return sdk_mapped_flags_n_flags_set((m_bcs.flags.central_flags) & (m_bcs.flags.connected_flags));
}


uint32_t ble_conn_state_n_peripherals(void)
{
    return sdk_mapped_flags_n_flags_set((~m_bcs.flags.central_flags) & (m_bcs.flags.connected_flags));
}


sdk_mapped_flags_key_list_t ble_conn_state_conn_handles(void)
{
    return sdk_mapped_flags_key_list_get(m_bcs.valid_conn_handles, m_bcs.flags.valid_flags);
}


sdk_mapped_flags_key_list_t ble_conn_state_central_handles(void)
{
    return sdk_mapped_flags_key_list_get(m_bcs.valid_conn_handles,
                                        (m_bcs.flags.central_flags) & (m_bcs.flags.connected_flags));
}


sdk_mapped_flags_key_list_t ble_conn_state_periph_handles(void)
{
    return sdk_mapped_flags_key_list_get(m_bcs.valid_conn_handles,
                                        (~m_bcs.flags.central_flags) & (m_bcs.flags.connected_flags));
}


ble_conn_state_user_flag_id_t ble_conn_state_user_flag_acquire(void)
{
    for (ble_conn_state_user_flag_id_t i = BLE_CONN_STATE_USER_FLAG0;
                                       i < BLE_CONN_STATE_N_USER_FLAGS;
                                       i++)
    {
        if ( !user_flag_is_acquired(i) )
        {
            user_flag_acquire(i);
            return i;
        }
    }

    return BLE_CONN_STATE_USER_FLAG_INVALID;
}


bool ble_conn_state_user_flag_get(uint16_t conn_handle, ble_conn_state_user_flag_id_t flag_id)
{
    if (user_flag_is_acquired(flag_id))
    {
        return sdk_mapped_flags_get_by_key(m_bcs.valid_conn_handles,
                                           m_bcs.flags.user_flags[flag_id],
                                           conn_handle);
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
    if (user_flag_is_acquired(flag_id))
    {
        sdk_mapped_flags_update_by_key(m_bcs.valid_conn_handles,
                                      &m_bcs.flags.user_flags[flag_id],
                                       conn_handle,
                                       value);
    }
}


sdk_mapped_flags_t ble_conn_state_user_flag_collection(ble_conn_state_user_flag_id_t flag_id)
{
    if ( user_flag_is_acquired(flag_id) )
    {
        return m_bcs.flags.user_flags[flag_id];
    }
    else
    {
        return 0;
    }
}
