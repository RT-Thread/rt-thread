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
#include "id_manager.h"

#include <string.h>
#include "ble.h"
#include "ble_gap.h"
#include "ble_conn_state.h"
#include "peer_manager_types.h"
#include "peer_database.h"
#include "peer_data_storage.h"
#include "nrf_soc.h"


#define IM_MAX_CONN_HANDLES             (20)
#define IM_NO_INVALID_CONN_HANDLES      (0xFF)
#define IM_ADDR_CLEARTEXT_LENGTH        (3)
#define IM_ADDR_CIPHERTEXT_LENGTH       (3)

// The number of registered event handlers.
#define IM_EVENT_HANDLERS_CNT           (sizeof(m_evt_handlers) / sizeof(m_evt_handlers[0]))


// Identity Manager event handlers in Peer Manager and GATT Cache Manager.
extern void pm_im_evt_handler(im_evt_t const * p_event);
extern void gcm_im_evt_handler(im_evt_t const * p_event);

// Identity Manager events' handlers.
// The number of elements in this array is IM_EVENT_HANDLERS_CNT.
static im_evt_handler_t const m_evt_handlers[] =
{
    pm_im_evt_handler,
    gcm_im_evt_handler
};


typedef struct
{
    pm_peer_id_t   peer_id;
    uint16_t       conn_handle;
    ble_gap_addr_t peer_address;
} im_connection_t;

static bool                             m_module_initialized;
static im_connection_t                  m_connections[IM_MAX_CONN_HANDLES];
static ble_conn_state_user_flag_id_t    m_conn_state_user_flag_id;

static uint8_t                          m_wlisted_peer_cnt;
static pm_peer_id_t                     m_wlisted_peers[BLE_GAP_WHITELIST_ADDR_MAX_COUNT];

#if (NRF_SD_BLE_API_VERSION <= 2)
    static ble_gap_addr_t               m_current_id_addr;
#endif


static void internal_state_reset()
{
    m_conn_state_user_flag_id = BLE_CONN_STATE_USER_FLAG_INVALID;

    for (uint32_t i = 0; i < IM_MAX_CONN_HANDLES; i++)
    {
        m_connections[i].conn_handle = BLE_CONN_HANDLE_INVALID;
    }
}


/**@brief Function for sending an event to all registered event handlers.
 *
 * @param[in] p_event The event to distribute.
 */
static void evt_send(im_evt_t * p_event)
{
    for (uint32_t i = 0; i < IM_EVENT_HANDLERS_CNT; i++)
    {
        m_evt_handlers[i](p_event);
    }
}

/**@brief Function finding a free position in m_connections.
 *
 * @detail All connection handles in the m_connections array are checked against the connection
 *         state module. The index of the first one that is not a connection handle for a current
 *         connection is returned. This position in the array can safely be used for a new connection.
 *
 * @return Either the index of a free position in the array or IM_NO_INVALID_CONN_HANDLES if no free
           position exists.
 */
uint8_t get_free_connection()
{
    for (uint32_t i = 0; i < IM_MAX_CONN_HANDLES; i++)
    {
        // Query the connection state module to check if the
        // connection handle does not belong to a valid connection.
        if (!ble_conn_state_user_flag_get(m_connections[i].conn_handle, m_conn_state_user_flag_id))
        {
            return i;
        }
    }
    // If all connection handles belong to a valid connection, return IM_NO_INVALID_CONN_HANDLES.
    return IM_NO_INVALID_CONN_HANDLES;
}


/**@brief Function finding a particular connection handle m_connections.
 *
 * @param[in]  conn_handle  The handle to find.
 *
 * @return Either the index of the conn_handle in the array or IM_NO_INVALID_CONN_HANDLES if the
 *         handle was not found.
 */
uint8_t get_connection_by_conn_handle(uint16_t conn_handle)
{
    if (ble_conn_state_user_flag_get(conn_handle, m_conn_state_user_flag_id))
    {
        for (uint32_t i = 0; i < IM_MAX_CONN_HANDLES; i++)
        {
            if (m_connections[i].conn_handle == conn_handle)
            {
                return i;
            }
        }
    }
    // If all connection handles belong to a valid connection, return IM_NO_INVALID_CONN_HANDLES.
    return IM_NO_INVALID_CONN_HANDLES;
}


/**@brief Function for registering a new connection instance.
 *
 * @param[in]  conn_handle  The handle of the new connection.
 * @param[in]  p_ble_addr   The address used to connect.
 *
 * @return Either the index of the new connection in the array or IM_NO_INVALID_CONN_HANDLES if no
 *         free position exists.
 */
