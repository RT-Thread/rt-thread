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
#ifndef PEER_ID_MANAGER_H__
#define PEER_ID_MANAGER_H__

#include <stdint.h>
#include "sdk_errors.h"
#include "ble.h"
#include "ble_gap.h"
#include "peer_manager_types.h"
#include "peer_manager_internal.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @cond NO_DOXYGEN
 * @defgroup id_manager ID Manager
 * @ingroup peer_manager
 * @{
 * @brief An internal module of @ref peer_manager. A module for keeping track of peer identities
 *       (IRK and peer address).
 */


/**@brief Function for initializing the Identity manager.
 *
 * @retval NRF_SUCCESS          If initialization was successful.
 * @retval NRF_ERROR_INTERNAL   If an error occurred.
 */
ret_code_t im_init(void);


/**@brief Function for dispatching SoftDevice events to the ID Manager module.
 *
 * @param[in]  p_ble_evt  The SoftDevice event.
 */
void im_ble_evt_handler(ble_evt_t const * p_ble_evt);


/**@brief Function for getting the corresponding peer ID from a connection handle.
 *
 * @param[in]  conn_handle  The connection handle.
 *
 * @return The corresponding peer ID, or @ref PM_PEER_ID_INVALID if none could be resolved.
 */
pm_peer_id_t im_peer_id_get_by_conn_handle(uint16_t conn_handle);


/**@brief Function for getting the corresponding peer ID from a master ID (EDIV and rand).
 *
 * @param[in]  p_master_id  The master ID.
 *
 * @return The corresponding peer ID, or @ref PM_PEER_ID_INVALID if none could be resolved.
 */
pm_peer_id_t im_peer_id_get_by_master_id(ble_gap_master_id_t const * p_master_id);


/**@brief Function for getting the corresponding connection handle from a peer ID.
 *
 * @param[in] peer_id  The peer ID.
 *
 * @return The corresponding connection handle, or @ref BLE_CONN_HANDLE_INVALID if none could be
 *         resolved.
 */
uint16_t im_conn_handle_get(pm_peer_id_t peer_id);


/**@brief Function for comparing two master ids
 * @note  Two invalid master IDs will not match.
 *
 * @param[in]  p_master_id1 First master id for comparison
 * @param[in]  p_master_id2 Second master id for comparison
 *
 * @return     True if the input matches, false if it does not.
 */
bool im_master_ids_compare(ble_gap_master_id_t const * p_master_id1,
                           ble_gap_master_id_t const * p_master_id2);


/**@brief Function for getting the BLE address used by the peer when connecting.
 *
 * @param[in]  conn_handle  The connection handle.
 * @param[out] p_ble_addr   The BLE address used by the peer when the connection specified by
 *                          conn_handle was established.
 *
 * @retval NRF_SUCCESS                   The address was found and copied.
 * @retval BLE_ERROR_CONN_HANDLE_INVALID conn_handle does not refer to an active connection.
 * @retval NRF_ERROR_NULL                p_ble_addr was NULL.
 */
ret_code_t im_ble_addr_get(uint16_t conn_handle, ble_gap_addr_t * p_ble_addr);


/**@brief Function for checking if a master ID is valid or invalid
 *
 * @param[in]  p_master_id  The master ID.
 *
 * @retval true   The master id is valid.
 * @retval false  The master id is invalid (i.e. all zeros).
 */
bool im_master_id_is_valid(ble_gap_master_id_t const * p_master_id);


/**@brief Function for checking if two pieces of bonding data correspond to the same peer.
 *
 * @param[in]  p_bonding_data1  The first piece of bonding data to check.
 * @param[in]  p_bonding_data2  The second piece of bonding data to check.
 *
 * @retval true   The bonding data correspond to the same peer.
 * @retval false  The bonding data do not correspond to the same peer.
 */
bool im_is_duplicate_bonding_data(pm_peer_data_bonding_t const * p_bonding_data1,
                                  pm_peer_data_bonding_t const * p_bonding_data2);


/**@brief Function for finding if we are already bonded to a peer.
 *
 * @param[in]  p_bonding_data  The bonding data to check.
 * @param[in]  peer_id_skip    Optional peer to ignore when searching for duplicates.
 *
 * @return  An existing peer ID for the peer, or PM_PEER_ID_INVALID if none was found.
 */
pm_peer_id_t im_find_duplicate_bonding_data(pm_peer_data_bonding_t const * p_bonding_data,
                                            pm_peer_id_t                   peer_id_skip);


/**@brief Function for reporting that a new peer ID has been allocated for a specified connection.
 *
 * @param[in]  conn_handle  The connection.
 * @param[in]  peer_id      The new peer ID.
 */
void im_new_peer_id(uint16_t conn_handle, pm_peer_id_t peer_id);


/**@brief Function for deleting all of a peer's data from flash and disassociating it from any
 *        connection handles it is associated with.
 *
 * @param[in]  peer_id  The peer to free.
 *
 * @return Any error code returned by @ref pdb_peer_free.
 */
ret_code_t im_peer_free(pm_peer_id_t peer_id);


/**@brief Function to set the local Bluetooth identity address.
 *
 * @details The local Bluetooth identity address is the address that identifies this device to other
 *          peers. The address type must be either @ref BLE_GAP_ADDR_TYPE_PUBLIC or @ref
 *          BLE_GAP_ADDR_TYPE_RANDOM_STATIC. The identity address cannot be changed while roles are
 *          running.
 *
 * @note This address will be distributed to the peer during bonding.
 *       If the address changes, the address stored in the peer device will not be valid and the
 *       ability to reconnect using the old address will be lost.
 *
 * @note By default the SoftDevice will set an address of type @ref BLE_GAP_ADDR_TYPE_RANDOM_STATIC
 *       upon being enabled. The address is a random number populated during the IC manufacturing
 *       process and remains unchanged for the lifetime of each IC.
 *
 * @param[in] p_addr Pointer to address structure.
 *
 * @retval NRF_SUCCESS                     Address successfully set.
 * @retval BLE_ERROR_GAP_INVALID_BLE_ADDR  If the GAP address is invalid.
 * @retval NRF_ERROR_BUSY                  Could not process at this time. Process SoftDevice events
 *                                         and retry.
 * @retval NRF_ERROR_INVALID_STATE         The identity address cannot be changed while advertising,
 *                                         scanning, or while in a connection.
 * @retval NRF_ERROR_INTERNAL              If an internal error occurred.
 */
ret_code_t im_id_addr_set(ble_gap_addr_t const * p_addr);


/**@brief Function to get the local Bluetooth identity address.
 *
 * @note This will always return the identity address irrespective of the privacy settings,
 *       i.e. the address type will always be either @ref BLE_GAP_ADDR_TYPE_PUBLIC or @ref
 *       BLE_GAP_ADDR_TYPE_RANDOM_STATIC.
 *
 * @param[out] p_addr Pointer to address structure to be filled in.
 *
 * @retval NRF_SUCCESS  If the address was successfully retrieved.
 */
ret_code_t im_id_addr_get(ble_gap_addr_t * p_addr);


/**@brief Function to set privacy settings.
 *
 * @details Privacy settings cannot be set while advertising, scanning, or while in a connection.
 *
 * @param[in] p_privacy_params Privacy settings.
 *
 * @retval NRF_SUCCESS              If privacy options were set successfully.
 * @retval NRF_ERROR_NULL           If @p p_privacy_params is NULL.
 * @retval NRF_ERROR_INVALID_PARAM  If the address type is not valid.
 * @retval NRF_ERROR_BUSY           If the request could not be processed at this time.
 *                                  Process SoftDevice events and retry.
 * @retval NRF_ERROR_INVALID_STATE  Privacy settings cannot be changed while BLE roles using
 *                                  privacy are enabled.
 */
ret_code_t im_privacy_set(pm_privacy_params_t const * p_privacy_params);


/**@brief Function to retrieve the current privacy settings.
 *
 * @details The privacy settings returned include the current device irk as well.
 *
 * @param[in] p_privacy_params Privacy settings.
 *
 * @retval NRF_SUCCESS            Successfully retrieved privacy settings.
 * @retval NRF_ERROR_NULL         @c p_privacy_params is NULL.
 * @retval NRF_ERROR_INTERNAL     If an internal error occurred.
 */
ret_code_t im_privacy_get(pm_privacy_params_t * p_privacy_params);


/**@brief Function for resolving a resolvable address with an identity resolution key (IRK).
 *
 * @details This function will use the ECB peripheral to resolve a resolvable address.
 *          This can be used to resolve the identity of a device distributing a random
 *          resolvable address based on any IRKs you have received earlier. If an address is
 *          resolved by an IRK, the device distributing the address must also know the IRK.
 *
 * @param[in] p_addr  A random resolvable address.
 * @param[in] p_irk   An identity resolution key (IRK).
 *
 * @retval true   The irk used matched the one used to create the address.
 * @retval false  The irk used did not match the one used to create the address, or an argument was
 *                NULL.
 */
bool im_address_resolve(ble_gap_addr_t const * p_addr, ble_gap_irk_t const * p_irk);


/**@brief Function for setting / clearing the whitelist.
 *
 * @param p_peers   The peers to whitelist. Pass NULL to clear the whitelist.
 * @param peer_cnt  The number of peers to whitelist. Pass zero to clear the whitelist.
 *
 * @retval NRF_SUCCESS                      If the whitelist was successfully set or cleared.
 * @retval BLE_GAP_ERROR_WHITELIST_IN_USE   If a whitelist is in use.
 * @retval BLE_ERROR_GAP_INVALID_BLE_ADDR   If any peer has an address which can not be used
 *                                          for whitelisting.
 * @retval NRF_ERROR_NOT_FOUND              If any peer or its data could not be found.
 * @retval NRF_ERROR_DATA_SIZE              If @p peer_cnt is greater than
 *                                          @ref BLE_GAP_WHITELIST_ADDR_MAX_COUNT.
 */
ret_code_t im_whitelist_set(pm_peer_id_t const * p_peers,
                            uint32_t     const   peer_cnt);


/**@brief Retrieves the current whitelist, set by a previous call to @ref im_whitelist_set.
 *
 * @param[out]   A buffer where to copy the GAP addresses.
 * @param[inout] In: the size of the @p p_addrs buffer.
 *               Out: the number of address copied into the buffer.
 * @param[out]   A buffer where to copy the IRKs.
 * @param[inout] In: the size of the @p p_irks buffer.
 *               Out: the number of IRKs copied into the buffer.
 *
 * @retval NRF_SUCCESS                      If the whitelist was successfully retreived.
 * @retval BLE_ERROR_GAP_INVALID_BLE_ADDR   If any peer has an address which can not be used for
 *                                          whitelisting.
 * @retval NRF_ERROR_NOT_FOUND              If the data for any of the cached whitelisted peers
 *                                          can not be found anymore. It might have been deleted in
 *                                          the meanwhile.
 * @retval NRF_ERROR_NO_MEM                 If the provided buffers are too small.
 */
ret_code_t im_whitelist_get(ble_gap_addr_t * p_addrs,
                            uint32_t       * p_addr_cnt,
                            ble_gap_irk_t  * p_irks,
                            uint32_t       * p_irk_cnt);


/**@brief Set the device identities list.
 */
ret_code_t im_device_identities_list_set(pm_peer_id_t const * p_peers,
                                         uint32_t             peer_cnt);


/** @}
 * @endcond
 */


#ifdef __cplusplus
}
#endif

#endif /* PEER_ID_MANAGER_H__ */