uint8_t new_connection(uint16_t conn_handle, ble_gap_addr_t * p_ble_addr)
{
    uint8_t conn_index = IM_NO_INVALID_CONN_HANDLES;

    if ((p_ble_addr != NULL) && (conn_handle != BLE_CONN_HANDLE_INVALID))
    {
        ble_conn_state_user_flag_set(conn_handle, m_conn_state_user_flag_id, true);

        conn_index = get_connection_by_conn_handle(conn_handle);
        if (conn_index == IM_NO_INVALID_CONN_HANDLES)
        {
            conn_index = get_free_connection();
        }

        if (conn_index != IM_NO_INVALID_CONN_HANDLES)
        {
            m_connections[conn_index].conn_handle  = conn_handle;
            m_connections[conn_index].peer_id      = PM_PEER_ID_INVALID;
            m_connections[conn_index].peer_address = *p_ble_addr;
        }
    }
    return conn_index;
}


/**@brief Function checking the validity of an IRK
 *
 * @detail An all-zero IRK is not valid. This function will check if a given IRK is valid.
 *
 * @param[in] p_irk The IRK for which the validity is going to be checked.
 *
 * @retval true  The IRK is valid.
 * @retval false The IRK is invalid.
 */
bool is_valid_irk(ble_gap_irk_t const * p_irk)
{
    NRF_PM_DEBUG_CHECK(p_irk != NULL);

    for (uint32_t i = 0; i < BLE_GAP_SEC_KEY_LEN; i++)
    {
        if (p_irk->irk[i] != 0)
        {
            return true;
        }
    }
    return false;
}


/**@brief Function for comparing two addresses to determine if they are identical
 *
 * @note The address type need to be identical, as well as every bit in the address itself.
 *
 * @param[in] p_addr1 The first address to be compared.
 * @param[in] p_addr2 The second address to be compared.
 *
 * @retval true  The addresses are identical.
 * @retval false The addresses are not identical.
 */
bool addr_compare(ble_gap_addr_t const * p_addr1, ble_gap_addr_t const * p_addr2)
{
    // @note emdi: use NRF_PM_DEBUG_CHECK ?
    if ((p_addr1 == NULL) || (p_addr2 == NULL))
    {
        return false;
    }

    // Check that the addr type is identical, return false if it is not
    if (p_addr1->addr_type != p_addr2->addr_type)
    {
        return false;
    }
    // Check if the addr bytes are is identical
    return (memcmp(p_addr1->addr, p_addr2->addr, BLE_GAP_ADDR_LEN) == 0);
}


void im_ble_evt_handler(ble_evt_t * ble_evt)
{
    ble_gap_evt_t gap_evt;
    pm_peer_id_t  bonded_matching_peer_id;

    NRF_PM_DEBUG_CHECK(m_module_initialized);

    if (ble_evt->header.evt_id != BLE_GAP_EVT_CONNECTED)
    {
        // Nothing to do.
        return;
    }

    gap_evt                 = ble_evt->evt.gap_evt;
    bonded_matching_peer_id = PM_PEER_ID_INVALID;

    if (   gap_evt.params.connected.peer_addr.addr_type
        != BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_NON_RESOLVABLE)
    {
        /* Search the database for bonding data matching the one that triggered the event.
         * Public and static addresses can be matched on address alone, while resolvable
         * random addresses can be resolved agains known IRKs. Non-resolvable random addresses
         * are never matching because they are not longterm form of identification.
         */

        pm_peer_id_t         peer_id;
        pm_peer_data_flash_t peer_data;

        pds_peer_data_iterate_prepare();

        switch (gap_evt.params.connected.peer_addr.addr_type)
        {
            case BLE_GAP_ADDR_TYPE_PUBLIC:
            case BLE_GAP_ADDR_TYPE_RANDOM_STATIC:
            {
                while (pds_peer_data_iterate(PM_PEER_DATA_ID_BONDING, &peer_id, &peer_data))
                {
                    if (addr_compare(&gap_evt.params.connected.peer_addr,
                                     &peer_data.p_bonding_data->peer_ble_id.id_addr_info))
                    {
                        bonded_matching_peer_id = peer_id;
                        break;
                    }
                }
            }
            break;

            case BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE:
            {
                while (pds_peer_data_iterate(PM_PEER_DATA_ID_BONDING, &peer_id, &peer_data))
                {
                    if (im_address_resolve(&gap_evt.params.connected.peer_addr,
                                           &peer_data.p_bonding_data->peer_ble_id.id_info))
                    {
                        bonded_matching_peer_id = peer_id;
                        break;
                    }
                }
            }
            break;

            default:
                NRF_PM_DEBUG_CHECK(false);
                break;
        }
    }

    uint8_t new_index = new_connection(gap_evt.conn_handle,
                                       &gap_evt.params.connected.peer_addr);
    UNUSED_VARIABLE(new_index);

    if (bonded_matching_peer_id != PM_PEER_ID_INVALID)
    {
        im_new_peer_id(gap_evt.conn_handle, bonded_matching_peer_id);

        // Send a bonded peer event
        im_evt_t im_evt;
        im_evt.conn_handle = gap_evt.conn_handle;
        im_evt.evt_id      = IM_EVT_BONDED_PEER_CONNECTED;
        evt_send(&im_evt);
    }
}


/**@brief Function to compare two sets of bonding data to check if they belong to the same device.
 * @note  Invalid irks will never match even though they are identical.
 *
 * @param[in]  p_bonding_data1 First bonding data for comparison
 * @param[in]  p_bonding_data2 Second bonding data for comparison
 *
 * @return     True if the input matches, false if it does not.
 */
bool im_is_duplicate_bonding_data(pm_peer_data_bonding_t const * p_bonding_data1,
                                  pm_peer_data_bonding_t const * p_bonding_data2)
{
    NRF_PM_DEBUG_CHECK(p_bonding_data1 != NULL);
    NRF_PM_DEBUG_CHECK(p_bonding_data2 != NULL);

    if (!is_valid_irk(&p_bonding_data1->peer_ble_id.id_info))
    {
        return false;
    }

    bool duplicate_irk = (memcmp(p_bonding_data1->peer_ble_id.id_info.irk,
                                 p_bonding_data2->peer_ble_id.id_info.irk,
                                 BLE_GAP_SEC_KEY_LEN) == 0);

    bool duplicate_addr = addr_compare(&p_bonding_data1->peer_ble_id.id_addr_info,
                                       &p_bonding_data2->peer_ble_id.id_addr_info);

    return duplicate_irk || duplicate_addr;
}


/**@brief Event handler for events from the Peer Database module.
 *        This function is extern in Peer Database.
 *
 * @param[in]  p_event The event that has happend with peer id and flags.
 */
void im_pdb_evt_handler(pdb_evt_t const * p_event)
{
    ret_code_t           ret;
    pm_peer_id_t         peer_id;
    pm_peer_data_flash_t peer_data;
    pm_peer_data_flash_t peer_data_duplicate;

    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_event != NULL);

    if ((p_event->evt_id  != PDB_EVT_WRITE_BUF_STORED) ||
        (p_event->data_id != PM_PEER_DATA_ID_BONDING))
    {
        return;
    }

    // If new data about peer id has been stored it is compared to other peers peer ids in
    // search of duplicates.

    ret = pdb_peer_data_ptr_get(p_event->peer_id, PM_PEER_DATA_ID_BONDING, &peer_data);

    if (ret != NRF_SUCCESS)
    {
        // @note emdi: this shouldn't happen, since the data was just stored, right?
        NRF_PM_DEBUG_CHECK(false);
        return;
    }

    pds_peer_data_iterate_prepare();

    while (pds_peer_data_iterate(PM_PEER_DATA_ID_BONDING, &peer_id, &peer_data_duplicate))
    {
        if (p_event->peer_id == peer_id)
        {
            // Skip the iteration if the bonding data retrieved is for a peer
            // with the same ID as the one contained in the event.
            continue;
        }

        if (im_is_duplicate_bonding_data(peer_data.p_bonding_data,
                                         peer_data_duplicate.p_bonding_data))
        {
            im_evt_t im_evt;
            im_evt.conn_handle                   = im_conn_handle_get(p_event->peer_id);
            im_evt.evt_id                        = IM_EVT_DUPLICATE_ID;
            im_evt.params.duplicate_id.peer_id_1 = p_event->peer_id;
            im_evt.params.duplicate_id.peer_id_2 = peer_id;
            evt_send(&im_evt);
            break;
        }
    }
}


ret_code_t im_init(void)
{
    NRF_PM_DEBUG_CHECK(!m_module_initialized);

    internal_state_reset();

    m_conn_state_user_flag_id = ble_conn_state_user_flag_acquire();
    if (m_conn_state_user_flag_id == BLE_CONN_STATE_USER_FLAG_INVALID)
    {
        return NRF_ERROR_INTERNAL;
    }

    #if (NRF_SD_BLE_API_VERSION <= 2)
        ret_code_t ret_code = sd_ble_gap_address_get(&m_current_id_addr);
        if (ret_code != NRF_SUCCESS)
        {
            return NRF_ERROR_INTERNAL;
        }
    #endif

    m_module_initialized = true;

    return NRF_SUCCESS;
}


pm_peer_id_t im_peer_id_get_by_conn_handle(uint16_t conn_handle)
{
    uint8_t conn_index;

    NRF_PM_DEBUG_CHECK(m_module_initialized);

    conn_index = get_connection_by_conn_handle(conn_handle);

    if (conn_index != IM_NO_INVALID_CONN_HANDLES)
    {
        return m_connections[conn_index].peer_id;
    }

    return PM_PEER_ID_INVALID;
}


ret_code_t im_ble_addr_get(uint16_t conn_handle, ble_gap_addr_t * p_ble_addr)
{
    uint8_t conn_index;

    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_ble_addr != NULL);

    conn_index = get_connection_by_conn_handle(conn_handle);

    if (conn_index != IM_NO_INVALID_CONN_HANDLES)
    {
        *p_ble_addr = m_connections[conn_index].peer_address;
        return NRF_SUCCESS;
    }

    return NRF_ERROR_NOT_FOUND;
}


bool im_master_ids_compare(ble_gap_master_id_t const * p_master_id1,
                           ble_gap_master_id_t const * p_master_id2)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_master_id1 != NULL);
    NRF_PM_DEBUG_CHECK(p_master_id2 != NULL);

    if (!im_master_id_is_valid(p_master_id1))
    {
        return false;
    }

    if (p_master_id1->ediv != p_master_id2->ediv)
    {
        return false;
    }

    return (memcmp(p_master_id1->rand, p_master_id2->rand, BLE_GAP_SEC_RAND_LEN) == 0);
}


pm_peer_id_t im_peer_id_get_by_master_id(ble_gap_master_id_t * p_master_id)
{
    pm_peer_id_t         peer_id;
    pm_peer_data_flash_t peer_data;

    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_master_id != NULL);

    pds_peer_data_iterate_prepare();

    // For each stored peer, check if the master_id matches p_master_id
    while (pds_peer_data_iterate(PM_PEER_DATA_ID_BONDING, &peer_id, &peer_data))
    {
        if (im_master_ids_compare(p_master_id, &peer_data.p_bonding_data->own_ltk.master_id) ||
            im_master_ids_compare(p_master_id, &peer_data.p_bonding_data->peer_ltk.master_id))
        {
            // If a matching master ID is found then return the peer ID.
            return peer_id;
        }
    }

    // If no matching master ID is found return PM_PEER_ID_INVALID.
    return PM_PEER_ID_INVALID;
}


uint16_t im_conn_handle_get(pm_peer_id_t peer_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    for (uint32_t i = 0; i < IM_MAX_CONN_HANDLES; i++)
    {
        if (peer_id == m_connections[i].peer_id)
        {
            return m_connections[i].conn_handle;
        }
    }
    return BLE_CONN_HANDLE_INVALID;
}


bool im_master_id_is_valid(ble_gap_master_id_t const * p_master_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    if (p_master_id->ediv != 0)
    {
        return true;
    }

    for (uint32_t i = 0; i < BLE_GAP_SEC_RAND_LEN; i++)
    {
        if (p_master_id->rand[i] != 0)
        {
            return true;
        }
    }
    return false;
}


/**@brief Function to set the peer ID associated with a connection handle.
 *
 * @param[in]  conn_handle  The connection handle.
 * @param[in]  peer_id      The peer ID to associate with @c conn_handle.
 */
static void peer_id_set(uint16_t conn_handle, pm_peer_id_t peer_id)
{
    uint8_t conn_index = get_connection_by_conn_handle(conn_handle);
    if (conn_index != IM_NO_INVALID_CONN_HANDLES)
    {
        m_connections[conn_index].peer_id = peer_id;
    }
}


void im_new_peer_id(uint16_t conn_handle, pm_peer_id_t peer_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    peer_id_set(conn_handle, peer_id);
}


ret_code_t im_peer_free(pm_peer_id_t peer_id)
{
    uint16_t   conn_handle;
    ret_code_t ret;

    NRF_PM_DEBUG_CHECK(m_module_initialized);

    conn_handle = im_conn_handle_get(peer_id);
    ret         = pdb_peer_free(peer_id);

    if ((conn_handle != BLE_CONN_HANDLE_INVALID) && (ret == NRF_SUCCESS))
    {
        peer_id_set(conn_handle, PM_PEER_ID_INVALID);
    }
    return ret;
}


/**@brief Given a list of peers, loads their GAP address and IRK into the provided buffers.
 */
static ret_code_t peers_id_keys_get(pm_peer_id_t   const * p_peers,
                                    uint32_t               peer_cnt,
                                    ble_gap_addr_t       * p_gap_addrs,
                                    uint32_t             * p_addr_cnt,
                                    ble_gap_irk_t        * p_gap_irks,
                                    uint32_t             * p_irk_cnt)
{
    ret_code_t ret;

    pm_peer_data_bonding_t bond_data;
    pm_peer_data_t         peer_data;

    uint32_t const buf_size = sizeof(bond_data);

    bool copy_addrs = false;
    bool copy_irks  = false;

    NRF_PM_DEBUG_CHECK(p_peers != NULL);

    // One of these two has to be provided.
    NRF_PM_DEBUG_CHECK((p_gap_addrs != NULL) || (p_gap_irks != NULL));

    if ((p_gap_addrs != NULL) && (p_addr_cnt != NULL))
    {
        NRF_PM_DEBUG_CHECK((*p_addr_cnt) >= peer_cnt);

        copy_addrs  = true;
        *p_addr_cnt = 0;
    }

    if ((p_gap_irks != NULL) && (p_irk_cnt != NULL))
    {
        NRF_PM_DEBUG_CHECK((*p_irk_cnt) >= peer_cnt);

        copy_irks  = true;
        *p_irk_cnt = 0;
    }

    memset(&peer_data, 0x00, sizeof(peer_data));
    peer_data.p_bonding_data = &bond_data;

    // Read through flash memory and look for peers ID keys.

    for (uint32_t i = 0; i < peer_cnt; i++)
    {
        memset(&bond_data, 0x00, sizeof(bond_data));

        // Read peer data from flash.
        ret = pds_peer_data_read(p_peers[i], PM_PEER_DATA_ID_BONDING,
                                 &peer_data, &buf_size);

        if ((ret == NRF_ERROR_NOT_FOUND) || (ret == NRF_ERROR_INVALID_PARAM))
        {
            // Peer data coulnd't be found in flash or peer ID is not valid.
            return NRF_ERROR_NOT_FOUND;
        }

        uint8_t const addr_type = bond_data.peer_ble_id.id_addr_info.addr_type;

        if ((addr_type != BLE_GAP_ADDR_TYPE_PUBLIC) &&
            (addr_type != BLE_GAP_ADDR_TYPE_RANDOM_STATIC))
        {
            // The address shared by the peer during bonding can't be used for whitelisting.
            return BLE_ERROR_GAP_INVALID_BLE_ADDR;
        }

        // Copy the GAP address.
        if (copy_addrs)
        {
            memcpy(&p_gap_addrs[i], &bond_data.peer_ble_id.id_addr_info, sizeof(ble_gap_addr_t));
            (*p_addr_cnt)++;
        }

        // Copy the IRK.
        if (copy_irks)
        {
            memcpy(&p_gap_irks[i], bond_data.peer_ble_id.id_info.irk, BLE_GAP_SEC_KEY_LEN);
            (*p_irk_cnt)++;
        }
    }

    return NRF_SUCCESS;
}


ret_code_t im_device_identities_list_set(pm_peer_id_t const * p_peers,
                                         uint32_t             peer_cnt)
{
    #if (NRF_SD_BLE_API_VERSION >= 3)

        ret_code_t             ret;
        pm_peer_data_t         peer_data;
        pm_peer_data_bonding_t bond_data;

        ble_gap_id_key_t         keys[BLE_GAP_DEVICE_IDENTITIES_MAX_COUNT];
        ble_gap_id_key_t const * key_ptrs[BLE_GAP_DEVICE_IDENTITIES_MAX_COUNT];

        if ((p_peers == NULL) || (peer_cnt == 0))
        {
            // Clear the device identities list.
            return sd_ble_gap_device_identities_set(NULL, NULL, 0);
        }

        peer_data.p_bonding_data = &bond_data;
        uint32_t const buf_size  = sizeof(bond_data);

        memset(keys, 0x00, sizeof(keys));
        for (uint32_t i = 0; i < BLE_GAP_DEVICE_IDENTITIES_MAX_COUNT; i++)
        {
            key_ptrs[i] = &keys[i];
        }

        for (uint32_t i = 0; i < peer_cnt; i++)
        {
            memset(&bond_data, 0x00, sizeof(bond_data));

            // Read peer data from flash.
            ret = pds_peer_data_read(p_peers[i], PM_PEER_DATA_ID_BONDING,
                                     &peer_data, &buf_size);

            if ((ret == NRF_ERROR_NOT_FOUND) || (ret == NRF_ERROR_INVALID_PARAM))
            {
                // Peer data coulnd't be found in flash or peer ID is not valid.
                return NRF_ERROR_NOT_FOUND;
            }

            uint8_t const addr_type = bond_data.peer_ble_id.id_addr_info.addr_type;

            if ((addr_type != BLE_GAP_ADDR_TYPE_PUBLIC) &&
                (addr_type != BLE_GAP_ADDR_TYPE_RANDOM_STATIC))
            {
                // The address shared by the peer during bonding can't be whitelisted.
                return BLE_ERROR_GAP_INVALID_BLE_ADDR;
            }

            // Copy data to the buffer.
            memcpy(&keys[i], &bond_data.peer_ble_id, sizeof(ble_gap_id_key_t));
        }

        return sd_ble_gap_device_identities_set(key_ptrs, NULL, peer_cnt);

    #else

        return NRF_ERROR_NOT_SUPPORTED;

    #endif
}


#if (NRF_SD_BLE_API_VERSION <= 2)

static ret_code_t address_set_v2(uint8_t cycle_mode, ble_gap_addr_t * p_addr)
{
    NRF_PM_DEBUG_CHECK(p_addr != NULL);

    ret_code_t ret = sd_ble_gap_address_set(cycle_mode, p_addr);

    switch (ret)
    {
        case NRF_SUCCESS:
        case NRF_ERROR_BUSY:
        case NRF_ERROR_INVALID_STATE:
        case NRF_ERROR_INVALID_PARAM:           // If cycle_mode is not AUTO or NONE.
        case BLE_ERROR_GAP_INVALID_BLE_ADDR:    // If the GAP address is not valid.
            return ret;

        default:
            return NRF_ERROR_INTERNAL;
    }
}

#endif


ret_code_t im_id_addr_set(ble_gap_addr_t const * p_addr)
{
    #if (NRF_SD_BLE_API_VERSION <= 2)

        ret_code_t     ret;
        ble_gap_addr_t current_addr;

        NRF_PM_DEBUG_CHECK(p_addr != NULL);

        (void) sd_ble_gap_address_get(&current_addr);

        ret = address_set_v2(BLE_GAP_ADDR_CYCLE_MODE_NONE, (ble_gap_addr_t *)p_addr);
        if (ret != NRF_SUCCESS)
        {
            return ret;
        }

        if (   current_addr.addr_type == BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE
            || current_addr.addr_type == BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_NON_RESOLVABLE)
        {
            // If currently using privacy, it must be re-enabled.
            // We force AUTO when privacy is enabled.
            ret = address_set_v2(BLE_GAP_ADDR_CYCLE_MODE_AUTO, &current_addr);
            if (ret != NRF_SUCCESS)
            {
                return ret;
            }
        }

        memcpy(&m_current_id_addr, p_addr, sizeof(ble_gap_addr_t));

        return NRF_SUCCESS;

    #else

        return sd_ble_gap_addr_set(p_addr);

    #endif
}


ret_code_t im_id_addr_get(ble_gap_addr_t * p_addr)
{
    NRF_PM_DEBUG_CHECK(p_addr != NULL);

    #if (NRF_SD_BLE_API_VERSION <= 2)
        memcpy(p_addr, &m_current_id_addr, sizeof(ble_gap_addr_t));
        return NRF_SUCCESS;
    #else
        return sd_ble_gap_addr_get(p_addr);
    #endif
}


ret_code_t im_privacy_set(pm_privacy_params_t const * p_privacy_params)
{
    #if (NRF_SD_BLE_API_VERSION <= 2)

        ret_code_t     ret;
        ble_gap_addr_t privacy_addr;
        ble_gap_irk_t  current_irk;
        ble_opt_t      privacy_options;
        ble_opt_t      current_privacy_options;

        NRF_PM_DEBUG_CHECK(p_privacy_params != NULL);

        privacy_addr.addr_type                        = p_privacy_params->private_addr_type;
        privacy_options.gap_opt.privacy.p_irk         = p_privacy_params->p_device_irk;
        privacy_options.gap_opt.privacy.interval_s    = p_privacy_params->private_addr_cycle_s;
        current_privacy_options.gap_opt.privacy.p_irk = &current_irk;

        // Can not fail.
        (void) sd_ble_opt_get(BLE_GAP_OPT_PRIVACY, &current_privacy_options);
        (void) sd_ble_opt_set(BLE_GAP_OPT_PRIVACY, &privacy_options);

        if (p_privacy_params->privacy_mode == BLE_GAP_PRIVACY_MODE_OFF)
        {
            ret = address_set_v2(BLE_GAP_ADDR_CYCLE_MODE_NONE, &m_current_id_addr);
        }
        else
        {
            ret = address_set_v2(BLE_GAP_ADDR_CYCLE_MODE_AUTO, &privacy_addr);
        }

        if (ret != NRF_SUCCESS)
        {
            // Restore previous settings.
            (void) sd_ble_opt_set(BLE_GAP_OPT_PRIVACY, &current_privacy_options);
        }

        // NRF_ERROR_BUSY,
        // NRF_ERROR_INVALID_STATE,
        // NRF_ERROR_INVALID_PARAM, if address type is not valid.
        return ret;

    #else

        return sd_ble_gap_privacy_set(p_privacy_params);

    #endif
}


ret_code_t im_privacy_get(pm_privacy_params_t * p_privacy_params)
{
    #if (NRF_SD_BLE_API_VERSION <= 2)

        ble_gap_addr_t cur_addr;
        ble_opt_t      cur_privacy_opt;

        NRF_PM_DEBUG_CHECK(p_privacy_params               != NULL);
        NRF_PM_DEBUG_CHECK(p_privacy_params->p_device_irk != NULL);

        cur_privacy_opt.gap_opt.privacy.p_irk = p_privacy_params->p_device_irk;

        // Can not fail.
        (void) sd_ble_gap_address_get(&cur_addr);

        if (   cur_addr.addr_type == BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE
            || cur_addr.addr_type == BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_NON_RESOLVABLE)
        {
            p_privacy_params->privacy_mode      = BLE_GAP_PRIVACY_MODE_DEVICE_PRIVACY;
            p_privacy_params->private_addr_type = cur_addr.addr_type;
        }
        else
        {
            p_privacy_params->privacy_mode = BLE_GAP_PRIVACY_MODE_OFF;
        }

        // Can not fail.
        (void) sd_ble_opt_get(BLE_GAP_OPT_PRIVACY, &cur_privacy_opt);

        p_privacy_params->private_addr_cycle_s = cur_privacy_opt.gap_opt.privacy.interval_s;

        return NRF_SUCCESS;

    #else

        return sd_ble_gap_privacy_get(p_privacy_params);

    #endif
}


/* Create a whitelist for the user using the cached list of peers.
 * This whitelist is meant to be provided by the application to the Advertising module.
 */
ret_code_t im_whitelist_get(ble_gap_addr_t * p_addrs,
                            uint32_t       * p_addr_cnt,
                            ble_gap_irk_t  * p_irks,
                            uint32_t       * p_irk_cnt)
{
    // One of the two buffers has to be provided.
    NRF_PM_DEBUG_CHECK((p_addrs    != NULL) || (p_irks    != NULL));
    NRF_PM_DEBUG_CHECK((p_addr_cnt != NULL) || (p_irk_cnt != NULL));

    if (((p_addr_cnt != NULL) && (m_wlisted_peer_cnt > *p_addr_cnt)) ||
        ((p_irk_cnt  != NULL) && (m_wlisted_peer_cnt > *p_irk_cnt)))
    {
        // The size of the cached list of peers is larger than the provided buffers.
        return NRF_ERROR_NO_MEM;
    }

    // NRF_SUCCESS or
    // NRF_ERROR_NOT_FOUND,            if a peer or its data were not found.
    // BLE_ERROR_GAP_INVALID_BLE_ADDR, if a peer address can not be used for whitelisting.
    return peers_id_keys_get(m_wlisted_peers, m_wlisted_peer_cnt,
                             p_addrs, p_addr_cnt,
                             p_irks,  p_irk_cnt);
}


/* Copies the peers to whitelist into a local cache.
 * The cached list will be used by im_whitelist_get() to retrieve the active whitelist.
 * For SoftDevices 3x, also loads the peers' GAP addresses and whitelists them using
 * sd_ble_gap_whitelist_set().
 */
ret_code_t im_whitelist_set(pm_peer_id_t const * p_peers,
                            uint32_t             peer_cnt)
{
    // Clear the cache of whitelisted peers.
    memset(m_wlisted_peers, 0x00, sizeof(m_wlisted_peers));

    if ((p_peers == NULL) || (peer_cnt == 0))
    {
        // Clear the current whitelist.
        m_wlisted_peer_cnt = 0;
        #if (NRF_SD_BLE_API_VERSION >= 3)
            // NRF_SUCCESS, or
            // BLE_GAP_ERROR_WHITELIST_IN_USE
            return sd_ble_gap_whitelist_set(NULL, 0);
        #else
            // The cached list of whitelisted peers is already cleared; nothing to do.
            return NRF_SUCCESS;
        #endif
    }

    // @todo emdi: should not ever cache more than BLE_GAP_WHITELIST_ADDR_MAX_COUNT...

    // Copy the new whitelisted peers.
    m_wlisted_peer_cnt = peer_cnt;
    memcpy(m_wlisted_peers, p_peers, sizeof(pm_peer_id_t) * peer_cnt);

    #if (NRF_SD_BLE_API_VERSION >= 3)

        ret_code_t ret;
        uint32_t   wlist_addr_cnt = 0;

        ble_gap_addr_t const * addr_ptrs[BLE_GAP_WHITELIST_ADDR_MAX_COUNT];
        ble_gap_addr_t         addrs[BLE_GAP_WHITELIST_ADDR_MAX_COUNT];

        memset(addrs, 0x00, sizeof(addrs));

        // Fetch GAP addresses for these peers, but don't fetch IRKs.
        ret = peers_id_keys_get(p_peers, peer_cnt, addrs, &wlist_addr_cnt, NULL, NULL);

        if (ret != NRF_SUCCESS)
        {
            // NRF_ERROR_NOT_FOUND,            if a peer or its data were not found.
            // BLE_ERROR_GAP_INVALID_BLE_ADDR, if a peer address can not be used for whitelisting.
            return ret;
        }

        for (uint32_t i = 0; i < BLE_GAP_WHITELIST_ADDR_MAX_COUNT; i++)
        {
            addr_ptrs[i] = &addrs[i];
        }

        // NRF_ERROR_DATA_SIZE,             if peer_cnt > BLE_GAP_WHITELIST_ADDR_MAX_COUNT.
        // BLE_ERROR_GAP_WHITELIST_IN_USE,  if a whitelist is in use.
        return sd_ble_gap_whitelist_set(addr_ptrs, peer_cnt);

    #else

        return NRF_SUCCESS;

    #endif
}


/**@brief Function for calculating the ah() hash function described in Bluetooth core specification
 *        4.2 section 3.H.2.2.2.
 *
 * @detail  BLE uses a hash function to calculate the first half of a resolvable address
 *          from the second half of the address and an irk. This function will use the ECB
 *          periferal to hash these data acording to the Bluetooth core specification.
 *
 * @note The ECB expect little endian input and output.
 *       This function expect big endian and will reverse the data as necessary.
 *
 * @param[in]  p_k          The key used in the hash function.
 *                          For address resolution this is should be the irk.
 *                          The array must have a length of 16.
 * @param[in]  p_r          The rand used in the hash function. For generating a new address
 *                          this would be a random number. For resolving a resolvable address
 *                          this would be the last half of the address being resolved.
 *                          The array must have a length of 3.
 * @param[out] p_local_hash The result of the hash operation. For address resolution this
 *                          will match the first half of the address being resolved if and only
 *                          if the irk used in the hash function is the same one used to generate
 *                          the address.
 *                          The array must have a length of 16.
 */
void ah(uint8_t const * p_k, uint8_t const * p_r, uint8_t * p_local_hash)
{
    nrf_ecb_hal_data_t ecb_hal_data;

    for (uint32_t i = 0; i < SOC_ECB_KEY_LENGTH; i++)
    {
        ecb_hal_data.key[i] = p_k[SOC_ECB_KEY_LENGTH - 1 - i];
    }

    memset(ecb_hal_data.cleartext, 0, SOC_ECB_KEY_LENGTH - IM_ADDR_CLEARTEXT_LENGTH);

    for (uint32_t i = 0; i < IM_ADDR_CLEARTEXT_LENGTH; i++)
    {
        ecb_hal_data.cleartext[SOC_ECB_KEY_LENGTH - 1 - i] = p_r[i];
    }

    // Can only return NRF_SUCCESS.
    (void) sd_ecb_block_encrypt(&ecb_hal_data);

    for (uint32_t i = 0; i < IM_ADDR_CIPHERTEXT_LENGTH; i++)
    {
        p_local_hash[i] = ecb_hal_data.ciphertext[SOC_ECB_KEY_LENGTH - 1 - i];
    }
}


bool im_address_resolve(ble_gap_addr_t const * p_addr, ble_gap_irk_t const * p_irk)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    uint8_t hash[IM_ADDR_CIPHERTEXT_LENGTH];
    uint8_t local_hash[IM_ADDR_CIPHERTEXT_LENGTH];
    uint8_t prand[IM_ADDR_CLEARTEXT_LENGTH];

    if (p_addr->addr_type != BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE)
    {
        return false;
    }

    memcpy(hash, p_addr->addr, IM_ADDR_CIPHERTEXT_LENGTH);
    memcpy(prand, &p_addr->addr[IM_ADDR_CIPHERTEXT_LENGTH], IM_ADDR_CLEARTEXT_LENGTH);
    ah(p_irk->irk, prand, local_hash);

    return (memcmp(hash, local_hash, IM_ADDR_CIPHERTEXT_LENGTH) == 0);
}
#endif // NRF_MODULE_ENABLED(PEER_MANAGER)
